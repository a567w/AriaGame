/************************************************************************************************/
/** 
 * @file		KsFlashTagType.h
 * @brief		
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSFLASHTAGTYPE_H__
#define __KSFLASHTAGTYPE_H__
/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "./core/KsCore.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/


enum ksFLASH_TAG_TYPE
{
	ksFLASH_TAG_DEFINESHAPE			=  2,
	ksFLASH_TAG_DEFINESHAPE2		= 22,
	ksFLASH_TAG_DEFINESHAPE3		= 32,
	ksFLASH_TAG_DEFINEMORPHSHAPE	= 46,
	ksFLASH_TAG_DEFINEBITS			=  6,
	ksFLASH_TAG_DEFINEBITSJPEG2		= 21,
	ksFLASH_TAG_DEFINEBITSJPEG3		= 35,
	ksFLASH_TAG_DEFINELOSSLESS		= 20,
	ksFLASH_TAG_DEFINELOSSLESS2		= 36,
	ksFLASH_TAG_JPEGTABLES			=  8,
	ksFLASH_TAG_DEFINEBUTTON		=  7,
	ksFLASH_TAG_DEFINEBUTTON2		= 34,
	ksFLASH_TAG_DEFINEBUTTONCXFORM	= 23,
	ksFLASH_TAG_DEFINEBUTTONSOUND	= 17,
	ksFLASH_TAG_DEFINEFONT			= 10,
	ksFLASH_TAG_DEFINEFONT2			= 48,
	ksFLASH_TAG_DEFINEFONTINFO		= 13,
	ksFLASH_TAG_DEFINEEDITTEXT		= 37,
	ksFLASH_TAG_DEFINETEXT			= 11,
	ksFLASH_TAG_DEFINETEXT2			= 33,
	ksFLASH_TAG_DEFINESOUND			= 14,
	ksFLASH_TAG_SOUNDSTREAMBLOCK	= 19,
	ksFLASH_TAG_SOUNDSTREAMHEAD		= 18,
	ksFLASH_TAG_SOUNDSTREAMHEAD2	= 45,
	ksFLASH_TAG_DEFINESPRITE		= 39,
	ksFLASH_TAG_PLACEOBJECT			=  4,
	ksFLASH_TAG_PLACEOBJECT2		= 26,
	ksFLASH_TAG_REMOVEOBJECT		=  5,
	ksFLASH_TAG_REMOVEOBJECT2		= 28,
	ksFLASH_TAG_SHOWFRAME			=  1,
	ksFLASH_TAG_SETBACKGROUNDCOLOR	=  9,
	ksFLASH_TAG_FRAMELABEL			= 43,
	ksFLASH_TAG_PROTECT				= 24,
	ksFLASH_TAG_STARTSOUND			= 15,
	ksFLASH_TAG_END					=  0,
	ksFLASH_TAG_DOACTION			= 12,
	ksFLASH_TAG_EXPORTASSETS		= 56,
	ksFLASH_TAG_IMPORTASSETS		= 57

};

#endif /* __KSFLASHTAGTYPE_H__ */


