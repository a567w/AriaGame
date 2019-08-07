/************************************************************************************************/
/** 
 * @file		KsDIB.cpp
 * @brief		DIB
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsDIB.h"
#include "KsCommon.h"

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
KsDIB::KsDIB()
{
	m_size       = 0;
	m_pitch      = 0;
	m_hDC        = NULL;
	m_hBitmap    = NULL;
	m_hBitmapOld = NULL;
}
/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
KsDIB::~KsDIB()
{
	/* DIB�̏ꍇ�����́A�E�C���h�E�Y�Ŋm�ۂ��Ă���̂ł����ŊJ�����Ȃ��Ă�,	*/
	/* �����Ȃ�(����Image�ŊJ�������2�d�J�����Ă��܂�)					*/
	destroy();
}
/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
void KsDIB::destroy()
{
	if( m_hDC )
	{
		::SelectObject( m_hDC,m_hBitmapOld );
		::DeleteDC( m_hDC );
		::DeleteObject( m_hBitmap );

		m_pixelFormat = ksPIXEL_UNKNOWN;
		m_width       = 0;
		m_height      = 0;
		m_pData       = NULL;
		m_size        = 0;
		m_pitch       = 0;
		m_hDC         = NULL;
		m_hBitmap     = NULL;
		m_hBitmapOld  = NULL;
	}
}
/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
KsBool	KsDIB::create( ksPIXEL_FORMAT format, KsInt32 width, KsInt32 height )
{
	BITMAPV4HEADER		header;
	HDC					hDC;
	HBITMAP				hBitmap;
	HBITMAP				hBitmapOld;
	BYTE*				pPixel;
	KsInt32			pitch;
	KsInt32			depth;

	/* 0�N���A */
	KsZeroMemory( &header, sizeof(BITMAPV4HEADER) );

	switch( format )
	{
		case ksPIXEL_X1R5G5B5:
		{
			header.bV4AlphaMask = 0x00000000;
			header.bV4RedMask   = 0x00007c00;
			header.bV4GreenMask = 0x000003e0;
			header.bV4BlueMask  = 0x0000001f;
			depth               = 16;
			break;
		}
		case ksPIXEL_A1R5G5B5:
		{
			header.bV4AlphaMask = 0x00008000;
			header.bV4RedMask   = 0x00007c00;
			header.bV4GreenMask = 0x000003e0;
			header.bV4BlueMask  = 0x0000001f;
			depth               = 16;
			break;
		}
		case ksPIXEL_A4R4G4B4:
		{
			header.bV4AlphaMask = 0x0000f000;
			header.bV4RedMask   = 0x00000f00;
			header.bV4GreenMask = 0x000000f0;
			header.bV4BlueMask  = 0x0000000f;
			depth               = 16;
			break;
		}
		case ksPIXEL_R5G6B5:
		{
			header.bV4AlphaMask = 0x00000000;
			header.bV4RedMask   = 0x0000f800;
			header.bV4GreenMask = 0x000007e0;
			header.bV4BlueMask  = 0x0000001f;
			depth               = 16;
			break;
		}
		case ksPIXEL_X8R8G8B8:
		{
			header.bV4AlphaMask = 0x00000000;
			header.bV4RedMask   = 0x00ff0000;
			header.bV4GreenMask = 0x0000ff00;
			header.bV4BlueMask  = 0x000000ff;
			depth               = 32;
			break;
		}
		case ksPIXEL_A8R8G8B8:
		{
			header.bV4AlphaMask = 0xff000000;
			header.bV4RedMask   = 0x00ff0000;
			header.bV4GreenMask = 0x0000ff00;
			header.bV4BlueMask  = 0x000000ff;
			depth               = 32;
			break;
		}
		default: break;
	}

	/* ���ݒ� */
	pitch                   = (width * depth/8 + 3)/4*4;	/* �s�b�`				*/
	header.bV4Size          = sizeof(BITMAPV4HEADER);		/* �\���̃T�C�Y			*/
	header.bV4Width         = width;						/* ��					*/
	header.bV4Height        = -( height + 1 );				/* ����					*/
	header.bV4BitCount      = depth;						/* �[��					*/
	header.bV4SizeImage     = height * pitch;				/* �C���[�W�T�C�Y		*/
	header.bV4Planes        = 1;							/* �v���[��1�Œ�			*/
	header.bV4V4Compression = BI_BITFIELDS;					/* �r�b�g�t�B�[���h�g�p	*/
	
	/* DIB���� */
	hBitmap = ::CreateDIBSection( NULL, (BITMAPINFO*)&header, DIB_RGB_COLORS, (void**)&pPixel, 0, 0 );

	/*�r�b�g�}�b�v�C���[�W�̃N���A */
	ZeroMemory( pPixel, header.bV4SizeImage );
	
	/* �������[DC�쐬 */
	hDC = ::CreateCompatibleDC( NULL );
	
	/* �������[DC��DIB�����蓖�� */
	hBitmapOld = (HBITMAP)::SelectObject( hDC, hBitmap );
	
	/* �Ƃ肠�����J�� */
	destroy();

	/* �ۑ� */
	m_hDC         = hDC;
	m_hBitmap     = hBitmap;
	m_hBitmapOld  = hBitmapOld;
	m_size        = header.bV4SizeImage;
	m_width       = width;
	m_height      = height;
	m_pixelFormat = format;
	m_pData       = pPixel;
	m_pitch       = pitch;

	return ksTRUE;
}
/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
void KsDIB::clear( COLORREF color )
{
	/* �u���V�ݒ� */
	LOGBRUSH		logBrush;

	logBrush.lbStyle = BS_SOLID;
	logBrush.lbColor = color;
	logBrush.lbHatch = 0;

	m_clearBrush = ::CreateBrushIndirect( &logBrush );

	RECT	rect = { 0, 0, m_width, m_height };
	::FillRect( m_hDC, &rect, m_clearBrush );

	::DeleteObject( m_clearBrush );
}


