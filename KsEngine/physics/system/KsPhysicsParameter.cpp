/************************************************************************************************/
/** 
 * @file		KsPhysicsParameter.h
 * @brief		物理シミュレーションシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"
#include "KsPhysicsParameter.h"

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
KsPhysicsParameter::KsPhysicsParameter()
	: m_type( 0 )
	, m_noCopyToBone( ksFALSE )
	, m_pBone( 0 )
	, m_pRigidBody( 0 )
{

}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsPhysicsParameter::~KsPhysicsParameter()
{

}

/************************************************************************************************/
/*
 * 更新処理
 */
/************************************************************************************************/
void KsPhysicsParameter::update( KsReal elapsedTime )
{
	if( m_type != 0 && !m_noCopyToBone )
	{
		//btTransform		bttrBoneTransform = m_pRigidBody->getCenterOfMassTransform() * m_invBoneOffset;

		//bttrBoneTransform.getOpenGLMatrix( (KsReal *)m_pBone->m_worldTransform );

		m_pBone->m_worldTransform = m_invBoneOffset * m_pRigidBody->getCenterOfMassTransform();
	}
}


//==================
// ボーン位置あわせ
//==================
void KsPhysicsParameter::fixPosition( KsReal elapsedTime )
{
#if 0
	if( m_type == 2 )
	{
		KsVector3d		bonePos = m_pBone->getWorldTransform().getTranslate();

		btTransform		transform = m_pRigidBody->getCenterOfMassTransform();

		transform.setOrigin( KsVector3d::ZERO );
		transform = m_boneOffset * transform;

		transform.setOrigin( transform.getOrigin() + KsVector3d( bonePos.x, bonePos.y, bonePos.z ) );

		KsReal	fRate = 0.2f * fElapsedFrame;
		if( fRate > 1.0f )
		{
			fRate = 1.0f;
		}
		m_pRigidBody->translate( (transform.getOrigin() - m_pRigidBody->getCenterOfMassTransform().getOrigin()) * fRate );
	}
#endif
}

//========================================
// 剛体をボーンの位置へ強制的に移動させる
//========================================
void KsPhysicsParameter::moveToBonePos()
{
#if 0
	if( m_type != 0 )
	{
		KsVector3d		bonePos = m_pBone->getWorldTransform().getTranslate();

		KsMatrix4x4		transform = m_pRigidBody->getCenterOfMassTransform();

		transform.setOrigin( KsVector3d::ZERO );
		transform = m_boneOffset * transform;

		transform.setOrigin( transform.getOrigin() + KsVector3d( bonePos.x, bonePos.y, bonePos.z ) );
		transform.setBasis( m_pRigidBody->getWorldTransform().getBasis() );

		m_pRigidBody->setCenterOfMassTransform( transform );

		m_pRigidBody->setLinearVelocity( KsVector3d::ZERO );
		m_pRigidBody->setAngularVelocity( KsVector3d::ZERO );
		m_pRigidBody->setInterpolationLinearVelocity( KsVector3d::ZERO );
		m_pRigidBody->setInterpolationAngularVelocity( KsVector3d::ZERO );
		m_pRigidBody->setInterpolationWorldTransform( m_pRigidBody->getCenterOfMassTransform() );
		m_pRigidBody->clearForces();
	}
#endif
}
