/************************************************************************************************/
/** 
 * @file		KsAdapterListDX11.h
 * @brief		アダプタ情報リスト
 * @author		Tsukasa Kato
 * @date		2003/03/22
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSADAPTERLISTDX11_H__
#define __KSADAPTERLISTDX11_H__

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
 * ビデオカード情報リストクラス
 * @class	KsAdapterListDX
 * @author  kato tukasa
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class ksDEVDX11_API KsAdapterListDX11 : public KsAdapterList
{
	public:
		typedef KsArray< KsAdapter* >		KsAdapterArray;

	private:
		KsAdapterArray						m_vpAdapterList;	/**< アダプタリスト			*/
		KsRenderSystem*						m_pRenderSystem;	/**< 描画システムオブジェクト	*/

	public:

		/**
		 * コンストラクタ
		 * @param		pRenderSystem		KsRenderSystemオブジェクト
		 */
											KsAdapterListDX11( KsRenderSystem* pRenderSystem );

		/**
		 * デストラクタ
		 */
		virtual								~KsAdapterListDX11();

		/**
		 * 初期化処理
		 * @param		pRenderSystem		KsRenderSystemオブジェクト
		 * @retval		ksTRUE				成功
		 * @retval		ksFALSE				失敗
		 */
		KsBool								initialize( KsRenderSystem* pRenderSystem );

	public:
		/**
		 * アダプタ数を取得する
		 * @return							アダプタ数
		 */
		virtual KsUInt32					getAdpterCount() const;

		/**
		 * 指定名インデックスのアダプタを取得する
		 * @param		index				指定インデックス
		 * @return							アダプタ	
		 */
		virtual const KsAdapter*			getAdapter( KsInt32 index );

	protected:
		/**
		 * アダプタを列挙する
		 * @return	yTrue					列挙成功
		 */
		virtual KsBool						enumerateAdapter();
};


#endif		/* __KSADAPTERLISTDX11_H__ */

