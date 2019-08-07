/************************************************************************************************/
/** 
 * @file		KsGraphicsDX11.h
 * @brief		�`��(DX11�p)
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSGRAPHICSDX11_H__
#define __KSGRAPHICSDX11_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsGraphicsDX11
 * @brief		�`��(DX11�p)
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksDEVDX11_API KsGraphicsDX11 : public KsGraphics
{
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsGraphicsDX11( KsRenderSystemDX11* pRenderSystem );

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsGraphicsDX11();

		/**
		 * Line�o�b�t�@�𐶐�����
		 * @param	count			�ő�v���~�e�B�u��
		 */
		virtual void				createLineBuffer( KsUInt32 lineMax );

		/**
		 * Line�o�b�t�@��j������
		 */
		virtual void				destroyLineBuffer();

		virtual void				setColorLine( const KsColorReal& lineColor );
		virtual void				setColorLine( KsReal r, KsReal g, KsReal b, KsReal a );
		virtual void				drawLine( const KsVector3d& start, const KsVector3d& end );
		virtual void				flushLine( KsRenderContext* pRenderContext );
		
		/**
		 * Rect�o�b�t�@�𐶐�����
		 * @param	count			�ő�v���~�e�B�u��
		 */
		virtual void				createRectBuffer( KsUInt32 rectMax );

		/**
		 * Rect�o�b�t�@��j������
		 */
		virtual void				destroyRectBuffer();

		virtual void				setColorRect( const KsColorReal& lineColor );
		virtual void				setColorRect( KsReal r, KsReal g, KsReal b, KsReal a );
		virtual void				setColorRect( KsInt32 index, const KsColorReal& rectColor );
		virtual void				setColorRect( KsInt32 index, KsReal r, KsReal g, KsReal b, KsReal a );

		/**
		 * RECT �`�悷��
		 * @param		left		X���W
		 * @param		top			Y���W
		 * @param		width		��
		 * @param		height		����
		 */
		virtual void				drawRect( KsInt32 left, KsInt32 top, KsInt32 width, KsInt32 height );

		/**
		 * RECT �`�悷��
		 * @param		left		X���W
		 * @param		top			Y���W
		 * @param		width		��
		 * @param		height		����
		 */
		virtual void				drawRect( KsReal left, KsReal top, KsReal width, KsReal height );

		virtual void				flushRect( KsRenderContext* pRenderContext );

		/**
		 * Sprite�o�b�t�@�𐶐�����
		 * @param	count			�ő�v���~�e�B�u��
		 */
		virtual void				createSpriteBuffer( KsUInt32 workMax, KsUInt32 spriteMax );
		virtual void				destroySpriteBuffer();
		
		virtual void				setColorSprite( const KsColorReal& lineColor );
		virtual void				setColorSprite( KsReal r, KsReal g, KsReal b, KsReal a );
		virtual void				setColorSprite( KsInt32 index, const KsColorReal& rectColor );
		virtual void				setColorSprite( KsInt32 index, KsReal r, KsReal g, KsReal b, KsReal a );
		virtual void				drawSprite( const KsTexture* pTexture, KsInt32 left, KsInt32 top, KsInt32 width, KsInt32 height, KsReal tx=0.0f, KsReal ty=0.0f, KsReal tw=1.0f, KsReal th=1.0f );
		virtual void				drawSprite( const KsTexture* pTexture, KsReal left, KsReal top, KsReal width, KsReal height, KsReal tx=0.0f, KsReal ty=0.0f, KsReal tw=1.0f, KsReal th=1.0f );
		virtual void				drawSprite( const KsTexture* pTexture, const KS_VERTEX_SPRITE* pVertices );
		virtual void				flushSprite( KsRenderContext* pRenderContext );

		/**
		 * �o�b�t�@���ꊇ�`�悷��
		 * @param	pRenderContext	�`��R���e�L�X�g
		 */
		virtual void				flush( KsRenderContext* pRenderContext );

	private:
		KsRenderSystemDX11*			m_pRenderSystem;		/**< �`��V�X�e��						*/
		KsConstantBuffer*			m_pGraphicsCB;			/**< �O���b�t�B�N�p�R���X�^���g�o�b�t�@	*/
		KS_GRAPHICS_CB				m_cbGraphics;			/**< �O���b�t�B�N���p�\����				*/
		KsBlendState*				m_pBlendState;			/**< �u�����h�X�e�[�g					*/
		KsLine2DBatch*				m_pLine2DBatch;			/**< Line2D�ꊇ�`��					*/
		KsLine3DBatch*				m_pLine3DBatch;			/**< Line3D�ꊇ�`��					*/
		KsRectBatch*				m_pRectBatch;			/**< Rect�ꊇ�`��						*/
		KsSpriteBatch*				m_pSpriteBatch;			/**< Sprite�ꊇ�`��					*/
};


#endif		/* __KSGRAPHICSDX11_H__ */



