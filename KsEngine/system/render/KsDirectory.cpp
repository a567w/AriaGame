/*************************************************************************************************/
/**
 * @file	KsDirectoy.cpp
 * @brief	ディレクトリ操作
 * @author	tsukasa kato
 * @date	2004/03/30
 * @version	1.0.0
 */
/*************************************************************************************************/

/*************************************************************************************************/
/*                                 << インクルード >>                                             */
/*************************************************************************************************/
#include "KsDirectory.h"
#include <mbctype.h>

/*************************************************************************************************/
/*                                     << 定義 >>                                                */
/*************************************************************************************************/

/*************************************************************************************************/
/*                                     << 宣言 >>                                                */
/*************************************************************************************************/
using namespace std;


/*
//=================================================================================================
// マルチバイト文字かをチェックする
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
// ディレクトリ名にする
//=================================================================================================
const string MakeFullPath()
{
	KsChar		currentDirectory[ _MAX_PATH ];
	
	// 現在のディレクトリを取得する
	::GetCurrentDirectory( _MAX_PATH, currentDirectory );

	// フルパス
	string		path   = currentDirectory;
	size_t		length = path.length();

	if( length ){
		// パスの終了チェックする
		if( path[ length-1 ] != '\\' && path[ length-1 ] != '/' ){
			path += '\\';
		}
	}

	return path;
}

//=================================================================================================
// フルパスからディレクトリと切り分ける
//=================================================================================================
const string SplitDirectoryName( const string& fullPath )
{
	string		path = fullPath;
	string		directoryName;
	size_t		pos;

	//..... ネットワークドライブかのチェック
	if( path.substr( 0, 2 ) == "\\\\" ){
		// ネットワークドライブ名を飛ばす
		pos = path.find( "\\", 2 );

		if( pos != -1 ){
			path.erase( 0, pos + 1 );
		}
		else{
			path.erase( 0, path.length() );
		}
	}
	else{
		// ドライブを飛ばす
		pos = path.find( ":" );

		if( pos != -1 ){
			path.erase( 0, pos+1 );
		}
	}

	//..... 先頭が '/' or '\\' なら削除する
	string::iterator	pTop = path.begin();

	if( *pTop == '\\' || *pTop == '/' ){
		path.erase( 0, 1 );
	}

	//..... 置換する( '/' だったら '\\' に置換する )
	for( string::iterator it = path.begin(); it != path.end(); it++ )
	{
		if( *it == '\0' ){ break; }

		if( _ismbblead( *it ) ){
			// マルチバイトなのでもう一文字進める
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
	// 最後から検索する							//
	// 終了条件'\\'を発見						//
	// length == 0								//
	// '\\'が一つもない							//
	//------------------------------------------//
	size_t	length = path.length();

	if( length ){
		// 先頭が '/' or '\\' なら削除する
		if( path[ length-1 ] == '\\' ){
			path.erase( length-1, length );
		}

		pos = path.rfind( '\\' );

		if( pos > -1 ){
			// 見つかった
			for( size_t i=pos+1; i<path.length(); i++ ){
				//directoryName.push_back( path[ i ] );
				directoryName[ directoryName.length() ] = path[ i ];
			}
		}
		else{
			// 見つからなかった
			directoryName = path;
		}
	}
	else{
		directoryName = "";
	}

	return directoryName;
}


//=================================================================================================
// コンストラクタ(再帰処理用)
//=================================================================================================
KsDirectory::KsDirectory( const string& directoryName, KsDirectory* pParent )
{
	m_directoryName = directoryName;
	m_fullPath      = pParent->getFullPath() + directoryName;

	size_t	length = m_fullPath.length();

	if( length ){
		// パスの終了チェックする
		if( m_fullPath[ length-1 ] != '\\' && m_fullPath[ length-1 ] != '/' ){
			m_fullPath += '\\';
		}
	}

	// 親をセットする
	if( pParent ){
		pParent->attach( this );
	}

	/* ディレクトリを解析する */
	parseDirectory( m_fullPath );
}

//=================================================================================================
// コンストラクタ
//=================================================================================================
KsDirectory::KsDirectory()
{
	m_fullPath      = MakeFullPath();
	m_directoryName = SplitDirectoryName( m_fullPath );
	m_pParent       = NULL;

	parseDirectory( m_fullPath );
}

//=================================================================================================
// デストラクタ
//=================================================================================================
KsDirectory::~KsDirectory()
{
	if( m_pParent ){
		m_pParent->detach( this );
	}

	// ファイルを削除する
	m_fileList.clear();

	// ディレクトリを削除する
	while( m_directoryList.size() ){
		delete m_directoryList[ 0 ];
	}
}

//=================================================================================================
// この前にきちんとディレクトリ名を切り分けておく必要がある
//=================================================================================================
void KsDirectory::parseDirectory( const string& directory )
{
	if( !directory.length() ){
		return;
	}

	WIN32_FIND_DATA		findData;
	KsChar				path[ _MAX_PATH ];

	//..... 検索情報を取得する
	strcpy( path, directory.c_str() );
	strcat( path, "*" );
	HANDLE	handle = ::FindFirstFile( path, &findData );

	// 情報取得処理
	if( handle != INVALID_HANDLE_VALUE )
	{
		do
		{
			//..... 現在のディレクトリ（フォルダ）と親ディレクトリは排除 
			if( ( strcmp( findData.cFileName, ".." ) != 0 ) && ( strcmp( findData.cFileName, "." ) != 0 ) )
			{
				//.....ディレクトリかファイルかのチェック
				if( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ){
					//..... ディレクトリの時(現在のディレクトリ名を渡す)
					new KsDirectory( string( findData.cFileName ), this );
				}
				else{
					//..... ファイルを追加する
					m_fileList.push_back( string( findData.cFileName ) );
				}
			}

		}while( ::FindNextFile( handle, &findData ) );
	}

	//..... 見つからなければ探索終了
	::FindClose( handle );
}

//=================================================================================================
// アタッチする
//=================================================================================================
void KsDirectory::attach( KsDirectory* pDirectory )
{
	/* 登録が不正かのチェック */
	if( !pDirectory ){
		return;
	}

	/* すでにこのディレクトリが登録されているかをチェックする */
	for( KsUInt32 i=0; i<m_directoryList.size(); i++ ){
		if( ( m_directoryList[ i ] == pDirectory ) || ( m_directoryList[ i ]->getDirectoryName() == pDirectory->getDirectoryName() ) ){
			return;
		}
	}

	/* ディレクトリ追加 */
	m_directoryList.push_back( pDirectory );

	/* 親に設定する */
	pDirectory->m_pParent = this;
}

//=================================================================================================
// デタッチする
//=================================================================================================
void KsDirectory::detach( KsDirectory* pDirectory )
{
	/* 登録が不正かのチェック */
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






