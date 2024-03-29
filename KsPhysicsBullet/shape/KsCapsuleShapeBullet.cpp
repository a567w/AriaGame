/************************************************************************************************/
/** 
 * @file		KsCapsuleShapeBullet.h
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
#include "KsCapsuleShapeBullet.h"

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
KsCapsuleShapeBullet::KsCapsuleShapeBullet( KsReal radius, KsReal height )
	: m_pCapsuleShape( 0 )
{
	m_pCapsuleShape = new btCapsuleShape( radius, height );
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsCapsuleShapeBullet::~KsCapsuleShapeBullet()
{
	ksDELETE( m_pCapsuleShape );
}


/************************************************************************************************/
/*
 * 慣性テンソルの計算
 */
/************************************************************************************************/
void KsCapsuleShapeBullet::calculateLocalInertia( KsReal mass, KsVector3d& inertia )
{
	btVector3	localInertia( 0.0f, 0.0f, 0.0f );

	m_pCapsuleShape->calculateLocalInertia( mass, localInertia );

	inertia.set( localInertia.getX(), localInertia.getY(), localInertia.getZ() );
}




