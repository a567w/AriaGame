/************************************************************************************************/
/** 
 * @file		KsUpdateList.cpp
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
KsUpdateList::KsUpdateList()
	: m_isActive( 0 )
	, m_pUpdateRoot( 0 )
	, m_pUpdateLast( 0 )
	, m_pUpdateManager( 0 )
{
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsUpdateList::~KsUpdateList()
{
}

/************************************************************************************************/
/*
 * �`��^�X�N��ǉ�����
 * @param		pUpdate				�`��^�X�N
 */
/************************************************************************************************/
void KsUpdateList::add( KsUpdate* pUpdate )
{
	if( NULL == m_pUpdateRoot && NULL == m_pUpdateLast )
	{
		m_pUpdateRoot = pUpdate;
		m_pUpdateLast = pUpdate;
	}
	else
	{
		if( m_pUpdateRoot->getUpdatePriority() == m_pUpdateLast->getUpdatePriority() )
		{
			// �`��v���C�I���e�B���ꏏ�Ȃ̂Ń��X�g�ɒǉ�����
			m_pUpdateLast->m_pUpdateNext = pUpdate;

			pUpdate->m_pUpdatePrev = m_pUpdateLast;
			pUpdate->m_pUpdateNext = NULL;

			m_pUpdateLast = pUpdate;
		}
		else
		{
			KsUpdate* pTemp = m_pUpdateLast;

			while( pTemp )
			{
				if( pTemp->getUpdatePriority() <= pUpdate->getUpdatePriority() )
				{
					break;
				}
				pTemp = pTemp->m_pUpdatePrev;
			}

			if( pTemp )
			{
				// ���X�g�ɒǉ�����
				if( pTemp == m_pUpdateLast )
				{
					m_pUpdateLast->m_pUpdateNext = pUpdate;

					pUpdate->m_pUpdatePrev = m_pUpdateLast;
					pUpdate->m_pUpdateNext = NULL;

					m_pUpdateLast = pUpdate;
				}
				else
				{
					// �r���ɒǉ�����
					pUpdate->m_pUpdatePrev = pTemp;
					pUpdate->m_pUpdateNext = pTemp->m_pUpdateNext;
					pTemp->m_pUpdateNext = pUpdate;
				}

			}
			else
			{
				// �擪�ɒǉ�����
				m_pUpdateRoot->m_pUpdatePrev = pUpdate;

				pUpdate->m_pUpdatePrev = NULL;
				pUpdate->m_pUpdateNext = m_pUpdateRoot;

				m_pUpdateRoot = pUpdate;

			}
		}
	}
}

/************************************************************************************************/
/*
 * �`��^�X�N����菜��
 * @param		pUpdate				�`��^�X�N
 */
/************************************************************************************************/
void KsUpdateList::remove( KsUpdate* pUpdate )
{
}

/************************************************************************************************/
/*
 * �`��^�X�N����菜��
 * @param		pUpdate				�`��^�X�N
 */
/************************************************************************************************/
void KsUpdateList::update( void* pParam )
{
	KsUpdate* pUpdate = m_pUpdateLast;

	while( pUpdate )
	{
		pUpdate->update( pParam );

		pUpdate = pUpdate->m_pUpdatePrev;
	}
}
	
