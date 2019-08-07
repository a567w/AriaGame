/************************************************************************************************/
/** 
 * @file		KsDrawList.cpp
 * @brief		描画処理
 * @author		Tsukasa Kato
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsDrawList::KsDrawList()
	: m_isActive( 0 )
	, m_pDrawRoot( 0 )
	, m_pDrawLast( 0 )
	, m_pDrawManager( 0 )
{
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsDrawList::~KsDrawList()
{
}

/************************************************************************************************/
/*
 * 描画タスクを追加する
 * @param		pDraw				描画タスク
 */
/************************************************************************************************/
void KsDrawList::add( KsDraw* pDraw )
{
	if( NULL == m_pDrawRoot && NULL == m_pDrawLast )
	{
		m_pDrawRoot = pDraw;
		m_pDrawLast = pDraw;
	}
	else
	{
		if( m_pDrawRoot->getDrawPriority() == m_pDrawLast->getDrawPriority() )
		{
			// 描画プライオリティが一緒なのでラストに追加する
			m_pDrawLast->m_pDrawNext = pDraw;

			pDraw->m_pDrawPrev = m_pDrawLast;
			pDraw->m_pDrawNext = NULL;

			m_pDrawLast = pDraw;
		}
		else
		{
			KsDraw* pTemp = m_pDrawLast;

			while( pTemp )
			{
				if( pTemp->getDrawPriority() <= pDraw->getDrawPriority() )
				{
					break;
				}
				pTemp = pTemp->m_pDrawPrev;
			}

			if( pTemp )
			{
				// ラストに追加する
				if( pTemp == m_pDrawLast )
				{
					m_pDrawLast->m_pDrawNext = pDraw;

					pDraw->m_pDrawPrev = m_pDrawLast;
					pDraw->m_pDrawNext = NULL;

					m_pDrawLast = pDraw;
				}
				else
				{
					// 途中に追加する
					pDraw->m_pDrawPrev = pTemp;
					pDraw->m_pDrawNext = pTemp->m_pDrawNext;
					pTemp->m_pDrawNext = pDraw;
				}

			}
			else
			{
				// 先頭に追加する
				m_pDrawRoot->m_pDrawPrev = pDraw;

				pDraw->m_pDrawPrev = NULL;
				pDraw->m_pDrawNext = m_pDrawRoot;

				m_pDrawRoot = pDraw;

			}
		}
	}
}

/************************************************************************************************/
/*
 * 描画タスクを取り除く
 * @param		pDraw				描画タスク
 */
/************************************************************************************************/
void KsDrawList::remove( KsDraw* pDraw )
{
	KsDraw* pTemp = m_pDrawLast;

	while( pTemp )
	{
		if( pTemp->getDrawPriority() <= pDraw->getDrawPriority() )
		{
			break;
		}
		pTemp = pTemp->m_pDrawPrev;
	}
}


/************************************************************************************************/
/*
 * 描画タスクを取り除く
 * @param		pUpdate				描画タスク
 */
/************************************************************************************************/
void KsDrawList::draw( void* pParam )
{
	KsDraw* pDraw = m_pDrawLast;

	while( pDraw )
	{
		pDraw->draw( pParam );

		pDraw = pDraw->m_pDrawPrev;
	}
}
	


