/************************************************************************************************/
/** 
 * @file		KsThread.cpp
 * @brief		�X���b�h�Ǘ�
 * @author		Tsukasa Kato
 * @date		2004/08/17
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                          */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"
#include "KsThread.h"

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
KsThread::KsThread() : m_bJoin( ksFALSE )
{
	m_handle = reinterpret_cast<void*>( ::GetCurrentThread() );
	m_id     = ::GetCurrentThreadId();
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 * @param	pParam		�p�����[�^
 */
/************************************************************************************************/
KsThread::KsThread( KsThreadFunc func, void* pParam ) : m_bJoin( ksTRUE )
{
	//KsThreadParam	param( func, pParam );

	m_handle = reinterpret_cast<void*>( _beginthreadex( 0, 0, func, pParam, 0, &m_id ) );
	//m_handle = reinterpret_cast<void*>( _beginthreadex( 0, 0, func, pParam, CREATE_SUSPENDED, &m_id ) );
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsThread::~KsThread()
{
	destroy();
}

/************************************************************************************************/
/*
 * == ���Z�q�I�[�o�[���[�h
 * @retval	ksTRUE		������
 * @retval	ksFALSE		�������Ȃ�
 */
/************************************************************************************************/
KsBool KsThread::operator == ( const KsThread& other ) const
{
	return ( other.m_id == m_id );
}

/************************************************************************************************/
/*
 * != ���Z�q�I�[�o�[���[�h
 * @retval	ksTRUE		�������Ȃ�
 * @retval	ksFALSE		������
 */
/************************************************************************************************/
KsBool KsThread::operator != ( const KsThread& other ) const
{
	return !( operator == (other) );
}

/************************************************************************************************/
/*
 * �X���b�h��j������
 */
/************************************************************************************************/
void KsThread::destroy()
{
	if( m_handle )
	{
		KsInt32	result = 0;

		result = ::CloseHandle(reinterpret_cast<HANDLE>(m_handle));

		KsAssertEx( result );

		m_handle = 0;
	}
}

/************************************************************************************************/
/*
 * �X���b�h�������J�n����
 */
/************************************************************************************************/
void KsThread::start()
{
	if( !m_bJoin )
	{
		m_handle = reinterpret_cast<void*>( _beginthreadex( 0, 0, KsThreadMainFunc, this, 0, &m_id ) );
		m_bJoin  = ksTRUE;
		return;
	}

	if( m_handle != NULL )
	{
		::ResumeThread( m_handle );
	}
}

/************************************************************************************************/
/*
 * �X���b�h�̏I����ҋ@����
 */
/************************************************************************************************/
void KsThread::join()
{
	KsAssertEx( m_bJoin );

	KsInt32	result = 0;

	/* �����ɑ҂� */
	result = ::WaitForSingleObject(reinterpret_cast<HANDLE>(m_handle), INFINITE);

	KsAssertEx( result == WAIT_OBJECT_0 );
	result = ::CloseHandle(reinterpret_cast<HANDLE>(m_handle));
	KsAssertEx(result);

	m_handle = 0;

	m_bJoin = ksFALSE;
}

/************************************************************************************************/
/*
 * �v���C�I���e�B���Z�b�g����
 * @param	priority	�v���C�I���e�B
 */
/************************************************************************************************/
void KsThread::setPriority( ksTHREAD_PRIORITY_TYPE priority )
{
	::SetThreadPriority( m_handle, priority );
}

/************************************************************************************************/
/*
 * �g�p�v���Z�b�T���Z�b�g����
 * @param	prosessor	�g�p�v���Z�b�T�ԍ�
 */
/************************************************************************************************/
KsBool KsThread::setProcessor( KsUInt32 prosessor )
{
#if(_WIN32_WINNT >= 0x0400)
	::SetThreadIdealProcessor( reinterpret_cast<HANDLE>(m_handle), static_cast<DWORD>(prosessor) );
#else
	::SetThreadAffinityMask( reinterpret_cast<HANDLE>(m_handle), static_cast<DWORD>( 1 << prosessor ) );
#endif 
	return ksTRUE;
}

/************************************************************************************************/
/*
 * �X���b�h��ҋ@����
 */
/************************************************************************************************/
void KsThread::wait( KsHandle handle )
{
	/* �����ɑ҂� */
	::WaitForSingleObject(reinterpret_cast<HANDLE>(handle), INFINITE);
}

/************************************************************************************************/
/*
 * �X���b�h�̃��C���֐�
 * @return	���s�I������
 */
/************************************************************************************************/
KsUInt32 KsThread::threadMain()
{
	return 0;
}

/************************************************************************************************/
/*
 * �w�莞�Ԍ��݂̃X���b�h�̎��s���x�~����
 * @param	time		�҂�����(ms)
 */
/************************************************************************************************/
void KsThread::sleep( const KsUInt32 time )
{
	::Sleep( time );
}

/************************************************************************************************/
/*
 * ���݂̃X���b�h�̎��s�𒆒f���đ��̃X���b�h�֎��s������܂��B
 */
/************************************************************************************************/
void KsThread::yield()
{
	::Sleep( 0 );
}

/************************************************************************************************/
/*
 * �w�肳�ꂽ�ϐ��̒l���C���N�������g���i1 ���₵�܂��j
 */
/************************************************************************************************/
KsLong KsThread::interlockedIncrement( KsLong* pCount )
{
	return InterlockedIncrement( pCount );
}

/************************************************************************************************/
/*
 * �w�肳�ꂽ�ϐ��̒l���f�N�������g���i1 ���炵�܂��j
 */
/************************************************************************************************/
KsLong KsThread::interlockedDecrement( KsLong* pCount )
{
	return InterlockedDecrement( pCount );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsUInt32 __stdcall KsThreadMainFunc( void* pParam )
{
	KsThread* pThread = reinterpret_cast< KsThread* >( pParam );

	const KsUInt32	ret = pThread->threadMain();

	_endthreadex( 0 );

	return ret;
}

