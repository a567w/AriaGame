/************************************************************************************************/
/** 
 * @file		KsRenderSystemDX11.cpp
 * @brief		DirectX用の描画システム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsDevDX11/KsDevDX11PreCompile.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsRenderSystemDX11::KsRenderSystemDX11()
#if 0
	: m_pD3D( 0 )
	, m_pD3DDevice( 0 )
	, m_pAdapterList( 0 )
	, m_pAdapter( 0 )
	, m_pRenderTarget( 0 )
	, m_useStencilBuffer( ksFALSE )
	, m_bDeviceLost( ksFALSE )
	, m_bResetRenderState( ksFALSE )
	, m_bFullScreen( ksFALSE )
#endif
{
}

/************************************************************************************************/
/*
 * コンストラクタ
 * @param		hWnd				ウインドウのハンドル
 */
/************************************************************************************************/
KsRenderSystemDX11::KsRenderSystemDX11( void* pParam )
#if 0
	: m_pD3D( 0 )
	, m_pD3DDevice( 0 )
	, m_pAdapterList( 0 )
	, m_pAdapter( 0 )
	, m_pRenderTarget( 0 )
	, m_useStencilBuffer( ksFALSE )
	, m_bDeviceLost( ksFALSE )
	, m_bResetRenderState( ksFALSE )
	, m_bFullScreen( ksFALSE )
#endif
{
	/* 初期化する */
	initialize( pParam );
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsRenderSystemDX11::~KsRenderSystemDX11()
{
	/* 後処理 */
	terminate();
}

/************************************************************************************************/
/*
 * 初期化処理
 * @param		hWnd				ウインドウのハンドル
 * @retval		ksTRUE				初期化成功
 * @retval		ksFALSE				初期化失敗
 */
/************************************************************************************************/
KsBool KsRenderSystemDX11::initialize( void* pParam )
{
	m_pWindow = reinterpret_cast<KsWindow*>( pParam );

	KsRenderContextDX11*		pRenderContext = ksNew KsRenderContextDX11();

	//--------------------------------------------------------------------
	// 初期化順のテーブル
	//--------------------------------------------------------------------
	const static D3D_FEATURE_LEVEL FeatureLevels[] = 
	{
		D3D_FEATURE_LEVEL_11_0,		// DirectX11対応GPU
		D3D_FEATURE_LEVEL_10_1,		// DirectX10.1対応GPU
		D3D_FEATURE_LEVEL_10_0,		// DirectX10対応GPU
		D3D_FEATURE_LEVEL_9_3,		// DirectX9/ShaderModel3対応GPU
		D3D_FEATURE_LEVEL_9_2,		// DirectX9/ShaderModel2対応GPU
		D3D_FEATURE_LEVEL_9_1,		// DirectX9/ShaderModel2対応GPU
	};

	IDXGIAdapter*		pAdapter         = NULL;
	KsUInt32			numFeatureLevels = sizeof(FeatureLevels) / sizeof(D3D_FEATURE_LEVEL);
	D3D_DRIVER_TYPE		driverType       = D3D_DRIVER_TYPE_HARDWARE;
	KsUInt32			flags            = 0;
	KsUInt32			sdkVersion       = D3D11_SDK_VERSION;
	D3D_FEATURE_LEVEL	validFeatureLevel;

	// スワップチェインの設定
	DXGI_SWAP_CHAIN_DESC	scDesc;
	ZeroMemory( &scDesc, sizeof(scDesc) );
	scDesc.BufferCount                        = 1;									// スワップ チェーンのバッファー数を表す値です。
	scDesc.BufferDesc.Width                   = (KsUInt32)m_pWindow->getWidth();	// 解像度の幅を表す値です。
	scDesc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;			// 表示フォーマット
	scDesc.BufferDesc.RefreshRate.Numerator   = 60;									// リフレッシュレート(最大値)
	scDesc.BufferDesc.RefreshRate.Denominator = 1;									// リフレッシュレート(最小値)
	scDesc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// バック バッファーのサーフェス使用法
	scDesc.OutputWindow                       = m_pWindow->getHWnd();				// 出力ウィンドウへの HWND ハンドルです。
	scDesc.SampleDesc.Count                   = 1;									// ピクセル単位のマルチサンプリングの数です。
	scDesc.SampleDesc.Quality                 = 0;									// イメージの品質レベルです。
	scDesc.Windowed                           = TRUE;								// 出力がウィンドウ モードの場合は TRUE です。

	//--------------------------------------------------------------------
    // デバイスの生成
    //--------------------------------------------------------------------

	// まずはハードウェアデバイス生成を試す。
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
			pAdapter,	// NULLを指定すると規定のデバイス(選択しない限りNULLで構わない)
			driverType,
			NULL,
			flags,
			FeatureLevels,
			numFeatureLevels,
			sdkVersion,
			&scDesc,
			&m_pSwapChain,
			&m_pDevice,
			&validFeatureLevel,
			&pRenderContext->m_pDeviceContext );

	if( ksSUCCEEDED(hr) )
	{
		goto Label_DeviceCreateOK;
	}

	// ソフトウェアデバイス生成を試す。

Label_DeviceCreateOK:

	m_pAdapterList = ksNew KsAdapterListDX11( this );

	KsRenderTarget*	pRenderTargetView = createRenderTargetView();
	KsRenderTarget*	pDepthStencilView = createDepthStencilView();

	pRenderContext->setRenderTarget( pRenderTargetView, pDepthStencilView );

	//pRenderContext->setViewports();

	m_pRenderContext = pRenderContext;

	m_pShaderManager         = ksNew KsShaderManagerDX11( this );
	m_pTextureManager        = ksNew KsTextureManagerDX11( this );
	m_pInputLayoutManager    = ksNew KsInputLayoutManagerDX11( this );
	m_pHardwareBufferManager = ksNew KsHardwareBufferManagerDX11( this );
	m_pGraphics              = ksNew KsGraphicsDX11( this );

	pRenderContext->m_pDeviceContext->GSSetShader( NULL, NULL, 0 );				// ジオメトリシェーダー
	pRenderContext->m_pDeviceContext->HSSetShader( NULL, NULL, 0 );				// ハルシェーダー
	pRenderContext->m_pDeviceContext->DSSetShader( NULL, NULL, 0 );				// ドメインシェーダー

	return ksTRUE;
}

/************************************************************************************************/
/*
 * 後処理
 * @retval		ksTRUE				後処理成功
 * @retval		ksFALSE				後処理失敗
 */
/************************************************************************************************/
KsBool KsRenderSystemDX11::terminate()
{
	ksDELETE( m_pAdapterList );
	//ksRELEASE( m_pD3DDevice );
	//ksRELEASE( m_pD3D );

	return ksTRUE;
}

/************************************************************************************************/
/*
 * シーンをクリアする
 * @param		flags				描画フラグ
 * @param		color				クリアーカラー
 * @param		depth				ディプスクリアする値
 * @param		stencil				ステンシルクリアする値
 */
/************************************************************************************************/
void KsRenderSystemDX11::clearScene( KsUInt32 flags, KsColor color, KsReal depth, KsUInt32 stencil )
{
	m_pRenderContext->clearScene( flags, color, depth, stencil );
}

/************************************************************************************************/
/*
 * シーン描画開始
 * @param		flags				描画フラグ
 * @param		color				クリアーカラー
 * @param		depth				ディプスクリアする値
 * @param		stencil				ステンシルクリアする値
 */
/************************************************************************************************/
void KsRenderSystemDX11::beginScene( KsUInt32 flags, KsColor color, KsReal depth, KsUInt32 stencil )
{
}

/************************************************************************************************/
/*
 * シーン描画終了
 */
/************************************************************************************************/
void KsRenderSystemDX11::endScene()
{
}

/************************************************************************************************/
/*
 * 描画バッファと表示バッファを入れ替え
 */
/************************************************************************************************/
void KsRenderSystemDX11::present()
{
	// 1、2、3、4 - n 番目の垂直同期の後に表示を同期します。
	// 0,(現在のバッファーから) 各バッファーのフレームを出力に表示します。
	m_pSwapChain->Present( 1, 0 );
}

/************************************************************************************************/
/*
 * ビューポートをセットする
 * @param		pViewport			ビューポート設定
 */
/************************************************************************************************/
void KsRenderSystemDX11::setViewport( const KsViewport* pViewport )
{
}

/************************************************************************************************/
/*
 * フォグをセットする
 */
/************************************************************************************************/
void KsRenderSystemDX11::setFog( ksFOG_MODE mode, KsColor color, KsReal start, KsReal end, KsReal density )
{
}

/*-------------------------------------<< プリミティブ描画機能関係 >>--------------------------------------------------*/

/************************************************************************************************/
/*
 * 短形を描画
 * @param		x					X座標
 * @param		y					Y座標
 * @param		w					幅
 * @param		h					高さ
 * @param		color				色
 */
/************************************************************************************************/
void KsRenderSystemDX11::drawRect( KsReal x, KsReal y, KsReal w, KsReal h, KsColor color )
{
}

/************************************************************************************************/
/*
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
/************************************************************************************************/
void KsRenderSystemDX11::drawRectEx( KsReal x, KsReal y, KsReal w, KsReal h, KsReal tx, KsReal ty, KsReal tw, KsReal th, KsColor color, KsTexture* pTexture )
{
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX11::drawIndexedPrimitive( ksPRIMITIVE_TYPE type, KsUInt32 vertexStart, KsUInt32 indexStart, KsUInt32 primitiveCount, KsVertexBuffer* pVertexBuffer, KsIndexBuffer* pIndexBuffer )
{
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX11::drawPrimitive( ksPRIMITIVE_TYPE type, KsUInt32 vertexStart, KsUInt32 primitiveCount, KsVertexBuffer* pVertexBuffer )
{
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX11::drawPrimitiveUP( ksPRIMITIVE_TYPE type, KsUInt32 primitiveCount, const void* pVertexStreamZeroData, KsUInt32 vertexStreamZeroStride )
{
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX11::copyRect( KsRenderTarget* pSrcTarget, const KsRect* pSrcRect, KsRenderTarget* pDstTarget, const KsRect* pDstRect )
{
}

/*------------------------------------------<< テクスチャ関係 >>------------------------------------------------------*/
/************************************************************************************************/
/*
 * テクスチャを生成する
 * @param		pFileName			ファイル名
 * @param		flags				生成フラグ
 * @return							テクスチャのポインタ
 */
/************************************************************************************************/
KsTexture* KsRenderSystemDX11::createTextureFromFile( const KsChar* pFileName, KsUInt32 flags )
{
	KsTexture*	pFindTexture = m_pTextureManager->findRefInc( pFileName );

	if( pFindTexture )
	{
		return pFindTexture;
	}

	// テクスチャ設定
	KsTextureDX11*	pTexture = ksNew KsTextureDX11( this, pFileName, flags );

	m_pTextureManager->add( pTexture );

	return pTexture;
}

/************************************************************************************************/
/*
 * テクスチャを生成する
 * @param		pData				イメージデータのポインタ
 * @param		width				テクスチャの幅
 * @param		height				テクスチャの高さ
 * @param		format				テクスチャフォーマット
 * @param		flags				生成フラグ
 * @return							テクスチャのポインタ
 */
/************************************************************************************************/
KsTexture* KsRenderSystemDX11::createTexture( const KS_SUBRESOURCE_DATA* pData, KsUInt32 width, KsUInt32 height, KsUInt32 format, KsUInt32 flags, KsUInt32 usage )
{
// レンダリングテクスチャを作成する
	ID3D11Texture2D*				pRenderTargetTexture = NULL;
	ID3D11ShaderResourceView*		pShaderResourceView  = NULL;
	D3D11_TEXTURE2D_DESC			textureDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	D3D11_SUBRESOURCE_DATA*			pResource = pData ? (D3D11_SUBRESOURCE_DATA*)pData : NULL;

	// ゼロクリアーする
	KsZeroMemory( &textureDesc, sizeof(textureDesc) );

	textureDesc.Width              = width;//(KsUInt32)m_pWindow->getWidth();		// 解像度の幅を表す値です。
	textureDesc.Height             = height;//(KsUInt32)m_pWindow->getWidth();		// 解像度の幅を表す値です。
	textureDesc.MipLevels          = 1;
	textureDesc.ArraySize          = 1;
	textureDesc.Format             = (DXGI_FORMAT)format;// DXGI_FORMAT_R8G8B8A8_TYPELESS;
	textureDesc.SampleDesc.Count   = 1;
	textureDesc.Usage              = usage != 0 ? (D3D11_USAGE)usage : D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags          = flags != 0 ? flags : ( D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE);
	textureDesc.CPUAccessFlags     = 0;
	textureDesc.MiscFlags          = 0;

	HRESULT		hr = m_pDevice->CreateTexture2D( &textureDesc, (D3D11_SUBRESOURCE_DATA*)pData, &pRenderTargetTexture );

	if( ksFAILED( hr ) )
	{
		return NULL;
	}

	// ShaderResourceViewを作成する
	// これを作成しておかないとテクスチャリソースとして使用できない
	shaderResourceViewDesc.Format                    = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels       = 1;


	hr = m_pDevice->CreateShaderResourceView( pRenderTargetTexture, &shaderResourceViewDesc, &pShaderResourceView );
	
	if( ksFAILED( hr ) )
	{
		return NULL;
	}

	KsTextureDX11*	pTexture = ksNew KsTextureDX11( pRenderTargetTexture, pShaderResourceView );

	return pTexture;
}

/************************************************************************************************/
/*
 * テクスチャをセットする
 * @param		statge				テクスチャステージ
 * @param		pTexture			テクスチャ
 */
/************************************************************************************************/
void KsRenderSystemDX11::setTexture( KsUInt32 stage, KsTexture* pTexture )
{
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsRenderTarget* KsRenderSystemDX11::getRenderTarget()
{
	return NULL;
}

void KsRenderSystemDX11::setRenderTarget( KsRenderTarget* pRenderTarget )
{
}

KsRenderTarget* KsRenderSystemDX11::createRenderTarget( KsUInt32 width, KsUInt32 height, ksPIXEL_FORMAT format, KsUInt32 flags )
{
	return NULL;
}

KsRenderTarget* KsRenderSystemDX11::createOffscreenTarget( KsUInt32 width, KsUInt32 height, ksPIXEL_FORMAT format, KsUInt32 flags )
{
	return NULL;
}

KsRenderTargetTexture* KsRenderSystemDX11::createRenderTargetTexture( KsUInt32 width, KsUInt32 height, ksPIXEL_FORMAT format, KsUInt32 flags )
{
	return NULL;
}

KsRenderTarget* KsRenderSystemDX11::createRenderTargetFromFile( KsUInt32 width, KsUInt32 height, ksPIXEL_FORMAT format, const KsChar* pFileName, KsColor color )
{
	return NULL;
}

KsVertexDeclaration* KsRenderSystemDX11::createVertexDeclaration( KS_VERTEX_ELEMENT* pVertexElements )
{
	return NULL;
}

void KsRenderSystemDX11::setVertexDeclaration( KsVertexDeclaration* pVertexDeclaration )
{
}

/*-----------------------------------<< マテリアル関係 >>--------------------------------------------------*/
/************************************************************************************************/
/*
 * マテリアルをセットする
 * @param		pMaterial			マテリアル
 */
/************************************************************************************************/
void KsRenderSystemDX11::setMaterial( KsMaterial* pMaterial )
{
}

/*-------------------------------------<< ライト関係 >>--------------------------------------------------*/
/************************************************************************************************/
/*
 * ライトを追加する
 * @param		index				ライトのインデックス
 * @param		pLight				ライト情報
 * @note							ライトを設置できる数は、最大８です。<br>
 *									ライトを取り除きいときは取り除きたいライトのインデックスとライトにNULLをセットしてください。
 */
/************************************************************************************************/
void KsRenderSystemDX11::setLight( KsUInt32 index, const KsLight* pLight )
{
}

/************************************************************************************************/
/*
 * 指定ライトを有効、無効にする。
 * @param		index				ライトのインデックス
 * @param		flag				ライトのON OFFのフラグ( ksTRUE: ON, ksFALSE: OFF )
 */
/************************************************************************************************/
void KsRenderSystemDX11::setLightEnable( KsUInt32 index, KsBool flag )
{
}

/************************************************************************************************/
/*
 * レンダーステートをセットする
 * @param		state				ステートの種類
 * @param		value				ステートに対応する値
 */
/************************************************************************************************/
void KsRenderSystemDX11::setRenderState( ksRENDER_STATE_TYPE state, KsUInt32 value )
{
}

/************************************************************************************************/
/*
 * サンプラーステートをセットする
 * @param		sampler				サンプラー番号
 * @param		state				ステートの種類
 * @param		value				ステートに対応する値
 */
/************************************************************************************************/
void KsRenderSystemDX11::setSamplerState( KsUInt32 sampler, ksSAMPLER_STATE_TYPE state, KsUInt32 value )
{
}

/************************************************************************************************/
/*
 * トランスフォームする
 * @param		state				トランスフォームのモード
 * @param		pMatrix				変換マトリックス
 */
/************************************************************************************************/
void KsRenderSystemDX11::setTransform( ksTRANSFORM_STATE state, const KsMatrix4x4* pMatrix )
{
}

/************************************************************************************************/
/*
 * 基本設定で3Dモードを初期化する
 */
/************************************************************************************************/
void KsRenderSystemDX11::auto2DMode()
{
}

/************************************************************************************************/
/*
 * 基本設定で3Dモードを初期化する
 */
/************************************************************************************************/
void KsRenderSystemDX11::auto3DMode()
{
}

#if 0
KsAdapterListDX createAdapterList()
{
	KsAdapterListDX		AdapterList = NULL;
	IDXGIAdapter*		pAdapter    = NULL; 
	IDXGIFactory*		pFactory    = NULL; 

	if( ksFAILED( CreateDXGIFactory(__uuidof(IDXGIFactory) ,(void**)&pFactory) ) )
	{
		return vAdapters;
	}


	for( KsUInt32 i=0; pFactory->EnumAdapters( i, &pAdapter ) != DXGI_ERROR_NOT_FOUND; ++i )
	{
		vAdapters.push_back(pAdapter); 
	} 

	ksRELEASE( pFactory );

	return vAdapters;

	}

// デフォルトアダプターのインターフェースを作成する
HRESULT D3D11USER::CreateAdapter()
{
   HRESULT hr = E_FAIL;
   IDXGIFactory* pFactory = NULL;

   if( m_Adapter == NULL )
   {
      // ファクトリを作成する。
      // CreateDXGIFactory
      hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFactory) );
      if( FAILED( hr ) ) goto EXIT;

      // デフォルトアダプターを取得
      // IDXGIFactory::EnumAdapters
      hr = pFactory->EnumAdapters( 0, &m_Adapter );
      if( FAILED( hr ) ) goto EXIT;
   }

   hr = S_OK;
EXIT:
   SAFE_RELEASE( pFactory );

   return hr;
}

	HRESULT			hr;
	KsWindow*		pWindow = (KsWindow*)pParam;
	D3DDEVTYPE		devType = D3DDEVTYPE_HAL;
	KsBool			vsync   = ksTRUE;
	KsInt32		width   = pWindow->getWidth();
	KsInt32		height  = pWindow->getHeight();

	//m_useStencilBuffer = useStencilBuffer;	
	m_hWnd = pWindow->getHWnd();
	m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );

	if( !m_pD3D )
	{
		return ksFALSE;
	}

	/* アダプタリストを取得する */
	//m_pAdapterList = ksNew KsAdapterListDX( m_pD3D );

	/* 本当は選択して選ぶがここでは、0番を選択する */
	//m_pAdapter = m_pAdapterList->getItem( 0 );

	KsZeroMemory( &m_present, sizeof(m_present) );

	/* 本当は、使用可能かどうかをチェックする必要がある */
	m_present.SwapEffect             = D3DSWAPEFFECT_DISCARD;
	m_present.Windowed               = m_bFullScreen ? FALSE : TRUE;
	m_present.EnableAutoDepthStencil = 1;//m_useStencilBuffer;
	m_present.BackBufferCount        = 1;
	m_present.BackBufferWidth        = width;
	m_present.BackBufferHeight       = height;
	m_present.hDeviceWindow          = m_hWnd;
	//m_present.BackBufferFormat     = D3DFMT_R5G6B5;
	m_present.BackBufferFormat       = D3DFMT_A8R8G8B8;
	m_present.Flags                  = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;	/* バックバッファをロック可能にする */
	

	if( vsync )
	{
		m_present.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	}
	else
	{
		m_present.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}

	//m_present.MultiSampleType = mFSAAType;
	//m_present.MultiSampleQuality = (mFSAAQuality == 0) ? NULL : mFSAAQuality;

	/* ステンシルバッファチェック */
	if( m_useStencilBuffer )
	{
		m_present.AutoDepthStencilFormat = D3DFMT_D24S8;

		if( ksFAILED( m_pD3D->CheckDeviceFormat(
												D3DADAPTER_DEFAULT,
												D3DDEVTYPE_HAL,
												m_present.BackBufferFormat,
												D3DUSAGE_DEPTHSTENCIL,
												D3DRTYPE_SURFACE,
												D3DFMT_D24S8
											) ) )
		{
			m_useStencilBuffer = ksFALSE;
		}
		else if( ksFAILED( m_pD3D->CheckDepthStencilMatch(
														D3DADAPTER_DEFAULT,
														D3DDEVTYPE_HAL,
														m_present.BackBufferFormat,
														m_present.BackBufferFormat,
														D3DFMT_D24S8
													) ) )
		{
			m_useStencilBuffer = ksFALSE;
		} 		
	}
	/* ステンシルバッファ使用不可または、使わないとき */
	if( !m_useStencilBuffer ){
		m_present.AutoDepthStencilFormat = D3DFMT_D16;
	}


	/* デバイス生成 */
	hr = m_pD3D->CreateDevice(	
								D3DADAPTER_DEFAULT,
								D3DDEVTYPE_HAL,
								m_hWnd,
								D3DCREATE_HARDWARE_VERTEXPROCESSING,
								//D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
								&m_present,
								&m_pD3DDevice
							);

	if( ksFAILED( hr ) )
	{
		/* デバイス生成に失敗した(生成1) */
		hr = m_pD3D->CreateDevice( 
									D3DADAPTER_DEFAULT,
									D3DDEVTYPE_HAL,
									m_hWnd,
									//D3DCREATE_MIXED_VERTEXPROCESSING,
									D3DCREATE_MIXED_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
									&m_present,
									&m_pD3DDevice
								);

		if( ksFAILED( hr ) )
		{
			/* デバイス生成に失敗した(生成2) */
			hr = m_pD3D->CreateDevice(
										D3DADAPTER_DEFAULT,
										D3DDEVTYPE_HAL,
										m_hWnd,
										//D3DCREATE_SOFTWARE_VERTEXPROCESSING,
										D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
										&m_present,
										&m_pD3DDevice
									);

			if( ksFAILED( hr ) )
			{
				/* デバイス生成に失敗した(生成3) */
				hr = m_pD3D->CreateDevice( 
											D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_REF, 
											m_hWnd,
											//D3DCREATE_SOFTWARE_VERTEXPROCESSING,
											D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
											&m_present,
											&m_pD3DDevice
										);
			}
		}
	}

	m_pD3DDevice->GetDeviceCaps( &m_caps );

	if( m_useStencilBuffer && (!(m_caps.StencilCaps & D3DSTENCILCAPS_DECR) || !(m_caps.StencilCaps & D3DSTENCILCAPS_INCR) || !(m_caps.StencilCaps & D3DSTENCILCAPS_KEEP)) )
	{
		m_useStencilBuffer = ksFALSE;
	}

	if( !KsTextureManagerDX::getInstancePtr() )
	{
		m_pTextureManager = ksNew KsTextureManagerDX( m_pD3DDevice );
	}

	if( !KsHardwareBufferManagerDX::getInstancePtr() )
	{
		m_pHardwareBufferManager = ksNew KsHardwareBufferManagerDX( m_pD3DDevice );
	}

	if( !KsShaderManagerDX11::getInstancePtr() )
	{
		m_pShaderManager = ksNew KsShaderManagerDX11( this );
	}

	/* 描画ターゲット */
	KsRenderTargetDX*	pRenderTarget= ksNew KsRenderTargetDX();

	if( pRenderTarget )
	{

		/* バックバッファのポインタを確保 */
		m_pD3DDevice->GetRenderTarget( 0, &pRenderTarget->m_pRenderBuffer );

		/* 深度バッファのサーフェスを確保する */
		m_pD3DDevice->GetDepthStencilSurface( &pRenderTarget->m_pZBuffer );

		/* バックバッファのサイズを取得する */
		D3DSURFACE_DESC			desc;

		pRenderTarget->m_pRenderBuffer->GetDesc( &desc );
		pRenderTarget->m_width  = s_cast<KsInt32>( desc.Width );
		pRenderTarget->m_height = s_cast<KsInt32>( desc.Height );
		
		switch( desc.Format )
		{
			case D3DFMT_R8G8B8:
			case D3DFMT_A8R8G8B8:
			{
				pRenderTarget->m_format = ksPIXEL_A8R8G8B8;
				break;
			}
			case D3DFMT_X8R8G8B8:
			{
				pRenderTarget->m_format = ksPIXEL_X8R8G8B8;
				break;
			}
			case D3DFMT_R5G6B5:
			{
				pRenderTarget->m_format = ksPIXEL_R5G6B5;
				break;
			}
			case D3DFMT_X1R5G5B5:
			{
				pRenderTarget->m_format = ksPIXEL_X1R5G5B5;
				break;
			}
			case D3DFMT_A1R5G5B5:
			{
				pRenderTarget->m_format = ksPIXEL_A1R5G5B5;
				break;
			}
			case D3DFMT_A4R4G4B4:
			{
				pRenderTarget->m_format = ksPIXEL_A4R4G4B4;
				break;
			}
			case D3DFMT_R3G3B2:
			case D3DFMT_A8:
			case D3DFMT_A8R3G3B2:
			case D3DFMT_X4R4G4B4:
			case D3DFMT_A2B10G10R10:
			case D3DFMT_A8B8G8R8:
			case D3DFMT_X8B8G8R8:
			case D3DFMT_G16R16:
			case D3DFMT_A2R10G10B10:
			case D3DFMT_A16B16G16R16:
			case D3DFMT_A8P8:
			case D3DFMT_P8:
			case D3DFMT_L8:
			case D3DFMT_L16:
			case D3DFMT_A8L8:
			case D3DFMT_A4L4:
			default: break;
		}

		m_pRenderTarget = pRenderTarget;
	}
#endif



#if 0

/************************************************************************************************/
/*
 * シーンをクリアする
 * @param		flags				描画フラグ
 * @param		color				クリアーカラー
 * @param		depth				ディプスクリアする値
 * @param		stencil				ステンシルクリアする値
 */
/************************************************************************************************/
void KsRenderSystemDX11::clearScene( KsUInt32 flags, KsColor color, KsReal depth, KsUInt32 stencil )
{
	KsUInt32	mask = 0;

	if( flags & ksCLEAR_FLAG_COLOR )
	{
		mask |= D3DCLEAR_TARGET;
	}

	if( flags & ksCLEAR_FLAG_DEPTH )
	{
		mask |= D3DCLEAR_ZBUFFER;
	}

	if( flags & ksCLEAR_FLAG_STENCIL )
	{
		mask |= D3DCLEAR_STENCIL;
	}

	m_pD3DDevice->Clear( 0, NULL, mask, D3DCOLOR_ARGB( color.getAlpha(), color.getRed(), color.getGreen(), color.getBlue() ), depth, stencil );
}

/************************************************************************************************/
/*
 * シーン描画開始
 * @param		flags				描画フラグ
 * @param		color				クリアーカラー
 * @param		depth				ディプスクリアする値
 * @param		stencil				ステンシルクリアする値
 */
/************************************************************************************************/
void KsRenderSystemDX11::beginScene( KsUInt32 flags, KsColor color, KsReal depth, KsUInt32 stencil )
{
	HRESULT		hr;

	if( m_bDeviceLost )
	{
		if( ksFAILED( hr = m_pD3DDevice->TestCooperativeLevel() ) )
        {
			if( hr == D3DERR_DEVICELOST )
			{
				return;
			}

            if( hr == D3DERR_DEVICENOTRESET )
            {
				if( ksFAILED( m_pD3DDevice->Reset( &m_present ) ) )
				{
					return;
				}

				m_bDeviceLost       = ksFALSE;
				m_bResetRenderState = ksTRUE;
            }
            return;
        }
	}

	KsUInt32	mask = 0;

	if( flags & ksCLEAR_FLAG_COLOR )
	{
		mask |= D3DCLEAR_TARGET;
	}

	if( flags & ksCLEAR_FLAG_DEPTH )
	{
		mask |= D3DCLEAR_ZBUFFER;
	}

	if( flags & ksCLEAR_FLAG_STENCIL )
	{
		mask |= D3DCLEAR_STENCIL;
	}

	m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	m_pD3DDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

	m_pD3DDevice->Clear( 0, NULL, mask, D3DCOLOR_ARGB( color.getAlpha(), color.getRed(), color.getGreen(), color.getBlue() ), depth, stencil );

	m_pD3DDevice->BeginScene();
}

/************************************************************************************************/
/*
 * シーン描画終了
 */
/************************************************************************************************/
void KsRenderSystemDX11::endScene()
{
	if( m_bDeviceLost ){ return; }

	m_pD3DDevice->EndScene();
}

/************************************************************************************************/
/*
 * 描画バッファと表示バッファを入れ替え
 */
/************************************************************************************************/
void KsRenderSystemDX11::present()
{
	if( D3DERR_DEVICELOST == m_pD3DDevice->Present( NULL, NULL, NULL, NULL ) ){
		m_bDeviceLost = ksTRUE;
	}
}

/************************************************************************************************/
/*
 * マテリアルをセットする
 * @param		pMaterial			マテリアル
 */
/************************************************************************************************/
void KsRenderSystemDX11::setMaterial( KsMaterial* pMaterial )
{
	D3DMATERIAL9		material;
	
	material.Diffuse.r  = pMaterial->getDiffuse()->getRed();
	material.Diffuse.g  = pMaterial->getDiffuse()->getGreen();
	material.Diffuse.b  = pMaterial->getDiffuse()->getBlue();
	material.Diffuse.a  = pMaterial->getDiffuse()->getAlpha();
	
	material.Ambient.r  = pMaterial->getAmbient()->getRed();
	material.Ambient.g  = pMaterial->getAmbient()->getGreen();
	material.Ambient.b  = pMaterial->getAmbient()->getBlue();
	material.Ambient.a  = pMaterial->getAmbient()->getAlpha();
	
	material.Emissive.r = pMaterial->getEmissive()->getRed();
	material.Emissive.g = pMaterial->getEmissive()->getGreen();
	material.Emissive.b = pMaterial->getEmissive()->getBlue();
	material.Emissive.a = pMaterial->getEmissive()->getAlpha();

	material.Power      = pMaterial->getPower();

	m_pD3DDevice->SetMaterial( &material);
}

/************************************************************************************************/
/*
 * ビューポートをセットする
 * @param		pViewport			ビューポート設定
 */
/************************************************************************************************/
void KsRenderSystemDX11::setViewport( const KsViewport* pViewport )
{
	m_pD3DDevice->SetViewport( (D3DVIEWPORT9*)pViewport );
}

/************************************************************************************************/
/*
 * トランスフォームする
 * @param		state				トランスフォームのモード
 * @param		pMatrix				変換マトリックス
 */
/************************************************************************************************/
void KsRenderSystemDX11::setTransform( ksTRANSFORM_STATE state, const KsMatrix4x4* pMatrix )
{
	switch( state )
	{
		case ksTRANSFORM_WORLD:
		{
			/* ワールドにセット */
			m_pD3DDevice->SetTransform( D3DTS_WORLD, (D3DMATRIX*)( (void*)pMatrix ) );
			break;
		}
		case ksTRANSFORM_VIEW:
		{
			/* ビューににセット */
			m_pD3DDevice->SetTransform( D3DTS_VIEW, (D3DMATRIX*)( (void*)pMatrix ) );
			break;
		}
		case ksTRANSFORM_PROJECTION:
		{
			/* プロジェクションをセットする */
			m_pD3DDevice->SetTransform( D3DTS_PROJECTION, (D3DMATRIX*)( (void*)pMatrix ) );
			break;
		}
		case ksTRANSFORM_TEXTURE0:
		{
			m_pD3DDevice->SetTransform( D3DTS_TEXTURE0, (D3DMATRIX*)( (void*)pMatrix ) );
			break;
		}
		case ksTRANSFORM_TEXTURE1:
		{
			m_pD3DDevice->SetTransform( D3DTS_TEXTURE1, (D3DMATRIX*)( (void*)pMatrix ) );
			break;
		}
		case ksTRANSFORM_TEXTURE2:
		{
			m_pD3DDevice->SetTransform( D3DTS_TEXTURE2, (D3DMATRIX*)( (void*)pMatrix ) );
			break;
		}
		case ksTRANSFORM_TEXTURE3:
		{
			m_pD3DDevice->SetTransform( D3DTS_TEXTURE3, (D3DMATRIX*)( (void*)pMatrix ) );
			break;
		}
		case ksTRANSFORM_TEXTURE4:
		{
			m_pD3DDevice->SetTransform( D3DTS_TEXTURE4, (D3DMATRIX*)( (void*)pMatrix ) );
			break;
		}
		case ksTRANSFORM_TEXTURE5:
		{
			m_pD3DDevice->SetTransform( D3DTS_TEXTURE5, (D3DMATRIX*)( (void*)pMatrix ) );
			break;
		}
		default:{ break; }
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX11::setFog( ksFOG_MODE mode, KsColor color, KsReal start, KsReal end, KsReal density  )
{
	D3DRENDERSTATETYPE		on;
	D3DRENDERSTATETYPE		off;

	if( m_caps.RasterCaps & D3DPRASTERCAPS_FOGTABLE )
	{
		on  = D3DRS_FOGTABLEMODE;
		off = D3DRS_FOGVERTEXMODE;
	}
	else
	{
		on  = D3DRS_FOGVERTEXMODE;
		off = D3DRS_FOGTABLEMODE;
	}

	switch( mode )
	{
		case ksFOG_NONE:
		{
			m_pD3DDevice->SetRenderState( on, D3DFOG_NONE );
			m_pD3DDevice->SetRenderState( D3DRS_FOGENABLE, FALSE );
			return;
		}
		case ksFOG_EXP:
		{
			m_pD3DDevice->SetRenderState( D3DRS_FOGENABLE, TRUE );
			m_pD3DDevice->SetRenderState( off, D3DFOG_NONE );
			m_pD3DDevice->SetRenderState( on,  D3DFOG_EXP );
			m_pD3DDevice->SetRenderState( D3DRS_FOGDENSITY, *(DWORD*)(&density) );
			break;
		}
		case ksFOG_EXP2:
		{
			m_pD3DDevice->SetRenderState( D3DRS_FOGENABLE, TRUE );
			m_pD3DDevice->SetRenderState( off, D3DFOG_NONE );
			m_pD3DDevice->SetRenderState( on,  D3DFOG_EXP2 );
			m_pD3DDevice->SetRenderState( D3DRS_FOGDENSITY, *(DWORD*)(&density) ); 
			break;
		}
		case ksFOG_LINEAR:
		{
			m_pD3DDevice->SetRenderState( D3DRS_FOGENABLE, TRUE );
			m_pD3DDevice->SetRenderState( off, D3DFOG_NONE );
			m_pD3DDevice->SetRenderState( on,  D3DFOG_LINEAR );
			m_pD3DDevice->SetRenderState( D3DRS_FOGSTART, *(DWORD*)(&start) ); 
			m_pD3DDevice->SetRenderState( D3DRS_FOGEND,   *(DWORD*)(&end)   ); 
			break;
		}
		default: break;
	}

	m_pD3DDevice->SetRenderState( D3DRS_FOGCOLOR, D3DCOLOR_ARGB( color.getAlpha(), color.getRed(), color.getGreen(), color.getBlue() ) );
}

/************************************************************************************************/
/*
 * 短形を描画
 * @param		x					X座標
 * @param		y					Y座標
 * @param		w					幅
 * @param		h					高さ
 * @param		color				色
 */
/************************************************************************************************/
void KsRenderSystemDX11::drawRect( KsReal x, KsReal y, KsReal w, KsReal h, KsColor color )
{
	struct KsVertex2D
	{
		KsReal		x, y, z, rhw;
		KsUInt32	color;
	};

	KsVertex2D			vertices[ 4 ];
	DWORD				argb = D3DCOLOR_ARGB( color.getAlpha(), color.getRed(), color.getGreen(), color.getBlue() );

	vertices[ 0 ].x     = x;
	vertices[ 0 ].y     = y;
	vertices[ 0 ].z     = 0.0f;
	vertices[ 0 ].rhw   = 1.0f;
	vertices[ 0 ].color = argb;

	vertices[ 1 ].x     = x + w;
	vertices[ 1 ].y     = y;
	vertices[ 1 ].z     = 0.0f;
	vertices[ 1 ].rhw   = 1.0f;
	vertices[ 1 ].color = argb;

	vertices[ 2 ].x     = x;
	vertices[ 2 ].y     = y + h;
	vertices[ 2 ].z     = 0.0f;
	vertices[ 2 ].rhw   = 1.0f;
	vertices[ 2 ].color = argb;

	vertices[ 3 ].x     = x + w;
	vertices[ 3 ].y     = y + h;
	vertices[ 3 ].z     = 0.0f;
	vertices[ 3 ].rhw   = 1.0f;
	vertices[ 3 ].color = argb;

	static const KsUInt16	indeces[] = { 0, 1, 2, 3 };

	m_pD3DDevice->SetTexture( 0, NULL );

	m_pD3DDevice->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE );

	m_pD3DDevice->DrawIndexedPrimitiveUP(	D3DPT_TRIANGLESTRIP,
											0,
											4, 
											2,
											indeces,
											D3DFMT_INDEX16,
											vertices,
											sizeof(KsVertex2D)
										);
}

/************************************************************************************************/
/*
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
/************************************************************************************************/
void KsRenderSystemDX11::drawRectEx( KsReal x, KsReal y, KsReal w, KsReal h, KsReal tx, KsReal ty, KsReal tw, KsReal th, KsColor color, KsTexture* pTexture )
{
	if( pTexture )
	{
		struct KsVertexTex2D
		{
			KsReal		x, y, z, rhw;
			KsUInt32	color;
			KsReal		u, v;
		};

		KsVertexTex2D		vertices[ 4 ];
		DWORD				argb = D3DCOLOR_ARGB( color.getAlpha(), color.getRed(), color.getGreen(), color.getBlue() );

		vertices[ 0 ].x     = x;
		vertices[ 0 ].y     = y;
		vertices[ 0 ].z     = 0.0f;
		vertices[ 0 ].rhw   = 1.0f;
		vertices[ 0 ].color = argb;
		vertices[ 0 ].u     = tx;
		vertices[ 0 ].v     = ty;

		vertices[ 1 ].x     = x + w ;
		vertices[ 1 ].y     = y;
		vertices[ 1 ].z     = 0.0f;
		vertices[ 1 ].rhw   = 1.0f;
		vertices[ 1 ].color = argb;
		vertices[ 1 ].u     = tx + tw;
		vertices[ 1 ].v     = ty;

		vertices[ 2 ].x     = x;
		vertices[ 2 ].y     = y + h;
		vertices[ 2 ].z     = 0.0f;
		vertices[ 2 ].rhw   = 1.0f;
		vertices[ 2 ].color = argb;
		vertices[ 2 ].u     = tx;
		vertices[ 2 ].v     = ty + th;

		vertices[ 3 ].x     = x + w;
		vertices[ 3 ].y     = y + h;
		vertices[ 3 ].z     = tx;
		vertices[ 3 ].rhw   = 1.0f;
		vertices[ 3 ].color = argb;
		vertices[ 3 ].u     = tx + tw;
		vertices[ 3 ].v     = ty + th;

		static const KsUInt16	indeces[] = { 0, 1, 2, 3 };

		setTexture( 0, pTexture );

		m_pD3DDevice->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 );

		m_pD3DDevice->DrawIndexedPrimitiveUP(	D3DPT_TRIANGLESTRIP,
												0,
												4, 
												2,
												indeces,
												D3DFMT_INDEX16,
												vertices,
												sizeof(KsVertexTex2D)
											);
	
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
D3DPRIMITIVETYPE KsRenderSystemDX11::getPrimitiveTypeD3D( ksPRIMITIVE_TYPE type )
{
	static D3DPRIMITIVETYPE	 s_primitiveTypeD3D[] = 
	{
		D3DPT_POINTLIST,
		D3DPT_POINTLIST,
		D3DPT_LINELIST,
		D3DPT_LINESTRIP,
		D3DPT_TRIANGLELIST,
		D3DPT_TRIANGLESTRIP,
		D3DPT_TRIANGLEFAN,
	};

	return s_primitiveTypeD3D[ type ];
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX11::setD3DIndices( KsIndexBuffer* pIndexBuffer )
{
	KsIndexBufferDX*	pIndex  = reinterpret_cast< KsIndexBufferDX* >( pIndexBuffer );

	m_pD3DDevice->SetIndices( pIndex->getIndexBuffer() );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX11::setD3DFVF( KsVertexBuffer* pVertexBuffer )
{
	KsVertexBufferDX*	pVertex = reinterpret_cast< KsVertexBufferDX* >( pVertexBuffer );
	m_pD3DDevice->SetFVF( pVertex->getFVF() );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX11::setD3DStreamSource( KsVertexBuffer* pVertexBuffer )
{
	KsVertexBufferDX*	pVertex = reinterpret_cast< KsVertexBufferDX* >( pVertexBuffer );
	m_pD3DDevice->SetStreamSource( 0, pVertex->getVertexBuffer(), 0, pVertex->getVertexSize() );
}


/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX11::drawD3DIndexedPrimitive( ksPRIMITIVE_TYPE type, KsUInt32 vertexStart, KsUInt32 indexStart, KsUInt32 primitiveCount, KsVertexBuffer* pVertexBuffer )
{
	KsVertexBufferDX*	pVertex = reinterpret_cast< KsVertexBufferDX* >( pVertexBuffer );

	m_pD3DDevice->DrawIndexedPrimitive( getPrimitiveTypeD3D( type ), vertexStart, 0, pVertex->getNumVertex() - vertexStart, indexStart, primitiveCount );
}


/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX11::drawPrimitive( ksPRIMITIVE_TYPE type, KsUInt32 vertexStart, KsUInt32 primitiveCount, KsVertexBuffer* pVertexBuffer )
{
	KsVertexBufferDX*	pVertex = reinterpret_cast< KsVertexBufferDX* >( pVertexBuffer );

	m_pD3DDevice->SetFVF( pVertex->getFVF() );
	m_pD3DDevice->SetStreamSource( 0, pVertex->getVertexBuffer(), 0, pVertex->getVertexSize() );

	m_pD3DDevice->DrawPrimitive( getPrimitiveTypeD3D( type ), vertexStart, primitiveCount );
}


/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX11::drawPrimitiveUP( ksPRIMITIVE_TYPE type, KsUInt32 primitiveCount, const void* pVertexStreamZeroData, KsUInt32 vertexStreamZeroStride )
{
	m_pD3DDevice->DrawPrimitiveUP( s_cast<D3DPRIMITIVETYPE>(type), primitiveCount, pVertexStreamZeroData, vertexStreamZeroStride );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX11::drawIndexedPrimitive( ksPRIMITIVE_TYPE type, KsUInt32 vertexStart, KsUInt32 indexStart, KsUInt32 primitiveCount, KsVertexBuffer* pVertexBuffer, KsIndexBuffer* pIndexBuffer )
{
	KsVertexBufferDX*	pVertex = reinterpret_cast< KsVertexBufferDX* >( pVertexBuffer );
	KsIndexBufferDX*	pIndex  = reinterpret_cast< KsIndexBufferDX* >( pIndexBuffer );

	if( ksFVF_NONE != pVertex->getFVF() )
	{
		m_pD3DDevice->SetFVF( pVertex->getFVF() );
	}

	m_pD3DDevice->SetStreamSource( 0, pVertex->getVertexBuffer(), 0, pVertex->getVertexSize() );
	m_pD3DDevice->SetIndices( pIndex->getIndexBuffer() );

	m_pD3DDevice->DrawIndexedPrimitive( getPrimitiveTypeD3D( type ), vertexStart, 0, pVertex->getNumVertex() - vertexStart, indexStart, primitiveCount );
}

/************************************************************************************************/
/*
 * ライトを追加する
 * @param		index				ライトのインデックス
 * @param		pLight				ライト情報
 * @note							ライトを設置できる数は、最大８です。<br>
 *									ライトを取り除きいときは取り除きたいライトのインデックスとライトにNULLをセットしてください。
 */
/************************************************************************************************/
void KsRenderSystemDX11::setLight( KsUInt32 index, const KsLight* pLight )
{
	D3DLIGHT9		light;

	switch( pLight->m_type )
	{
		case ksLIGHT_TYPE_DIRECTION:
		{
			light.Type = D3DLIGHT_DIRECTIONAL;
			break;
		}
		case ksLIGHT_TYPE_POINT:
		{
			light.Type = D3DLIGHT_POINT;
			break;
		}
		case ksLIGHT_TYPE_SPOT:
		{
			light.Type = D3DLIGHT_SPOT;
			break;
		}
		default: break;
	}

	light.Diffuse.a    = pLight->m_diffuse.getAlpha();
	light.Diffuse.r    = pLight->m_diffuse.getRed();
	light.Diffuse.g    = pLight->m_diffuse.getGreen();
	light.Diffuse.b    = pLight->m_diffuse.getBlue();
	light.Specular.a   = pLight->m_specular.getAlpha();
	light.Specular.r   = pLight->m_specular.getRed();
	light.Specular.g   = pLight->m_specular.getGreen();
	light.Specular.b   = pLight->m_specular.getBlue();
	light.Ambient.a    = pLight->m_ambient.getAlpha();
	light.Ambient.r    = pLight->m_ambient.getRed();
	light.Ambient.g    = pLight->m_ambient.getGreen();
	light.Ambient.b    = pLight->m_ambient.getBlue();
	light.Position.x   = pLight->m_position.x;
	light.Position.y   = pLight->m_position.y;
	light.Position.z   = pLight->m_position.z;
	light.Direction.x  = pLight->m_direction.x;
	light.Direction.y  = pLight->m_direction.y;
	light.Direction.z  = pLight->m_direction.z;
	light.Range        = pLight->m_range;
	light.Falloff      = pLight->m_falloff;
	light.Attenuation0 = pLight->m_attenuation0;
    light.Attenuation1 = pLight->m_attenuation1;
    light.Attenuation2 = pLight->m_attenuation2;
	light.Theta        = pLight->m_theta;
	light.Phi          = pLight->m_phi;

	m_pD3DDevice->SetLight( index, &light );
}

/************************************************************************************************/
/*
 * 指定ライトを有効、無効にする。
 * @param		index				ライトのインデックス
 * @param		flag				ライトのON OFFのフラグ( ksTRUE: ON, ksFALSE: OFF )
 */
/************************************************************************************************/
void KsRenderSystemDX11::setLightEnable( KsUInt32 index, KsBool flag )
{
	m_pD3DDevice->LightEnable( index, flag );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX11::setSrcBlendFunc( ksBLEND_MODE blend )
{
	static D3DBLEND blendTbl[] = {	D3DBLEND_ZERO,
									D3DBLEND_ZERO,
									D3DBLEND_ONE,
									D3DBLEND_SRCCOLOR,
									D3DBLEND_DESTCOLOR,
									D3DBLEND_INVSRCCOLOR,
									D3DBLEND_INVDESTCOLOR,
									D3DBLEND_SRCALPHA,
									D3DBLEND_DESTALPHA,
									D3DBLEND_INVSRCALPHA,
									D3DBLEND_INVDESTALPHA
								};

	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, (DWORD)blendTbl[ blend ]  );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX11::setDstBlendFunc( ksBLEND_MODE blend )
{
	static D3DBLEND blendTbl[] = {	D3DBLEND_ZERO,
									D3DBLEND_ZERO,
									D3DBLEND_ONE,
									D3DBLEND_SRCCOLOR,
									D3DBLEND_DESTCOLOR,
									D3DBLEND_INVSRCCOLOR,
									D3DBLEND_INVDESTCOLOR,
									D3DBLEND_SRCALPHA,
									D3DBLEND_DESTALPHA,
									D3DBLEND_INVSRCALPHA,
									D3DBLEND_INVDESTALPHA
								};

	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, (DWORD)blendTbl[ blend ]  );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX11::setCullMode( ksCULL_MODE value )
{
	switch( value )
	{
		case ksCULL_NONE:
		{
			/* 背面のカリングなし */
			m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, (DWORD)D3DCULL_NONE );
			break;
		}
		case ksCULL_CW:
		{
			/* 背面のカリングあり */
			m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, (DWORD)D3DCULL_CW );
			break;
		}
		case ksCULL_CCW:
		{
			/* 背面のカリングあり */
			m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, (DWORD)D3DCULL_CCW );
			break;
		}
		default:
		{
			/* 背面のカリングなし */
			m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, (DWORD)D3DCULL_NONE );
			break;
		}
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX11::setShadeMode( ksSHADE_MODE value )
{
    switch( value )
    {
		case ksSHADE_FLAT:
		{
			m_pD3DDevice->SetRenderState( D3DRS_SHADEMODE, (DWORD)D3DSHADE_FLAT );
			break;
		}
		case ksSHADE_GOURAUD:
		{
			m_pD3DDevice->SetRenderState( D3DRS_SHADEMODE, (DWORD)D3DSHADE_GOURAUD );
			break;
		}
		default:
		{
			m_pD3DDevice->SetRenderState( D3DRS_SHADEMODE, (DWORD)D3DSHADE_GOURAUD );
			break;
		}
    }
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX11::setStencilFunc( ksSTENCIL_FUNC_MODE mode )
{
	static D3DCMPFUNC stencilFunc[] = 
	{
		D3DCMP_NEVER,
		D3DCMP_ALWAYS,
		D3DCMP_EQUAL,
		D3DCMP_NOTEQUAL,
		D3DCMP_LESS,
		D3DCMP_LESSEQUAL,
		D3DCMP_GREATER,
		D3DCMP_GREATEREQUAL,
	};

	m_pD3DDevice->SetRenderState( D3DRS_STENCILFUNC, stencilFunc[ mode ] );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
D3DSTENCILOP KsRenderSystemDX11::convStencilMode(  ksSTENCIL_OP_MODE op )
{
	static D3DSTENCILOP		stencilMode[] = 
	{
		D3DSTENCILOP_KEEP,
		D3DSTENCILOP_ZERO,
		D3DSTENCILOP_REPLACE,
		D3DSTENCILOP_INCRSAT,
		D3DSTENCILOP_DECRSAT,
		D3DSTENCILOP_INVERT,
		D3DSTENCILOP_INCR,
		D3DSTENCILOP_DECR,
	};

	return stencilMode[ op ];
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX11::setStencilZFail( ksSTENCIL_OP_MODE op )
{
	m_pD3DDevice->SetRenderState( D3DRS_STENCILZFAIL, convStencilMode( op ) );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX11::setStencilFail( ksSTENCIL_OP_MODE op )
{
	m_pD3DDevice->SetRenderState( D3DRS_STENCILFAIL, convStencilMode( op ) );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX11::setStencilPass( ksSTENCIL_OP_MODE op )
{
	m_pD3DDevice->SetRenderState( D3DRS_STENCILPASS, convStencilMode( op ) );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX11::setTexture(  KsUInt32 stage, KsTexture* pTexture )
{
	IDirect3DTexture9*		pDirect3DTexture;

	if( pTexture )
	{
		pDirect3DTexture = reinterpret_cast< KsTextureDX* >( pTexture )->getDirect3DTexture();
	}
	else
	{
		pDirect3DTexture = NULL;
	}

	m_pD3DDevice->SetTexture( stage, pDirect3DTexture );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX11::createD3DSurfaceFromFile( IDirect3DSurface9** pSurface, const KsChar* pFileName )
{
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsRenderTarget* KsRenderSystemDX11::createRenderTargetFromFile( KsUInt32 width, KsUInt32 height, ksPIXEL_FORMAT format, const KsChar* pFileName, KsColor color )
{
	KsRenderTargetDX*		pRenderTarget = ksNew KsRenderTargetDX();

	if( pRenderTarget )
	{
		HRESULT	hr;

		hr = m_pD3DDevice->CreateOffscreenPlainSurface( width, height, getD3DFormat( format ), D3DPOOL_DEFAULT, &pRenderTarget->m_pRenderBuffer, NULL );
		hr = D3DXLoadSurfaceFromFile( pRenderTarget->m_pRenderBuffer, NULL, NULL, pFileName, NULL, D3DX_DEFAULT, D3DCOLOR_ARGB( 0xff, color.getRed(), color.getGreen(), color.getBlue() ), NULL );
		pRenderTarget->m_width  = width;
		pRenderTarget->m_height = height;
		pRenderTarget->m_format = format;

		return pRenderTarget;
	}

	return NULL;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsRenderTarget* KsRenderSystemDX11::createRenderTarget( KsUInt32 width, KsUInt32 height, ksPIXEL_FORMAT format, KsUInt32 flags )
{
	//KsRenderTargetDX*	pRenderTarget = NULL;
	//pRenderTarget = ksNew KsRenderTarget();
	//m_pD3DDevice->CreateRenderTarget( width, height, TEXTURE_FORMAT, D3DMULTISAMPLE_NONE, 0, FALSE, &pRenderTarget->m_pRenderBuffer, NULL );
	return NULL;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsRenderTargetTexture* KsRenderSystemDX11::createRenderTargetTexture( KsUInt32 width, KsUInt32 height, ksPIXEL_FORMAT format, KsUInt32 flags )
{
	KsRenderTargetTextureDX*	pRenderTarget = ksNew KsRenderTargetTextureDX();

	if( pRenderTarget )
	{
		HRESULT				hr;
		IDirect3DTexture9*	pTexture;
		KsTextureDX*		pTextureDX;

		hr = m_pD3DDevice->CreateTexture(	width,
											height,
											1,
											D3DUSAGE_RENDERTARGET,
											getD3DFormat( format ),
											D3DPOOL_DEFAULT,
											&pTexture,
											NULL
										);

		pTextureDX = ksNew KsTextureDX();

		pTextureDX->m_pDirect3DTexture = pTexture;

		pTexture->GetSurfaceLevel( 0, &pRenderTarget->m_pRenderBuffer );

		pRenderTarget->m_pTexture = pTextureDX;
		pRenderTarget->m_width    = width;
		pRenderTarget->m_height   = height;
		pRenderTarget->m_format   = format;

		if( 0 == flags )
		{
			pRenderTarget->m_flags = ksRENDER_TARGET_BACKBUFFER_TEXTURE;
		}

		return pRenderTarget;
	}

#if 0
	/* 描画ターゲット */
	KsRenderTargetDX*	pRenderTarget= ksNew KsRenderTargetDX();

		/* バックバッファのポインタを確保 */
		m_pD3DDevice->GetRenderTarget( 0, &pRenderTarget->m_pRenderBuffer );

		/* 深度バッファのサーフェスを確保する */
		m_pD3DDevice->GetDepthStencilSurface( &pRenderTarget->m_pZBuffer );

		/* バックバッファのサイズを取得する */
		D3DSURFACE_DESC			desc;

		pRenderTarget->m_pRenderBuffer->GetDesc( &desc );
		pRenderTarget->m_width  = s_cast<KsInt32>( desc.Width );
		pRenderTarget->m_height = s_cast<KsInt32>( desc.Height );

		/* 描画用のテクスチャを生成する */
		IDirect3DTexture9*	pRenderTargetTexture;
		IDirect3DSurface9*	pRenderTargetSurface;

		m_pD3DDevice->CreateTexture(	desc.Width,
										desc.Height,
										1,
										D3DUSAGE_RENDERTARGET,
										D3DFMT_A8R8G8B8,
										D3DPOOL_DEFAULT,
										&pRenderTargetTexture
									);
		/* テクスチャのサーフェースを取得する(参照カウントがアップされる) */
		pRenderTargetTexture->GetSurfaceLevel( 0, &pRenderTargetSurface );

		/* レンダーターゲットにテクスチャをセットする */
		m_pD3DDevice->SetRenderTarget( 0, pRenderTargetSurface );

		/* Ｚステンシルターゲットにテクスチャをセットする */
		//m_pD3DDevice->SetDepthStencilSurface( pZStencilSurface );
#endif
	return NULL;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsRenderTarget* KsRenderSystemDX11::createOffscreenTarget( KsUInt32 width, KsUInt32 height, ksPIXEL_FORMAT format, KsUInt32 flags )
{
	KsRenderTargetDX*		pRenderTarget = ksNew KsRenderTargetDX();

	if( pRenderTarget )
	{
		HRESULT	hr;
		hr = m_pD3DDevice->CreateOffscreenPlainSurface( width, height, getD3DFormat( format ), D3DPOOL_DEFAULT, &pRenderTarget->m_pRenderBuffer, NULL );
		hr = m_pD3DDevice->ColorFill( pRenderTarget->m_pRenderBuffer, NULL, 0x00000000 );
		pRenderTarget->m_width  = width;
		pRenderTarget->m_height = height;
		pRenderTarget->m_format = format;

		return pRenderTarget;
	}

	return NULL;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsTexture*	KsRenderSystemDX11::createTextureFromFile( const KsChar* pFileName, KsUInt32 flags )
{
	KsTexture*	pFindTexture = m_pTextureManager->findRefInc( pFileName );

	if( pFindTexture )
	{
		return pFindTexture;
	}


	HRESULT					hr;
	LPDIRECT3DTEXTURE9		pDirect3DTexture;
	
	hr = D3DXCreateTextureFromFile( m_pD3DDevice, pFileName,  &pDirect3DTexture );
	//WCHAR		buffer[ ksPATH_MAX ];
	//KsInt32	len = ::MultiByteToWideChar( CP_THREAD_ACP, 0, pFileName, -1, NULL, 0 );
	//::MultiByteToWideChar( CP_THREAD_ACP, 0, pFileName, static_cast<KsInt32>(strlen(pFileName)+1), buffer, len );
	//D3DXCreateTextureFromFileEx(m_pD3DDevice, pFileName, D3DX_DEFAULT, D3DX_DEFAULT, 1,0,D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0,255,0),NULL,NULL, &(pTexture->m_pDirect3DTexture)  );

	if( hr != D3D_OK )
	{
		return NULL;
	}

	D3DSURFACE_DESC		desc;
	KsTextureDX*		pTexture = ksNew KsTextureDX();

	pTexture->m_id = KsCrc32( (KsUInt8*)pFileName );
	pTexture->m_name = pFileName;
	pTexture->m_pDirect3DTexture = pDirect3DTexture;
	pTexture->m_pDirect3DTexture->GetLevelDesc( 0, &desc );
	pTexture->m_width  = s_cast<KsUInt16>( desc.Width );
	pTexture->m_height = s_cast<KsUInt16>( desc.Height );

	// 転送元のブレンディング ステートを設定します。
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	// 転送先のブレンディング ステートを設定します。

	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
    
	//m_pD3DDevice->CreateTexture( 256, 256, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &pTex, NULL );

	//m_pD3DDevice->CreateTexture(

	//D3DXCreateTextureFromFileEx( m_pD3DDevice, 256, 256, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &pTex );
	//D3DXCreateTextureFromFileEx(m_pD3DDevice,pFileName,256,256, 1,0,D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0,255,0),NULL,NULL, &(pTexture->m_pDirect3DTexture)  );

	m_pTextureManager->add( pTexture );

	//return pTexture;
	return pTexture;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsVertexDeclaration* KsRenderSystemDX11::createVertexDeclaration( KS_VERTEX_ELEMENT* pVertexElements )
{
	KsVertexDeclarationDX* pVertexDecl = ksNew KsVertexDeclarationDX( this, pVertexElements );

	return pVertexDecl;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX11::setVertexDeclaration( KsVertexDeclaration* pVertexDeclaration )
{
	KsVertexDeclarationDX*	pVertexDeclarationDX = r_cast<KsVertexDeclarationDX*>( pVertexDeclaration );

	m_pD3DDevice->SetVertexDeclaration( pVertexDeclarationDX->m_pDecl );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsRenderTarget* KsRenderSystemDX11::getRenderTarget()
{
	return m_pRenderTarget;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX11::setRenderTarget( KsRenderTarget* pRenderTarget )
{
	if( pRenderTarget->getFlags() & ksRENDER_TARGET_BACKBUFFER_TEXTURE )
	{
		KsRenderTargetTextureDX*	pRenderTargetTextureDX  = r_cast<KsRenderTargetTextureDX*>( pRenderTarget );
		m_pD3DDevice->SetRenderTarget( 0, pRenderTargetTextureDX->m_pRenderBuffer );
	}
	else
	{
		KsRenderTargetDX*	pRenderTargetDX  = r_cast<KsRenderTargetDX*>( pRenderTarget );

		m_pD3DDevice->SetRenderTarget( 0, pRenderTargetDX->m_pRenderBuffer );
		m_pD3DDevice->SetDepthStencilSurface( pRenderTargetDX->m_pZBuffer );

		//m_pRenderTarget = pRenderTarget;
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX11::copyRect( KsRenderTarget* pSrcTarget, const KsRect* pSrcRect, KsRenderTarget* pDstTarget, const KsRect* pDstRect )
{
#if 0
	HRESULT			hr;
	D3DLOCKED_RECT	lockRect;
	D3DLOCKED_RECT	srcRect;
	D3DLOCKED_RECT	dstRect;
	KsInt32		y;
	KsChar*			p1;
	KsChar*			p2;
	
	IDirect3DSurface9*	pSrcSurface = r_cast<KsRenderTargetDX*>(pSrcTarget)->m_pRenderBuffer;
	IDirect3DSurface9*	pDstSurface = r_cast<KsRenderTargetDX*>(pDstTarget)->m_pRenderBuffer;

	hr = pDstSurface->LockRect( &dstRect, NULL, D3DLOCK_NOSYSLOCK );
	hr = pSrcSurface->LockRect( &srcRect, NULL, D3DLOCK_READONLY  );
	

	pSrcSurface->UnlockRect();
	pDstSurface->UnlockRect();

#endif

	m_pD3DDevice->StretchRect(	r_cast<KsRenderTargetDX*>(pSrcTarget)->m_pRenderBuffer,  
								r_cast<const RECT*>(pSrcRect),
								r_cast<KsRenderTargetDX*>(pDstTarget)->m_pRenderBuffer,  
								r_cast<const RECT*>(pDstRect),
								D3DTEXF_LINEAR
							);
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
D3DFORMAT KsRenderSystemDX11::getD3DFormat( ksPIXEL_FORMAT format )
{
	switch( format )
	{
		case ksPIXEL_X1R5G5B5:		return D3DFMT_X1R5G5B5;
		case ksPIXEL_A1R5G5B5:		return D3DFMT_A1R5G5B5;
		case ksPIXEL_A4R4G4B4:		return D3DFMT_A4R4G4B4;
		case ksPIXEL_R5G6B5:		return D3DFMT_R5G6B5;
		case ksPIXEL_X8R8G8B8:		return D3DFMT_X8R8G8B8;
		case ksPIXEL_A8R8G8B8:		return D3DFMT_A8R8G8B8;
		case ksPIXEL_BACKBUFFER:	return m_present.BackBufferFormat;
		default: break;
	}

	return m_present.BackBufferFormat;
}

/************************************************************************************************/
/*
 * レンダーステートをセットする
 * @param		state				ステートの種類
 * @param		value				ステートに対応する値
 */
/************************************************************************************************/
void KsRenderSystemDX11::setRenderState( ksRENDER_STATE_TYPE state, KsUInt32 value )
{
	switch( state )
	{
		case ksRENDER_STATE_ZTEST_ENABLE:
		{
			/* ZTEST */
			m_pD3DDevice->SetRenderState( D3DRS_ZENABLE, static_cast<DWORD>(value) );
			break;
		}
		case ksRENDER_STATE_ZWRITE_ENABLE:
		{
			/* ZWRITE */
			m_pD3DDevice->SetRenderState( D3DRS_ZWRITEENABLE, static_cast<DWORD>(value) );
			break;
		}
		case ksRENDER_STATE_FOG_ENABLE:
		{
			/* フォグのON, OFF */
			m_pD3DDevice->SetRenderState( D3DRS_FOGENABLE, static_cast<DWORD>(value) );
			break;
		}
		case ksRENDER_STATE_SRC_BLEND:
		{
			/* SRCブレンドモード設定 */
			m_renderState.m_srcBlend = static_cast<ksBLEND_MODE>(value);
			setSrcBlendFunc( m_renderState.m_srcBlend );
			break;
		}
		case ksRENDER_STATE_DST_BLEND:
		{
			/* DSTブレンドモード設定 */
			m_renderState.m_dstBlend = static_cast<ksBLEND_MODE>(value);
			setDstBlendFunc( m_renderState.m_dstBlend );
			break;
		}
		case ksRENDER_STATE_ALPHA_BLEND:
		{
			/* アルファブレンドをセット */
			m_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, static_cast<DWORD>(value) );
			break;
		}
		case ksRENDER_STATE_ALPHA_FUNC:
		{
			/* アルファFUNC */
			break;
		}
		case ksRENDER_STATE_ALPHA_REF:
		{
			/* アルファの基準値 */
			m_pD3DDevice->SetRenderState( D3DRS_ALPHAREF, static_cast<DWORD>(value) );
			break;
		}
		case ksRENDER_STATE_ALPHA_MASK:
		{
			/* アルファのマスク値 */
			//m_pD3DDevice->SetRenderState( D3DRS_ALPHAREF, static_cast<DWORD>(value) );
			break;
		}
		case ksRENDER_STATE_ALPAHTEST_ENABLE:
		{
			/* アルファテスト */
			m_pD3DDevice->SetRenderState( D3DRS_ALPHATESTENABLE, static_cast<DWORD>(value) );
			break;
		}
		case ksRENDER_STATE_LIGHTING:
		{
			/* ライト */
			m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, static_cast<DWORD>(value) );
			break;
		}
		case ksRENDER_STATE_CULL:
		{
			/* カリング設定 */
			setCullMode( static_cast<ksCULL_MODE>(value) );
			break;
		}
		case ksRENDER_STATE_SHADE:
		{
			/* シェーディングモード */
			setShadeMode( static_cast<ksSHADE_MODE>(value) );
			break;
		}
		case ksRENDER_STATE_STENCIL_ENABLE:
		{
			/* ステンシル(ON,OFF) */
			m_pD3DDevice->SetRenderState( D3DRS_STENCILENABLE, static_cast<DWORD>(value) );
			break;
		}
		case ksRENDER_STATE_STENCIL_FAIL:
		{
			/* ステンシルテスト失敗時のオペレーション */
			setStencilFail( static_cast<ksSTENCIL_OP_MODE>(value) );
			break;
		}
		case ksRENDER_STATE_STENCIL_ZFAIL:
		{
			/* ステンシルテストかつZテストに失敗時のオペレーション */
			setStencilZFail( static_cast<ksSTENCIL_OP_MODE>(value) );
			break;
		}
		case ksRENDER_STATE_STENCIL_PASS:
		{
			/* ステンシルテストかつZテストの成功時のオペレーション */
			setStencilPass( static_cast<ksSTENCIL_OP_MODE>(value) );
			break;
		}
		case ksRENDER_STATE_STENCIL_FUNC:
		{
			/* ステンシルファンクション */
			setStencilFunc( static_cast<ksSTENCIL_FUNC_MODE>(value) );
			break;
		}
		case ksRENDER_STATE_STENCIL_REF:
		{
			/* ステンシルの基準値 */
			m_pD3DDevice->SetRenderState( D3DRS_STENCILREF, static_cast<DWORD>(value) );
			break;
		}
		case ksRENDER_STATE_STENCIL_MASK:
		{
			/* ステンシルのマスク値 */
			m_pD3DDevice->SetRenderState( D3DRS_STENCILMASK, static_cast<DWORD>(value) );
			break;
		}
		case ksRENDER_STATE_STENCIL_WRITE_MASK:
		{
			m_pD3DDevice->SetRenderState( D3DRS_STENCILWRITEMASK, static_cast<DWORD>(value) );
			break;
		}
		case ksRENDER_STATE_COLOR_TEST_ENABLE:
		{
			/* カラーテスト(ON,OFF) */
			break;
		}
		case ksRENDER_STATE_COLOR_FUNC:
		{
			/* カラー関数 */
			break;
		}
		case ksRENDER_STATE_COLOR_REF:
		{
			/* カラー基準値 */
			break;
		}
		case ksRENDER_STATE_COLOR_MASK:
		{
			/* カラーマスク値 */
			break;
		}
		case ksRENDER_STATE_PIXEL_MASK:
		{
			/* ピクセルマスク */
			break;
		}
		case ksRENDER_STATE_LOGICAL_OP_ENABLE:
		{
			/* ロジカルオペレーション(ON,OFF) */
			break;
		}
		case ksRENDER_STATE_LOGICAL_OP_BLEND:
		{
			/* ロジカルオペレーションモード */
			break;
		}
		default:
		{
			break;
		}
	}
}

/************************************************************************************************/
/*
 * サンプラーステートをセットする
 * @param		sampler				サンプラー番号
 * @param		state				ステートの種類
 * @param		value				ステートに対応する値
 */
/************************************************************************************************/
void KsRenderSystemDX11::setSamplerState( KsUInt32 sampler, ksSAMPLER_STATE_TYPE state, KsUInt32 value )
{
	switch( state )
	{
		case ksSAMP_ADDRESSU:
		{
			break;
		}
		case ksSAMP_ADDRESSV:
		{
			break;
		}
		case ksSAMP_ADDRESSW:
		{
			break;
		}
		case ksSAMP_BORDERCOLOR:
		{
			break;
		}
		case ksSAMP_MAGFILTER:
		{
			m_pD3DDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, value );
			break;
		}
		case ksSAMP_MINFILTER:
		{
			m_pD3DDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, value );
			break;
		}
		case ksSAMP_MIPFILTER:
		{
			m_pD3DDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, value );
			break;
		}
		case ksSAMP_MIPMAPLODBIAS:
		{
			break;
		}
		case ksSAMP_MAXMIPLEVEL:
		{
			break;
		}
		case ksSAMP_MAXANISOTROPY:
		{
			break;
		}
		case ksSAMP_SRGBTEXTURE:
		{
			break;
		}
		case ksSAMP_ELEMENTINDEX:
		{
			break;
		}
		case ksSAMP_DMAPOFFSET: 
		{
			break;
		}
		default:
		{
			break;
		}
	}
}

/************************************************************************************************/
/*
 * 基本設定で2Dモードを初期化する
 */
/************************************************************************************************/
void KsRenderSystemDX11::auto2DMode()
{
	m_pD3DDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
	m_pD3DDevice->SetRenderState( D3DRS_SPECULARENABLE, TRUE );
	m_pD3DDevice->SetRenderState( D3DRS_COLORVERTEX, FALSE );
	m_pD3DDevice->SetRenderState( D3DRS_AMBIENT, D3DCOLOR_COLORVALUE( 0.2f, 0.2f, 0.2f, 1.0f ) );

	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );

	//m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	setRenderState( ksRENDER_STATE_ALPHA_BLEND, ksTRUE );
	setRenderState( ksRENDER_STATE_ZTEST_ENABLE, ksFALSE );

	D3DLIGHT9 light;
	KsZeroMemory( &light, sizeof(light) );
	light.Type = D3DLIGHT_DIRECTIONAL;

	D3DXVECTOR3 vecDir;
	//vecDir = D3DXVECTOR3(0.5f, 2.0f, -5.5f);
	vecDir = D3DXVECTOR3(0.0f, -2.0f, -4.0f);
	D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );

	// set directional light diffuse color
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Diffuse.a = 1.0f;
	light.Specular.r = 1.0f;
	light.Specular.g = 1.0f;
	light.Specular.b = 1.0f;
	light.Specular.a = 1.0f;

	m_pD3DDevice->SetLight( 0, &light );
	m_pD3DDevice->LightEnable( 0, TRUE );

	D3DXMATRIX matView;
	D3DXVECTOR3 pos(0.0f, 0.8f, 8.0f);
	D3DXVECTOR3 pnt(0.0f, 0.8f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	//D3DXMatrixLookAtLH(&matView, &pos, &pnt, &up);
	D3DXMatrixLookAtRH(&matView, &pos, &pnt, &up);
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &matView); 

	D3DXMATRIX mProjection;
	//D3DXMatrixPerspectiveFovLH( &mProjection, D3DXToRadian( 45.0f ), 640.0f / 480.0f, 0.1f, 500.0f );
	D3DXMatrixPerspectiveFovRH( &mProjection, D3DXToRadian( 45.0f ), 640.0f / 480.0f, 0.1f, 500.0f );
	m_pD3DDevice->SetTransform( D3DTS_PROJECTION, &mProjection );
}

/************************************************************************************************/
/*
 * 基本設定で3Dモードを初期化する
 */
/************************************************************************************************/
void KsRenderSystemDX11::auto3DMode()
{
	m_pD3DDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
	m_pD3DDevice->SetRenderState( D3DRS_SPECULARENABLE, TRUE );
	m_pD3DDevice->SetRenderState( D3DRS_COLORVERTEX, FALSE );
	m_pD3DDevice->SetRenderState( D3DRS_AMBIENT, D3DCOLOR_COLORVALUE( 0.2f, 0.2f, 0.2f, 1.0f ) );
	m_pD3DDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
	m_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );

	//m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP );
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP );
	//m_pD3DDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER );
	//m_pD3DDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER );

	D3DLIGHT9 light;
	KsZeroMemory( &light, sizeof(light) );
	light.Type = D3DLIGHT_DIRECTIONAL;

	D3DXVECTOR3 vecDir;
	//vecDir = D3DXVECTOR3(0.5f, 2.0f, -5.5f);
	vecDir = D3DXVECTOR3(0.0f, -2.0f, -4.0f);
	D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );

	// set directional light diffuse color
	light.Diffuse.r = 0.3f;
	light.Diffuse.g = 0.3f;
	light.Diffuse.b = 0.3f;
	light.Diffuse.a = 1.0f;
	light.Specular.r = 0.8f;
	light.Specular.g = 0.8f;
	light.Specular.b = 0.8f;
	light.Specular.a = 1.0f;
	light.Ambient.r = 0.6f;
	light.Ambient.g = 0.6f;
	light.Ambient.b = 0.6f;
	light.Ambient.a = 1.0f;

	m_pD3DDevice->SetLight( 0, &light );
	m_pD3DDevice->LightEnable( 0, TRUE );


	D3DXMATRIX matView;
	//D3DXVECTOR3 pos(0.0f, 0.8f, 15.0f);
	//D3DXVECTOR3 pnt(0.0f, 0.8f, 0.0f);
	
	//D3DXVECTOR3 pos(0.0f, 0.8f, 3.0f);
	//D3DXVECTOR3 pnt(0.0f, 0.8f, 0.0f);
	//D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	D3DXVECTOR3 pos( 2.0f, 2.0f, -5.0f );
	D3DXVECTOR3 pnt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	//D3DXMatrixLookAtLH(&matView, &pos, &pnt, &up);
	D3DXMatrixLookAtRH(&matView, &pos, &pnt, &up);
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &matView); 

	D3DXMATRIX mProjection;
	//D3DXMatrixPerspectiveFovLH( &mProjection, D3DXToRadian( 45.0f ), 640.0f / 480.0f, 0.1f, 500.0f );
	D3DXMatrixPerspectiveFovRH( &mProjection, D3DXToRadian( 45.0f ), 640.0f / 480.0f, 0.1f, 500.0f );
	m_pD3DDevice->SetTransform( D3DTS_PROJECTION, &mProjection );




	D3DXMatrixLookAtLH(&matView, &pos, &pnt, &up);
    D3DXMatrixPerspectiveFovLH(&mProjection, D3DXToRadian(60.0f), 1.0f, 0.0f, 1.0f);

    m_pD3DDevice->SetTransform( D3DTS_VIEW, &matView );
    m_pD3DDevice->SetTransform( D3DTS_PROJECTION, &mProjection );

}

#endif


//! レンダリングターゲットを作成する
/*!
スワップチェインはバックバッファを持っていますが、レンダリングターゲットは持っていません。
バックバッファをレンダリングターゲットとして使用する場合、別途ターゲットを作成する必要があります。
この関数では作成済みのスワップチェインからバックバッファを取得し、それを利用してターゲットを作成しています。
*/
KsRenderTarget* KsRenderSystemDX11::createRenderTargetView()
{
	// レンダリングターゲットを作成する
	ID3D11Texture2D*	pBackBuffer;
	HRESULT				hr = m_pSwapChain->GetBuffer( 0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer) );

	if( ksFAILED( hr ) ) 
	{
		return NULL;
	}

	ID3D11RenderTargetView*	pTargetView;

	hr = m_pDevice->CreateRenderTargetView( pBackBuffer, NULL, &pTargetView );
	    
	ksRELEASE( pBackBuffer );
		
	if( ksFAILED( hr ) )
	{
		return NULL;
	}

	return ksNew KsRenderTargetDX11( pTargetView );
}


//! レンダリングターゲットを作成する
/*!
スワップチェインはバックバッファを持っていますが、レンダリングターゲットは持っていません。
バックバッファをレンダリングターゲットとして使用する場合、別途ターゲットを作成する必要があります。
この関数では作成済みのスワップチェインからバックバッファを取得し、それを利用してターゲットを作成しています。
*/
KsRenderTarget* KsRenderSystemDX11::createRenderTextureView( KsUInt32 width, KsUInt32 height, KsUInt32 format )
{
	// レンダリングテクスチャを作成する
	ID3D11Texture2D*				pRenderTargetTexture = NULL;
	ID3D11RenderTargetView*			pRenderTargetView    = NULL;
	ID3D11ShaderResourceView*		pShaderResourceView  = NULL;
	D3D11_TEXTURE2D_DESC			textureDesc;
	D3D11_RENDER_TARGET_VIEW_DESC	renderTargetViewDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;

	// ゼロクリアーする
	KsZeroMemory( &textureDesc, sizeof(textureDesc) );

	textureDesc.Width              = width;//(KsUInt32)m_pWindow->getWidth();		// 解像度の幅を表す値です。
	textureDesc.Height             = height;//(KsUInt32)m_pWindow->getWidth();		// 解像度の幅を表す値です。
	textureDesc.MipLevels          = 1;
	textureDesc.ArraySize          = 1;
	textureDesc.Format             = (DXGI_FORMAT)format;// DXGI_FORMAT_R8G8B8A8_TYPELESS;
	textureDesc.SampleDesc.Count   = 1;
	textureDesc.Usage              = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags          = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags     = 0;
	textureDesc.MiscFlags          = 0;

	HRESULT		hr = m_pDevice->CreateTexture2D( &textureDesc, NULL, &pRenderTargetTexture );

	if( ksFAILED( hr ) )
	{
		return NULL;
	}

	// レンダリングターゲットを作成する
	renderTargetViewDesc.Format             = textureDesc.Format;
	renderTargetViewDesc.ViewDimension      = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	hr = m_pDevice->CreateRenderTargetView( pRenderTargetTexture, &renderTargetViewDesc, &pRenderTargetView );

	if( ksFAILED( hr ) )
	{
		return NULL;
	}

	// ShaderResourceViewを作成する
	// これを作成しておかないとテクスチャリソースとして使用できない
	shaderResourceViewDesc.Format                    = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels       = 1;


	hr = m_pDevice->CreateShaderResourceView( pRenderTargetTexture, &shaderResourceViewDesc, &pShaderResourceView );
	
	if( ksFAILED( hr ) )
	{
		return NULL;
	}

	KsTextureDX11*	pTexture = ksNew KsTextureDX11( pRenderTargetTexture, pShaderResourceView );
	KsRenderTarget*	pTarget  = ksNew KsRenderTargetTextureDX11( pTexture, pRenderTargetView );

	return pTarget;
}

KsRenderTarget* KsRenderSystemDX11::createDepthStencilView( KsUInt32 width, KsUInt32 height, KsUInt32 format, KsUInt32 viewFormat, KsUInt32 resFormat )
{
	ID3D11Texture2D*	pDepthStencilTexture;

	// 深度バッファテクスチャを作成する
	D3D11_TEXTURE2D_DESC	depthDesc;

	// ゼロクリアーする
	ZeroMemory( &depthDesc, sizeof(depthDesc) );

	depthDesc.Width              = width;
	depthDesc.Height             = height;
	depthDesc.MipLevels          = 1;
	depthDesc.ArraySize          = 1;
	depthDesc.Format             = (DXGI_FORMAT)format;
//	depthDesc.Format             = DXGI_FORMAT_R32_TYPELESS;
	depthDesc.SampleDesc.Count   = 1;
	depthDesc.SampleDesc.Quality = 0;
	depthDesc.Usage              = D3D11_USAGE_DEFAULT;
	depthDesc.BindFlags          = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	depthDesc.CPUAccessFlags     = 0;
	depthDesc.MiscFlags          = 0;

	HRESULT		hr = m_pDevice->CreateTexture2D( &depthDesc, NULL, &pDepthStencilTexture );

	if( ksFAILED( hr ) )
	{
		return NULL;
	}

	ID3D11DepthStencilView*		pDepthStencilView;

	// 深度バッファターゲットを作成する
	D3D11_DEPTH_STENCIL_VIEW_DESC	dsvDesc;

	// ゼロクリアーする
	ZeroMemory( &dsvDesc, sizeof(dsvDesc) );

	//dsvDesc.Format             = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.Format             = (DXGI_FORMAT)viewFormat;
	//dsvDesc.ViewDimension    = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	dsvDesc.ViewDimension      = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	hr = m_pDevice->CreateDepthStencilView( pDepthStencilTexture, &dsvDesc, &pDepthStencilView );
	
	if( ksFAILED( hr ) )
	{
		return NULL;
	}

	ID3D11ShaderResourceView*		pShaderResourceView  = NULL;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;

	shaderResourceViewDesc.Format                    = (DXGI_FORMAT)resFormat;
	//shaderResourceViewDesc.Format                    = DXGI_FORMAT_R32_FLOAT;
	shaderResourceViewDesc.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels       = 1;

	hr = m_pDevice->CreateShaderResourceView( pDepthStencilTexture, &shaderResourceViewDesc, &pShaderResourceView );

	if( ksFAILED( hr ) )
	{
		return NULL;
	}

	KsTextureDX11*	pTexture = ksNew KsTextureDX11( pDepthStencilTexture, pShaderResourceView );

	return ksNew KsDepthStencilDX11( pTexture, pDepthStencilView );
}

//! 深度バッファを作成する
/*!
深度バッファはスワップチェインには含まれていないため、バッファとなるテクスチャから作成します。
テクスチャ作成時に深度バッファとして使用する旨を通知する必要があります。
また、レンダリングターゲットと同様にバッファと別にターゲットを作成する必要があります。
*/
KsRenderTarget* KsRenderSystemDX11::createDepthStencilView()
{
	ID3D11Texture2D*	pDepthStencilTexture;

	// 深度バッファテクスチャを作成する
	D3D11_TEXTURE2D_DESC	depthDesc;

	// ゼロクリアーする
	ZeroMemory( &depthDesc, sizeof(depthDesc) );

	depthDesc.Width              = (KsUInt32)m_pWindow->getWidth();		// 解像度の幅を表す値です。
	depthDesc.Height             = (KsUInt32)m_pWindow->getHeight();	// 解像度の高さを表す値です。
	depthDesc.MipLevels          = 1;
	depthDesc.ArraySize          = 1;
	depthDesc.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
	//depthDesc.Format             = DXGI_FORMAT_R32_TYPELESS;
	depthDesc.SampleDesc.Count   = 1;
	depthDesc.SampleDesc.Quality = 0;
	depthDesc.Usage              = D3D11_USAGE_DEFAULT;
	depthDesc.BindFlags          = D3D11_BIND_DEPTH_STENCIL;
	//depthDesc.BindFlags          = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	depthDesc.CPUAccessFlags     = 0;
	depthDesc.MiscFlags          = 0;

	HRESULT		hr = m_pDevice->CreateTexture2D( &depthDesc, NULL, &pDepthStencilTexture );

	if( ksFAILED( hr ) )
	{
		return NULL;
	}

	ID3D11DepthStencilView*		pDepthStencilView;

	// 深度バッファターゲットを作成する
	D3D11_DEPTH_STENCIL_VIEW_DESC	dsvDesc;

	// ゼロクリアーする
	ZeroMemory( &dsvDesc, sizeof(dsvDesc) );

	dsvDesc.Format           = depthDesc.Format;
	//dsvDesc.Format             = DXGI_FORMAT_D32_FLOAT;
	//dsvDesc.ViewDimension    = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	dsvDesc.ViewDimension      = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	hr = m_pDevice->CreateDepthStencilView( pDepthStencilTexture, &dsvDesc, &pDepthStencilView );
	
	if( ksFAILED( hr ) )
	{
		return NULL;
	}

	KsTextureDX11*	pTexture = ksNew KsTextureDX11( pDepthStencilTexture, NULL );

	return ksNew KsDepthStencilDX11( pTexture, pDepthStencilView );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsUnorderedAccessView* KsRenderSystemDX11::createUnorderedAccessView( KsUInt32 elementSize, KsUInt32 numElements, KsUInt32 format, KsUInt32 flags )
{
	return ksNew KsUnorderedAccessViewDX11( this, elementSize, numElements, format, flags );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsStructuredBuffer* KsRenderSystemDX11::createStructuredBuffer( KsUInt32 elementSize, KsUInt32 numElements, KsUInt32 format, KsUInt32 flags )
{
	return ksNew KsStructuredBufferDX11( this, elementSize, numElements, format, flags );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsRasterizerState* KsRenderSystemDX11::createRasterizerState( const KS_RASTERIZER_DESC* pRasterizerState )
{
	return ksNew KsRasterizerStateDX11( this, pRasterizerState );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsSamplerState* KsRenderSystemDX11::createSamplerState( const KS_SAMPLER_DESC* pSamplerStateDesc )
{
	return ksNew KsSamplerStateDX11( this, pSamplerStateDesc );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsBlendState* KsRenderSystemDX11::createBlendState( const KS_BLEND_DESC* pBlendStateDesc )
{
	return ksNew KsBlendStateDX11( this, pBlendStateDesc );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsDepthStencilState* KsRenderSystemDX11::createDepthStencilState( const KS_DEPTH_STENCIL_DESC* pDepthStencilDesc )
{
	return ksNew KsDepthStencilStateDX11( this, pDepthStencilDesc );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsRenderContext* KsRenderSystemDX11::createDeferredContext()
{
	KsRenderContextDX11*	pRenderContext = ksNew KsRenderContextDX11();

	m_pDevice->CreateDeferredContext( 0, &pRenderContext->m_pDeviceContext );
	
	return pRenderContext;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsCommandList* KsRenderSystemDX11::createCommandList()
{
	KsCommandListDX11*	pCommandList = ksNew KsCommandListDX11();
	
	return pCommandList;
}


#if 0
//--------------------------------------------------------------------------------------
// Blend states
//--------------------------------------------------------------------------------------

KsBlendState* KsRenderSystem::Opaque() const
{
	return ksNew KsBlendState( );
}




    SpriteSortMode mSortMode;
    ComPtr<ID3D11BlendState> mBlendState;
    ComPtr<ID3D11SamplerState> mSamplerState;
    ComPtr<ID3D11DepthStencilState> mDepthStencilState;
    ComPtr<ID3D11RasterizerState> mRasterizerState;

    auto blendState        = mBlendState        ? mBlendState.Get()        : mDeviceResources->stateObjects.AlphaBlend();
    auto depthStencilState = mDepthStencilState ? mDepthStencilState.Get() : mDeviceResources->stateObjects.DepthNone();
    auto rasterizerState   = mRasterizerState   ? mRasterizerState.Get()   : mDeviceResources->stateObjects.CullCounterClockwise();
    auto samplerState      = mSamplerState      ? mSamplerState.Get()      : mDeviceResources->stateObjects.LinearClamp();



	
//--------------------------------------------------------------------------------------
// Blend states
//--------------------------------------------------------------------------------------

ID3D11BlendState* CommonStates::Opaque() const
{
    return DemandCreate(pImpl->opaque, pImpl->mutex, [&](ID3D11BlendState** pResult)
    {
        return pImpl->CreateBlendState(D3D11_BLEND_ONE, D3D11_BLEND_ZERO, pResult);
    });
}


ID3D11BlendState* CommonStates::AlphaBlend() const
{
    return DemandCreate(pImpl->alphaBlend, pImpl->mutex, [&](ID3D11BlendState** pResult)
    {
        return pImpl->CreateBlendState(D3D11_BLEND_ONE, D3D11_BLEND_INV_SRC_ALPHA, pResult);
    });
}


ID3D11BlendState* CommonStates::Additive() const
{
    return DemandCreate(pImpl->additive, pImpl->mutex, [&](ID3D11BlendState** pResult)
    {
        return pImpl->CreateBlendState(D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_ONE, pResult);
    });
}


ID3D11BlendState* CommonStates::NonPremultiplied() const
{
    return DemandCreate(pImpl->nonPremultiplied, pImpl->mutex, [&](ID3D11BlendState** pResult)
    {
        return pImpl->CreateBlendState(D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA, pResult);
    });
}


//--------------------------------------------------------------------------------------
// Depth stencil states
//--------------------------------------------------------------------------------------

ID3D11DepthStencilState* CommonStates::DepthNone() const
{
    return DemandCreate(pImpl->depthNone, pImpl->mutex, [&](ID3D11DepthStencilState** pResult)
    {
        return pImpl->CreateDepthStencilState(false, false, pResult);
    });
}


ID3D11DepthStencilState* CommonStates::DepthDefault() const
{
    return DemandCreate(pImpl->depthDefault, pImpl->mutex, [&](ID3D11DepthStencilState** pResult)
    {
        return pImpl->CreateDepthStencilState(true, true, pResult);
    });
}


ID3D11DepthStencilState* CommonStates::DepthRead() const
{
    return DemandCreate(pImpl->depthRead, pImpl->mutex, [&](ID3D11DepthStencilState** pResult)
    {
        return pImpl->CreateDepthStencilState(true, false, pResult);
    });
}


//--------------------------------------------------------------------------------------
// Rasterizer states
//--------------------------------------------------------------------------------------

ID3D11RasterizerState* CommonStates::CullNone() const
{
    return DemandCreate(pImpl->cullNone, pImpl->mutex, [&](ID3D11RasterizerState** pResult)
    {
        return pImpl->CreateRasterizerState(D3D11_CULL_NONE, D3D11_FILL_SOLID, pResult);
    });
}


ID3D11RasterizerState* CommonStates::CullClockwise() const
{
    return DemandCreate(pImpl->cullClockwise, pImpl->mutex, [&](ID3D11RasterizerState** pResult)
    {
        return pImpl->CreateRasterizerState(D3D11_CULL_FRONT, D3D11_FILL_SOLID, pResult);
    });
}


ID3D11RasterizerState* CommonStates::CullCounterClockwise() const
{
    return DemandCreate(pImpl->cullCounterClockwise, pImpl->mutex, [&](ID3D11RasterizerState** pResult)
    {
        return pImpl->CreateRasterizerState(D3D11_CULL_BACK, D3D11_FILL_SOLID, pResult);
    });
}


ID3D11RasterizerState* CommonStates::Wireframe() const
{
    return DemandCreate(pImpl->wireframe, pImpl->mutex, [&](ID3D11RasterizerState** pResult)
    {
        return pImpl->CreateRasterizerState(D3D11_CULL_BACK, D3D11_FILL_WIREFRAME, pResult);
    });
}


//--------------------------------------------------------------------------------------
// Sampler states
//--------------------------------------------------------------------------------------

ID3D11SamplerState* CommonStates::PointWrap() const
{
    return DemandCreate(pImpl->pointWrap, pImpl->mutex, [&](ID3D11SamplerState** pResult)
    {
        return pImpl->CreateSamplerState(D3D11_FILTER_MIN_MAG_MIP_POINT, D3D11_TEXTURE_ADDRESS_WRAP, pResult);
    });
}


ID3D11SamplerState* CommonStates::PointClamp() const
{
    return DemandCreate(pImpl->pointClamp, pImpl->mutex, [&](ID3D11SamplerState** pResult)
    {
        return pImpl->CreateSamplerState(D3D11_FILTER_MIN_MAG_MIP_POINT, D3D11_TEXTURE_ADDRESS_CLAMP, pResult);
    });
}


ID3D11SamplerState* CommonStates::LinearWrap() const
{
    return DemandCreate(pImpl->linearWrap, pImpl->mutex, [&](ID3D11SamplerState** pResult)
    {
        return pImpl->CreateSamplerState(D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP, pResult);
    });
}


ID3D11SamplerState* CommonStates::LinearClamp() const
{
    return DemandCreate(pImpl->linearClamp, pImpl->mutex, [&](ID3D11SamplerState** pResult)
    {
        return pImpl->CreateSamplerState(D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_CLAMP, pResult);
    });
}


ID3D11SamplerState* CommonStates::AnisotropicWrap() const
{
    return DemandCreate(pImpl->anisotropicWrap, pImpl->mutex, [&](ID3D11SamplerState** pResult)
    {
        return pImpl->CreateSamplerState(D3D11_FILTER_ANISOTROPIC, D3D11_TEXTURE_ADDRESS_WRAP, pResult);
    });
}


ID3D11SamplerState* CommonStates::AnisotropicClamp() const
{
    return DemandCreate(pImpl->anisotropicClamp, pImpl->mutex, [&](ID3D11SamplerState** pResult)
    {
        return pImpl->CreateSamplerState(D3D11_FILTER_ANISOTROPIC, D3D11_TEXTURE_ADDRESS_CLAMP, pResult);
    });
}

#endif


#if 0
    class CommonStates
    {
    public:
        explicit CommonStates(_In_ ID3D11Device* device);
        CommonStates(CommonStates&& moveFrom);
        CommonStates& operator= (CommonStates&& moveFrom);
        virtual ~CommonStates();

        // Blend states.
        ID3D11BlendState* Opaque() const;
        ID3D11BlendState* AlphaBlend() const;
        ID3D11BlendState* Additive() const;
        ID3D11BlendState* NonPremultiplied() const;

        // Depth stencil states.
        ID3D11DepthStencilState* DepthNone() const;
        ID3D11DepthStencilState* DepthDefault() const;
        ID3D11DepthStencilState* DepthRead() const;

        // Rasterizer states.
        ID3D11RasterizerState* CullNone() const;
        ID3D11RasterizerState* CullClockwise() const;
        ID3D11RasterizerState* CullCounterClockwise() const;
        ID3D11RasterizerState* Wireframe() const;

        // Sampler states.
        ID3D11SamplerState* PointWrap() const;
        ID3D11SamplerState* PointClamp() const;
        ID3D11SamplerState* LinearWrap() const;
        ID3D11SamplerState* LinearClamp() const;
        ID3D11SamplerState* AnisotropicWrap() const;
        ID3D11SamplerState* AnisotropicClamp() const;

    private:
        // Private implementation.
        class Impl;

        std::shared_ptr<Impl> pImpl;

        // Prevent copying.
        CommonStates(CommonStates const&);
        CommonStates& operator= (CommonStates const&);
    };
#endif