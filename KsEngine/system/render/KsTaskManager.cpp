/************************************************************************************************/
/** 
 * @file		KsTaskManager.cpp
 * @brief		��{�^�X�N�}�l�[�W��
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsTaskManager.h"
#include "KsWorkArea.h"

#ifndef _MASTER
	#include "KsTimer.h"
#endif

//KsInt32	KsTaskManager::m_taskID = 0;

/*==============================================================================================*/
/*                                     << ��` >>                                               */
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

		/* �`�惊���N�������܂��́A�Z�b�g */
		if( pTask->m_pManager ){
			/* �`�惊���N���� */
			pTask->m_pManager->m_renderTbl.entry( pTask );
		}
		else{
			/* �`�惊���N������ */
			pTask->m_pPrev = NULL;
			pTask->m_pNext = NULL;
		}

		return pTask;
	}

	return NULL;
}
/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsTaskManager::KsTaskManager() : m_pRootTask( 0 )
{
}
/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsTaskManager::~KsTaskManager()
{
	/* ���ׂẴ����N��j������ */
	kill( m_pRootTask, this );
}
/************************************************************************************************/
/*
 * ���ׂč폜
 */
/************************************************************************************************/
void KsTaskManager::allKill( void* pParam )
{
	/* ���ׂẴ����N��j������ */
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

	/* �`�惊���N���N���A(���̂Ƃ��`�惊���N�����ŃJ���������N�́A�N���A����Ȃ�) */
	m_renderTbl.clear();

	/* NULL���Z�b�g */
	allCallback( setManagerCallback, NULL );

	pOldTask    = m_pRootTask;
	m_pRootTask = pTask;

	/* �}�l�[�W���̃|�C���^���Z�b�g���� */
	allCallback( setManagerCallback, this );

	return pOldTask;
}
/************************************************************************************************/
/*
 * ���s����
 */
/************************************************************************************************/
void KsTaskManager::execute( void* pParam )
{
	taskExecute( m_pRootTask, pParam );
}
/************************************************************************************************/
/*
 * �`�悷��
 */
/************************************************************************************************/
void KsTaskManager::render( void* pParam )
{
	/* �`�揈�� */
	begineRender();

	m_renderTbl.render( pParam );

	endRender();
}
/************************************************************************************************/
/*
 * �X�V����
 */
/************************************************************************************************/
void KsTaskManager::update( void* pParam )
{
	/* �폜�t���O�������Ă����� */
	for( KsInt32 i=0; i<KsWorkArea::m_count; i++ ){
		kill( KsWorkArea::m_work[ i ], pParam );
	}

	KsWorkArea::clear();
}
/************************************************************************************************/
/*
 * �w��I�[�_�[�����X�g�b�v������Ƃ��̋@�\���ق���
 */
/************************************************************************************************/
void KsTaskManager::run( void* pParam )
{
#ifndef _MASTER
	/* ���Ԃ������� */
	KsTimer::checkStart();
#endif

	/* ���s */
	execute( pParam );

#ifndef _MASTER
	/* CPU���Ԃ𑪒� */
	KsTimer::checkCpu();
#endif

	/* �`��(�J�����̕`��͂�������) */
	render( pParam );

#ifndef _MASTER
	/* �`�掞�Ԃ𑪒� */
	KsTimer::checkGpu();
#endif

	/* �X�V */
	update( pParam );
	
#ifndef _MASTER
	/* �g�[�^�����Ԃ𑪒� */
	KsTimer::checkTotal();
#endif
}
/************************************************************************************************/
/*
 * �q��ǉ��܂��́A�Z���ǉ����ɕ`�惊���N����������K�v������?
 * ����Ƃ��}�l�[�W���[�̎��s���ɖ��t���[���`�惊���N�𐶐�����(order����)
 * �܂��́AOT�ɓo�^�֐���ǉ�����
 * �X�V�t���O�ŉ��x�������N�����Ȃ��悢�悤�ɂ���K�v������
 * (���x���`�F�b�N����)
 */
/************************************************************************************************/
void KsTaskManager::taskExecute( KsTask* pTask, void* pUserData )
{
	if( pTask ){
		/* �������t���O���`�F�b�N���� */
		if( pTask->m_flags & ksTASK_FALGS_INITIALIZE ){
			/* ������ */
			pTask->initialize( pUserData );
			/* �������I�� */
			pTask->m_flags &= (KsUInt32)(~ksTASK_FALGS_INITIALIZE);
			//pTask->m_id = m_taskID;
			//m_taskID++;
		}

		/* �|�[�Y�t���O�`�F�b�N */
		if( !(pTask->m_flags & ksTASK_FLAGS_PAUSE) ){
			/* ���s */
			pTask->execute( pUserData );
		}

		/* �q�^�X�N */
		/* ���������ƂՃt���O�������Ă�����return �Ŗ߂�K�v������ */
		if( !(pTask->m_flags & ksTASK_FLAGS_PAUSE_CHILD) ){
			if( pTask->m_pChild ){
				taskExecute( pTask->m_pChild, pUserData );
			}
		}

		/* �Z��^�X�N */
		if( pTask->m_pNextBrother ){
			taskExecute( pTask->m_pNextBrother, pUserData );
		}
	}
}
/************************************************************************************************/
/*
 * �`��J�n
 */
/************************************************************************************************/
void KsTaskManager::begineRender()
{
}
/************************************************************************************************/
/*
 * �`��I��
 */
/************************************************************************************************/
void KsTaskManager::endRender()
{
}
/************************************************************************************************/
/*
 * �폜
 */
/************************************************************************************************/
void KsTaskManager::kill( KsTask* pTask, void* pParam )
{
	KsTask*		pChild   = NULL;
	KsTask*		pBrother = NULL;

	if( pTask ){
		/* �`��t���O�`�F�b�N */
		pChild   = pTask->m_pChild;
		pBrother = pTask->m_pNextBrother;

		/* �`�惊���N���͂����K�v������ */
		this->m_renderTbl.remove( pTask );

		/*
			�폜����Ƃ��J������������`�惊���N����͂����Ă���폜���Ȃ��Ƃ���
			����Ȃ��ƃ����N�Ɏc�����܂܏����Ă��܂�
		*/
		//if( pTask->getType() == ksTASK_TYPE_CAMERA ){
		//	m_renderTbl.getOrder( 32 )->clear();
		//}

#ifdef ksTASK_DELETE_BEFORE
		/* �����̃^�X�N���폜���Ă���q�^�X�N������(�J�����ł܂����̂ł��̏����́A��߂Ă���) */

		/* �㏈�� */
		pTask->terminate( pParam );

		/* ���[�N�G���A�g�p���`�F�b�N���� */
		if( !( pTask->getFlags() & ksTASK_FLAGS_USE_WORKAREA ) ){
			delete pTask;
		}

		/* �q�^�X�N */
		if( pChild ){
			kill( pChild, pParam );
		}

		/* �Z��^�X�N */
		if( pBrother ){
			kill( pBrother, pParam );
		}
#else
		/* �ŏ��Ɏq�^�X�N�ƌZ�������(������̗p) */

		/* �q�^�X�N */
		if( pChild ){
			kill( pChild, pParam );
		}

		/* �Z��^�X�N */
		if( pBrother ){
			kill( pBrother, pParam );
		}
		
		/* �㏈�� */
		pTask->terminate( pParam );

		/* ���[�N�G���A�g�p���`�F�b�N���� */
		if( !( pTask->getFlags() & ksTASK_FLAGS_USE_WORKAREA ) ){
			delete pTask;
		}
#endif

	}
}
/************************************************************************************************/
/*
 * ���ׂĂɓK�p����
 */
/************************************************************************************************/
void KsTaskManager::allCallback( KsTaskCallback callback, void* pUserData )
{
	allChildCallback( m_pRootTask, callback, pUserData );
}
/************************************************************************************************/
/*
 * ���ׂĂ̎q���ɓK�p
 */
/************************************************************************************************/
void KsTaskManager::allChildCallback( KsTask* pTask, KsTaskCallback callback, void* pUserData )
{
	if( pTask ){

		if( !callback( pTask, pUserData ) ){ return; }

		/* �q�^�X�N */
		if( pTask->m_pChild ){
			allChildCallback( pTask->m_pChild, callback, pUserData );
		}

		/* �Z��^�X�N */
		if( pTask->m_pNextBrother ){
			allChildCallback( pTask->m_pNextBrother, callback, pUserData );
		}
	}
}

