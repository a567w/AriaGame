/************************************************************************************************/
/** 
 * @file		KsPhysicsController.h
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
#include "KsPhysicsController.h"

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
KsPhysicsController::KsPhysicsController()
{

}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsPhysicsController::~KsPhysicsController()
{

}

/************************************************************************************************/
/*
 * 更新処理
 */
/************************************************************************************************/
void KsPhysicsController::update( KsReal gameTime )
{
	for( KsUInt32 i=0; i<m_pParameters.size(); i++ )
	{
		m_pParameters[ i ]->update( gameTime );
	}
}

