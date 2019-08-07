/************************************************************************************************/
/**
 * @file	KsDisplayDX.h
 * @brief	
 * @author	Tsukasa Kato
 * @date	2003/11/30
 * @version	1.0.0
 */
/************************************************************************************************/
#ifndef __KSDISPLAYDX_H__
#define __KSDISPLAYDX_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsTypeD3D9.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsAdapterDX;

/************************************************************************************************/
/**
 * 画面情報選択クラス
 * @class	KsDisplay
 * @author  kato tukasa
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class ksDEVDX11_API KsDisplaySubItemDX
{
	public:
		/**
		 * コンストラクタ
		 */
										KsDisplaySubItemDX();

		/**
		 * デストラクタ
		 */
										~KsDisplaySubItemDX();

		/**
		 * リフレッシュレートを取得する
		 * @return						リフレッシュレート
		 */
		KsUInt32						getRefreshRate() const { return m_refreshRate; }

		/**
		 * フォーマット取得
		 * @return						フォーマット
		 */
		D3DFORMAT						getFormat()	const { return m_format; }

		/**
		 * フルカラーをもっているか
		 * @retval		ksTRUE			持っている
		 * @retval		ksFALSE			持っていない
		 */
		KsBool							isFullColor()	const { return m_bFullColor; }

		/**
		 * リフレッシュレートをセットする
		 * @param		refreshRate		リフレッシュレート
		 */
		void							setRefreshRate( KsUInt32 refreshRate ){ m_refreshRate = refreshRate; }

		/**
		 * フォーマットをセットする
		 * @param		format			フォーマット
		 */
		void							setFormat( D3DFORMAT format ) { m_format = format; }

		/**
		 * フルカラーのフラグをセットする
		 * @param		flag			フルカラーを持っているかのフラグ
		 */
		void							setFullColor( KsBool flag ) { m_bFullColor = flag; }

	public:
		KsUInt32						m_refreshRate;	/**< リフレッシュレートリスト		*/
		D3DFORMAT						m_format;		/**< フォーマットリスト				*/
		KsUInt32						m_colorFlags;	/**< どのカラーをもっているか？		*/
		KsBool							m_bFullColor;	/**< フルカラーを持っているかどうか	*/
		KsArray< D3DFORMAT >			m_vFormatList;	/**< フォーマットの種類				*/
};

/************************************************************************************************/
/**
 * 画面情報選択クラス<BR>
 * @class	KsDisplay
 * @author  kato tukasa
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class KsDisplayItemDX
{
	public:
		typedef KsArray< KsDisplaySubItemDX* >	KsDisplaySubItemDXList;

	public:
		/**
		 * コンストラクタ
		 */
										KsDisplayItemDX();

		/**
		 * デストラクタ
		 */
		virtual						~KsDisplayItemDX();

		/**
		 * 画面幅を取得する
		 * @return						画面幅
		 */
		KsInt32						getWidth() const { return m_width; }

		/**
		 * 画面の高さを取得する
		 * @return						画面の高さ
		 */
		KsInt32						getHeight() const { return m_height; }

		/**
		 * 画面幅をセットする
		 * @param		width			画面幅
		 */
		void							setWidth( KsInt32 width ) { m_width = width; }

		/**
		 * 画面の高さをセットする
		 * @param		height			画面の高さ
		 */
		void							setHeight( KsInt32 height ) { m_height = height; }

	public:
		KsInt32						m_width;			/**< 幅				*/
		KsInt32						m_height;			/**< 高さ			*/
		KsDisplaySubItemDXList			m_vpSubItems;		/**< サブアイテム	*/
};

/************************************************************************************************/
/**
 * 画面情報選択リストクラス<BR>
 * @class	KsDisplayListDX
 * @author  kato tukasa
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class KsDisplayDX
{
	public:
		typedef KsArray< KsDisplayItemDX* >	KsDisplayItemDXList;

	public:
		/**
		 * コンストラクタ
 		 * @param		pAdapter		アダプタ
		 */
										KsDisplayDX( KsAdapterDX* pAdapter );
		/**
		 * デストラクタ
		 */
		virtual						~KsDisplayDX();

		/**
		 * 画面設定情報を取得する
		 * @param		index			配列の指定インデックス
		 * @return						画面設定情報
		 */
		const KsDisplayItemDX*			getItem( KsInt32 index ) { return m_vDisplayItems[ index ]; }

		/**
		 * 画面設定情報の数を取得する
		 * @return						画面設定情報の数
		 */
		KsUInt32						getCount() const { return m_vDisplayItems.size(); }

		/**
		 * アダプタ名を取得する
		 * @return						アダプタ名
		 */
		const KsString&					getAdapterName() { return m_adapterName; }

	protected:
		KsString						m_adapterName;		/**< アダプタ名				*/
		KsDisplayItemDXList				m_vDisplayItems;	/**< 画面設定情報リスト		*/
};

#endif	/* __KSDISPLAYDX_H__ */


