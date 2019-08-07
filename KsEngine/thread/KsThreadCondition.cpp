/************************************************************************************************/
/** 
 * @file		KsEvent.cpp
 * @brief		イベント処理
 * @author		Tsukasa Kato
 * @date		2004/08/17
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                          */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


KsConditionImpl::KsConditionImpl()
	: m_gone(0)
	, m_blocked(0)
	, m_waiting(0)
{
	m_gate  = reinterpret_cast<void*>( ::CreateSemaphore(0, 1, 1, 0) );
	m_queue = reinterpret_cast<void*>( ::CreateSemaphore(0, 0, KsInt32MAXVAL, 0) );
	m_mutex = reinterpret_cast<void*>( ::CreateMutex(0, 0, 0) );

    if (!m_gate || !m_queue || !m_mutex)
    {
        KsInt32 result = 0;
        
		if( m_gate )
        {
			result = ::CloseHandle(reinterpret_cast<HANDLE>(m_gate));
            KsAssertEx( result );
        }
        if( m_queue )
        {
			result = ::CloseHandle(reinterpret_cast<HANDLE>(m_queue));
            KsAssertEx( result );
        }
        if( m_mutex )
        {
			result = ::CloseHandle(reinterpret_cast<HANDLE>(m_mutex));
            KsAssertEx( result );
        }
        //throw thread_resource_error();
    }
}

KsConditionImpl::~KsConditionImpl()
{
    KsInt32		result = 0;

    result = ::CloseHandle(reinterpret_cast<HANDLE>(m_gate));
    KsAssertEx( result );
    result = ::CloseHandle(reinterpret_cast<HANDLE>(m_queue));
    KsAssertEx( result );
	result = ::CloseHandle(reinterpret_cast<HANDLE>(m_mutex));
    KsAssertEx( result );
}

void KsConditionImpl::notify_one()
{
    unsigned	signals = 0;
    KsInt32		result = 0;

	result = ::WaitForSingleObject(reinterpret_cast<HANDLE>(m_mutex), INFINITE);
    KsAssertEx( result == WAIT_OBJECT_0 );

    if( m_waiting != 0 )
    {
        if (m_blocked == 0)
        {
            result = ReleaseMutex(reinterpret_cast<HANDLE>(m_mutex));
            KsAssertEx(result);
            return;
        }
        ++m_waiting;
        --m_blocked;
        signals = 1;
    }
    else
    {
		result = ::WaitForSingleObject(reinterpret_cast<HANDLE>(m_gate), INFINITE);
        KsAssertEx(result == WAIT_OBJECT_0);

        if( m_blocked > m_gone )
        {
            if( m_gone != 0 )
            {
                m_blocked -= m_gone;
                m_gone = 0;
            }
            signals = m_waiting = 1;
            --m_blocked;
        }
        else
        {
			result = ::ReleaseSemaphore(reinterpret_cast<HANDLE>(m_gate), 1, 0);
            KsAssertEx(result);
        }
    }

	result = ::ReleaseMutex(reinterpret_cast<HANDLE>(m_mutex));
    KsAssertEx(result);

    if( signals )
    {
		result = ::ReleaseSemaphore(reinterpret_cast<HANDLE>(m_queue), signals, 0);
        KsAssertEx(result);
    }
}

void KsConditionImpl::notify_all()
{
    unsigned	signals = 0;
    KsInt32		result = 0;

	result = ::WaitForSingleObject(reinterpret_cast<HANDLE>(m_mutex), INFINITE);
    KsAssertEx(result == WAIT_OBJECT_0);

    if( m_waiting != 0 )
    {
        if( m_blocked == 0 )
        {
			result = ::ReleaseMutex(reinterpret_cast<HANDLE>(m_mutex));
            KsAssertEx(result);
            return;
        }

        m_waiting += (signals = m_blocked);
        m_blocked = 0;
    }
    else
    {
		result = ::WaitForSingleObject(reinterpret_cast<HANDLE>(m_gate), INFINITE);
        KsAssertEx(result == WAIT_OBJECT_0);
        if (m_blocked > m_gone)
        {
            if( m_gone != 0 )
            {
                m_blocked -= m_gone;
                m_gone = 0;
            }
            signals = m_waiting = m_blocked;
            m_blocked = 0;
        }
        else
        {
			result = ::ReleaseSemaphore(reinterpret_cast<HANDLE>(m_gate), 1, 0);
            KsAssertEx(result);
        }
    }

	result = ::ReleaseMutex(reinterpret_cast<HANDLE>(m_mutex));
    KsAssertEx(result);

    if( signals )
    {
		result = ::ReleaseSemaphore(reinterpret_cast<HANDLE>(m_queue), signals, 0);
        KsAssertEx(result);
    }
}

void KsConditionImpl::enter_wait()
{
	KsInt32		result = 0;

	result = ::WaitForSingleObject(reinterpret_cast<HANDLE>(m_gate), INFINITE);
    KsAssertEx(result == WAIT_OBJECT_0);
    ++m_blocked;
	result = ::ReleaseSemaphore(reinterpret_cast<HANDLE>(m_gate), 1, 0);
    KsAssertEx(result);
}

void KsConditionImpl::wait()
{
	KsInt32		result = 0;

	result = ::WaitForSingleObject(reinterpret_cast<HANDLE>(m_queue), INFINITE);
    KsAssertEx(result == WAIT_OBJECT_0);

    unsigned was_waiting=0;
    unsigned was_gone=0;

	result = ::WaitForSingleObject(reinterpret_cast<HANDLE>(m_mutex), INFINITE);
    KsAssertEx(result == WAIT_OBJECT_0);
    was_waiting = m_waiting;
    was_gone = m_gone;

    if(was_waiting != 0)
    {
        if (--m_waiting == 0)
        {
            if (m_blocked != 0)
            {
				result = ::ReleaseSemaphore(reinterpret_cast<HANDLE>(m_gate), 1,0);
                KsAssertEx(result);
                was_waiting = 0;
            }
			else if (m_gone != 0){
                m_gone = 0;
			}
        }
    }
    else if(++m_gone == (KsInt32MAXVAL / 2))
    {
		result = ::WaitForSingleObject(reinterpret_cast<HANDLE>(m_gate), INFINITE);
        KsAssertEx(result == WAIT_OBJECT_0);
        m_blocked -= m_gone;
        result = ReleaseSemaphore(reinterpret_cast<HANDLE>(m_gate), 1, 0);
        KsAssertEx(result);
        m_gone = 0;
    }
	result = ::ReleaseMutex(reinterpret_cast<HANDLE>(m_mutex));
    KsAssertEx(result);

    if(was_waiting == 1)
    {
        for(; was_gone; --was_gone)
        {
			result = ::WaitForSingleObject(reinterpret_cast<HANDLE>(m_queue),INFINITE);
            KsAssertEx(result == WAIT_OBJECT_0);
        }
		result = ::ReleaseSemaphore(reinterpret_cast<HANDLE>(m_gate), 1, 0);
        KsAssertEx(result);
    }
}

KsBool KsConditionImpl::timed_wait( KsUInt32 time )
{
    KsBool		ret    = ksFALSE;
    KsUInt32	result = 0;

    while( 1 )
    {
        result = WaitForSingleObject(reinterpret_cast<HANDLE>(m_queue), time );
        KsAssertEx(result != WAIT_FAILED && result != WAIT_ABANDONED);
        ret = (result == WAIT_OBJECT_0);

        if (result == WAIT_TIMEOUT)
        {
			// 実際の時間を計ってチェックする
			//continue;
        }

        break;
    }

    unsigned was_waiting=0;
    unsigned was_gone=0;

	result = ::WaitForSingleObject(reinterpret_cast<HANDLE>(m_mutex), INFINITE);
    KsAssertEx(result == WAIT_OBJECT_0);
    was_waiting = m_waiting;
    was_gone = m_gone;

    if(was_waiting != 0)
    {
        if (!ret)
        {
			if (m_blocked != 0){
                --m_blocked;
			}
			else{
                ++m_gone;
			}
        }
        if (--m_waiting == 0)
        {
            if (m_blocked != 0)
            {
				result = ::ReleaseSemaphore(reinterpret_cast<HANDLE>(m_gate), 1, 0);
                KsAssertEx(result);
                was_waiting = 0;
            }
			else if(m_gone != 0){
                m_gone = 0;
			}
        }
    }
    else if (++m_gone == (KsInt32MAXVAL / 2))
    {
		result = ::WaitForSingleObject(reinterpret_cast<HANDLE>(m_gate), INFINITE);
        KsAssertEx(result == WAIT_OBJECT_0);
        m_blocked -= m_gone;
		result = ::ReleaseSemaphore(reinterpret_cast<HANDLE>(m_gate), 1, 0);
        KsAssertEx(result);
        m_gone = 0;
    }

	result = ::ReleaseMutex(reinterpret_cast<HANDLE>(m_mutex));
    KsAssertEx(result );

    if(was_waiting == 1)
    {
        for(; was_gone; --was_gone)
        {
			result = ::WaitForSingleObject(reinterpret_cast<HANDLE>(m_queue),INFINITE);
            KsAssertEx(result ==  WAIT_OBJECT_0);
        }
		result = ::ReleaseSemaphore(reinterpret_cast<HANDLE>(m_gate), 1, 0);
        KsAssertEx(result);
    }

    return ret;
}


