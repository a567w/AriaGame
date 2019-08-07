/************************************************************************************************/
/** 
 * @file		KsGraphicsDX11.cpp
 * @brief		描画コンテキスト(DX11用)
 * @author		Tsukasa Kato
 * @date		2004/08/17
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>												*/
/*==============================================================================================*/
#include "KsDevDX11/KsDevDX11PreCompile.h"
#include "KsDevDX11/device/KsGraphicsDX11.h"

/*==============================================================================================*/
/*									  << 宣言 >>													*/
/*==============================================================================================*/


/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsGraphicsDX11::KsGraphicsDX11( KsRenderSystemDX11* pRenderSystem )
	: m_pRenderSystem( pRenderSystem )
	, m_pLine3DBatch( 0 )
	, m_pRectBatch( 0 )
	, m_pSpriteBatch( 0 )
{
	m_cbGraphics.BaseColor      = KsVector4d::ONE;
	m_cbGraphics.BasePosScale.x = 2.0f/1280.0f;
	m_cbGraphics.BasePosScale.y = 2.0f/720.0f;

	KsHardwareBufferManager*	pHardwareBufferManager = KsHardwareBufferManagerDX11::getInstancePtr();
	m_pGraphicsCB = pHardwareBufferManager->createConstantBuffer( 4 * 16, 0 );

	KS_BLEND_DESC	desc = KsBlendState::SPRITE;
	m_pBlendState = m_pRenderSystem->createBlendState( &desc );
	//
	createLineBuffer( 1024 );
	createRectBuffer( 1024 );
	createSpriteBuffer( 256, 1024 );
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsGraphicsDX11::~KsGraphicsDX11()
{
	destroyLineBuffer();
	destroyRectBuffer();
	destroySpriteBuffer();
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsGraphicsDX11::createLineBuffer( KsUInt32 lineMax )
{
	m_pLine3DBatch = ksNew KsLine3DBatchDX11( lineMax );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsGraphicsDX11::destroyLineBuffer()
{
	ksDELETE( m_pLine3DBatch );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsGraphicsDX11::setColorLine( const KsColorReal& lineColor )
{
	m_pLine3DBatch->setColor( lineColor );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsGraphicsDX11::setColorLine( KsReal r, KsReal g, KsReal b, KsReal a )
{
	m_pLine3DBatch->setColor( r, g, b, a );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsGraphicsDX11::drawLine( const KsVector3d& start, const KsVector3d& end )
{
#if 0
// ビュー変換
Vector4 viewPosition = Vector4.Transform(new Vector4(X, Y, Z, 1.0f), viewMatrix);

// プロジェクション変換
Vector4 projectionPosition = Vector4.Transform(viewPosition, projectionMatrix);

// 同次座標を考慮
projectionPosition /= projectionPosition.W;

// スクリーン変換
Vector2 screenPosition = new Vector2(
 (1.0f + projectionPosition.X) / 2.0f * this.GraphicsDevice.Viewport.Width,
 (1.0f - projectionPosition.Y) / 2.0f * this.GraphicsDevice.Viewport.Height);
#endif
	m_pLine3DBatch->draw( start, end );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsGraphicsDX11::flushLine( KsRenderContext* pRenderContext )
{
	m_pLine3DBatch->flush( pRenderContext );
}

/************************************************************************************************/
/*
 * Rect バッファ生成する
 * @param	count	Rect数
 */
/************************************************************************************************/
void KsGraphicsDX11::createRectBuffer( KsUInt32 count )
{
	m_pRectBatch = ksNew KsRectBatchDX11( count );
}

/************************************************************************************************/
/*
 * Rect バッファを破棄する
 */
/************************************************************************************************/
void KsGraphicsDX11::destroyRectBuffer()
{
	ksDELETE( m_pRectBatch );
}

/************************************************************************************************/
/*
 * カラーをセットする
 * @param	rectColor	カラー値
 */
/************************************************************************************************/
void KsGraphicsDX11::setColorRect( const KsColorReal& rectColor )
{
	m_pRectBatch->setColor( rectColor );
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
void KsGraphicsDX11::setColorRect( KsReal r, KsReal g, KsReal b, KsReal a )
{
	m_pRectBatch->setColor( r, g, b, a );
}

/************************************************************************************************/
/*
 * カラーをセットする
 * @param	index			インデックス
 * @param	rectColor		カラー値
 */
/************************************************************************************************/
void KsGraphicsDX11::setColorRect( KsInt32 index, const KsColorReal& rectColor )
{
	m_pRectBatch->setColor( index, rectColor );
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
void KsGraphicsDX11::setColorRect( KsInt32 index, KsReal r, KsReal g, KsReal b, KsReal a )
{
	m_pRectBatch->setColor( index, r, g, b, a );
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
void KsGraphicsDX11::drawRect( KsInt32 left, KsInt32 top, KsInt32 width, KsInt32 height )
{
	m_pRectBatch->draw( left, top, width, height );
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
void KsGraphicsDX11::drawRect( KsReal left, KsReal top, KsReal width, KsReal height )
{
	m_pRectBatch->draw( left, top, width, height );
}

/************************************************************************************************/
/*
 * バッファを一括描画する
 * @param	pRenderContext	描画コンテキスト
 */
/************************************************************************************************/
void KsGraphicsDX11::flushRect( KsRenderContext* pRenderContext )
{
	m_pRectBatch->flush( pRenderContext );
}

/************************************************************************************************/
/*
 * バッファを生成する
 * @param	count			最大プリミティブ数
 */
/************************************************************************************************/
void KsGraphicsDX11::createSpriteBuffer( KsUInt32 workMax, KsUInt32 spriteMax )
{
	m_pSpriteBatch = ksNew KsSpriteBatchDX11( workMax, spriteMax );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsGraphicsDX11::destroySpriteBuffer()
{
	ksDELETE( m_pSpriteBatch );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsGraphicsDX11::setColorSprite( const KsColorReal& spriteColor )
{
	m_pSpriteBatch->setColor( spriteColor );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsGraphicsDX11::setColorSprite( KsReal r, KsReal g, KsReal b, KsReal a )
{
	m_pSpriteBatch->setColor( r, g, b, a );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsGraphicsDX11::setColorSprite( KsInt32 index, const KsColorReal& spriteColor )
{
	m_pSpriteBatch->setColor( index, spriteColor );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsGraphicsDX11::setColorSprite( KsInt32 index, KsReal r, KsReal g, KsReal b, KsReal a )
{
	m_pSpriteBatch->setColor( index, r, g, b, a );
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
void KsGraphicsDX11::drawSprite( const KsTexture* pTexture, KsInt32 left, KsInt32 top, KsInt32 width, KsInt32 height, KsReal tx, KsReal ty, KsReal tw, KsReal th )
{
	m_pSpriteBatch->draw( pTexture, left, top, width, height, tx, ty, tw, th );
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
void KsGraphicsDX11::drawSprite( const KsTexture* pTexture, KsReal left, KsReal top, KsReal width, KsReal height, KsReal tx, KsReal ty, KsReal tw, KsReal th )
{
	m_pSpriteBatch->draw( pTexture, left, top, width, height, tx, ty, tw, th );
}

/************************************************************************************************/
/*
 * Sprite 描画する
 * @param		pTexture	テクスチャ
 * @param		pVertices	スプライト用頂点データ
 */
/************************************************************************************************/
void KsGraphicsDX11::drawSprite( const KsTexture* pTexture, const KS_VERTEX_SPRITE* pVertices )
{
	m_pSpriteBatch->draw( pTexture, pVertices );
}

/************************************************************************************************/
/*
 * バッファを一括描画する
 * @param	pRenderContext	描画コンテキスト
 */
/************************************************************************************************/
void KsGraphicsDX11::flushSprite( KsRenderContext* pRenderContext )
{
	m_pSpriteBatch->flush( pRenderContext );
}

/************************************************************************************************/
/*
 * バッファを一括描画する
 * @param	pRenderContext	描画コンテキスト
 */
/************************************************************************************************/
void KsGraphicsDX11::flush( KsRenderContext* pRenderContext )
{
	pRenderContext->setBlendState( m_pBlendState, 0, 0xFFFFFFFF );
	pRenderContext->updateConstantBuffers( m_pGraphicsCB, &m_cbGraphics );
	pRenderContext->setVertexConstantBuffers( 0, 1, m_pGraphicsCB );
	pRenderContext->setPixelConstantBuffers( 0, 1, m_pGraphicsCB );

	flushLine( pRenderContext );
	flushRect( pRenderContext );
	flushSprite( pRenderContext );
}


