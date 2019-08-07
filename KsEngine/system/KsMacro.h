/*************************************************************************************************/
/**
 * @file	KsMacro.h
 * @brief	マクロ
 * @author	Tsukasa Kato
 * @date	----/--/--
 * @version	1.0.0
 */
/*************************************************************************************************/
#ifndef __KSMACRO_H__
#define __KSMACRO_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*************************************************************************************************/
/**
 * メモリーのゼロクリア
 * @param	p		クリアするメモリーの先頭アドレス
 * @param	size	クリアするサイズ
 */
/*************************************************************************************************/
inline void KsZeroMemory( void* p, KsSize size )
{
	memset( p, 0, size );
}

/*************************************************************************************************/
/**
 * メモリーのゼロクリア
 * @param	p		クリアするメモリーの先頭アドレス
 * @param	size	クリアするサイズ
 */
/*************************************************************************************************/
inline void KsMemset( void* p, KsInt32 val, KsSize size )
{
	memset( p, val, size );
}

/*************************************************************************************************/
/**
 * メモリーのゼロクリア
 * @param	p		クリアするメモリーの先頭アドレス
 * @param	size	クリアするサイズ
 */
/*************************************************************************************************/
inline void KsMemCopy( void* dst, const void* src, KsSize size )
{
	memcpy( dst, src, size );
}

/*************************************************************************************************/
/**
 * 配列のサイズを取得する
 * @param	dataArray		配列
 */
/*************************************************************************************************/
template <typename T, size_t N>
char (*KsRtlpNumberOf( UNALIGNED T (&)[N] ))[N];
#define ksARRAYSIZE( dataArray )	( sizeof(*KsRtlpNumberOf( dataArray )) )
//#define ksARRAYSIZE( dataArray )	( sizeof(dataArray)/sizeof(dataArray[ 0 ]) )

/*************************************************************************************************/
/**
 * 角度変換（度からラジアンに変換）
 * @param	degree		角度
 */
/*************************************************************************************************/
#define ksDEG( degree )				( (degree) * ( ksPI / 180.0f) )

/*************************************************************************************************/
/**
 * 角度変換（ラジアンから度に変換）
 * @param	radian		ラジアン
 */
/*************************************************************************************************/
#define ksRAD( radian )				( (radian) * ( 180.0f / ksPI) )

/*************************************************************************************************/
/**
 * 32bitカラー値
 * @param	r		レッド
 * @param	g		グリーン
 * @param	b		ブルー
 * @param	a		アルファ
 */
/*************************************************************************************************/
#define ksRGBA32( r, g, b, a )		( (KsUInt32)(a<<24) | (KsUInt32)(b<<16) | (KsUInt32)(g<<8) | (KsUInt32)r )

/*************************************************************************************************/
/**
 * 32bitカラー値
 */
/*************************************************************************************************/
#define ksRGB32( r, g, b )			( (KsUInt32)(b<<16) | (KsUInt32)(g<<8) | (KsUInt32)r )

/*************************************************************************************************/
/**
 * ワード値にする
 */
/*************************************************************************************************/
#define ksMAKE_WORD( a, b )		( (KsWord)(b<<8) | (KsWord)a )

/*************************************************************************************************/
/**
 * ダブルワード値にする
 */
/*************************************************************************************************/
#define ksMAKE_DWORD( a, b, c, d ) ( (KsDWord)(d<<24) | (KsDWord)(c<<16) | (KsDWord)(b<<8) | (KsDWord)a )

/* delete マクロ */
/*************************************************************************************************/
/**
 * new で確保したメモリーの解放をする
 * @param		p					開放するメモリーのポインタ
 */
/*************************************************************************************************/
#define ksDELETE( p )				if( p ){ delete p; p = NULL; }

/*************************************************************************************************/
/**
 * new [] で確保したメモリーの解放をする
 * @param		p					開放するメモリーのポインタ
 */
/*************************************************************************************************/
#define ksDELETEARRAY( p )		if( p ){ delete [] p; p = NULL; }

/*************************************************************************************************/
/**
 * 開放マクロ
 */
/*************************************************************************************************/
#define ksRELEASE( p )			if( p ){ (p)->Release(); p = NULL; }

/*************************************************************************************************/
/**
 * 開放マクロ
 */
/*************************************************************************************************/
#define ksFREE( p )				if( p ){ free( p ); p = NULL; }

/*************************************************************************************************/
/**
 * DirectX用,開放マクロ
 */
/*************************************************************************************************/
#define ksDESTROY( p )			if( p ){ (p)->destroy(); p = NULL; }

#define ksDELETEOBJECT( p )		if( p ){ ::DeleteObject(p); p = NULL; }

#define ksSUCCEEDED( x )			( (HRESULT)(x) >= 0 )
#define ksFAILED( x )				( (HRESULT)(x)  < 0 )

#define ksDELETEARRAYTEMPLATE( _arrayData )		\
{													\
	for( KsUInt32 i=0; i<_arrayData.size(); i++ )	\
	{												\
		ksDELETE( _arrayData[ i ] );				\
	}												\
	_arrayData.clear();								\
}



inline KsChar* ks_strcpy( KsChar* _Str1, const KsChar* _Str2 )
{
#ifdef  UNICODE
	return wcscpy( _Str1, _Str2 );
#else
	return strcpy( _Str1, _Str2 );
#endif // #ifdef  UNICODE
}

inline KsChar* ks_strncpy( KsChar* _Str1, const KsChar* _Str2, KsInt32 _Count )
{
#ifdef  UNICODE
	return wcsncpy( _Str1, _Str2, _Count );
#else
	return strncpy( _Str1, _Str2, _Count );
#endif // #ifdef  UNICODE
}


inline KsInt32 ks_strcmp( const KsChar* _Str1, const KsChar* _Str2 )
{
#ifdef  UNICODE
	return wcscmp( _Str1, _Str2 );
#else
	return strcmp( _Str1, _Str2 );
#endif // #ifdef  UNICODE
}

inline KsInt32 ks_strncmp( const KsChar* _Str1, const KsChar* _Str2, KsInt32 _Count )
{
#ifdef  UNICODE
	return wcsncmp( _Str1, _Str2, _Count );
#else
	return strncmp( _Str1, _Str2, _Count );
#endif // #ifdef  UNICODE
}


inline KsInt32 ks_strlen( const KsChar* _Str )
{
#ifdef  UNICODE
	return s_cast<KsInt32>(wcslen( _Str ));
#else
	return strlen( _Str );
#endif // #ifdef  UNICODE
}

inline KsChar* ks_strcat( KsChar* _Dest, const KsChar* _Source )
{
#ifdef  UNICODE
	return wcscat( _Dest, _Source );
#else
	return strcat( _Dest, _Source );
#endif // #ifdef  UNICODE
}


inline FILE* ks_fopen( const KsChar* filename, const KsChar* mode )
{
#ifdef  UNICODE
	return _wfopen( filename, mode );
#else
	return fopen( filename, mode );
#endif // #ifdef  UNICODE
}

inline KsChar* ks_fgets( KsChar* str, KsInt32 n, FILE* stream )
{
#ifdef  UNICODE
	return fgetws( str, n, stream );
#else
	return fgets( str, n, stream );
#endif // #ifdef  UNICODE
}

#ifdef  UNICODE

#define sprintf

#else

#define sprintf

#endif// #ifdef  UNICODE

//inline KsInt32 fprintf( FILE *stream, const char *format, ... )

inline void ks_vsprintf( KsChar* buffer, KsInt32 count, const KsChar* format, va_list argptr )
{
#ifdef  UNICODE
	vswprintf( buffer, count, format, argptr );
#else
	vsprintf( buffer, format, argptr );
#endif // #ifdef  UNICODE
}

inline void ks_splitpath( const KsChar* path, KsChar* drive, KsChar* dir, KsChar* fname, KsChar* ext )
{
#ifdef  UNICODE
	_wsplitpath( path, drive, dir, fname, ext );
#else
	_splitpath( path, drive, dir, fname, ext );
#endif // #ifdef  UNICODE
}

#endif /* __KSMACRO_H__ */


