/************************************************************************************************/
/** 
 * @file		KsTaskBase.cpp
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
#include "KsTaskBase.h"
#include "KsTaskManager.h"
#include "KsWorkArea.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * タスク検索コールバック用パラメータ
 */
/************************************************************************************************/
typedef struct _KSFINDPARAM
{
	KsUInt32			id;
	const KsChar*		pName;
	KsTaskBase*				pTask;

}KSFINDPARAM;

/************************************************************************************************/
/*
 * 名前検索
 */
/************************************************************************************************/
static void* KsTaskFindName( KsTaskBase* pTask, void* pUserData )
{
	KSFINDPARAM*	pParam = (KSFINDPARAM*)pUserData;

	if( strncmp( pTask->getName(), pParam->pName, ksTASK_NAME_LENGTH ) == 0 )
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
static void* KsTaskFindID( KsTaskBase* pTask, void* pUserData )
{
	KSFINDPARAM*	pParam = (KSFINDPARAM*)pUserData;

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
void KsTaskDelete( KsTaskBase* pTask )
{
	KsTaskBase*		pChild   = NULL;
	KsTaskBase*		pBrother = NULL;

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
			KsTaskDelete( pChild );
		}

		/* 兄弟タスク */
		if( pBrother ){
			KsTaskDelete( pBrother );
		}

		/* ワークエリア使用かチェックする */
		if( !( pTask->getFlags() & ksTASK_FLAGS_USE_WORKAREA ) ){
			delete pTask;
		}
	}
}

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsTaskBase::KsTaskBase() :	m_id( 0 ),
					m_flags( ksTASK_FALGS_INITIALIZE ),
					m_order( ksTASK_ORDER_DEFAULT ),
					m_type( ksTASK_TYPE_BASE ),
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
 * コンストラクタ
 * @param	order	描画オーダー
 */
/************************************************************************************************/
KsTaskBase::KsTaskBase( KsUInt32 order )
	: m_id( 0 )
	, m_flags( ksTASK_FALGS_INITIALIZE )
	, m_order( order )
	, m_type( ksTASK_TYPE_BASE )
	, m_pParent( 0 )
	, m_pPrevBrother( 0 )
	, m_pNextBrother( 0 )
	, m_pChild( 0 )
	, m_pPrev( 0 )
	, m_pNext( 0 )
	, m_pManager( 0 )
{
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsTaskBase::~KsTaskBase()
{
}
/************************************************************************************************/
/*
 * 長男の先頭ポインタに最後尾のポインタを入れておく
 */
/************************************************************************************************/
void KsTaskBase::addBrother( KsTaskBase* pTask, void* pUserData )
{
	/* 高速にする */
	if( m_pParent ){
		/* 最後の兄弟を取得 */
		/* このタスクの兄弟になるはずなので、m_pParent->m_pChildがNULLであることはないはず */
		KsTaskBase*		pLast = m_pParent->m_pChild->m_pPrevBrother;

		/* 最後尾保存用 */
		m_pParent->m_pChild->m_pPrevBrother = pTask;

		/* リンク */
		pLast->m_pNextBrother = pTask;
		pTask->m_pPrevBrother = pLast;

		/* 親セット */
		pTask->m_pParent = m_pParent;
	}
	else{
		KsTaskBase*		pTop = getTopBrother();

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
	if( pUserData && pTask->m_flags & ksTASK_FALGS_INITIALIZE ){
		/* 初期化 */
		pTask->initialize( pUserData );
		/* 初期化終了 */
		pTask->m_flags &= (KsUInt32)(~ksTASK_FALGS_INITIALIZE);
		//pTask->m_id = m_taskID;
		//m_taskID++;
	}
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsTaskBase::addChild( KsTaskBase* pTask, void* pUserData )
{
	//KsAssert( pTask != NULL, "追加した子タスクがNULLです。" );

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
		if( pUserData && pTask->m_flags & ksTASK_FALGS_INITIALIZE ){
			/* 初期化 */
			pTask->initialize( pUserData );
			/* 初期化終了 */
			pTask->m_flags &= (KsUInt32)(~ksTASK_FALGS_INITIALIZE);
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
void KsTaskBase::detach()
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
		KsTaskManager*		pManager = m_pManager;
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
void KsTaskBase::removeRenderLink( KsTaskBase* pTask )
{
	KsTaskBase*		pTemp = pTask;

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
KsTaskBase* KsTaskBase::cut()
{
	/* 取り外す */
	detach();

	/* すべての子供の親をNULLにする */
	KsUInt32	index  = 0;
	KsTaskBase*		pChild = m_pChild;
	KsTaskBase*		pTask  = getChild( index );

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
void KsTaskBase::remove()
{
	/* 取り外す */
	detach();
	
	/* 削除フラグを立てる？でもその場合マネージャに登録されていないとだめなのでワークエリアを使用する？ */
	KsWorkArea::push( this );
}
/************************************************************************************************/
/*
 * 自分のタスクだけを削除する
 */
/************************************************************************************************/
void KsTaskBase::destroy()
{
	/* 取り外す */
	detach();
	
	/* 削除フラグを立てる？でもその場合マネージャに登録されていないとだめなのでワークエリアを使用する？ */
	KsWorkArea::push( this );
}
/************************************************************************************************/
/*
 * 描画リンクを変更する
 * @param		order				新しいオーダー
 */
/************************************************************************************************/
void KsTaskBase::changeRenderLink( KsUInt32 order )
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
void KsTaskBase::setName( const KsChar* string )
{
	strncpy( m_name, string, ksTASK_NAME_LENGTH - 1 );

	/* null 文字セット */
	m_name[ ksTASK_NAME_LENGTH - 1 ] = '\0';
}
/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsTaskBase::setID( KsUInt32 id )
{
	m_id = id;
}
/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsTaskBase::setFlags( KsUInt32 flags )
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
void KsTaskBase::setPriority( KsInt32 priority )
{
	m_priority.i = priority;
}
/************************************************************************************************/
/*
 * オーダをセット
 */
/************************************************************************************************/
void KsTaskBase::setOrder( KsUInt32 order )
{
	m_order = order;
}
/************************************************************************************************/
/*
 * Z値をセットする
 * @param		z					z値
 */
/************************************************************************************************/
void KsTaskBase::setZsort( KsReal z )
{
	m_priority.z = z;
}
/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
const KsChar* KsTaskBase::getName()
{
	return m_name;
}
/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KsUInt32 KsTaskBase::getID() const
{
	return m_id;
}
/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KsUInt32 KsTaskBase::getFlags() const
{
	return	m_flags;
}
/************************************************************************************************/
/*
 * タスクのタイプを取得する
 */
/************************************************************************************************/
ksTASK_TYPE KsTaskBase::getType() const
{
	return m_type;
}
/************************************************************************************************/
/*
 * 優先順位をセットする
 */
/************************************************************************************************/
KsTaskPRIORITY KsTaskBase::getPriority() const
{
	return m_priority;
}
/************************************************************************************************/
/*
 * オーダをセット
 */
/************************************************************************************************/
KsUInt32 KsTaskBase::getOrder() const
{
	return m_order;
}
/************************************************************************************************/
/*
 * 親タスクを取得する
 * @return		親タスクのポインタ
 */
/************************************************************************************************/
KsTaskBase* KsTaskBase::getParent()
{
	return m_pParent;
}
		
/************************************************************************************************/
/*
 * 長男タスクを取得する
 */
/************************************************************************************************/
KsTaskBase* KsTaskBase::getTopBrother()
{
	/* 最後尾を取得 */
	if( m_pParent ){
		return m_pParent->m_pChild;
	}
	else{
		/* ルートのとき */
		KsTaskBase*		pTop  = m_pPrevBrother;

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
KsTaskBase* KsTaskBase::getEndBrother()
{
	KsTaskBase*		pTemp = m_pNextBrother;

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
KsTaskBase* KsTaskBase::getPrevBrother()
{
	return m_pPrevBrother;
}
/************************************************************************************************/
/*
 * 弟タスクを取得する(ルートだったらわからない)
 */
/************************************************************************************************/
KsTaskBase* KsTaskBase::getNextBrother()
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
KsTaskBase* KsTaskBase::getBrother( KsUInt32 index )
{
	if( m_pParent ){
		return m_pParent->getChild( index );
	}

	/* ルートなので普通に数える */
	/* 長男まで行って数える必要がある */

	KsUInt32	count = 1;
	KsTaskBase*		pTask = m_pNextBrother;

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
KsUInt32 KsTaskBase::getNumBrother() const
{
	if( m_pParent ){
		return m_pParent->getNumChild();
	}

	/* ルートなので普通に数える */
	/* 長男まで行って数える必要がある */

	KsUInt32	count = 1;
	KsTaskBase*		pTask = m_pNextBrother;

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
KsTaskBase* KsTaskBase::getChild( KsUInt32 index )
{
	KsTaskBase*		pTask = m_pChild;
	KsUInt32	count = 0;

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
KsUInt32 KsTaskBase::getNumChild() const
{
	KsTaskBase*		pTask = m_pChild;
	KsUInt32	count = 0;

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
KsTaskBase* KsTaskBase::find( KsUInt32 id )
{
	KSFINDPARAM		param;

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
KsTaskBase* KsTaskBase::find( const KsChar* name )
{
	KSFINDPARAM		param;

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
KsTaskBase* KsTaskBase::allChildCallback( KsTaskBase* pTask, KsTaskCallback callback, void* pUserData )
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

