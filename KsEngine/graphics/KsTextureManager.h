/************************************************************************************************/
/** 
 * @file		KsTextureManager.h
 * @brief		�e�N�X�`���}�l�[�W��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSTEXTUREMANAGER_H__
#define __KSTEXTUREMANAGER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsTexture.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsTextureManager
 * @brief		�e�N�X�`���}�l�[�W��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		�{���́A�n�b�V���e�[�u���Ȃǂ��g�p�����ق������������܂�e�N�X�`���́A
 *				���܂�A�g��Ȃ��͂��Ȃ̂Ő��`�ŒT������B
 */
/************************************************************************************************/
class ksENGINE_API KsTextureManager : public KsSingleton< KsTextureManager >
{
	public:
		/**
		 * �R���X�g���N�^
		 */
											KsTextureManager();

		/**
		 * �f�X�g���N�^
		 */
		virtual								~KsTextureManager();

		/**
		 * �w�肵�����O�̃e�N�X�`������������
		 * �擾������ɎQ�ƃJ�E���g��������K�v������
		 * @param	pFileName				�t�@�C����
		 * @return							���������e�N�X�`���̃|�C���^
		 */
		virtual KsTexture*					find( const KsChar* pFileName );

		/**
		 * �������Č���������Q�ƃJ�E���g���A�b�v����
		 * @param	pFileName				�t�@�C����
		 * @return							���������e�N�X�`���̃|�C���^
		 */
		virtual KsTexture*					findRefInc( const KsChar* pFileName );

		/**
		 * �e�N�X�`����ǉ�����
		 * DEBUG���[�h�̂Ƃ��́A2�d�o�^�`�F�b�N������
		 * @param	pTexture				�ǉ�����e�N�X�`���̃|�C���^
		 * @retval	ksTRUE					����
		 * @retval	ksFALSE					���s
		 */
		virtual KsBool						add( KsTexture* pTexture );

		/**
		 * �e�N�X�`�����}�l�[�W�������菜��
		 * @param	pTexture				��菜���e�N�X�`���̃|�C���^
		 * @retval	ksTRUE					����
		 * @retval	ksFALSE					���s
		 */
		virtual KsBool						remove( KsTexture* pTexture );

		/**
		 * �e�N�X�`�����폜����
		 * @param	pTexture				�폜����e�N�X�`���̃|�C���^
		 * @retval	ksTRUE					����
		 * @retval	ksFALSE					���s
		 */
		virtual KsBool						destroy( KsTexture* pTexture );

		/**
		 * ���ׂẴe�N�X�`����j������(�Q�ƃJ�E���g�֌W�Ȃ��j�������)
		 * @retval	ksTRUE					����
		 * @retval	ksFALSE					���s
		 */
		virtual KsBool						destroyAll();

		/**
		 * �V���O���g���̎Q�Ƃ��擾
		 * @return							�V���O���g���̎Q��
		 */
		static KsTextureManager&			getInstance();
		
		/**
		 * �V���O���g���̃|�C���^���擾
		 * @return							�V���O���g���̃|�C���^
		 */
		static KsTextureManager*			getInstancePtr();

	protected:
		KsTexture*							m_pTop;		/**< ���X�g�̐擪�|�C���^	*/
};

#endif		/* __KSTEXTUREMANAGER_H__ */




