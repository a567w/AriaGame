/************************************************************************************************/
/** 
 * @file		KsRasterizerStateDX11.cpp
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
#include "KsDevDX11/device/KsRasterizerStateDX11.h"

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
KsRasterizerStateDX11::KsRasterizerStateDX11( KsRenderSystemDX11* pDevice, const KS_RASTERIZER_DESC* pRasterizerState )
	: KsRasterizerState( pRasterizerState )
	, m_pState( NULL )
{
	D3D11_RASTERIZER_DESC	desc;
	
	desc.FillMode              = (D3D11_FILL_MODE)pRasterizerState->FillMode;
	desc.CullMode              = (D3D11_CULL_MODE)pRasterizerState->CullMode;
	desc.FrontCounterClockwise = pRasterizerState->FrontCounterClockwise;
	desc.DepthBias             = pRasterizerState->DepthBias;
	desc.DepthBiasClamp        = pRasterizerState->DepthBiasClamp;
	desc.SlopeScaledDepthBias  = pRasterizerState->SlopeScaledDepthBias;
	desc.DepthClipEnable       = pRasterizerState->DepthClipEnable;
	desc.ScissorEnable         = pRasterizerState->ScissorEnable;
	desc.MultisampleEnable     = pRasterizerState->MultisampleEnable;
	desc.AntialiasedLineEnable = pRasterizerState->AntialiasedLineEnable;

	pDevice->getD3DDevice()->CreateRasterizerState( &desc, &m_pState );
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KsRasterizerStateDX11::~KsRasterizerStateDX11()
{
	destroy();
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsRasterizerStateDX11::destroy()
{
	ksRELEASE( m_pState );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void* KsRasterizerStateDX11::getRenderResource()
{
	return m_pState;
}


