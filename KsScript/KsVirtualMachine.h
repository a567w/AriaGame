/************************************************************************************************/
/** 
 * @file		KsVirtualMachine.h
 * @brief		バーチャルマシン
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSVIRTUALMACHINE_H__
#define __KSSVIRTUALMACHINE_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsTypeScript.h"
#include "KsVariable.h"
#include "KsFunction.h"
#include "KsHandleManager.h"
#include "KsScript.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
#define ksVARIABLE_STACK_SIZE		( 1024 * 10 )	/**< 変数のスタックのサイズ				*/
#define ksHANDLE_LIST_BLOCK_SIZE	( 1024 * 10 )	/**< ハンドルリストブロックのサイズ		*/
#define ksSTRUCT_MEMBER_BLOCK_SIZE	( 256 )			/**< 構造体メンバーブロックのサイズ		*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * バージャルマシン
 * @class	KsVirtualMachine
 * @author	Tsukasa Kato
 * @since   2006/--/--
 * @version 2006/--/--
 */
/************************************************************************************************/
class ksSCRIPT_API KsVirtualMachine
{
	private:
		KsInt32								m_id;						/**< 管理ID登録用				*/
		KsInt32								m_pos;						/**< スタック位置				*/
		KsInt32								m_end;						/**< スタック最後の位置			*/
		KsVariable*							m_variables;				/**< 全体のスタック				*/
		KsVariable*							m_esp;						/**< 最後にセットされた値(返り値とかはここを参照すればいい)*/
		KsMemoryFixed						m_structMemberBlock;		/**< 構造体のメンバーブロック		*/
		KsMemoryFixed						m_handleListBlock;			/**< ハンドルのリスト用ブロック	*/

	public:
		KsArray< KsScript* >				m_vpScripts;				/**< 最大のスクリプトリスト			*/
		KsHashTable< KsFunction* >			m_vpFunctions;				/**< グローバル関数リスト				*/
		KsHashTable< KsScriptLibCallback >	m_vpLibraries;				/**< ライブラリ関数リスト				*/
		KsUInt32							m_variableStackSize;		/**< 変数のスタックのサイズ			*/
		KsUInt32							m_structMemberBlockSize;	/**< ハンドルリストブロックのサイズ	*/
		KsUInt32							m_handleListBlockSize;		/**< 構造体メンバーブロックのサイズ	*/
		KsHandleManager*					m_pHandleManager;			/**< ハンドルマネージャ				*/
	private:
		/**
		 * 空きIDを検索する
		 * @return							空きスクリプトID
		 */
		KsInt32								findFreeID();

		/**
		 * IDからスクリプトを検索する
		 * @param	id						スクリプトID
		 * @return							見つかったスクリプトポインタ
		 */
		KsScript*							findScript( KsInt32 id );

		/**
		 * 構造体メンバー情報確保
		 * @return							構造体メンバー情報ポインタ
		 */
		KsStructMemberInfo*					allocStructMemberBlock();

		/**
		 * ハンドルリストブロック確保
		 * @return							ハンドルリストブロックポインタ
		 */
		KsHandleList*						allocHandleListBlock();

		/**
		 * スクリプト関数の呼び出し
		 * @param	pFunc					呼び出す関数
		 */
		void								call( KsFunction* pFunc );

	public:
		/**
		 * コンストラクタ
		 */
											KsVirtualMachine();

		/**
		 * コンストラクタ(スクリプトエンジンの初期化処理あり)
		 * @param	variableStackSize		変数のスタックのサイズ
		 * @param	structMemberBlockSize	ハンドルリストブロックのサイズ
		 * @param	handleListBlockSize		構造体メンバーブロックのサイズ
		 */
											KsVirtualMachine( KsUInt32 variableStackSize, KsUInt32 structMemberBlockSize, KsUInt32 handleListBlockSize );

		/**
		 * デストラクタ
		 */
		virtual								~KsVirtualMachine();

		/**
		 * 変数スタックのトップを取得する
		 */
		KsVariable*							getStackTop() { return &m_variables[ m_pos ]; }

		/**
		 * 変数スタックのトップのタイプを取得する
		 */
		ksVALUE_TYPE						getVariableTypeTop() const { return m_variables[ m_pos ].getType(); }

		/**
		 * 指定変数スタックのトップのタイプを取得する
		 */
		ksVALUE_TYPE						getVariableType( KsInt32 index ) const { return m_variables[ m_pos - index ].getType(); }

		/**
		 * 変数スタックのトップを取得する
		 */
		KsVariable*							getVariableTop() { return &m_variables[ m_pos ]; }

		/**
		 * 指定変数スタックを取得する
		 */
		KsVariable*							getVariable( KsInt32 index ) { return &m_variables[ m_pos - index ]; }

		/** 
		 * ポップする
		 */
		void								pop() { --m_pos; }

		/**
		 * 整数をプッシュする
		 * @param	value					整数値
		 */
		void								pushInt( KsInt32 value ) { m_variables[ m_pos++ ].setInt( value ); }

		/**
		 * 浮動小数をプッシュする
		 * @param	value					実数値
		 */
		void								pushFloat( KsReal value ) { m_variables[ m_pos++ ].setFloat( value ); }


		/**
		 * スクリプトエンジンの初期化処理
		 * @param	variableStackSize		変数のスタックのサイズ
		 * @param	structMemberBlockSize	ハンドルリストブロックのサイズ
		 * @param	handleListBlockSize		構造体メンバーブロックのサイズ
		 * @retval	ksTRUE					成功
		 * @retval	ksFALSE					失敗
		 */
		KsBool								initialize(	KsUInt32 variableStackSize     = ksVARIABLE_STACK_SIZE,
														KsUInt32 structMemberBlockSize = ksHANDLE_LIST_BLOCK_SIZE,
														KsUInt32 handleListBlockSize   = ksSTRUCT_MEMBER_BLOCK_SIZE );

		/**
		 * シャットダウン処理
		 * @retval	ksTRUE					成功
		 * @retval	ksFALSE					失敗
		 */
		KsBool								shutdown();

		/**
		 * スクリプトフィルの読み込み処理
		 * 管理するための名前が必要(?スクリプトに入ってる名前を使う？)
		 * @param	pFile					読み込むファイルオブジェクト
		 */
		KsInt32								loadScriptFile( KsFileObject* pFile );

		/**
		 * アンロード処理
		 * @param	id						アンロードするスクリプトのID
		 */
		KsBool								unloadScript( KsInt32 id );

		/**
		 * スクリプト関数の呼び出し
		 * @param	pFuncName				呼び出す関数名
		 * @param	pArgs					引数フォーマット
		 * @param	...						可変引数
		 * @return							返り値
		 */
		KsVariable*							callFunc( const KsChar* pFuncName, KsChar* pArgs, ... );

		/**
		 * スクリプト関数の呼び出し
		 * @param	pFuncName				呼び出す関数名
		 */
		KsVariable*							callFunc( const KsChar* pFuncName );

		/**
		 * ライブラリをセットする(内部ライブラリ)
		 * ライブラリを増やすと検索に時間がかかるようになるのでなるべく使用するライブラリだけをリンクするようにする
		 * @param	pLibInfo				スクリプトライブラリ情報
		 */
		KsBool								loadLib( const KsScriptLibInfo* pLibInfo );

		/**
		 * ライブラリを開放する
		 * @param	pLibInfo				スクリプトライブラリ情報
		 */
		KsBool								unloadLib( const KsScriptLibInfo* pLibInfo );
};


#endif /* __KSSVIRTUALMACHINE_H__ */



