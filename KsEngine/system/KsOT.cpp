/************************************************************************************************/
/** 
 * @file		KsOT.cpp
 * @brief		オーダリングテーブル
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsOT.h"
#include "KsTaskBase.h"
#include "KsCameraObject.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/* ソート部分をコールバックでできるようにする */

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsTaskQuickSort( KsTaskBase** pSortTbl, KsInt32 left, KsInt32 right )
{
	KsTaskBase*			pTemp;
	KsInt32			i, j;
	KsInt32			val;

	/* 基点の値 */
	val = pSortTbl[ ( left + right ) / 2 ]->getPriority().i;

	i = left;
	j = right;

	/* ソートする */
	while( 1 )
	{
		/* 比較(左側) */
		while ( pSortTbl[ i ]->getPriority().i > val ) { i++; }

		/* 比較(右側) */
		while ( val > pSortTbl[ j ]->getPriority().i ) { j--; }

		/* 入れ替え */
		if( i < j )
		{
			pTemp         = pSortTbl[ i ];
			pSortTbl[ i ] = pSortTbl[ j ];
			pSortTbl[ j ] = pTemp;
			i++;
			j--;
		}
		else{ break; }
	}

	/* 再帰処理 */
	if(  left < (i-1) ) 
	{
		KsTaskQuickSort( pSortTbl, left, i-1   );
	}
	if( (j+1) < right ) 
	{
		KsTaskQuickSort( pSortTbl, j+1,  right );
	}
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsTaskZSort( KsTaskBase** pSortTbl, KsInt32 left, KsInt32 right )
{
	KsTaskBase*			pTemp;
	KsInt32			i, j;
	KsReal			val;

	/* 基点の値 */
	val = pSortTbl[ ( left + right ) / 2 ]->getPriority().z;

	i = left;
	j = right;

	/* ソートする */
	while( 1 )
	{
		/* 比較(左側) */
		while ( pSortTbl[ i ]->getPriority().z > val ) { i++; }

		/* 比較(右側) */
		while ( val > pSortTbl[ j ]->getPriority().z ) { j--; }

		/* 入れ替え */
		if( i < j )
		{
			pTemp         = pSortTbl[ i ];
			pSortTbl[ i ] = pSortTbl[ j ];
			pSortTbl[ j ] = pTemp;
			i++;
			j--;
		}
		else{ break; }
	}

	/* 再帰処理 */
	if(  left < (i-1) ) { KsTaskQuickSort( pSortTbl, left, i-1   ); }
	if( (j+1) < right ) { KsTaskQuickSort( pSortTbl, j+1,  right ); }
}

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsOT_List::KsOT_List() : m_flags( 0 ), m_pTop( 0 ), m_pEnd( 0 ), m_count( 0 )
{
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsOT_List::~KsOT_List()
{
}

/************************************************************************************************/
/*
 * リンクにタスクを追加する
 */
/************************************************************************************************/
void KsOT_List::add( KsTaskBase* pTask )
{
//	KsAssert( pTask != NULL, "OT add Task NULL" );
//	KsAssert( pTask->m_pNext, "OT add Next Task Not NULL" );

	if( m_pTop )
	{
		m_pEnd->m_pNext = pTask;
		pTask->m_pPrev = m_pEnd;
		//pTask->m_pNext = NULL;
		m_pEnd = pTask;
	}
	else
	{
		m_pTop = m_pEnd = pTask;
	}

	++m_count;
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsOT_List::remove( KsTaskBase* pTask )
{
	// 2005/5/13 追加 これでチェックしないと描画リンクに登録されていないタスクをはずそうとしておかしくなる
	if( (pTask->m_pPrev == NULL) && (pTask->m_pNext == NULL) )
	{
		if( m_pTop == pTask && m_pEnd == pTask )
		{
			m_pTop = m_pEnd = NULL;
			m_count = 0;
		}
		return;
	}

	if( m_pTop == pTask )
	{
		if( m_pEnd == pTask )
		{
			m_pTop = NULL;
			m_pEnd = NULL;
		}
		else
		{
			pTask->m_pNext->m_pPrev = NULL;
			m_pTop = pTask->m_pNext;
		}
	}
	else if( m_pEnd == pTask )
	{
		pTask->m_pPrev->m_pNext = NULL;
		m_pEnd = pTask->m_pPrev;
	}
	else
	{
		if( pTask->m_pPrev ){ pTask->m_pPrev->m_pNext = pTask->m_pNext; }
		if( pTask->m_pNext ){ pTask->m_pNext->m_pPrev = pTask->m_pPrev; }
	}

	pTask->m_pPrev = NULL;
	pTask->m_pNext = NULL;

	if( !--m_count )
	{
		m_pTop = m_pEnd = NULL;
	}
}
/************************************************************************************************/
/*
 * タスクのプライオリティでソートする
 */
/************************************************************************************************/
void KsOT_List::sort()
{
	KsTaskBase*		pTask = m_pTop;
	KsInt32		count = 0;

	while( pTask )
	{
		m_sortTbl[ count ] = pTask;
		count++;
		pTask = pTask->m_pNext;
	}

	if( count == 0 )
	{
		return;
	}

	KsTaskQuickSort( m_sortTbl, 0, (KsInt32)(m_count-1) );
}

/************************************************************************************************/
/*
 * タスクのZ値でソートする
 */
/************************************************************************************************/
void KsOT_List::zsort()
{
	KsTaskZSort( m_sortTbl, 0, (KsInt32)m_count );
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsOT_List::normalRender( void* pParam )
{
	KsTaskBase*		pTask = m_pTop;

	while( pTask )
	{
		/* 描画フラグをチェックする */
		if( !( pTask->getFlags() & ksTASK_FALGS_RENDER_HIDE ) )
		{
			pTask->render( pParam );
		}

		pTask = pTask->m_pNext;
	}
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsOT_List::sortRender( void* pParam )
{
	for( KsUInt32 i=0; i<m_count; i++ )
	{
		/* 描画フラグをチェックする */
		if( !( m_sortTbl[ i ]->getFlags() & ksTASK_FALGS_RENDER_HIDE ) )
		{
			m_sortTbl[ i ]->render( pParam );
		}
	}
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsOT_List::clear()
{
	m_pTop  = NULL;
	m_pEnd  = NULL;
	m_count = 0;
}

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsOT::KsOT() : m_flags( 0 )
{
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsOT::~KsOT()
{
}

/************************************************************************************************/
/*
 * タスクを登録する
 */
/************************************************************************************************/
KsBool KsOT::entry( KsTaskBase* pTask )
{
//	KsAssert( pTask != NULL, "登録タスクがNULLです!!" );
//	KsAssert( pTask->getOrder() < ksOT_ORDER_MAX, "登録タスクのオーダーが範囲外です!!" );

	/* フラグをチェックする */

	/* カメラのフラグが立っていたら */
	if( pTask->getType() == ksTASK_TYPE_CAMERA )
	{
		/* 追加 */
		m_order[ ksOT_ORDER_CAMERA ].add( pTask );
	}
	else
	{
		/* 追加 */
		m_order[ pTask->m_order ].add( pTask );
	}

	return ksTRUE;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsOT::remove( KsTaskBase* pTask )
{
//	KsAssert( pTask != NULL, "登録タスクがNULLです!!" );
//	KsAssert( pTask->getOrder() < ksOT_ORDER_MAX, "登録タスクのオーダーが範囲外です!!" );

	if( pTask->getType() == ksTASK_TYPE_CAMERA )
	{
		m_order[ ksOT_ORDER_CAMERA ].remove( pTask );
	}
	else
	{
		m_order[ pTask->m_order ].remove( pTask );
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsOT::clear()
{
	for( KsUInt32 i=0; i<getOrderMax()+1; i++ )
	{
		m_order[ i ].clear();
	}
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsOT::render( void* pParam )
{
	/* カメラリンクを使用した描画方法を利用する */
	
	/*
	 * 基本的にカメラの場合は、オーダーの各ビットが描画するオーダーのどれなのかを示す
	 */
	if( m_order[ ksOT_ORDER_CAMERA ].getCount() )
	{
		/* カメラリンク */
		cameraRender( pParam );
	}
	else
	{
		/* デフォルト */
		defaultRender( pParam );
	}
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsOT::orderRender( KsUInt32 order, void* pParam )
{
	/* 描画するかどうかをチェックする */
	if( !(m_order[ order ].getFlags() & ksOT_FLAGS_STOP) )
	{
		if( m_order[ order ].getFlags() & ksOT_FLAGS_SORT_USE )
		{
			if( m_order[ order ].getFlags() & ksOT_FLAGS_PRIORITYSORT )
			{
				/* プライオリティソートする */
				m_order[ order ].sort();
			}
			else if( m_order[ order ].getFlags() & ksOT_FLAGS_ZSORT )
			{
				/* Zソートする */
				m_order[ order ].zsort();
			}

			/* ソートテーブルから描画 */
			m_order[ order ].sortRender( pParam );
		}
		else
		{
			/* ノーマル描画 */
			m_order[ order ].normalRender( pParam );
		}
	}
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsOT::cameraRender( void* pParam )
{
	KsCameraObject*	pCamera = (KsCameraObject*)m_order[ ksOT_ORDER_CAMERA ].getTop();

	/* このカメラを描画するかのフラグと */
	/* ソートするかどうかのフラグをチェックする必要がある */
	while( pCamera )
	{
		/* 描画するかどうかのフラグをチェック */
		if( !( pCamera->getFlags() & ksTASK_FALGS_RENDER_HIDE ) )
		{
			KsUInt32	order = getOrderMax();

			/* 実際は、ここに */
			pCamera->beginRender();

			while( order )
			{
				--order;

				if( pCamera->getOrder() & (1<<order) )
				{
					/* ソートするかどうかのフラグをチェック */
					orderRender( order, pParam );
				}
			}

			/* 実際は、ここに */
			pCamera->endRender();
			// あったほうがいい
		}

		pCamera = (KsCameraObject*)pCamera->m_pNext;
	}
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsOT::defaultRender( void* pParam )
{
	/* 描画処理 */
	for( KsInt32 i=((KsInt32)getOrderMax())-1; i>=0 ; i-- )
	{
		orderRender( (KsUInt32)i, pParam );
	}
}

