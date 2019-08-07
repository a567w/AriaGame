/************************************************************************************************/
/** 
 * @file		KsImagePNG.cpp
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
#include "KsImagePNG.h"
#include "./png/png.h"

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
KsBool KsIsFileExtensionPNG( const KsChar* pFileName )
{
	/* 拡張子が tga or TGA かをチェックする */
	if( strstr( pFileName, ".png" ) ){
		return ksTRUE;
	}

	return ( strstr( pFileName, ".PNG" ) != 0 );
}
/************************************************************************************************/
/*
 * データ読み込み用コールバック関数
 * @param	pPngStruct		PNG構造体
 * @param	pDataBuf		データ用バッファ
 * @param	size			読み込みサイズ
 */
/************************************************************************************************/
static void KsReadPngCallback( png_struct* pPngStruct, png_byte* pDataBuf, png_size_t size )
{
	KsFileObject*	pFile = (KsFileObject*)png_get_io_ptr( pPngStruct );

	/* 先にファイルを読み込んでから処理 */
	pFile->read( pDataBuf, (KsInt32)size );
}

/************************************************************************************************/
//*
//* パックされたデータから読み込むときもあるのでFILE*ではだめ

	/************************************************************************/
	/*	画像のカラータイプを格納する intへのポインタを指定します。				*/
	/*	カラータイプの各ビットは以下のように定義されます。					*/
	/*																		*/
	/*	bit0	パレットの使用(1)/未使用(0)									*/
	/*	bit1	カラー(1)/モノクロ(0)										*/
	/*	bit2	αチャネル有り(1)/無し(0)									*/
	/*																		*/
	/*	実際にはカラータイプ(名称 / 色深度)は以下の物だけ					*/
	/*	0(グレースケール / 1,2,4,8,16) 										*/
	/*	2(Trueカラー / 8,16) 												*/
	/*	3(インデックスカラー / 1,2,4,8)										*/
	/*	4(αチャネルのあるグレースケール / 8,16)							*/
	/*	6(αチャネルのある Trueカラー / 8,16)								*/
	/************************************************************************/

 //
//************************************************************************************************/
KsImage* KsLoadImagePNG( KsFileObject* pFile )
{
	/* PNGの読み込み */
	KsByte*				pDataBuf        = NULL;
	png_struct*			pPngStruct      = NULL;
    png_info*			pPngInfo        = NULL;
	png_info*			pPngInfoEnd     = NULL;
	png_bytep*			ppData          = NULL;
	KsByte*				pData           = NULL;
	KsImage*			pImage          = NULL;
    KsInt32			width           = 0;
	KsInt32			height          = 0;
	KsInt32			depth           = 0;
	KsInt32			colorType       = 0;
    KsInt32			filterType      = 0;
	KsInt32			size            = 0;

	/* 先頭に移動 */
	pFile->seek( 0, ksSEEK_SET );

	/* PNG生成 */
	pPngStruct = png_create_read_struct( PNG_LIBPNG_VER_STRING, NULL, NULL, NULL );
	if( !pPngStruct )
	{
		return NULL;
	}

	/* PNG情報 */
	pPngInfo = png_create_info_struct( pPngStruct );
	if( !pPngInfo )
	{
		return NULL;
	}

	/* スタック保持ジャンプ */
	if( setjmp( png_jmpbuf( pPngStruct) ) )
	{
		return NULL;
	}

	/* バッファに読み込み処理をセット */
	png_set_read_fn( pPngStruct, (void*)pFile, (png_rw_ptr)KsReadPngCallback );

	/* 情報読み込み */
	png_read_info( pPngStruct, pPngInfo );

	width      = png_get_image_width( pPngStruct, pPngInfo );
	height     = png_get_image_height( pPngStruct, pPngInfo );
	depth      = png_get_bit_depth( pPngStruct, pPngInfo );
	colorType  = png_get_color_type( pPngStruct, pPngInfo );
	filterType = ( colorType == PNG_COLOR_TYPE_RGB_ALPHA ) ? 4 : 3;

	/* パレットを使用しているか? */
	if( colorType == PNG_COLOR_TYPE_PALETTE )
	{
		filterType = 3;
		colorType  = PNG_COLOR_TYPE_RGB;

		/* パレットからRGBに変換 */
		png_set_palette_to_rgb( pPngStruct );
	}

	/* グレイスケールで深度が8以下なら？ */
	if( ( colorType == PNG_COLOR_TYPE_GRAY ) && ( depth < 8 ) ){
		/* 8bitに変換する */
		png_set_gray_1_2_4_to_8( pPngStruct );
	}

	/* グレイスケール(アルファで使用するのでコメント) */
	if( colorType == PNG_COLOR_TYPE_GRAY )
	{
		filterType  = 1;
		//colorType = PNG_COLOR_TYPE_RGB;
		//png_set_gray_to_rgb( pPngStruct );
	}

	/* アルファ */
	if( colorType == PNG_COLOR_TYPE_GRAY_ALPHA )
	{
		filterType = 4;
		colorType  = PNG_COLOR_TYPE_RGB_ALPHA;

		png_set_gray_to_rgb( pPngStruct );
	}

	if( png_get_valid( pPngStruct, pPngInfo, PNG_INFO_tRNS ) )
	{
		filterType = 4;
		colorType  = PNG_COLOR_TYPE_RGB_ALPHA;
		
		png_set_tRNS_to_alpha( pPngStruct );
	}

	/* タイプチェック */
	if( ( colorType != PNG_COLOR_TYPE_RGB ) && ( colorType != PNG_COLOR_TYPE_RGB_ALPHA ) )
	{
		return NULL;
	}

	/* 8bit から 16bit */
	if( depth > 8 ){
		png_set_strip_16( pPngStruct );
	}

	/* 更新処理 */
	png_read_update_info( pPngStruct, pPngInfo );

	/* メモリー確保 */
	ppData = new png_byte* [ height ];

	for( KsInt32 i=0; i<height; i++ )
	{
		ppData[ i ] = new png_byte[ png_get_rowbytes( pPngStruct, pPngInfo ) ];
	}

	/* イメージ取得 */
	png_read_image( pPngStruct, ppData );

	/* 読み込み終了 */
	png_read_end( pPngStruct, pPngInfo );

	/* イメージデータ生成処理 */
	pData = new KsByte[ width * height * 3 ];

	for( KsInt32 j=0; j<height; j++ )
	{
		memcpy( ( pData + j*width*3 ), ppData[ j ], width * 3 );
	}

	/* イメージを生成(実際は、24bit以外の場合も設定する) */
	pImage = new KsImage();
	
	// RGB or RGBA
	pImage->m_pData  = pData;
	pImage->m_height = height;
	pImage->m_width  = width;
	pImage->m_format = ksIMAGE_R8G8B8;

	/* 後処理 */
	for( i=0; i<height; i++ )
	{
		ksDELETEARRAY( ppData[ i ] );
	}
	ksDELETEARRAY( ppData );

	/* 破棄 */
	png_destroy_read_struct( &pPngStruct, &pPngInfo, png_infopp_NULL );

	return pImage;
}



