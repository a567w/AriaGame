/************************************************************************************************/
/** 
 * @file		KsGameConfigManager.h
 * @brief		�Q�[���R���t�B�b�O
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSGAMECONFIGMANAGER_H__
#define __KSGAMECONFIGMANAGER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsGameConfigManager
 * @brief		�Q�[���R���t�B�b�O
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsGameConfigManager : public KsSingleton< KsGameConfigManager >
{
	public:
		/**
		 * �V���O���g���̎Q�Ƃ��擾
		 * @return							�V���O���g���̎Q��
		 */
		static KsGameConfigManager&			getInstance();
		
		/**
		 * �V���O���g���̃|�C���^���擾
		 * @return							�V���O���g���̃|�C���^
		 */
		static KsGameConfigManager*			getInstancePtr();

		/**
		 * �Z�b�g�A�b�v��������
		 */
		static void							setup();

		/**
		 * �㏈����������
		 */
		static void							shutdown();

	public:
		/**
		 * �R���X�g���N�^
		 */
											KsGameConfigManager();

		/**
		 * �f�X�g���N�^
		 */
		virtual								~KsGameConfigManager();

		/** 
		 * �t�@�C���p�b�N����V�F�_�[�𐶐�����
		 * @param	rFileName		�t�@�C���p�b�N
		 * @retval	ksTRUE			����
		 * @retval	ksFALSE			���s
		 */
		KsBool								create( const KsString& rFileName );

		/**
		 * ���ׂẴ��\�[�X���������
		 */
		void								destroy();

	protected:
		KsBool								m_isWindowMode;		/**< �E�B���h�E���[�h���ǂ���	*/
		KsInt32								m_windowWidth;
		KsInt32								m_windowHeight;
};

#endif /* __KSGAMECONFIGMANAGER_H__ */

