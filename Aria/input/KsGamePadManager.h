/************************************************************************************************/
/** 
 * @file		KsGamePadManager.h
 * @brief		�Q�[�����͏���
 * @author		Tsukasa Kato
 * @date		2006/10/17
 * @since		2006/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSGAMEPADMANAGER_H__
#define __KSGAMEPADMANAGER_H__

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
 * @class		KsGamePadManager
 * @brief		�Q�[�����͏���
 * @date		2006/10/17
 * @since		2006/10/17
 * @version		0.10
 * @note		�Ȃ�
 */
/************************************************************************************************/
class KsGamePadManager : public KsSingleton< KsGamePadManager >
{
	public:
		/**
		 * �C���X�^���X�擾
		 * @return					�C���X�^���X
		 */
		static KsGamePadManager&	getInstance();

		/**
		 * �C���X�^���X�擾
		 * @return					�C���X�^���X
		 */
		static KsGamePadManager*	getInstancePtr();

	public:
		/**
		 * �R���X�g���N�^
		 * @param	pInputSystem	���̓V�X�e��
		 */

									KsGamePadManager( KsInputSystem* pInputSystem );

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsGamePadManager();

		/** 
		 * �X�V����
		 */
		virtual void				update();

		/**
		 * �w��Q�[���p�b�h�̎擾
		 * @param	index			�C���f�b�N�X
		 * @return					�w��Q�[���p�b�h�̎Q��
		 */
		const KsGamePad&			getGamePad( KsInt32 index );

		/**
		 * �w��Q�[���p�b�h�̎擾
		 * @param	index			�C���f�b�N�X
		 * @return					�w��Q�[���p�b�h�̃|�C���^
		 */
		const KsGamePad*			getGamePadPtr( KsInt32 index );

		/**
		 * �w��Q�[���}�E�X�̎擾
		 * @param	index			�C���f�b�N�X
		 * @return					�w��Q�[���p�b�h�̎Q��
		 */
		const KsGameMouse&			getGameMouse();

		/**
		 * �w��Q�[���}�E�X�̎擾
		 * @param	index			�C���f�b�N�X
		 * @return					�w��Q�[���p�b�h�̃|�C���^
		 */
		const KsGameMouse*			getGameMousePtr();

	protected:
		KsArray< KsGamePad* >		m_vpGamePad;		/**< �Q�[���p�b�h	*/
		KsArray< KsGameMouse* >		m_vpGameMouse;		/**< �Q�[���}�E�X	*/
		KsInputSystem*				m_pInputSystem;		/**< ���̓V�X�e��	*/
};


#endif /* __KSGAMEPADMANAGER_H__ */

