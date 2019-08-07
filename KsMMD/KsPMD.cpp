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
/*                                 << �C���N���[�h >>                                             */
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
 * PMD�t�@�C���ǂݍ��ݏ���
 * @param	filePath	�t�@�C���p�X
 * @return	PMD�t�@�C���f�[�^
 */
/*************************************************************************************************/
KS_PMD_DATA* KsLoadPMDFile( KsFileObject* pFile )
{
	KS_PMD_DATA*	pPMD  = new KS_PMD_DATA();

	// PMD �w�b�_�[�ǂݍ���
	pFile->read( &pPMD->Header, sizeof( KS_PMD_HEADER ) );

	// Vertex�����擾
	const	KsUInt32		VertexCount = pFile->readUInt32();
			KS_PMD_VERTEX*	Vertices    = new KS_PMD_VERTEX[ VertexCount ];

	pFile->read( Vertices, sizeof(KS_PMD_VERTEX) * VertexCount );

	// �C���f�b�N�X���ǂݍ���
	const	KsUInt32		IndexCount = pFile->readUInt32();
			KsUInt16*		Indices    = new KsUInt16[ IndexCount ];

	pFile->read( Indices, sizeof(KsUInt16) * IndexCount );

	// �}�e���A�����ǂݍ���
	const	KsUInt32			MaterialCount = pFile->readUInt32();
			KS_PMD_MATERIAL*	Materials     = new KS_PMD_MATERIAL[ MaterialCount ];

	pFile->read( Materials, sizeof(KS_PMD_MATERIAL) * MaterialCount );

	// �{�[�����ǂݍ���
	const	KsUInt16			BoneCount = pFile->readUInt16();
			KS_PMD_BONE*		Bones     = new KS_PMD_BONE[ BoneCount ];

	pFile->read( Bones, sizeof(KS_PMD_BONE) * BoneCount );

	// IK���ǂݍ���
	const	KsUInt16			IKCount = pFile->readUInt16();
			KS_PMD_IK*			IKList  = new KS_PMD_IK[ IKCount ];

	for( KsUInt16 i=0; i<IKCount; i++ )
	{
		KS_PMD_IK*	ik = &IKList[ i ];

		ik->BoneIndex        = pFile->readUInt16();
		ik->TargetBoneIndex  = pFile->readUInt16();
		ik->ChainLength      = pFile->readUInt8();
		ik->Iterations       = pFile->readUInt16();
		ik->ControlWeight    = pFile->readReal() * ksPI;
		ik->ChildBoneIndices = new KsUInt16[ ik->ChainLength ];

		pFile->read( ik->ChildBoneIndices, sizeof(KsUInt16) * ik->ChainLength );
	}

	//  �\����擾
	const	KsUInt16			FacialCount = pFile->readUInt16();
			KS_PMD_FACIAL*		FacialList  = new KS_PMD_FACIAL[ FacialCount ];
			
	for( KsUInt16 i=0; i<FacialCount; i++ )
	{
		KS_PMD_FACIAL*	facial = &FacialList[ i ];

		pFile->read( facial->Name, 20 );

		facial->VertexCount = pFile->readUInt32();
		facial->Type        = pFile->readUInt8();
		facial->Vertices    = new KS_PMD_FACIAL_VERTEX[ facial->VertexCount ];

		pFile->read( facial->Vertices, sizeof(KS_PMD_FACIAL_VERTEX) * facial->VertexCount );
	}

	// �\���p(���ɕK�v�Ȃ�)
	const	KsUInt8				FacialDispCount = pFile->readUInt8();
			KsUInt16*			FacialIndices   = new KsUInt16[ FacialDispCount ];

	pFile->read( FacialIndices, sizeof(KsUInt16) * FacialDispCount );

	// �\���p(���ɕK�v�Ȃ�)
	const	KsUInt8				NameDispCount = pFile->readUInt8();
			KS_PMD_NAME_50*		DispNames     = new KS_PMD_NAME_50[ NameDispCount ];

	pFile->read( DispNames, sizeof(KS_PMD_NAME_50) * NameDispCount );

	// �\���p(���ɕK�v�Ȃ�)
	const	KsUInt32			BoneDispCount = pFile->readUInt32();
			KS_PMD_BONE_DISP*	BoneDisp      = new KS_PMD_BONE_DISP[ BoneDispCount ];

	pFile->read( BoneDisp, sizeof(KS_PMD_BONE_DISP) * BoneDispCount );

	const KsUInt8 bEnglishNameExist = pFile->readUInt8();
	
	if( 1 == bEnglishNameExist )
	{
		// ���f�����ƃR�����g(�p��)
		KS_PMD_NAME_20  modelName;
		KS_PMD_NAME_256 comment;
		KS_PMD_NAME_20  boneName;
		KS_PMD_NAME_20  facialName;
		KS_PMD_NAME_50  boneDispName;

		pFile->read( &modelName, sizeof(KS_PMD_NAME_20) );
		pFile->read( &comment,   sizeof(KS_PMD_NAME_256) );

		// �{�[����(�p��)
		for( KsUInt16 i=0; i<BoneCount; i++ )
		{
			pFile->read( &boneName, sizeof(KS_PMD_NAME_20) );
		}

		for( KsUInt16 i=0; i<FacialCount-1; i++ )
		{
			pFile->read( &facialName, sizeof(KS_PMD_NAME_20) );
		}

		for( KsUInt8 i=0; i<NameDispCount; i++ )
		{
			pFile->read( &boneDispName, sizeof(KS_PMD_NAME_50) );
		}
	}

	// �g�D�[���e�N�X�`�����X�g
	pFile->read( &pPMD->ToonTextureNameList, sizeof(KS_PMD_TOON_TEXTURE_NAME_LIST) );

	KsUInt32			RigidBodyCount  = 0;
	KS_PMD_RIGID_BODY*	RigidBodyList   = NULL;
	KsUInt32			ConstraintCount = 0;
	KS_PMD_CONSTRAINT*	ConstraintList  = NULL;

	// �g���f�[�^�����邩�ǂ���
	if( pFile->tell() < pFile->getSize() )
	{
		RigidBodyCount = pFile->readUInt32();

		if( RigidBodyCount > 0 )
		{
			RigidBodyList = new KS_PMD_RIGID_BODY[ RigidBodyCount ];

			pFile->read( RigidBodyList, sizeof(KS_PMD_RIGID_BODY) * RigidBodyCount );
		}

		ConstraintCount =  pFile->readUInt32();
					
		if( ConstraintCount > 0 )
		{
			ConstraintList = new KS_PMD_CONSTRAINT[ ConstraintCount ];

			pFile->read( ConstraintList, sizeof(KS_PMD_CONSTRAINT) * ConstraintCount );
		}
	}
	
	pPMD->VertexList.VertexCount         = VertexCount;
	pPMD->VertexList.Vertices            = Vertices;
	pPMD->IndexList.IndexCount           = IndexCount;
	pPMD->IndexList.Indices              = Indices;
	pPMD->MaterialList.MaterialCount     = MaterialCount;
	pPMD->MaterialList.Materials         = Materials;
	pPMD->BoneList.BoneCount             = BoneCount;
	pPMD->BoneList.Bones                 = Bones;
	pPMD->IKList.IKCount                 = IKCount;
	pPMD->IKList.IKList                  = IKList;
	pPMD->FacialDispList.DispCount       = FacialDispCount;
	pPMD->FacialDispList.FacialIndices   = FacialIndices;
	pPMD->BoneNameDispList.DispCount     = NameDispCount;
	pPMD->BoneNameDispList.Names         = DispNames;
	pPMD->BoneDispList.DispCount         = BoneDispCount;
	pPMD->BoneDispList.BoneDisp          = BoneDisp;
	pPMD->RigidBodyList.RigidBodyCount   = RigidBodyCount;
	pPMD->RigidBodyList.RigidBodyList    = RigidBodyList;
	pPMD->ConstraintList.ConstraintCount = ConstraintCount;
	pPMD->ConstraintList.ConstraintList  = ConstraintList;

	ksDELETE( pFile );

	return pPMD;
}

/*************************************************************************************************/
/*
 * PMD�t�@�C���ǂݍ��ݏ���
 * @param	filePath	�t�@�C���p�X
 * @return	PMD�t�@�C���f�[�^
 */
/*************************************************************************************************/
KS_PMD_DATA* KsLoadPMDFile( const KsString& filePath )
{
	KsFileObject*	pFile = new KsFileBuffer( filePath, ksREAD | ksBINARY );

	return KsLoadPMDFile( pFile );
}

/*************************************************************************************************/
/*
 * PMD�t�@�C���ǂݍ��ݏ���
 * @param	filePath	�t�@�C���p�X
 * @return	PMD�t�@�C���f�[�^
 */
/*************************************************************************************************/
KsHumanIK* KsHumanIKCreateFromPMD( KS_PMD_DATA*	pPMD, KsModel* pModel )
{
	KsHumanIK*	pHumanIK = new KsHumanIK( pModel );

	for( KsUInt16 i=0; i<pPMD->IKList.IKCount; i++ )
	{
		KsIKParameter*	pIKParameter = new KsIKParameter();
		KsIKEffector*	pIKEffector  = new KsIKEffector();
	
		KsUInt16 boneIndex = pPMD->IKList.IKList[ i ].BoneIndex;

		KsString boneName = pPMD->BoneList.Bones[ boneIndex ].Name;
		
		boneIndex	= pModel->getBoneIndex( boneName );

		if( boneIndex < 0 ) continue;

		KsUInt16 targetIndex = pPMD->IKList.IKList[ i ].TargetBoneIndex;

		KsString targetName = pPMD->BoneList.Bones[ targetIndex ].Name;
		
		targetIndex	= pModel->getBoneIndex( targetName );

		if( targetIndex < 0 ) continue;

		pIKParameter->BoneIndex       = boneIndex;
		pIKParameter->BoneName        = boneName;
		pIKParameter->TargetBoneIndex = targetIndex;
		pIKParameter->TargetBoneName  = targetName;
		pIKParameter->ControlWeight   = pPMD->IKList.IKList[ i ].ControlWeight;
		pIKParameter->ChainLength     = (KsInt32)pPMD->IKList.IKList[ i ].ChainLength;
		pIKParameter->Iterations      = (KsInt32)pPMD->IKList.IKList[ i ].Iterations;

		KsBone*	pTarget   = pModel->m_vpBones[ boneIndex   ];
		KsBone*	pEffector = pModel->m_vpBones[ targetIndex ];

		KsString childName;

		pIKEffector->m_controlWeight = pPMD->IKList.IKList[ i ].ControlWeight;
		pIKEffector->m_iterations    = (KsInt32)pPMD->IKList.IKList[ i ].Iterations;
		pIKEffector->m_pTarget       = new KsIKPoint( pTarget );
		pIKEffector->m_pEffector     = new KsIKPoint( pEffector );


		for( KsUInt8 j=0; j<pPMD->IKList.IKList[ i ].ChainLength; j++ )
		{
			KsUInt16	childIndex = pPMD->IKList.IKList[ i ].ChildBoneIndices[ j ];

			childName  = pPMD->BoneList.Bones[ childIndex ].Name;
			childIndex = pModel->getBoneIndex( childName );

			KsBone*		pChild   = pModel->m_vpBones[ childIndex ];
			KsIKPoint*	pIKPoint = new KsIKPoint( pChild );

			pIKEffector->m_vpChain.push_back( pIKPoint );

			pIKParameter->ChildBoneIndices.push_back( childIndex );
			pIKParameter->ChildBoneNames.push_back( childName );
		}

		pHumanIK->m_vpParameters.push_back( pIKParameter );
		pHumanIK->m_vpEffectors.push_back( pIKEffector );
	}

	return pHumanIK;
}

/*************************************************************************************************/
/*
 * PMD�t�@�C���ǂݍ��ݏ���
 * @param	filePath	�t�@�C���p�X
 * @return	PMD�t�@�C���f�[�^
 */
/*************************************************************************************************/
KsPhysicsController* KsPhysicsControllerCreateFromPMD( KS_PMD_DATA* pPMD, KsModel* pModel )
{
	KsPhysicsSystem*	pPhysicsSystem = KsPhysicsSystem::getInstancePtr();

	if( NULL == pPhysicsSystem )
	{
		return NULL;
	}

	KsWorld* pWorld = pPhysicsSystem->getWorld();

	if( NULL == pWorld )
	{
		return NULL;
	}

	if( 0 == pPMD->RigidBodyList.RigidBodyCount )
	{
		return NULL;
	}

	KsPhysicsController*	pPhysicsController = new KsPhysicsController();

	for( KsUInt32 i=0 ; i < pPMD->RigidBodyList.RigidBodyCount ; i++ )
	{
		KS_PMD_RIGID_BODY*	pPMDRigidBody = &pPMD->RigidBodyList.RigidBodyList[ i ];
		
		KsBone*				pBone     = NULL;
		KsInt32				boneIndex = 0;

		if( pPMDRigidBody->BoneIndex == 0xFFFF )
		{
			boneIndex = pModel->getBoneIndex( "�Z���^�[" );
		}
		else
		{
			boneIndex = pModel->getBoneIndex( pPMD->BoneList.Bones[ pPMDRigidBody->BoneIndex ].Name );
		}

		if( boneIndex >= 0 )
		{
			pBone = pModel->m_vpBones[ boneIndex ];
		}

		KsCollisionShape*	pShape = NULL;
		KsVector3d			halfExtents;

		switch( pPMDRigidBody->ShapeType )
		{
			case ksPMD_SHAPHE_SPHERE:
			{
				halfExtents.x = pPMDRigidBody->Width;
				pShape = pPhysicsSystem->createShape( ksSHAPE_SPHERE, halfExtents );
				break;
			}
			case ksPMD_SHAPHE_BOX:
			{
				halfExtents.x = pPMDRigidBody->Width;
				halfExtents.y = pPMDRigidBody->Height;
				halfExtents.z = pPMDRigidBody->Depth;
				pShape = pPhysicsSystem->createShape( ksSHAPE_BOX, halfExtents );
				break;
			}
			case ksPMD_SHAPHE_CAPSULE:
			{
				halfExtents.x = pPMDRigidBody->Width;
				halfExtents.y = pPMDRigidBody->Height;
				pShape = pPhysicsSystem->createShape( ksSHAPE_CAPSULE, halfExtents );
				break;
			}
			default:
				break;
		}

		// ���ʂƊ����e���\���̐ݒ�
		KsReal		mass = 0.0f;
		KsVector3d	localInertia;

		if( 0 != pPMDRigidBody->RigidBodyType )
		{
			mass = pPMDRigidBody->Mass;
		}

		// �����e���\���̌v�Z
		if( mass != 0.0f )
		{
			pShape->calculateLocalInertia( mass, localInertia );
		}

		// �{�[���̈ʒu�擾
		KsVector3d		BonePos = pBone->getWorldTransform().getTranslate();

		// �{�[���I�t�Z�b�g�p�g�����X�t�H�[���쐬
		KsMatrix4x4		BoneOffset;
		BoneOffset.setEulerZYX( pPMDRigidBody->Rotation.x, pPMDRigidBody->Rotation.y, pPMDRigidBody->Rotation.z );
		BoneOffset.setTranslate( pPMDRigidBody->Position.x, pPMDRigidBody->Position.y, pPMDRigidBody->Position.z );

		// ���̂̏����g�����X�t�H�[���쐬
		KsMatrix4x4		Transform = KsMatrix4x4::IDENTITY;
		Transform.setTranslate( BonePos.x, BonePos.y, BonePos.z );
		Transform = BoneOffset * Transform;

		KsMotionState*		pMotionState = NULL;

		switch( pPMDRigidBody->RigidBodyType )
		{
			case 0 :
			{
				pMotionState = pPhysicsSystem->createMotionState( ksMOTION_STATE_KINEMATIC, &Transform, &BoneOffset, pBone );
				break;
			}
			case 1 :
			{
				pMotionState = pPhysicsSystem->createMotionState( ksMOTION_STATE_DEFAULT, &Transform );
				break;
			}
			case 2 :
			{
				pMotionState = pPhysicsSystem->createMotionState( ksMOTION_STATE_DEFAULT, &Transform );
				break;
			}
			//case 2 : pMotionState = new btKinematicMotionState( Transform, bttrBoneOffset, pBone );	break;
			default:
				break;
		}

		// ���̂̃p�����[�^�̐ݒ�
		KsRigidBody::KsRigidBodyConstructionInfo	info( mass, pMotionState, pShape, localInertia );

		info.m_linearDamping     = pPMDRigidBody->LinearDamping;	// �ړ���
		info.m_angularDamping    = pPMDRigidBody->AngularDamping;	// ��]��
		info.m_restitution       = pPMDRigidBody->Restitution;		// ������
		info.m_friction          = pPMDRigidBody->Friction;			// ���C��
		info.m_additionalDamping = ksTRUE;

		KsRigidBody*	pRigidBody = pPhysicsSystem->createRigidBody( info );

		// Kinematic�ݒ�
		if( 0 == pPMDRigidBody->RigidBodyType )
		{
			pRigidBody->setCollisionFlags( pRigidBody->getCollisionFlags() | ksCF_KINEMATIC_OBJECT );
			pRigidBody->setActivationState( ksDISABLE_DEACTIVATION );
		}

		pRigidBody->setSleepingThresholds( 0.0f, 0.0f );

		// ���̂��V�~�����[�V�������[���h�ɒǉ�
		pWorld->addRigidBody( pRigidBody, 0x0001 << pPMDRigidBody->ColGroupIndex, pPMDRigidBody->ColGroupMask );

		// RigidBody�ǉ�
		pPhysicsController->addRigidBody( pRigidBody );

		// �p�����[�^����
		KsPhysicsParameter*	pParameter = ksNew KsPhysicsParameter();

		pParameter->m_type          = pPMDRigidBody->RigidBodyType;
		pParameter->m_boneOffset    = BoneOffset;
		pParameter->m_invBoneOffset = BoneOffset.inverse();
		pParameter->m_pBone         = pBone;
		pParameter->m_pRigidBody    = pRigidBody;

		if( pBone->getName() == "�Z���^�[" )
		{
			pParameter ->m_noCopyToBone  = ksTRUE;
		}

		pPhysicsController->addParameter( pParameter );
	}

	// �R���X�g���C���g
	for( KsUInt32 i=0 ; i < pPMD->ConstraintList.ConstraintCount ; i++ )
	{
		KS_PMD_CONSTRAINT*	pPMDConstraint = &pPMD->ConstraintList.ConstraintList[ i ];

		// �R���X�g���C���g�̃g�����X�t�H�[�����쐬
		KsMatrix4x4		bttrTransform;
		bttrTransform.setEulerZYX( pPMDConstraint->Rotation.x, pPMDConstraint->Rotation.y, pPMDConstraint->Rotation.z );
		bttrTransform.setTranslate( pPMDConstraint->Position.x, pPMDConstraint->Position.y, pPMDConstraint->Position.z );

		KsRigidBody*	pRigidBodyA = pPhysicsController->getRigidBody( pPMDConstraint->RigidA );
		KsRigidBody*	pRigidBodyB = pPhysicsController->getRigidBody( pPMDConstraint->RigidB );

		// ����A,B���猩���R���X�g���C���g�̃g�����X�t�H�[�����쐬 
		KsMatrix4x4		bttrRigidAInvTransform = pRigidBodyA->getWorldTransform().inverse();
		KsMatrix4x4		bttrRigidBInvTransform = pRigidBodyB->getWorldTransform().inverse();

		//bttrRigidAInvTransform = bttrRigidAInvTransform * bttrTransform;
		//bttrRigidBInvTransform = bttrRigidBInvTransform * bttrTransform;

		bttrRigidAInvTransform = bttrTransform * bttrRigidAInvTransform;
		bttrRigidBInvTransform = bttrTransform * bttrRigidBInvTransform;

		KsPhysicsParameter*	pParameterA = pPhysicsController->getParameter( pPMDConstraint->RigidA );
		KsPhysicsParameter*	pParameterB = pPhysicsController->getParameter( pPMDConstraint->RigidB );

		KsSpringConstraint* pConstraint = (KsSpringConstraint*)pPhysicsSystem->createConstraint( ksCONSTRAINT_SPRING, *pRigidBodyA, *pRigidBodyB, bttrRigidAInvTransform, bttrRigidBInvTransform, ksTRUE );

		// �e�퐧���p�����[�^�̃Z�b�g
		pConstraint->setLinearLowerLimit( pPMDConstraint->PosLimitL.x, pPMDConstraint->PosLimitL.y, pPMDConstraint->PosLimitL.z );
		pConstraint->setLinearUpperLimit( pPMDConstraint->PosLimitL.x, pPMDConstraint->PosLimitL.y, pPMDConstraint->PosLimitL.z );

		pConstraint->setAngularLowerLimit( pPMDConstraint->RotLimitL.x, pPMDConstraint->RotLimitL.y, pPMDConstraint->RotLimitL.z );
		pConstraint->setAngularUpperLimit( pPMDConstraint->RotLimitL.x, pPMDConstraint->RotLimitL.y, pPMDConstraint->RotLimitL.z );

		// 0 : translation X
		if( pPMDConstraint->SpringPos.x != 0.0f )
		{
			pConstraint->enableSpring( 0, ksTRUE );
			pConstraint->setStiffness( 0, pPMDConstraint->SpringPos.x );
		}

			// 1 : translation Y
		if( pPMDConstraint->SpringPos.y != 0.0f )
		{
			pConstraint->enableSpring( 1, ksTRUE );
			pConstraint->setStiffness( 1, pPMDConstraint->SpringPos.y );
		}

			// 2 : translation Z
		if( pPMDConstraint->SpringPos.z != 0.0f )
		{
			pConstraint->enableSpring( 2, ksTRUE );
			pConstraint->setStiffness( 2, pPMDConstraint->SpringPos.z );
		}

		pConstraint->enableSpring( 3, ksTRUE );	pConstraint->setStiffness( 3, pPMDConstraint->SpringRot.x );
		pConstraint->enableSpring( 4, ksTRUE );	pConstraint->setStiffness( 4, pPMDConstraint->SpringRot.y );
		pConstraint->enableSpring( 5, ksTRUE );	pConstraint->setStiffness( 5, pPMDConstraint->SpringRot.z );

		pPhysicsController->addConstraint( pConstraint );

		// �V�~�����[�V�������[���h�ɒǉ�
		pWorld->addConstraint( pConstraint );
	}

	return pPhysicsController;
}

/*************************************************************************************************/
/*
 * PMD�t�@�C���ǂݍ��ݏ���
 * @param	filePath	�t�@�C���p�X
 * @return	PMD�t�@�C���f�[�^
 */
/*************************************************************************************************/
KsModel* KsModelCreateFromPMD( KS_PMD_DATA*	pPMD, KsUInt32 flags )
{
	KsRenderSystem*				pRenderSystem          = KsRenderSystem::getInstancePtr();
	KsShaderManager*			pShaderManager         = KsShaderManager::getInstancePtr();
	KsInputLayoutManager*		pInputLayoutManager    = KsInputLayoutManager::getInstancePtr();
	KsHardwareBufferManager*	pBufferManager         = KsHardwareBufferManager::getInstancePtr();

	KsVertexShader*				pVS = (KsVertexShader*)pShaderManager->createFromFile( "GBuffer.fx", "VS_GBuffer", ksSHADE_MODEL_5_0, ksVERTEX_SHADER );	// Vertex Shader 
	KsPixelShader*				pPS = (KsPixelShader*)pShaderManager->createFromFile(  "GBuffer.fx", "PS_GBuffer",  ksSHADE_MODEL_5_0, ksPIXEL_SHADER );	// Pixel Shader
	KsInputLayout*				pIL = pInputLayoutManager->createInputLayout( InputLayoutMMD, ksARRAYSIZE( InputLayoutMMD ), (KsVertexShader*)pVS );		// Input Layout
	KsConstantBuffer*			pCB = pBufferManager->createConstantBuffer( KsGBufferParameter::Size, 0 );													// Constant Buffer
	KsConstantBuffer*			pMB = pBufferManager->createConstantBuffer( KsMatrixPalletParameter::Size, 0 );												// Constant Buffer

	// ���f���r���_�[
	KsModelBuilder			builder;
	const KsInt32			materialCount = static_cast< KsInt32 >( pPMD->MaterialList.MaterialCount );	// �}�e���A���P�ʂŃp�[�c��������
	const KsInt32			boneCount     = static_cast< KsInt32 >( pPMD->BoneList.BoneCount );
	const KsUInt32			numVertex     = pPMD->VertexList.VertexCount;
	KS_MMD_VERTEX*			pVertices     = new KS_MMD_VERTEX[ numVertex ];
	KS_MMD_VERTEX*			pVertices_New = new KS_MMD_VERTEX[ numVertex ];
	KsUInt32				offset        = 0;
	KsVector3d				headPos;

	// ���f�������J�n
	KsModel*	pModel = builder.start( pPMD->Header.ModelName, boneCount );

	// �e�𔲂��o��
	for( KsInt32 i=0; i<boneCount; i++ )
	{
		KsBone*	pBone = new KsBone();

		pBone->m_name    = pPMD->BoneList.Bones[ i ].Name;
		pBone->m_index   = i + 1;

		// ���[�g���ǂ������`�F�b�N����
		if( 0xFFFF == pPMD->BoneList.Bones[ i ].Parent )
		{
			headPos.set( pPMD->BoneList.Bones[ i ].HeadPos.x, pPMD->BoneList.Bones[ i ].HeadPos.y, pPMD->BoneList.Bones[ i ].HeadPos.z );

			pBone->m_parent           = 0;
			pBone->m_defaultTransform = KsMatrix4x4::CreateTranslation( headPos );
		}
		else
		{
			headPos.set(	pPMD->BoneList.Bones[ i ].HeadPos.x - pPMD->BoneList.Bones[ pPMD->BoneList.Bones[ i ].Parent ].HeadPos.x,
							pPMD->BoneList.Bones[ i ].HeadPos.y - pPMD->BoneList.Bones[ pPMD->BoneList.Bones[ i ].Parent ].HeadPos.y,
							pPMD->BoneList.Bones[ i ].HeadPos.z - pPMD->BoneList.Bones[ pPMD->BoneList.Bones[ i ].Parent ].HeadPos.z );
			
			pBone->m_parent           = pPMD->BoneList.Bones[ i ].Parent + 1;
			pBone->m_defaultTransform = KsMatrix4x4::CreateTranslation( headPos );
		}

		// �t�}�g���b�N�X�𐶐�����
		builder.addBone( pBone );
	}

	// �e�q�֌W���\�z����
	builder.createHierarchy();

	// AbsoluteMatrix���\�z����
	builder.createAbsoluteTransforms();

	// ���_���g���₷���`�ɕϊ����Ȃ���
	for( KsUInt32 vi = 0; vi < numVertex; vi++ )
	{
		KS_PMD_VERTEX*	pPMD_Vertices = &pPMD->VertexList.Vertices[ vi ];

		pVertices[ vi ].x = pPMD_Vertices->Pos.x;
		pVertices[ vi ].y = pPMD_Vertices->Pos.y;
		pVertices[ vi ].z = pPMD_Vertices->Pos.z;

		pVertices[ vi ].nx = pPMD_Vertices->Normal.x;
		pVertices[ vi ].ny = pPMD_Vertices->Normal.y;
		pVertices[ vi ].nz = pPMD_Vertices->Normal.z;

		pVertices[ vi ].u = pPMD_Vertices->UV.x;
		pVertices[ vi ].v = pPMD_Vertices->UV.y;

		pVertices[ vi ].indices_16[ 0 ] = builder.getMatrixPalletIndex( pPMD_Vertices->Bone1 + 1 );
		pVertices[ vi ].indices_16[ 1 ] = builder.getMatrixPalletIndex( pPMD_Vertices->Bone2 + 1 );
		//pVertices[ vi ].indices[ 2 ] = 0;
		//pVertices[ vi ].indices[ 3 ] = 0;

		pVertices[ vi ].weight[ 0 ] = static_cast<KsReal>( pPMD_Vertices->Weight ) * 0.01f;
		pVertices[ vi ].weight[ 1 ] = 1.0f - pVertices[ vi ].weight[ 0 ];
		pVertices[ vi ].weight[ 2 ] = 0.0f;
		pVertices[ vi ].weight[ 3 ] = 0.0f;
	}

	KsUInt32 fs = 0;
	KsUInt32 fe = 0;

	for( KsInt32 mi=0; mi<materialCount; mi++ )
	{
		KS_PMD_MATERIAL*	pPMD_Material = &pPMD->MaterialList.Materials[ mi ];
		KsUInt32			numFaceVertex = static_cast<KsUInt32>( pPMD_Material->FaceVertCount );
		KsBool				hasTexture    = ksFALSE;

		KsEffectMMD*		pMaterial = new KsEffectMMD();

		// �}�e���A���p�����[�^���Z�b�g����
		pMaterial->setDiffuse(  pPMD_Material->Diffuse.x,  pPMD_Material->Diffuse.y,  pPMD_Material->Diffuse.z,  pPMD_Material->Alpha );
		pMaterial->setAmbient(  pPMD_Material->Ambient.x,  pPMD_Material->Ambient.y,  pPMD_Material->Ambient.z,  1.0f );
		pMaterial->setSpecular( pPMD_Material->Specular.x, pPMD_Material->Specular.y, pPMD_Material->Specular.z, 1.0f );
		pMaterial->setSpecularity( pPMD_Material->Specularity );
		pMaterial->m_pVS = pVS;
		pMaterial->m_pPS = pPS;
		pMaterial->m_pCB = pCB;
		pMaterial->m_pMB = pMB;

		if( ks_strlen( pPMD_Material->TextureName ) > 0 )
		{
			pMaterial->setDiffuseTextureName( pPMD_Material->TextureName );
			hasTexture = ksTRUE;

			KsTexture*	pTexture = NULL;

			if( 0 == flags )
			{
				KsChar		DataPath[512];
				strcpy( DataPath, MODEL_DATA_PATH );
				strcat( DataPath, pPMD_Material->TextureName );

				// Texture��ǂݍ���
				pTexture = pRenderSystem->createTextureFromFile( DataPath, 0 );
			}
			else
			{
				pTexture = pRenderSystem->createTexture( NULL, 1, 1, KS_GI_FORMAT_R8G8B8A8_UNORM, 0, 0 );
				pTexture->setName( pPMD_Material->TextureName );
			}

			pMaterial->setDiffuseTexture( pTexture );
			
		}

		//
		fs  = fe;
		fe += numFaceVertex;

		KsUInt32	numIndex     = pPMD->IndexList.IndexCount;
		KsUInt16*	pIndexMap    = new KsUInt16[ numIndex ];
		KsUInt16*	pIndices_New = new KsUInt16[ numIndex ];
		KsUInt32	vertexCount  = 0;
		KsUInt32	indexCount   = 0;

		memset( pIndexMap, 0xffff, sizeof(KsUInt16) * numIndex );

		for( KsUInt32 i=fs; i<fe; i++ )
		{
			const KsUInt16 face    = pPMD->IndexList.Indices[ i ];
			
			if( pIndexMap[ face ] == 0xffff )
			{
				pIndexMap[ face ] = vertexCount;

				pVertices_New[ vertexCount ] = pVertices[ face ];

				++vertexCount;
			}

			pIndices_New[ indexCount ] = pIndexMap[ face ];
			
			++indexCount;
		}

		// ���b�V���p�[�c��������
		builder.createMeshPart( pMaterial, pIL, vertexCount, &pVertices_New[ 0 ], indexCount, &pIndices_New[ 0 ] );

		offset += numFaceVertex;

		ksDELETEARRAY( pIndexMap );
		ksDELETEARRAY( pIndices_New );
	}

	builder.finish();

	return pModel;
}

/*************************************************************************************************/
/*
 * PMD�t�@�C���ǂݍ��ݏ���
 * @param	filePath	�t�@�C���p�X
 * @return	PMD�t�@�C���f�[�^
 */
/*************************************************************************************************/
KsModel* KsModelCreateFromPMD( const KsString& filePath )
{
	KS_PMD_DATA*	pPMD = KsLoadPMDFile( filePath );

	if( NULL == pPMD )
	{
		return NULL;
	}

	return KsModelCreateFromPMD( pPMD );
}

/*************************************************************************************************/
/*
 * PMD�t�@�C���ǂݍ��ݏ���
 * @param	filePath	�t�@�C���p�X
 * @return	PMD�t�@�C���f�[�^
 */
/*************************************************************************************************/
KsActor* KsActorCreateFromPMD( const KsString& filePath )
{
	KS_PMD_DATA*	pPMD = KsLoadPMDFile( filePath );

	if( NULL == pPMD )
	{
		return NULL;
	}

	KsModel*				pModel   = KsModelCreateFromPMD( pPMD );
	KsHumanIK*				pHumanIK = KsHumanIKCreateFromPMD( pPMD, pModel );
	KsPhysicsController*	pPhysics = KsPhysicsControllerCreateFromPMD( pPMD, pModel );
	KsActor*				pActor   = new KsActor( pModel );

	pActor->setHumanIK( pHumanIK );
	pActor->setPhysics( pPhysics );

	return pActor;
}

class KsModelKMD
{
	public:
		KsArray<KsString>			m_vTextures;		
};


#if 0



struct KS_KMD_INFO
{
	KsUInt32			MeshCount;
	KS_KMD_MESH*		Meshes;
	KsUInt32			BoneCount;
	KS_KMD_BONE*		Bones;

		KsMeshCollection			m_vpMeshes;		/// �I�u�W�F�N�g�̃R���N�V����
		KsBoneCollection			m_vpBones;		/// �{�[���R���N�V����
		KsBone*						m_pRoot;		/// ���[�g�{�[��
		KsModelParameter*			m_pParameter;	/// ���f���p�����[�^
		//KsUserData*				m_pUserData;	/// ���[�U�[�f�[�^

#endif

/*************************************************************************************************/
/*
 * PMD�t�@�C���ǂݍ��ݏ���
 * @param	filePath	�t�@�C���p�X
 * @return	PMD�t�@�C���f�[�^
 */
/*************************************************************************************************/
void* KsModelConvertFromPMD( const KsString& filePath )
{
	KS_PMD_DATA*	pPMD = KsLoadPMDFile( filePath );

	if( NULL == pPMD )
	{
		return NULL;
	}

	//return KsModelCreateFromPMD( pPMD );

	return NULL;
}


