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
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

//--------------------------------------------------------------------------------------
// Miscellaneous constants
//--------------------------------------------------------------------------------------
#define LIGHT_INDEX_BUFFER_SENTINEL     0x7fffffff

//--------------------------------------------------------------------------------------
// Light culling constants.
// These must match their counterparts in ForwardPlusUtil.h
//--------------------------------------------------------------------------------------
#define TILE_RES 16
#define MAX_NUM_LIGHTS_PER_TILE         544

/************************************************************************************************/
/**
 * @cbuffer		Constant Buffers
 * @brief		PerObject構造体
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
cbuffer cbPerObject : register( b0 )
{
    matrix              WorldViewProj            : packoffset(  c0 );
    matrix              WorldView                : packoffset(  c4 );
    matrix              World                    : packoffset(  c8 );
    float4              MaterialAmbientColorUp   : packoffset( c12 );
    float4              MaterialAmbientColorDown : packoffset( c13 );
};

/************************************************************************************************/
/**
 * @cbuffer		Constant Buffers
 * @brief		PerFrame構造体
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
cbuffer cbPerFrame : register( b1 )
{
    matrix              Projection           : packoffset( c0 );
    matrix              ProjectionInv        : packoffset( c4 );
    float3              CameraPos            : packoffset( c8 );
    float               AlphaTest            : packoffset( c8.w );
    uint                NumLights            : packoffset( c9 );
    uint                WindowWidth          : packoffset( c9.y );
    uint                WindowHeight         : packoffset( c9.z );
    uint                MaxNumLightsPerTile  : packoffset( c9.w );
};


/************************************************************************************************/
/**
 * @function	GetTileIndex
 * @brief		GetTileIndex
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
uint GetTileIndex( float2 ScreenPos )
{
    float fTileRes   = (float)TILE_RES;
    uint  nNumCellsX = (g_uWindowWidth + TILE_RES - 1)/TILE_RES;
    uint  nTileIdx   = floor(ScreenPos.x/fTileRes) + floor(ScreenPos.y/fTileRes) * nNumCellsX;

    return nTileIdx;
}

