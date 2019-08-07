/************************************************************************************************/
/** 
 * @file		KsDraw.h
 * @brief		描画タスク
 * @author		Tsukasa Kato
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSDRAW_H__
#define __KSDRAW_H__

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
 * @class		KsDraw
 * @brief		描画タスク
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
class ksENGINE_API KsDraw
{
		friend class KsTaskManager;
		friend class KsDrawList;
	
	public:
		/**
		 * コンストラクタ
		 * @brief	0で初期化される
		 */
											KsDraw();

		/**
		 * コンストラクタ
		 * @param	order					描画オーダー
		 */
											KsDraw( KsUInt32 order );

		/**
		 * デストラクタ
		 */
		virtual								~KsDraw();

		/**
		 * タスクの識別IDを取得する
		 * @return		タスクのIDを取得する
		 */
		KsUInt32							getDrawID() const { return m_drawID; }

		/**
		 * オーダーを取得する
		 * @return		描画オーダーを取得する
		 */
		KsUInt32							getDrawOrder() const { return m_drawOrder; }

		/**
		 * 描画するかどうかをセットする
		 * @param		drawActive		描画するかどうかをセットする
		 */
		void								setActiveDraw( KsBool drawActive ) { m_drawActive = drawActive; }

		/**
		 * 描画するかどうかを取得する
		 * @return		描画するかどうかを取得する
		 */
		KsBool								isActiveDraw() const { return m_drawActive; }

		/**
		 * 描画プライオリティを取得する
		 * @return		描画プライオリティを取得する
		 */
		KsUInt32							getDrawPriority() const { return m_drawPriority; }

	protected:
		/**
		 * 初期化処理(マネージャに登録されたときに登録)
		 * @param		pParam				パラメータ
		 */
		virtual void*						initializeGraphics( void* pParam ) = 0;

		/**
		 * 描画処理
		 * @param		pParam				パラメータ
		 */
		virtual void*						draw( void* pParam ) = 0;

		/**
		 * 後処理関数でメモリーから削除されるときに呼ばれる
		 * @param		pParam				パラメータ
		 */
		virtual void*						terminateGraphics( void* pParam ) = 0;

		/**
		 * 破棄する(マネージャ側で削除する)
		 */
		virtual void						destroyDraw();

	protected:
		KsUInt32							m_drawID;		/**< タスク識別ID(自動的に割り振る?)	*/
		KsUInt32							m_drawOrder;	/**< 描画オーダー					*/
		KsUInt32							m_drawPriority;	/**< 描画プライオリティ				*/
		KsBool								m_drawActive;	/**< 描画アクティブフラグ				*/
		KsBool								m_drawFlags;	/**< 描画フラグ						*/
		KsDraw*								m_pDrawPrev;	/**< 描画前方リスト					*/
		KsDraw*								m_pDrawNext;	/**< 描画後方リスト					*/
		KsTaskManager*						m_pDrawManager;	/**< タスクマネージャ					*/
};

#endif /* __KSDRAW_H__ */

