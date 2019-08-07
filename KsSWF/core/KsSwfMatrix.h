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
#ifndef __KSSWFMATRIXY_H__
#define __KSSWFMATRIXY_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsSwfMatrix
 * @brief		SWF用マトリックス
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 * @note		なし
 */
/************************************************************************************************/
class KsSwfMatrix
{
		friend class KsSwfImporter;
	public:
								KsSwfMatrix();
								KsSwfMatrix( KsBool			hasScale,
											 KsSwfFixed		scaleX,
											 KsSwfFixed		scaleY,
											 KsBool			hasRotate,
											 KsSwfFixed		rotateX,
											 KsSwfFixed		rotateY,
											 KsInt16		translateX,
											 KsInt16		translateY );

	    void					setScale( KsSwfFixed scaleX, KsSwfFixed scaleY );
	    void					setRotate( KsSwfFixed rotateX, KsSwfFixed rotateY );
	    void					setTranslate( KsInt16 translateX, KsInt16 translateY );

	    KsBool					hasScale() const { return m_hasScale; }
	    KsBool					hasRotate() const { return m_hasRotate; }

	    KsSwfFixed				getRotateX() const { return m_rotateX; }
	    KsSwfFixed				getRotateY() const { return m_rotateY; }

	    KsSwfFixed				getScaleX() const { return m_scaleX; }
	    KsSwfFixed				getScaleY() const { return m_scaleY; }

	    KsSwfFixed				getTranslateX() const { return m_translateX; }
	    KsSwfFixed				getTranslateY() const { return m_translateY; }

	private:
	    KsBool					m_hasScale;
	    KsSwfFixed				m_scaleX;
	    KsSwfFixed				m_scaleY;
	    KsBool					m_hasRotate;
	    KsSwfFixed				m_rotateX;
	    KsSwfFixed				m_rotateY;
	    KsInt16					m_translateX;
	    KsInt16					m_translateY;
};


#endif /* __KSSWFMATRIXY_H__ */

