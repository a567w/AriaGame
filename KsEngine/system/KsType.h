/*************************************************************************************************/
/**
 * @file	KsType.h
 * @brief	�^�C�v��`
 * @author	Tsukasa Kato
 * @date	2003/11/30
 * @version	1.0.0
 */
 /************************************************************************************************/
#ifndef __KSTYPE_H__
#define __KSTYPE_H__

/*===============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
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
/*                                     << ��` >>                                                */
/*===============================================================================================*/
#define ksENGINEVERSION			( 0x0001 )						/**< KsEngine�o�[�W����			*/
#define ksENGINEVERSIONSTRING	"Aria Engine Version 0.1.1"		/**< KsEngine�o�[�W����������	*/
#define ksTRUE					( 1 )							/**< �^							*/
#define ksFALSE					( 0 )							/**< �U							*/

/* �L���X�g */
#define s_cast					static_cast
#define c_cast					const_cast
#define r_cast					reinterpret_cast
#define d_cast					dynamic_cast


/* �����^ �ő�l/�ŏ��l */
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
/* ���������^ �ő�l/�ŏ��l */
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

typedef			int				KsBool;							/**< �u�[���l							*/
typedef			float			KsReal;							/**< ���������_�^						*/
typedef			float			KsReal32;						/**< ���������_�^						*/
typedef			double			KsReal64;						/**< �{���x���������_�^				*/
typedef			long			KsLong;							/**< 32 �r�b�g�̕����t������			*/
typedef			int				KsInt32;						/**< 32 �r�b�g�̕����t������			*/
typedef			short			KsInt16;						/**< 16 �r�b�g�̕����t������			*/
typedef			char			KsInt8;							/**<  8 �r�b�g�̕����t������			*/
#ifdef  UNICODE
typedef			wchar_t			KsChar;							/**<  8 �r�b�g�̕����t������			*/
#else
typedef			char			KsChar;							/**<  8 �r�b�g�̕����t������			*/
#endif // #ifdef  UNICODE
typedef			char			KsSChar;						/**<  8 �r�b�g�̕����t������			*/
typedef			wchar_t			KsWChar;						/**< 16 �r�b�g�̕����t������			*/
typedef unsigned long			KsULong;						/**< 32 �r�b�g�̕����Ȃ�����			*/
typedef unsigned int			KsUInt32;						/**< 32 �r�b�g�̕����Ȃ�����			*/
typedef unsigned short			KsUInt16;						/**< 16 �r�b�g�̕����Ȃ�����			*/
typedef unsigned char			KsUInt8;						/**<  8 �r�b�g�̕����Ȃ�����			*/
typedef unsigned char			KsByte;							/**<  8 �r�b�g�̕����Ȃ�����			*/
typedef unsigned short			KsWord;							/**< 16 �r�b�g�̕����Ȃ�����			*/
typedef unsigned long			KsDWord;						/**< 32 �r�b�g�̕����Ȃ�����			*/
typedef __int64					KsInt64;						/**< 64 �r�b�g�̕����t������			*/
typedef unsigned __int64		KsUInt64;						/**< 64 �r�b�g�̕����Ȃ�����			*/
typedef size_t					KsSize;							/**< �T�C�Y�p							*/
typedef void*					KsHandle;						/**< �n���h��							*/

/* ���w�֐� */
#define KsSin(_x)				sinf(_x)						/**< sin							*/
#define KsSinh(_x)				sinhf(_x)						/**< �n�C�p�[�{���b�Nsin				*/
#define KsCos(_x)				cosf(_x)						/**< cos							*/
#define KsCosh(_x)				coshf(_x)						/**< �n�C�p�[�{���b�Ncos				*/
#define KsTan(_x)				tanf(_x)						/**< tan							*/
#define KsTanh(_x)				tanhf(_x)						/**< �n�C�p�[�{���b�Ntan				*/
#define KsASin(_x)				asinf(_x)						/**< asin							*/
#define KsASinh(_x)				asinhf(_x)						/**< �n�C�p�[�{���b�Nasin				*/
#define KsACos(_x)				acosf(_x)						/**< acos							*/
#define KsACosh(_x)				acoshf(_x)						/**< �n�C�p�[�{���b�Nacos				*/
#define KsATan(_x)				atanf(_x)						/**< atan							*/
#define KsATan2(_x,_y)			atan2f(_x,_y)					/**< atan2							*/
#define KsAbs(_x)				abs(_x)							/**< abs							*/
#define KsFabs(_x)				fabsf(_x)						/**< fabs							*/
#define KsExp(_x)				expf(_x)						/**< exp(�w�����v�Z)					*/
#define KsFmod(_x,_y)			fmodf(_x,_y)					/**< fmod(���������_���̏�]���v�Z)		*/
#define KsLogE(_x)				logf(_x)						/**< log							*/
#define KsLog10(_x)				log10f(_x)						/**< log10							*/
#define KsModf(_x,_y)			modf(_x,_y)						/**< modf							*/
#define KsPow(_x,_y)			pow(_x,_y)						/**< pow(x �� y ����v�Z����)			*/
#define KsSqrt(_x)				sqrtf(_x)						/**< ������							*/
#define KsRsqrt(_x)				rsqrtf(_x)						/**< �������̋t��						*/

#define KsFloor(_x)				s_cast<KsReal>(s_cast<KsInt32>(_x))

#define ksPI					(3.14159265358979323846264338f)	/**< �~����(��)						*/
#define ksHALF_PI				(1.57079632679489661923132169f)	/**< �~����(��/�Q)						*/
#define ksTWO_PI				(6.28318530717958647692528676f)	/**< �~����(�Q��)						*/
#define ksTOLERANCE				(0.0001f)						/**< �ł��؂�덷						*/
#define ksTOLERANCE2			(0.00000001f)					/**< �ł��؂�덷�Q					*/
#define ksPATH_MAX				( 512 )							/**< �ő�p�X��						*/

#endif	/* __KSTYPE_H__ */

