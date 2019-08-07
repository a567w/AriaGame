/************************************************************************************************/
/** 
 * @file		KsShaderManagerHLSL.cpp
 * @brief		シェーダーマネージャー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsShaderManagerHLSL.h"
#include "KsShaderHLSL.h"
#include "KsRenderSystemDX.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * コンストラクタ
 * @param	pRenderSystem		描画システム
 */
/************************************************************************************************/
KsShaderManagerHLSL::KsShaderManagerHLSL( KsRenderSystemDX* pRenderSystem )
	: m_pRenderSystem( pRenderSystem )
{
	KsZeroMemory( m_handls, sizeof(m_handls) );
}

/************************************************************************************************/
/*
 * デストラクタ
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
 * リソースからシェーダーを生成
 * @param	pName				シェーダー名
 * @param	bCompiled			コンパイル済みかどうかのフラグ
 * @return						シェーダーデータのポインタ
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
