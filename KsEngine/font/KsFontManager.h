/************************************************************************************************/
/** 
 * @file		KsFontManager.h
 * @brief		
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSFONTMANAGER_H__
#define __KSFONTMANAGER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsType.h"
#include "KsArray.h"
#include "KsFont.h"
#include "KsSingleton.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsRenderSystem;

/************************************************************************************************/
/**
 * @class		KsFontManager
 * @brief		
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsFontManager : public KsSingleton< KsFontManager >
{
	public:
		/**
		 * コンストラクタ
		 */
											KsFontManager( KsRenderSystem* pRenderSystem );

		/**
		 * デストラクタ
		 */
		virtual							~KsFontManager();

		/**
		 * フォント生成
		 * @param		pFileName			ファイル名
		 * @return							フォントデータ
		 */
		virtual KsFont*					createFromXml( const KsChar* pFileName );

		/**
		 * フォント削除
		 */
		//virtual KsBool					destroyFont( KsFont* pFont );

		/**
		 * フォントを追加する。
		 * @param		pFont				フォントデータ
		 * @return							インデックス
		 */
		KsUInt32							addFont( KsFont* pFont ) { m_vpFonts.push_back(pFont); return m_vpFonts.size(); }

		/**
		 * フォントデータを取得
		 * @param		index				インデックス
		 * @return							フォントデータ
		 */
		KsFont*								getFont( KsUInt32 index=0 ) { return m_vpFonts[ index ]; }

		/**
		 * シングルトンの参照を取得
		 * @return							シングルトンの参照
		 */
		static KsFontManager&				getInstance();
		
		/**
		 * シングルトンのポインタを取得
		 * @return							シングルトンのポインタ
		 */
		static KsFontManager*				getInstancePtr();

	protected:
		KsRenderSystem*						m_pRenderSystem;
		KsArray< KsFont* >					m_vpFonts;
};

#endif		/* __KSFONTMANAGER_H__ */



