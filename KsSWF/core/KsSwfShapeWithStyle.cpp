/************************************************************************************************/
/** 
 * @file		KsSwfShapeWithStyle.h
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
#include "KsSWF/KsSWFPreCompile.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

KsSwfShapeWithStyle::KsSwfShapeWithStyle()
	: m_red( 0xff )
	, m_green( 0xff )
	, m_blue( 0xff )
	, m_alpha( 0xff )
{
}

KsSwfShapeWithStyle::KsSwfShapeWithStyle( KsUInt8 r, KsUInt8 g, KsUInt8 b )
	: m_red( r )
	, m_green( g )
	, m_blue( b )
	, m_alpha( 0xff )
{
}


KsSwfShapeWithStyle::KsSwfShapeWithStyle( KsUInt8 r, KsUInt8 g, KsUInt8 b, KsUInt8 a )
	: m_red( r )
	, m_green( g )
	, m_blue( b )
	, m_alpha( a )
{
}


void KsSwfShapeWithStyle::setRGBA( KsUInt8 r, KsUInt8 g, KsUInt8 b, KsUInt8 a )
{
	m_red   = r;
	m_green = g;
	m_blue  = b;
	m_alpha = a;
}

void KsSwfShapeWithStyle::setRGB( KsUInt8 r, KsUInt8 g, KsUInt8 b )
{
	m_red   = r;
	m_green = g;
	m_blue  = b;
}

