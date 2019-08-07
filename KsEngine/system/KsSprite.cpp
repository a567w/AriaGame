/*************************************************************************************************/
/**
 * @file	KsSprite.cpp
 * @brief	�X�v���C�g�N���X
 * @author	Tsukasa Kato
 * @date	2003/11/30
 * @version	1.0.0
 */
/*************************************************************************************************/

/*===============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*===============================================================================================*/
#include "KsSprite.h"
#include "KsPrimitive.h"
#include "KsGameSystem.h"

/*===============================================================================================*/
/*                                     << ��` >>                                                */
/*===============================================================================================*/

/*===============================================================================================*/
/*                                     << �錾 >>                                                */
/*===============================================================================================*/
KsSprite   KsSpriteWorkArea::m_spriteWork[ ksSPRITE_WORK_MAX ];
KsSprite*  KsSpriteWorkArea::m_spriteStack[ ksSPRITE_WORK_MAX ];
KsInt32    KsSpriteWorkArea::m_stackCount = 0;

/************************************************************************************************/
/*
 * �R���X�g���N�^
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
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsSprite::~KsSprite()
{
	destroyVertexBuffer();
}

/************************************************************************************************/
/*
 * �X�v���C�g����
 * @param		x				X���W
 * @param		y				Y���W
 * @param		w				��
 * @param		h				����
 * @param		tx				�e�N�X�`����X���W
 * @param		ty				�e�N�X�`����Y���W
 * @param		tw				�e�N�X�`���̕�
 * @param		th				�e�N�X�`���̍���
 * @param		scaleX			X�̃X�P�[���l
 * @param		scaleY			Y�̃X�P�[���l
 * @param		rotate			��]��
 * @param		color			�J���[
 * @param		pTexture		�g�p�e�N�X�`���̃|�C���^(�g�p���Ȃ��Ƃ��́ANULL��ݒ�)
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
 * �X�v���C�g����
 * @param		x				X���W
 * @param		y				Y���W
 * @param		w				��
 * @param		h				����
 * @param		tx				�e�N�X�`����X���W
 * @param		ty				�e�N�X�`����Y���W
 * @param		tw				�e�N�X�`���̕�
 * @param		th				�e�N�X�`���̍���
 * @param		color			�J���[
 * @param		pTexture		�g�p�e�N�X�`���̃|�C���^(�g�p���Ȃ��Ƃ��́ANULL��ݒ�)
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
	/*	|x'|   | cos�� - sin��	| x |	| Tx |	*/
	/*	|  | = |				|	| + |	 |	*/
	/*	|y'|   | sin�� + cos��	| y |	| Ty |	*/
	/*------------------------------------------*/
}

/************************************************************************************************/
/*
 * �X�v���C�g����
 * @param		x				�X�v���C�g�\����X���W(�X�v���C�g�̒��S����_�Ƃ���)
 * @param		y				�X�v���C�g�\����Y���W(�X�v���C�g�̒��S����_�Ƃ���)
 * @param		tx				�e�N�X�`����X���W
 * @param		ty				�e�N�X�`����Y���W
 * @param		w				��
 * @param		h				����
 * @param		color			�J���[
 * @param		pTexture		�g�p�e�N�X�`���̃|�C���^(�g�p���Ȃ��Ƃ��́ANULL��ݒ�)
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
 * �X�v���C�g�t���O���Z�b�g����
 * @param		flags			�e��t���O
 */
/************************************************************************************************/
void KsSprite::setSpriteFlags( KsUInt32 flags )
{
	m_spriteFlags = flags;
}

/************************************************************************************************/
/*
 * UV���W���Z�b�g���܂�
 * @param		tx				�e�N�X�`����X���W
 * @param		ty				�e�N�X�`����Y���W
 * @param		tw				�e�N�X�`���̕�
 * @param		th				�e�N�X�`���̍���
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
 * �w�蒸�_�̒��_�J���[���Z�b�g����
 * @param		index			�C���f�b�N�X
 * @param		color			�J���[
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
 * ���ׂĂ̒��_�J���[���Z�b�g����
 * @param		color			�J���[
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
 * �X�P�[���l���Z�b�g����
 * @param		scaleX			�X�P�[��X
 * @param		scaleX			�X�P�[��Y
 */
/************************************************************************************************/
void KsSprite::setScale( KsReal scaleX, KsReal scaleY )
{
	m_scaleX = scaleX;
	m_scaleY = scaleY;
}
/************************************************************************************************/
/*
 * �e�N�X�`�����Z�b�g����
 * @param		pTexture		�e�N�X�`��
 */
/************************************************************************************************/
void KsSprite::setTexture( KsTexture* pTexture )
{
	m_pTexture = pTexture;
}

/************************************************************************************************/
/*
 * �ʒu���W���Z�b�g����
 * @param		x				X���W
 * @param		y				Y���W
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
 * ��]�p�x�Z�b�g����
 * @param		rotate			��]�p�x
 */
/************************************************************************************************/
void KsSprite::setRotate( KsReal rotate )
{
	m_rotate = rotate;

	reset();
}

/************************************************************************************************/
/*
 * ���̏�Ԃ���w��ʉ�]������
 * @param		x				X�����̈ړ���
 * @param		y				Y�����̈ړ���
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
 * ���̏�Ԃ���w��ʉ�]������
 * @param		rotate			��]��
 */
/************************************************************************************************/
void KsSprite::rotate( KsReal rotate )
{
	m_rotate += rotate;

	reset();
}

/************************************************************************************************/
/*
 * ����������(�}�l�[�W���ɓo�^���ꂽ�Ƃ��ɓo�^)
 * @param		pParam			�p�����[�^
 */
/************************************************************************************************/
void* KsSprite::initialize( void* pParam )
{
	return pParam;
}

/************************************************************************************************/
/*
 * �^�X�N�̎��s
 * @param		pParam			�p�����[�^
 */
/************************************************************************************************/
void* KsSprite::execute( void* pParam )
{
	return pParam;
}

/************************************************************************************************/
/*
 * �`�揈��
 * @param		pParam			�p�����[�^
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
 * �㏈���֐��Ń������[����폜�����Ƃ��ɌĂ΂��
 * @param		pParam			�p�����[�^
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
 * �X�^�[�g�A�b�v
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
 * �p�����[�^���N���A�[����
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
 * ���_�Ȃǂ��ăZ�b�g���Ȃ���
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
 * ���_�o�b�t�@�𐶐�����
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
 * ���_�o�b�t�@���폜����
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

	/* ���������Ă���n���悤�ɂ��� */
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






