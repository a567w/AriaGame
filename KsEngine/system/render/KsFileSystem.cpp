/************************************************************************************************/
/**
 * @file		StFileSystem.cpp
 * @brief		�t�@�C���V�X�e��
 * @author		Tsukasa Kato
 * @date		2004/03/30
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "StFileSystem.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * �ǂݍ��݂悤�o�b�t�@���Z�b�g����(�w��o�b�t�@���g�p�������Ƃ�)
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


