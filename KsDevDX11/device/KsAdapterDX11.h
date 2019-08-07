/************************************************************************************************/
/** 
 * @file		KsAdapterDX.h
 * @brief		アダプタ情報<BR>
 * @author		Tsukasa Kato
 * @date		2003/03/22
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSADAPTERDX11_H__
#define __KSADAPTERDX11_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * ビデオカード情報クラス
 * @class	KsAdapterDX
 * @author  kato tukasa
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class ksDEVDX11_API KsAdapterDX11 : public KsAdapter
{
	protected:
		KsRenderSystem*						m_pRenderSystem;
		IDXGIAdapter*						m_pDXGIAdapter;			/**< アダプターDX11			*/
		KsArray<IDXGIOutput*>				m_vpOutputs;
		//KsVideoModeListDX*					m_pVideoModeList;		/**< ビデオモードリスト		*/
		KsString							m_name;
		KsString							m_description;

	public:
		/**
		 * コンストラクタ(コピー)
		 * @param		refAdapter			アダプタ
		 */
											KsAdapterDX11( IDXGIAdapter* pDXGIAdapter );

		/**
		 * デストラクタ
		 */
		virtual								~KsAdapterDX11();

		/**
		 * 初期化処理
		 * @param		pDXGIAdapter		IDXGIAdapterオブジェクト
		 * @retval		ksTRUE				成功
		 * @retval		ksFALSE				失敗
		 */
		KsBool								initialize( IDXGIAdapter* pDXGIAdapter );

		/**
		 * アダプタ名を取得する
		 * @return							アダプタ名
		 */
		virtual const KsString&				getAdapterName();

		/**
		 * アダプタ詳細を取得する
		 * @return							アダプタ詳細
		 */
		virtual const KsString&				getAdapterDescription();

		/**
		 * アダプタナンバーを取得する
		 * @return							アダプタナンバ		
		 */
		virtual const KsDisplayMode*		getDisplayMode( KsInt32 index );

		/**
		 * アダプタナンバーを取得する
		 * @return							アダプタナンバ		
		 */
		virtual const KsDisplayModeList*	getDisplayModeList();

	protected:

		/**
		 * ディスプレイモードを列挙する
		 * @return	yTrue					列挙成功
		 */
		virtual KsBool						enumerateDisplayMode();
};

#endif		/* __KSADAPTERDX11_H__ */

