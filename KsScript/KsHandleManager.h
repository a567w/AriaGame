/************************************************************************************************/
/** 
 * @file		KsHandleManager.h
 * @brief		ハンドルマネージャ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSHANDLEMANAGER_H__
#define __KSHANDLEMANAGER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsTypeScript.h"
#include "KsVariable.h"
#include "KsStringObject.h"
#include "KsGlobalObject.h"
#include "KsStructObject.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 *	@class		KsHandleManager
 *	@brief		ハンドルマネージャ
 *	@since		2005/10/25
 *	@author		Tsukasa Kato
 */
/************************************************************************************************/
class ksSCRIPT_API KsHandleManager
{
	public:
		/**
		 * コンストラクタ
		 */
											KsHandleManager();

		/**
		 * デストラクタ
		 */
		virtual							~KsHandleManager();

		/**
		 * 関数のハンドル
		 */
		KsHandle							getFuncHandle();

		/**
		 * 変数のハンドル
		 */
		KsHandle							getGlobalHandle( const KsChar* pString );

		/**
		 * 文字列のハンドル
		 */
		KsHandle							getStringHandle( const KsChar* pString );

		/** 
		 * 構造体のハンドル
		 */
		KsHandle							getStructHandle( const KsChar* pString );
		KsGlobalObject*						getGlobalObject( const KsChar* pString );
		KsStructObject*						getStructObject( const KsChar* pString );

		//
		KsHandle							createStringHandle( const KsChar* pString );
		KsHandle							createGlobalHandle( const KsChar* pString );
		KsStructObject*						createStructObject( const KsChar* pString );

		void								destoryStringObject( KsHandle handle );
		void								destoryGlobalObject( KsHandle handle );
		void								destoryStructObject( KsHandle handle );

	public:
		/* ハッシュテーブルから変数名や関数名で指定オブジェクトを検索する */
		/* 文字列を管理する */
		KsHashTable< KsHandleObject* >		m_stringHandleList;		/**< 文字列のハンドルオブジェクトリスト			*/

		/* グローバル変数を管理する */
		KsHashTable< KsHandleObject* >		m_globalHandleList;		/**< グローバル変数のハンドルオブジェクトリスト	*/

		/* 構造体を管理する */
		KsHashTable< KsHandleObject* >		m_structHandleList;		/**< 構造体のハンドルオブジェクトリスト			*/
};


extern KsHandle KsGetStringHandle( KsHandleManager* pHM, const KsChar* pString );
extern KsHandle KsGetGlobalHandle( KsHandleManager* pHM, const KsChar* pString );
extern KsHandle KsGetStructHandle( KsHandleManager* pHM, const KsChar* pString );
extern KsHandle KsGetFuncHandle( const KsChar* pString );

extern KsHandleObject* KsGetHandleObject( KsHandle handle );
extern KsGlobalObject* KsGetGlobalObject( KsHandleManager* pHM, const KsChar* pString );
extern KsStructObject* KsGetStructObject( KsHandleManager* pHM, const KsChar* pString );

extern KsHandle KsCreateStringHandle( KsHandleManager* pHM, const KsChar* pString );
extern KsHandle KsCreateGlobalHandle( KsHandleManager* pHM, const KsChar* pString );

extern void KsDestoryStringObject( KsHandleManager* pHM, KsHandle handle );
extern void KsDestoryGlobalObject( KsHandleManager* pHM, KsHandle handle );
extern void KsDestoryStructObject( KsHandleManager* pHM, KsHandle handle );

#endif		/* __KSHANDLEMANAGER_H__	*/




