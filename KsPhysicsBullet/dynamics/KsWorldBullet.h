/************************************************************************************************/
/** 
 * @file		KsWorldBullet.h
 * @brief		物理シミュレーションシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSPWORLDBULLET_H__
#define __KSPWORLDBULLET_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsWorldBullet
 * @brief		物理シミュレーションシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
class ksPHYSICSBULLET_API KsWorldBullet : public KsWorld
{
	public:
		/**
		 * コンストラクタ
		 */
												KsWorldBullet();

		/**
		 * デストラクタ
		 */
		virtual									~KsWorldBullet();

		virtual KsInt32							stepSimulation( KsReal timeStep, KsInt32 maxSubSteps, KsReal fixedTimeStep );

		//virtual void							setGravity( const KsVector3d& gravity ) = 0;

		//virtual KsVector3d&					getGravity() const = 0;

		//virtual void							addCollisionObject(btCollisionObject* collisionObject,short int collisionFilterGroup=btBroadphaseProxy::StaticFilter,short int collisionFilterMask=btBroadphaseProxy::AllFilter ^ btBroadphaseProxy::StaticFilter);
		//virtual void							removeCollisionObject(btCollisionObject* collisionObject);

		virtual void							addRigidBody( KsRigidBody* pRigidBody );

		virtual void							addRigidBody( KsRigidBody* pRigidBody, KsUInt16 group, KsUInt16 mask );

		virtual void							removeRigidBody( KsRigidBody* body );

		virtual void							addConstraint( KsConstraint* pConstraint, KsBool disableCollisionsBetweenLinkedBodies=ksFALSE );

		virtual void							removeConstraint( KsConstraint* pConstraint );

		//virtual void							addAction( KsActionInterface* );

		//virtual void							removeAction( KsActionInterface* );

	private:
		btDefaultCollisionConfiguration*		m_pCollisionConfig;
		btCollisionDispatcher*					m_pCollisionDispatcher;
		btAxisSweep3*							m_pOverlappingPairCache;
		btSequentialImpulseConstraintSolver*	m_pSolver;
		btDiscreteDynamicsWorld*				m_pWorld;
		btCollisionShape*						m_pGroundShape;
		KsArray<KsRigidBody*>					m_pRigidBodies;
		KsArray<KsConstraint*>					m_pConstraints;
};

#endif		/* __KSPWORLDBULLET_H__ */

