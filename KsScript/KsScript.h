/************************************************************************************************/
/** 
 * @file		KsScript.h
 * @brief		スクリプト
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSCRIPT_H__
#define __KSSCRIPT_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsTypeScript.h"
#include "KsVariable.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * スクリプト
 * @class	KsScript
 * @author	Tsukasa Kato
 * @since   2006/--/--
 * @version 2006/--/--
 */
/************************************************************************************************/
class ksSCRIPT_API KsScript
{
		friend class KsVirtualMachine;

	public:
		/**
		 * コンストラクタ
		 */
								KsScript();

		/**
		 * デストラクタ
		 */
		virtual				~KsScript();

		/**
		 * スクリプト作成
		 * @param	size		サイズ
		 */
		void					create( KsInt32 size );

		/**
		 * スクリプトを破棄する
		 */
		void					destroy();

		/**
		 * スクリプトコードを取得する
		 * @return				スクリプトコードのポインタ
		 */
		KsChar*					getCode() { return m_pCode; }

		/**
		 * スクリプト名を取得する
		 * @return				スクリプト名
		 */
		const KsString&			getName() { return m_name; }

		/**
		 * スクリプトIDを取得する
		 * @return				スクリプトID
		 */
		KsInt32				getID() const { return m_id; }

		/**
		 * 文字列ハンドルリストを取得する
		 * @return				文字列ハンドルリスト
		 */
		KsHandleList*			getStringHandleList() { return m_pStringHandleList; }

		/**
		 * グローバルハンドルリストを取得する
		 * @return				グローバルハンドルリスト
		 */
		KsHandleList*			getGlobalHandleList() { return m_pGlobalHandleList; }

		/**
		 * 構造体ハンドルリストを取得する
		 * @return				構造体ハンドルリスト
		 */
		KsHandleList*			getStructHandleList() { return m_pStructHandleList; }

		/**
		 * 関数ハンドルリストを取得する
		 * @return				関数ハンドルリスト
		 */
		KsHandleList*			getFuncHandleList() { return m_pFuncHandleList; }

	protected:
		KsString				m_name;					/**< スクリプト名					*/
		KsInt32				m_id;					/**< 識別用ＩＤ						*/
		KsChar*					m_pCode;				/**< 実行コード						*/
		KsHandleList*			m_pStringHandleList;	/**< 文字列ハンドルリスト			*/
		KsHandleList*			m_pGlobalHandleList;	/**< グローバルハンドルリスト		*/
		KsHandleList*			m_pStructHandleList;	/**< 構造体ハンドルリスト			*/
		KsHandleList*			m_pFuncHandleList;		/**< 関数ハンドルリスト				*/
};


#endif /* __KSSCRIPT_H__ */



