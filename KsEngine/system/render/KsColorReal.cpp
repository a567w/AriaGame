/************************************************************************************************/
/** 
 * @file		KsColorReal.cpp
 * @brief		カラー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsColor.h"
#include "KsColorReal.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
const KsColorReal	KsColorReal::RED( 1.0f, 0.0f, 0.0f, 0.0f );
const KsColorReal	KsColorReal::GREEN( 0.0f, 1.0f, 0.0f, 0.0f );
const KsColorReal	KsColorReal::BLUE( 0.0f, 0.0f, 1.0f, 0.0f );
const KsColorReal	KsColorReal::WHITE( 1.0f, 1.0f, 1.0f, 0.0f );
const KsColorReal	KsColorReal::BLACK( 0.0f, 0.0f, 0.0f, 0.0f );

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsColorReal& KsColorReal::operator = ( const KsColor& refColor )
{
	KsInt32		inv = 1 / 255;
	
	set( ( KsReal )( inv*refColor.getRed() ), ( KsReal )( inv*refColor.getGreen() ), ( KsReal )( inv*refColor.getBlue() ), ( KsReal )( inv*refColor.getAlpha() ) );
	
	return ( *this );
}

