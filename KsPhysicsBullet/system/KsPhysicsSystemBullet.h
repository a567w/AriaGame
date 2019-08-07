/************************************************************************************************/
/** 
 * @file		KsPhysicsSystemBullet.h
 * @brief		�����V�~�����[�V�����V�X�e��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSPHYSICSSYSTEMBULLET_H__
#define __KSPHYSICSSYSTEMBULLET_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsPhysicsSystemBullet
 * @brief		�����V�~�����[�V�����V�X�e��
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
		 * �R���X�g���N�^
		 */
											KsPhysicsSystemBullet();

		/**
		 * �f�X�g���N�^
		 */
		virtual								~KsPhysicsSystemBullet();

		/**
		 * ����������
		 * @param		pParam				�p�����[�^
		 * @retval		ksTRUE				����������
		 * @retval		ksFALSE				���������s
		 */
		virtual KsBool						initialize( void* pParam );

		/**
		 * �㏈��
		 * @retval		ksTRUE				�㏈������
		 * @retval		ksFALSE				�㏈�����s
		 */
		virtual KsBool						terminate();

		/**
		 * ���[���h�𐶐�����
		 */
		virtual KsWorld*					createWorld();

		/**
		 * �V�F�C�v��������
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

