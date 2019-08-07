/************************************************************************************************/
/** 
 * @file		KsSwfPlaceObject.cpp
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
KsSwfPlaceObject::KsSwfPlaceObject( KsFileObject* pFile )
	: KsSwfCommand( ksSWF_PLACEOBJECT )
{
	m_characterId = pFile->readUInt16();
	m_depth       = pFile->readUInt16();

	KsSwfImporter::readMatrix( pFile, &m_matrix );
}

/************************************************************************************************/
/* 
 * デストラクタ
 */
/************************************************************************************************/
KsSwfPlaceObject::~KsSwfPlaceObject()
{
}

/************************************************************************************************/
/* 
 * コマンド実行
 */
/************************************************************************************************/
void KsSwfPlaceObject::execute()
{
}


/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsSwfPlaceObject2::KsSwfPlaceObject2( KsFileObject* pFile )
	: KsSwfCommand( ksSWF_PLACEOBJECT2 )
{
	m_characterId = pFile->readUInt16();
	m_depth       = pFile->readUInt16();

	KsSwfImporter::readMatrix( pFile, &m_matrix );
}

/************************************************************************************************/
/* 
 * デストラクタ
 */
/************************************************************************************************/
KsSwfPlaceObject2::~KsSwfPlaceObject2()
{
}

/************************************************************************************************/
/* 
 * コマンド実行
 */
/************************************************************************************************/
void KsSwfPlaceObject2::execute()
{
}

