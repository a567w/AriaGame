/************************************************************************************************/
/** 
 * @file		KsAnim2DPart.h
 * @brief		ボーン
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSANIM2DPART_H__
#define __KSANIM2DPART_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsCore.h"
#include "KsColor.h"
#include "KsVector.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsTexture;

/************************************************************************************************/
/**
 * @class		KsAnim2DPart
 * @brief		アニメパーツ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsAnim2DPart
{
	public:
						KsAnim2DPart();
		virtual		~KsAnim2DPart();

	public:
		KsReal			m_x;
		KsReal			m_y;
		KsReal			m_w;
		KsReal			m_h;
		KsReal			m_u0;
		KsReal			m_v0;
		KsReal			m_u1;
		KsReal			m_v1;
		KsColor			m_color;
		KsTexture*		m_pTexture;
};


#endif /* __KSANIM2DPART_H__ */



