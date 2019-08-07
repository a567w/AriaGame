/************************************************************************************************/
/** 
 * @file		KsTaskBase.h
 * @brief		基本タスク
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSTASK_H__
#define __KSTASK_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsCore.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsTaskBase;
class KsOT_List;
class KsOT;

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
#define ksTASK_NAME_LENGTH			( 16 )			/**< タスクの名前の最大長( 15文字 + '\0' )	*/
#define ksTASK_ORDER_DEFAULT		(  4 )			/**< デフォルトのタスクオーダー				*/

/************************************************************************************************/
/**
 * タスクの制御フラグ
 */
/************************************************************************************************/
#define ksTASK_FLAGS_NONE			( 0 )			/**< 空										*/
#define ksTASK_FLAGS_DELETE		( 1<< 1 )		/**< 削除フラグ								*/
#define ksTASK_FLAGS_DELETE_FORCE	( 1<< 2 )		/**< 強制削除フラグ							*/
#define ksTASK_FLAGS_SLEEP_EXEC	( 1<< 3 )		/**< タスク実行処理をスリープ状態にする		*/
#define ksTASK_FLAGS_SLEEP_REND	( 1<< 4 )		/**< タスク描画処理をスリープ状態にする		*/
#define ksTASK_FLAGS_WAIT_EXEC		( 1<< 5 )		/**< ウエイトタイマー分は実行させない		*/
#define ksTASK_FLAGS_WAIT_REND		( 1<< 6 )		/**< ウエイトタイマー分は描画させない		*/
#define ksTASK_FALGS_RENDER_HIDE	( 1<< 9 )		/**< 描画しないフラグ						*/
#define ksTASK_FALGS_INITIALIZE	( 1<<10 )		/**< 初期化したかどうかのフラグ				*/
#define ksTASK_FLAGS_PAUSE_CHILD	( 1<<28 )		/**< 子供のタスクだけ影響					*/
#define ksTASK_FLAGS_PAUSE_MY		( 1<<29 )		/**< 自分のタスクだけ影響					*/
#define ksTASK_FLAGS_LINK_UPDATE	( 1<<30 )		/**< 描画リンクの更新処理					*/
#define ksTASK_FLAGS_USE_WORKAREA	( 1<<31 )		/**< ワークエリアを使用する					*/

// カメラだけは、フラグを持っていたほうがいいかも
//#define ksTASK_FLAGS_CAMERA
// 自分だけストップexec
// 自分以下ストップexec
// 描画しないフラグをセット
// 自分だけストップrender
// 自分以下ストップrender

#define ksTASK_FLAGS_SLEEP			( ksTASK_FLAGS_SLEEP_EXEC | ksTASK_FLAGS_SLEEP_REND )
#define ksTASK_FLAGS_WAIT			( ksTASK_FLAGS_WAIT_EXEC | ksTASK_FLAGS_WAIT_REND )
#define ksTASK_FLAGS_PAUSE			( ksTASK_FLAGS_PAUSE_CHILD | ksTASK_FLAGS_PAUSE_MY )

#define ksTASK_RENDER_ORDER_NONE	( 0 )
#define ksTASK_RENDER_ORDER_ALL	( 0xffffffff )

/************************************************************************************************/
/**
 * @enum	タスクのタイプ
 */
/************************************************************************************************/
enum ksTASK_TYPE
{
	ksTASK_TYPE_BASE    = 0,				/**< 基本タスク				*/
	ksTASK_TYPE_SCENE   = 1,				/**< シーンタスク			*/
	ksTASK_TYPE_SPRITE  = 2,				/**< スプライトタスク		*/
	ksTASK_TYPE_SHADOW  = 3,				/**< 影用タスク				*/
	ksTASK_TYPE_MANAGER = 4,				/**< 制御タスク				*/
	ksTASK_TYPE_DEBUG   = 16,				/**< デバック用タスク		*/
	ksTASK_TYPE_CAMERA  = 0xffff,
};

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

typedef void* (*KsTaskCallback)( KsTaskBase* pTask, void* pParam );

/************************************************************************************************/
/** 
 * タスクの優先順位( 描画でソートする場合に必要 )
 *		-i : 32bit整数で整数値でソート用
 *		-z : 浮動小数点でZソート用
 */
/************************************************************************************************/
typedef union _KsTaskPRIORITY
{
	KsInt32		i;					/**< 優先順位		*/
	KsReal		z;					/**< Zソート値		*/
}KsTaskPRIORITY;

/************************************************************************************************/
/**
 * 基本タスククラス
 * @class		KsTaskBase
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
class ksENGINE_API KsTaskBase
{
		friend class KsOT_List;
		friend class KsOT;
		friend class KsTaskManager;
	
	public:
		/**
		 * コンストラクタ
		 * @brief	0で初期化される
		 */
											KsTaskBase();

		/**
		 * コンストラクタ
		 * @param	order					描画オーダー
		 */
											KsTaskBase( KsUInt32 order );

		/**
		 * デストラクタ
		 */
		virtual							~KsTaskBase();

		/**
		 * 兄弟タスクを追加する
		 * @param		pTask				追加する兄弟タスクのポインタ
		 * @param		pUserData			ユーザーデータ
		 * @note		ユーザーデータがNULLのときは、マネージャの実行処理のときに,
		 *				マネージャに渡されたユーザーデータがユーザーデータに渡されて初期化される。
		 *				しかし、この場合、addChildしたときには、初期化が呼ばれない。そのため、
		 *				ユーザーデータにNULL以外を入れるとそのユーザーデータを使用してaddChildしたときに
		 *				追加されたタスクの初期化処理が呼ばれる。
		 */
		void								addBrother( KsTaskBase* pTask, void* pUserData=NULL );

		/**
		 * 子タスクを追加する
		 * @param		pTask				追加する子タスクのポインタ
		 * @param		pUserData			ユーザーデータ
		 * @note		ユーザーデータがNULLのときは、マネージャの実行処理のときに,
		 *				マネージャに渡されたユーザーデータがユーザーデータに渡されて初期化される。
		 *				しかし、この場合、addChildしたときには、初期化が呼ばれない。そのため、
		 *				ユーザーデータにNULL以外を入れるとそのユーザーデータを使用してaddChildしたときに
		 *				追加されたタスクの初期化処理が呼ばれる。
		 */
		void								addChild( KsTaskBase* pTask, void* pUserData=NULL );

		/**
		 * 自分のタスクをとりはずす(階層は、自分についたまま)
		 */
		void								detach();

		/**
		 * 完全に切り離すdetachが必要
		 * @param		pTask				取り除く子タスクのポインタ
		 * 完全に切り離されて1つのタスクになる
		 */
		KsTaskBase*								cut();

		/**
		 * 自分より下の階層からタスクを削除する(削除フラグが、たつ)
		 */
		void								remove();

		/**
		 * 自分より下の階層からタスクを削除する(削除フラグが、たつ)
		 */
		void								destroy();

		/**
		 * 即時死ぬkill関数 (マネージャから外れているときだけ使用可能にする？)
		 */
		//void								kill();

		/**
		 * ID(検索自分より下の階層から一致するタスクを検索する)
		 * @param		id					検索するID
		 */
		KsTaskBase*								find( KsUInt32 id );

		/**
		 * 名前検索(検索自分より下の階層から一致するタスクを検索する)
		 *
		 */
		KsTaskBase*								find( const KsChar* name );

		/**
		 * 描画リンクを変更する(これを使用するには、マネージャに登録されている必要があります。)
		 * @param		order				新しいオーダー
		 */
		void								changeRenderLink( KsUInt32 order );

		/**
		 * 描画リンクから取り外す
		 * @param		pTask				描画リンクからはずすタスクのポインタ
		 */
		void								removeRenderLink( KsTaskBase* pTask=NULL );

		/**
		 * タスク名をセットする
		 * @param		string				タスク名
		 */
		void								setName( const KsChar* string );

		/**
		 * タスクの識別IDをセットする(基本的にはかぶらないようにする)
		 * @param		id					タスクのID
		 */
		void								setID( KsUInt32 id );

		/**
		 * タスクの制御フラグをセットする
		 * @param		flags				タスクの制御フラグ
		 */
		void								setFlags( KsUInt32 flags );

		/**
		 * 優先順位をセットする
		 * @param		priotiry			プライオリティ
		 */
		void								setPriority( KsInt32 priority );

		/**
		 * オーダをセット
		 * @param		order				指定オーダー
		 */
		void								setOrder( KsUInt32 order );

		/**
		 * Z値をセットする
		 * @param		z					z値
		 */
		void								setZsort( KsReal z );

		/**
		 * タスク名を取得する
		 * @return		タスク名の文字列( 最長15文字 + '\0' )
		 */
		const KsChar*						getName();

		/**
		 * タスクの識別IDを取得する
		 * @return		タスクのIDを取得する
		 */
		KsUInt32							getID() const;

		/**
		 * タスクの制御フラグを取得する
		 * @return		タスクの制御フラグ
		 */
		KsUInt32							getFlags() const;

		/**
		 * タスクのタイプを取得する
		 */
		ksTASK_TYPE							getType() const;

		/**
		 * 優先順位をセットする
		 * @return							プライオリティ
		 */
		KsTaskPRIORITY						getPriority() const;

		/**
		 * オダーを取得する
		 */
		KsUInt32							getOrder() const;

		/**
		 * 親タスクを取得する
		 * @return		親タスクのポインタ
		 */
		KsTaskBase*								getParent();

		/**
		 * 長男タスクを取得する
		 */
		KsTaskBase*								getTopBrother();

		/**
		 * 最後尾タスクを取得する
		 */
		KsTaskBase*								getEndBrother();

		/**
		 * 兄タスクを取得する
		 */
		KsTaskBase*								getPrevBrother();

		/**
		 * 弟タスクを取得する
		 */
		KsTaskBase*								getNextBrother();

		/**
		 * 兄弟タスクを取得する
		 * @param		index				子タスクのインデックス
		 * @return		子タスクのポインタ
		 */
		KsTaskBase*								getBrother( KsUInt32 index );

		/**
		 * 子タスクの数を取得する
		 * @return		子タスクの数
		 */
		KsUInt32							getNumBrother() const;

		/**
		 * 子タスクを取得する
		 * @param		index				子タスクのインデックス
		 * @return		子タスクのポインタ
		 */
		KsTaskBase*								getChild( KsUInt32 index );

		/**
		 * 子タスクの数を取得する
		 * @return		子タスクの数
		 */
		KsUInt32							getNumChild() const;

		/**
		 * コールバック関数
		 */
		KsTaskBase*								allChildCallback( KsTaskBase* pTask, KsTaskCallback callback, void* pUserData );

	protected:
		/**
		 * 初期化処理(マネージャに登録されたときに登録)
		 * @param		pParam				パラメータ
		 */
		virtual void*						initialize( void* pParam ) = 0;

		/**
		 * タスクの実行
		 * @param		pParam				パラメータ
		 */
		virtual void*						execute( void* pParam ) = 0;

		/**
		 * 描画処理
		 * @param		pParam				パラメータ
		 */
		virtual void*						render( void* pParam ) = 0;

		/**
		 * 後処理関数でメモリーから削除されるときに呼ばれる
		 * @param		pParam				パラメータ
		 */
		virtual void*						terminate( void* pParam ) = 0;

	protected:
		KsChar								m_name[ ksTASK_NAME_LENGTH ];		/**< タスク名の最大長					*/
		KsUInt32							m_id;								/**< タスク識別ID(自動的に割り振る?)	*/
		KsUInt32							m_flags;							/**< タスクの各種フラグ					*/
		KsUInt32							m_order;							/**< 描画オーダー						*/
		ksTASK_TYPE							m_type;								/**< タスクのタイプ(種別)				*/
		KsTaskPRIORITY						m_priority;							/**< 優先順位							*/
		KsReal								m_waitTimer;						/**< ウエイトタイマー					*/
		KsTaskBase*								m_pParent;							/**< 親タスクのポインタ					*/
		KsTaskBase*								m_pPrevBrother;						/**< 兄弟タスクのポインタ(兄)			*/
		KsTaskBase*								m_pNextBrother;						/**< 兄弟タスクのポインタ(弟)			*/
		KsTaskBase*								m_pChild;							/**< 子タスクのポインタ					*/
		KsTaskBase*								m_pPrev;							/**< 描画リンク前						*/
		KsTaskBase*								m_pNext;							/**< 描画リンク後						*/
		KsTaskManager*						m_pManager;							/**< 登録されているマネージャのポインタ	*/
};

#endif /* __ksTASK_H__ */

