/************************************************************************************************/
/** 
 * @file		KsScene.cpp
 * @brief		シーン
 * @author		Tsukasa Kato
 * @date		2011/07/02
 * @since		2011/07/02
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << ワーニング抑制 >>                                          */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "Aria/KsGamePreCompile.h"
#include "Aria/game/scene/KsScene.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * コンストラクタ
 * @param	updateOrder				更新オーダー
 * @param	drawOrder				描画オーダー
 */
/************************************************************************************************/
KsScene::KsScene( ksSCENE_TYPE sceneType, KsUInt32 updateOrder, KsUInt32 drawOrder )
	: KsTask( updateOrder, drawOrder )
	, m_sceneType( sceneType )
{
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsScene::~KsScene()
{
}

/************************************************************************************************/
/*
 * 更新処理
 * @param		pParam				パラメータ
 */
/************************************************************************************************/
void* KsScene::update( void* pParam )
{
	return pParam;
}

/************************************************************************************************/
/*
 * 描画処理
 * @param		pParam				パラメータ
 */
/************************************************************************************************/
void* KsScene::draw( void* pParam )
{
	return pParam;
}

