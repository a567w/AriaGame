/************************************************************************************************/
/** 
 * @file		KsGamePad.h
 * @brief		ゲームパッド入力処理
 * @author		Tsukasa Kato
 * @date		2006/10/17
 * @since		2006/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSGAMEPAD_H__
#define __KSGAMEPAD_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsGamePad
 * @brief		ゲームパッド入力処理
 * @date		2006/10/17
 * @since		2006/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
class KsKeyConfig
{
	public:
		/**
		 * コンストラクタ
		 */
		KsKeyConfig();

	public:
		KsUInt32		m_decision;		/**< 決定ボタン				*/
		KsUInt32		m_cancel;		/**< キャンセルボタン			*/
		KsUInt32		m_menuOpen;		/**< メニューオープンボタン	*/
		
		/* 方向キー */
		KsUInt32		m_up;
		KsUInt32		m_down;
		KsUInt32		m_left;
		KsUInt32		m_right;
};

/************************************************************************************************/
/**
 * @class		KsGamePad
 * @brief		ゲームパッド入力処理
 * @date		2006/10/17
 * @since		2006/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
class KsGamePad
{
		friend class KsGamePadManager;

	protected:
		/**
		 * コンストラクタ
		 */
							KsGamePad( KsInputSystem* pInputSystem, KsInt32 padIndex );
	public:
		/**
		 * デストラクタ
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

