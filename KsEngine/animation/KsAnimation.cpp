/************************************************************************************************/
/** 
 * @file		KsAnimation.cpp
 * @brief		アニメーションクラス
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"

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
KsAnimation::KsAnimation( const KsString& animationName, KsAnimationChannel* pAnimationChannel )
{
	m_animationName  = animationName;
	m_boneAnimations = pAnimationChannel;
	m_duration       = 0.0f;

	KsInt32 maxFrame = 0;

	for( KsUInt32 ii=0; ii<pAnimationChannel->getNumCollection(); ii++ )
	{
		KsKeyFrameCollection*	pItem = pAnimationChannel->getKeyFrameCollection( ii );

		if( pItem->getDuration() > maxFrame )
		{
			maxFrame = pItem->getDuration();
		}
	}

	m_duration = (KsReal)maxFrame;
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsAnimation::~KsAnimation()
{
}

