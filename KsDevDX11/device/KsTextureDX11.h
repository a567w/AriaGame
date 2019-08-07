/************************************************************************************************/
/** 
 * @file		KsTextureDX11.h
 * @brief		DirectX用テクスチャ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSTEXTUREDX11_H__
#define __KSTEXTUREDX11_H__

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
 * @class		KsTextureDX11
 * @brief		テクスチャ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		参照カウンタつき
 */
/************************************************************************************************/
class ksDEVDX11_API KsTextureDX11 : public KsTexture
{
		friend class KsRenderSystemDX11;
		friend class KsRenderContextDX11;
	public:
		/**
		 * コンストラクタ
		 */
											KsTextureDX11();

		/**
		 * コンストラクタ
		 * @param		pFileName			ファイル名
		 * @param		flags				読み込み方法のフラグ
		 */
											KsTextureDX11( KsRenderSystemDX11* pRenderSystem, const KsChar* pFileName, KsUInt32 flags );

		/**
		 * コンストラクタ
		 * @param		pImage				イメージファイル
		 * @param		flags				読み込み方法のフラグ
		 */
											KsTextureDX11( KsImage* pImage, KsUInt32 flags );

		/**
		 * コンストラクタ
		 * @param		pD3D11Texture		Direct3Dテクスチャ
		 * @param		pShaderView			シェーダーリソースビュー
		 */
											KsTextureDX11( ID3D11Texture2D* pD3D11Texture, ID3D11ShaderResourceView* pShaderResourceView );

		/**
		 * デストラクタ
		 */
		virtual								~KsTextureDX11();

		/**
		 * テクスチャの破棄
		 */
		virtual void						destroy();

		/**
		 * テクスチャをアクティブにする
		 */
		virtual void						active();

		/**
		 * リソースを取得する
		 * @return							 リソース
		 */
		virtual void*						getBufferResource();

		/**
		 * リソースを取得する
		 * @return							 リソース
		 */
		virtual void*						getTextureResource() { return m_pShaderResourceView; }

		/**
		 * バッファをロックする
		 * @param	pContext				描画コンテキスト
		 * @param	flags					ロックフラグ
		 * @return							ロックしたバッファの先頭ポインタ
		 */
		virtual void*						lock( const KsRenderContext* pContext, KsUInt32 flags );

		/**
		 * バッファのロックを解除する
		 * @param	pContext				描画コンテキスト
		 */
		virtual void						unlock( const KsRenderContext* pContext );

		/**
		 * バッファからの読み込み
		 * @param	pContext				描画コンテキスト
		 * @param	pData					データ読み込み用のポインタ
		 * @param	size					データサイズ
		 */
		virtual void						read( const KsRenderContext* pContext, void* pData, KsUInt32 size );

		/**
		 * バッファへの書き込み
		 * @param	pContext				描画コンテキスト
		 * @param	pData					データ読み込み用のポインタ
		 * @param	size					データサイズ
		 */
		virtual void						write( const KsRenderContext* pContext, void* pData, KsUInt32 size );

		/**
		 * ID3D11Texture2Dのポインタを取得する
		 * @return							ID3D11Texture2Dのポインタ
		 */
		virtual ID3D11Texture2D*			getD3D11Texture() { return m_pD3D11Texture; }

		/**
		 * ID3D11ShaderResourceViewのポインタを取得する
		 * @return							シェーダーリソースビューのポインタ
		 */
		virtual ID3D11ShaderResourceView*	getD3D11ShaderResourceView() { return m_pShaderResourceView; }

	protected:
		KsImage*							m_pImage;				/**< イメージデータ			*/
		ID3D11Texture2D*					m_pD3D11Texture;		/**< Direct3Dテクスチャ		*/
		ID3D11ShaderResourceView*			m_pShaderResourceView;	/**< シェーダーリソースビュー	*/
};


#endif		/* __KSTEXTUREDX11_H__ */

