/*************************************************************************************************/
/**
 * @file	KsMain.cpp
 * @brief	メイン
 * @author	tsukasa kato
 * @date	2004/03/30
 * @version	1.0.0
 */
/*************************************************************************************************/

/*************************************************************************************************/
/*                                 << ライブラリリンク >>                                         */
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
/*                                 << インクルード >>                                             */
/*************************************************************************************************/
//#include "KsTestSystem.h"
//#include "KsColor.h"
//#include "KsColorReal.h"
#include "KsType.h"
#include "KsWindow.h"
#include "KsWindowUtil.h"

/*************************************************************************************************/
/*                                     << 定義 >>                                                */
/*************************************************************************************************/


/*************************************************************************************************/
/*                                     << 宣言 >>                                                */
/*************************************************************************************************/
KsInt32 APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, KsInt32 nCmdShow )
{
	KsAppInstance::set( hInstance, hPrevInstance, lpCmdLine, nCmdShow );

	RECT			rect;

	/* デスクトップのクライアント領域を取得する */
	KsGetDeskTopClientRect( &rect );

	/* ini ファイルから設定を取得する */
	/*
	フルスクリーン
	window size x y
	flag
	*/
	/* ウインドウの生成パらーメータをセットする */
	KsWindowParam	m_mainWindowParam;
	m_mainWindowParam.m_caption   = "Test";
	m_mainWindowParam.m_className = "KsSystem";
	m_mainWindowParam.m_style     = ksWINDOW_DEFAULT_STYLE;
	m_mainWindowParam.m_styleEx   = 0;
	m_mainWindowParam.m_posX      = ( rect.right  - rect.left )/2 - 320;
	m_mainWindowParam.m_posY      = ( rect.bottom - rect.top  )/2 - 240;
	m_mainWindowParam.m_sizeX     = 640;
	m_mainWindowParam.m_sizeY     = 480;

	/* ウインドウ生成 */
	KsWindow*	m_pMainWindow = new KsWindow( m_mainWindowParam );

	do{
	
	}while( m_pMainWindow->messageLoop() );

	return	0;
}