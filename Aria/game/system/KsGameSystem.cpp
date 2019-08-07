/************************************************************************************************/
/** 
 * @file		KsGameSystem.cpp
 * @brief		ゲームシステム
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                     　      */
/*==============================================================================================*/
#include "Aria/KsGamePreCompile.h"
#include "Aria/game/system/KsGameSystem.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
KsGameSystem* KsGameSystem::m_pInstance = NULL;

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsGameSystem::KsGameSystem()
	: KsSceneManager()
	, m_bActive( ksFALSE )
	, m_pMainWindow( 0 )
	, m_pRenderSystem( 0 )
	, m_pPhysicsSystem( 0 )
	, m_pOVRSystem( 0 )
	, m_pVirtualMachine( 0 )
	, m_pInputSystem( 0 )
	, m_pPadManager( 0 )
	, m_pGameResourceManager( 0 )
	, m_pCameraManager( 0 )
	, m_pFileSystem( 0 )
	//, m_pSoundManager( 0 )
	, m_clearColor( 32, 64, 128, 0xff )
	, m_bRender( ksTRUE )
	, m_bMainLoop( ksTRUE )
	, m_pDeferredRender( 0 )
	, m_pPhysicsThread( 0 )
{
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsGameSystem::~KsGameSystem()
{
	/* 後処理をする */
	terminate();
}

/************************************************************************************************/
/*
 * ゲーム生成
 * @param	hInstance			インスタンス
 * @param	hPrevInstance		インスタンス
 * @param	lpCmdLine			コマンドライン
 * @param	nCmdShow			コマンド表示
 */
/************************************************************************************************/
KsBool KsGameSystem::create( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, KsInt32 nCmdShow )
{
	//---------------------------------------------------------------
	// ウインドウの設定ファイルをチェックする
	//---------------------------------------------------------------
	KsGameConfigManager::setup();

	//---------------------------------------------------------------
	// ウインドウのパラメータ保存
	//---------------------------------------------------------------
	KsAppInstance::setup( hInstance, hPrevInstance, lpCmdLine, nCmdShow );

	//---------------------------------------------------------------
	// ウインドウのスタイル設定 
	//---------------------------------------------------------------
	RECT	rect;

	KsWindowUtility::getDeskTopClientRect( &rect );

	m_mainWindowParam.m_caption   = ksGAME_TITLE;
	m_mainWindowParam.m_className = ksGAME_CLASS;
	m_mainWindowParam.m_style     = ksWINDOW_DEFAULT_STYLE;
	m_mainWindowParam.m_styleEx   = 0;
	m_mainWindowParam.m_posX      = ( rect.right  - rect.left )/2 - ksWINDOW_DEFAULT_SIZE_X/2;
	m_mainWindowParam.m_posY      = ( rect.bottom - rect.top  )/2 - ksWINDOW_DEFAULT_SIZE_Y/2;
	m_mainWindowParam.m_sizeX     = ksWINDOW_DEFAULT_SIZE_X;
	m_mainWindowParam.m_sizeY     = ksWINDOW_DEFAULT_SIZE_Y;

	try
	{
		/* ウインドウ生成 */
		m_pMainWindow = ksNew KsWindow();

		if( !m_pMainWindow )
		{
			throw "ウインドウメモリ確保エラー!!";
		}

		if( !( m_pMainWindow->create( m_mainWindowParam, NULL, this ) ) )
		{
			throw "ウインドウ生成エラー!!";
		}

		/* 描画システム生成 */
		m_pRenderSystem = KsRenderSystemFactory( ksRENDERSYSTEM_DIRECTX11, m_pMainWindow );

		if( !m_pRenderSystem )
		{
			throw "描画システム生成エラー!!";
		}

		/* 物理エンジンシステム生成 */
		m_pPhysicsSystem = KsPhysicsSystemFactory( ksPHYSICSSYSTEM_BULLET, NULL );

		if( !m_pPhysicsSystem )
		{
			throw "物理エンジンシステム生成エラー!!";
		}
	}
	catch( const char *pszError )
	{
		/* エラー */
		KsError( pszError );

		ksDELETE( m_pMainWindow );

		return ksFALSE;
	}

	/* 初期化と終了のときウエイトを入れる必要がある */

	return ksTRUE;
}

/************************************************************************************************/
/*
 * 初期化処理
 * @retval		ksTRUE			成功
 * @retval		ksFALSE			失敗
 */
/************************************************************************************************/
KsBool KsGameSystem::initialize()
{
	/* COM初期化 */
	//#define _WIN32_DCOM
	//::CoInitializeEx( NULL, COINIT_APARTMENTTHREADED );
	::CoInitializeEx( NULL, COINIT_MULTITHREADED );

	/* タイマー初期化 */
	KsTimer::initialize();

	/* ファイルシステム初期化 */
	m_pFileSystem = ksNew KsFileSystem( ksTHREAD_PRIORITY_HIGHEST, 2 );

	/* 入力マネージャ初期化 */
	m_pInputSystem = ksNew KsInputSystem( KsGameCommon::ksGAME_PAD_MAX );

	/* ゲームパッドマネージャ初期化 */
	m_pPadManager = ksNew KsGamePadManager( m_pInputSystem );

	/* ゲームリソースマネージャ初期化 */
	m_pGameResourceManager = ksNew KsGameResourceManager();

	/* ゲーム用シェダーマネージャ初期化 */
	m_pGameShaderManager = ksNew KsGameShaderManager();

	/* カメラマネージャ初期化*/
	m_pCameraManager = ksNew KsCameraManager();
	
	/* ゲームサウンドマネージャ初期化*/
	//m_pSoundManager = ksNew KsGameSoundManager();

	/* バーチャルマシン */
	m_pVirtualMachine = ksNew KsVirtualMachine( ksVARIABLE_STACK_SIZE, ksHANDLE_LIST_BLOCK_SIZE, ksSTRUCT_MEMBER_BLOCK_SIZE );

	/* ディファードレンダリングシステムを初期化する */
	m_pDeferredRender = ksNew KsDeferredRender( m_pRenderSystem, ksWINDOW_DEFAULT_SIZE_X, ksWINDOW_DEFAULT_SIZE_Y );

	/* Forward+レンダリングシステムを初期化する */
	m_pForwardPlusRender = ksNew KsForwardPlusRender( m_pRenderSystem, ksWINDOW_DEFAULT_SIZE_X, ksWINDOW_DEFAULT_SIZE_Y );

	// OVRシステム
	m_pOVRSystem = ksNew KsOVRSystem();

	/* 物理シミュレーションスレッド生成する */
	//m_pPhysicsThread = ksNew KsPhysicsThread( ksTHREAD_PRIORITY_NORMAL, 3 );

	/* シーン管理システムを初期化する */
	KsSceneManager::initialize();

	/* スクリプト用ライブラリをロード */
	KsScriptLoadSystemLib( m_pVirtualMachine );
	KsScriptLoadMathLib( m_pVirtualMachine );

	/* デバックシステム初期化 */
	ksDEBUG_INIT( ".\\Font\\ascii.dds" );

	//KsLoadSwf("D:\\KGDC\\Aria\\Aria\\test.swf");

	return ksTRUE;
}

/************************************************************************************************/
/*
 * 後処理
 * @retval		ksTRUE		成功
 * @retval		ksFALSE		失敗
 */
/************************************************************************************************/
KsBool KsGameSystem::terminate()
{
	//---------------------------------------------------------------
	// デバックフォント解放
	//---------------------------------------------------------------
	ksDEBUG_TERM();

	/* マネージャを参照しているタスクもあるので,まずタスクを消さないとまずい */
	KsSceneManager::terminate();

	/* スクリプト用ライブラリをアンロード */
	KsScriptUnloadMathLib( m_pVirtualMachine );
	KsScriptUnloadSystemLib( m_pVirtualMachine );

	//---------------------------------------------------------------
	// 後処理 
	//---------------------------------------------------------------
	ksDELETE( m_pPhysicsThread );
	ksDELETE( m_pOVRSystem );
	ksDELETE( m_pForwardPlusRender );
	ksDELETE( m_pDeferredRender );
	ksDELETE( m_pCameraManager );
	ksDELETE( m_pGameResourceManager );
	ksDELETE( m_pPadManager );
	ksDELETE( m_pInputSystem );
	ksDELETE( m_pVirtualMachine );
	//ksDELETE( m_pSoundManager );
	ksDELETE( m_pPhysicsSystem );
	ksDELETE( m_pRenderSystem );
	ksDELETE( m_pMainWindow );

	/* ファイルシステム後処理 */
	ksDELETE( m_pFileSystem );

	/* サウンドシステム後処理 */
	//ksDELETE( m_pSoundManager );

	/* デバック後処理 */
	//ksDEBUG_TERM();

	//---------------------------------------------------------------
	// ウインドウの設定ファイルをチェックする
	//---------------------------------------------------------------
	KsGameConfigManager::shutdown();

	//---------------------------------------------------------------
	// COM後処理 
	//---------------------------------------------------------------
	::CoUninitialize();

	return ksTRUE;
}

/************************************************************************************************/
/*
 * ソフトウェアーリセット処理
 */
/************************************************************************************************/
void KsGameSystem::softwareReset()
{
}

/************************************************************************************************/
/*
 * ソフトリセット要求があったかどうか？
 */
/************************************************************************************************/
KsBool KsGameSystem::isSoftwareReset()
{
	return ksFALSE;
}

/************************************************************************************************/
/*
 * ゲームを終了させる
 */
/************************************************************************************************/
void KsGameSystem::gameExit()
{
	m_bMainLoop = ksFALSE;
}

/************************************************************************************************/
/*
 * ゲームループ中か？
 * @retval		ksTRUE			ゲームループ中
 * @retval		ksFALSE			ゲームループ終了
 */
/************************************************************************************************/
KsBool KsGameSystem::isGameLoop()
{
	if( m_pMainWindow->messageLoop() )
	{
		if( isSoftwareReset() )
		{
			return ksFALSE;
		}

		return ksTRUE;
	}

	gameExit();

	return ksFALSE;
}

/************************************************************************************************/
/*
 * ゲームループ中か？
 * @retval		ksTRUE			ゲームループ中
 * @retval		ksFALSE			ゲームループ終了
 */
/************************************************************************************************/
KsBool KsGameSystem::messageLoop()
{
	while( m_pMainWindow->messageLoop() )
	{
	}

	return ksTRUE;
}

/************************************************************************************************/
/*
 * 描画開始
 */
/************************************************************************************************/
void KsGameSystem::begineRender()
{
	/* 描画開始 */
	//m_pRenderSystem->beginScene( (ksCLEAR_FLAG_COLOR | ksCLEAR_FLAG_DEPTH ), m_clearColor, 1.0f, 0 );
}

/************************************************************************************************/
/*
 * 描画終了
 */
/************************************************************************************************/
void KsGameSystem::endRender()
{
	//ksDEBUG_PRINT( "FPS:%2d", KsTimer::getFps() );
	//ksDEBUG_FLUSH();

	/* 描画終了 */
	//m_pRenderSystem->endScene();

	/* 描画バッファと表示バッファを入れ替え */
	m_pRenderSystem->present();
}

/************************************************************************************************/
/*
 * 実行する
 */
/************************************************************************************************/
void KsGameSystem::execute( void* pParam )
{
	// シーン更新
	KsSceneManager::execute( pParam );
}
/************************************************************************************************/
/*
 * 描画する
 */
/************************************************************************************************/
void KsGameSystem::render( void* pParam )
{
	// シーン描画
	KsSceneManager::render( pParam );

	/* 描画処理 */
	//render( pParam );

	//begineRender();

	// レンダリング
	//m_renderTbl.render( pParam );
	m_pDeferredRender->render();

	endRender();
}
/************************************************************************************************/
/*
 * 更新処理
 */
/************************************************************************************************/
void KsGameSystem::update( void* pParam )
{
	/* 削除フラグがたっていたら */
	//for( KsInt32 i=0; i<KsWorkArea::m_count; i++ )
	//{
		//kill( KsWorkArea::m_work[ i ], pParam );
	//}

	//KsWorkArea::clear();
}

/************************************************************************************************/
/*
 * すべての処理を実行
 * @param	pParam		ここでわたしたパラメータがタスクのexecuteやrenderの引数に渡る
 *						デフォルトでは、NULLが設定されている。
 */
/************************************************************************************************/
void KsGameSystem::run( void* pParam )
{
	if( m_pPhysicsThread )
	{
		m_pPhysicsThread->waitSimulation();
	}

	/* 実行 */
	execute( pParam );

	/* 描画(カメラの描画はここだけ) */
	if( isRender() )
	{
		render( pParam );
	}

	/* 更新 */
	update( pParam );

	if( m_pPhysicsThread )
	{
		m_pPhysicsThread->startSimulation();
	}
}

/************************************************************************************************/
/*
 * ポーリング処理
 */
/************************************************************************************************/
void KsGameSystem::polling()
{
	m_pFileSystem->callback();
}

/************************************************************************************************/
/*
 * サウンド更新処理
 */
/************************************************************************************************/
void KsGameSystem::sound()
{
	//m_pSoundManager->update();
}

/************************************************************************************************/
/*
 * パッド処理
 */
/************************************************************************************************/
void KsGameSystem::pad()
{
	/* パッド情報更新 */
	m_pPadManager->update();
}

/************************************************************************************************/
/*
 * VSync待ちの処理(仮想)
 */
/************************************************************************************************/
void KsGameSystem::vsync()
{
	/* タイマー更新 */
	KsTimer::update();

	/* VSYNC 待ち(仮想) */
	//KsTimer::vsync( KsTimer::ksFPS60 );
}

/************************************************************************************************/
/*
 * ゲームループ
 */
/************************************************************************************************/
void KsGameSystem::loop()
{
	/* ゲームループ */
	while( isMainLoop() )
	{
		/* ソフトウェアリセット */
		softwareReset();

		if( isGameLoop() )
		{
			/* ファイルシステムポーリング */
			polling();

			/* サウンド更新処理 */
			sound();

			/* 入力処理 */
			pad();

			/* 実行処理 */
			run( this );

			/* VSYNC 待ち(仮想) */
			vsync();
		}
	}
}

/************************************************************************************************/
/*
 * モデルを追加する
 */
/************************************************************************************************/
void KsGameSystem::addModel( KsModel* pModel )
{
	m_pDeferredRender->addModel( pModel );
}

/************************************************************************************************/
/*
 * アクターを追加する
 */
/************************************************************************************************/
void KsGameSystem::addActor( KsActor* pActor )
{
	m_pDeferredRender->addActor( pActor );
}

/************************************************************************************************/
/*
 * インスタンス取得
 */
/************************************************************************************************/
KsGameSystem* KsGameSystem::getInstancePtr()
{
	if( !m_pInstance )
	{
		m_pInstance = ksNew KsGameSystem();
	}

	return m_pInstance;
}

/************************************************************************************************/
/*
 * インスタンス破棄
 */
/************************************************************************************************/
void KsGameSystem::destoryInstance()
{
	ksDELETE( m_pInstance );
}

/************************************************************************************************/
/*
 * ゲームタスクを追加する
 */
/************************************************************************************************/
KsBool KsGameSystem::addGameTask( KsTask* pTask )
{
	m_pInstance->addTask( pTask );

	return ksTRUE;
}

/************************************************************************************************/
/*
 * ゲームタスクを取り除く
 */
/************************************************************************************************/
KsBool KsGameSystem::removeGameTask( KsTask* pTask )
{
	m_pInstance->removeTask( pTask );

	return ksTRUE;
}

/************************************************************************************************/
/*
 * ゲームシステム生成
 * @param	hInstance			インスタンス
 * @param	hPrevInstance		インスタンス
 * @param	lpCmdLine			コマンドライン
 * @param	nCmdShow			コマンド表示
 * @note	すでにウインドウがある場合は、それをもとのサイズで復旧させる
 */
/************************************************************************************************/
KsGameSystem* KsGameCreate( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, KsInt32 nCmdShow )
{
	/* マネージャを生成する */
	KsGameSystem*	pGameSystem;
	
	/* インスタンス取得ここでは、生成されるはず */
	pGameSystem = KsGameSystem::getInstancePtr();

	/* 生成 */
	pGameSystem->create( hInstance, hPrevInstance, lpCmdLine, nCmdShow );

	return pGameSystem;
}

/************************************************************************************************/
/*
 * ゲームループ
 * @param	pGame	ゲームシステムのポインタ
 */
/************************************************************************************************/
void KsGameLoop( KsGameSystem* pGame )
{
	pGame->loop();
}

/************************************************************************************************/
/*
 * ゲームシステム破棄
 * @param	pGame	ゲームシステムのポインタ
 */
/************************************************************************************************/
void KsGameDestroy( KsGameSystem* pGame )
{
	/* 開放 */
	KsGameSystem::destoryInstance();

	/* メモリーリークチェック */
	//KsDumpMemoryLeaks();
}

