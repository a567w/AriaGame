/************************************************************************************************/
/**
 * @file		KsRand.h
 * @brief		乱数発生（高速バージョン）
 * @author		Tsukasa Kato
 * @date		2004/11/30
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSRAND_H__
#define __KSRAND_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsType.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * 乱数発生の種
 * @param	seed	乱数の種
 */
/************************************************************************************************/
ksENGINE_API void KsRandSeed( KsUInt32 seed );

/************************************************************************************************/
/**
 * 乱数発生
 * @return		0 <= return <= 65535 の乱数を返します
 */
/************************************************************************************************/
ksENGINE_API KsUInt32 KsRand();

/************************************************************************************************/
/**
 * 乱数発生
 * @return		0.0f <= return <= 1.0f の乱数を返します
 */
/************************************************************************************************/
ksENGINE_API KsReal KsRandF();

/************************************************************************************************/
/**
 * 乱数発生
 * @param	num		乱数範囲
 * @return			0 <= return <= num の乱数を返します
 */
/************************************************************************************************/
ksENGINE_API KsUInt32 KsRandX( KsUInt32 num );


#endif	/* __KSRAND_H__ */


