/************************************************************************************************/
/** 
 * @file		KsPhysicsSystemBullet.h
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
#include "KsPhysicsBullet/KsPhysicsBulletPreCompile.h"
#include "KsPhysicsSystemBullet.h"

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
KsPhysicsSystemBullet::KsPhysicsSystemBullet()
{
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsPhysicsSystemBullet::~KsPhysicsSystemBullet()
{
}

/************************************************************************************************/
/*
 * 初期化処理
 * @param		pParam				パラメータ
 * @retval		ksTRUE				初期化成功
 * @retval		ksFALSE				初期化失敗
 */
/************************************************************************************************/
KsBool KsPhysicsSystemBullet::initialize( void* pParam )
{
	return ksTRUE;
}

/************************************************************************************************/
/*
 * 後処理
 * @retval		ksTRUE				後処理成功
 * @retval		ksFALSE				後処理失敗
 */
/************************************************************************************************/
KsBool KsPhysicsSystemBullet::terminate()
{
	return ksTRUE;
}

/************************************************************************************************/
/*
 * ワールドを生成する
 */
/************************************************************************************************/
KsWorld* KsPhysicsSystemBullet::createWorld()
{
	KsWorld*	pWorld = new KsWorldBullet();

	if( NULL == m_pWorld )
	{
		m_pWorld = pWorld;
	}

	return pWorld;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsCollisionShape* KsPhysicsSystemBullet::createShape( ksSHAPE_TYPE type, const KsVector3d& halfExtents )
{
	switch( type )
	{
		case ksSHAPE_SPHERE:
		{
			return new KsSphereShapeBullet( halfExtents.x );
		}
		case ksSHAPE_BOX:
		{
			return new KsBoxShapeBullet( halfExtents );
		}
		case ksSHAPE_CAPSULE:
		{
			return new KsCapsuleShapeBullet( halfExtents.x, halfExtents.y );
		}
		default:
			break;
	}

	return NULL;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsRigidBody* KsPhysicsSystemBullet::createRigidBody( const KsRigidBody::KsRigidBodyConstructionInfo& Info )
{
	return new KsRigidBodyBullet( Info );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsMotionState* KsPhysicsSystemBullet::createMotionState( ksMOTION_STATE_TYPE type, const KsMatrix4x4* pTransform, const KsMatrix4x4* pOffset, KsBone* pBone )
{
	switch( type )
	{
		case ksMOTION_STATE_DEFAULT:
		{
			return new KsDefaultMotionState( *pTransform );	
		}
		case ksMOTION_STATE_KINEMATIC:
		{
			return new KsKinematicMotionState( *pTransform, *pOffset, pBone );
		}
		default:
			break;
	}

	return NULL;
}

KsConstraint* KsPhysicsSystemBullet::createConstraint( ksCONSTRAINT_TYPE type, KsRigidBody& rbA, KsRigidBody& rbB, const KsMatrix4x4& frameInA, const KsMatrix4x4& frameInB, KsBool useLinearReferenceFrameA )
{
	switch( type )
	{
		case ksCONSTRAINT_SPRING:
		{
			return new KsSpringConstraintBullet( rbA, rbB, frameInA, frameInB, useLinearReferenceFrameA );
		}
		default:
			break;
	}

	return NULL;
}

