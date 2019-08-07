/*************************************************************************************************/
/**
 * @file	KsDirectoy.cpp
 * @brief	�f�B���N�g������
 * @author	tsukasa kato
 * @date	2004/03/30
 * @version	1.0.0
 */
/*************************************************************************************************/

/*===============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*===============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"
#include <mbctype.h>

/*===============================================================================================*/
/*                                     << ��` >>                                                */
/*===============================================================================================*/

/*===============================================================================================*/
/*                                     << �錾 >>                                                */
/*===============================================================================================*/
using namespace std;

/*
//=================================================================================================
// �}���`�o�C�g���������`�F�b�N����
//=================================================================================================
inline KsBool _ismbblead( KsUInt32 c )
{
	if( ((KsByte)c >= 0x80 && (KsByte)c <= 0xA0) || ((KsByte)c >= 0xE0 && (KsByte)c <= 0xFF)) {
		return ksTRUE;
	}
	return ksFALSE;
}
*/


//=================================================================================================
// �f�B���N�g�����ɂ���
//=================================================================================================
const KsString MakeFullPath()
{
	KsChar		currentDirectory[ _MAX_PATH ];
	
	// ���݂̃f�B���N�g�����擾����
	//::GetCurrentDirectory( _MAX_PATH, currentDirectory );
	::GetCurrentDirectory( _MAX_PATH, currentDirectory );

	// �t���p�X
	KsString	path   = currentDirectory;
	KsUInt32	length = path.length();

	if( length )
	{
		// �p�X�̏I���`�F�b�N����
		if( path[ length-1 ] != '\\' && path[ length-1 ] != '/' ){
			path += '\\';
		}
	}

	return path;
}

//=================================================================================================
// �t���p�X����f�B���N�g���Ɛ؂蕪����
//=================================================================================================
const KsString SplitDirectoryName( const KsString& fullPath )
{
	KsString		path = fullPath;
	KsString		directoryName;
	KsUInt32		pos;

	//..... �l�b�g���[�N�h���C�u���̃`�F�b�N
	if( ( path.length() > 1 ) && ( path[ 0 ] == '\\') && ( path[ 1 ] == '\\' ) )
	{
		// �l�b�g���[�N�h���C�u�����΂�
		path.erase( 0, 2 );
	}
	else
	{
		// �h���C�u���΂�
		for( KsUInt32 i=0; i<path.length(); i++ )
		{
			if( path[ i ] == ':' )
			{
				pos = i;
				break;
			}
		}

		if( pos != -1 )
		{
			path.erase( 0, pos+1 );
		}
	}

	//..... �擪�� '/' or '\\' �Ȃ�폜����
	KsChar	top = path[ 0 ];

	if( top == '\\' || top == '/' )
	{
		path.erase( 0, 1 );
	}

	//..... �u������( '/' �������� '\\' �ɒu������ )
	for( KsUInt32 i=0; i<path.length(); i++ )
	{
		KsChar	temp = path[ i ];

		if( temp == '\0' ){ break; }

		if( _ismbblead( temp ) )
		{
			// �}���`�o�C�g�Ȃ̂ł����ꕶ���i�߂�
			i++;
			// if( *(++it) == '\0' ){ break; }
		}
		else
		{
			if( temp == '/' ){
				temp = '\\';
			}
		}
	}

	//------------------------------------------//
	// �Ōォ�猟������							//
	// �I������'\\'�𔭌�						//
	// length == 0								//
	// '\\'������Ȃ�							//
	//------------------------------------------//
	KsUInt32	length = path.length();

	if( length )
	{
		// �擪�� '/' or '\\' �Ȃ�폜����
		if( path[ length-1 ] == '\\' )
		{
			path.erase( length-1, length );
		}

		pos = -1;

		for( KsUInt32 i=length; i != 0; i-- )
		{
			if( path[ i ] == '\\' )
			{
				pos = i;
				break;
			}
		}

		if( pos > -1 )
		{
			// ��������
			directoryName = path;
			directoryName.erase( 0, pos+1 );
		}
		else
		{
			// ������Ȃ�����
			directoryName = path;
		}
	}
	else
	{
		directoryName = _T("");
	}

	return directoryName;
}


//=================================================================================================
// �R���X�g���N�^(�ċA�����p)
//=================================================================================================
KsDirectory::KsDirectory( const KsString& directoryName, KsDirectory* pParent )
{
	m_directoryName = directoryName;
	m_fullPath      = pParent->getFullPath();
	m_fullPath     += directoryName;

	KsUInt32	length = m_fullPath.length();

	if( length ){
		// �p�X�̏I���`�F�b�N����
		if( m_fullPath[ length-1 ] != '\\' && m_fullPath[ length-1 ] != '/' ){
			m_fullPath += '\\';
		}
	}

	// �e���Z�b�g����
	if( pParent ){
		pParent->attach( this );
	}

	/* �f�B���N�g������͂��� */
	parseDirectory( m_fullPath );
}

//=================================================================================================
// �R���X�g���N�^
//=================================================================================================
KsDirectory::KsDirectory()
{
	m_fullPath      = MakeFullPath();
	m_directoryName = SplitDirectoryName( m_fullPath );
	m_pParent       = NULL;

	parseDirectory( m_fullPath );
}

//=================================================================================================
// �f�X�g���N�^
//=================================================================================================
KsDirectory::~KsDirectory()
{
	if( m_pParent ){
		m_pParent->detach( this );
	}

	// �t�@�C�����폜����
	m_fileList.clear();

	// �f�B���N�g�����폜����
	while( m_vpDirectories.size() )
	{
		delete m_vpDirectories[ 0 ];
	}
}

//=================================================================================================
// ���̑O�ɂ�����ƃf�B���N�g������؂蕪���Ă����K�v������
//=================================================================================================
void KsDirectory::parseDirectory( const KsString& directory )
{
	if( !directory.length() ){
		return;
	}

	//WIN32_FIND_DATA		findData;
	WIN32_FIND_DATA		findData;
	KsChar				path[ _MAX_PATH ];

	//..... ���������擾����
	ks_strcpy( path, directory.c_str() );
	ks_strcat( path, _T("*") );
	HANDLE	handle = ::FindFirstFile( path, &findData );
	//HANDLE	handle = ::FindFirstFile( path, &findData );

	// ���擾����
	if( handle != INVALID_HANDLE_VALUE )
	{
		do
		{
			//..... ���݂̃f�B���N�g���i�t�H���_�j�Ɛe�f�B���N�g���͔r�� 
			if( ( ks_strcmp( findData.cFileName, _T("..") ) != 0 ) && ( ks_strcmp( findData.cFileName, _T(".") ) != 0 ) )
			{
				//.....�f�B���N�g�����t�@�C�����̃`�F�b�N
				if( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
				{
					//..... �f�B���N�g���̎�(���݂̃f�B���N�g������n��)
					new KsDirectory( KsString( findData.cFileName ), this );
				}
				else
				{
					//..... �t�@�C����ǉ�����
					m_fileList.push_back( KsString( findData.cFileName ) );
				}
			}

		}while( ::FindNextFile( handle, &findData ) );
		//}while( ::FindNextFile( handle, &findData ) );
	}

	//..... ������Ȃ���ΒT���I��
	::FindClose( handle );
}

//=================================================================================================
// �A�^�b�`����
//=================================================================================================
void KsDirectory::attach( KsDirectory* pDirectory )
{
	/* �o�^���s�����̃`�F�b�N */
	if( !pDirectory ){
		return;
	}

	/* ���łɂ��̃f�B���N�g�����o�^����Ă��邩���`�F�b�N���� */
	for( KsUInt32 i=0; i<m_vpDirectories.size(); i++ )
	{
		if( ( m_vpDirectories[ i ] == pDirectory ) || ( m_vpDirectories[ i ]->getDirectoryName() == pDirectory->getDirectoryName() ) ){
			return;
		}
	}

	/* �f�B���N�g���ǉ� */
	m_vpDirectories.push_back( pDirectory );

	/* �e�ɐݒ肷�� */
	pDirectory->m_pParent = this;
}

//=================================================================================================
// �f�^�b�`����
//=================================================================================================
void KsDirectory::detach( KsDirectory* pDirectory )
{
	/* �o�^���s�����̃`�F�b�N */
	if( !pDirectory )
	{
		return;
	}

	for( KsUInt32 i=0; i<m_vpDirectories.size(); i++ )
	{
		KsDirectory*	pTemp = m_vpDirectories[ i ];

		if( pTemp == pDirectory )
		{
			m_vpDirectories.erase( i );
			pDirectory->m_pParent = NULL;
			return;
		}
	}

	pDirectory->m_pParent = NULL;
}


#if 0
char[] toMBS(wchar[] s)
{
	char[] result;
version(Win32){
	result.length = WideCharToMultiByte(0, 0, (char*)s, s.length,
		null, 0, null, null);
	WideCharToMultiByte(0, 0, (char*)s, s.length, result,
		result.length, null, null);
}else{
	synchronized (locale_sync_object) {
		char* o = setlocale(LC_ALL, null);
		setlocale(LC_ALL, "");
		result.length = wcstombs(null, s, 0);
		wcstombs(result, s, result.length);
		setlocale(LC_ALL, o);
	}
}
	return result;
}

///	�}���`�o�C�g��unicode�ϊ�
wchar[] toWCS(char[] s)
{
	wchar[] result;
version(Win32){
	result.length = MultiByteToWideChar(0, 0, (char*)s, s.length,
		null, 0);
	MultiByteToWideChar(0, 0, (char*)s, s.length,(wchar*)result,
		result.length);
}else{
	synchronized (locale_sync_object) {
		char* o = setlocale(LC_ALL, null);
		setlocale(LC_ALL, "");
		result.length = mbstowcs(null, s, 0);
		mbstowcs(result, s, result.length);
		setlocale(LC_ALL, o);
	}
}
	return result;
}


///	�[���I�[��WCS��Ԃ�
char* toMBSz(wchar[] s) { return std.string.toStringz(toMBS(s)); }

///	�[���I�[��MBS��Ԃ�
char* toMBSz(wchar* s) { return std.string.toStringz(toMBS(s[0..std.string.wcslen(s)])); }

/// UTF8����WCS��Ԃ�
char[] toMBS(char[] s) { return toMBS(std.utf.toUTF16(s)); }

/// UTF8����[���I�[��WCS��Ԃ�
char* toMBSz(char[] s) { return std.string.toStringz(toMBS(s)); }

/*
/// �[���I�[��WCS��Ԃ�
wchar[] toWCSz(char[] s) { return std.string.toStringz(toWCS(s)); }
/// �[���I�[��WCS��Ԃ�
wchar[] toWCSz(char* s) { return std.string.toStringz(toWCS(s[0..std.string.strlen(s)])); }
*/

version(Win32){
} else {
/// set locale�ŃX���b�h�r�����邽�߂̓����I�u�W�F�N�g
private static Object locale_sync_object;
}
#endif


