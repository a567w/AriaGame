/************************************************************************************************/
/** 
 * @file		KsDeferredRender.cpp
 * @brief		ディファードレンダリング
 * @author		Tsukasa Kato
 * @date		2006/07/02
 * @since		2006/07/02
 * @version		0.1
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << ワーニング抑制 >>                                          */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                 << ライブラリリンク >>                                        */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "Aria/KsGamePreCompile.h"
#include "Aria/render/deferred/KsDeferredRender.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsDeferredRender::KsDeferredRender( KsRenderSystem* pRenderSystem, KsUInt32 width, KsUInt32 height, KsUInt32 MSAA )
	: m_pRenderSystem( pRenderSystem )
	, m_pRenderContext( 0 )
	, m_pBackBuffer( 0 )
	, m_pDepthStencil( 0 )
	, m_isMRT( ksFALSE )
	, m_pParameter( 0 )
	, m_dispatchWidth( 0 )
	, m_dispatchHeight( 0 )
	, m_totalTime( 0.0f )
	, m_numRenderThread( 0 )
	, m_pDeferredEffect( 0 )
	, m_pContourEffect( 0 )
	, m_pLighting( 0 )
{
	//----------------------------------------------------------------------
	// パラメータを初期化する。
	//----------------------------------------------------------------------
	KsZeroMemory( m_pGBuffer, sizeof(m_pGBuffer) );
	KsZeroMemory( m_pGBufferTexture, sizeof(m_pGBufferTexture) );
	KsZeroMemory( m_pRenderThread, sizeof(m_pRenderThread) );

	//----------------------------------------------------------------------
	// 遅延コンテキストを作成する
	//----------------------------------------------------------------------
	m_pRenderThread[ 0 ] = ksNew KsRenderThread( pRenderSystem, this );
	m_pRenderThread[ 0 ]->run();
	++m_numRenderThread;

	//----------------------------------------------------------------------
	// ディファードレンダリング用のテクスチャを作成する
	//----------------------------------------------------------------------

	// Normal Specular [ R, G, B, A]
	m_pGBuffer[ ksMRT_NORMAL     ] = pRenderSystem->createRenderTextureView( width, height,  KS_GI_FORMAT_R16G16B16A16_FLOAT );

	// Albedo [ R, G, B, A]
	m_pGBuffer[ ksMRT_ALBEDO     ] = pRenderSystem->createRenderTextureView( width, height, KS_GI_FORMAT_R8G8B8A8_UNORM );

	// Position [R, G]
	m_pGBuffer[ ksMRT_POSITION   ] = pRenderSystem->createRenderTextureView( width, height, KS_GI_FORMAT_R16G16_FLOAT );

	// ZBuffer
	m_pGBuffer[ ksMRT_ZBUFFER    ] = pRenderSystem->createDepthStencilView( width, height, KS_GI_FORMAT_R32_TYPELESS, KS_GI_FORMAT_D32_FLOAT, KS_GI_FORMAT_R32_FLOAT );

	// Light [ R, G, B, A] (deferred lighting accumulation buffer)
	m_pGBuffer[ ksMRT_ACCUMULATE ] = pRenderSystem->createRenderTextureView( width, height, KS_GI_FORMAT_R16G16B16A16_FLOAT );

	// テクスチャを覚えておく
	m_pGBufferTexture[ ksMRT_NORMAL     ] = ((KsRenderTargetTexture*)m_pGBuffer[ ksMRT_NORMAL     ])->getTexture();
	m_pGBufferTexture[ ksMRT_ALBEDO     ] = ((KsRenderTargetTexture*)m_pGBuffer[ ksMRT_ALBEDO     ])->getTexture();
	m_pGBufferTexture[ ksMRT_POSITION   ] = ((KsRenderTargetTexture*)m_pGBuffer[ ksMRT_POSITION   ])->getTexture();
	m_pGBufferTexture[ ksMRT_ZBUFFER    ] = ((KsRenderTargetTexture*)m_pGBuffer[ ksMRT_ZBUFFER    ])->getTexture();
	m_pGBufferTexture[ ksMRT_ACCUMULATE ] = ((KsRenderTargetTexture*)m_pGBuffer[ ksMRT_ACCUMULATE ])->getTexture();

	// テクスチャ名をセットしておく
	m_pGBufferTexture[ ksMRT_NORMAL     ]->setName( "G-Buffer0" );
	m_pGBufferTexture[ ksMRT_ALBEDO     ]->setName( "G-Buffer1" );
	m_pGBufferTexture[ ksMRT_POSITION   ]->setName( "G-Buffer2" );
	m_pGBufferTexture[ ksMRT_ZBUFFER    ]->setName( "Z-Buffer"  );
	m_pGBufferTexture[ ksMRT_ACCUMULATE ]->setName( "Accumulate" );

	//----------------------------------------------------------------------
	// ライト設定をする
	//----------------------------------------------------------------------

	// レンダーターゲットを取得しておく(イミディエイト コンテキスト)
	m_pRenderContext = pRenderSystem->getRenderContex();

	m_pBackBuffer   = m_pRenderContext->getRenderTarget();
	m_pDepthStencil = m_pRenderContext->getDepthStencil();

	// ライティング用セットアップ
	KsShaderManager*			pShaderManager         = KsShaderManagerDX11::getInstancePtr();
	KsHardwareBufferManager*	pHardwareBufferManager = KsHardwareBufferManagerDX11::getInstancePtr();
	KsInputLayoutManager*		pInputLayoutManager    = KsInputLayoutManagerDX11::getInstancePtr();

	// ライティング処理生成
	m_pLighting = ksNew KsDeferredLighting( pRenderSystem, width, height, MSAA );

	// Deferred エフェクト	
	m_pDeferredEffect = ksNew KsDeferredEffect();

	// カートゥーン輪郭線 エフェクト	
	m_pContourEffect =ksNew KsContourEffect();

	// コンスタントバッファ
	m_pParameter = new KsModelParameter();

	// ラスタライズステート
	{
		KS_RASTERIZER_DESC		desc = KsRasterizerState::DEFAULT;
		//desc.CullMode = KS_CULL_NONE;
		desc.CullMode = KS_CULL_BACK;
		m_pRasterizerState = pRenderSystem->createRasterizerState( &desc );
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

	// ビューポート設定
	setViewport( 0, 0, 1280, 720, 0.0f, 1.0f );

	//----------------------------------------------------------------------
	// シャドウマップ管理生成
	//----------------------------------------------------------------------
	KsUInt32		shadowLevels = 3;
	KsUInt32		shadowWidth  = 2048;
	KsUInt32		shadowHeight = 2048;
	m_pShadowManager = ksNew KsShadowManager( pRenderSystem, shadowWidth, shadowHeight, shadowLevels );

	//----------------------------------------------------------------------
	// カメラ生成
	//----------------------------------------------------------------------
	KsCameraManager*	pCameraManager = KsCameraManager::getInstancePtr();
	m_pCamera = ksNew KsFreeCamera();

	pCameraManager->addCamera( m_pCamera );
	pCameraManager->addCamera( ksNew KsPlayerCamera() );
	pCameraManager->setActiveCamera( m_pCamera );
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsDeferredRender::~KsDeferredRender()
{
	ksDELETE( m_pLighting );

	for( KsUInt32 i=0; i<ksARRAYSIZE(m_pGBuffer); i++ )
	{
		ksDELETE( m_pGBuffer[ i ] );
	}
}

/************************************************************************************************/
/*
 * ビューポート設定
 * @param		x		X座標
 * @param		y		X座標
 * @param		w		幅
 * @param		h		高さ
 * @param		near	nearクリップ値
 * @param		far		farクリップ値
 */
/************************************************************************************************/
void KsDeferredRender::setViewport( KsInt32 x, KsInt32 y, KsInt32 w, KsInt32 h, KsReal minZ, KsReal maxZ, KsRenderContext* pRenderContext )
{
	// ビューポート設定
	m_viewport.set( x, y, w, h, minZ, maxZ );

	if( pRenderContext )
	{
		pRenderContext->setViewports( &m_viewport );
	}
	else
	{
		m_pRenderContext->setViewports( &m_viewport );
	}
}

/************************************************************************************************/
/*
 * マルチレンダーターゲットをセットする
 */
/************************************************************************************************/
void KsDeferredRender::setRenderTarget_MRT( KsRenderContext* pRenderContext )
{
	// MRTセット
	pRenderContext->setRenderTargets( 3, m_pGBuffer, m_pGBuffer[ ksMRT_ZBUFFER ] );

	m_isMRT = ksTRUE;
}

/************************************************************************************************/
/*
 * レンダーターゲットをデフォルトに戻す
 */
/************************************************************************************************/
void KsDeferredRender::setRenderTarget_Default( KsRenderContext* pRenderContext )
{
	// レンダーターゲットを元に戻す
	pRenderContext->setRenderTarget( m_pBackBuffer, m_pDepthStencil );

	m_isMRT = ksFALSE;
}

/************************************************************************************************/
/*
 * シーンをクリアする
 */
/************************************************************************************************/
void KsDeferredRender::clearScene()
{
	// ターゲットをクリアーする
	if( m_isMRT )
	{
		m_pRenderContext->clearScenes( 3, (ksCLEAR_FLAG_COLOR | ksCLEAR_FLAG_DEPTH ), KsColor::BLACK, 1.0f, 0 );
	}
	else
	{
		m_pRenderContext->clearScene( (ksCLEAR_FLAG_COLOR | ksCLEAR_FLAG_DEPTH ), KsColor::BLUE, 1.0f, 0 );
	}
}

/************************************************************************************************/
/*
 * カラーをクリアする
 */
/************************************************************************************************/
void KsDeferredRender::clearColor()
{
	// ターゲットをクリアーする
	if( m_isMRT )
	{
		KsColor		clearColor( 0, 0, 0, 0 );

		m_pRenderContext->clearScene( ksCLEAR_FLAG_COLOR, clearColor, 1.0f, 0 );
	}
	else
	{
		m_pRenderContext->clearScene( ksCLEAR_FLAG_COLOR, KsColor::BLUE, 1.0f, 0 );
	}
}

/************************************************************************************************/
/*
 * 深度をクリアする
 */
/************************************************************************************************/
void KsDeferredRender::clearDepthStencil()
{
	// 深度ステンシルバッファをクリアーする
	m_pRenderContext->clearScene( ksCLEAR_FLAG_DEPTH | ksCLEAR_FLAG_STENCIL, KsColor::BLACK, 0.0f, 0 );
}

/************************************************************************************************/
/*
 * ライティングを初期化する
 */
/************************************************************************************************/
void KsDeferredRender::initializeLight()
{
}

/************************************************************************************************/
/*
 * シェーダーパラメータを更新する
 */
/************************************************************************************************/
void KsDeferredRender::updateShaderParameter()
{
	//KsReal			fNear       = 0.1f;
	//KsReal			fFar        = 1000.0f;

	// (1-z)で計算するのでこちら
	KsReal			fNear       = 1500.0f;
	KsReal			fFar        = 0.05f;
	KsMatrix4x4		worldMat    = KsMatrix4x4::IDENTITY;

	m_pCamera->update();

	m_pParameter->GBuffer.World         = worldMat;
	m_pParameter->GBuffer.Proj          = m_pCamera->getProjMatrix();
	m_pParameter->GBuffer.ViewProj      = m_pCamera->getViewProjMatrix();
	m_pParameter->GBuffer.WorldView     = worldMat * m_pCamera->getViewMatrix();
	m_pParameter->GBuffer.WorldViewProj = worldMat * m_pCamera->getViewProjMatrix();

	m_pParameter->GBuffer.CameraNearFar.set( fNear, fFar, 0.0f, 0.0f );
	m_pParameter->GBuffer.FramebufferDimensionsX = 1280;
	m_pParameter->GBuffer.FramebufferDimensionsY = 720;
	m_pParameter->GBuffer.FramebufferDimensionsZ = 0;
	m_pParameter->GBuffer.FramebufferDimensionsW = 0;

	m_pParameter->GBuffer.World.transpose();
	m_pParameter->GBuffer.Proj.transpose();
	m_pParameter->GBuffer.ViewProj.transpose();
	m_pParameter->GBuffer.WorldView.transpose();
	m_pParameter->GBuffer.WorldViewProj.transpose();

	//m_pRenderContext->updateConstantBuffers( m_pLighting->getLightingBuffer(), m_pParameter );

}

/************************************************************************************************/
/*
 * ライトを更新する( ライト情報をテクスチャに書き込む )
 */
/************************************************************************************************/
void KsDeferredRender::updateLight()
{
	m_pLighting->updateLight( 1.0f/60.0f, m_pCamera, m_pParameter );
}

/************************************************************************************************/
/*
 * GBufferを描画する
 */
/************************************************************************************************/
void KsDeferredRender::renderGBuffer()
{
	// 深度ステンシルバッファをクリアーする
	//m_pRenderContext->clearDepthStencil( m_pGBuffer[ ksMRT_ZBUFFER ], ksCLEAR_FLAG_DEPTH | ksCLEAR_FLAG_STENCIL, 0.0f, 0 );

	// 深度ステンシルステートをセットする
	m_pRenderContext->setDepthStencilState( m_pDepthState, 0 );
	
	// MRT をセットする
	m_pRenderContext->setRenderTargets( MRT_RENDER_COUNT, m_pGBuffer, m_pGBuffer[ ksMRT_ZBUFFER ] );

	m_pRenderContext->clearScenes( 3, (ksCLEAR_FLAG_COLOR | ksCLEAR_FLAG_DEPTH ), KsColor::BLACK, 0.0f, 0 );

	// ブレンドステート
	m_pRenderContext->setBlendState( m_pBlendState, 0, 0xFFFFFFFF );

	// ラスタライザーステート
	m_pRenderContext->setRasterizerState( m_pRasterizerState );

	// ビューポートをセットする
	m_pRenderContext->setViewports( &m_viewport );

	// モデルを描画する
	// Input Layout
	// constant buffer G-Buffer用( VS, PS両方セットする)
	// VS, PSをセットする
	for( KsUInt32 i=0; i<m_pActors.size(); i++ )
	{
		KsActor* pActor = m_pActors[ i ];
		pActor->update( 1.0f/60.0f );
		pActor->draw( m_pRenderContext );
	}

	for( KsUInt32 i=0; i<m_pModels.size(); i++ )
	{
		KsModel* pModel = m_pModels[ i ];
		pModel->update();
		pModel->draw( m_pRenderContext );
	}

	// レンダーターゲットをリセットする
	m_pRenderContext->setRenderTargets( 0, 0, 0 );
}

/************************************************************************************************/
/*
 * ライティングする
 */
/************************************************************************************************/
void KsDeferredRender::computeLighting()
{
	m_pLighting->computeLighting( MRT_RENDER_COUNT+1, &m_pGBufferTexture[ 0 ] );
}

/************************************************************************************************/
/*
 * シーンを描画する
 */
/************************************************************************************************/
void KsDeferredRender::finalRender()
{
	m_pDeferredEffect->setShader( m_pRenderContext, this );

	m_pRenderContext->setPixelTexture( 0, 1, 0 );
	m_pRenderContext->setPixelConstantBuffers( 0, 1, m_pLighting->getLightingBuffer() );
	m_pRenderContext->setPrimitiveTopology( KS_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
	m_pRenderContext->setPixelTexture( 8, 1, m_pLighting->getLightingUAV() );
	m_pRenderContext->drawIndexed( 4, 0, 0 );

	//m_pRenderContext->clearState();
}

/************************************************************************************************/
/*
 * カートゥーン輪郭線
 */
/************************************************************************************************/
void KsDeferredRender::renderContourExtraction()
{
	const KsUInt32	stride = sizeof( KS_CONTOUR_VERTEX );
	const KsUInt32	offset = 0;

	//m_pRenderContext->setPixelTexture( 0, 1, 0 );
	//m_pRenderContext->setPixelTexture( 8, 1, m_pLightBufferUAV );
	m_pRenderContext->setPixelTexture( 0, 1, m_pGBufferTexture[ ksMRT_NORMAL     ] );
	m_pRenderContext->setPixelTexture( 1, 1, m_pGBufferTexture[ ksMRT_ALBEDO     ] );
	m_pRenderContext->setPixelTexture( 3, 1, m_pGBufferTexture[ ksMRT_ZBUFFER    ] );

	m_pContourEffect->setShader( m_pRenderContext, this );

	m_pRenderContext->setPrimitiveTopology( KS_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
	m_pRenderContext->drawIndexed( 4, 0, 0 );
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsDeferredRender::drawDebug()
{
	KsGraphics*	pGraphics = KsGraphics::getInstancePtr();

	pGraphics->drawSprite( ((KsRenderTargetTexture*)m_pGBuffer[ ksMRT_NORMAL     ])->getTexture(),   0,   0, 640, 360 );
	pGraphics->drawSprite( ((KsRenderTargetTexture*)m_pGBuffer[ ksMRT_ALBEDO     ])->getTexture(), 640,   0, 640, 360 );
	pGraphics->drawSprite( ((KsRenderTargetTexture*)m_pGBuffer[ ksMRT_POSITION   ])->getTexture(),   0, 360, 640, 360 );
	//pGraphics->drawSprite( ((KsRenderTargetTexture*)m_pGBuffer[ ksMRT_ZBUFFER    ])->getTexture(), 640, 360, 640, 360 );
	//pGraphics->drawSprite( ((KsRenderTargetTexture*)m_pGBuffer[ ksMRT_ACCUMULATE ])->getTexture(), 640, 360, 640, 360 );
	pGraphics->drawSprite( m_pLighting->getLightingUAV(), 640, 360, 640, 360 );	
	
	pGraphics->flush( m_pRenderContext );
}

/************************************************************************************************/
/*
 * シーンを描画する
 */
/************************************************************************************************/
void KsDeferredRender::render()
{
	// 別スレッドの描画スレッド処理
	for( KsUInt32 i=0; i<m_numRenderThread; i++ )
	{
		m_pRenderThread[ i ]->startBeginRender();
	}

#if 1
	// ライト更新
	updateLight();

	// G-Bufferを生成する
	renderGBuffer();

	// パラメータを更新する
	updateShaderParameter();

	// ライティング
	computeLighting();

	// レンダーターゲットを元に戻す
	setRenderTarget_Default( m_pRenderContext );

	// ターゲットをクリアーする
	//pDeferredRender->clearScene();

	// 最終レンダリング
	finalRender();
	//renderContourExtraction();

	//drawDebug();

	KsGraphics*	pGraphics = KsGraphics::getInstancePtr();

	pGraphics->flush( m_pRenderContext );

	ksDEBUG_FLUSH();

#endif

	// 描画終了待ち
	for( KsUInt32 i=0; i<m_numRenderThread; i++ )
	{
		m_pRenderThread[ i ]->waitEndRender();
	}
	//KsWaitEventForMultiple( m_numRenderThread,  g_hEndPerSceneRenderDeferredEvent );

	// 描画コマンド実行処理
	for( KsUInt32 i=0; i<m_numRenderThread; i++ )
	{
		m_pRenderContext->executeCommandList( m_pRenderThread[ i ]->getCommandList(), ksTRUE );
		//m_pRenderThread[ i ]->getCommandList()->clear();
	}
}

/************************************************************************************************/
/*
 * モデルを追加する
 */
/************************************************************************************************/
void KsDeferredRender::addModel( KsModel* pModel )
{
	m_pModels.push_back( pModel );
}

/************************************************************************************************/
/*
 * アクターを追加する
 */
/************************************************************************************************/
void KsDeferredRender::addActor( KsActor* pActor )
{
	m_pActors.push_back( pActor );
}

