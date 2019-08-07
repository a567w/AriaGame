/************************************************************************************************/
/** 
 * @file		KsSmartPointer.h
 * @brief		�z��o�[�W�����X�}�[�g�|�C���^
 * @author		Tsukasa Kato
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSSMARTPOINTERARRAY_H__
#define __KSSMARTPOINTERARRAY_H__
#if 0
/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsType.h"


/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 *	@class		KsSmartPtrArray
 *	@brief		�X�}�[�g�|�C���^
 *	@since		2005/10/25
 *	@author		tukasa kato
 */
/************************************************************************************************/
template<typename T> class KsSmartPtrArray : public KsSmartPtrObject
{
	public:
		/* �^���Z�b�g */
		typedef T				element_type;
		
	public:
		/**
		 * �R���X�g���N�^
		 */
		explicit				KsSmartPtrArray();
			
		/**
		 * �R���X�g���N�^
		 */
		explicit				KsSmartPtrArray( T* p, KsInt32 num = 0 );
		
		/**
		 * �R�s�[�R���X�g���N�^
		 */
								KsSmartPtrArray( const KsSmartPtrArray<T>& rhs );
		
		/**
		 * �f�X�g���N�^
		 */
		virtual				~KsSmartPtrArray();

		/**
		 * �폜����
		 */
		void					destroy()

		/**
		 * = ���Z�q�I�[�o�[���[�h
		 */
		KsSmartPtrArray<T>&		operator=( const KsSmartPtrArray<T>& rhs );

		/**
		 * = ���Z�q�I�[�o�[���[�h
		 */
		KsSmartPtrArray<T>&		operator=( const T* ptr );


		KsBool					operator < ( const KsSmartPtrArray<T>& rhs ) const { return *m_ptr < *rhs->get(); }

		T&						operator*()  const { return *m_ptr; }
		T*						operator->() const { return  m_ptr; }
		T*						get()        const  { return  m_ptr; }

		T**						operator&() const { return &m_ptr; }

		T&						operator [] ( KsInt32 index ){ return *get( index ); }

	private:
		T*						m_ptr;			/**< �|�C���^����	*/
		KsInt32				m_num;			/**< */
		KsInt32				m_sizeof;		/**< */
		KsSmartPtrArray<T>*		m_pPrev;
		KsSmartPtrArray<T>*		m_pNext;
};

#endif

/*************************************************************************************************/
/*---------------------------<< �C�����C�������w�b�_�[�t�@�C�� >>--------------------------------*/
								#include "KsSmartPointerArray.inl"
/*-----------------------------------------------------------------------------------------------*/
/*************************************************************************************************/

#endif	/* SMARTPOINTER_H */

#endif