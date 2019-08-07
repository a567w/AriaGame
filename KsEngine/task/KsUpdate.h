/************************************************************************************************/
/** 
 * @file		KsUpdate.h
 * @brief		更新処理
 * @author		Tsukasa Kato
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSUPDATE_H__
#define __KSUPDATE_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * 更新処理タスク
 * @class		KsUpdate
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
class ksENGINE_API KsUpdate
{
		friend class KsTaskManager;
		friend class KsUpdateList;
	
	public:
		/**
		 * コンストラクタ
		 * @brief	0で初期化される
		 */
											KsUpdate();

		/**
		 * コンストラクタ
		 * @param	order					更新オーダー
		 */
											KsUpdate( KsUInt32 order );

		/**
		 * デストラクタ
		 */
		virtual								~KsUpdate();

		/**
		 * タスクの識別IDを取得する
		 * @return		タスクのIDを取得する
		 */
		KsUInt32							getUpdateID() const { return m_updateID; }

		/**
		 * オーダーを取得する
		 * @return		更新オーダーを取得する
		 */
		KsUInt32							getUpdateOrder() const { return m_updateOrder; }

		/**
		 * 更新するかどうかをセットする
		 * @param		updateActive		更新するかどうかをセットする
		 */
		void								setActiveUpdate( KsBool updateActive ) { m_updateActive = updateActive; }

		/**
		 * 更新するかどうかを取得する
		 * @return		更新するかどうかを取得する
		 */
		KsBool								isActiveUpdate() const { return m_updateActive; }

		/**
		 * 更新プライオリティを取得する
		 * @return		更新プライオリティを取得する
		 */
		KsUInt32							getUpdatePriority() const { return m_updatePriority; }

	protected:
		/**
		 * 初期化処理(マネージャに登録されたときに登録)
		 * @param		pParam				パラメータ
		 */
		virtual void*						initialize( void* pParam ) = 0;

		/**
		 * 更新処理
		 * @param		pParam				パラメータ
		 */
		virtual void*						update( void* pParam ) = 0;

		/**
		 * 後処理関数でメモリーから削除されるときに呼ばれる
		 * @param		pParam				パラメータ
		 */
		virtual void*						terminate( void* pParam ) = 0;

		/**
		 * 破棄する(マネージャ側で削除する)
		 */
		virtual void						destroyUpdate();

	protected:
		KsUInt32							m_updateID;			/**< タスク識別ID(自動的に割り振る?)	*/
		KsUInt32							m_updateOrder;		/**< 更新オーダー					*/
		KsUInt32							m_updatePriority;	/**< 更新プライオリティ				*/
		KsBool								m_updateActive;		/**< 更新アクティブフラグ				*/
		KsBool								m_updateFlags;		/**< 更新フラグ						*/
		KsUpdate*							m_pUpdatePrev;		/**< 更新前方リスト					*/
		KsUpdate*							m_pUpdateNext;		/**< 更新後方リスト					*/
		KsTaskManager*						m_pUpdateManager;	/**< タスクマネージャ					*/
};


#endif /* __KSUPDATE_H__ */

