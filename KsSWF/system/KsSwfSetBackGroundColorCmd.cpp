/************************************************************************************************/
/** 
 * @file		KsSwfSetBackGroundColorCmd.cpp
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
KsSwfSetBackGroundColorCmd::KsSwfSetBackGroundColorCmd( KsFileObject* pFile )
	: KsSwfCommand( ksSWF_SETBACKGROUNDCOLOR )
{
	const KsUInt8	red   = pFile->readUInt8();
	const KsUInt8	green = pFile->readUInt8();
	const KsUInt8	blue  = pFile->readUInt8();

	//m_color.setRGB( red, green, blue );
}

/************************************************************************************************/
/* 
 * デストラクタ
 */
/************************************************************************************************/
KsSwfSetBackGroundColorCmd::~KsSwfSetBackGroundColorCmd()
{
}

/************************************************************************************************/
/* 
 * コマンド実行
 */
/************************************************************************************************/
void KsSwfSetBackGroundColorCmd::execute()
{
}

