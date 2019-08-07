/************************************************************************************************/
/** 
 * @file		KsForwardPlusRender.h
 * @brief		Foward+レンダリング
 * @author		Tsukasa Kato
 * @date		2006/07/02
 * @since		2006/07/02
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSDFORWARDPLUSRENDER_H__
#define __KSDFORWARDPLUSRENDER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsForwardPlusRender
 * @brief		基本タスクマネージャクラス
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
class KsForwardPlusRender
{
	public:
		static const KsUInt32 MAX_NUM_LIGHTS          = 2*1024;
        static const KsUInt32 TILE_RES                = 16;
        static const KsUInt32 MAX_NUM_LIGHTS_PER_TILE = 544;

		/**
		 * コンストラクタ
		 * @param	pRenderSystem	描画システム
		 * @param	width			レンダーターゲットの幅
		 * @param	height			レンダーターゲットの高さ
		 */
		KsForwardPlusRender( KsRenderSystem* pRenderSystem, KsUInt32 width, KsUInt32 height, KsUInt32 MSAA=MSAA_SAMPLES );

		/**
		 * デストラクタ
		 */
		virtual						~KsForwardPlusRender();

		/**
		 * ビューポート設定
		 * @param		x		X座標
		 * @param		y		X座標
		 * @param		w		幅
		 * @param		h		高さ
 		 * @param		near	nearクリップ値
		 * @param		far		farクリップ値
		 */
		void						setViewport( KsInt32 x, KsInt32 y, KsInt32 w, KsInt32 h, KsReal minZ, KsReal maxZ, KsRenderContext* pRenderContext=NULL );

	private:
		/**
		 * レンダーステートを生成する
		 */
		void						createRenderState();

	private:
		KsRenderSystem*				m_pRenderSystem;				/**< 描画システム						*/
		KsRenderContext*			m_pRenderContext;				/**< 描画コンテキスト					*/
		KsGameSystem*				m_pGameSystem;					/**< ゲームシステム管理クラス			*/
		KsViewport					m_viewport;						/**< ビューポート						*/


        // state
		KsBlendState*				m_pAdditiveBlendingState;		/**< 不透明ブレンドステート				*/
		KsDepthStencilState*		m_pDisableDepthWrite;			/**< 深度ステンシルステート				*/
		KsDepthStencilState*		m_pDisableDepthTest;			/**< 深度ステンシルステート				*/
		KsRasterizerState*			m_pDisableCulling;				/**< ラスタライズステート				*/
};


#if 0

class KsRenderThread;
class KsGameSystem;
class KsShadowManager;
class KsDeferredLighting;

/************************************************************************************************/
/**
 * @class		KsForwardPlusRender
 * @brief		基本タスクマネージャクラス
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
class KsForwardPlusRender
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
		KsForwardPlusRender( KsRenderSystem* pRenderSystem, KsUInt32 width, KsUInt32 height, KsUInt32 MSAA=MSAA_SAMPLES );

		/**
		 * デストラクタ
		 */
		virtual					~KsForwardPlusRender();

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
		KsRasterizerState*		m_pRasterizerState;						/**< ラスタライズステート				*/
		KsBlendState*			m_pOpaqueState;							/**< 不透明ブレンドステート				*/
		KsBlendState*			m_pAlphaToCoverageState;				/**< アルファブレンドステート			*/
		KsDepthStencilState*	m_pDepthState;							/**< 深度ステンシルステート				*/


		KS_BLEND_DESC			desc = KsBlendState::DEFAULT;
		m_pBlendState = pRenderSystem->createBlendState( &desc );

	// ラスタライズステート
	{
		KS_RASTERIZER_DESC		desc = KsRasterizerState::DEFAULT;
		//desc.CullMode = KS_CULL_NONE;
		desc.CullMode = KS_CULL_BACK;
		desc.
		m_pRasterizerState = pRenderSystem->createRasterizerState( &desc );

    D3D11_BLEND_DESC BlendStateDesc;
    BlendStateDesc.AlphaToCoverageEnable = FALSE;
    BlendStateDesc.IndependentBlendEnable = FALSE;
    BlendStateDesc.RenderTarget[0].BlendEnable = FALSE;
    BlendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    BlendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE; 
    BlendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO; 
    BlendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    BlendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE; 
    BlendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO; 
    BlendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    V_RETURN( pd3dDevice->CreateBlendState( &BlendStateDesc, &g_pOpaqueState ) );
    BlendStateDesc.AlphaToCoverageEnable = TRUE;
    V_RETURN( pd3dDevice->CreateBlendState( &BlendStateDesc, &g_pAlphaToCoverageState ) );


	}

	// ブレンドステート
	{
		KS_BLEND_DESC			desc = KsBlendState::DEFAULT;
		m_pBlendState = pRenderSystem->createBlendState( &desc );
	}

	// ラスタライズステート
	{
		KS_DEPTH_STENCIL_DESC	desc = KsDepthStencilState::DEFAULT;
		desc.DepthFunc = KS_COMPARISON_GREATER_EQUAL;
		m_pDepthState = pRenderSystem->createDepthStencilState( &desc );
	}

		KsRenderSystem*			m_pRenderSystem;						/**< 描画システム						*/
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

#endif

#endif /* __KSDFORWARDPLUSRENDER_H__ */

