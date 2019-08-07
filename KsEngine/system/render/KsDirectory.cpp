/*************************************************************************************************/
/**
 * @file	KsDirectoy.cpp
 * @brief	�f�B���N�g������
 * @author	tsukasa kato
 * @date	2004/03/30
 * @version	1.0.0
 */
/*************************************************************************************************/

/*************************************************************************************************/
/*                                 << �C���N���[�h >>                                             */
/*************************************************************************************************/
#include "KsDirectory.h"
#include <mbctype.h>

/*************************************************************************************************/
/*                                     << ��` >>                                                */
/*************************************************************************************************/

/*************************************************************************************************/
/*                                     << �錾 >>                                                */
/*************************************************************************************************/
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
const string MakeFullPath()
{
	KsChar		currentDirectory[ _MAX_PATH ];
	
	// ���݂̃f�B���N�g�����擾����
	::GetCurrentDirectory( _MAX_PATH, currentDirectory );

	// �t���p�X
	string		path   = currentDirectory;
	size_t		length = path.length();

	if( length ){
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
const string SplitDirectoryName( const string& fullPath )
{
	string		path = fullPath;
	string		directoryName;
	size_t		pos;

	//..... �l�b�g���[�N�h���C�u���̃`�F�b�N
	if( path.substr( 0, 2 ) == "\\\\" ){
		// �l�b�g���[�N�h���C�u�����΂�
		pos = path.find( "\\", 2 );

		if( pos != -1 ){
			path.erase( 0, pos + 1 );
		}
		else{
			path.erase( 0, path.length() );
		}
	}
	else{
		// �h���C�u���΂�
		pos = path.find( ":" );

		if( pos != -1 ){
			path.erase( 0, pos+1 );
		}
	}

	//..... �擪�� '/' or '\\' �Ȃ�폜����
	string::iterator	pTop = path.begin();

	if( *pTop == '\\' || *pTop == '/' ){
		path.erase( 0, 1 );
	}

	//..... �u������( '/' �������� '\\' �ɒu������ )
	for( string::iterator it = path.begin(); it != path.end(); it++ )
	{
		if( *it == '\0' ){ break; }

		if( _ismbblead( *it ) ){
			// �}���`�o�C�g�Ȃ̂ł����ꕶ���i�߂�
			it++;
			// if( *(++it) == '\0' ){ break; }
		}
		else{
			if( *it == '/' ){
				*it = '\\';
			}
		}
	}

	//------------------------------------------//
	// �Ōォ�猟������							//
	// �I������'\\'�𔭌�						//
	// length == 0								//
	// '\\'������Ȃ�							//
	//------------------------------------------//
	size_t	length = path.length();

	if( length ){
		// �擪�� '/' or '\\' �Ȃ�폜����
		if( path[ length-1 ] == '\\' ){
			path.erase( length-1, length );
		}

		pos = path.rfind( '\\' );

		if( pos > -1 ){
			// ��������
			for( size_t i=pos+1; i<path.length(); i++ ){
				//directoryName.push_back( path[ i ] );
				directoryName[ directoryName.length() ] = path[ i ];
			}
		}
		else{
			// ������Ȃ�����
			directoryName = path;
		}
	}
	else{
		directoryName = "";
	}

	return directoryName;
}


//=================================================================================================
// �R���X�g���N�^(�ċA�����p)
//=================================================================================================
KsDirectory::KsDirectory( const string& directoryName, KsDirectory* pParent )
{
	m_directoryName = directoryName;
	m_fullPath      = pParent->getFullPath() + directoryName;

	size_t	length = m_fullPath.length();

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
	while( m_directoryList.size() ){
		delete m_directoryList[ 0 ];
	}
}

//=================================================================================================
// ���̑O�ɂ�����ƃf�B���N�g������؂蕪���Ă����K�v������
//=================================================================================================
void KsDirectory::parseDirectory( const string& directory )
{
	if( !directory.length() ){
		return;
	}

	WIN32_FIND_DATA		findData;
	KsChar				path[ _MAX_PATH ];

	//..... ���������擾����
	strcpy( path, directory.c_str() );
	strcat( path, "*" );
	HANDLE	handle = ::FindFirstFile( path, &findData );

	// ���擾����
	if( handle != INVALID_HANDLE_VALUE )
	{
		do
		{
			//..... ���݂̃f�B���N�g���i�t�H���_�j�Ɛe�f�B���N�g���͔r�� 
			if( ( strcmp( findData.cFileName, ".." ) != 0 ) && ( strcmp( findData.cFileName, "." ) != 0 ) )
			{
				//.....�f�B���N�g�����t�@�C�����̃`�F�b�N
				if( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ){
					//..... �f�B���N�g���̎�(���݂̃f�B���N�g������n��)
					new KsDirectory( string( findData.cFileName ), this );
				}
				else{
					//..... �t�@�C����ǉ�����
					m_fileList.push_back( string( findData.cFileName ) );
				}
			}

		}while( ::FindNextFile( handle, &findData ) );
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
	for( KsUInt32 i=0; i<m_directoryList.size(); i++ ){
		if( ( m_directoryList[ i ] == pDirectory ) || ( m_directoryList[ i ]->getDirectoryName() == pDirectory->getDirectoryName() ) ){
			return;
		}
	}

	/* �f�B���N�g���ǉ� */
	m_directoryList.push_back( pDirectory );

	/* �e�ɐݒ肷�� */
	pDirectory->m_pParent = this;
}

//=================================================================================================
// �f�^�b�`����
//=================================================================================================
void KsDirectory::detach( KsDirectory* pDirectory )
{
	/* �o�^���s�����̃`�F�b�N */
	if( !pDirectory ){
		return;
	}

	for( KsDirectoryListPtr it=m_directoryList.begin(); it!=m_directoryList.end(); it++ )
	{
		if( (*it) == pDirectory ){
			m_directoryList.erase( it );
			pDirectory->m_pParent = NULL;
			return;
		}
	}

	pDirectory->m_pParent = NULL;
}






