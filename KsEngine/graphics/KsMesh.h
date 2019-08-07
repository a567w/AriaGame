/************************************************************************************************/
/** 
 * @file		KsMesh.h
 * @brief		メッシュ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMESH_H__
#define __KSMESH_H__


/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsType.h"
#include "KsSubMesh.h"
#include "KsMaterial.h"
#include "KsTexture.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsMesh
 * @brief		メッシュクラス
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsMesh
{
	public:
		/**
		 * コンストラクタ
		 */
										KsMesh();

		/**
		 * デストラクタ
		 */
		virtual						~KsMesh();

		/**
		 * 描画処理
		 */
		virtual void					draw();
	
	protected:

};

#if 0

/************************************************************************************************/
/**
 * @class		KsMesh
 * @brief		メッシュクラス
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsMesh// : public KsRefCounter
{
		typedef std::vector< KsSubMesh* >					KsSubMeshList;
		typedef std::vector< KsMaterial* >					KsMaterialList;
		typedef std::map< std::string, KsTexture* >		KsTextureList;
	public:
		/**
		 * コンストラクタ
		 */
										KsMesh();

		/**
		 * コンストラクタ
		 * @param		numVertices		頂点数
		 * @param		numFaces		面の数
		 * @param		numMaterials	マテリアル数
		 * @param		numTextures		テクスチャ数
		 */
		//								KsMesh( KsUInt16 numVertices, KsUInt16 numFaces, KsUInt16 numMaterials, KsUInt16 numTextures );

		/**
		 * デストラクタ
		 */
		virtual						~KsMesh();

		/**
		 * ジオメトリ生成
		 * @param		pData			データの先頭ポインタ
		 * @retval		ksTRUE			成功
		 * @retval		ksFALSE			失敗
		 */
		//KsBool							create( KsByte* pData );

		/**
		 * ファイルからジオメトリを生成する
		 * @param		pFile			ファイルデータ
		 * @retval		ksTRUE			成功
		 * @retval		ksFALSE			失敗
		 */
		//KsBool							create( KsFileObject* pFile );

		/**
		 * ジオメトリ生成
		 * @param		numVertices		頂点数
		 * @param		numFaces		面の数
		 * @param		numMaterials	マテリアル数
		 * @param		numTextures		テクスチャ数
		 * @retval		ksTRUE			成功
		 * @retval		ksFALSE			失敗
		 */
		//KsBool							create( KsUInt16 numVertices, KsUInt16 numFaces, KsUInt16 numMaterials, KsUInt16 numTextures );

		/**
		 * ジオメトリのフラグを取得する
		 * @return		ジオメトリの各種フラグ
		 */
		KsUInt32						getFlags()	const { return m_flags; }

		const std::string&				getName() { return m_name; }

		KsSubMesh*						getSubMesh( KsInt32 index )	{ return m_pSubMeshList[ index ]; }
		KsMaterial*						getMaterial( KsInt32 index )	{ return m_pMaterialList[ index ]; }
		KsTexture*						getTexture( const std::string& name )	{ return m_pTextureList[ name ]; }

	public:
		std::string						m_name;					/**< 名前(ファイル名)	*/
		KsUInt32						m_flags;				/**< フラグ				*/
		KsHierarchy*					m_pHierarchy;			/**< 骨組み(階層構造)	*/
		KsSubMeshList					m_pSubMeshList;			/**< サブメッシュリスト	*/
		KsMaterialList					m_pMaterialList;		/**< マテリアルリスト		*/
		KsTextureList					m_pTextureList;			/**< テクスチャリスト		*/
		//BoneList
};
#endif

#endif		/* __KSMESH_H__ */



