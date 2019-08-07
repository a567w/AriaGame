/************************************************************************************************/
/** 
 * @file		KsBone.cpp
 * @brief		ボーン関係
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
KsAnimationController::KsAnimationController( KsAnimation* pAnimation )
	: m_pAnimation( pAnimation )
	, m_speedFactor( 1.0f )
	, m_elapsedTime( 0.0f )
	, m_elapsed( 0.0f )
	, m_isLooping( ksTRUE )
{
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsAnimationController::~KsAnimationController()
{
}

/************************************************************************************************/
/*
 * アニメーション更新
 */
/************************************************************************************************/
void KsAnimationController::update( KsReal gameTime )
{
	m_elapsed = m_speedFactor * gameTime;

	if( m_isLooping )
	{
		if( m_elapsed > 0.0f )
		{
			m_elapsedTime += m_elapsed;

			if( m_elapsedTime > m_pAnimation->getDuration() )
			{
				//OnAnimationEnded(null);
				m_elapsedTime -= m_pAnimation->getDuration();
			}
		}
	}
	else if( m_elapsedTime != m_pAnimation->getDuration() )
	{
		if( m_elapsed > 0.0f )
		{
			m_elapsedTime += m_elapsed;

			if( m_elapsedTime >= m_pAnimation->getDuration() || m_elapsedTime < 0.0f )
			{
				m_elapsedTime = m_pAnimation->getDuration();

				//OnAnimationEnded(null);
			}
		}
	}

	
	static float xxx = 80.0f;
	{
		//m_elapsedTime = xxx;
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsMatrix4x4 KsAnimationController::getCurrentBoneTransform( const KsBone* pBone )
{
	KsAnimationChannel*		channels   = m_pAnimation->getAnimationChannels();
	KsKeyFrameCollection*	channel    = channels->getKeyFrameCollection( pBone->getName() );
	KsMatrix4x4				poseMatrix;

	if( channel )
	{
		poseMatrix = channel->getPoseMatrix( m_elapsedTime );
	}

	return poseMatrix;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsBool KsAnimationController::containsAnimationTrack( const KsBone* pBone )
{
	return m_pAnimation->getAnimationChannels()->hasAffectsBone( pBone->getName() );
}

