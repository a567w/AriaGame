/************************************************************************************************/
/** 
 * @file		KsPMD.cpp
 * @brief		PMD�t�@�C��
 * @author		Tsukasa Kato
 * @date		2010/12/17
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>												*/
/*==============================================================================================*/
#include "KsMMD/KsMMDPreCompile.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
void KsCalculateAbsoluteTransforms( KsModel* pModel, KsBone* pBone )
{
	if( -1 == pBone->getParentIndex() )
	{
		pModel->m_vpBones[ pBone->getIndex() ]->m_worldTransform = pBone->m_defaultTransform;
	}
	else
	{
		pModel->m_vpBones[ pBone->getIndex() ]->m_worldTransform = pBone->m_defaultTransform * pModel->m_vpBones[ pBone->getParentIndex() ]->m_worldTransform;
	}

	for( KsUInt32 i=0; i<pBone->getNumChild(); i++ )
	{
		KsCalculateAbsoluteTransforms( pModel, pBone->getChild( i ) );
	}
}

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
void KsBuildBoneIndex( KsBone* pBone, KsInt32* pIndex, KsInt32* conv_tbl, KsBoneCollection* vpBones )
{
	KsInt32	index = *pIndex;

	conv_tbl[ pBone->m_index ] = index;

	pBone->m_index = index;

	vpBones->insert( index, pBone );

	++index;

	*pIndex = index;

	for( KsUInt32 i=0; i<pBone->getNumChild(); i++ )
	{
		KsBuildBoneIndex( pBone->getChild( i ), pIndex, conv_tbl, vpBones );
	}
}

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
void KsBuildParentBoneIndex( KsBone* pBone )
{
	if( pBone->m_pParent )
	{
		pBone->m_parent = pBone->m_pParent->getIndex();
	}

	for( KsUInt32 i=0; i<pBone->getNumChild(); i++ )
	{
		KsBuildParentBoneIndex( pBone->getChild( i ) );
	}
}

/*************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/*************************************************************************************************/
KsModelBuilder::KsModelBuilder()
{
}

/*************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/*************************************************************************************************/
KsModelBuilder::~KsModelBuilder()
{
}

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
KsModel* KsModelBuilder::start( const KsString& name, KsUInt32 boneCount )
{
	// ���f������
	m_pModel = new KsModel();

	// ���f�������Z�b�g
	m_pModel->setModelName( name );

	// ���b�V������
	m_pMesh = new KsMesh();

	// root �{�[�����P�ǉ�����
	m_boneCount = boneCount + 1;

	// �{�[���m��
	m_pModel->m_vpBones.arrayRalloc( m_boneCount );
	m_vpBones.arrayRalloc( m_boneCount );

	// ���[�g�{�[�����Z�b�g����
	m_pRoot = new KsBone();

	m_pRoot->m_name    = "ks_root";
	m_pRoot->m_index   = 0;
	m_pRoot->m_parent  = -1;
	m_pRoot->m_pParent = NULL;

	m_vpBones.push_back( m_pRoot );

	// 0�N���A�[
	KsZeroMemory( m_boneConvertTbl, sizeof(m_boneConvertTbl) );

	return m_pModel;
}

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
void KsModelBuilder::createHierarchy()
{
	// �e�q�֌W���\�z����
	for( KsUInt32 i=1; i<m_vpBones.size(); i++ )
	{
		const KsInt32	index = m_vpBones[ i ]->m_parent;

		m_vpBones[ i ]->m_pParent = m_vpBones[ index ];
		m_vpBones[ i ]->m_pParent->m_vpChildren.push_back( m_vpBones[ i ] );
	}
}

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
void KsModelBuilder::createAbsoluteTransforms()
{
	KsInt32		boneIndex = 0;

	// �{�[���C���f�b�N�X�č\�z
	KsBuildBoneIndex( m_pRoot, &boneIndex, m_boneConvertTbl, &m_pModel->m_vpBones );

	// �e�{�[���C���f�b�N�X�č\�z
	KsBuildParentBoneIndex( m_pRoot );

	// AbsoluteMatrix���\�z����
	KsCalculateAbsoluteTransforms( m_pModel, m_pRoot );

	// InverseMatrix���\�z����
	for( KsUInt32 i=0; i<m_pModel->m_vpBones.size(); i++ )
	{
		KsBone*		pBone = m_pModel->m_vpBones[ i ];
		pBone->m_inverseTransform = pBone->m_worldTransform.inverse();
	}
}

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
KsModel* KsModelBuilder::finish()
{
	m_pModel->addMesh( m_pMesh );

	return m_pModel;
}

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
void KsModelBuilder::createMeshPart( KsEffect* pEffect, KsInputLayout* pInputLayout, KsUInt32 numVertex, KS_MMD_VERTEX* pVertices, KsUInt32 numIndex, KsUInt16* pIndices )
{
	KsByte			currentPallet = 0;
	KsInt32			sortPallet[ 1024 ];
	KsInt32			meshPallet[ 1024 ];

	for( KsInt32 i=0; i<1024; i++ )
	{
		sortPallet[ i ] = -1;
		meshPallet[ i ] = -1;
	}

	for( KsUInt32 i=0; i<numVertex; i++ )
	{
		KsInt32 org[ 2 ];
		
		org[ 0 ] = pVertices[ i ].indices_16[ 0 ];
		org[ 1 ] = pVertices[ i ].indices_16[ 1 ];

		for( KsUInt32 j=0; j<2; j++ )
		{
			if( pVertices[ i ].weight[ j ] == 0.0f )
			{
				continue;
			}

			if( -1 == sortPallet[ org[ j ] ] )
			{
				pVertices[ i ].indices[ j ] = currentPallet;

				meshPallet[ currentPallet ] = org[ j ];
				sortPallet[ org[ j ] ] = currentPallet;
				++currentPallet;
			}
			else
			{
				pVertices[ i ].indices[ j ] = sortPallet[ org[ j ] ];
			}
		}
	}

	KsHardwareBufferManager*	pBufferManager = KsHardwareBufferManager::getInstancePtr();
	KsVertexBuffer*				pVertexBuffer  = pBufferManager->createVertexBuffer( pVertices, sizeof(KS_MMD_VERTEX), numVertex, ksMMD_FVF, ksCPU_ACCESS_WRITE );
	KsIndexBuffer*				pIndexBuffer   = pBufferManager->createIndexBuffer( pIndices, sizeof(KsUInt16)*numIndex , numIndex, ksFMT_INDEX16, 0 );
	KsMeshPart*					pMeshPart      = ksNew KsMeshPart( pEffect, pIndexBuffer, pVertexBuffer, pInputLayout, numVertex, numIndex, 0, 0 );

	pMeshPart->createPallet( currentPallet, meshPallet );

	for( KsInt32 i=0; i<currentPallet; i++ )
	{
		const KsInt32 index = meshPallet[ i ];
		KsBone* pBone = m_pModel->m_vpBones[ index ];

		pMeshPart->addBone( pBone );
	}

	m_pMesh->addMeshParts( pMeshPart );
	
	m_pModel->addEffect( pEffect );
	m_pModel->addTexture( ((KsEffectMMD*)pEffect)->getDiffuseTexture() );
}


