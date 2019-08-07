/************************************************************************************************/
/** 
 * @file		KsMemFix.cpp
 * @brief		�Œ胁����
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsMemFix.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * �R���X�g���N�^(�u���b�N���X�g�𐶐�����)
 * @param		elementSize		�v�f�̃T�C�Y
 * @param		numElement		�v�f��
 * @param		numBlock		�u���b�N��
 */
/************************************************************************************************/
KsMemoryBlockList::KsMemoryBlockList( KsUInt32 elementSize, KsUInt32 numElement, KsUInt32 numBlock )
{
	m_elementSize   = elementSize;
	m_blockSize     = elementSize * numElement;
	m_pTopBlock     = NULL;
	m_pCurrentBlock = NULL;

	for( KsUInt32 i=0; i<numBlock; i++ )
	{
		KsChar*			pMemory = new KsChar[ sizeof(KsMemoryBlock) + m_blockSize ];
		KsMemoryBlock*	pBlock  = (KsMemoryBlock*)pMemory;

		/* �������[�u���b�N��� */
		pBlock->m_pStartAddr    = pMemory + sizeof( KsMemoryBlock );
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
 * �u���b�N���X�g�𐶐�����
 * @param		elementSize		�v�f�̃T�C�Y
 * @param		numElement		�v�f��
 * @param		numBlock		�u���b�N��
 */
/************************************************************************************************/
void KsMemoryBlockList::create( KsUInt32 elementSize, KsUInt32 numElement, KsUInt32 numBlock )
{
	clear();

	m_elementSize   = elementSize;
	m_blockSize     = elementSize * numElement;

	for( KsUInt32 i=0; i<numBlock; i++ )
	{
		KsChar*			pMemory = new KsChar[ sizeof(KsMemoryBlock) + m_blockSize ];
		KsMemoryBlock*	pBlock  = (KsMemoryBlock*)pMemory;

		/* �������[�u���b�N��� */
		pBlock->m_pStartAddr    = pMemory + sizeof( KsMemoryBlock );
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
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsMemoryBlockList::~KsMemoryBlockList()
{
	clear();
}
/************************************************************************************************/
/*
 * �j������
 */
/************************************************************************************************/
void KsMemoryBlockList::destroy()
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
 * �������[�u���b�N�𐶐�����
 */
/************************************************************************************************/
void KsMemoryBlockList::createMemoryBlock()
{
	if( m_pCurrentBlock && m_pCurrentBlock->m_pNext )
	{
		/* ���łɃu���b�N�̃��X�g������ꍇ */
		m_pCurrentBlock->m_pNext->m_pCurrentAddr = m_pCurrentBlock->m_pNext->m_pStartAddr;    
		m_pCurrentBlock                          = m_pCurrentBlock->m_pNext;
	}
	else
	{
		KsChar*			pMemory = new KsChar[ sizeof(KsMemoryBlock) + m_blockSize ];
		KsMemoryBlock*	pBlock  = (KsMemoryBlock*)pMemory;

		/* �������[�u���b�N��� */
		pBlock->m_pStartAddr    = pMemory + sizeof( KsMemoryBlock );
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
 * �������[���u���b�N����m�ۂ���
 */
/************************************************************************************************/
void* KsMemoryBlockList::alloc()
{
	void*		pAddress;

	if( !m_pTopBlock ){
		createMemoryBlock();
	}

	if( ( (KsUInt32)m_pCurrentBlock->m_pCurrentAddr + m_elementSize ) > (KsUInt32)m_pCurrentBlock->m_pEndAddr ){
		/* �m�ۂł��Ȃ��̂ŐV�����u���b�N����� */
		createMemoryBlock();
	}

	pAddress = m_pCurrentBlock->m_pCurrentAddr;
	m_pCurrentBlock->m_pCurrentAddr = (void*)( (KsUInt32)m_pCurrentBlock->m_pCurrentAddr + m_elementSize );

	return pAddress;
}
/************************************************************************************************/
/*
 * �v�f�����N���A����
 */
/************************************************************************************************/
void KsMemoryBlockList::clear()
{
	if( m_pTopBlock ){
		m_pTopBlock->m_pCurrentAddr  = m_pTopBlock->m_pStartAddr;
	}

	m_pCurrentBlock = m_pTopBlock;
}

/************************************************************************************************/
/*
 * ���̃��X�g�Ŋm�ۂ��ꂽ�������[���̃`�F�b�N
 * @retval		ksTRUE			����Ŋm�ۂ��ꂽ������
 * @retval		ksFALSE			����ȊO�Ŋm�ۂ��ꂽ������
 */
/************************************************************************************************/
KsBool KsMemoryBlockList::isBlockListMemory( void* ptr )
{
	KsMemoryBlock*	pTemp = m_pTopBlock;
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

/************************************************************************************************/
/*
 * �������[�m��
 */
/************************************************************************************************/
void* KsMemoryFix::KsAlloc()
{
	if( m_pFreeList ){
		KsFreeList*		pTemp = m_pFreeList;
		m_pFreeList = pTemp->m_pNext;
		return pTemp;
	}

	return m_memoryBlockList.alloc();
}

/************************************************************************************************/
/*
 * �������[�J�� 
 */
/************************************************************************************************/
void KsMemoryFix::KsFree( void* ptr )
{
	KsFreeList*		pList = (KsFreeList*)ptr;

	pList->m_pNext = m_pFreeList;
	m_pFreeList    = pList;
}

/************************************************************************************************/
/*
 * ��������
 * @param		elementSize		�v�f�̃T�C�Y
 * @param		numElement		�v�f��
 * @param		numBlock		�u���b�N��
 */
/************************************************************************************************/
void KsMemoryFix::create( KsUInt32 elementSize, KsUInt32 numElement, KsUInt32 numBlock )
{
	m_memoryBlockList.create( elementSize, numElement, numBlock );
}
/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsMemoryFix::~KsMemoryFix()
{
	destroy();
}

/************************************************************************************************/
/*
 * ���̃��X�g�Ŋm�ۂ��ꂽ�������[���̃`�F�b�N
 * @retval		ksTRUE			����Ŋm�ۂ��ꂽ������
 * @retval		ksFALSE			����ȊO�Ŋm�ۂ��ꂽ������
 */
/************************************************************************************************/
KsBool KsMemoryFix::isMemory( void* ptr )
{
	return m_memoryBlockList.isBlockListMemory( ptr );
}


