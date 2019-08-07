/************************************************************************************************/
/** 
 * @file		KsScriptFormat.h
 * @brief		スクリプトファイルフォーマット
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSSCRIPTFORMAT_H__
#define __KSSCRIPTFORMAT_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsVariable.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
#define ksSCRIPT_SIGNATURE		ksMAKE_DWORD( '@', 'K', 'G', 'S' )
#define ksSCRIPT_VERSION		( 0x00010000 )

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*
中間コードファイルフォーマット
----------------------------------------------------------------------------
HEADER
	signature				4byte
	version					4byte
	offsetInfo				4byte
	offsetCode				4byte			
----------------------------------------------------------------------------
INFO
	numString				2byte	
	numGlobal				2byte
	numFunc					2byte
	numStruct				2byte

	offsetGlobal			4byte			グローバル変数情報へのオフセット
	offsetFunc				4byte			
	offsetStruct			4byte
	offsetString			4byte

	FILE(ファイル名ローカルとグローバルの関数を分けるため)
		length				2byte
		name				可変長

	STRING
		numString				2byte
			STRING
				length			2byte		文字列の長さ
				next			2byte		次の文字列へのオフセット
				string			可変			文字列
				numCode			2byte		確保したあとに書き換えるコード数
					offset		4byte		numCode分ある(offsetCodeからのオフセット)
			.....繰り返し

	GLOBAL
		numGlobal				2byte
			VARIABL_GLOBAL
				length			2byte		文字列の長さ
				next			2byte		次の文字列へのオフセット
				numCode			2byte		確保したあとに書き換えるコード数
					offset		4byte		numCode分ある(offsetCodeからのオフセット)
				string			可変			文字列
			.....繰り返し

	FUNC
		numFunc					2byte
			id					4byte		関数のID
			numArg				2byte		引数の数
			numVar				2byte		ローカル変数の数
			stackSize			4byte		この関数のスタックサイズ
			codeSize			4byte		関数のコードサイズ
			codeOffset			4byte		コード情報部からのオフセットアドレス
			next				4byte		次の関数へのオフセットアドレス(0で終了)
			numLocal			2byte
				VARIABL_LOCAL(オフセット順に入っている)
					length		2byte		文字列の長さ
					next		2byte		次の文字列へのオフセット
					string		可変			文字列
					.....繰り返し
			.....繰り返し

	STRUCT
		numStruct			2byte

----------------------------------------------------------------------------
CODE
	size		4byte		コードサイズ
	data		サイズ分
----------------------------------------------------------------------------
	
*/

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_SCRIPT_FILE_HEADER
{
	KsUInt32			signature;			/**< 識別用サイン							*/
	KsUInt32			version;			/**< バージョン情報							*/
	KsUInt32			offsetInfo;			/**< 情報部へのオフセットアドレス			*/
	KsUInt32			offsetCode;			/**< コマンド部へのオフセットアドレス		*/
}KS_SCRIPT_FILE_HEADER;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_SCRIPT_INFO_HEADER
{
	KsUInt32			numString;			/**< 文字列の数								*/
	KsUInt32			numGlobal;			/**< グローバル変数の数						*/
	KsUInt32			numFunc;			/**< 関数の数								*/
	KsUInt32			numStruct;			/**< 構造体の数								*/
	KsUInt32			offsetString;		/**< 文字列情報へのオフセット				*/
	KsUInt32			offsetGlobal;		/**< グローバル変数情報へのオフセット		*/
	KsUInt32			offsetFunc;			/**< 文字列の数								*/
	KsUInt32			offsetStruct;		/**< 文字列の数								*/

}KS_SCRIPT_INFO_HEADER;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_SCRIPT_FUNC_INFO
{
	KsUInt32			id;					/**< 関数のID								*/
	KsUInt16			numArg;				/**< 引数の数								*/
	KsUInt16			numVar;				/**< ローカル変数の数						*/
	KsUInt32			stackSize;			/**< この関数のスタックサイズ				*/
	KsUInt32			codeSize;			/**< 関数のコードサイズ						*/
	KsUInt32			codeOffset;			/**< コード情報部からのオフセットアドレス	*/
	KsUInt32			nextOffset;			/**< 次の関数へのオフセットアドレス(0で終了)*/
	KsChar*				pSymbol;			/**< 関数名 + arg0+'\0'...local2+'\0'+'\0' 4バイトアラインメント	*/
}KS_SCRIPT_FUNC_INFO;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_SCRIPT_STRUCT_INFO
{
	KsUInt16			numVar;				/**< メンバー変数の数							*/
	KsUInt16			numFunc;			/**< メンバー関数の数							*/
	KsUInt32			nextOffset;			/**< 次の構造体へのオフセットアドレス(0で終了)	*/
	KsChar*				pSymbol;			/**< 構造体名 + メンバー変数	+ メンバー関数	*/
}KS_SCRIPT_STRUCT_INFO;



#endif		/* __KSSCRIPTFORMAT_H__	*/





