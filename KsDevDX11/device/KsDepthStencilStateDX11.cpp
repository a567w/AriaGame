/************************************************************************************************/
/** 
 * @file		KsDepthStencilStateDX11.cpp
 * @brief		DirectX用深度ステンシルステート
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsDevDX11/KsDevDX11PreCompile.h"
#include "KsDevDX11/device/KsDepthStencilStateDX11.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KsDepthStencilStateDX11::KsDepthStencilStateDX11( KsRenderSystemDX11* pDevice, const KS_DEPTH_STENCIL_DESC* pDepthStencilDesc )
	: KsDepthStencilState( pDepthStencilDesc )
	, m_pState( NULL )
{
	D3D11_DEPTH_STENCIL_DESC	desc;
	
	desc.DepthEnable	              = (KsBool)pDepthStencilDesc->DepthEnable;
	desc.DepthWriteMask	              = (D3D11_DEPTH_WRITE_MASK)pDepthStencilDesc->DepthWriteMask;
	desc.DepthFunc		              = (D3D11_COMPARISON_FUNC)pDepthStencilDesc->DepthFunc;
	desc.StencilEnable	              = pDepthStencilDesc->StencilEnable;
	desc.StencilReadMask              = pDepthStencilDesc->StencilReadMask;
	desc.StencilWriteMask             = pDepthStencilDesc->StencilWriteMask;
	desc.FrontFace.StencilFailOp      = (D3D11_STENCIL_OP)pDepthStencilDesc->FrontFace.StencilFailOp;
	desc.FrontFace.StencilDepthFailOp = (D3D11_STENCIL_OP)pDepthStencilDesc->FrontFace.StencilDepthFailOp;
	desc.FrontFace.StencilPassOp      = (D3D11_STENCIL_OP)pDepthStencilDesc->FrontFace.StencilPassOp;
	desc.FrontFace.StencilFunc        = (D3D11_COMPARISON_FUNC)pDepthStencilDesc->FrontFace.StencilFunc;
	desc.BackFace.StencilFailOp       = (D3D11_STENCIL_OP)pDepthStencilDesc->BackFace.StencilFailOp;
	desc.BackFace.StencilDepthFailOp  = (D3D11_STENCIL_OP)pDepthStencilDesc->BackFace.StencilDepthFailOp;
	desc.BackFace.StencilPassOp       = (D3D11_STENCIL_OP)pDepthStencilDesc->BackFace.StencilPassOp;
	desc.BackFace.StencilFunc         = (D3D11_COMPARISON_FUNC)pDepthStencilDesc->BackFace.StencilFunc;

	pDevice->getD3DDevice()->CreateDepthStencilState( &desc, &m_pState );
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KsDepthStencilStateDX11::~KsDepthStencilStateDX11()
{
	destroy();
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsDepthStencilStateDX11::destroy()
{
	ksRELEASE( m_pState );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void* KsDepthStencilStateDX11::getRenderResource()
{
	return m_pState;
}


