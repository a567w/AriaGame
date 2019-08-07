/*************************************************************************************************/
/** 
 * @file	KsMMDCompile.h
 * @brief	コンパイルなどの設定
 * @author	Tsukasa Kato
 * @date	2008/02/12
 * @since	2008/02/12
 */
/*************************************************************************************************/
#ifndef __KSMMDCOMPILE_H__
#define __KSMMDCOMPILE_H__

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
	#define ksMMD_API
	#define ksMMD_EXTERN
#else
	#ifdef ksMMD_EXPORTS
		#define ksMMD_API			__declspec( dllexport )
		#define ksMMD_EXTERN
	#else
		#define ksMMD_API			__declspec( dllimport )
		#define ksMMD_EXTERN		extern
	#endif
#endif

#define ksMMD_CDECL __cdecl

/*===============================================================================================*/
/*                                     << 宣言 >>                                                */
/*===============================================================================================*/


#endif	/* __KSMMDCOMPILE_H__ */


