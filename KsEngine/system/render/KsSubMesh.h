/************************************************************************************************/
/** 
 * @file		KsSubMesh.h
 * @brief		ジオメトリ生成
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSUBMESH_H__
#define __KSSUBMESH_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsType.h"
#include "KsVertexData.h"
#include "KsIndexData.h"
#include "KsMaterial.h"
#include "KsTexture.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

class KsFaceList
{
public:
	KsUInt16		m_start;
	KsUInt16		m_end;
	KsUInt16		m_materialID;
};


/************************************************************************************************/
/**
 * サブメッシュ
 * @class		KsSubMesh
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsSubMesh
{
	public:
		/**
		 * コンストラクタ
		 */
										KsSubMesh();
		/**
		 * デストラクタ
		 */
		virtual						~KsSubMesh();

		/**
		 * ジオメトリ生成
		 * @param		pData			データの先頭ポインタ
		 * @retval		ksTRUE			成功
		 * @retval		ksFALSE			失敗
		 */
		//KsBool							create( KsByte* pData );

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

		/**
		 * 頂点数を取得する
		 * @return		頂点数
		 */
		KsUInt16						getNumVertex() const { return m_numVertex; }

		/**
		 * 面の数を取得する
		 * @return		面の数
		 */
		KsUInt16						getNumIndex() const { return m_numIndex; }

		/**
		 * マテリアル数を取得する
		 * @return		マテリアル数
		 */
		const std::string&				getName() { return m_name; }

		/**
		 * マテリアル数を取得する
		 * @return		マテリアル数
		 */
		const std::string&				getMaterialName() { return m_materialName; }

		/**
		 * テクスチャ数を取得する
		 * @return		テクスチャ数
		 */
		const std::string&				getTextureName() { return m_textureName; }

		/**
		 * 指定インデックスの頂点を取得する
		 * @param		index			インデックス
		 * @return						頂点のポインタ
		 */
		//const KsVertexData*				getVertexData() const { return &m_pVertices[ index ]; }

		/**
		 * 指定インデックスの面を取得する
		 * @param		index			インデックス
		 * @return						面のポインタ
		 */
		//const KsIndexData*				getIndexData( KsUInt16 index ) { return &m_pFaces[ index ]; }

		/**
		 * 指定インデックスのマテリアルを取得する
		 * @param		index			インデックス
		 * @return						マテリアルのポインタ
		 */
		//const KsMaterial*				getMaterial() { return &m_pMaterials[ index ]; }

		/**
		 * 指定インデックスのテクスチャを取得する
		 * @param		index			インデックス
		 * @return						テクスチャのポインタ
		 */
		//const KsTexture*				getTexture() { return &m_pTextures[ index ]; }

	public:
		KsUInt32						m_flags;				/**< フラグ				*/
		KsUInt16						m_numVertex;			/**< 頂点数				*/
		KsUInt16						m_numIndex;				/**< 面の数				*/
		KsUInt16						m_numFaceList;			/**< 面構成				*/
		KsVertexData*					m_pVertices;			/**< 頂点データ			*/
		KsIndexData*					m_pIndices;				/**< 面データ			*/
		KsFaceList*						m_pFaceList;			/**< 面構成リスト		*/
		std::string						m_name;					/**< サブメッシュ名前		*/
		std::string						m_textureName;			/**< 使用テクスチャ名		*/
		std::string						m_materialName;			/**< 使用マテリアル名		*/
};

#endif		/* __KSSUBMESH_H__ */


