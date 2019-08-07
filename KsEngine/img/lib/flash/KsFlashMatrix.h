/************************************************************************************************/
/** 
 * @file		KsFlashMatrix.h
 * @brief		FLASH用マトリックス
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSFLASMATRIXY_H__
#define __KSFLASMATRIXY_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsFlashBase.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsFlashMatrix
 * @brief		FLASH用マトリックス
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 * @note		なし
 */
/************************************************************************************************/
class KsFlashMatrix
{
	public:
							KsFlashMatrix();

							KsFlashMatrix( KsFlashFixed scaleX,  KsFlashFixed scaleY );

							KsFlashMatrix( KsFlashFixed rotateX,  KsFlashFixed rotateY );

							KsFlashMatrix( KsInt16 translateX, KsInt16 translateY );

							KsFlashMatrix( KsBool hasScale, KsFlashFixed scaleX,  KsFlashFixed m_scaleY,
										   KsBool hasRotate, KsFlashFixed rotateX, KsFlashFixed m_rotateY,
										   KsInt16 translateX, KsInt16 translateY );

	    void				setScale( KsFlashFixed scaleX, KsFlashFixed scaleX );
	    void				setRotate( KsFlashFixed rotateX, KsFlashFixed rotateY );
	    void				setTranslate( KsInt16 translateX, KsInt16 translateY );

	    KsBool				hasScale() const { return m_hasScale; }
	    KsBool				hasRotate() const { return m_hasRotate; }

	    KsFlashFixed		getRotateX() const { return m_rotateX; }
	    KsFlashFixed		getRotateY() const { return m_rotateY; }

	    KsFlashFixed		getScaleX() const { return m_scaleX; }
	    KsFlashFixed		getScaleY() const { return m_scaleY; }

	    KsFlashFixed		getTranslateX() const { return m_translateX; }
	    KsFlashFixed		getTranslateY() const { return m_translateY; }

	private:
	    KsBool				m_hasScale;
	    KsFlashFixed		m_scaleX;
	    KsFlashFixed		m_scaleY;
	    KsBool				m_hasRotate;
	    KsFlashFixed		m_rotateX;
	    KsFlashFixed		m_rotateY;
	    KsInt16				m_translateX;
	    KsInt16				m_translateY;
};


KsFlashMatrix::KsFlashMatrix()
	: m_hasScale( ksFALSE )
	, m_scalex( 0 )
	, scaley( 0 )
	, m_hasRotate( ksFALSE )
	, m_rotatex( 0 )
	, rotatey( 0 )
	, m_translateX( 0 )
	, m_translateY( 0 )
{
}

							KsFlashMatrix( KsFlashFixed scaleX,  KsFlashFixed scaleY )
										: m_hasScale( ksTRUE ), m_scaleX( scaleX ), m_scaleY( scaleY )
										  m_hasRotate( ksFALSE ), m_rotatex( 0 ), rotatey( 0 ),
										  m_translateX( 0 ), m_translateY( 0 ){}

							KsFlashMatrix( KsFlashFixed rotateX,  KsFlashFixed rotateY )
									: m_hasScale( ksFALSE ), m_scaleX( 0 ), m_scaleY( 0 )
									  m_hasRotate( ksTRUE ), m_rotatex( rotateX ), rotatey( rotateY ),
									  m_translateX( 0 ), m_translateY( 0 ){}

							KsFlashMatrix( KsInt16 translateX, KsInt16 translateY )
									 : m_hasScale( ksFALSE ), m_scalex( 0 ), scaley( 0 ),
									  m_hasRotate( ksFALSE ), m_rotatex( 0 ), rotatey( 0 ),
									  m_translateX( translateX ), m_translateY( translateY ){}

							KsFlashMatrix( KsBool hasScale, KsFlashFixed scaleX,  KsFlashFixed m_scaleY,
										   KsBool hasRotate, KsFlashFixed rotateX, KsFlashFixed m_rotateY,
										   KsInt16 translateX, KsInt16 translateY )
										: m_hasScale( hasScale ), m_scaleX( scaleX ), m_scaleY( scaleY ),
										  m_hasRotate( hasRotate ), m_rotateX( rotateX ), m_rotateY( rotateY ),
										  m_translateX( translateX ), m_translateY( translateY ){}

	    void				setScale( KsFlashFixed scaleX, KsFlashFixed scaleX ) { m_scaleX = scaleX; m_scaleY = scaleY; m_hasScale = ksTRUE; }
	    void				setRotate( KsFlashFixed rotateX, KsFlashFixed rotateY ) { m_rotateX = rotateX; m_rotateY = rotateY; m_hasRotate = ksTRUE; }
	    void				setTranslate( KsInt16 translateX, KsInt16 translateY ) { m_translateX = translateX; m_translateY = translateY; }



#endif /* __KSFLASMATRIXY_H__ */

