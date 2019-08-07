/************************************************************************************************/
/** 
 * @file		KsModuleDynamic.h
 * @brief		DLLモジュール
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMODULEDYNAMIC_H__
#define __KSMODULEDYNAMIC_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsModule.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 *  モジュールのインターフェースクラス
 *	@class		KsModule
 *	@brief		モジュールのインターフェース
 *	@since		2003/10/25
 *	@author		Tsukasa Kato
 */
/************************************************************************************************/
class ksENGINE_API KsModuleDynamic : public KsModule
{
	public:
		/**
		 * コンストラクタ(初期化)
		 * @param	path				パス名
		 * @param	name				モジュール名
		 * @param	pKsModuleManager		モジュールマネージャ
		 */
										KsModuleDynamic( const KsString& path, const KsString& name, KsModuleManager* pModuleManager );

		/**
		 * デストラクタ
		 */
		virtual						~KsModuleDynamic();

		/**
		 * 有効かどうかを取得する
		 * @retval	ksTRUE				有効
		 * @retval	ksFALSE				無効
		 */
		virtual KsBool					isValid() const { return ( m_pLib != 0 ); }

		/**
		 * 静的モジュールかを取得する
		 * @retval	ksTRUE				静的モジュールです
		 * @retval	ksFALSE				静的モジュールでない
		 */
		virtual KsBool					isStatic() const { return ksFALSE; }

		/**
		 * 動的モジュールかを取得する
		 * @retval	ksTRUE				動的モジュールです
		 * @retval	ksFALSE				動的モジュールでない
		 */
		virtual KsBool					isDynamic() const { return ksTRUE; }

		/**
		 * モジュール内のエクスポート関数のアドレスを取得します。
		 * @param			name		エクスポート関数名
		 * @return						モジュール内のエクスポート関数のアドレス
		 */
		virtual void*					getProcAddress( const KsString& name );

	protected:
		void*							m_pLib;			/**< ライブラリ		*/
		KsString						m_fullPath;		/**< フルパス		*/
};


#endif /* __KSMODULEDYNAMIC_H__ */



