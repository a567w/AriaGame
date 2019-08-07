/************************************************************************************************/
/** 
 * @file		KsRectBatch.h
 * @brief		描画
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSRECTBATCH_H__
#define __KSRECTBATCH_H__

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
 * @class		KsRectBatch
 * @brief		RECT 描画
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsRectBatch
{
	public:
		/**
		 * コンストラクタ
		 * @param	count			最大プリミティブ数
		 */
									KsRectBatch();

		/**
		 * デストラクタ
		 */
		virtual						~KsRectBatch();

		/**
		 * バッファを生成する
		 * @param	count			最大プリミティブ数
		 */
		virtual void				create( KsUInt32 count ) = 0;

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
		 * RECT 描画する
		 * @param		left		X座標
		 * @param		top			Y座標
		 * @param		width		幅
		 * @param		height		高さ
		 */
		virtual void				draw( KsInt32 left, KsInt32 top, KsInt32 width, KsInt32 height ) = 0;

		/**
		 * RECT 描画する
		 * @param		left		X座標
		 * @param		top			Y座標
		 * @param		width		幅
		 * @param		height		高さ
		 */
		virtual void				draw( KsReal left, KsReal top, KsReal width, KsReal height ) = 0;

		/**
		 * バッファを一括描画する
		 * @param	pRenderContext	描画コンテキスト
		 */
		virtual void				flush( KsRenderContext* pRenderContext ) = 0;
};



#endif		/* __KSRECTBATCH_H__ */



