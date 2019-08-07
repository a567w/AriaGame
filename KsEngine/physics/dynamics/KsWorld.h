/************************************************************************************************/
/** 
 * @file		KsWorld.h
 * @brief		物理シミュレーションシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSPWORLD_H__
#define __KSPWORLD_H__

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
 * @class		KsWorld
 * @brief		物理シミュレーションシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
class ksENGINE_API KsWorld
{
	public:
		/**
		 * コンストラクタ
		 */
									KsWorld();

		/**
		 * デストラクタ
		 */
		virtual						~KsWorld();

		virtual KsInt32				stepSimulation( KsReal timeStep, KsInt32 maxSubSteps, KsReal fixedTimeStep ) = 0;

		//virtual void				setGravity( const KsVector3d& gravity ) = 0;

		//virtual KsVector3d&			getGravity() const = 0;

		//virtual void				addCollisionObject(btCollisionObject* collisionObject,short int collisionFilterGroup=btBroadphaseProxy::StaticFilter,short int collisionFilterMask=btBroadphaseProxy::AllFilter ^ btBroadphaseProxy::StaticFilter);
		//virtual void				removeCollisionObject(btCollisionObject* collisionObject);

		virtual void				addRigidBody( KsRigidBody* pRigidBody ) = 0;

		virtual void				addRigidBody( KsRigidBody* pRigidBody, KsUInt16 group, KsUInt16 mask ) = 0;

		virtual void				removeRigidBody( KsRigidBody* body ) = 0;

		virtual void				addConstraint( KsConstraint* pConstraint, KsBool disableCollisionsBetweenLinkedBodies=ksFALSE ) = 0;

		virtual void				removeConstraint( KsConstraint* pConstraint ) = 0;

		//virtual void				addAction( KsActionInterface* );

		//virtual void				removeAction( KsActionInterface* );
};

#endif		/* __KSPWORLD_H__ */

