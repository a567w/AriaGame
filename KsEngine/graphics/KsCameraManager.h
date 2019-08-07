/************************************************************************************************/
/** 
 * @file		KsCameraManager.h
 * @brief		�J�����Ǘ�
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSCAMERAMANAGER_H__
#define __KSCAMERAMANAGER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsCameraManager
 * @brief		�J�����Ǘ��N���X
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsCameraManager : public KsSingleton< KsCameraManager >
{
	public:
		/**
		 * �V���O���g���̎Q�Ƃ��擾
		 * @return							�V���O���g���̎Q��
		 */
		static KsCameraManager&				getInstance();
		
		/**
		 * �V���O���g���̃|�C���^���擾
		 * @return							�V���O���g���̃|�C���^
		 */
		static KsCameraManager*				getInstancePtr();

		/**
		 * �R���X�g���N�^
		 */
											KsCameraManager();

		/**
		 * �f�X�g���N�^
		 */
		virtual								~KsCameraManager();

		/**
		 * ����������(�}�l�[�W���ɓo�^���ꂽ�Ƃ��ɓo�^)
		 * @param		pParam				�p�����[�^
		 * @return							���[�U�[�p�����[�^
		 */
		virtual void*						initialize( void* pParam );

		/**
		 * �^�X�N�̎��s
		 * @param		pParam				�p�����[�^
		 * @return							���[�U�[�p�����[�^
		 */
		virtual void*						execute( void* pParam );

		/**
		 * �`�揈��
		 * @param		pParam				�p�����[�^
		 * @return							���[�U�[�p�����[�^
		 */
		virtual void*						render( void* pParam );

		/**
		 * �㏈���֐��Ń������[����폜�����Ƃ��ɌĂ΂��
		 * @param		pParam				�p�����[�^
		 * @return							���[�U�[�p�����[�^
		 */
		virtual void*						terminate( void* pParam );

		/**
		 * �A�N�e�B�u�J�������Z�b�g����
		 * @param							�J����
		 */
		void								setActiveCamera( KsCamera* pCamera );

		/**
		 * �A�N�e�B�u�J�������Z�b�g����
		 * @param							�J����
		 */
		void								setActiveCamera( KsUInt32 index ) { m_pActiveCamera = m_pCameras[ index ]; }

		/**
		 * �A�N�e�B�u�J�������擾����
		 * @return							�A�N�e�B�u�J����
		 */
		KsCamera*							getActiveCamera() { return m_pActiveCamera; }

		/**
		 * �J�������擾����
		 * @return							�J����
		 */
		KsCamera*							getCamera( KsUInt32 index ) { return m_pCameras[ index ]; }

		/**
		 * �J�������Z�b�g����
		 * @param							�J����
		 */
		void								addCamera( KsCamera* pCamera );

		/**
		 * �J�������폜����
		 * @param							�J����
		 */
		void								removeCamera( KsCamera* pCamera );

	protected:
		KsCamera*							m_pActiveCamera;	/**< �A�N�e�B�u�J����		*/
		KsArray<KsCamera*>					m_pCameras;			/**< �J�������X�g		*/
};


#endif		/* __KSCAMERAMANAGER_H__ */



