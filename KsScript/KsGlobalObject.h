/************************************************************************************************/
/** 
 * @file		KsGlobalObject.h
 * @brief		�n���h���I�u�W�F�N�g
 * @author		Tsukasa Kato
 * @date		2006/10/17
 * @since		2006/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSGLOBALOBJECT_H__
#define __KSGLOBALOBJECT_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsStringObject.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * ������Ȃǂ̕ϐ��I�u�W�F�N�g�p
 * @class	KsGlobalObject
 * @author	Tsukasa Kato
 * @since   2006/--/--
 * @version 2006/--/--
 */
/************************************************************************************************/
class KsGlobalObject : public KsStringObject
{
		friend class KsHandleManager;
		friend class KsVirtualMachine;
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsGlobalObject(){}

		/**
		 * �R���X�g���N�^
		 * @param	pString			������
		 */
									KsGlobalObject( const KsChar* pString ) : KsStringObject( pString ) {}

		/**
		 * �f�X�g���N�^
		 */
		virtual					~KsGlobalObject(){}

		/**
		 * �l�̃^�C�v
		 * @return					�l�̃^�C�v(������)
		 */
		virtual ksVALUE_TYPE		getType() const { return m_variable.getType(); }

		/**
		 * �����̕ϐ����Z�b�g����
		 * @param	value			�����l
		 */
		void						setVarInt( KsInt32 value ){ m_variable.setInt( value ); }

		/**
		 * ���������l���Z�b�g����
		 * @param	value			���������l
		 */
		void						setVarFloat( KsReal value ){ m_variable.setFloat( value ); }

		/**
		 * �n���h�����Z�b�g����
		 * @param	value			�n���h���l
		 */
		void						setVarHandle( KsHandle value ){ m_variable.setHandle( value ); }

		/**
		 * �ϐ����Z�b�g����
		 * @param	value			�ϐ�
		 */
		void						setVariable( const KsVariable& variable ){ m_variable = variable; }

		/**
		 * �����l���擾����
		 * @return					�����l
		 */
		KsInt32					getVarInt() const { return m_variable.getInt(); }

		/**
		 * ���������l���擾����
		 * @return					�����l
		 */
		KsReal						getVarFloat() const { return m_variable.getFloat(); }

		/**
		 * �n���h���l���擾����
		 * @return					�����l
		 */
		KsHandle					getVarHandle() const { return m_variable.getHandle(); }

		/**
		 * �ϐ��l���擾����
		 * @return					�����l
		 */
		const KsVariable*			getVariable() { return &m_variable; }

	protected:
		KsVariable					m_variable;		/**< �ϐ��l�\��	*/
};


#endif /* __KSGLOBALOBJECT_H__ */

