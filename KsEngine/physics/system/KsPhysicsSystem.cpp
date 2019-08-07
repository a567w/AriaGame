/************************************************************************************************/
/** 
 * @file		KsPhysicsSystem.h
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
#include "KsEngine/KsEnginePreCompile.h"
#include "KsPhysicsSystem.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
template<> KsPhysicsSystem* KsSingleton< KsPhysicsSystem >::m_pInstance = 0;

/************************************************************************************************/
/*
 * シングルトンの参照を取得
 * @return	シングルトンの参照
 */
/************************************************************************************************/
KsPhysicsSystem& KsPhysicsSystem::getInstance()
{  
	return (*m_pInstance);  
}

/************************************************************************************************/
/*
 * シングルトンのポインタを取得
 * @return	シングルトンのポインタ
 */
/************************************************************************************************/
KsPhysicsSystem* KsPhysicsSystem::getInstancePtr()
{
	return m_pInstance;
}

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsPhysicsSystem::KsPhysicsSystem()
	: m_pWorld( 0 )
{

}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsPhysicsSystem::~KsPhysicsSystem()
{
	ksDELETE( m_pWorld );
}

/************************************************************************************************/
/*
 * 物理シミュレーション処理をする
 */
/************************************************************************************************/
KsInt32 KsPhysicsSystem::stepSimulation( KsReal timeStep, KsInt32 maxSubSteps, KsReal fixedTimeStep )
{
	if( m_pWorld )
	{
		m_pWorld->stepSimulation( timeStep, maxSubSteps, fixedTimeStep );
	}

	return 0;
}

