/************************************************************************************************/
/** 
 * @file		KsFileThread.cpp
 * @brief		�t�@�C���X���b�h
 * @author		Tsukasa Kato
 * @date		2011/07/02
 * @since		2011/07/02
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * �t�@�C���X���b�h����
 */
/************************************************************************************************/
KsFileThread::KsFileThread( KsFileSystem* pFileSystem, ksTHREAD_PRIORITY_TYPE priority, KsUInt32 prosessor )
	: m_pFileSystem( pFileSystem )
	, m_priority( priority )
	, m_prosessor( prosessor )
	, m_bThreadLoop( ksFALSE )
{
	try
	{
		m_waitEvent = KsCreateEvent( ksTRUE, ksFALSE, _T("waitFileEvent") );
		m_syncEvent = KsCreateEvent( ksTRUE, ksFALSE, _T("syncFileEvent") );
	}
	catch( const KsChar* pszError )
	{
		/* �G���[ */
		KsError( pszError );
	}
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsFileThread::~KsFileThread()
{
	// �I��������
	m_bThreadLoop = ksFALSE;

	// �X���b�h�I���҂�����
	join();

	KsCloseEvent( m_waitEvent );
	KsCloseEvent( m_syncEvent );
}

/************************************************************************************************/
/*
 * �t�@�C���X���b�h�̏������J�n����B
 */
/************************************************************************************************/
KsBool KsFileThread::run()
{
	m_bThreadLoop = ksTRUE;

	/* �X���b�h�J�n���� */
	start();

	return ksTRUE;
}

/************************************************************************************************/
/*
 * �����܂�������
 */
/************************************************************************************************/
KsUInt32 KsFileThread::threadMain()
{
	setPriority( m_priority );
	setProcessor( m_prosessor );
	
	/* �Q�[�����[�v */
	while( m_bThreadLoop )
	{
		KsWaitEvent( m_waitEvent );
	
		m_pFileSystem->lock();
		
		m_pFileSystem->polling();
		
		m_pFileSystem->unlock();

		yield();
	}

	return 0;
}

/************************************************************************************************/
/*
 * �E�G�C�g�C�x���g���Z�b�g����
 */
/************************************************************************************************/
void KsFileThread::setWaitEvent()
{
	// �E�G�C�g�C�x���g���Z�b�g����
	KsSetEvent( m_waitEvent );
}

/************************************************************************************************/
/*
 * �����C�x���g���Z�b�g����
 */
/************************************************************************************************/
void KsFileThread::setSyncEvent()
{
	// �����C�x���g���Z�b�g����
	KsSetEvent( m_syncEvent );
}

/************************************************************************************************/
/*
 * �E�G�C�g�C�x���g�����Z�b�g����
 */
/************************************************************************************************/
void KsFileThread::resetWaitEvent()
{
	// �E�G�C�g�C�x���g�����Z�b�g����
	KsResetEvent( m_waitEvent );
}

/************************************************************************************************/
/*
 * �����C�x���g�����Z�b�g����
 */
/************************************************************************************************/
void KsFileThread::resetSyncEvent()
{
	// �����C�x���g�����Z�b�g����
	KsResetEvent( m_syncEvent );
}

