/*************************************************************************************************/
/** 
 * @file	KsAppInstance.cpp
 * @brief	�A�v���P�[�V�����C���X�^���X
 * @author	Tukasa Kato
 * @date	2003/03/22
 * @since	----/--/--
 * @version	1.0.0
 */
/*************************************************************************************************/

/*===============================================================================================*/
/*                                 << �C���N���[�h >>                                             */
/*===============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"
#include "KsEngine/win/KsAppInstance.h"

/*===============================================================================================*/
/*                                     << ��` >>                                                */
/*===============================================================================================*/
HINSTANCE	KsAppInstance::m_hInstance     = 0;
HINSTANCE	KsAppInstance::m_hPrevInstance = 0;
LPSTR		KsAppInstance::m_lpCmdLine     = 0;
KsInt32		KsAppInstance::m_nCmdShow      = 0;

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
void KsAppInstance::setup( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, KsInt32 nCmdShow )
{
	m_hInstance		= hInstance;
	m_hPrevInstance	= hPrevInstance;
	m_lpCmdLine		= lpCmdLine;
	m_nCmdShow		= nCmdShow;
}



