/************************************************************************************************/
/** 
 * @file		KsMouse.h
 * @brief		マウス操作クラス
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSMOUSE_H__
#define __KSMOUSE_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
#define ksMOUSE_BUTTON_LEFT			( 1 << 0 )
#define ksMOUSE_BUTTON_RIGHT		( 1 << 1 )
#define ksMOUSE_BUTTON_CENTER		( 1 << 2 )
#define ksMOUSE_BUTTON_EX1			( 1 << 3 )
#define ksMOUSE_BUTTON_EX2			( 1 << 4 )

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsMouse
 * @brief		マウスコントロール
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsMouse
{
	public:
		/**
		 * コンストラクタ
		 */
							KsMouse();

		/**
		 * デストラクタ
		 */
							~KsMouse();

		/**
		 * 更新処理
		 */
		void				update();

		/**
		 * マウスのX座標を取得する
		 * @return			マウスのX座標
		 */
		KsInt32				getPosX()      const { return m_x; }

		/**
		 * マウスのY座標を取得する
		 * @return			マウスのY座標
		 */
		KsInt32				getPosY()      const { return m_y; }

		/**
		 * マウスのZ座標を取得する(ホイール)
		 * @return			マウスのZ座標
		 */
		KsInt32				getPosZ()      const { return m_z; }

		/**
		 * ボタンの現在情報を取得する
		 * @return			マウスのボタン情報
		 */
		KsInt32				getButtonNow() const { return m_button_now; }

		/**
		 * 過去のボタン情報を取得する
		 * @return			マウスの過去のボタン情報
		 */
		KsInt32				getButtonOld() const { return m_button_old; }

		/**
		 * ボタンを押したときの情報を取得する
		 * @return			マウスのボタンを押したときの情報
		 */
		KsInt32				getButtonTrg() const { return m_button_trg; }

		/**
		 * ボタンを離したときの情報を取得する
		 * @return			マウスのボタンを離したときの情報
		 */
		KsInt32				getButtonOff() const { return m_button_off; }

		/**
		 * マウスカーソルの表示のON,OFF
		 * @param	bFlag	ksTRUE : 表示, ksFALSE : 非表示
		 */
		void				setShowCursor( KsBool bFlag );

	protected:
		KsInt32				m_x;				/**< X座標						*/
		KsInt32				m_y;				/**< Y座標						*/
		KsInt32				m_z;				/**< Z座標						*/
		KsInt32				m_button_now;		/**< ボタンデータ				*/
		KsInt32				m_button_trg;		/**< トリガー					*/
		KsInt32				m_button_off;		/**< リリース					*/
		KsInt32				m_button_old;		/**< 一つ前のデータ				*/
		KsInt32				m_clickCount;		/**< クリックした回数				*/
		KsReal				m_timer;			/**< タイマー					*/
		HWND				m_hWnd;				/**< 指定ウインドウのハンドル		*/	
};


#endif		/* __KSMOUSE_H__ */

