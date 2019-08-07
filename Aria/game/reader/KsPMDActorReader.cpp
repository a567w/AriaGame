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
/*                                 << ���[�j���O�}�� >>                                          */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "Aria/KsGamePreCompile.h"
#include "Aria/game/reader/KsPMDActorReader.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/



/************************************************************************************************/
/*
 * �R���X�g���N�^
 * �����ǂݍ���(�ǂݍ��݂��I������܂ő҂�)
 * @param		fileName		�t�@�C����
 */
/************************************************************************************************/
KsPMDActorReader::KsPMDActorReader( const KsString& fileName )
	: KsFileAsyncReader( fileName )
	, m_pActor( 0 )
{
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsPMDActorReader::~KsPMDActorReader()
{
}

/************************************************************************************************/
/**
 * �ǂݍ��ݏI�����̃R�[���o�b�N�֐�
 * @param		pFile			�t�@�C���I�u�W�F�N�g
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
 * �ǂݍ��ݏI�����̃R�[���o�b�N�֐�
 * @param		pFile			�t�@�C���I�u�W�F�N�g
 */
/************************************************************************************************/
KsBool KsPMDActorReader::readEndCB( KsFileObject* pFile )
{
	KsGameSystem*	pSystem = KsGameSystem::getInstancePtr();

	pSystem->addActor( m_pActor );

	return ksTRUE;
}
