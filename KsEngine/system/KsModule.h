/************************************************************************************************/
/** 
 * @file		KsModule.h
 * @brief		���W���[��
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMODULE_H__
#define __KSMODULE_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsType.h"
#include "KsString.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsModuleManager;

/************************************************************************************************/
/**
 *  ���W���[���̃C���^�[�t�F�[�X�N���X
 *	@class		KsModule
 *	@brief		���W���[���̃C���^�[�t�F�[�X
 *	@since		2003/10/25
 *	@author		Tsukasa Kato
 */
/************************************************************************************************/
class ksENGINE_API KsModule
{
		friend class KsModuleManager;

	protected:
		KsString						m_name;				/**< ���W���[����			*/
		KsModuleManager*				m_pModuleManager;	/**< ���W���[���}�l�[�W��	*/

	public:

		/**
		 * �R���X�g���N�^(������)
		 * @param	name				���W���[����
		 * @param	pKsModuleManager		���W���[���}�l�[�W��
		 */
										KsModule( const KsString& name, KsModuleManager* m_pModuleManager );

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsModule();

		/**
		 * �L�����ǂ������擾����
		 * @retval	ksTRUE				�L��
		 * @retval	ksFALSE				����
		 */
		virtual KsBool					isValid() const = 0;

		/**
		 * �ÓI���W���[�������擾����
		 * @retval	ksTRUE				�ÓI���W���[���ł�
		 * @retval	ksFALSE				�ÓI���W���[���łȂ�
		 */
		virtual KsBool					isStatic() const = 0;

		/**
		 * ���I���W���[�������擾����
		 * @retval	ksTRUE				���I���W���[���ł�
		 * @retval	ksFALSE				���I���W���[���łȂ�
		 */
		virtual KsBool					isDynamic() const = 0;

		/**
		 * ���W���[�����̃G�N�X�|�[�g�֐��̃A�h���X���擾���܂��B
		 * @param			name		�G�N�X�|�[�g�֐���
		 * @return						���W���[�����̃G�N�X�|�[�g�֐��̃A�h���X
		 */
		virtual void*					getProcAddress( const KsString& name ) = 0;

		/**
		 * ���W���[�������擾����
		 * @return						���W���[����
		 */
		const KsString&					getName() const { return m_name; }
};


#endif /* __KSMODULE_H__ */

