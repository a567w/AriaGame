/************************************************************************************************/
/** 
 * @file		KsPhysicsSystemBullet.h
 * @brief		物理シミュレーションシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSPHYSICSSYSTEMBULLET_H__
#define __KSPHYSICSSYSTEMBULLET_H__

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
 * @class		KsPhysicsSystemBullet
 * @brief		物理シミュレーションシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
class ksPHYSICSBULLET_API KsPhysicsSystemBullet : public KsPhysicsSystem
{
	public:
		/**
		 * コンストラクタ
		 */
											KsPhysicsSystemBullet();

		/**
		 * デストラクタ
		 */
		virtual								~KsPhysicsSystemBullet();

		/**
		 * 初期化処理
		 * @param		pParam				パラメータ
		 * @retval		ksTRUE				初期化成功
		 * @retval		ksFALSE				初期化失敗
		 */
		virtual KsBool						initialize( void* pParam );

		/**
		 * 後処理
		 * @retval		ksTRUE				後処理成功
		 * @retval		ksFALSE				後処理失敗
		 */
		virtual KsBool						terminate();

		/**
		 * ワールドを生成する
		 */
		virtual KsWorld*					createWorld();

		/**
		 * シェイプ生成する
		 */
		virtual KsCollisionShape*			createShape( ksSHAPE_TYPE type, const KsVector3d& halfExtents );

		/**
		 *
		 */
		virtual KsRigidBody*				createRigidBody( const KsRigidBody::KsRigidBodyConstructionInfo& Info );

		virtual KsMotionState*				createMotionState( ksMOTION_STATE_TYPE type, const KsMatrix4x4* pTransform, const KsMatrix4x4* pOffset=NULL, KsBone* pBone=NULL );

		virtual KsConstraint*				createConstraint( ksCONSTRAINT_TYPE type, KsRigidBody& rbA, KsRigidBody& rbB, const KsMatrix4x4& frameInA, const KsMatrix4x4& frameInB, KsBool useLinearReferenceFrameA );
};

#endif		/* __KSPHYSICSSYSTEMBULLET_H__ */

