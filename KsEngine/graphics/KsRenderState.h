/************************************************************************************************/
/** 
 * @file		KsRenderState.h
 * @brief		描画ステート
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSRENDERSTATE_H__
#define __KSRENDERSTATE_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsColor.h"
#include "KsLight.h"
#include "KsMaterial.h"
#include "KsViewport.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
#define ksRENDER_TARGET_BACKBUFFER_SURFACE		( 0 )
#define ksRENDER_TARGET_DEPTHSTENCIL_SURFACE	( 1<<0 )
#define ksRENDER_TARGET_BACKBUFFER_TEXTURE		( 1<<1 )
#define ksRENDER_TARGET_DEPTHSTENCIL_TEXTURE	( 1<<2 )

#define ksLIGHT_MAX				( 4 )		/**< ライトの最大数						*/
#define ksRENDER_STATE_STACK_MAX	( 16 )		/**< レンダーステート最大スタックサイズ	*/

/* クリアービット */
#define ksCLEAR_FLAG_COLOR			( 1<<0 )	/**< カラークリアフラグ					*/
#define ksCLEAR_FLAG_DEPTH			( 1<<1 )	/**< 深度バッファクリアフラグ			*/
#define ksCLEAR_FLAG_STENCIL		( 1<<2 )	/**< ステンシルバッファクリアフラグ		*/
#define ksCLEAR_FLAG_ACCUM			( 1<<3 )	/**< アキュームレフバッファ				*/

#define ksLOCK_DISCARD				( 0 )
#define ksLOCK_DONOTWAIT			( 1 )
#define ksLOCK_NO_DIRTY_UPDATE		( 2 )
#define ksLOCK_NOOVERWRITE			( 3 )
#define ksLOCK_NOSYSLOCK			( 4 )
#define ksLOCK_READONLY				( 5 )

#define ksFVF_NONE					( 0x000 )
#define ksFVF_POSITION_MASK			( 0x00E )
#define ksFVF_XYZ					( 0x002 )
#define ksFVF_XYZRHW				( 0x004 )
#define ksFVF_XYZB1					( 0x006 )
#define ksFVF_XYZB2					( 0x008 )
#define ksFVF_XYZB3					( 0x00a )
#define ksFVF_XYZB4					( 0x00c )
#define ksFVF_XYZB5					( 0x00e )
#define ksFVF_NORMAL				( 0x010 )
#define ksFVF_DIFFUSE				( 0x040 )
#define ksFVF_SPECULAR				( 0x080 )

#define ksFVF_TEXCOUNT_MASK			( 0xf00 )
#define ksFVF_TEXCOUNT_SHIFT		( 8 )
#define ksFVF_TEX					( 0x100 )
#define ksFVF_TEX1					( 0x100 )
#define ksFVF_TEX2					( 0x200 )
#define ksFVF_TEX3					( 0x300 )
#define ksFVF_TEX4					( 0x400 )
#define ksFVF_TEX5					( 0x500 )
#define ksFVF_TEX6					( 0x600 )
#define ksFVF_TEX7					( 0x700 )
#define ksFVF_TEX8					( 0x800 )

#define ksFVF_INDICES				( 0x901 )
#define ksFVF_WEIGHT				( 0x910 )

#define ksFVF_LASTBETA_COLOR		( 0x1000 )
#define ksFVF_LASTBETA_UBYTE4		( 0x2000 )

#define ksFMT_INDEX16				( 0 )
#define ksFMT_INDEX32				( 1 )

#define ksFLAG_CPU_ACCESS_NONE		( 0 )
#define ksFLAG_CPU_ACCESS_WRITE		( 1 )
#define ksFLAG_CPU_ACCESS_READ		( 2 )

enum ksDECLUSAGE
{
    ksDECLUSAGE_POSITION = 0,
    ksDECLUSAGE_BLENDWEIGHT,   // 1
    ksDECLUSAGE_BLENDINDICES,  // 2
    ksDECLUSAGE_NORMAL,        // 3
    ksDECLUSAGE_PSIZE,         // 4
    ksDECLUSAGE_TEXCOORD,      // 5
    ksDECLUSAGE_TANGENT,       // 6
    ksDECLUSAGE_BINORMAL,      // 7
    ksDECLUSAGE_TESSFACTOR,    // 8
    ksDECLUSAGE_POSITIONT,     // 9
    ksDECLUSAGE_COLOR,         // 10
    ksDECLUSAGE_FOG,           // 11
    ksDECLUSAGE_DEPTH,         // 12
    ksDECLUSAGE_SAMPLE,        // 13
};

#define MAXD3DDECLUSAGE         D3DDECLUSAGE_SAMPLE
#define MAXD3DDECLUSAGEINDEX    15
#define MAXD3DDECLLENGTH        64 // does not include "end" marker vertex element


enum ksDECLMETHOD
{
    ksDECLMETHOD_DEFAULT = 0,
    ksDECLMETHOD_PARTIALU,
    ksDECLMETHOD_PARTIALV,
    ksDECLMETHOD_CROSSUV,    // Normal
    ksDECLMETHOD_UV,
    ksDECLMETHOD_LOOKUP,               // Lookup a displacement map
    ksDECLMETHOD_LOOKUPPRESAMPLED,     // Lookup a pre-sampled displacement map
};

// Declarations for _Type fields
//
enum ksDECLTYPE
{
    ksDECLTYPE_FLOAT1    =  0,  // 1D float expanded to (value, 0., 0., 1.)
    ksDECLTYPE_FLOAT2    =  1,  // 2D float expanded to (value, value, 0., 1.)
    ksDECLTYPE_FLOAT3    =  2,  // 3D float expanded to (value, value, value, 1.)
    ksDECLTYPE_FLOAT4    =  3,  // 4D float
    ksDECLTYPE_COLOR  =  4,  // 4D packed unsigned bytes mapped to 0. to 1. range
                                 // Input is in D3DCOLOR format (ARGB) expanded to (R, G, B, A)
    ksDECLTYPE_UBYTE4    =  5,  // 4D unsigned byte
    ksDECLTYPE_SHORT2    =  6,  // 2D signed short expanded to (value, value, 0., 1.)
    ksDECLTYPE_SHORT4    =  7,  // 4D signed short

// The following types are valid only with vertex shaders >= 2.0


    ksDECLTYPE_UBYTE4N   =  8,  // Each of 4 bytes is normalized by dividing to 255.0
    ksDECLTYPE_SHORT2N   =  9,  // 2D signed short normalized (v[0]/32767.0,v[1]/32767.0,0,1)
    ksDECLTYPE_SHORT4N   = 10,  // 4D signed short normalized (v[0]/32767.0,v[1]/32767.0,v[2]/32767.0,v[3]/32767.0)
    ksDECLTYPE_USHORT2N  = 11,  // 2D unsigned short normalized (v[0]/65535.0,v[1]/65535.0,0,1)
    ksDECLTYPE_USHORT4N  = 12,  // 4D unsigned short normalized (v[0]/65535.0,v[1]/65535.0,v[2]/65535.0,v[3]/65535.0)
    ksDECLTYPE_UDEC3     = 13,  // 3D unsigned 10 10 10 format expanded to (value, value, value, 1)
    ksDECLTYPE_DEC3N     = 14,  // 3D signed 10 10 10 format normalized and expanded to (v[0]/511.0, v[1]/511.0, v[2]/511.0, 1)
    ksDECLTYPE_FLOAT16_2 = 15,  // Two 16-bit floating point values, expanded to (value, value, 0, 1)
    ksDECLTYPE_FLOAT16_4 = 16,  // Four 16-bit floating point values
    ksDECLTYPE_UNUSED    = 17,  // When the type field in a decl is unused.
};


// This is used to initialize the last vertex element in a vertex declaration
// array
//
#define ksDECL_END() { 0xFF, 0, ksDECLTYPE_UNUSED, 0, 0, 0 }

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * トランスフォームの種類
 */
/************************************************************************************************/
typedef enum _ksTRANSFORM_STATE
{
	ksTRANSFORM_WORLD,				/**< ワールド						*/
	ksTRANSFORM_VIEW,				/**< ビュー							*/
	ksTRANSFORM_PROJECTION,			/**< プロジェクション				*/
	ksTRANSFORM_TEXTURE0,			/**< テクスチャ0					*/
	ksTRANSFORM_TEXTURE1,			/**< テクスチャ1					*/
	ksTRANSFORM_TEXTURE2,			/**< テクスチャ2					*/
	ksTRANSFORM_TEXTURE3,			/**< テクスチャ3					*/
	ksTRANSFORM_TEXTURE4,			/**< テクスチャ4					*/
	ksTRANSFORM_TEXTURE5,			/**< テクスチャ5					*/

}ksTRANSFORM_STATE;

/************************************************************************************************/
/**
 * テクスチャステート
 */
/************************************************************************************************/
typedef enum _ksTEXTURE_STATE_TYPE
{
	ksTEXTURE_STATE_COLOR_OP  = 0,			/**< テクスチャファンクション				*/
	ksTEXTURE_STATE_ADDRESSU  = 1,			/**< テクスチャ座標 u 方向のラップモード 	*/
	ksTEXTURE_STATE_ADDRESSV  = 2,			/**< テクスチャ座標 v 方向のラップモード	*/
	ksTEXTURE_STATE_MAGFILTER = 3,			/**< 拡大フィルタ						*/
	ksTEXTURE_STATE_MINFILTER = 4,			/**< 縮小フィルタ						*/
	ksTEXTURE_STATE_MIPFILTER = 5,			/**< ミップマップフィルタ					*/
	ksTEXTURE_STATE_FORCE32   = 0x7fffffff,	/**< 強制的に32bitにする					*/

}ksTEXTURE_STATE_TYPE;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef enum _ksTEXTURE_COLOR_OP_MODE
{
	ksTEXTURE_COLOR_OP_MODULATE = 0,
	ksTEXTURE_COLOR_OP_DECAL    = 1,
	ksTEXTURE_COLOR_OP_BLEND    = 2,
	ksTEXTURE_COLOR_OP_REPLACE  = 3,
	ksTEXTURE_COLOR_OP_ADD      = 4,
	ksTEXTURE_COLOR_OP_FORCE32  = 0x7fffffff,	/**< 強制的に32bitにする	*/

}ksTEXTURE_COLOR_OP_MODE;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef enum _ksTEXTURE_ADDRESS_MODE
{
	ksTEXTURE_ADDRESS_REPEAT  = 0,
	ksTEXTURE_ADDRESS_CLAMP   = 1,
	ksTEXTURE_ADDRESS_FORCE32 = 0x7fffffff,	/**< 強制的に32bitにする		*/

}ksTEXTURE_ADDRESS_MODE;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef enum _ksTEXTURE_FILTER
{
	ksTEXTURE_FILTER_NEAREST = 0,  
	ksTEXTURE_FILTER_LINEAR  = 1,
	ksTEXTURE_FILTER_FORCE32 = 0x7fffffff,	/**< 強制的に32bitにする		*/

}ksTEXTURE_FILTER;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef enum _ksTEXTURE_MIPMAP_FILTER
{
	ksTEXTURE_MIPMAP_FILTER_NEAREST = 0,
	ksTEXTURE_MIPMAP_FILTER_LINEAR  = 1,
	ksTEXTURE_MIPMAP_FILTER_FORCE32 = 0x7fffffff,	/**< 強制的に32bitにする		*/

}ksTEXTURE_MIPMAP_FILTER;

/************************************************************************************************/
/**
 * レンダーステート
 */
/************************************************************************************************/
typedef enum _ksRENDER_STATE_TYPE
{
	ksRENDER_STATE_OP_BLEND           = 0,			/**< ブレンドモード											*/
	ksRENDER_STATE_SRC_BLEND          = 1,			/**< SRCブレンディング										*/
    ksRENDER_STATE_DST_BLEND          = 2,			/**< DESTブレンディング										*/
	ksRENDER_STATE_ALPHA_BLEND        = 3,			/**< アルファブレンド										*/
	ksRENDER_STATE_ALPHA_FUNC         = 4,			/**< アルファ関数											*/
	ksRENDER_STATE_ALPHA_REF          = 5,			/**< アルファ基準値											*/
	ksRENDER_STATE_ALPHA_MASK         = 6,			/**< アルファマスク値										*/

	ksRENDER_STATE_ZTEST_ENABLE       = 7,			/**< Zバッファ(ON,OFF)										*/
	ksRENDER_STATE_ZWRITE_ENABLE      = 8,			/**< Zライト(ON,OFF)										*/
	ksRENDER_STATE_ALPAHTEST_ENABLE   = 9,			/**< アルファテスト(ON,OFF)									*/
	ksRENDER_STATE_FOG_ENABLE         = 10,			/**< フォグ(ON,OFF)											*/
	ksRENDER_STATE_LIGHTING           = 11,			/**< ライティング(ON,OFF)									*/
	ksRENDER_STATE_SHADE              = 12,			/**< シェーディング											*/
	ksRENDER_STATE_CULL               = 13,			/**< カリング												*/

	ksRENDER_STATE_STENCIL_ENABLE     = 14,			/**< ステンシル(ON,OFF)										*/
	ksRENDER_STATE_STENCIL_FAIL       = 15,			/**< ステンシルテスト失敗時のオペレーション					*/
	ksRENDER_STATE_STENCIL_ZFAIL      = 16,			/**< ステンシルテストかつZテストに失敗時のオペレーション	*/
	ksRENDER_STATE_STENCIL_PASS       = 17,			/**< ステンシルテストかつZテストの成功時のオペレーション	*/
	ksRENDER_STATE_STENCIL_FUNC       = 18,			/**< ステンシルファンクション								*/
	ksRENDER_STATE_STENCIL_REF        = 19,			/**< ステンシルの基準値										*/
	ksRENDER_STATE_STENCIL_MASK       = 20,			/**< ステンシルのマスク値									*/
	ksRENDER_STATE_STENCIL_WRITE_MASK = 21,			/**< ステンシル書き込みマスク								*/
	ksRENDER_STATE_COLOR_TEST_ENABLE  = 22,			/**< カラーテスト(ON,OFF)									*/
	ksRENDER_STATE_COLOR_FUNC         = 23,			/**< カラー関数												*/
	ksRENDER_STATE_COLOR_REF          = 24,			/**< カラー基準値											*/
	ksRENDER_STATE_COLOR_MASK         = 25,			/**< カラーマスク値											*/
	ksRENDER_STATE_PIXEL_MASK         = 26,			/**< ピクセルマスク											*/
	ksRENDER_STATE_LOGICAL_OP_ENABLE  = 27,			/**< ロジカルオペレーション(ON,OFF)							*/
	ksRENDER_STATE_LOGICAL_OP_BLEND   = 28,			/**< ロジカルオペレーションモード							*/

	ksRENDER_STATE_FORCE32            = 0x7fffffff,	/**< 強制的に32bitにする									*/

}ksRENDER_STATE_TYPE;


/* Special sampler which is used in the tesselator */
#define ksDMAP_SAMPLER				( 256 )

/* Samplers used in vertex shaders */
#define ksVERTEX_TEXTURE_SAMPLER0 ( ksDMAP_SAMPLER + 1 )
#define ksVERTEX_TEXTURE_SAMPLER1 ( ksDMAP_SAMPLER + 2 )
#define ksVERTEX_TEXTURE_SAMPLER2 ( ksDMAP_SAMPLER + 3 )
#define ksVERTEX_TEXTURE_SAMPLER3 ( ksDMAP_SAMPLER + 4 )

/************************************************************************************************/
/**
 * サンプラーステート
 */
/************************************************************************************************/
typedef enum _ksSAMPLER_STATE_TYPE
{
    ksSAMP_ADDRESSU       = 1,			/* TEXTUREADDRESS for U coordinate					*/
    ksSAMP_ADDRESSV       = 2,			/* TEXTUREADDRESS for V coordinate					*/
    ksSAMP_ADDRESSW       = 3,			/* TEXTUREADDRESS for W coordinate					*/
    ksSAMP_BORDERCOLOR    = 4,			/* COLOR											*/
    ksSAMP_MAGFILTER      = 5,			/* TEXTUREFILTER filter to use for magnification	*/
    ksSAMP_MINFILTER      = 6,			/* TEXTUREFILTER filter to use for minification		*/
    ksSAMP_MIPFILTER      = 7,			/* TEXTUREFILTER filter to use between mipmaps during minification */
    ksSAMP_MIPMAPLODBIAS  = 8,			/* float Mipmap LOD bias							*/
    ksSAMP_MAXMIPLEVEL    = 9,			/* DWORD 0..(n-1) LOD index of largest map to use (0 == largest) */
    ksSAMP_MAXANISOTROPY  = 10,			/* DWORD maximum anisotropy */
    ksSAMP_SRGBTEXTURE    = 11,			/* Default = 0 (which means Gamma 1.0, no correction required.) else correct for Gamma = 2.2 */
    ksSAMP_ELEMENTINDEX   = 12,			/* When multi-element texture is assigned to sampler, this indicates which element index to use.  Default = 0.  */
    ksSAMP_DMAPOFFSET     = 13,			/* Offset in vertices in the pre-sampled displacement map. Only valid for DMAPSAMPLER sampler  */
    ksSAMP_STATE_FORCE32  = 0x7fffffff, /**< 強制的に32bitにする									*/

}ksSAMPLER_STATE_TYPE;

/************************************************************************************************/
/**
 * Values for D3DSAMP_***FILTER texture stage states
 */
/************************************************************************************************/
typedef enum _ksTEXTURE_FILTER_TYPE
{
	ksTEXF_NONE            = 0,				/**< filtering disabled (valid for mip filter only)	*/
	ksTEXF_POINT           = 1,				/**< nearest										*/
	ksTEXF_LINEAR          = 2,				/**< linear interpolation							*/
	ksTEXF_ANISOTROPIC     = 3,				/**< anisotropic									*/
	ksTEXF_PYRAMIDALQUAD   = 6,				/**< 4-sample tent									*/
	ksTEXF_GAUSSIANQUAD    = 7,				/**< 4-sample gaussian								*/
	ksTEXF_FORCE32         = 0x7fffffff,	/**< 強制的に32bitにする							*/

}ksTEXTURE_FILTER_TYPE;

/************************************************************************************************/
/**
 * ブレンドの演算
 */
/************************************************************************************************/
typedef enum _ksBLEND_OP_MODE
{
    ksBLEND_OP_ADD         = 1,			/**< 結果は転送元に転送先が加算される  ( 結果 = 転送元 + 転送先 )		*/
    ksBLEND_OP_SUBTRACT    = 2,			/**< 結果は転送元から転送先が減算される( 結果 = 転送元 - 転送先 )		*/
    ksBLEND_OP_REVSUBTRACT = 3,			/**< 結果は転送先から転送元が減算される( 結果 = 転送先 - 転送元 )		*/
    ksBLEND_OP_MIN         = 4,			/**< 結果は転送元と転送先の最小値である( 結果 = MIN(転送元, 転送先) )	*/
    ksBLEND_OP_MAX         = 5,			/**< 結果は転送元と転送先の最大値である( 結果 = MAX(転送元, 転送先) )	*/
    ksBLEND_OP_FORCE_DWORD = 0x7fffffff,/**< 強制的に32bitにする												*/

}ksBLEND_OP_MODE;

/************************************************************************************************/
/**
 * ブレンドFUNC
 */
/************************************************************************************************/
typedef enum _ksALPHA_FUNC_MODE
{
	ksALPHA_FUNC_NEVER    = 0,			/**< 全てのピクセルを描画しない							*/
	ksALPHA_FUNC_ALWAYS   = 1,			/**< 全てのピクセルを描画する							*/
	ksALPHA_FUNC_EQUAL    = 2,			/**< 設定値＝アルファ値の場合にピクセルを描画する		*/
	ksALPHA_FUNC_NOTEQUAL = 3,			/**< 設定値≠アルファ値の場合にピクセルを描画する		*/
	ksALPHA_FUNC_LESS     = 4,			/**< 設定値＜アルファ値の場合にピクセルを描画する		*/
	ksALPHA_FUNC_LEQUAL   = 5,			/**< 設定値≦アルファ値の場合にピクセルを描画する		*/
	ksALPHA_FUNC_GREATER  = 6,			/**< 設定値＞アルファ値の場合にピクセルを描画する		*/
	ksALPHA_FUNC_GEQUAL   = 7,			/**< 設定値≧アルファ値の場合にピクセルを描画する		*/
	ksALPHA_FUNC_FORCE32  = 0x7fffffff,	/**< 強制的に32bitにする								*/

}ksALPHA_FUNC_MODE;

/************************************************************************************************/
/**
 * ステンシル操作
 */
/************************************************************************************************/
typedef enum _ksSTENCIL_OP_MODE
{
	ksSTENCIL_OP_KEEP    = 0,				/**< 何もしない									*/
	ksSTENCIL_OP_ZERO    = 1,				/**< ステンシル値を 0 に変更する				*/
	ksSTENCIL_OP_REPLACE = 2,				/**< ステンシル値を設定値に変更する				*/
	ksSTENCIL_OP_INCRSAT = 3,				/**< 最大値に達するまで増加させる				*/
	ksSTENCIL_OP_DECRSAT = 4,				/**< 0 になるまで減少させる						*/
	ksSTENCIL_OP_INVERT  = 5,				/**< ステンシル値を反転する						*/
	ksSTENCIL_OP_INCR    = 6,				/**< ステンシル値を 1 増加する					*/
	ksSTENCIL_OP_DECR    = 7,				/**< ステンシル値を 1 減少する					*/
	ksSTENCIL_OP_FORCE32 = 0x7fffffff,		/**< 強制的に32bitにする						*/

}ksSTENCIL_OP_MODE;

/************************************************************************************************/
/**
 * ステンシルFUNC
 */
/************************************************************************************************/
typedef enum _ksSTENCIL_FUNC_MODE
{
	ksSTENCIL_FUNC_NEVER    = 0,			/**< 全てのピクセルを描画しない							*/
	ksSTENCIL_FUNC_ALWAYS   = 1,			/**< 全てのピクセルを描画する							*/
	ksSTENCIL_FUNC_EQUAL    = 2,			/**< 設定値＝ステンシル値の場合にピクセルを描画する		*/
	ksSTENCIL_FUNC_NOTEQUAL = 3,			/**< 設定値≠ステンシル値の場合にピクセルを描画する		*/
	ksSTENCIL_FUNC_LESS     = 4,			/**< 設定値＜ステンシル値の場合にピクセルを描画する		*/
	ksSTENCIL_FUNC_LEQUAL   = 5,			/**< 設定値≦ステンシル値の場合にピクセルを描画する		*/
	ksSTENCIL_FUNC_GREATER  = 6,			/**< 設定値＞ステンシル値の場合にピクセルを描画する		*/
	ksSTENCIL_FUNC_GEQUAL   = 7,			/**< 設定値≧ステンシル値の場合にピクセルを描画する		*/
	ksSTENCIL_FUNC_FORCE32  = 0x7fffffff,	/**< 強制的に32bitにする								*/

}ksSTENCIL_FUNC_MODE;

/************************************************************************************************/
/**
 * カラーFUNC
 */
/************************************************************************************************/
typedef enum _ksCOLOR_FUNC_MODE
{
	ksCOLOR_FUNC_NEVER    = 0,				/**< 全てのピクセルを描画しない						*/
	ksCOLOR_FUNC_ALWAYS   = 1,				/**< 全てのピクセルを描画する							*/
	ksCOLOR_FUNC_EQUAL    = 2,				/**< ピクセルカラー＝固定値の場合にピクセルを描画する	*/
	ksCOLOR_FUNC_NOTEQUAL = 3,				/**< ピクセルカラー≠固定値の場合にピクセルを描画する	*/
	ksCOLOR_FUNC_FORCE32  = 0x7fffffff,		/**< 強制的に32bitにする								*/

}ksCOLOR_FUNC_MODE;

/************************************************************************************************/
/**
 * ブレンドモード
 */
/************************************************************************************************/
typedef enum _ksBLEND_MODE
{
	ksBLEND_ZERO                = 1,			/**< ブレンディング係数 (0, 0, 0, 0)				*/
	ksBLEND_ONE                 = 2,			/**< ブレンディング係数 (1, 1, 1, 1)				*/
	ksBLEND_SRC_COLOR           = 3,			/**< ブレンディング係数 (Rs,Gs,Bs,As)				*/
	ksBLEND_DST_COLOR           = 4,			/**< ブレンディング係数 (Rd,Gd,Bd,Ad)				*/
	ksBLEND_ONE_MINUS_SRC_COLOR = 5,			/**< ブレンディング係数 (1-Rs,1-Gs,1-Bs,1-As)		*/
	ksBLEND_ONE_MINUS_DST_COLOR = 6,			/**< ブレンディング係数 (1-Rd,1-Gd,1-Bd,1-Ad)		*/
	ksBLEND_SRC_ALPHA           = 7,			/**< ブレンディング係数 (As, As, As, As)			*/
	ksBLEND_DST_ALPHA           = 8,			/**< ブレンディング係数 (Ad, Ad, Ad, Ad) 禁止		*/
	ksBLEND_ONE_MINUS_SRC_ALPHA = 9,			/**< ブレンディング係数 (1-As,1-As,1-As,1-As)		*/
	ksBLEND_ONE_MINUS_DST_ALPHA = 10,			/**< ブレンディング係数 (1-Ad,1-Ad,1-Ad,1-Ad)禁止	*/
	ksBLEND_FORCE32             = 0x7fffffff,	/**< 強制的に32bitにする							*/

}ksBLEND_MODE;

/************************************************************************************************/
/**
 * シェーディングモード
 */
/************************************************************************************************/
typedef enum _ksSHADE_MODE
{
	ksSHADE_FLAT    = 1,				/**< フラットシェーディング		*/
	ksSHADE_GOURAUD = 2,				/**< グーローシェーディング		*/
	ksSHADE_FORCE32 = 0x7fffffff,		/**< 強制的に32bitにする		*/

}ksSHADE_MODE;

/************************************************************************************************/
/**
 * カリングモード
 */
/************************************************************************************************/
typedef enum _ksCULL_MODE
{
	ksCULL_NONE    = 1,					/**< 背面のカリングはしない		*/
	ksCULL_CW      = 2,					/**< 背面を右回りでカリングする	*/
	ksCULL_CCW     = 3,					/**< 背面を左回りでカリングする	*/
	ksCULL_FORCE32 = 0x7fffffff,		/**< 強制的に32bitにする		*/

}ksCULL_MODE;

/************************************************************************************************/
/**
 * カリングモード
 */
/************************************************************************************************/
typedef enum _ksFOG_MODE
{
	ksFOG_NONE    = 0,					/**< フォグなし										*/
	ksFOG_EXP     = 1,					/**< 指数で、フォグ エフェクトが増す				*/
	ksFOG_EXP2    = 2,					/**< 指数の 2 乗で、フォグ エフェクトが増す			*/
	ksFOG_LINEAR  = 3,					/**< 始点と終点の間で線形にフォグ エフェクトが増す	*/
	ksFOG_FORCE32 = 0x7fffffff,			/**< 強制的に32bitにする							*/

}ksFOG_MODE;

/************************************************************************************************/
/**
 * 描画プリミティブのタイプ
 */
/************************************************************************************************/
typedef enum _ksPRIMITIVE_TYPE
{
    ksPRIMITIVE_POINT_LIST     = 1,
    ksPRIMITIVE_LINE_LIST      = 2,
    ksPRIMITIVE_LINE_STRIP     = 3,
    ksPRIMITIVE_TRIANGLE_LIST  = 4,
    ksPRIMITIVE_TRIANGLE_STRIP = 5,
	ksPRIMITIVE_TRIANGLE_FAN   = 6,
    ksPRIMITIVE_FORCE32        = 0x7fffffff,

}ksPRIMITIVE_TYPE;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
class KsTextureState
{
	public:
		ksTEXTURE_COLOR_OP_MODE			m_colorOP;
		ksTEXTURE_ADDRESS_MODE			m_addressU;
		ksTEXTURE_ADDRESS_MODE			m_addressV;
		ksTEXTURE_FILTER				m_magFilter;
		ksTEXTURE_FILTER				m_minFilter;
		ksTEXTURE_MIPMAP_FILTER			m_mipMapFilter;
};

/************************************************************************************************/
/**
 * @class		KsRenderState
 * @brief		レンダーステート
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsRenderState
{
	public:
		/* 復元するレンダーステートのビット */
		//push されたときすべての現状のすべてのレンダーステートを保存する
		//pop  のときは違うものだけを変更する
		ksBLEND_OP_MODE					m_opBlend;
		ksBLEND_MODE					m_srcBlend;
		ksBLEND_MODE					m_dstBlend;
		
		KsBool							m_alphaBlend;
		ksALPHA_FUNC_MODE				m_alphaFunc;
		KsUInt32						m_alphaRef;
		KsUInt32						m_alphaMask;

		KsBool							m_zTest;
		KsBool							m_zWrite;
		KsBool							m_alphaTest;
		KsBool							m_fog;
		KsBool							m_lighting;
		ksSHADE_MODE					m_shadeMode;
		ksCULL_MODE						m_cullMode;

		KsBool							m_stencil;
		KsUInt32						m_stencilRef;
		KsUInt32						m_stencilMask;
		KsUInt32						m_stencilWriteMask;
		ksSTENCIL_OP_MODE				m_stencilOpFail;
		ksSTENCIL_OP_MODE				m_stencilOpZFail;
		ksSTENCIL_OP_MODE				m_stencilOpPass;
		ksSTENCIL_FUNC_MODE				m_stencilFunc;

		KsBool							m_colorTest;
		ksCOLOR_FUNC_MODE				m_colorFunc;
		KsUInt32						m_colorRef;
		KsUInt32						m_colorMask;

		KsUInt32						m_pixelMask;

		KsBool							m_logicalOp;
		//stLOGICAL_FUNC_MODE			m_logicalFunc;
		//KsUInt32						m_changeStateMask;	/**< 変更したレンダーステートのマスク	*/
};

/************************************************************************************************/
/**
 * @class		KsRenderStateStack
 * @brief		レンダーステートスタック
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsRenderStateStack
{
	public:
		/**
		 * コンストラクタ
		 */
											KsRenderStateStack() : m_index( 0 ) {}

		/**
		 * レンダーステートをプッシュする
		 * @param		pState				プッシュするレンダーステート
		 * @retval		ksTRUE				成功
		 * @retval		ksFALSE				失敗
		 */
		KsBool								push( const KsRenderState* pState );

		/**
		 * レンダーステートをポップする
		 * @param		pState				レンダーステートを取得するためのポインタ
		 * @retval		ksTRUE				成功
		 * @retval		ksFALSE				失敗
		 */
		KsBool								pop( KsRenderState* pState );

		/**
		 * スタックをクリアーする
		 */
		void								clear();

	private:
		KsRenderState						m_stack[ ksRENDER_STATE_STACK_MAX ];	/**< レンダーステートスタック	*/
		KsInt32								m_index;								/**< 現在のスタックの深さ		*/
};


#endif /* __KSRENDERSTATE_H__ */

