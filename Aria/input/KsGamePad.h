/************************************************************************************************/
/** 
 * @file		KsGamePad.h
 * @brief		�Q�[���p�b�h���͏���
 * @author		Tsukasa Kato
 * @date		2006/10/17
 * @since		2006/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSGAMEPAD_H__
#define __KSGAMEPAD_H__

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
 * @class		KsGamePad
 * @brief		�Q�[���p�b�h���͏���
 * @date		2006/10/17
 * @since		2006/10/17
 * @version		0.10
 * @note		�Ȃ�
 */
/************************************************************************************************/
class KsKeyConfig
{
	public:
		/**
		 * �R���X�g���N�^
		 */
		KsKeyConfig();

	public:
		KsUInt32		m_decision;		/**< ����{�^��				*/
		KsUInt32		m_cancel;		/**< �L�����Z���{�^��			*/
		KsUInt32		m_menuOpen;		/**< ���j���[�I�[�v���{�^��	*/
		
		/* �����L�[ */
		KsUInt32		m_up;
		KsUInt32		m_down;
		KsUInt32		m_left;
		KsUInt32		m_right;
};

/************************************************************************************************/
/**
 * @class		KsGamePad
 * @brief		�Q�[���p�b�h���͏���
 * @date		2006/10/17
 * @since		2006/10/17
 * @version		0.10
 * @note		�Ȃ�
 */
/************************************************************************************************/
class KsGamePad
{
		friend class KsGamePadManager;

	protected:
		/**
		 * �R���X�g���N�^
		 */
							KsGamePad( KsInputSystem* pInputSystem, KsInt32 padIndex );
	public:
		/**
		 * �f�X�g���N�^
		 */
							~KsGamePad();

		KsBool				isCancelOn() const;
		KsBool				isCancelPress() const;
		KsBool				isCancelOff() const;
		KsBool				isCancelRepeat() const;

		KsBool				isDecisionOn() const;
		KsBool				isDecisionPress() const;
		KsBool				isDecisionOff() const;
		KsBool				isDecisionRepeat() const;

		KsBool				isUpOn() const;
		KsBool				isUpPress() const;
		KsBool				isUpOff() const;
		KsBool				isUpRepeat() const;

		KsBool				isDownOn() const;
		KsBool				isDownPress() const;
		KsBool				isDownOff() const;
		KsBool				isDownRepeat() const;

		KsBool				isLeftOn() const;
		KsBool				isLeftPress() const;
		KsBool				isLeftOff() const;
		KsBool				isLeftRepeat() const;

		KsBool				isRightOn() const;
		KsBool				isRightPress() const;
		KsBool				isRightOff() const;
		KsBool				isRightRepeat() const;

	protected:
		KsInputSystem*		m_pInputSystem;
		KsInt32				m_padIndex;
		KsKeyConfig			m_keyConfig;
};


#endif /* __KSGAMEPAD_H__ */

