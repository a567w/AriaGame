/************************************************************************************************/
/** 
 * @file		KsBone.cpp
 * @brief		ボーン
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"
#include "KsBone.h"
#include "KsSkeleton.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsBone::KsBone()
{	
	m_name			= "none";
	m_id			= 0;
	m_flags			= 0;
	m_initPivot     = KsVector3d::ZERO;
	m_initTranslate = KsVector3d::ZERO;
	m_initRotate    = KsQuaternion::IDENTITY;
	m_initScale     = KsVector3d::ONE;
	m_pivot			= KsVector3d::ZERO;
	m_translate		= KsVector3d::ZERO;
	m_rotate		= KsQuaternion::IDENTITY;
	m_scale			= KsVector3d::ONE;
	m_localMatrix   = KsMatrix4x4::IDENTITY;
	m_worldMatrix   = KsMatrix4x4::IDENTITY;
	m_stackMatrix   = KsMatrix4x4::IDENTITY;
	m_stackScale    = KsVector3d::ONE;	
	m_pSkeleton     = 0;
	m_pParent       = 0;
	m_pChildren.clear();
	m_pUserData     = 0;
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsBone::~KsBone()
{
	ksDELETEARRAYTEMPLATE( m_pChildren );
}


#if 0

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/

#if 0

/** A way of recording the way each LODs is recorded this Mesh. */
struct MeshLodUsage
{
	/// squared Z value from which this LOD will apply
	Real fromDepthSquared;
	/// Only relevant if mIsLodManual is true, the name of the alternative mesh to use
	String manualName;
	/// Hard link to mesh to avoid looking up each time
	mutable Mesh* manualMesh;
    /// Edge list for this LOD level (may be derived from manual mesh)
    mutable EdgeData* edgeData;
};


std::vector< KsBoneData >		KsBoneDataList;

class KsModelObject
{
public:
	//LODをどうするか? numLOD *lodData
	//KsAABB				m_bundingBox;
	//KsSphere				m_bundingSphere;

	KsModelNodeList			m_pModelList;
	KsVertex*				m_pVertices;
	KsIndex*				m_pIndices;
	KsMaterial*				m_pMaterials;
	//KsModel*				m_pModel;
	KsBoneDataList			m_boneList;

	// LOD faceList
};

class KsModel
{
public:
	//LODをどうするか? numLOD *lodData
	//KsAABB				m_bundingBox;
	//KsSphere			m_bundingSphere;
	KsSkeleton*				m_pSkeleton;		/**< 骨組み（階層構造）*/

	KsModelNodeObjectList		m_pModelObjectList;
	KsBoneDataList				m_boneList;

};

    public:
        SubMesh();
        ~SubMesh();
        bool useSharedVertices;
        RenderOperation::OperationType operationType;
        VertexData *vertexData;
        IndexData *indexData;
        ProgressiveMesh::LODFaceList mLodFaceList;
        Mesh* parent;
        typedef std::multimap<size_t, VertexBoneAssignment> VertexBoneAssignmentList;
        typedef MapIterator<VertexBoneAssignmentList> BoneAssignmentIterator;
    protected:
        String mMaterialName;
        VertexBoneAssignmentList mBoneAssignments;



    class _OgreExport Mesh: public Resource
    {
        friend class SubMesh;
    public:
		/** A way of recording the way each LODs is recorded this Mesh. */
		struct MeshLodUsage
		{
			/// squared Z value from which this LOD will apply
			Real fromDepthSquared;
			/// Only relevant if mIsLodManual is true, the name of the alternative mesh to use
			String manualName;
			/// Hard link to mesh to avoid looking up each time
			mutable Mesh* manualMesh;
            /// Edge list for this LOD level (may be derived from manual mesh)
            mutable EdgeData* edgeData;
		};

		typedef std::vector<Real> LodDistanceList;
        typedef std::multimap<size_t, VertexBoneAssignment> VertexBoneAssignmentList;
        typedef MapIterator<VertexBoneAssignmentList> BoneAssignmentIterator;
        typedef std::vector<SubMesh*> SubMeshList;

    protected:
        SubMeshList mSubMeshList;
        void organiseTangentsBuffer(VertexData *vertexData, unsigned short destCoordSet);
    public:
		typedef HashMap<String, ushort> SubMeshNameMap ;
		typedef std::vector<MeshLodUsage> MeshLodUsageList;

    };



					
	
	/* Version 1.2 of the .mesh fornmat (deprecated)
	enum MeshChunkID {
        M_HEADER                = 0x1000,
            // char*          version           : Version number check
        M_MESH                = 0x3000,
			// bool skeletallyAnimated   // important flag which affects h/w buffer policies
            // Optional M_GEOMETRY chunk
            M_SUBMESH             = 0x4000, 
                // char* materialName
                // bool useSharedVertices
                // unsigned int indexCount
                // bool indexes32Bit
                // unsigned int* faceVertexIndices (indexCount)
                // OR
                // unsigned short* faceVertexIndices (indexCount)
                // M_GEOMETRY chunk (Optional: present only if useSharedVertices = false)
                M_SUBMESH_OPERATION = 0x4010, // optional, trilist assumed if missing
                    // unsigned short operationType
                M_SUBMESH_BONE_ASSIGNMENT = 0x4100,
                    // Optional bone weights (repeating section)
                    // unsigned int vertexIndex;
                    // unsigned short boneIndex;
                    // Real weight;
            M_GEOMETRY          = 0x5000, // NB this chunk is embedded within M_MESH and M_SUBMESH
			*/
                // unsigned int vertexCount
                // Real* pVertices (x, y, z order x numVertices)
                M_GEOMETRY_NORMALS = 0x5100,    //(Optional)
                    // Real* pNormals (x, y, z order x numVertices)
                M_GEOMETRY_COLOURS = 0x5200,    //(Optional)
                    // unsigned long* pColours (RGBA 8888 format x numVertices)
                M_GEOMETRY_TEXCOORDS = 0x5300,    //(Optional, REPEATABLE, each one adds an extra set)
                    // unsigned short dimensions    (1 for 1D, 2 for 2D, 3 for 3D)
                    // Real* pTexCoords  (u [v] [w] order, dimensions x numVertices)
			/*
            M_MESH_SKELETON_LINK = 0x6000,
                // Optional link to skeleton
                // char* skeletonName           : name of .skeleton to use
            M_MESH_BONE_ASSIGNMENT = 0x7000,
                // Optional bone weights (repeating section)
                // unsigned int vertexIndex;
                // unsigned short boneIndex;
                // Real weight;
            M_MESH_LOD = 0x8000,
                // Optional LOD information
                // unsigned short numLevels;
                // bool manual;  (true for manual alternate meshes, false for generated)
                M_MESH_LOD_USAGE = 0x8100,
                // Repeating section, ordered in increasing depth
				// NB LOD 0 (full detail from 0 depth) is omitted
                // Real fromSquaredDepth;
                    M_MESH_LOD_MANUAL = 0x8110,
                    // Required if M_MESH_LOD section manual = true
                    // String manualMeshName;
                    M_MESH_LOD_GENERATED = 0x8120,
                    // Required if M_MESH_LOD section manual = false
					// Repeating section (1 per submesh)
                    // unsigned int indexCount;
                    // bool indexes32Bit
                    // unsigned short* faceIndexes;  (indexCount)
                    // OR
                    // unsigned int* faceIndexes;  (indexCount)
            M_MESH_BOUNDS = 0x9000
                // Real minx, miny, minz
                // Real maxx, maxy, maxz
                // Real radius

			// Added By DrEvil
			// optional chunk that contains a table of submesh indexes and the names of
			// the sub-meshes.
			M_SUBMESH_NAME_TABLE,
				// Subchunks of the name table. Each chunk contains an index & string
				M_SUBMESH_NAME_TABLE_ELEMENT,
	                // short index
                    // char* name
	*/
    };

		    enum SkeletonChunkID {
        SKELETON_HEADER            = 0x1000,
            // char* version           : Version number check
        SKELETON_BONE              = 0x2000,
        // Repeating section defining each bone in the system. 
        // Bones are assigned indexes automatically based on their order of declaration
        // starting with 0.

            // char* name                       : name of the bone
            // unsigned short handle            : handle of the bone, should be contiguous & start at 0
            // Vector3 position                 : position of this bone relative to parent 
            // Quaternion orientation           : orientation of this bone relative to parent 

        SKELETON_BONE_PARENT       = 0x3000,
        // Record of the parent of a single bone, used to build the node tree
        // Repeating section, listed in Bone Index order, one per Bone

            // unsigned short handle             : child bone
            // unsigned short parentHandle   : parent bone

        SKELETON_ANIMATION         = 0x4000,
        // A single animation for this skeleton

            // char* name                       : Name of the animation
            // Real length                      : Length of the animation in seconds

            SKELETON_ANIMATION_TRACK = 0x4100,
            // A single animation track (relates to a single bone)
            // Repeating section (within SKELETON_ANIMATION)
                
                // unsigned short boneIndex     : Index of bone to apply to

                SKELETON_ANIMATION_TRACK_KEYFRAME = 0x4110
                // A single keyframe within the track
                // Repeating section

                    // Real time                    : The time position (seconds)
                    // Quaternion rotate            : Rotation to apply at this keyframe
                    // Vector3 translate            : Translation to apply at this keyframe
                    // Vector3 scale                : Scale to apply at this keyframe
    };
#endif

#endif
