/************************************************************************************************/
/** 
 * @file		KsGameSystemManager.h
 * @brief		�Q�[���}�l�[�W��
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSGAMESYSTEMMANGER_H__
#define __KSGAMESYSTEMMANGER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
//#include "KsGameCommon.h"
//#include "KsPad.h"
//#include "KsTaskManager.h"
//#include "KsRenderSystemPSP.h"
//#include "KsFileSystemPSP.h"
//#include "KsFontManager.h"
//#include "KsRand.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsGameSystemManager
 * @brief		��{�^�X�N�}�l�[�W���N���X
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		�Ȃ�
 */
/************************************************************************************************/
class KsGameSystemManager : public KsTaskManager
{
	public:
		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsGameSystemManager();
		
		/**
		 * �C���X�^���X�擾
		 */
		static KsGameSystemManager*		instance();

		/**
		 * �Q�[�����[�v
		 */
		void							gameLoop();

		/**
		 * ����������
		 */
		void							initialize();

		/**
		 * �㏈��
		 */
		void							terminate();

		/**
		 * �`��V�X�e���擾
		 */
		KsRenderSystem*					getRenderSystem() { return m_pRenderSystem; }

	protected:
		/**
		 *
		 */
		virtual KsBool					createWindow();

		/**
		 * �`��J�n
		 */
		virtual void					begineRender();

		/**
		 * �`��I��
		 */
		virtual void					endRender();
	
		/**
		 * �R���X�g���N�^(�V���O���g���̂��߂�private)
		 */
										KsGameSystemManager();

	private:
		KsWindowParam					m_mainWindowParam;		/**< �E�C���h�E�̐����p�����[�^				*/
		KsWindow						m_pMainWindow;			/**< �E�C���h�E								*/
#if 0
		// �{���́Anew �Ŋm�ۂ����ق����������ǁA�������[�m�ۂ́A���܂肵�����Ȃ��̂�
		KsRenderSystem*					m_pRenderSystem;		/**< �`��V�X�e��							*/
		KsFileSystemPSP*				m_pFileSystem;			/**< �t�@�C���V�X�e��							*/
		KsPadManager*					m_pPadManager;			/**< �p�b�h�}�l�[�W��							*/

		/* �\�t�g���Z�b�g���ɕۑ����Ă����p�����[�^SYS0W */

		/* �V�X�e���n */
		KsInt8							m_gameMode;				/**< �Q�[�����[�h�I��							*/
		KsUInt32						m_gameTimer;			/**< �Q�[���^�C�}�[							*/
		KsUInt32						m_soundVolume;			/**< �T�E���h�̃}�X�^�[�{�����[��				*/

		/* �t���O */
		KsUInt8							m_exitFlag;				/**< �I���t���O(���ۂɂ͂��肦�Ȃ�����)		*/
		KsUInt8							m_softResetFlag;		/**< �\�t�g�E�F�A���Z�b�g�t���O				*/
		KsUInt8							m_softResetPermission;	/**< �\�t�g���Z�b�g�t���O��ύX���Ă��������H	*/
		KsUInt8							m_pauseFlag;			/**< �|�[�Y��Ԃ��ǂ����̃t���O				*/
		KsUInt8							m_pausePermission;		/**< �|�[�Y�t���O��ύX���Ă��������H			*/

		/**
		 * �\�t�g���Z�b�g���̏���������
		 */
		void							softResetInitialize();
		void							softExitCheck();
		void							setTaskOrder();
#endif
};


#endif		/* __KSGAMESYSTEMMANGER_H__ */

