/************************************************************************************************/
/** 
 * @file		KsInputLayoutManagerDX11.cpp
 * @brief		���̓��C�A�E�g�}�l�[�W��(DirectX11)
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsDevDX11/KsDevDX11PreCompile.h"
#include "KsDevDX11/device/KsInputLayoutManagerDX11.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsInputLayoutManagerDX11::KsInputLayoutManagerDX11( KsRenderSystemDX11* pRenderSystem )
	: m_pRenderSystem( pRenderSystem ) 
{
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsInputLayoutManagerDX11::~KsInputLayoutManagerDX11()
{
}

/************************************************************************************************/
/*
 * �C���v�b�g���C�A�E�g�𐶐�����
 * @param		numIndex			�C���f�b�N�X��
 * @param		flags				�t���O
 * @return							�C���v�b�g���C�A�E�g�̃|�C���^
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

