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
#include "KsThreadCondition.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * �X���b�h�p�����[�^
 * @class	KsThreadParam
 * @author  Tsukasa Kato
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class KsThreadParam
{
	public:
		KsMutex					m_mutex;		/**< �r������p			*/
		void*					m_pParam;		/**< �X���b�h�p�����[�^	*/
		KsBool					m_bStart;		/**< �X�^�[�g�t���O		*/
		KsThreadCondition		m_condition;
		KsThreadFunc			m_func;


		KsThreadParam( KsThreadFunc func, void* pParam )
			: m_pParam( pParam )
			, m_bStart( ksFALSE )
		{
		}

		void wait()
		{
			KsMutex::scoped_lock scoped_lock(m_mutex);
			
			if( !m_bStart )
			{
				m_condition.wait( scoped_lock );
			}
		}
		void started()
		{
			KsMutex::scoped_lock scoped_lock(m_mutex);
			m_bStart = ksTRUE;
		}
};

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

	if( !m_handle )
	{
		//KsMessage( "" ):
	}

    //param.wait();
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsThread::~KsThread()
{
    if( m_bJoin )
    {
        KsInt32	result = 0;
		result = ::CloseHandle(reinterpret_cast<HANDLE>(m_handle));
        KsAssertEx( result );
    }
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

    m_bJoin = ksFALSE;
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


