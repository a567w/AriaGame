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
#ifndef __KSMODULEMANAGER_H__
#define __KSMODULEMANAGER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsType.h"
#include "KsSingleton.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
#if 0
/************************************************************************************************/
/**
 *  モジュールのインターフェースクラス
 *	@class		KsModule
 *	@brief		モジュールのインターフェース
 *	@since		2003/10/25
 *	@author		Tsukasa Kato
 */
/************************************************************************************************/
class ksENGINE_API KsModuleManager : public KsSingleton< KsModuleManager >
{
	friend class KsModule;

	public:

		/**
		 * コンストラクタ
		 */
										KsModuleManager();

		/**
		 * デストラクタ
		 */
		virtual						~KsModuleManager();

		/**
		 * 検索するパスを追加する
		 * @param	path				追加するパス
		 * @retval	ksTRUE				追加成功
		 * @retval	kaFALSE				追加失敗(パスが存在しない)
		 */
		KsBool							addSearchPath( const KsString& path );

		void							removeSearchPath( const KsString& path );

		virtual void*					loadModule( const KsString& path );

		virtual void					addModule( KsModule* pModule );

		virtual void					removeModule( KsModule* pModule );

		/**
		 * 指定パスが存在しているかどうかのチェック
		 * @param	path				チェックするパス
		 * @retval	ksTRUE				パスが存在する
		 * @retval	kaFALSE				パスが存在しない
		 */
		KsBool							isPathExists( const KsString& path );

	protected:
		KsArray< KsString >				m_searchPaths;		/**< 検索パスリスト		*/
		KsHashTable< KsModule* >		m_hashModules;		/**< モージュールリスト	*/
};

#endif

#endif /* __KSMODULEMANAGER_H__ */

