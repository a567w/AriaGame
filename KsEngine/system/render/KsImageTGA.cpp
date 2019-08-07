/************************************************************************************************/
/** 
 * @file		KsImageTGA.cpp
 * @brief		イメージ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsImageTGA.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/*
 * 拡張子のチェック
 */
/************************************************************************************************/
KsBool KsIsFileExtensionTGA( const KsChar* pFileName )
{
	/* 拡張子が tga or TGA かをチェックする */
	if( strstr( pFileName, ".tga" ) ){
		return ksTRUE;
	}

	return ( strstr( pFileName, ".TGA" ) != 0 );
}

/************************************************************************************************/
/*
 * 圧縮を展開する
 */
/************************************************************************************************/
static KsByte* KsLoadCommpressTGA( KsFileObject* pFile, KS_TGA_HEADER* pHeader )
{
	KsInt32		curByte = 0;
	KsInt32		depth   = 0;
	KsInt32		size    = 0;
	KsByte*		pData   = NULL;

	depth = pHeader->pixelDepth / 8;
	size  = pHeader->height * pHeader->width * depth;
	pData = new KsByte[ size ];

	while( curByte < size )
	{
		KsByte	chunkHeader = 0;

		pFile->read( &chunkHeader, sizeof(KsByte) );
		
		if( chunkHeader < 128 )
		{
			chunkHeader++;

			pFile->read( &pData[ curByte ], depth * chunkHeader );
			curByte += depth * chunkHeader;
		}
		else
		{
			chunkHeader -= 127;
			pFile->read( &pData[ curByte ], depth );

			for( KsInt32 i=0; i<chunkHeader; i++ )
			{
				for( KsInt32 j=0; j<depth; j++ ){
					pData[ curByte + j ] = pData[ curByte + j - depth ];
				}
				curByte += depth;
			}
		}
	}

	return pData;
}
#if 0
/************************************************************************************************/
/*
 * パックされたデータから読み込むときもあるのでFILE*ではだめ
 * KsFileを使用する
 * pack->txd, pack->tga, txd, tga
 */
/************************************************************************************************/
KsImage* KsLoadImageTGA( KsFileObject* pFile )
{
	/* TGAの読み込み */
	KsByte*			pData  = NULL;
	KsImage*		pImage = NULL;
	KsInt32			depth  = 0;
	KsInt32			size   = 0;
	KS_TGA_HEADER	header;

	/* 先頭に移動 */
	pFile->seek( 0, ksSEEK_SET );

	/* ヘッダーを読み込む */
	pFile->read( &header, sizeof(KS_TGA_HEADER) );

	if( header.idLength ){
		pFile->seek( header.idLength, ksSEEK_CUR );
	}

	/* パレットチェック */
	if( header.colorMapType != 0 ){
		pFile->seek( ( header.palletBits / 8 * header.palletMax ), ksSEEK_CUR );
	}

	depth = header.pixelDepth / 8;
	size  = header.height * header.width * depth;

	/* 圧縮がかかっているかのチェック */
	switch( header.imageType )
	{
		case 2:
		{
			/* 無圧縮 */
			pData = new KsByte[ size ];
		  	pFile->read( pData, size );
			/* RGBをなおして上下入れ替え */
			KsImageFlip_V( pData, header.width, header.height, header.pixelDepth );
			KsImageSwapRGB( pData, header.width, header.height, header.pixelDepth );
			break;
		}
		case 10:
		{
			/* 圧縮あり */
			pData = KsLoadCommpressTGA( pFile, &header ); 
			break;
		}
		default:
		{
			/* エラー */
			return NULL; 
		}
	}

	/* カラー深度 */
	switch( depth )
	{
		case 1:
		{
			break;
		}
		case 2:
		{
			// 16 bit image
			break;
		}
		case 3:
		{
			break;
		}
		case 4:
		{
			break;
		}
		default: break;
	}

	/* イメージを生成(実際は、24bit以外の場合も設定する) */
	pImage = new KsImage();

	pImage->m_pData  = pData;
	pImage->m_height = header.height;
	pImage->m_width  = header.width;
	pImage->m_format = ksIMAGE_R8G8B8;

	return pImage;
}
#endif



