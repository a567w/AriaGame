/************************************************************************************************/
/** 
 * @file		KsOT.h
 * @brief		オーダリングテーブル
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSOT_H__
#define __KSOT_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsType.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsTaskBase;

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
#define ksOT_ORDER_MAX			( 32 )					/**< オーダーの最大値			*/
#define ksOT_ORDER_CAMERA		( ksOT_ORDER_MAX )		/**< カメラのオーダー			*/
#define ksOT_SORT_TBL_MAX		( 1<<14 )				/**< ソート用のテーブルの最大値	*/

/************************************************************************************************/
/**
 * オーダリングテーブル制御用のフラグ
 */
/************************************************************************************************/
#define ksOT_FLAGS_PRIORITYSORT	( 1<<1 )										/**< 優先順位でソートするかどうかのフラグ					*/
#define ksOT_FLAGS_ZSORT			( 1<<2 )										/**< Z値でソートするかどうかのフラグ						*/
#define ksOT_FLAGS_STOP			( 1<<3 )										/**< ストップさせるとそのオーダーは動かないので描画しない	*/
#define ksOT_FLAGS_SORT_USE		( ksOT_FLAGS_PRIORITYSORT | ksOT_FLAGS_ZSORT )	/**< ソートを使用するかどうかのフラグ						*/

/************************************************************************************************/
/**
 * @class		KsOT_List
 * @brief		基本タスクマネージャクラス
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
class ksENGINE_API KsOT_List
{
	public:
		/**
		 * コンストラクタ
		 */
									KsOT_List();

		/**
		 * デストラクタ
		 */
		virtual					~KsOT_List();
		
		/**
		 * タスクのプライオリティでソートする
		 * @brief 		基本的にソートして描画順番を変更するのでこのリストにつながっているタスクは
		 *				すべてプライオリティが、きちんと設定されていないと,正しくソートできない。
		 */
		void						sort();

		/**
		 * タスクのZ値でソートする(Zソート)
		 * @brief 		基本的にソートして描画順番を変更するのでこのリストにつながっているタスクは
		 *				すべてZ値が、きちんと設定されていないと,正しくソートできない。
		 */
		void						zsort();

		/**
		 * リンクを追加する
		 * @param		pTask		追加タスク
		 */
		void						add( KsTaskBase* pTask );

		/**
		 * フラグを取得する
		 * @return					フラグを取得する
		 */
		KsUInt32					getFlags() const { return m_flags; }

		/**
		 * フラグをセットする
		 * @param		flags		各種フラグ
		 */
		void						setFlags( KsUInt32 flags ) { m_flags = flags; }

		/**
		 * リスト数を取得する
		 * @return					リスト数
		 */
		KsUInt32					getCount() const { return m_count; }

		/**
		 * リストの先頭のポインタを取得する
		 * @return					リストの先頭ポインタ
		 */
		KsTaskBase*						getTop() { return m_pTop; }

		/**
		 * リストの最後尾のポインタを取得する
		 * @return					リストの最後尾ポインタ
		 */
		KsTaskBase*						getEnd() { return m_pEnd; }

		/**
		 * ノーマル描画
		 * @param		pParam		パラメータ
		 */
		void						normalRender( void* pParam );

		/**
		 * ソート描画
		 * @param		pParam		パラメータ
		 */
		void						sortRender( void* pParam );

		/**
		 * クリア処理
		 */
		void						clear();

		/**
		 * リストから取り外し処理
		 * @param		pTask		取り外すタスクのポインタ
		 */
		void						remove( KsTaskBase* pTask );

	protected:
		KsUInt32					m_flags;						/**< 各種フラグ				*/
		KsTaskBase*						m_pTop;							/**< リストの先頭			*/
		KsTaskBase*						m_pEnd;							/**< リストの最後			*/
		KsUInt32					m_count;						/**< リストの数				*/
		KsTaskBase*						m_sortTbl[ ksOT_SORT_TBL_MAX ];	/**< ソート用のワークエリア	*/
};

/************************************************************************************************/
/**
 * オダーリングテーブル
 * @class		KsOT
 * @brief		オダーリングテーブル
 * @date		2004/10/17
 * @since		2004/10/17
 * @sa			KsOT_List (関連項目を参照)
 */
/************************************************************************************************/
class ksENGINE_API KsOT
{
		//friend class KsOT;
		friend class KsOT_List;
	public:
		/**
		 * コンストラクタ
		 */
									KsOT();
		/**
		 * デストラクタ
		 */
		virtual					~KsOT();

		/**
		 * タスクを登録する
		 * @param		pTask		登録するタスクのポインタ
		 * @retval		ksTRUE		成功
		 * @retval		ksFALSE		失敗
		 */
        KsBool						entry( KsTaskBase* pTask );

		/**
		 * 取り外す
		 * @param		pTask		取り外すタスクのポインタ
		 */
		void						remove( KsTaskBase* pTask );

		/**
		 * オーダーの最大値を取得する
		 * @return					オーダの最大値
		 */
		KsUInt32					getOrderMax() const { return ksOT_ORDER_MAX; }

		/**
		 * フラグを取得する
		 * @return					フラグを取得する
		 */
		KsUInt32					getFlags() const { return m_flags; }

		/**
		 * フラグをセットする
		 * @param		flags		各種フラグ
		 */
		void						setFlags( KsUInt32 flags ) { m_flags = flags; }

		/**
		 * オーダーを取得する
		 * @param		index		インデックス
		 * @return					オーダーリストのポインタ
		 */
		KsOT_List*					getOrder( KsUInt32 index ) { return &m_order[ index ]; }

		/**
		 * 描画処理
		 * @param		pParam		パラメータ
		 */
		void						render( void* pParam );

		/**
		 * クリア処理
		 */
		void						clear();

	protected:
		/**
		 * 指定オーダーを描画
		 * @param		order		指定オーダー
		 * @param		pParam		パラメータ
		 */
		void						orderRender( KsUInt32 order, void* pParam );

		/**
		 * カメラリンクを描画
		 * @param		pParam		パラメータ
		 */
		void						cameraRender( void* pParam );

		/**
		 * デフォルト描画
		 * @param		pParam		パラメータ
		 */
		void						defaultRender( void* pParam );

	protected:
		KsUInt32					m_flags;						/**< フラグ								*/
		KsOT_List					m_order[ ksOT_ORDER_MAX+1 ];	/**< オーダー(+1はカメラリンクのため)	*/
};

#endif	/* __KSOT_H__ */

