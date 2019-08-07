/************************************************************************************************/
/** 
 * @file		KsDrawList.cpp
 * @brief		�`�揈��
 * @author		Tsukasa Kato
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * �R���X�g���N�^
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
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsDrawList::~KsDrawList()
{
}

/************************************************************************************************/
/*
 * �`��^�X�N��ǉ�����
 * @param		pDraw				�`��^�X�N
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
			// �`��v���C�I���e�B���ꏏ�Ȃ̂Ń��X�g�ɒǉ�����
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
				// ���X�g�ɒǉ�����
				if( pTemp == m_pDrawLast )
				{
					m_pDrawLast->m_pDrawNext = pDraw;

					pDraw->m_pDrawPrev = m_pDrawLast;
					pDraw->m_pDrawNext = NULL;

					m_pDrawLast = pDraw;
				}
				else
				{
					// �r���ɒǉ�����
					pDraw->m_pDrawPrev = pTemp;
					pDraw->m_pDrawNext = pTemp->m_pDrawNext;
					pTemp->m_pDrawNext = pDraw;
				}

			}
			else
			{
				// �擪�ɒǉ�����
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
 * �`��^�X�N����菜��
 * @param		pDraw				�`��^�X�N
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
 * �`��^�X�N����菜��
 * @param		pUpdate				�`��^�X�N
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
	


