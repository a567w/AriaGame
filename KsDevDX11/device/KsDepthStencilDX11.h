/************************************************************************************************/
/** 
 * @file		KsDepthStencilDX11.h
 * @brief		描画ターゲット
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSDEPTHSTENCILDX11_H__
#define __KSDEPTHSTENCILDX11_H__

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
 * @class		KsDepthStencilDX11
 * @brief		描画ターゲット(DX11)
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsDepthStencilDX11 : public KsRenderTargetTexture
{
		friend class KsRenderSystemDX11;
		friend class KsRenderContextDX11;
	public:
		/**
		 * コンストラクタ
		 */
									KsDepthStencilDX11();

		/**
		 * コンストラクタ
		 */
									KsDepthStencilDX11( KsTexture* pDepthStencilTexture, ID3D11DepthStencilView* pDepthStencilView );

		/**
		 * デストラクタ
		 */
		virtual						~KsDepthStencilDX11();

		/**
		 * ロックする
		 * @return					データのポインタ
		 */
		virtual void*				lock();

		/**
		 * ロックを解除する
		 */
		virtual void				unlock();

		/**
		 * テクスチャの破棄
		 */
		virtual void				destroy();

		/**
		 * リソースを取得する
		 * @return					 リソース
		 */
		virtual void*				getRenderResource() { return m_pDepthStencilView; }

	protected:
		ID3D11DepthStencilView*		m_pDepthStencilView;	/**< 深度ステンシルビュー		*/
};



#endif		/* __KSDEPTHSTENCILDX11_H__ */



