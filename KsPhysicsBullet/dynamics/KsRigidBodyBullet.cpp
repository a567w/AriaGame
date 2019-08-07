/************************************************************************************************/
/** 
 * @file		KsRigidBodyBullet.h
 * @brief		�����V�~�����[�V�����V�X�e��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsPhysicsBullet/KsPhysicsBulletPreCompile.h"
#include "KsRigidBodyBullet.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsRigidBodyBullet::KsRigidBodyBullet( const KsRigidBodyConstructionInfo& Info )
	: KsRigidBody()
	, m_pRigidBody( 0 )
{
	btMotionState*		pMotionState = NULL;
	btCollisionShape*	pColShape    = NULL;

	if( Info.m_motionState )
	{
		pMotionState = (btMotionState*)Info.m_motionState->getMotionStateResource();
	}

	if( Info.m_collisionShape )
	{
		pColShape = (btCollisionShape*)Info.m_collisionShape->getCollisionShapeResource();
	}

	// ���̂̃p�����[�^�̐ݒ�
	btRigidBody::btRigidBodyConstructionInfo	infoBullet( Info.m_mass, pMotionState, pColShape );

	// ���̂̍쐬
	m_pRigidBody = new btRigidBody( infoBullet );
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsRigidBodyBullet::~KsRigidBodyBullet()
{
#if 0
	if( m_pRigidBody )
	{
		if( m_pRigidBody->getMotionState() )
		{
			delete m_pRigidBody->getMotionState();
		}

		g_clBulletPhysics.removeFromWorld( m_pRigidBody );

		ksDELETE( m_pRigidBody );
	}

	if( m_pbtColShape )
	{
		delete m_pbtColShape;
		m_pbtColShape = NULL;
	}
#endif
}

/************************************************************************************************/
/*
 * ���\�[�X���擾����
 * @return							 ���\�[�X
 */
/************************************************************************************************/
void* KsRigidBodyBullet::getRigidBodyResource()
{
	return m_pRigidBody;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsInt32 KsRigidBodyBullet::getCollisionFlags() const
{
	return m_pRigidBody->getCollisionFlags();
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRigidBodyBullet::setCollisionFlags( KsInt32 flags )
{
	m_pRigidBody->setCollisionFlags( flags );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRigidBodyBullet::setSleepingThresholds( KsReal linear, KsReal angular )
{
	m_pRigidBody->setSleepingThresholds( linear, angular );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRigidBodyBullet::setActivationState( KsInt32 state )
{
	m_pRigidBody->setActivationState( state );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsMatrix4x4& KsRigidBodyBullet::getWorldTransform()
{
	m_pRigidBody->getWorldTransform().getOpenGLMatrix( m_worldTransform.data );

	return m_worldTransform;
}

 void KsRigidBodyBullet::setCenterOfMassTransform( const KsMatrix4x4& refMatrix )
 {
	 btTransform		transform;

	 transform.setFromOpenGLMatrix( refMatrix.data );
	 m_pRigidBody->setCenterOfMassTransform( transform );
 }

 const KsMatrix4x4& KsRigidBodyBullet::getCenterOfMassTransform() const
{
	btTransform		transform = m_pRigidBody->getCenterOfMassTransform();

	transform.getOpenGLMatrix( const_cast<KsReal*>(&m_centerOfMassTransform.data[0]) );

	return m_centerOfMassTransform;
}

void KsRigidBodyBullet::setLinearVelocity( const KsVector3d& refV )
{
	m_pRigidBody->setLinearVelocity( btVector3(refV.x, refV.y, refV.z) );
}

void KsRigidBodyBullet::setAngularVelocity( const KsVector3d& refV )
{
	m_pRigidBody->setAngularVelocity( btVector3(refV.x, refV.y, refV.z) );
}

void KsRigidBodyBullet::setInterpolationLinearVelocity( const KsVector3d& refV )
{
	m_pRigidBody->setInterpolationLinearVelocity( btVector3(refV.x, refV.y, refV.z) );
}

void KsRigidBodyBullet::setInterpolationAngularVelocity( const KsVector3d& refV )
{
	m_pRigidBody->setInterpolationAngularVelocity( btVector3(refV.x, refV.y, refV.z) );
}

void KsRigidBodyBullet::setInterpolationWorldTransform( const KsMatrix4x4& refMatrix )
{
	btTransform		transform;

	transform.setFromOpenGLMatrix( refMatrix.data );
	m_pRigidBody->setInterpolationWorldTransform( transform );
}

void KsRigidBodyBullet::clearForces()
{
	m_pRigidBody->clearForces();
}

