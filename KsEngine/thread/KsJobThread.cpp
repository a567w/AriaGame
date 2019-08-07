/************************************************************************************************/
/** 
 * @file		KsThread.cpp
 * @brief		スレッド管理
 * @author		Tsukasa Kato
 * @date		2004/08/17
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                          */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"
#include "KsThread.h"
#include "KsThreadCondition.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * スレッドパラメータ
 * @class	KsThreadParam
 * @author  Tsukasa Kato
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class KsThreadParam
{
	public:
		KsMutex					m_mutex;		/**< 排他制御用			*/
		void*					m_pParam;		/**< スレッドパラメータ	*/
		KsBool					m_bStart;		/**< スタートフラグ		*/
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
 * コンストラクタ
 */
/************************************************************************************************/
KsThread::KsThread() : m_bJoin( ksFALSE )
{
	m_handle = reinterpret_cast<void*>( ::GetCurrentThread() );
	m_id     = ::GetCurrentThreadId();
}

/************************************************************************************************/
/*
 * コンストラクタ
 * @param	pParam		パラメータ
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
 * デストラクタ
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
 * == 演算子オーバーロード
 * @retval	ksTRUE		等しい
 * @retval	ksFALSE		等しくない
 */
/************************************************************************************************/
KsBool KsThread::operator == ( const KsThread& other ) const
{
    return ( other.m_id == m_id );
}

/************************************************************************************************/
/*
 * != 演算子オーバーロード
 * @retval	ksTRUE		等しくない
 * @retval	ksFALSE		等しい
 */
/************************************************************************************************/
KsBool KsThread::operator != ( const KsThread& other ) const
{
    return !( operator == (other) );
}

/************************************************************************************************/
/*
 * スレッドの終了を待機する
 */
/************************************************************************************************/
void KsThread::join()
{
    KsAssertEx( m_bJoin );

    KsInt32	result = 0;

	/* 無限に待つ */
	result = ::WaitForSingleObject(reinterpret_cast<HANDLE>(m_handle), INFINITE);

    KsAssertEx( result == WAIT_OBJECT_0 );
	result = ::CloseHandle(reinterpret_cast<HANDLE>(m_handle));
    KsAssertEx(result);

    m_bJoin = ksFALSE;
}

/************************************************************************************************/
/*
 * 使用プロセッサをセットする
 * @param	prosessor	使用プロセッサ番号
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
 * 指定時間現在のスレッドの実行を休止する
 * @param	time		待ち時間(ms)
 */
/************************************************************************************************/
void KsThread::sleep( const KsUInt32 time )
{
	::Sleep( time );
}

/************************************************************************************************/
/*
 * 現在のスレッドの実行を中断して他のスレッドへ実行を譲ります。
 */
/************************************************************************************************/
void KsThread::yield()
{
	::Sleep( 0 );
}


