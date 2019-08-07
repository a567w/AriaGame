/************************************************************************************************/
/** 
 * @file		KsVideoModeDX.h
 * @brief		ビデをモードを取得する
 * @author		Tsukasa Kato
 * @date		2004/08/17
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSVIDEOMODELISTDX_H__
#define __KSVIDEOMODELISTDX_H__

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
 * @class	KsVideoModeListDX
 * @author  Tsukasa Kato
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class ksDEVD3D9_API KsVideoModeListDX
{
	public:
		typedef KsArray< KsVideoModeDX* >		KsVideoModeDXArray;

	protected:
		KsVideoModeDXArray			m_vpVideoModeList;	/**< ビデオモードリスト	*/
		KsAdapterDX*				m_pAdapter;			/**< アダプタ			*/
	
	public:
		/**
		 * コンストラクタ
		 */
									KsVideoModeListDX();

		/**
		 * コンストラクタ
		 * @param		pAdapter	アダプタのポインタ
		 */
									KsVideoModeListDX( KsAdapterDX* pAdapter );

		/**
		 * デストラクタ
		 */
		virtual					~KsVideoModeListDX();

		/**
		 * 初期化
		 * @param		pAdapter	アダプタクラスのポインタ
		 * @retval		ksTRUE		成功
		 * @retval		ksFALSE		失敗
		 */
		KsBool						initialize( KsAdapterDX* pAdapter );

		/**
		 * アイテム数を取得する
		 * @return					アイテム数
		 */
		KsUInt32					getCount();


		/**
		 * アイテム数を取得する
		 * @return					アイテム数
		 */
		KsUInt32					getCount() const;

		/**
		 * 指定インデックスのビデオモードを取得する
		 * @param		index		指定インデックス
		 * @return					ビデオモード
		 */
		KsVideoModeDX*				getItem( KsInt32 index );

		/**
		 * 指定名のビデオモードを取得する
		 * @param		name		ビデオモード名
		 * @return					ビデオモード
		 */
		KsVideoModeDX*				getItem( const KsString& name );
};


#endif /* __KSVIDEOMODELISTDX_H__ */



