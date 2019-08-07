/************************************************************************************************/
/** 
 * @file		StSceneManager.h
 * @brief		�V�[���Ǘ�
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __STSCENEMANAGER_H__
#define __STSCENEMANAGER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "StScene.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * �V�[�����ƂɊǗ�����
 */
/************************************************************************************************/
typedef enum _stGAME_SCENE_KIND
{
	stGAME_SCENE_NONE          =  0,					/**< �V�[���Ȃ�						*/
	stGAME_SCENE_LOGO          =  1,					/**< ���S							*/
	stGAME_SCENE_TITLE         =  2,					/**< �^�C�g���X�^�[�g���				*/
	stGAME_SCENE_TITLE_SELECT  =  3,					/**< �^�C�g���I�����					*/
	stGAME_SCENE_GUNDAM_MENU   =  4,					/**< �K���_���V���[�Y�őI�����j��		*/
	stGAME_SCENE_GGENE_MENU    =  5,					/**< G�W�F�l�V���[�Y�őI�����j��		*/
	stGAME_SCENE_MUSIC_GALLERY =  6,					/**< �~���[�W�b�N�M�������[			*/
	stGAME_SCENE_OPTION        =  7,					/**< �I�v�V����						*/
	stGAME_SCENE_DEMO_MOVI     =  8,					/**< �f�����[�r�[�Đ�					*/
	stGAME_SCENE_MOVI          =  9,					/**< ���[�r�[�Đ�					*/
	stGAME_SCENE_CREDIT        = 10,					/**< �N���W�b�g���					*/
	stGAME_SCENE_FORCE32       = 0x7fffffff,			/**< ����32�r�b�g					*/

}stGAME_SCENE_KIND;


/************************************************************************************************/
/**
 * @class		StSceneManager
 * @brief		�V�[���Ǘ��^�X�N
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		�Ȃ�
 */
/************************************************************************************************/
class StSceneManager : public StTask
{
	public:
		/**
		 * �R���X�g���N�^
		 */
											StSceneManager();

		/**
		 * �f�X�g���N�^
		 */
		virtual								~StSceneManager();
	
	protected:
		/**
		 * ����������(�}�l�[�W���ɓo�^���ꂽ�Ƃ��ɓo�^)
		 * @param		pParam				�p�����[�^
		 */
		virtual void*						initialize( void* pParam );

		/**
		 * �^�X�N�̎��s
		 * @param		pParam				�p�����[�^
		 */
		virtual void*						execute( void* pParam );

		/**
		 * �`�揈��
		 * @param		pParam				�p�����[�^
		 */
		virtual void*						render( void* pParam );

		/**
		 * �㏈���֐��Ń������[����폜�����Ƃ��ɌĂ΂��
		 * @param		pParam				�p�����[�^
		 */
		virtual void*						terminate( void* pParam );

	private:
		/**
		 * �w��V�[���𐶐�����
		 * @param		scene				�V�[��
		 * @return							���������V�[���̃|�C���^
		 */
		StScene*							createScene( stGAME_SCENE_KIND scene );

		/**
		 * �w��V�[����ǉ�����
		 * @param		scene				�V�[��
		 */
		void								addScene( stGAME_SCENE_KIND scene );

		//sceneCheck()
		//checkScene( )

	private:
		stGAME_SCENE_KIND					m_scene;	/**< ���݂̃V�[��	*/
		
		/* scene�}�l�[�W���̂ق��Ō��݂̃J�����ƃ��[���h���Ǘ����� */
		// �}�l�[�W���̂ق���
		//StCamera*							m_pCurrentCamera;
		//StCamera*							getNextCamera();
};


#endif /* __STSCENEMANAGER_H__ */

