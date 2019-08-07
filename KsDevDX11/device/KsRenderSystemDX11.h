/************************************************************************************************/
/** 
 * @file		KsRenderSystemDX11.h
 * @brief		DirectX描画システム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSRENDERSYSTEMDX11_H__
#define __KSRENDERSYSTEMDX11_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsTextureManagerDX11;
class KsHardwareBufferManagerDX11;
class KsShaderManagerDX11;

/************************************************************************************************/
/**
 * @class		KsRenderSystemDX11
 * @brief		DirectX用の描画システム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksDEVDX11_API KsRenderSystemDX11 : public KsRenderSystem
{
	public:
		/**
		 * コンストラクタ
		 */
											KsRenderSystemDX11();

		/**
		 * コンストラクタ
		 * @param		pParam				生成パラメータ
		 */
											KsRenderSystemDX11( void* pParam );

		/**
		 * デストラクタ
		 */
		virtual								~KsRenderSystemDX11();

		/**
		 * 初期化処理
		 * @param		hWnd				ウインドウのハンドル
		 * @retval		ksTRUE				初期化成功
		 * @retval		ksFALSE				初期化失敗
		 */
		virtual KsBool						initialize( void* pParam );

		/**
		 * 後処理
		 * @retval		ksTRUE				後処理成功
		 * @retval		ksFALSE				後処理失敗
		 */
		virtual KsBool						terminate();

		/**
		 * シーンをクリアする
		 * @param		flags				描画フラグ
		 * @param		color				クリアーカラー
		 * @param		depth				ディプスクリアする値
		 * @param		stencil				ステンシルクリアする値
		 */
		virtual void						clearScene( KsUInt32 flags, KsColor color, KsReal depth, KsUInt32 stencil );

		/**
		 * シーン描画開始
		 * @param		flags				描画フラグ
		 * @param		color				クリアーカラー
		 * @param		depth				ディプスクリアする値
		 * @param		stencil				ステンシルクリアする値
		 */
		virtual void						beginScene( KsUInt32 flags, KsColor color, KsReal depth, KsUInt32 stencil );

		/**
		 * シーン描画終了
		 */
		virtual void						endScene();

		/**
		 * 描画バッファと表示バッファを入れ替え
		 */
		virtual void						present();

		/**
		 * ビューポートをセットする
		 * @param		pViewport			ビューポート設定
		 */
		virtual void						setViewport( const KsViewport* pViewport );

		/**
		 * フォグをセットする
		 */
		virtual void						setFog( ksFOG_MODE mode, KsColor color, KsReal start, KsReal end, KsReal density );

		/*-------------------------------------<< プリミティブ描画機能関係 >>--------------------------------------------------*/
		/**
		 * ラインを描画(2D)
		 * @param		x					X座標
		 * @param		y					Y座標
		 * @param		color				色
		 */
		//virtual void						drawLine( KsInt16 x0, KsInt16 y0, KsInt16 x1, KsInt16 y1, KsUInt32 color );

		/**
		 * 短形を描画
		 * @param		x					X座標
		 * @param		y					Y座標
		 * @param		w					幅
		 * @param		h					高さ
		 * @param		color				色
		 */
		virtual void						drawRect( KsReal x, KsReal y, KsReal w, KsReal h, KsColor color );

		/**
		 * テクスチャ付き短形を描画
		 * @param		x					X座標
		 * @param		y					Y座標
		 * @param		w					幅
		 * @param		h					高さ
		 * @param		tx					X座標
		 * @param		ty					Y座標
		 * @param		tw					幅
		 * @param		th					高さ
		 * @param		color				色
		 * @param		pTexture			テクスチャ
		 */
		virtual void						drawRectEx( KsReal x, KsReal y, KsReal w, KsReal h, KsReal tx, KsReal ty, KsReal tw, KsReal th, KsColor color, KsTexture* pTexture );

		/**
		 *
		 */
		virtual void						drawIndexedPrimitive( ksPRIMITIVE_TYPE type, KsUInt32 vertexStart, KsUInt32 indexStart, KsUInt32 primitiveCount, KsVertexBuffer* pVertexBuffer, KsIndexBuffer* pIndexBuffer );

		virtual void						drawPrimitive( ksPRIMITIVE_TYPE type, KsUInt32 vertexStart, KsUInt32 primitiveCount, KsVertexBuffer* pVertexBuffer );

		virtual void						drawPrimitiveUP( ksPRIMITIVE_TYPE type, KsUInt32 primitiveCount, const void* pVertexStreamZeroData, KsUInt32 vertexStreamZeroStride );

		virtual void						copyRect( KsRenderTarget* pSrcTarget, const KsRect* pSrcRect, KsRenderTarget* pDstTarget, const KsRect* pDstRect );

#if 0
		/*------------------------------------------<< Render State関係 >>--------------------------------------------------*/
		/*------------------------------------------<< Render State関係 >>--------------------------------------------------*/

		//-------------------------------------------------------------------------------------------------------------------
		// Blend states.
		//-------------------------------------------------------------------------------------------------------------------
		virtual KsBlendState*				Opaque() = 0;
		virtual KsBlendState*				AlphaBlend() = 0;
		virtual KsBlendState*				Additive() = 0;
		virtual KsBlendState*				NonPremultiplied() = 0;

		//-------------------------------------------------------------------------------------------------------------------
		// Depth stencil states.
		//-------------------------------------------------------------------------------------------------------------------
		virtual KsDepthStencilState*		DepthNone() = 0;
		virtual KsDepthStencilState*		DepthDefault() = 0;
		virtual KsDepthStencilState*		DepthRead() = 0;

		//-------------------------------------------------------------------------------------------------------------------
		// Rasterizer states.
		//-------------------------------------------------------------------------------------------------------------------
		virtual KsRasterizerState*			CullNone() = 0;
		virtual KsRasterizerState*			CullClockwise() = 0;
		virtual KsRasterizerState*			CullCounterClockwise() = 0;
		virtual KsRasterizerState*			Wireframe() = 0;

		//-------------------------------------------------------------------------------------------------------------------
		// Sampler states.
		//-------------------------------------------------------------------------------------------------------------------
		virtual KsSamplerState*				PointWrap() = 0;
		virtual KsSamplerState*				PointClamp() = 0;
		virtual KsSamplerState*				LinearWrap() = 0;
		virtual KsSamplerState*				LinearClamp() = 0;
		virtual KsSamplerState*				AnisotropicWrap() = 0;
		virtual KsSamplerState*				AnisotropicClamp() = 0;
		//-------------------------------------------------------------------------------------------------------------------
		// Blend states.
		//-------------------------------------------------------------------------------------------------------------------
		virtual KsBlendState*				Opaque();
		virtual KsBlendState*				AlphaBlend();
		virtual KsBlendState*				Additive();
		virtual KsBlendState*				NonPremultiplied();

		//-------------------------------------------------------------------------------------------------------------------
		// Depth stencil states.
		//-------------------------------------------------------------------------------------------------------------------
		virtual KsDepthStencilState*		DepthNone();
		virtual KsDepthStencilState*		DepthDefault();
		virtual KsDepthStencilState*		DepthRead();

		//-------------------------------------------------------------------------------------------------------------------
		// Rasterizer states.
		//-------------------------------------------------------------------------------------------------------------------
		virtual KsRasterizerState*			CullNone();
		virtual KsRasterizerState*			CullClockwise();
		virtual KsRasterizerState*			CullCounterClockwise();
		virtual KsRasterizerState*			Wireframe();

		//-------------------------------------------------------------------------------------------------------------------
		// Sampler states.
		//-------------------------------------------------------------------------------------------------------------------
		virtual KsSamplerState*				PointWrap();
		virtual KsSamplerState*				PointClamp();
		virtual KsSamplerState*				LinearWrap();
		virtual KsSamplerState*				LinearClamp();
		virtual KsSamplerState*				AnisotropicWrap();
		virtual KsSamplerState*				AnisotropicClamp();
#endif

		/*------------------------------------------<< テクスチャ関係 >>------------------------------------------------------*/
		/**
		 * テクスチャを生成する
		 * @param		pFileName			ファイル名
		 * @param		flags				生成フラグ
		 * @return							テクスチャのポインタ
		 */
		virtual KsTexture*					createTextureFromFile( const KsChar* pFileName, KsUInt32 flags );

		/**
		 * テクスチャを生成する
		 * @param		pData				イメージデータのポインタ
		 * @param		width				テクスチャの幅
		 * @param		height				テクスチャの高さ
		 * @param		format				テクスチャフォーマット
		 * @param		flags				生成フラグ
		 * @return							テクスチャのポインタ
		 */
		virtual KsTexture*					createTexture( const KS_SUBRESOURCE_DATA* pData, KsUInt32 width, KsUInt32 height, KsUInt32 format, KsUInt32 flags, KsUInt32 usage );
		/**
		 * イメージデータからテクスチャを生成する
		 * @param		pImage				イメージデータのポインタ
		 * @param		flags				生成フラグ
		 * @return							テクスチャのポインタ
		 */
		//virtual KsTexture*					createTexture( KsImage* pImage, KsUInt32 flags );

		/**
		 * テクスチャをセットする
		 * @param		statge				テクスチャステージ
		 * @param		pTexture			テクスチャ
		 */
		virtual void						setTexture( KsUInt32 stage, KsTexture* pTexture );

		/*-----------------------------------<< render 関係 >>--------------------------------------------------*/
		/* レンダーターゲット */
		virtual KsRenderTarget*				getRenderTarget();
		virtual void						setRenderTarget( KsRenderTarget* pRenderTarget );
		virtual KsRenderTarget*				createRenderTarget( KsUInt32 width, KsUInt32 height, ksPIXEL_FORMAT format, KsUInt32 flags );
		virtual KsRenderTarget*				createOffscreenTarget( KsUInt32 width, KsUInt32 height, ksPIXEL_FORMAT format, KsUInt32 flags );
		virtual KsRenderTargetTexture*		createRenderTargetTexture( KsUInt32 width, KsUInt32 height, ksPIXEL_FORMAT format, KsUInt32 flags );
		virtual KsRenderTarget*				createRenderTargetFromFile( KsUInt32 width, KsUInt32 height, ksPIXEL_FORMAT format, const KsChar* pFileName, KsColor color );
		virtual KsVertexDeclaration*		createVertexDeclaration( KS_VERTEX_ELEMENT* pVertexElements );
		virtual KsRenderTarget*				createRenderTextureView( KsUInt32 width, KsUInt32 height, KsUInt32 format );
		virtual KsRenderTarget*				createDepthStencilView( KsUInt32 width, KsUInt32 height, KsUInt32 textureFormat, KsUInt32 viewFormat, KsUInt32 resFormat );
		virtual KsUnorderedAccessView*		createUnorderedAccessView( KsUInt32 elementSize, KsUInt32 numElements, KsUInt32 format, KsUInt32 flags );
		virtual KsStructuredBuffer*			createStructuredBuffer( KsUInt32 elementSize, KsUInt32 numElements, KsUInt32 format, KsUInt32 flags );
		virtual void						setVertexDeclaration( KsVertexDeclaration* pVertexDeclaration );

		virtual KsSamplerState*				createSamplerState( const KS_SAMPLER_DESC* pSamplerStateDesc );
		virtual KsBlendState*				createBlendState( const KS_BLEND_DESC* pBlendStateDesc );
		virtual KsRasterizerState*			createRasterizerState( const KS_RASTERIZER_DESC* pRasterizerState );
		virtual KsDepthStencilState*		createDepthStencilState( const KS_DEPTH_STENCIL_DESC* pDepthStencilDesc );
		virtual KsRenderContext*			createDeferredContext();
		virtual KsCommandList*				createCommandList();

		/*-----------------------------------<< マテリアル関係 >>--------------------------------------------------*/
		/**
		 * マテリアルをセットする
		 * @param		pMaterial			マテリアル
		 */
		virtual void						setMaterial( KsMaterial* pMaterial );

		/*-------------------------------------<< ライト関係 >>--------------------------------------------------*/
		/**
		 * ライトを追加する
		 * @param		index				ライトのインデックス
		 * @param		pLight				ライ xト情報
		 * @note							ライトを設置できる数は、最大８です。<br>
		 *									ライトを取り除きいときは取り除きたいライトのインデックスとライトにNULLをセットしてください。
		 */
		virtual void						setLight( KsUInt32 index, const KsLight* pLight );

		/**
		 * 指定ライトを有効、無効にする。
		 * @param		index				ライトのインデックス
		 * @param		flag				ライトのON OFFのフラグ( ksTRUE: ON, ksFALSE: OFF )
		 */
		virtual void						setLightEnable( KsUInt32 index, KsBool flag );

		/*-------------------------------------<< レンダーステート関係 >>--------------------------------------------------*/
		/**
		 * レンダーステートをセットする
		 * @param		state				ステートの種類
		 * @param		value				ステートに対応する値
		 */
		virtual void						setRenderState( ksRENDER_STATE_TYPE state, KsUInt32 value );

		/**
		 * サンプラーステートをセットする
		 * @param		sampler				サンプラー番号
		 * @param		state				ステートの種類
		 * @param		value				ステートに対応する値
		 */
		virtual void						setSamplerState( KsUInt32 sampler, ksSAMPLER_STATE_TYPE state, KsUInt32 value );

		/**
		 * トランスフォームする
		 * @param		state				トランスフォームのモード
		 * @param		pMatrix				変換マトリックス
		 */
		virtual void						setTransform( ksTRANSFORM_STATE state, const KsMatrix4x4* pMatrix );

		/**
		 * 基本設定で3Dモードを初期化する
		 */
		virtual void						auto2DMode();

		/**
		 * 基本設定で3Dモードを初期化する
		 */
		virtual void						auto3DMode();


#if 0
		/**
		 * 基本設定で3Dモードを初期化する
		 */
		virtual void						auto2DMode();

		/**
		 * 基本設定で3Dモードを初期化する
		 */
		virtual void						auto3DMode();

	public:
		KsBool								m_vsync;					/**< vsyncを使用するかのフラグ				*/
		KsBool								m_useStencilBuffer;			/**< ステンシルバッファを使用するかどうか		*/

		D3DMULTISAMPLE_TYPE					m_FSAAType;					/**< マルチサンプリングタイプ					*/
		KsUInt32							m_FSAAQuality;				/**< マルチサンプリングの品質(level)			*/
	
		KsAdapterDX*						m_pAdapter;					/**< 現在使用しているアダプター				*/
		KsAdapterListDX*					m_pAdapterList;				/**< アダプターリスト							*/

		HWND								m_hWnd;						/**< ウインドウのハンドル						*/
		//HINSTANCE							m_D3DLibrary;				/**< ライブラリ								*/
		KsRenderTarget*						m_pRenderTarget;			/**< 描画ターゲット							*/
		KsBool								m_bDeviceLost;				/**< デバイスがロスト去れたかどうか			*/
		KsBool								m_bResetRenderState;
		KsBool								m_bFullScreen;


#endif
	public:
		ID3D11Device*						getD3DDevice() { return m_pDevice; }

	private:
		KsRenderTarget*						createRenderTargetView();
		KsRenderTarget*						createDepthStencilView();

	private:
		KsAdapterList*						m_pAdapterList;				/**< アダプターリスト						*/
		IDXGISwapChain*						m_pSwapChain;				/**< 						*/
		ID3D11Device*						m_pDevice;					/**< 						*/
		KsWindow*							m_pWindow;					/**< 						*/
		KsShaderManagerDX11*				m_pShaderManager;			/**< 						*/
		KsTextureManagerDX11*				m_pTextureManager;			/**< 						*/
		KsInputLayoutManagerDX11*			m_pInputLayoutManager;		/**< 						*/
		KsHardwareBufferManagerDX11*		m_pHardwareBufferManager;	/**< 						*/
		KsGraphicsDX11*						m_pGraphics;				/**< 						*/
};

#endif		/* __KSRENDERSYSTEMDX11_H__ */


