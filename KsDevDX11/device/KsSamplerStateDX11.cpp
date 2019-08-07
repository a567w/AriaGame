/************************************************************************************************/
/** 
 * @file		KsSamplerStateDX11.cpp
 * @brief		DirectX用サンプラーステート
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
#include "KsDevDX11/device/KsSamplerStateDX11.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsSamplerStateDX11::KsSamplerStateDX11( KsRenderSystemDX11* pDevice, const KS_SAMPLER_DESC* pSamplerDesc )
	: KsSamplerState( pSamplerDesc )
	, m_pState( NULL )
{
	D3D11_SAMPLER_DESC	desc;

	desc.Filter	          = (D3D11_FILTER)pSamplerDesc->Filter;
	desc.AddressU         = (D3D11_TEXTURE_ADDRESS_MODE)pSamplerDesc->AddressU;
	desc.AddressV         = (D3D11_TEXTURE_ADDRESS_MODE)pSamplerDesc->AddressV;
	desc.AddressW         = (D3D11_TEXTURE_ADDRESS_MODE)pSamplerDesc->AddressW;
	desc.MipLODBias       = pSamplerDesc->MipLODBias;
	desc.MaxAnisotropy    = pSamplerDesc->MaxAnisotropy;
	desc.ComparisonFunc   = (D3D11_COMPARISON_FUNC)pSamplerDesc->ComparisonFunc;
	desc.BorderColor[ 0 ] = pSamplerDesc->BorderColor[ 0 ];
	desc.BorderColor[ 1 ] = pSamplerDesc->BorderColor[ 1 ];
	desc.BorderColor[ 2 ] = pSamplerDesc->BorderColor[ 2 ];
	desc.BorderColor[ 3 ] = pSamplerDesc->BorderColor[ 3 ];
	desc.MinLOD           = pSamplerDesc->MinLOD;
	desc.MaxLOD           = pSamplerDesc->MaxLOD;

	pDevice->getD3DDevice()->CreateSamplerState( &desc, &m_pState );
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsSamplerStateDX11::~KsSamplerStateDX11()
{
	destroy();
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsSamplerStateDX11::destroy()
{
	ksRELEASE( m_pState );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void* KsSamplerStateDX11::getRenderResource()
{
	return m_pState;
}


