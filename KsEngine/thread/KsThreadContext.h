/************************************************************************************************/
/** 
 * @file		KsThreadContext.h
 * @brief		�X���b�h�R���e�L�X�g
 * @author		Tsukasa Kato
 * @date		2004/08/17
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSTHREADCONTEXT_H__
#define __KSTHREADCONTEXT_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                          */
/*==============================================================================================*/
#include "KsMutex.h"
#include "KsEvent.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * �X���b�h
 * @class	KsThreadContext
 * @author  Tsukasa Kato
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsThreadContext
{
	public:
		/**
		 * �R���X�g���N�^
		 */
								KsThreadContext();

		/**
		 * �f�X�g���N�^
		 */
								~KsThreadContext();

		/** 
		 * == ���Z�q�I�[�o�[���[�h
		 * @retval	ksTRUE		������
		 * @retval	ksFALSE		�������Ȃ�
		 */
		KsBool					operator == ( const KsThread& rhs ) const;

		/** 
		 * != ���Z�q�I�[�o�[���[�h
		 * @retval	ksTRUE		�������Ȃ�
		 * @retval	ksFALSE		������
		 */
		KsBool					operator != ( const KsThread& rhs ) const;

		//void					create( const char* pName, MemoryAllocator*     pAllocator = nullptr );

		/**
		 * �X���b�h��j������
		 */
		void					destroy();

		/**
		 * �X���b�h�������J�n����
		 */
		void					start();

		/**
		 * �X���b�h�̏I����ҋ@����
		 */
		void					join();

		/**
		 * �X���b�h�h�c���擾����
		 * @return	�X���b�h�h�c
		 */
		KsUInt32				getID() const { return m_id; }

		/**
		 * �v���C�I���e�B���Z�b�g����
		 * @param	priority	�v���C�I���e�B
		 */
		void					setPriority( ksTHREAD_PRIORITY_TYPE priority );

		/**
		 * �g�p�v���Z�b�T���Z�b�g����
		 * @param	prosessor	�g�p�v���Z�b�T�ԍ�
		 */
		KsBool					setProcessor( KsUInt32 prosessor );

		/**
		 * �X���b�h��ҋ@����
		 */
		void					wait( KsHandle handle );

		/**
		 * �X���b�h�̃��C���֐�
		 * @return	���s�I������
		 */
		virtual KsUInt32		threadMain();

		/**
		 * �w�莞�Ԍ��݂̃X���b�h�̎��s���x�~����
		 * @param	time		�҂�����(ms)
		 */
		static void				sleep( const KsUInt32 time );

		/**
		 * ���݂̃X���b�h�̎��s�𒆒f���đ��̃X���b�h�֎��s������܂��B
		 */
		static void				yield();

		/**
		 * �w�肳�ꂽ�ϐ��̒l���C���N�������g���i1 ���₵�܂��j
		 */
		static KsLong			interlockedIncrement( KsLong* pCount );

		/**
		 * �w�肳�ꂽ�ϐ��̒l���f�N�������g���i1 ���炵�܂��j
		 */
		static KsLong			interlockedDecrement( KsLong* pCount );

		/**
		 * �X���b�h�̃��C���֐�
		 * @param	pParam		�X���b�h�p�����[�^
		 */
		friend static KsUInt32 __stdcall KsThreadMainFunc( void* pParam );

	private:
		KsHandle				m_handle;		/**< �X���b�h�n���h��						*/
		KsUInt32				m_id;			/**< �X���b�hID							*/
		KsBool					m_bJoin;		/**< �X���b�h�o�^��Ԃ��ǂ����̃t���O		*/
		KsThreadParam			m_param;		/**< �X���b�h�p�����[�^					*/
};

#endif		/* __KSTHREADCONTEXT_H__ */

