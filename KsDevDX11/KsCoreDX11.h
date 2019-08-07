/************************************************************************************************/
/** 
 * @file		KsCoreDX11.h
 * @brief		DirectX11用エンジン,コアヘッダー
 * @author		Tsukasa Kato
 * @date		2004/08/17
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSCOREDX11_H__
#define __KSCOREDX11_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

//------------------------------------------------------------------
// DirectX11
//------------------------------------------------------------------
#include <d3d11.h>
//#include <d3dx11.h>
#include <dxgi.h>
#include <D3Dcompiler.h>

//------------------------------------------------------------------
// 基本エンジン
//------------------------------------------------------------------
#include <KsEngine/KsCore.h>

//------------------------------------------------------------------
// DX11用エンジン
//------------------------------------------------------------------
#include <KsDevDX11/KsDevDX11Compile.h>
#include <KsDevDX11/KsMacroDX11.h>
#include <KsDevDX11/device/KsAdapterDX11.h>
#include <KsDevDX11/device/KsAdapterListDX11.h>
#include <KsDevDX11/device/KsInputLayoutDX11.h>
#include <KsDevDX11/device/KsInputLayoutManagerDX11.h>
#include <KsDevDX11/device/KsConstantBufferDX11.h>
#include <KsDevDX11/device/KsRasterizerStateDX11.h>
#include <KsDevDX11/device/KsSamplerStateDX11.h>
#include <KsDevDX11/device/KsBlendStateDX11.h>
#include <KsDevDX11/device/KsDepthStencilStateDX11.h>
#include <KsDevDX11/device/KsIndexBufferDX11.h>
#include <KsDevDX11/device/KsVertexBufferDX11.h>
#include <KsDevDX11/device/KsUnorderedAccessViewDX11.h>
#include <KsDevDX11/device/KsStructuredBufferDX11.h>
#include <KsDevDX11/device/KsHardwareBufferManagerDX11.h>
#include <KsDevDX11/device/KsRenderTargetDX11.h>
#include <KsDevDX11/device/KsDepthStencilDX11.h>
#include <KsDevDX11/device/KsTextureDX11.h>
#include <KsDevDX11/device/KsTextureManagerDX11.h>
#include <KsDevDX11/device/KsRenderTargetTextureDX11.h>
#include <KsDevDX11/device/KsLine2DBatchDX11.h>
#include <KsDevDX11/device/KsLine3DBatchDX11.h>
#include <KsDevDX11/device/KsRectBatchDX11.h>
#include <KsDevDX11/device/KsSpriteBatchDX11.h>
#include <KsDevDX11/device/KsGraphicsDX11.h>
#include <KsDevDX11/device/KsCommandListDX11.h>
#include <KsDevDX11/device/KsRenderContextDX11.h>
#include <KsDevDX11/device/KsRenderSystemDX11.h>



//------------------------------------------------------------------
// シェーダー
//------------------------------------------------------------------
#include <KsDevDX11/shader/hlsl/KsVertexShaderDX11.h>
#include <KsDevDX11/shader/hlsl/KsPixelShaderDX11.h>
#include <KsDevDX11/shader/hlsl/KsComputeShaderDX11.h>
#include <KsDevDX11/shader/hlsl/KsShaderManagerDX11.h>

//------------------------------------------------------------------
// utility
//------------------------------------------------------------------
#include "KsDevDX11/utility/KsDDSTextureLoader.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

// インスタンス化する
//template class ksDEVDX11_API KsArray<int>;
//extern template class ksDEVDX11_API std::vector<int>;

#endif /* __KSCOREDX11_H__ */



