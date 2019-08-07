/************************************************************************************************/
/** 
 * @file		KsAnim2DKeyFrame.cpp
 * @brief		アニメーションのキーフレーム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsAnim2DKeyFrame.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsAnim2DKeyFrame::KsAnim2DKeyFrame()
	: m_flags( 0 )
	, m_time( 0.0f )
	, m_pos( KsVector2d::ZERO )
	, m_scale( KsVector2d::ONE )
	, m_angle( 0.0f )
	, m_color( KsColor::WHITE )
{
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsAnim2DKeyFrame::~KsAnim2DKeyFrame()
{
}

