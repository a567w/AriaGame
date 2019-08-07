/************************************************************************************************/
/** 
 * @file		KsKMD.h
 * @brief		KMDファイル
 * @author		Tsukasa Kato
 * @date		2010/12/17
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSKMD_H__
#define __KSKMD_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
#include "KsMMDType.h"


/************************************************************************************************/
/**
 * @enum	ksKMD_CHUNK_TYPE
 * @brief	チャンクデータタイプ
 */
/************************************************************************************************/
enum ksKMD_CHUNK_TYPE
{
	ksKMD_CHUNK_MESH    = 1,
	ksKMD_CHUNK_BONE    = 2,
	ksKMD_CHUNK_TEXTURE = 3,
	ksKMD_CHUNK_EFFECT  = 4,
	ksKMD_CHUNK_IK      = 5,
	ksKMD_CHUNK_PHYSICS = 6,
};

/************************************************************************************************/
/**
 * @struct	KS_KMD_CHUNK
 * @brief	チャンクデータ
 */
/************************************************************************************************/
struct KS_KMD_CHUNK
{
	KsUInt16				Type;					/// チャンクタイプ
	KsUInt16				Count;					/// 同一チャンク数
	KsUInt32				Size;					/// データサイズ
};

/************************************************************************************************/
/**
 * @struct	KS_KMD_HEADER
 * @brief	モデルヘッダー
 */
/************************************************************************************************/
struct KS_KMD_HEADER
{
	KsInt8					Signature[ 4 ];			/// 識別コード		
	KsUInt16				Version;				/// バージョン情報
	KsUInt8					ModelName[ 24 ];		/// モデル名
	KsUInt16				ChunkCount;				/// チャンク数
};

/************************************************************************************************/
/**
 * @struct	KS_KMD_BONE
 * @brief	ボーンデータ
 */
/************************************************************************************************/
struct KS_KMD_BONE
{
	KsSChar					Name[ 32 ];				/// ボーン名
	KsInt32					Index;					/// ボーンのインデックス
	KsInt32					Parent;					/// 親ボーンのインデックス
	KsInt32					ChildCount;				/// 子ボーン数
	KsVector3d				Position;				/// ボーン位置
	KsQuaternion			Rotation;				/// ボーン回転
};

/************************************************************************************************/
/**
 * @struct	KS_KMD_TEXTURE
 * @brief	テクスチャデータ
 */
/************************************************************************************************/
struct KS_KMD_TEXTURE
{
	KsChar					Name[ 32 ];				/// テクスチャ名
};

/************************************************************************************************/
/**
 * @struct	KS_KMD_MMD_MATERIAL
 * @brief	マテリアルデータ
 */
/************************************************************************************************/
struct KS_KMD_EFFECT
{
	KsUInt8					TextureName[ 32 ];		/// テクスチャ名
	KsVector4d				Diffuse;				/// ディフューズ
	KsVector4d				Ambient;				/// 環境色(ambient)
	KsVector4d				Specular;				/// スペキュラーカラー
	KsReal					Specularity;			/// スペキュラ値
};

/************************************************************************************************/
/**
 * @struct	KS_KMD_MMD_MATERIAL
 * @brief	マテリアルデータ
 */
/************************************************************************************************/
struct KS_KMD_MMD_MATERIAL
{
	KsUInt8					TextureName[ 32 ];	/// テクスチャ名
	KsVector4d				Diffuse;			/// ディフューズ
	KsVector4d				Ambient;			/// 環境色(ambient)
	KsVector4d				Specular;			/// スペキュラーカラー
	KsReal					Specularity;		/// スペキュラ値
};

/************************************************************************************************/
/**
 * @struct	KS_KMD_MESH_PARTS
 * @brief	メッシュパーツデータ
 */
/************************************************************************************************/
struct KS_KMD_MESH_PARTS
{
	KsUInt32				MeshPartsSize;		/// メッシュパーツデータサイズ
	KsUInt32				IndexType;			/// 頂点インデックスのタイプ
	KsUInt32				IndexCount;			/// 頂点インデックス数
	KsUInt32				IndexSize;			/// 頂点インデックスサイズ
	KsByte*					IndexData;			/// 頂点インデックスデータ

	KsUInt32				VertexType;			/// 頂点データのタイプ
	KsUInt32				VertexCount;		/// 頂点データの数
	KsUInt32				VertexSize;			/// 頂点サイズ
	KsByte*					VertexData;			/// 頂点データ

	KsInt32					PrimitiveCount;		/// レンダリングするプリミティブの数
	KsUInt32				StartIndex;			/// インデックス配列の中で頂点の読み取りを開始する位置
	KsUInt32				StartVertex;		/// 頂点バッファーの最上部からのオフセット
	KsUInt32				EffectID;			/// エフェクトID
	KsUInt32				MatrixPalletCount;	/// 使用マトリックスパレット数
	KsInt32*				MatrixPalletData;	/// 使用マトリックスパレット
	KsUInt32				BoneCount;			/// ボーン数
	KsInt32*				BoneData;			/// ボーンデータ
};

/************************************************************************************************/
/**
 * @struct	KS_KMD_MESH
 * @brief	メッシュデータ
 */
/************************************************************************************************/
struct KS_KMD_MESH
{
	KsUInt32				MeshPartCount;
	KS_KMD_MESH_PARTS*		MeshParts;
};

/************************************************************************************************/
/**
 * @class		KsIKPoint
 * @brief		
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
struct KS_KMD_IK_POINT
{
	KsInt16					BoneNo;
	KsUInt8					IsLimitAngle;
	KsUInt8					LimitAngleType;
};

/************************************************************************************************/
/**
 * @class		KS_KMD_IK_EFFECTOR
 * @brief		
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
struct KS_KMD_IK_EFFECTOR
{
	KS_KMD_IK_POINT			Target;
	KS_KMD_IK_POINT			Effector;
	KsReal					ControlWeight;	// IKの影響度( IK値2 )
	KsInt16					Iterations;		// 再帰演算回数( IK値1 )
	KsUInt16				ChainCount;		//
	KS_KMD_IK_POINT*		Chain;	
};

/************************************************************************************************/
/**
 * @struct		KS_KMD_HUMAN_IK
 * @brief		
 */
/************************************************************************************************/
struct KS_KMD_HUMAN_IK
{
	KsUInt32				EffectorCount;
	KS_KMD_IK_EFFECTOR*		Effectors;
};


/************************************************************************************************/
/**
 * @struct		KS_PMD_RIGID_BODY
 * @brief		剛体データ
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_KMD_RIGID_BODY
{
	KsInt8				Name[ 20 ];		/// 剛体名[20]
	KsUInt16			BoneIndex;		/// 関連ボーン番号
	KsUInt8				ColGroupIndex;	/// 衝突グループ
	KsUInt16			ColGroupMask;	/// 衝突グループマスク
	KsUInt8				ShapeType;		/// 形状  0:球 1:箱 2:カプセル
	KsReal				Width;			/// 半径(幅)
	KsReal				Height;			/// 高さ
	KsReal				Depth;			/// 奥行
	KsReal				Position[3];	/// 位置(ボーン相対)
	KsReal				Rotation[3];	/// 回転(radian)
	KsReal				Mass;			/// 質量
	KsReal				LinearDamping;	/// 移動ダンパー
	KsReal				AngularDamping;	/// 回転減
	KsReal				Restitution;	/// 反発力
	KsReal				Friction;		/// 摩擦力
	KsUInt8				RigidBodyType;	/// タイプ 0:Bone追従 1:物理演算 2:物理演算(Bone位置合せ)
};

/*************************************************************************************************/
/*
 * PMDファイル読み込み処理
 * @param	filePath	ファイルパス
 * @return	PMDファイルデータ
 */
/*************************************************************************************************/
class ksMMD_API KsKmdLoader
{
	public:
		KsKmdLoader( KsFileObject* pFile );

		KsModel*					createModel();

	private:
		KsMesh*						readMesh( KsModel* pModel );

		void						readBones( KsModel* pModel, KsUInt16 count );
		void						readEffects( KsModel* pModel, KsUInt16 count );
		void						readTextures( KsModel* pModel, KsUInt16 count );
		void						readHumanIK( KsModel* pModel, KsUInt16 count );
		void						readPhysics( KsModel* pModel, KsUInt16 count );

		KsBone*						readBone();
		KsEffect*					readEffect( KsModel* pModel );
		KsTexture*					readTexture();

	private:
		KsFileObject*				m_pFile;
		KsRenderSystem*				m_pRenderSystem;
		KsHardwareBufferManager*	m_pBufferManager;
		KsShaderManager*			m_pShaderManager;
		KsInputLayoutManager*		m_pInputLayoutManager;
		KsVertexShader*				m_pVS;
		KsPixelShader*				m_pPS;
		KsInputLayout*				m_pIL;
		KsConstantBuffer*			m_pCB;
		KsConstantBuffer*			m_pMB;
		KsString					m_DataPath;
		KsModel*					m_pModel;
		KsHumanIK*					m_pHumanIK;
		KsPhysicsController*		m_pPhysics;
};


/*************************************************************************************************/
/*
 * PMDファイル読み込み処理
 * @param	filePath	ファイルパス
 * @return	PMDファイルデータ
 */
/*************************************************************************************************/
ksMMD_API KsModel*	KsModelCreateFromKMD( KsFileObject* pFile );

/*************************************************************************************************/
/*
 * PMDファイル読み込み処理
 * @param	filePath	ファイルパス
 * @return	PMDファイルデータ
 */
/*************************************************************************************************/
ksMMD_API KsModel*	KsModelCreateFromKMD( const KsString& filePath );

/*************************************************************************************************/
/*
 * PMDファイル読み込み処理
 * @param	filePath	ファイルパス
 * @return	PMDファイルデータ
 */
/*************************************************************************************************/
ksMMD_API KsActor* KsActorCreateFromKMD( const KsString& filePath );


#endif /* __KSKMD_H__ */


