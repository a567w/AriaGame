/************************************************************************************************/
/** 
 * @file		KsInputLayoutManagerDX11.cpp
 * @brief		入力レイアウトマネージャ(DirectX11)
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsDevDX11/KsDevDX11PreCompile.h"
#include "KsDevDX11/device/KsInputLayoutManagerDX11.h"

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
KsInputLayoutManagerDX11::KsInputLayoutManagerDX11( KsRenderSystemDX11* pRenderSystem )
	: m_pRenderSystem( pRenderSystem ) 
{
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsInputLayoutManagerDX11::~KsInputLayoutManagerDX11()
{
}

/************************************************************************************************/
/*
 * インプットレイアウトを生成する
 * @param		numIndex			インデックス数
 * @param		flags				フラグ
 * @return							インプットレイアウトのポインタ
 */
/************************************************************************************************/
KsInputLayout* KsInputLayoutManagerDX11::createInputLayout( const KS_INPUT_ELEMENT_DESC* pInputElementDescs, KsUInt32 numElements, const KsVertexShader* pVertexShader )
{
	ID3D11Device*		pDevice        = m_pRenderSystem->getD3DDevice();
	ID3D11InputLayout*	pInputLayoutDX = NULL;

	const KsUInt32 hr = pDevice->CreateInputLayout( (const D3D11_INPUT_ELEMENT_DESC*)pInputElementDescs,
													numElements,
													((KsVertexShader*)pVertexShader)->getBufferPointer(),
													((KsVertexShader*)pVertexShader)->getBufferSize(),
													&pInputLayoutDX );

	if( ksFAILED( hr ) )
	{
		return NULL;
	}

	KsInputLayoutDX11*	pInputLayout = new KsInputLayoutDX11();
	
	pInputLayout->m_pVertexLayout = pInputLayoutDX;

	return pInputLayout;
}

