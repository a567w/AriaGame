/************************************************************************************************/
/** 
 * @file		KsModule.h
 * @brief		モジュール
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSFONTDATA_H__
#define __KSFONTDATA_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsTexture;

/************************************************************************************************/
/**
 *  モジュールのインターフェースクラス
 *	@class		KsModule
 *	@brief		モジュールのインターフェース
 *	@since		2003/10/25
 *	@author		Tsukasa Kato
 */
/************************************************************************************************/
class ksENGINE_API KsFontData
{
	public:
		enum
		{
			ksCODE_ASCII_START	= 0x0000,
			ksCODE_ASCII_END	= 0x00FF,

			ksCODE_SJIS_A_START	= 0x8140,
			ksCODE_SJIS_A_END	= 0x9FFF,

			ksCODE_SJIS_B_START	= 0xE040,
			ksCODE_SJIS_B_END	= 0xEEFF,

			ksCODE_SJIS_C_START	= 0xF8A0,
			ksCODE_SJIS_C_END	= 0xFC4F,

			ksCODE_TABLE_SIZE	= (ksCODE_ASCII_END - ksCODE_ASCII_START) + (ksCODE_SJIS_A_END - ksCODE_SJIS_A_START) + (ksCODE_SJIS_B_END - ksCODE_SJIS_B_START) + (ksCODE_SJIS_C_END - ksCODE_SJIS_C_START),
		};

		struct KsHeader
		{
			KsChar				signature[ 4 ];
			KsUInt8				fontSize;
			KsUInt8				numSheet;
			KsUInt16			sheetWidth;
			KsUInt16			sheetHeight;
			KsUInt16			numFont;
			KsUInt16			fontTbl[ ksCODE_TABLE_SIZE ];
		};

		struct KsFontInfo
		{
			KsInt8				sheetNo;		///< シート番号
			KsInt8				leftSpace;		///< ABC幅
			KsInt8				fontWidth;		///< ABC幅
			KsInt8				rightSpace;		///< ABC幅
			KsInt16				x1;				///< UVデータ
			KsInt16				y1;				///< UVデータ
			KsInt16				x2;				///< UVデータ
			KsInt16				y2;				///< UVデータ
		};

	public:
		/**
		 * コンストラクタ
		 */
								KsFontData();
								KsFontData( KsFileObject& file );

		/**
		 * デストラクタ
		 */
		virtual					~KsFontData();

		KsBool					create( KsFileObject& file );
		void					destroy();
		void					addTexture( KsTexture* pTexture ){ m_vpTextures.push_back( pTexture ); }

		KsInt32					getHeight() const { return m_fontSize; }
		KsInt32					getFontSize() const { return m_fontSize; }
		KsReal					getFontSizeReal() const { return static_cast<KsReal>(m_fontSize); }
		KsInt32					getFontIndex( KsUInt16 code ) const { return m_fontTbl[ code ]; }
		const KsFontInfo*		getFontInfo( KsInt32 index ) { return &m_pFontInfo[ index ]; }
		KsTexture*				getFontTexture( KsInt32 index ) { return m_vpTextures[ index ]; }
		KsInt32					getSheetWidth() const { return m_sheetWidth; }
		KsInt32					getSheetHeight() const { return m_sheetHeight; }
		KsReal					getSheetWidthReal() const { return static_cast<KsReal>( m_sheetWidth ); }
		KsReal					getSheetHeightReal() const { return static_cast<KsReal>( m_sheetHeight ); }

		static KsUInt16			code2Index( KsUInt16 code );
		static KsBool			ismbblead( KsUInt8 c );
		static KsUInt16			getCharCode( KsUInt8* pStr );
		static KsInt32			getCharCode( KsUInt8* pStr, KsUInt16* pCode );

	protected:
		KsFontInfo*				m_pFontInfo;
		KsInt32					m_sheetWidth;	///< シート横幅
		KsInt32					m_sheetHeight;	///< シート縦幅
		KsInt32					m_numSheet;		///< シート数
		KsInt32					m_fontSize;		///< フォントサイズ
		KsInt32					m_numFont;		///< フォント数
		KsUInt16				m_fontTbl[ ksCODE_TABLE_SIZE ];
		KsArray<KsTexture*>		m_vpTextures;

		KsBool					m_bAlpha;		///< αチャンネルを使うか否か
		KsBool					m_bAntialias;	///< アンチエイリアスを使うか否か
};


#endif /* __KSFONTDATA_H__ */

