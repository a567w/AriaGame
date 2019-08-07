/************************************************************************************************/
/**
 * @class		KsMaterialManager
 * @brief		マテリアルマネージャ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		本当は、ハッシュテーブルなどを使用したほうがいいがあまりテクスチャマテリアルは、
 *				あまり、使わないはずなので線形で探索する。
 */
/************************************************************************************************/
class KsMaterialManager : public KsSingleton< KsMaterialManager >
{
	public:
		/**
		 * コンストラクタ
		 */
										KsMateiralManager();

		/**
		 * デストラクタ
		 */
		virtual						~KsMateiralManager();

		/**
		 * 指定した名前のテクスチャを検索する
		 * 取得した後に参照カウントをあげる必要がある
		 * @param	pName				ファイル名
		 * @return						見つかったテクスチャのポインタ
		 */
		virtual KsTexture*				find( const KsChar* pName );

		/**
		 * 検索して見つかったら参照カウントをアップする
		 * @param	pName				ファイル名
		 * @return						見つかったテクスチャのポインタ
		 */
		virtual KsTexture*				findRefInc( const KsChar* pName );

		/**
		 * テクスチャを追加する
		 * DEBUGモードのときは、2重登録チェックをする
		 * @param	pMaterial			追加するテクスチャのポインタ
		 * @retval	ksTRUE				成功
		 * @retval	ksFALSE				失敗
		 */
		virtual KsBool					add( KsMaterial* pMaterial );

		/**
		 * テクスチャをマネージャから取り除く
		 * @param	pMaterial			取り除くテクスチャのポインタ
		 * @retval	ksTRUE				成功
		 * @retval	ksFALSE				失敗
		 */
		virtual KsBool					remove( KsMaterial* pMaterial );

		/**
		 * テクスチャを削除する
		 * @param	pMaterial			削除するテクスチャのポインタ
		 * @retval	ksTRUE				成功
		 * @retval	ksFALSE				失敗
		 */
		virtual KsBool					destroy( KsMaterial* pMaterial );

		/**
		 * すべてのテクスチャを破棄する(参照カウント関係なく破棄される)
		 * @retval	ksTRUE				成功
		 * @retval	ksFALSE				失敗
		 */
		virtual KsBool					destroyAll();

		/**
		 * シングルトンの参照を取得
		 * @return						シングルトンの参照
		 */
		static KsMaterialManager&		getInstance();
		
		/**
		 * シングルトンのポインタを取得
		 * @return						シングルトンのポインタ
		 */
		static KsMaterialManager*		getInstancePtr();

	protected:
		KsTexture*						m_pTop;		/**< リストの先頭ポインタ	*/
};

