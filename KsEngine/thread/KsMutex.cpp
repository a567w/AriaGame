/************************************************************************************************/
/** 
 * @file		KsMutex.cpp
 * @brief		排他制御クラス
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
#include "KsMutex.inl"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsMutex::KsMutex( KsBool bCriticalSection )
    : m_mutex( 0 )
    , m_critical_section( bCriticalSection )
{
	if( m_critical_section )
	{
        m_mutex = new_critical_section();
	}
	else
	{
        m_mutex = new_mutex( 0 );
	}
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsMutex::~KsMutex()
{
	if( m_critical_section )
	{
        delete_critical_section( m_mutex );
	}
	else
	{
        delete_mutex( m_mutex );
	}
}

/************************************************************************************************/
/*
 * ロックする
 */
/************************************************************************************************/
void KsMutex::lock()
{
	if( m_critical_section )
	{
        wait_critical_section_infinite( m_mutex );
	}
	else
	{
        wait_mutex( m_mutex, INFINITE );
	}
}

/************************************************************************************************/
/*
 * ロックする
 * @param	state	ロックステータス(未使用)
 */
/************************************************************************************************/
void KsMutex::lock( void* state )
{
    lock();
}

/************************************************************************************************/
/*
 * アンロックする
 */
/************************************************************************************************/
void KsMutex::unlock()
{
	if( m_critical_section )
	{
        release_critical_section( m_mutex );
	}
	else
	{
        release_mutex( m_mutex );
	}
}

/************************************************************************************************/
/*
 * アンロックする
 * @param	state	ロックステータス(未使用)
 */
/************************************************************************************************/
void KsMutex::unlock( void* state )
{
    unlock();
}

#if 0

KsMutexTry::KsMutexTry()
    : m_mutex(0)
    , m_critical_section(false)
{
    m_critical_section = has_TryEnterCriticalSection();
    if (m_critical_section)
        m_mutex = new_critical_section();
    else
        m_mutex = new_mutex(0);
}

KsMutexTry::~KsMutexTry()
{
    if (m_critical_section)
        delete_critical_section(m_mutex);
    else
        delete_mutex(m_mutex);
}

void KsMutexTry::lock()
{
    if (m_critical_section)
        wait_critical_section_infinite(m_mutex);
    else
        wait_mutex(m_mutex, INFINITE);
}

bool KsMutexTry::do_trylock()
{
    if (m_critical_section)
        return wait_critical_section_try(m_mutex);
    else
        return wait_mutex(m_mutex, 0) == WAIT_OBJECT_0;
}

/************************************************************************************************/
/*
 * アンロックする
 * @param	state	ロックステータス(未使用)
 */
/************************************************************************************************/
void KsMutexTry::unlock()
{
    if (m_critical_section)
        release_critical_section(m_mutex);
    else
        release_mutex(m_mutex);
}

/************************************************************************************************/
/*
 * アンロックする
 * @param	state	ロックステータス(未使用)
 */
/************************************************************************************************/
void KsMutexTry::lock(cv_state&)
{
    lock();
}

/************************************************************************************************/
/*
 * アンロックする
 * @param	state	ロックステータス(未使用)
 */
/************************************************************************************************/
void KsMutexTry::unlock(cv_state&)
{
    unlock();
}













timed_mutex::timed_mutex()
    : m_mutex(0)
{
    m_mutex = new_mutex(0);
}

timed_mutex::~timed_mutex()
{
    delete_mutex(m_mutex);
}

void timed_mutex::lock()
{
    wait_mutex(m_mutex, INFINITE);
}

bool timed_mutex::do_trylock()
{
    return wait_mutex(m_mutex, 0) == WAIT_OBJECT_0;
}

bool timed_mutex::do_timedlock(const xtime& xt)
{
    for (;;)
    {
        int milliseconds;
        to_duration(xt, milliseconds);

        int res = wait_mutex(m_mutex, milliseconds);

        if (res == WAIT_TIMEOUT)
        {
            boost::xtime cur;
            boost::xtime_get(&cur, boost::TIME_UTC);
            if (boost::xtime_cmp(xt, cur) > 0)
                continue;
        }

        return res == WAIT_OBJECT_0;
    }
}

void timed_mutex::unlock()
{
    release_mutex(m_mutex);
}

void timed_mutex::lock(cv_state&)
{
    lock();
}

void timed_mutex::unlock(cv_state&)
{
    unlock();
}

#elif defined(BOOST_HAS_PTHREADS)

mutex::mutex()
{
    int res = 0;
    res = pthread_mutex_init(&m_mutex, 0);
    if (res != 0)
        throw thread_resource_error();
}

mutex::~mutex()
{
    int res = 0;
    res = pthread_mutex_destroy(&m_mutex);
    assert(res == 0);
}

void mutex::lock()
{
    int res = 0;
    res = pthread_mutex_lock(&m_mutex);
    if (res == EDEADLK) throw lock_error();
    assert(res == 0);
}

void mutex::unlock()
{
    int res = 0;
    res = pthread_mutex_unlock(&m_mutex);
    if (res == EPERM) throw lock_error();
    assert(res == 0);
}

void mutex::lock(cv_state&)
{
}

void mutex::unlock(cv_state& state)
{
    state.pmutex = &m_mutex;
}

KsMutexTry::KsMutexTry()
{
    int res = 0;
    res = pthread_mutex_init(&m_mutex, 0);
    if (res != 0)
        throw thread_resource_error();
}

KsMutexTry::~KsMutexTry()
{
    int res = 0;
    res = pthread_mutex_destroy(&m_mutex);
    assert(res == 0);
}

void KsMutexTry::lock()
{
    int res = 0;
    res = pthread_mutex_lock(&m_mutex);
    if (res == EDEADLK) throw lock_error();
    assert(res == 0);
}

bool KsMutexTry::do_trylock()
{
    int res = 0;
    res = pthread_mutex_trylock(&m_mutex);
    if (res == EDEADLK) throw lock_error();
    assert(res == 0 || res == EBUSY);
    return res == 0;
}

void KsMutexTry::unlock()
{
    int res = 0;
    res = pthread_mutex_unlock(&m_mutex);
    if (res == EPERM) throw lock_error();
    assert(res == 0);
}

void KsMutexTry::lock(cv_state&)
{
}

void KsMutexTry::unlock(cv_state& state)
{
    state.pmutex = &m_mutex;
}

timed_mutex::timed_mutex()
    : m_locked(false)
{
    int res = 0;
    res = pthread_mutex_init(&m_mutex, 0);
    if (res != 0)
        throw thread_resource_error();

    res = pthread_cond_init(&m_condition, 0);
    if (res != 0)
    {
        pthread_mutex_destroy(&m_mutex);
        throw thread_resource_error();
    }
}

timed_mutex::~timed_mutex()
{
    assert(!m_locked);
    int res = 0;
    res = pthread_mutex_destroy(&m_mutex);
    assert(res == 0);

    res = pthread_cond_destroy(&m_condition);
    assert(res == 0);
}

void timed_mutex::lock()
{
    int res = 0;
    res = pthread_mutex_lock(&m_mutex);
    assert(res == 0);

    while (m_locked)
    {
        res = pthread_cond_wait(&m_condition, &m_mutex);
        assert(res == 0);
    }

    assert(!m_locked);
    m_locked = true;

    res = pthread_mutex_unlock(&m_mutex);
    assert(res == 0);
}

bool timed_mutex::do_trylock()
{
    int res = 0;
    res = pthread_mutex_lock(&m_mutex);
    assert(res == 0);

    bool ret = false;
    if (!m_locked)
    {
        m_locked = true;
        ret = true;
    }

    res = pthread_mutex_unlock(&m_mutex);
    assert(res == 0);
    return ret;
}

bool timed_mutex::do_timedlock(const xtime& xt)
{
    int res = 0;
    res = pthread_mutex_lock(&m_mutex);
    assert(res == 0);

    timespec ts;
    to_timespec(xt, ts);

    while (m_locked)
    {
        res = pthread_cond_timedwait(&m_condition, &m_mutex, &ts);
        assert(res == 0 || res == ETIMEDOUT);

        if (res == ETIMEDOUT)
            break;
    }

    bool ret = false;
    if (!m_locked)
    {
        m_locked = true;
        ret = true;
    }

    res = pthread_mutex_unlock(&m_mutex);
    assert(res == 0);
    return ret;
}

void timed_mutex::unlock()
{
    int res = 0;
    res = pthread_mutex_lock(&m_mutex);
    assert(res == 0);

    assert(m_locked);
    m_locked = false;

    res = pthread_cond_signal(&m_condition);
    assert(res == 0);

    res = pthread_mutex_unlock(&m_mutex);
    assert(res == 0);
}

void timed_mutex::lock(cv_state&)
{
    int res = 0;
    while (m_locked)
    {
        res = pthread_cond_wait(&m_condition, &m_mutex);
        assert(res == 0);
    }

    assert(!m_locked);
    m_locked = true;

    res = pthread_mutex_unlock(&m_mutex);
    assert(res == 0);
}

void timed_mutex::unlock(cv_state& state)
{
    int res = 0;
    res = pthread_mutex_lock(&m_mutex);
    assert(res == 0);

    assert(m_locked);
    m_locked = false;

    res = pthread_cond_signal(&m_condition);
    assert(res == 0);

    state.pmutex = &m_mutex;
}

#endif


/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsCriticalSection::KsCriticalSection()
{
	::InitializeCriticalSection( &m_cs );
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsCriticalSection::~KsCriticalSection()
{
	::DeleteCriticalSection( &m_cs );
}

/************************************************************************************************/
/*
 * ロックする
 */
/************************************************************************************************/
void KsCriticalSection::lock()
{
	::EnterCriticalSection( &m_cs );
}

/************************************************************************************************/
/*
 * アンロックする
 */
/************************************************************************************************/
void KsCriticalSection::unlock()
{
	LeaveCriticalSection( &m_cs );
}

