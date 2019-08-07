/************************************************************************************************/
/** 
 * @file		KsPMDConverter.cpp
 * @brief		PMDファイル
 * @author		Tsukasa Kato
 * @date		2010/12/17
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsMMD/KsMMDPreCompile.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
#define KS_MODEL_MESH_SIZE			(4)
#define KS_MODEL_MESH_PARTS_SIZE	(sizeof(KS_MODEL_MESH_PARTS) - 2*sizeof(KsByte*) - 2*sizeof(KsInt32*))

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KS_MODEL_HEADER::KS_MODEL_HEADER()
{
	Signature[0] = 'K';
	Signature[1] = 'M';
	Signature[2] = 'D';
	Signature[3] = '1';
	Version      = 1;
	ChunkCount   = 0;

	KsZeroMemory( ModelName, sizeof(ModelName) );
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KS_MODEL_HEADER::KS_MODEL_HEADER( const KsString& modelName )
{
	Signature[0] = 'K';
	Signature[1] = 'M';
	Signature[2] = 'D';
	Signature[3] = '1';
	Version      = 1;
	ChunkCount   = 0;

	KsUInt32	nameLength = modelName.length();

	if( nameLength > 25 ) { nameLength = 25; }

	KsZeroMemory( ModelName, sizeof(ModelName) );
	KsMemCopy( ModelName, modelName.c_str(), nameLength );
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KS_DATA_CHUNK::KS_DATA_CHUNK( ksDATA_CHUNK_TYPE chunkType, KsUInt16 count, KsUInt32 size )
{
	Type   = (KsUInt16)chunkType;
	Count  = count;
	Size   = size;

	const KsUInt32 bufferSize = Size ? Count * Size : (1024 * 1024);

	pFile  = ksNew KsFileBuffer( NULL, bufferSize, ksOPEN, ksTRUE );
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KS_DATA_CHUNK::~KS_DATA_CHUNK()
{
	ksDELETE( pFile );
}


/************************************************************************************************/
/*
 * ファイルに値を書き込む
 * @param	val				書き込む値
 * @return					書き込んだバイト数
 */
/************************************************************************************************/
KsSize KS_DATA_CHUNK::writeInt16( KsInt16 val )
{
	return pFile->writeInt16( val );
}

/************************************************************************************************/
/*
 * ファイルに値を書き込む
 * @param	val				書き込む値
 * @return					書き込んだバイト数
 */
/************************************************************************************************/
KsSize KS_DATA_CHUNK::writeUInt16( KsUInt16 val )
{
	return pFile->writeUInt16( val );
}

/************************************************************************************************/
/*
 * ファイルに値を書き込む
 * @param	val				書き込む値
 * @return					書き込んだバイト数
 */
/************************************************************************************************/
KsSize KS_DATA_CHUNK::writeInt32( KsInt32 val )
{
	return pFile->writeInt32( val );
}

/************************************************************************************************/
/*
 * ファイルに値を書き込む
 * @param	val				書き込む値
 * @return					書き込んだバイト数
 */
/************************************************************************************************/
KsSize KS_DATA_CHUNK::writeUInt32( KsUInt32 val )
{
	return pFile->writeUInt32( val );
}

/************************************************************************************************/
/*
 * ファイルに値を書き込む
 * @param	val				書き込む値
 * @return					書き込んだバイト数
 */
/************************************************************************************************/
KsSize KS_DATA_CHUNK::writeReal( KsReal val )
{
	return pFile->writeReal( val );
}

/************************************************************************************************/
/*
 * ファイルに値を書き込む
 * @param	val				書き込む値
 * @return					書き込んだバイト数
 */
/************************************************************************************************/
KsSize KS_DATA_CHUNK::writeInt8( KsInt8 val )
{
	return pFile->writeInt8( val );
}

/************************************************************************************************/
/*
 * ファイルに値を書き込む
 * @param	val				書き込む値
 * @return					書き込んだバイト数
 */
/************************************************************************************************/
KsSize KS_DATA_CHUNK::writeUInt8( KsUInt8 val )
{
	return pFile->writeUInt8( val );
}

/************************************************************************************************/
/*
 * ファイルに値を書き込む
 * @param	val				書き込む値
 * @return					書き込んだバイト数
 */
/************************************************************************************************/
KsSize KS_DATA_CHUNK::writeChar( KsChar val )
{
	return pFile->writeChar( val );
}

/************************************************************************************************/
/*
 * ファイルに値を書き込む
 * @param	val				書き込む値
 * @return					書き込んだバイト数
 */
/************************************************************************************************/
KsSize KS_DATA_CHUNK::writeByte( KsInt32 val )
{
	return pFile->writeByte( val );
}

/************************************************************************************************/
/*
 * バッファからファイルに値を書き込む
 * @param	pBuffer			書き込むバッファ
 * @param	count			書き込むバイト数
 * @return					書き込んだバイト数
 */
/************************************************************************************************/
KsUInt32 KS_DATA_CHUNK::write( const void *pBuffer, KsInt32 count )
{
	return pFile->write( pBuffer, count );
}

/************************************************************************************************/
/*
 * チャンクサイズを更新する
 */
/************************************************************************************************/
KsSize KS_DATA_CHUNK::updateSize()
{
	Size = pFile->tell();

	return Size;
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KS_MODEL_DATA::KS_MODEL_DATA( const KsString& modelName )
	: Header( modelName )
{
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KS_MODEL_DATA::KS_MODEL_DATA()
{
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KS_MODEL_DATA::~KS_MODEL_DATA()
{
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KS_MODEL_MESH::KS_MODEL_MESH()
	: MeshPartCount( 0 )
{
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KS_MODEL_MESH::KS_MODEL_MESH( KsUInt32 meshPartCount )
{
	MeshPartCount = meshPartCount;
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KS_MODEL_MESH::~KS_MODEL_MESH()
{
	ksDELETEARRAYTEMPLATE( MeshParts );
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KsInt16 KsFindBoneIndexFromName( KS_MODEL_DATA* pModelData, KsInt8* pBoneName )
{
	for( KsUInt32 i=0; i<pModelData->Bones.size(); i++ )
	{
		if( ks_strcmp( pBoneName, &pModelData->Bones[ i ]->Name[ 0 ] ) == 0 )
		{
			return pModelData->Bones[ i ]->Index;
		}
	}

	return -1;
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KsInt16 KsFindBoneIndex( KS_MODEL_DATA* pModelData, KsBone* pBone )
{
	for( KsUInt32 i=0; i<pModelData->Bones.size(); i++ )
	{
		if( ks_strcmp( pBone->getName().c_str(), &pModelData->Bones[ i ]->Name[ 0 ] ) == 0 )
		{
			return pModelData->Bones[ i ]->Index;
		}
	}

	return -1;
}

/************************************************************************************************/
/*
 * PMDファイル読み込み処理
 * @param	filePath	ファイルパス
 * @return	PMDファイルデータ
 */
/************************************************************************************************/
KsBool KsModelConvertFromPMD( const KsString& inputFilePath, const KsString& outputFilePath, KsModelConvertOption& opt )
{
	KsRenderContext*		pRenderContext = KsRenderSystem::getInstancePtr()->getRenderContex();

	// ファイルを読み込む
	KS_PMD_DATA*			pPMD = KsLoadPMDFile( inputFilePath );

	if( NULL == pPMD )
	{
		return ksFALSE;
	}

	KsModel*				pModel   = KsModelCreateFromPMD( pPMD, ksTRUE );
	KsHumanIK*				pHumanIK = KsHumanIKCreateFromPMD( pPMD, pModel );
	KsPhysicsController*	pPhysics = KsPhysicsControllerCreateFromPMD( pPMD, pModel );

	//--------------------------------------------------------
	// モデルヘッダー
	//--------------------------------------------------------
	KS_MODEL_DATA*		pModelData = ksNew KS_MODEL_DATA( pModel->getModelName() );

	//--------------------------------------------------------
	// テクスチャチャンク
	//--------------------------------------------------------
	KS_DATA_CHUNK*		pTextureChunk = ksNew KS_DATA_CHUNK( ksDATA_CHUNK_TEXTURE, pModel->getTextureCount(), sizeof(KS_MODEL_TEXTURE)*pModel->getTextureCount() );
	
	for( KsUInt32 i=0; i<pModel->getTextureCount(); i++ )
	{
		KsString			fileName = KsPath::getFileName( pModel->getTexture( i )->getName() );
		KS_MODEL_TEXTURE	texName;
		
		KsZeroMemory( &texName, sizeof(KS_MODEL_TEXTURE) );
		ks_strcpy( texName.Name, fileName.c_str() );

		pTextureChunk->pFile->write( &texName, sizeof(KS_MODEL_TEXTURE) );
	}

	pModelData->Chunks.push_back( pTextureChunk );

	//--------------------------------------------------------
	// ボーンチャンク
	//--------------------------------------------------------
	const KsUInt32		boneCount = opt.bStaticMesh ? 1 : pModel->getBoneCount();
	KS_DATA_CHUNK*		pBoneChunk = ksNew KS_DATA_CHUNK( ksDATA_CHUNK_BONE, boneCount, sizeof(KS_MODEL_BONE)*boneCount );
		
	for( KsUInt32 i=0; i<boneCount; i++ )
	{
		KsBone*			pBone_Src = c_cast<KsBone*>( pModel->getBone( i ) );
		KS_MODEL_BONE*	pBone_Dst = ksNew KS_MODEL_BONE();

		KsZeroMemory( pBone_Dst, sizeof(KS_MODEL_BONE) );

		KsMemCopy( pBone_Dst->Name, pBone_Src->getName().c_str(), pBone_Src->getName().length() );
		pBone_Dst->Index      = pBone_Src->getIndex();
		pBone_Dst->Parent     = pBone_Src->getParentIndex();
		pBone_Dst->ChildCount = pBone_Src->getNumChild();
		pBone_Dst->Position   = pBone_Src->getDefaultTransform().getTranslate();
		pBone_Dst->Rotation   = pBone_Src->getDefaultTransform().getRotate();

		pModelData->Bones.push_back( pBone_Dst );

		pBoneChunk->pFile->write( pBone_Dst, sizeof(KS_MODEL_BONE) );
	}
	pModelData->Chunks.push_back( pBoneChunk );

	//--------------------------------------------------------
	// メッシュ情報
	//--------------------------------------------------------
	const KsUInt32		meshCount    = pModel->getMeshCount();
	KsUInt32			EffectID     = 0;

	for( KsUInt32 i=0; i<meshCount; i++ )
	{
		KsMesh*			pMesh_Src  = c_cast<KsMesh*>( pModel->getMesh( i ) );
		KS_MODEL_MESH*	pMesh_Dst  = ksNew KS_MODEL_MESH( pMesh_Src->getMeshPartCount() );
		KsUInt32		MeshSize   = KS_MODEL_MESH_SIZE;

		//--------------------------------------------------------
		// メッシュパーツ
		//--------------------------------------------------------
		for( KsUInt32 j=0; j<pMesh_Src->getMeshPartCount(); j++ )
		{
			KsMeshPart*				pParts_Src  = c_cast<KsMeshPart*>( pMesh_Src->getMeshPart( j ) );
			KS_MODEL_MESH_PARTS*	pParts_Dst  = ksNew KS_MODEL_MESH_PARTS();
			KsEffectMMD*			pEffect_Src = r_cast<KsEffectMMD*>( pParts_Src->getEffect() );
			KS_MODEL_MMD_MATERIAL*	pEffect_Dst = ksNew KS_MODEL_MMD_MATERIAL();
			KsInt32					numPallet   = opt.bStaticMesh ? 1 : pParts_Src->getNumMatrixPallet();
			KsString				texName     = "none";
			
			if( pEffect_Src->getDiffuseTexture() )
			{
				texName = KsPath::getFileName( pEffect_Src->getDiffuseTexture()->getName() );
			}

			//--------------------------------------------------------
			// マテリアル情報
			//--------------------------------------------------------
			pEffect_Dst->Ambient     = pEffect_Src->getAmbient();
			pEffect_Dst->Diffuse     = pEffect_Src->getDiffuse();
			pEffect_Dst->Specular    = pEffect_Src->getSpecular();
			pEffect_Dst->Specularity = pEffect_Src->getSpecularity();
			ks_strcpy( (KsChar*)&pEffect_Dst->TextureName[ 0 ], texName.c_str() );

			pModelData->Effects.push_back( pEffect_Dst );

			pParts_Dst->EffectID = EffectID;

			++EffectID;

			//--------------------------------------------------------
			// プリミティブ
			//--------------------------------------------------------
			KsIndexBuffer*			pIndexBuffer   = pParts_Src->getIndexBuffer();
			KsUInt32				indexSize      = ( pIndexBuffer->getIndexFormatType() + 1 ) * 2;
			KsUInt32				indexDataSize  = pIndexBuffer->getNumIndex() * indexSize;
			KsByte*					pIndexData     = ksNew KsByte[ indexDataSize ];
			KsVertexBuffer*			pVertexBuffer  = pParts_Src->getVertexBuffer();
			KsUInt32				vertexSize     = pVertexBuffer->getVertexSize();
			KsUInt32				vertexDataSize = pVertexBuffer->getVertexSize() * pVertexBuffer->getNumVertex();
			KsByte*					pVertexData    = ksNew KsByte[ vertexDataSize ];
			KsInt32*				pMatrixPallet  = ksNew KsInt32 [ numPallet ];

			pIndexBuffer->read(  pRenderContext, pIndexData,  indexDataSize  );
			pVertexBuffer->read( pRenderContext, pVertexData, vertexDataSize );

			//--------------------------------------------------------
			// プリミティブデータ
			//--------------------------------------------------------
			pParts_Dst->StartIndex     = pParts_Src->getStartIndex();
			pParts_Dst->StartVertex    = pParts_Src->getVertexOffset();
			pParts_Dst->PrimitiveCount = pParts_Src->getPrimitiveCount();

			//--------------------------------------------------------
			// インデックスデータ
			//--------------------------------------------------------
			pParts_Dst->IndexType      = pIndexBuffer->getIndexFormatType();
			pParts_Dst->IndexCount     = pIndexBuffer->getNumIndex();
			pParts_Dst->IndexSize      = indexSize;
			pParts_Dst->IndexData      = pIndexData;

			//--------------------------------------------------------
			// 頂点データ
			//--------------------------------------------------------
			pParts_Dst->VertexType     = pVertexBuffer->getVertexFormat();
			pParts_Dst->VertexCount    = pVertexBuffer->getNumVertex();
			pParts_Dst->VertexSize     = vertexSize;
			pParts_Dst->VertexData     = pVertexData;

			//--------------------------------------------------------
			// マトリックスパレット(メッシュパーツ内でのボーンインデックス)
			//--------------------------------------------------------
			if( numPallet <= 0 ) { numPallet = 1; }
			pParts_Dst->MatrixPalletCount = (KsUInt32)numPallet;
			pParts_Dst->MatrixPalletData  = ksNew KsInt32[ numPallet ];
			
			if( opt.bStaticMesh || pParts_Src->getNumMatrixPallet() <= 0 )
			{
				pParts_Dst->MatrixPalletData[ 0 ] = 0;
			}
			else
			{
				for( KsInt32 k=0; k<numPallet; k++ )
				{
					pParts_Dst->MatrixPalletData[ 0 ] = pParts_Src->getMatrixPallet( k );
				}
			}

			//--------------------------------------------------------
			// ボーン情報
			//--------------------------------------------------------
			KsInt32		boneCount = pParts_Src->getNumBone();
			if( opt.bStaticMesh || boneCount <= 0 )
			{
				pParts_Dst->BoneCount = 1;
				pParts_Dst->BoneData  = ksNew KsInt32[ 1 ];
				pParts_Dst->BoneData[ 0 ] = 0;
			}
			else
			{
				pParts_Dst->BoneCount = boneCount;
				pParts_Dst->BoneData  = ksNew KsInt32[ boneCount ];

				for( KsInt32 k=0; k<boneCount; k++ )
				{
					KsBone*	pBone = pParts_Src->getBone( k );

					pParts_Dst->BoneData[ k ] = pBone->getIndex();
				}
			}

			//--------------------------------------------------------
			// メッシュパーツサイズ計算
			//--------------------------------------------------------
			pParts_Dst->MeshPartsSize  = KS_MODEL_MESH_PARTS_SIZE;
			pParts_Dst->MeshPartsSize += ksALIGN4(indexDataSize);
			pParts_Dst->MeshPartsSize += ksALIGN4(vertexDataSize);
			pParts_Dst->MeshPartsSize += sizeof(KsInt32) * numPallet;
			pParts_Dst->MeshPartsSize += sizeof(KsInt32) * pParts_Dst->BoneCount;

			//--------------------------------------------------------
			// メッシュパーツ追加
			//--------------------------------------------------------
			pMesh_Dst->MeshParts.push_back( pParts_Dst );

			//--------------------------------------------------------
			// メッシュサイズ計算
			//--------------------------------------------------------
			MeshSize += pParts_Dst->MeshPartsSize;

			//--------------------------------------------------------
			// NvStripに変換する？
			//--------------------------------------------------------
			if( opt.bTriStrip )
			{

			}
		}

		//--------------------------------------------------------
		// メッシュ追加
		//--------------------------------------------------------
		pModelData->Meshes.push_back( pMesh_Dst );

		//--------------------------------------------------------
		// メッシュをチャンクデータに書き込む
		//--------------------------------------------------------
		KS_DATA_CHUNK*	pMeshChunk = ksNew KS_DATA_CHUNK( ksDATA_CHUNK_MESH, 1, MeshSize );
		
		pMeshChunk->pFile->writeUInt32( pMesh_Dst->MeshPartCount );

		for( KsUInt32 j=0; j<pMesh_Dst->MeshPartCount; j++ )
		{
			KS_MODEL_MESH_PARTS*	pMeshParts = pMesh_Dst->MeshParts[ j ];

			// メッシュパーツサイズ
			pMeshChunk->pFile->writeUInt32( pMeshParts->MeshPartsSize );

			// 頂点インデックスのタイプ
			pMeshChunk->pFile->writeUInt32( pMeshParts->IndexType );

			// 頂点インデックスのタイプ
			pMeshChunk->pFile->writeUInt32( pMeshParts->IndexCount );

			// 頂点インデックスサイズ
			pMeshChunk->pFile->writeUInt32( pMeshParts->IndexSize );

			// 頂点インデックスデータ
			pMeshChunk->pFile->write( pMeshParts->IndexData, pMeshParts->IndexCount * pMeshParts->IndexSize );

			// 頂点データのタイプ
			pMeshChunk->pFile->writeUInt32( pMeshParts->VertexType );

			// 頂点データのタイプ
			pMeshChunk->pFile->writeUInt32( pMeshParts->VertexCount );

			// 頂点サイズ
			pMeshChunk->pFile->writeUInt32( pMeshParts->VertexSize );

			// 頂点データ
			pMeshChunk->pFile->write( pMeshParts->VertexData, pMeshParts->VertexCount * pMeshParts->VertexSize );

			// レンダリングするプリミティブの数
			pMeshChunk->pFile->writeInt32( pMeshParts->PrimitiveCount );

			// インデックス配列の中で頂点の読み取りを開始する位置
			pMeshChunk->pFile->writeUInt32( pMeshParts->StartIndex );

			// 頂点バッファーの最上部からのオフセット
			pMeshChunk->pFile->writeUInt32( pMeshParts->StartVertex );

			// エフェクトID
			pMeshChunk->pFile->writeUInt32( pMeshParts->EffectID );

			// 使用マトリックスパレット数
			pMeshChunk->pFile->writeUInt32( pMeshParts->MatrixPalletCount );

			// 使用マトリックスパレット
			pMeshChunk->pFile->write( pMeshParts->MatrixPalletData, sizeof(KsInt32)*pMeshParts->MatrixPalletCount );

			// ボーン数
			pMeshChunk->pFile->writeUInt32( pMeshParts->BoneCount );

			// ボーンデータ
			pMeshChunk->pFile->write( pMeshParts->BoneData, sizeof(KsInt32)*pMeshParts->BoneCount );
		}

		pModelData->Chunks.push_back( pMeshChunk );
	}

	//--------------------------------------------------------
	// Effectをチャンクデータに書き込む
	//--------------------------------------------------------
	KS_DATA_CHUNK*	pEffectChunk = ksNew KS_DATA_CHUNK( ksDATA_CHUNK_EFFECT, pModelData->Effects.size(), sizeof(KS_MODEL_EFFECT)*pModelData->Effects.size() );

	for( KsUInt32 i=0; i<pModelData->Effects.size(); i++ )
	{
		pEffectChunk->pFile->write( pModelData->Effects[ i ], sizeof(KS_MODEL_EFFECT) );
	}

	pModelData->Chunks.push_back( pEffectChunk );


	//--------------------------------------------------------
	// HumanIK をチャンクデータに書き込む
	//--------------------------------------------------------
	if( pHumanIK && !opt.bStaticMesh )
	{
		const KsUInt32	IKEffectorCount  = (KsUInt32)pHumanIK->m_vpEffectors.size();

		KS_DATA_CHUNK*	pIKChunk = ksNew KS_DATA_CHUNK( ksDATA_CHUNK_IK, IKEffectorCount );

		pIKChunk->pFile->writeUInt32( IKEffectorCount );

		for( KsUInt16 i=0; i<IKEffectorCount; i++ )
		{
			KsIKEffector*	pEffector = pHumanIK->m_vpEffectors[ i ];
			KsIKPoint*		pIKPoint  = pEffector->getTargetPoint();

			KsInt16		boneNo    = KsFindBoneIndex( pModelData, pIKPoint->getBone() );
			KsUInt8		isLimit   = pIKPoint->IsIKLimitAngle();
			KsUInt8		limitType = pIKPoint->getIKLimitAngleType();

			pIKChunk->pFile->writeInt16( boneNo );
			pIKChunk->pFile->writeUInt8( isLimit );
			pIKChunk->pFile->writeUInt8( limitType );

			pIKPoint  = pEffector->getEffectorPoint();
			boneNo    = KsFindBoneIndex( pModelData, pIKPoint->getBone() );
			isLimit   = pIKPoint->IsIKLimitAngle();
			limitType = pIKPoint->getIKLimitAngleType();

			pIKChunk->pFile->writeInt16( boneNo );
			pIKChunk->pFile->writeUInt8( isLimit );
			pIKChunk->pFile->writeUInt8( limitType );

			pIKChunk->pFile->writeReal(   pEffector->getControlWeight() );
			pIKChunk->pFile->writeInt16(  (KsInt16)pEffector->getIterations() );
			pIKChunk->pFile->writeUInt16( (KsUInt16)pEffector->getChainPointCount() );

			for( KsUInt16 j=0; j<IKEffectorCount; j++ )
			{
				pIKPoint  = pEffector->getChainPoint( j );
				boneNo    = KsFindBoneIndex( pModelData, pIKPoint->getBone() );
				isLimit   = pIKPoint->IsIKLimitAngle();
				limitType = pIKPoint->getIKLimitAngleType();

				pIKChunk->pFile->writeInt16( boneNo );
				pIKChunk->pFile->writeUInt8( isLimit );
				pIKChunk->pFile->writeUInt8( limitType );
			}
		}

		pIKChunk->updateSize();

		pModelData->Chunks.push_back( pIKChunk );
	}

	//--------------------------------------------------------
	// Physics をチャンクデータに書き込む
	//--------------------------------------------------------
	if( pPhysics && !opt.bStaticMesh )
	{
		const KsUInt32	physicsParameterCount  = (KsUInt32)pPMD->RigidBodyList.RigidBodyCount;

		KS_DATA_CHUNK*	pPhysicsChunk = ksNew KS_DATA_CHUNK( ksDATA_CHUNK_PHYSICS, physicsParameterCount );

		pPhysicsChunk->pFile->writeUInt32( physicsParameterCount );

		for( KsUInt16 i=0; i<physicsParameterCount; i++ )
		{
			KS_MODEL_RIGID_BODY	rigidBody;

			KsMemCopy( &rigidBody, &pPMD->RigidBodyList.RigidBodyList[ i ], sizeof(KS_MODEL_RIGID_BODY) );
			
			rigidBody.BoneIndex = KsFindBoneIndexFromName( pModelData, &pPMD->BoneList.Bones[ rigidBody.BoneIndex ].Name[0] );

			pPhysicsChunk->write( &rigidBody, sizeof(KS_MODEL_RIGID_BODY) );
		}

		pPhysicsChunk->updateSize();

		pModelData->Chunks.push_back( pPhysicsChunk );
	}

	//--------------------------------------------------------
	// コンストレイントをチャンクデータに書き込む
	//--------------------------------------------------------
	if( !opt.bStaticMesh )
	{
		const KsUInt32	constraintCount  = (KsUInt32)pPMD->ConstraintList.ConstraintCount;

		KS_DATA_CHUNK*	pConstraintChunk = ksNew KS_DATA_CHUNK( ksDATA_CHUNK_CONSTRAINT, constraintCount );

		pConstraintChunk->pFile->writeUInt32( constraintCount );

		for( KsUInt16 i=0; i<constraintCount; i++ )
		{
			KS_MODEL_CONSTRAINT constraint;

			KsMemCopy( &constraint, &pPMD->ConstraintList.ConstraintList[ i ], sizeof(KS_MODEL_CONSTRAINT) );
			
			//pPMD->BoneList.Bones[ constraint.RigidA ].Name[0]
			//constraint.RigidA = KsFindBoneIndexFromName( pModelData, &pPMD->BoneList.Bones[ rigidBody.BoneIndex ].Name[0] );
			//constraint.RigidB = KsFindBoneIndexFromName( pModelData, &pPMD->BoneList.Bones[ rigidBody.BoneIndex ].Name[0] );

			pConstraintChunk->write( &constraint, sizeof(KS_MODEL_CONSTRAINT) );
		}

		pConstraintChunk->updateSize();

		pModelData->Chunks.push_back( pConstraintChunk );
	}

	//--------------------------------------------------------
	// 表情のモーフィングデータをチャンクデータに書き込む
	//--------------------------------------------------------
	if( !opt.bStaticMesh )
	{
	}

	//--------------------------------------------------------
	// Chunk数を書き込む
	//--------------------------------------------------------
	pModelData->Header.ChunkCount = (KsUInt16)pModelData->Chunks.size();

	//--------------------------------------------------------
	// DUMPしておく
	//--------------------------------------------------------
	if( opt.bDump )
	{
		static const KsChar* s_ChunkTypeString[] = { "NONE", "MESH", "BONE", "TEXTURE", "EFFECT", "IK", "PHYSICS" };

		KsPrintf( "------<< Model Header >>------\n" );
		KsPrintf( "Signature          %s\n", pModelData->Header.Signature );
		KsPrintf( "Version            %d\n", pModelData->Header.Version );
		KsPrintf( "ModelName          %s\n", pModelData->Header.ModelName );
		KsPrintf( "ChunkCount         %d\n", pModelData->Header.ChunkCount );

		KsPrintf( "------<< Model Chunks >>------\n" );
		KsPrintf( "Chunk Count        %d\n", pModelData->Chunks.size() );

		for( KsUInt32 i=0; i<pModelData->Chunks.size(); i++ )
		{
			KS_DATA_CHUNK*	pChunk = pModelData->Chunks[ i ];

			KsPrintf( "------<<Chunk [%d]>>------\n", i );
			KsPrintf( "Chunk Type        %d\n", pChunk->Type  );
			KsPrintf( "Chunk Count       %d\n", pChunk->Count );
			KsPrintf( "Chunk Size        %d\n", pChunk->Size  );
			KsPrintf( "      [ %s ]        \n", s_ChunkTypeString[ pChunk->Type ] );

			for( KsUInt32 j=0; j<pChunk->Count; j++ )
			{
				switch( pChunk->Type )
				{
					case ksDATA_CHUNK_MESH:
					{
#if 0
						KsByte*		pMeshAddress = (KsByte*)pChunk->pFile->getFilePtr();

						for( KsUInt32 j=0; j<pChunk->Count; j++ )
						{
							KS_KMD_MESH*	pMesh = (KS_KMD_MESH*)pMeshAddress;
							pMeshAddress += sizeof(KsUInt32);

							KsPrintf( "MeshPartCount : [ %d ]\n", pMesh->MeshPartCount );

							for( KsUInt32 k=0; k<pMesh->MeshPartCount; k++ )
							{
								KS_KMD_MESH_PARTS*	pMeshParts = (KS_KMD_MESH_PARTS*)pMeshAddress;

								KsPrintf( "IndexType  : [ %d ]\n", pMeshParts->IndexType );
								KsPrintf( "IndexCount : [ %d ]\n", pMeshParts->IndexCount );
								KsPrintf( "IndexSize  : [ %d ]\n", pMeshParts->IndexSize );
								//pFile->write( pMeshParts->IndexData, pMeshParts->IndexCount * pMeshParts->IndexSize );

								KsPrintf( "VertexType  : [ %d ]\n", pMeshParts->VertexType );
								KsPrintf( "VertexCount : [ %d ]\n", pMeshParts->VertexCount );
								KsPrintf( "VertexSize  : [ %d ]\n", pMeshParts->VertexSize );
								//pFile->write( pMeshParts->VertexData, pMeshParts->VertexCount * pMeshParts->VertexSize );

								KsPrintf( "PrimitiveCount    : [ %d ]\n", pMeshParts->PrimitiveCount );
								KsPrintf( "StartIndex        : [ %d ]\n", pMeshParts->StartIndex );
								KsPrintf( "StartVertex       : [ %d ]\n", pMeshParts->StartVertex );
								KsPrintf( "EffectID          : [ %d ]\n", pMeshParts->EffectID );

								KsPrintf( "MatrixPalletCount : [ %d ]\n", pMeshParts->MatrixPalletCount );
								//pFile->write( pMeshParts->MatrixPalletData, sizeof(KsInt32)*pMeshParts->MatrixPalletCount );

								KsPrintf( "EffectID          : [ %d ]\n", pMeshParts->EffectID );

								KsPrintf( "BoneCount         : [ %d ]\n", pMeshParts->BoneCount );

								//KsPrintf( "BoneData         : [ %d ]\n", pMeshParts->BoneCount );
							}
						}
#endif
						break;
					}
					case ksDATA_CHUNK_BONE:
					{
						KS_KMD_BONE*	pBones = (KS_KMD_BONE*)pChunk->pFile->getFilePtr();
						KsPrintf( "Bone\n" );
						KsPrintf( "Name       : [ %s ]\n", pBones[ j ].Name );
						KsPrintf( "Parent     : [ %d ]\n", pBones[ j ].Parent );
						KsPrintf( "Index      : [ %d ]\n", pBones[ j ].Index );
						KsPrintf( "ChildCount : [ %d ]\n", pBones[ j ].ChildCount );
						KsPrintf( "Position   : [ %f, %f, %f ]\n",     pBones[ j ].Position.x, pBones[ j ].Position.y, pBones[ j ].Position.z );
						KsPrintf( "Rotation   : [ %f, %f, %f, %f ]\n", pBones[ j ].Rotation.x, pBones[ j ].Rotation.y, pBones[ j ].Rotation.z, pBones[ j ].Rotation.w );
						break;
					}
					case ksDATA_CHUNK_TEXTURE:
					{
						KS_KMD_TEXTURE*	pTextures = (KS_KMD_TEXTURE*)pChunk->pFile->getFilePtr();
						KsPrintf( "Texture : %s\n", pTextures[ j ].Name );
						break;
					}
					case ksDATA_CHUNK_EFFECT:
					{
						KS_KMD_MMD_MATERIAL*	pMaterials = (KS_KMD_MMD_MATERIAL*)pChunk->pFile->getFilePtr();
						KsPrintf( "Material\n" );
						KsPrintf( "Texture     : [ %s ]\n", pMaterials[ j ].TextureName );
						KsPrintf( "Diffuse     : [ %f, %f, %f, %f ]\n", pMaterials[ j ].Diffuse.x,  pMaterials[ j ].Diffuse.y,  pMaterials[ j ].Diffuse.z,  pMaterials[ j ].Diffuse.w );
						KsPrintf( "Ambient     : [ %f, %f, %f, %f ]\n", pMaterials[ j ].Ambient.x,  pMaterials[ j ].Ambient.y,  pMaterials[ j ].Ambient.z,  pMaterials[ j ].Ambient.w );
						KsPrintf( "Specular    : [ %f, %f, %f, %f ]\n", pMaterials[ j ].Specular.x, pMaterials[ j ].Specular.y, pMaterials[ j ].Specular.z, pMaterials[ j ].Specular.w );
						KsPrintf( "Specularity : [ %f ]\n", pMaterials[ j ].Specularity );
						break;
					}
					case ksDATA_CHUNK_IK:
					{
						break;
					}
					case ksDATA_CHUNK_PHYSICS:
					{
						break;
					}
					default:break;
				}
			}
		}
	}

	//--------------------------------------------------------
	// KMD ファイル書き込み
	//--------------------------------------------------------
	KsFileObject*	pFile = new KsFile( outputFilePath, ksWRITE | ksBINARY );

	// KMDヘッダー
	pFile->write( &pModelData->Header, sizeof(KS_MODEL_HEADER) );

	for( KsUInt32 i=0; i<pModelData->Chunks.size(); i++ )
	{
		KS_DATA_CHUNK*	pChunk = pModelData->Chunks[ i ];

		// チャンクヘッダー
		pFile->writeUInt16( pChunk->Type  );
		pFile->writeUInt16( pChunk->Count );
		pFile->writeUInt32( pChunk->Size  );

		// チャンクデータ
		switch( pChunk->Type )
		{
			case ksDATA_CHUNK_MESH:
			case ksDATA_CHUNK_BONE:
			case ksDATA_CHUNK_TEXTURE:
			case ksDATA_CHUNK_EFFECT:
			{
				pFile->write( pChunk->pFile->getFilePtr(), pChunk->Size );
			}
			case ksDATA_CHUNK_IK:
			{
				break;
			}
			case ksDATA_CHUNK_PHYSICS:
			{
				break;
			}
			case ksDATA_CHUNK_CONSTRAINT:
			{
				break;
			}
			default:break;
		}
	}

	ksDELETE( pFile );

	return ksTRUE;
}


