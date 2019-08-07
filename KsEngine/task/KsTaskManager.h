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
/*                                 << インクルード >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
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
		friend class KsUpdate;
		friend class KsDraw;
		friend class KsTask;
	public:
		/**
		 * コンストラクタ
		 * @param		numUpdateList		更新リスト数
		 * @param		numDrawList			描画リスト数
		 */
											KsTaskManager( KsUInt32 numUpdateList, KsUInt32 numDrawList );

		/**
		 * デストラクタ
		 */
		virtual								~KsTaskManager();

		/**
		 * すべての処理を実行
		 * @param		pParam				ここでわたしたパラメータがタスクのexecuteやrenderの引数に渡る
		 *									デフォルトでは、NULLが設定されている。
		 */
		virtual void						run( void* pParam=NULL );

		/**
		 * 更新処理
		 * @param		pParam				パラメータ
		 */
		virtual void						execute( void* pParam );

		/**
		 * 描画処理
		 * @param		pParam				パラメータ
		 */
		virtual void						render( void* pParam );

		/**
		 * 
		 */
		virtual void						addTask( KsTask* pTask );

		/**
		 * 
		 */
		virtual void						addUpdate( KsUpdate* pUpdate );

		/**
		 * 
		 */
		virtual void						addDraw( KsDraw* pDraw );


		virtual void						removeTask( KsTask* pTask );

		/**
		 * 
		 */
		virtual void						removeUpdate( KsUpdate* pUpdate );

		/**
		 * 
		 */
		virtual void						removeDraw( KsDraw* pDraw );

		virtual void						destroyTask( KsTask* pTask );

		/**
		 * 
		 */
		virtual void						destroyUpdate( KsUpdate* pUpdate );

		/**
		 * 
		 */
		virtual void						destroyDraw( KsDraw* pDraw );

		virtual void						destroyAll();
	protected:
		/**
		 * 描画開始
		 */
		virtual void						begineRender();

		/**
		 * 描画終了
		 */
		virtual void						endRender();

	protected:
		KsUInt32							m_numUpdateList;	/**< */
		KsUInt32							m_numDrawList;		/**< */
		KsUpdateList*						m_pUpdates;			/**< 更新リスト	*/
		KsDrawList*							m_pDraws;			/**< 描画リスト	*/
};


#endif /* __KSTASKMANAGER_H__ */

