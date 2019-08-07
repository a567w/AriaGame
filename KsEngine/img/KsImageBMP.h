/************************************************************************************************/
/** 
 * @file		KsImageBMP.h
 * @brief		�C���[�W
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSIMAGEBMP_H__
#define __KSIMAGEBMP_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsType.h"
#include "KsImage.h"
#include "KsFile.h"
#include <pshpack2.h>		// 2�o�C�g�p�b�N�p�ɓǂݍ���
/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * << bfType >>
 *	BM - Windows 3.1x, 95, NT, 98, 2000, ME, XP
 *	BA - OS/2 Bitmap Array
 *	CI - OS/2 Color Icon
 *	CP - OS/2 Color Pointer
 *	IC - OS/2 Icon
 *	PT - OS/2 Pointer
 */
/************************************************************************************************/
typedef struct _KS_BITMAP_FILEHEADER
{

	KsUInt16					bfType;				/**< �t�@�C���̃^�C�v(BM)			*/
	KsUInt32					bfSize;				/**< �t�@�C���T�C�Y					*/
	KsUInt16					bfReserved1;		/**< �\���g							*/
	KsUInt16					bfReserved2;		/**< �\���g							*/
	KsUInt32					bfOffBits;			/**< �I�t�Z�b�g�A�h���X				*/

}KS_BITMAP_FILEHEADER; 

/************************************************************************************************/
/**
 * << biSize >>
 * should be 28h for windows bitmaps or
 * 0Ch for OS/2 1.x or F0h for OS/2 2.x
 *
 * << biBitCount >>
 * 1: Monochrome bitmap
 * 4: 16 color bitmap
 * 8: 256 color bitmap
 * 16: 16bit (high color) bitmap
 * 24: 24bit (true color) bitmap
 * 32: 32bit (true color) bitmap
 *
 * << biCompression >>
 * 0: none (Also identified by BI_RGB)
 * 1: RLE 8-bit / pixel (Also identified by BI_RLE4)
 * 2: RLE 4-bit / pixel (Also identified by BI_RLE8)
 * 3: Bitfields  (Also identified by BI_BITFIELDS)
 */
/************************************************************************************************/
typedef struct _KS_BITMAP_INFOHEADER
{
	KsUInt32				biSize;				/**< ���̍\���̂̃T�C�Y					*/
	KsInt32					biWidth;			/**< �摜�̉���(�h�b�g��)				*/
	KsInt32					biHeight;			/**< �摜�̏c��(�h�b�g��)				*/
	KsUInt16				biPlanes;			/**< �K��1�����						*/
	KsUInt16				biBitCount;			/**< �F��(�r�b�g�P��)					*/
	KsUInt32				biCompression;		/**< ���k�̎��							*/
	KsUInt32				biSizeImage;		/**< �C���[�W�̃T�C�Y					*/
	KsInt32					biXPelsPerMeter;	/**< �����𑜓x							*/
	KsInt32					biYPelsPerMeter;	/**< �����𑜓x							*/
	KsUInt32				biClrUsed;			/**< �g�p����J���[�C���f�b�N�X��		*/
	KsUInt32				biClrImportant;		/**< �J���[�C���f�b�N�X��				*/

}KS_BITMAP_INFOHEADER; 

/************************************************************************************************/
/**
 * �r�b�g�}�b�v�w�b�_
 */
/************************************************************************************************/
typedef struct _KS_BITMAP_HEADER
{
	KS_BITMAP_FILEHEADER		bmfh;				/**< BMP�t�@�C���w�b�_�[				*/
	KS_BITMAP_INFOHEADER		bmih;				/**< BMP���w�b�_�[					*/

}KS_BITMAP_HEADER;

/************************************************************************************************/
/**
 * BMP�t�@�C�������`�F�b�N����
 * @param		pFileName		�t�@�C����
 * @retval		ksTRUE			����
 * @retval		ksFALSE			���s
 */
/************************************************************************************************/
extern KsBool KsIsFileExtensionBMP( const KsChar* pFileName );

#if 0
/************************************************************************************************/
/**
 * BMP�ǂݍ���
 * @param		pFile			�t�@�C��
 * @return						�C���[�W�f�[�^
 *								���s�����Ƃ���NULL��Ԃ�
 */
/************************************************************************************************/
extern KsImage* KsLoadImageBMP( KsFileObject* pFile );

/************************************************************************************************/
/**
 * BMP�ǂݍ���
 * @param		pFileName		�t�@�C����
 * @return						�C���[�W�f�[�^
 *								���s�����Ƃ���NULL��Ԃ�
 */
/************************************************************************************************/
extern KsImage* KsLoadImageBMP( const KsChar* pFileName );


/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
extern KsBool KsSaveImage( FILE* pFile, KsImage* pImage );

KsBool KsSaveImage( FILE* pFile, KsImage* pImage )
{
	BITMAPFILEHEADER	bf;
	BITMAPINFOHEADER	bi;
	KsUInt32			numTable   = 0;
	KsUInt32			fileSize   = 0;
	KsUInt32			imageSize  = 0;
	KsUInt32			offBits    = 0;
	KsInt32			lineBytes  = 0;
	KsInt32			count      = 0;
	KsInt32			pixelBytes = 0;
	KsInt32			widthBytes = 0;
	KsInt32			idx        = 0;
	KsInt32			width      = pImage->m_width;
	KsInt32			height     = pImage->m_height;
	KsInt32			depth      = 32;
	KsByte*				img        = NULL;

	memset( &bf, 0, sizeof(BITMAPFILEHEADER) );
	memset( &bi, 0, sizeof(BITMAPINFOHEADER) );

	pixelBytes = ( depth + 7 )/8;					/* 1�s�N�Z���̃o�C�g��	*/
	lineBytes  = ( ( width * depth + 31 )/32 ) * 4;	/* 1���C���̃o�C�g��		*/
	imageSize  = lineBytes * height;
	offBits    = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + numTable*sizeof(RGBQUAD);
	fileSize   = offBits + imageSize;
	widthBytes = width * pixelBytes;

	img = new KsByte[ imageSize ];

	if( !img ){
		return ksFALSE;
	}

	/* �f�[�^���Z�b�g���� */
	for( KsInt32 j=0; j<height; j++ )
	{
		/* �C���[�W�f�[�^���㉺����ւ� */
		KsByte* pData = &img[ ( height - j -1 )*lineBytes ];
		
		for( KsInt32 i=0; i<lineBytes; i++ )
		{
			if( i < widthBytes ){
				*( pData++ ) = pImage->m_pData[ idx++ ];
			}
		}
		/* RGB ���� BGR��,�ϊ����� */
		pData = &img[ ( height - j -1 )*lineBytes ];

		for( KsInt32 ct=0; ct<width; ct++ ){
			KsByte	r = *( pData + 0 );
			KsByte	g = *( pData + 1 );
			KsByte	b = *( pData + 2 );
			*( pData++ ) = b;
			*( pData++ ) = g;
			*( pData++ ) = r;
			pData++;
		}
	}

	/* �r�b�g�}�b�v�t�@�C���w�b�_ */
	bf.bfType          = 0x4D42;
	bf.bfSize          = fileSize;
	bf.bfReserved1     = 0;
	bf.bfReserved2     = 0;
	bf.bfOffBits       = offBits;
	/* �r�b�g�}�b�v�̏��w�b�_ */
	bi.biSize          = sizeof(BITMAPINFOHEADER);
	bi.biWidth         = width;
	bi.biHeight        = height;
	bi.biPlanes        = 1;
	bi.biBitCount      = 32;
	bi.biCompression   = BI_RGB;
	bi.biSizeImage     = imageSize;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed       = 0;
	bi.biClrImportant  = 0;

	/* �t�@�C���ɏ������� */
	fwrite( &bf, 1, sizeof(BITMAPFILEHEADER), pFile );
	fwrite( &bi, 1, sizeof(BITMAPINFOHEADER), pFile );
	fwrite( img, 1, bi.biSizeImage,            pFile );

	/* �J������ */
	ksDELETEARRAY( img );
	
	return ksTRUE;
}

#endif

#endif		/* __KSIMAGEBMP_H__ */





