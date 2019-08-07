/************************************************************************************************/
/**
 * @file	KsMemoryManager.cpp
 * @brief	�������[�Ǘ�
 * @author	tsukasa kato
 * @date	2004/03/30
 * @version	1.0.0
 */
/************************************************************************************************/

/*===============================================================================================*/
/*                                 << �C���N���[�h >>                                             */
/*===============================================================================================*/
#include "KsMemoryManager.h"
#include "KsLog.h"

/*===============================================================================================*/
/*                                     << ��` >>                                                */
/*===============================================================================================*/
// ��`����Ă�����A����Ă��Ȃ��悤�ɂ���
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
/*                                     << �錾 >>                                                */
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
KsMemoryStats		KsMemoryManager::m_stats;

//===============================================================================================//
// �p�X�ƃt�@�C�����𕪊�����
//===============================================================================================//
static void KsSplitFileName( KsChar* pOutFileName, const KsChar* pPath )
{
	KsChar	drive[ _MAX_DRIVE ];
	KsChar	dir[ _MAX_DIR ];
	KsChar	fname[ _MAX_FNAME ];
	KsChar	ext[ _MAX_EXT ];

	_splitpath( pPath, drive, dir, fname, ext );

	strcat( fname, ext );

	strncpy( pOutFileName, fname, ksMEMORY_NAME_SIZE );

	pOutFileName[ (ksMEMORY_NAME_SIZE-1) ] = '\0';

}

//===============================================================================================//
// new ���Z�q�I�[�o�[���[�h
//===============================================================================================//
void*	operator new ( size_t size )
{
	void*		pMemory;
	KsChar*		pszFile = KsMemoryManager::m_sourceFile;
	KsChar*		pszFunc = KsMemoryManager::m_funcName;
	KsUInt32	line	= KsMemoryManager::m_sourceLine;

	pMemory = KsMemoryManager::Allocator( size, ksALLOC_TYPE_NEW, line, pszFile, pszFunc );

//	KsAssert( pMemory, "�������[���m�ۂł��܂���" );

	return pMemory;
}

//===============================================================================================//
// new[] ���Z�q�I�[�o�[���[�h
//===============================================================================================//
void*	operator new[] ( size_t size )
{
	void*		pMemory;
	KsChar*		pszFile = KsMemoryManager::m_sourceFile;
	KsChar*		pszFunc = KsMemoryManager::m_funcName;
	KsUInt32	line	= KsMemoryManager::m_sourceLine;

	pMemory = KsMemoryManager::Allocator( size, ksALLOC_TYPE_NEW_ARRAY, line, pszFile, pszFunc );

//	KsAssert( pMemory, "�������[���m�ۂł��܂���" );

	return pMemory;
}

//===============================================================================================//
// delete ���Z�q�I�[�o�[���[�h
//===============================================================================================//
void	operator delete ( void* pAddress )
{
	KsMemoryManager::Deallocator( pAddress, ksALLOC_TYPE_DELETE );
}

//===============================================================================================//
// delete[] ���Z�q�I�[�o�[���[�h
//===============================================================================================//
void	operator delete[] ( void* pAddress )
{
	KsMemoryManager::Deallocator( pAddress, ksALLOC_TYPE_DELETE_ARRAY );
}

//===============================================================================================//
// malloc �m��
//===============================================================================================//
void* KsMemoryManager::KsMalloc( size_t size, KsUInt32 line, const KsChar* pszFile, const KsChar* pszFunc )
{
	void *pMemory = KsMemoryManager::Allocator( size, ksALLOC_TYPE_MALLOC, line, pszFile, pszFunc );

//	KsAssert( pMemory, "�������[���m�ۂł��܂���" );

	return pMemory;
}
//===============================================================================================//
// calloc �m��
//===============================================================================================//
void* KsMemoryManager::KsCalloc( size_t size, KsUInt32 line, const KsChar* pszFile, const KsChar* pszFunc )
{
	void *pMemory = KsMemoryManager::Allocator( size, ksALLOC_TYPE_CALLOC, line, pszFile, pszFunc );
	
//	KsAssert( pMemory, "�������[���m�ۂł��܂���" );

	return pMemory;
}
//===============================================================================================//
// realloc �m��
//===============================================================================================//
void* KsMemoryManager::KsRealloc( void* pAddress, size_t size, KsUInt32 line, const KsChar* pszFile, const KsChar* pszFunc )
{
	void *pMemory = KsMemoryManager::Allocator( size, ksALLOC_TYPE_REALLOC, line, pszFile, pszFunc );
	
//	KsAssert( pMemory, "�������[���m�ۂł��܂���" );
	
	// �������[���R�s�[����
	KsMemoryUnit*		pUnit = KsMemoryManager::FindAllocUnit( pAddress );
	
//	KsAssert( pUnit, "�������[�����j�b�g��������܂���" );
	
	memcpy( pMemory, pAddress, pUnit->m_requestSize );
	
	// �J��
	KsMemoryManager::KsFree( pAddress );

	return pMemory;
}

//===============================================================================================//
// free �������[�J��
//===============================================================================================//
void KsMemoryManager::KsFree( void* pAddress )
{
	KsMemoryManager::Deallocator( pAddress, ksALLOC_TYPE_FREE );
}
//===============================================================================================//
// �ǂ̃t�@�C������Ă΂ꂽ�����L�^����
//===============================================================================================//
void KsMemoryManager::SetCallFile( KsUInt32 line, const KsChar* pszFile, const KsChar* pszFunc )
{
	m_sourceLine = line;
	m_sourceFile = const_cast< KsChar* >( pszFile );
	m_funcName   = const_cast< KsChar* >( pszFunc );
}

//===============================================================================================//
//
//===============================================================================================//
KsMemoryUnit* KsMemoryManager::FindAllocUnit( const void* pAddress )
{
	KsUInt32		hashIndex = ( reinterpret_cast<KsUInt32>( const_cast<void*>( pAddress ) ) >> 4 ) & ( ksMEMORY_HASH_SIZE - 1 );
	KsMemoryUnit*	pUnit = m_pHashTable[ hashIndex ];	// �o�^����Ă���n�b�V���e�[�u�����擾
	
	// �w�胁�����[���擾����
	while( pUnit )
	{
		// �m�ۂ���Ă��郁�����[�����`�F�b�N����
		if( pUnit->m_pRequestAddress == pAddress ){
			return pUnit;
		}
		pUnit = pUnit->m_pNext;
	}

	return NULL;
}


//===============================================================================================//
// �������[�m�ۊ֐�
//===============================================================================================//
void* KsMemoryManager::Allocator( size_t size, KsUInt32 type, KsUInt32 line, const KsChar* pszFile, const KsChar* pszFunc )
{
	try{
		// 0�o�C�g�w�肾������1�o�C�g�ɕύX����
		if( size == 0 ){
			size = 1;
		}

		// �m�ۃJ�E���g���A�b�v
		++m_currentAllocCount;

		// �������[�m�ۏ��Ǘ��̃��X�g������Ȃ��Ȃ�����A�V���Ɋm�ۂ��Ȃ���
		if( !m_pReservoir ){
			// �m��
			m_pReservoir = (KsMemoryUnit*)malloc( sizeof( KsMemoryUnit ) * ksMEMORY_UNIT_ALLOC_SIZE );
			
			// ��O����
			if( !m_pReservoir ) { throw "m_pReservoir not alloc !! "; }

			// �[���N���A�[
			memset( m_pReservoir, 0, (sizeof( KsMemoryUnit ) * ksMEMORY_UNIT_ALLOC_SIZE) );
		
			// ���X�g���Z�b�g����
			for( KsUInt32 i = 0; i < ksMEMORY_UNIT_ALLOC_SIZE - 1; ++i ){
				m_pReservoir[ i ].m_pNext = &m_pReservoir[ i + 1 ];
			}

			// �V���Ɋm�ۂ��Ȃ���
			KsMemoryUnit**	ppTemp = (KsMemoryUnit**)realloc( m_ppReservoirBuffer, ( (m_reservoirBufferSize + 1) * sizeof(KsMemoryUnit*) ) );
			
			// ��O����
			if( !ppTemp ) { throw "ppTemp not alloc !! "; }
			
			// �������[���m�ۂł������̃`�F�b�N
			if( ppTemp ){
				m_ppReservoirBuffer = ppTemp;
				m_ppReservoirBuffer[ m_reservoirBufferSize++ ] = m_pReservoir;
			}
		}

		KsMemoryUnit*	pUnit = m_pReservoir;
		m_pReservoir = pUnit->m_pNext;

		// �[���N���A�[
		memset( pUnit, 0, sizeof(KsMemoryUnit) );

		pUnit->m_actualSize		 = ( size + ksPADDING_SIZE * 2 );		// ���T�C�Y
		pUnit->m_pActualAddress	 = malloc( pUnit->m_actualSize );		// ���A�h���X
		pUnit->m_requestSize	 = size;								// �v���T�C�Y
		pUnit->m_pRequestAddress = ComputeRequestAddress( pUnit->m_pActualAddress);
		pUnit->m_allocType		 = type;
		pUnit->m_sourceLine		 = line;
		pUnit->m_allocNumber	 = m_currentAllocCount;

		// �t�@�C�������Z�b�g����
		if( pszFile )	{ KsSplitFileName( pUnit->m_sourceFile, pszFile );	}
		else			{ strcpy( pUnit->m_sourceFile, "??" );			}
	
		// ��O����
		if( !pUnit->m_pActualAddress ) { throw "pUnit->m_pActualAddress null pointer !! "; }
		
		if( type == ksALLOC_TYPE_UNKNOWN ) { throw "Unknown type !! "; }

		// �n�b�V���e�[�u��
		KsUInt32	hashIndex = ( reinterpret_cast<KsUInt32>( pUnit->m_pRequestAddress ) >> 4 ) & ( ksMEMORY_HASH_SIZE - 1 );

		if( m_pHashTable[ hashIndex ] ) { m_pHashTable[ hashIndex ]->m_pPrev = pUnit; }

		pUnit->m_pNext = m_pHashTable[ hashIndex ];
		pUnit->m_pPrev = NULL;

		m_pHashTable[ hashIndex ] = pUnit;

		m_stats.m_totalRequestMemory += static_cast<KsUInt32>( pUnit->m_requestSize );
		m_stats.m_totalActualMemory  += static_cast<KsUInt32>( pUnit->m_actualSize );
		m_stats.m_totalAllocUnitCount++;

		if( m_stats.m_totalRequestMemory > m_stats.m_peakRequestMemory ){
			m_stats.m_peakRequestMemory  = m_stats.m_totalRequestMemory;
		}
		if( m_stats.m_totalActualMemory > m_stats.m_peakActualMemory ){
			m_stats.m_peakActualMemory  = m_stats.m_totalActualMemory;
		}
		if( m_stats.m_totalAllocUnitCount > m_stats.m_peakAllocUnitCount ){
			m_stats.m_peakAllocUnitCount  = m_stats.m_totalAllocUnitCount;
		}

		m_stats.m_accumulatedRequestMemory += static_cast<KsUInt32>( pUnit->m_requestSize );
		m_stats.m_accumulatedActualMemory  += static_cast<KsUInt32>( pUnit->m_actualSize );
		m_stats.m_accumulatedAllocUnitCount++;

		// calloc ��������0�N���A�[����
		if( type == ksALLOC_TYPE_CALLOC ){
			memset( pUnit->m_pRequestAddress, 0, pUnit->m_requestSize );
		}

		// (�G���[�j���`�F�b�N)
		//if( g_bAlwaysValidateAll ){
		//	ValidateAllAllocUnits();
		//}

		Reset();

		return pUnit->m_pRequestAddress;
	}
	catch( const char *pszError ){
		// ��O����
		Reset();
		printf( pszError );
		return 0;
	}
}

//===============================================================================================//
// �������[���������
//===============================================================================================//
void KsMemoryManager::Deallocator( void* pAddress, KsUInt32 type )
{
	try{
		KsMemoryUnit*	pUnit = FindAllocUnit( pAddress );

		// ���̂ǂꂩ�̃������[�̊m�ۂƊJ���̃^�C�v�������Ă��Ȃ��Ƃ���
		if( !(	( type == ksALLOC_TYPE_DELETE       && pUnit->m_allocType == ksALLOC_TYPE_NEW       ) ||
				( type == ksALLOC_TYPE_DELETE_ARRAY && pUnit->m_allocType == ksALLOC_TYPE_NEW_ARRAY ) ||
				( type == ksALLOC_TYPE_FREE         && pUnit->m_allocType == ksALLOC_TYPE_MALLOC    ) ||
				( type == ksALLOC_TYPE_FREE         && pUnit->m_allocType == ksALLOC_TYPE_CALLOC    ) ||
				( type == ksALLOC_TYPE_FREE         && pUnit->m_allocType == ksALLOC_TYPE_REALLOC   ) ||
				( type == ksALLOC_TYPE_UNKNOWN ) ) )
		{
			throw "�������[�̊m�ۂƊJ���̑Ή������������ł��";
		}

		free( pUnit->m_pActualAddress );

		// �n�b�V���e�[�u�������菜��
		KsUInt32 hashIndex = ( reinterpret_cast<KsUInt32>( pUnit->m_pRequestAddress ) >> 4 ) & ( ksMEMORY_HASH_SIZE - 1 );
		
		if( m_pHashTable[ hashIndex ] == pUnit ){
			m_pHashTable[ hashIndex ] = pUnit->m_pNext;
		}
		else{
			if( pUnit->m_pPrev ) { pUnit->m_pPrev->m_pNext = pUnit->m_pNext; }
			if( pUnit->m_pNext ) { pUnit->m_pNext->m_pPrev = pUnit->m_pPrev; }
		}

		m_stats.m_totalRequestMemory -= static_cast<KsUInt32>( pUnit->m_requestSize );
		m_stats.m_totalActualMemory  -= static_cast<KsUInt32>( pUnit->m_actualSize );
		m_stats.m_totalAllocUnitCount--;

		// �N���A�[
		memset( pUnit, 0, sizeof( KsMemoryUnit ) );
		pUnit->m_pNext = m_pReservoir;
		m_pReservoir   = pUnit;

		Reset();
	}
	catch( const char *pszError ){
		KsAssert( ksFALSE, pszError );
		Reset();
	}
}

//===============================================================================================//
// ���Z�b�g
//===============================================================================================//
void KsMemoryManager::Reset()
{
	m_sourceLine = 0;
	m_sourceFile = 0;
	m_sourceFile = 0;
}
//===============================================================================================//
// ���A�h���X����v�����ꂽ�A�h���X�ɂ���
//===============================================================================================//
void *KsMemoryManager::ComputeRequestAddress( const void *pActualAddress )
{
	if( !pActualAddress ){
		return 0;
	}

	return reinterpret_cast<void *>( const_cast<char *>( reinterpret_cast<const char *>( pActualAddress ) + ksPADDING_SIZE ) );
}
//===============================================================================================//
// �������[�̊m�ۏ󋵂��_���v����
//===============================================================================================//
void KsMemoryManager::Dump()
{
	static KsChar*		allocType[] = { "     new",
										"   new[]",
										"  malloc",
										"  calloc",
										" realloc",
										"  delete",
										"delete[]",
										"    free",
										"  unknow",
									};

	FILE*	fp;
	
	fp = fopen( ksMEMORY_DUMP_FILE_NAME, "w+t" );

	if( !fp ) { return; }

	time_t  t   = time( 0 );
	tm*		tme = localtime( &t );

	// �m�ۂ����ԍ����Ƀ\�[�g���Ă���_���v����
	fprintf( fp, " --------------------------------------------------------------------------------- \n" );
	fprintf( fp, "|            Memory report for: %02d/%02d/%04d %02d:%02d:%02d           |\n", tme->tm_mon + 1, tme->tm_mday, tme->tm_year + 1900, tme->tm_hour, tme->tm_min, tme->tm_sec);
	fprintf( fp, " --------------------------------------------------------------------------------- \n" );
	fprintf( fp, "\n" );
	fprintf( fp, "�m�۔ԍ� �m�ۃ^�C�v �\�[�X�t�@�C�� �s�� �m�ۃT�C�Y �m�ۃA�h���X\n" );

	for( KsUInt32 i=0; i<ksMEMORY_HASH_SIZE; ++i ){

		KsMemoryUnit	*pUnit = m_pHashTable[ i ];

		while( pUnit ){
			fprintf( fp, "%08d %s, %s %06d, %08d %0x\n", pUnit->m_allocNumber, allocType[ pUnit->m_allocType ], pUnit->m_sourceFile, pUnit->m_sourceLine, pUnit->m_requestSize, (KsUInt32)(pUnit->m_pRequestAddress) ); 
			pUnit = pUnit->m_pNext;
		}
	}

	fclose( fp );
}


