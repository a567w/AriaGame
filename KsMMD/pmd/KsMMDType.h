/************************************************************************************************/
/** 
 * @file		KsMMDType.h
 * @brief		MMD タイプ
 * @author		Tsukasa Kato
 * @date		2010/08/17
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSMMDTYPE_H__
#define __KSMMDTYPE_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

enum ksPMD_SHAPHE_TYPE
{
	ksPMD_SHAPHE_SPHERE  = 0,
	ksPMD_SHAPHE_BOX     = 1,
	ksPMD_SHAPHE_CAPSULE = 2
};

#pragma pack( push, 1 )

/************************************************************************************************/
/**
 * @struct		KS_MMD_VECTOR2
 * @brief		Vector2
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_MMD_VECTOR2
{
	KsReal		x;
	KsReal		y;
};

/************************************************************************************************/
/**
 * @struct		KS_MMD_VECTOR3
 * @brief		Vector3
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_MMD_VECTOR3
{
	KsReal		x;
	KsReal		y;
	KsReal		z;
};

/************************************************************************************************/
/**
 * @struct		KS_MMD_VECTOR4
 * @brief		Vector4
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_MMD_VECTOR4
{
	KsReal		x;
	KsReal		y;
	KsReal		z;
	KsReal		w;
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_BONE_NAME_DISP_LIST
 * @brief		ボーン枠用枠名リスト
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_NAME_20
{
	KsInt8					Name[ 20 ];		/// 枠名(20Bytes/枠)
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_BONE_NAME_DISP_LIST
 * @brief		ボーン枠用枠名リスト
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_NAME_50
{
	KsInt8					Name[ 50 ];		/// 枠名(50Bytes/枠)
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_NAME_100
 * @brief		ボーン枠用枠名リスト
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_NAME_100
{
	KsInt8					Name[ 100 ];	/// 枠名(100Bytes/枠)
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_BONE_NAME_DISP_LIST
 * @brief		ボーン枠用枠名リスト
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_NAME_256
{
	KsInt8					Name[ 256 ];	/// 枠名( 256Bytes/枠)
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_HEADER
 * @brief		PMDヘッダー
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_HEADER
{
	KsInt8		Magic[ 3 ];				/**< 識別コード		*/
	KsReal		Version;				/**< バージョン情報	*/
	KsInt8		ModelName[ 20 ];		/**< モデル名		*/
	KsInt8		Comment[ 256 ];			/**< コメント		*/
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_VERTEX
 * @brief		PMD頂点情報
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_VERTEX
{
	KS_MMD_VECTOR3		Pos;			/// x, y, z 座標
	KS_MMD_VECTOR3		Normal;			/// nx, ny, nz 法線ベクトル
	KS_MMD_VECTOR2		UV;				/// UV座標( MMDは頂点UV )
	KsUInt16			Bone1;			/// ボーン番号1( モデル変形(頂点移動)時に影響 )
	KsUInt16			Bone2;			/// ボーン番号2( モデル変形(頂点移動)時に影響 )
	KsUInt8				Weight;			/// ボーン1に与える影響度[min:0 max:100](ボーン2への影響度は、(100 - bone_weight) )
	KsUInt8				EdgeFlag;		/// 0:通常、1:エッジ無効( エッジ(輪郭)が有効の場合 )
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_VERTEX_LIST
 * @brief		PMD頂点情報
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_VERTEX_LIST
{
	KsUInt32			VertexCount;
	KS_PMD_VERTEX*		Vertices;
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_INDEX_LIST
 * @brief		PMD頂点情報
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_INDEX_LIST
{
	KsUInt32			IndexCount;
	KsUInt16*			Indices;
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_MATERIAL
 * @brief		PMDマテリアル
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_MATERIAL
{
	KS_MMD_VECTOR3		Diffuse;			/// 透明度
	KsReal				Alpha;				/// 透明度
	KsReal				Specularity;		/// スペキュラ値
	KS_MMD_VECTOR3		Specular;			/// スペキュラーカラー
	KS_MMD_VECTOR3		Ambient;			/// 環境色(ambient)
	KsUInt8				ToonIndex;			/// toon??.bmp(0.bmp:0xFF, 1(01).bmp:0x00…10.bmp:0x09 )
	KsUInt8				EdgeFlag;			/// 輪郭、影
	KsUInt32			FaceVertCount;		/// 面頂点数(インデックスに変換する場合は、材質0から順に加算)
	KsInt8				TextureName[ 20 ];	/// テクスチャファイル名( 20バイトぎりぎりまで使える 終端の0x00は無くても動く) 
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_MATERIAL_LIST
 * @brief		PMDマテリアルリスト
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_MATERIAL_LIST
{
	KsUInt32			MaterialCount;
	KS_PMD_MATERIAL*	Materials;
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_BONE
 * @brief		PMDボーン情報
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_BONE
{
	KsInt8				Name[ 20 ];	/// ボーン名[20]
	KsUInt16			Parent;		/// 親ボーン番号(ない場合は0xFFFF)
	KsUInt16			Tail;		/// tail位置のボーン番号(チェーン末端の場合は0xFFFF)  親：子は1：多なので、主に位置決め用
	KsUInt8				Type;		///	ボーンの種類 0:回転 1:回転と移動 2:IK 3:不明 4:IK影響下 5:回転影響下 6:IK接続先 7:非表示 8:捻り 9:回転運動
	KsUInt16			IKParent;	/// IKボーン番号(影響IKボーン。ない場合は0)
	KS_MMD_VECTOR3		HeadPos;	/// ボーンのヘッドの位置
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_BONE_LIST
 * @brief		PMDマテリアルリスト
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_BONE_LIST
{
	KsUInt16			BoneCount;
	KS_PMD_BONE*		Bones;
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_IK
 * @brief		PMD IK 情報
 * @version		1.0.0
 * @note
 *	0x00　通常ボーン(回転のみ)
 *	0x01　通常ボーン(移動可能)
 *	0x02　IKボーン(移動可能)
 *	0x03　見えない(選択可)
 *	0x04　IKボーン(回転のみ)
 *	0x05　回転追従(回転のみ)
 *	0x06　IK接続先
 *	0x07　見えない(選択不可)
 *	0x08　ひねり
 *	0x09　回転運動
 */
/************************************************************************************************/
struct KS_PMD_IK
{
	KsUInt16			BoneIndex;			/// IKボーン番号
	KsUInt16			TargetBoneIndex;	/// IKターゲットボーン番号( IKボーンが最初に接続するボーン )
	KsUInt8				ChainLength;		/// IKチェーンの長さ(子の数)
	KsUInt16			Iterations;			/// 再帰演算回数( IK値1 )
	KsReal				ControlWeight;		///  IKの影響度( IK値2 )
	KsUInt16*			ChildBoneIndices;	/// IK影響下のボーン番号(ChainLength)
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_IK_LIST
 * @brief		PMDIKリスト
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_IK_LIST
{
	KsUInt16			IKCount;
	KS_PMD_IK*			IKList;
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_FACIAL_VERTEX
 * @brief		表情データの頂点情報
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_FACIAL_VERTEX
{
	KsUInt32				Index;			/// 表情用の頂点の番号(baseの番号。Index)	
	KS_MMD_VECTOR3			Pos;			/// 頂点位置
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_FACIAL
 * @brief		表情データ
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_FACIAL
{
	KsInt8					Name[ 20 ];		/// 表情名[20]
	KsUInt32				VertexCount;	/// 表情用の頂点数
	KsUInt8					Type;			/// 表情の種類( 0：base、1：まゆ、2：目、3：リップ、4：その他 )
	KS_PMD_FACIAL_VERTEX*	Vertices;		/// 表情用の頂点のデータ(16Bytes/vert)
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_FACIAL_LIST
 * @brief		表情データ
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_FACIAL_LIST
{
	KsUInt16				FacialCount;
	KS_PMD_FACIAL*			FacialList;
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_RIGID_BODY
 * @brief		剛体データ
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_RIGID_BODY
{
	KsInt8				Name[ 20 ];		/// 剛体名[20]
	KsUInt16			BoneIndex;		/// 関連ボーン番号
	KsUInt8				ColGroupIndex;	/// 衝突グループ
	KsUInt16			ColGroupMask;	/// 衝突グループマスク
	KsUInt8				ShapeType;		/// 形状  0:球 1:箱 2:カプセル
	KsReal				Width;			/// 半径(幅)
	KsReal				Height;			/// 高さ
	KsReal				Depth;			/// 奥行
	KS_MMD_VECTOR3		Position;		/// 位置(ボーン相対)
	KS_MMD_VECTOR3		Rotation;		/// 回転(radian)
	KsReal				Mass;			/// 質量
	KsReal				LinearDamping;	/// 移動ダンパー
	KsReal				AngularDamping;	/// 回転減
	KsReal				Restitution;	/// 反発力
	KsReal				Friction;		/// 摩擦力
	KsUInt8				RigidBodyType;	/// タイプ 0:Bone追従 1:物理演算 2:物理演算(Bone位置合せ)
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_RIGID_BODY_LIST
 * @brief		剛体データ
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_RIGID_BODY_LIST
{
	KsUInt32			RigidBodyCount;
	KS_PMD_RIGID_BODY*	RigidBodyList;
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_CONSTRAINT
 * @brief		コンストレイント(ジョイント)データ
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_CONSTRAINT
{
	KsInt8				Name[ 20 ];		/// コンストレイント名[20]
	KsUInt32			RigidA;			/// 剛体A
	KsUInt32			RigidB;			/// 剛体B
	KS_MMD_VECTOR3		Position;		/// 位置(モデル原点中心)
	KS_MMD_VECTOR3		Rotation;		/// 回転(radian)
	KS_MMD_VECTOR3		PosLimitL;		/// 移動制限1
	KS_MMD_VECTOR3		PosLimitU;		/// 移動制限2
	KS_MMD_VECTOR3		RotLimitL;		/// 回転制限1
	KS_MMD_VECTOR3		RotLimitU;		/// 回転制限2
	KS_MMD_VECTOR3		SpringPos;		/// ばね移動
	KS_MMD_VECTOR3		SpringRot;		/// ばね回転
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_CONSTRAINT_LIST
 * @brief		コンストレイント(ジョイント)データ
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_CONSTRAINT_LIST
{
	KsUInt32			ConstraintCount;
	KS_PMD_CONSTRAINT*	ConstraintList;
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_FACIAL_DISP_LIST
 * @brief		表情枠に表示する表情リスト
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_FACIAL_DISP_LIST
{
	KsUInt8					DispCount;			/// 表情枠に表示する表情数
	KsUInt16*				FacialIndices;		/// 表情枠用表示リスト( 表情番号)
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_BONE_NAME_DISP_LIST
 * @brief		ボーン枠用枠名リスト
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_BONE_NAME_DISP_LIST
{
	KsUInt8					DispCount;		/// ボーン枠用の枠名数
	KS_PMD_NAME_50*			Names;			/// 枠名(50Bytes/枠)
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_BONE_DISP
 * @brief		ボーン表示
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_BONE_DISP
{
	KsUInt16				BoneIndex;		/// ボーンインデックス
	KsUInt8					FrameIndex;		/// フレームインデックス
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_BONE_DISP_LIST
 * @brief		ボーン枠用枠名リスト
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_BONE_DISP_LIST
{
	KsUInt32				DispCount;		/// ボーン枠用の枠名数
	KS_PMD_BONE_DISP*		BoneDisp;		/// 枠名(50Bytes/枠)
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_TOON_TEXTURE_NAME_LIST
 * @brief		トゥーンテクスチャ名リスト
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_TOON_TEXTURE_NAME_LIST
{
	KS_PMD_NAME_100			Names[ 10 ];		/// トゥーンテクスチャ名リスト
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_DATA
 * @brief		PMDデータ
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_DATA
{
	KS_PMD_HEADER					Header;
	KS_PMD_VERTEX_LIST				VertexList;
	KS_PMD_INDEX_LIST				IndexList;
	KS_PMD_MATERIAL_LIST			MaterialList;
	KS_PMD_BONE_LIST				BoneList;
	KS_PMD_IK_LIST					IKList;
	KS_PMD_FACIAL_LIST				FacialList;
	KS_PMD_FACIAL_DISP_LIST			FacialDispList;
	KS_PMD_BONE_NAME_DISP_LIST		BoneNameDispList;
	KS_PMD_BONE_DISP_LIST			BoneDispList;
	KS_PMD_TOON_TEXTURE_NAME_LIST	ToonTextureNameList;
	KS_PMD_RIGID_BODY_LIST			RigidBodyList;
	KS_PMD_CONSTRAINT_LIST			ConstraintList;
};


#pragma pack( pop )



#endif /* __KSMMDTYPE_H__ */



