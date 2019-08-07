/************************************************************************************************/
/** 
 * @file		KsSwfRemoveObject2.cpp
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
KsSwfRemoveObject2::KsSwfRemoveObject2( KsFileObject* pFile )
	: KsSwfCommand( ksSWF_REMOVEOBJECT2 )
{
	m_depth       = pFile->readUInt16();
}

/************************************************************************************************/
/* 
 * デストラクタ
 */
/************************************************************************************************/
KsSwfRemoveObject2::~KsSwfRemoveObject2()
{
}

/************************************************************************************************/
/* 
 * コマンド実行
 */
/************************************************************************************************/
void KsSwfRemoveObject2::execute()
{
}

