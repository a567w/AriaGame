/************************************************************************************************/
/** 
 * @file		KsThread.h
 * @brief		スレッド管理
 * @author		Tsukasa Kato
 * @date		2004/08/17
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSTHREADCONDITION_H__
#define __KSTHREADCONDITION_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

class ksENGINE_API KsConditionImpl
{
		friend class KsThreadCondition;

	public:
		KsConditionImpl();
		~KsConditionImpl();

		void				notify_one();
		void				notify_all();

		void				enter_wait();
		void				wait();
		KsBool				timed_wait( KsUInt32 time );

		void*				m_gate;
		void*				m_queue;
		void*				m_mutex;
		unsigned			m_gone;
		unsigned long		m_blocked;
		unsigned			m_waiting;
};

class ksENGINE_API KsThreadCondition
{
	public:
		/**
		 * コンストラクタ
		 */
		KsThreadCondition() {}

		/**
		 * デストラクタ
		 */
		~KsThreadCondition() {}

		template <typename L> void wait(L& lock)
		{
			if (!lock){
//				throw lock_error();
			}

			do_wait(lock.m_mutex);
		}

		template <typename L, typename Pr> void wait(L& lock, Pr pred)
		{
			if (!lock)
				throw lock_error();

			while (!pred())
				do_wait(lock.m_mutex);
		}

		template <typename L> KsBool timed_wait(L& lock, KsUInt32 time )
		{
			if (!lock)
				throw lock_error();

			return do_timed_wait(lock.m_mutex, time);
		}

		template <typename L, typename Pr> KsBool timed_wait(L& lock, KsUInt32 time, Pr pred)
		{
			if (!lock)
				throw lock_error();

			while (!pred())
			{
				if (!do_timed_wait(lock.m_mutex, time))
					return false;
			}

			return true;
		}

	private:
		KsConditionImpl		m_impl;

		template <typename M> void do_wait(M& mutex)
		{
			m_impl.enter_wait();

			typedef KsThreadLockOps<M> lock_ops;

			lock_ops::unlock( mutex );

			m_impl.wait();

			lock_ops::lock( mutex );

			#undef lock_ops
		}

		template <typename M> KsBool do_timed_wait(M& mutex, KsUInt32 time )
		{
			m_impl.enter_wait();

			typedef KsThreadLockOps<Mutex> lock_ops;

			void*	state;
			lock_ops::unlock( Mutex, state );

			KsBool ret = false;

			ret = m_impl.timed_wait(time);

			lock_ops::lock(mutex, state);
	#undef lock_ops

			return ret;
		}
};


#endif /* __KSTHREADCONDITION_H__ */


