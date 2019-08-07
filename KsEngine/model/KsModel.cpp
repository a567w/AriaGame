/************************************************************************************************/
/** 
 * @file		KsModel.h
 * @brief		���f��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsModel::KsModel()
	: m_pRoot( 0 )
	, m_pParameter( 0 )
	, m_pCamera( 0 )
{
	m_pParameter = new KsModelParameter();
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsModel::~KsModel()
{
	//ksDELETEARRAYTEMPLATE( m_vpMeshes );
	//ksDELETEARRAYTEMPLATE( m_vpBones );
	//ksDELETEARRAYTEMPLATE( m_vpTextures );
	//ksDELETEARRAYTEMPLATE( m_vpEffects );
}

/************************************************************************************************/
/*
 * �X�V����
 */
/************************************************************************************************/
void KsModel::update()
{
	if( m_vpBones.size() > 100 )
	{
		m_vpBones[ 0 ]->m_worldTransform.setTranslate( 0.0f, 16.0f, 0.0f );
	}
	updateBoneMatrix();
	updateWorldMatrix();
	updateSkinMatrix();
}

/************************************************************************************************/
/*
 * �X�V����
 */
/************************************************************************************************/
KsBool KsModel::updateShaderParameter()
{
	KsCamera*	pCamera = m_pCamera;

	if( !pCamera )
	{
		KsCameraManager*	pCameraManager = KsCameraManager::getInstancePtr();

		if( pCameraManager )
		{
			pCamera = pCameraManager->getActiveCamera();
		}
	}

	if( !pCamera )
	{
		return ksFALSE;
	}

	KsMatrix4x4		worldMat = KsMatrix4x4::IDENTITY;

	m_pParameter->GBuffer.World         = worldMat;
	m_pParameter->GBuffer.Proj          = pCamera->getProjMatrix();
	m_pParameter->GBuffer.ViewProj      = pCamera->getViewProjMatrix();
	m_pParameter->GBuffer.WorldView     = worldMat * pCamera->getViewMatrix();
	m_pParameter->GBuffer.WorldViewProj = worldMat * pCamera->getViewProjMatrix();

	m_pParameter->GBuffer.World.transpose();
	m_pParameter->GBuffer.Proj.transpose();
	m_pParameter->GBuffer.ViewProj.transpose();
	m_pParameter->GBuffer.WorldView.transpose();
	m_pParameter->GBuffer.WorldViewProj.transpose();

	//m_vpBones[ 3 ]->m_skinTransform.setTranslate( 0.0f, 5.0f, 0.0f );
#if 0
	for( KsUInt32 i=0; i<getBoneCount(); i++ )
	{
		const KsBone*	pBone = m_vpBones[ i ];
		//m_vpBones[ i ]->m_skinTransform = KsMatrix4x4::IDENTITY;
		m_pParameter->Model.MatrixPalette[ i ] = pBone->m_skinTransform;
		//m_pParameter->Model.MatrixPalette[ i ] = KsMatrix4x4::IDENTITY;
		m_pParameter->Model.MatrixPalette[ i ].transpose();
	}
#endif

	m_pParameter->GBuffer.CameraNearFar.set( pCamera->getFar(), pCamera->getNear(), 0.0f, 0.0f );
	m_pParameter->GBuffer.FramebufferDimensionsX = pCamera->getViewport().m_w;
	m_pParameter->GBuffer.FramebufferDimensionsY = pCamera->getViewport().m_h;
	m_pParameter->GBuffer.FramebufferDimensionsZ = 0;     // Unused
	m_pParameter->GBuffer.FramebufferDimensionsW = 0;     // Unused

	return ksTRUE;
}

/************************************************************************************************/
/*
 * �`�揈��
 * @param	pRenderContext	�`��R���e�L�X�g
 */
/************************************************************************************************/
void KsModel::draw( KsRenderContext* pRenderContext )
{
	if( !updateShaderParameter() )
	{
		return;
	}

	const KsUInt32 numMesh = m_vpMeshes.size();

	for( KsUInt32 i=0; i<numMesh; i++ )
	{
		KsMesh*	pMesh = m_vpMeshes[ i ];

		pMesh->draw( pRenderContext, m_pParameter );
	}

#if 0
	for( KsUInt32 i=0; i<m_vpBones.size(); i++ )
	{
		m_vpBones[ i ]->draw();
	}
#endif
}

/************************************************************************************************/
/*
 * �{�[���}�g���b�N�X�X�V
 */
/************************************************************************************************/
void KsModel::updateBoneMatrix()
{
#if 0
	KsMatrix4x4 rootTransform = KsMatrix4x4::IDENTITY;

	m_pBonePose[ 0 ].m_worldMatrix = m_pBonePose[ 0 ].m_defaultMatrix * rootTransform;

	for( KsUInt32 bone=1; bone<m_joints.Length; bone++ )
	{
		m_joints[ bone ].AnimTransform = m_joints[ bone ].GetCurrentTransform();
		m_joints[ bone ].BoneTransform = m_joints[ bone ].AnimTransform * m_joints[ bone ].DefaultTransform;
	}
#endif

	for( KsUInt32 i=0; i<getBoneCount(); i++ )
	{
		KsBone*	pBone = m_vpBones[ i ];

		pBone->m_boneTransform = pBone->m_animationTransform * pBone->m_defaultTransform;
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsModel::updateWorldMatrix()
{
	for( KsUInt32 i=1; i<getBoneCount(); i++ )
	{
		const KsUInt32 parentBone = m_vpBones[ i ]->getParentIndex();
		KsBone*	pBone = m_vpBones[ i ];

		pBone->m_worldTransform = pBone->m_boneTransform * m_vpBones[ parentBone ]->m_worldTransform;
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsModel::updateSkinMatrix()
{
	for( KsUInt32 i=0; i<getBoneCount(); i++ )
	{
		KsBone*		pBone = m_vpBones[ i ];

		pBone->m_skinTransform = pBone->m_inverseTransform * pBone->m_worldTransform;
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsModel::setWorldMatrix( const KsMatrix4x4& worldMatrix )
{
	m_pParameter->GBuffer.World = worldMatrix;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsModel::setViewMatrix( const KsMatrix4x4& viewMatrix )
{
	//m_pParameter->GBuffer.ViewProj = viewMatrix * projMat;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsModel::setProjectionMatrix( const KsMatrix4x4& projMatrix )
{
	//m_pParameter->GBuffer.ViewProj = viewMat * projMatrix;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsInt32 KsModel::getBoneIndex( const KsString& name )
{
	const KsInt32	numBone = (KsInt32)getBoneCount();

	for( KsInt32  i=0; i<numBone; i++ )
	{
		if( m_vpBones[ i ]->getName() == name )
		{
			return i;
		}
	}
	
	return -1;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsModel::addTexture( KsTexture* pTexture )
{
	if( NULL == pTexture )
	{
		return;
	}

	const KsInt32	numTexture = (KsInt32)m_vpTextures.size();

	for( KsInt32  i=0; i<numTexture; i++ )
	{
		if( m_vpTextures[ i ]->getName() == pTexture->getName() )
		{
			return;
		}
	}

	m_vpTextures.push_back( pTexture );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsModel::addEffect( KsEffect* pEffect )
{
	if( NULL == pEffect )
	{
		return;
	}

	const KsInt32	numEffect = (KsInt32)m_vpEffects.size();

	for( KsInt32  i=0; i<numEffect; i++ )
	{
		if( m_vpEffects[ i ] == pEffect )
		{
			return;
		}
	}

	m_vpEffects.push_back( pEffect );
}


/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
void KsModel::calculateAbsoluteTransforms( KsBone* pBone )
{
	if( -1 == pBone->getParentIndex() )
	{
		m_vpBones[ pBone->getIndex() ]->m_worldTransform = pBone->m_defaultTransform;
	}
	else
	{
		m_vpBones[ pBone->getIndex() ]->m_worldTransform = pBone->m_defaultTransform * m_vpBones[ pBone->getParentIndex() ]->m_worldTransform;
	}

	for( KsUInt32 i=0; i<pBone->getNumChild(); i++ )
	{
		calculateAbsoluteTransforms( pBone->getChild( i ) );
	}
}

/************************************************************************************************/
/*
 * �e�q�֌W���\�z����
 */
/************************************************************************************************/
KsTexture* KsModel::findTexture( KsChar* pName )
{
	for( KsUInt32 i=0; i<m_vpTextures.size(); i++ )
	{
		if( ks_strcmp( m_vpTextures[ i ]->getName(), pName ) == 0 )
		{
			return m_vpTextures[ i ];
		}
	}

	return NULL;
}

/************************************************************************************************/
/*
 * �e�q�֌W���\�z����
 */
/************************************************************************************************/
void KsModel::createHierarchy()
{
	m_pRoot = m_vpBones[ 0 ];

	for( KsUInt32 i=1; i<m_vpBones.size(); i++ )
	{
		m_vpBones[ i ]->m_pParent = m_vpBones[ m_vpBones[ i ]->m_parent ];
		m_vpBones[ i ]->m_pParent->m_vpChildren.push_back( m_vpBones[ i ] );
	}

	// AbsoluteMatrix���\�z����
	calculateAbsoluteTransforms( m_pRoot );

	// InverseMatrix���\�z����
	for( KsUInt32 i=0; i<m_vpBones.size(); i++ )
	{
		KsBone*		pBone = m_vpBones[ i ];
		pBone->m_inverseTransform = pBone->m_worldTransform.inverse();
	}
}

/************************************************************************************************/
/*
 * �}�e���A�����\�z����
 */
/************************************************************************************************/
void KsModel::createMaterial()
{
	for( KsUInt32 i=0; i<m_vpMeshes.size(); i++ )
	{
		KsMesh* pMesh = m_vpMeshes[ i ];

		for( KsUInt32 j=0; j<pMesh->getMeshPartCount(); j++ )
		{
			KsMeshPart*	pMeshPart = pMesh->getMeshPart( j );
			KsEffect*	pEffect   = m_vpEffects[ pMeshPart->getEffectID() ];
			
			pMeshPart->setEffect( pEffect );
		}
	}
}




