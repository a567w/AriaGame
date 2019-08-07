/************************************************************************************************/
/** 
 * @file		KsSystemGL.h
 * @brief		カラー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSRENDERSYSGL_H__
#define __KSRENDERSYSGL_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsSystem.h"
/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/


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
class KsRenderSystemGL : public KsRenderSystem
{
	public:
		/**
		 * コンストラクタ
		 */
											KsRenderSystemGL();
											
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
		virtual void						beginScene();

		/**
		 * シーン描画終了
		 */
		virtual void						endScene();

		/**
		 * ビューポートをセットする
		 * @param		pViewport			ビューポート設定
		 */
		virtual void						setViewport( const KsViewport* pViewport );


		/**
		 * トランスフォームする
		 * @param		state				トランスフォームのモード
		 * @param		pMatrix				変換マトリックス
		 */
		virtual void						setTransform( ksTRANSFORM_STATE state, const KsMatrix* pMatrix );

		/**
		 * フォグをセットする
		 * @param		pFog				フォグをセットする( NULL )をセットするとフォグを無効
		 */
		//virtual void						setFog( const KsFog* pFog );

		/**
		 * テクスチャをセットする
		 * @param		statge				テクスチャステージ
		 * @param		pTexture			テクスチャ
		 */
		virtual void						setTexture(  KsUInt32 stage, KsTexture* pTexture );


		/**
		 * マテリアルをセットする
		 * @param		pMaterial			マテリアル
		 */
		virtual void						setMaterial( KsMaterial* pMaterial );

/*-------------------------------------<< ライト関係 >>--------------------------------------------------*/
		/**
		 * ライトを追加する
		 * @param		index				ライトのインデックス
		 * @param		pLight				ライト情報
		 * @note							ライトを設置できる数は、最大８です。<br>
		 *									ライトを取り除きいときは取り除きたいライトのインデックスとライトにNULLをセットしてください。
		 */
		virtual void						addLight( KsUInt32 index, const KsLight* pLight );

		/**
		 * 指定インデックスのライトを取得する
		 * @param		index				インデックス
		 * @return							ライトのポインタ(セットされていないときはNULLが返る)
		 */
		virtual KsLight*					getLight( KsUInt32 index );

		/**
		 * 指定インデックスのライトを削除する
		 * @param		index				インデックス
		 * @return							セットされていたライトのポインタ(ないときは、NULLが返る)
		 */
		virtual void						removeLight( KsUInt32 index );

		/**
		 * すべてのライトを削除する
		 */
		virtual void						removeAllLight();

		/**
		 * 指定ライトを有効、無効にする。
		 */
		virtual void						setLightEnable( KsUInt32 index, KsBool flag );
/*-------------------------------------<< レンダーステート関係 >>--------------------------------------------------*/

		/**
		 * レンダーステートをスタックにプッシュする
		 */
		virtual void						pushRenderState();

		/**
		 * レンダーステートをスタックにポップする
		 */
		virtual void						popRenderState();

		/**
		 * レンダーステート
		 * @param		state				ステートの種類
		 * @param		value				ステートに対応する値
		 */
		virtual void						setRenderState( ksRENDER_STATE_TYPE state, KsUInt32 value );

/*-------------------------------------<< プリミティブ描画機能関係 >>--------------------------------------------------*/
	protected:
		/**
		 * ピクセルフォーマットをセットアップする
		 */
		KsBool								setupPixelFormat();

		/**
		 * OpenGLの拡張をセットアップする
		 */
		//void								setupExtensions();

		/**
		 * ３Ｄのレンダーステートモードデフォルトでセットする
		 */
		//void								setRenderStates3D();

	protected:
		KsBool								m_useStencilBuffer;		/**< ステンシルバッファを使用するかどうか	*/
		HWND								m_hWnd;					/**< ウインドウのハンドル					*/
		HDC									m_hDC;					/**< デバイスコンテキスト					*/
		HGLRC								m_hRC;					/**< レンダリングコンテキスト				*/
};

#endif		/* __KSRENDERSYSGL_H__ */