/************************************************************************************************/
/** 
 * @file		KsOT.cpp
 * @brief		�I�[�_�����O�e�[�u��
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsOT.h"
#include "KsTaskBase.h"
#include "KsCameraObject.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/* �\�[�g�������R�[���o�b�N�łł���悤�ɂ��� */

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

	/* ��_�̒l */
	val = pSortTbl[ ( left + right ) / 2 ]->getPriority().i;

	i = left;
	j = right;

	/* �\�[�g���� */
	while( 1 )
	{
		/* ��r(����) */
		while ( pSortTbl[ i ]->getPriority().i > val ) { i++; }

		/* ��r(�E��) */
		while ( val > pSortTbl[ j ]->getPriority().i ) { j--; }

		/* ����ւ� */
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

	/* �ċA���� */
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

	/* ��_�̒l */
	val = pSortTbl[ ( left + right ) / 2 ]->getPriority().z;

	i = left;
	j = right;

	/* �\�[�g���� */
	while( 1 )
	{
		/* ��r(����) */
		while ( pSortTbl[ i ]->getPriority().z > val ) { i++; }

		/* ��r(�E��) */
		while ( val > pSortTbl[ j ]->getPriority().z ) { j--; }

		/* ����ւ� */
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

	/* �ċA���� */
	if(  left < (i-1) ) { KsTaskQuickSort( pSortTbl, left, i-1   ); }
	if( (j+1) < right ) { KsTaskQuickSort( pSortTbl, j+1,  right ); }
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsOT_List::KsOT_List() : m_flags( 0 ), m_pTop( 0 ), m_pEnd( 0 ), m_count( 0 )
{
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsOT_List::~KsOT_List()
{
}

/************************************************************************************************/
/*
 * �����N�Ƀ^�X�N��ǉ�����
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
	// 2005/5/13 �ǉ� ����Ń`�F�b�N���Ȃ��ƕ`�惊���N�ɓo�^����Ă��Ȃ��^�X�N���͂������Ƃ��Ă��������Ȃ�
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
 * �^�X�N�̃v���C�I���e�B�Ń\�[�g����
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
 * �^�X�N��Z�l�Ń\�[�g����
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
		/* �`��t���O���`�F�b�N���� */
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
		/* �`��t���O���`�F�b�N���� */
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
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsOT::KsOT() : m_flags( 0 )
{
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsOT::~KsOT()
{
}

/************************************************************************************************/
/*
 * �^�X�N��o�^����
 */
/************************************************************************************************/
KsBool KsOT::entry( KsTaskBase* pTask )
{
//	KsAssert( pTask != NULL, "�o�^�^�X�N��NULL�ł�!!" );
//	KsAssert( pTask->getOrder() < ksOT_ORDER_MAX, "�o�^�^�X�N�̃I�[�_�[���͈͊O�ł�!!" );

	/* �t���O���`�F�b�N���� */

	/* �J�����̃t���O�������Ă����� */
	if( pTask->getType() == ksTASK_TYPE_CAMERA )
	{
		/* �ǉ� */
		m_order[ ksOT_ORDER_CAMERA ].add( pTask );
	}
	else
	{
		/* �ǉ� */
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
//	KsAssert( pTask != NULL, "�o�^�^�X�N��NULL�ł�!!" );
//	KsAssert( pTask->getOrder() < ksOT_ORDER_MAX, "�o�^�^�X�N�̃I�[�_�[���͈͊O�ł�!!" );

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
	/* �J���������N���g�p�����`����@�𗘗p���� */
	
	/*
	 * ��{�I�ɃJ�����̏ꍇ�́A�I�[�_�[�̊e�r�b�g���`�悷��I�[�_�[�̂ǂ�Ȃ̂�������
	 */
	if( m_order[ ksOT_ORDER_CAMERA ].getCount() )
	{
		/* �J���������N */
		cameraRender( pParam );
	}
	else
	{
		/* �f�t�H���g */
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
	/* �`�悷�邩�ǂ������`�F�b�N���� */
	if( !(m_order[ order ].getFlags() & ksOT_FLAGS_STOP) )
	{
		if( m_order[ order ].getFlags() & ksOT_FLAGS_SORT_USE )
		{
			if( m_order[ order ].getFlags() & ksOT_FLAGS_PRIORITYSORT )
			{
				/* �v���C�I���e�B�\�[�g���� */
				m_order[ order ].sort();
			}
			else if( m_order[ order ].getFlags() & ksOT_FLAGS_ZSORT )
			{
				/* Z�\�[�g���� */
				m_order[ order ].zsort();
			}

			/* �\�[�g�e�[�u������`�� */
			m_order[ order ].sortRender( pParam );
		}
		else
		{
			/* �m�[�}���`�� */
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

	/* ���̃J������`�悷�邩�̃t���O�� */
	/* �\�[�g���邩�ǂ����̃t���O���`�F�b�N����K�v������ */
	while( pCamera )
	{
		/* �`�悷�邩�ǂ����̃t���O���`�F�b�N */
		if( !( pCamera->getFlags() & ksTASK_FALGS_RENDER_HIDE ) )
		{
			KsUInt32	order = getOrderMax();

			/* ���ۂ́A������ */
			pCamera->beginRender();

			while( order )
			{
				--order;

				if( pCamera->getOrder() & (1<<order) )
				{
					/* �\�[�g���邩�ǂ����̃t���O���`�F�b�N */
					orderRender( order, pParam );
				}
			}

			/* ���ۂ́A������ */
			pCamera->endRender();
			// �������ق�������
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
	/* �`�揈�� */
	for( KsInt32 i=((KsInt32)getOrderMax())-1; i>=0 ; i-- )
	{
		orderRender( (KsUInt32)i, pParam );
	}
}

