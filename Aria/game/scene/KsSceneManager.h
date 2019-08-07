/************************************************************************************************/
/** 
 * @file		KsSceneManager.h
 * @brief		�V�[���Ǘ�
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSSCENEMANAGER_H__
#define __KSSCENEMANAGER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsScene.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsSceneManager
 * @brief		�V�[���Ǘ��^�X�N
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		�Ȃ�
 */
/************************************************************************************************/
class KsSceneManager : public KsTaskManager
{
	public:
		/**
		 * �R���X�g���N�^
		 */
											KsSceneManager();

		/**
		 * �f�X�g���N�^
		 */
		virtual								~KsSceneManager();
	
	protected:
		/**
		 * ����������
		 * @retval		ksTRUE				����
		 * @retval		ksFALSE				���s
		 */
		KsBool								initialize();

		/**
		 * �㏈��
		 * @retval		ksTRUE				����
		 * @retval		ksFALSE				���s
		 */
		KsBool								terminate();

		/**
		 * �^�X�N�̎��s
		 * @param		pParam				�p�����[�^
		 */
		virtual void						execute( void* pParam );

		/**
		 * �`�揈��
		 * @param		pParam				�p�����[�^
		 */
		virtual void						render( void* pParam );

	private:
		/**
		 * �w��V�[���𐶐�����
		 * @param		scene				�V�[��
		 * @return							���������V�[���̃|�C���^
		 */
		KsScene*							createScene( ksSCENE_TYPE scene );

		/**
		 * �w��V�[���𐶐�����
		 * @param		scene				�V�[��
		 * @return							���������V�[���̃|�C���^
		 */
		KsBool								addScene( ksSCENE_TYPE scene );

		/**
		 * �w��V�[�����폜����
		 * @param		pScene				�V�[��
		 */
		void								destroyScene( KsScene* pScene );

	private:
		ksSCENE_TYPE						m_scene;
		KsScene*							m_pScene;	/**< ���݂̃V�[��	*/
		//StCamera*							m_pCurrentCamera;
		//StCamera*							getNextCamera();
};


#endif /* __KSSCENEMANAGER_H__ */
