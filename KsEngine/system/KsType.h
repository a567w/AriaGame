/*************************************************************************************************/
/**
 * @file	KsType.h
 * @brief	タイプ定義
 * @author	Tsukasa Kato
 * @date	2003/11/30
 * @version	1.0.0
 */
 /************************************************************************************************/
#ifndef __KSTYPE_H__
#define __KSTYPE_H__

/*===============================================================================================*/
/*                                 << インクルード >>                                            */
/*===============================================================================================*/
#include "KsEngine/KsEngineCompile.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <tchar.h>
#include <string.h>
#include <stdarg.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <process.h>
#include <memory>
#include <exception>
#include <type_traits>

/*===============================================================================================*/
/*                                     << 定義 >>                                                */
/*===============================================================================================*/
#define ksENGINEVERSION			( 0x0001 )						/**< KsEngineバージョン			*/
#define ksENGINEVERSIONSTRING	"Aria Engine Version 0.1.1"		/**< KsEngineバージョン文字列	*/
#define ksTRUE					( 1 )							/**< 真							*/
#define ksFALSE					( 0 )							/**< 偽							*/

/* キャスト */
#define s_cast					static_cast
#define c_cast					const_cast
#define r_cast					reinterpret_cast
#define d_cast					dynamic_cast


/* 整数型 最大値/最小値 */
#define KsInt8MAXVAL			( 0x7F )
#define KsInt8MINVAL			( 0x80 )
#define KsUInt8MAXVAL			( 0xFF )
#define KsUInt8MINVAL			( 0x00 )
#define KsInt16MAXVAL			( 0x7FFF )
#define KsInt16MINVAL			( 0x8000 )
#define KsUInt16MAXVAL			( 0xFFFF )
#define KsUInt16MINVAL			( 0x0000 )
#define KsInt32MAXVAL			( 0x7FFFFFFF )
#define KsInt32MINVAL			( 0x80000000 )
#define KsUInt32MAXVAL			( 0xFFFFFFFF )
#define KsUInt32MINVAL			( 0x00000000 )					/**< */
/* 浮動少数型 最大値/最小値 */
#define KsRealMAXVAL			( 0x7f7fc99e )					/**<  3.4 * 10^38					*/
#define KsRealMINVAL			( 0xff7fc99e )					/**< -3.4 * 10^38					*/
#define ksFLOAT32_MAX			( 3.402823466e+38f )
#define ksFLOAT32_MIN			(-3.402823466e+38f )

#define ksFLT_DIG				6								/* # of decimal digits of precision */
#define ksFLT_EPSILON			1.192092896e-07F				/* smallest such that 1.0+FLT_EPSILON != 1.0 */
#define ksFLT_GUARD				0
#define ksFLT_MANT_DIG			24								/* # of bits in mantissa */
#define ksFLT_MAX				3.402823466e+38F				/* max value */
#define ksFLT_MAX_10_EXP		38								/* max decimal exponent */
#define ksFLT_MAX_EXP			128								/* max binary exponent */
#define ksFLT_MIN				1.175494351e-38F				/* min positive value */
#define ksFLT_MIN_10_EXP		(-37)							/**< min decimal exponent */
#define ksFLT_MIN_EXP			(-125)							/**< min binary exponent */
#define ksFLT_NORMALIZE			0
#define ksFLT_RADIX				2								/**< exponent radix */
#define ksFLT_ROUNDS			1								/**< addition rounding: near */

#define ksALIGNED_CLASS16(a)	__declspec(align(16)) a
#define ksATTRIBUTE_ALIGN16		__declspec(align(16))
#define ksFORCE_INLINE			__forceinline

#define ksALIGN2(x)				(((x)+ 1) & ~1)					/**<  2 bytes alignment				*/
#define ksALIGN4(x)				(((x)+ 3) & ~3)					/**<  4 bytes alignment				*/
#define ksALIGN8(x)				(((x)+ 7) & ~7)					/**<  8 bytes alignment				*/
#define ksALIGN16(x)			(((x)+15) & ~15)				/**< 16 bytes alignment				*/

typedef			int				KsBool;							/**< ブール値							*/
typedef			float			KsReal;							/**< 浮動小数点型						*/
typedef			float			KsReal32;						/**< 浮動小数点型						*/
typedef			double			KsReal64;						/**< 倍精度浮動小数点型				*/
typedef			long			KsLong;							/**< 32 ビットの符号付き整数			*/
typedef			int				KsInt32;						/**< 32 ビットの符号付き整数			*/
typedef			short			KsInt16;						/**< 16 ビットの符号付き整数			*/
typedef			char			KsInt8;							/**<  8 ビットの符号付き整数			*/
#ifdef  UNICODE
typedef			wchar_t			KsChar;							/**<  8 ビットの符号付き整数			*/
#else
typedef			char			KsChar;							/**<  8 ビットの符号付き整数			*/
#endif // #ifdef  UNICODE
typedef			char			KsSChar;						/**<  8 ビットの符号付き整数			*/
typedef			wchar_t			KsWChar;						/**< 16 ビットの符号付き整数			*/
typedef unsigned long			KsULong;						/**< 32 ビットの符号なし整数			*/
typedef unsigned int			KsUInt32;						/**< 32 ビットの符号なし整数			*/
typedef unsigned short			KsUInt16;						/**< 16 ビットの符号なし整数			*/
typedef unsigned char			KsUInt8;						/**<  8 ビットの符号なし整数			*/
typedef unsigned char			KsByte;							/**<  8 ビットの符号なし整数			*/
typedef unsigned short			KsWord;							/**< 16 ビットの符号なし整数			*/
typedef unsigned long			KsDWord;						/**< 32 ビットの符号なし整数			*/
typedef __int64					KsInt64;						/**< 64 ビットの符号付き整数			*/
typedef unsigned __int64		KsUInt64;						/**< 64 ビットの符号なし整数			*/
typedef size_t					KsSize;							/**< サイズ用							*/
typedef void*					KsHandle;						/**< ハンドル							*/

/* 数学関数 */
#define KsSin(_x)				sinf(_x)						/**< sin							*/
#define KsSinh(_x)				sinhf(_x)						/**< ハイパーボリックsin				*/
#define KsCos(_x)				cosf(_x)						/**< cos							*/
#define KsCosh(_x)				coshf(_x)						/**< ハイパーボリックcos				*/
#define KsTan(_x)				tanf(_x)						/**< tan							*/
#define KsTanh(_x)				tanhf(_x)						/**< ハイパーボリックtan				*/
#define KsASin(_x)				asinf(_x)						/**< asin							*/
#define KsASinh(_x)				asinhf(_x)						/**< ハイパーボリックasin				*/
#define KsACos(_x)				acosf(_x)						/**< acos							*/
#define KsACosh(_x)				acoshf(_x)						/**< ハイパーボリックacos				*/
#define KsATan(_x)				atanf(_x)						/**< atan							*/
#define KsATan2(_x,_y)			atan2f(_x,_y)					/**< atan2							*/
#define KsAbs(_x)				abs(_x)							/**< abs							*/
#define KsFabs(_x)				fabsf(_x)						/**< fabs							*/
#define KsExp(_x)				expf(_x)						/**< exp(指数を計算)					*/
#define KsFmod(_x,_y)			fmodf(_x,_y)					/**< fmod(浮動小数点数の剰余を計算)		*/
#define KsLogE(_x)				logf(_x)						/**< log							*/
#define KsLog10(_x)				log10f(_x)						/**< log10							*/
#define KsModf(_x,_y)			modf(_x,_y)						/**< modf							*/
#define KsPow(_x,_y)			pow(_x,_y)						/**< pow(x の y 乗を計算する)			*/
#define KsSqrt(_x)				sqrtf(_x)						/**< 平方根							*/
#define KsRsqrt(_x)				rsqrtf(_x)						/**< 平方根の逆数						*/

#define KsFloor(_x)				s_cast<KsReal>(s_cast<KsInt32>(_x))

#define ksPI					(3.14159265358979323846264338f)	/**< 円周率(π)						*/
#define ksHALF_PI				(1.57079632679489661923132169f)	/**< 円周率(π/２)						*/
#define ksTWO_PI				(6.28318530717958647692528676f)	/**< 円周率(２π)						*/
#define ksTOLERANCE				(0.0001f)						/**< 打ち切り誤差						*/
#define ksTOLERANCE2			(0.00000001f)					/**< 打ち切り誤差２					*/
#define ksPATH_MAX				( 512 )							/**< 最大パス長						*/

#endif	/* __KSTYPE_H__ */

