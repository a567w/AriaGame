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
#ifndef __KSFLASHCOLOR_H__
#define __KSFLASHCOLOR_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsFlashColor
 * @brief		Flash(SWF)Header
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
class KsFlashColor
{
	public: 
	    KsFlashColor();
		KsFlashColor( KsUInt8 r, KsUInt8 g, KsUInt8 b );
		KsFlashColor( KsUInt8 r, KsUInt8 g, KsUInt8 b, KsUInt8 a );

		KsInt32			getNumBits();
	    
		KsBool			getAlphaWriteMode() const { return m_bAlpha; }

		KsUInt8			getRed() const { return m_red; }
		KsUInt8			getGreen() const { return m_green; }
		KsUInt8			getBlue() const { return m_blue; }
		KsUInt8			getAlpha() const { return m_alpha; }
	
		void			setAlphaWriteMode( KsBool bAlpha ) { m_bAlpha = bAlpha; }

		void			setRed( KsUInt8 red ) { m_red = red; }
		void			setGreen(  KsUInt8 green ) { m_green = green; }
		void			setBlue(  KsUInt8 blue ) { m_blue = blue; }
		void			setAlpha( KsUInt8 alpha ) { m_alpha = alpha; }

	    void			setRGBA( KsUInt8 r, KsUInt8 g, KsUInt8 b, KsUInt8 a );
	    void			setRGB( KsUInt8 r, KsUInt8 g, KsUInt8 b );
	private:    
	    KsBool			m_bAlpha;
	    KsUInt8			m_red;
	    KsUInt8			m_green;
	    KsUInt8			m_blue;
	    KsUInt8			m_alpha;
};

		
class KsFlashColorTransform : public KsFlashVersion
{
	public:
								KsFlashColorTransform();
		
								KsFlashColorTransform( KsBool add, KsFlashColor& addColor, KsBool mult, KsFlashColor& multColor );
		
		KsBool					hasAdd() const { return m_add; }
		KsBool					hasMult() const { return m_mult; }
	    
	    KsFlashColor			getAddColor() const { return m_addColor; }
	    KsFlashColor			getMultColor() const { return m_multColor; }

	private:
	    KsBool					m_add;
	    KsBool					m_mult;
	    KsFlashColor			m_addColor;
	    KsFlashColor			m_multColor;
};

#endif	/* __KSFLASHCOLOR_H__ */

