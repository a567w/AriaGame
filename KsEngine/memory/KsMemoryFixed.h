/************************************************************************************************/
/** 
 * @file		KsMemoryFixed.h
 * @brief		固定メモリ管理（フリーリスト）
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMEMORYFIXED_H__
#define __KSMEMORYFIXED_H__

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
 * @class		KsMemoryFixed
 * @brief		固定メモリーマネージャ(4バイト以上でないとダメ)
 * @since		2005/03/04
 * @author		Tsukasa Kato
 */
/************************************************************************************************/
class ksENGINE_API KsMemoryFixed
{
	private:
		/**
		 * フリーリスト
		 */
		class KsFreeList
		{
			public:
				KsFreeList*				m_pNext;	/**< リストのポインタ		*/
		};

	public:
		/**
		 * コンストラクタ
		 */
										KsMemoryFixed();

		/**
		 * コンストラクタ
		 * @param		elementSize		要素のサイズ
		 * @param		numElement		要素数
		 * @param		numBlock		ブロック数
		 */
										KsMemoryFixed( KsUInt32 elementSize, KsUInt32 numElement, KsUInt32 numBlock=0 );

		/**
		 * デストラクタ
		 */
										~KsMemoryFixed();

		/**
		 * 生成する
		 * @param		elementSize		要素のサイズ
		 * @param		numElement		要素数
		 * @param		numBlock		ブロック数
		 */
		void							create( KsUInt32 elementSize, KsUInt32 numElement, KsUInt32 numBlock );

		/**
		 * クリアーする
		 */
		void							clear();
	
		/**
		 * 破棄する
		 */
		void							destroy();

		/**
		 * メモリー確保
		 * @return						確保したメモリー
		 */
		void*							KsAlloc();

		/**
		 * メモリー開放 
		 * @param		ptr				ポインタ
		 */
		void							KsFree( void* ptr );

		/**
		 * このリストで確保されたメモリーかのチェック
		 * @retval		ksTRUE			これで確保されたメモリ
		 * @retval		ksFALSE			これ以外で確保されたメモリ
		 */
		KsBool							isMemory( void* ptr );

	private:
		KsMemoryFixedBlock				m_memoryBlockList;		/**< メモリーブロックリスト	*/
		KsFreeList*						m_pFreeList;			/**< フリーリストの先頭		*/
};


#endif		/* __KSMEMORYFIXED_H__ */

