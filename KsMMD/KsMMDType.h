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


/************************************************************************************************/
/**
 * @struct		KS_PMX_HEADER
 * @brief		PMXヘッダー
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMX_HEADER
{
	KsInt8			Magic[ 4 ];				/**< 識別コード		*/
	KsReal			Version;				/**< バージョン情報	*/
	KsUInt8			infoSize;				/**< 情報のサイズ		*/
	KsUInt8*		pInfo;					/**< 情報			*/	
};

/************************************************************************************************/
/**
 * @struct		KS_PMX_HEADER
 * @brief		PMXヘッダー
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMX_MODEL_INFO
{
	KsString		ModelName_J;			/**< モデル名			*/
	KsString		ModelName_E;			/**< モデル名英		*/
	KsString		Comment_J;				/**< コメント			*/
	KsString		Comment_E;				/**< コメント英		*/	
};

/************************************************************************************************/
/**
 * @struct		KS_PMX_DATA
 * @brief		PMX DATA
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMX_WEIGHT
{
	KsInt32		Indices[ 4 ];
	KsReal		Weight[ 4 ];
};


/************************************************************************************************/
/**
 * @struct		KS_PMX_VERTEX
 * @brief		PMX Vertex
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMX_VERTEX
{
	KsVector3d				Position;
	KsVector3d				Normal;
	KsVector2d				TextureCoord;
	KsArray<KsVector4d>		ExtTextureCoords;
	KS_PMX_WEIGHT			Weight;
	KsReal					Edge;
};

/************************************************************************************************/
/**
 * @struct		KS_PMX_MATERIAL
 * @brief		PMX Material
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMX_MATERIAL
{
	KsString		MaterialName_J;			/**< マテリアル名			*/
	KsString		MaterialName_E;			/**< マテリアル名英		*/
	KsVector4d		Diffuse;				/**< Diffuse (R,G,B,A)	*/
	KsVector3d		Specular;				/**< Specular (R,G,B)	*/
	KsReal			SpecularPower;			/**< Specular係数		*/
	KsVector3d		Ambient;				/**< Ambient (R,G,B)	*/
	KsUInt8			bitFlag;				/**< 描画フラグ(8bit)	*/
	KsVector4d		EdgeColor;				/**< エッジ色 (R,G,B,A)	*/
	KsReal			EdgeSize;				/**< エッジサイズ			*/
	KsInt32			NormalTextureIndex;		/**< 通常テクスチャ参照Index	*/
	KsInt32			SphereTextureIndex;		/**< スフィアテクスチャ参照Index 	*/
	KsInt32			ToonTextureIndex;		/**< Toonテクスチャ参照Index	*/
	KsUInt8			SphereMode;				/**< スフィアモード		*/
	KsUInt8			ToonFlag;				/**< 共有Toonフラグ		*/
	KsString		Comment;				/**< コメント				*/
	KsInt32			NumIndices;				/**< 材質に対応する面(頂点)数	*/
};

/************************************************************************************************/
/**
 * @struct		KS_PMX_IK_LINK_INFO
 * @brief		PMX Material
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMX_IK_LINK
{
	KsInt32					BoneIndex;				/**< リンクボーンのボーンIndex				*/
	KsUInt8					IsAngleLimit;			/**< 角度制限 0:OFF 1:ON					*/
	KsVector3d				AngleLimitMin;			/**< 角度制限 下限 (x,y,z) -> ラジアン角	*/
	KsVector3d				AngleLimitMax;			/**< 角度制限 上限 (x,y,z) -> ラジアン角	*/
};

/************************************************************************************************/
/**
 * @struct		KS_PMX_MATERIAL
 * @brief		PMX Material
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMX_BONE
{
	KsString				BoneName_J;				/**< ボーン名								*/
	KsString				BoneName_E;				/**< ボーン名英							*/
	KsVector3d				Position;				/**< 位置								*/
	KsInt32					Parent;					/**< 親ボーンのボーンIndex					*/
	KsInt32					Node;					/**< 変形階層								*/
	KsUInt16				bitFlag;				/**< ボーンフラグ(16bit) 各bit 0:OFF 1:ON	*/
	KsInt32					Connect;				/**< 接続先ボーンのボーンIndex				*/
	KsVector3d				Offset;					/**< 座標オフセット, ボーン位置からの相対分	*/
	KsInt32					AddParent;				/**< 付与親ボーンのボーンIndex				*/
	KsReal					AddRate;				/**< 付与率								*/
	KsVector3d				Axis;					/**< 軸の方向ベクトル						*/
	KsVector3d				AxisX;					/**< X軸の方向ベクトル						*/
	KsVector3d				AxisZ;					/**< Z軸の方向ベクトル						*/
	KsInt32					Morph;					/**< 外部親変形:1 の場合 Key値				*/
	KsInt32					IKTargetBoneIndex;		/**< IKターゲットボーンのボーンIndex		*/
	KsInt32					IKIterations;			/**< IKループ回数 (PMD及びMMD環境では255回が最大になるようです)	*/
	KsReal					IKLimit;				/**< IKループ計算時の1回あたりの制限角度 -> ラジアン角 | PMDのIK値とは4倍異なるので注意	*/
	KsInt32					IKLinkCount;			/**< IKリンク数 : 後続の要素数				*/
	KS_PMX_IK_LINK*			IKLinks;				/**< IKデータ							*/
};

/************************************************************************************************/
/**
 * @enum		ksPMX_MORPH_TYPE
 * @brief		PMX DATA
 * @version		1.0.0
 */
/************************************************************************************************/
enum ksPMX_MORPH_TYPE
{
	ksPMX_MORPH_GROUP    = 0,						/**< グループ		*/
	ksPMX_MORPH_VERTEX   = 1,						/**< 頂点		*/
	ksPMX_MORPH_BONE     = 2,						/**< ボーン		*/
	ksPMX_MORPH_UV       = 3,						/**< UV			*/
	ksPMX_MORPH_UV1      = 4,						/**< 追加UV1		*/
	ksPMX_MORPH_UV2      = 5,						/**< 追加UV2		*/
	ksPMX_MORPH_UV3      = 6,						/**< 追加UV3		*/
	ksPMX_MORPH_UV4      = 7,						/**< 追加UV4		*/
	ksPMX_MORPH_MATERIAL = 8						/**< 材質		*/
};

/************************************************************************************************/
/**
 * @struct		KS_PMX_MORPH_VERTEX
 * @brief		PMX Morph Vertex
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMX_MORPH_VERTEX
{
	KsInt32					VertexIndex;			/**< 頂点Index				*/
	KsVector3d				Offset;					/**< 座標オフセット量(x,y,z)	*/
};

/************************************************************************************************/
/**
 * @struct		KS_PMX_MORPH_VERTEX
 * @brief		PMX Morph
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMX_MORPH_UV
{
	KsInt32					VertexIndex;			/**< 頂点Index				*/
	KsVector4d				Offset;					/**< UVオフセット量(x,y,z,w) ※通常UVはz,wが不要項目になるがモーフとしてのデータ値は記録しておく	*/
};

/************************************************************************************************/
/**
 * @struct		KS_PMX_MORPH_BONE
 * @brief		PMX Morph Bone
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMX_MORPH_BONE
{
	KsInt32					BoneIndex;				/**< ボーンIndex						*/
	KsVector3d				Position;				/**< 移動量(x,y,z)					*/
	KsQuaternion			Rotation;				/**< 回転量-クォータニオン(x,y,z,w)	*/
};

/************************************************************************************************/
/**
 * @struct		KS_PMX_MORPH_MATERIAL
 * @brief		PMX Morph Material
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMX_MORPH_MATERIAL
{
	KsInt32					MaterialIndex;				/**< 材質Index			*/
	KsUInt8					Operate;					/**< 0:乗算, 1:加算		*/
	KsVector4d				Diffuse;					/**< Diffuse (R,G,B,A) - 乗算:1.0／加算:0.0 が初期値となる(同以下)		*/
	KsVector3d				Specular;					/**< Specular (R,G,B)	*/
	KsReal					SpecularPower;				/**< Specular係数		*/
	KsVector3d				Ambient;					/**< Ambient (R,G,B)	*/
	KsVector4d				EdgeColor;					/**< エッジ色 (R,G,B,A)			*/
	KsReal					EdgeSize;					/**< エッジサイズ					*/
	KsVector4d				NormalTextureCoefficient;	/**< テクスチャ係数 (R,G,B,A)		*/
	KsVector4d				SphereTextureCoefficient;	/**< スフィアテクスチャ参照Index 	*/
	KsVector4d				ToonTextureCoefficient;		/**< Toonテクスチャ参照Index		*/
};

/************************************************************************************************/
/**
 * @struct		KS_PMX_MORPH_GROUP
 * @brief		PMX グループモーフ
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMX_MORPH_GROUP
{
	KsInt32					MorphIndex;		/**< モーフIndex														*/
	KsReal					MorphRate;		/**< モーフ率	(グループモーフのモーフ値 * モーフ率 = 対象モーフのモーフ値)	*/
};

/************************************************************************************************/
/**
 * @struct		KS_PMX_MORPH
 * @brief		PMX Morph
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMX_MORPH
{
	KsString				MorphName_J;			/**< ボーン名			*/
	KsString				MorphName_E;			/**< ボーン名英		*/
	KsVector3d				Position;
	KsUInt8					Category;
	KsUInt8					Type;
	KsInt32					NumOffsetData;
	KsByte*					pData;
};

/************************************************************************************************/
/**
 * @struct		KS_PMX_DISPLAY
 * @brief		PMX Display
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMX_DISPLAY
{
	KsString				DisplayName_J;			/**< 表示名J			*/
	KsString				DisplayName_E;			/**< 表示名英			*/
	KsUInt8					FrameType;
	KsInt32					NumDisplayFrame;
	KsUInt8					ElementType;
	KsInt32					DisplayIndex;
};

/************************************************************************************************/
/**
 * @struct		KS_PMX_RIGIDBODY
 * @brief		PMX RigidBody
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMX_RIGIDBODY
{
	KsString				RigidBodyName_J;			/**< ボーン名			*/
	KsString				RigidBodyName_E;			/**< ボーン名英		*/
	KsInt32					BoneIndex;
	KsUInt8					Group;
	KsUInt16				GroupFlag;
	KsUInt8					ShapeType;
	KsVector3d				Size;
	KsVector3d				Position;			/**< 移動量(x,y,z)					*/
	KsVector3d				Rotation;			/**< 回転量(x,y,z)	*/	
	KsReal					Mass;
	KsReal					MoveDamping;
	KsReal					SpinDamping;
	KsReal					Repulsion;
	KsReal					Friction;
	KsUInt8					CalcType;

};

/************************************************************************************************/
/**
 * @struct		KS_PMX_JOINT
 * @brief		PMX Joint
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMX_JOINT
{
	KsString				JointName_J;			/**< Joint名			*/
	KsString				JointName_E;			/**< Joint名英		*/
	KsUInt8					Type;					// Joint種類 - 0:スプリング6DOF   | PMX2.0では 0 のみ(拡張用)

	KsInt32					RigidA;					/**< ボーンIndex						*/
	KsInt32					RigidB;					/**< ボーンIndex						*/
	KsVector3d				Position;				/**< 移動量(x,y,z)					*/
	KsVector3d				Rotation;				/**< 回転量-ラジアン角(x,y,z)	*/

	KsVector3d				MoveLimitMin;			/**< 移動量(x,y,z)					*/
	KsVector3d				MoveLimitMax;			/**< 移動量(x,y,z)					*/
	KsVector3d				AngleLimitMin;			/**< 回転量-ラジアン角(x,y,z)	*/
	KsVector3d				AngleLimitMax;			/**< 回転量-ラジアン角(x,y,z)	*/

	KsVector3d				SpringMove;				/**< 回転量-ラジアン角(x,y,z)	*/
	KsVector3d				SpringAngle;			/**< 回転量-ラジアン角(x,y,z)	*/
};


/************************************************************************************************/
/**
 * @struct		KS_PMX_DATA
 * @brief		PMX DATA
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMX_DATA
{
	KS_PMX_HEADER			Header;					/**<　PMX Header			*/
	KS_PMX_MODEL_INFO		ModelInfo;				/**<　モデル情報			*/
	KsInt32					NumVertex;				/**<　頂点数				*/
	KS_PMX_VERTEX*			pVertices;				/**<　頂点データ			*/
	KsInt32					NumFaces;				/**<　インデックス数		*/
	KsInt32*				Indices;				/**<　インデックスデータ	*/
	KsInt32					NumTexture;				/**<　テクスチャ数		*/
	KsString*				pTextures;				/**<　テクスチャデータ		*/
	KsInt32					NumMaterial;			/**<　マテリアル数		*/
	KS_PMX_MATERIAL*		pMaterials;				/**<　マテリアルデータ		*/
	KsInt32					NumBone;				/**<　ボーン数			*/
	KS_PMX_BONE*			pBones;					/**<　ボーンデータ		*/
	KsInt32					NumMorph;
	KS_PMX_MORPH*			pMorph;
	KsInt32					NumDisplay;
	KS_PMX_DISPLAY*			pDisplays;
	KsInt32					NumRigidBody;
	KS_PMX_RIGIDBODY*		pRigidBodies;
	KsInt32					NumJoint;
	KS_PMX_JOINT*			pJoints;
};

/************************************************************************************************/
/**
 * @enum		ksPMX_MODEL_INFO_TYPE
 * @brief		PMX DATA
 * @version		1.0.0
 */
/************************************************************************************************/
enum ksPMX_MODEL_INFO_TYPE
{
  ksPMX_MODEL_INFO_ENCODEING            = 0, // エンコード方式  | 0:UTF16 1:UTF8
  ksPMX_MODEL_INFO_TEXTURE_EXT_UV       = 1, // 追加UV数 | 0～4 詳細は頂点参照
  ksPMX_MODEL_INFO_VERTEX_INDEX_SIZE    = 2, // 頂点Indexサイズ | 1,2,4 のいずれか
  ksPMX_MODEL_INFO_TEXTURE_INDEX_SIZE   = 3, // テクスチャIndexサイズ | 1,2,4 のいずれか
  ksPMX_MODEL_INFO_MATERIAL_INDEX_SIZE  = 4, // 材質Indexサイズ | 1,2,4 のいずれか
  ksPMX_MODEL_INFO_BONE_INDEX_SIZE      = 5, // ボーンIndexサイズ | 1,2,4 のいずれか
  ksPMX_MODEL_INFO_MORPH_INDEX_SIZE     = 6, // モーフIndexサイズ | 1,2,4 のいずれか
  ksPMX_MODEL_INFO_RIGIDBODY_INDEX_SIZE = 7  // 剛体Indexサイズ | 1,2,4 のいずれか
};

/************************************************************************************************/
/**
 * @enum		ksPMX_MODEL_INFO_TYPE
 * @brief		PMX DATA
 * @version		1.0.0
 */
/************************************************************************************************/
enum ksPMX_BONE_TYPE
{
	ksPMX_BDEF1 = 0, // : int 		| 4   | ボーンのみ
	ksPMX_BDEF2 = 1, // : int,int,float 	| 4*3 | ボーン2つと、ボーン1のウェイト値(PMD方式)
	ksPMX_BDEF4 = 2, // : int*4, float*4	| 4*8 | ボーン4つと、それぞれのウェイト値。ウェイト合計が1.0である保障はしない
	ksPMX_SDEF  = 3  // : int,int,float, float3*3 | 4*12 | BDEF2に加え、SDEF用のfloat3(Vector3)が3つ。実際の計算ではさらに補正値の算出が必要(一応そのままBDEF2としても使用可能)
};

/************************************************************************************************/
/**
 * @enum		ksPMX_BONE_BIT_FLAGS
 * @brief		PMX DATA
 * @version		1.0.0
 */
/************************************************************************************************/
enum ksPMX_BONE_BIT_FLAGS
{
	ksPMX_BONE_BIT_CONNECT    = 0x0001, // : 接続先(PMD子ボーン指定)表示方法 -> 0:座標オフセットで指定 1:ボーンで指定
	ksPMX_BONE_BIT_ROT        = 0x0002, // : 回転可能
	ksPMX_BONE_BIT_MOVE       = 0x0004, // : 移動可能
	ksPMX_BONE_BIT_DISP       = 0x0008, // : 表示
	ksPMX_BONE_BIT_CTRL       = 0x0010, // : 操作可
	ksPMX_BONE_BIT_IK         = 0x0020, // : IK
	ksPMX_BONE_BIT_ADD_ROT    = 0x0100, // : 回転付与
	ksPMX_BONE_BIT_ADD_MOVE   = 0x0200, // : 移動付与
	ksPMX_BONE_BIT_AXIS       = 0x0400, // : 軸固定
	ksPMX_BONE_BIT_LOCAL_AXIS = 0x0800, // : ローカル軸
	ksPMX_BONE_BIT_PHYICS     = 0x1000, // : 物理後変形
	ksPMX_BONE_BIT_MORPH      = 0x2000  // : 外部親変形
};

/************************************************************************************************/
/**
 * @struct		KS_PMX_DATA
 * @brief		PMX DATA
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMX_BDEF1
{
	KsInt32		Index;
};

/************************************************************************************************/
/**
 * @struct		KS_PMX_DATA
 * @brief		PMX DATA
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMX_BDEF2
{
	KsInt32		Indices[ 2 ];
	KsReal		Weight;
};

/************************************************************************************************/
/**
 * @struct		KS_PMX_DATA
 * @brief		PMX DATA
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMX_BDEF4
{
	KsInt32		Indices[ 4 ];
	KsReal		Weight[ 4 ];
};

#pragma pack( pop )



#endif /* __KSMMDTYPE_H__ */



