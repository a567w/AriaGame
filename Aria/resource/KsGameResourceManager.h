/************************************************************************************************/
/** 
 * @file		KsGameResourceManager.h
 * @brief		ゲームリソース
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSGAMERESOURCEMANAGER_H__
#define __KSGAMERESOURCEMANAGER_H__

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
 * @enum		ksTEXTURE_RESOURCE_TYPE
 * @brief		テクスチャリソースタイプ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
enum ksTEXTURE_RESOURCE_TYPE
{
	ksTEXTURE_RESOURCE_COMMON,					/**< 共通テクスチャ					*/
	ksTEXTURE_RESOURCE_MENUM,					/**< メニュー用テクスチャ			*/
	ksTEXTURE_RESOURCE_STAGE,					/**< ステージ用テクスチャ			*/
	ksTEXTURE_RESOURCE_MAX,						/**< テクスチャリソースタイプ最大数	*/
	ksTEXTURE_RESOURCE_FORCE32 = 0x7fffffff,	/**< 強制32bit						*/
};

/************************************************************************************************/
/**
 * @class		KsGameResourceManager
 * @brief		ゲームリソース
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsGameResourceManager : public KsSingleton< KsGameResourceManager >
{
		typedef KsArray<KsTexture*>		KsTextureArray;

	public:
		/**
		 * シングルトンの参照を取得
		 * @return							シングルトンの参照
		 */
		static KsGameResourceManager&		getInstance();
		
		/**
		 * シングルトンのポインタを取得
		 * @return							シングルトンのポインタ
		 */
		static KsGameResourceManager*		getInstancePtr();

	public:
		/**
		 * コンストラクタ
		 */
											KsGameResourceManager();

		/**
		 * デストラクタ
		 */
		virtual								~KsGameResourceManager();

		/**
		 * 生成状況コールバック
		 */
		//KsBool							setup( callback=NULL );

		/** 
		 * 生成する
		 */
		void								create();

		/**
		 * すべてのテクスチャリソースを解放する
		 */
		void								destroy();

		/**
		 * 指定タイプのテクスチャリソースを解放する
		 * @param	type					テクスチャタイプ
		 */
		void								destroyTextures( ksTEXTURE_RESOURCE_TYPE type );

	protected:
		KsTextureArray						m_vpTextures[ ksTEXTURE_RESOURCE_MAX ];	/**< テクスチャ	*/
};

#endif /* __KSGAMERESOURCEMANAGER_H__ */

