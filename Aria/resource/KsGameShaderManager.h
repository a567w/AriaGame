/************************************************************************************************/
/** 
 * @file		KsGameShaderManager.h
 * @brief		ゲームリソース
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSGAMESHADEREMANAGER_H__
#define __KSGAMESHADEREMANAGER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsGameShaderManager
 * @brief		ゲームリソース
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsGameShaderManager : public KsSingleton< KsGameShaderManager >
{
	public:
		/**
		 * シングルトンの参照を取得
		 * @return							シングルトンの参照
		 */
		static KsGameShaderManager&			getInstance();
		
		/**
		 * シングルトンのポインタを取得
		 * @return							シングルトンのポインタ
		 */
		static KsGameShaderManager*			getInstancePtr();

	public:
		/**
		 * コンストラクタ
		 */
											KsGameShaderManager();

		/**
		 * デストラクタ
		 */
		virtual								~KsGameShaderManager();

		/** 
		 * ファイルパックからシェダーを生成する
		 * @param	rFileName		ファイルパック
		 * @retval	ksTRUE			成功
		 * @retval	ksFALSE			失敗
		 */
		KsBool								create( const KsString& rFileName );

		/**
		 * すべてのリソースを解放する
		 */
		void								destroy();

		/** 
		 * シェダープログラムを検索する
		 * @param	rShaderName		シェダープログラム名
		 * @return					シェダープログラム見つからない時はNULLを返す
		 */
		KsShaderProgram*					find( const KsString& rShaderName );
		

	protected:
		KsFilePack*							m_pFilePack;	/**< ファイルパック		*/
		KsHashTable<KsShaderProgram*>		m_vpShaderTbl;	/**< シェーダーテーブル	*/
};

#endif /* __KSGAMESHADEREMANAGER_H__ */

