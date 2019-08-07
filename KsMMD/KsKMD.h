/************************************************************************************************/
/** 
 * @file		KsKMD.h
 * @brief		KMD�t�@�C��
 * @author		Tsukasa Kato
 * @date		2010/12/17
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSKMD_H__
#define __KSKMD_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
#include "KsMMDType.h"


/************************************************************************************************/
/**
 * @enum	ksKMD_CHUNK_TYPE
 * @brief	�`�����N�f�[�^�^�C�v
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
 * @brief	�`�����N�f�[�^
 */
/************************************************************************************************/
struct KS_KMD_CHUNK
{
	KsUInt16				Type;					/// �`�����N�^�C�v
	KsUInt16				Count;					/// ����`�����N��
	KsUInt32				Size;					/// �f�[�^�T�C�Y
};

/************************************************************************************************/
/**
 * @struct	KS_KMD_HEADER
 * @brief	���f���w�b�_�[
 */
/************************************************************************************************/
struct KS_KMD_HEADER
{
	KsInt8					Signature[ 4 ];			/// ���ʃR�[�h		
	KsUInt16				Version;				/// �o�[�W�������
	KsUInt8					ModelName[ 24 ];		/// ���f����
	KsUInt16				ChunkCount;				/// �`�����N��
};

/************************************************************************************************/
/**
 * @struct	KS_KMD_BONE
 * @brief	�{�[���f�[�^
 */
/************************************************************************************************/
struct KS_KMD_BONE
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
 * @struct	KS_KMD_TEXTURE
 * @brief	�e�N�X�`���f�[�^
 */
/************************************************************************************************/
struct KS_KMD_TEXTURE
{
	KsChar					Name[ 32 ];				/// �e�N�X�`����
};

/************************************************************************************************/
/**
 * @struct	KS_KMD_MMD_MATERIAL
 * @brief	�}�e���A���f�[�^
 */
/************************************************************************************************/
struct KS_KMD_EFFECT
{
	KsUInt8					TextureName[ 32 ];		/// �e�N�X�`����
	KsVector4d				Diffuse;				/// �f�B�t���[�Y
	KsVector4d				Ambient;				/// ���F(ambient)
	KsVector4d				Specular;				/// �X�y�L�����[�J���[
	KsReal					Specularity;			/// �X�y�L�����l
};

/************************************************************************************************/
/**
 * @struct	KS_KMD_MMD_MATERIAL
 * @brief	�}�e���A���f�[�^
 */
/************************************************************************************************/
struct KS_KMD_MMD_MATERIAL
{
	KsUInt8					TextureName[ 32 ];	/// �e�N�X�`����
	KsVector4d				Diffuse;			/// �f�B�t���[�Y
	KsVector4d				Ambient;			/// ���F(ambient)
	KsVector4d				Specular;			/// �X�y�L�����[�J���[
	KsReal					Specularity;		/// �X�y�L�����l
};

/************************************************************************************************/
/**
 * @struct	KS_KMD_MESH_PARTS
 * @brief	���b�V���p�[�c�f�[�^
 */
/************************************************************************************************/
struct KS_KMD_MESH_PARTS
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
 * @struct	KS_KMD_MESH
 * @brief	���b�V���f�[�^
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
	KsReal					ControlWeight;	// IK�̉e���x( IK�l2 )
	KsInt16					Iterations;		// �ċA���Z��( IK�l1 )
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
 * @brief		���̃f�[�^
 * @version		1.0.0
 */
/************************************************************************************************/
struct KS_KMD_RIGID_BODY
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

/*************************************************************************************************/
/*
 * PMD�t�@�C���ǂݍ��ݏ���
 * @param	filePath	�t�@�C���p�X
 * @return	PMD�t�@�C���f�[�^
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
 * PMD�t�@�C���ǂݍ��ݏ���
 * @param	filePath	�t�@�C���p�X
 * @return	PMD�t�@�C���f�[�^
 */
/*************************************************************************************************/
ksMMD_API KsModel*	KsModelCreateFromKMD( KsFileObject* pFile );

/*************************************************************************************************/
/*
 * PMD�t�@�C���ǂݍ��ݏ���
 * @param	filePath	�t�@�C���p�X
 * @return	PMD�t�@�C���f�[�^
 */
/*************************************************************************************************/
ksMMD_API KsModel*	KsModelCreateFromKMD( const KsString& filePath );

/*************************************************************************************************/
/*
 * PMD�t�@�C���ǂݍ��ݏ���
 * @param	filePath	�t�@�C���p�X
 * @return	PMD�t�@�C���f�[�^
 */
/*************************************************************************************************/
ksMMD_API KsActor* KsActorCreateFromKMD( const KsString& filePath );


#endif /* __KSKMD_H__ */


