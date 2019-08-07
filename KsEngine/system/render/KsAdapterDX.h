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
#ifndef __KSADAPTERDX_H__
#define __KSADAPTERDX_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsType.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr9.h>

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsVideoModeDXList;


/************************************************************************************************/
/**
 * ウインドウアプリケーションのパラメータクラス<BR>
 * @class	KsVideoMode
 * @author  kato tukasa
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class KsAdapterDX
{
	protected:
		IDirect3D9*									m_pD3D;					/**< Direct3D9オブジェクト	*/
		KsUInt32									m_adapterNumber;		/**< アダプタナンバー			*/
		D3DADAPTER_IDENTIFIER9						m_adapterIdentifier;	/**< アダプタ確認			*/
		D3DDISPLAYMODE								m_desktopDisplayMode;	/**< ディスプレイモード		*/
		KsVideoModeDXList*							m_pVideoModeList;		/**< ビデオモードリスト		*/
		KsInt32									m_tempNumber;			/**< 予備ナンバー			*/
		static KsInt32								m_adapterCount;			/**< アダプタ数				*/

	public:
		/**
		 * コンストラクタ
		 */
													KsAdapterDX();

		/**
		 * コンストラクタ(コピー)
		 * @param		refAdapter					アダプタ
		 */
													KsAdapterDX( const KsAdapterDX& refAdapter );

		/**
		 * コンストラクタ
		 * @param		pD3D						Direct3D9オブジェクト
		 * @param		adapterNumber				アダプタナンバー
		 * @param		adapterIdentifier			アダプタ確認
		 * @param		desktopDisplayMode			ディスプレイモード
		 */
													KsAdapterDX( IDirect3D9* pD3D, KsUInt32 adapterNumber, D3DADAPTER_IDENTIFIER9 adapterIdentifier, D3DDISPLAYMODE desktopDisplayMode );

		/**
		 * デストラクタ
		 */
		virtual									~KsAdapterDX();

		/**
		 * アダプタ名を取得する
		 * @return									アダプタ名
		 */
		std::string									getAdapterName();

		/**
		 * アダプタ詳細を取得する
		 * @return									アダプタ詳細
		 */
		std::string									getAdapterDescription();

		/**
		 * Direct3D9オブジェクトを取得する
		 * @return									Direct3D9オブジェクト
		 */
		IDirect3D9*									getD3D() { return m_pD3D; }

		/**
		 * アダプタナンバーを取得する
		 * @return									アダプタナンバ		
		 */
		KsUInt32									getAdapterNumber() const { return m_adapterNumber; }

		/**
		 * アダプタナンバーを取得する
		 * @return									アダプタナンバ		
		 */
		D3DADAPTER_IDENTIFIER9						getAdapterIdentifier() const { return m_adapterIdentifier; }

		/**
		 * アダプタナンバーを取得する
		 * @return									アダプタナンバ		
		 */
		D3DDISPLAYMODE								getDesktopMode() const { return m_desktopDisplayMode; }

		/**
		 * アダプタナンバーを取得する
		 * @return									アダプタナンバ		
		 */
		KsVideoModeDXList*							getVideoModeList();
};


/************************************************************************************************/
/**
 * ウインドウアプリケーションのパラメータクラス<BR>
 * @class	KsVideoMode
 * @author  kato tukasa
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class KsAdapterDXList
{
	public:
		typedef std::vector< KsAdapterDX >				KsAdapterDXArray;
		typedef std::vector< KsAdapterDX >::iterator	KsAdapterDXPtr;

	private:
		KsAdapterDXArray							m_adapterList;	/**< アダプタリスト			*/
		IDirect3D9*									m_pD3D;			/**< Direct3D9オブジェクト	*/

	public:

		/**
		 * コンストラクタ
		 * @param									Direct3D9オブジェクト
		 */
													KsAdapterDXList( IDirect3D9* pD3D );

		/**
		 * デストラクタ
		 */
		virtual									~KsAdapterDXList();

		/**
		 * 初期化処理
		 * @param									Direct3D9オブジェクト
		 * @retval			ksTRUE					成功
		 * @retval			ksFALSE					失敗
		 */
		KsBool										initialize( IDirect3D9* pD3D );

		/**
		 * アイテム数を取得する
		 * @return									アイテム数
		 */
		KsUInt32									getCount() const;

		/**
		 * 指定インデックスのアダプタを取得する
		 * @param			index					指定インデックス
		 * @return									アダプタ
		 */
		KsAdapterDX*								getItem( KsInt32 index );

		/**
		 * 指定名のアダプタを取得する
		 * @param			name					アダプタ名
		 * @return									アダプタ
		 */
		KsAdapterDX*								getItem( const std::string& name );
};


#endif		/* __KSADAPTERDX_H__ */

