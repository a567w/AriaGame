/************************************************************************************************/
/** 
 * @file		KsThreadGroup.cpp
 * @brief		�X���b�h�Ǘ�
 * @author		Tsukasa Kato
 * @date		2004/08/17
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"
#include "KsThreadGroup.h"
#include "KsThreadCondition.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsThreadGroup::KsThreadGroup()
{
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsThreadGroup::~KsThreadGroup()
{
	for( KsList<KsThread*>::Iterator it = m_threadList.begin(); it != m_threadList.end(); ++it )
	{
		delete (*it);
	}
}

/************************************************************************************************/
/*
 * �w��X���b�h���̃O���[�v�ɒǉ�����
 * @param	pThread		�X���b�h�̃|�C���^
 */
/************************************************************************************************/
void KsThreadGroup::addThread( KsThreadFunc func, void* pParam )
{
    KsMutex::scoped_lock	scoped_lock( m_mutex );

	KsThread* pThread = new KsThread( func, pParam );

	// �Q�d�o�^�`�F�b�N
	KsList<KsThread*>::Iterator it;

    for( it = m_threadList.begin(); it != m_threadList.end(); ++it )
    {
		if( (*it) == pThread )
		{
		}
    }

	KsAssert( it != m_threadList.end(), "can't add thead" );

	if( it != m_threadList.end() )
	{
		m_threadList.push_back( pThread );
	}
}

/************************************************************************************************/
/*
 * �w��X���b�h���̃O���[�v�ɒǉ�����
 * @param	pThread		�X���b�h�̃|�C���^
 */
/************************************************************************************************/
void KsThreadGroup::addThread( KsThread* pThread )
{
    KsMutex::scoped_lock	scoped_lock( m_mutex );

	// �Q�d�o�^�`�F�b�N
	KsList<KsThread*>::Iterator it;

    for( it = m_threadList.begin(); it != m_threadList.end(); ++it )
    {
		if( (*it) == pThread ){
		}
    }

	KsAssert( it != m_threadList.end(), "can't add thead" );

	if( it != m_threadList.end() )
	{
		m_threadList.push_back( pThread );
	}
}

/************************************************************************************************/
/*
 * �w��X���b�h�����̃O���[�v�����菜��
 * @param	pThread		�X���b�h�̃|�C���^
 */
/************************************************************************************************/
void KsThreadGroup::removeThread( KsThread* pThread )
{
    KsMutex::scoped_lock scoped_lock( m_mutex );

	KsList<KsThread*>::Iterator it;

    for( it = m_threadList.begin(); it != m_threadList.end(); ++it )
    {
		if( (*it) == pThread ){
		}
    }

	KsAssert( it != m_threadList.end(), "can't remove thead" );

	if( it != m_threadList.end() )
	{
		m_threadList.erase( it );
	}
}

/************************************************************************************************/
/*
 * ���ׂẴX���b�h�̏I����ҋ@����
 */
/************************************************************************************************/
void KsThreadGroup::joinAll()
{
    KsMutex::scoped_lock scoped_lock( m_mutex );

    for( KsList<KsThread*>::Iterator it = m_threadList.begin(); it != m_threadList.end(); ++it )
    {
        (*it)->join();
    }
}

/************************************************************************************************/
/*
 * �o�^����Ă���X���b�h�̐����擾����
 * @return				�o�^����Ă���X���b�h�̐�
 */
/************************************************************************************************/
KsInt32 KsThreadGroup::getNumThread()
{
	return m_threadList.size();
}

