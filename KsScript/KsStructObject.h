/************************************************************************************************/
/** 
 * @file		KsStructObject.h
 * @brief		構造体オブジェクト
 * @author		Tsukasa Kato
 * @date		2006/10/17
 * @since		2006/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSTRUCTOBJECT_H__
#define __KSSTRUCTOBJECT_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsTypeScript.h"
#include "KsStringObject.h"

/************************************************************************************************/
/**
 * 構造体メンバー情報
 * @class	KsStructMemberInfo
 * @author	Tsukasa Kato
 * @since   2006/--/--
 * @version 2006/--/--
 */
/************************************************************************************************/
typedef struct KsStructMemberInfo
{
	KsChar						name[ 56 ];		/**< メンバー変数名や関数名最大(55文字)	*/
	KsInt32					handle;			/**< ハンドルまたはインデックス			*/
	KsStructMemberInfo*			next;			/**< 次のメンバーへのポインタ			*/
}KsStructMemberInfo;

/************************************************************************************************/
/**
 * 構造体オブジェクト
 * @class	KsStructObject
 * @author	Tsukasa Kato
 * @since   2006/--/--
 * @version 2006/--/--
 */
/************************************************************************************************/
class KsStructObject : public KsStringObject
{
		friend class KsHandleManager;
		friend class KsVirtualMachine;

	public:
		/**
		 * コンストラクタ
		 */
										KsStructObject();

		/**
		 * コンストラクタ
		 * @param	pString			文字列
		 */
										KsStructObject( const KsChar* pString );


		/**
		 * デストラクタ
		 */
		virtual						~KsStructObject();

		/**
		 * タイプ取得
		 */
		virtual ksVALUE_TYPE			getType() const { return ksVALUE_STRCT; }

		/**
		 * 名前から構造体メンバー情報を取得する
		 * @param	pName				名前
		 * @return						構造体メンバー情報
		 */
		KsStructMemberInfo*				findVar( const KsChar* pName );

		/**
		 * 名前から構造体メンバー情報のインデックスを取得する
		 * @param	pName				名前
		 * @return						構造体メンバー情報のインデックス
		 */
		KsInt32						findVarIndex( const KsChar* pName );

	public:
		KsInt32						m_numMember;		/**< メンバーの数			*/
		KsInt32						m_numVar;			/**< メンバー変数の数		*/
		KsInt32						m_numFunc;			/**< メンバー関数の数		*/
		KsStructMemberInfo*				m_pVarList;			/**< メンバー変数のリスト	*/
		KsStructMemberInfo*				m_pFuncList;		/**< メンバー関数のリスト	*/

		//KsStructMemberInfo*			findFunc( const KsChar* pName );
};



#endif /* __KSSTRUCTOBJECT_H__ */

