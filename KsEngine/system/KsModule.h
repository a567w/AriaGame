/************************************************************************************************/
/** 
 * @file		KsModule.h
 * @brief		モジュール
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMODULE_H__
#define __KSMODULE_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsType.h"
#include "KsString.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsModuleManager;

/************************************************************************************************/
/**
 *  モジュールのインターフェースクラス
 *	@class		KsModule
 *	@brief		モジュールのインターフェース
 *	@since		2003/10/25
 *	@author		Tsukasa Kato
 */
/************************************************************************************************/
class ksENGINE_API KsModule
{
		friend class KsModuleManager;

	protected:
		KsString						m_name;				/**< モジュール名			*/
		KsModuleManager*				m_pModuleManager;	/**< モジュールマネージャ	*/

	public:

		/**
		 * コンストラクタ(初期化)
		 * @param	name				モジュール名
		 * @param	pKsModuleManager		モジュールマネージャ
		 */
										KsModule( const KsString& name, KsModuleManager* m_pModuleManager );

		/**
		 * デストラクタ
		 */
		virtual						~KsModule();

		/**
		 * 有効かどうかを取得する
		 * @retval	ksTRUE				有効
		 * @retval	ksFALSE				無効
		 */
		virtual KsBool					isValid() const = 0;

		/**
		 * 静的モジュールかを取得する
		 * @retval	ksTRUE				静的モジュールです
		 * @retval	ksFALSE				静的モジュールでない
		 */
		virtual KsBool					isStatic() const = 0;

		/**
		 * 動的モジュールかを取得する
		 * @retval	ksTRUE				動的モジュールです
		 * @retval	ksFALSE				動的モジュールでない
		 */
		virtual KsBool					isDynamic() const = 0;

		/**
		 * モジュール内のエクスポート関数のアドレスを取得します。
		 * @param			name		エクスポート関数名
		 * @return						モジュール内のエクスポート関数のアドレス
		 */
		virtual void*					getProcAddress( const KsString& name ) = 0;

		/**
		 * モジュール名を取得する
		 * @return						モジュール名
		 */
		const KsString&					getName() const { return m_name; }
};


#endif /* __KSMODULE_H__ */

