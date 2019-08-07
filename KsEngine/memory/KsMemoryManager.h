/************************************************************************************************/
/**
 * @file	KsMemoryManager.h
 * @brief	メモリー管理
 * @author	Tsukasa Kato
 * @date	2004/03/30
 * @version	1.0.0
 */
/************************************************************************************************/
#ifndef __KSMEMORYMANAGER_H__
#define __KSMEMORYMANAGER_H__

/*==============================================================================================*/
/*									<< インクルード >>											*/
/*==============================================================================================*/

/*==============================================================================================*/
/*										<< 定義 >>												*/
/*==============================================================================================*/
#ifndef KS_NORMAL_MEMORY_MANAGER
	#undef new
	#undef DEBUG_NEW
#endif 
	
/*==============================================================================================*/
/*										<< 宣言 >>												*/
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsMemoryManager
 * @brief		メモリー管理
 * @author		Tsukasa Kato
 * @todo		指定サイズ以下は固定場所を使うようにする
 */
/************************************************************************************************/
class ksENGINE_API KsMemoryManager
{
	public:
		/**
		 * メモリーを確保する(malloc)
		 * @param		KsSize				確保するメモリーのサイズ
		 * @param		pszFile				ファイル名
		 * @param		line				ファイルの何行目かの行数
		 * @return							確保したメモリーのアドレス
		 */
		static void*						KsMalloc( KsSize size, KsUInt32 line, const KsChar* pszFile, const KsChar* pszFunc );

		/**
		 * メモリーを確保する(calloc)
		 * @param		KsSize				確保するメモリーのサイズ
		 * @param		pszFile				ファイル名
		 * @param		line				ファイルの何行目かの行数
		 * @return							確保したメモリーのアドレス
		 */
		static void*						KsCalloc( KsSize size, KsUInt32 line, const KsChar* pszFile, const KsChar* pszFunc );

		/**
		 * メモリーを確保する(ralloc)
		 * @param		pAddress			確保アドレス
		 * @param		KsSize				確保するメモリーのサイズ
		 * @param		pszFile				ファイル名
		 * @param		line				ファイルの何行目かの行数
		 * @return							確保したメモリーのアドレス
		 */
		static void*						KsRealloc( void* pAddress, KsSize size, KsUInt32 line, const KsChar* pszFile, const KsChar* pszFunc );

		/**
		 * メモリーを開放する(free)
		 * @param		pAddress			開放するメモリーのアドレス
		 */
		static void							KsFree( void* pAddress );

		/**
		 * メモリーの状況をファイルにダンプします
		 */
		static void							dump();

		/**
		 * タグ名をスタックにPushしてセットする
		 * @param		pTagName			タグ名
		 */
		static void							pushTag( const KsChar* pTagName );

		/**
		 * タグ名をPopする
		 */
		static void							popTag();

		/**
		 * メモリー確保関数が呼ばれるファイル名と何行目かをセットする
		 * @param		pszFile				ファイル名
		 * @param		line				ファイルの何行目かの行数
		 */
		static void							SetCallFile( KsUInt32 line, const KsChar* pszFile, const KsChar* pszFunc );

		/**
		 * new 演算子オーバーロード
		 */
		friend void*						operator new   ( KsSize size );

		/**
		 * new[] 演算子オーバーロード
		 */
		friend void*						operator new[] ( KsSize size );

		/**
		 * delete 演算子オーバーロード
		 */
		friend void							operator delete   ( void* pAddress );

		/**
		 * delete[] 演算子オーバーロード
		 */
		friend void							operator delete[] ( void* pAddress );

	protected:
		/**
		 * メモリーを確保する
		 * @param		KsSize				確保するメモリーのサイズ
		 * @param		type				確保するメモリーのタイプ
		 * @param		pszFile				ファイル名
		 * @param		line				ファイルの何行目かの行数
		 * @return							確保したメモリーのアドレス
		 */
		static void*						allocator( KsSize size, KsUInt32 type, KsUInt32 line, const KsChar* pszFile, const KsChar* pszFunc );
	
		/**
		 * メモリーを開放する
		 * @param		pAddress			開放するメモリーのアドレス
		 * @param		type				開放するメモリーのタイプ
		 */
		static void							deallocator( void* pAddress, KsUInt32 type );

		/**
		 * 指定されたアドレスのメモリーユニットを見つける
		 * @param		pAddress			確保したメモリーのサイズ
		 * @return							指定メモリを使用しているメモリーユニットのアドレス
		 */
		static KsMemoryUnit*				findAllocUnit( const void* pAddress );

		/**
		 * 実アドレスから要求されたアドレスを求める
		 * @param		pActualAddress	
		 * @return							要求されたアドレス
		 */
		static void*						computeRequestAddress( const void* pActualAddress );

		/**
		 * リセットする
		 */
		static void							reset();

	protected:
		static KsMemoryUnit*				m_pHashTable[ ksMEMORY_HASH_SIZE ];	/**< ハッシュテーブル					*/
		static KsUInt32						m_currentAllocCount;				/**< 現在のメモリー確保カウント		*/
		static KsUInt32						m_breakOnAllocCount;				/**< 開放メモリーカウント				*/
		static KsUInt32						m_sourceLine;						/**< ソースファイルの何行目か			*/
		static KsChar*						m_sourceFile;						/**< ソースファイル名					*/
		static KsChar*						m_funcName;							/**< 関数名							*/
		static KsMemoryUnit*				m_pReservoir;						/**< メモリ管理のユニットリスト		*/
		static KsMemoryUnit**				m_ppReservoirBuffer;				/**< メモリーユニットのバッファ		*/
		static KsUInt32						m_reservoirBufferSize;				/**< バッファを何回確保しなおしたか	*/
		static KsMemoryState				m_state;							/**< メモリーステータス				*/
		static KsInt32						m_tagCount;							/**< タグスタック位置					*/
		static KsInt32						m_zeroAlloc;						/**< サイズ０確保用					*/
		static KsCriticalSection			m_cs;								/**< クリティカルセクション			*/
		static KsChar						m_tagNameStack[ ksMEMORY_TAG_STACK_SIZE ][ ksMEMORY_NAME_SIZE ];
		static KsChar						m_nowTagName[ ksMEMORY_NAME_SIZE ];
};

#ifndef KS_NORMAL_MEMORY_MANAGER

/************************************************************************************************/
/*
 * メモリー確保(new)
 */
/************************************************************************************************/
inline void*	operator new ( KsSize size )
{
	return KsMemoryManager::allocator( size, ksALLOC_TYPE_NEW, KsMemoryManager::m_sourceLine, KsMemoryManager::m_sourceFile, KsMemoryManager::m_funcName );
}

/************************************************************************************************/
/*
 * メモリー確保(new[])
 */
/************************************************************************************************/
inline void*	operator new[] ( KsSize size )
{
	return KsMemoryManager::allocator( size, ksALLOC_TYPE_NEW_ARRAY, KsMemoryManager::m_sourceLine, KsMemoryManager::m_sourceFile, KsMemoryManager::m_funcName );
}

/************************************************************************************************/
/*
 * メモリー解法(delete)
 */
/************************************************************************************************/
inline void	operator delete ( void* pAddress )
{
	KsMemoryManager::deallocator( pAddress, ksALLOC_TYPE_DELETE );
}

/************************************************************************************************/
/*
 * メモリー解法(delete[])
 */
/************************************************************************************************/
inline void	operator delete[] ( void* pAddress ) 
{
	KsMemoryManager::deallocator( pAddress, ksALLOC_TYPE_DELETE_ARRAY );
}

/************************************************************************************************/
/*								<< メモリー関数置き換え >>										*/
/************************************************************************************************/
#define	new				( KsMemoryManager::SetCallFile( __LINE__, _T(__FILE__), _T(__FUNCTION__) ), ksFALSE ) ? 0 : new
#define	delete			( KsMemoryManager::SetCallFile( __LINE__, _T(__FILE__), _T(__FUNCTION__) ), ksFALSE ) ? KsMemoryManager::SetCallFile( 0, _T("??"), _T("??") ) : delete
#define	malloc( s )		( KsMemoryManager::KsMalloc( s, __LINE__, _T(__FILE__), _T(__FUNCTION__) ) )
#define	calloc( s )		( KsMemoryManager::KsCalloc( s, __LINE__, _T(__FILE__), _T(__FUNCTION__) ) )
#define	realloc( p, s )	( KsMemoryManager::KsRalloc( s, p, __LINE__, _T(__FILE__), _T(__FUNCTION__) ) )
#define	free( p )		( KsMemoryManager::KsFree( p ) )

#define	ksNew			( KsMemoryManager::SetCallFile( __LINE__, _T(__FILE__), _T(__FUNCTION__) ), ksFALSE ) ? 0 : new
#define	ksDelete		( KsMemoryManager::SetCallFile( __LINE__, _T(__FILE__), _T(__FUNCTION__) ), ksFALSE ) ? KsMemoryManager::SetCallFile( 0, _T("??"), _T("??") ) : delete

#endif

/************************************************************************************************/
/**
 * メモリーリークチェック関数
 * @note	メモリーリークをmemoryLeaks.log ファイルにダンプする
 */
/************************************************************************************************/
#ifdef DEBUG
	#define KsDumpMemoryLeaks()			KsMemoryManager::dump()
	#define KsMemPushTag( pTagName )	KsMemoryManager::pushTag( pTagName );
	#define KsMemPopTag()				KsMemoryManager::popTag();
#else
	#define KsDumpMemoryLeaks()
	#define KsMemPushTag( pTagName )
	#define KsMemPopTag()
#endif



#endif	/* __KSMEMORYMANAGER_H__ */


