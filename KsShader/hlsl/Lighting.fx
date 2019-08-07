/************************************************************************************************/
/** 
 * @file		Lighting.fx
 * @brief		ライティング
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef LIGHTING_FX
#define LIGHTING_FX

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

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
struct PointLight
{
	float3		PositionView;
	float		AttenuationBegin;
	float3		Color;
	float		AttenuationEnd;
};

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
struct KsLight
{
	float3		Ground;
	float3		Versatile;
	float3		Sky;
};

/************************************************************************************************/
/**
 * @cbuffer		cbGBuffers
 * @brief		G-バッファ出力,構造体
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
cbuffer cbGBuffers : register( b2 )
{
	KsLight		hemiSphereLight;
};

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
StructuredBuffer<PointLight>	g_Light : register(t5);

/************************************************************************************************/
/*
 * Phong shading
 */
/************************************************************************************************/
void AccumulatePhongBRDF(float3 normal,
                         float3 lightDir,
                         float3 viewDir,
                         float3 lightContrib,
                         float specularPower,
                         inout float3 litDiffuse,
                         inout float3 litSpecular)
{
	float NdotL = dot(normal, lightDir);

	if( NdotL > 0.0f )
	{
		float3	r        = reflect( lightDir, normal );
		float	RdotV    = max( 0.0f, dot(r, viewDir) );
		float	specular = pow( RdotV, specularPower );

		litDiffuse  += lightContrib * NdotL;
		litSpecular += lightContrib * specular;
	}
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void AccumulateBRDFDiffuseSpecular(	KsSurfaceData surface,
									PointLight light,
									inout float3 litDiffuse,
									inout float3 litSpecular)
{
	float3 directionToLight = light.PositionView - surface.PositionView;
	float  distanceToLight  = length(directionToLight);

	if (distanceToLight < light.AttenuationEnd)
	{
		float attenuation = linstep(light.AttenuationEnd, light.AttenuationBegin, distanceToLight);
		directionToLight *= rcp(distanceToLight);

		AccumulatePhongBRDF(surface.Normal, directionToLight, normalize(surface.PositionView),
			attenuation * light.Color, surface.SpecularPower, litDiffuse, litSpecular);
	}
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void AccumulateBRDF( KsSurfaceData surface, PointLight light, inout float3 lit )
{
	float3 directionToLight = light.PositionView - surface.PositionView;
	float  distanceToLight  = length(directionToLight);

	if( distanceToLight < light.AttenuationEnd )
	{
		float attenuation = linstep(light.AttenuationEnd, light.AttenuationBegin, distanceToLight);
		directionToLight *= rcp(distanceToLight);

		float3 litDiffuse  = float3(0.0f, 0.0f, 0.0f);
		float3 litSpecular = float3(0.0f, 0.0f, 0.0f);

		AccumulatePhongBRDF(surface.Normal, directionToLight, normalize(surface.PositionView),
			attenuation * light.Color, surface.SpecularPower, litDiffuse, litSpecular);
		lit += surface.Albedo.rgb * (litDiffuse + surface.SpecularAmount * litSpecular);
	}
}


// 影
// アンビエントオクルージョン
/************************************************************************************************/
/*
 * ブラシシェーダー
 * A  ... A Parameter
 * B  ... B Parameter
 * N  ... Normal vector
 * L  ... Light vector
 * T1 ... albedo texture color
 * T2 ... deep texture color
 */
/************************************************************************************************/
float3 KsBrush( float3 N, float3 L, float4 T1 )
{
	float	A = 6.0f;
	float	B = 3.0f;
	float	shade;
	float	cell_shade;
	float3	texture_color;
	float4	T2;

	T2 = T1*T1;
	shade         = 0.5f * dot(N,L) + 0.5f;
	cell_shade    = saturate(shade*A - B);
	texture_color = lerp(T2, T1, cell_shade );

	return texture_color;
}

/************************************************************************************************/
/*
 * リムライト
 * N       ... Normal vector
 * L       ... Light vector
 */
/************************************************************************************************/
float KsRimLight( float3 N, float3 E, float3 L )
{
	// 視線からモデルの縁を強く
	float power = 2.0f;
	float rim   = 1.0 - dot(N, E);

	// リムライトの強さ補正
	rim = pow(abs(rim), power);

	// 太陽との逆光を計算（頂点シェーダでOK）
	//float light_rim = max(dot(-L, E), 0.0);

	// モデルの縁計算と、太陽の逆光計算を乗算
	//float3 color = rim * light_rim;

	return rim;
}

/************************************************************************************************/
/*
 * 半球ライティング
 * L ... Low( Ground Color )
 * M ... Middle( Versatile Color )
 * U ... Upper( Sky Color )
 * N ... Normal vector
 * V ... Upper Vector
 */
/************************************************************************************************/
float4 KsHemiSphereLighting( float3 L, float3 M, float3 U, float3 N, float3 V )
{
	float3 ambient;
	float  rate;

	rate = 0.5f * dot(N,V) + 0.5f;

	// Ambient = lerp(lerp(L, M, rate), lerp(M, U, rate), rate)
	// optimized
	ambient = (0.25f*(L+U - 2.0f*M))*rate*rate + (0.25f*(2.0f*U - 2.0f*L))*rate + (0.25f*(L+U + 2.0f*M));

	return float4( ambient, 1.0f );
}

/************************************************************************************************/
/*
 * 肌シェーダー
 * redness ... Skin color parameter
 * shadow  ... Shadow Coefficient
 * N       ... Normal vector
 * L       ... Light vector
 */
/************************************************************************************************/
float4 KsSkin( float4 redness, float4 shadow, float3 N, float3 L )
{
	float	diffuse_shade;
	float4	ambient;
	float4	ret;

	diffuse_shade = saturate(dot(N,L));
	ambient       = KsHemiSphereLighting( hemiSphereLight.Ground, hemiSphereLight.Versatile, hemiSphereLight.Sky, N, L );
	ambient      += (0.5f + 0.5f*abs(dot(N,L))) * redness;

	ret = diffuse_shade * shadow + ambient;

	return ret;
}

#endif // LIGHTING_FX

