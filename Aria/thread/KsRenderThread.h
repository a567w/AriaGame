/************************************************************************************************/
/** 
 * @file		KsRenderThread.h
 * @brief		描画スレッド
 * @author		Tsukasa Kato
 * @date		2011/07/02
 * @since		2011/07/02
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSRENDERTHREAD_H__
#define __KSRENDERTHREAD_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsDeferredRender;

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * 描画スレッド
 * @class	KsRenderThread
 * @author  Tsukasa Kato
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class KsRenderThread : public KsThread
{
	public:
		/**
		 * コンストラクタ
		 */
										KsRenderThread( KsRenderSystem* pRenderSystem, KsDeferredRender* pDeferredRender );

		/**
		 * デストラクタ
		 */
										~KsRenderThread();

		/**
		 * 実行する
		 */
		KsBool							run();

		/**
		 * スレッドのメイン関数
		 * @return	実行終了結果
		 */
		virtual KsUInt32				threadMain();

		/**
		 * スレッド描画開始する
		 */
		void							startBeginRender();

		/**
		 * 描画終了イベントを待つ
		 */
		void							waitEndRender();
		
		/**
		 * コマンドリストを取得する
		 * @return	コマンドリストのポインタ
		 */
		KsCommandList*					getCommandList() { return m_pCommandList; }

	private:
		KsHandle						m_syncEvent;			/**< 同期イベント				*/
		KsHandle						m_beginRenderEvent;		/**< 描画開始イベント				*/
		KsHandle						m_endRenderEvent;		/**< 描画終了イベント				*/
		KsBool							m_bThreadLoop;			/**< スレッドループ				*/
		KsMainThread*					m_pMainThread;			/**< メインスレッド				*/

		KsRenderSystem*					m_pRenderSystem;		/**< 描画システム				*/
		KsDeferredRender*				m_pDeferredRender;		/**< ディファード描画システム		*/
		KsBool							m_bClearState;			/**< ステートをクリアする			*/
		KsBool							m_bRestoreState;		/**< ステートをクリアする			*/
		KsRenderContext*				m_pRenderContext;		/**< 描画コンテキスト(遅延)		*/
		KsCommandList*					m_pCommandList;			/**< 描画コマンドリスト			*/

		KsDepthStencilState*			m_pDepthState;			/**< ラスタライズステート			*/
};


#endif	/* __KSRENDERTHREAD_H__ */


