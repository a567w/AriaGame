/************************************************************************************************/
/** 
 * @file		KsFlashColor.h
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

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/


KsFlashColor::KsFlashColor() : m_red(0), m_green( 0 ), m_blue( 0 ), a( 0xff ), m_bAlpha( ksFalse )
{
}
KsFlashColor::KsFlashColor( KsInt16 r, KsInt16 g, KsInt16 b )
	: m_red( r )
	, m_green( g )
	, m_blue( b )
	, m_alpha( 0xff )
	, m_bAlpha( ksFalse )
{
}


KsFlashColor::KsFlashColor( KsInt16 r, KsInt16 g, KsInt16 b, KsInt16 a )
	: m_red( r )
	, m_green( g )
	, m_blue( b )
	, m_alpha( a )
	, m_bAlpha( ksTRUE )
{
}
	

KsInt32 KsFlashColor::getNumBits()
{ 
	if( m_alpha ){
		return KsMax( KsMax( KsGetBitSizeSigned( a ), KsGetBitSizeSigned( b ) ), KsMax( KsGetBitSizeSigned( r ), KsGetBitSizeSigned( g ) ) );
	}

    return KsMax( KsGetBitSizeSigned( b ), KsMax( KsGetBitSizeSigned( r ), KsGetBitSizeSigned( g ) ) );
}
	    

void KsFlashColor::setRGBA( KsInt16 r, KsInt16 g, KsInt16 b, KsInt16 a )
{
	m_red   = r;
	m_green = g;
	m_blue  = b;
	m_alpha = a;
}
void KsFlashColor::setRGB( KsInt16 r, KsInt16 g, KsInt16 b )
{
	m_red   = r;
	m_green = g;
	m_blue  = b;
}



KsFlashColorTransform::KsFlashColorTransform()
	: add( ksFALSE )
	, mult( ksFALSE )
{
}

KsFlashColorTransform::KsFlashColorTransform( KsBool add, KsFlashColor& addColor, KsBool mult, KsFlashColor& multColor )
	: m_add( add )
	, m_mult( mult )
	, m_addColor( addColor )
	, m_multColor( multColor )
{
}
