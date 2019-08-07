/************************************************************************************************/
/** 
 * @file		StTask.cpp
 * @brief		��{�^�X�N
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "StTask.h"
#include "StTaskManager.h"
#include "StWorkArea.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * �^�X�N�����R�[���o�b�N�p�p�����[�^
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
 * ���O����
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
 * ID����
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
 * ID����
 */
/************************************************************************************************/
void StTaskDelete( StTask* pTask )
{
	StTask*		pChild   = NULL;
	StTask*		pBrother = NULL;

	if( pTask ){
		/* �`��t���O�`�F�b�N */
		pChild   = pTask->getChild( 0 );
		pBrother = pTask->getBrother( 0 );

		/* �`�惊���N���͂����K�v������(���łɕ`�惊���N����O��Ă���K�v������) */
		//if( m_pManager ){
		//m_renderTbl.remove( pTask );
		//}

		// �ŏ��ɐe�����H
		//delete pTask;

		/* �q�^�X�N */
		if( pChild ){
			StTaskDelete( pChild );
		}

		/* �Z��^�X�N */
		if( pBrother ){
			StTaskDelete( pBrother );
		}

		/* ���[�N�G���A�g�p���`�F�b�N���� */
		if( !( pTask->getFlags() & stTASK_FLAGS_USE_WORKAREA ) ){
			delete pTask;
		}
	}
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
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
 * �f�X�g���N�^
 */
/************************************************************************************************/
StTask::~StTask()
{
}
/************************************************************************************************/
/*
 * ���j�̐擪�|�C���^�ɍŌ���̃|�C���^�����Ă���
 */
/************************************************************************************************/
void StTask::addBrother( StTask* pTask, void* pUserData )
{
	/* �����ɂ��� */
	if( m_pParent ){
		/* �Ō�̌Z����擾 */
		/* ���̃^�X�N�̌Z��ɂȂ�͂��Ȃ̂ŁAm_pParent->m_pChild��NULL�ł��邱�Ƃ͂Ȃ��͂� */
		StTask*		pLast = m_pParent->m_pChild->m_pPrevBrother;

		/* �Ō���ۑ��p */
		m_pParent->m_pChild->m_pPrevBrother = pTask;

		/* �����N */
		pLast->m_pNextBrother = pTask;
		pTask->m_pPrevBrother = pLast;

		/* �e�Z�b�g */
		m_pNextBrother->m_pParent = m_pParent;
	}
	else{
		StTask*		pTop = getTopBrother();

		/* ���[�g�Ȃ̂Œ��j���擾 */
		pTop->m_pPrevBrother->m_pNextBrother = pTask;

		/* ���̂Ƃ��ǉ�����^�X�N�ɌZ�킪�����炾�߂� */
		/* �L�`���̌Z�킪���邩�`�F�b�N���ăZ�b�g���� */

		if( pTask->m_pNextBrother ){
			/* ���łɌZ�킪����̂ōŌ�����擾���� */
			pTop->m_pPrevBrother = pTask->getEndBrother();
		}
		else{
			pTop->m_pPrevBrother = pTask;
		}
	}

	/* �`�惊���N���Z�b�g���� */
	pTask->m_pManager = m_pManager;

	if( m_pManager ){
		/* �o�^ */
		m_pManager->m_renderTbl.entry( pTask );
	}

	/* �������t���O���`�F�b�N���� */
	if( pUserData && pTask->m_flags & stTASK_FALGS_INITIALIZE ){
		/* ������ */
		pTask->initialize( pUserData );
		/* �������I�� */
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
	StAssert( pTask != NULL, "�ǉ������q�^�X�N��NULL�ł��B" );

	if( m_pChild )
	{
		/* �Z��ǉ� */
		m_pChild->addBrother( pTask, pUserData );
	}
	else
	{
		/* �q���ɒǉ� */
		m_pChild = pTask;

		/* �Ō�����Z�b�g */
		m_pChild->m_pPrevBrother = pTask;

		/* �e�Z�b�g */
		m_pChild->m_pParent = this;

		/* �`�惊���N���Z�b�g���� */
		pTask->m_pManager = m_pManager;

		if( m_pManager ){
			/* �o�^ */
			m_pManager->m_renderTbl.entry( pTask );
		}

		/* �������t���O���`�F�b�N���� */
		if( pUserData && pTask->m_flags & stTASK_FALGS_INITIALIZE ){
			/* ������ */
			pTask->initialize( pUserData );
			/* �������I�� */
			pTask->m_flags &= (StUInt32)(~stTASK_FALGS_INITIALIZE);
			//pTask->m_id = m_taskID;
			//m_taskID++;
		}
	}
}
/************************************************************************************************/
/*
 * �����̃^�X�N���Ƃ�͂���(������艺�̊K�w�́A�����ɂ����܂܁A�Z��͂�����Ƃ͂���)
 * �`�惊���N�����O���K�v������
 * @param		pTask				��菜���q�^�X�N�̃|�C���^
 */
/************************************************************************************************/
void StTask::detach()
{
	if( m_pParent )
	{
		if( m_pPrevBrother->m_pNextBrother == NULL ){
			/* ���������j */

			/* �Ō�������X�V */
			if( m_pNextBrother ){
				/* �����������Ȃ� */
				m_pNextBrother->m_pPrevBrother = m_pPrevBrother;
			}
			m_pParent->m_pChild = m_pNextBrother;
		}
		else{
			/* �Ȃ��ς� */
			if( m_pNextBrother ){
				m_pPrevBrother->m_pNextBrother = m_pNextBrother;
				m_pNextBrother->m_pPrevBrother = m_pPrevBrother;
			}
			else{
				/* �Ō�������X�V���� */
				m_pPrevBrother->m_pNextBrother = NULL;
				m_pParent->m_pChild->m_pPrevBrother = m_pPrevBrother;
			}
		}

		/* ���Z�b�g */
		m_pNextBrother = NULL;
		m_pPrevBrother = NULL;

		/* �`�惊�X�g����Ƃ�͂�������Manager��NULL�ɂ���K�v������ */
		removeRenderLink( NULL );
	}
	else
	{
		/*(�����Ή�) �����������}�l�[�W���ɓo�^����Ă��郋�[�g�ŌZ�킪���Ȃ�������}�l�[�W���̃��[�g����ύX����K�v������ */
		StTaskManager*		pManager = m_pManager;
		if( pManager ){
			pManager->setRootTask( NULL );
		}
	}
}
/************************************************************************************************/
/*
 * �`�惊���N������O��
 */
/************************************************************************************************/
void StTask::removeRenderLink( StTask* pTask )
{
	StTask*		pTemp = pTask;

	/* �}�l�[�W�����킩��Ȃ��ƕs�\ */
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
 * ���S�ɐ؂藣��detach���K�v
 * @param		pTask				��菜���q�^�X�N�̃|�C���^
 * ���S�ɐ؂藣�����1�̃^�X�N�ɂȂ�
 */
/************************************************************************************************/
StTask* StTask::cut()
{
	/* ���O�� */
	detach();

	/* ���ׂĂ̎q���̐e��NULL�ɂ��� */
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
 * �����̃^�X�N�������폜����
 */
/************************************************************************************************/
void StTask::remove()
{
	/* ���O�� */
	detach();
	
	/* �폜�t���O�𗧂Ă�H�ł����̏ꍇ�}�l�[�W���ɓo�^����Ă��Ȃ��Ƃ��߂Ȃ̂Ń��[�N�G���A���g�p����H */
	StWorkArea::push( this );
}
/************************************************************************************************/
/*
 * �����̃^�X�N�������폜����
 */
/************************************************************************************************/
void StTask::destroy()
{
	/* ���O�� */
	detach();
	
	/* �폜�t���O�𗧂Ă�H�ł����̏ꍇ�}�l�[�W���ɓo�^����Ă��Ȃ��Ƃ��߂Ȃ̂Ń��[�N�G���A���g�p����H */
	StWorkArea::push( this );
}
/************************************************************************************************/
/*
 * �`�惊���N��ύX����
 * @param		order				�V�����I�[�_�[
 */
/************************************************************************************************/
void StTask::changeRenderLink( StUInt32 order )
{
	/* ���̎��_�ŕ`�惊���N��ύX */
	if( m_pManager ){
		/* ��菜�� */
		m_pManager->m_renderTbl.remove( this );
		/* �V���ɒǉ� */
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

	/* null �����Z�b�g */
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
 * �D�揇�ʂ��Z�b�g����
 * @return							�v���C�I���e�B
 */
/************************************************************************************************/
void StTask::setPriority( StInt32 priority )
{
	m_priority.i = priority;
}
/************************************************************************************************/
/*
 * �I�[�_���Z�b�g
 */
/************************************************************************************************/
void StTask::setOrder( StUInt32 order )
{
	m_order = order;
}
/************************************************************************************************/
/*
 * Z�l���Z�b�g����
 * @param		z					z�l
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
 * �^�X�N�̃^�C�v���擾����
 */
/************************************************************************************************/
stTASK_TYPE StTask::getType() const
{
	return m_type;
}
/************************************************************************************************/
/*
 * �D�揇�ʂ��Z�b�g����
 */
/************************************************************************************************/
STTASKPRIORITY StTask::getPriority() const
{
	return m_priority;
}
/************************************************************************************************/
/*
 * �I�[�_���Z�b�g
 */
/************************************************************************************************/
StUInt32 StTask::getOrder() const
{
	return m_order;
}
/************************************************************************************************/
/*
 * �e�^�X�N���擾����
 * @return		�e�^�X�N�̃|�C���^
 */
/************************************************************************************************/
StTask* StTask::getParent()
{
	return m_pParent;
}
		
/************************************************************************************************/
/*
 * ���j�^�X�N���擾����
 */
/************************************************************************************************/
StTask* StTask::getTopBrother()
{
	/* �Ō�����擾 */
	if( m_pParent ){
		return m_pParent->m_pChild;
	}
	else{
		/* ���[�g�̂Ƃ� */
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
 * �Ō���^�X�N���擾����
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
 * �Z�^�X�N���擾����(���[�g��������킩��Ȃ�)
 */
/************************************************************************************************/
StTask* StTask::getPrevBrother()
{
	return m_pPrevBrother;
}
/************************************************************************************************/
/*
 * ��^�X�N���擾����(���[�g��������킩��Ȃ�)
 */
/************************************************************************************************/
StTask* StTask::getNextBrother()
{
	return m_pNextBrother;
}
/************************************************************************************************/
/*
 * �Z��^�X�N���擾����
 * @param		index				�q�^�X�N�̃C���f�b�N�X
 * @return		�q�^�X�N�̃|�C���^
 */
/************************************************************************************************/
StTask* StTask::getBrother( StUInt32 index )
{
	if( m_pParent ){
		return m_pParent->getChild( index );
	}

	/* ���[�g�Ȃ̂ŕ��ʂɐ����� */
	/* ���j�܂ōs���Đ�����K�v������ */

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
 * �q�^�X�N�̐����擾����
 * @return		�q�^�X�N�̐�
 */
/************************************************************************************************/
StUInt32 StTask::getNumBrother() const
{
	if( m_pParent ){
		return m_pParent->getNumChild();
	}

	/* ���[�g�Ȃ̂ŕ��ʂɐ����� */
	/* ���j�܂ōs���Đ�����K�v������ */

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
 * �q�^�X�N���擾����
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
 * �q�^�X�N�̐����擾����
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
 * ID����
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
 * ���ׂĂ̎q���ɓK�p
 */
/************************************************************************************************/
StTask* StTask::allChildCallback( StTask* pTask, StTaskCallback callback, void* pUserData )
{
	if( pTask ){
		if( !callback( pTask, pUserData ) ){ return NULL; }

		/* �q�^�X�N */
		if( pTask->m_pChild ){
			allChildCallback( pTask->m_pChild, callback, pUserData );
		}

		/* �Z��^�X�N */
		if( pTask->m_pNextBrother ){
			allChildCallback( pTask->m_pNextBrother, callback, pUserData );
		}
	}

	return NULL;
}

