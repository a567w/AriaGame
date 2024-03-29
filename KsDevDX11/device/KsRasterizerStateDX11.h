/************************************************************************************************/
/** 
 * @file		KsRasterizerStateDX11.h
 * @brief		DirectX用深度ステンシルステート
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSRASTERIZERSTATEDX11_H__
#define __KSRASTERIZERSTATEDX11_H__

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
 * @class		KsRasterizerStateDX11
 * @brief		深度ステンシルステート
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		参照カウンタつき
 */
/************************************************************************************************/
class ksDEVDX11_API KsRasterizerStateDX11 : public KsRasterizerState
{
		friend class KsRenderSystemDX11;
		friend class KsRenderContextDX11;
	public:
		/**
		 * コンストラクタ
		 */
											KsRasterizerStateDX11( KsRenderSystemDX11* pDevice, const KS_RASTERIZER_DESC* pRasterizerState );


		/**
		 * デストラクタ
		 */
		virtual								~KsRasterizerStateDX11();

		/**
		 * テクスチャの破棄
		 */
		virtual void						destroy();

		/**
		 * リソースを取得する
		 * @return							リソース
		 */
		virtual void*						getRenderResource();

	protected:
		ID3D11RasterizerState*				m_pState;
};

#endif		/* __KSRASTERIZERSTATEDX11_H__ */

