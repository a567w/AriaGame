/************************************************************************************************/
/** 
 * @file		KsMutex.h
 * @brief		�r������N���X
 * @author		Tsukasa Kato
 * @date		2004/08/17
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMUTEX_H__
#define __KSMUTEX_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                          */
/*==============================================================================================*/
#include "KsThreadLock.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class	KsMutex
 * @brief	�r������
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
		 * �R���X�g���N�^
		 */
							KsMutex( KsBool bCriticalSection = ksTRUE );

		/**
		 * �f�X�g���N�^
		 */
							~KsMutex();

	public:
		/**
		 * ���b�N����
		 */
		void				lock();

		/**
		 * ���b�N����
		 * @param	state	���b�N�X�e�[�^�X(���g�p)
		 */
		void				lock( void* state );

		/**
		 * �A�����b�N����
		 */
		void				unlock();

		/**
		 * �A�����b�N����
		 * @param	state	���b�N�X�e�[�^�X(���g�p)
		 */
		void				unlock( void* state );

	private:
		void*				m_mutex;				/**< �r������p�n���h��		*/
		KsBool				m_critical_section;		/**< �N���e�B�J���Z�N�V����	*/
};

/************************************************************************************************/
/**
 * �r������
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
		 * �R���X�g���N�^
		 */
							KsMutexTry();

		/**
		 * �f�X�g���N�^
		 */
							~KsMutexTry();

	public:
		/**
		 * ���b�N����
		 */
		void				lock();

		/**
		 * ���b�N����
		 */
		void				lockTry();

		/**
		 * ���b�N����
		 * @param	state	���b�N�X�e�[�^�X(���g�p)
		 */
		void				lock( void* state );

		/**
		 * �A�����b�N����
		 */
		void				unlock();

		/**
		 * �A�����b�N����
		 * @param	state	���b�N�X�e�[�^�X(���g�p)
		 */
		void				unlock( void* state );

	private:
		void*				m_mutex;				/**< �r������p�n���h��		*/
		KsBool				m_critical_section;		/**< �N���e�B�J���Z�N�V����	*/
};

/************************************************************************************************/
/**
 * �r������
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
		 * �R���X�g���N�^
		 */
							KsMutexTime();

		/**
		 * �f�X�g���N�^
		 */
							~KsMutexTime();

	public:
		/**
		 * ���b�N����
		 */
		void				lock();

		/**
		 * ���b�N����
		 */
		void				lockTry();

		/**
		 * �w�莞�ԃ��b�N����
		 * @param	time	���b�N����(ms)
		 */
		void				lockTime( KsUInt32 time );

		/**
		 * ���b�N����
		 * @param	state	���b�N�X�e�[�^�X(���g�p)
		 */
		void				lock( void* state );

		/**
		 * �A�����b�N����
		 */
		void				unlock();

		/**
		 * �A�����b�N����
		 * @param	state	���b�N�X�e�[�^�X(���g�p)
		 */
		void				unlock( void* state );

	private:
		void*				m_mutex;				/**< �r������p�n���h��		*/

};

/************************************************************************************************/
/**
 * @class	KsCriticalSection
 * @brief	�r������
 * @author  Tsukasa Kato
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsCriticalSection
{
	public:
		/**
		 * �R���X�g���N�^
		 */
							KsCriticalSection();

		/**
		 * �f�X�g���N�^
		 */
							~KsCriticalSection();

		/**
		 * ���b�N����
		 */
		void				lock();

		/**
		 * �A�����b�N����
		 */
		void				unlock();

	private:
		CRITICAL_SECTION	m_cs;
};

#endif /* __KSMUTEX_H__ */

