/************************************************************************************************/
/** 
 * @file		KsSpriteBatchDX11.cpp
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
#include "KsDevDX11/device/KsSpriteBatchDX11.h"


/*==============================================================================================*/
/*									  << 宣言 >>													*/
/*==============================================================================================*/

namespace
{
	KS_INPUT_ELEMENT_DESC VS_SPRITE_LAYOUT[] =
	{
		{ "POSITION", 0, KS_GI_FORMAT_R32G32B32_FLOAT,    0,  0, KS_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",	  0, KS_GI_FORMAT_R32G32B32A32_FLOAT, 0, 12, KS_INPUT_PER_VERTEX_DATA, 0 },	// COLOR
		{ "TEXCOORD", 0, KS_GI_FORMAT_R32G32_FLOAT,       0, 28, KS_INPUT_PER_VERTEX_DATA, 0 },
	};
}

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsSpriteWork::KsSpriteWork()
	: m_spriteCount( 0 )
	, m_spriteMax( 0 )
	, m_spriteIndex( 0 )
	, m_pSpriteVertices( 0 )
	, m_pSpriteVB( 0 )
	, m_pTexture( 0 )
{
}

/************************************************************************************************/
/*
 * コンストラクタ
 * @param	count			最大プリミティブ数
 */
/************************************************************************************************/
KsSpriteWork::KsSpriteWork( KsUInt32 spriteMax )
	: m_spriteCount( 0 )
	, m_spriteMax( 0 )
	, m_spriteIndex( 0 )
	, m_pSpriteVertices( 0 )
	, m_pSpriteVB( 0 )
	, m_pTexture( 0 )
{
	create( spriteMax );
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsSpriteWork::~KsSpriteWork()
{
	destroy();
}

/************************************************************************************************/
/*
 * バッファを生成する
 * @param	count			最大プリミティブ数
 */
/************************************************************************************************/
void KsSpriteWork::create( KsUInt32 spriteMax )
{
	KsHardwareBufferManager*	pHardwareBufferManager = KsHardwareBufferManagerDX11::getInstancePtr();

	m_spriteMax       = spriteMax;	
	m_pSpriteVB       = pHardwareBufferManager->createVertexBuffer( sizeof(KS_VERTEX_SPRITE), spriteMax * 4, ksSPRITE_FVF, ksCPU_ACCESS_WRITE );
	m_pSpriteVertices = ksNew KS_VERTEX_SPRITE[ spriteMax * 4 ];
}

/************************************************************************************************/
/*
 * バッファを破棄する
 */
/************************************************************************************************/
void KsSpriteWork::destroy()
{
	ksDELETEARRAY( m_pSpriteVB );
	ksDELETEARRAY( m_pSpriteVertices );
}




/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsSpriteBatchDX11::KsSpriteBatchDX11( KsUInt32 workMax, KsUInt32 spriteMax )
	: m_pSpriteWork( 0 )
	, m_spriteWorkMax( 0 )
	, m_spriteStride( 0 )
	, m_spriteOffset( 0 )
	, m_pSpriteVS( 0 )
	, m_pSpritePS( 0 )
	, m_pSpriteIL( 0 )
	, m_pSpriteIB( 0 )
	, m_spriteDepth( 1.0f )
	, m_textureCount( 0 )
	, m_textureMax( 0 )
{
	create( workMax, spriteMax );
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsSpriteBatchDX11::~KsSpriteBatchDX11()
{
	destroy();
}


/************************************************************************************************/
/*
 * バッファを生成する
 * @param	workMax			ワーク数
 * @param	spriteMax		最大プリミティブ数
 */
/************************************************************************************************/
void KsSpriteBatchDX11::create( KsUInt32 workMax, KsUInt32 spriteMax )
{
	KsRenderSystem*				pRenderSystem          = KsRenderSystemDX11::getInstancePtr();
	KsShaderManager*			pShaderManager         = KsShaderManagerDX11::getInstancePtr();
	KsInputLayoutManager*		pInputLayoutManager    = KsInputLayoutManagerDX11::getInstancePtr();
	KsHardwareBufferManager*	pHardwareBufferManager = KsHardwareBufferManagerDX11::getInstancePtr();

	m_spriteStride  = sizeof( KS_VERTEX_SPRITE );
	m_spriteOffset  = 0;
	m_spriteWorkMax = workMax;
	m_textureCount  = 0;

	for( KsInt32 i=0; i<4; i++ )
	{
		m_spriteColor[ i ] = KsColorReal::WHITE;
	}

	const KsUInt32	numIndex = spriteMax * 6;
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

	m_pSpriteVS = (KsVertexShader*)pShaderManager->createFromFile( "sprite.fx", "VS_Sprite", ksSHADE_MODEL_5_0, ksVERTEX_SHADER );
	m_pSpritePS = (KsPixelShader*) pShaderManager->createFromFile( "sprite.fx", "PS_Sprite", ksSHADE_MODEL_5_0, ksPIXEL_SHADER  );
	m_pSpriteIL = pInputLayoutManager->createInputLayout( VS_SPRITE_LAYOUT, ksARRAYSIZE( VS_SPRITE_LAYOUT ), (KsVertexShader*)m_pSpriteVS );
	m_pSpriteIB = pHardwareBufferManager->createIndexBuffer( pIndices, sizeof(KsUInt16)* numIndex, numIndex, ksFMT_INDEX16, 0 );

	// ワークを生成する
	m_pSpriteWork = ksNew KsSpriteWork[ workMax ];

	for( KsUInt32 i=0; i<workMax; i++ )
	{
		m_pSpriteWork[ i ].create( spriteMax );
	}

	m_textureDict.create( workMax );

	m_spriteDepth = 1.0f;

	ksDELETEARRAY( pIndices );
}

/************************************************************************************************/
/*
 * バッファを破棄する
 */
/************************************************************************************************/
void KsSpriteBatchDX11::destroy()
{
	ksDELETEARRAY( m_pSpriteWork );
	ksDELETEARRAY( m_pSpriteVS );
	ksDELETEARRAY( m_pSpritePS );
	ksDELETEARRAY( m_pSpriteIL );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsSpriteBatchDX11::setColor( const KsColorReal& spriteColor )
{
	for( KsInt32 i=0; i<4; i++ )
	{
		m_spriteColor[ i ].set( spriteColor );
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsSpriteBatchDX11::setColor( KsReal r, KsReal g, KsReal b, KsReal a )
{
	for( KsInt32 i=0; i<4; i++ )
	{
		m_spriteColor[ i ].set( r, g, b, a ); 
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsSpriteBatchDX11::setColor( KsInt32 index, const KsColorReal& spriteColor )
{
	m_spriteColor[ index ].set( spriteColor );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsSpriteBatchDX11::setColor( KsInt32 index, KsReal r, KsReal g, KsReal b, KsReal a )
{
	m_spriteColor[ index ].set( r, g, b, a ); 
}

/************************************************************************************************/
/*
 * Sprite 描画する
 * @param		pTexture	テクスチャ
 * @param		left		X座標
 * @param		top			Y座標
 * @param		width		幅
 * @param		height		高さ
 * @param		tx			テクスチャ X座標
 * @param		ty			テクスチャ Y座標
 * @param		tw			テクスチャ 幅
 * @param		th			テクスチャ 高さ
 */
/************************************************************************************************/
void KsSpriteBatchDX11::draw( const KsTexture* pTexture, KsInt32 left, KsInt32 top, KsInt32 width, KsInt32 height, KsReal tx, KsReal ty, KsReal tw, KsReal th )
{
	draw( pTexture, (KsReal)left, (KsReal)top, (KsReal)width, (KsReal)height, tx, ty, tw, th );
}

/************************************************************************************************/
/*
 * Sprite 描画する
 * @param		pTexture	テクスチャ
 * @param		left		X座標
 * @param		top			Y座標
 * @param		width		幅
 * @param		height		高さ
 * @param		tx			テクスチャ X座標
 * @param		ty			テクスチャ Y座標
 * @param		tw			テクスチャ 幅
 * @param		th			テクスチャ 高さ
 */
/************************************************************************************************/
void KsSpriteBatchDX11::draw( const KsTexture* pTexture, KsReal left, KsReal top, KsReal width, KsReal height, KsReal tx, KsReal ty, KsReal tw, KsReal th )
{
	KS_VERTEX_SPRITE	value[] = 
	{
		{ left,           (top + height), m_spriteDepth, m_spriteColor[ 2 ].getRed(), m_spriteColor[ 2 ].getGreen(), m_spriteColor[ 2 ].getBlue(), m_spriteColor[ 2 ].getAlpha(), tx, th },
		{ left,           top,            m_spriteDepth, m_spriteColor[ 0 ].getRed(), m_spriteColor[ 0 ].getGreen(), m_spriteColor[ 0 ].getBlue(), m_spriteColor[ 0 ].getAlpha(), tx, ty },
		{ (left + width), top,            m_spriteDepth, m_spriteColor[ 1 ].getRed(), m_spriteColor[ 1 ].getGreen(), m_spriteColor[ 1 ].getBlue(), m_spriteColor[ 1 ].getAlpha(), tw, ty },
		{ (left + width), (top + height), m_spriteDepth, m_spriteColor[ 3 ].getRed(), m_spriteColor[ 3 ].getGreen(), m_spriteColor[ 3 ].getBlue(), m_spriteColor[ 3 ].getAlpha(), tw, th },
		{ left,           (top + height), m_spriteDepth, m_spriteColor[ 2 ].getRed(), m_spriteColor[ 2 ].getGreen(), m_spriteColor[ 2 ].getBlue(), m_spriteColor[ 2 ].getAlpha(), tx, th },
		{ (left + width), top,            m_spriteDepth, m_spriteColor[ 1 ].getRed(), m_spriteColor[ 1 ].getGreen(), m_spriteColor[ 1 ].getBlue(), m_spriteColor[ 1 ].getAlpha(), tw, ty }
	};

	KsSpriteWork*		pSpriteWork = getSpriteWork( const_cast<KsTexture*>(pTexture)->getName(), pTexture );

	KS_VERTEX_SPRITE*	pVertex = &pSpriteWork->m_pSpriteVertices[ pSpriteWork->m_spriteIndex ];

	KsMemCopy( pVertex, value, sizeof(KS_VERTEX_SPRITE)*6 );

	pSpriteWork->m_spriteIndex += 6;

	++pSpriteWork->m_spriteCount;
}

/************************************************************************************************/
/*
 * Sprite 描画する
 * @param		pTexture	テクスチャ
 * @param		pVertices	スプライト用頂点データ
 */
/************************************************************************************************/
void KsSpriteBatchDX11::draw( const KsTexture* pTexture, const KS_VERTEX_SPRITE* pVertices )
{
	KsSpriteWork*		pSpriteWork = getSpriteWork( const_cast<KsTexture*>(pTexture)->getName(), pTexture );

	KS_VERTEX_SPRITE*	pVertex = &pSpriteWork->m_pSpriteVertices[ pSpriteWork->m_spriteIndex ];

	KsMemCopy( pVertex, pVertices, sizeof(KS_VERTEX_SPRITE)*4 );

	pSpriteWork->m_spriteIndex += 4;

	++pSpriteWork->m_spriteCount;
}

/************************************************************************************************/
/*
 * バッファを一括描画する
 * @param	pRenderContext	描画コンテキスト
 */
/************************************************************************************************/
void KsSpriteBatchDX11::flush( KsRenderContext* pRenderContext )
{
	if( m_textureCount )
	{
		pRenderContext->setVertexShader( m_pSpriteVS );
		pRenderContext->setPixelShader( m_pSpritePS );
		pRenderContext->setInputLayout( m_pSpriteIL );
		pRenderContext->setPrimitiveTopology( KS_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

		for( KsUInt32 i=0; i<m_textureCount; i++ )
		{
			KsSpriteWork*	pSpriteWork = &m_pSpriteWork[ i ];

			pRenderContext->write( pSpriteWork->m_pSpriteVB, pSpriteWork->m_pSpriteVertices, m_spriteStride * pSpriteWork->m_spriteIndex, 0 );
			pRenderContext->setVertexBuffers( 0, 1, pSpriteWork->m_pSpriteVB, &m_spriteStride, &m_spriteOffset );		
			pRenderContext->setPixelTexture( 0, 1, pSpriteWork->m_pTexture );
			pRenderContext->draw( pSpriteWork->m_spriteCount * 6, 0 );
		
			pSpriteWork->m_spriteIndex = 0;
			pSpriteWork->m_spriteCount = 0;
		}
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsSpriteWork* KsSpriteBatchDX11::getSpriteWork( const KsChar* name, const KsTexture* pTexture )
{
	KsHashTable<KsSpriteWork*>::KsHashNodeType* pNode = m_textureDict.find( name );

	if( NULL == pNode )
	{
		KsSpriteWork*	pSpriteWork = &m_pSpriteWork[ m_textureCount ];

		pSpriteWork->m_pTexture = pTexture;
		m_textureDict.add( name, pSpriteWork );

		++m_textureCount;

		return pSpriteWork;
	}


	return pNode->m_pData;
}

