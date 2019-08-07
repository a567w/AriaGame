/************************************************************************************************/
/** 
 * @file		KsWorldBullet.h
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
#include "KsWorldBullet.h"

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
KsWorldBullet::KsWorldBullet()
{
	// コリジョンコンフィグを作成する
	m_pCollisionConfig = new btDefaultCollisionConfiguration();

	// コリジョンディスパッチャを作成する
	m_pCollisionDispatcher = new btCollisionDispatcher( m_pCollisionConfig );

	// コリジョンワールドの最大サイズを指定する
	btVector3	btv3WorldAabbMin( -3000.0f, -3000.0f, -3000.0f );
	btVector3	btv3WorldAabbMax(  3000.0f,  3000.0f,  3000.0f );
	KsInt32		iMaxProxies = 1024;
	m_pOverlappingPairCache = new btAxisSweep3( btv3WorldAabbMin, btv3WorldAabbMax, iMaxProxies );

	// 拘束計算ソルバを作成する
	m_pSolver = new btSequentialImpulseConstraintSolver();

	// ワールドの作成
	m_pWorld = new btDiscreteDynamicsWorld( m_pCollisionDispatcher, m_pOverlappingPairCache, m_pSolver, m_pCollisionConfig );

	// 重力設定
	m_pWorld->setGravity( btVector3( 0.0f, -10.0f, 0.0f ) );	// ネクタイなどがふわふわするのでなんとなく2倍しておく

	//-----------------------------------------------------
	// 床用として無限平面を作成
	m_pGroundShape = new btStaticPlaneShape( btVector3( 0.0f, 1.0f, 0.0f ), 0.0f );

	// 床のトランスフォームを設定
	btTransform		groundTransform;
	groundTransform.setIdentity();

	// MotionStateを作成する。剛体の姿勢制御をするもの
	btMotionState*	pMotionState = new btDefaultMotionState( groundTransform );

	// 剛体を作成する
	// 質量 0.0、慣性テンソル 0.0 ならこの剛体は動かない
	btRigidBody::btRigidBodyConstructionInfo	rbInfo( 0.0f, pMotionState, m_pGroundShape, btVector3( 0.0f, 0.0f, 0.0f ) );
	btRigidBody*	pRigidBody = new btRigidBody( rbInfo );

	// 物理ワールドに床を追加
	m_pWorld->addRigidBody( pRigidBody );
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsWorldBullet::~KsWorldBullet()
{
	if( !m_pWorld )	return;

	for( KsInt32 i = m_pWorld->getNumCollisionObjects() - 1 ; i >= 0 ; i-- )
	{
		btCollisionObject*	pObj       = m_pWorld->getCollisionObjectArray()[i];
		btRigidBody*		pRigidBody = btRigidBody::upcast( pObj );

		if( pRigidBody && pRigidBody->getMotionState() )
		{
			btMotionState*	pMotionState = pRigidBody->getMotionState();
			ksDELETE( pMotionState );
		}

		m_pWorld->removeCollisionObject( pObj );

		ksDELETE( pObj );
	}

	ksDELETE( m_pGroundShape );
	ksDELETE( m_pWorld );
	ksDELETE( m_pSolver );
	ksDELETE( m_pOverlappingPairCache );
	ksDELETE( m_pCollisionDispatcher );
	ksDELETE( m_pCollisionConfig );
}


/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KsInt32 KsWorldBullet::stepSimulation( KsReal timeStep, KsInt32 maxSubSteps, KsReal fixedTimeStep )
{
	return m_pWorld->stepSimulation( timeStep, maxSubSteps, fixedTimeStep );
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsWorldBullet::addRigidBody( KsRigidBody* pRigidBody )
{

}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsWorldBullet::addRigidBody( KsRigidBody* pRigidBody, KsUInt16 group, KsUInt16 mask )
{
	btRigidBody*	pbtRigidBody = reinterpret_cast<btRigidBody*>( pRigidBody->getRigidBodyResource() );

	m_pWorld->addRigidBody( pbtRigidBody, group, mask );

	m_pRigidBodies.push_back( pRigidBody );
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsWorldBullet::removeRigidBody( KsRigidBody* pRigidBody )
{
	btRigidBody*	pbtRigidBody = reinterpret_cast<btRigidBody*>( pRigidBody->getRigidBodyResource() );

	m_pWorld->removeRigidBody( pbtRigidBody );

	KsUInt32	index = 0;

	for( KsUInt32 i=0; i<m_pRigidBodies.size(); i++ )
	{
		if( pRigidBody == m_pRigidBodies[ i ] )
		{
			index = i;
			break;
		}
	}

	m_pRigidBodies.erase( index );
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsWorldBullet::addConstraint( KsConstraint* pConstraint, KsBool disableCollisionsBetweenLinkedBodies )
{
	btTypedConstraint*	pbtConstraint = reinterpret_cast<btTypedConstraint*>( pConstraint->getConstraintResource() );

	m_pWorld->addConstraint( pbtConstraint );

	m_pConstraints.push_back( pConstraint );
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsWorldBullet::removeConstraint( KsConstraint* pConstraint )
{
	btTypedConstraint*	pbtConstraint = reinterpret_cast<btTypedConstraint*>( pConstraint->getConstraintResource() );

	m_pWorld->removeConstraint( pbtConstraint );

	KsUInt32	index = 0;

	for( KsUInt32 i=0; i<m_pConstraints.size(); i++ )
	{
		if( pConstraint == m_pConstraints[ i ] )
		{
			index = i;
			break;
		}
	}

	m_pConstraints.erase( index );
}

