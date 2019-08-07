/************************************************************************************************/
/** 
 * @file		KsSwfDefineSceneAndFrameLabelData.cpp
 * @brief		SWF�R�}���h
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsSWF/KsSWFPreCompile.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsSwfDefineSceneAndFrameLabelData::KsSwfDefineSceneAndFrameLabelData( KsFileObject* pFile, const KsSwfRecordHeader* tag )
	: KsSwfCommand( ksSWF_DEFINESCENEANDFRAMELABELDATA )
	, m_sceneCount( 0 )
	, m_pScenes( 0 )
	, m_frameLabelCount( 0 )
	, m_pFrameLabels( 0 )
{
	m_sceneCount = pFile->readEncodedU32();

	if( m_sceneCount )
	{
		m_pScenes = ksNew KS_SWF_SCENE[ m_sceneCount ];

		for( KsUInt32 i=0; i<m_sceneCount; i++ )
		{
			m_pScenes[ i ].m_offset = pFile->readEncodedU32();
			m_pScenes[ i ].m_name   = pFile->readString();
		}
	}

	m_frameLabelCount = pFile->readEncodedU32();

	if( m_frameLabelCount )
	{
		m_pFrameLabels = ksNew KS_SWF_FRAMELABEL[ m_frameLabelCount ];

		for( KsUInt32 i=0; i<m_frameLabelCount; i++ )
		{
			m_pFrameLabels[ i ].m_frameNum   = pFile->readEncodedU32();
			m_pFrameLabels[ i ].m_frameLabel = pFile->readString();
		}
	}
}

/************************************************************************************************/
/* 
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsSwfDefineSceneAndFrameLabelData::~KsSwfDefineSceneAndFrameLabelData()
{
	ksDELETEARRAY( m_pScenes );
	ksDELETEARRAY( m_pFrameLabels );
}

/************************************************************************************************/
/* 
 * �R�}���h���s
 */
/************************************************************************************************/
void KsSwfDefineSceneAndFrameLabelData::execute()
{
}

