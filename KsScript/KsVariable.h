/************************************************************************************************/
/** 
 * @file		KsVariable.h
 * @brief		�ϐ��N���X
 * @author		Tsukasa Kato
 * @date		2006/10/17
 * @since		2006/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSVARIABLE_H__
#define __KSVARIABLE_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsTypeScript.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * �X�N���v�g�p�̕ϐ�
 * @class	KsVariable
 * @author	Tsukasa Kato
 * @since   2006/--/--
 * @version 2006/--/--
 */
/************************************************************************************************/
class ksSCRIPT_API KsVariable
{
	public:
		ksVALUE_TYPE				m_type;			/**< �l�̃^�C�v		*/
		KsValue						m_value;		/**< �l				*/

	public:
		/**
		 * �R���X�g���N�^
		 */
									KsVariable();

		/**
		 * �R���X�g���N�^
		 * @param	value_int		�����l
		 */
									KsVariable( KsInt32 value_int );

		/**
		 * �R���X�g���N�^
		 * @param	value_float		�����l
		 */
									KsVariable( KsReal value_float );

		/**
		 * �^�C�v���擾����
		 */
		ksVALUE_TYPE				getType() const;

		/**
		 * �����l���Z�b�g����
		 * @param	value_int		�����l
		 */
		void						setInt( KsInt32 value_int );

		/**
		 * �����l���Z�b�g����
		 * @param	value_float		�����l
		 */
		void						setFloat( KsReal value_float );

		/**
		 * �n���h�����Z�b�g����
		 * @param	value_handle	�����l
		 */
		void						setHandle( KsHandle value_handle );

		/**
		 * �����l���擾����
		 * @return					�����l
		 */
		KsReal						getFloat() const;

		/**
		 * �����l���擾����
		 * @return					�����l
		 */
		KsInt32					getInt() const;

		/**
		 * �n���h�����擾����
		 * @return					�n���h��
		 */
		KsHandle					getHandle() const;

		/**
		 * �ϐ��l���擾����
		 * @return					�ϐ��l
		 */
		KsValue						getValue() const;

		/**
		 * =���Z�q�I�[�o�[���[�h�i�l�̑���j
		 * @param	value			�ϐ��l�̎Q��
		 * @return					�������g�̎Q��
		 */
		KsVariable&					operator=( const KsVariable& value );
};

#endif		/* __KSVARIABLE_H__ */

