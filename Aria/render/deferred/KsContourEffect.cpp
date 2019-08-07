/************************************************************************************************/
/** 
 * @file		KsContourEffect.cpp
 * @brief		KsContourEffect�t�@�C��
 * @author		Tsukasa Kato
 * @date		2010/12/17
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                          */
/*==============================================================================================*/
#include "Aria/KsGamePreCompile.h"
#include "Aria/render/deferred/KsContourEffect.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/
#define ksCONTOUR_FVF		( ksFVF_XYZ | ksFVF_TEX )

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

namespace
{
	KS_INPUT_ELEMENT_DESC VS_CONTOUR_LAYOUT[] =
	{
		{ "POSITION", 0, KS_GI_FORMAT_R32G32B32_FLOAT,    0,  0, KS_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, KS_GI_FORMAT_R32G32_FLOAT,       0, 12, KS_INPUT_PER_VERTEX_DATA, 0 },
	};

	KS_CONTOUR_VERTEX	contourVertices[] = 
	{
		{ -1.0f,  1.0f, 1.0f, 0.0f, 0.0f },
		{  1.0f,  1.0f, 1.0f, 1.0f, 0.0f },
		{ -1.0f, -1.0f, 1.0f, 0.0f, 1.0f },
		{  1.0f, -1.0f, 1.0f, 1.0f, 1.0f }
	};

	KsUInt16 contourIndices[] = { 0, 1, 2, 3 };
};

/*************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/*************************************************************************************************/
KsContourEffect::KsContourEffect()
	: KsEffect()
{
	KsShaderManager*			pShaderManager         = KsShaderManagerDX11::getInstancePtr();
	KsHardwareBufferManager*	pHardwareBufferManager = KsHardwareBufferManagerDX11::getInstancePtr();
	KsInputLayoutManager*		pInputLayoutManager    = KsInputLayoutManagerDX11::getInstancePtr();

	KsVertexShader*	pVS = (KsVertexShader*) pShaderManager->createFromFile( "ContourExtraction.fx", "VS_ContourExtraction", ksSHADE_MODEL_5_0, ksVERTEX_SHADER );
	KsPixelShader*	pPS = (KsPixelShader*)  pShaderManager->createFromFile( "ContourExtraction.fx", "PS_ContourExtraction", ksSHADE_MODEL_5_0, ksPIXEL_SHADER );
	KsInputLayout*	pIL = pInputLayoutManager->createInputLayout( VS_CONTOUR_LAYOUT, ksARRAYSIZE( VS_CONTOUR_LAYOUT ), (KsVertexShader*)pVS );
	KsVertexBuffer*	pVB = pHardwareBufferManager->createVertexBuffer( contourVertices, sizeof(KS_CONTOUR_VERTEX), 4, ksCONTOUR_FVF, 0 );
	KsIndexBuffer*	pIB = pHardwareBufferManager->createIndexBuffer( contourIndices, sizeof(KsUInt16)* 4, 4, ksFMT_INDEX16, 0 );

	addVertexShader( pVS );
	addPixelShader ( pPS );
	addInputLayout ( pIL );
	addVertexBuffer( pVB );
	addIndexBuffer ( pIB );
}

/*************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/*************************************************************************************************/
KsContourEffect::~KsContourEffect()
{
}

/*************************************************************************************************/
/*
 * �V�F�[�_�[�Z�b�g
 */
/*************************************************************************************************/
void KsContourEffect::setShader( KsRenderContext* pRenderContext, void* pParameter )
{
	const KsUInt32	stride = sizeof( KS_CONTOUR_VERTEX );
	const KsUInt32	offset = 0;

	pRenderContext->setInputLayout( getInputLayout() );
	pRenderContext->setVertexBuffers( 0, 1, getVertexBuffer(), &stride, &offset );
	pRenderContext->setIndexBuffer( getIndexBuffer(), ksFMT_INDEX16, 0 );
	pRenderContext->setVertexShader( getVertexShader() );
	pRenderContext->setPixelShader( getPixelShader() );
}

