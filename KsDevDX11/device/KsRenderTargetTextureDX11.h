/************************************************************************************************/
/** 
 * @file		KsRenderTargetTextureDX11.h
 * @brief		描画ターゲット
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSRENDERTARGETTEXTUREDX11_H__
#define __KSRENDERTARGETTEXTUREDX11_H__

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
 * @class		KsRenderTargetTextureDX11
 * @brief		描画ターゲット
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsRenderTargetTextureDX11 : public KsRenderTargetTexture
{
		friend class KsRenderSystemDX;
	public:
		/**
		 * コンストラクタ
		 */
									KsRenderTargetTextureDX11();

		/**
		 * コンストラクタ
		 */
									KsRenderTargetTextureDX11( KsTexture* pRenderTexture, ID3D11RenderTargetView* pTargetView );

		/**
		 * デストラクタ
		 */
		virtual						~KsRenderTargetTextureDX11();

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
		virtual void*				getRenderResource() { return m_pTargetView; }

	protected:
		ID3D11RenderTargetView*		m_pTargetView;
};



#endif		/* __KSRENDERTARGETTEXTUREDX11_H__ */



