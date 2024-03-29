/************************************************************************************************/
/** 
 * @file		KsSwfDefineShape4.cpp
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
KsSwfDefineShape4::KsSwfDefineShape4( KsFileObject* pFile )
	: KsSwfCommand( ksSWF_DEFINESHAPE4 )
{
	m_shapeId = pFile->readUInt16();

	KsSwfImporter::readRect( pFile, &m_shapeBounds );
	KsSwfImporter::readRect( pFile, &m_edgeBounds );

	KsBitReader		bitReader;
	KsUInt8			uTemp[ 512 ];

	uTemp[ 0 ] = pFile->readUInt8();
	
	bitReader.setup( uTemp, sizeof(uTemp) );
	
}

/************************************************************************************************/
/* 
 * デストラクタ
 */
/************************************************************************************************/
KsSwfDefineShape4::~KsSwfDefineShape4()
{
}

/************************************************************************************************/
/* 
 * コマンド実行
 */
/************************************************************************************************/
void KsSwfDefineShape4::execute()
{
}

