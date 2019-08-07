/************************************************************************************************/
/** 
 * @file		KsSubMesh.h
 * @brief		サブメッシュ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSUBMESH_H__
#define __KSSUBMESH_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsType.h"
#include "KsArray.h"
#include "KsString.h"
#include "KsVector.h"
#include "KsMatrix.h"
#include "KsQuaternion.h"
#include "KsVertexBuffer.h"
#include "KsIndexBuffer.h"
#include "KsMaterial.h"
#include "KsTexture.h"
#include "KsFace.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsSubMesh
 * @brief		サブメッシュ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsSubMesh
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
		 * 描画処理
		 */
		virtual void					draw();

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
#if 0
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
		 * インデックス数を取得する
		 * @return		インデックス数
		 */
		KsUInt16						getNumIndex() const { return m_numIndex; }

		/**
		 * サブメッシュ名を取得する
		 * @return		サブメッシュ名
		 */
		const KsString&				getName() { return m_name; }

		/**
		 * マテリアル数を取得する
		 * @return		マテリアル数
		 */
		const KsString&				getMaterialName() { return m_materialName; }

		/**
		 * テクスチャ数を取得する
		 * @return		テクスチャ数
		 */
		const KsString&				getTextureName() { return m_textureName; }
#endif

		/**
		 * 指定インデックスの頂点を取得する
		 * @param		index			インデックス
		 * @return						頂点のポインタ
		 */
		//const KsVertexBuffer*			getVertexBuffer() const { return m_pVertices[ index ]; }

		/**
		 * 指定インデックスの面を取得する
		 * @param		index			インデックス
		 * @return						面のポインタ
		 */
		//const KsIndexBuffer*				getIndexData( KsUInt16 index ) { return &m_pFaces[ index ]; }

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
		KsString						m_name;					/**< サブメッシュ名前		*/
		KsString						m_textureName;			/**< 使用テクスチャ名		*/
		KsString						m_materialName;			/**< 使用マテリアル名		*/
		KsUInt32						m_flags;				/**< フラグ					*/
		KsUInt16						m_numVertex;			/**< 頂点数					*/
		KsUInt16						m_numIndex;				/**< 面の数					*/
		KsUInt16						m_numFace;				/**< 面構成					*/
		KsVertexBuffer*					m_pVertices;			/**< 頂点データ				*/
		KsIndexBuffer*					m_pIndices;				/**< 面データ				*/
		KsFace*							m_pFaces;				/**< 面構成データ			*/
		KsMaterial*						m_pMaterials;			/**< マテリアルデータ		*/
		
};

#endif		/* __KSSUBMESH_H__ */


