/************************************************************************************************/
/** 
 * @file		KsShaderManager.h
 * @brief		シェーダーマネージャー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSSHADERMANAGER_H__
#define __KSSHADERMANAGER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsShaderProgram;

/************************************************************************************************/
/**
 * @class		KsShaderManager
 * @brief		シェーダーマネージャー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		本当は、ハッシュテーブルなどを使用したほうがいいがあまりテクスチャマテリアルは、
 *				あまり、使わないはずなので線形で探索する。
 */
/************************************************************************************************/
class ksENGINE_API KsShaderManager : public KsSingleton< KsShaderManager >
{
	public:
		/**
		 * コンストラクタ
		 */
										KsShaderManager(){}

		/**
		 * デストラクタ
		 */
		virtual							~KsShaderManager(){}

		/**
		 * ファイルからシェーダーを生成
		 * @param	pFileName			ファイル名
		 * @param	pEntryPoint			エントリーポイント
		 * @param	shaderModel			シェーダーモデル
		 * @param	shaderType			シェーダータイプ
		 * @return						シェーダープログラムのポインタ
		 */
		virtual KsShaderProgram*		createFromFile( const KsChar* pFileName, const KsChar* pEntryPoint, ksSHADER_MODEL_TYPE shaderModel, ksSHADER_TYPE shaderType ) = 0;

		/**
		 * データからシェーダーを生成
		 * @param	pData				データ
		 * @param	dataSize			データサイズ
		 * @param	shaderType			シェーダータイプ
		 * @return						シェーダープログラムのポインタ
		 */
		virtual KsShaderProgram*		createFromMemory( const void* pData, KsUInt32 dataSize, ksSHADER_TYPE shaderType ) = 0;

		/**
		 * ファイルからシェーダーを生成
		 * @param	pFileName			ファイル名
		 * @param	pEntryPoint			エントリーポイント
		 * @param	shaderModel			シェーダーモデル
		 * @param	shaderType			シェーダータイプ
		 * @return						シェーダープログラムのポインタ
		 */
		virtual KsShaderProgram*		createFromResource( const KsChar* pFileName, const KsChar* pEntryPoint, ksSHADER_MODEL_TYPE shaderModel, ksSHADER_TYPE shaderType ) = 0;

		/**
		 * 指定した名前のシェーダーを検索する
		 * 取得した後に参照カウントをあげる必要がある
		 * @param	pName				ファイル名
		 * @return						見つかったシェーダーのポインタ
		 */
		virtual KsShaderProgram*		find( const KsChar* pName );

		/**
		 * 検索して見つかったら参照カウントをアップする
		 * @param	pName				ファイル名
		 * @return						見つかったシェーダーのポインタ
		 */
		virtual KsShaderProgram*		findRefInc( const KsChar* pName );

		/**
		 * シェーダーを追加する
		 * DEBUGモードのときは、2重登録チェックをする
		 * @param	pShader				追加するシェーダーのポインタ
		 * @retval	ksTRUE				成功
		 * @retval	ksFALSE				失敗
		 */
		virtual KsBool					add( KsShaderProgram* pShader );

		/**
		 * シェーダーをマネージャから取り除く
		 * @param	pShader				取り除くシェーダーのポインタ
		 * @retval	ksTRUE				成功
		 * @retval	ksFALSE				失敗
		 */
		virtual KsBool					remove( KsShaderProgram* pShader );

		/**
		 * シェーダーを削除する
		 * @param	pShader				削除するシェーダーのポインタ
		 * @retval	ksTRUE				成功
		 * @retval	ksFALSE				失敗
		 */
		virtual KsBool					destroy( KsShaderProgram* pShader );

		/**
		 * すべてのシェーダーを破棄する(参照カウント関係なく破棄される)
		 * @retval	ksTRUE				成功
		 * @retval	ksFALSE				失敗
		 */
		virtual KsBool					destroyAll();

	protected:
		KsHashTable< KsShaderProgram* >	m_pShaders;		/**< シェーダーリスト	*/

	public:
		/**
		 * シングルトンの参照を取得
		 * @return						シングルトンの参照
		 */
		static KsShaderManager&			getInstance();
		
		/**
		 * シングルトンのポインタを取得
		 * @return						シングルトンのポインタ
		 */
		static KsShaderManager*			getInstancePtr();
};

#endif		/* __KSSHADERMANAGER_H__ */




