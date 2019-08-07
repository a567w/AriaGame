/************************************************************************************************/
/** 
 * @file		KsTaskManager.cpp
 * @brief		基本タスクマネージャ
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsTaskManager.h"
#include "KsWorkArea.h"

#ifndef _MASTER
	#include "KsTimer.h"
#endif

//KsInt32	KsTaskManager::m_taskID = 0;

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
//#define ksTASK_DELETE_BEFORE	( 1 )

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void* KsTaskManager::setManagerCallback( KsTask* pTask, void* pParam )
{
	if( pTask ){
		pTask->m_pManager = (KsTaskManager*)pParam;

		/* 描画リンクを解除または、セット */
		if( pTask->m_pManager ){
			/* 描画リンク生成 */
			pTask->m_pManager->m_renderTbl.entry( pTask );
		}
		else{
			/* 描画リンクを解除 */
			pTask->m_pPrev = NULL;
			pTask->m_pNext = NULL;
		}

		return pTask;
	}

	return NULL;
}
/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsTaskManager::KsTaskManager() : m_pRootTask( 0 )
{
}
/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsTaskManager::~KsTaskManager()
{
	/* すべてのリンクを破棄する */
	kill( m_pRootTask, this );
}
/************************************************************************************************/
/*
 * すべて削除
 */
/************************************************************************************************/
void KsTaskManager::allKill( void* pParam )
{
	/* すべてのリンクを破棄する */
	kill( m_pRootTask, pParam );
	m_pRootTask = NULL;
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsTask* KsTaskManager::setRootTask( KsTask* pTask )
{
	KsTask*			pOldTask;

	/* 描画リンクをクリア(このとき描画リンクだけでカメラリンクは、クリアされない) */
	m_renderTbl.clear();

	/* NULLをセット */
	allCallback( setManagerCallback, NULL );

	pOldTask    = m_pRootTask;
	m_pRootTask = pTask;

	/* マネージャのポインタをセットする */
	allCallback( setManagerCallback, this );

	return pOldTask;
}
/************************************************************************************************/
/*
 * 実行する
 */
/************************************************************************************************/
void KsTaskManager::execute( void* pParam )
{
	taskExecute( m_pRootTask, pParam );
}
/************************************************************************************************/
/*
 * 描画する
 */
/************************************************************************************************/
void KsTaskManager::render( void* pParam )
{
	/* 描画処理 */
	begineRender();

	m_renderTbl.render( pParam );

	endRender();
}
/************************************************************************************************/
/*
 * 更新処理
 */
/************************************************************************************************/
void KsTaskManager::update( void* pParam )
{
	/* 削除フラグがたっていたら */
	for( KsInt32 i=0; i<KsWorkArea::m_count; i++ ){
		kill( KsWorkArea::m_work[ i ], pParam );
	}

	KsWorkArea::clear();
}
/************************************************************************************************/
/*
 * 指定オーダーだけストップさせるとかの機能がほしい
 */
/************************************************************************************************/
void KsTaskManager::run( void* pParam )
{
#ifndef _MASTER
	/* 時間を初期化 */
	KsTimer::checkStart();
#endif

	/* 実行 */
	execute( pParam );

#ifndef _MASTER
	/* CPU時間を測定 */
	KsTimer::checkCpu();
#endif

	/* 描画(カメラの描画はここだけ) */
	render( pParam );

#ifndef _MASTER
	/* 描画時間を測定 */
	KsTimer::checkGpu();
#endif

	/* 更新 */
	update( pParam );
	
#ifndef _MASTER
	/* トータル時間を測定 */
	KsTimer::checkTotal();
#endif
}
/************************************************************************************************/
/*
 * 子を追加または、兄弟を追加時に描画リンクも生成する必要がある?
 * それともマネージャーの実行時に毎フレーム描画リンクを生成する(orderから)
 * または、OTに登録関数を追加する
 * 更新フラグで何度もリンクを作らなくよいようにする必要がある
 * (速度をチェックする)
 */
/************************************************************************************************/
void KsTaskManager::taskExecute( KsTask* pTask, void* pUserData )
{
	if( pTask ){
		/* 初期化フラグをチェックする */
		if( pTask->m_flags & ksTASK_FALGS_INITIALIZE ){
			/* 初期化 */
			pTask->initialize( pUserData );
			/* 初期化終了 */
			pTask->m_flags &= (KsUInt32)(~ksTASK_FALGS_INITIALIZE);
			//pTask->m_id = m_taskID;
			//m_taskID++;
		}

		/* ポーズフラグチェック */
		if( !(pTask->m_flags & ksTASK_FLAGS_PAUSE) ){
			/* 実行 */
			pTask->execute( pUserData );
		}

		/* 子タスク */
		/* もしすっとぷフラグがたっていたらreturn で戻る必要がある */
		if( !(pTask->m_flags & ksTASK_FLAGS_PAUSE_CHILD) ){
			if( pTask->m_pChild ){
				taskExecute( pTask->m_pChild, pUserData );
			}
		}

		/* 兄弟タスク */
		if( pTask->m_pNextBrother ){
			taskExecute( pTask->m_pNextBrother, pUserData );
		}
	}
}
/************************************************************************************************/
/*
 * 描画開始
 */
/************************************************************************************************/
void KsTaskManager::begineRender()
{
}
/************************************************************************************************/
/*
 * 描画終了
 */
/************************************************************************************************/
void KsTaskManager::endRender()
{
}
/************************************************************************************************/
/*
 * 削除
 */
/************************************************************************************************/
void KsTaskManager::kill( KsTask* pTask, void* pParam )
{
	KsTask*		pChild   = NULL;
	KsTask*		pBrother = NULL;

	if( pTask ){
		/* 描画フラグチェック */
		pChild   = pTask->m_pChild;
		pBrother = pTask->m_pNextBrother;

		/* 描画リンクをはずす必要がある */
		this->m_renderTbl.remove( pTask );

		/*
			削除するときカメラだったら描画リンクからはずしてから削除しないとだめ
			じゃないとリンクに残ったまま消えてしまう
		*/
		//if( pTask->getType() == ksTASK_TYPE_CAMERA ){
		//	m_renderTbl.getOrder( 32 )->clear();
		//}

#ifdef ksTASK_DELETE_BEFORE
		/* 自分のタスクを削除してから子タスクを消す(カメラでまずいのでこの処理は、やめておく) */

		/* 後処理 */
		pTask->terminate( pParam );

		/* ワークエリア使用かチェックする */
		if( !( pTask->getFlags() & ksTASK_FLAGS_USE_WORKAREA ) ){
			delete pTask;
		}

		/* 子タスク */
		if( pChild ){
			kill( pChild, pParam );
		}

		/* 兄弟タスク */
		if( pBrother ){
			kill( pBrother, pParam );
		}
#else
		/* 最初に子タスクと兄弟を消す(これを採用) */

		/* 子タスク */
		if( pChild ){
			kill( pChild, pParam );
		}

		/* 兄弟タスク */
		if( pBrother ){
			kill( pBrother, pParam );
		}
		
		/* 後処理 */
		pTask->terminate( pParam );

		/* ワークエリア使用かチェックする */
		if( !( pTask->getFlags() & ksTASK_FLAGS_USE_WORKAREA ) ){
			delete pTask;
		}
#endif

	}
}
/************************************************************************************************/
/*
 * すべてに適用する
 */
/************************************************************************************************/
void KsTaskManager::allCallback( KsTaskCallback callback, void* pUserData )
{
	allChildCallback( m_pRootTask, callback, pUserData );
}
/************************************************************************************************/
/*
 * すべての子供に適用
 */
/************************************************************************************************/
void KsTaskManager::allChildCallback( KsTask* pTask, KsTaskCallback callback, void* pUserData )
{
	if( pTask ){

		if( !callback( pTask, pUserData ) ){ return; }

		/* 子タスク */
		if( pTask->m_pChild ){
			allChildCallback( pTask->m_pChild, callback, pUserData );
		}

		/* 兄弟タスク */
		if( pTask->m_pNextBrother ){
			allChildCallback( pTask->m_pNextBrother, callback, pUserData );
		}
	}
}

