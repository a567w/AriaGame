/************************************************************************************************/
/** 
 * @file		Common.fxh
 * @brief		共通データ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef COMMON_FXH
#define COMMON_FXH

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
#define MAX_LIGHTS_POWER				10
#define MAX_LIGHTS						(1<<MAX_LIGHTS_POWER)
#define COMPUTE_SHADER_TILE_GROUP_DIM	16
#define COMPUTE_SHADER_TILE_GROUP_SIZE	(COMPUTE_SHADER_TILE_GROUP_DIM*COMPUTE_SHADER_TILE_GROUP_DIM)
#define DEFER_PER_SAMPLE				1
#define MSAA_SAMPLES					1
#define MAX_BONES						256

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @struct		KsSurfaceData
 * @brief		サーフェースデータ構造体
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
struct KsSurfaceData
{
	float3		PositionView;		// View space position
	float3		PositionViewDX;		// Screen space derivatives
	float3		PositionViewDY;		// of view space position
	float3		Normal;				// View space normal
	float4		Albedo;				// ディフューズ
	float		SpecularAmount;		// 反射量
	float		SpecularPower;		// スペキュラパワー
};

/************************************************************************************************/
/**
 * @struct		UIConstants
 * @brief		サーフェースデータ構造体
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
struct UIConstants
{
	uint lightingOnly;
	uint faceNormals;
	uint visualizeLightCount;
	uint visualizePerSampleShading;
	uint lightCullTechnique;
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
cbuffer cbGBuffers : register( b0 )
{
	float4x4			WorldViewProj;				// ビュー,プロジェクションマトリックス
	float4x4			WorldView;					// プロジェクションマトリックス
	float4x4			ViewProj;					// プロジェクションマトリックス
	float4x4			Proj;						// ワールドマトリックス
	float4x4			World;						// ワールドマトリックス
	float4				CameraNearFar;
	uint4				FramebufferDimensions;
	UIConstants			mUI;
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
cbuffer cbMatrixPallet : register( b1 )
{
	float4x4			MatrixPalette[ MAX_BONES ];		// マトリックスパレット
};



/************************************************************************************************/
/**
 * 最小値と最大値の区間で引数をリニア補間した結果を表す、0 ～ 1 の範囲に写像した比例値を返します。
 */
/************************************************************************************************/
float linstep(float min, float max, float v)
{
	// saturate : 指定された値を 0 ～ 1 の範囲にクランプします。
	return saturate((v - min) / (max - min));
}

/************************************************************************************************/
/**
 * RGBA 16-bit per component packed into a uint2 per texel
 */
/************************************************************************************************/
float4 UnpackRGBA16(uint2 e)
{
	return float4(f16tof32(e), f16tof32(e >> 16));
}

/************************************************************************************************/
/**
 * カラー値 float4 を uint2に変換する
 */
/************************************************************************************************/
uint2 PackRGBA16(float4 c)
{
	return f32tof16(c.rg) | (f32tof16(c.ba) << 16);
}

/************************************************************************************************/
/**
 * Linearize the given 2D address + sample index into our flat framebuffer array
 */
/************************************************************************************************/
uint GetFramebufferSampleAddress(uint2 coords, uint sampleIndex)
{
	// Major ordering: Row (x), Col (y), MSAA sample
	return (sampleIndex * FramebufferDimensions.y + coords.y) * FramebufferDimensions.x + coords.x;
}

#endif // COMMON_FXH

