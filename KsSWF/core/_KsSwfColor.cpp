/************************************************************************************************/
/** 
 * @file		KsSwfColor.h
 * @brief		
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsSwfColor.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
KsSwfColor::KsSwfColor() : m_red( 0xff ), m_green( 0xff ), m_blue( 0xff ), m_alpha( 0xff ), m_bAlpha( ksFALSE )
{
}
KsSwfColor::KsSwfColor( KsUInt8 r, KsUInt8 g, KsUInt8 b )
	: m_red( r )
	, m_green( g )
	, m_blue( b )
	, m_alpha( 0xff )
	, m_bAlpha( ksFALSE )
{
}


KsSwfColor::KsSwfColor( KsUInt8 r, KsUInt8 g, KsUInt8 b, KsUInt8 a )
	: m_red( r )
	, m_green( g )
	, m_blue( b )
	, m_alpha( a )
	, m_bAlpha( ksTRUE )
{
}


void KsSwfColor::setRGBA( KsUInt8 r, KsUInt8 g, KsUInt8 b, KsUInt8 a )
{
	m_red   = r;
	m_green = g;
	m_blue  = b;
	m_alpha = a;
}
void KsSwfColor::setRGB( KsUInt8 r, KsUInt8 g, KsUInt8 b )
{
	m_red   = r;
	m_green = g;
	m_blue  = b;
}



KsSwfColorTransform::KsSwfColorTransform()
	: m_bAdd( ksFALSE )
	, m_bMult( ksFALSE )
{
}

KsSwfColorTransform::KsSwfColorTransform( KsBool add, KsSwfColor& addColor, KsBool mult, KsSwfColor& multColor )
	: m_bAdd( add )
	, m_bMult( mult )
	, m_addColor( addColor )
	, m_multColor( multColor )
{
}

