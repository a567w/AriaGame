/************************************************************************************************/
/** 
 * @file		KsPhysicsSystem.h
 * @brief		物理シミュレーションシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSPHYSICSSYSTEM_H__
#define __KSPHYSICSSYSTEM_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsEngine/physics/system/KsPhysicsType.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsBone;

/************************************************************************************************/
/**
 * @class		KsPhysicsSystem
 * @brief		物理シミュレーションシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
class ksENGINE_API KsPhysicsSystem : public KsSingleton< KsPhysicsSystem >
{
	public:
		/**
		 * シングルトンの参照を取得
		 * @return							シングルトンの参照
		 */
		static KsPhysicsSystem&				getInstance();
		
		/**
		 * シングルトンのポインタを取得
		 * @return							シングルトンのポインタ
		 */
		static KsPhysicsSystem*				getInstancePtr();

	public:
		/**
		 * コンストラクタ
		 */
											KsPhysicsSystem();

		/**
		 * デストラクタ
		 */
		virtual								~KsPhysicsSystem();

		/**
		 * 初期化処理
		 * @param		pParam				パラメータ
		 * @retval		ksTRUE				初期化成功
		 * @retval		ksFALSE				初期化失敗
		 */
		virtual KsBool						initialize( void* pParam ) = 0;

		/**
		 * 後処理
		 * @retval		ksTRUE				後処理成功
		 * @retval		ksFALSE				後処理失敗
		 */
		virtual KsBool						terminate() = 0;

		/**
		 * ワールドを生成する
		 */
		virtual KsWorld*					createWorld() = 0;

		/**
		 * シェイプ生成する
		 */
		virtual KsCollisionShape*			createShape( ksSHAPE_TYPE type, const KsVector3d& halfExtents ) = 0;

		/**
		 *
		 */
		virtual KsRigidBody*				createRigidBody( const KsRigidBody::KsRigidBodyConstructionInfo& Info ) = 0;


		virtual KsMotionState*				createMotionState( ksMOTION_STATE_TYPE type, const KsMatrix4x4* pTransform, const KsMatrix4x4* pOffset=NULL, KsBone* pBone=NULL ) = 0;

		virtual KsConstraint*				createConstraint( ksCONSTRAINT_TYPE type, KsRigidBody& rbA, KsRigidBody& rbB, const KsMatrix4x4& frameInA, const KsMatrix4x4& frameInB, KsBool useLinearReferenceFrameA ) = 0;

		KsWorld*							getWorld() { return m_pWorld; }

		virtual KsInt32						stepSimulation( KsReal timeStep, KsInt32 maxSubSteps, KsReal fixedTimeStep );
	
	protected:
		KsWorld*							m_pWorld;
};

#endif		/* __KSPHYSICSSYSTEM_H__ */

