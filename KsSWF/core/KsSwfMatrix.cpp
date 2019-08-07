/************************************************************************************************/
/** 
 * @file		KsSwfMatrix.h
 * @brief		SWF用マトリックス
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
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




KsSwfMatrix::KsSwfMatrix()
	: m_hasScale( ksFALSE )
	, m_scaleX( 0 )
	, m_scaleY( 0 )
	, m_hasRotate( ksFALSE )
	, m_rotateX( 0 )
	, m_rotateY( 0 )
	, m_translateX( 0 )
	, m_translateY( 0 )
{

}


KsSwfMatrix::KsSwfMatrix(	KsBool		hasScale,
							KsSwfFixed	scaleX,
							KsSwfFixed	scaleY,
							KsBool		hasRotate,
							KsSwfFixed	rotateX,
							KsSwfFixed	rotateY,
							KsInt16	translateX,
							KsInt16	translateY )
	: m_hasScale( ksFALSE )
	, m_scaleX( scaleX )
	, m_scaleY( scaleY )
	, m_hasRotate( ksFALSE )
	, m_rotateX( rotateX )
	, m_rotateY( rotateY )
	, m_translateX( translateX )
	, m_translateY( translateY )
{
}

void KsSwfMatrix::setScale( KsSwfFixed scaleX, KsSwfFixed scaleY )
{
	m_scaleX = scaleX;
	m_scaleY = scaleY;
	m_hasScale = ksTRUE;
}

void KsSwfMatrix::setRotate( KsSwfFixed rotateX, KsSwfFixed rotateY )
{
	m_rotateX   = rotateX;
	m_rotateY   = rotateY;
	m_hasRotate = ksTRUE;
}

void KsSwfMatrix::setTranslate( KsInt16 translateX, KsInt16 translateY )
{
	m_translateX = translateX;
	m_translateY = translateY;
}

