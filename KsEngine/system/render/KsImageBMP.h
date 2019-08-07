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
/*                                 << インクルード >>                                            */
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

	KsUInt16					bfType;				/**< ファイルのタイプ(BM)				*/
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
	KsUInt32					biSize;				/**< この構造体のサイズ				*/
	KsInt32					biWidth;			/**< 画像の横幅(ドット数)				*/
	KsInt32					biHeight;			/**< 画像の縦幅(ドット数)				*/
	KsUInt16					biPlanes;			/**< 必ず1を入力						*/
	KsUInt16					biBitCount;			/**< 色数(ビット単位)				*/
	KsUInt32					biCompression;		/**< 圧縮の種類						*/
	KsUInt32					biSizeImage;		/**< イメージのサイズ					*/
	KsInt32					biXPelsPerMeter;	/**< 水平解像度						*/
	KsInt32					biYPelsPerMeter;	/**< 垂直解像度						*/
	KsUInt32					biClrUsed;			/**< 使用するカラーインデックス数		*/
	KsUInt32					biClrImportant;		/**< カラーインデックス数				*/

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
#endif

#endif		/* __KSIMAGEBMP_H__ */





