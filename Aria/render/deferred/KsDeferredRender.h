/************************************************************************************************/
/** 
 * @file		KsDeferredRender.h
 * @brief		ディファードレンダリング
 * @author		Tsukasa Kato
 * @date		2006/07/02
 * @since		2006/07/02
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSDEFERREDRENDER_H__
#define __KSDEFERREDRENDER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
#define MSAA_SAMPLES					1

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsRenderThread;
class KsGameSystem;
class KsShadowManager;
class KsDeferredLighting;

/************************************************************************************************/
/**
 * @class		KsDeferredRender
 * @brief		基本タスクマネージャクラス
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
class KsDeferredRender
{
	public:
		static const KsUInt32	MAX_GBUFFER = 5;
		static const KsUInt32	MRT_RENDER_COUNT = 3;
		static const KsUInt32	MAX_RENDER_THREAD = 8;

	public:
		// G-Buffer
		// RT 0 [ Albedo r, g, b ] [ Specular Intensity ]
		// RT 1 [ Normal x, y ] [ Specular Power. ]
		enum ksMRT_TYPE
		{
			ksMRT_NORMAL,			/**< 法線情報	    */
			ksMRT_ALBEDO,			/**< Albedo     */
			ksMRT_POSITION,			/**< Position   */
			ksMRT_ZBUFFER,			/**< Z-Buffer   */
			ksMRT_ACCUMULATE		/**< Accumulate */
		};

	public:
		/**
		 * コンストラクタ
		 * @param	pRenderSystem	描画システム
		 * @param	width			レンダーターゲットの幅
		 * @param	height			レンダーターゲットの高さ
		 */
		KsDeferredRender( KsRenderSystem* pRenderSystem, KsUInt32 width, KsUInt32 height, KsUInt32 MSAA=MSAA_SAMPLES );

		/**
		 * デストラクタ
		 */
		virtual					~KsDeferredRender();

		/**
		 * ビューポート設定
		 * @param		x		X座標
		 * @param		y		X座標
		 * @param		w		幅
		 * @param		h		高さ
 		 * @param		near	nearクリップ値
		 * @param		far		farクリップ値
		 */
		void					setViewport( KsInt32 x, KsInt32 y, KsInt32 w, KsInt32 h, KsReal minZ, KsReal maxZ, KsRenderContext* pRenderContext=NULL );

		void					setRenderTarget_MRT( KsRenderContext* pRenderContext );
		void					setRenderTarget_Default( KsRenderContext* pRenderContext );
		void					clearScene();
		void					clearColor();
		void					clearDepthStencil();
		void					drawDebug();

		/**
		 * ライティングを初期化する
		 */
		void					initializeLight();

		/**
		 * シェーダーパラメータを更新する
		 */
		void					updateShaderParameter();

		/**
		 * ライトを更新する( ライト情報をテクスチャに書き込む )
		 */
		void					updateLight();

		/**
		 * ライティング計算
		 */
		void					computeLighting();

		/**
		 * GBufferを描画する
		 */
		void					renderGBuffer();

		/**
		 * カートゥーン輪郭線を描画する
		 */
		void					renderContourExtraction();

		/**
		 * 最終的な描画をする
		 */
		void					finalRender();

		/**
		 * 描画処理
		 */
		void					render();

		void					addModel( KsModel* pModel );
		void					addActor( KsActor* pActor );

	protected:
		KsRenderSystem*			m_pRenderSystem;						/**< 描画システム					*/
		KsRenderContext*		m_pRenderContext;						/**< 描画コンテキスト					*/
		KsRenderTarget*			m_pBackBuffer;							/**< バックバッファ					*/
		KsRenderTarget*			m_pDepthStencil;						/**< 深度バッファ					*/
		KsRenderTarget*			m_pGBuffer[ MAX_GBUFFER ];				/**< G-Buffer						*/
		KsTexture*				m_pGBufferTexture[ MAX_GBUFFER ];		/**< G-Buffer Texture				*/
		KsBool					m_isMRT;								/**< MRTかどうか？					*/
		KsModelParameter*		m_pParameter;							/**< Deferred シェーダーパラメータ	*/
		KsUInt32				m_dispatchWidth;						/**< Compute Shader Dispatch Widht	*/
		KsUInt32				m_dispatchHeight;						/**< Compute Shader Dispatch Height	*/
		KsReal					m_totalTime;							/**< */
		KsViewport				m_viewport;								/**< ビューポート					*/

		KsRasterizerState*		m_pRasterizerState;						/**< ラスタライズステート				*/
		KsBlendState*			m_pBlendState;							/**< ラスタライズステート				*/
		KsDepthStencilState*	m_pDepthState;							/**< ラスタライズステート				*/
		
		KsShadowManager*		m_pShadowManager;						/**< シャドウ管理クラス				*/

		// タスクマネージャに移行する
		KsArray<KsModel*>		m_pModels;								/**< */
		KsArray<KsActor*>		m_pActors;								/**< */

		//m_pDiffuseSampler;
		KsRenderThread*			m_pRenderThread[ MAX_RENDER_THREAD ];	/**< */
		KsUInt32				m_numRenderThread;						/**< */
		KsCamera*				m_pCamera;								/**< */

		KsEffect*				m_pDeferredEffect;						/**< Deferred エフェクト				*/
		KsEffect*				m_pContourEffect;						/**< カートゥーン輪郭線 エフェクト	*/
		KsDeferredLighting*		m_pLighting;							/**< ライティング処理	クラス			*/
		KsGameSystem*			m_pGameSystem;							/**< ゲームシステム管理クラス			*/
};

#endif /* __KSDEFERREDRENDER_H__ */

