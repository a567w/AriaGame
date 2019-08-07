/************************************************************************************************/
/** 
 * @file		KsConstantBufferDX11.h
 * @brief		定数バッファ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSCONSTANTBUFFERDX11_H__
#define __KSCONSTANTBUFFERDX11_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
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
 * @class		KsConstantBufferDX11
 * @brief		定数バッファ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksDEVDX11_API KsConstantBufferDX11 : public KsConstantBuffer
{
		friend class KsRenderContextDX11;
	public:
		/**
		 * コンストラクタ
		 * @param	pRenderSystem	描画システム
		 * @param	pData			データ読み込み用のポインタ
		 * @param	size			データサイズ
		 * @param	flags			フラグ
		 */
									KsConstantBufferDX11( KsRenderSystemDX11* pRenderSystem, void* pData, KsUInt32 size, KsUInt32 flags );

		/**
		 * デストラクタ
		 */
		virtual						~KsConstantBufferDX11();

		/**
		 * 定数バッファを生成する
		 * @param	pRenderSystem	描画システム
		 * @param	pData			データ読み込み用のポインタ
		 * @param	size			データサイズ
		 * @retval	ksTRUE			生成成功
		 * @retval	ksFALSE			生成失敗
		 */
		virtual KsBool				create( KsRenderSystemDX11* pRenderSystem, void* pData, KsUInt32 size, KsUInt32 flags );


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
		 * 定数バッファをロックする
		 * @param	pContext		描画コンテキスト
		 * @param	flags			ロックフラグ
		 * @return					ロックしたバッファの先頭ポインタ
		 */
		virtual void*				lock( const KsRenderContext* pContext, KsUInt32 flags );

		/**
		 * 定数バッファのロックを解除する
		 * @param	pContext		描画コンテキスト
		 */
		virtual void				unlock( const KsRenderContext* pContext );

		/**
		 * 定数バッファからの読み込み
		 * @param	pContext		描画コンテキスト
		 * @param	pData			データ読み込み用のポインタ
		 * @param	size			データサイズ
		 */
		virtual void				read( const KsRenderContext* pContext, void* pData, KsUInt32 size );

		/**
		 * 定数バッファへの書き込み
		 * @param	pContext		描画コンテキスト
		 * @param	pData			データ読み込み用のポインタ
		 * @param	size			データサイズ
		 */
		virtual void				write( const KsRenderContext* pContext, void* pData, KsUInt32 size );

	protected:
		KsRenderSystemDX11*			m_pRenderSystem;		/**< 描画システム			*/
		ID3D11Buffer*				m_pConstantBuffer;		/**< DirectX定数バッファ		*/
};


#endif		/* __KSCONSTANTBUFFERDX11_H__ */



