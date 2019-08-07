/************************************************************************************************/
/** 
 * @file		KsTaskManager.h
 * @brief		基本タスク
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSTASKMANAGER_H__
#define __KSTASKMANAGER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsTaskBase.h"
#include "KsOT.h"
#include "KsSingleton.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * 
 * @class		KsTaskManager
 * @brief		基本タスクマネージャクラス
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
class ksENGINE_API KsTaskManager
{
		friend class KsTaskBase;
	public:
		/**
		 * コンストラクタ
		 * @brief	0で初期化される
		 */
											KsTaskManager();

		/**
		 * デストラクタ
		 */
		virtual							~KsTaskManager();

		/**
		 * ルートタスクをセットする(このとき下のタスクにどのユーザーデータをセットする)
		 * このときも描画リンクが再設定される
		 * @param		pTask				セットするルートタスク
		 * @return							前のルートタスクのポインタを返す(ないときはNULLを返す)
		 */
		KsTaskBase*								setRootTask( KsTaskBase* pTask );

		/**
		 * ルートタスクをセットする
		 * @return							ルートタスクのポインタ
		 */
		KsTaskBase*								getRootTask();

		/**
		 * 実行処理
		 * @param		pParam				パラメータ
		 */
		virtual void						execute( void* pParam );

		/**
		 * 描画処理
		 * @param		pParam				パラメータ
		 */
		virtual void						render( void* pParam );

		/**
		 * 更新処理
		 * @param		pParam				パラメータ
		 */
		virtual void						update( void* pParam );

		/**
		 * すべての処理を実行
		 * @param		pParam				ここでわたしたパラメータがタスクのexecuteやrenderの引数に渡る
		 *									デフォルトでは、NULLが設定されている。
		 */
		virtual void						run( void* pParam=NULL );

		/**
		 * 削除処理
		 * @param		pTask				削除するタスクのポインタ
		 */
		void								kill( KsTaskBase* pTask, void* pParam );

		/**
		 * すべて削除
		 */
		void								allKill( void* pParam );

		/**
		 * コールバック関数
		 */
		void								allCallback( KsTaskCallback callback, void* pUserData=0 );

		/**
		 * コールバック関数
		 */
		void								allChildCallback( KsTaskBase* pTask, KsTaskCallback callback, void* pUserData=0 );

	protected:
		/**
		 * タスク実行用再帰関数
		 */
		void								taskExecute( KsTaskBase* pTask, void* pUserData );

		/**
		 * 描画開始
		 */
		virtual void						begineRender();

		/**
		 * 描画終了
		 */
		virtual void						endRender();

	protected:
		KsTaskBase*								m_pRootTask;					/**< ルートタスク		*/
		KsTaskCallback						m_pCallback;					/**< コールバック関数	*/
		KsOT								m_renderTbl;					/**< 描画リンクテーブル	*/

		static void*						setManagerCallback( KsTaskBase* pTask, void* pParam );
};



#endif /* __KSTASKMANAGER_H__ */

