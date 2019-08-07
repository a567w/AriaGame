/*************************************************************************************************/
/**
 * @file	KsDirectoy.cpp
 * @brief	ディレクトリ操作
 * @author	tsukasa kato
 * @date	2004/03/30
 * @version	1.0.0
 */
/*************************************************************************************************/

/*===============================================================================================*/
/*                                 << インクルード >>                                            */
/*===============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"
#include <mbctype.h>

/*===============================================================================================*/
/*                                     << 定義 >>                                                */
/*===============================================================================================*/

/*===============================================================================================*/
/*                                     << 宣言 >>                                                */
/*===============================================================================================*/
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
const KsString MakeFullPath()
{
	KsChar		currentDirectory[ _MAX_PATH ];
	
	// 現在のディレクトリを取得する
	//::GetCurrentDirectory( _MAX_PATH, currentDirectory );
	::GetCurrentDirectory( _MAX_PATH, currentDirectory );

	// フルパス
	KsString	path   = currentDirectory;
	KsUInt32	length = path.length();

	if( length )
	{
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
const KsString SplitDirectoryName( const KsString& fullPath )
{
	KsString		path = fullPath;
	KsString		directoryName;
	KsUInt32		pos;

	//..... ネットワークドライブかのチェック
	if( ( path.length() > 1 ) && ( path[ 0 ] == '\\') && ( path[ 1 ] == '\\' ) )
	{
		// ネットワークドライブ名を飛ばす
		path.erase( 0, 2 );
	}
	else
	{
		// ドライブを飛ばす
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

	//..... 先頭が '/' or '\\' なら削除する
	KsChar	top = path[ 0 ];

	if( top == '\\' || top == '/' )
	{
		path.erase( 0, 1 );
	}

	//..... 置換する( '/' だったら '\\' に置換する )
	for( KsUInt32 i=0; i<path.length(); i++ )
	{
		KsChar	temp = path[ i ];

		if( temp == '\0' ){ break; }

		if( _ismbblead( temp ) )
		{
			// マルチバイトなのでもう一文字進める
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
	// 最後から検索する							//
	// 終了条件'\\'を発見						//
	// length == 0								//
	// '\\'が一つもない							//
	//------------------------------------------//
	KsUInt32	length = path.length();

	if( length )
	{
		// 先頭が '/' or '\\' なら削除する
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
			// 見つかった
			directoryName = path;
			directoryName.erase( 0, pos+1 );
		}
		else
		{
			// 見つからなかった
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
// コンストラクタ(再帰処理用)
//=================================================================================================
KsDirectory::KsDirectory( const KsString& directoryName, KsDirectory* pParent )
{
	m_directoryName = directoryName;
	m_fullPath      = pParent->getFullPath();
	m_fullPath     += directoryName;

	KsUInt32	length = m_fullPath.length();

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
	while( m_vpDirectories.size() )
	{
		delete m_vpDirectories[ 0 ];
	}
}

//=================================================================================================
// この前にきちんとディレクトリ名を切り分けておく必要がある
//=================================================================================================
void KsDirectory::parseDirectory( const KsString& directory )
{
	if( !directory.length() ){
		return;
	}

	//WIN32_FIND_DATA		findData;
	WIN32_FIND_DATA		findData;
	KsChar				path[ _MAX_PATH ];

	//..... 検索情報を取得する
	ks_strcpy( path, directory.c_str() );
	ks_strcat( path, _T("*") );
	HANDLE	handle = ::FindFirstFile( path, &findData );
	//HANDLE	handle = ::FindFirstFile( path, &findData );

	// 情報取得処理
	if( handle != INVALID_HANDLE_VALUE )
	{
		do
		{
			//..... 現在のディレクトリ（フォルダ）と親ディレクトリは排除 
			if( ( ks_strcmp( findData.cFileName, _T("..") ) != 0 ) && ( ks_strcmp( findData.cFileName, _T(".") ) != 0 ) )
			{
				//.....ディレクトリかファイルかのチェック
				if( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
				{
					//..... ディレクトリの時(現在のディレクトリ名を渡す)
					new KsDirectory( KsString( findData.cFileName ), this );
				}
				else
				{
					//..... ファイルを追加する
					m_fileList.push_back( KsString( findData.cFileName ) );
				}
			}

		}while( ::FindNextFile( handle, &findData ) );
		//}while( ::FindNextFile( handle, &findData ) );
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
	for( KsUInt32 i=0; i<m_vpDirectories.size(); i++ )
	{
		if( ( m_vpDirectories[ i ] == pDirectory ) || ( m_vpDirectories[ i ]->getDirectoryName() == pDirectory->getDirectoryName() ) ){
			return;
		}
	}

	/* ディレクトリ追加 */
	m_vpDirectories.push_back( pDirectory );

	/* 親に設定する */
	pDirectory->m_pParent = this;
}

//=================================================================================================
// デタッチする
//=================================================================================================
void KsDirectory::detach( KsDirectory* pDirectory )
{
	/* 登録が不正かのチェック */
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

///	マルチバイト→unicode変換
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


///	ゼロ終端なWCSを返す
char* toMBSz(wchar[] s) { return std.string.toStringz(toMBS(s)); }

///	ゼロ終端なMBSを返す
char* toMBSz(wchar* s) { return std.string.toStringz(toMBS(s[0..std.string.wcslen(s)])); }

/// UTF8からWCSを返す
char[] toMBS(char[] s) { return toMBS(std.utf.toUTF16(s)); }

/// UTF8からゼロ終端なWCSを返す
char* toMBSz(char[] s) { return std.string.toStringz(toMBS(s)); }

/*
/// ゼロ終端なWCSを返す
wchar[] toWCSz(char[] s) { return std.string.toStringz(toWCS(s)); }
/// ゼロ終端なWCSを返す
wchar[] toWCSz(char* s) { return std.string.toStringz(toWCS(s[0..std.string.strlen(s)])); }
*/

version(Win32){
} else {
/// set localeでスレッド排他するための同期オブジェクト
private static Object locale_sync_object;
}
#endif


