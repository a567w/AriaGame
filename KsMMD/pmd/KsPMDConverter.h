/************************************************************************************************/
/** 
 * @file		KsPMDConverter.h
 * @brief		PMD�t�@�C��
 * @author		Tsukasa Kato
 * @date		2010/12/17
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSPMDCONVERTER_H__
#define __KSPMDCONVERTER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                          */
/*==============================================================================================*/
#include "KsMMDType.h"
/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @enum	ksDATA_CHUNK_TYPE
 * @brief	�`�����N�f�[�^�^�C�v
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
 * @brief	�`�����N�f�[�^
 */
/************************************************************************************************/
class KS_DATA_CHUNK
{
	public:
		KsUInt16				Type;					/// �`�����N�^�C�v
		KsUInt16				Count;					/// ����`�����N��
		KsUInt32				Size;					/// �f�[�^�T�C�Y
		KsFileBuffer*			pFile;					/// �f�[�^

	public:
		/**
		 * �R���X�g���N�^
		 */
		KS_DATA_CHUNK( ksDATA_CHUNK_TYPE chunkType, KsUInt16 count, KsUInt32 size=0 );

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KS_DATA_CHUNK();

		/**
		 * �t�@�C���ɒl����������
		 * @param	val				�������ޒl
		 * @return					�������񂾃o�C�g��
		 */
		virtual KsSize				writeReal( KsReal val );

		/**
		 * �t�@�C���ɒl����������
		 * @param	val				�������ޒl
		 * @return					�������񂾃o�C�g��
		 */
		virtual KsSize				writeInt32( KsInt32 val );

		/**
		 * �t�@�C���ɒl����������
		 * @param	val				�������ޒl
		 * @return					�������񂾃o�C�g��
		 */
		virtual KsSize				writeUInt32( KsUInt32 val );

		/**
		 * �t�@�C���ɒl����������
		 * @param	val				�������ޒl
		 * @return					�������񂾃o�C�g��
		 */
		virtual KsSize				writeInt16( KsInt16 val );

		/**
		 * �t�@�C���ɒl����������
		 * @param	val				�������ޒl
		 * @return					�������񂾃o�C�g��
		 */
		virtual KsSize				writeUInt16( KsUInt16 val );

		/**
		 * �t�@�C���ɒl����������
		 * @param	val				�������ޒl
		 * @return					�������񂾃o�C�g��
		 */
		virtual KsSize				writeInt8( KsInt8 val );

		/**
		 * �t�@�C���ɒl����������
		 * @param	val				�������ޒl
		 * @return					�������񂾃o�C�g��
		 */
		virtual KsSize				writeUInt8( KsUInt8 val );

		/**
		 * �t�@�C���ɒl����������
		 * @param	val				�������ޒl
		 * @return					�������񂾃o�C�g��
		 */
		virtual KsSize				writeChar( KsChar val );

		/**
		 * �t�@�C���ɒl����������
		 * @param	val				�������ޒl
		 * @return					�������񂾃o�C�g��
		 */
		virtual KsSize				writeByte( KsInt32 val );

		/**
		 * �o�b�t�@����t�@�C���ɒl����������
		 * @param	pBuffer			�������ރo�b�t�@
		 * @param	count			�������ރo�C�g��
		 * @return					�������񂾃o�C�g��
		 */
		virtual KsSize				write( const void *pBuffer, KsInt32 count );

		/**
		 * �`�����N�T�C�Y���X�V����
		 */
		virtual KsSize				updateSize();
};

/************************************************************************************************/
/**
 * @struct	KS_MODEL_HEADER
 * @brief	���f���w�b�_�[
 */
/************************************************************************************************/
struct KS_MODEL_HEADER
{
	KsInt8					Signature[ 4 ];			/// ���ʃR�[�h		
	KsUInt16				Version;				/// �o�[�W�������
	KsUInt8					ModelName[ 24 ];		/// ���f����
	KsUInt16				ChunkCount;				/// �`�����N��

	KS_MODEL_HEADER();
	KS_MODEL_HEADER( const KsString& modelName );
};

/************************************************************************************************/
/**
 * @struct	KS_MODEL_BONE
 * @brief	�{�[���f�[�^
 */
/************************************************************************************************/
struct KS_MODEL_BONE
{
	KsSChar					Name[ 32 ];				/// �{�[����
	KsInt32					Index;					/// �{�[���̃C���f�b�N�X
	KsInt32					Parent;					/// �e�{�[���̃C���f�b�N�X
	KsInt32					ChildCount;				/// �q�{�[����
	KsVector3d				Position;				/// �{�[���ʒu
	KsQuaternion			Rotation;				/// �{�[����]
};

/************************************************************************************************/
/**
 * @struct	KS_MODEL_TEXTURE
 * @brief	�e�N�X�`���f�[�^
 */
/************************************************************************************************/
struct KS_MODEL_TEXTURE
{
	KsSChar					Name[ 32 ];				/// �e�N�X�`����
};

/************************************************************************************************/
/**
 * @struct	KS_MODEL_MMD_MATERIAL
 * @brief	�}�e���A���f�[�^
 */
/************************************************************************************************/
struct KS_MODEL_EFFECT
{
	KsUInt8					TextureName[ 32 ];		/// �e�N�X�`����
	KsVector4d				Diffuse;				/// �f�B�t���[�Y
	KsVector4d				Ambient;				/// ���F(ambient)
	KsVector4d				Specular;				/// �X�y�L�����[�J���[
	KsReal					Specularity;			/// �X�y�L�����l
};

/************************************************************************************************/
/**
 * @struct	KS_MODEL_MMD_MATERIAL
 * @brief	�}�e���A���f�[�^
 */
/************************************************************************************************/
struct KS_MODEL_MMD_MATERIAL
{
	KsUInt8					TextureName[ 32 ];	/// �e�N�X�`����
	KsVector4d				Diffuse;			/// �f�B�t���[�Y
	KsVector4d				Ambient;			/// ���F(ambient)
	KsVector4d				Specular;			/// �X�y�L�����[�J���[
	KsReal					Specularity;		/// �X�y�L�����l
};

/************************************************************************************************/
/**
 * @struct	KS_MODEL_MESH_PARTS
 * @brief	���b�V���p�[�c�f�[�^
 */
/************************************************************************************************/
struct KS_MODEL_MESH_PARTS
{
	KsUInt32				MeshPartsSize;		/// ���b�V���p�[�c�f�[�^�T�C�Y
	KsUInt32				IndexType;			/// ���_�C���f�b�N�X�̃^�C�v
	KsUInt32				IndexCount;			/// ���_�C���f�b�N�X��
	KsUInt32				IndexSize;			/// ���_�C���f�b�N�X�T�C�Y
	KsByte*					IndexData;			/// ���_�C���f�b�N�X�f�[�^

	KsUInt32				VertexType;			/// ���_�f�[�^�̃^�C�v
	KsUInt32				VertexCount;		/// ���_�f�[�^�̐�
	KsUInt32				VertexSize;			/// ���_�T�C�Y
	KsByte*					VertexData;			/// ���_�f�[�^

	KsInt32					PrimitiveCount;		/// �����_�����O����v���~�e�B�u�̐�
	KsUInt32				StartIndex;			/// �C���f�b�N�X�z��̒��Œ��_�̓ǂݎ����J�n����ʒu
	KsUInt32				StartVertex;		/// ���_�o�b�t�@�[�̍ŏ㕔����̃I�t�Z�b�g
	KsUInt32				EffectID;			/// �G�t�F�N�gID
	KsUInt32				MatrixPalletCount;	/// �g�p�}�g���b�N�X�p���b�g��
	KsInt32*				MatrixPalletData;	/// �g�p�}�g���b�N�X�p���b�g
	KsUInt32				BoneCount;			/// �{�[����
	KsInt32*				BoneData;			/// �{�[���f�[�^
};

/************************************************************************************************/
/**
 * @struct	KS_MODEL_MESH
 * @brief	���b�V���f�[�^
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
 * @brief	���b�V���f�[�^
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
	KsReal						ControlWeight;	// IK�̉e���x( IK�l2 )
	KsInt16						Iterations;		// �ċA���Z��( IK�l1 )
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
 * @brief		���̃f�[�^
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_MODEL_RIGID_BODY
{
	KsInt8				Name[ 20 ];		/// ���̖�[20]
	KsUInt16			BoneIndex;		/// �֘A�{�[���ԍ�
	KsUInt8				ColGroupIndex;	/// �Փ˃O���[�v
	KsUInt16			ColGroupMask;	/// �Փ˃O���[�v�}�X�N
	KsUInt8				ShapeType;		/// �`��  0:�� 1:�� 2:�J�v�Z��
	KsReal				Width;			/// ���a(��)
	KsReal				Height;			/// ����
	KsReal				Depth;			/// ���s
	KsReal				Position[3];	/// �ʒu(�{�[������)
	KsReal				Rotation[3];	/// ��](radian)
	KsReal				Mass;			/// ����
	KsReal				LinearDamping;	/// �ړ��_���p�[
	KsReal				AngularDamping;	/// ��]��
	KsReal				Restitution;	/// ������
	KsReal				Friction;		/// ���C��
	KsUInt8				RigidBodyType;	/// �^�C�v 0:Bone�Ǐ] 1:�������Z 2:�������Z(Bone�ʒu����)
};

/************************************************************************************************/
/**
 * @struct		KS_MODEL_CONSTRAINT
 * @brief		�R���X�g���C���g(�W���C���g)�f�[�^
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_MODEL_CONSTRAINT
{
	KsInt8						Name[ 20 ];		/// �R���X�g���C���g��[20]
	KsUInt32					RigidA;			/// ����A
	KsUInt32					RigidB;			/// ����B
	KsVector3d					Position;		/// �ʒu(���f�����_���S)
	KsVector3d					Rotation;		/// ��](radian)
	KsVector3d					PosLimitL;		/// �ړ�����1
	KsVector3d					PosLimitU;		/// �ړ�����2
	KsVector3d					RotLimitL;		/// ��]����1
	KsVector3d					RotLimitU;		/// ��]����2
	KsVector3d					SpringPos;		/// �΂ˈړ�
	KsVector3d					SpringRot;		/// �΂ˉ�]
};

/************************************************************************************************/
/**
 * @struct	KS_MODEL_DATA
 * @brief	���f���f�[�^
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
 * PMD�t�@�C���ǂݍ��ݏ���
 * @param	filePath	�t�@�C���p�X
 * @return	PMD�t�@�C���f�[�^
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
 * PMD�t�@�C���ǂݍ��ݏ���
 * @param	filePath	�t�@�C���p�X
 * @return	PMD�t�@�C���f�[�^
 */
/************************************************************************************************/
ksMMD_API KsBool KsModelConvertFromPMD( const KsString& inputFilePath, const KsString& outputFilePath, KsModelConvertOption& opt );

#endif /* __KSPMDCONVERTER_H__ */


