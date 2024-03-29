/************************************************************************************************/
/** 
 * @file		KsAdapterList.h
 * @brief		アダプタクラスのインターフェイス
 * @author		Tsukasa Kato
 * @date		2010/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSADAPTERLIST_H__
#define __KSADAPTERLIST_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsAdapter;

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsAdapter
 * @brief		アダプタクラス
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
class ksENGINE_API KsAdapterList
{
	public:
		/**
		 * コンストラクタ
		 */
											KsAdapterList(){}

		/**
		 * デストラクタ
		 */
		virtual								~KsAdapterList(){}

	public:
		/**
		 * アダプタ数を取得する
		 * @return							アダプタ数
		 */
		virtual KsUInt32					getAdpterCount() const = 0;

		/**
		 * 指定名のアダプタを取得する
		 * @param		name				アダプタ名
		 * @return							アダプタ	
		 */
		virtual const KsAdapter*			getAdapter( KsInt32 index ) = 0;

	protected:
		/**
		 * アダプタを列挙する
		 * @return	yTrue					列挙成功
		 */
		virtual KsBool						enumerateAdapter() = 0;
};

#endif /*__KSADAPTERLIST_H__*/





