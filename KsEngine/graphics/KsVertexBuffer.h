/************************************************************************************************/
/** 
 * @file		KsVertexBuffer.h
 * @brief		頂点バッファ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSVERTEXBUFFER_H__
#define __KSVERTEXBUFFER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsRenderContext;

/************************************************************************************************/
/**
 * @class		KsVertexBuffer
 * @brief		頂点バッファ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsVertexBuffer : public KsBufferObject
{
	public:
		/**
		 * コンストラクタ
		 */
									KsVertexBuffer();

		/**
		 * デストラクタ
		 */
		virtual						~KsVertexBuffer();

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

		/**
		 * 頂点のサイズを取得する
		 * @return					頂点のサイズ
		 */
		virtual KsUInt32			getVertexSize() const { return m_vertexSize; }

		/**
		 * 頂点数を取得する
		 * @return					頂点数
		 */
		virtual KsUInt32			getNumVertex() const { return m_numVertex; }

		/**
		 * 頂点フォーマットを取得する
		 * @return					頂点フォーマットを
		 */
		virtual KsUInt32			getVertexFormat() const { return m_vertexFormat; }

	protected:
		KsUInt32					m_vertexSize;		/**< 頂点のサイズ		*/
		KsUInt32					m_numVertex;		/**< 頂点数				*/
		KsUInt32					m_vertexFormat;		/**< 頂点フォーマット		*/
};

#endif		/* __KSVERTEXBUFFER_H__ */



