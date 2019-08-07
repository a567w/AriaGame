/************************************************************************************************/
/** 
 * @file		KsFont.cpp
 * @brief		��������
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsFont.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
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

	/* �t�H���g�ݒ� */
	LOGFONT		logFont;
	logFont.lfHeight         = 16;							/* �t�H���g����				*/
	logFont.lfWidth          = 0;							/* �t�H���g��(0���Ǝ����ݒ�)	*/
	logFont.lfEscapement     = 0;							/* �����̕�����X���Ƃ̊p�x	*/
	logFont.lfOrientation    = 0;							/* �x�[�X���C����X���Ƃ̊p�x	*/
	logFont.lfWeight         = FW_NORMAL;					/* �t�H���g����				*/
	//logFont.lfWeight         = FW_SEMIBOLD;					/* �t�H���g����				*/
	logFont.lfItalic         = FALSE;						/* �C�^���b�N�̎w��			*/
	logFont.lfUnderline      = FALSE;						/* �����t���w��				*/
	logFont.lfStrikeOut      = FALSE;						/* �ł��������t���w��			*/
	logFont.lfCharSet        = SHIFTJIS_CHARSET;			/* �L�����N�^�Z�b�g			*/
	logFont.lfOutPrecision   = OUT_DEFAULT_PRECIS;			/* �o�͐��x					*/
	logFont.lfClipPrecision  = CLIP_DEFAULT_PRECIS;			/* �N���b�s���O�̐��x			*/
	logFont.lfQuality        = DEFAULT_QUALITY;				/* �o�͕i��					*/
	//logFont.lfQuality        = ANTIALIASED_QUALITY;			/* �o�͕i��(NT,2000,XP����)	*/
	logFont.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;	/* �s�b�`�ƃt�@�~��			*/
	lstrcpy( logFont.lfFaceName, "�l�r �S�V�b�N" );			/* �t�H���g���				*/
	//lstrcpy( logFont.lfFaceName, "�l�r ����" );			/* �t�H���g���				*/

	/* �u���V�ݒ� */
	LOGBRUSH		logBrush;
	logBrush.lbStyle = BS_SOLID;
	logBrush.lbColor = RGB( 0, 255, 0 );
	logBrush.lbHatch = 0;

	/* �y���ݒ� */
	LOGPEN			logPen;
	logPen.lopnStyle   = PS_NULL;
	logPen.lopnWidth.x = 1;
	logPen.lopnWidth.y = 0;
    logPen.lopnColor   = RGB( 0, 255, 0 );

	/* ���� */
	m_hFont  = CreateFontIndirect( &logFont );
	m_hBrush = CreateBrushIndirect( &logBrush );
	m_hPen   = CreatePenIndirect( &logPen );

	/* �e�L�X�g�J���[ */
	m_textColor = RGB( 255, 255, 255 );
	/* �o�b�N�J���[ */
	m_backColor = RGB( 255,  255,   0 );
	/* �����̃J���[ */
	m_borderColor = RGB( 255, 255, 255 );
}
/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
KsBool	KsFont::create( ksPIXEL_FORMAT format, KsInt32 width, KsInt32 height )
{
	/* DIB�������� */
	KsDIB::create( format, width, height );

	/* �f�t�H���g�ݒ� */
	//ConfigDefault();

	clear();

	return ksTRUE;
}

void KsFont::setTextColor( COLORREF color )
{
	/* �e�L�X�g�J���[ */
	m_textColor = RGB( 255, 255, 255 );
}
void KsFont::setBackColor( COLORREF color )
{
	/* �o�b�N�J���[ */
	m_backColor = RGB( 255,  255,   0 );
}
void KsFont::setBorderColor( COLORREF color )
{
	/* �����̃J���[ */
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

	/* �T�C�Y�`�F�b�N���� */
	TextOut( m_hDC, x, y, buffer, len );
	
	SelectObject( m_hDC, hFontOld );
	SelectObject( m_hDC, hBrushOld );
	SelectObject( m_hDC, hPenOld );
}
#endif


