/************************************************************************************************/
/** 
 * @file		KsPMD.cpp
 * @brief		PMDファイル
 * @author		Tsukasa Kato
 * @date		2010/12/17
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                          */
/*==============================================================================================*/
#include "KsMMD/KsMMDPreCompile.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
KsEffectMMD::KsEffectMMD()
	: m_pMB( 0 )
{
	m_pDiffuseTexture = NULL; 
}

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
void KsEffectMMD::setShader( KsRenderContext* pRenderContext, void* pParameter )
{
	KsModelParameter*	pModelParameter = (KsModelParameter*)pParameter;

	if( m_pMB )
	{
		pRenderContext->updateConstantBuffers( m_pMB, &pModelParameter->Model );
	}

	pRenderContext->updateConstantBuffers( m_pCB, &pModelParameter->GBuffer );
	pRenderContext->setVertexShader( m_pVS );
	pRenderContext->setPixelShader( m_pPS );

	pRenderContext->setVertexConstantBuffers( 0, 1, m_pCB );
	pRenderContext->setVertexConstantBuffers( 1, 1, m_pMB );
	pRenderContext->setPixelConstantBuffers( 0, 1, m_pCB );
	pRenderContext->setVertexConstantBuffers( 1, 1, m_pMB );

	if( m_pDiffuseTexture )
	{
		pRenderContext->setPixelTexture( 0, 1, m_pDiffuseTexture );
	}
}

