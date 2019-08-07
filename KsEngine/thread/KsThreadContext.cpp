/************************************************************************************************/
/** 
 * @file		KsThreadContext.cpp
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
#include "KsThreadContext.h"

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
KsThreadContext::KsThreadContext() : m_bJoin( ksFALSE )
{
	m_handle = reinterpret_cast<void*>( ::GetCurrentThread() );
	m_id     = ::GetCurrentThreadId();
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsThreadContext::~KsThreadContext()
{
	destroy();
}

/************************************************************************************************/
/*
 * �X���b�h��j������
 */
/************************************************************************************************/
void KsThreadContext::destroy()
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
void KsThreadContext::start()
{
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
void KsThreadContext::join()
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
void KsThreadContext::setPriority( ksTHREAD_PRIORITY_TYPE priority )
{
	::SetThreadPriority( m_handle, priority );
}

/************************************************************************************************/
/*
 * �g�p�v���Z�b�T���Z�b�g����
 * @param	prosessor	�g�p�v���Z�b�T�ԍ�
 */
/************************************************************************************************/
KsBool KsThreadContext::setProcessor( KsUInt32 prosessor )
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
void KsThreadContext::wait( KsHandle handle )
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
KsUInt32 KsThreadContext::threadMain()
{
	return 0;
}

/************************************************************************************************/
/*
 * �w�莞�Ԍ��݂̃X���b�h�̎��s���x�~����
 * @param	time		�҂�����(ms)
 */
/************************************************************************************************/
void KsThreadContext::sleep( const KsUInt32 time )
{
	::Sleep( time );
}

/************************************************************************************************/
/*
 * ���݂̃X���b�h�̎��s�𒆒f���đ��̃X���b�h�֎��s������܂��B
 */
/************************************************************************************************/
void KsThreadContext::yield()
{
	::Sleep( 0 );
}

/************************************************************************************************/
/*
 * �w�肳�ꂽ�ϐ��̒l���C���N�������g���i1 ���₵�܂��j
 */
/************************************************************************************************/
KsLong KsThreadContext::interlockedIncrement( KsLong* pCount )
{
	return InterlockedIncrement( pCount );
}

/************************************************************************************************/
/*
 * �w�肳�ꂽ�ϐ��̒l���f�N�������g���i1 ���炵�܂��j
 */
/************************************************************************************************/
KsLong KsThreadContext::interlockedDecrement( KsLong* pCount )
{
	return InterlockedDecrement( pCount );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsUInt32 __stdcall KsThreadContextMainFunc( void* pParam )
{
	KsThreadContext* pThread = reinterpret_cast< KsThreadContext* >( pParam );

#if 0
	TlsSetValue( s_contextTlsIndex, &pThread->m_context );

	// take ownership of the allocator:
	if( pThread->m_context.pAllocator != nullptr )
	{
			pThread->m_context.pAllocator->setOwnerThread( pThread );
	}
#endif

	return pThread->threadMain();
}

