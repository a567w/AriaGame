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
#ifndef __KSVIDEOMODEDX_H__
#define __KSVIDEOMODEDX_H__

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
 * 
 * @class	KsVideoMode
 * @author  Tsukasa Kato
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class ksDEVD3D9_API KsVideoModeDX
{
	protected:
		D3DDISPLAYMODE				m_displayMode;		/**< ディスプレイモード			*/
		KsInt32					m_modeNumber;		/**< モードリストの何番目か		*/
		static KsInt32				m_modeCount;		/**< 設定できるビデオモード数	*/

	public:
		/**
		 * コンストラクタ
		 */
									KsVideoModeDX();

		/**
		 * コピーコンストラクタ
		 */
									KsVideoModeDX( const KsVideoModeDX& refKsVideoMode );

		/**
		 * コピーコンストラクタ
		 */
									KsVideoModeDX( D3DDISPLAYMODE displayMode );

		/**
		 * デストラクタ
		 */
		virtual					~KsVideoModeDX() { --m_modeCount; }

		/**
		 * 画面幅を取得
		 * @return					画面幅
		 */
		KsUInt32					getWidth() const { return m_displayMode.Width; }

		/**
		 * 画面高さを取得
		 * @return					画面高さ
		 */
		KsUInt32					getHeight() const { return m_displayMode.Height; }

		/**
		 * リフレッシュレート(Hz)を取得する
		 * @return					リフレッシュレート(Hz)
		 */
		KsUInt32					getRefreshRate() const { return m_displayMode.RefreshRate; }

		/**
		 * カラー深度(何ビットカラーか)を取得する
		 * @return					カラー深度
		 */
		KsUInt32					getColorDepth() const;

		/**
		 * ディスプレイのフォーマットを取得する
		 * @return					ディスプレイのフォーマット
		 */
		D3DFORMAT					getFormat() const { return m_displayMode.Format; }

		/**
		 * ディスプレイモードを取得する
		 * @return					ディスプレイモード
		 */
		D3DDISPLAYMODE				getDisplayMode() const { return m_displayMode; }

		/**
		 * リフレッシュレート(Hz)をセットする
		 * @param		rate		リフレッシュレート(Hz)
		 */
		void						setRefreshRate( KsUInt32 rate ) { m_displayMode.RefreshRate = rate; } 
		
		/**
		 * ディスプレイモードの情報を取得する
		 * @return					ディスプレイモードの情報
		 */
		KsString					getDisplayModeInfo();
};


#endif /* __KSVIDEOMODEDX_H__ */



