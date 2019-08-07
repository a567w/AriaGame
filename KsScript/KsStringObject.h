/************************************************************************************************/
/** 
 * @file		KsStringObject.h
 * @brief		������I�u�W�F�N�g
 * @author		Tsukasa Kato
 * @date		2006/10/17
 * @since		2006/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSTRINGOBJECT_H__
#define __KSSTRINGOBJECT_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsTypeScript.h"
#include "KsHandleObject.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * ������Ȃǂ̕ϐ��I�u�W�F�N�g�p
 * @class	KsStringObject
 * @author	Tsukasa Kato
 * @since   2006/--/--
 * @version 2006/--/--
 */
/************************************************************************************************/
class KsStringObject : public KsHandleObject
{
		friend class KsHandleManager;
		friend class KsVirtualMachine;
	public:

		/**
		 * �R���X�g���N�^
		 */
									KsStringObject() : m_refCount( 0 ) {}

		/**
		 * �R���X�g���N�^
		 * @param	pString			������
		 */
									KsStringObject( const KsChar* pString ) : m_refCount( 0 ) { m_string = pString; }

		/**
		 * �f�X�g���N�^
		 */
		virtual					~KsStringObject(){}

		/**
		 * �l�̃^�C�v
		 * @return					�l�̃^�C�v(������)
		 */
		virtual ksVALUE_TYPE		getType() const { return ksVALUE_STRING; }

		/**
		 * �Q�ƃJ�E���g�A�b�v
		 */
		void						incRefCount() { ++m_refCount; }

		/**
		 * �Q�ƃJ�E���g�_�E��
		 */
		void						decRefCount() { --m_refCount; }

		/**
		 * ���݂̎Q�ƃJ�E���g�l���擾����
		 */
		KsInt32					getRefCount() { return m_refCount; }

		/**
		 * ��������擾����
		 * @return					������̎Q�ƒl
		 */
		const KsString&				getString() { return m_string; }

	protected:
		KsString					m_string;		/**< ������			*/
		KsInt32					m_refCount;		/**< �Q�ƃJ�E���g	*/
};


#endif /* __KSSTRINGOBJECT_H__ */

