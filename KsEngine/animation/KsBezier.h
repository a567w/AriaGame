/************************************************************************************************/
/** 
 * @file		KsBezier.h
 * @brief		ベジェ曲線クラス
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSBEZIER_H__
#define __KSBEZIER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsBezier
 * @brief		アニメーション
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsBezier
{
	private:
		static const KsInt32	DIV_NUM = 16;

	private:
		KsReal		m_value[ DIV_NUM + 1 ];
		KsBool		m_bLinear;

	public:
		void		setup( KsReal fPointX1, KsReal fPointY1, KsReal fPointX2, KsReal fPointY2 );
		KsReal		getInterValue( KsReal fT ) const;

	private:
		KsReal		getValue( KsReal fX, KsReal fX1, KsReal fY1, KsReal fX2, KsReal fY2 );
};


#endif /* __KSBEZIER_H__ */

