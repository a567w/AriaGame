/************************************************************************************************/
/** 
 * @file		KsModelLoader.h
 * @brief		���f�����[�_�[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMODELLOADER_H__
#define __KSMODELLOADER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsType.h"
#include "KsMesh.h"
#include "KsVertexBuffer.h"
#include "KsRenderSystemDX.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsModelLoader
 * @brief		���f�����[�_�[
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
	KsUInt32				signature;			/**< ���ʗp						*/
	KsUInt32				version;			/**< �o�[�W�������				*/
	KsUInt32				type;				/**< �^�C�v						*/
	KsUInt32				flags;				/**< �e��t���O					*/

}KS_KMD_FILE_HEADER;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_KMD_VECTOR2D
{
	KsReal					x, y;				/**< ���_���W					*/
}KS_KMD_VECTOR2D;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_KMD_VECTOR3D
{
	KsReal					x, y, z;			/**< ���_���W					*/
}KS_KMD_VECTOR3D;


/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_KMD_VECTOR4D
{
	KsReal					x, y, z, w;			/**< ���_���W					*/
}KS_KMD_VECTOR4D;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_KMD_BOUNDING_BOX
{
	KS_KMD_VECTOR3D			min;				/**< �{�b�N�X�̒��_ min			*/
	KS_KMD_VECTOR3D			max;				/**< �{�b�N�X�̒��_ max			*/
}KS_KMD_BOUNDING_BOX;

/************************************************************************************************/
/**
 * �`��ʃ��X�g
 */
/************************************************************************************************/
typedef struct _KS_KMD_FACE_LIST
{
	KsInt16				start;				/**< �`��J�n�C���f�b�N�X			*/
	KsInt16				end;				/**< �`��I���C���f�b�N�X			*/
	KsInt16				materialID;			/**< �}�e���A��ID				*/
}KS_KMD_FACE_LIST;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_KMD_MESH
{
	KsUInt32				flags;				/**< �e��t���O					*/
	KsUInt32				numHierarchyNode;	/**< �K�w�\���̃m�[�h��			*/
	KsUInt32				numSubMesh;			/**< �T�u���b�V���̐�				*/
	KsUInt32				numBone;			/**< �{�[����					*/
	KsUInt32				numPoint;			/**< NULL�|�C���g��				*/
	KsUInt32				numMaterial;		/**< �g�[�^���}�e���A��			*/
	KsUInt32				numTexture;			/**< �g�[�^���Ŏg�p����e�N�X�`��	*/
	KsUInt32				numAnim;			/**< �A�j���̐�					*/
	KsUInt32				offsetHierarchy;	/**< �K�w�\���̃I�t�Z�b�g�ʒu		*/
	KsUInt32				offsetSubMesh;		/**< �T�u���b�V���̃I�t�Z�b�g�ʒu	*/
	KsUInt32				offsetBone;			/**< �{�[���̃I�t�Z�b�g�ʒu		*/
	KsUInt32				offsetPoint;		/**< NULL�|�C���g�̃I�t�Z�b�g�ʒu	*/
	KsUInt32				offsetMaterial;		/**< �}�e���A���̃I�t�Z�b�g�ʒu	*/
	KsUInt32				offsetTexture;		/**< �e�N�X�`���̃I�t�Z�b�g�ʒu	*/
	KsUInt32				offsetAnim;			/**< �A�j���̂̃I�t�Z�b�g�ʒu		*/
	KS_KMD_BOUNDING_BOX		bundingBox;			/**< �o�E���f�B���O�{�b�N�X�X		*/
}KS_KMD_MESH;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_KMD_HIERARCHY_NODE
{
	KsUInt32				id;					/**< ID							*/
	KsUInt32				flags;				/**< �e��t���O					*/
	KsUInt32				type;				// �I�u�W�F�N�g�̃^�C�v(mesh,bone,point�Ȃ�)
	KsUInt32				objLink;			// �g�p�I�u�W�F�N�g�̃C���f�b�N�X( subMeshList �̉��Ԗڂ��g���Ă��邩�Ȃ�)
	KS_KMD_VECTOR3D			pivot;				// ��_�ʒu( pivot )
	KS_KMD_VECTOR3D			translate;			// �ʒu
	KS_KMD_VECTOR4D			rotate;				// ��](�N�H�[�^�j�I��)
	KS_KMD_VECTOR3D			scale;				// �X�P�[��
	KsUInt32				parent;				// �e��index( -1�̂Ƃ��͂��Ȃ�root )
	KsUInt32				numChild;			// �q�̐�
	//KsUInt32				children;			// �q���̐������ꂪ���݂���(��)

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
	KsUInt16				point[ 3 ];			/**< ���_�C���f�b�N�X				*/
	KsUInt16				materialID;			/**< �}�e���A��ID				*/
	KsUInt16				smoothGroup;		/**< �X���[�W���O�O���[�v			*/
}KS_KMD_FACE;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_KMD_SUBMESH
{
	KsUInt32				id;					/**< ID							*/
	KsUInt32				flags;				/**< �e��t���O					*/
	KS_KMD_BOUNDING_BOX		bundingBox;			/**< �o�E���f�B���O�{�b�N�X�X		*/
	KsUInt32				vertexType;			/**< ���_�̃^�C�v				*/
	KsUInt32				faceType;			/**< index type ( 16bit, 32bit �ǂ���)	*/
	KsUInt32				numVertex;			/**< ���_��						*/
	KsUInt32				numFace;			/**< �|���S����					*/
	KsUInt32				numFaceList;		/**< �ʂ̍\�����X�g��				*/
	KsUInt32				numBoneWeight;		/**< �E�G�C�g��					*/

}KS_KMD_SUBMESH;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_KMD_WEIGHT
{
	KsInt32				index;				/**< node index				*/
	KsReal					weight;				/**< �E�G�C�g				*/
}KS_KMD_WEIGHT;

typedef struct _KS_KMD_BONE_DATA
{
	KsInt32				vertexIndex;		/**< vertex index				*/
	KsInt32				numWeight;			/**< �E�G�C�g��					*/
}KS_KMD_BONE_DATA;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_KMD_BONEWEIGHT
{
	KsInt32				vertexIndex;		/**< vertex index				*/
	KsInt32				numWeight;			/**< �E�G�C�g��					*/
	KS_KMD_WEIGHT			weight[ 4 ];		/**< �E�G�C�g�f�[�^				*/
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
				// size �Ȃ�
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
	KS_KMD_COLOR			diffuse;		/**< �f�B�t���[�Y�F( �g�U�� )		*/
	KS_KMD_COLOR			ambient;		/**< �A���r�G���g�F( ���� )		*/
	KS_KMD_COLOR			specular;		/**< �X�y�L�����F( ���ʌ� )		*/
	KS_KMD_COLOR			emissive;		/**< �G�~�b�V�����F				*/
	KsReal					power;			/**< �X�y�L���� �n�C���C�g�̑N��	*/
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
	KsReal					m_time;			/**< �t���[���Đ�����		*/
	KsVector3d				m_pos;			/**< �ʒu���W			*/
	KsQuaternion			m_rotation;		/**< ��]				*/
	KsVector3d				m_scale;		/**< �X�P�[��			*/

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

	KsAnimTrackList			m_pvTracks;			// �I�u�W�F�N�g����
	KsReal					m_frameRate;		/**< �t���[�����[�g	*/
	KsReal					m_startTime;		/**< �J�n����		*/
	KsReal					m_endTime;			/**< �I������		*/
};

extern KsAnim* KsLoadAnim( const KsChar* pFileName );

#endif	/* __KSMODELLOADER_H__ */




#if 0

typedef enum _ksKMD_CHUNK_ID
{
	ksKMD_FILE_HEADER		= 0x1000
		// ���ʗp
		// �o�[�W�������
		// �^�C�v
		// �e��t���O
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
				// �I�u�W�F�N�g�̃^�C�v(mesh,bone,point�Ȃ�)
				// �g�p�I�u�W�F�N�g�̃C���f�b�N�X( subMeshList �̉��Ԗڂ��g���Ă��邩�Ȃ�)
				// ��_�ʒu( pivot )
				// �ʒu
				// ��](�N�H�[�^�j�I��)
				// �X�P�[��
				// �e��index( -1�̂Ƃ��͂��Ȃ�root )
				// �q�̐�
				// �q��ID���X�g
		ksKMD_SUBMESH			= 0x5000
			// id
			// flags
			ksKMD_BOUNDING_BOX	= 0x5100
				// min, max
			ksKMD_GEOMETRY		= 0x5200
				// num vertex
				// num face
				// vertex type
				// index type ( 16bit, 32bit �ǂ���) 
				ksKMD_VERTEX	= 0x5210
					// ���_�̃^�C�v
					// [ x, y, z ], [ nx, ny, nz ], [ u, v ], matID
				ksKMD_FACE		= 0x5220
					// �ʏ��( index List )
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
				// size �Ȃ�
		ksKMD_LOD
	
		ksKMD_MATERIAL			= 
			// material
		ksKMD_TEXTURE
			//texture file name
		ksKMD_ANIM
			// �A�j���[�V�������
}ksCHUNK_ID;


		



typedef struct _KS_KMD_SUBMESH
{
	KsUInt32			flags;				/**< �t���O	*/
	KsUInt32			
};

class KsChunk
{
	public:
		KsUInt16			m_type;				/**< �`�����N�^�C�v				*/
		KsUInt16			m_option;			/**< �`�����N�I�v�V����			*/
		KsUInt32			m_nextOffset;		/**< ���̃`�����N�̃I�t�Z�b�g	*/
		KsUInt32			m_childOffset;		/**< ���ʃ`�����N�̃I�t�Z�b�g	*/
		KsUInt32			m_dataOffset;		/**< �u���b�N�f�[�^�̃I�t�Z�b�g	*/
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

