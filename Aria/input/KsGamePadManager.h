/************************************************************************************************/
/** 
 * @file		KsGamePadManager.h
 * @brief		ゲーム入力処理
 * @author		Tsukasa Kato
 * @date		2006/10/17
 * @since		2006/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSGAMEPADMANAGER_H__
#define __KSGAMEPADMANAGER_H__

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
 * @class		KsGamePadManager
 * @brief		ゲーム入力処理
 * @date		2006/10/17
 * @since		2006/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
class KsGamePadManager : public KsSingleton< KsGamePadManager >
{
	public:
		/**
		 * インスタンス取得
		 * @return					インスタンス
		 */
		static KsGamePadManager&	getInstance();

		/**
		 * インスタンス取得
		 * @return					インスタンス
		 */
		static KsGamePadManager*	getInstancePtr();

	public:
		/**
		 * コンストラクタ
		 * @param	pInputSystem	入力システム
		 */

									KsGamePadManager( KsInputSystem* pInputSystem );

		/**
		 * デストラクタ
		 */
		virtual						~KsGamePadManager();

		/** 
		 * 更新処理
		 */
		virtual void				update();

		/**
		 * 指定ゲームパッドの取得
		 * @param	index			インデックス
		 * @return					指定ゲームパッドの参照
		 */
		const KsGamePad&			getGamePad( KsInt32 index );

		/**
		 * 指定ゲームパッドの取得
		 * @param	index			インデックス
		 * @return					指定ゲームパッドのポインタ
		 */
		const KsGamePad*			getGamePadPtr( KsInt32 index );

		/**
		 * 指定ゲームマウスの取得
		 * @param	index			インデックス
		 * @return					指定ゲームパッドの参照
		 */
		const KsGameMouse&			getGameMouse();

		/**
		 * 指定ゲームマウスの取得
		 * @param	index			インデックス
		 * @return					指定ゲームパッドのポインタ
		 */
		const KsGameMouse*			getGameMousePtr();

	protected:
		KsArray< KsGamePad* >		m_vpGamePad;		/**< ゲームパッド	*/
		KsArray< KsGameMouse* >		m_vpGameMouse;		/**< ゲームマウス	*/
		KsInputSystem*				m_pInputSystem;		/**< 入力システム	*/
};


#endif /* __KSGAMEPADMANAGER_H__ */

