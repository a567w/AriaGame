/************************************************************************************************/
/** 
 * @file		KsKMD.cpp
 * @brief		KMDファイル
 * @author		Tsukasa Kato
 * @date		2010/12/17
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                          */
/*==============================================================================================*/
#include "KsMMD/KsMMDPreCompile.h"
#include "KsKMD.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/*************************************************************************************************/
/*
 * KMDファイル読み込み処理
 * @param	filePath	ファイルパス
 * @return	KMDファイルデータ
 */
/*************************************************************************************************/
KsKmdLoader::KsKmdLoader( KsFileObject* pFile )
	: m_pFile( pFile )
{
	m_pRenderSystem          = KsRenderSystem::getInstancePtr();
	m_pBufferManager         = KsHardwareBufferManager::getInstancePtr();
	m_pShaderManager         = KsShaderManager::getInstancePtr();
	m_pInputLayoutManager    = KsInputLayoutManager::getInstancePtr();

	m_pVS = (KsVertexShader*)m_pShaderManager->createFromFile( "GBuffer.fx", "VS_GBuffer", ksSHADE_MODEL_5_0, ksVERTEX_SHADER );	// Vertex Shader 
	m_pPS = (KsPixelShader* )m_pShaderManager->createFromFile( "GBuffer.fx", "PS_GBuffer", ksSHADE_MODEL_5_0, ksPIXEL_SHADER  );	// Pixel Shader
	m_pIL = m_pInputLayoutManager->createInputLayout( InputLayoutMMD, ksARRAYSIZE( InputLayoutMMD ), (KsVertexShader*)m_pVS );		// Input Layout
	m_pCB = m_pBufferManager->createConstantBuffer( KsGBufferParameter::Size, 0 );													// Constant Buffer
	m_pMB = m_pBufferManager->createConstantBuffer( KsMatrixPalletParameter::Size, 0 );		

	//m_DataPath = "D:\\MMD\\";
	m_DataPath = "D:\\KGDC\\Aria\\data\\Model\\bg\\";

	m_pHumanIK = NULL;
	m_pPhysics = NULL;
}

/*************************************************************************************************/
/*
 * KMDファイル読み込み処理
 * @param	filePath	ファイルパス
 * @return	KMDファイルデータ
 */
/*************************************************************************************************/
KsBone* KsKmdLoader::readBone()
{
	KS_KMD_BONE		Bone;

	m_pFile->read( &Bone, sizeof(KS_KMD_BONE) );

	KsBone*	pBone = ksNew KsBone();

	pBone->m_index            = Bone.Index;
	pBone->m_parent           = Bone.Parent;
	pBone->m_defaultTransform = KsMatrix4x4::CreateTranslation( Bone.Position );
	pBone->m_name             = Bone.Name;

	return pBone;
}

/*************************************************************************************************/
/*
 * KMDファイル読み込み処理
 * @param	filePath	ファイルパス
 * @return	KMDファイルデータ
 */
/*************************************************************************************************/
KsMesh* KsKmdLoader::readMesh( KsModel* pModel )
{
	const KsUInt32 meshPartCount = m_pFile->readUInt32();

	KsMesh*	pMesh = ksNew KsMesh();

	for( KsUInt32 i=0; i<meshPartCount; i++ )
	{
		const KsUInt32	MeshPartsSize     = m_pFile->readUInt32();				// メッシュパーツサイズ
		const KsUInt32	IndexType         = m_pFile->readUInt32();				// 頂点インデックスのタイプ
		const KsUInt32	IndexCount        = m_pFile->readUInt32();				// 頂点インデックス数
		const KsUInt32	IndexSize         = m_pFile->readUInt32();				// 頂点インデックスサイズ
		const KsUInt32	IndexDataSize     = IndexCount * IndexSize;				// 頂点インデックスデータサイズ
			  KsByte*	IndexData         = ksNew KsByte[ IndexDataSize ];		// 頂点インデックスデータ

		m_pFile->read( IndexData, IndexDataSize );

		const KsUInt32	VertexType        = m_pFile->readUInt32();				// 頂点データのタイプ
		const KsUInt32	VertexCount       = m_pFile->readUInt32();				// 頂点データの数
		const KsUInt32	VertexSize        = m_pFile->readUInt32();				// 頂点サイズ
		const KsUInt32	VertexDataSize    = VertexCount * VertexSize;			// 頂点データサイズ
			  KsByte*	VertexData        = ksNew KsByte[ VertexDataSize ];		// 頂点データ

		m_pFile->read( VertexData, VertexDataSize );

		const KsInt32	PrimitiveCount    = m_pFile->readUInt32();				// レンダリングするプリミティブの数
		const KsUInt32	StartIndex        = m_pFile->readUInt32();				// インデックス配列の中で頂点の読み取りを開始する位置
		const KsUInt32	StartVertex       = m_pFile->readUInt32();				// 頂点バッファーの最上部からのオフセット
		const KsUInt32	EffectID          = m_pFile->readUInt32();				// エフェクトID
		const KsUInt32	MatrixPalletCount = m_pFile->readUInt32();				// 使用マトリックスパレット数

			  KsInt32*	MatrixPalletData  = ksNew KsInt32[ MatrixPalletCount ];	/// 使用マトリックスパレット

		m_pFile->read( MatrixPalletData, sizeof(KsInt32) * MatrixPalletCount );

		const KsUInt32	BoneCount         = m_pFile->readUInt32();				// ボーン数
			  KsInt32*	BoneData          = ksNew KsInt32[ BoneCount ];			// ボーンデータ

		m_pFile->read( BoneData, sizeof(KsInt32) * BoneCount );

		KsVertexBuffer*	pVertexBuffer = m_pBufferManager->createVertexBuffer( VertexData, VertexSize, VertexCount, ksMMD_FVF, ksCPU_ACCESS_WRITE );
		KsIndexBuffer*	pIndexBuffer  = m_pBufferManager->createIndexBuffer( IndexData, IndexDataSize, IndexCount, ksFMT_INDEX16, 0 );
		KsMeshPart*		pMeshPart     = ksNew KsMeshPart( NULL, pIndexBuffer, pVertexBuffer, m_pIL, VertexCount, IndexCount, 0, 0 );
		
		pMeshPart->setEffectID( EffectID );
		pMeshPart->createPallet( MatrixPalletCount, MatrixPalletData );

		for( KsUInt32 j=0; j<MatrixPalletCount; j++ )
		{
			const KsInt32 index = MatrixPalletData[ j ];
			KsBone* pBone = pModel->m_vpBones[ index ];

			pMeshPart->addBone( pBone );
		}

		pMesh->addMeshParts( pMeshPart );
	}

	return pMesh;
}

/*************************************************************************************************/
/*
 * KMDファイル読み込み処理
 * @param	filePath	ファイルパス
 * @return	KMDファイルデータ
 */
/*************************************************************************************************/
KsEffect* KsKmdLoader::readEffect( KsModel* pModel )
{
	KS_KMD_MMD_MATERIAL		Material;

	m_pFile->read( &Material, sizeof(KS_KMD_MMD_MATERIAL) );

	KsEffectMMD*		pMaterial = new KsEffectMMD();

	// マテリアルパラメータをセットする
	pMaterial->setDiffuse(  Material.Diffuse.x,  Material.Diffuse.y,  Material.Diffuse.z,  Material.Diffuse.w );
	pMaterial->setAmbient(  Material.Ambient.x,  Material.Ambient.y,  Material.Ambient.z,  1.0f );
	pMaterial->setSpecular( Material.Specular.x, Material.Specular.y, Material.Specular.z, 1.0f );
	pMaterial->setSpecularity( Material.Specularity );
	pMaterial->m_pVS = m_pVS;
	pMaterial->m_pPS = m_pPS;
	pMaterial->m_pCB = m_pCB;
	pMaterial->m_pMB = m_pMB;

	pMaterial->setDiffuseTexture( pModel->findTexture( (KsChar*)&Material.TextureName[0] ) );

	return pMaterial;
}

/*************************************************************************************************/
/*
 * KMDファイル読み込み処理
 * @param	filePath	ファイルパス
 * @return	KMDファイルデータ
 */
/*************************************************************************************************/
KsTexture* KsKmdLoader::readTexture()
{
	KS_KMD_TEXTURE		Texture;
	KsTexture*			pTexture;

	m_pFile->read( &Texture, sizeof(KS_KMD_TEXTURE) );

	// テクスチャを生成する
	//KsString	FullPath = m_DataPath + Texture.Name + ".bmp";
	KsString	FullPath = m_DataPath + Texture.Name + ".dds";
	pTexture = m_pRenderSystem->createTextureFromFile( FullPath.c_str(), 0 );
	pTexture->setName( Texture.Name );

	return pTexture;
}

/*************************************************************************************************/
/*
 * KMDファイル読み込み処理
 * @param	filePath	ファイルパス
 * @return	KMDファイルデータ
 */
/*************************************************************************************************/
void KsKmdLoader::readBones( KsModel* pModel, KsUInt16 count )
{
	for( KsUInt16 idx=0; idx < count; idx++ )
	{
		KsBone*	pBone = readBone();

		pModel->addBone( pBone );
	}
}

/*************************************************************************************************/
/*
 * KMDファイル読み込み処理
 * @param	filePath	ファイルパス
 * @return	KMDファイルデータ
 */
/*************************************************************************************************/
void KsKmdLoader::readEffects( KsModel* pModel, KsUInt16 count )
{
	for( KsUInt16 idx=0; idx < count; idx++ )
	{
		KsEffect*	pEffect = readEffect(pModel);
					
		pModel->addEffect( pEffect );
	}
}

/*************************************************************************************************/
/*
 * KMDファイル読み込み処理
 * @param	filePath	ファイルパス
 * @return	KMDファイルデータ
 */
/*************************************************************************************************/
void KsKmdLoader::readTextures( KsModel* pModel, KsUInt16 count )
{
	for( KsUInt16 idx=0; idx < count; idx++ )
	{
		KsTexture*	pTexture = readTexture();

		pModel->addTexture( pTexture );
	}
}

/*************************************************************************************************/
/*
 * KMDファイル読み込み処理
 * @param	filePath	ファイルパス
 * @return	KMDファイルデータ
 */
/*************************************************************************************************/
void KsKmdLoader::readHumanIK( KsModel* pModel, KsUInt16 count )
{
	for( KsUInt16 idx=0; idx < count; idx++ )
	{
	}
}

/*************************************************************************************************/
/*
 * KMDファイル読み込み処理
 * @param	filePath	ファイルパス
 * @return	KMDファイルデータ
 */
/*************************************************************************************************/
void KsKmdLoader::readPhysics( KsModel* pModel, KsUInt16 count )
{
	KsPhysicsSystem*	pPhysicsSystem = KsPhysicsSystem::getInstancePtr();

	if( NULL == pPhysicsSystem )
	{
		return;
	}

	KsWorld* pWorld = pPhysicsSystem->getWorld();

	if( NULL == pWorld )
	{
		return;
	}

	if( 0 == count )
	{
		return;
	}

	KsPhysicsController*	pPhysicsController = ksNew KsPhysicsController();
	KS_KMD_RIGID_BODY		rigidBody;

	for( KsUInt16 idx=0; idx < count; idx++ )
	{
		KsBone*				pBone     = NULL;
		KsInt32				boneIndex = 0;
		
		m_pFile->read( &rigidBody, sizeof(KS_KMD_RIGID_BODY) );

		//pBone = pModel->m_vpBones[ rigidBody.BoneIndex ];
	}
	

#if 0
	KsPhysicsController*	pPhysicsController = ksNew KsPhysicsController();
	KS_KMD_RIGID_BODY		rigidBody;

	for( KsUInt32 i=0 ; i < count; i++ )
	{
		KsBone*				pBone     = NULL;
		KsInt32				boneIndex = 0;

		m_pFile->read( &rigidBody, sizeof(KS_KMD_RIGID_BODY) );

		if( pPMDRigidBody->BoneIndex == 0xFFFF )
		{
			boneIndex = pModel->getBoneIndex( "センター" );
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

		// 質量と慣性テンソルの設定
		KsReal		mass = 0.0f;
		KsVector3d	localInertia;

		if( 0 != pPMDRigidBody->RigidBodyType )
		{
			mass = pPMDRigidBody->Mass;
		}

		// 慣性テンソルの計算
		if( mass != 0.0f )
		{
			pShape->calculateLocalInertia( mass, localInertia );
		}

		// ボーンの位置取得
		KsVector3d		BonePos = pBone->getWorldTransform().getTranslate();

		// ボーンオフセット用トランスフォーム作成
		KsMatrix4x4		BoneOffset;
		BoneOffset.setEulerZYX( pPMDRigidBody->Rotation.x, pPMDRigidBody->Rotation.y, pPMDRigidBody->Rotation.z );
		BoneOffset.setTranslate( pPMDRigidBody->Position.x, pPMDRigidBody->Position.y, pPMDRigidBody->Position.z );

		// 剛体の初期トランスフォーム作成
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

		// 剛体のパラメータの設定
		KsRigidBody::KsRigidBodyConstructionInfo	info( mass, pMotionState, pShape, localInertia );

		info.m_linearDamping     = pPMDRigidBody->LinearDamping;	// 移動減
		info.m_angularDamping    = pPMDRigidBody->AngularDamping;	// 回転減
		info.m_restitution       = pPMDRigidBody->Restitution;		// 反発力
		info.m_friction          = pPMDRigidBody->Friction;			// 摩擦力
		info.m_additionalDamping = ksTRUE;

		KsRigidBody*	pRigidBody = pPhysicsSystem->createRigidBody( info );

		// Kinematic設定
		if( 0 == pPMDRigidBody->RigidBodyType )
		{
			pRigidBody->setCollisionFlags( pRigidBody->getCollisionFlags() | ksCF_KINEMATIC_OBJECT );
			pRigidBody->setActivationState( ksDISABLE_DEACTIVATION );
		}

		pRigidBody->setSleepingThresholds( 0.0f, 0.0f );

		// 剛体をシミュレーションワールドに追加
		pWorld->addRigidBody( pRigidBody, 0x0001 << pPMDRigidBody->ColGroupIndex, pPMDRigidBody->ColGroupMask );

		// RigidBody追加
		pPhysicsController->addRigidBody( pRigidBody );

		// パラメータ生成
		KsPhysicsParameter*	pParameter = ksNew KsPhysicsParameter();

		pParameter->m_type          = pPMDRigidBody->RigidBodyType;
		pParameter->m_boneOffset    = BoneOffset;
		pParameter->m_invBoneOffset = BoneOffset.inverse();
		pParameter->m_pBone         = pBone;
		pParameter->m_pRigidBody    = pRigidBody;

		if( pBone->getName() == "センター" )
		{
			pParameter ->m_noCopyToBone  = ksTRUE;
		}

		pPhysicsController->addParameter( pParameter );
	}

	// コンストレイント
	for( KsUInt32 i=0 ; i < pPMD->ConstraintList.ConstraintCount ; i++ )
	{
		KS_PMD_CONSTRAINT*	pPMDConstraint = &pPMD->ConstraintList.ConstraintList[ i ];

		// コンストレイントのトランスフォームを作成
		KsMatrix4x4		bttrTransform;
		bttrTransform.setEulerZYX( pPMDConstraint->Rotation.x, pPMDConstraint->Rotation.y, pPMDConstraint->Rotation.z );
		bttrTransform.setTranslate( pPMDConstraint->Position.x, pPMDConstraint->Position.y, pPMDConstraint->Position.z );

		KsRigidBody*	pRigidBodyA = pPhysicsController->getRigidBody( pPMDConstraint->RigidA );
		KsRigidBody*	pRigidBodyB = pPhysicsController->getRigidBody( pPMDConstraint->RigidB );

		// 剛体A,Bから見たコンストレイントのトランスフォームを作成 
		KsMatrix4x4		bttrRigidAInvTransform = pRigidBodyA->getWorldTransform().inverse();
		KsMatrix4x4		bttrRigidBInvTransform = pRigidBodyB->getWorldTransform().inverse();

		//bttrRigidAInvTransform = bttrRigidAInvTransform * bttrTransform;
		//bttrRigidBInvTransform = bttrRigidBInvTransform * bttrTransform;

		bttrRigidAInvTransform = bttrTransform * bttrRigidAInvTransform;
		bttrRigidBInvTransform = bttrTransform * bttrRigidBInvTransform;

		KsPhysicsParameter*	pParameterA = pPhysicsController->getParameter( pPMDConstraint->RigidA );
		KsPhysicsParameter*	pParameterB = pPhysicsController->getParameter( pPMDConstraint->RigidB );

		KsSpringConstraint* pConstraint = (KsSpringConstraint*)pPhysicsSystem->createConstraint( ksCONSTRAINT_SPRING, *pRigidBodyA, *pRigidBodyB, bttrRigidAInvTransform, bttrRigidBInvTransform, ksTRUE );

		// 各種制限パラメータのセット
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

		// シミュレーションワールドに追加
		pWorld->addConstraint( pConstraint );
	}

	return pPhysicsController;
#endif
}

/*************************************************************************************************/
/*
 * KMDファイル読み込み処理
 * @param	filePath	ファイルパス
 * @return	KMDファイルデータ
 */
/*************************************************************************************************/
KsModel* KsKmdLoader::createModel()
{
	KS_KMD_HEADER		Header;
	KS_KMD_CHUNK		Chunk;
	KsModel*			pModel = ksNew KsModel();

	// KMD ヘッダー読み込み
	m_pFile->read( &Header, sizeof( KS_KMD_HEADER ) );

	// KMD チャンク読み込み
	for( KsUInt16 i=0; i<Header.ChunkCount; i++ )
	{
		m_pFile->read( &Chunk, sizeof(KS_KMD_CHUNK) );

		switch( Chunk.Type )
		{
			case ksDATA_CHUNK_MESH:
			{
				// メッシュ読み込み
				KsMesh* pMesh = readMesh( pModel );
				pModel->addMesh( pMesh );
				break;
			}
			case ksDATA_CHUNK_BONE:
			{
				// ボーン読み込み
				readBones( pModel, Chunk.Count );
				break;
			}
			case ksDATA_CHUNK_TEXTURE:
			{
				// テクスチャ読み込み
				readTextures( pModel, Chunk.Count );
				break;
			}
			case ksDATA_CHUNK_EFFECT:
			{
				// エフェクト読み込み
				readEffects( pModel, Chunk.Count );
				break;
			}
			case ksDATA_CHUNK_IK:
			{
				// IKデータ読み込み
				readHumanIK( pModel, Chunk.Count );
				break;
			}
			case ksDATA_CHUNK_PHYSICS:
			{
				// 剛体データ読み込み
				readPhysics( pModel, Chunk.Count );
				break;
			}
			default: break;
		}
	}

	// 親子関係を構築する
	pModel->createHierarchy();

	// テクスチャとマテリアルＩＤを設定する
	pModel->createMaterial();

	return pModel;
}

/*************************************************************************************************/
/*
 * KMDファイル読み込み処理
 * @param	filePath	ファイルパス
 * @return	KMDファイルデータ
 */
/*************************************************************************************************/
KsModel* KsLoadKMDFile( const KsString& filePath )
{
	KsFileObject*	pFile = new KsFileBuffer( filePath, ksREAD | ksBINARY );

	KsKmdLoader		Loader( pFile );

	return Loader.createModel();
}

/*************************************************************************************************/
/*
 * PMDファイル読み込み処理
 * @param	filePath	ファイルパス
 * @return	PMDファイルデータ
 */
/*************************************************************************************************/
KsModel* KsModelCreateFromKMD( KsFileObject* pFile )
{
	KsKmdLoader		Loader( pFile );

	return Loader.createModel();
}

/*************************************************************************************************/
/*
 * PMDファイル読み込み処理
 * @param	filePath	ファイルパス
 * @return	PMDファイルデータ
 */
/*************************************************************************************************/
KsModel* KsModelCreateFromKMD( const KsString& filePath )
{
	return KsLoadKMDFile( filePath );
}

/*************************************************************************************************/
/*
 * PMDファイル読み込み処理
 * @param	filePath	ファイルパス
 * @return	PMDファイルデータ
 */
/*************************************************************************************************/
KsActor* KsActorCreateFromKMD( const KsString& filePath )
{
	return NULL;
#if 0
	KsFileObject*	pFile = new KsFileBuffer( filePath, ksREAD | ksBINARY );

	return KsLoadKMDFile( pFile );

	KsModel*				pModel   = KsModelCreateFromKMD( pPMD );
	KsHumanIK*				pHumanIK = KsHumanIKCreateFromPMD( pPMD, pModel );
	KsPhysicsController*	pPhysics = KsPhysicsControllerCreateFromPMD( pPMD, pModel );
	KsActor*				pActor   = new KsActor( pModel );

	pActor->setHumanIK( pHumanIK );
	pActor->setPhysics( pPhysics );

	return pActor;
#endif
}



