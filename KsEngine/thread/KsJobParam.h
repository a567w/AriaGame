/************************************************************************************************/
/** 
 * @file		KsThread.h
 * @brief		スレッド管理
 * @author		Tsukasa Kato
 * @date		2004/08/17
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSTHREAD_H__
#define __KSTHREAD_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                          */
/*==============================================================================================*/
#include "KsMutex.h"
#include "KsEvent.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
#define ksTHREAD_END()		_endthreadex( 0 )	/**< スレッド終了マクロ		*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
typedef KsUInt32 ( __stdcall *KsThreadFunc )( void * );

/************************************************************************************************/
/**
 * スレッド
 * @class	KsThread
 * @author  Tsukasa Kato
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsThread
{
	public:
		/**
		 * コンストラクタ
		 */
								KsThread();

		/**
		 * コンストラクタ
		 * @param	pParam		パラメータ
		 */
		explicit				KsThread( KsThreadFunc func, void* pParam );

		/**
		 * デストラクタ
		 */
								~KsThread();

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

		/**
		 * スレッドの終了を待機する
		 */
		void					join();

		/**
		 * 使用プロセッサをセットする
		 * @param	prosessor	使用プロセッサ番号
		 */
		KsBool					setProcessor( KsUInt32 prosessor );

		/**
		 * 指定時間現在のスレッドの実行を休止する
		 * @param	time		待ち時間(ms)
		 */
		static void				sleep( const KsUInt32 time );

		/**
		 * 現在のスレッドの実行を中断して他のスレッドへ実行を譲ります。
		 */
		static void				yield();

	private:
		KsHandle				m_handle;		/**< スレッドハンドル						*/
		KsUInt32				m_id;			/**< スレッドID							*/
		KsBool					m_bJoin;		/**< スレッド登録状態かどうかのフラグ		*/
};

#endif		/* __KSTHREAD_H__ */

