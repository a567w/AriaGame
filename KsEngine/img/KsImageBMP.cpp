/************************************************************************************************/
/** 
 * @file		KsImageBMP.cpp
 * @brief		イメージ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsImageBMP.h"
/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/* 拡張子のチェック */
/************************************************************************************************/
KsBool KsIsFileExtensionBMP( const KsChar* pFileName )
{
	/* 拡張子が bmp or BMP かをチェックする */
	if( strstr( pFileName, ".bmp" ) ){
		return ksTRUE;
	}

	return ( strstr( pFileName, ".BMP" ) != 0 );
}

#if 0
/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
KsImage* KsLoadImageBMP( KsFileObject* pFile )
{
	/* BMPの読み込み */
	KS_BITMAP_HEADER		header;
	KsImage*				pImage       = NULL;
	KsInt32*				pPaletteData = NULL;
	KsByte*					pData        = NULL;
	KsInt32				pitch        = 0;
	KsInt32				line         = 0;

	/* 先頭に移動 */
	pFile->seek( 0, ksSEEK_SET );

	/* ヘッダーを読み込む */
	pFile->read( &header, sizeof(KS_BITMAP_HEADER) );

	/* BMかのチェック */
	if( ( header.bmfh.bfType != ksMAKE_WORD( 'B', 'M' ) ) && ( header.bmfh.bfType != ksMAKE_WORD( 'M', 'B' ) ) )
	{
		//( "ビットマップ画像ではありません。\n" );
		return NULL;
	}

	/* 圧縮がかかっているBMPはサポート外 */
	if( header.bmih.biCompression )
	{
		//( "ビットマップ画像にサーポート外の圧縮がかかっています。" );
		return NULL;
	}

	/* 4バイトバウンダリングあわせ */
	header.bmih.biSizeImage += ( 4 - ( header.bmih.biSizeImage & 3 ) );

	/* パレットが使われていたらパレットを読み込む */
	KsInt32		pos          = pFile->tell();
	KsInt32		paletteSize  = ( header.bmfh.bfOffBits - pos ) / 4;

	if( paletteSize ){
		pPaletteData = new KsInt32[ paletteSize ];
		pFile->read( pPaletteData, paletteSize * sizeof(KsInt32) );
	}

	if( !header.bmih.biSizeImage ){
		header.bmih.biSizeImage = pFile->getSize() - header.bmfh.bfOffBits;
	}

	/* イメージデータへ移動 */
	pFile->seek( 0, ksSEEK_SET );
	pFile->seek( header.bmfh.bfOffBits, ksSEEK_SET );

	if( header.bmih.biBitCount < 8 ){
		line  = ( 8 * header.bmih.biWidth ) + header.bmih.biBitCount;
		line += ( 8 - ( line & 7 ) );
		line  = line / 8;
	}
	else{
		line  = header.bmih.biWidth * ( header.bmih.biBitCount / 8 );
	}

	pitch = ( 4 - ( line & 3 ) );

	/* データを取得 */
	pData = new KsByte[ header.bmih.biSizeImage ];
	pFile->read( pData, header.bmih.biSizeImage );

	/* イメージ生成 */
	switch( header.bmih.biBitCount )
	{
		case 1:
		{
			//pImage = new KsImage( ksIMAGE_RGB24, header.width, header.height );
			break;
		}
		case 4:
		{
			//pImage = new KsImage( ksIMAGE_RGB24, header.width, header.height );
			break;
		}
		case 8:
		{
			//pImage = new KsImage( ksIMAGE_RGB24, header.width, header.height );
			break;
		}
		case 16:
		{
			//pImage = new KsImage( ksIMAGE_RGB24, header.width, header.height );
			break;
		}
		case 24:
		{
			pImage = new KsImage( ksIMAGE_A8R8G8B8, header.bmih.biWidth, header.bmih.biHeight );

			for( KsUInt32 i=0; i<header.bmih.biSizeImage/3; i++ )
			{
				if( ( pData[ i*3 ] == 0x00 ) && ( pData[ i*3+1 ] == 0xff ) && ( pData[ i*3+2 ] == 0x00 ) )
				{
					pImage->m_pData[ i*4+0 ] = 0;
					pImage->m_pData[ i*4+1 ] = 0;
					pImage->m_pData[ i*4+2 ] = 0;
					pImage->m_pData[ i*4+3 ] = 0;
				}
				else
				{
					pImage->m_pData[ i*4+0 ] = pData[ i*3+2 ];
					pImage->m_pData[ i*4+1 ] = pData[ i*3+1 ];
					pImage->m_pData[ i*4+2 ] = pData[ i*3+0 ];
					pImage->m_pData[ i*4+3 ] = 0xff;
				}
			}
			break;
		}

		default: break;
	};

	ksDELETEARRAY( pPaletteData );
	ksDELETEARRAY( pData );

	return pImage;
}
/************************************************************************************************/
/**
 * BMP読み込み
 * @param		pFileName		ファイル名
 * @return						イメージデータ
 *								失敗したときはNULLを返す
 */
/************************************************************************************************/
KsImage* KsLoadImageBMP( const KsChar* pFileName )
{
	KsFile		file;
	KsImage*	pImage;

	file.open( pFileName, ksREAD | ksBINARY );
	pImage = KsLoadImageBMP( &file );
	file.close();

	return pImage;
}
#endif


