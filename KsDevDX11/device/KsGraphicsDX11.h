/************************************************************************************************/
/** 
 * @file		KsGraphicsDX11.h
 * @brief		描画(DX11用)
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSGRAPHICSDX11_H__
#define __KSGRAPHICSDX11_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsGraphicsDX11
 * @brief		描画(DX11用)
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksDEVDX11_API KsGraphicsDX11 : public KsGraphics
{
	public:
		/**
		 * コンストラクタ
		 */
									KsGraphicsDX11( KsRenderSystemDX11* pRenderSystem );

		/**
		 * デストラクタ
		 */
		virtual						~KsGraphicsDX11();

		/**
		 * Lineバッファを生成する
		 * @param	count			最大プリミティブ数
		 */
		virtual void				createLineBuffer( KsUInt32 lineMax );

		/**
		 * Lineバッファを破棄する
		 */
		virtual void				destroyLineBuffer();

		virtual void				setColorLine( const KsColorReal& lineColor );
		virtual void				setColorLine( KsReal r, KsReal g, KsReal b, KsReal a );
		virtual void				drawLine( const KsVector3d& start, const KsVector3d& end );
		virtual void				flushLine( KsRenderContext* pRenderContext );
		
		/**
		 * Rectバッファを生成する
		 * @param	count			最大プリミティブ数
		 */
		virtual void				createRectBuffer( KsUInt32 rectMax );

		/**
		 * Rectバッファを破棄する
		 */
		virtual void				destroyRectBuffer();

		virtual void				setColorRect( const KsColorReal& lineColor );
		virtual void				setColorRect( KsReal r, KsReal g, KsReal b, KsReal a );
		virtual void				setColorRect( KsInt32 index, const KsColorReal& rectColor );
		virtual void				setColorRect( KsInt32 index, KsReal r, KsReal g, KsReal b, KsReal a );

		/**
		 * RECT 描画する
		 * @param		left		X座標
		 * @param		top			Y座標
		 * @param		width		幅
		 * @param		height		高さ
		 */
		virtual void				drawRect( KsInt32 left, KsInt32 top, KsInt32 width, KsInt32 height );

		/**
		 * RECT 描画する
		 * @param		left		X座標
		 * @param		top			Y座標
		 * @param		width		幅
		 * @param		height		高さ
		 */
		virtual void				drawRect( KsReal left, KsReal top, KsReal width, KsReal height );

		virtual void				flushRect( KsRenderContext* pRenderContext );

		/**
		 * Spriteバッファを生成する
		 * @param	count			最大プリミティブ数
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
		 * バッファを一括描画する
		 * @param	pRenderContext	描画コンテキスト
		 */
		virtual void				flush( KsRenderContext* pRenderContext );

	private:
		KsRenderSystemDX11*			m_pRenderSystem;		/**< 描画システム						*/
		KsConstantBuffer*			m_pGraphicsCB;			/**< グラッフィク用コンスタントバッファ	*/
		KS_GRAPHICS_CB				m_cbGraphics;			/**< グラッフィクす用構造体				*/
		KsBlendState*				m_pBlendState;			/**< ブレンドステート					*/
		KsLine2DBatch*				m_pLine2DBatch;			/**< Line2D一括描画					*/
		KsLine3DBatch*				m_pLine3DBatch;			/**< Line3D一括描画					*/
		KsRectBatch*				m_pRectBatch;			/**< Rect一括描画						*/
		KsSpriteBatch*				m_pSpriteBatch;			/**< Sprite一括描画					*/
};


#endif		/* __KSGRAPHICSDX11_H__ */



