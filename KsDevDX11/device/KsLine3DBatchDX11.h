/************************************************************************************************/
/** 
 * @file		KsLine3DBatchDX11.h
 * @brief		3Dライン描画
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSLINE3DBATCHDX11_H__
#define __KSLINE3DBATCHDX11_H__

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
 * @class		KsLine3DBatchDX11
 * @brief		Line3D 描画
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksDEVDX11_API KsLine3DBatchDX11 : public KsLine3DBatch
{
	public:
		/**
		 * コンストラクタ
		 * @param	count			最大プリミティブ数
		 */
									KsLine3DBatchDX11( KsUInt32 count );

		/**
		 * デストラクタ
		 */
		virtual						~KsLine3DBatchDX11();

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
		 * ライン描画する
		 * @param		start		X座標
		 * @param		end			Y座標
		 */
		virtual void				draw( const KsVector3d& start, const KsVector3d& end );

		/**
		 * バッファを一括描画する
		 * @param	pRenderContext	描画コンテキスト
		 */
		virtual void				flush( KsRenderContext* pRenderContext );

	private:
		KsUInt32					m_lineCount;
		KsUInt32					m_lineMax;
		KsUInt32					m_lineIndex;
		KsUInt32					m_lineStride;
		KsUInt32					m_lineOffset;
		KsColorReal					m_lineColor;
		KS_VERTEX_LINE3D*			m_pLineVertices;
		KsVertexShader*				m_pLineVS;
		KsPixelShader*				m_pLinePS;
		KsVertexBuffer*				m_pLineVB;
		KsInputLayout*				m_pLineIL;
};



#endif		/* __KSLINE3DBATCHDX11_H__ */



