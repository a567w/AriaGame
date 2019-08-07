/************************************************************************************************/
/** 
 * @file		KsSwfRGB.h
 * @brief		
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSWFRGB_H__
#define __KSSWFRGB_H__

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
 * @class		KsSwfRGB
 * @brief		Flash(SWF)Header
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
class KsSwfRGB
{
		friend class KsSwfImporter;

	private:
		KsUInt8			m_red;
		KsUInt8			m_green;
		KsUInt8			m_blue;

	public: 
						KsSwfRGB();
						KsSwfRGB( KsUInt8 r, KsUInt8 g, KsUInt8 b );

		KsUInt8			getRed() const { return m_red; }
		KsUInt8			getGreen() const { return m_green; }
		KsUInt8			getBlue() const { return m_blue; }
		
		void			setRed( KsUInt8 red ) { m_red = red; }
		void			setGreen( KsUInt8 green ) { m_green = green; }
		void			setBlue( KsUInt8 blue ) { m_blue = blue; }
		void			setRGB( KsUInt8 r, KsUInt8 g, KsUInt8 b );
};


#endif	/* __KSSWFRGB_H__ */

