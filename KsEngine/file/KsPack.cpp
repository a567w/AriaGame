/************************************************************************************************/
/** 
 * @file		KsPack.cpp
 * @brief		パック
 * @author		Tsukasa Kato
 * @date		2004/11/24
 * @since		2004/11/24
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

#if 0
/************************************************************************************************/
/* 
 *
 */
/************************************************************************************************/
KsPack::KsPack()
{
	m_fd        = -1;
	m_topSector = 0;
	m_path[ 0 ] = '\0';
	m_pInfoList = NULL;
}

/************************************************************************************************/
/* 
 *
 */
/************************************************************************************************/
KsPack::~KsPack()
{
	destroy();
}

/************************************************************************************************/
/* 
 * 情報リストを生成
 */
/************************************************************************************************/
KsBool KsPack::create( const KsChar* pPackName )
{
	/* HOSTから読み込む */
	sprintf( m_path, "host0:DATA/%s", pPackName );

	m_fd = StIoOpen( m_path, SCE_O_RDONLY, 0644 );

	/* 読み込み */
	StIoRead( m_fd, &m_header, sizeof( KsPackHeader ) );

	m_pInfoList = new KsPackInfo2[ m_header.numFiles ];

	/* 情報部を読み込む */
	StIoRead( m_fd, m_pInfoList, m_header.numFiles * sizeof( KsPackInfo2 ) );

#if 0
	StPrintf( "numFiles %d\n", m_header.numFiles );
	StPrintf( "alignment %d\n", m_header.alignment );

	for( KsUInt32 i=0; i<m_header.numFiles; i++ ){
		StPrintf("--------------------------------------------------\n");
		StPrintf( "nameLen  %d \n", m_pInfoList[ i ].nameLength );
		StPrintf( "nameCRC1 %x \n", m_pInfoList[ i ].nameCRC1 );
		StPrintf( "nameCRC2 %x \n", m_pInfoList[ i ].nameCRC2 );
		StPrintf( "offset   %d \n", m_pInfoList[ i ].offset );
		StPrintf( "flag     %d \n", m_pInfoList[ i ].flags );
		StPrintf( "realSize %d \n", m_pInfoList[ i ].realSize );
		StPrintf( "compSize %d \n", m_pInfoList[ i ].compressedSize );

	}
#endif

	StIoClose( m_fd );
	m_fd = -1;

	return stTRUE;
}

/************************************************************************************************/
/* 
 * 情報リストを生成
 */
/************************************************************************************************/
void KsPack::destroy()
{
	if( m_fd >= 0 ){
		sceIoClose( m_fd );
		m_fd = -1;
	}
	stDELETEARRAY( m_pInfoList );
}

/************************************************************************************************/
/*
 * ファイルを開くする
 */
/************************************************************************************************/
KsBool KsPack::open()
{
	close();

	/* 無限リトライ */
	m_fd = StIoOpen( m_path );

	return stTRUE;
}

/************************************************************************************************/
/*
 * 閉じる
 */
/************************************************************************************************/
void KsPack::close()
{
	if( m_fd >= 0 ){
		sceIoClose( m_fd );
		m_fd = -1;
	}
}

/************************************************************************************************/
/* 
 *
 */
/************************************************************************************************/
KsPackInfo2* KsPack::find( const KsChar* pFileName )
{
	/* キー */
	KsUInt32	key = KsCrc32( (StUInt8*)pFileName );

	/* ２分探索で指定キーのデータ情報を検索する */
	KsInt32		index = binarySearch( key );

	if( index < 0 ){
		/* ファイルが見つからない */
		return NULL;
	}

	return &m_pInfoList[ index ];

/*
	CRC1だけではダメな場合は、ファイル名の長さやCRC2までチェックするようにする
*/
	/*
	if( m_pInfoList[ index ].nameCRC2 != key2 ){
		if( m_pInfoList[ index ].nameCRC2 < key2 ){
			// 上を調べる
			for( KsInt32 i=index+1; i<m_header.numFiles; i++ ){
				if( m_pInfoList[ i ].nameCRC1 != key ){
					break;
				}
				if( m_pInfoList[ i ].nameCRC2 == key2 ){
					//if( m_pInfoList[ index ].nameLength == length ){
					//}
					findFlag = stTRUE;
					break;
				}
			}
		}
		else{
			// 下を調べる
			for( KsInt32 i=index-1; i>0; i-- ){
				if( m_pInfoList[ i ].nameCRC1 != key ){
					break;
				}
				if( m_pInfoList[ i ].nameCRC2 == key2 ){
					findFlag = stTRUE;
					break;
				}
			}
		}
	}*/
}


/************************************************************************************************/
/* 
 *
 */
/************************************************************************************************/
KsInt32 KsPack::binarySearch( KsUInt32 key )
{
	KsInt32		left, right, center;
	
	left  = 0;
	right = m_header.numFiles - 1;
	
	while( left <= right )
	{
		center = ( left + right ) / 2;
		
		if( m_pInfoList[ center ].nameCRC1 > key ){
			right = center - 1;
		}
		else if( m_pInfoList[ center ].nameCRC1 < key ){
			left = center + 1;
		}
		else{
			return center;
		}
	}

	return -1;
}
#endif
