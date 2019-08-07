/************************************************************************************************/
/** 
 * @file		KsFont.cpp
 * @brief		文字操作
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsFont.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
KsFont::KsFont()
{
	m_hFont  = NULL;
	m_hBrush = NULL;
	m_hPen   = NULL;
}

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
KsFont::~KsFont()
{
	KsDIB::destroy();

	ksDELETEOBJECT( m_hFont );
	ksDELETEOBJECT( m_hBrush );
	ksDELETEOBJECT( m_hPen );
}

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
void KsFont::ConfigDefault()
{
	ksDELETEOBJECT( m_hFont );
	ksDELETEOBJECT( m_hBrush );
	ksDELETEOBJECT( m_hPen );

	/* フォント設定 */
	LOGFONT		logFont;
	logFont.lfHeight         = 16;							/* フォント高さ				*/
	logFont.lfWidth          = 0;							/* フォント幅(0だと自動設定)	*/
	logFont.lfEscapement     = 0;							/* 文字の方向とX軸との角度	*/
	logFont.lfOrientation    = 0;							/* ベースラインとX軸との角度	*/
	logFont.lfWeight         = FW_NORMAL;					/* フォント太さ				*/
	//logFont.lfWeight         = FW_SEMIBOLD;					/* フォント太さ				*/
	logFont.lfItalic         = FALSE;						/* イタリック体指定			*/
	logFont.lfUnderline      = FALSE;						/* 下線付き指定				*/
	logFont.lfStrikeOut      = FALSE;						/* 打ち消し線付き指定			*/
	logFont.lfCharSet        = SHIFTJIS_CHARSET;			/* キャラクタセット			*/
	logFont.lfOutPrecision   = OUT_DEFAULT_PRECIS;			/* 出力精度					*/
	logFont.lfClipPrecision  = CLIP_DEFAULT_PRECIS;			/* クリッピングの精度			*/
	logFont.lfQuality        = DEFAULT_QUALITY;				/* 出力品質					*/
	//logFont.lfQuality        = ANTIALIASED_QUALITY;			/* 出力品質(NT,2000,XPだけ)	*/
	logFont.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;	/* ピッチとファミリ			*/
	lstrcpy( logFont.lfFaceName, "ＭＳ ゴシック" );			/* フォント種類				*/
	//lstrcpy( logFont.lfFaceName, "ＭＳ 明朝" );			/* フォント種類				*/

	/* ブラシ設定 */
	LOGBRUSH		logBrush;
	logBrush.lbStyle = BS_SOLID;
	logBrush.lbColor = RGB( 0, 255, 0 );
	logBrush.lbHatch = 0;

	/* ペン設定 */
	LOGPEN			logPen;
	logPen.lopnStyle   = PS_NULL;
	logPen.lopnWidth.x = 1;
	logPen.lopnWidth.y = 0;
    logPen.lopnColor   = RGB( 0, 255, 0 );

	/* 生成 */
	m_hFont  = CreateFontIndirect( &logFont );
	m_hBrush = CreateBrushIndirect( &logBrush );
	m_hPen   = CreatePenIndirect( &logPen );

	/* テキストカラー */
	m_textColor = RGB( 255, 255, 255 );
	/* バックカラー */
	m_backColor = RGB( 255,  255,   0 );
	/* 縁取りのカラー */
	m_borderColor = RGB( 255, 255, 255 );
}
/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
KsBool	KsFont::create( ksPIXEL_FORMAT format, KsInt32 width, KsInt32 height )
{
	/* DIB生成する */
	KsDIB::create( format, width, height );

	/* デフォルト設定 */
	//ConfigDefault();

	clear();

	return ksTRUE;
}

void KsFont::setTextColor( COLORREF color )
{
	/* テキストカラー */
	m_textColor = RGB( 255, 255, 255 );
}
void KsFont::setBackColor( COLORREF color )
{
	/* バックカラー */
	m_backColor = RGB( 255,  255,   0 );
}
void KsFont::setBorderColor( COLORREF color )
{
	/* 縁取りのカラー */
	m_borderColor = RGB( 255, 255, 255 );
}

#if 0
/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
void KsFont::Printf( KsInt32 x, KsInt32 y, const KsChar* format, ... )
{
	KsChar		buffer[ 1024 ];
	va_list		list;
	
	va_start( list, format );
	vsprintf( buffer, format, list );	
	va_end( list );

	HFONT		hFontOld;
	HBRUSH		hBrushOld;
	HPEN		hPenOld;

	hFontOld  =  (HFONT)SelectObject( m_hDC, m_hFont );
	hBrushOld = (HBRUSH)SelectObject( m_hDC, m_hBrush );
	hPenOld   =   (HPEN)SelectObject( m_hDC, m_hPen );

	SetBkMode( m_hDC, TRANSPARENT );
	//SetBkColor( m_hDC,  m_backColor );
	SetTextColor( m_hDC, m_textColor );
	
	KsInt32	len = (KsInt32)strlen( buffer );

	/* サイズチェックする */
	TextOut( m_hDC, x, y, buffer, len );
	
	SelectObject( m_hDC, hFontOld );
	SelectObject( m_hDC, hBrushOld );
	SelectObject( m_hDC, hPenOld );
}
#endif


