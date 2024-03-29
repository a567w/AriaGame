/************************************************************************************************/
/** 
 * @file		KsImageLoader.cpp
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
#include "KsImageLoader.h"
#include "KsImageBMP.h"
#include "KsImageTGA.h"

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
KsImageLoader::KsImageLoader()
{
}
/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
KsImageLoader::~KsImageLoader()
{
}
/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
KsImageLoader* KsImageLoader::getInstance()
{
	static KsImageLoader		instance;

	return &instance;
}

/************************************************************************************************/
/*
 * 画像ファイルを読み込む
 * @param		pFileName		ファイル名
 * @retval						イメージデータ失敗時は、NULLが返る
 */
/************************************************************************************************/
KsImage* KsImageLoader::load( const KsChar* pFileName )
{
	KsImage*		pImage = NULL;

	if( KsIsFileExtensionBMP( pFileName ) ){
		/* BMP読み込み */
	}
	else if( KsIsFileExtensionTGA( pFileName ) ){
		/* TGA読み込み */
	}
	else{
		/* サポート外の画像フォーマットです。 */
	}

	return NULL;
}


