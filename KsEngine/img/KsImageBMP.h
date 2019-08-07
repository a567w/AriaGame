/************************************************************************************************/
/** 
 * @file		KsImageBMP.h
 * @brief		イメージ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSIMAGEBMP_H__
#define __KSIMAGEBMP_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsType.h"
#include "KsImage.h"
#include "KsFile.h"
#include <pshpack2.h>		// 2バイトパック用に読み込む
/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
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

	KsUInt16					bfType;				/**< ファイルのタイプ(BM)			*/
	KsUInt32					bfSize;				/**< ファイルサイズ					*/
	KsUInt16					bfReserved1;		/**< 予備枠							*/
	KsUInt16					bfReserved2;		/**< 予備枠							*/
	KsUInt32					bfOffBits;			/**< オフセットアドレス				*/

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
	KsUInt32				biSize;				/**< この構造体のサイズ					*/
	KsInt32					biWidth;			/**< 画像の横幅(ドット数)				*/
	KsInt32					biHeight;			/**< 画像の縦幅(ドット数)				*/
	KsUInt16				biPlanes;			/**< 必ず1を入力						*/
	KsUInt16				biBitCount;			/**< 色数(ビット単位)					*/
	KsUInt32				biCompression;		/**< 圧縮の種類							*/
	KsUInt32				biSizeImage;		/**< イメージのサイズ					*/
	KsInt32					biXPelsPerMeter;	/**< 水平解像度							*/
	KsInt32					biYPelsPerMeter;	/**< 垂直解像度							*/
	KsUInt32				biClrUsed;			/**< 使用するカラーインデックス数		*/
	KsUInt32				biClrImportant;		/**< カラーインデックス数				*/

}KS_BITMAP_INFOHEADER; 

/************************************************************************************************/
/**
 * ビットマップヘッダ
 */
/************************************************************************************************/
typedef struct _KS_BITMAP_HEADER
{
	KS_BITMAP_FILEHEADER		bmfh;				/**< BMPファイルヘッダー				*/
	KS_BITMAP_INFOHEADER		bmih;				/**< BMP情報ヘッダー					*/

}KS_BITMAP_HEADER;

/************************************************************************************************/
/**
 * BMPファイルかをチェックする
 * @param		pFileName		ファイル名
 * @retval		ksTRUE			成功
 * @retval		ksFALSE			失敗
 */
/************************************************************************************************/
extern KsBool KsIsFileExtensionBMP( const KsChar* pFileName );

#if 0
/************************************************************************************************/
/**
 * BMP読み込み
 * @param		pFile			ファイル
 * @return						イメージデータ
 *								失敗したときはNULLを返す
 */
/************************************************************************************************/
extern KsImage* KsLoadImageBMP( KsFileObject* pFile );

/************************************************************************************************/
/**
 * BMP読み込み
 * @param		pFileName		ファイル名
 * @return						イメージデータ
 *								失敗したときはNULLを返す
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

	pixelBytes = ( depth + 7 )/8;					/* 1ピクセルのバイト数	*/
	lineBytes  = ( ( width * depth + 31 )/32 ) * 4;	/* 1ラインのバイト数		*/
	imageSize  = lineBytes * height;
	offBits    = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + numTable*sizeof(RGBQUAD);
	fileSize   = offBits + imageSize;
	widthBytes = width * pixelBytes;

	img = new KsByte[ imageSize ];

	if( !img ){
		return ksFALSE;
	}

	/* データをセットする */
	for( KsInt32 j=0; j<height; j++ )
	{
		/* イメージデータを上下入れ替え */
		KsByte* pData = &img[ ( height - j -1 )*lineBytes ];
		
		for( KsInt32 i=0; i<lineBytes; i++ )
		{
			if( i < widthBytes ){
				*( pData++ ) = pImage->m_pData[ idx++ ];
			}
		}
		/* RGB から BGRに,変換する */
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

	/* ビットマップファイルヘッダ */
	bf.bfType          = 0x4D42;
	bf.bfSize          = fileSize;
	bf.bfReserved1     = 0;
	bf.bfReserved2     = 0;
	bf.bfOffBits       = offBits;
	/* ビットマップの情報ヘッダ */
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

	/* ファイルに書き込み */
	fwrite( &bf, 1, sizeof(BITMAPFILEHEADER), pFile );
	fwrite( &bi, 1, sizeof(BITMAPINFOHEADER), pFile );
	fwrite( img, 1, bi.biSizeImage,            pFile );

	/* 開放処理 */
	ksDELETEARRAY( img );
	
	return ksTRUE;
}

#endif

#endif		/* __KSIMAGEBMP_H__ */





