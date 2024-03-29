/************************************************************************************************/
/** 
 * @file		KsSkeleton.cpp
 * @brief		スケルトンクラス
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"

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
KsSkeleton::KsSkeleton()
{
}

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsSkeleton::KsSkeleton( KsModel* pModel )
{
	const KsUInt32 boneCount = pModel->getBoneCount();

	m_vpBonePose.arrayRalloc( boneCount );

	for( KsUInt32 i=0; i<boneCount; i++ )
	{
		KsBonePose*		pBonePose = new KsBonePose();

		pBonePose->m_index  = pModel->m_vpBones[ i ]->m_index;
		pBonePose->m_name   = pModel->m_vpBones[ i ]->m_name;
		pBonePose->m_parent = pModel->m_vpBones[ i ]->m_parent;

		m_vpBonePose.push_back( pBonePose );
	}
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsSkeleton::~KsSkeleton()
{
}

/************************************************************************************************/
/*
 * 更新処理
 * @param	gameTime			更新時間
 */
/************************************************************************************************/
void KsSkeleton::update( KsReal gameTime )
{
}

