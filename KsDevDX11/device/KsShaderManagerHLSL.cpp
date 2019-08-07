/************************************************************************************************/
/** 
 * @file		KsShaderManagerHLSL.cpp
 * @brief		�V�F�[�_�[�}�l�[�W���[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsShaderManagerHLSL.h"
#include "KsShaderHLSL.h"
#include "KsRenderSystemDX.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * �R���X�g���N�^
 * @param	pRenderSystem		�`��V�X�e��
 */
/************************************************************************************************/
KsShaderManagerHLSL::KsShaderManagerHLSL( KsRenderSystemDX* pRenderSystem )
	: m_pRenderSystem( pRenderSystem )
{
	KsZeroMemory( m_handls, sizeof(m_handls) );
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsShaderManagerHLSL::~KsShaderManagerHLSL()
{
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsShader* KsShaderManagerHLSL::createFromFile( const KsChar* pName, KsBool bCompiled )
{
	KsShader*		pShader = findRefInc( pName );

	if( pShader )
	{
		return pShader;
	}

	LPD3DXEFFECT	pEffect = NULL;
	LPD3DXBUFFER	pError  = NULL;
	HRESULT			hr;
	DWORD			flags = 0;
	
	if( bCompiled )
	{
		flags = D3DXFX_NOT_CLONEABLE;
	}

	hr = D3DXCreateEffectFromFile( m_pRenderSystem->getD3DDevice(), pName, NULL , NULL , flags , NULL , &pEffect , &pError );

	ksRELEASE( pError );

	if( D3D_OK != hr )
	{
		return NULL;
	}

	KsShaderHLSL*	pShaderHLSL = new KsShaderHLSL( m_pRenderSystem );
	
	pShaderHLSL->initialize( pName, pEffect );

	add( pShaderHLSL );

	return pShaderHLSL;
}

/************************************************************************************************/
/*
 * ���\�[�X����V�F�[�_�[�𐶐�
 * @param	pName				�V�F�[�_�[��
 * @param	bCompiled			�R���p�C���ς݂��ǂ����̃t���O
 * @return						�V�F�[�_�[�f�[�^�̃|�C���^
 */
/************************************************************************************************/
KsShader* KsShaderManagerHLSL::createFromResource( const KsChar* pName, KsBool bCompiled )
{
	KsShader*		pShader = findRefInc( pName );

	if( pShader )
	{
		return pShader;
	}

	LPD3DXEFFECT	pEffect;
	LPD3DXBUFFER	pError;
	HRESULT			hr;
	DWORD			flags = 0;
	
	if( bCompiled )
	{
		flags = D3DXFX_NOT_CLONEABLE;
	}

	hr = D3DXCreateEffectFromResource( m_pRenderSystem->getD3DDevice(), NULL, pName, NULL , NULL , flags , NULL , &pEffect , &pError );

	ksRELEASE( pError );

	if( D3D_OK != hr )
	{
		return NULL;
	}

	KsShaderHLSL*	pShaderHLSL = new KsShaderHLSL( m_pRenderSystem );
	
	pShaderHLSL->initialize( pName, pEffect );

	add( pShaderHLSL );

	return pShaderHLSL;
}

void KsShaderManagerHLSL::setVertexShaderConstantB( KsUInt32 startRegister, const KsBool* pConstantData, KsUInt32 count )
{
	m_pRenderSystem->getD3DDevice()->SetVertexShaderConstantB( startRegister, pConstantData, count );
}

void KsShaderManagerHLSL::setVertexShaderConstantF( KsUInt32 startRegister, const KsReal* pConstantData, KsUInt32 count )
{
	m_pRenderSystem->getD3DDevice()->SetVertexShaderConstantF( startRegister, pConstantData, count );
}

void KsShaderManagerHLSL::setVertexShaderConstantI( KsUInt32 startRegister, const KsInt32* pConstantData, KsUInt32 count )
{
	m_pRenderSystem->getD3DDevice()->SetVertexShaderConstantI( startRegister, pConstantData, count );
}


void KsShaderManagerHLSL::setPixelShaderConstantB( KsUInt32 startRegister, const KsBool*  pConstantData, KsUInt32 count )
{
	m_pRenderSystem->getD3DDevice()->SetPixelShaderConstantB( startRegister, pConstantData, count );
}

void KsShaderManagerHLSL::setPixelShaderConstantF( KsUInt32 startRegister, const KsReal*  pConstantData, KsUInt32 count )
{
	m_pRenderSystem->getD3DDevice()->SetPixelShaderConstantF( startRegister, pConstantData, count );
}

void KsShaderManagerHLSL::setPixelShaderConstantI( KsUInt32 startRegister, const KsInt32* pConstantData, KsUInt32 count )
{
	m_pRenderSystem->getD3DDevice()->SetPixelShaderConstantI( startRegister, pConstantData, count );
}
