/************************************************************************************************/
/** 
 * @file		KsGeometry.h
 * @brief		ジオメトリ生成
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSGEOMETRY_H__
#define __KSGEOMETRY_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsType.h"
#include "KsVertex.h"
#include "KsFace.h"
#include "KsMaterial.h"
#include "KsTexture.h"
#include "KsFileObject.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * ジオメトリクラス
 * @class		KsGeometry
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsGeometry : public KsRefCounter
{
	public:
		/**
		 * コンストラクタ
		 */
										KsGeometry();

		/**
		 * コンストラクタ
		 * @param		numVertices		頂点数
		 * @param		numFaces		面の数
		 * @param		numMaterials	マテリアル数
		 * @param		numTextures		テクスチャ数
		 */
										KsGeometry( KsUInt16 numVertices, KsUInt16 numFaces, KsUInt16 numMaterials, KsUInt16 numTextures );

		/**
		 * デストラクタ
		 */
		virtual						~KsGeometry();

		/**
		 * ジオメトリ生成
		 * @param		pData			データの先頭ポインタ
		 * @retval		ksTRUE			成功
		 * @retval		ksFALSE			失敗
		 */
		KsBool							create( KsByte* pData );

		/**
		 * ファイルからジオメトリを生成する
		 * @param		pFile			ファイルデータ
		 * @retval		ksTRUE			成功
		 * @retval		ksFALSE			失敗
		 */
		KsBool							create( KsFileObject* pFile );

		/**
		 * ジオメトリ生成
		 * @param		numVertices		頂点数
		 * @param		numFaces		面の数
		 * @param		numMaterials	マテリアル数
		 * @param		numTextures		テクスチャ数
		 * @retval		ksTRUE			成功
		 * @retval		ksFALSE			失敗
		 */
		KsBool							create( KsUInt16 numVertices, KsUInt16 numFaces, KsUInt16 numMaterials, KsUInt16 numTextures );

		/**
		 * ジオメトリの破棄
		 */
		void							destory();

		/**
		 *
		 */
		void							lock();

		/**
		 *
		 */
		void							unlock();

		/**
		 * ジオメトリのフラグを取得する
		 * @return		ジオメトリの各種フラグ
		 */
		KsUInt32						getFlags()	const { return m_flags; }

		/**
		 * 頂点数を取得する
		 * @return		頂点数
		 */
		KsUInt16						getNumVertices() const { return m_numVertices; }

		/**
		 * 面の数を取得する
		 * @return		面の数
		 */
		KsUInt16						getNumFaces() const { return m_numFaces; }

		/**
		 * マテリアル数を取得する
		 * @return		マテリアル数
		 */
		KsUInt16						getNumMaterials() const { return m_numMaterials; }

		/**
		 * テクスチャ数を取得する
		 * @return		テクスチャ数
		 */
		KsUInt16						getNumTexture()	const { return m_numTextures; }

		/**
		 * 指定インデックスの頂点を取得する
		 * @param		index			インデックス
		 * @return						頂点のポインタ
		 */
		const KsVertex*					getVertex( KsUInt16 index ) const { return &m_pVertices[ index ]; }

		/**
		 * 指定インデックスの面を取得する
		 * @param		index			インデックス
		 * @return						面のポインタ
		 */
		const KsFace*					getFace( KsUInt16 index ) { return &m_pFaces[ index ]; }

		/**
		 * 指定インデックスのマテリアルを取得する
		 * @param		index			インデックス
		 * @return						マテリアルのポインタ
		 */
		const KsMaterial*				getMaterial( KsUInt16 index ) { return &m_pMaterials[ index ]; }

		/**
		 * 指定インデックスのテクスチャを取得する
		 * @param		index			インデックス
		 * @return						テクスチャのポインタ
		 */
		const KsTexture*				getTexture( KsUInt16 index ) { return &m_pTextures[ index ]; }

	public:
		KsUInt32						m_id;					/**< ID					*/
		KsUInt32						m_flags;				/**< フラグ				*/
		KsUInt16						m_numVertices;			/**< 頂点数				*/
		KsUInt16						m_numFaces;				/**< 面の数				*/
		KsUInt16						m_numMaterials;			/**< マテリアル数		*/
		KsUInt16						m_numTextures;			/**< テクスチャ数		*/
		KsVertex*						m_pVertices;			/**< 頂点データ			*/
		KsFace*							m_pFaces;				/**< 面データ			*/
		KsMaterial*						m_pMaterials;			/**< マテリアルデータ		*/
		KsTexture*						m_pTextures;			/**< 参照するテクスチャ	*/
};


#endif		/* __KSGEOMETRY_H__ */
