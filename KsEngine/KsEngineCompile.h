/*************************************************************************************************/
/** 
 * @file	KsCompile.h
 * @brief	コンパイルなどの設定
 * @author	Tsukasa Kato
 * @date	2008/02/12
 * @since	2008/02/12
 */
/*************************************************************************************************/
#ifndef __KSCOMPILE_H__
#define __KSCOMPILE_H__

/*===============================================================================================*/
/*								<< インクルードファイル >>										 */
/*===============================================================================================*/

/*===============================================================================================*/
/*                                     << 定義 >>                                                */
/*===============================================================================================*/

//#define ksBUILD_STATIC	// プロジェクトで設定
//#define ksBUILD_DYNAMIC	// プロジェクトで設定
//#define ksENGINE_EXPORTS	// プロジェクトで設定

/* 出力形式 */
#ifdef ksBUILD_STATIC
	#define ksENGINE_API
	#define ksEXTERN
#else
	#ifdef ksENGINE_EXPORTS
		#define ksENGINE_API	__declspec( dllexport )
		#define ksEXTERN
	#else
		#define ksENGINE_API	__declspec( dllimport )
		#define ksEXTERN		extern
	#endif
#endif

#define ksCDECL __cdecl

#ifdef WIN32
	#include <vector>
	#include <map>
	#include <string>

	#ifdef _MSC_VER
		#pragma warning( disable : 4231 )
		#pragma warning( disable : 4251 )	/* テンプレートエクスポート時の警告		*/
		#pragma warning( disable : 4311 )	/* ポインタから整数値への変更				*/
		#pragma warning( disable : 4312 )	/* 整数値からポインタへの変更				*/
		#pragma warning( disable : 4333 )	/* 右シフトの回数が多すぎます。データが失われる可能性があります				*/
		#pragma warning( disable : 4661 )	/* 明示的なテンプレートのインスタンス生成要求に対して適切な定義がありません。 */
		#pragma warning( disable : 4819 )
		#pragma warning( disable : 4995 )
		#pragma warning( disable : 4996 )
	#endif
#endif

/*===============================================================================================*/
/*                                     << 宣言 >>                                                */
/*===============================================================================================*/


#endif	/* __KSCOMPILE_H__ */


