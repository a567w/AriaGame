/************************************************************************************************/
/** 
 * @file		KsRectBatchDX11DX11.cpp
 * @brief		描画コンテキスト(DX11用)
 * @author		Tsukasa Kato
 * @date		2004/08/17
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>											*/
/*==============================================================================================*/
#include "KsDevDX11/KsDevDX11PreCompile.h"
#include "KsDevDX11/device/KsRectBatchDX11.h"


/*==============================================================================================*/
/*									  << 宣言 >>													*/
/*==============================================================================================*/

namespace
{
	KS_INPUT_ELEMENT_DESC VS_RECT_LAYOUT[] =
	{
		{ "POSITION", 0, KS_GI_FORMAT_R32G32B32_FLOAT,    0,  0, KS_INPUT_PER_VERTEX_DATA, 0 },	// POSITION
		{ "COLOR",	  0, KS_GI_FORMAT_R32G32B32A32_FLOAT, 0, 12, KS_INPUT_PER_VERTEX_DATA, 0 },	// COLOR
	};
}

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsRectBatchDX11::KsRectBatchDX11( KsUInt32 count )
	: m_rectCount( 0 )
	, m_rectMax( 0 )
	, m_rectIndex( 0 )
	, m_rectStride( 0 )
	, m_rectOffset( 0 )
	, m_rectDepth( 0 )
	, m_pRectVertices( 0 )
	, m_pRectVS( 0 )
	, m_pRectPS( 0 )
	, m_pRectIL( 0 )
	, m_pRectVB( 0 )
	, m_pRectIB( 0 )
{
	create( count );
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsRectBatchDX11::~KsRectBatchDX11()
{
	destroy();
}

/************************************************************************************************/
/*
 * バッファを生成する
 * @param	count			最大プリミティブ数
 */
/************************************************************************************************/
void KsRectBatchDX11::create( KsUInt32 count )
{
	KsShaderManager*			pShaderManager         = KsShaderManagerDX11::getInstancePtr();
	KsInputLayoutManager*		pInputLayoutManager    = KsInputLayoutManagerDX11::getInstancePtr();
	KsHardwareBufferManager*	pHardwareBufferManager = KsHardwareBufferManagerDX11::getInstancePtr();

	m_rectStride = sizeof( KS_VERTEX_RECT );
	m_rectOffset = 0;
	m_rectMax    = count;
	m_rectDepth  = 1.0f;

	for( KsInt32 i=0; i<4; i++ )
	{
		m_rectColor[ i ] = KsColorReal::WHITE;
	}

	const KsUInt32	numIndex = count * 6;
		  KsUInt16* pIndices = ksNew KsUInt16[ numIndex ];

	for( KsUInt32 i=0; i<numIndex; i+=6 )
	{
		pIndices[ i + 0 ] = i + 0;
		pIndices[ i + 1 ] = i + 1;
		pIndices[ i + 2 ] = i + 2;
		pIndices[ i + 3 ] = i + 1;
		pIndices[ i + 4 ] = i + 3;
		pIndices[ i + 5 ] = i + 2;
	}

	m_pRectVS = (KsVertexShader*)pShaderManager->createFromFile( "rect.fx", "VS_Rect", ksSHADE_MODEL_5_0, ksVERTEX_SHADER );
	m_pRectPS = (KsPixelShader*) pShaderManager->createFromFile( "rect.fx", "PS_Rect", ksSHADE_MODEL_5_0, ksPIXEL_SHADER  );
	m_pRectVB = pHardwareBufferManager->createVertexBuffer( sizeof(KS_VERTEX_RECT), count * 4, ksRECT_FVF, ksCPU_ACCESS_WRITE );
	m_pRectIB = pHardwareBufferManager->createIndexBuffer( pIndices, sizeof(KsUInt16)* numIndex, numIndex, ksFMT_INDEX16, 0 );
	m_pRectIL = pInputLayoutManager->createInputLayout( VS_RECT_LAYOUT, ksARRAYSIZE( VS_RECT_LAYOUT ), (KsVertexShader*)m_pRectVS );
	
	m_pRectVertices = ksNew KS_VERTEX_RECT[ count * 4 ];

	ksDELETEARRAY( pIndices );
}

/************************************************************************************************/
/*
 * バッファを破棄する
 */
/************************************************************************************************/
void KsRectBatchDX11::destroy()
{
	ksDELETEARRAY( m_pRectVS );
	ksDELETEARRAY( m_pRectPS );
	ksDELETEARRAY( m_pRectIL );
	ksDELETEARRAY( m_pRectVB );
	ksDELETEARRAY( m_pRectIB );
	ksDELETEARRAY( m_pRectVertices );
}

/************************************************************************************************/
/*
 * カラーをセットする
 * @param	rectColor	カラー値
 */
/************************************************************************************************/
void KsRectBatchDX11::setColor( const KsColorReal& rectColor )
{
	for( KsInt32 i=0; i<4; i++ )
	{
		m_rectColor[ i ].set( rectColor );
	}
}

/************************************************************************************************/
/*
 * カラーをセットする
 * @param	r				R値
 * @param	g				G値
 * @param	b				B値
 * @param	a				A値
 */
/************************************************************************************************/
void KsRectBatchDX11::setColor( KsReal r, KsReal g, KsReal b, KsReal a )
{
	for( KsInt32 i=0; i<4; i++ )
	{
		m_rectColor[ i ].set( r, g, b, a ); 
	}
}

/************************************************************************************************/
/*
 * カラーをセットする
 * @param	index			インデックス
 * @param	rectColor		カラー値
 */
/************************************************************************************************/
void KsRectBatchDX11::setColor( KsInt32 index, const KsColorReal& rectColor )
{
	m_rectColor[ index ].set( rectColor );
}

/************************************************************************************************/
/*
 * カラーをセットする
 * @param	index			インデックス
 * @param	r				R値
 * @param	g				G値
 * @param	b				B値
 * @param	a				A値
 */
/************************************************************************************************/
void KsRectBatchDX11::setColor( KsInt32 index, KsReal r, KsReal g, KsReal b, KsReal a )
{
	m_rectColor[ index ].set( r, g, b, a ); 
}

/************************************************************************************************/
/*
 * RECT 描画する
 * @param		left		X座標
 * @param		top			Y座標
 * @param		width		幅
 * @param		height		高さ
 */
/************************************************************************************************/
void KsRectBatchDX11::draw( KsInt32 left, KsInt32 top, KsInt32 width, KsInt32 height )
{
	draw( (KsReal)left, (KsReal)top, (KsReal)width, (KsReal)height );
}

/************************************************************************************************/
/*
 * RECT 描画する
 * @param		left		X座標
 * @param		top			Y座標
 * @param		width		幅
 * @param		height		高さ
 */
/************************************************************************************************/
void KsRectBatchDX11::draw( KsReal left, KsReal top, KsReal width, KsReal height )
{
	KS_VERTEX_RECT	value[] = 
	{
		{ left,           top,            m_rectDepth, m_rectColor[ 0 ].getRed(), m_rectColor[ 0 ].getGreen(), m_rectColor[ 0 ].getBlue(), m_rectColor[ 0 ].getAlpha() },
		{ (left + width), top,            m_rectDepth, m_rectColor[ 1 ].getRed(), m_rectColor[ 1 ].getGreen(), m_rectColor[ 1 ].getBlue(), m_rectColor[ 1 ].getAlpha() },
		{ left,           (top + height), m_rectDepth, m_rectColor[ 2 ].getRed(), m_rectColor[ 2 ].getGreen(), m_rectColor[ 2 ].getBlue(), m_rectColor[ 2 ].getAlpha() },
		{ (left + width), (top + height), m_rectDepth, m_rectColor[ 3 ].getRed(), m_rectColor[ 3 ].getGreen(), m_rectColor[ 3 ].getBlue(), m_rectColor[ 3 ].getAlpha() }
	};

	KS_VERTEX_RECT*	pVertex = &m_pRectVertices[ m_rectIndex ];

	KsMemCopy( pVertex, value, sizeof(KS_VERTEX_RECT)*4 );

	m_rectIndex += 4;

	++m_rectCount;
}

/************************************************************************************************/
/*
 * バッファを一括描画する
 * @param	pRenderContext	描画コンテキスト
 */
/************************************************************************************************/
void KsRectBatchDX11::flush( KsRenderContext* pRenderContext )
{
	if( m_rectCount )
	{
		pRenderContext->write( m_pRectVB, m_pRectVertices, m_rectStride * m_rectIndex, 0 );
		pRenderContext->setInputLayout( m_pRectIL );
		pRenderContext->setVertexBuffers( 0, 1, m_pRectVB, &m_rectStride, &m_rectOffset );
		pRenderContext->setIndexBuffer( m_pRectIB, ksFMT_INDEX16, 0 );
		pRenderContext->setPrimitiveTopology( KS_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
		pRenderContext->setVertexShader( m_pRectVS );
		pRenderContext->setPixelShader( m_pRectPS );
		pRenderContext->drawIndexed( m_rectCount * 6, 0, 0 );

		m_rectIndex = 0;
		m_rectCount = 0;
	}
}

