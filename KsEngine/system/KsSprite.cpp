/*************************************************************************************************/
/**
 * @file	KsSprite.cpp
 * @brief	スプライトクラス
 * @author	Tsukasa Kato
 * @date	2003/11/30
 * @version	1.0.0
 */
/*************************************************************************************************/

/*===============================================================================================*/
/*                                 << インクルード >>                                            */
/*===============================================================================================*/
#include "KsSprite.h"
#include "KsPrimitive.h"
#include "KsGameSystem.h"

/*===============================================================================================*/
/*                                     << 定義 >>                                                */
/*===============================================================================================*/

/*===============================================================================================*/
/*                                     << 宣言 >>                                                */
/*===============================================================================================*/
KsSprite   KsSpriteWorkArea::m_spriteWork[ ksSPRITE_WORK_MAX ];
KsSprite*  KsSpriteWorkArea::m_spriteStack[ ksSPRITE_WORK_MAX ];
KsInt32    KsSpriteWorkArea::m_stackCount = 0;

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsSprite::KsSprite()
{
	m_id           = 0;
	m_flags        = ksTASK_FALGS_INITIALIZE;
	m_type         = ksTASK_TYPE_BASE;
	m_pParent      = 0;
	m_pPrevBrother = 0;
	m_pNextBrother = 0;
	m_pChild       = 0;
	m_pPrev        = 0;
	m_pNext        = 0;
	m_pManager     = 0;
	m_scaleX       = 0.0f;
	m_scaleY       = 0.0f;
	m_spriteFlags  = 0;
	m_useWork      = 0;
	m_clipX        = 0;
	m_clipY        = 0;
	m_clipW        = 0;
	m_clipH        = 0;
	m_pTexture     = NULL;
	m_pVertex      = NULL;
	m_priority.i   = ksSPRITE_DEFAULT_PRIORITY;
	m_order        = ksSPRITE_TASK_ORDER;
}
/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsSprite::~KsSprite()
{
	destroyVertexBuffer();
}

/************************************************************************************************/
/*
 * スプライト生成
 * @param		x				X座標
 * @param		y				Y座標
 * @param		w				幅
 * @param		h				高さ
 * @param		tx				テクスチャのX座標
 * @param		ty				テクスチャのY座標
 * @param		tw				テクスチャの幅
 * @param		th				テクスチャの高さ
 * @param		scaleX			Xのスケール値
 * @param		scaleY			Yのスケール値
 * @param		rotate			回転量
 * @param		color			カラー
 * @param		pTexture		使用テクスチャのポインタ(使用しないときは、NULLを設定)
 */
/************************************************************************************************/
void KsSprite::create(	KsReal  x, KsReal  y, KsReal  w, KsReal h, 
					    KsReal tx, KsReal ty, KsReal tw, KsReal th,
						KsUInt32 color, KsTexture* pTexture )
{
	create( x, y, w, h, tx, ty, tw, th, 1.0f, 1.0f, 0.0f, color, pTexture );
}
/************************************************************************************************/
/*
 * スプライト生成
 * @param		x				X座標
 * @param		y				Y座標
 * @param		w				幅
 * @param		h				高さ
 * @param		tx				テクスチャのX座標
 * @param		ty				テクスチャのY座標
 * @param		tw				テクスチャの幅
 * @param		th				テクスチャの高さ
 * @param		color			カラー
 * @param		pTexture		使用テクスチャのポインタ(使用しないときは、NULLを設定)
 */
/************************************************************************************************/
void KsSprite::create(	KsReal  x, KsReal  y, KsReal  w, KsReal h, 
					    KsReal tx, KsReal ty, KsReal tw, KsReal th,
						KsReal scaleX, KsReal scaleY, KsReal rotate, KsUInt32 color, KsTexture* pTexture )
{
	KsReal		cx = ((KsReal)w) * 0.5f;
	KsReal		cy = ((KsReal)h) * 0.5f;

	m_x[ 0 ] = -cx;
	m_y[ 0 ] = -cy;

	m_x[ 1 ] =  cx;
	m_y[ 1 ] = -cy;

	m_x[ 2 ] = -cx;
	m_y[ 2 ] =  cy;

	m_x[ 3 ] =  cx;
	m_y[ 3 ] =  cy;

	m_centerX = (KsReal)x + cx;
	m_centerY = (KsReal)y + cy;

	m_rotate = rotate;
	m_scaleX = scaleX;
	m_scaleY = scaleY;

	createVertexBuffer();

	setUVWH( tx, ty, tw, th );
	setColorAll( color );

	m_pTexture = pTexture;

	reset();

	/*------------------------------------------*/
	/*	|x'|   | cosθ - sinθ	| x |	| Tx |	*/
	/*	|  | = |				|	| + |	 |	*/
	/*	|y'|   | sinθ + cosθ	| y |	| Ty |	*/
	/*------------------------------------------*/
}

/************************************************************************************************/
/*
 * スプライト生成
 * @param		x				スプライト表示のX座標(スプライトの中心を基点とする)
 * @param		y				スプライト表示のY座標(スプライトの中心を基点とする)
 * @param		tx				テクスチャのX座標
 * @param		ty				テクスチャのY座標
 * @param		w				幅
 * @param		h				高さ
 * @param		color			カラー
 * @param		pTexture		使用テクスチャのポインタ(使用しないときは、NULLを設定)
 */
/************************************************************************************************/
void KsSprite::create(	KsReal	x,	KsReal	y,
						KsReal	tx,	KsReal	ty,
						KsReal	w,	KsReal	h,
						KsUInt32	color,	KsTexture* pTexture )
{
}

/************************************************************************************************/
/*
 * スプライトフラグをセットする
 * @param		flags			各種フラグ
 */
/************************************************************************************************/
void KsSprite::setSpriteFlags( KsUInt32 flags )
{
	m_spriteFlags = flags;
}

/************************************************************************************************/
/*
 * UV座標をセットします
 * @param		tx				テクスチャのX座標
 * @param		ty				テクスチャのY座標
 * @param		tw				テクスチャの幅
 * @param		th				テクスチャの高さ
 */
/************************************************************************************************/
void KsSprite::setUVWH( KsReal tx, KsReal ty, KsReal tw, KsReal th )
{
	KS_SPRITE_PRIM* v = (KS_SPRITE_PRIM*)m_pVertex->lock( 0, 4, ksLOCK_DISCARD );

	v[ 0 ].u = tx;
	v[ 1 ].u = tx + tw;
	v[ 2 ].u = tx;
	v[ 3 ].u = tx + tw;

	v[ 0 ].v = ty;
	v[ 1 ].v = ty;
	v[ 2 ].v = ty + th;
	v[ 3 ].v = ty + th;

	m_pVertex->unlock();
}

/************************************************************************************************/
/*
 * 指定頂点の頂点カラーをセットする
 * @param		index			インデックス
 * @param		color			カラー
 */
/************************************************************************************************/
void KsSprite::setColor( KsUInt32 index, KsUInt32 color )
{
	KS_SPRITE_PRIM* v = (KS_SPRITE_PRIM*)m_pVertex->lock( 0, 4, ksLOCK_DISCARD );

	v[ index ].color = color;

	m_pVertex->unlock();
}

/************************************************************************************************/
/*
 * すべての頂点カラーをセットする
 * @param		color			カラー
 */
/************************************************************************************************/
void KsSprite::setColorAll( KsUInt32 color )
{
	KS_SPRITE_PRIM* v = (KS_SPRITE_PRIM*)m_pVertex->lock( 0, 4, ksLOCK_DISCARD );

	for( KsInt32 i=0; i<4; i++ ){
		v[ i ].color = color;
	}

	m_pVertex->unlock();
}

/************************************************************************************************/
/*
 * スケール値をセットする
 * @param		scaleX			スケールX
 * @param		scaleX			スケールY
 */
/************************************************************************************************/
void KsSprite::setScale( KsReal scaleX, KsReal scaleY )
{
	m_scaleX = scaleX;
	m_scaleY = scaleY;
}
/************************************************************************************************/
/*
 * テクスチャをセットする
 * @param		pTexture		テクスチャ
 */
/************************************************************************************************/
void KsSprite::setTexture( KsTexture* pTexture )
{
	m_pTexture = pTexture;
}

/************************************************************************************************/
/*
 * 位置座標をセットする
 * @param		x				X座標
 * @param		y				Y座標
 */
/************************************************************************************************/
void KsSprite::setTranslate( KsReal x, KsReal y )
{
	m_centerX = x;
	m_centerY = y;

	reset();
}

/************************************************************************************************/
/*
 * 回転角度セットする
 * @param		rotate			回転角度
 */
/************************************************************************************************/
void KsSprite::setRotate( KsReal rotate )
{
	m_rotate = rotate;

	reset();
}

/************************************************************************************************/
/*
 * 今の状態から指定量回転させる
 * @param		x				X方向の移動量
 * @param		y				Y方向の移動量
 */
/************************************************************************************************/
void KsSprite::translate( KsReal x, KsReal y )
{
	KS_SPRITE_PRIM* v = (KS_SPRITE_PRIM*)m_pVertex->lock( 0, 4, ksLOCK_DISCARD );

	for( KsInt32 i=0; i<4; i++ ){
		v[ i ].x += x;
		v[ i ].y += y;
	}

	m_pVertex->unlock();
}

/************************************************************************************************/
/*
 * 今の状態から指定量回転させる
 * @param		rotate			回転量
 */
/************************************************************************************************/
void KsSprite::rotate( KsReal rotate )
{
	m_rotate += rotate;

	reset();
}

/************************************************************************************************/
/*
 * 初期化処理(マネージャに登録されたときに登録)
 * @param		pParam			パラメータ
 */
/************************************************************************************************/
void* KsSprite::initialize( void* pParam )
{
	return pParam;
}

/************************************************************************************************/
/*
 * タスクの実行
 * @param		pParam			パラメータ
 */
/************************************************************************************************/
void* KsSprite::execute( void* pParam )
{
	return pParam;
}

/************************************************************************************************/
/*
 * 描画処理
 * @param		pParam			パラメータ
 */
/************************************************************************************************/
void* KsSprite::render( void* pParam )
{
	KsRenderSystem*	pRS = KsGameSystem::getInstancePtr()->getRenderSystem();

	pRS->setTexture( 0, m_pTexture );
	pRS->drawPrimitive( ksPRIMITIVE_TRIANGLE_STRIP, 0, 2, m_pVertex );

	return pParam;
}

/************************************************************************************************/
/*
 * 後処理関数でメモリーから削除されるときに呼ばれる
 * @param		pParam			パラメータ
 */
/************************************************************************************************/
void* KsSprite::terminate( void* pParam )
{
	if( m_useWork ){
		KsSpriteWorkArea::destroySpreite( this );
	}

	return pParam;
}

/************************************************************************************************/
/*
 * スタートアップ
 */
/************************************************************************************************/
void KsSprite::startup()
{
	m_id           = 0;
	m_flags        = ksTASK_FALGS_INITIALIZE;
	m_type         = ksTASK_TYPE_BASE;
	m_pParent      = 0;
	m_pPrevBrother = 0;
	m_pNextBrother = 0;
	m_pChild       = 0;
	m_pPrev        = 0;
	m_pNext        = 0;
	m_pManager     = 0;
	m_scaleX       = 0.0f;
	m_scaleY       = 0.0f;
	m_spriteFlags  = 0;
	m_useWork      = 0;
	m_clipX        = 0;
	m_clipY        = 0;
	m_clipW        = 0;
	m_clipH        = 0;
	m_pTexture     = NULL;
	m_pVertex      = NULL;
	m_priority.i   = ksSPRITE_DEFAULT_PRIORITY;
	m_order        = ksSPRITE_TASK_ORDER;
}

/************************************************************************************************/
/*
 * パラメータをクリアーする
 */
/************************************************************************************************/
void KsSprite::clear()
{
	m_id           = 0;
	m_flags        = ksTASK_FALGS_INITIALIZE;
	m_type         = ksTASK_TYPE_BASE;
	m_pParent      = 0;
	m_pPrevBrother = 0;
	m_pNextBrother = 0;
	m_pChild       = 0;
	m_pPrev        = 0;
	m_pNext        = 0;
	m_pManager     = 0;
	m_scaleX       = 0.0f;
	m_scaleY       = 0.0f;
	m_spriteFlags  = 0;
	m_useWork      = 0;
	m_pTexture     = NULL;
	m_priority.i   = ksSPRITE_DEFAULT_PRIORITY;
	m_order        = ksSPRITE_TASK_ORDER;
}

/************************************************************************************************/
/*
 * 頂点などを再セットしなおす
 */
/************************************************************************************************/
void KsSprite::reset()
{
	KsReal		x;
	KsReal		y;
	KsReal		sinTH = KsSin( -m_rotate );
	KsReal		cosTH = KsCos( -m_rotate );

	KS_SPRITE_PRIM* v = (KS_SPRITE_PRIM*)m_pVertex->lock( 0, 4, ksLOCK_DISCARD );

	for( KsInt32 i=0; i<4; i++ ){
		x = m_scaleX * m_x[ i ];
		y = m_scaleY * m_y[ i ];

		v[ i ].x   = x * cosTH - y * sinTH + m_centerX;
		v[ i ].y   = x * sinTH + y * cosTH + m_centerY;
		v[ i ].z   = 1.0f;
		v[ i ].rhw = 1.0f;
	}

	m_pVertex->unlock();
}

/************************************************************************************************/
/*
 * 頂点バッファを生成する
 */
/************************************************************************************************/
void KsSprite::createVertexBuffer()
{
	if( !m_pVertex ){
		m_pVertex = KsHardwareBufferManager::getInstancePtr()->createVertexBuffer( sizeof(KS_SPRITE_PRIM), 4, ksFVF_XYZRHW | ksFVF_DIFFUSE | ksFVF_TEX1 , 0 );
	}
}

/************************************************************************************************/
/*
 * 頂点バッファを削除する
 */
/************************************************************************************************/
void KsSprite::destroyVertexBuffer()
{
	ksDELETE( m_pVertex );
}





/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsSpriteWorkArea::initialize()
{
	for( KsInt32 i=0; i<ksSPRITE_WORK_MAX; i++ ){
		m_spriteWork[ i ].m_useWork = 1;
		m_spriteWork[ i ].setFlags( m_spriteWork[ i ].getFlags() | ksTASK_FLAGS_USE_WORKAREA );
		m_spriteStack[ i ] = &m_spriteWork[ i ];
	}

	m_stackCount = ksSPRITE_WORK_MAX;
}

void KsSpriteWorkArea::terminate()
{
	for( KsInt32 i=0; i<ksSPRITE_WORK_MAX; i++ ){
		m_spriteWork[ i ].destroyVertexBuffer();
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsSprite* KsSpriteWorkArea::createSprite()
{
	if( m_stackCount <= 0 ){
		KsMessage( "sprite area over!!" );
		KsSprite* pSprite = new KsSprite();
		pSprite->createVertexBuffer();

		return pSprite;
	}

	m_stackCount--;

	/* 初期化してから渡すようにする */
	m_spriteStack[ m_stackCount ]->createVertexBuffer();
	m_spriteStack[ m_stackCount ]->clear();
	m_spriteStack[ m_stackCount ]->m_useWork = 1;
	m_spriteStack[ m_stackCount ]->setFlags( m_spriteStack[ m_stackCount ]->getFlags() | ksTASK_FLAGS_USE_WORKAREA );

	return m_spriteStack[ m_stackCount ];
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsSpriteWorkArea::destroySpreite( KsSprite* pSprite )
{
	m_spriteStack[ m_stackCount ] = pSprite;

	m_stackCount++;
}






