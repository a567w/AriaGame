/************************************************************************************************/
/** 
 * @file		KsSwfFixed16.h
 * @brief		固定小数点(16bit)
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSWFFIXED16_H__
#define __KSSWFFIXED16_H__

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
 * @class		KsSwfFixed16
 * @brief		固定小数点(16bit)
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
class KsSwfFixed16
{
	public:
		/**
		 * コンストラクタ
		 */
								KsSwfFixed16();

		/**
		 * コンストラクタ
		 * @param	upperval	整数部
		 * @param	lowerval	小数部
		 */
								KsSwfFixed16( KsInt8 upperval, KsUInt8 lowerval );

		/**
		 * コンストラクタ
		 * @param	f			実数値
		 */
								KsSwfFixed16( KsReal64 f ); 

		KsUInt16				convertToRaw() const;
		
		void					setFromRaw( KsInt16 raw );
		KsReal64				convertToDouble();
		void					setFromDouble( KsReal64 f );

	private:
		KsInt8					m_upperval;		/**< 整数部		*/
		KsUInt8					m_lowerval;		/**< 小数部		*/
};


#endif	/* __KSSWFFIXED16_H__ */

