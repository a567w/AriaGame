/************************************************************************************************/
/** 
 * @file		KsRenderTargetTextureDX11.cpp
 * @brief		DirectX用テクスチャ
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
#include "KsDevDX11/device/KsTextureManagerDX11.h"

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
KsRenderTargetTextureDX11::KsRenderTargetTextureDX11()
	: KsRenderTargetTexture()
	, m_pTargetView( 0 )
{
}

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsRenderTargetTextureDX11::KsRenderTargetTextureDX11( KsTexture* pRenderTexture, ID3D11RenderTargetView* pTargetView )
	: KsRenderTargetTexture( pRenderTexture )
	, m_pTargetView( pTargetView )
{
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KsRenderTargetTextureDX11::~KsRenderTargetTextureDX11()
{
}

/************************************************************************************************/
/*
 * ロックする
 * @return					データのポインタ
 */
/************************************************************************************************/
void* KsRenderTargetTextureDX11::lock()
{
	return NULL;
}

/************************************************************************************************/
/*
 * ロックを解除する
 */
/************************************************************************************************/
void KsRenderTargetTextureDX11::unlock()
{
}

/************************************************************************************************/
/*
 * テクスチャの破棄
 */
/************************************************************************************************/
void KsRenderTargetTextureDX11::destroy()
{
	ksRELEASE( m_pTargetView );
}
