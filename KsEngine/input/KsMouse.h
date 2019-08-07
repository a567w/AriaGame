/************************************************************************************************/
/** 
 * @file		KsMouse.h
 * @brief		�}�E�X����N���X
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSMOUSE_H__
#define __KSMOUSE_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/
#define ksMOUSE_BUTTON_LEFT			( 1 << 0 )
#define ksMOUSE_BUTTON_RIGHT		( 1 << 1 )
#define ksMOUSE_BUTTON_CENTER		( 1 << 2 )
#define ksMOUSE_BUTTON_EX1			( 1 << 3 )
#define ksMOUSE_BUTTON_EX2			( 1 << 4 )

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsMouse
 * @brief		�}�E�X�R���g���[��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsMouse
{
	public:
		/**
		 * �R���X�g���N�^
		 */
							KsMouse();

		/**
		 * �f�X�g���N�^
		 */
							~KsMouse();

		/**
		 * �X�V����
		 */
		void				update();

		/**
		 * �}�E�X��X���W���擾����
		 * @return			�}�E�X��X���W
		 */
		KsInt32				getPosX()      const { return m_x; }

		/**
		 * �}�E�X��Y���W���擾����
		 * @return			�}�E�X��Y���W
		 */
		KsInt32				getPosY()      const { return m_y; }

		/**
		 * �}�E�X��Z���W���擾����(�z�C�[��)
		 * @return			�}�E�X��Z���W
		 */
		KsInt32				getPosZ()      const { return m_z; }

		/**
		 * �{�^���̌��ݏ����擾����
		 * @return			�}�E�X�̃{�^�����
		 */
		KsInt32				getButtonNow() const { return m_button_now; }

		/**
		 * �ߋ��̃{�^�������擾����
		 * @return			�}�E�X�̉ߋ��̃{�^�����
		 */
		KsInt32				getButtonOld() const { return m_button_old; }

		/**
		 * �{�^�����������Ƃ��̏����擾����
		 * @return			�}�E�X�̃{�^�����������Ƃ��̏��
		 */
		KsInt32				getButtonTrg() const { return m_button_trg; }

		/**
		 * �{�^���𗣂����Ƃ��̏����擾����
		 * @return			�}�E�X�̃{�^���𗣂����Ƃ��̏��
		 */
		KsInt32				getButtonOff() const { return m_button_off; }

		/**
		 * �}�E�X�J�[�\���̕\����ON,OFF
		 * @param	bFlag	ksTRUE : �\��, ksFALSE : ��\��
		 */
		void				setShowCursor( KsBool bFlag );

	protected:
		KsInt32				m_x;				/**< X���W						*/
		KsInt32				m_y;				/**< Y���W						*/
		KsInt32				m_z;				/**< Z���W						*/
		KsInt32				m_button_now;		/**< �{�^���f�[�^				*/
		KsInt32				m_button_trg;		/**< �g���K�[					*/
		KsInt32				m_button_off;		/**< �����[�X					*/
		KsInt32				m_button_old;		/**< ��O�̃f�[�^				*/
		KsInt32				m_clickCount;		/**< �N���b�N������				*/
		KsReal				m_timer;			/**< �^�C�}�[					*/
		HWND				m_hWnd;				/**< �w��E�C���h�E�̃n���h��		*/	
};


#endif		/* __KSMOUSE_H__ */

