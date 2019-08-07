/************************************************************************************************/
/** 
 * @file		KsLine3DBatchDX11.cpp
 * @brief		3D���C���`��
 * @author		Tsukasa Kato
 * @date		2004/08/17
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*									  << �C���N���[�h >>											*/
/*==============================================================================================*/
#include "KsDevDX11/KsDevDX11PreCompile.h"
#include "KsDevDX11/device/KsLine3DBatchDX11.h"


/*==============================================================================================*/
/*									  << �錾 >>													*/
/*==============================================================================================*/

namespace
{
	KS_INPUT_ELEMENT_DESC VS_LINE3D_LAYOUT[] =
	{
		{ "POSITION", 0, KS_GI_FORMAT_R32G32B32_FLOAT,    0,  0, KS_INPUT_PER_VERTEX_DATA, 0 },	// POSITION
		{ "COLOR",	  0, KS_GI_FORMAT_R32G32B32A32_FLOAT, 0, 12, KS_INPUT_PER_VERTEX_DATA, 0 },	// COLOR
	};
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsLine3DBatchDX11::KsLine3DBatchDX11( KsUInt32 count )
	: m_lineCount( 0 )
	, m_lineMax( 0 )
	, m_lineIndex( 0 )
	, m_lineStride( 0 )
	, m_lineOffset( 0 )
	, m_lineColor( 1.0f, 1.0f, 1.0f, 1.0f )
	, m_pLineVertices( 0 )
	, m_pLineVS( 0 )
	, m_pLinePS( 0 )
	, m_pLineVB( 0 )
	, m_pLineIL( 0 )
{
	create( count );
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsLine3DBatchDX11::~KsLine3DBatchDX11()
{
	destroy();
}

/************************************************************************************************/
/*
 * �o�b�t�@�𐶐�����
 * @param	count			�ő�v���~�e�B�u��
 */
/************************************************************************************************/
void KsLine3DBatchDX11::create( KsUInt32 count )
{
	KsShaderManager*			pShaderManager         = KsShaderManagerDX11::getInstancePtr();
	KsInputLayoutManager*		pInputLayoutManager    = KsInputLayoutManagerDX11::getInstancePtr();
	KsHardwareBufferManager*	pHardwareBufferManager = KsHardwareBufferManagerDX11::getInstancePtr();

	m_lineStride = sizeof( KS_VERTEX_LINE3D );
	m_lineOffset = 0;
	m_lineMax    = count;

	m_pLineVS = (KsVertexShader*)pShaderManager->createFromFile( "line.fx", "VS_Line3D", ksSHADE_MODEL_5_0, ksVERTEX_SHADER );
	m_pLinePS = (KsPixelShader*) pShaderManager->createFromFile( "line.fx", "PS_Line3D", ksSHADE_MODEL_5_0, ksPIXEL_SHADER  );
	m_pLineVB = pHardwareBufferManager->createVertexBuffer( sizeof(KS_VERTEX_LINE3D), count * 2, ksLINE3D_FVF, ksCPU_ACCESS_WRITE );
	m_pLineIL = pInputLayoutManager->createInputLayout( VS_LINE3D_LAYOUT, ksARRAYSIZE( VS_LINE3D_LAYOUT ), (KsVertexShader*)m_pLineVS );
	
	m_pLineVertices = ksNew KS_VERTEX_LINE3D[ count * 2 ];
}

/************************************************************************************************/
/*
 * �o�b�t�@��j������
 */
/************************************************************************************************/
void KsLine3DBatchDX11::destroy()
{
	ksDELETEARRAY( m_pLineVS );
	ksDELETEARRAY( m_pLinePS );
	ksDELETEARRAY( m_pLineVB );
	ksDELETEARRAY( m_pLineIL );
	ksDELETEARRAY( m_pLineVertices );
}

/************************************************************************************************/
/*
 * �J���[���Z�b�g����
 * @param	rectColor	�J���[�l
 */
/************************************************************************************************/
void KsLine3DBatchDX11::setColor( const KsColorReal& rectColor )
{
	m_lineColor.set( rectColor );
}

/************************************************************************************************/
/*
 * �J���[���Z�b�g����
 * @param	r				R�l
 * @param	g				G�l
 * @param	b				B�l
 * @param	a				A�l
 */
/************************************************************************************************/
void KsLine3DBatchDX11::setColor( KsReal r, KsReal g, KsReal b, KsReal a )
{
	m_lineColor.set( r, g, b, a ); 
}

/************************************************************************************************/
/*
 * ���C���`�悷��
 * @param		start		X���W
 * @param		end			Y���W
 */
/************************************************************************************************/
void KsLine3DBatchDX11::draw( const KsVector3d& start, const KsVector3d& end )
{
	KS_VERTEX_LINE3D*	pVertex = &m_pLineVertices[ m_lineIndex ];

	pVertex->x = start.x;
	pVertex->y = start.y;
	pVertex->z = start.z;

	pVertex->r = m_lineColor.getRed();
	pVertex->g = m_lineColor.getGreen();
	pVertex->b = m_lineColor.getBlue();
	pVertex->a = m_lineColor.getAlpha();

	++m_lineIndex;

	pVertex = &m_pLineVertices[ m_lineIndex ];

	pVertex->x = end.x;
	pVertex->y = end.y;
	pVertex->z = end.z;

	pVertex->r = m_lineColor.getRed();
	pVertex->g = m_lineColor.getGreen();
	pVertex->b = m_lineColor.getBlue();
	pVertex->a = m_lineColor.getAlpha();

	++m_lineIndex;

	++m_lineCount;
}

/************************************************************************************************/
/*
 * �o�b�t�@���ꊇ�`�悷��
 * @param	pRenderContext	�`��R���e�L�X�g
 */
/************************************************************************************************/
void KsLine3DBatchDX11::flush( KsRenderContext* pRenderContext )
{
	if( m_lineCount )
	{
		pRenderContext->write( m_pLineVB, m_pLineVertices, m_lineStride * m_lineIndex, 0 );
		pRenderContext->setInputLayout( m_pLineIL );
		pRenderContext->setVertexBuffers( 0, 1, m_pLineVB, &m_lineStride, &m_lineOffset );
		pRenderContext->setPrimitiveTopology( KS_PRIMITIVE_TOPOLOGY_LINELIST );
		pRenderContext->setVertexShader( m_pLineVS );
		pRenderContext->setPixelShader( m_pLinePS );
		pRenderContext->draw( m_lineIndex, 0 );

		m_lineIndex = 0;
		m_lineCount = 0;
	}
}

