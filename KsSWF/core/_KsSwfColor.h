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
#ifndef __KSSWFCOLOR_H__
#define __KSSWFCOLOR_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsTypeSwf.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsSwfColor
 * @brief		Flash(SWF)Header
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
class KsSwfColor
{
	    friend class KsSwfImporter;

	public: 
	    KsSwfColor();
		KsSwfColor( KsUInt8 r, KsUInt8 g, KsUInt8 b );
		KsSwfColor( KsUInt8 r, KsUInt8 g, KsUInt8 b, KsUInt8 a );
	    
		KsBool				getAlphaWriteMode() const { return m_bAlpha; }

		KsUInt8			getRed() const { return m_red; }
		KsUInt8			getGreen() const { return m_green; }
		KsUInt8			getBlue() const { return m_blue; }
		KsUInt8			getAlpha() const { return m_alpha; }
	
		void				setAlphaWriteMode( KsBool bAlpha ) { m_bAlpha = bAlpha; }

		void				setRed( KsUInt8 red ) { m_red = red; }
		void				setGreen(  KsUInt8 green ) { m_green = green; }
		void				setBlue(  KsUInt8 blue ) { m_blue = blue; }
		void				setAlpha( KsUInt8 alpha ) { m_alpha = alpha; }

	    void				setRGBA( KsUInt8 r, KsUInt8 g, KsUInt8 b, KsUInt8 a );
	    void				setRGB( KsUInt8 r, KsUInt8 g, KsUInt8 b );
	private:    
	    KsBool				m_bAlpha;
	    KsUInt8			m_red;
	    KsUInt8			m_green;
	    KsUInt8			m_blue;
	    KsUInt8			m_alpha;
};



		
class KsSwfColorTransform
{
		friend class KsSwfImporter;

	public:
								KsSwfColorTransform();
		
								KsSwfColorTransform( KsBool add, KsSwfColor& addColor, KsBool mult, KsSwfColor& multColor );
		
		KsBool					hasAdd() const { return m_bAdd; }
		KsBool					hasMult() const { return m_bMult; }
	    
	    KsSwfColor				getAddColor() const { return m_addColor; }
	    KsSwfColor				getMultColor() const { return m_multColor; }

	private:
	    KsBool					m_bAdd;
	    KsBool					m_bMult;
	    KsSwfColor				m_addColor;
	    KsSwfColor				m_multColor;
};



#endif	/* __KSSWFCOLOR_H__ */

