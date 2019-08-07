/*************************************************************************************************/
/** 
 * @file	KsSmartPointer.h
 * @brief	�V���O���g��
 * @author	Tsukasa Kato
 * @date	2003/10/25
 * @since	2003/10/25
 */
/*************************************************************************************************/
#ifndef __KSSMARTPOINTER_H__
#define __KSSMARTPOINTER_H__

/*===============================================================================================*/
/*								<< �C���N���[�h�t�@�C�� >>										 */
/*===============================================================================================*/
#include "KsSmartPointerObject.h"

/*===============================================================================================*/
/*										<< ��` >>												 */
/*===============================================================================================*/

/*************************************************************************************************/
/**
 * �X�}�[�g�|�C���^(�����N����)
 *	@author	 kato tukasa
 * 	@since   2002/12/05
 *	@version 2002/12/05
 */
/*************************************************************************************************/
template< typename T > class KsSmartPtr : public KsSmartPtrObject
{
		//friend	class KsSmartPtr<T>;
	public:
		/* �^���Z�b�g */
		typedef T							element_type;
		
		/* explicit �����I�Ȍ^�`�F�b�N�p */
		explicit							KsSmartPtr( T* p = 0 );
		
		/**
		 * �R�s�[�R���X�g���N�^
		 */
											KsSmartPtr( const KsSmartPtr<T>& ref );
		
		/**
		 * �f�X�g���N�^
		 */
											~KsSmartPtr();

		/**
		 * �폜����
		 */
		void								destroy();

		/**
		 * �����N�J�E���g���擾
		 */
		KsInt32							getCount() const;

		/**
		 * = ���Z�q�I�[�o�[���[�h
		 */
		KsSmartPtr<T>&						operator = ( const KsSmartPtr<T>& ref );

		/**
		 * = ���Z�q�I�[�o�[���[�h
		 */
		KsSmartPtr<T>&						operator = ( const T* ptr );


		KsBool								operator < ( const KsSmartPtr<T>& ref ) const;

		T**									operator&()	const { return &m_ptr; }
		T&									operator*()	const { return *m_ptr; }
		T*									operator->()	const { return  m_ptr; }
		T*									get()			const { return  m_ptr; }

	private:
		T*									m_ptr;		/**< �|�C���^����			*/
		mutable const KsSmartPtr<T>*		m_pPrev;	/**< �O�̃����N�|�C���^		*/
		mutable const KsSmartPtr<T>*		m_pNext;	/**< ���̃����N�|�C���^	*/

};

/*************************************************************************************************/
/*---------------------------<< �C�����C�������w�b�_�[�t�@�C�� >>--------------------------------*/
								#include "KsSmartPointer.inl"
/*-----------------------------------------------------------------------------------------------*/
/*************************************************************************************************/


#endif	/* __KSSMARTPOINTER_H__ */
