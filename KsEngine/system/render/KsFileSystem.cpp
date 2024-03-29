/************************************************************************************************/
/**
 * @file		StFileSystem.cpp
 * @brief		ファイルシステム
 * @author		Tsukasa Kato
 * @date		2004/03/30
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "StFileSystem.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * 読み込みようバッファをセットする(指定バッファを使用したいとき)
 */
/************************************************************************************************/
void StReadRequest::setBuffer( StUInt8* pBuffer, StUInt32 bufferSize )
{
	m_bufferFlag = stTRUE;
	m_pBuffer    = pBuffer;
	m_bufferSize = bufferSize;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
StFileSystem::StFileSystem()
{
	m_packIndex = 0;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
StFileSystem::~StFileSystem()
{
}



