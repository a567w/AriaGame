/************************************************************************************************/
/** 
 * @file		KsRenderSystemGL.h
 * @brief		GL
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSRENDERSYSTEMPSP_H__
#define __KSRENDERSYSTEMPSP_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsRenderSystem.h"

/************************************************************************************************/
/**
 * @class		KsRenderSystemGL
 * @brief		OpenGL用の描画システム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsRenderSystemGL : public KsRenderSystem
{
	public:
		/**
		 * コンストラクタ
		 */
											KsRenderSystemGL();

		/**
		 * コンストラクタ
		 * @param		hWnd				ウインドウのハンドル
		 */
											KsRenderSystemGL( HWND hWnd );

		/**
		 * デストラクタ
		 */
		virtual							~KsRenderSystemGL();

		/**
		 * 初期化処理
		 * @param		hWnd				ウインドウのハンドル
		 * @retval		ksTRUE				初期化成功
		 * @retval		ksFALSE				初期化失敗
		 */
		virtual KsBool						initialize( HWND hWnd );

		/**
		 * 後処理
		 * @retval		ksTRUE				後処理成功
		 * @retval		ksFALSE				後処理失敗
		 */
		virtual KsBool						terminate();
		
		/**
		 * シーン描画開始
		 */
		virtual void						beginScene( KsUInt32 flags, KsColor color, KsReal depth, KsUInt32 stencil );

		/**
		 * シーン描画終了
		 */
		virtual void						endScene();

		/**
		 * 描画バッファと表示バッファを入れ替え
		 */
		virtual void						swapBuffer();

		/**
		 * マテリアルをセットする
		 * @param		pMaterial			マテリアル
		 */
		virtual void						setMaterial( KsMaterial* pMaterial ){}

		/**
		 * ビューポートをセットする
		 * @param		pViewport			ビューポート設定
		 */
		virtual void						setViewport( const KsViewport* pViewport ){}

		/**
		 * トランスフォームする
		 * @param		state				トランスフォームのモード
		 * @param		pMatrix				変換マトリックス
		 */
		virtual void						setTransform( ksTRANSFORM_STATE state, const KsMatrix* pMatrix ){}

		/**
		 * フォグをセットする
		 */
		virtual void						setFog( ksFOG_MODE mode, KsColor color, KsReal start, KsReal end, KsReal density ){}


	private:
		/**
		 * ピクセルフォーマットをセットする
		 * @retval		ksTRUE				成功
		 * @retval		ksFALSE				失敗
		 */
		KsBool								setupPixelFormat();

	private:
		KsBool								m_useStencilBuffer;		/**< ステンシルバッファを使用するかどうか	*/
		HWND								m_hWnd;					/**< ウインドウのハンドル					*/
		HDC									m_hDC;					/**< デバイスコンテキスト					*/
		HGLRC								m_hRC;					/**< レンダリングコンテキスト				*/
};


#if 0
/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
#define stDISP_LIST_SIZE				( 0x80000 )		/**< ディスプレイリストのサイズ(512KB)	*/
#define stPROJ_MATRIX_STACK_SIZE		( 8 )			/**< プロジェクション行列の数				*/
#define stVIEW_MATRIX_STACK_SIZE		( 32 )			/**< ビュー行列の数						*/
#define stWORLD_MATRIX_STACK_SIZE		( 8 )			/**< ワールド行列の数						*/
#define stTEX_MATRIX_STACK_SIZE			( 4 )			/**< テクスチャ行列の数					*/

#define stRENDER_VIEWPORT_OFFSET_X		( 2048 )		/**< ビューポート初期位置					*/
#define stRENDER_VIEWPORT_OFFSET_Y		( 2048 )		/**< ビューポート初期位置					*/

#define stRENDER_CLEAR_COLOR			( 0x00000000 )	/**< バッファのクリアする色				*/
#define stRENDER_CLEAR_DEPTH			( 0 )			/**< Zバッファをクリアする値				*/
#define stRENDER_CLEAR_STENCIL			( 0 )			/**< ステンシルバッファをクリアする値		*/

/* マトリックスのスタックのサイズ	*/
#define stMATRIX_STACK_SIZE	(	stPROJ_MATRIX_STACK_SIZE  + \
									stVIEW_MATRIX_STACK_SIZE  + \
									stWORLD_MATRIX_STACK_SIZE + \
									stTEX_MATRIX_STACK_SIZE )

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/



/************************************************************************************************/
/**
 * @class		KsRenderSystemGL
 * @brief		OpenGL用の描画システム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class StRenderSystemPSP : public StRenderSystem
{
	public:
		/**
		 * コンストラクタ
		 */
											StRenderSystemPSP();
											
		/**
		 * デストラクタ
		 */
		virtual							~StRenderSystemPSP();

		/**
		 * 初期化処理
		 * @param		hWnd				ウインドウのハンドル
		 * @retval		ksTRUE				初期化成功
		 * @retval		ksFALSE				初期化失敗
		 */
		virtual StBool						initialize();

		/**
		 * 後処理
		 * @retval		ksTRUE				後処理成功
		 * @retval		ksFALSE				後処理失敗
		 */
		virtual StBool						terminate();
		
		/**
		 * シーン描画開始
		 */
		virtual void						beginScene();

		/**
		 * シーン描画終了
		 */
		virtual void						endScene();

		/**
		 * 描画バッファと表示バッファを入れ替え
		 */
		virtual void						swapBuffer();

		/**
		 * ビューポートをセットする
		 * @param		pViewport			ビューポート設定
		 */
		virtual void						setViewport( const StViewport* pViewport );

		/**
		 * ビューオフセット値をセットする
		 * @param		offsetX				X座標オフセット
		 * @param		offsetY				Y座標オフセット
		 */
		virtual void						setViewOffset( StInt32 offsetX, StInt32 offsetY );

		/**
		 * フォグをセットする
		 */
		virtual void						setFog( StReal zs, StReal ze, StUInt32 color );

		/*-------------------------------------<< プリミティブ描画機能関係 >>--------------------------------------------------*/
		/**
		 * ラインを描画(2D)
		 * @param		x					X座標
		 * @param		y					Y座標
		 * @param		color				色
		 */
		virtual void						drawLine( StInt16 x0, StInt16 y0, StInt16 x1, StInt16 y1, StUInt32 color );

		/**
		 * 短形を描画
		 * @param		x					X座標
		 * @param		y					Y座標
		 * @param		w					幅
		 * @param		h					高さ
		 * @param		color				色
		 */
		virtual void						drawRect( StInt16 x, StInt16 y, StInt16 w, StInt16 h, StUInt32 color );

		/**
		 * 短形を描画
		 * @param		x					X座標
		 * @param		y					Y座標
		 * @param		w					幅
		 * @param		h					高さ
		 * @param		tx					テクスチャのX座標
		 * @param		ty					テクスチャのY座標
		 * @param		tw					テクスチャの幅
		 * @param		th					テクスチャの高さ
		 * @param		color				色
		 * @param		pTexture			テクスチャ
		 */
		virtual void						drawRectEx( StInt16 x, StInt16 y, StInt16 w, StInt16 h, StUInt16 tx, StUInt16 ty, StUInt16 tw, StUInt16 th, StUInt32 color, StTexture* pTexture );

		/**
		 * スプライト描画
		 * @param		pSpritePrim			スプライトのプリミティブ(4つの頂点配列をわたさないとバグる)
		 */
		virtual void						drawSprite( ST_SPRITE_PRIM* pSpritePrim );

		/*------------------------------------------<< テクスチャ関係 >>------------------------------------------------------*/
		/**
		 * テクスチャを生成する
		 * @param		pFileName			ファイル名
		 * @param		flags				生成フラグ
		 * @return							テクスチャのポインタ
		 */
		virtual StTexture*					createTexture( const StChar* pFileName, StUInt32 flags=0 );

		/**
		 * イメージデータからテクスチャを生成する
		 * @param		pImage				イメージデータのポインタ
		 * @param		flags				生成フラグ
		 * @return							テクスチャのポインタ
		 */
		virtual StTexture*					createTexture( StImage* pImage, StUInt32 flags=0 );

		/**
		 * テクスチャをセットする
		 * @param		statge				テクスチャステージ
		 * @param		pTexture			テクスチャ
		 */
		virtual void						setTexture(  StUInt32 stage, StTexture* pTexture );

		/**
		 * テクスチャステートをセットする
		 * @param		statge				テクスチャステージ
		 * @param		state				セットするステータスの種類
		 * @param		value				セットする値
		 */
		virtual void						setTextureState( StUInt32 stage, stTEXTURE_STATE_TYPE state, StUInt32 value );

		/*-----------------------------------<< マテリアル関係 >>--------------------------------------------------*/
		/**
		 * マテリアルをセットする
		 * @param		pMaterial			マテリアル
		 */
		virtual void						setMaterial( StMaterial* pMaterial );

		/*-------------------------------------<< ライト関係 >>--------------------------------------------------*/
		/**
		 * ライトを追加する
		 * @param		index				ライトのインデックス
		 * @param		pLight				ライト情報
		 * @note							ライトを設置できる数は、最大８です。<br>
		 *									ライトを取り除きいときは取り除きたいライトのインデックスとライトにNULLをセットしてください。
		 */
		virtual void						setLight( StUInt32 index, const StLight* pLight );

		/**
		 * 指定ライトを有効、無効にする。
		 */
		virtual void						setLightEnable( StUInt32 index, StBool flag );

		/**
		 * 基本的に設定で3Dモードを初期化する
		 */
		virtual void						auto2DMode();

		/**
		 * 基本的に設定で3Dモードを初期化する
		 */
		virtual void						auto3DMode();

		/*-------------------------------------<< レンダーステート関係 >>--------------------------------------------------*/
		/**
		 * レンダーステート
		 * @param		state				ステートの種類
		 * @param		value				ステートに対応する値
		 */
		virtual void						setRenderState( stRENDER_STATE_TYPE state, StUInt32 value );

		/**
		 * トランスフォームする
		 * @param		state				トランスフォームのモード
		 * @param		pMatrix				変換マトリックス
		 */
		//virtual void						setTransform( ksTRANSFORM_STATE state, const KsMatrix* pMatrix );

	private:
		void								setAlphaBlend( StBool value );
		void								setZTestEnable( StBool value );
		void								setFogEnable( StBool value );
		void								setZWriteEnable( StBool value );
		void								setAlphaTestEnable( StBool value );
		void								setLightEnable( StBool value );
		void								setShadeMode( stSHADE_MODE value );
		void								setCullMode( stCULL_MODE value );
		void								setBlendFunc( stBLEND_OP_MODE op, stBLEND_MODE src, stBLEND_MODE dst );

	private:
		KsTexture*							m_pCurrentTexture;
		//StUInt32							m_pixelFormat;
		//StInt32							m_width;
		//StInt32							m_height;
};
#endif


#endif		/* __STRENDERSYSTEMGL_H__ */

