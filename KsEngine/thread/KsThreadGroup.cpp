/************************************************************************************************/
/** 
 * @file		KsThreadGroup.cpp
 * @brief		スレッド管理
 * @author		Tsukasa Kato
 * @date		2004/08/17
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"
#include "KsThreadGroup.h"
#include "KsThreadCondition.h"

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
KsThreadGroup::KsThreadGroup()
{
}

/************************************************************************************************/
/*
 * デストラクタ
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
 * 指定スレッドこのグループに追加する
 * @param	pThread		スレッドのポインタ
 */
/************************************************************************************************/
void KsThreadGroup::addThread( KsThreadFunc func, void* pParam )
{
    KsMutex::scoped_lock	scoped_lock( m_mutex );

	KsThread* pThread = new KsThread( func, pParam );

	// ２重登録チェック
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
 * 指定スレッドこのグループに追加する
 * @param	pThread		スレッドのポインタ
 */
/************************************************************************************************/
void KsThreadGroup::addThread( KsThread* pThread )
{
    KsMutex::scoped_lock	scoped_lock( m_mutex );

	// ２重登録チェック
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
 * 指定スレッドをこのグループから取り除く
 * @param	pThread		スレッドのポインタ
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
 * すべてのスレッドの終了を待機する
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
 * 登録されているスレッドの数を取得する
 * @return				登録されているスレッドの数
 */
/************************************************************************************************/
KsInt32 KsThreadGroup::getNumThread()
{
	return m_threadList.size();
}

