/************************************************************************************************/
/** 
 * @file		KsSwfCommon.cpp
 * @brief		SWF共通ヘッダ
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsSwfCommon.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

KsSwfFixed::KsSwfFixed()
	: m_upperval( 0 )
	, m_lowerval( 0 )
{
}

KsSwfFixed::KsSwfFixed( KsInt16 upperval, KsUInt16 lowerval )
	: m_upperval( upperval )
	, m_lowerval( lowerval )
{
}

KsSwfFixed::KsSwfFixed( KsReal64 f )
	: m_upperval( (KsUInt16)floor( f ) )
	, m_lowerval( (KsUInt16)( (f-floor(f) ) * 0x10000 ) )
{
}


KsUInt32 KsSwfFixed::convertToRaw() const
{
	KsUInt32 r = ((KsInt32)m_upperval)<<16;
	r |= m_lowerval;
	return r;
}
void KsSwfFixed::getFromRaw( KsInt32 raw )
{
	m_upperval = raw >> 16;
	m_lowerval = (raw & 0xffff);
}

KsReal64 KsSwfFixed::convertToDouble() const
{
	return m_upperval + (KsReal64)m_lowerval / 0x10000;
}
void KsSwfFixed::getFromDouble( KsReal64 f )
{
	m_upperval = (KsUInt16)floor( f );
	m_lowerval = (KsUInt16)((f-floor( f ))*0x10000);
}
		


KsSwfFixed16::KsSwfFixed16()
	: m_upperval( 0 )
	, m_lowerval( 0 )
{
}

KsSwfFixed16::KsSwfFixed16( KsInt8 u, KsUInt8 l )
	: m_upperval( u )
	, m_lowerval( l )
{
}

KsSwfFixed16::KsSwfFixed16( KsReal64 f )
	: m_upperval( (KsInt8)floor( f ) )
	, m_lowerval( (KsUInt8)((f-floor(f))*0x100) )
{
}




KsUInt16 KsSwfFixed16::convertToRaw() const
{
    KsUInt16 r = ((KsInt16)m_upperval)<<8;
    r |= m_lowerval;
    return r;
}
void KsSwfFixed16::setFromRaw(KsInt16 raw)
{
    m_upperval = raw >> 8;
    m_lowerval = (raw & 0xff);
}
KsReal64 KsSwfFixed16::convertToDouble()
{
    return m_upperval + (KsReal64)m_lowerval / 0x100;
}
void KsSwfFixed16::setFromDouble(KsReal64 f)
{
    m_upperval = (KsInt8)floor(f);
    m_lowerval = (KsUInt8)((f-floor(f))*0x100);
}

