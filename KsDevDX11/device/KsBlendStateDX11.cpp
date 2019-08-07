/************************************************************************************************/
/** 
 * @file		KsBlendStateDX11.cpp
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
#include "KsDevDX11/device/KsBlendStateDX11.h"

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
KsBlendStateDX11::KsBlendStateDX11( KsRenderSystemDX11* pDevice, const KS_BLEND_DESC* pBlendStateDesc )
	: KsBlendState( pBlendStateDesc )
	, m_pState( NULL )
{
	D3D11_BLEND_DESC	desc;

	desc.AlphaToCoverageEnable  = pBlendStateDesc->AlphaToCoverageEnable;
	desc.IndependentBlendEnable = pBlendStateDesc->IndependentBlendEnable;
	
	for( KsUInt32 i=0; i<ksARRAYSIZE(pBlendStateDesc->RenderTarget); i++ )
	{
		desc.RenderTarget[ i ].BlendEnable           = (KsBool)pBlendStateDesc->RenderTarget[ i ].BlendEnable;
		desc.RenderTarget[ i ].SrcBlend              = (D3D11_BLEND)pBlendStateDesc->RenderTarget[ i ].SrcBlend;
		desc.RenderTarget[ i ].DestBlend             = (D3D11_BLEND)pBlendStateDesc->RenderTarget[ i ].DestBlend;
		desc.RenderTarget[ i ].BlendOp               = (D3D11_BLEND_OP)pBlendStateDesc->RenderTarget[ i ].BlendOp;
		desc.RenderTarget[ i ].SrcBlendAlpha         = (D3D11_BLEND)pBlendStateDesc->RenderTarget[ i ].SrcBlendAlpha;
		desc.RenderTarget[ i ].DestBlendAlpha        = (D3D11_BLEND)pBlendStateDesc->RenderTarget[ i ].DestBlendAlpha;
		desc.RenderTarget[ i ].BlendOpAlpha          = (D3D11_BLEND_OP)pBlendStateDesc->RenderTarget[ i ].BlendOpAlpha;
		desc.RenderTarget[ i ].RenderTargetWriteMask = pBlendStateDesc->RenderTarget[ i ].RenderTargetWriteMask;
	}

	pDevice->getD3DDevice()->CreateBlendState( &desc, &m_pState );
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KsBlendStateDX11::~KsBlendStateDX11()
{
	destroy();
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsBlendStateDX11::destroy()
{
	ksRELEASE( m_pState );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void* KsBlendStateDX11::getRenderResource()
{
	return m_pState;
}


