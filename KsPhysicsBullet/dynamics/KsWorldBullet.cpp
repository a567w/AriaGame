/************************************************************************************************/
/** 
 * @file		KsWorldBullet.h
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
#include "KsWorldBullet.h"

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
KsWorldBullet::KsWorldBullet()
{
	// �R���W�����R���t�B�O���쐬����
	m_pCollisionConfig = new btDefaultCollisionConfiguration();

	// �R���W�����f�B�X�p�b�`�����쐬����
	m_pCollisionDispatcher = new btCollisionDispatcher( m_pCollisionConfig );

	// �R���W�������[���h�̍ő�T�C�Y���w�肷��
	btVector3	btv3WorldAabbMin( -3000.0f, -3000.0f, -3000.0f );
	btVector3	btv3WorldAabbMax(  3000.0f,  3000.0f,  3000.0f );
	KsInt32		iMaxProxies = 1024;
	m_pOverlappingPairCache = new btAxisSweep3( btv3WorldAabbMin, btv3WorldAabbMax, iMaxProxies );

	// �S���v�Z�\���o���쐬����
	m_pSolver = new btSequentialImpulseConstraintSolver();

	// ���[���h�̍쐬
	m_pWorld = new btDiscreteDynamicsWorld( m_pCollisionDispatcher, m_pOverlappingPairCache, m_pSolver, m_pCollisionConfig );

	// �d�͐ݒ�
	m_pWorld->setGravity( btVector3( 0.0f, -10.0f, 0.0f ) );	// �l�N�^�C�Ȃǂ��ӂ�ӂ킷��̂łȂ�ƂȂ�2�{���Ă���

	//-----------------------------------------------------
	// ���p�Ƃ��Ė������ʂ��쐬
	m_pGroundShape = new btStaticPlaneShape( btVector3( 0.0f, 1.0f, 0.0f ), 0.0f );

	// ���̃g�����X�t�H�[����ݒ�
	btTransform		groundTransform;
	groundTransform.setIdentity();

	// MotionState���쐬����B���̂̎p��������������
	btMotionState*	pMotionState = new btDefaultMotionState( groundTransform );

	// ���̂��쐬����
	// ���� 0.0�A�����e���\�� 0.0 �Ȃ炱�̍��͓̂����Ȃ�
	btRigidBody::btRigidBodyConstructionInfo	rbInfo( 0.0f, pMotionState, m_pGroundShape, btVector3( 0.0f, 0.0f, 0.0f ) );
	btRigidBody*	pRigidBody = new btRigidBody( rbInfo );

	// �������[���h�ɏ���ǉ�
	m_pWorld->addRigidBody( pRigidBody );
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
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

