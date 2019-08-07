#if 0

/************************************************************************************************/
/** 
 * @file		KsGameSystemManager.cpp
 * @brief		ゲームマネージャ
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsGameSystemManager.h"
#include "StPs2IOP.h"
#include "StTimer.h"
#include "StVBlank.h"
#include "StMallocFix.h"
#include "StSceneManager.h"
#include "StDebugManager.h"
//#include "StTimer.h"
//#include "StSprite.h"
//#include "StDebugManager.h"
//#include "StSoundUtil.h"

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
KsGameSystemManager::KsGameSystemManager()
{
	m_gameMode            = 0;
	m_gameTimer           = 0;
	m_exitFlag            = stSOFT_EXIT_FLAG_OFF;
	m_softResetFlag       = stSOFT_RESET_FLAG_OFF;
	m_softResetPermission = stPERMISSION_OK;
	m_pauseFlag           = stPAUSE_FLAG_OFF;
	m_pausePermission     = stPERMISSION_OK;
	m_pPadManager   = NULL;
}
/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsGameSystemManager::~KsGameSystemManager()
{
	
}

/************************************************************************************************/
/**
* インスタンス取得
*/
/************************************************************************************************/
KsGameSystemManager* KsGameSystemManager::getInstance()
{
	static KsGameSystemManager		gsm;

	return ( &gsm );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsGameSystemManager::initialize()
{
	/* タイマ初期化 */
	StTimerInitialize();

	/* パッド初期化 */
	StPadManagerInitialize();

	/* RenderWare初期化 */
	m_renderSystem.initialize();
	
	/* パラメータをセット */
	//m_pFileSystem = StFileSystemPSP::instance();
	m_pPadManager = StPadManager::instance();
	
	/* タスクオーダーをセットする */
	setTaskOrder();
	
	/* 最低1つは、カメラを作っておこう */
	/* ルートタスクを作る */
	setRootTask( new StSceneManager() );
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsGameSystemManager::terminate()
{
	/* マネージャを参照しているタスクもあるので,まずタスクを消さないとまずい */
	allKill( this );

	/* 描画システムを開放する */
	m_renderSystem.terminate();

	/* ファイルシステム後処理 */
	//StFileSystemPSPTerminate();

	/* ログ関係後処理 */
	//StLogTerminate();

}
/************************************************************************************************/
/*
 * ソフトリセット
 */
/************************************************************************************************/
void KsGameSystemManager::softResetInitialize()
{
	/* ソフトリセットOFF */
	m_softResetFlag = stSOFT_RESET_FLAG_OFF;

	/* 初期化とどのシーンに戻るかなどの情報 */
}
/************************************************************************************************/
/*
 * ソフトリセットチェック
 */
/************************************************************************************************/
void KsGameSystemManager::softExitCheck()
{
	if( ( m_pPadManager->getNow() & stPAD_SOFT_RESET ) == stPAD_SOFT_RESET ){
		m_softResetFlag = stSOFT_RESET_FLAG_ON;
		m_exitFlag      = stSOFT_EXIT_FLAG_ON;
	}
}
/************************************************************************************************/
/*
 * ゲームループ
 */
/************************************************************************************************/
void KsGameSystemManager::gameLoop()
{
	/* ゲームループ */
	while( m_exitFlag )
	{
		/* ゲームシステム系の初期化 */
		softResetInitialize();

		while( m_softResetFlag )
		{
			/* パッド情報更新 */
			//KsPadManagerUpdate();

			/* タスク実行(描画が終了してから一括で削除処理をするように変更する) */
			run( (void*)this );

			/* 終了チェック */
			softExitCheck();

			/* タイマーの更新 */
			StTimerUpdate();
		}
	}

}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsGameSystemManager::begineRender()
{
	//m_renderSystem.beginScene();
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsGameSystemManager::endRender()
{
	//m_renderSystem.endScene();
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsGameSystemManager::setTaskOrder()
{
	/* スプライトタスクはソートを使用するようにする */
	//this->m_renderTbl.getOrder( stSPRITE_TASK_ORDER )->setFlags( stOT_FLAGS_PRIORITYSORT );
}

#if 0
sTestSystem*	KsTestSystemCreate()
{
	return new KsTestSystem();
}

KsTestSystem::KsTestSystem()
{
	m_pMainWindow   = NULL;
}

KsTestSystem::~KsTestSystem()
{
	ksDELETE( m_pMainWindow );
}

KsBool KsGameSystemManager::createWindow()
{
	RECT			rect;

	/* デスクトップのクライアント領域を取得する */
	KsGetDeskTopClientRect( &rect );

	/* ini ファイルから設定を取得する */
	/*
	フルスクリーン
	window size x y
	flag
	*/
	/* ウインドウの生成パらーメータをセットする */
	m_mainWindowParam.m_caption   = "Test";
	m_mainWindowParam.m_className = "KsSystem";
	m_mainWindowParam.m_style     = ksWINDOW_DEFAULT_STYLE;
	m_mainWindowParam.m_styleEx   = 0;
	m_mainWindowParam.m_posX      = ( rect.right  - rect.left )/2 - 320;
	m_mainWindowParam.m_posY      = ( rect.bottom - rect.top  )/2 - 240;
	m_mainWindowParam.m_sizeX     = 640;
	m_mainWindowParam.m_sizeY     = 480;

	/* ウインドウ生成 */
	m_pMainWindow = new KsWindow();

	if( !m_pMainWindow ){
		return ksFALSE;
	}

	if( !( m_pMainWindow->create( m_mainWindowParam ) ) ){
		return ksFALSE;
	}

	return ksTRUE;
}

KsBool KsTestSystem::Create( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, KsInt32 nCmdShow )
{
	KsAppInstance::set( hInstance, hPrevInstance, lpCmdLine, nCmdShow );

	//m_pRenderSystem = new KsRenderSystemGL( m_pMainWindow->getHWnd() );
	m_pRenderSystem = new KsRenderSystemDX( m_pMainWindow->getHWnd() );


	m_pRenderSystem->auto3DMode();

	// 初期化と終了のときウエイトを入れる必要がある

	return ksTRUE;
}


/************************************************************************************************/
/*
 * ウエイト
 */
/************************************************************************************************/


void KsTestSystem::Loop()
{
	do{
		m_pRenderSystem->beginScene( ksCLEAR_FLAG_COLOR | ksCLEAR_FLAG_DEPTH, KsColor( 0, 80, 80, 1 ), 1.0f, 0 );
		m_pRenderSystem->endScene();
		m_pRenderSystem->swapBuffer();
		vsync( 1 );

	}while( m_pMainWindow->messageLoop() );
}
#endif



#endif

