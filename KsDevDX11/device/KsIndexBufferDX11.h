/************************************************************************************************/
/** 
 * @file		KsIndexBufferDX11.h
 * @brief		インデックスバッファ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSINDEXBUFFERDX11_H__
#define __KSINDEXBUFFERDX11_H__

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
 * @class		KsIndexBufferDX
 * @brief		インデックスバッファ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksDEVDX11_API KsIndexBufferDX11 : public KsIndexBuffer
{
		friend class KsRenderContextDX11;
	public:
		/**
		 * コンストラクタ
		 * @param	pRenderSystem	描画システム
		 * @param	pData			データ読み込み用のポインタ
		 * @param	size			データサイズ
		 * @param	numIndex		インデックスの数
		 * @param	indexFormat		インデックスフォーマット
		 * @param	flags			フラグ
		 */
									KsIndexBufferDX11( KsRenderSystemDX11* pRenderSystem, void* pData, KsUInt32 size, KsUInt32 numIndex, KsUInt32 indexFormat, KsUInt32 flags );

		/**
		 * デストラクタ
		 */
		virtual						~KsIndexBufferDX11();

		/**
		 * インデックスバッファを生成する
		 * @param	pRenderSystem	描画システム
		 * @param	pData			データ読み込み用のポインタ
		 * @param	size			データサイズ
		 * @param	numIndex		インデックスの数
		 * @param	indexFormat		インデックスフォーマット
		 * @param	flags			フラグ
		 * @retval	ksTRUE			生成成功
		 * @retval	ksFALSE			生成失敗
		 */
		virtual KsBool				create( KsRenderSystemDX11* pRenderSystem, void* pData, KsUInt32 size, KsUInt32 numIndex, KsUInt32 indexFormat, KsUInt32 flags );

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
		 * インデックスバッファをロックする
		 * @param	pContext		描画コンテキスト
		 * @param	flags			ロックフラグ
		 * @return					ロックしたバッファの先頭ポインタ
		 */
		virtual void*				lock( const KsRenderContext* pContext, KsUInt32 flags );

		/**
		 * インデックスバッファのロックを解除する
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
		 * インデックスバッファバッファを取得
		 * @return					インデックスバッファのポインタ
		 */
		ID3D11Buffer*				getIndexBuffer() { return m_pIndexBuffer; }

	private:
		KsRenderSystemDX11*			m_pRenderSystem;	/**< 描画システム				*/
		ID3D11Buffer*				m_pIndexBuffer;		/**< DirectXインデックスバッファ	*/
		KsUInt32					m_indexSize;		/**< インデックスサイズ			*/
		D3D11_MAPPED_SUBRESOURCE	m_resource;			/**< アクセス用リソース			*/
};


#endif		/* __KSINDEXBUFFERDX11_H__ */


