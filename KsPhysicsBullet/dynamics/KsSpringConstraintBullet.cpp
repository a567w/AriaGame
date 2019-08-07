/************************************************************************************************/
/** 
 * @file		KsSpringConstraintBullet.h
 * @brief		物理シミュレーションシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsPhysicsBullet/KsPhysicsBulletPreCompile.h"
#include "KsSpringConstraintBullet.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsSpringConstraintBullet::KsSpringConstraintBullet( KsRigidBody& rbA, KsRigidBody& rbB, const KsMatrix4x4& frameInA, const KsMatrix4x4& frameInB, KsBool useLinearReferenceFrameA )
{
	btRigidBody*	pRigidBodyA = (btRigidBody*)rbA.getRigidBodyResource();
	btRigidBody*	pRigidBodyB = (btRigidBody*)rbB.getRigidBodyResource();
	btTransform		transformA;
	btTransform		transformB;
	btMatrix3x3		rotMatA;
	btMatrix3x3		rotMatB;

	rotMatA.setValue( frameInA.m11, frameInA.m12, frameInA.m13, 
					  frameInA.m21, frameInA.m22, frameInA.m23, 
					  frameInA.m31, frameInA.m32, frameInA.m33 );

	rotMatB.setValue( frameInB.m11, frameInB.m12, frameInB.m13, 
					  frameInB.m21, frameInB.m22, frameInB.m23, 
					  frameInB.m31, frameInB.m32, frameInB.m33 );

	// 移動
	transformA.setOrigin( btVector3( frameInA.m[ 3 ][ 0 ], frameInA.m[ 3 ][ 1 ], frameInA.m[ 3 ][ 2 ] ) );
	transformB.setOrigin( btVector3( frameInB.m[ 3 ][ 0 ], frameInB.m[ 3 ][ 1 ], frameInB.m[ 3 ][ 2 ] ) );

	// 回転
	transformA.setBasis( rotMatA );
	transformB.setBasis( rotMatB );

	const bool	flag = useLinearReferenceFrameA ? true : false;

	m_pSpringConstraint = new btGeneric6DofSpringConstraint( 
								*pRigidBodyA,
								*pRigidBodyB,
								transformA,
								transformB,
								flag );
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsSpringConstraintBullet::~KsSpringConstraintBullet()
{

}

/************************************************************************************************/
/*
 * リソースを取得する
 * @return							 リソース
 */
/************************************************************************************************/
void* KsSpringConstraintBullet::getConstraintResource()
{
	return m_pSpringConstraint;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsSpringConstraintBullet::enableSpring( KsInt32 index, KsBool enable )
{
	const bool	flag = enable ? true : false;

	m_pSpringConstraint->enableSpring( index, flag );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsSpringConstraintBullet::setStiffness( KsInt32 index, KsReal stiffness )
{
	m_pSpringConstraint->setStiffness( index, stiffness );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsSpringConstraintBullet::setDamping( KsInt32 index, KsReal damping )
{
	m_pSpringConstraint->setDamping( index, damping );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsSpringConstraintBullet::setEquilibriumPoint()
{
	m_pSpringConstraint->setEquilibriumPoint();
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsSpringConstraintBullet::setEquilibriumPoint( KsInt32 index )
{
	m_pSpringConstraint->setEquilibriumPoint( index );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsSpringConstraintBullet::setLinearLowerLimit( KsReal x, KsReal y, KsReal z )
{
	m_pSpringConstraint->setLinearLowerLimit( btVector3( x, y, z ) );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsSpringConstraintBullet::setLinearUpperLimit( KsReal x, KsReal y, KsReal z )
{
	m_pSpringConstraint->setLinearUpperLimit( btVector3( x, y, z ) );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsSpringConstraintBullet::setAngularLowerLimit( KsReal x, KsReal y, KsReal z )
{
	m_pSpringConstraint->setAngularLowerLimit( btVector3( x, y, z ) );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsSpringConstraintBullet::setAngularUpperLimit( KsReal x, KsReal y, KsReal z )
{
	m_pSpringConstraint->setAngularUpperLimit( btVector3( x, y, z ) );
}



