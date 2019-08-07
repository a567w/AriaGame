/************************************************************************************************/
/** 
 * @file		KsRigidBodyBullet.h
 * @brief		物理シミュレーションシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSRIGIDBODYBULLET_H__
#define __KSRIGIDBODYBULLET_H__

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
 * @class		KsRigidBodyBullet
 * @brief		物理シミュレーションシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
class ksPHYSICSBULLET_API KsRigidBodyBullet : public KsRigidBody
{
	public:
		/**
		 * コンストラクタ
		 */
									KsRigidBodyBullet( const KsRigidBodyConstructionInfo& Info );

		/**
		 * デストラクタ
		 */
		virtual						~KsRigidBodyBullet();

		/**
		 * リソースを取得する
		 * @return					 リソース
		 */
		virtual void*				getRigidBodyResource();


		virtual KsInt32				getCollisionFlags() const;

		virtual void				setCollisionFlags( KsInt32 flags );

		virtual void				setSleepingThresholds( KsReal linear, KsReal angular );

		virtual void				setActivationState( KsInt32 state );

		virtual void				setCenterOfMassTransform( const KsMatrix4x4& refMatrix );
		virtual const KsMatrix4x4&	getCenterOfMassTransform() const;
		virtual void				setLinearVelocity( const KsVector3d& refV );
		virtual void				setAngularVelocity( const KsVector3d& refV );
		virtual void				setInterpolationLinearVelocity( const KsVector3d& refV );
		virtual void				setInterpolationAngularVelocity( const KsVector3d& refV );
		virtual void				setInterpolationWorldTransform( const KsMatrix4x4& refMatrix );
		virtual void				clearForces();

		virtual KsMatrix4x4&		getWorldTransform();

	private:
		btRigidBody*				m_pRigidBody;
};

#endif		/* __KSRIGIDBODYBULLET_H__ */

