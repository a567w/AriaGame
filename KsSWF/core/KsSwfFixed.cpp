/************************************************************************************************/
/** 
 * @file		KsSwfFixed.cpp
 * @brief		固定小数点(32bit)
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsSWF/KsSWFPreCompile.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KsSwfFixed::KsSwfFixed()
	: m_upperval( 0 )
	, m_lowerval( 0 )
{
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KsSwfFixed::KsSwfFixed( KsInt16 upperval, KsUInt16 lowerval )
	: m_upperval( upperval )
	, m_lowerval( lowerval )
{
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KsSwfFixed::KsSwfFixed( KsReal64 f )
	: m_upperval( (KsUInt16)floor( f ) )
	, m_lowerval( (KsUInt16)( (f-floor(f) ) * 0x10000 ) )
{
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KsUInt32 KsSwfFixed::convertToRaw() const
{
	KsUInt32 r = ((KsInt32)m_upperval)<<16;
	r |= m_lowerval;
	return r;
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsSwfFixed::getFromRaw( KsInt32 raw )
{
	m_upperval = raw >> 16;
	m_lowerval = (raw & 0xffff);
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KsReal64 KsSwfFixed::convertToDouble() const
{
	return m_upperval + (KsReal64)m_lowerval / 0x10000;
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsSwfFixed::getFromDouble( KsReal64 f )
{
	m_upperval = (KsUInt16)floor( f );
	m_lowerval = (KsUInt16)((f-floor( f ))*0x10000);
}


