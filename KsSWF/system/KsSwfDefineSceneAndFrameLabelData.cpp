/************************************************************************************************/
/** 
 * @file		KsSwfDefineSceneAndFrameLabelData.cpp
 * @brief		SWFコマンド
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsSWF/KsSWFPreCompile.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/*
 * コンストラクタ
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
 * デストラクタ
 */
/************************************************************************************************/
KsSwfDefineSceneAndFrameLabelData::~KsSwfDefineSceneAndFrameLabelData()
{
	ksDELETEARRAY( m_pScenes );
	ksDELETEARRAY( m_pFrameLabels );
}

/************************************************************************************************/
/* 
 * コマンド実行
 */
/************************************************************************************************/
void KsSwfDefineSceneAndFrameLabelData::execute()
{
}

