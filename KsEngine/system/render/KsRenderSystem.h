/************************************************************************************************/
/** 
 * @file		KsRenderSystem.h
 * @brief		描画システム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSRENDERSYSTEM_H__
#define __KSRENDERSYSTEM_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsType.h"
#include "KsColor.h"
#include "KsLight.h"
#include "KsMaterial.h"
#include "KsViewport.h"
#if 0
#include "KsTexture.h"
#include "ksImage.h"
#include "KsMatrix.h"
#include "KsVertexBuffer.h"
#include "KsIndexBuffer.h"
#endif

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
#define ksLIGHT_MAX						( 4 )		/**< ライトの最大数					*/
#define ksRENDER_STATE_STACK_MAX		( 8 )		/**< レンダーステートスタック最大数	*/

/* クリアービット */
#define ksCLEAR_FLAG_COLOR				( 1<<0 )	/**< カラークリアフラグ				*/
#define ksCLEAR_FLAG_DEPTH				( 1<<1 )	/**< 深度バッファクリアフラグ			*/
#define ksCLEAR_FLAG_STENCIL			( 1<<2 )	/**< ステンシルバッファクリアフラグ	*/
#define ksCLEAR_FLAG_ACCUM				( 1<<3 )	/**< アキュームレフバッファ			*/

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
	ksTRANSFORM_WORLD,				/**< ワールド					*/
	ksTRANSFORM_VIEW,				/**< ビュー						*/
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
	ksTEXTURE_COLOR_OP_FORCE32  = 0x7fffffff,	/**< 強制的に32bitにする					*/
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
	ksRENDER_STATE_OP_BLEND          = 0,			/**< ブレンドモード										*/
	ksRENDER_STATE_SRC_BLEND         = 1,			/**< SRCブレンディング									*/
    ksRENDER_STATE_DST_BLEND         = 2,			/**< DESTブレンディング									*/
	ksRENDER_STATE_ALPHA_BLEND       = 3,			/**< アルファブレンド										*/
	ksRENDER_STATE_ALPHA_FUNC        = 4,			/**< アルファ関数										*/
	ksRENDER_STATE_ALPHA_REF         = 5,			/**< アルファ基準値										*/
	ksRENDER_STATE_ALPHA_MASK        = 6,			/**< アルファマスク値										*/

	ksRENDER_STATE_ZTEST_ENABLE      = 7,			/**< Zバッファ(ON,OFF)									*/
	ksRENDER_STATE_ZWRITE_ENABLE     = 8,			/**< Zライト(ON,OFF)										*/
	ksRENDER_STATE_ALPAHTEST_ENABLE  = 9,			/**< アルファテスト(ON,OFF)								*/
	ksRENDER_STATE_FOG_ENABLE        = 10,			/**< フォグ(ON,OFF)										*/
	ksRENDER_STATE_LIGHTING          = 11,			/**< ライティング(ON,OFF)								*/
	ksRENDER_STATE_SHADE             = 12,			/**< シェーディング										*/
	ksRENDER_STATE_CULL              = 13,			/**< カリング											*/

	ksRENDER_STATE_STENCIL_ENABLE    = 14,			/**< ステンシル(ON,OFF)									*/
	ksRENDER_STATE_STENCIL_FAIL      = 15,			/**< ステンシルテスト失敗時のオペレーション				*/
	ksRENDER_STATE_STENCIL_ZFAIL     = 16,			/**< ステンシルテストかつZテストに失敗時のオペレーション	*/
	ksRENDER_STATE_STENCIL_PASS      = 17,			/**< ステンシルテストかつZテストの成功時のオペレーション	*/
	ksRENDER_STATE_STENCIL_FUNC      = 18,			/**< ステンシルファンクション								*/
	ksRENDER_STATE_STENCIL_REF       = 19,			/**< ステンシルの基準値									*/
	ksRENDER_STATE_STENCIL_MASK      = 20,			/**< ステンシルのマスク値									*/

	ksRENDER_STATE_COLOR_TEST_ENABLE = 21,			/**< カラーテスト(ON,OFF)								*/
	ksRENDER_STATE_COLOR_FUNC        = 22,			/**< カラー関数											*/
	ksRENDER_STATE_COLOR_REF         = 23,			/**< カラー基準値										*/
	ksRENDER_STATE_COLOR_MASK        = 24,			/**< カラーマスク値										*/
	ksRENDER_STATE_PIXEL_MASK        = 25,			/**< ピクセルマスク										*/
	ksRENDER_STATE_LOGICAL_OP_ENABLE = 26,			/**< ロジカルオペレーション(ON,OFF)						*/
	ksRENDER_STATE_LOGICAL_OP_BLEND  = 27,			/**< ロジカルオペレーションモード							*/

	ksRENDER_STATE_FORCE32           = 0x7fffffff,	/**< 強制的に32bitにする									*/

}ksRENDER_STATE_TYPE;


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

typedef enum _ksALPHA_FUNC_MODE
{
/*
SCEGU_NEVER   全てのピクセルを描画しない  
SCEGU_ALWAYS   全てのピクセルを描画する  
SCEGU_EQUAL   ピクセルのアルファ値＝固定値の場合に ピクセルを描画する  
SCEGU_NOTEQUAL   ピクセルのアルファ値≠固定値の場合に ピクセルを描画する  
SCEGU_LESS   ピクセルのアルファ値＜固定値の場合に ピクセルを描画する  
SCEGU_LEQUAL   ピクセルのアルファ値≦固定値の場合に ピクセルを描画する  
SCEGU_GREATER   ピクセルのアルファ値＞固定値の場合に ピクセルを描画する  
SCEGU_GEQUAL   ピクセルのアルファ値≧固定値の場合に ピクセルを描画する  
*/
	ksALPHA_FUNC_FORCE_DWORD = 0x7fffffff,	/**< 強制的に32bitにする		*/
}ksALPHA_FUNC_MODE;

/************************************************************************************************/
/**
 * ステンシル操作
 */
/************************************************************************************************/
typedef enum _ksSTENCIL_OP_MODE
{
	ksSTENCIL_OP_KEEP    = 0,				/**< 何もしない								*/
	ksSTENCIL_OP_ZERO    = 1,				/**< ステンシル値を 0 に変更する				*/
	ksSTENCIL_OP_REPLACE = 2,				/**< ステンシル値を設定値に変更する			*/
	ksSTENCIL_OP_INVERT  = 3,				/**< ステンシル値を反転する					*/
	ksSTENCIL_OP_INCR    = 4,				/**< ステンシル値を 1 増加する				*/
	ksSTENCIL_OP_DECR    = 5,				/**< ステンシル値を 1 減少する				*/
	ksSTENCIL_OP_FORCE32 = 0x7fffffff,		/**< 強制的に32bitにする						*/

}ksSTENCIL_OP_MODE;

/************************************************************************************************/
/**
 * ステンシルFUNC
 */
/************************************************************************************************/
typedef enum _ksSTENCIL_FUNC_MODE
{
	ksSTENCIL_FUNC_NEVER    = 0,			/**< 全てのピクセルを描画しない						*/
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
	ksBLEND_ONE_MINUS_DST_ALPHA = 10,			/**< ブレンディング係数 (1-Ad,1-Ad,1-Ad,1-Ad)	禁止	*/
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
	ksSHADE_FORCE32 = 0x7fffffff,		/**< 強制的に32bitにする			*/

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
	ksCULL_FORCE32 = 0x7fffffff,		/**< 強制的に32bitにする			*/

}ksCULL_MODE;

/************************************************************************************************/
/**
 * カリングモード
 */
/************************************************************************************************/
typedef enum _ksFOG_MODE
{
	ksFOG_NONE    = 0,					/**< フォグなし									*/
	ksFOG_EXP     = 1,					/**< 指数で、フォグ エフェクトが増す				*/
	ksFOG_EXP2    = 2,					/**< 指数の 2 乗で、フォグ エフェクトが増す		*/
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
    ksPRIMITIVE_FORCE32        = 0x7fffffff,

}ksPRIMITIVE_TYPE;


/************************************************************************************************/
/**
 * プリミティブの種類
 */
/************************************************************************************************/
typedef enum _ksRENDER_PRIM_TYPE
{

}ksRENDER_PRIM_TYPE;

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
class KsRenderState
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
class KsRenderStateStack
{
	public:
		/**
		 * コンストラクタ
		 */
											KsRenderStateStack() : m_index( 0 ) {}

		/**
		 * レンダーステートをプッシュする
		 * @param		pState				プッシュするレンダーステート
		 */
		KsBool								push( const KsRenderState* pState );

		/**
		 * レンダーステートをポップする
		 * @param		pState				レンダーステートを取得するためのポインタ
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

/************************************************************************************************/
/**
 * @class		KsRenderSystem
 * @brief		ベース描画システム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsRenderSystem
{
	public:
		/**
		 * コンストラクタ
		 */
											KsRenderSystem();

		/**
		 * デストラクタ
		 */
		virtual							~KsRenderSystem(){}

		/**
		 * 初期化処理
		 * @param		hWnd				ウインドウのハンドル
		 * @retval		ksTRUE				初期化成功
		 * @retval		ksFALSE				初期化失敗
		 */
		virtual KsBool						initialize( HWND hWnd ) = 0;

		/**
		 * 後処理
		 * @retval		ksTRUE				後処理成功
		 * @retval		ksFALSE				後処理失敗
		 */
		virtual KsBool						terminate() = 0;
		
		/**
		 * シーン描画開始
		 */
		virtual void						beginScene( KsUInt32 flags, KsColor color, KsReal depth, KsUInt32 stencil ) = 0;

		/**
		 * シーン描画終了
		 */
		virtual void						endScene() = 0;

		/**
		 * 描画バッファと表示バッファを入れ替え
		 */
		virtual void						swapBuffer() = 0;

		/**
		 * ビューポートをセットする
		 * @param		pViewport			ビューポート設定
		 */
		virtual void						setViewport( const KsViewport* pViewport ) = 0;

		/**
		 * フォグをセットする
		 */
		virtual void						setFog( ksFOG_MODE mode, KsColor color, KsReal start, KsReal end, KsReal density ) = 0;

		/*-------------------------------------<< プリミティブ描画機能関係 >>--------------------------------------------------*/
		/**
		 * ラインを描画(2D)
		 * @param		x					X座標
		 * @param		y					Y座標
		 * @param		color				色
		 */
		//virtual void						drawLine( KsInt16 x0, KsInt16 y0, KsInt16 x1, KsInt16 y1, KsUInt32 color ) = 0;

		/**
		 * 短形を描画
		 * @param		x					X座標
		 * @param		y					Y座標
		 * @param		w					幅
		 * @param		h					高さ
		 * @param		color				色
		 */
		virtual void						drawRect( KsInt32 x, KsInt32 y, KsInt32 w, KsInt32 h, KsColor color ) = 0;

		/**
		 * 短形を描画
		 * @param		x					X座標
		 * @param		y					Y座標
		 * @param		w					幅
		 * @param		h					高さ
		 * @param		u0					テクスチャのX座標
		 * @param		v0					テクスチャのY座標
		 * @param		u1					テクスチャの幅
		 * @param		v1					テクスチャの高さ
		 * @param		color				色
		 * @param		pTexture			テクスチャ
		 */
		//virtual void						drawRectEx( KsInt16 x, KsInt16 y, KsInt16 w, KsInt16 h, KsUInt16 tx, KsUInt16 ty, KsUInt16 tw, KsUInt16 th, KsUInt32 color, KsTexture* pTexture ) = 0;

		/**
		 * スプライト描画
		 * @param		pSpritePrim			スプライトのプリミティブ(4つの頂点配列をわたさないとバグる)
		 */
		//virtual void						drawSprite( KS_SPRITE_PRIM* pSpritePrim ) = 0;

		/**
		 *
		 */
		virtual void						drawPrimitive( ksPRIMITIVE_TYPE type, KsUInt32 vertexStart, KsUInt32 indexStart, KsUInt32 primitiveCount, KsVertexBuffer* pVertexBuffer, KsIndexBuffer* pIndexBuffer ) = 0;

		/*------------------------------------------<< テクスチャ関係 >>------------------------------------------------------*/
		/**
		 * テクスチャを生成する
		 * @param		pFileName			ファイル名
		 * @param		flags				生成フラグ
		 * @return							テクスチャのポインタ
		 */
		//virtual KsTexture*					createTexture( const KsChar* pFileName, KsUInt32 flags=0 ) = 0;

		/**
		 * イメージデータからテクスチャを生成する
		 * @param		pImage				イメージデータのポインタ
		 * @param		flags				生成フラグ
		 * @return							テクスチャのポインタ
		 */
		//virtual KsTexture*					createTexture( KsImage* pImage, KsUInt32 flags=0 ) = 0;

		/**
		 * テクスチャをセットする
		 * @param		statge				テクスチャステージ
		 * @param		pTexture			テクスチャ
		 */
		//virtual void						setTexture( KsUInt32 stage, KsTexture* pTexture ) = 0;

		/**
		 * テクスチャステートをセットする
		 * @param		statge				テクスチャステージ
		 * @param		state				セットするステータスの種類
		 * @param		value				セットする値
		 */
		//virtual void						setTextureState( KsUInt32 stage, ksTEXTURE_STATE_TYPE state, KsUInt32 value ) = 0;

		/*-----------------------------------<< マテリアル関係 >>--------------------------------------------------*/
		/**
		 * マテリアルをセットする
		 * @param		pMaterial			マテリアル
		 */
		virtual void						setMaterial( KsMaterial* pMaterial ) = 0;

		/*-------------------------------------<< ライト関係 >>--------------------------------------------------*/
		/**
		 * ライトを追加する
		 * @param		index				ライトのインデックス
		 * @param		pLight				ライト情報
		 * @note							ライトを設置できる数は、最大８です。<br>
		 *									ライトを取り除きいときは取り除きたいライトのインデックスとライトにNULLをセットしてください。
		 */
		virtual void						setLight( KsUInt32 index, const KsLight* pLight ) = 0;

		/**
		 * 指定ライトを有効、無効にする。
		 * @param		index				ライトのインデックス
		 * @param		flag				ライトのON OFFのフラグ( ksTRUE: ON, ksFALSE: OFF )
		 */
		virtual void						setLightEnable( KsUInt32 index, KsBool flag ) = 0;

		/**
		 * 指定インデックスのライトを取得する
		 * @param		index				インデックス
		 * @return							ライトのポインタ(セットされていないときはNULLが返る)
		 */
		virtual KsLight*					getLight( KsUInt32 index );

		/**
		 * 基本的に設定で3Dモードを初期化する
		 */
		//virtual void						auto2DMode() = 0;

		/**
		 * 基本的に設定で3Dモードを初期化する
		 */
		virtual void						auto3DMode() = 0;

		/*-------------------------------------<< レンダーステート関係 >>--------------------------------------------------*/
		/**
		 * レンダーステートをスタックにプッシュする
		 */
		void								pushRenderState();

		/**
		 * レンダーステートをスタックにポップする
		 */
		void								popRenderState();

		/**
		 * レンダーステート
		 * @param		state				ステートの種類
		 * @param		value				ステートに対応する値
		 */
		//virtual void						setRenderState( ksRENDER_STATE_TYPE state, KsUInt32 value ) = 0;

		/**
		 * トランスフォームする
		 * @param		state				トランスフォームのモード
		 * @param		pMatrix				変換マトリックス
		 */
		virtual void						setTransform( ksTRANSFORM_STATE state, const KsMatrix* pMatrix ) = 0;

	protected:
		KsMatrix							m_viewMatrix;					/**< ビューマトリックス					*/
		KsMatrix							m_worldMatrix;					/**< ワールドマトリックス					*/
		KsMatrix							m_textureMatrix;				/**< テクスチャマトリックス				*/
		KsTextureState						m_textureState;					/**< 現在のテクスチャステート				*/
		KsRenderState						m_renderState;					/**< 現在のレンダーステート				*/
		KsRenderStateStack					m_renderStateStack;				/**< レンダーステートスタック				*/
		KsLight								m_pLights[ ksLIGHT_MAX ];		/**< ライト								*/
		KsUInt32							m_clearFlags;					/**< クリアフラグ						*/
		KsColor								m_clearColor;					/**< バッファのクリアカラーセット			*/
		KsInt32								m_clearDepth;					/**< Zバッファのクリア値セット			*/
		KsInt32								m_clearStencil;					/**< ステンシルバッファのクリア値セット	*/
};

#endif		/* __KSRENDERSYSTEM_H__ */

