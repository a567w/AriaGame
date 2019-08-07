/************************************************************************************************/
/** 
 * @file		KsStringObject.h
 * @brief		文字列オブジェクト
 * @author		Tsukasa Kato
 * @date		2006/10/17
 * @since		2006/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSTRINGOBJECT_H__
#define __KSSTRINGOBJECT_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsTypeScript.h"
#include "KsHandleObject.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * 文字列などの変数オブジェクト用
 * @class	KsStringObject
 * @author	Tsukasa Kato
 * @since   2006/--/--
 * @version 2006/--/--
 */
/************************************************************************************************/
class KsStringObject : public KsHandleObject
{
		friend class KsHandleManager;
		friend class KsVirtualMachine;
	public:

		/**
		 * コンストラクタ
		 */
									KsStringObject() : m_refCount( 0 ) {}

		/**
		 * コンストラクタ
		 * @param	pString			文字列
		 */
									KsStringObject( const KsChar* pString ) : m_refCount( 0 ) { m_string = pString; }

		/**
		 * デストラクタ
		 */
		virtual					~KsStringObject(){}

		/**
		 * 値のタイプ
		 * @return					値のタイプ(文字列)
		 */
		virtual ksVALUE_TYPE		getType() const { return ksVALUE_STRING; }

		/**
		 * 参照カウントアップ
		 */
		void						incRefCount() { ++m_refCount; }

		/**
		 * 参照カウントダウン
		 */
		void						decRefCount() { --m_refCount; }

		/**
		 * 現在の参照カウント値を取得する
		 */
		KsInt32					getRefCount() { return m_refCount; }

		/**
		 * 文字列を取得する
		 * @return					文字列の参照値
		 */
		const KsString&				getString() { return m_string; }

	protected:
		KsString					m_string;		/**< 文字列			*/
		KsInt32					m_refCount;		/**< 参照カウント	*/
};


#endif /* __KSSTRINGOBJECT_H__ */

