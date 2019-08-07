/************************************************************************************************/
/** 
 * @file		KsThreadLock.h
 * @brief		�X���b�h���b�N
 * @author		Tsukasa Kato
 * @date		2004/08/17
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSTHREADLOCK_H__
#define __KSTHREADLOCK_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsThreadCondition;

/************************************************************************************************/
/**
 * ���b�N�I�v�V����
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
		 * �R���X�g���N�^
		 */
								KsThreadLockOps(){}
	public:
		/**
		 * ���b�N����
		 * @param		m		���b�N����r������p�N���X
		 */
		static void			lock( Mutex& m ) { m.lock(); }

		/** 
		 * ���b�N�ł��邩�`�F�b�N���Ăł���Ȃ烍�b�N����
		 * @param		m		���b�N����r������p�N���X
		 */
		static KsBool			lockTry( Mutex& m ) { return m.lockTry(); }

		/**
		 * �w�莞�ԃ��b�N����
		 * @param		m		���b�N����r������p�N���X
		 */
		static KsBool			lockTime( Mutex& m, KsUInt32 time ) { return m.lockTime( time ); }

		/**
		 * �w��X�e�[�^�X�Ń��b�N����
		 * @param		m		���b�N����r������p�N���X
		 * @param		state	���b�N�X�e�[�^�X
		 */
		static void			lock( Mutex& m, void* state ) { m.lock( state ); }

		/**
		 * �A�����b�N����
		 * @param		m		�A�����b�N����r������p�N���X
		 */
		static void			unlock( Mutex& m ) { m.unlock(); }

		/**
		 * �A�����b�N����
		 * @param		m		�A�����b�N����r������p�N���X
		 * @param		state	�A�����b�N�X�e�[�^�X
		 */
		static void			unlock( Mutex& m, void* state ) { m.unlock( state ); }
};

/************************************************************************************************/
/**
 * ���b�N
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
		typedef Mutex		mutexType;	/**< Mutex�^�C�v	*/

	public:
		/**
		 * �R���X�g���N�^
		 * @param	mx	Mutex
		 * @param	initLoacked		�������b�N���邩
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
		 * �f�X�g���N�^
		 */
		~KsThreadLock()
		{
			if( m_bLocked ){
				unlock();
			}
		}

		/**
		 * ���b�N����
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
		 * �A�����b�N����
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
		 * ���b�N��Ԃ��̃`�F�b�N
		 * @retval	ksTRUE		���b�N���
		 * @retval	ksFALSE		�A�����b�N���
		 */
		KsBool		isLocked() const { return m_bLocked; }

		/**
		 * �L���X�g�p
		 */
		operator const void*() const { return m_bLocked ? this : 0; }

	private:
		Mutex&			m_mutex;		/**< Mutex			*/
		KsBool			m_bLocked;		/**< ���b�N�t���O	*/
};

/************************************************************************************************/
/**
 * ���b�N
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
		 * �R���X�g���N�^
		 * @param	m	Mutex
		 * @param	initLoacked		�������b�N���邩
		 */
		explicit KsThreadLockTry( Mutex& m ) : m_mutex( m ), m_bLocked( ksFALSE )
		{
			try_lock();
		}

		/**
		 * �R���X�g���N�^
		 * @param	m	Mutex
		 * @param	initLoacked		�������b�N���邩
		 */
		KsThreadLockTry( Mutex& m, KsBool initLocked=ksTRUE ) : m_mutex( m ), m_bLocked( ksFALSE )
		{
			if( initLocked ){
				lock();
			}
		}

		/**
		 * �f�X�g���N�^
		 */
		~KsThreadLockTry()
		{
			if( m_bLocked ){
				unlock();
			}
		}

		/**
		 * ���b�N����
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
		 * ���b�N��Ԃ��̃`�F�b�N
		 * @retval	ksTRUE		���b�N���
		 * @retval	ksFALSE		�A�����b�N���
		 */
		KsBool	lockTry()
		{
			if( m_bLocked ){
				throw lock_error();
			}

			return ( m_bLocked = KsThreadLockOps<TryMutex>::lockTry( m_mutex ) );
		}

		/**
		 * �A�����b�N����
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
		 * ���b�N��Ԃ��̃`�F�b�N
		 * @retval	ksTRUE		���b�N���
		 * @retval	ksFALSE		�A�����b�N���
		 */
		KsBool		isLocked() const { return m_bLocked; }

		/**
		 * �L���X�g�p
		 */
		operator const void*() const { return m_bLocked ? this : 0; }

	private:
		Mutex&			m_mutex;		/**< Mutex			*/
		KsBool			m_bLocked;		/**< ���b�N�t���O	*/
};

/************************************************************************************************/
/**
 * ���b�N
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
		 * �R���X�g���N�^
		 * @param	m				Mutex
		 * @param	initLoacked		�������b�N���邩
		 */
		explicit KsThreadLockTime( Mutex& m, KsUInt32 time ) : m_mutex( m ), m_bLocked( ksFALSE )
		{
			lockTime( time );
		}

		/**
		 * �R���X�g���N�^
		 * @param	m				Mutex
		 * @param	initLoacked		�������b�N���邩
		 */
		KsThreadLockTime( Mutex& m, KsBool initLocked=ksTRUE ) : m_mutex( m ), m_bLocked( ksFALSE )
		{
			if( initLocked ){
				lock();
			}
		}

		/**
		 * �f�X�g���N�^
		 */
		~KsThreadLockTime()
		{
			if( m_bLocked ){
				unlock();
			}
		}

		/**
		 * ���b�N����
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
		 * ���b�N��Ԃ��̃`�F�b�N
		 * @retval	ksTRUE		���b�N���
		 * @retval	ksFALSE		�A�����b�N���
		 */
		KsBool	lockTry()
		{
			if( m_bLocked ){
				throw lock_error();
			}

			return ( m_bLocked = KsThreadLockOps<Mutex>::lockTry( m_mutex ) );
		}


		/**
		 * ���ԂŃ��b�N����
		 * @param	time		���b�N����
		 * @retval	ksTRUE		���b�N���
		 * @retval	ksFALSE		�A�����b�N���
		 */
		KsBool	lockTime( KsUInt32 time )
		{
			if( m_bLocked ){
				throw lock_error();
			}

			return ( m_bLocked = KslockOps<Mutex>::lockTime( m_mutex, time ) );
		}

		/**
		 * �A�����b�N����
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
		 * ���b�N��Ԃ��̃`�F�b�N
		 * @retval	ksTRUE		���b�N���
		 * @retval	ksFALSE		�A�����b�N���
		 */
		KsBool		isLocked() const { return m_bLocked; }

		/**
		 * �L���X�g�p
		 */
		operator const void*() const { return m_bLocked ? this : 0; }

	private:
		Mutex&			m_mutex;		/**< Mutex			*/
		KsBool			m_bLocked;		/**< ���b�N�t���O	*/
};


#endif /* __KSTHREADLOCK_H__ */

