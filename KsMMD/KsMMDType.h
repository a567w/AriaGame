/************************************************************************************************/
/** 
 * @file		KsMMDType.h
 * @brief		MMD �^�C�v
 * @author		Tsukasa Kato
 * @date		2010/08/17
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSMMDTYPE_H__
#define __KSMMDTYPE_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
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
 * @brief		�{�[���g�p�g�����X�g
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_NAME_20
{
	KsInt8					Name[ 20 ];		/// �g��(20Bytes/�g)
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_BONE_NAME_DISP_LIST
 * @brief		�{�[���g�p�g�����X�g
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_NAME_50
{
	KsInt8					Name[ 50 ];		/// �g��(50Bytes/�g)
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_NAME_100
 * @brief		�{�[���g�p�g�����X�g
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_NAME_100
{
	KsInt8					Name[ 100 ];	/// �g��(100Bytes/�g)
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_BONE_NAME_DISP_LIST
 * @brief		�{�[���g�p�g�����X�g
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_NAME_256
{
	KsInt8					Name[ 256 ];	/// �g��( 256Bytes/�g)
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_HEADER
 * @brief		PMD�w�b�_�[
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_HEADER
{
	KsInt8		Magic[ 3 ];				/**< ���ʃR�[�h		*/
	KsReal		Version;				/**< �o�[�W�������	*/
	KsInt8		ModelName[ 20 ];		/**< ���f����		*/
	KsInt8		Comment[ 256 ];			/**< �R�����g		*/
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_VERTEX
 * @brief		PMD���_���
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_VERTEX
{
	KS_MMD_VECTOR3		Pos;			/// x, y, z ���W
	KS_MMD_VECTOR3		Normal;			/// nx, ny, nz �@���x�N�g��
	KS_MMD_VECTOR2		UV;				/// UV���W( MMD�͒��_UV )
	KsUInt16			Bone1;			/// �{�[���ԍ�1( ���f���ό`(���_�ړ�)���ɉe�� )
	KsUInt16			Bone2;			/// �{�[���ԍ�2( ���f���ό`(���_�ړ�)���ɉe�� )
	KsUInt8				Weight;			/// �{�[��1�ɗ^����e���x[min:0 max:100](�{�[��2�ւ̉e���x�́A(100 - bone_weight) )
	KsUInt8				EdgeFlag;		/// 0:�ʏ�A1:�G�b�W����( �G�b�W(�֊s)���L���̏ꍇ )
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_VERTEX_LIST
 * @brief		PMD���_���
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
 * @brief		PMD���_���
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
 * @brief		PMD�}�e���A��
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_MATERIAL
{
	KS_MMD_VECTOR3		Diffuse;			/// �����x
	KsReal				Alpha;				/// �����x
	KsReal				Specularity;		/// �X�y�L�����l
	KS_MMD_VECTOR3		Specular;			/// �X�y�L�����[�J���[
	KS_MMD_VECTOR3		Ambient;			/// ���F(ambient)
	KsUInt8				ToonIndex;			/// toon??.bmp(0.bmp:0xFF, 1(01).bmp:0x00�c10.bmp:0x09 )
	KsUInt8				EdgeFlag;			/// �֊s�A�e
	KsUInt32			FaceVertCount;		/// �ʒ��_��(�C���f�b�N�X�ɕϊ�����ꍇ�́A�ގ�0���珇�ɉ��Z)
	KsInt8				TextureName[ 20 ];	/// �e�N�X�`���t�@�C����( 20�o�C�g���肬��܂Ŏg���� �I�[��0x00�͖����Ă�����) 
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_MATERIAL_LIST
 * @brief		PMD�}�e���A�����X�g
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
 * @brief		PMD�{�[�����
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_BONE
{
	KsInt8				Name[ 20 ];	/// �{�[����[20]
	KsUInt16			Parent;		/// �e�{�[���ԍ�(�Ȃ��ꍇ��0xFFFF)
	KsUInt16			Tail;		/// tail�ʒu�̃{�[���ԍ�(�`�F�[�����[�̏ꍇ��0xFFFF)  �e�F�q��1�F���Ȃ̂ŁA��Ɉʒu���ߗp
	KsUInt8				Type;		///	�{�[���̎�� 0:��] 1:��]�ƈړ� 2:IK 3:�s�� 4:IK�e���� 5:��]�e���� 6:IK�ڑ��� 7:��\�� 8:�P�� 9:��]�^��
	KsUInt16			IKParent;	/// IK�{�[���ԍ�(�e��IK�{�[���B�Ȃ��ꍇ��0)
	KS_MMD_VECTOR3		HeadPos;	/// �{�[���̃w�b�h�̈ʒu
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_BONE_LIST
 * @brief		PMD�}�e���A�����X�g
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
 * @brief		PMD IK ���
 * @version		1.0.0
 * @note
 *	0x00�@�ʏ�{�[��(��]�̂�)
 *	0x01�@�ʏ�{�[��(�ړ��\)
 *	0x02�@IK�{�[��(�ړ��\)
 *	0x03�@�����Ȃ�(�I����)
 *	0x04�@IK�{�[��(��]�̂�)
 *	0x05�@��]�Ǐ](��]�̂�)
 *	0x06�@IK�ڑ���
 *	0x07�@�����Ȃ�(�I��s��)
 *	0x08�@�Ђ˂�
 *	0x09�@��]�^��
 */
/************************************************************************************************/
struct KS_PMD_IK
{
	KsUInt16			BoneIndex;			/// IK�{�[���ԍ�
	KsUInt16			TargetBoneIndex;	/// IK�^�[�Q�b�g�{�[���ԍ�( IK�{�[�����ŏ��ɐڑ�����{�[�� )
	KsUInt8				ChainLength;		/// IK�`�F�[���̒���(�q�̐�)
	KsUInt16			Iterations;			/// �ċA���Z��( IK�l1 )
	KsReal				ControlWeight;		///  IK�̉e���x( IK�l2 )
	KsUInt16*			ChildBoneIndices;	/// IK�e�����̃{�[���ԍ�(ChainLength)
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_IK_LIST
 * @brief		PMDIK���X�g
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
 * @brief		�\��f�[�^�̒��_���
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_FACIAL_VERTEX
{
	KsUInt32				Index;			/// �\��p�̒��_�̔ԍ�(base�̔ԍ��BIndex)	
	KS_MMD_VECTOR3			Pos;			/// ���_�ʒu
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_FACIAL
 * @brief		�\��f�[�^
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_FACIAL
{
	KsInt8					Name[ 20 ];		/// �\�[20]
	KsUInt32				VertexCount;	/// �\��p�̒��_��
	KsUInt8					Type;			/// �\��̎��( 0�Fbase�A1�F�܂�A2�F�ځA3�F���b�v�A4�F���̑� )
	KS_PMD_FACIAL_VERTEX*	Vertices;		/// �\��p�̒��_�̃f�[�^(16Bytes/vert)
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_FACIAL_LIST
 * @brief		�\��f�[�^
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
 * @brief		���̃f�[�^
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_RIGID_BODY
{
	KsInt8				Name[ 20 ];		/// ���̖�[20]
	KsUInt16			BoneIndex;		/// �֘A�{�[���ԍ�
	KsUInt8				ColGroupIndex;	/// �Փ˃O���[�v
	KsUInt16			ColGroupMask;	/// �Փ˃O���[�v�}�X�N
	KsUInt8				ShapeType;		/// �`��  0:�� 1:�� 2:�J�v�Z��
	KsReal				Width;			/// ���a(��)
	KsReal				Height;			/// ����
	KsReal				Depth;			/// ���s
	KS_MMD_VECTOR3		Position;		/// �ʒu(�{�[������)
	KS_MMD_VECTOR3		Rotation;		/// ��](radian)
	KsReal				Mass;			/// ����
	KsReal				LinearDamping;	/// �ړ��_���p�[
	KsReal				AngularDamping;	/// ��]��
	KsReal				Restitution;	/// ������
	KsReal				Friction;		/// ���C��
	KsUInt8				RigidBodyType;	/// �^�C�v 0:Bone�Ǐ] 1:�������Z 2:�������Z(Bone�ʒu����)
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_RIGID_BODY_LIST
 * @brief		���̃f�[�^
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
 * @brief		�R���X�g���C���g(�W���C���g)�f�[�^
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_CONSTRAINT
{
	KsInt8				Name[ 20 ];		/// �R���X�g���C���g��[20]
	KsUInt32			RigidA;			/// ����A
	KsUInt32			RigidB;			/// ����B
	KS_MMD_VECTOR3		Position;		/// �ʒu(���f�����_���S)
	KS_MMD_VECTOR3		Rotation;		/// ��](radian)
	KS_MMD_VECTOR3		PosLimitL;		/// �ړ�����1
	KS_MMD_VECTOR3		PosLimitU;		/// �ړ�����2
	KS_MMD_VECTOR3		RotLimitL;		/// ��]����1
	KS_MMD_VECTOR3		RotLimitU;		/// ��]����2
	KS_MMD_VECTOR3		SpringPos;		/// �΂ˈړ�
	KS_MMD_VECTOR3		SpringRot;		/// �΂ˉ�]
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_CONSTRAINT_LIST
 * @brief		�R���X�g���C���g(�W���C���g)�f�[�^
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
 * @brief		�\��g�ɕ\������\��X�g
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_FACIAL_DISP_LIST
{
	KsUInt8					DispCount;			/// �\��g�ɕ\������\�
	KsUInt16*				FacialIndices;		/// �\��g�p�\�����X�g( �\��ԍ�)
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_BONE_NAME_DISP_LIST
 * @brief		�{�[���g�p�g�����X�g
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_BONE_NAME_DISP_LIST
{
	KsUInt8					DispCount;		/// �{�[���g�p�̘g����
	KS_PMD_NAME_50*			Names;			/// �g��(50Bytes/�g)
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_BONE_DISP
 * @brief		�{�[���\��
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_BONE_DISP
{
	KsUInt16				BoneIndex;		/// �{�[���C���f�b�N�X
	KsUInt8					FrameIndex;		/// �t���[���C���f�b�N�X
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_BONE_DISP_LIST
 * @brief		�{�[���g�p�g�����X�g
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_BONE_DISP_LIST
{
	KsUInt32				DispCount;		/// �{�[���g�p�̘g����
	KS_PMD_BONE_DISP*		BoneDisp;		/// �g��(50Bytes/�g)
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_TOON_TEXTURE_NAME_LIST
 * @brief		�g�D�[���e�N�X�`�������X�g
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMD_TOON_TEXTURE_NAME_LIST
{
	KS_PMD_NAME_100			Names[ 10 ];		/// �g�D�[���e�N�X�`�������X�g
};

/************************************************************************************************/
/**
 * @struct		KS_PMD_DATA
 * @brief		PMD�f�[�^
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
 * @brief		PMX�w�b�_�[
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMX_HEADER
{
	KsInt8			Magic[ 4 ];				/**< ���ʃR�[�h		*/
	KsReal			Version;				/**< �o�[�W�������	*/
	KsUInt8			infoSize;				/**< ���̃T�C�Y		*/
	KsUInt8*		pInfo;					/**< ���			*/	
};

/************************************************************************************************/
/**
 * @struct		KS_PMX_HEADER
 * @brief		PMX�w�b�_�[
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMX_MODEL_INFO
{
	KsString		ModelName_J;			/**< ���f����			*/
	KsString		ModelName_E;			/**< ���f�����p		*/
	KsString		Comment_J;				/**< �R�����g			*/
	KsString		Comment_E;				/**< �R�����g�p		*/	
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
	KsString		MaterialName_J;			/**< �}�e���A����			*/
	KsString		MaterialName_E;			/**< �}�e���A�����p		*/
	KsVector4d		Diffuse;				/**< Diffuse (R,G,B,A)	*/
	KsVector3d		Specular;				/**< Specular (R,G,B)	*/
	KsReal			SpecularPower;			/**< Specular�W��		*/
	KsVector3d		Ambient;				/**< Ambient (R,G,B)	*/
	KsUInt8			bitFlag;				/**< �`��t���O(8bit)	*/
	KsVector4d		EdgeColor;				/**< �G�b�W�F (R,G,B,A)	*/
	KsReal			EdgeSize;				/**< �G�b�W�T�C�Y			*/
	KsInt32			NormalTextureIndex;		/**< �ʏ�e�N�X�`���Q��Index	*/
	KsInt32			SphereTextureIndex;		/**< �X�t�B�A�e�N�X�`���Q��Index 	*/
	KsInt32			ToonTextureIndex;		/**< Toon�e�N�X�`���Q��Index	*/
	KsUInt8			SphereMode;				/**< �X�t�B�A���[�h		*/
	KsUInt8			ToonFlag;				/**< ���LToon�t���O		*/
	KsString		Comment;				/**< �R�����g				*/
	KsInt32			NumIndices;				/**< �ގ��ɑΉ������(���_)��	*/
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
	KsInt32					BoneIndex;				/**< �����N�{�[���̃{�[��Index				*/
	KsUInt8					IsAngleLimit;			/**< �p�x���� 0:OFF 1:ON					*/
	KsVector3d				AngleLimitMin;			/**< �p�x���� ���� (x,y,z) -> ���W�A���p	*/
	KsVector3d				AngleLimitMax;			/**< �p�x���� ��� (x,y,z) -> ���W�A���p	*/
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
	KsString				BoneName_J;				/**< �{�[����								*/
	KsString				BoneName_E;				/**< �{�[�����p							*/
	KsVector3d				Position;				/**< �ʒu								*/
	KsInt32					Parent;					/**< �e�{�[���̃{�[��Index					*/
	KsInt32					Node;					/**< �ό`�K�w								*/
	KsUInt16				bitFlag;				/**< �{�[���t���O(16bit) �ebit 0:OFF 1:ON	*/
	KsInt32					Connect;				/**< �ڑ���{�[���̃{�[��Index				*/
	KsVector3d				Offset;					/**< ���W�I�t�Z�b�g, �{�[���ʒu����̑��Ε�	*/
	KsInt32					AddParent;				/**< �t�^�e�{�[���̃{�[��Index				*/
	KsReal					AddRate;				/**< �t�^��								*/
	KsVector3d				Axis;					/**< ���̕����x�N�g��						*/
	KsVector3d				AxisX;					/**< X���̕����x�N�g��						*/
	KsVector3d				AxisZ;					/**< Z���̕����x�N�g��						*/
	KsInt32					Morph;					/**< �O���e�ό`:1 �̏ꍇ Key�l				*/
	KsInt32					IKTargetBoneIndex;		/**< IK�^�[�Q�b�g�{�[���̃{�[��Index		*/
	KsInt32					IKIterations;			/**< IK���[�v�� (PMD�y��MMD���ł�255�񂪍ő�ɂȂ�悤�ł�)	*/
	KsReal					IKLimit;				/**< IK���[�v�v�Z����1�񂠂���̐����p�x -> ���W�A���p | PMD��IK�l�Ƃ�4�{�قȂ�̂Œ���	*/
	KsInt32					IKLinkCount;			/**< IK�����N�� : �㑱�̗v�f��				*/
	KS_PMX_IK_LINK*			IKLinks;				/**< IK�f�[�^							*/
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
	ksPMX_MORPH_GROUP    = 0,						/**< �O���[�v		*/
	ksPMX_MORPH_VERTEX   = 1,						/**< ���_		*/
	ksPMX_MORPH_BONE     = 2,						/**< �{�[��		*/
	ksPMX_MORPH_UV       = 3,						/**< UV			*/
	ksPMX_MORPH_UV1      = 4,						/**< �ǉ�UV1		*/
	ksPMX_MORPH_UV2      = 5,						/**< �ǉ�UV2		*/
	ksPMX_MORPH_UV3      = 6,						/**< �ǉ�UV3		*/
	ksPMX_MORPH_UV4      = 7,						/**< �ǉ�UV4		*/
	ksPMX_MORPH_MATERIAL = 8						/**< �ގ�		*/
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
	KsInt32					VertexIndex;			/**< ���_Index				*/
	KsVector3d				Offset;					/**< ���W�I�t�Z�b�g��(x,y,z)	*/
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
	KsInt32					VertexIndex;			/**< ���_Index				*/
	KsVector4d				Offset;					/**< UV�I�t�Z�b�g��(x,y,z,w) ���ʏ�UV��z,w���s�v���ڂɂȂ邪���[�t�Ƃ��Ẵf�[�^�l�͋L�^���Ă���	*/
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
	KsInt32					BoneIndex;				/**< �{�[��Index						*/
	KsVector3d				Position;				/**< �ړ���(x,y,z)					*/
	KsQuaternion			Rotation;				/**< ��]��-�N�H�[�^�j�I��(x,y,z,w)	*/
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
	KsInt32					MaterialIndex;				/**< �ގ�Index			*/
	KsUInt8					Operate;					/**< 0:��Z, 1:���Z		*/
	KsVector4d				Diffuse;					/**< Diffuse (R,G,B,A) - ��Z:1.0�^���Z:0.0 �������l�ƂȂ�(���ȉ�)		*/
	KsVector3d				Specular;					/**< Specular (R,G,B)	*/
	KsReal					SpecularPower;				/**< Specular�W��		*/
	KsVector3d				Ambient;					/**< Ambient (R,G,B)	*/
	KsVector4d				EdgeColor;					/**< �G�b�W�F (R,G,B,A)			*/
	KsReal					EdgeSize;					/**< �G�b�W�T�C�Y					*/
	KsVector4d				NormalTextureCoefficient;	/**< �e�N�X�`���W�� (R,G,B,A)		*/
	KsVector4d				SphereTextureCoefficient;	/**< �X�t�B�A�e�N�X�`���Q��Index 	*/
	KsVector4d				ToonTextureCoefficient;		/**< Toon�e�N�X�`���Q��Index		*/
};

/************************************************************************************************/
/**
 * @struct		KS_PMX_MORPH_GROUP
 * @brief		PMX �O���[�v���[�t
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_PMX_MORPH_GROUP
{
	KsInt32					MorphIndex;		/**< ���[�tIndex														*/
	KsReal					MorphRate;		/**< ���[�t��	(�O���[�v���[�t�̃��[�t�l * ���[�t�� = �Ώۃ��[�t�̃��[�t�l)	*/
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
	KsString				MorphName_J;			/**< �{�[����			*/
	KsString				MorphName_E;			/**< �{�[�����p		*/
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
	KsString				DisplayName_J;			/**< �\����J			*/
	KsString				DisplayName_E;			/**< �\�����p			*/
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
	KsString				RigidBodyName_J;			/**< �{�[����			*/
	KsString				RigidBodyName_E;			/**< �{�[�����p		*/
	KsInt32					BoneIndex;
	KsUInt8					Group;
	KsUInt16				GroupFlag;
	KsUInt8					ShapeType;
	KsVector3d				Size;
	KsVector3d				Position;			/**< �ړ���(x,y,z)					*/
	KsVector3d				Rotation;			/**< ��]��(x,y,z)	*/	
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
	KsString				JointName_J;			/**< Joint��			*/
	KsString				JointName_E;			/**< Joint���p		*/
	KsUInt8					Type;					// Joint��� - 0:�X�v�����O6DOF   | PMX2.0�ł� 0 �̂�(�g���p)

	KsInt32					RigidA;					/**< �{�[��Index						*/
	KsInt32					RigidB;					/**< �{�[��Index						*/
	KsVector3d				Position;				/**< �ړ���(x,y,z)					*/
	KsVector3d				Rotation;				/**< ��]��-���W�A���p(x,y,z)	*/

	KsVector3d				MoveLimitMin;			/**< �ړ���(x,y,z)					*/
	KsVector3d				MoveLimitMax;			/**< �ړ���(x,y,z)					*/
	KsVector3d				AngleLimitMin;			/**< ��]��-���W�A���p(x,y,z)	*/
	KsVector3d				AngleLimitMax;			/**< ��]��-���W�A���p(x,y,z)	*/

	KsVector3d				SpringMove;				/**< ��]��-���W�A���p(x,y,z)	*/
	KsVector3d				SpringAngle;			/**< ��]��-���W�A���p(x,y,z)	*/
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
	KS_PMX_HEADER			Header;					/**<�@PMX Header			*/
	KS_PMX_MODEL_INFO		ModelInfo;				/**<�@���f�����			*/
	KsInt32					NumVertex;				/**<�@���_��				*/
	KS_PMX_VERTEX*			pVertices;				/**<�@���_�f�[�^			*/
	KsInt32					NumFaces;				/**<�@�C���f�b�N�X��		*/
	KsInt32*				Indices;				/**<�@�C���f�b�N�X�f�[�^	*/
	KsInt32					NumTexture;				/**<�@�e�N�X�`����		*/
	KsString*				pTextures;				/**<�@�e�N�X�`���f�[�^		*/
	KsInt32					NumMaterial;			/**<�@�}�e���A����		*/
	KS_PMX_MATERIAL*		pMaterials;				/**<�@�}�e���A���f�[�^		*/
	KsInt32					NumBone;				/**<�@�{�[����			*/
	KS_PMX_BONE*			pBones;					/**<�@�{�[���f�[�^		*/
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
  ksPMX_MODEL_INFO_ENCODEING            = 0, // �G���R�[�h����  | 0:UTF16 1:UTF8
  ksPMX_MODEL_INFO_TEXTURE_EXT_UV       = 1, // �ǉ�UV�� | 0�`4 �ڍׂ͒��_�Q��
  ksPMX_MODEL_INFO_VERTEX_INDEX_SIZE    = 2, // ���_Index�T�C�Y | 1,2,4 �̂����ꂩ
  ksPMX_MODEL_INFO_TEXTURE_INDEX_SIZE   = 3, // �e�N�X�`��Index�T�C�Y | 1,2,4 �̂����ꂩ
  ksPMX_MODEL_INFO_MATERIAL_INDEX_SIZE  = 4, // �ގ�Index�T�C�Y | 1,2,4 �̂����ꂩ
  ksPMX_MODEL_INFO_BONE_INDEX_SIZE      = 5, // �{�[��Index�T�C�Y | 1,2,4 �̂����ꂩ
  ksPMX_MODEL_INFO_MORPH_INDEX_SIZE     = 6, // ���[�tIndex�T�C�Y | 1,2,4 �̂����ꂩ
  ksPMX_MODEL_INFO_RIGIDBODY_INDEX_SIZE = 7  // ����Index�T�C�Y | 1,2,4 �̂����ꂩ
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
	ksPMX_BDEF1 = 0, // : int 		| 4   | �{�[���̂�
	ksPMX_BDEF2 = 1, // : int,int,float 	| 4*3 | �{�[��2�ƁA�{�[��1�̃E�F�C�g�l(PMD����)
	ksPMX_BDEF4 = 2, // : int*4, float*4	| 4*8 | �{�[��4�ƁA���ꂼ��̃E�F�C�g�l�B�E�F�C�g���v��1.0�ł���ۏ�͂��Ȃ�
	ksPMX_SDEF  = 3  // : int,int,float, float3*3 | 4*12 | BDEF2�ɉ����ASDEF�p��float3(Vector3)��3�B���ۂ̌v�Z�ł͂���ɕ␳�l�̎Z�o���K�v(�ꉞ���̂܂�BDEF2�Ƃ��Ă��g�p�\)
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
	ksPMX_BONE_BIT_CONNECT    = 0x0001, // : �ڑ���(PMD�q�{�[���w��)�\�����@ -> 0:���W�I�t�Z�b�g�Ŏw�� 1:�{�[���Ŏw��
	ksPMX_BONE_BIT_ROT        = 0x0002, // : ��]�\
	ksPMX_BONE_BIT_MOVE       = 0x0004, // : �ړ��\
	ksPMX_BONE_BIT_DISP       = 0x0008, // : �\��
	ksPMX_BONE_BIT_CTRL       = 0x0010, // : �����
	ksPMX_BONE_BIT_IK         = 0x0020, // : IK
	ksPMX_BONE_BIT_ADD_ROT    = 0x0100, // : ��]�t�^
	ksPMX_BONE_BIT_ADD_MOVE   = 0x0200, // : �ړ��t�^
	ksPMX_BONE_BIT_AXIS       = 0x0400, // : ���Œ�
	ksPMX_BONE_BIT_LOCAL_AXIS = 0x0800, // : ���[�J����
	ksPMX_BONE_BIT_PHYICS     = 0x1000, // : ������ό`
	ksPMX_BONE_BIT_MORPH      = 0x2000  // : �O���e�ό`
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



