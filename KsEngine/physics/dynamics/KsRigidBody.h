/************************************************************************************************/
/** 
 * @file		KsRigidBody.h
 * @brief		物理シミュレーションシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSRIGIDBODY_H__
#define __KSRIGIDBODY_H__

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
 * @class		KsRigidBody
 * @brief		物理シミュレーションシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
class ksENGINE_API KsRigidBody
{
	public:
		struct	KsRigidBodyConstructionInfo
		{
			KsReal				m_mass;
			KsMotionState*		m_motionState;
			KsMatrix4x4			m_startWorldTransform;
			KsCollisionShape*	m_collisionShape;
			KsVector3d			m_localInertia;
			KsReal				m_linearDamping;
			KsReal				m_angularDamping;
			KsReal				m_friction;
			KsReal				m_restitution;
			KsReal				m_linearSleepingThreshold;
			KsReal				m_angularSleepingThreshold;
			KsBool				m_additionalDamping;
			KsReal				m_additionalDampingFactor;
			KsReal				m_additionalLinearDampingThresholdSqr;
			KsReal				m_additionalAngularDampingThresholdSqr;
			KsReal				m_additionalAngularDampingFactor;
		
			KsRigidBodyConstructionInfo( KsReal mass, KsMotionState* pMotionState, KsCollisionShape* pCollisionShape, const KsVector3d& localInertia=KsVector3d::ZERO )
				: m_mass( mass )
				, m_motionState( pMotionState )
				, m_startWorldTransform( KsMatrix4x4::IDENTITY )
				, m_collisionShape( pCollisionShape )
				, m_localInertia( localInertia )
				, m_linearDamping( 0.0f )
				, m_angularDamping( 0.0f )
				, m_friction( 0.5f )
				, m_restitution( 0.0f )
				, m_linearSleepingThreshold( 0.8f )
				, m_angularSleepingThreshold( 1.0f )
				, m_additionalDamping( ksFALSE )
				, m_additionalDampingFactor( 0.005f )
				, m_additionalLinearDampingThresholdSqr( 0.01f )
				, m_additionalAngularDampingThresholdSqr( 0.01f )
				, m_additionalAngularDampingFactor( 0.01f )
			{
			}
		};

	public:
		/**
		 * コンストラクタ
		 */
									KsRigidBody();

		/**
		 * デストラクタ
		 */
		virtual						~KsRigidBody();

		/**
		 * リソースを取得する
		 * @return					 リソース
		 */
		virtual void*				getRigidBodyResource() = 0;

		virtual KsInt32				getCollisionFlags() const = 0;

		virtual void				setCollisionFlags( KsInt32 flags ) = 0;

		virtual void				setSleepingThresholds( KsReal linear, KsReal angular ) = 0;

		virtual void				setActivationState( KsInt32 state ) = 0;

		virtual void				setCenterOfMassTransform( const KsMatrix4x4& refMatrix ) = 0;
		virtual const KsMatrix4x4&	getCenterOfMassTransform() const = 0;
		virtual void				setLinearVelocity( const KsVector3d& refV ) = 0;
		virtual void				setAngularVelocity( const KsVector3d& refV ) = 0;
		virtual void				setInterpolationLinearVelocity( const KsVector3d& refV ) = 0;
		virtual void				setInterpolationAngularVelocity( const KsVector3d& refV ) = 0;
		virtual void				setInterpolationWorldTransform( const KsMatrix4x4& refMatrix ) = 0;
		virtual void				clearForces() = 0;

		virtual KsMatrix4x4&		getWorldTransform() { return m_worldTransform; }

	protected:
		KsCollisionShape*			m_pColShape;
		KsMatrix4x4					m_worldTransform;
		KsMatrix4x4					m_centerOfMassTransform;
};

#endif		/* __KSRIGIDBODY_H__ */

