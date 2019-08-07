/************************************************************************************************/
/** 
 * @file		KsMutex.h
 * @brief		排他制御クラス
 * @author		Tsukasa Kato
 * @date		2004/08/17
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMUTEX_H__
#define __KSMUTEX_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                          */
/*==============================================================================================*/
#include "KsThreadLock.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class	KsMutex
 * @brief	排他制御
 * @author  Tsukasa Kato
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsMutex
{
	public:
		friend class KsThreadLockOps< KsMutex >;

		typedef KsThreadLock< KsMutex > scoped_lock;

	public:
		/**
		 * コンストラクタ
		 */
							KsMutex( KsBool bCriticalSection = ksTRUE );

		/**
		 * デストラクタ
		 */
							~KsMutex();

	public:
		/**
		 * ロックする
		 */
		void				lock();

		/**
		 * ロックする
		 * @param	state	ロックステータス(未使用)
		 */
		void				lock( void* state );

		/**
		 * アンロックする
		 */
		void				unlock();

		/**
		 * アンロックする
		 * @param	state	ロックステータス(未使用)
		 */
		void				unlock( void* state );

	private:
		void*				m_mutex;				/**< 排他制御用ハンドル		*/
		KsBool				m_critical_section;		/**< クリティカルセクション	*/
};

/************************************************************************************************/
/**
 * 排他制御
 * @class	KsMutexTry
 * @author  Tsukasa Kato
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class KsMutexTry
{
	public:
		friend class KsThreadLockOps<KsMutexTry>;

		typedef KsThreadLock<KsMutexTry>		scoped_lock;
		typedef KsThreadLockTry<KsMutexTry>	scoped_try_lock;

	public:
		/**
		 * コンストラクタ
		 */
							KsMutexTry();

		/**
		 * デストラクタ
		 */
							~KsMutexTry();

	public:
		/**
		 * ロックする
		 */
		void				lock();

		/**
		 * ロックする
		 */
		void				lockTry();

		/**
		 * ロックする
		 * @param	state	ロックステータス(未使用)
		 */
		void				lock( void* state );

		/**
		 * アンロックする
		 */
		void				unlock();

		/**
		 * アンロックする
		 * @param	state	ロックステータス(未使用)
		 */
		void				unlock( void* state );

	private:
		void*				m_mutex;				/**< 排他制御用ハンドル		*/
		KsBool				m_critical_section;		/**< クリティカルセクション	*/
};

/************************************************************************************************/
/**
 * 排他制御
 * @class	KsMutexTime
 * @author  Tsukasa Kato
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class KsMutexTime
{
	public:
		friend class KsThreadLockOps<KsMutexTime>;

		typedef KsThreadLock<KsMutexTime>		scoped_lock;
		typedef KsThreadLockTry<KsMutexTime>	scoped_try_lock;
		typedef KsThreadLockTime<KsMutexTime>	scoped_timed_lock;

	public:
		/**
		 * コンストラクタ
		 */
							KsMutexTime();

		/**
		 * デストラクタ
		 */
							~KsMutexTime();

	public:
		/**
		 * ロックする
		 */
		void				lock();

		/**
		 * ロックする
		 */
		void				lockTry();

		/**
		 * 指定時間ロックする
		 * @param	time	ロック時間(ms)
		 */
		void				lockTime( KsUInt32 time );

		/**
		 * ロックする
		 * @param	state	ロックステータス(未使用)
		 */
		void				lock( void* state );

		/**
		 * アンロックする
		 */
		void				unlock();

		/**
		 * アンロックする
		 * @param	state	ロックステータス(未使用)
		 */
		void				unlock( void* state );

	private:
		void*				m_mutex;				/**< 排他制御用ハンドル		*/

};

/************************************************************************************************/
/**
 * @class	KsCriticalSection
 * @brief	排他制御
 * @author  Tsukasa Kato
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsCriticalSection
{
	public:
		/**
		 * コンストラクタ
		 */
							KsCriticalSection();

		/**
		 * デストラクタ
		 */
							~KsCriticalSection();

		/**
		 * ロックする
		 */
		void				lock();

		/**
		 * アンロックする
		 */
		void				unlock();

	private:
		CRITICAL_SECTION	m_cs;
};

#endif /* __KSMUTEX_H__ */

