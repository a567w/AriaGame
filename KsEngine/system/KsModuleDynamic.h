/************************************************************************************************/
/** 
 * @file		KsModuleDynamic.h
 * @brief		DLL���W���[��
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMODULEDYNAMIC_H__
#define __KSMODULEDYNAMIC_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsModule.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 *  ���W���[���̃C���^�[�t�F�[�X�N���X
 *	@class		KsModule
 *	@brief		���W���[���̃C���^�[�t�F�[�X
 *	@since		2003/10/25
 *	@author		Tsukasa Kato
 */
/************************************************************************************************/
class ksENGINE_API KsModuleDynamic : public KsModule
{
	public:
		/**
		 * �R���X�g���N�^(������)
		 * @param	path				�p�X��
		 * @param	name				���W���[����
		 * @param	pKsModuleManager		���W���[���}�l�[�W��
		 */
										KsModuleDynamic( const KsString& path, const KsString& name, KsModuleManager* pModuleManager );

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsModuleDynamic();

		/**
		 * �L�����ǂ������擾����
		 * @retval	ksTRUE				�L��
		 * @retval	ksFALSE				����
		 */
		virtual KsBool					isValid() const { return ( m_pLib != 0 ); }

		/**
		 * �ÓI���W���[�������擾����
		 * @retval	ksTRUE				�ÓI���W���[���ł�
		 * @retval	ksFALSE				�ÓI���W���[���łȂ�
		 */
		virtual KsBool					isStatic() const { return ksFALSE; }

		/**
		 * ���I���W���[�������擾����
		 * @retval	ksTRUE				���I���W���[���ł�
		 * @retval	ksFALSE				���I���W���[���łȂ�
		 */
		virtual KsBool					isDynamic() const { return ksTRUE; }

		/**
		 * ���W���[�����̃G�N�X�|�[�g�֐��̃A�h���X���擾���܂��B
		 * @param			name		�G�N�X�|�[�g�֐���
		 * @return						���W���[�����̃G�N�X�|�[�g�֐��̃A�h���X
		 */
		virtual void*					getProcAddress( const KsString& name );

	protected:
		void*							m_pLib;			/**< ���C�u����		*/
		KsString						m_fullPath;		/**< �t���p�X		*/
};


#endif /* __KSMODULEDYNAMIC_H__ */



