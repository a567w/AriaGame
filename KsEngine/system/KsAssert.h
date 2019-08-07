	/************************************************************************************************/
/** 
 * @file		KsAssert.h
 * @brief		アサート処理
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSASSERT_H__
#define __KSASSERT_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsType.h"


/*************************************************************************************************/
/**
 * デバック用マクロ(ブレイクポイント設定)
 */
/*************************************************************************************************/
#ifdef _DEBUG
	/* ブレイクポイント設定 */
	//#ifdef _WIN
	#define KsDebugBreak()			__asm { int 3 }
	//#endif
#else
	#define KsDebugBreak()			::exit( 0 );
#endif

/*************************************************************************************************/
/**
 * アサート用マクロ, ログに情報を残します。
 */
/*************************************************************************************************/
//#ifdef _MASTER
#if 1
	// 警告(マスターでは，ださない)
	#define KsAssert( cmp, str )
	#define KsAssertEx( cmp )
#else
	// 警告(ログに残す)
	#define KsAssert( cmp, str )	if( !(cmp) ){															\
										KsChar		buf[ 512 ];												\
										sprintf( buf,"%s [ FILE %s, LINE %d ]\n", str, __FILE__,__LINE__);	\
										KsLogManager::message( str, ksLOG_LEVEL_ASSERT );					\
										KsDebugBreak();														\
									}

	#define KsAssertEx( cmp )		if( !(cmp) ){													\
										KsChar		buf[ 512 ];										\
										sprintf( buf,"FILE %s, LINE %d\n", __FILE__,__LINE__);		\
										KsLogManager::message( buf, ksLOG_LEVEL_ASSERT );			\
										KsDebugBreak();												\
									}
#endif

/*************************************************************************************************/
/**
 * メッセージ用マクロ, ログに情報を残します。
 */
/*************************************************************************************************/
#ifdef _MASTER
	#define KsMessage( str )
#else
	#define KsMessage( str ) KsLogManager::message( str, ksLOG_LEVEL_MESSAGE )
#endif

/*************************************************************************************************/
/**
 * エラー用マクロ, ログに情報を残します。
 */
/*************************************************************************************************/
#ifdef _MASTER
	#define KsError( str )
#else
	#define KsError( str )		KsLogManager::message( str, ksLOG_LEVEL_ERROR );
#endif


/*************************************************************************************************/
/**
 * エラー用マクロ, ログに情報を残します。
 */
/*************************************************************************************************/
inline void KsPrintf( const KsChar* pszFormat, ... )
{
#if !defined( _MASTER )
	va_list	argp;
	KsChar pszBuf[ 512 ];
	va_start(argp, pszFormat);
	vsprintf( pszBuf, pszFormat, argp);
	va_end(argp);
	OutputDebugString( pszBuf );
#endif
}

#endif	/* __KSASSERT_H__ */
