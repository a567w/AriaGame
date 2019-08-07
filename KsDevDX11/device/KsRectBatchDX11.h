/************************************************************************************************/
/** 
 * @file		KsRectBatchDX11.h
 * @brief		描画(DX11用)
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSRECTBATCHDX11_H__
#define __KSRECTBATCHDX11_H__

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
 * @class		KsRectBatchDX11
 * @brief		RECT 描画(DX11用)
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksDEVDX11_API KsRectBatchDX11 : public KsRectBatch
{
	public:
		/**
		 * コンストラクタ
		 * @param	count			最大プリミティブ数
		 */
									KsRectBatchDX11( KsUInt32 count );

		/**
		 * デストラクタ
		 */
		virtual						~KsRectBatchDX11();

		/**
		 * バッファを生成する
		 * @param	count			最大プリミティブ数
		 */
		virtual void				create( KsUInt32 count );

		/**
		 * バッファを破棄する
		 */
		virtual void				destroy();

		/**
		 * カラーをセットする
		 * @param	rectColor		カラー値
		 */
		virtual void				setColor( const KsColorReal& lineColor );

		/**
		 * カラーをセットする
		 * @param	r				R値
		 * @param	g				G値
		 * @param	b				B値
		 * @param	a				A値
		 */
		virtual void				setColor( KsReal r, KsReal g, KsReal b, KsReal a );

		/**
		 * カラーをセットする
		 * @param	index			インデックス
		 * @param	rectColor		カラー値
		 */
		virtual void				setColor( KsInt32 index, const KsColorReal& rectColor );

		/**
		 * カラーをセットする
		 * @param	index			インデックス
		 * @param	r				R値
		 * @param	g				G値
		 * @param	b				B値
		 * @param	a				A値
		 */
		virtual void				setColor( KsInt32 index, KsReal r, KsReal g, KsReal b, KsReal a );

		/**
		 * RECT 描画する
		 * @param		left		X座標
		 * @param		top			Y座標
		 * @param		width		幅
		 * @param		height		高さ
		 */
		virtual void				draw( KsInt32 left, KsInt32 top, KsInt32 width, KsInt32 height );

		/**
		 * RECT 描画する
		 * @param		left		X座標
		 * @param		top			Y座標
		 * @param		width		幅
		 * @param		height		高さ
		 */
		virtual void				draw( KsReal left, KsReal top, KsReal width, KsReal height );

		/**
		 * バッファを一括描画する
		 * @param	pRenderContext	描画コンテキスト
		 */
		virtual void				flush( KsRenderContext* pRenderContext );

	private:
		KsUInt32					m_rectCount;		/**< 描画するRect数			*/
		KsUInt32					m_rectMax;			/**< 描画するRect最大数		*/
		KsUInt32					m_rectIndex;		/**< 描画するRect最大数		*/
		KsUInt32					m_rectStride;		/**< Rect Stride			*/
		KsUInt32					m_rectOffset;		/**< Rect Offset			*/
		KsReal						m_rectDepth;		/**< Rect 深度値				*/
		KS_VERTEX_RECT*				m_pRectVertices;	/**< Rect頂点				*/
		KsVertexShader*				m_pRectVS;			/**< Rect Vertex　Shader		*/
		KsPixelShader*				m_pRectPS;			/**< Rect Pixel　 Shader		*/
		KsInputLayout*				m_pRectIL;			/**< 頂点レイアウト			*/
		KsVertexBuffer*				m_pRectVB;			/**< 頂点バッファ				*/
		KsIndexBuffer*				m_pRectIB;			/**< インデックスバッファ		*/
		KsColorReal					m_rectColor[ 4 ];	/**< Rect描画の4頂点のカラー	*/
};



#endif		/* __KSRECTBATCHDX11_H__ */



