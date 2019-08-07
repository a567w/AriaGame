/************************************************************************************************/
/** 
 * @file		KsThreadLock.h
 * @brief		スレッドロック
 * @author		Tsukasa Kato
 * @date		2004/08/17
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSTHREADLOCK_H__
#define __KSTHREADLOCK_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsThreadCondition;

/************************************************************************************************/
/**
 * ロックオプション
 * @class	KsThreadLockOps
 * @author  Tsukasa Kato
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
template < typename Mutex > class ksENGINE_API KsThreadLockOps
{
	public:
		/**
		 * コンストラクタ
		 */
								KsThreadLockOps(){}
	public:
		/**
		 * ロックする
		 * @param		m		ロックする排他制御用クラス
		 */
		static void			lock( Mutex& m ) { m.lock(); }

		/** 
		 * ロックできるかチェックしてできるならロックする
		 * @param		m		ロックする排他制御用クラス
		 */
		static KsBool			lockTry( Mutex& m ) { return m.lockTry(); }

		/**
		 * 指定時間ロックする
		 * @param		m		ロックする排他制御用クラス
		 */
		static KsBool			lockTime( Mutex& m, KsUInt32 time ) { return m.lockTime( time ); }

		/**
		 * 指定ステータスでロックする
		 * @param		m		ロックする排他制御用クラス
		 * @param		state	ロックステータス
		 */
		static void			lock( Mutex& m, void* state ) { m.lock( state ); }

		/**
		 * アンロックする
		 * @param		m		アンロックする排他制御用クラス
		 */
		static void			unlock( Mutex& m ) { m.unlock(); }

		/**
		 * アンロックする
		 * @param		m		アンロックする排他制御用クラス
		 * @param		state	アンロックステータス
		 */
		static void			unlock( Mutex& m, void* state ) { m.unlock( state ); }
};

/************************************************************************************************/
/**
 * ロック
 * @class	KsThreadLock
 * @author  Tsukasa Kato
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
template < typename Mutex > class ksENGINE_API KsThreadLock
{
		friend class		KsThreadCondition;

	public:
		typedef Mutex		mutexType;	/**< Mutexタイプ	*/

	public:
		/**
		 * コンストラクタ
		 * @param	mx	Mutex
		 * @param	initLoacked		初期ロックするか
		 */
		explicit KsThreadLock( Mutex& m, KsBool initLocked=ksTRUE )
			: m_mutex( m ),
			  m_bLocked( ksFALSE )
		{
			if( initLocked ){
				lock();
			}
		}
		
		/**
		 * デストラクタ
		 */
		~KsThreadLock()
		{
			if( m_bLocked ){
				unlock();
			}
		}

		/**
		 * ロックする
		 */
		void		lock()
		{
			if( m_bLocked ){
//				throw lock_error();
			}

			KsThreadLockOps<Mutex>::lock( m_mutex );

			m_bLocked = ksTRUE;
		}

		/**
		 * アンロックする
		 */
		void		unlock()
		{
			if( !m_bLocked ){
//				throw lock_error();
			}

			KsThreadLockOps<Mutex>::unlock( m_mutex );

			m_bLocked = ksFALSE;
		}

		/**
		 * ロック状態かのチェック
		 * @retval	ksTRUE		ロック状態
		 * @retval	ksFALSE		アンロック状態
		 */
		KsBool		isLocked() const { return m_bLocked; }

		/**
		 * キャスト用
		 */
		operator const void*() const { return m_bLocked ? this : 0; }

	private:
		Mutex&			m_mutex;		/**< Mutex			*/
		KsBool			m_bLocked;		/**< ロックフラグ	*/
};

/************************************************************************************************/
/**
 * ロック
 * @class	KsThreadLock
 * @author  Tsukasa Kato
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
template <typename Mutex> class ksENGINE_API KsThreadLockTry
{
		friend class		KsThreadCondition;

	public:
		typedef Mutex		mutexType;

	public:
		/**
		 * コンストラクタ
		 * @param	m	Mutex
		 * @param	initLoacked		初期ロックするか
		 */
		explicit KsThreadLockTry( Mutex& m ) : m_mutex( m ), m_bLocked( ksFALSE )
		{
			try_lock();
		}

		/**
		 * コンストラクタ
		 * @param	m	Mutex
		 * @param	initLoacked		初期ロックするか
		 */
		KsThreadLockTry( Mutex& m, KsBool initLocked=ksTRUE ) : m_mutex( m ), m_bLocked( ksFALSE )
		{
			if( initLocked ){
				lock();
			}
		}

		/**
		 * デストラクタ
		 */
		~KsThreadLockTry()
		{
			if( m_bLocked ){
				unlock();
			}
		}

		/**
		 * ロックする
		 */
		void		lock()
		{
			if( m_bLocked ){
				throw lock_error();
			}

			KsThreadLockOps<Mutex>::lock(m_mutex);

			m_bLocked = ksTRUE;
		}

		/**
		 * ロック状態かのチェック
		 * @retval	ksTRUE		ロック状態
		 * @retval	ksFALSE		アンロック状態
		 */
		KsBool	lockTry()
		{
			if( m_bLocked ){
				throw lock_error();
			}

			return ( m_bLocked = KsThreadLockOps<TryMutex>::lockTry( m_mutex ) );
		}

		/**
		 * アンロックする
		 */
		void		unlock()
		{
			if( !m_bLocked ){
				throw lock_error();
			}

			KsThreadLockOps<Mutex>::unlock(m_mutex);

			m_bLocked = ksFALSE;
		}

		/**
		 * ロック状態かのチェック
		 * @retval	ksTRUE		ロック状態
		 * @retval	ksFALSE		アンロック状態
		 */
		KsBool		isLocked() const { return m_bLocked; }

		/**
		 * キャスト用
		 */
		operator const void*() const { return m_bLocked ? this : 0; }

	private:
		Mutex&			m_mutex;		/**< Mutex			*/
		KsBool			m_bLocked;		/**< ロックフラグ	*/
};

/************************************************************************************************/
/**
 * ロック
 * @class	KsThreadLock
 * @author  Tsukasa Kato
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
template <typename Mutex> class ksENGINE_API KsThreadLockTime
{
		friend class		KsThreadCondition;

	public:
		typedef Mutex		mutexType;

	public:
		/**
		 * コンストラクタ
		 * @param	m				Mutex
		 * @param	initLoacked		初期ロックするか
		 */
		explicit KsThreadLockTime( Mutex& m, KsUInt32 time ) : m_mutex( m ), m_bLocked( ksFALSE )
		{
			lockTime( time );
		}

		/**
		 * コンストラクタ
		 * @param	m				Mutex
		 * @param	initLoacked		初期ロックするか
		 */
		KsThreadLockTime( Mutex& m, KsBool initLocked=ksTRUE ) : m_mutex( m ), m_bLocked( ksFALSE )
		{
			if( initLocked ){
				lock();
			}
		}

		/**
		 * デストラクタ
		 */
		~KsThreadLockTime()
		{
			if( m_bLocked ){
				unlock();
			}
		}

		/**
		 * ロックする
		 */
		void		lock()
		{
			if( m_bLocked ){
				throw lock_error();
			}

			KsThreadLockOps<Mutex>::lock(m_mutex);

			m_bLocked = ksTRUE;
		}

		/**
		 * ロック状態かのチェック
		 * @retval	ksTRUE		ロック状態
		 * @retval	ksFALSE		アンロック状態
		 */
		KsBool	lockTry()
		{
			if( m_bLocked ){
				throw lock_error();
			}

			return ( m_bLocked = KsThreadLockOps<Mutex>::lockTry( m_mutex ) );
		}


		/**
		 * 時間でロックする
		 * @param	time		ロック時間
		 * @retval	ksTRUE		ロック状態
		 * @retval	ksFALSE		アンロック状態
		 */
		KsBool	lockTime( KsUInt32 time )
		{
			if( m_bLocked ){
				throw lock_error();
			}

			return ( m_bLocked = KslockOps<Mutex>::lockTime( m_mutex, time ) );
		}

		/**
		 * アンロックする
		 */
		void		unlock()
		{
			if( !m_bLocked ){
				throw lock_error();
			}

			KsThreadLockOps<Mutex>::unlock(m_mutex);

			m_bLocked = ksFALSE;
		}

		/**
		 * ロック状態かのチェック
		 * @retval	ksTRUE		ロック状態
		 * @retval	ksFALSE		アンロック状態
		 */
		KsBool		isLocked() const { return m_bLocked; }

		/**
		 * キャスト用
		 */
		operator const void*() const { return m_bLocked ? this : 0; }

	private:
		Mutex&			m_mutex;		/**< Mutex			*/
		KsBool			m_bLocked;		/**< ロックフラグ	*/
};


#endif /* __KSTHREADLOCK_H__ */

