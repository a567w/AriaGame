/************************************************************************************************/
/** 
 * @file		KsSmartPointer.h
 * @brief		配列バージョンスマートポインタ
 * @author		Tsukasa Kato
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSSMARTPOINTERARRAY_H__
#define __KSSMARTPOINTERARRAY_H__
#if 0
/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsType.h"


/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 *	@class		KsSmartPtrArray
 *	@brief		スマートポインタ
 *	@since		2005/10/25
 *	@author		tukasa kato
 */
/************************************************************************************************/
template<typename T> class KsSmartPtrArray : public KsSmartPtrObject
{
	public:
		/* 型をセット */
		typedef T				element_type;
		
	public:
		/**
		 * コンストラクタ
		 */
		explicit				KsSmartPtrArray();
			
		/**
		 * コンストラクタ
		 */
		explicit				KsSmartPtrArray( T* p, KsInt32 num = 0 );
		
		/**
		 * コピーコンストラクタ
		 */
								KsSmartPtrArray( const KsSmartPtrArray<T>& rhs );
		
		/**
		 * デストラクタ
		 */
		virtual				~KsSmartPtrArray();

		/**
		 * 削除処理
		 */
		void					destroy()

		/**
		 * = 演算子オーバーロード
		 */
		KsSmartPtrArray<T>&		operator=( const KsSmartPtrArray<T>& rhs );

		/**
		 * = 演算子オーバーロード
		 */
		KsSmartPtrArray<T>&		operator=( const T* ptr );


		KsBool					operator < ( const KsSmartPtrArray<T>& rhs ) const { return *m_ptr < *rhs->get(); }

		T&						operator*()  const { return *m_ptr; }
		T*						operator->() const { return  m_ptr; }
		T*						get()        const  { return  m_ptr; }

		T**						operator&() const { return &m_ptr; }

		T&						operator [] ( KsInt32 index ){ return *get( index ); }

	private:
		T*						m_ptr;			/**< ポインタ部分	*/
		KsInt32				m_num;			/**< */
		KsInt32				m_sizeof;		/**< */
		KsSmartPtrArray<T>*		m_pPrev;
		KsSmartPtrArray<T>*		m_pNext;
};

#endif

/*************************************************************************************************/
/*---------------------------<< インライン部分ヘッダーファイル >>--------------------------------*/
								#include "KsSmartPointerArray.inl"
/*-----------------------------------------------------------------------------------------------*/
/*************************************************************************************************/

#endif	/* SMARTPOINTER_H */

#endif