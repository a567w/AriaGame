/************************************************************************************************/
/** 
 * @file		KsHandleObject.h
 * @brief		�n���h���I�u�W�F�N�g
 * @author		Tsukasa Kato
 * @date		2006/10/17
 * @since		2006/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSHANDLEOBJECT_H__
#define __KSHANDLEOBJECT_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsTypeScript.h"

/************************************************************************************************/
/**
 * ������Ȃǂ̕ϐ��I�u�W�F�N�g�p
 * @class	KsHandleObject
 * @author	Tsukasa Kato
 * @since   2006/--/--
 * @version 2006/--/--
 */
/************************************************************************************************/
class ksSCRIPT_API KsHandleObject
{
		friend class KsHandleManager;
		friend class KsVirtualMachine;
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsHandleObject() : m_pNext( 0 ) {}

		/**
		 * �f�X�g���N�^
		 */
		virtual					~KsHandleObject(){}

		/**
		 * �l�̃^�C�v
		 * @return					�l�̃^�C�v
		 */
		virtual ksVALUE_TYPE		getType() const = 0;

		/**
		 * �Q��(�n���h��)
		 * @return					�n���h��
		 */
		virtual KsHandle			getHandle() { return reinterpret_cast<KsHandle>( this ); }

	protected:
		KsHandleObject*				m_pNext;	/**< ���̃n���h���|�C���^	*/
};


#endif /* __KSHANDLEOBJECT_H__ */

