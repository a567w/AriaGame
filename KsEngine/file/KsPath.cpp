/*************************************************************************************************/
/**
 * @file	KsPath.cpp
 * @brief	PATHクラス
 * @author	tsukasa kato
 * @date	2003/11/30
 * @version	1.0.0
 */
/*************************************************************************************************/

/*===============================================================================================*/
/*                                 << インクルード >>                                            */
/*===============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"

/*===============================================================================================*/
/*                                     << 定義 >>                                                */
/*===============================================================================================*/

/*===============================================================================================*/
/*                                     << 宣言 >>                                                */
/*===============================================================================================*/


/************************************************************************************************/
/**
 * フルパスからファイル名だけを取得する開く
 * @param	path			ファイルのフルパス
 * @return					ファイル名
 */
/************************************************************************************************/
KsString KsPath::getFileName( const KsString& path )
{
	KsChar			drive[ _MAX_DRIVE ];
	KsChar			dir[ _MAX_DIR ];
	KsChar			fname[ _MAX_FNAME ];
	KsChar			ext[ _MAX_EXT ];

	ks_splitpath( path.c_str(), drive, dir, fname, ext );

	return KsString( fname );
}


