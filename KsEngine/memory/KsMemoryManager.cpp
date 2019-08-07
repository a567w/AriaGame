/************************************************************************************************/
/**
 * @file	KsMemoryManager.cpp
 * @brief	メモリー管理
 * @author	Tsukasa Kato
 * @date	2004/03/30
 * @version	1.0.0
 */
/************************************************************************************************/

/*===============================================================================================*/
/*                                 << インクルード >>                                            */
/*===============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"
#include "KsEngine/memory/KsMemoryManager.h"

/*===============================================================================================*/
/*                                     << 定義 >>                                                */
/*===============================================================================================*/
// 定義されていたら、されていないようにする
#ifdef new
	#undef new
#endif

#ifdef delete
	#undef delete
#endif

#ifdef malloc
	#undef malloc
#endif

#ifdef calloc
	#undef calloc
#endif

#ifdef realloc
	#undef realloc
#endif

#ifdef free
	#undef free
#endif

/*===============================================================================================*/
/*                                     << 宣言 >>                                                */
/*===============================================================================================*/
KsMemoryUnit*		KsMemoryManager::m_pHashTable[ ksMEMORY_HASH_SIZE ];
KsUInt32			KsMemoryManager::m_currentAllocCount   = 0;
KsUInt32			KsMemoryManager::m_breakOnAllocCount   = 0;
KsUInt32			KsMemoryManager::m_sourceLine          = 0;
KsChar*				KsMemoryManager::m_sourceFile          = 0;
KsChar*				KsMemoryManager::m_funcName            = 0;
KsMemoryUnit*		KsMemoryManager::m_pReservoir          = 0;
KsMemoryUnit**		KsMemoryManager::m_ppReservoirBuffer   = 0;
KsUInt32			KsMemoryManager::m_reservoirBufferSize = 0;
KsInt32				KsMemoryManager::m_tagCount            = 0;
KsInt32				KsMemoryManager::m_zeroAlloc           = 0;
KsMemoryState		KsMemoryManager::m_state;
KsCriticalSection	KsMemoryManager::m_cs;
KsChar				KsMemoryManager::m_tagNameStack[ ksMEMORY_TAG_STACK_SIZE ][ ksMEMORY_NAME_SIZE ];
KsChar				KsMemoryManager::m_nowTagName[ ksMEMORY_NAME_SIZE ];

/************************************************************************************************/
/*
 * パスとファイル名を分割する
 */
/************************************************************************************************/
static void KsSplitFileName( KsChar* pOutFileName, const KsChar* pPath )
{
	KsChar	drive[ _MAX_DRIVE ];
	KsChar	dir[ _MAX_DIR ];
	KsChar	fname[ _MAX_FNAME ];
	KsChar	ext[ _MAX_EXT ];

	ks_splitpath( pPath, drive, dir, fname, ext );

	ks_strcat( fname, ext );

	ks_strncpy( pOutFileName, fname, ksMEMORY_NAME_SIZE );

	pOutFileName[ (ksMEMORY_NAME_SIZE-1) ] = '\0';

}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void* KsMemoryManager::KsMalloc( KsSize size, KsUInt32 line, const KsChar* pszFile, const KsChar* pszFunc )
{
	void *pMemory = KsMemoryManager::allocator( size, ksALLOC_TYPE_MALLOC, line, pszFile, pszFunc );

	KsAssert( pMemory, "メモリーを確保できません" );

	return pMemory;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void* KsMemoryManager::KsCalloc( KsSize size, KsUInt32 line, const KsChar* pszFile, const KsChar* pszFunc )
{
	void *pMemory = KsMemoryManager::allocator( size, ksALLOC_TYPE_CALLOC, line, pszFile, pszFunc );

	KsAssert( pMemory, "メモリーを確保できません" );

	return pMemory;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void* KsMemoryManager::KsRealloc( void* pAddress, KsSize size, KsUInt32 line, const KsChar* pszFile, const KsChar* pszFunc )
{
	void *pMemory = KsMemoryManager::allocator( size, ksALLOC_TYPE_REALLOC, line, pszFile, pszFunc );

	KsAssert( pMemory, "メモリーを確保できません" );

	// メモリーをコピーする
	KsMemoryUnit*		pUnit = KsMemoryManager::findAllocUnit( pAddress );

	KsAssert( pUnit, "メモリーをユニットが見つかりません" );

	memcpy( pMemory, pAddress, pUnit->m_requestSize );

	// 開放
	KsMemoryManager::KsFree( pAddress );

	return pMemory;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsMemoryManager::KsFree( void* pAddress )
{
	KsMemoryManager::deallocator( pAddress, ksALLOC_TYPE_FREE );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsMemoryManager::SetCallFile( KsUInt32 line, const KsChar* pszFile, const KsChar* pszFunc )
{
	m_sourceLine = line;
	m_sourceFile = const_cast< KsChar* >( pszFile );
	m_funcName   = const_cast< KsChar* >( pszFunc );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsMemoryUnit* KsMemoryManager::findAllocUnit( const void* pAddress )
{
	KsUInt32		hashIndex = ( reinterpret_cast<KsUInt32>( const_cast<void*>( pAddress ) ) >> 4 ) & ( ksMEMORY_HASH_SIZE - 1 );
	KsMemoryUnit*	pUnit = m_pHashTable[ hashIndex ];	// 登録されているハッシュテーブルを取得

	// 指定メモリーを取得する
	while( pUnit )
	{
		// 確保されているメモリーかをチェックする
		if( pUnit->m_pRequestAddress == pAddress )
		{
			return pUnit;
		}
		pUnit = pUnit->m_pNext;
	}

	return NULL;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void* KsMemoryManager::allocator( KsSize size, KsUInt32 type, KsUInt32 line, const KsChar* pszFile, const KsChar* pszFunc )
{
	if( 0 == size )
	{
		return (void*)&m_zeroAlloc;
	}

	try
	{
		m_cs.lock();

		// 0バイト指定だったら1バイトに変更する
		if( size == 0 )
		{
			size = 1;
		}

		// 確保カウントをアップ
		++m_currentAllocCount;

		// メモリー確保情報管理のリストがたりなくなったら、新たに確保しなおす
		if( !m_pReservoir )
		{
			// 確保
			m_pReservoir = (KsMemoryUnit*)malloc( sizeof( KsMemoryUnit ) * ksMEMORY_UNIT_ALLOC_SIZE );
		
			// 例外発生
			if( !m_pReservoir ) { throw "m_pReservoir not alloc !! "; }

			// ゼロクリアー
			memset( m_pReservoir, 0, (sizeof( KsMemoryUnit ) * ksMEMORY_UNIT_ALLOC_SIZE) );
	
			// リストをセットする
			for( KsUInt32 i = 0; i < ksMEMORY_UNIT_ALLOC_SIZE - 1; ++i ){
				m_pReservoir[ i ].m_pNext = &m_pReservoir[ i + 1 ];
			}

			// 新たに確保しなおす
			KsMemoryUnit**	ppTemp = (KsMemoryUnit**)realloc( m_ppReservoirBuffer, ( (m_reservoirBufferSize + 1) * sizeof(KsMemoryUnit*) ) );
		
			// 例外発生
			if( !ppTemp ) { throw "ppTemp not alloc !! "; }
		
			// メモリーを確保できたかのチェック
			if( ppTemp ){
				m_ppReservoirBuffer = ppTemp;
				m_ppReservoirBuffer[ m_reservoirBufferSize++ ] = m_pReservoir;
			}
		}

		KsMemoryUnit*	pUnit = m_pReservoir;
		m_pReservoir = pUnit->m_pNext;

		// ゼロクリアー
		memset( pUnit, 0, sizeof(KsMemoryUnit) );

		pUnit->m_actualSize		 = ( size + ksPADDING_SIZE * 2 );		// 実サイズ
		pUnit->m_pActualAddress	 = malloc( pUnit->m_actualSize );		// 実アドレス
		pUnit->m_requestSize	 = size;								// 要求サイズ
		pUnit->m_pRequestAddress = computeRequestAddress( pUnit->m_pActualAddress );
		pUnit->m_allocType		 = type;
		pUnit->m_sourceLine		 = line;
		pUnit->m_allocNumber	 = m_currentAllocCount;

		// ファイル名をセットする
		if( pszFile )	{ KsSplitFileName( pUnit->m_sourceFile, pszFile );	}
		else			{ ks_strcpy( pUnit->m_sourceFile, _T("??") );		}

		/* タグ名をセットする */
		ks_strncpy( pUnit->m_userTag, m_nowTagName, ksMEMORY_NAME_SIZE-1 );
		pUnit->m_userTag[ ksMEMORY_NAME_SIZE -1 ] = '\0';

		// 例外発生
		if( !pUnit->m_pActualAddress ) { throw "pUnit->m_pActualAddress null pointer !! "; }
	
		if( type == ksALLOC_TYPE_UNKNOWN ) { throw "Unknown type !! "; }

		// ハッシュテーブル
		KsUInt32	hashIndex = ( reinterpret_cast<KsUInt32>( pUnit->m_pRequestAddress ) >> 4 ) & ( ksMEMORY_HASH_SIZE - 1 );

		if( m_pHashTable[ hashIndex ] ) { m_pHashTable[ hashIndex ]->m_pPrev = pUnit; }

		pUnit->m_pNext = m_pHashTable[ hashIndex ];
		pUnit->m_pPrev = NULL;

		m_pHashTable[ hashIndex ] = pUnit;

		m_state.m_totalRequestMemory += static_cast<KsUInt32>( pUnit->m_requestSize );
		m_state.m_totalActualMemory  += static_cast<KsUInt32>( pUnit->m_actualSize );
		m_state.m_totalAllocUnitCount++;

		if( m_state.m_totalRequestMemory > m_state.m_peakRequestMemory ){
			m_state.m_peakRequestMemory  = m_state.m_totalRequestMemory;
		}
		if( m_state.m_totalActualMemory > m_state.m_peakActualMemory ){
			m_state.m_peakActualMemory  = m_state.m_totalActualMemory;
		}
		if( m_state.m_totalAllocUnitCount > m_state.m_peakAllocUnitCount ){
			m_state.m_peakAllocUnitCount  = m_state.m_totalAllocUnitCount;
		}

		m_state.m_accumulatedRequestMemory += static_cast<KsUInt32>( pUnit->m_requestSize );
		m_state.m_accumulatedActualMemory  += static_cast<KsUInt32>( pUnit->m_actualSize );
		m_state.m_accumulatedAllocUnitCount++;

		// calloc だったら0クリアーする
		if( type == ksALLOC_TYPE_CALLOC ){
			memset( pUnit->m_pRequestAddress, 0, pUnit->m_requestSize );
		}

		// (エラー破損チェック)
		//if( g_bAlwaysValidateAll ){
		//	ValidateAllAllocUnits();
		//}

		reset();

		m_cs.unlock();

		return pUnit->m_pRequestAddress;
	}
	catch( const char *pszError )
	{
		// 例外処理
		reset();
		printf( pszError );

		m_cs.unlock();

		return 0;
	}
}

/*************************************************************	***********************************/
// メモリーを解放する
/************************************************************************************************/
void KsMemoryManager::deallocator( void* pAddress, KsUInt32 type )
{
	if( NULL == pAddress || pAddress == (void*)&m_zeroAlloc )
	{
		return;
	}

	m_cs.lock();

	try
	{
		KsMemoryUnit*	pUnit = findAllocUnit( pAddress );

		if( !pUnit )
		{
			throw "Not find allocUnit";
		}

		// このどれかのメモリーの確保と開放のタイプがあっていないとだめ
		if( !(	( type == ksALLOC_TYPE_DELETE       && pUnit->m_allocType == ksALLOC_TYPE_NEW       ) ||
				( type == ksALLOC_TYPE_DELETE_ARRAY && pUnit->m_allocType == ksALLOC_TYPE_NEW_ARRAY ) ||
				( type == ksALLOC_TYPE_FREE         && pUnit->m_allocType == ksALLOC_TYPE_MALLOC    ) ||
				( type == ksALLOC_TYPE_FREE         && pUnit->m_allocType == ksALLOC_TYPE_CALLOC    ) ||
				( type == ksALLOC_TYPE_FREE         && pUnit->m_allocType == ksALLOC_TYPE_REALLOC   ) ||
				( type == ksALLOC_TYPE_UNKNOWN ) ) )
		{
			throw "メモリーの確保と開放の対応がおかしいです｡";
		}

		free( pUnit->m_pActualAddress );

		// ハッシュテーブルから取り除く
		KsUInt32 hashIndex = ( reinterpret_cast<KsUInt32>( pUnit->m_pRequestAddress ) >> 4 ) & ( ksMEMORY_HASH_SIZE - 1 );
	
		if( m_pHashTable[ hashIndex ] == pUnit )
		{
			m_pHashTable[ hashIndex ] = pUnit->m_pNext;
		}
		else
		{
			if( pUnit->m_pPrev ) { pUnit->m_pPrev->m_pNext = pUnit->m_pNext; }
			if( pUnit->m_pNext ) { pUnit->m_pNext->m_pPrev = pUnit->m_pPrev; }
		}

		m_state.m_totalRequestMemory -= static_cast<KsUInt32>( pUnit->m_requestSize );
		m_state.m_totalActualMemory  -= static_cast<KsUInt32>( pUnit->m_actualSize );
		m_state.m_totalAllocUnitCount--;

		// クリアー
		memset( pUnit, 0, sizeof( KsMemoryUnit ) );
		pUnit->m_pNext = m_pReservoir;
		m_pReservoir   = pUnit;

		reset();
	}
	catch( const KsChar *pszError )
	{
		KsError( pszError );
		reset();
	}

	m_cs.unlock();
}

/************************************************************************************************/
/*
 * リセットする
 */
/************************************************************************************************/
void KsMemoryManager::reset()
{
	m_sourceLine = 0;
	m_sourceFile = 0;
	m_sourceFile = 0;
}

/************************************************************************************************/
/*
 * 実アドレスから要求されたアドレスを求める
 * @param		pActualAddress	
 * @return							要求されたアドレス
 */
/************************************************************************************************/
void *KsMemoryManager::computeRequestAddress( const void *pActualAddress )
{
	if( !pActualAddress ){
		return 0;
	}

	return reinterpret_cast<void *>( const_cast<char *>( reinterpret_cast<const char *>( pActualAddress ) + ksPADDING_SIZE ) );
}
/************************************************************************************************/
/*
 * メモリーの確保状況をダンプする
 */
/************************************************************************************************/
void KsMemoryManager::dump()
{
	static KsChar*		allocType[] = {
										_T("     new"),
										_T("   new[]"),
										_T("  malloc"),
										_T("  calloc"),
										_T(" realloc"),
										_T("  delete"),
										_T("delete[]"),
										_T("    free"),
										_T("  unknow"),
									};

	FILE*	fp;

	fp = fopen( ksMEMORY_DUMP_FILE_NAME, "w+t" );

	if( !fp ) { return; }

	time_t  t   = time( 0 );
	tm*		tme = localtime( &t );

	// 確保した番号順にソートしてからダンプする
	fprintf( fp, " --------------------------------------------------------------------------------- \n" );
	fprintf( fp, "|            Memory report for: %02d/%02d/%04d %02d:%02d:%02d           |\n", tme->tm_mon + 1, tme->tm_mday, tme->tm_year + 1900, tme->tm_hour, tme->tm_min, tme->tm_sec);
	fprintf( fp, " --------------------------------------------------------------------------------- \n" );
	fprintf( fp, "\n" );
	fprintf( fp, "確保番号 確保タイプ ソースファイル 行数 確保サイズ 確保アドレス\n" );

	for( KsUInt32 i=0; i<ksMEMORY_HASH_SIZE; ++i )
	{

		KsMemoryUnit	*pUnit = m_pHashTable[ i ];

		while( pUnit )
		{
			fprintf( fp, "%08d %s, %s %06d, %08d %0x\n", pUnit->m_allocNumber, allocType[ pUnit->m_allocType ], pUnit->m_sourceFile, pUnit->m_sourceLine, pUnit->m_requestSize, (KsUInt32)(pUnit->m_pRequestAddress) ); 
			pUnit = pUnit->m_pNext;
		}
	}

	fclose( fp );
}

/************************************************************************************************/
/**
 * タグ名をスタックにPushしてセットする
 * @param		pTagName			タグ名
 */
/************************************************************************************************/
void KsMemoryManager::pushTag( const KsChar* pTagName )
{
	if( pTagName )
	{
		ks_strncpy( m_nowTagName, pTagName, ksMEMORY_NAME_SIZE-1 );
		m_nowTagName[ ksMEMORY_NAME_SIZE-1 ] = '\0';
	}
	else
	{
		m_nowTagName[ 0 ] = '\0';
	}

	if( m_tagCount < ksMEMORY_TAG_STACK_SIZE )
	{
		ks_strcpy( &m_tagNameStack[ m_tagCount ][ 0 ], m_nowTagName );
		++m_tagCount;
		ks_strcpy( m_nowTagName, _T("none") );
	}
	else
	{
		printf("not enough memtag stack !!\n");
	}
}

/************************************************************************************************/
/*
 * タグ名をPopする
 */
/************************************************************************************************/
void KsMemoryManager::popTag()
{
	if( m_tagCount > 0 )
	{
		m_tagCount--;
		ks_strcpy( m_nowTagName, m_tagNameStack[ m_tagCount ] );
	}
}


