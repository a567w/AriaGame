/************************************************************************************************/
/** 
 * @file		KsDebugFontManager.h
 * @brief		デバック用フォント表示操作
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSDEBUGFONTMANAGER_H__
#define __KSDEBUGFONTMANAGER_H__

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
 * @class		KsDebugFontManager
 * @brief		デバック用フォントマネージャクラス
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
class ksENGINE_API KsDebugFontManager : public KsSingleton< KsDebugFontManager >
{
	public:
		/**
		 * シングルトンの参照を取得
		 * @return						シングルトンの参照
		 */
		static KsDebugFontManager&		getInstance();
		
		/**
		 * シングルトンのポインタを取得
		 * @return						シングルトンのポインタ
		 */
		static KsDebugFontManager*		getInstancePtr();

	public:
		/**
		 * コンストラクタ
		 * @param	pFullPath			フォントフルパス
		 */
										KsDebugFontManager( const KsChar* pFullPath );

		/**
		 * コンストラクタ
		 * @param	pTexture			フォントテクスチャ	
		 */
										KsDebugFontManager( KsTexture* pTexture );

		/**
		 * デストラクタ
		 */
										~KsDebugFontManager();

		/**
		 * デバック文字列を表示する
		 */
		void							print( KsInt32 x, KsInt32 y, const KsChar* format, ... );

		/**
		 * デバック文字列を表示する
		 */
		void							print( const KsChar* format, ... );

		/**
		 * デバック文字列を表示する
		 */
		void							flush();

	public:
		KsTexture*						getTexture() { return m_pTexture; }

	private:
		KsDebugFont						m_fontWork[ 256 ];	/**< */
		KsTexture*						m_pTexture;			/**< */
		KsInt32							m_count;			/**< */
		KsInt32							m_px;				/**< */
		KsInt32							m_py;				/**< */
		KsInt32							m_line;
};

#ifndef MASTER
	#define ksDEBUG_INIT( pTex )	if( !KsDebugFontManager::getInstancePtr() ){  new KsDebugFontManager( pTex ); }
	#define ksDEBUG_FLUSH()			if( KsDebugFontManager::getInstancePtr() ){  KsDebugFontManager::getInstance().flush(); }
	#define ksDEBUG_PRINT			KsDebugFontManager::getInstance().print
	#define ksDEBUG_TERM()			if( KsDebugFontManager::getInstancePtr() ) { delete KsDebugFontManager::getInstancePtr(); }
#else
	#define ksDEBUG_INIT( _pRS )	
	#define ksDEBUG_FLUSH()		
	#define ksDEBUG_PRINT			
	#define ksDEBUG_TERM()
#endif //#ifndef MASTER

#endif /* __KSDEBUGFONTMANAGER_H__ */
