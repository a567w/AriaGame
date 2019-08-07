/*************************************************************************************************/
/**
 * @file	main.cpp
 * @brief	メイン関数
 * @author	Tsukasa Kato
 * @date	2004/12/13
 * @version	1.0.0
 */
/*************************************************************************************************/

/*===============================================================================================*/
/*                                 << インクルード >>                                             */
/*===============================================================================================*/
#include "StCommon.h"
#include "StModuleManager.h"
#include "StGameSystemManager.h"
#include "StMemoryManager.h"
#include "StMoviePlayer.h"

/*===============================================================================================*/
/*										<< 定義 >>												 */
/*===============================================================================================*/

/* モジュール名とバージョン (name, atribute, major, mainor) */
SCE_MODULE_INFO( ggmc, 0, 0, 1 );

/* malloc 用ヒープサイズ */
SceInt32 sce_newlib_heap_kb_size = ( 18*1024 );	/*　18 MB	*/

/* スタックサイズ */
SceInt32 sce_newlib_stack_kb_size = 512;		/*　512 KB	*/

/* main()関数の動作するスレッドの優先度 */
SceInt32 sce_newlib_priority = 64;

/* 登録モジュール一覧 */
static ST_MODULE_TBL_DATA		s_moduleTbl[] = 
{
	{ "KMODULE/videocodec.prx",      0,      0 },
	{ "KMODULE/sc_sascore.prx",      0,      1 },
	{ "KMODULE/audiocodec.prx",      0,      2 },
	{ "KMODULE/mpegbase.prx",        0,      3 },
	{ "MODULE/libatrac3plus.prx",    1,      4 },
	{ "MODULE/mpeg.prx",             1,      5 },
	{ "MODULE/libfont.prx",          1,      6 },
	{ "none",                   0xffff, 0xffff }
};

/*************************************************************************************************/
/**
 * 終了コールバックによって呼び出される関数を定義します。
 */
/*************************************************************************************************/
static int exitFunc( int count, int arg1, void* arg2 )
{
    /* arg1 は NotifyCallback で渡される引数です */
    /* arg2 は CreateCallback で与えられる引数です */
    StPrintf("** %s(0x%08x)\n", __FUNCTION__, *((int *)arg2));

    /**/
    /* ここでアプリケーション固有の終了処理を行います。 */
    /* 画像やサウンドの処理は特に行わなくても構いません。 */
    /**/
	StGameSystemManager*	pSys = (StGameSystemManager*)arg2;

	// スレッドが動いていたら
	// サウンドとムービーのスレッドを止める必要がある
	//pSys->crash();
	//StUmdUnAssign();

	/* ムービーが再生中だったらスレッドを終了させる */
	StMoviePlayer::exit();

	/* ゲームシステム後処理 */
	pSys->terminate();

	/* モジュール開放 */
	StModuleManager*		pModule = StModuleManager::instance();
	pModule->unloadAll();

    /* ゲーム終了システムサービスを呼び出します。 */
    sceKernelExitGame();

    /* 上記関数はこの関数内に戻ってきません。 */
    return 0;
}

/*************************************************************************************************/
/**
 * VFPUを使うためにThreadを使う必要がある
 */
/*************************************************************************************************/
#if 0
void StMainThread( SceSize _ArgNum, void* _ArgData )
{
	/* マルチスレッドにする必要あり */
	StModuleManager*		pModule = StModuleManager::instance();
	StGameSystemManager*	pSys    = StGameSystemManager::instance();
	SceUID					exitCB;

	/* モジュール読み込み */
	pModule->loadAll( s_moduleTbl );

    /*  HOMEまたはUMDが抜かれて終了用のコールバック関数生成 */
	exitCB = sceKernelCreateCallback( "gameExitCB", exitFunc, (void *)pSys );

    /* コールバックを登録します。 */
    sceKernelRegisterExitCallback( exitCB );

	/* ゲームシステム初期化 */
	pSys->initialize();

	/* ゲームループ */
	pSys->gameLoop();

	/* ゲームシステム後処理 */
	pSys->terminate();

	/* メモリーリークチェック */
	StDumpMemoryLeaks();

	/* モジュール開放 */
	pModule->unloadAll();

	StPrintf( "PROGRAM EXIT!!\n" );

	return 0;
}
/*************************************************************************************************/
/**
 * メインスレッドスタート
 */
/*************************************************************************************************/
void StStartMainThread()
{
	SceUID		mainThread = 0;

	mainThread = sceKernelCreateThread( "main", MainThread, 64, 512*1024, SCE_KERNEL_TH_USE_VFPU, NULL );
	sceKernelStartThread( mainThread, 0, NULL );
	sceKernelSleepThread();
}
#endif
/*************************************************************************************************/
/**
 * メイン
 */
/*************************************************************************************************/
int main(void)
{
	/* マルチスレッドにする必要あり */
	StModuleManager*		pModule = StModuleManager::instance();
	StGameSystemManager*	pSys    = StGameSystemManager::instance();
	SceUID					exitCB;

	/* モジュール読み込み */
	pModule->loadAll( s_moduleTbl );

    /*  HOMEまたはUMDが抜かれて終了用のコールバック関数生成 */
	exitCB = sceKernelCreateCallback( "gameExitCB", exitFunc, (void *)pSys );

    /* コールバックを登録します。 */
    sceKernelRegisterExitCallback( exitCB );

	/* ゲームシステム初期化 */
	pSys->initialize();

	/* ゲームループ */
	pSys->gameLoop();

	/* ゲームシステム後処理 */
	pSys->terminate();

	/* メモリーリークチェック */
	StDumpMemoryLeaks();

	/* モジュール開放 */
	pModule->unloadAll();

	StPrintf( "PROGRAM EXIT!!\n" );

	return 0;
}







