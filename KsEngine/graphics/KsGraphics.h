/************************************************************************************************/
/** 
 * @file		KsGraphics.h
 * @brief		�`��V�X�e��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSGRAPHICS_H__
#define __KSGRAPHICS_H__

/*==============================================================================================*/
/*                                  << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsGraphics
 * @brief		�x�[�X�`��V�X�e��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsGraphics : public KsSingleton< KsGraphics >
{
	public:
		/**
		 * �V���O���g���̎Q�Ƃ��擾
		 * @return						�V���O���g���̎Q��
		 */
		static KsGraphics&				getInstance();
		
		/**
		 * �V���O���g���̃|�C���^���擾
		 * @return						�V���O���g���̃|�C���^
		 */
		static KsGraphics*				getInstancePtr();

	public:
		/**
		 * �R���X�g���N�^
		 */
										KsGraphics();

		/**
		 * �f�X�g���N�^
		 */
		virtual							~KsGraphics();

		virtual void					setColorLine( const KsColorReal& lineColor )  = 0;
		virtual void					setColorLine( KsReal r, KsReal g, KsReal b, KsReal a ) = 0;
		virtual void					drawLine( const KsVector3d& start, const KsVector3d& end ) = 0;
		virtual void					flushLine( KsRenderContext* pRenderContext ) = 0;

		virtual void					setColorRect( const KsColorReal& lineColor ) = 0;
		virtual void					setColorRect( KsReal r, KsReal g, KsReal b, KsReal a ) = 0;
		virtual void					setColorRect( KsInt32 index, const KsColorReal& rectColor ) = 0;
		virtual void					setColorRect( KsInt32 index, KsReal r, KsReal g, KsReal b, KsReal a ) = 0;
		virtual void					drawRect( KsInt32 left, KsInt32 top, KsInt32 width, KsInt32 height ) = 0;
		virtual void					drawRect( KsReal left, KsReal top, KsReal width, KsReal height ) = 0;
		virtual void					flushRect( KsRenderContext* pRenderContext ) = 0;
		
		virtual void					setColorSprite( const KsColorReal& lineColor ) = 0;
		virtual void					setColorSprite( KsReal r, KsReal g, KsReal b, KsReal a ) = 0;
		virtual void					setColorSprite( KsInt32 index, const KsColorReal& rectColor ) = 0;
		virtual void					setColorSprite( KsInt32 index, KsReal r, KsReal g, KsReal b, KsReal a ) = 0;
		virtual void					drawSprite( const KsTexture* pTexture, KsInt32 left, KsInt32 top, KsInt32 width, KsInt32 height, KsReal tx=0.0f, KsReal ty=0.0f, KsReal tw=1.0f, KsReal th=1.0f ) = 0;
		virtual void					drawSprite( const KsTexture* pTexture, KsReal left, KsReal top, KsReal width, KsReal height, KsReal tx=0.0f, KsReal ty=0.0f, KsReal tw=1.0f, KsReal th=1.0f ) = 0;
		virtual void					drawSprite( const KsTexture* pTexture, const KS_VERTEX_SPRITE* pVertices ) = 0;
		virtual void					flushSprite( KsRenderContext* pRenderContext ) = 0;

		virtual void					flush( KsRenderContext* pRenderContext ) = 0;
};

#endif		/* __KSGRAPHICS_H__ */

