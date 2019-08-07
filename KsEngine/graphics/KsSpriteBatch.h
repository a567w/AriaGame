/************************************************************************************************/
/** 
 * @file		KsSpriteBatch.h
 * @brief		描画
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSPRITEBATCH_H__
#define __KSSPRITEBATCH_H__

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
 * @class		KsSpriteBatch
 * @brief		描画
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsSpriteBatch
{
	public:
		/**
		 * コンストラクタ
		 */
									KsSpriteBatch();

		/**
		 * デストラクタ
		 */
		virtual						~KsSpriteBatch();

		/**
		 * バッファを生成する
		 * @param	count			最大プリミティブ数
		 */
		virtual void				create( KsUInt32 workMax, KsUInt32 spriteMax ) = 0;

		/**
		 * バッファを破棄する
		 */
		virtual void				destroy() = 0;

		/**
		 * カラーをセットする
		 * @param	rectColor		カラー値
		 */
		virtual void				setColor( const KsColorReal& lineColor ) = 0;

		/**
		 * カラーをセットする
		 * @param	r				R値
		 * @param	g				G値
		 * @param	b				B値
		 * @param	a				A値
		 */
		virtual void				setColor( KsReal r, KsReal g, KsReal b, KsReal a ) = 0;

		/**
		 * カラーをセットする
		 * @param	index			インデックス
		 * @param	rectColor		カラー値
		 */
		virtual void				setColor( KsInt32 index, const KsColorReal& rectColor ) = 0;

		/**
		 * カラーをセットする
		 * @param	index			インデックス
		 * @param	r				R値
		 * @param	g				G値
		 * @param	b				B値
		 * @param	a				A値
		 */
		virtual void				setColor( KsInt32 index, KsReal r, KsReal g, KsReal b, KsReal a ) = 0;

		/**
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
		virtual void				draw( const KsTexture* pTexture, KsInt32 left, KsInt32 top, KsInt32 width, KsInt32 height, KsReal tx, KsReal ty, KsReal tw, KsReal th ) = 0;

		/**
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
		virtual void				draw( const KsTexture* pTexture, KsReal left, KsReal top, KsReal width, KsReal height, KsReal tx, KsReal ty, KsReal tw, KsReal th ) = 0;

		/**
		 * Sprite 描画する
		 * @param		pTexture	テクスチャ
		 * @param		pVertices	スプライト用頂点データ
		 */
		virtual void				draw( const KsTexture* pTexture, const KS_VERTEX_SPRITE* pVertices ) = 0;

		/**
		 * バッファを一括描画する
		 * @param	pRenderContext	描画コンテキスト
		 */
		virtual void				flush( KsRenderContext* pRenderContext ) = 0;
};


#endif		/* __KSSPRITEBATCH_H__ */



