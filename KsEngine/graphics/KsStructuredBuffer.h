/************************************************************************************************/
/** 
 * @file		KsStructuredBuffer.h
 * @brief		サンプラー設定クラス
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSTRUCTUREBUFFER_H__
#define __KSSTRUCTUREBUFFER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsStructuredBuffer
 * @brief		サンプラー設定クラス
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		参照カウンタつき
 */
/************************************************************************************************/
class ksENGINE_API KsStructuredBuffer : public KsTexture
{
	public:
		/**
		 * コンストラクタ
		 */
									KsStructuredBuffer();

		/**
		 * デストラクタ
		 */
		virtual						~KsStructuredBuffer();

		/**
		 * 破棄処理
		 */
		virtual void				destroy() = 0;

		/**
		 * リソースを取得する
		 * @return					 リソース
		 */
		virtual void*				getBufferResource() = 0;

		/**
		 * 頂点バッファをロックする
		 * @param	pContext		描画コンテキスト
		 * @param	flags			ロックフラグ
		 * @return					ロックしたバッファの先頭ポインタ
		 */
		virtual void*				lock( const KsRenderContext* pContext, KsUInt32 flags ) = 0;

		/**
		 * 頂点バッファのロックを解除する
		 * @param	pContext		描画コンテキスト
		 */
		virtual void				unlock( const KsRenderContext* pContext ) = 0;

		/**
		 * インデックスバッファからの読み込み
		 * @param	pContext		描画コンテキスト
		 * @param	pData			データ読み込み用のポインタ
		 * @param	size			データサイズ
		 */
		virtual void				read( const KsRenderContext* pContext, void* pData, KsUInt32 size ) = 0;

		/**
		 * インデックスバッファへの書き込み
		 * @param	pContext		描画コンテキスト
		 * @param	pData			データ読み込み用のポインタ
		 * @param	size			データサイズ
		 */
		virtual void				write( const KsRenderContext* pContext, void* pData, KsUInt32 size ) = 0;
};

#endif		/* __KSSTRUCTUREBUFFER_H__ */



