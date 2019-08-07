/************************************************************************************************/
/** 
 * @file		KsModelLoader.h
 * @brief		モデルローダー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMODELLOADER_H__
#define __KSMODELLOADER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsType.h"
#include "KsMesh.h"
#include "KsVertexBuffer.h"
#include "KsRenderSystemDX.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsModelLoader
 * @brief		モデルローダー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_KMD_FILE_HEADER
{
	KsUInt32				signature;			/**< 識別用						*/
	KsUInt32				version;			/**< バージョン情報				*/
	KsUInt32				type;				/**< タイプ						*/
	KsUInt32				flags;				/**< 各種フラグ					*/

}KS_KMD_FILE_HEADER;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_KMD_VECTOR2D
{
	KsReal					x, y;				/**< 頂点座標					*/
}KS_KMD_VECTOR2D;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_KMD_VECTOR3D
{
	KsReal					x, y, z;			/**< 頂点座標					*/
}KS_KMD_VECTOR3D;


/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_KMD_VECTOR4D
{
	KsReal					x, y, z, w;			/**< 頂点座標					*/
}KS_KMD_VECTOR4D;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_KMD_BOUNDING_BOX
{
	KS_KMD_VECTOR3D			min;				/**< ボックスの頂点 min			*/
	KS_KMD_VECTOR3D			max;				/**< ボックスの頂点 max			*/
}KS_KMD_BOUNDING_BOX;

/************************************************************************************************/
/**
 * 描画面リスト
 */
/************************************************************************************************/
typedef struct _KS_KMD_FACE_LIST
{
	KsInt16				start;				/**< 描画開始インデックス			*/
	KsInt16				end;				/**< 描画終了インデックス			*/
	KsInt16				materialID;			/**< マテリアルID				*/
}KS_KMD_FACE_LIST;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_KMD_MESH
{
	KsUInt32				flags;				/**< 各種フラグ					*/
	KsUInt32				numHierarchyNode;	/**< 階層構造のノード数			*/
	KsUInt32				numSubMesh;			/**< サブメッシュの数				*/
	KsUInt32				numBone;			/**< ボーン数					*/
	KsUInt32				numPoint;			/**< NULLポイント数				*/
	KsUInt32				numMaterial;		/**< トータルマテリアル			*/
	KsUInt32				numTexture;			/**< トータルで使用するテクスチャ	*/
	KsUInt32				numAnim;			/**< アニメの数					*/
	KsUInt32				offsetHierarchy;	/**< 階層構造のオフセット位置		*/
	KsUInt32				offsetSubMesh;		/**< サブメッシュのオフセット位置	*/
	KsUInt32				offsetBone;			/**< ボーンのオフセット位置		*/
	KsUInt32				offsetPoint;		/**< NULLポイントのオフセット位置	*/
	KsUInt32				offsetMaterial;		/**< マテリアルのオフセット位置	*/
	KsUInt32				offsetTexture;		/**< テクスチャのオフセット位置	*/
	KsUInt32				offsetAnim;			/**< アニメののオフセット位置		*/
	KS_KMD_BOUNDING_BOX		bundingBox;			/**< バウンディングボックスス		*/
}KS_KMD_MESH;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_KMD_HIERARCHY_NODE
{
	KsUInt32				id;					/**< ID							*/
	KsUInt32				flags;				/**< 各種フラグ					*/
	KsUInt32				type;				// オブジェクトのタイプ(mesh,bone,pointなど)
	KsUInt32				objLink;			// 使用オブジェクトのインデックス( subMeshList の何番目を使っているかなど)
	KS_KMD_VECTOR3D			pivot;				// 基点位置( pivot )
	KS_KMD_VECTOR3D			translate;			// 位置
	KS_KMD_VECTOR4D			rotate;				// 回転(クォータニオン)
	KS_KMD_VECTOR3D			scale;				// スケール
	KsUInt32				parent;				// 親のindex( -1のときはいないroot )
	KsUInt32				numChild;			// 子の数
	//KsUInt32				children;			// 子供の数分これが存在する(可変)

}KS_KMD_HIERARCHY_NODE;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_KMD_VERTEX
{
	KS_KMD_VECTOR3D			pos;
	KS_KMD_VECTOR3D			normal;
	KS_KMD_VECTOR2D			uv;
	KsUInt32				color;
}KS_KMD_VERTEX;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_KMD_FACE
{
	KsUInt16				point[ 3 ];			/**< 頂点インデックス				*/
	KsUInt16				materialID;			/**< マテリアルID				*/
	KsUInt16				smoothGroup;		/**< スムージンググループ			*/
}KS_KMD_FACE;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_KMD_SUBMESH
{
	KsUInt32				id;					/**< ID							*/
	KsUInt32				flags;				/**< 各種フラグ					*/
	KS_KMD_BOUNDING_BOX		bundingBox;			/**< バウンディングボックスス		*/
	KsUInt32				vertexType;			/**< 頂点のタイプ				*/
	KsUInt32				faceType;			/**< index type ( 16bit, 32bit どうか)	*/
	KsUInt32				numVertex;			/**< 頂点数						*/
	KsUInt32				numFace;			/**< ポリゴン数					*/
	KsUInt32				numFaceList;		/**< 面の構成リスト数				*/
	KsUInt32				numBoneWeight;		/**< ウエイト数					*/

}KS_KMD_SUBMESH;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_KMD_WEIGHT
{
	KsInt32				index;				/**< node index				*/
	KsReal					weight;				/**< ウエイト				*/
}KS_KMD_WEIGHT;

typedef struct _KS_KMD_BONE_DATA
{
	KsInt32				vertexIndex;		/**< vertex index				*/
	KsInt32				numWeight;			/**< ウエイト数					*/
}KS_KMD_BONE_DATA;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_KMD_BONEWEIGHT
{
	KsInt32				vertexIndex;		/**< vertex index				*/
	KsInt32				numWeight;			/**< ウエイト数					*/
	KS_KMD_WEIGHT			weight[ 4 ];		/**< ウエイトデータ				*/
}KS_KMD_BONEWEIGHT;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_KMD_BONE
{
				// id
				// flags
				// start, end point
				// size など
}KS_KMD_BONE;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_KMD_COLOR
{
	KsReal		r, g, b, a;
}KS_KMD_COLOR;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_KMD_MATERIAL
{
	KS_KMD_COLOR			diffuse;		/**< ディフューズ色( 拡散光 )		*/
	KS_KMD_COLOR			ambient;		/**< アンビエント色( 環境光 )		*/
	KS_KMD_COLOR			specular;		/**< スペキュラ色( 鏡面光 )		*/
	KS_KMD_COLOR			emissive;		/**< エミッション色				*/
	KsReal					power;			/**< スペキュラ ハイライトの鮮明	*/
	KsUInt32				textureIndex;

}KS_KMD_MATERIAL;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_KMD_TEXTURE
{
	KsUInt32		size;
	//KsChar*			name;
}KS_KMD_TEXTURE;

#include "KsVertexBufferDX.h"
#include "KsIndexBufferDX.h"

typedef struct SUBMESH
{
	KsUInt32				numVertex;
	KsUInt32				numFace;
	KsVertexBufferDX*		m_pVB;
	KsIndexBufferDX*		m_pIB;
}SUBMESH;

typedef struct MESH
{
	
	KsUInt32			numSubMesh;
	SUBMESH*			pSubMesh;
	KsUInt32			numMaterial;
	KS_KMD_MATERIAL*	pMaterial;
}MESH;

extern KsMesh* KsModelLoadDX( KsRenderSystemDX* pRS, KsChar* pFileName );
extern void KsModelRenderDX( KsRenderSystemDX* pRS, KsMesh* pMesh );



class KsAnimKeyFrame
{
public:
	KsReal					m_time;			/**< フレーム再生時間		*/
	KsVector3d				m_pos;			/**< 位置座標			*/
	KsQuaternion			m_rotation;		/**< 回転				*/
	KsVector3d				m_scale;		/**< スケール			*/

	//KsAnimationTrack*		m_pParentTrack;

};

class KsAnimTrack
{
public:
	typedef std::vector<KsAnimKeyFrame*> KsAnimKeyFrameList;

	KsReal						m_maxTime;
	KsAnimKeyFrameList			m_vKeyFrames;
	KsJoint*					m_pTarget;
	//Animation*					mParent;

	KsInt32					getNumKeyFrame() const { return static_cast<KsInt32>( m_vKeyFrames.size() ); }
	KsInt32					getKeyFrame( KsReal time, KsReal *pParam, KsAnimKeyFrame* pKey1, KsAnimKeyFrame* pKey2 );
};

class KsAnim
{
public:
	typedef std::vector<KsAnimTrack*>		KsAnimTrackList;

	void					anim( KsReal time, KsMesh* pMesh );

	KsInt32				getNumTrack() const { return static_cast<KsInt32>( m_pvTracks.size() ); }

	KsAnimTrackList			m_pvTracks;			// オブジェクトごと
	KsReal					m_frameRate;		/**< フレームレート	*/
	KsReal					m_startTime;		/**< 開始時間		*/
	KsReal					m_endTime;			/**< 終了時間		*/
};

extern KsAnim* KsLoadAnim( const KsChar* pFileName );

#endif	/* __KSMODELLOADER_H__ */




#if 0

typedef enum _ksKMD_CHUNK_ID
{
	ksKMD_FILE_HEADER		= 0x1000
		// 識別用
		// バージョン情報
		// タイプ
		// 各種フラグ
	ksKMD_MESH				= 0x3000
		// num subMesh
		// num bone
		// num material
		// num texture
		// num anim
		// bounding box min, max
		ksHIERARCHY				= 0x4000
			// num hierarchy node
			ksHIERARCHY_NODE	= 0x4010
				// id
				// name
				// オブジェクトのタイプ(mesh,bone,pointなど)
				// 使用オブジェクトのインデックス( subMeshList の何番目を使っているかなど)
				// 基点位置( pivot )
				// 位置
				// 回転(クォータニオン)
				// スケール
				// 親のindex( -1のときはいないroot )
				// 子の数
				// 子のIDリスト
		ksKMD_SUBMESH			= 0x5000
			// id
			// flags
			ksKMD_BOUNDING_BOX	= 0x5100
				// min, max
			ksKMD_GEOMETRY		= 0x5200
				// num vertex
				// num face
				// vertex type
				// index type ( 16bit, 32bit どうか) 
				ksKMD_VERTEX	= 0x5210
					// 頂点のタイプ
					// [ x, y, z ], [ nx, ny, nz ], [ u, v ], matID
				ksKMD_FACE		= 0x5220
					// 面情報( index List )
			ksKMD_BONE_WEIGHT_LIST
				// num bone weight
				ksKMD_BONE_WEIGHT
					// boneID
					// vertex index
					// weight
		ksKMD_BONE	= 0x5300
			// id
			// flags
			ksKMD_BONE_GEOMETRY
				// start, end point
				// size など
		ksKMD_LOD
	
		ksKMD_MATERIAL			= 
			// material
		ksKMD_TEXTURE
			//texture file name
		ksKMD_ANIM
			// アニメーション情報
}ksCHUNK_ID;


		



typedef struct _KS_KMD_SUBMESH
{
	KsUInt32			flags;				/**< フラグ	*/
	KsUInt32			
};

class KsChunk
{
	public:
		KsUInt16			m_type;				/**< チャンクタイプ				*/
		KsUInt16			m_option;			/**< チャンクオプション			*/
		KsUInt32			m_nextOffset;		/**< 次のチャンクのオフセット	*/
		KsUInt32			m_childOffset;		/**< 下位チャンクのオフセット	*/
		KsUInt32			m_dataOffset;		/**< ブロックデータのオフセット	*/
};

KsUInt32	KsGetChunkType( KsChunk* pChunk );
KsChunk*	KsGetChunkNext( KsChunk* pChunk );
KsChunk*	KsGetChunkChild( KsChunk* pChunk );
KsUInt8*	KsGetChunkData( KsChunk* pChunk );


inline KsChunk* KsGetChunkNext( KsChunk* pChunk )
{
	return (KsChunk *)( (KsUInt8*)pChunk + pChunk->m_nextOffset );
}

inline KsChunk* KsGetChunkChild( KsChunk* pChunk )
{
	return (KsChunk *)( (KsUInt8*)pChunk + pChunk->m_childOffset );
}

inline KsUInt8* KsGetChunkData( KsChunk* pChunk )
{
	return (KsChunk *)( (KsUInt8*)pChunk + pChunk->m_dataOffset );
}


#endif

