/************************************************************************************************/
/** 
 * @file		ComputeTile.fx
 * @brief		ライトを反映させる
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef COMPUTE_TILE_FX
#define COMPUTE_TILE_FX

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "Rendering.fx"
#include "GBuffer.fx"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
RWStructuredBuffer<uint2>	g_Framebuffer : register(u0);
groupshared uint			s_MinZ;
groupshared uint			s_MaxZ;
groupshared uint			s_TileLightIndices[MAX_LIGHTS];
groupshared uint			s_TileNumLights;
groupshared uint			s_PerSamplePixels[COMPUTE_SHADER_TILE_GROUP_SIZE];
groupshared uint			s_NumPerSamplePixels;

/************************************************************************************************/
/**
 * Utility for writing to our flat MSAAed UAV
 */
/************************************************************************************************/
void WriteSample(uint2 coords, uint sampleIndex, float4 value)
{
	g_Framebuffer[ GetFramebufferSampleAddress(coords, sampleIndex) ] = PackRGBA16(value);
}

/************************************************************************************************/
/**
 * Pack and unpack two <=16-bit coordinates into a single uint
 */
/************************************************************************************************/
uint PackCoords(uint2 coords)
{
    return coords.y << 16 | coords.x;
}

/************************************************************************************************/
/**
 * 
 */
/************************************************************************************************/
uint2 UnpackCoords(uint coords)
{
    return uint2(coords & 0xFFFF, coords >> 16);
}

/************************************************************************************************/
/**
 * ライティング
 */
/************************************************************************************************/
[numthreads(COMPUTE_SHADER_TILE_GROUP_DIM, COMPUTE_SHADER_TILE_GROUP_DIM, 1)]
void CS_LightingTile( uint3 groupId          : SV_GroupID,
                      uint3 dispatchThreadId : SV_DispatchThreadID,
                      uint3 groupThreadId    : SV_GroupThreadID
                      )
{
	uint		groupIndex = groupThreadId.y * COMPUTE_SHADER_TILE_GROUP_DIM + groupThreadId.x;
	uint		totalLights;		
	uint		dummy;

	// トータルのポイントライト数を取得する
	g_Light.GetDimensions( totalLights, dummy );

	uint2			globalCoords = dispatchThreadId.xy;
	KsSurfaceData	surfaceSamples[ MSAA_SAMPLES ];

	// G-Bufferから情報を取得する
	KsComputeSurfaceDataFromGBufferAllSamples( globalCoords, surfaceSamples );

	// Work out Z bounds for our samples
	float		minZSample = CameraNearFar.y;
	float		maxZSample = CameraNearFar.x;
	{
		for( uint sample = 0; sample < MSAA_SAMPLES; ++sample )
		{
			// Avoid shading skybox/background or otherwise invalid pixels
			float viewSpaceZ = surfaceSamples[sample].PositionView.z;
			bool  validPixel = viewSpaceZ >= CameraNearFar.x && viewSpaceZ <  CameraNearFar.y;

			if( validPixel )
			{
				minZSample = min( minZSample, viewSpaceZ );
				maxZSample = max( maxZSample, viewSpaceZ );
			}
		}
	}

	// Initialize shared memory light list and Z bounds
	if( groupIndex == 0 )
	{
		s_TileNumLights      = 0;
		s_NumPerSamplePixels = 0;
		s_MinZ               = 0x7F7FFFFF;		// Max float
		s_MaxZ               = 0;
	}

	GroupMemoryBarrierWithGroupSync();

	// NOTE: Can do a parallel reduction here but now that we have MSAA and store sample frequency pixels
	if( maxZSample >= minZSample )
	{
		InterlockedMin(s_MinZ, asuint(minZSample));
		InterlockedMax(s_MaxZ, asuint(maxZSample));
	}

	GroupMemoryBarrierWithGroupSync();

	float minTileZ = asfloat(s_MinZ);
	float maxTileZ = asfloat(s_MaxZ);

	// Work out scale/bias from [0, 1]
	float2 tileScale = float2(FramebufferDimensions.xy) * rcp(float(2 * COMPUTE_SHADER_TILE_GROUP_DIM));
	float2 tileBias = tileScale - float2(groupId.xy);

	// Now work out composite projection matrix
	// Relevant matrix columns for this tile frusta
	float4 c1 = float4(Proj._11 * tileScale.x, 0.0f, tileBias.x, 0.0f);
	float4 c2 = float4(0.0f, -Proj._22 * tileScale.y, tileBias.y, 0.0f);
	float4 c4 = float4(0.0f, 0.0f, 1.0f, 0.0f);

	// Derive frustum planes
	float4 frustumPlanes[6];
	// Sides
	frustumPlanes[0] = c4 - c1;
	frustumPlanes[1] = c4 + c1;
	frustumPlanes[2] = c4 - c2;
	frustumPlanes[3] = c4 + c2;
	// Near/far
	frustumPlanes[4] = float4(0.0f, 0.0f,  1.0f, -minTileZ);
	frustumPlanes[5] = float4(0.0f, 0.0f, -1.0f,  maxTileZ);

	// Normalize frustum planes (near/far already normalized)
	for (uint i = 0; i < 4; ++i)
	{
		frustumPlanes[i] *= rcp(length(frustumPlanes[i].xyz));
	}

	// タイルベースでライトをカリングする
	for( uint lightIndex = groupIndex; lightIndex < totalLights; lightIndex += COMPUTE_SHADER_TILE_GROUP_SIZE )
	{
		PointLight light = g_Light[ lightIndex ];

		// Cull: point light sphere vs tile frustum
		bool inFrustum = true;
		
		for( uint i = 0; i < 6; ++i )
		{
			float d = dot(frustumPlanes[i], float4(light.PositionView, 1.0f));
			inFrustum = inFrustum && (d >= -light.AttenuationEnd);
		}

		if( inFrustum )
		{
			// Append light to list
			// Compaction might be better if we expect a lot of lights
			uint listIndex;
			InterlockedAdd(s_TileNumLights, 1, listIndex);
			s_TileLightIndices[ listIndex ] = lightIndex;
		}
	}

	GroupMemoryBarrierWithGroupSync();

	uint numLights = s_TileNumLights;

	// ret all(x)
	// 指定された値のすべての成分が 0 以外であるかどうかを判断します。
	// x パラメーターのすべての成分が 0 以外である場合は True、それ以外の場合は false。

	// 画面ないかのチェック
	if( all(globalCoords < FramebufferDimensions.xy) )
	{
		if( numLights > 0 )
		{
			for( uint sample = 0; sample < MSAA_SAMPLES; ++sample )
			{
				float3 lit = float3( 0.0f, 0.0f, 0.0f );

				for( uint tileLightIndex = 0; tileLightIndex < numLights; ++tileLightIndex )
				{
					PointLight light = g_Light[ s_TileLightIndices[ tileLightIndex ] ];
					AccumulateBRDF(surfaceSamples[0], light, lit);
				}

				// サーフェイスに書き込む
				WriteSample( globalCoords, sample, float4(lit, 1.0f) );

				// 本当はいらない
				WriteSample( globalCoords, sample, surfaceSamples[0].Albedo );
			}
		}
	}

	#if DEFER_PER_SAMPLE && MSAA_SAMPLES > 1
		GroupMemoryBarrierWithGroupSync();

		// Now handle any pixels that require per-sample shading
		// NOTE: Each pixel requires MSAA_SAMPLES - 1 additional shading passes
		const uint shadingPassesPerPixel = MSAA_SAMPLES - 1;
		uint globalSamples = s_NumPerSamplePixels * shadingPassesPerPixel;

		for (uint globalSample = groupIndex; globalSample < globalSamples; globalSample += COMPUTE_SHADER_TILE_GROUP_SIZE) {
			uint listIndex = globalSample / shadingPassesPerPixel;
			uint sampleIndex = globalSample % shadingPassesPerPixel + 1;        // sample 0 has been handled earlier

			uint2 sampleCoords = UnpackCoords(s_PerSamplePixels[listIndex]);
			KsSurfaceData surface = KsComputeSurfaceDataFromGBufferSample(sampleCoords, sampleIndex);

			float3 lit = float3(0.0f, 0.0f, 0.0f);
			for (uint tileLightIndex = 0; tileLightIndex < numLights; ++tileLightIndex) {
				PointLight light = g_Light[s_TileLightIndices[tileLightIndex]];
				AccumulateBRDF(surface, light, lit);
			}
			WriteSample(sampleCoords, sampleIndex, float4(lit, 1.0f));
		}
	#endif
}
#if 0
/************************************************************************************************/
/**
 * 並行光源の計算
 */
/************************************************************************************************/
float3 KsLambert( float3 float3 )
{
	float3 P = input.objPosition.xyz;
	float3 N = normalize(input.normal);

	//　Ambient Color
	float3 ambient = gAmbient * Ka;
	
	//　Diffuse Color
	float3 L = normalize(lightPosition - P);	//　ローカル座標系のでのライトベクトル
	float diffuseLight = max(dot(L, N), 0);
	float3 diffuse = Kd * lightColor * diffuseLight;

	return ( ambient + diffuse );
}

/************************************************************************************************/
/**
 * 半球ライティングの計算
 */
/************************************************************************************************/
float3 HalfLambertPS(VertexOutput input)
{
	float3 P = input.objPosition.xyz;
	float3 N = normalize(input.normal);

	//　Ambient Color
	float3 ambient = gAmbient * Ka;
	
	//　Diffuse Color
	float3 L = normalize(lightPosition - P);	//　ローカル座標系のでのライトベクトル
	float diffuseLight = max(dot(L, N), 0) * 0.5 + 0.5;
	float3 diffuse = Kd * lightColor * (diffuseLight * diffuseLight);

	return float4(ambient + diffuse, 1.0f);
}


float4 RimLighting(VertexShaderOutput input) : COLOR0
00082:  {
00083:      // TODO: add your pixel shader code here.
00084:  	float3 N = normalize( input.Normal );
00085:  	float3 E = normalize( CameraPosition - input.WorldPosition );
00086:  	float3 L = normalize( - LightDirection );
00087:  
00088:  	float3 Ambient = input.Color * 0.3;
00089:  	float3 Diffuse = input.Color * ( max( dot( N, L ), 0 ) * 0.5 + 0.5 );
00090:  	float3 Rim = RimColor * Kr * pow( 1 - dot( N, E ), Power );
00091:  
00092:  	float4 color = float4( Ambient + Diffuse + Rim, 1.0f );
00093:  
00094:      return color;
00095:  }


 float4 PixelShaderFunction( VertexShaderOutput input ) : COLOR
00075:  {
00076:  	float3 N = normalize( input.Normal );
00077:  	float3 E = normalize( input.Eye );
00078:  	float3 L = normalize( input.Light );
00079:  	float3 H = normalize( L + E );
00080:  	float3 A = normalize( HemiSphereAxis );
00081:  
00082:  	float4 output;
00083:  	float amount = (dot( N, A )+1) * 0.5;
00084:  	float3 hemisphere = lerp( GroundColor, SkyColor, amount ) * 0.8;
00085:  	float3 ambient = input.Color.rgb * 0.2;
00086:  	float3 diffuse = input.Color.rgb * max( dot( N, L ), 0 );
00087:  	float3 specular = input.Color.rgb * 0.6 * pow( max( dot( N, H ), 0 ), 25.0f );
00088:  
00089:  	output.rgb = ( hemisphere + ambient + diffuse + specular );
00090:  	output.a = 1.0;
00091:  
00092:  	return output;
00093:  }
#endif

#endif // COMPUTE_TILE_FX

