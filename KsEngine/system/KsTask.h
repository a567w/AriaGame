/************************************************************************************************/
/** 
 * @file		KsTask.h
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
/*                                 << インクルード >>                                          */
/*==============================================================================================*/
#include "KsCore.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
#define ksTASK_NAME_LENGTH			( 16 )			/**< タスクの名前の最大長( 15文字 + '\0' )	*/
#define ksTASK_ORDER_DEFAULT		(  4 )			/**< デフォルトのタスクオーダー				*/


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
		 * 子タスクを追加する
		 * @param		pTask				追加する子タスクのポインタ
		 * @param		pUserData			ユーザーデータ
		 * @note		ユーザーデータがNULLのときは、マネージャの実行処理のときに,
		 *				マネージャに渡されたユーザーデータがユーザーデータに渡されて初期化される。
		 *				しかし、この場合、addChildしたときには、初期化が呼ばれない。そのため、
		 *				ユーザーデータにNULL以外を入れるとそのユーザーデータを使用してaddChildしたときに
		 *				追加されたタスクの初期化処理が呼ばれる。
		 */
		void								add( KsTaskBase* pTask, void* pUserData=NULL );

		/**
		 * 自分のタスクをとりはずす(階層は、自分についたまま)
		 */
		void								detach();

		/**
		 * 自分より下の階層からタスクを削除する(削除フラグが、たつ)
		 */
		void								remove();

		/**
		 * 自分より下の階層からタスクを削除する(削除フラグが、たつ)
		 */
		void								destroy();

		/**
		 * ID(検索自分より下の階層から一致するタスクを検索する)
		 * @param		id					検索するID
		 */
		KsTaskBase*							find( KsUInt32 id );

		/**
		 * 名前検索(検索自分より下の階層から一致するタスクを検索する)
		 *
		 */
		KsTaskBase*							find( const KsChar* name );

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
		virtual void*						update( void* pParam ) = 0;

		/**
		 * 描画処理
		 * @param		pParam				パラメータ
		 */
		virtual void*						draw( void* pParam ) = 0;

		/**
		 * 後処理関数でメモリーから削除されるときに呼ばれる
		 * @param		pParam				パラメータ
		 */
		virtual void*						terminate( void* pParam ) = 0;

	protected:
		KsChar								m_name[ ksTASK_NAME_LENGTH ];		/**< タスク名の最大長					*/
		KsUInt32							m_id;								/**< タスク識別ID(自動的に割り振る?)	*/
		ksTASK_TYPE							m_type;								/**< タスクのタイプ(種別)				*/

		KsReal								m_wait;													
		KsTaskParam							m_UpdateParam;
		KsTaskParam							m_DrawParam;
		KsRenderCommandBuffer*				
		KsTaskManager*						m_pManager;							/**< 登録されているマネージャのポインタ	*/
};

class KsTaskParam
{


	KsBool			m_bActive;		
	KsUInt32		m_order;
	KsTaskBase*		m_pPrev;
	KsTaskBase*		m_pNext;


/**< ウエイトタイマー					*/
/**< 親タスクのポインタ					*/
/**< 子タスクのポインタ					*/
/**< 描画リンク前						*/
/**< 描画リンク後						*/







}

#endif /* _KSTASK_H__ */

