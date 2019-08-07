/*************************************************************************************************/
/** 
 * @file	KsWindow.cpp
 * @brief	�E�C���h�E
 * @author	Tukasa Kato
 * @date	2003/03/22
 * @since	----/--/--
 * @version	1.0.0
 */
/*************************************************************************************************/

/*************************************************************************************************/
/*                                 << �C���N���[�h >>                                             */
/*************************************************************************************************/
#include "KsWindow.h"

/*************************************************************************************************/
/*                              << �v���g�^�C�v�錾 >>                                            */
/*************************************************************************************************/
HINSTANCE	KsAppInstance::m_hInstance     = 0;
HINSTANCE	KsAppInstance::m_hPrevInstance = 0;
LPSTR		KsAppInstance::m_lpCmdLine     = 0;
KsInt32		KsAppInstance::m_nCmdShow      = 0;

//=================================================================================================
//
//=================================================================================================
void KsAppInstance::set( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, KsInt32 nCmdShow )
{
	m_hInstance		= hInstance;
	m_hPrevInstance	= hPrevInstance;
	m_lpCmdLine		= lpCmdLine;
	m_nCmdShow		= nCmdShow;
}

/*
 * �R���X�g���N�^(�E�C���h�E����)
 * @param		param			�E�C���h�E�����̂��߂̃p�����[�^
 * @param		hParent			�e�E�C���h�E�̃n���h��
 */
KsWindow::KsWindow( KsWindowParam& param, HWND hParent, void* pUserData )
{
	KsAssert( ksTRUE == create( param, hParent, pUserData ), "�E�C���h�E�𐶐��ł��܂���B" );
}

//=================================================================================================
//
//=================================================================================================
KsBool KsWindow::create( KsWindowParam &param, HWND hParent, void* pUserData )
{
	m_windowParam = param;

	WNDCLASSEX			wc;

	wc.cbSize			= sizeof( WNDCLASSEX );
	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc		= wndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 4;									// ���[�U�[�f�[�^�p��4�o�C�g�m�ۂ��Ă���
	wc.hInstance		= KsAppInstance::m_hInstance;			// �C���X�^���X
	wc.hIcon			= LoadIcon( NULL, IDI_APPLICATION );	//LoadIcon( KsAppInstance::m_hInstance, MAKEINTRESOURCE( IDI_ICON_MAIN ) );
	wc.hIconSm			= LoadIcon( NULL, IDI_APPLICATION );	//LoadIcon( KsAppInstance::m_hInstance, MAKEINTRESOURCE( IDI_ICON_SUB  ) );
	wc.lpszMenuName		= NULL;									//MAKEINTRESOURCE( IDR_MENU_MAIN );
	wc.hCursor			= LoadCursor( NULL,IDC_ARROW );
	wc.hbrBackground	= ( HBRUSH )GetStockObject( BLACK_BRUSH );
	wc.lpszClassName	= param.m_className.c_str();

	if( !::RegisterClassEx( &wc ) ) {
		return ksFALSE;
	}

	RECT	rect;

	rect.left   = 0;
	rect.top    = 0;
	rect.right  = param.m_sizeX;
	rect.bottom = param.m_sizeY;

    // �N���C�A���g�̃T�C�Y����E�B���h�E�̃T�C�Y�𓾂�
    AdjustWindowRectEx( &rect, param.m_style ,FALSE, 0 );		//���j���[�Ȃ�
	//AdjustWindowRectEx( &rect, param.m_style ,TRUE, 0 );		//���j���[����

	//.....�E�C���h�E�쐬
	m_hWnd = CreateWindowEx(
							param.m_styleEx,
							param.m_className.c_str(),
							param.m_caption.c_str(),
							param.m_style,
							param.m_posX,
							param.m_posY,
							rect.right  - rect.left,
							rect.bottom - rect.top,
							hParent,
							NULL,
							KsAppInstance::m_hInstance,
							pUserData
							);
	//.....�`��
	ShowWindow( m_hWnd, KsAppInstance::m_nCmdShow );
	//.....�X�V
	UpdateWindow( m_hWnd );

	return ksTRUE;
}
//=================================================================================================
//
//=================================================================================================
void KsWindow::setPos( int x, int y )
{
	if(m_hWnd==NULL) return;
	//
	SetWindowPos( m_hWnd, HWND_TOP, x, y, NULL, NULL, SWP_NOSIZE|SWP_NOZORDER );
}
//=================================================================================================
//
//=================================================================================================
void KsWindow::setCenter()
{
	HWND		hDeskWnd;
	RECT		deskrc,	rc;
	KsInt32	x, y;
	
	if( m_hWnd ){
		hDeskWnd = GetDesktopWindow();
		GetWindowRect( hDeskWnd, (LPRECT)&deskrc );
		GetWindowRect( m_hWnd, (LPRECT)&rc );
		x = ( deskrc.right  - ( rc.right-rc.left ) )/2;
		y = ( deskrc.bottom - ( rc.bottom-rc.top ) )/2;
		SetWindowPos( m_hWnd, HWND_TOP, x, y, (rc.right-rc.left), (rc.bottom-rc.top), SWP_SHOWWINDOW );
	}
}
//=================================================================================================
//
//=================================================================================================
KsInt32 KsWindow::messageLoop()
{
	MSG		msg;

	if( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )
	{
		if( msg.message == WM_QUIT ){
			return 0;
		}

		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}

	return 1;
}
//=================================================================================================
//
//=================================================================================================
LRESULT CALLBACK KsWindow::wndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	/*LPCREATESTRUCT lpcs;
		D3D9RenderWindow* win;

	if( WM_CREATE != uMsg )
	{
			// Get window pointer
			win = (D3D9RenderWindow*)GetWindowLong( hWnd, 0 );
	}*/

	switch( uMsg )
	{
		case WM_CREATE:
		{
			LPCREATESTRUCT	lpcs = (LPCREATESTRUCT)lParam;
			//win = (D3D9RenderWindow*)(lpcs->lpCreateParams);
			if( lpcs->lpCreateParams ){
				// Store pointer in window user data area
				//SetWindowLong( hWnd, 0, (KsInt32)win );
			}
			else{
				//win->mActive = true;
			}
			break;
		}
		/*case WM_CREATE:
		{
		lpcs = (LPCREATESTRUCT)lParam;
			win = (D3D9RenderWindow*)(lpcs->lpCreateParams);
			// Store pointer in window user data area
			SetWindowLong( hWnd, 0, (KsInt32)win );
			win->mActive = true;
			break;
		}*/
		case WM_KEYDOWN:
		{
	        switch( wParam )
			{	//�����I��
				case VK_ESCAPE:
			    case VK_F12:
					//WINDOW::m_AppEndReq = TRUE;
					//���b�Z�[�WWM_CLOASE��Windows�ɑ���
					// �E�C���h�E��Ԃ̎�����
					if( IDYES == MessageBox( hWnd, "�I�����܂����H", "�I���`�F�b�N", MB_YESNO | MB_ICONQUESTION ) ){
						PostMessage( hWnd, WM_CLOSE, 0, 0 );
					}
				break;
			}
			break;
		}
		case WM_DESTROY:
		{
			//::ShowWindow( hWnd, SW_HIDE );
			//::SetWindowLong( hWnd, GWL_STYLE, WS_POPUP );
			//::SetWindowPos( hWnd, (HWND)HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE );
	//		::ShowWindow( hWnd, SW_HIDE );
			PostQuitMessage(0);
			//PostMessage( hWnd, WM_CLOSE, 0, 0 );
			break;
		}
		/*case WM_NCDESTROY:
		{
			hWnd = NULL;
			break;
		}*/
		default:
		{
            return DefWindowProc( hWnd, uMsg, wParam, lParam );
		}

	}
	return 0;
}

