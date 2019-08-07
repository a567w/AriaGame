/*************************************************************************************************/
/** 
 * @file	KsWindowUtility.cpp
 * @brief	Windows�֌W���[�e�B���e�B
 * @author	Tukasa Kato
 * @date	2003/03/22
 * @since	----/--/--
 * @version	1.0.0
 */
/*************************************************************************************************/


/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"
#include "KsEngine/win/KsWindowUtility.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/*************************************************************************************************/
/*
 * �^�X�N�o�[���������f�X�N�g�b�v�̃T�C�Y���擾����
 * @param		pRect		(OUT)�T�C�Y���擾����\���̂̃|�C���^
 */
/*************************************************************************************************/
void KsWindowUtility::getDeskTopClientRect( RECT* pRect )
{
	// �^�X�N�o�[���������T�C�Y���擾����
	::SystemParametersInfo( SPI_GETWORKAREA, 0, pRect, 0 );
}

/*************************************************************************************************/
/*
 * �f�X�N�g�b�v�̃T�C�Y���擾����
 * @param		pRect		(OUT)�T�C�Y���擾����\���̂̃|�C���^
 */
/*************************************************************************************************/
void KsWindowUtility::getDeskTopWindowRect( RECT* pRect )
{
	::GetWindowRect( GetDesktopWindow(), pRect );
}

/*************************************************************************************************/
/*
 * GetNativeSystemInfo���b�p�[�֐�
 * @parm	lpSystemInfo	(OUT)�V�X�e�������擾����\���̂̃|�C���^
 * @retval	ksTRUE			�擾����
 * @retval	ksFALSE			�擾���s
 * @note GetNativeSystemInfo��Windows XP�ȍ~�ŃT�|�[�g����Ă���B
 *		 ���̂���Windows 2000�ȑO�ł�ksFALSE���Ԃ�
 */
/*************************************************************************************************/
KsBool KsWindowUtility::getNativeSystemInfo( LPSYSTEM_INFO lpSystemInfo )
{
	HMODULE	hDLL;
	void	(CALLBACK* pfnGetNativeSystemInfo)(LPSYSTEM_INFO);

	if( lpSystemInfo == NULL )
	{
		return ksFALSE;
	}

	KsZeroMemory( lpSystemInfo, sizeof(SYSTEM_INFO) );

	hDLL = ::LoadLibrary( _T("Kernel32.dll") );

	if( hDLL == NULL )
	{
		return ksFALSE;
	}

	(*(FARPROC*)&pfnGetNativeSystemInfo) = ::GetProcAddress( hDLL, "GetNativeSystemInfo" );

	if( pfnGetNativeSystemInfo == NULL )
	{
		::FreeLibrary( hDLL );
		return	ksFALSE;
	}

	pfnGetNativeSystemInfo( lpSystemInfo );

	::FreeLibrary( hDLL );

	return	ksTRUE;
}

/*************************************************************************************************/
/*
 * �v���Z�b�T�̐����擾����
 * @return	�v���Z�b�T�̐�
 */
/*************************************************************************************************/
KsUInt32 KsWindowUtility::getNumProcessor()
{
	SYSTEM_INFO	sysInfo;

	if( getNativeSystemInfo( &sysInfo ) )
	{
		return s_cast<KsUInt32>( sysInfo.dwNumberOfProcessors );
	}

	return 1;
}

/*************************************************************************************************/
/*
 * �������E�C���h�E���A�N�e�B�u�ɂ���
 */
/*************************************************************************************************/
KsBool KsWindowUtility::activeFindWindow( const KsChar* pClassName, const KsChar* pWindowName )
{
	/* �E�B���h�E�̃^�C�g������ɓ����ꍇ�́A��Q�����Ƀ^�C�g�����w�� */
	HWND	hWnd = FindWindow( pClassName, pWindowName );

	if( hWnd )
	{
		/* ���� */
		/* �A�C�R��������Ă���̂ł���΁A���̃T�C�Y�ɖ߂� */
		if( IsIconic( hWnd ) )
		{
			ShowWindow( hWnd, SW_RESTORE );
		}

		/* ���������E�B���h�E���t�H�A�O���E���h�E�B���h�E�ɂ��� */
		SetForegroundWindow( ::GetLastActivePopup( hWnd ) );
		//::SetForegroundWindow(hWnd);

		SetActiveWindow( hWnd );

		InvalidateRect( hWnd, NULL, false );

		return ksTRUE;
	}

	return ksFALSE;
}



