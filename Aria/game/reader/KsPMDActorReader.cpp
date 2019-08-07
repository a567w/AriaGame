/************************************************************************************************/
/** 
 * @file		KsPMDActorReader.cpp
 * @brief		PMD Model Reader
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
#include "Aria/game/reader/KsPMDActorReader.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/



/************************************************************************************************/
/*
 * コンストラクタ
 * 同期読み込み(読み込みが終了するまで待つ)
 * @param		fileName		ファイル名
 */
/************************************************************************************************/
KsPMDActorReader::KsPMDActorReader( const KsString& fileName )
	: KsFileAsyncReader( fileName )
	, m_pActor( 0 )
{
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsPMDActorReader::~KsPMDActorReader()
{
}

/************************************************************************************************/
/**
 * 読み込み終了時のコールバック関数
 * @param		pFile			ファイルオブジェクト
 */
/************************************************************************************************/
KsBool KsPMDActorReader::readEndThreadCB( KsFileObject* pFile )
{
	KS_PMD_DATA*			pPMD     = KsLoadPMDFile( pFile );
	KsModel*				pModel   = KsModelCreateFromPMD( pPMD );
	KsHumanIK*				pHumanIK = KsHumanIKCreateFromPMD( pPMD, pModel );
	KsPhysicsController*	pPhysics = KsPhysicsControllerCreateFromPMD( pPMD, pModel );

	m_pActor   = ksNew KsActor( pModel );
	m_pActor->setHumanIK( pHumanIK );
	m_pActor->setPhysics( pPhysics );

	//KsString			VMDFilePath     = "D:\\MMD\\yellow.vmd";
	KsString			VMDFilePath     = "D:\\MMD\\dash01.vmd";
	
	KsAnimation*		pAnim       = KsAnimationCreateFromVMD( VMDFilePath );
	m_pActor->setAnimation( ksNew KsAnimationController( pAnim ) );
	m_pActor->getAnimation()->setSpeedFactor( 0.5f );

	return ksTRUE;
}

/************************************************************************************************/
/*
 * 読み込み終了時のコールバック関数
 * @param		pFile			ファイルオブジェクト
 */
/************************************************************************************************/
KsBool KsPMDActorReader::readEndCB( KsFileObject* pFile )
{
	KsGameSystem*	pSystem = KsGameSystem::getInstancePtr();

	pSystem->addActor( m_pActor );

	return ksTRUE;
}
