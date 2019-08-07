/************************************************************************************************/
/** 
 * @file		KsVertexBufferDX11.h
 * @brief		頂点バッファ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSVERTEXBUFFERDX11_H__
#define __KSVERTEXBUFFERDX11_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsRenderSystemDX11;

/************************************************************************************************/
/**
 * @class		KsVertexBufferDX11
 * @brief		頂点バッファ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksDEVDX11_API KsVertexBufferDX11 : public KsVertexBuffer
{
		friend class KsRenderContextDX11;
	public:
		/**
		 * 頂点バッファを生成する
		 * @param	pRenderSystem	描画システム
		 * @param	pData			データ読み込み用のポインタ
		 * @param	vertexSize		頂点サイズ
		 * @param	numVertex		頂点数
		 * @param	vertexFormat	頂点フォーマット
		 * @param	flags			フラグ
		 */
									KsVertexBufferDX11( KsRenderSystemDX11* pRenderSystem, void* pData, KsUInt32 vertexSize, KsUInt32 numVertex, KsUInt32 vertexFormat, KsUInt32 flags );

		/**
		 * デストラクタ
		 */
		virtual						~KsVertexBufferDX11();

		/**
		 * 頂点バッファを生成する
		 * @param	pRenderSystem	描画システム
		 * @param	pData			データ読み込み用のポインタ
		 * @param	vertexSize		頂点サイズ
		 * @param	numVertex		頂点数
		 * @param	vertexFormat	頂点フォーマット
		 * @param	flags			フラグ
		 * @retval	ksTRUE			生成成功
		 * @retval	ksFALSE			生成失敗
		 */
		virtual KsBool				create( KsRenderSystemDX11* pRenderSystem, void* pData, KsUInt32 vertexSize, KsUInt32 numVertex, KsUInt32 vertexFormat, KsUInt32 flags );

		/**
		 * 破棄処理
		 */
		virtual void				destroy();

		/**
		 * リソースを取得する
		 * @return					 リソース
		 */
		virtual void*				getBufferResource();

		/**
		 * 頂点バッファをロックする
		 * @param	pContext		描画コンテキスト
		 * @param	flags			ロックフラグ
		 * @return					ロックしたバッファの先頭ポインタ
		 */
		virtual void*				lock( const KsRenderContext* pContext, KsUInt32 flags );

		/**
		 * 頂点バッファのロックを解除する
		 * @param	pContext		描画コンテキスト
		 */
		virtual void				unlock( const KsRenderContext* pContext );

		/**
		 * インデックスバッファからの読み込み
		 * @param	pContext		描画コンテキスト
		 * @param	pData			データ読み込み用のポインタ
		 * @param	size			データサイズ
		 */
		virtual void				read( const KsRenderContext* pContext, void* pData, KsUInt32 size );

		/**
		 * インデックスバッファへの書き込み
		 * @param	pContext		描画コンテキスト
		 * @param	pData			データ読み込み用のポインタ
		 * @param	size			データサイズ
		 */
		virtual void				write( const KsRenderContext* pContext, void* pData, KsUInt32 size );

		/**
		 * 頂点バッファを取得
		 * @return					頂点バッファのポインタ
		 */
		ID3D11Buffer*				getVertexBuffer() { return m_pVertexBuffer; }

	private:
		KsRenderSystemDX11*			m_pRenderSystem;	/**< 描画システム			*/
		ID3D11Buffer*				m_pVertexBuffer;	/**< DirectX頂点バッファ		*/
		D3D11_MAPPED_SUBRESOURCE	m_resource;			/**< アクセス用リソース		*/
};


#endif		/* __KSVERTEXBUFFERDX11_H__ */


