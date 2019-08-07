/************************************************************************************************/
/** 
 * @file		KsMemoryFixedBlock.h
 * @brief		固定メモリ管理（フリーリスト）
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMEMORYFIXEDBLOCK_H__
#define __KSMEMORYFIXEDBLOCK_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsMemoryFixedBlock
 * @brief		固定メモリーマネージャ(4バイト以上でないとダメ)
 * @since		2005/03/04
 * @author		Tsukasa Kato
 */
/************************************************************************************************/
class ksENGINE_API KsMemoryFixedBlock
{
	public:
		/**
		 * コンストラクタ
		 */
										KsMemoryFixedBlock();

		/**
		 * コンストラクタ(ブロックリストを生成する)
		 * @param		elementSize		要素のサイズ
		 * @param		numElement		要素数
		 * @param		numBlock		ブロック数
		 */
										KsMemoryFixedBlock( KsUInt32 elementSize, KsUInt32 numElement, KsUInt32 numBlock=0 );

		/**
		 * デストラクタ
		 */
										~KsMemoryFixedBlock();

		/**
		 * ブロックリストを生成する
		 * @param		elementSize		要素のサイズ
		 * @param		numElement		要素数
		 * @param		numBlock		ブロック数
		 */
		void							create( KsUInt32 elementSize, KsUInt32 numElement, KsUInt32 numBlock=0 );

		/**
		 * 要素ををクリアする
		 */
		void							clear();
	
		/**
		 * 破棄する
		 */
		void							destroy();
	
		/**
		 * メモリーブロックを生成する
		 */
		void							createMemoryBlock();
	
		/**
		 * メモリーをブロックから確保する
		 */
		void*							alloc();
	
		/**
		 * このリストで確保されたメモリーかのチェック
		 * @retval		ksTRUE			これで確保されたメモリ
		 * @retval		ksFALSE			これ以外で確保されたメモリ
		 */
		KsBool							isBlockListMemory( void* ptr );

	public:
		KsMemoryFixedUnit*				m_pTopBlock;		/**< 先頭ブロックのポインタ	*/
		KsMemoryFixedUnit*				m_pCurrentBlock;	/**< 現在のブロックのポインタ	*/
		KsUInt32						m_elementSize;		/**< 要素のサイズ			*/
		KsUInt32						m_blockSize;		/**< ブロックサイズ			*/
};

#endif		/* __KSMEMORYFIXEDBLOCK_H__ */

