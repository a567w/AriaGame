/************************************************************************************************/
/** 
 * @file		KsBoxShapeBullet.h
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
#include "KsBoxShapeBullet.h"

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
KsBoxShapeBullet::KsBoxShapeBullet( const KsVector3d& halfExtents )
	: m_pBoxShape( 0 )
{
	m_pBoxShape = new btBoxShape( btVector3( halfExtents.x, halfExtents.y, halfExtents.z ) );
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsBoxShapeBullet::KsBoxShapeBullet( KsReal width, KsReal height, KsReal depth )
	: m_pBoxShape( 0 )
{
	m_pBoxShape = new btBoxShape( btVector3( width, height, depth ) );

	// �����e���\���̌v�Z
	//if( btsMass != 0.0f )	m_pbtColShape->calculateLocalInertia( btsMass, btv3LocalInertia );
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsBoxShapeBullet::~KsBoxShapeBullet()
{
	ksDELETE( m_pBoxShape );
}


/************************************************************************************************/
/*
 * �����e���\���̌v�Z
 */
/************************************************************************************************/
void KsBoxShapeBullet::calculateLocalInertia( KsReal mass, KsVector3d& inertia )
{
	btVector3	localInertia( 0.0f, 0.0f, 0.0f );

	m_pBoxShape->calculateLocalInertia( mass, localInertia );

	inertia.set( localInertia.getX(), localInertia.getY(), localInertia.getZ() );
}



