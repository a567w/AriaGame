/************************************************************************************************/
/** 
 * @file		KsThreadContext.h
 * @brief		スレッドコンテキスト
 * @author		Tsukasa Kato
 * @date		2004/08/17
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSTHREADCONTEXT_H__
#define __KSTHREADCONTEXT_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                          */
/*==============================================================================================*/
#include "KsMutex.h"
#include "KsEvent.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * スレッド
 * @class	KsThreadContext
 * @author  Tsukasa Kato
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsThreadContext
{
	public:
		/**
		 * コンストラクタ
		 */
								KsThreadContext();

		/**
		 * デストラクタ
		 */
								~KsThreadContext();

		/** 
		 * == 演算子オーバーロード
		 * @retval	ksTRUE		等しい
		 * @retval	ksFALSE		等しくない
		 */
		KsBool					operator == ( const KsThread& rhs ) const;

		/** 
		 * != 演算子オーバーロード
		 * @retval	ksTRUE		等しくない
		 * @retval	ksFALSE		等しい
		 */
		KsBool					operator != ( const KsThread& rhs ) const;

		//void					create( const char* pName, MemoryAllocator*     pAllocator = nullptr );

		/**
		 * スレッドを破棄する
		 */
		void					destroy();

		/**
		 * スレッド処理を開始する
		 */
		void					start();

		/**
		 * スレッドの終了を待機する
		 */
		void					join();

		/**
		 * スレッドＩＤを取得する
		 * @return	スレッドＩＤ
		 */
		KsUInt32				getID() const { return m_id; }

		/**
		 * プライオリティをセットする
		 * @param	priority	プライオリティ
		 */
		void					setPriority( ksTHREAD_PRIORITY_TYPE priority );

		/**
		 * 使用プロセッサをセットする
		 * @param	prosessor	使用プロセッサ番号
		 */
		KsBool					setProcessor( KsUInt32 prosessor );

		/**
		 * スレッドを待機する
		 */
		void					wait( KsHandle handle );

		/**
		 * スレッドのメイン関数
		 * @return	実行終了結果
		 */
		virtual KsUInt32		threadMain();

		/**
		 * 指定時間現在のスレッドの実行を休止する
		 * @param	time		待ち時間(ms)
		 */
		static void				sleep( const KsUInt32 time );

		/**
		 * 現在のスレッドの実行を中断して他のスレッドへ実行を譲ります。
		 */
		static void				yield();

		/**
		 * 指定された変数の値をインクリメントし（1 つ増やします）
		 */
		static KsLong			interlockedIncrement( KsLong* pCount );

		/**
		 * 指定された変数の値をデクリメントし（1 つ減らします）
		 */
		static KsLong			interlockedDecrement( KsLong* pCount );

		/**
		 * スレッドのメイン関数
		 * @param	pParam		スレッドパラメータ
		 */
		friend static KsUInt32 __stdcall KsThreadMainFunc( void* pParam );

	private:
		KsHandle				m_handle;		/**< スレッドハンドル						*/
		KsUInt32				m_id;			/**< スレッドID							*/
		KsBool					m_bJoin;		/**< スレッド登録状態かどうかのフラグ		*/
		KsThreadParam			m_param;		/**< スレッドパラメータ					*/
};

#endif		/* __KSTHREADCONTEXT_H__ */

