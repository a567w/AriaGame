/************************************************************************************************/
/** 
 * @file		KsMemFix.cpp
 * @brief		固定メモリ管理（フリーリスト）
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsMemoryFixedBlock::KsMemoryFixedBlock()
	: m_pTopBlock( 0 )
	, m_pCurrentBlock( 0 )
	, m_elementSize( 0 )
	, m_blockSize( 0 )
{
}

/************************************************************************************************/
/*
 * コンストラクタ(ブロックリストを生成する)
 * @param		elementSize		要素のサイズ
 * @param		numElement		要素数
 * @param		numBlock		ブロック数
 */
/************************************************************************************************/
KsMemoryFixedBlock::KsMemoryFixedBlock( KsUInt32 elementSize, KsUInt32 numElement, KsUInt32 numBlock )
{
	m_elementSize   = elementSize;
	m_blockSize     = elementSize * numElement;
	m_pTopBlock     = NULL;
	m_pCurrentBlock = NULL;

	for( KsUInt32 i=0; i<numBlock; i++ )
	{
		KsChar*			pMemory = new KsChar[ sizeof(KsMemoryFixedUnit) + m_blockSize ];
		KsMemoryFixedUnit*	pBlock  = (KsMemoryFixedUnit*)pMemory;

		/* メモリーブロック情報 */
		pBlock->m_pStartAddr    = pMemory + sizeof( KsMemoryFixedUnit );
		pBlock->m_pEndAddr      = (void*)((KsUInt32)pBlock->m_pStartAddr + m_blockSize );
		pBlock->m_pCurrentAddr  = pBlock->m_pStartAddr;

		pBlock->m_pPrev = m_pTopBlock;
		pBlock->m_pNext = NULL;

		if( m_pCurrentBlock ){
			m_pCurrentBlock->m_pNext = pBlock;
		}

		if( !m_pTopBlock ){
			m_pTopBlock = pBlock;
		}

		m_pCurrentBlock = pBlock;
	}
}
/************************************************************************************************/
/*
 * ブロックリストを生成する
 * @param		elementSize		要素のサイズ
 * @param		numElement		要素数
 * @param		numBlock		ブロック数
 */
/************************************************************************************************/
void KsMemoryFixedBlock::create( KsUInt32 elementSize, KsUInt32 numElement, KsUInt32 numBlock )
{
	clear();

	m_elementSize   = elementSize;
	m_blockSize     = elementSize * numElement;

	for( KsUInt32 i=0; i<numBlock; i++ )
	{
		KsChar*			pMemory = new KsChar[ sizeof(KsMemoryFixedUnit) + m_blockSize ];
		KsMemoryFixedUnit*	pBlock  = (KsMemoryFixedUnit*)pMemory;

		/* メモリーブロック情報 */
		pBlock->m_pStartAddr    = pMemory + sizeof( KsMemoryFixedUnit );
		pBlock->m_pEndAddr      = (void*)((KsUInt32)pBlock->m_pStartAddr + m_blockSize );
		pBlock->m_pCurrentAddr  = pBlock->m_pStartAddr;

		pBlock->m_pPrev = m_pTopBlock;
		pBlock->m_pNext = NULL;

		if( m_pCurrentBlock ){
			m_pCurrentBlock->m_pNext = pBlock;
		}

		if( !m_pTopBlock ){
			m_pTopBlock = pBlock;
		}

		m_pCurrentBlock = pBlock;
	}
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsMemoryFixedBlock::~KsMemoryFixedBlock()
{
	clear();
}
/************************************************************************************************/
/*
 * 破棄する
 */
/************************************************************************************************/
void KsMemoryFixedBlock::destroy()
{
	while( m_pTopBlock )
	{
		KsChar*		pPtr = (KsChar*)m_pTopBlock;

		m_pTopBlock = m_pTopBlock->m_pNext;

		delete [] pPtr;
	}

	m_pTopBlock     = NULL;
	m_pCurrentBlock = NULL;
}

/************************************************************************************************/
/*
 * メモリーブロックを生成する
 */
/************************************************************************************************/
void KsMemoryFixedBlock::createMemoryBlock()
{
	if( m_pCurrentBlock && m_pCurrentBlock->m_pNext )
	{
		/* すでにブロックのリストがある場合 */
		m_pCurrentBlock->m_pNext->m_pCurrentAddr = m_pCurrentBlock->m_pNext->m_pStartAddr;    
		m_pCurrentBlock                          = m_pCurrentBlock->m_pNext;
	}
	else
	{
		KsChar*			pMemory = new KsChar[ sizeof(KsMemoryFixedUnit) + m_blockSize ];
		KsMemoryFixedUnit*	pBlock  = (KsMemoryFixedUnit*)pMemory;

		/* メモリーブロック情報 */
		pBlock->m_pStartAddr    = pMemory + sizeof( KsMemoryFixedUnit );
		pBlock->m_pEndAddr      = (void*)((KsUInt32)pBlock->m_pStartAddr + m_blockSize );
		pBlock->m_pCurrentAddr  = pBlock->m_pStartAddr;

		pBlock->m_pPrev = m_pTopBlock;
		pBlock->m_pNext = NULL;

		if( m_pCurrentBlock ){
			m_pCurrentBlock->m_pNext = pBlock;
		}

		if( !m_pTopBlock ){
			m_pTopBlock = pBlock;
		}

		m_pCurrentBlock = pBlock;
	}
}

/************************************************************************************************/
/*
 * メモリーをブロックから確保する
 */
/************************************************************************************************/
void* KsMemoryFixedBlock::alloc()
{
	void*		pAddress;

	if( !m_pTopBlock ){
		createMemoryBlock();
	}

	if( ( (KsUInt32)m_pCurrentBlock->m_pCurrentAddr + m_elementSize ) > (KsUInt32)m_pCurrentBlock->m_pEndAddr ){
		/* 確保できないので新しくブロックを作る */
		createMemoryBlock();
	}

	pAddress = m_pCurrentBlock->m_pCurrentAddr;
	m_pCurrentBlock->m_pCurrentAddr = (void*)( (KsUInt32)m_pCurrentBlock->m_pCurrentAddr + m_elementSize );

	return pAddress;
}
/************************************************************************************************/
/*
 * 要素ををクリアする
 */
/************************************************************************************************/
void KsMemoryFixedBlock::clear()
{
	if( m_pTopBlock ){
		m_pTopBlock->m_pCurrentAddr  = m_pTopBlock->m_pStartAddr;
	}

	m_pCurrentBlock = m_pTopBlock;
}

/************************************************************************************************/
/*
 * このリストで確保されたメモリーかのチェック
 * @retval		ksTRUE			これで確保されたメモリ
 * @retval		ksFALSE			これ以外で確保されたメモリ
 */
/************************************************************************************************/
KsBool KsMemoryFixedBlock::isBlockListMemory( void* ptr )
{
	KsMemoryFixedUnit*	pTemp = m_pTopBlock;
	KsUInt32		addr  = (KsUInt32)ptr;

	while( pTemp )
	{
		KsUInt32	top = (KsUInt32)pTemp->m_pStartAddr;
		KsUInt32	end = top + m_blockSize;

		if( top<= addr && addr < end ){
			return ksTRUE;
		}

		pTemp = pTemp->m_pNext;
	}

	return ksFALSE;
}


