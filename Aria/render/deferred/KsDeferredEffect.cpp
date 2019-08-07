/************************************************************************************************/
/** 
 * @file		KsDeferredEffect.cpp
 * @brief		KsDeferredEffectファイル
 * @author		Tsukasa Kato
 * @date		2010/12/17
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                          */
/*==============================================================================================*/
#include "Aria/KsGamePreCompile.h"
#include "Aria/render/deferred/KsDeferredEffect.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
#define ksDEFERRED_FVF		( ksFVF_XYZ )

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

namespace
{
	KS_INPUT_ELEMENT_DESC VS_DEFERRED_LAYOUT[] =
	{
		{ "POSITION", 0, KS_GI_FORMAT_R32G32B32_FLOAT, 0,  0, KS_INPUT_PER_VERTEX_DATA, 0 }	// POSITION
	};

	KS_DEFERRED_VERTEX	deferredVertices[] = 
	{
		{ -1.0f,  1.0f, 0.9f },
		{  1.0f,  1.0f, 0.9f },
		{ -1.0f, -1.0f, 0.9f },
		{  1.0f, -1.0f, 0.9f }
	};

	KsUInt16 deferredIndices[] = { 0, 1, 2, 3 };
};

/*************************************************************************************************/
/*
 * コンストラクタ
 */
/*************************************************************************************************/
KsDeferredEffect::KsDeferredEffect()
	: KsEffect()
{
	KsShaderManager*			pShaderManager         = KsShaderManagerDX11::getInstancePtr();
	KsHardwareBufferManager*	pHardwareBufferManager = KsHardwareBufferManagerDX11::getInstancePtr();
	KsInputLayoutManager*		pInputLayoutManager    = KsInputLayoutManagerDX11::getInstancePtr();

	KsVertexShader*	pVS = (KsVertexShader*) pShaderManager->createFromFile( "GBuffer.fx", "VS_Deferred", ksSHADE_MODEL_5_0, ksVERTEX_SHADER );
	KsPixelShader*	pPS = (KsPixelShader*)  pShaderManager->createFromFile( "GBuffer.fx", "PS_Deferred", ksSHADE_MODEL_5_0, ksPIXEL_SHADER );
	KsInputLayout*	pIL = pInputLayoutManager->createInputLayout( VS_DEFERRED_LAYOUT, ksARRAYSIZE( VS_DEFERRED_LAYOUT ), (KsVertexShader*)pVS );
	KsVertexBuffer*	pVB = pHardwareBufferManager->createVertexBuffer( deferredVertices, sizeof(KS_DEFERRED_VERTEX), 4, ksDEFERRED_FVF, 0 );
	KsIndexBuffer*	pIB = pHardwareBufferManager->createIndexBuffer( deferredIndices, sizeof(KsUInt16)* 4, 4, ksFMT_INDEX16, 0 );
	
	addVertexShader( pVS );
	addPixelShader ( pPS );
	addInputLayout ( pIL );
	addVertexBuffer( pVB );
	addIndexBuffer ( pIB );
}

/*************************************************************************************************/
/*
 * デストラクタ
 */
/*************************************************************************************************/
KsDeferredEffect::~KsDeferredEffect()
{
}

/*************************************************************************************************/
/*
 * シェーダーセット
 */
/*************************************************************************************************/
void KsDeferredEffect::setShader( KsRenderContext* pRenderContext, void* pParameter )
{
	const KsUInt32	stride = sizeof( KS_DEFERRED_VERTEX );
	const KsUInt32	offset = 0;

	pRenderContext->setInputLayout( getInputLayout() );
	pRenderContext->setVertexBuffers( 0, 1, getVertexBuffer(), &stride, &offset );
	pRenderContext->setIndexBuffer( getIndexBuffer(), ksFMT_INDEX16, 0 );
	pRenderContext->setVertexShader( getVertexShader() );
	pRenderContext->setPixelShader( getPixelShader() );
}

