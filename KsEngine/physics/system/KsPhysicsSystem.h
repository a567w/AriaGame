/************************************************************************************************/
/** 
 * @file		KsPhysicsSystem.h
 * @brief		�����V�~�����[�V�����V�X�e��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSPHYSICSSYSTEM_H__
#define __KSPHYSICSSYSTEM_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsEngine/physics/system/KsPhysicsType.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsBone;

/************************************************************************************************/
/**
 * @class		KsPhysicsSystem
 * @brief		�����V�~�����[�V�����V�X�e��
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
		 * �V���O���g���̎Q�Ƃ��擾
		 * @return							�V���O���g���̎Q��
		 */
		static KsPhysicsSystem&				getInstance();
		
		/**
		 * �V���O���g���̃|�C���^���擾
		 * @return							�V���O���g���̃|�C���^
		 */
		static KsPhysicsSystem*				getInstancePtr();

	public:
		/**
		 * �R���X�g���N�^
		 */
											KsPhysicsSystem();

		/**
		 * �f�X�g���N�^
		 */
		virtual								~KsPhysicsSystem();

		/**
		 * ����������
		 * @param		pParam				�p�����[�^
		 * @retval		ksTRUE				����������
		 * @retval		ksFALSE				���������s
		 */
		virtual KsBool						initialize( void* pParam ) = 0;

		/**
		 * �㏈��
		 * @retval		ksTRUE				�㏈������
		 * @retval		ksFALSE				�㏈�����s
		 */
		virtual KsBool						terminate() = 0;

		/**
		 * ���[���h�𐶐�����
		 */
		virtual KsWorld*					createWorld() = 0;

		/**
		 * �V�F�C�v��������
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

