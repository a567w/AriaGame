/************************************************************************************************/
/** 
 * @file		GBuffer.fx
 * @brief		G-バッファ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef GBUFFER_FX
#define GBUFFER_FX

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "Common.fxh"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

Texture2DMS<float4, MSAA_SAMPLES> g_GBufferTextures[ 4 ] : register(t0);

Texture2D		g_AlbedoTexture : register( t0 );

SamplerState	g_AlbedoSampler : register( s0 )
{
	Filter   = MIN_MAG_MIP_LINEAR;
	AddressU = Clamp;
	AddressV = Clamp;
};

/************************************************************************************************/
/**
 * @struct		VS_INPUT
 * @brief		G-バッファ出力,構造体
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
struct VS_INPUT
{
	float3 Position    : POSITION;
	float3 Normal      : NORMAL;
	float2 TexCoord    : TEXCOORD;
	uint4  BoneIndices : BLENDINDICES;
	float4 BoneWeights : BLENDWEIGHT;
};

/************************************************************************************************/
/**
 * @struct		VS_OUTPUT
 * @brief		G-バッファ出力,構造体
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
struct VS_OUTPUT
{
	float4	Position     : SV_Position;
	float3	PositionView : POSITIONVIEW;
	float3	Normal       : NORMAL;
	float2	TexCoord     : TEXCOORD;
};


/************************************************************************************************/
/**
 * @struct		PS_OUTPUT
 * @brief		G-バッファ出力,構造体
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
struct PS_OUTPUT
{
	float4	Normal_Specular : SV_Target0;
	float4	Albedo          : SV_Target1;
	float2	PositionZGrad   : SV_Target2;
};

/************************************************************************************************/
/**
 * 球状環境マッピング(法線情報)
 * 環境マッピングの対象となる各頂点に指定するテクスチャ座標の公式
 * u = Nx/2 + 0.5
 * v = Ny/2 + 0.5
 */
/************************************************************************************************/
float2 KsEncodeSphereMap( float3 normal )
{
	float oneMinusZ = 1.0f - normal.z;	// 0.0～1.0にする
	float len       = sqrt(normal.x * normal.x + normal.y * normal.y + oneMinusZ * oneMinusZ);

	return normal.xy / len * 0.5f + 0.5f;
}

/************************************************************************************************/
/**
 * 球状環境マッピング(法線情報)
 * 環境マッピングの対象となる各頂点に指定するテクスチャ座標の公式
 * u = Nx/2 + 0.5
 * v = Ny/2 + 0.5
 */
/************************************************************************************************/
float3 KsDecodeSphereMap( float2 e )
{
	float2 tmp = e - e * e;
	float  f   = tmp.x + tmp.y;
	float  m   = sqrt( 4.0f * f - 1.0f );

	float3	n;

	n.xy = m * (e * 4.0f - 2.0f);
	n.z  = 3.0f - 8.0f * f;

	return n;
}

/************************************************************************************************/
/**
 * Zからの位置座標に変換する
 */
/************************************************************************************************/
float3 KsComputePositionViewFromZ( float2 posScreen, float viewSpaceZ )
{
	float2 screenSpaceRay = float2( posScreen.x / Proj._11, posScreen.y / Proj._22 );
	
	float3 positionView;

	positionView.z  = viewSpaceZ;
	positionView.xy = screenSpaceRay.xy * positionView.z;

	return positionView;
}

/************************************************************************************************/
/**
 * スクリーン空間の x 座標に対する低精度の偏微分を計算します。
 */
/************************************************************************************************/
float3 KsComputeFaceNormal( float3 position )
{
	return cross( ddx_coarse(position), ddy_coarse(position) );
}

/************************************************************************************************/
/**
 * サーフェースデータを取得する
 */
/************************************************************************************************/
KsSurfaceData KsComputeSurfaceData( VS_OUTPUT In )
{
	KsSurfaceData	surface;

	surface.PositionView   = In.PositionView;
	surface.PositionViewDX = ddx_coarse( surface.PositionView );
	surface.PositionViewDY = ddy_coarse( surface.PositionView );
	surface.Normal         = In.Normal;
	surface.Albedo         = g_AlbedoTexture.Sample( g_AlbedoSampler, In.TexCoord );
	surface.SpecularAmount = 0.9f;
	surface.SpecularPower  = 25.0f;

	//uint2		textureDim;
	//g_AlbedoTexture.GetDimensions( textureDim.x, textureDim.y );
	//surface.Albedo = (textureDim.x == 0U ? float4(1.0f, 1.0f, 1.0f, 1.0f) : surface.Albedo);  

	return surface;
}

/************************************************************************************************/
/**
 *  * G-Buffer用 頂点シェーダー
 */
/************************************************************************************************/
VS_OUTPUT VS_GBuffer( VS_INPUT In )
{
	VS_OUTPUT	Out;

	float4x4	skinTransform = 0;

	skinTransform += MatrixPalette[ In.BoneIndices.x ] * In.BoneWeights.x;
	skinTransform += MatrixPalette[ In.BoneIndices.y ] * In.BoneWeights.y;
	skinTransform += MatrixPalette[ In.BoneIndices.z ] * In.BoneWeights.z;
	skinTransform += MatrixPalette[ In.BoneIndices.w ] * In.BoneWeights.w;

	float4	position = mul( float4( In.Position, 1.0f ), skinTransform );
	float4	normal   = mul( float4( In.Normal,   0.0f ), skinTransform );

	Out.Position     = mul( position, WorldViewProj );
	Out.PositionView = mul( position, WorldView ).xyz;
	Out.Normal       = mul( normal,   WorldView ).xyz;
	Out.TexCoord     = In.TexCoord;

	return Out;
}

/************************************************************************************************/
/**
 * G-Buffer用 ピクセルシェーダー
 * MRTでそれぞれのターゲットに出力する
 * Normal_Specular : SV_Target0;
 * Albedo          : SV_Target1;
 * PositionZGrad   : SV_Target2;
 */
/************************************************************************************************/
PS_OUTPUT PS_GBuffer( VS_OUTPUT In )
{
	PS_OUTPUT		GBuffer;

	KsSurfaceData	surface = KsComputeSurfaceData( In );

	GBuffer.Normal_Specular = float4( KsEncodeSphereMap(surface.Normal), surface.SpecularAmount, surface.SpecularPower );
	GBuffer.Albedo          = surface.Albedo;
	GBuffer.PositionZGrad   = float2( ddx_coarse(surface.PositionView.z), ddy_coarse(surface.PositionView.z) );

	return GBuffer;
}

/************************************************************************************************/
/**
 * G-Buffer用 ピクセルシェーダー(アルファテストする)
 * MRTでそれぞれのターゲットに出力する
 * Normal_Specular : SV_Target0;
 * Albedo          : SV_Target1;
 * PositionZGrad   : SV_Target2;
 */
/************************************************************************************************/
PS_OUTPUT PS_GBufferAlphaTest( VS_OUTPUT In )
{
	PS_OUTPUT	GBuffer = PS_GBuffer( In );

	clip( GBuffer.Albedo.a - 0.3f );

	GBuffer.Normal_Specular.xy = KsEncodeSphereMap( normalize( KsComputeFaceNormal( In.PositionView ) ) );

	return GBuffer;
}


/************************************************************************************************/
/**
 * G-Bufferから情報を取得する
 */
/************************************************************************************************/
KsSurfaceData KsComputeSurfaceDataFromGBufferSample( uint2 positionViewport, uint sampleIndex )
{
	// Load the raw data from the GBuffer
	PS_OUTPUT		rawData;
	rawData.Normal_Specular = g_GBufferTextures[0].Load( positionViewport.xy, sampleIndex ).xyzw;
	rawData.Albedo          = g_GBufferTextures[1].Load( positionViewport.xy, sampleIndex ).xyzw;
	rawData.PositionZGrad   = g_GBufferTextures[2].Load( positionViewport.xy, sampleIndex ).xy;
	float           zBuffer = g_GBufferTextures[3].Load( positionViewport.xy, sampleIndex ).x;

	float2		gbufferDim;
	uint		dummy;

	g_GBufferTextures[0].GetDimensions( gbufferDim.x, gbufferDim.y, dummy );

	float2 screenPixelOffset = float2(2.0f, -2.0f) / gbufferDim;
	float2 positionScreen    = (float2(positionViewport.xy) + 0.5f) * screenPixelOffset.xy + float2(-1.0f, 1.0f);
	float2 positionScreenX   = positionScreen + float2(screenPixelOffset.x, 0.0f);
	float2 positionScreenY   = positionScreen + float2(0.0f, screenPixelOffset.y);

	// Decode into reasonable outputs
	KsSurfaceData data;

	// Unproject depth buffer Z value into view space
	float viewSpaceZ = Proj._43 / (zBuffer - Proj._33);

	data.PositionView   = KsComputePositionViewFromZ( positionScreen, viewSpaceZ );
	data.PositionViewDX = KsComputePositionViewFromZ( positionScreenX, viewSpaceZ + rawData.PositionZGrad.x ) - data.PositionView;
	data.PositionViewDY = KsComputePositionViewFromZ( positionScreenY, viewSpaceZ + rawData.PositionZGrad.y ) - data.PositionView;
	data.Normal         = KsDecodeSphereMap( rawData.Normal_Specular.xy );
	data.Albedo         = rawData.Albedo;
	data.SpecularAmount = rawData.Normal_Specular.z;
	data.SpecularPower  = rawData.Normal_Specular.w;

	return data;
}

/************************************************************************************************/
/**
 * G-Bufferから情報を取得する(MSAA対応)
 */
/************************************************************************************************/
void KsComputeSurfaceDataFromGBufferAllSamples( uint2 positionViewport, out KsSurfaceData surface[ MSAA_SAMPLES ] )
{
	for( uint i = 0; i < MSAA_SAMPLES; ++i )
	{
		surface[i] = KsComputeSurfaceDataFromGBufferSample( positionViewport, i );
	}
}

//TextureCube<float4>					gSkyboxTexture : register(t5);
//Texture2DMS<float, MSAA_SAMPLES>	gDepthTexture : register(t6);
//Texture2DMS<float4, MSAA_SAMPLES>	gLitTexture : register(t7);
StructuredBuffer<uint2>				gLitTextureFlat : register(t8);

struct VS_INPUT_DEFERRED
{
	float3 Position : POSITION;
};

struct VS_OUTPUT_DEFERRED
{
	float4 Position : SV_Position;
};


VS_OUTPUT_DEFERRED VS_Deferred( VS_INPUT_DEFERRED In )
{
	VS_OUTPUT_DEFERRED	Out;

	//Out.Position = mul( float4( In.Position, 0.0f ), ViewProj ).xyww;
	//Out.Position = float4( In.Position, 1.0f );
	Out.Position = float4( In.Position, 1.0f );

	return Out;
}

float4 PS_Deferred( VS_OUTPUT_DEFERRED In ) : SV_Target0
{
	uint2	coords = In.Position.xy;

	uint	sampleIndex = 0;
	
	uint	pixelIndex = GetFramebufferSampleAddress(coords, sampleIndex);
	uint2	pixelData  = gLitTextureFlat[ pixelIndex ];
	float4	pixelColor = UnpackRGBA16( pixelData );

	float4 color = float4( pixelColor.xyz, 1.0f );

	return color;
}

#if 0
    // Use the flattened MSAA lit buffer if provided
    uint2 dims;
    gLitTextureFlat.GetDimensions(dims.x, dims.y);
    bool useFlatLitBuffer = dims.x > 0;
    
    uint2 coords = input.positionViewport.xy;

    float3 lit = float3(0.0f, 0.0f, 0.0f);
    float skyboxSamples = 0.0f;
    #if MSAA_SAMPLES <= 1
    [unroll]
    #endif
    for (unsigned int sampleIndex = 0; sampleIndex < MSAA_SAMPLES; ++sampleIndex) {
        float depth = gDepthTexture.Load(coords, sampleIndex);

        // Check for skybox case (NOTE: complementary Z!)
        if (depth <= 0.0f && !mUI.visualizeLightCount) {
            ++skyboxSamples;
        } else {
            float3 sampleLit;
            [branch] if (useFlatLitBuffer) {
                sampleLit = UnpackRGBA16(gLitTextureFlat[GetFramebufferSampleAddress(coords, sampleIndex)]).xyz;
            } else {
                sampleLit = gLitTexture.Load(coords, sampleIndex).xyz;
            }

            // Tone map each sample separately (identity for now) and accumulate
            lit += sampleLit;
        }
    }

    // If necessary, add skybox contribution
    [branch] if (skyboxSamples > 0) {
        float3 skybox = gSkyboxTexture.Sample(gDiffuseSampler, input.skyboxCoord).xyz;
        // Tone map and accumulate
        lit += skyboxSamples * skybox;
    }

    // Resolve MSAA samples (simple box filter)
    return float4(lit * rcp(MSAA_SAMPLES), 1.0f);
#endif

#endif // GBUFFER_FX

