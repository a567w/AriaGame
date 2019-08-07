/************************************************************************************************/
/** 
 * @file		KsRenderThread.cpp
 * @brief		描画スレッド
 * @author		Tsukasa Kato
 * @date		2011/07/02
 * @since		2011/07/02
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "Aria/KsGamePreCompile.h"
#include "Aria/thread/KsRenderThread.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * 描画システム生成
 */
/************************************************************************************************/
KsRenderThread::KsRenderThread( KsRenderSystem* pRenderSystem, KsDeferredRender* pDeferredRender )
	: m_pRenderSystem( pRenderSystem )
	, m_pDeferredRender( pDeferredRender )
	, m_bThreadLoop( ksFALSE )
	, m_bClearState( ksFALSE )
	, m_bRestoreState( ksFALSE )
	, m_pRenderContext( 0 )
	, m_pCommandList( 0 )
{
	try
	{
		m_beginRenderEvent = KsCreateEvent( ksFALSE, ksFALSE, "BeginRenderEvent" );
		m_endRenderEvent   = KsCreateEvent( ksFALSE, ksFALSE, "EndRenderEvent" );

		m_pRenderContext   = pRenderSystem->createDeferredContext();
		m_pCommandList     = pRenderSystem->createCommandList();

		KS_DEPTH_STENCIL_DESC	desc = KsDepthStencilState::DEFAULT;
		desc.DepthFunc = KS_COMPARISON_GREATER_EQUAL;
		m_pDepthState = m_pRenderSystem->createDepthStencilState( &desc );

		//m_pRenderContext->setRenderTarget( pRenderSystem->getRenderContex()->getRenderTarget(), pRenderSystem->getRenderContex()->getDepthStencil() );

		if( !m_pRenderContext )
		{
			throw "描画コンテキスト生成エラー!!";
		}

		if( !m_pCommandList )
		{
			throw "描画コマンドリストエラー!!";
		}
	}
	catch( const KsChar* pszError )
	{
		/* エラー */
		KsError( pszError );
	}
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsRenderThread::~KsRenderThread()
{
	KsCloseEvent( m_beginRenderEvent );
	KsCloseEvent( m_endRenderEvent );

	ksDELETE( m_pRenderContext );
	ksDELETE( m_pCommandList );
}

/************************************************************************************************/
/*
 * 実行する
 */
/************************************************************************************************/
KsBool KsRenderThread::run()
{
	m_bThreadLoop = ksTRUE;

	start();

	return ksTRUE;
}

/************************************************************************************************/
/*
 * スレッドのメイン関数
 * @return	実行終了結果
 */
/************************************************************************************************/
KsUInt32 KsRenderThread::threadMain()
{
	// 指定プロセッサを割り当てる。
	//setProcessor( 1<<2 );

	/* ゲームループ */
	while( m_bThreadLoop )
	{
		// メインスレッドとの同期待ち
		KsWaitEvent( m_beginRenderEvent );

		// ステートをクリアする
		if( m_bClearState )
		{
			m_pRenderContext->clearState();
		}

#if 0
		m_pDeferredRender->setViewport( 0, 0, 1280, 720, 0.0f, 1.0f, m_pRenderContext );

		// レンダーターゲットをセットしないと描画されない。
		m_pDeferredRender->setRenderTarget_Default( m_pRenderContext );

		m_pRenderContext->setDepthStencilState( m_pDepthState, 0 );
		KsGraphics*	pGraphics = KsGraphics::getInstancePtr();

		pGraphics->setColorRect( 1.0f, 1.0f, 0.0f, 1.0f ); 
		pGraphics->drawRect( 0, 0, 400, 400 );
	
		pGraphics->flush( m_pRenderContext );

		//m_pRenderContext->clearScene( ksCLEAR_FLAG_COLOR, KsColor::RED, 1.0f, 0 );
#endif


		// 描画する
		//render( m_pRenderContext );

		// コマンドリストを生成する
		m_pRenderContext->finishCommandList( m_bRestoreState, m_pCommandList );

		// 描画終了イベントをセットする
		KsSetEvent( m_endRenderEvent );
	}

	return 0;
}

/************************************************************************************************/
/*
 * スレッド描画開始する
 */
/************************************************************************************************/
void KsRenderThread::startBeginRender()
{
	// 描画終了イベントをセットする
	KsSetEvent( m_beginRenderEvent );
}

/************************************************************************************************/
/*
 * 描画終了イベントを待つ
 */
/************************************************************************************************/
void KsRenderThread::waitEndRender()
{
	// 描画終了イベントを待つ
	KsWaitEvent( m_endRenderEvent );
}

