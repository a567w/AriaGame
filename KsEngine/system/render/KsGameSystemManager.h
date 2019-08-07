/************************************************************************************************/
/** 
 * @file		KsGameSystemManager.h
 * @brief		ゲームマネージャ
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSGAMESYSTEMMANGER_H__
#define __KSGAMESYSTEMMANGER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
//#include "KsGameCommon.h"
//#include "KsPad.h"
//#include "KsTaskManager.h"
//#include "KsRenderSystemPSP.h"
//#include "KsFileSystemPSP.h"
//#include "KsFontManager.h"
//#include "KsRand.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsGameSystemManager
 * @brief		基本タスクマネージャクラス
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
class KsGameSystemManager : public KsTaskManager
{
	public:
		/**
		 * デストラクタ
		 */
		virtual						~KsGameSystemManager();
		
		/**
		 * インスタンス取得
		 */
		static KsGameSystemManager*		instance();

		/**
		 * ゲームループ
		 */
		void							gameLoop();

		/**
		 * 初期化処理
		 */
		void							initialize();

		/**
		 * 後処理
		 */
		void							terminate();

		/**
		 * 描画システム取得
		 */
		KsRenderSystem*					getRenderSystem() { return m_pRenderSystem; }

	protected:
		/**
		 *
		 */
		virtual KsBool					createWindow();

		/**
		 * 描画開始
		 */
		virtual void					begineRender();

		/**
		 * 描画終了
		 */
		virtual void					endRender();
	
		/**
		 * コンストラクタ(シングルトンのためにprivate)
		 */
										KsGameSystemManager();

	private:
		KsWindowParam					m_mainWindowParam;		/**< ウインドウの生成パラメータ				*/
		KsWindow						m_pMainWindow;			/**< ウインドウ								*/
#if 0
		// 本当は、new で確保したほうがいいけど、メモリー確保は、あまりしたくないので
		KsRenderSystem*					m_pRenderSystem;		/**< 描画システム							*/
		KsFileSystemPSP*				m_pFileSystem;			/**< ファイルシステム							*/
		KsPadManager*					m_pPadManager;			/**< パッドマネージャ							*/

		/* ソフトリセット時に保存しておくパラメータSYS0W */

		/* システム系 */
		KsInt8							m_gameMode;				/**< ゲームモード選択							*/
		KsUInt32						m_gameTimer;			/**< ゲームタイマー							*/
		KsUInt32						m_soundVolume;			/**< サウンドのマスターボリューム				*/

		/* フラグ */
		KsUInt8							m_exitFlag;				/**< 終了フラグ(実際にはありえないけど)		*/
		KsUInt8							m_softResetFlag;		/**< ソフトウェアリセットフラグ				*/
		KsUInt8							m_softResetPermission;	/**< ソフトリセットフラグを変更してもいいか？	*/
		KsUInt8							m_pauseFlag;			/**< ポーズ状態かどうかのフラグ				*/
		KsUInt8							m_pausePermission;		/**< ポーズフラグを変更してもいいか？			*/

		/**
		 * ソフトリセット時の初期化処理
		 */
		void							softResetInitialize();
		void							softExitCheck();
		void							setTaskOrder();
#endif
};


#endif		/* __KSGAMESYSTEMMANGER_H__ */

