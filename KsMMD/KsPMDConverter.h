/************************************************************************************************/
/** 
 * @file		KsPMDConverter.h
 * @brief		PMDファイル
 * @author		Tsukasa Kato
 * @date		2010/12/17
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSPMDCONVERTER_H__
#define __KSPMDCONVERTER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                          */
/*==============================================================================================*/
#include "KsMMDType.h"
/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @enum	ksDATA_CHUNK_TYPE
 * @brief	チャンクデータタイプ
 */
/************************************************************************************************/
enum ksDATA_CHUNK_TYPE
{
	ksDATA_CHUNK_MESH       = 1,
	ksDATA_CHUNK_BONE       = 2,
	ksDATA_CHUNK_TEXTURE    = 3,
	ksDATA_CHUNK_EFFECT     = 4,
	ksDATA_CHUNK_IK         = 5,
	ksDATA_CHUNK_PHYSICS    = 6,
	ksDATA_CHUNK_CONSTRAINT = 7,
	ksDATA_CHUNK_MAX
};

/************************************************************************************************/
/**
 * @struct	KS_DATA_CHUNK
 * @brief	チャンクデータ
 */
/************************************************************************************************/
class KS_DATA_CHUNK
{
	public:
		KsUInt16				Type;					/// チャンクタイプ
		KsUInt16				Count;					/// 同一チャンク数
		KsUInt32				Size;					/// データサイズ
		KsFileBuffer*			pFile;					/// データ

	public:
		/**
		 * コンストラクタ
		 */
		KS_DATA_CHUNK( ksDATA_CHUNK_TYPE chunkType, KsUInt16 count, KsUInt32 size=0 );

		/**
		 * デストラクタ
		 */
		virtual						~KS_DATA_CHUNK();

		/**
		 * ファイルに値を書き込む
		 * @param	val				書き込む値
		 * @return					書き込んだバイト数
		 */
		virtual KsSize				writeReal( KsReal val );

		/**
		 * ファイルに値を書き込む
		 * @param	val				書き込む値
		 * @return					書き込んだバイト数
		 */
		virtual KsSize				writeInt32( KsInt32 val );

		/**
		 * ファイルに値を書き込む
		 * @param	val				書き込む値
		 * @return					書き込んだバイト数
		 */
		virtual KsSize				writeUInt32( KsUInt32 val );

		/**
		 * ファイルに値を書き込む
		 * @param	val				書き込む値
		 * @return					書き込んだバイト数
		 */
		virtual KsSize				writeInt16( KsInt16 val );

		/**
		 * ファイルに値を書き込む
		 * @param	val				書き込む値
		 * @return					書き込んだバイト数
		 */
		virtual KsSize				writeUInt16( KsUInt16 val );

		/**
		 * ファイルに値を書き込む
		 * @param	val				書き込む値
		 * @return					書き込んだバイト数
		 */
		virtual KsSize				writeInt8( KsInt8 val );

		/**
		 * ファイルに値を書き込む
		 * @param	val				書き込む値
		 * @return					書き込んだバイト数
		 */
		virtual KsSize				writeUInt8( KsUInt8 val );

		/**
		 * ファイルに値を書き込む
		 * @param	val				書き込む値
		 * @return					書き込んだバイト数
		 */
		virtual KsSize				writeChar( KsChar val );

		/**
		 * ファイルに値を書き込む
		 * @param	val				書き込む値
		 * @return					書き込んだバイト数
		 */
		virtual KsSize				writeByte( KsInt32 val );

		/**
		 * バッファからファイルに値を書き込む
		 * @param	pBuffer			書き込むバッファ
		 * @param	count			書き込むバイト数
		 * @return					書き込んだバイト数
		 */
		virtual KsSize				write( const void *pBuffer, KsInt32 count );

		/**
		 * チャンクサイズを更新する
		 */
		virtual KsSize				updateSize();
};

/************************************************************************************************/
/**
 * @struct	KS_MODEL_HEADER
 * @brief	モデルヘッダー
 */
/************************************************************************************************/
struct KS_MODEL_HEADER
{
	KsInt8					Signature[ 4 ];			/// 識別コード		
	KsUInt16				Version;				/// バージョン情報
	KsUInt8					ModelName[ 24 ];		/// モデル名
	KsUInt16				ChunkCount;				/// チャンク数

	KS_MODEL_HEADER();
	KS_MODEL_HEADER( const KsString& modelName );
};

/************************************************************************************************/
/**
 * @struct	KS_MODEL_BONE
 * @brief	ボーンデータ
 */
/************************************************************************************************/
struct KS_MODEL_BONE
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
 * @struct	KS_MODEL_TEXTURE
 * @brief	テクスチャデータ
 */
/************************************************************************************************/
struct KS_MODEL_TEXTURE
{
	KsSChar					Name[ 32 ];				/// テクスチャ名
};

/************************************************************************************************/
/**
 * @struct	KS_MODEL_MMD_MATERIAL
 * @brief	マテリアルデータ
 */
/************************************************************************************************/
struct KS_MODEL_EFFECT
{
	KsUInt8					TextureName[ 32 ];		/// テクスチャ名
	KsVector4d				Diffuse;				/// ディフューズ
	KsVector4d				Ambient;				/// 環境色(ambient)
	KsVector4d				Specular;				/// スペキュラーカラー
	KsReal					Specularity;			/// スペキュラ値
};

/************************************************************************************************/
/**
 * @struct	KS_MODEL_MMD_MATERIAL
 * @brief	マテリアルデータ
 */
/************************************************************************************************/
struct KS_MODEL_MMD_MATERIAL
{
	KsUInt8					TextureName[ 32 ];	/// テクスチャ名
	KsVector4d				Diffuse;			/// ディフューズ
	KsVector4d				Ambient;			/// 環境色(ambient)
	KsVector4d				Specular;			/// スペキュラーカラー
	KsReal					Specularity;		/// スペキュラ値
};

/************************************************************************************************/
/**
 * @struct	KS_MODEL_MESH_PARTS
 * @brief	メッシュパーツデータ
 */
/************************************************************************************************/
struct KS_MODEL_MESH_PARTS
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
 * @struct	KS_MODEL_MESH
 * @brief	メッシュデータ
 */
/************************************************************************************************/
struct KS_MODEL_MESH
{
	KsUInt32						MeshPartCount;
	KsArray<KS_MODEL_MESH_PARTS*>	MeshParts;

	KS_MODEL_MESH( KsUInt32 meshPartCount );
	KS_MODEL_MESH();
	~KS_MODEL_MESH();
};

/************************************************************************************************/
/**
 * @struct	KS_MODEL_MESH
 * @brief	メッシュデータ
 */
/************************************************************************************************/
struct KS_MODEL_BONE_NAME
{
	KsSChar				Name[ 16 ];
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
struct KS_MODEL_IK_POINT
{
	KsInt16					BoneNo;
	KsUInt8					IsLimitAngle;
	KsUInt8					LimitAngleType;
};

/************************************************************************************************/
/**
 * @class		KsIKEffector
 * @brief		
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
struct KS_MODEL_IK_EFFECTOR
{
	KS_MODEL_IK_POINT			Target;
	KS_MODEL_IK_POINT			Effector;
	KsReal						ControlWeight;	// IKの影響度( IK値2 )
	KsInt16						Iterations;		// 再帰演算回数( IK値1 )
	KsUInt16					ChainCount;		//
	KS_MODEL_IK_POINT*			Chain;	
};

/************************************************************************************************/
/**
 * @struct		KS_MODEL_HUMAN_IK
 * @brief		
 */
/************************************************************************************************/
struct KS_MODEL_HUMAN_IK
{
	KsUInt32					EffectorCount;
	KS_MODEL_IK_EFFECTOR*		Effectors;
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_RIGID_BODY
 * @brief		剛体データ
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_MODEL_RIGID_BODY
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

/************************************************************************************************/
/**
 * @struct		KS_MODEL_CONSTRAINT
 * @brief		コンストレイント(ジョイント)データ
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_MODEL_CONSTRAINT
{
	KsInt8						Name[ 20 ];		/// コンストレイント名[20]
	KsUInt32					RigidA;			/// 剛体A
	KsUInt32					RigidB;			/// 剛体B
	KsVector3d					Position;		/// 位置(モデル原点中心)
	KsVector3d					Rotation;		/// 回転(radian)
	KsVector3d					PosLimitL;		/// 移動制限1
	KsVector3d					PosLimitU;		/// 移動制限2
	KsVector3d					RotLimitL;		/// 回転制限1
	KsVector3d					RotLimitU;		/// 回転制限2
	KsVector3d					SpringPos;		/// ばね移動
	KsVector3d					SpringRot;		/// ばね回転
};

/************************************************************************************************/
/**
 * @struct	KS_MODEL_DATA
 * @brief	モデルデータ
 */
/************************************************************************************************/
struct KS_MODEL_DATA
{
	KS_MODEL_HEADER						Header;
	KsArray<KS_DATA_CHUNK*>				Chunks;

	KsArray<KS_MODEL_MESH*>				Meshes;
	KsArray<KS_MODEL_MMD_MATERIAL*>		Effects;
	KsArray<KS_MODEL_BONE*>				Bones;
	KsArray<KS_MODEL_TEXTURE*>			Textures;

	KS_MODEL_DATA( const KsString& modelName );
	KS_MODEL_DATA();
	~KS_MODEL_DATA();
};


/************************************************************************************************/
/*
 * PMDファイル読み込み処理
 * @param	filePath	ファイルパス
 * @return	PMDファイルデータ
 */
/************************************************************************************************/
class KsModelConvertOption
{
public:
	KsModelConvertOption():bStaticMesh(ksTRUE), bTriStrip(ksFALSE), bDump(ksTRUE) {};

	KsBool	bStaticMesh;
	KsBool	bTriStrip;
	KsBool	bDump;
};

/************************************************************************************************/
/*
 * PMDファイル読み込み処理
 * @param	filePath	ファイルパス
 * @return	PMDファイルデータ
 */
/************************************************************************************************/
ksMMD_API KsBool KsModelConvertFromPMD( const KsString& inputFilePath, const KsString& outputFilePath, KsModelConvertOption& opt );

#endif /* __KSPMDCONVERTER_H__ */


