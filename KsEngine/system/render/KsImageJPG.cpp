/************************************************************************************************/
/** 
 * @file		KsImageJPG.cpp
 * @brief		
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsImageJPG.h"
#include "./jpeg/jpeglib.h"
#include "./jpeg/jinclude.h"
#include "./jpeg/jerror.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
typedef struct
{
  struct jpeg_source_mgr	pub;
  KsFileObject*				infile;
  JOCTET*					buffer;
}my_source_mgr;

/************************************************************************************************/
/*
 * 初期化
 */
/************************************************************************************************/
void KS_init_source( j_decompress_ptr cinfo )
{
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
boolean KS_fill_input_buffer( j_decompress_ptr cinfo )
{
	return TRUE;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KS_skip_input_data( j_decompress_ptr cinfo, long num_bytes )
{
	my_source_mgr*	src = (my_source_mgr*) cinfo->src;

	if( num_bytes > 0 )
	{
		src->pub.next_input_byte += (size_t) num_bytes;
		src->pub.bytes_in_buffer -= (size_t) num_bytes;
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KS_term_source( j_decompress_ptr cinfo )
{
	ksDELETE( cinfo->src );
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KS_jpeg_stdio_src( j_decompress_ptr cinfo, KsFileObject* infile )
{
	/* 面倒なので一気に読み込む */
	KsByte*		pBuffer = new KsByte[ infile->getSize() ];
	infile->read( pBuffer, infile->getSize() );

	jpeg_source_mgr*   pJpgMgr = new jpeg_source_mgr;
	pJpgMgr->bytes_in_buffer   = infile->getSize();
	pJpgMgr->next_input_byte   = (JOCTET*)pBuffer;
	pJpgMgr->init_source       = KS_init_source;
	pJpgMgr->fill_input_buffer = KS_fill_input_buffer;
	pJpgMgr->skip_input_data   = KS_skip_input_data;
	pJpgMgr->term_source       = KS_term_source;
	pJpgMgr->resync_to_restart = jpeg_resync_to_restart;
	cinfo->src                 = pJpgMgr;
}
/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KsBool KsIsFileExtensionJPG( const KsChar* pFileName )
{
	/* 拡張子が jpg or jpeg or JPG or JPEG かをチェックする */
	if( strstr( pFileName, ".jpg" ) ){
		return ksTRUE;
	}

	if( strstr( pFileName, ".jpeg" ) ){
		return ksTRUE;
	}

	if( strstr( pFileName, ".JPG" ) ){
		return ksTRUE;
	}

	return ( strstr( pFileName, ".JPEG" ) != 0 );
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsImage* KsLoadImageJPEG( FILE* pFile )
{
	struct jpeg_decompress_struct	jpegStruct;
	struct jpeg_error_mgr			jpegError;
	KsInt32						height      = 0;
	KsInt32						width       = 0;
	KsInt32						rowStride   = 0;
	KsInt32						offset      = 0;
	KsBool							hasAlpha    = ksFALSE;	/* アルファ値の情報があるかどうか？ */
	KsBool							isGreyscale = ksFALSE; /* グレイスケールのデータかどうか？ */
	KsByte*							pData       = NULL;
	KsByte**						ppRow       = NULL;
	KsImage*						pImage      = NULL;

	/*  JPEG読み込み */
	jpegStruct.err = jpeg_std_error( &jpegError );
	
	/* 構造体の生成 */
	jpeg_create_decompress( &jpegStruct );
	
	/* 自作関数を使用する */
	jpeg_stdio_src( &jpegStruct, pFile );
	
	/* JPEGヘッダ情報の読み込み */
	jpeg_read_header( &jpegStruct, ksTRUE );
	
	/* 解凍の開始 */
	jpeg_start_decompress( &jpegStruct );

    /* 行バッファの領域設定 */
    rowStride = jpegStruct.output_width * jpegStruct.output_components;

	/* イメージ生成 */
	width  = jpegStruct.output_width;
	height = jpegStruct.output_height;

	/* グレースケール？ */
	if( jpegStruct.jpeg_color_space == JCS_GRAYSCALE ){
		isGreyscale = ksTRUE;
	}

	/* データ領域確保 */
	pData = new KsByte[ rowStride * height ];

	if( !pData ){
		/* メモリー確保エラー */
		jpeg_finish_decompress( &jpegStruct );
		jpeg_destroy_decompress( &jpegStruct );
		return NULL;
	}

	ppRow = new KsByte*[ height ];

	if( !ppRow ){
		/* メモリー確保エラー */
		jpeg_finish_decompress( &jpegStruct );
		jpeg_destroy_decompress( &jpegStruct );
		ksDELETEARRAY( pData );
		return NULL;
	}

	/* データの読み取り用にセット */
	for( KsInt32 i = 0; i < height; i++ ){
		ppRow[ i ] = &pData[ i * rowStride ];
	}

	/* データ読み込み処理 */
	while( jpegStruct.output_scanline < jpegStruct.output_height ){
		offset += jpeg_read_scanlines( &jpegStruct, &ppRow[ offset ], jpegStruct.output_height - offset );
	}

	/* 後処理 */
	jpeg_finish_decompress( &jpegStruct );
	jpeg_destroy_decompress( &jpegStruct );

	ksDELETEARRAY( ppRow );

	/* イメージを生成 */
	pImage = new KsImage();

	pImage->m_pData  = pData;
	pImage->m_height = height;
	pImage->m_width  = width;
	pImage->m_format = ksIMAGE_R8G8B8;

	return pImage;
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsImage* KsLoadImageJPEG( KsFileObject* pFile )
{
	struct jpeg_decompress_struct	jpegStruct;
	struct jpeg_error_mgr			jpegError;
	KsInt32						height      = 0;
	KsInt32						width       = 0;
	KsInt32						rowStride   = 0;
	KsInt32						offset      = 0;
	KsBool							hasAlpha    = ksFALSE;	/* アルファ値の情報があるかどうか？ */
	KsBool							isGreyscale = ksFALSE; /* グレイスケールのデータかどうか？ */
	KsByte*							pData       = NULL;
	KsByte**						ppRow       = NULL;
	KsImage*						pImage      = NULL;

	/*  JPEG読み込み */
	jpegStruct.err = jpeg_std_error( &jpegError );
	
	/* 構造体の生成 */
	jpeg_create_decompress( &jpegStruct );
	
	/* 自作関数を使用する(ライブラリでは、FILEからしか読み込めない) */
	KS_jpeg_stdio_src( &jpegStruct, pFile );
	
	/* JPEGヘッダ情報の読み込み */
	jpeg_read_header( &jpegStruct, ksTRUE );
	
	/* 解凍の開始 */
	jpeg_start_decompress( &jpegStruct );

    /* 行バッファの領域設定 */
    rowStride = jpegStruct.output_width * jpegStruct.output_components;

	/* イメージ生成 */
	width  = jpegStruct.output_width;
	height = jpegStruct.output_height;

	/* グレースケール？ */
	if( jpegStruct.jpeg_color_space == JCS_GRAYSCALE ){
		isGreyscale = ksTRUE;
	}

	/* データ領域確保 */
	pData = new KsByte[ rowStride * height ];

	if( !pData ){
		/* メモリー確保エラー */
		jpeg_finish_decompress( &jpegStruct );
		jpeg_destroy_decompress( &jpegStruct );
		return NULL;
	}

	ppRow = new KsByte*[ height ];

	if( !ppRow ){
		/* メモリー確保エラー */
		jpeg_finish_decompress( &jpegStruct );
		jpeg_destroy_decompress( &jpegStruct );
		ksDELETEARRAY( pData );
		return NULL;
	}

	/* データの読み取り用にセット */
	for( KsInt32 i = 0; i < height; i++ ){
		ppRow[ i ] = &pData[ i * rowStride ];
	}

	/* データ読み込み処理 */
	while( jpegStruct.output_scanline < jpegStruct.output_height ){
		offset += jpeg_read_scanlines( &jpegStruct, &ppRow[ offset ], jpegStruct.output_height - offset );
	}

	/* 後処理 */
	jpeg_finish_decompress( &jpegStruct );
	jpeg_destroy_decompress( &jpegStruct );

	ksDELETEARRAY( ppRow );

	/* イメージを生成(実際は、24bit以外の場合も設定する) */
	pImage = new KsImage();

	pImage->m_pData  = pData;
	pImage->m_height = height;
	pImage->m_width  = width;
	pImage->m_format = ksIMAGE_R8G8B8;

	return pImage;
}

