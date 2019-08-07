/************************************************************************************************/
/** 
 * @file		KsTaskBase.cpp
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
#include "KsTaskBase.h"
#include "KsTaskManager.h"
#include "KsWorkArea.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * �^�X�N�����R�[���o�b�N�p�p�����[�^
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
 * ���O����
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
 * ID����
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
 * ID����
 */
/************************************************************************************************/
void KsTaskDelete( KsTaskBase* pTask )
{
	KsTaskBase*		pChild   = NULL;
	KsTaskBase*		pBrother = NULL;

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
			KsTaskDelete( pChild );
		}

		/* �Z��^�X�N */
		if( pBrother ){
			KsTaskDelete( pBrother );
		}

		/* ���[�N�G���A�g�p���`�F�b�N���� */
		if( !( pTask->getFlags() & ksTASK_FLAGS_USE_WORKAREA ) ){
			delete pTask;
		}
	}
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
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
 * �R���X�g���N�^
 * @param	order	�`��I�[�_�[
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
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsTaskBase::~KsTaskBase()
{
}
/************************************************************************************************/
/*
 * ���j�̐擪�|�C���^�ɍŌ���̃|�C���^�����Ă���
 */
/************************************************************************************************/
void KsTaskBase::addBrother( KsTaskBase* pTask, void* pUserData )
{
	/* �����ɂ��� */
	if( m_pParent ){
		/* �Ō�̌Z����擾 */
		/* ���̃^�X�N�̌Z��ɂȂ�͂��Ȃ̂ŁAm_pParent->m_pChild��NULL�ł��邱�Ƃ͂Ȃ��͂� */
		KsTaskBase*		pLast = m_pParent->m_pChild->m_pPrevBrother;

		/* �Ō���ۑ��p */
		m_pParent->m_pChild->m_pPrevBrother = pTask;

		/* �����N */
		pLast->m_pNextBrother = pTask;
		pTask->m_pPrevBrother = pLast;

		/* �e�Z�b�g */
		pTask->m_pParent = m_pParent;
	}
	else{
		KsTaskBase*		pTop = getTopBrother();

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
	if( pUserData && pTask->m_flags & ksTASK_FALGS_INITIALIZE ){
		/* ������ */
		pTask->initialize( pUserData );
		/* �������I�� */
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
	//KsAssert( pTask != NULL, "�ǉ������q�^�X�N��NULL�ł��B" );

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
		if( pUserData && pTask->m_flags & ksTASK_FALGS_INITIALIZE ){
			/* ������ */
			pTask->initialize( pUserData );
			/* �������I�� */
			pTask->m_flags &= (KsUInt32)(~ksTASK_FALGS_INITIALIZE);
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
void KsTaskBase::detach()
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
		KsTaskManager*		pManager = m_pManager;
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
void KsTaskBase::removeRenderLink( KsTaskBase* pTask )
{
	KsTaskBase*		pTemp = pTask;

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
KsTaskBase* KsTaskBase::cut()
{
	/* ���O�� */
	detach();

	/* ���ׂĂ̎q���̐e��NULL�ɂ��� */
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
 * �����̃^�X�N�������폜����
 */
/************************************************************************************************/
void KsTaskBase::remove()
{
	/* ���O�� */
	detach();
	
	/* �폜�t���O�𗧂Ă�H�ł����̏ꍇ�}�l�[�W���ɓo�^����Ă��Ȃ��Ƃ��߂Ȃ̂Ń��[�N�G���A���g�p����H */
	KsWorkArea::push( this );
}
/************************************************************************************************/
/*
 * �����̃^�X�N�������폜����
 */
/************************************************************************************************/
void KsTaskBase::destroy()
{
	/* ���O�� */
	detach();
	
	/* �폜�t���O�𗧂Ă�H�ł����̏ꍇ�}�l�[�W���ɓo�^����Ă��Ȃ��Ƃ��߂Ȃ̂Ń��[�N�G���A���g�p����H */
	KsWorkArea::push( this );
}
/************************************************************************************************/
/*
 * �`�惊���N��ύX����
 * @param		order				�V�����I�[�_�[
 */
/************************************************************************************************/
void KsTaskBase::changeRenderLink( KsUInt32 order )
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
void KsTaskBase::setName( const KsChar* string )
{
	strncpy( m_name, string, ksTASK_NAME_LENGTH - 1 );

	/* null �����Z�b�g */
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
 * �D�揇�ʂ��Z�b�g����
 * @return							�v���C�I���e�B
 */
/************************************************************************************************/
void KsTaskBase::setPriority( KsInt32 priority )
{
	m_priority.i = priority;
}
/************************************************************************************************/
/*
 * �I�[�_���Z�b�g
 */
/************************************************************************************************/
void KsTaskBase::setOrder( KsUInt32 order )
{
	m_order = order;
}
/************************************************************************************************/
/*
 * Z�l���Z�b�g����
 * @param		z					z�l
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
 * �^�X�N�̃^�C�v���擾����
 */
/************************************************************************************************/
ksTASK_TYPE KsTaskBase::getType() const
{
	return m_type;
}
/************************************************************************************************/
/*
 * �D�揇�ʂ��Z�b�g����
 */
/************************************************************************************************/
KsTaskPRIORITY KsTaskBase::getPriority() const
{
	return m_priority;
}
/************************************************************************************************/
/*
 * �I�[�_���Z�b�g
 */
/************************************************************************************************/
KsUInt32 KsTaskBase::getOrder() const
{
	return m_order;
}
/************************************************************************************************/
/*
 * �e�^�X�N���擾����
 * @return		�e�^�X�N�̃|�C���^
 */
/************************************************************************************************/
KsTaskBase* KsTaskBase::getParent()
{
	return m_pParent;
}
		
/************************************************************************************************/
/*
 * ���j�^�X�N���擾����
 */
/************************************************************************************************/
KsTaskBase* KsTaskBase::getTopBrother()
{
	/* �Ō�����擾 */
	if( m_pParent ){
		return m_pParent->m_pChild;
	}
	else{
		/* ���[�g�̂Ƃ� */
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
 * �Ō���^�X�N���擾����
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
 * �Z�^�X�N���擾����(���[�g��������킩��Ȃ�)
 */
/************************************************************************************************/
KsTaskBase* KsTaskBase::getPrevBrother()
{
	return m_pPrevBrother;
}
/************************************************************************************************/
/*
 * ��^�X�N���擾����(���[�g��������킩��Ȃ�)
 */
/************************************************************************************************/
KsTaskBase* KsTaskBase::getNextBrother()
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
KsTaskBase* KsTaskBase::getBrother( KsUInt32 index )
{
	if( m_pParent ){
		return m_pParent->getChild( index );
	}

	/* ���[�g�Ȃ̂ŕ��ʂɐ����� */
	/* ���j�܂ōs���Đ�����K�v������ */

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
 * �q�^�X�N�̐����擾����
 * @return		�q�^�X�N�̐�
 */
/************************************************************************************************/
KsUInt32 KsTaskBase::getNumBrother() const
{
	if( m_pParent ){
		return m_pParent->getNumChild();
	}

	/* ���[�g�Ȃ̂ŕ��ʂɐ����� */
	/* ���j�܂ōs���Đ�����K�v������ */

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
 * �q�^�X�N���擾����
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
 * �q�^�X�N�̐����擾����
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
 * ID����
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
 * ���ׂĂ̎q���ɓK�p
 */
/************************************************************************************************/
KsTaskBase* KsTaskBase::allChildCallback( KsTaskBase* pTask, KsTaskCallback callback, void* pUserData )
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

