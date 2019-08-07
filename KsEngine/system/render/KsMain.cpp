/*************************************************************************************************/
/**
 * @file	KsMain.cpp
 * @brief	���C��
 * @author	tsukasa kato
 * @date	2004/03/30
 * @version	1.0.0
 */
/*************************************************************************************************/

/*************************************************************************************************/
/*                                 << ���C�u���������N >>                                         */
/*************************************************************************************************/
#pragma comment( lib, "comctl32.lib" )
#pragma comment( lib, "Ole32.lib" )
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )
#pragma comment( lib, "cg.lib" )
#pragma comment( lib, "cgD3D9.lib" )

/*************************************************************************************************/
/*                                 << �C���N���[�h >>                                             */
/*************************************************************************************************/
//#include "KsTestSystem.h"
//#include "KsColor.h"
//#include "KsColorReal.h"
#include "KsType.h"
#include "KsWindow.h"
#include "KsWindowUtil.h"

/*************************************************************************************************/
/*                                     << ��` >>                                                */
/*************************************************************************************************/


/*************************************************************************************************/
/*                                     << �錾 >>                                                */
/*************************************************************************************************/
KsInt32 APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, KsInt32 nCmdShow )
{
	KsAppInstance::set( hInstance, hPrevInstance, lpCmdLine, nCmdShow );

	RECT			rect;

	/* �f�X�N�g�b�v�̃N���C�A���g�̈���擾���� */
	KsGetDeskTopClientRect( &rect );

	/* ini �t�@�C������ݒ���擾���� */
	/*
	�t���X�N���[��
	window size x y
	flag
	*/
	/* �E�C���h�E�̐����p��[���[�^���Z�b�g���� */
	KsWindowParam	m_mainWindowParam;
	m_mainWindowParam.m_caption   = "Test";
	m_mainWindowParam.m_className = "KsSystem";
	m_mainWindowParam.m_style     = ksWINDOW_DEFAULT_STYLE;
	m_mainWindowParam.m_styleEx   = 0;
	m_mainWindowParam.m_posX      = ( rect.right  - rect.left )/2 - 320;
	m_mainWindowParam.m_posY      = ( rect.bottom - rect.top  )/2 - 240;
	m_mainWindowParam.m_sizeX     = 640;
	m_mainWindowParam.m_sizeY     = 480;

	/* �E�C���h�E���� */
	KsWindow*	m_pMainWindow = new KsWindow( m_mainWindowParam );

	do{
	
	}while( m_pMainWindow->messageLoop() );

	return	0;
}