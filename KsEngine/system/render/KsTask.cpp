/************************************************************************************************/
/** 
 * @file		StTask.cpp
 * @brief		基本タスク
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "StTask.h"
#include "StTaskManager.h"
#include "StWorkArea.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * タスク検索コールバック用パラメータ
 */
/************************************************************************************************/
typedef struct _STFINDPARAM
{
	StUInt32		id;
	StChar*			pName;
	StTask*			pTask;

}STFINDPARAM;

/************************************************************************************************/
/*
 * 名前検索
 */
/************************************************************************************************/
static void* KsTaskFindName( StTask* pTask, void* pUserData )
{
	STFINDPARAM*	pParam = (STFINDPARAM*)pUserData;

	if( strncmp( pTask->getName(), pParam->pName, stTASK_NAME_LENGTH ) == 0 )
	{
		pParam->pTask = pTask;
		return NULL;
	}

	return pTask;
}

/************************************************************************************************/
/*
 * ID検索
 */
/************************************************************************************************/
static void* KsTaskFindID( StTask* pTask, void* pUserData )
{
	STFINDPARAM*	pParam = (STFINDPARAM*)pUserData;

	if( pTask->getID() == pParam->id )
	{
		pParam->pTask = pTask;
		return NULL;
	}

	return pTask;
}
/************************************************************************************************/
/*
 * ID検索
 */
/************************************************************************************************/
void StTaskDelete( StTask* pTask )
{
	StTask*		pChild   = NULL;
	StTask*		pBrother = NULL;

	if( pTask ){
		/* 描画フラグチェック */
		pChild   = pTask->getChild( 0 );
		pBrother = pTask->getBrother( 0 );

		/* 描画リンクをはずす必要がある(すでに描画リンクから外れている必要がある) */
		//if( m_pManager ){
		//m_renderTbl.remove( pTask );
		//}

		// 最初に親消す？
		//delete pTask;

		/* 子タスク */
		if( pChild ){
			StTaskDelete( pChild );
		}

		/* 兄弟タスク */
		if( pBrother ){
			StTaskDelete( pBrother );
		}

		/* ワークエリア使用かチェックする */
		if( !( pTask->getFlags() & stTASK_FLAGS_USE_WORKAREA ) ){
			delete pTask;
		}
	}
}

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
StTask::StTask() :	m_id( 0 ),
					m_flags( stTASK_FALGS_INITIALIZE ),
					m_order( stTASK_ORDER_DEFAULT ),
					m_type( stTASK_TYPE_BASE ),
					m_pParent( 0 ),
					m_pPrevBrother( 0 ),
					m_pNextBrother( 0 ),
					m_pChild( 0 ),
					m_pPrev( 0 ),
					m_pNext( 0 ),
					m_pManager( 0 )
{
}
/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
StTask::~StTask()
{
}
/************************************************************************************************/
/*
 * 長男の先頭ポインタに最後尾のポインタを入れておく
 */
/************************************************************************************************/
void StTask::addBrother( StTask* pTask, void* pUserData )
{
	/* 高速にする */
	if( m_pParent ){
		/* 最後の兄弟を取得 */
		/* このタスクの兄弟になるはずなので、m_pParent->m_pChildがNULLであることはないはず */
		StTask*		pLast = m_pParent->m_pChild->m_pPrevBrother;

		/* 最後尾保存用 */
		m_pParent->m_pChild->m_pPrevBrother = pTask;

		/* リンク */
		pLast->m_pNextBrother = pTask;
		pTask->m_pPrevBrother = pLast;

		/* 親セット */
		m_pNextBrother->m_pParent = m_pParent;
	}
	else{
		StTask*		pTop = getTopBrother();

		/* ルートなので長男を取得 */
		pTop->m_pPrevBrother->m_pNextBrother = pTask;

		/* このとき追加するタスクに兄弟がいたらだめだ */
		/* キチンの兄弟がいるかチェックしてセットする */

		if( pTask->m_pNextBrother ){
			/* すでに兄弟がいるので最後尾を取得する */
			pTop->m_pPrevBrother = pTask->getEndBrother();
		}
		else{
			pTop->m_pPrevBrother = pTask;
		}
	}

	/* 描画リンクをセットする */
	pTask->m_pManager = m_pManager;

	if( m_pManager ){
		/* 登録 */
		m_pManager->m_renderTbl.entry( pTask );
	}

	/* 初期化フラグをチェックする */
	if( pUserData && pTask->m_flags & stTASK_FALGS_INITIALIZE ){
		/* 初期化 */
		pTask->initialize( pUserData );
		/* 初期化終了 */
		pTask->m_flags &= (StUInt32)(~stTASK_FALGS_INITIALIZE);
		//pTask->m_id = m_taskID;
		//m_taskID++;
	}
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void StTask::addChild( StTask* pTask, void* pUserData )
{
	StAssert( pTask != NULL, "追加した子タスクがNULLです。" );

	if( m_pChild )
	{
		/* 兄弟追加 */
		m_pChild->addBrother( pTask, pUserData );
	}
	else
	{
		/* 子供に追加 */
		m_pChild = pTask;

		/* 最後尾情報セット */
		m_pChild->m_pPrevBrother = pTask;

		/* 親セット */
		m_pChild->m_pParent = this;

		/* 描画リンクをセットする */
		pTask->m_pManager = m_pManager;

		if( m_pManager ){
			/* 登録 */
			m_pManager->m_renderTbl.entry( pTask );
		}

		/* 初期化フラグをチェックする */
		if( pUserData && pTask->m_flags & stTASK_FALGS_INITIALIZE ){
			/* 初期化 */
			pTask->initialize( pUserData );
			/* 初期化終了 */
			pTask->m_flags &= (StUInt32)(~stTASK_FALGS_INITIALIZE);
			//pTask->m_id = m_taskID;
			//m_taskID++;
		}
	}
}
/************************************************************************************************/
/*
 * 自分のタスクをとりはずす(自分より下の階層は、自分についたまま、兄弟はきちんとはずす)
 * 描画リンクも取り外す必要がある
 * @param		pTask				取り除く子タスクのポインタ
 */
/************************************************************************************************/
void StTask::detach()
{
	if( m_pParent )
	{
		if( m_pPrevBrother->m_pNextBrother == NULL ){
			/* 自分が長男 */

			/* 最後尾情報を更新 */
			if( m_pNextBrother ){
				/* 自分しかいない */
				m_pNextBrother->m_pPrevBrother = m_pPrevBrother;
			}
			m_pParent->m_pChild = m_pNextBrother;
		}
		else{
			/* つなぎ変え */
			if( m_pNextBrother ){
				m_pPrevBrother->m_pNextBrother = m_pNextBrother;
				m_pNextBrother->m_pPrevBrother = m_pPrevBrother;
			}
			else{
				/* 最後尾情報を更新する */
				m_pPrevBrother->m_pNextBrother = NULL;
				m_pParent->m_pChild->m_pPrevBrother = m_pPrevBrother;
			}
		}

		/* リセット */
		m_pNextBrother = NULL;
		m_pPrevBrother = NULL;

		/* 描画リストからとりはずしたりManagerをNULLにする必要がある */
		removeRenderLink( NULL );
	}
	else
	{
		/*(※未対応) もし自分がマネージャに登録されているルートで兄弟がいなかったらマネージャのルート情報を変更する必要がある */
		StTaskManager*		pManager = m_pManager;
		if( pManager ){
			pManager->setRootTask( NULL );
		}
	}
}
/************************************************************************************************/
/*
 * 描画リンクから取り外す
 */
/************************************************************************************************/
void StTask::removeRenderLink( StTask* pTask )
{
	StTask*		pTemp = pTask;

	/* マネージャがわからないと不可能 */
	if( m_pManager ){
		m_pManager->m_renderTbl.remove( this );
		m_pManager = NULL;

		if( m_pChild ){
			removeRenderLink( m_pChild );
		}

		if( m_pNextBrother ){
			removeRenderLink( m_pNextBrother );
		}
	}
}
/************************************************************************************************/
/*
 * 完全に切り離すdetachが必要
 * @param		pTask				取り除く子タスクのポインタ
 * 完全に切り離されて1つのタスクになる
 */
/************************************************************************************************/
StTask* StTask::cut()
{
	/* 取り外す */
	detach();

	/* すべての子供の親をNULLにする */
	StUInt32	index  = 0;
	StTask*		pChild = m_pChild;
	StTask*		pTask  = getChild( index );

	while( pTask )
	{
		pTask->m_pParent = NULL;
		++index;
		pTask = getChild( index );
	}

	m_pChild       = NULL;
	m_pPrevBrother = NULL;
	m_pNextBrother = NULL;

	return pChild;
}

/************************************************************************************************/
/*
 * 自分のタスクだけを削除する
 */
/************************************************************************************************/
void StTask::remove()
{
	/* 取り外す */
	detach();
	
	/* 削除フラグを立てる？でもその場合マネージャに登録されていないとだめなのでワークエリアを使用する？ */
	StWorkArea::push( this );
}
/************************************************************************************************/
/*
 * 自分のタスクだけを削除する
 */
/************************************************************************************************/
void StTask::destroy()
{
	/* 取り外す */
	detach();
	
	/* 削除フラグを立てる？でもその場合マネージャに登録されていないとだめなのでワークエリアを使用する？ */
	StWorkArea::push( this );
}
/************************************************************************************************/
/*
 * 描画リンクを変更する
 * @param		order				新しいオーダー
 */
/************************************************************************************************/
void StTask::changeRenderLink( StUInt32 order )
{
	/* この時点で描画リンクを変更 */
	if( m_pManager ){
		/* 取り除く */
		m_pManager->m_renderTbl.remove( this );
		/* 新たに追加 */
		m_order = order;
		m_pManager->m_renderTbl.entry( this );
	}
}
/************************************************************************************************/
/**
 * 
 */
/************************************************************************************************/
void StTask::setName( const StChar* string )
{
	strncpy( m_name, string, stTASK_NAME_LENGTH - 1 );

	/* null 文字セット */
	m_name[ stTASK_NAME_LENGTH - 1 ] = '\0';
}
/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void StTask::setID( StUInt32 id )
{
	m_id = id;
}
/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void StTask::setFlags( StUInt32 flags )
{
	m_flags = flags;
}
/************************************************************************************************/
/*
 *
 * 優先順位をセットする
 * @return							プライオリティ
 */
/************************************************************************************************/
void StTask::setPriority( StInt32 priority )
{
	m_priority.i = priority;
}
/************************************************************************************************/
/*
 * オーダをセット
 */
/************************************************************************************************/
void StTask::setOrder( StUInt32 order )
{
	m_order = order;
}
/************************************************************************************************/
/*
 * Z値をセットする
 * @param		z					z値
 */
/************************************************************************************************/
void StTask::setZsort( StReal z )
{
	m_priority.z = z;
}
/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
const StChar* StTask::getName()
{
	return m_name;
}
/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
StUInt32 StTask::getID() const
{
	return m_id;
}
/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
StUInt32 StTask::getFlags() const
{
	return	m_flags;
}
/************************************************************************************************/
/*
 * タスクのタイプを取得する
 */
/************************************************************************************************/
stTASK_TYPE StTask::getType() const
{
	return m_type;
}
/************************************************************************************************/
/*
 * 優先順位をセットする
 */
/************************************************************************************************/
STTASKPRIORITY StTask::getPriority() const
{
	return m_priority;
}
/************************************************************************************************/
/*
 * オーダをセット
 */
/************************************************************************************************/
StUInt32 StTask::getOrder() const
{
	return m_order;
}
/************************************************************************************************/
/*
 * 親タスクを取得する
 * @return		親タスクのポインタ
 */
/************************************************************************************************/
StTask* StTask::getParent()
{
	return m_pParent;
}
		
/************************************************************************************************/
/*
 * 長男タスクを取得する
 */
/************************************************************************************************/
StTask* StTask::getTopBrother()
{
	/* 最後尾を取得 */
	if( m_pParent ){
		return m_pParent->m_pChild;
	}
	else{
		/* ルートのとき */
		StTask*		pTop  = m_pPrevBrother;

		while( pTop->m_pPrevBrother->m_pNextBrother ){
				pTop = pTop->m_pPrevBrother;
		}

		return pTop;
	}

	return NULL;
}
/************************************************************************************************/
/*
 * 最後尾タスクを取得する
 */
/************************************************************************************************/
StTask* StTask::getEndBrother()
{
	StTask*		pTemp = m_pNextBrother;

	if( pTemp ){
		while( pTemp->m_pNextBrother ){

			pTemp = pTemp->m_pNextBrother;
		}

		return pTemp;
	}

	return this;
}

/************************************************************************************************/
/*
 * 兄タスクを取得する(ルートだったらわからない)
 */
/************************************************************************************************/
StTask* StTask::getPrevBrother()
{
	return m_pPrevBrother;
}
/************************************************************************************************/
/*
 * 弟タスクを取得する(ルートだったらわからない)
 */
/************************************************************************************************/
StTask* StTask::getNextBrother()
{
	return m_pNextBrother;
}
/************************************************************************************************/
/*
 * 兄弟タスクを取得する
 * @param		index				子タスクのインデックス
 * @return		子タスクのポインタ
 */
/************************************************************************************************/
StTask* StTask::getBrother( StUInt32 index )
{
	if( m_pParent ){
		return m_pParent->getChild( index );
	}

	/* ルートなので普通に数える */
	/* 長男まで行って数える必要がある */

	StUInt32	count = 1;
	StTask*		pTask = m_pNextBrother;

	while( pTask ){
		if( count == index ){
			return pTask;
		}

		pTask = pTask->m_pNextBrother;

		++count;
	}

	return NULL;
}
/************************************************************************************************/
/*
 * 子タスクの数を取得する
 * @return		子タスクの数
 */
/************************************************************************************************/
StUInt32 StTask::getNumBrother() const
{
	if( m_pParent ){
		return m_pParent->getNumChild();
	}

	/* ルートなので普通に数える */
	/* 長男まで行って数える必要がある */

	StUInt32	count = 1;
	StTask*		pTask = m_pNextBrother;

	while( pTask ){
		pTask = pTask->m_pNextBrother;

		++count;
	}

	return count;
}
/************************************************************************************************/
/*
 * 子タスクを取得する
 */
/************************************************************************************************/
StTask* StTask::getChild( StUInt32 index )
{
	StTask*		pTask = m_pChild;
	StUInt32	count = 0;

	while( pTask )
	{
		if( count == index ){
			return pTask;
		}

		pTask = pTask->m_pNextBrother;

		++count;
	}

	return	NULL;
}
/************************************************************************************************/
/*
 * 子タスクの数を取得する
 */
/************************************************************************************************/
StUInt32 StTask::getNumChild() const
{
	StTask*		pTask = m_pChild;
	StUInt32	count = 0;

	while( pTask )
	{
		pTask = pTask->m_pNextBrother;

		++count;
	}

	return	count;
}
/************************************************************************************************/
/*
 * ID検索
 */
/************************************************************************************************/
StTask* StTask::find( StUInt32 id )
{
	STFINDPARAM		param;

	param.pTask = NULL;
	param.id	= id;

	allChildCallback( m_pChild, KsTaskFindID, (void*)(&param) );
	
	return param.pTask;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
StTask* StTask::find( StChar* name )
{
	STFINDPARAM		param;

	param.pTask = NULL;
	param.pName = name;

	allChildCallback( m_pChild, KsTaskFindName, (void*)(&param) );
	
	return param.pTask;
}

/************************************************************************************************/
/*
 * すべての子供に適用
 */
/************************************************************************************************/
StTask* StTask::allChildCallback( StTask* pTask, StTaskCallback callback, void* pUserData )
{
	if( pTask ){
		if( !callback( pTask, pUserData ) ){ return NULL; }

		/* 子タスク */
		if( pTask->m_pChild ){
			allChildCallback( pTask->m_pChild, callback, pUserData );
		}

		/* 兄弟タスク */
		if( pTask->m_pNextBrother ){
			allChildCallback( pTask->m_pNextBrother, callback, pUserData );
		}
	}

	return NULL;
}

