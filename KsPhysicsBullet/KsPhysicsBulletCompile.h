/*************************************************************************************************/
/** 
 * @file	KsPhysicsBulletCompile.h
 * @brief	コンパイルなどの設定
 * @author	Tsukasa Kato
 * @date	2008/02/12
 * @since	2008/02/12
 */
/*************************************************************************************************/
#ifndef __KSPHYSICSBULLETCOMPILE_H__
#define __KSPHYSICSBULLETCOMPILE_H__

/*===============================================================================================*/
/*								<< インクルードファイル >>										 */
/*===============================================================================================*/

/*===============================================================================================*/
/*                                     << 定義 >>                                                */
/*===============================================================================================*/

//#define ksBUILD_STATIC	// プロジェクトで設定
//#define ksBUILD_DYNAMIC	// プロジェクトで設定
//#define ksENGINE_EXPORTS	// プロジェクトで設定

#if 0
#if defined( ksBUILD_DYNAMIC ) && defined( ksBUILD_STATIC )
	#undef ksBUILD_STATIC
#else
	#if !defined(ksBUILD_DYNAMIC)
		#define ksBUILD_DYNAMIC
	#endif
#endif
#endif

/* 出力形式 */
/* 出力形式 */
#ifdef ksBUILD_STATIC
	#define ksPHYSICSBULLET_API
	#define ksPHYSICSBULLET_EXTERN
#else
	#ifdef ksPHYSICSBULLET_EXPORTS
		#define ksPHYSICSBULLET_API			__declspec( dllexport )
		#define ksPHYSICSBULLET_EXTERN
	#else
		#define ksPHYSICSBULLET_API			__declspec( dllimport )
		#define ksPHYSICSBULLET_EXTERN		extern
	#endif
#endif

#define ksPHYSICSBULLET_CDECL __cdecl

/*===============================================================================================*/
/*                                     << 宣言 >>                                                */
/*===============================================================================================*/


#endif	/* __KSPHYSICSBULLETCOMPILE_H__ */


