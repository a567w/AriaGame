/************************************************************************************************/
/** 
 * @file		KsHandleObject.h
 * @brief		ハンドルオブジェクト
 * @author		Tsukasa Kato
 * @date		2006/10/17
 * @since		2006/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSHANDLEOBJECT_H__
#define __KSHANDLEOBJECT_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsTypeScript.h"

/************************************************************************************************/
/**
 * 文字列などの変数オブジェクト用
 * @class	KsHandleObject
 * @author	Tsukasa Kato
 * @since   2006/--/--
 * @version 2006/--/--
 */
/************************************************************************************************/
class ksSCRIPT_API KsHandleObject
{
		friend class KsHandleManager;
		friend class KsVirtualMachine;
	public:
		/**
		 * コンストラクタ
		 */
									KsHandleObject() : m_pNext( 0 ) {}

		/**
		 * デストラクタ
		 */
		virtual					~KsHandleObject(){}

		/**
		 * 値のタイプ
		 * @return					値のタイプ
		 */
		virtual ksVALUE_TYPE		getType() const = 0;

		/**
		 * 参照(ハンドル)
		 * @return					ハンドル
		 */
		virtual KsHandle			getHandle() { return reinterpret_cast<KsHandle>( this ); }

	protected:
		KsHandleObject*				m_pNext;	/**< 次のハンドルポインタ	*/
};


#endif /* __KSHANDLEOBJECT_H__ */

