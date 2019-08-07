/************************************************************************************************/
/** 
 * @file		KsSwfARGB.h
 * @brief		
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSWFARGB_H__
#define __KSSWFARGB_H__

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
 * @class		KsSwfARGB
 * @brief		Flash(SWF)Header
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
class KsSwfARGB
{
		friend class KsSwfImporter;

	private:
		KsUInt8				m_alpha;
		KsUInt8				m_red;
		KsUInt8				m_green;
		KsUInt8				m_blue;

	public: 
							KsSwfARGB();
							KsSwfARGB( KsUInt8 r, KsUInt8 g, KsUInt8 b );
							KsSwfARGB( KsUInt8 r, KsUInt8 g, KsUInt8 b, KsUInt8 a );

		KsUInt8				getRed() const { return m_red; }
		KsUInt8				getGreen() const { return m_green; }
		KsUInt8				getBlue() const { return m_blue; }
		KsUInt8				getAlpha() const { return m_alpha; }

		void				setRed( KsUInt8 red ) { m_red = red; }
		void				setGreen(  KsUInt8 green ) { m_green = green; }
		void				setBlue(  KsUInt8 blue ) { m_blue = blue; }
		void				setAlpha( KsUInt8 alpha ) { m_alpha = alpha; }

		void				setRGBA( KsUInt8 r, KsUInt8 g, KsUInt8 b, KsUInt8 a );
		void				setRGB( KsUInt8 r, KsUInt8 g, KsUInt8 b );
};

#endif	/* __KSSWFARGB_H__ */

