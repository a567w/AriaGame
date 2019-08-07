/************************************************************************************************/
/** 
 * @file		KsUpdateList.h
 * @brief		更新処理
 * @author		Tsukasa Kato
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSUPDATELIST_H__
#define __KSUPDATELIST_H__

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
 * @class		KsUpdateList
 * @brief		描画タスクリスト
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
class ksENGINE_API KsUpdateList
{
		friend class KsTaskManager;
		friend class KsUpdate;
	
	public:
		/**
		 * コンストラクタ
		 * @brief	0で初期化される
		 */
											KsUpdateList();

		/**
		 * デストラクタ
		 */
		virtual								~KsUpdateList();

		/**
		 * 描画するかどうかをセットする
		 * @param		drawActive		描画するかどうかをセットする
		 */
		void								setActive( KsBool isActive ) { m_isActive = isActive; }

		/**
		 * 描画するかどうかを取得する
		 * @return		描画するかどうかを取得する
		 */
		KsBool								isActive() const { return m_isActive; }
		
		/**
		 * 描画タスクを追加する
		 * @param		pUpdate				描画タスク
		 */
		void								add( KsUpdate* pUpdate );

		/**
		 * 描画タスクを取り除く
		 * @param		pUpdate				描画タスク
		 */
		void								remove( KsUpdate* pUpdate );

		/**
		 * タスクを追加する
		 * @param		pUpdate				描画タスク
		 */
		void								update( void* pParam );

	protected:
		KsBool								m_isActive;			/**< 描画アクティブフラグ				*/
		KsUpdate*							m_pUpdateRoot;		/**< 描画ルート						*/
		KsUpdate*							m_pUpdateLast;		/**< 描画ラスト						*/
		KsTaskManager*						m_pUpdateManager;	/**< タスクマネージャ					*/
};



#endif /* __KSUPDATELIST_H__ */

