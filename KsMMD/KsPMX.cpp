/************************************************************************************************/
/** 
 * @file		KsPMX.cpp
 * @brief		PMXファイル
 * @author		Tsukasa Kato
 * @date		2010/12/17
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                             */
/*==============================================================================================*/
#include "KsMMD/KsMMDPreCompile.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*************************************************************************************************/
/*
 * 文字列を取得する
 */
/*************************************************************************************************/
KsString KsPMXReadString( KsFileObject* pFile )
{
	const KsInt32 strSize = pFile->readInt32();

	if( 0 == strSize )
	{
		return KsString();
	}

	KsWChar buffer[ 1024 ];

	KsZeroMemory( buffer, sizeof(buffer) );

	pFile->read( buffer, strSize );

	return KsString( buffer );
}

/*************************************************************************************************/
/*
 * 指定タイプのインデックスを取得する
 */
/*************************************************************************************************/
KsInt32  KsPMXReadIndex( KsFileObject* pFile, KsInt32 IndexSize )
{
	KsInt32 index = 0;

	switch( IndexSize )
	{
		case 1:
			index = (KsInt32)pFile->readUInt8();
			break;
		case 2:
			index = (KsInt32)pFile->readUInt16();
			break;
		case 4:
			index = (KsInt32)pFile->readInt32();
			break;
		default:
			break;
	}

	return index;
}

/*************************************************************************************************/
/*
 * テクスチャ名を取得する
 */
/*************************************************************************************************/
KsString* KsPMXGetTexture( KS_PMX_DATA* pPMX, KsInt32 index )
{
	if( index < 0 || pPMX->NumTexture <= index )
	{
		return NULL;
	}

	return &pPMX->pTextures[ index ];
}

/*************************************************************************************************/
/*
 * PMXファイル読み込み処理
 * @param	filePath	ファイルパス
 * @return	PMXファイルデータ
 */
/*************************************************************************************************/
KS_PMX_DATA* KsLoadPMXFile( KsFileObject* pFile )
{
	KS_PMX_DATA*	pPMX  = ksNew KS_PMX_DATA();

	//-----------------------------------------------------------------------------
	// ヘッダー情報
	//-----------------------------------------------------------------------------
	pFile->read( pPMX->Header.Magic, sizeof(pPMX->Header.Magic) );

	pPMX->Header.Version  = pFile->readReal();
	pPMX->Header.infoSize = pFile->readUInt8();
	pPMX->Header.pInfo    = ksNew KsUInt8[ pPMX->Header.infoSize ];

	pFile->read( pPMX->Header.pInfo, pPMX->Header.infoSize );

	const KsInt32 IndexSize      = pPMX->Header.pInfo[ ksPMX_MODEL_INFO_VERTEX_INDEX_SIZE ];
	const KsInt32 numExtUV       = pPMX->Header.pInfo[ ksPMX_MODEL_INFO_TEXTURE_EXT_UV ];
	const KsInt32 textureSize    = pPMX->Header.pInfo[ ksPMX_MODEL_INFO_TEXTURE_INDEX_SIZE ];
	const KsInt32 boneIndexSize  = pPMX->Header.pInfo[ ksPMX_MODEL_INFO_BONE_INDEX_SIZE ];
	const KsInt32 morphIndexSize = pPMX->Header.pInfo[ ksPMX_MODEL_INFO_MORPH_INDEX_SIZE ];
	const KsInt32 rigidIndexSize = pPMX->Header.pInfo[ ksPMX_MODEL_INFO_RIGIDBODY_INDEX_SIZE ];

	//-----------------------------------------------------------------------------
	// モデル情報
	//-----------------------------------------------------------------------------
	pPMX->ModelInfo.ModelName_J = KsPMXReadString( pFile );
	pPMX->ModelInfo.ModelName_E = KsPMXReadString( pFile );
	pPMX->ModelInfo.Comment_J   = KsPMXReadString( pFile );
	pPMX->ModelInfo.Comment_E   = KsPMXReadString( pFile );

	//-----------------------------------------------------------------------------
	// 頂点
	//-----------------------------------------------------------------------------

	// 頂点数
	pPMX->NumVertex = pFile->readInt32();

	pPMX->pVertices = ksNew KS_PMX_VERTEX[ pPMX->NumVertex ];

	for( KsInt32 i=0; i < pPMX->NumVertex; i++ )
	{
		// 位置座標
		pPMX->pVertices[ i ].Position.x = pFile->readReal();
		pPMX->pVertices[ i ].Position.y = pFile->readReal();
		pPMX->pVertices[ i ].Position.z = pFile->readReal();

		// 法線
		pPMX->pVertices[ i ].Normal.x = pFile->readReal();
		pPMX->pVertices[ i ].Normal.y = pFile->readReal();
		pPMX->pVertices[ i ].Normal.z = pFile->readReal();

		// UV座標
		pPMX->pVertices[ i ].TextureCoord.x = pFile->readReal();
		pPMX->pVertices[ i ].TextureCoord.y = pFile->readReal();

		// 拡張用UV座標
		for( KsInt32 j=0; j < numExtUV; j++ )
		{
			KsVector4d	vTexcoord;

			vTexcoord.x = pFile->readReal();
			vTexcoord.y = pFile->readReal();
			vTexcoord.z = pFile->readReal();
			vTexcoord.w = pFile->readReal();

			pPMX->pVertices[ i ].ExtTextureCoords.push_back( vTexcoord );

		}

		//-----------------------------------------------------------------------------
		// 頂点ウェイト
		//-----------------------------------------------------------------------------
		const KsUInt8 weightType = pFile->readUInt8();

		switch( weightType )
		{
			case ksPMX_BDEF1:
			{
				pPMX->pVertices[ i ].Weight.Indices[ 0 ] = KsPMXReadIndex( pFile, IndexSize );
				pPMX->pVertices[ i ].Weight.Indices[ 1 ] = -1;
				pPMX->pVertices[ i ].Weight.Indices[ 2 ] = -1;
				pPMX->pVertices[ i ].Weight.Indices[ 3 ] = -1;
				pPMX->pVertices[ i ].Weight.Weight [ 0 ] = 1.0f;
				pPMX->pVertices[ i ].Weight.Weight [ 1 ] = 0.0f;
				pPMX->pVertices[ i ].Weight.Weight [ 2 ] = 0.0f;
				pPMX->pVertices[ i ].Weight.Weight [ 3 ] = 0.0f;
				break;
			}
			case ksPMX_BDEF2:
			{
				pPMX->pVertices[ i ].Weight.Indices[ 0 ] = KsPMXReadIndex( pFile, IndexSize );
				pPMX->pVertices[ i ].Weight.Indices[ 1 ] = KsPMXReadIndex( pFile, IndexSize );
				pPMX->pVertices[ i ].Weight.Indices[ 2 ] = -1;
				pPMX->pVertices[ i ].Weight.Indices[ 3 ] = -1;
				pPMX->pVertices[ i ].Weight.Weight [ 0 ] = pFile->readReal();
				pPMX->pVertices[ i ].Weight.Weight [ 1 ] = 1.0f - pPMX->pVertices[ i ].Weight.Weight[ 0 ];
				pPMX->pVertices[ i ].Weight.Weight [ 2 ] = 0.0f;
				pPMX->pVertices[ i ].Weight.Weight [ 3 ] = 0.0f;
				break;
			}
			case ksPMX_BDEF4:
			{
				pPMX->pVertices[ i ].Weight.Indices[ 0 ] = KsPMXReadIndex( pFile, IndexSize );
				pPMX->pVertices[ i ].Weight.Indices[ 1 ] = KsPMXReadIndex( pFile, IndexSize );
				pPMX->pVertices[ i ].Weight.Indices[ 2 ] = KsPMXReadIndex( pFile, IndexSize );
				pPMX->pVertices[ i ].Weight.Indices[ 3 ] = KsPMXReadIndex( pFile, IndexSize );
				pPMX->pVertices[ i ].Weight.Weight [ 0 ] = pFile->readReal();
				pPMX->pVertices[ i ].Weight.Weight [ 1 ] = pFile->readReal();
				pPMX->pVertices[ i ].Weight.Weight [ 2 ] = pFile->readReal();
				pPMX->pVertices[ i ].Weight.Weight [ 3 ] = pFile->readReal();
				break;
			}
			case ksPMX_SDEF:
			{
				pPMX->pVertices[ i ].Weight.Indices[ 0 ] = KsPMXReadIndex( pFile, IndexSize );
				pPMX->pVertices[ i ].Weight.Indices[ 1 ] = KsPMXReadIndex( pFile, IndexSize );
				pPMX->pVertices[ i ].Weight.Indices[ 2 ] = -1;
				pPMX->pVertices[ i ].Weight.Indices[ 3 ] = -1;

				pPMX->pVertices[ i ].Weight.Weight[ 0 ]  = pFile->readReal();
				pPMX->pVertices[ i ].Weight.Weight[ 1 ]  = pFile->readReal();
				pPMX->pVertices[ i ].Weight.Weight[ 2 ]  = pFile->readReal();
				pPMX->pVertices[ i ].Weight.Weight[ 3 ]  = pFile->readReal();
				pPMX->pVertices[ i ].Weight.Weight[ 2 ]  = pFile->readReal();
				pPMX->pVertices[ i ].Weight.Weight[ 3 ]  = pFile->readReal();
				pPMX->pVertices[ i ].Weight.Weight[ 2 ]  = pFile->readReal();
				pPMX->pVertices[ i ].Weight.Weight[ 3 ]  = pFile->readReal();
				pPMX->pVertices[ i ].Weight.Weight[ 3 ]  = pFile->readReal();
				pPMX->pVertices[ i ].Weight.Weight[ 3 ]  = pFile->readReal();
				break;
			}
			default:
				break;
		}

		// edge
		pPMX->pVertices[ i ].Edge = pFile->readReal();
	}

	//-----------------------------------------------------------------------------
	// 面
	//-----------------------------------------------------------------------------
	pPMX->NumFaces = pFile->readInt32();

	pPMX->Indices = ksNew KsInt32[ pPMX->NumFaces ];

	for( KsInt32 i=0; i < pPMX->NumFaces; i++ )
	{
		pPMX->Indices[ i ] = KsPMXReadIndex( pFile, IndexSize );
	}

	//-----------------------------------------------------------------------------
	// テクスチャ
	//-----------------------------------------------------------------------------
	pPMX->NumTexture = pFile->readInt32();
	pPMX->pTextures  = ksNew KsString[ pPMX->NumTexture ];

	for( KsInt32 i=0; i < pPMX->NumTexture; i++ )
	{
		pPMX->pTextures[ i ] = KsPMXReadString( pFile );
	}

	//-----------------------------------------------------------------------------
	// マテリアル
	//-----------------------------------------------------------------------------
	pPMX->NumMaterial = pFile->readInt32();
	pPMX->pMaterials  = ksNew KS_PMX_MATERIAL[ pPMX->NumMaterial ];
	
	for( KsInt32 i=0; i < pPMX->NumMaterial; i++ )
	{
		pPMX->pMaterials[ i ].MaterialName_J     = KsPMXReadString( pFile );
		pPMX->pMaterials[ i ].MaterialName_E     = KsPMXReadString( pFile );
		pPMX->pMaterials[ i ].Diffuse.x          = pFile->readReal();
		pPMX->pMaterials[ i ].Diffuse.y          = pFile->readReal();
		pPMX->pMaterials[ i ].Diffuse.z          = pFile->readReal();
		pPMX->pMaterials[ i ].Diffuse.w          = pFile->readReal();
		pPMX->pMaterials[ i ].Specular.x         = pFile->readReal();
		pPMX->pMaterials[ i ].Specular.y         = pFile->readReal();
		pPMX->pMaterials[ i ].Specular.z         = pFile->readReal();
		pPMX->pMaterials[ i ].SpecularPower      = pFile->readReal();
		pPMX->pMaterials[ i ].Ambient.x          = pFile->readReal();
		pPMX->pMaterials[ i ].Ambient.y          = pFile->readReal();
		pPMX->pMaterials[ i ].Ambient.z          = pFile->readReal();
		pPMX->pMaterials[ i ].bitFlag            = pFile->readUInt8();
		pPMX->pMaterials[ i ].EdgeColor.x        = pFile->readReal();
		pPMX->pMaterials[ i ].EdgeColor.y        = pFile->readReal();
		pPMX->pMaterials[ i ].EdgeColor.z        = pFile->readReal();
		pPMX->pMaterials[ i ].EdgeColor.w        = pFile->readReal();
		pPMX->pMaterials[ i ].EdgeSize           = pFile->readReal();
		pPMX->pMaterials[ i ].NormalTextureIndex = KsPMXReadIndex( pFile, textureSize );
		pPMX->pMaterials[ i ].SphereTextureIndex = KsPMXReadIndex( pFile, textureSize );
		pPMX->pMaterials[ i ].SphereMode         = pFile->readUInt8();
		pPMX->pMaterials[ i ].ToonFlag           = pFile->readUInt8();

		if( 0 == pPMX->pMaterials[ i ].ToonFlag )
		{
			pPMX->pMaterials[ i ].ToonTextureIndex   = KsPMXReadIndex( pFile, textureSize );
		}
		else if( 1 == pPMX->pMaterials[ i ].ToonFlag )
		{
			pPMX->pMaterials[ i ].ToonTextureIndex   = s_cast<KsInt32>( pFile->readUInt8() );
		}
	
		pPMX->pMaterials[ i ].Comment            = KsPMXReadString( pFile );
		pPMX->pMaterials[ i ].NumIndices         = pFile->readUInt32();
	}

	//-----------------------------------------------------------------------------
	// ボーン
	//-----------------------------------------------------------------------------
	pPMX->NumBone = pFile->readInt32();
	pPMX->pBones  = ksNew KS_PMX_BONE[ pPMX->NumBone ];

	for( KsInt32 i=0; i < pPMX->NumBone; i++ )
	{
		pPMX->pBones[ i ].BoneName_J = KsPMXReadString( pFile );
		pPMX->pBones[ i ].BoneName_E = KsPMXReadString( pFile );
		pPMX->pBones[ i ].Position.x = pFile->readReal();
		pPMX->pBones[ i ].Position.y = pFile->readReal();
		pPMX->pBones[ i ].Position.z = pFile->readReal();
		pPMX->pBones[ i ].Parent     = KsPMXReadIndex( pFile, boneIndexSize );
		pPMX->pBones[ i ].Node       = pFile->readInt32();
		pPMX->pBones[ i ].bitFlag    = pFile->readUInt16();

		if( pPMX->pBones[ i ].bitFlag & ksPMX_BONE_BIT_CONNECT )
		{
			pPMX->pBones[ i ].Connect = KsPMXReadIndex( pFile, boneIndexSize );
		}
		else
		{
			pPMX->pBones[ i ].Offset.x = pFile->readReal();
			pPMX->pBones[ i ].Offset.y = pFile->readReal();
			pPMX->pBones[ i ].Offset.z = pFile->readReal();
		}

		if( pPMX->pBones[ i ].bitFlag & (ksPMX_BONE_BIT_ADD_ROT | ksPMX_BONE_BIT_ADD_MOVE) )
		{
			pPMX->pBones[ i ].AddParent = KsPMXReadIndex( pFile, boneIndexSize );
			pPMX->pBones[ i ].AddRate   = pFile->readReal();
		}

		if( pPMX->pBones[ i ].bitFlag & ksPMX_BONE_BIT_AXIS )
		{
			pPMX->pBones[ i ].Axis.x = pFile->readReal();
			pPMX->pBones[ i ].Axis.y = pFile->readReal();
			pPMX->pBones[ i ].Axis.z = pFile->readReal();
		}

		if( pPMX->pBones[ i ].bitFlag & ksPMX_BONE_BIT_LOCAL_AXIS )
		{
			pPMX->pBones[ i ].AxisX.x = pFile->readReal();
			pPMX->pBones[ i ].AxisX.y = pFile->readReal();
			pPMX->pBones[ i ].AxisX.z = pFile->readReal();

			pPMX->pBones[ i ].AxisZ.x = pFile->readReal();
			pPMX->pBones[ i ].AxisZ.y = pFile->readReal();
			pPMX->pBones[ i ].AxisZ.z = pFile->readReal();
		}

		if( pPMX->pBones[ i ].bitFlag & ksPMX_BONE_BIT_MORPH )
		{
			pPMX->pBones[ i ].Morph   = pFile->readInt32();
		}
		
		if( pPMX->pBones[ i ].bitFlag & ksPMX_BONE_BIT_IK )
		{
			pPMX->pBones[ i ].IKTargetBoneIndex = KsPMXReadIndex( pFile, boneIndexSize );
			pPMX->pBones[ i ].IKIterations      = pFile->readInt32();
			pPMX->pBones[ i ].IKLimit           = pFile->readReal();
			pPMX->pBones[ i ].IKLinkCount       = pFile->readInt32();

			if( pPMX->pBones[ i ].IKLinkCount )
			{
				pPMX->pBones[ i ].IKLinks = ksNew KS_PMX_IK_LINK[ pPMX->pBones[ i ].IKLinkCount ];
				
				for( KsInt32 j=0; j < pPMX->pBones[ i ].IKLinkCount; j++ )
				{
					pPMX->pBones[ i ].IKLinks[ j ].BoneIndex    = KsPMXReadIndex( pFile, boneIndexSize );
					pPMX->pBones[ i ].IKLinks[ j ].IsAngleLimit = pFile->readUInt8();

					if( pPMX->pBones[ i ].IKLinks[ j ].IsAngleLimit )
					{
						pPMX->pBones[ i ].IKLinks[ j ].AngleLimitMin.x = pFile->readReal();
						pPMX->pBones[ i ].IKLinks[ j ].AngleLimitMin.y = pFile->readReal();
						pPMX->pBones[ i ].IKLinks[ j ].AngleLimitMin.z = pFile->readReal();
						pPMX->pBones[ i ].IKLinks[ j ].AngleLimitMax.x = pFile->readReal();
						pPMX->pBones[ i ].IKLinks[ j ].AngleLimitMax.y = pFile->readReal();
						pPMX->pBones[ i ].IKLinks[ j ].AngleLimitMax.z = pFile->readReal();
					}
				}
			}
		}
	}

	//-----------------------------------------------------------------------------
	// モーフ
	//-----------------------------------------------------------------------------
	pPMX->NumMorph = pFile->readInt32();
	pPMX->pMorph   = ksNew KS_PMX_MORPH[ pPMX->NumMorph ];

	KS_PMX_MORPH_VERTEX		MorphVertex;
	KS_PMX_MORPH_UV			MorphUV;
	KS_PMX_MORPH_BONE		MorphBone;
	KS_PMX_MORPH_GROUP		MorphGroup;
	KS_PMX_MORPH_MATERIAL	MorphMaterial;

	for( KsInt32 i=0; i < pPMX->NumMorph; i++ )
	{
		pPMX->pMorph[ i ].MorphName_J   = KsPMXReadString( pFile );
		pPMX->pMorph[ i ].MorphName_E   = KsPMXReadString( pFile );
		pPMX->pMorph[ i ].Category      = pFile->readUInt8();
		pPMX->pMorph[ i ].Type          = pFile->readUInt8();
		pPMX->pMorph[ i ].NumOffsetData = pFile->readInt32();

		for( KsInt32 j=0; j<pPMX->pMorph[ i ].NumOffsetData; j++ )
		{
			switch( pPMX->pMorph[ i ].Type )
			{
				case ksPMX_MORPH_GROUP:
				{
					MorphGroup.MorphIndex = KsPMXReadIndex( pFile, morphIndexSize );
					MorphGroup.MorphRate  = pFile->readReal();
					break;
				}
				case ksPMX_MORPH_VERTEX:
				{
					MorphVertex.VertexIndex = KsPMXReadIndex( pFile, IndexSize );
					MorphVertex.Offset.x    = pFile->readReal();
					MorphVertex.Offset.y    = pFile->readReal();
					MorphVertex.Offset.z    = pFile->readReal();
					break;
				}
				case ksPMX_MORPH_BONE:
				{
					MorphBone.BoneIndex  = KsPMXReadIndex( pFile, boneIndexSize );
					MorphBone.Position.x = pFile->readReal();
					MorphBone.Position.y = pFile->readReal();
					MorphBone.Position.z = pFile->readReal();
					MorphBone.Rotation.x = pFile->readReal();
					MorphBone.Rotation.y = pFile->readReal();
					MorphBone.Rotation.z = pFile->readReal();
					MorphBone.Rotation.w = pFile->readReal();
					break;
				}
				case ksPMX_MORPH_UV:
				case ksPMX_MORPH_UV1:
				case ksPMX_MORPH_UV2: 
				case ksPMX_MORPH_UV3: 
				case ksPMX_MORPH_UV4:
				{
					MorphUV.VertexIndex = KsPMXReadIndex( pFile, IndexSize );
					MorphUV.Offset.x    = pFile->readReal();
					MorphUV.Offset.y    = pFile->readReal();
					MorphUV.Offset.z    = pFile->readReal();
					MorphUV.Offset.w    = pFile->readReal();
					break;
				}
				case ksPMX_MORPH_MATERIAL:
				{
					MorphMaterial.MaterialIndex              = KsPMXReadIndex( pFile, morphIndexSize );
					MorphMaterial.Operate                    = pFile->readUInt8();
					MorphMaterial.Diffuse.x                  = pFile->readReal();
					MorphMaterial.Diffuse.y                  = pFile->readReal();
					MorphMaterial.Diffuse.z                  = pFile->readReal();
					MorphMaterial.Diffuse.w                  = pFile->readReal();
					MorphMaterial.Specular.x                 = pFile->readReal();
					MorphMaterial.Specular.y                 = pFile->readReal();
					MorphMaterial.Specular.z                 = pFile->readReal();
					MorphMaterial.SpecularPower              = pFile->readReal();
					MorphMaterial.Ambient.x                  = pFile->readReal();
					MorphMaterial.Ambient.y                  = pFile->readReal();
					MorphMaterial.Ambient.z                  = pFile->readReal();
					MorphMaterial.EdgeColor.x                = pFile->readReal();
					MorphMaterial.EdgeColor.y                = pFile->readReal();
					MorphMaterial.EdgeColor.z                = pFile->readReal();
					MorphMaterial.EdgeColor.w                = pFile->readReal();
					MorphMaterial.EdgeSize                   = pFile->readReal();
					MorphMaterial.NormalTextureCoefficient.x = pFile->readReal();
					MorphMaterial.NormalTextureCoefficient.y = pFile->readReal();
					MorphMaterial.NormalTextureCoefficient.z = pFile->readReal();
					MorphMaterial.NormalTextureCoefficient.w = pFile->readReal();
					MorphMaterial.SphereTextureCoefficient.x = pFile->readReal();
					MorphMaterial.SphereTextureCoefficient.y = pFile->readReal();
					MorphMaterial.SphereTextureCoefficient.z = pFile->readReal();
					MorphMaterial.SphereTextureCoefficient.w = pFile->readReal();
					MorphMaterial.ToonTextureCoefficient.x   = pFile->readReal();
					MorphMaterial.ToonTextureCoefficient.y   = pFile->readReal();
					MorphMaterial.ToonTextureCoefficient.z   = pFile->readReal();
					MorphMaterial.ToonTextureCoefficient.w   = pFile->readReal();
					break;
				}
				default:
					break;
			}
		}
	}

	//-----------------------------------------------------------------------------
	// 表示枠
	//-----------------------------------------------------------------------------
	pPMX->NumDisplay = pFile->readInt32();
	pPMX->pDisplays  = ksNew KS_PMX_DISPLAY[ pPMX->NumDisplay ];

	for( KsInt32 i=0; i < pPMX->NumDisplay; i++ )
	{
		pPMX->pDisplays[ i ].DisplayName_J   = KsPMXReadString( pFile );
		pPMX->pDisplays[ i ].DisplayName_E   = KsPMXReadString( pFile );
		pPMX->pDisplays[ i ].FrameType       = pFile->readUInt8();
		pPMX->pDisplays[ i ].NumDisplayFrame = pFile->readUInt32();

		for( KsInt32 j=0; j<pPMX->pDisplays[ i ].NumDisplayFrame; j++ )
		{
			pPMX->pDisplays[ i ].ElementType = pFile->readUInt8();

			if( 0 == pPMX->pDisplays[ i ].ElementType )
			{
				pPMX->pDisplays[ i ].DisplayIndex = KsPMXReadIndex( pFile, boneIndexSize );
			}
			else if( 1 == pPMX->pDisplays[ i ].ElementType )
			{
				pPMX->pDisplays[ i ].DisplayIndex = KsPMXReadIndex( pFile, morphIndexSize );
			}
		}
	}

	//-----------------------------------------------------------------------------
	// 剛体
	//-----------------------------------------------------------------------------
	pPMX->NumRigidBody = pFile->readInt32();
	pPMX->pRigidBodies = ksNew KS_PMX_RIGIDBODY[ pPMX->NumRigidBody ];

	for( KsInt32 i=0; i < pPMX->NumRigidBody; i++ )
	{
		pPMX->pRigidBodies[ i ].RigidBodyName_J   = KsPMXReadString( pFile );
		pPMX->pRigidBodies[ i ].RigidBodyName_E   = KsPMXReadString( pFile );
		pPMX->pRigidBodies[ i ].BoneIndex         = KsPMXReadIndex( pFile, boneIndexSize );
		pPMX->pRigidBodies[ i ].Group             = pFile->readUInt8();
		pPMX->pRigidBodies[ i ].GroupFlag         = pFile->readUInt16();
		pPMX->pRigidBodies[ i ].ShapeType         = pFile->readUInt8();
		pPMX->pRigidBodies[ i ].Size.x            = pFile->readReal();
		pPMX->pRigidBodies[ i ].Size.y            = pFile->readReal();
		pPMX->pRigidBodies[ i ].Size.z            = pFile->readReal();
		pPMX->pRigidBodies[ i ].Position.x        = pFile->readReal();
		pPMX->pRigidBodies[ i ].Position.y        = pFile->readReal();
		pPMX->pRigidBodies[ i ].Position.z        = pFile->readReal();
		pPMX->pRigidBodies[ i ].Rotation.x        = pFile->readReal();
		pPMX->pRigidBodies[ i ].Rotation.y        = pFile->readReal();
		pPMX->pRigidBodies[ i ].Rotation.z        = pFile->readReal();
		pPMX->pRigidBodies[ i ].Mass              = pFile->readReal();
		pPMX->pRigidBodies[ i ].MoveDamping       = pFile->readReal();
		pPMX->pRigidBodies[ i ].SpinDamping       = pFile->readReal();
		pPMX->pRigidBodies[ i ].Repulsion         = pFile->readReal();
		pPMX->pRigidBodies[ i ].Friction          = pFile->readReal();
		pPMX->pRigidBodies[ i ].CalcType          = pFile->readUInt8();
	}

	//-----------------------------------------------------------------------------
	// Joint
	//-----------------------------------------------------------------------------
	pPMX->NumJoint = pFile->readInt32();
	pPMX->pJoints  = ksNew KS_PMX_JOINT[ pPMX->NumJoint ];

	for( KsInt32 i=0; i < pPMX->NumJoint; i++ )
	{
		pPMX->pJoints[ i ].JointName_J     = KsPMXReadString( pFile );
		pPMX->pJoints[ i ].JointName_E     = KsPMXReadString( pFile );
		pPMX->pJoints[ i ].Type            = pFile->readUInt8();
		pPMX->pJoints[ i ].RigidA          = KsPMXReadIndex( pFile, rigidIndexSize );
		pPMX->pJoints[ i ].RigidB          = KsPMXReadIndex( pFile, rigidIndexSize );
		pPMX->pJoints[ i ].Position.x      = pFile->readReal();
		pPMX->pJoints[ i ].Position.y      = pFile->readReal();
		pPMX->pJoints[ i ].Position.z      = pFile->readReal();
		pPMX->pJoints[ i ].Rotation.x      = pFile->readReal();
		pPMX->pJoints[ i ].Rotation.y      = pFile->readReal();
		pPMX->pJoints[ i ].Rotation.z      = pFile->readReal();
		pPMX->pJoints[ i ].MoveLimitMin.x  = pFile->readReal();
		pPMX->pJoints[ i ].MoveLimitMin.y  = pFile->readReal();
		pPMX->pJoints[ i ].MoveLimitMin.z  = pFile->readReal();
		pPMX->pJoints[ i ].MoveLimitMax.x  = pFile->readReal();
		pPMX->pJoints[ i ].MoveLimitMax.y  = pFile->readReal();
		pPMX->pJoints[ i ].MoveLimitMax.z  = pFile->readReal();
		pPMX->pJoints[ i ].AngleLimitMin.x = pFile->readReal();
		pPMX->pJoints[ i ].AngleLimitMin.y = pFile->readReal();
		pPMX->pJoints[ i ].AngleLimitMin.z = pFile->readReal();
		pPMX->pJoints[ i ].AngleLimitMax.x = pFile->readReal();
		pPMX->pJoints[ i ].AngleLimitMax.y = pFile->readReal();
		pPMX->pJoints[ i ].AngleLimitMax.z = pFile->readReal();
		pPMX->pJoints[ i ].SpringMove.x    = pFile->readReal();
		pPMX->pJoints[ i ].SpringMove.y    = pFile->readReal();
		pPMX->pJoints[ i ].SpringMove.z    = pFile->readReal();
		pPMX->pJoints[ i ].SpringAngle.x   = pFile->readReal();
		pPMX->pJoints[ i ].SpringAngle.y   = pFile->readReal();
		pPMX->pJoints[ i ].SpringAngle.z   = pFile->readReal();
	}

	return pPMX;
}

/*************************************************************************************************/
/*
 * PMXファイル読み込み処理
 * @param	filePath	ファイルパス
 * @return	PMXファイルデータ
 */
/*************************************************************************************************/
KS_PMX_DATA* KsLoadPMXFile( const KsString& filePath )
{
	KsFileObject*	pFile = ksNew KsFileBuffer( filePath, ksREAD | ksBINARY );
	KS_PMX_DATA*	pPMX  = KsLoadPMXFile( pFile );

	ksDELETE( pFile );

	return pPMX;
}

/*************************************************************************************************/
/*
 * PMXファイル読み込み処理
 * @param	filePath	ファイルパス
 * @return	PMXファイルデータ
 */
/*************************************************************************************************/
KsHumanIK* KsHumanIKCreateFromPMX( KS_PMX_DATA*	pPMX, KsModel* pModel )
{
#if 0
	KsHumanIK*	pHumanIK = ksNew KsHumanIK( pModel );

	for( KsUInt16 i=0; i<pPMX->NumBone; i++ )
	{
		KsIKParameter*	pIKParameter = ksNew KsIKParameter();
		KsIKEffector*	pIKEffector  = ksNew KsIKEffector();
	
		KsUInt16 boneIndex = pPMX->pBones[ i ].BoneIndex;

		KsString boneName = pPMX->BoneList.Bones[ boneIndex ].Name;
		
		boneIndex	= pModel->getBoneIndex( boneName );

		if( boneIndex < 0 ) continue;

		KsUInt16 targetIndex = pPMX->IKList.IKList[ i ].TargetBoneIndex;

		KsString targetName = pPMX->BoneList.Bones[ targetIndex ].Name;
		
		targetIndex	= pModel->getBoneIndex( targetName );

		if( targetIndex < 0 ) continue;

		pIKParameter->BoneIndex       = boneIndex;
		pIKParameter->BoneName        = boneName;
		pIKParameter->TargetBoneIndex = targetIndex;
		pIKParameter->TargetBoneName  = targetName;
		pIKParameter->ControlWeight   = pPMX->IKList.IKList[ i ].ControlWeight;
		pIKParameter->ChainLength     = (KsInt32)pPMX->IKList.IKList[ i ].ChainLength;
		pIKParameter->Iterations      = (KsInt32)pPMX->IKList.IKList[ i ].Iterations;

		KsBone*	pTarget   = pModel->m_vpBones[ boneIndex   ];
		KsBone*	pEffector = pModel->m_vpBones[ targetIndex ];

		KsString childName;

		pIKEffector->m_controlWeight = pPMX->IKList.IKList[ i ].ControlWeight;
		pIKEffector->m_iterations    = (KsInt32)pPMX->IKList.IKList[ i ].Iterations;
		pIKEffector->m_pTarget       = ksNew KsIKPoint( pTarget );
		pIKEffector->m_pEffector     = ksNew KsIKPoint( pEffector );


		for( KsUInt8 j=0; j<pPMX->IKList.IKList[ i ].ChainLength; j++ )
		{
			KsUInt16	childIndex = pPMX->IKList.IKList[ i ].ChildBoneIndices[ j ];

			childName  = pPMX->BoneList.Bones[ childIndex ].Name;
			childIndex = pModel->getBoneIndex( childName );

			KsBone*		pChild   = pModel->m_vpBones[ childIndex ];
			KsIKPoint*	pIKPoint = ksNew KsIKPoint( pChild );

			pIKEffector->m_vpChain.push_back( pIKPoint );

			pIKParameter->ChildBoneIndices.push_back( childIndex );
			pIKParameter->ChildBoneNames.push_back( childName );
		}

		pHumanIK->m_vpParameters.push_back( pIKParameter );
		pHumanIK->m_vpEffectors.push_back( pIKEffector );
	}

	return pHumanIK;
#else
	return NULL;
#endif
}

/*************************************************************************************************/
/*
 * PMXファイル読み込み処理
 * @param	filePath	ファイルパス
 * @return	PMXファイルデータ
 */
/*************************************************************************************************/
KsPhysicsController* KsPhysicsControllerCreateFromPMX( KS_PMX_DATA* pPMX, KsModel* pModel )
{
#if 0
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

	if( 0 == pPMX->RigidBodyList.RigidBodyCount )
	{
		return NULL;
	}

	KsPhysicsController*	pPhysicsController = ksNew KsPhysicsController();

	for( KsUInt32 i=0 ; i < pPMX->RigidBodyList.RigidBodyCount ; i++ )
	{
		KS_PMX_RIGID_BODY*	pPMXRigidBody = &pPMX->RigidBodyList.RigidBodyList[ i ];
		
		KsBone*				pBone     = NULL;
		KsInt32				boneIndex = 0;

		if( pPMXRigidBody->BoneIndex == 0xFFFF )
		{
			boneIndex = pModel->getBoneIndex( "センター" );
		}
		else
		{
			boneIndex = pModel->getBoneIndex( pPMX->BoneList.Bones[ pPMXRigidBody->BoneIndex ].Name );
		}

		if( boneIndex >= 0 )
		{
			pBone = pModel->m_vpBones[ boneIndex ];
		}

		KsCollisionShape*	pShape = NULL;
		KsVector3d			halfExtents;

		switch( pPMXRigidBody->ShapeType )
		{
			case ksPMX_SHAPHE_SPHERE:
			{
				halfExtents.x = pPMXRigidBody->Width;
				pShape = pPhysicsSystem->createShape( ksSHAPE_SPHERE, halfExtents );
				break;
			}
			case ksPMX_SHAPHE_BOX:
			{
				halfExtents.x = pPMXRigidBody->Width;
				halfExtents.y = pPMXRigidBody->Height;
				halfExtents.z = pPMXRigidBody->Depth;
				pShape = pPhysicsSystem->createShape( ksSHAPE_BOX, halfExtents );
				break;
			}
			case ksPMX_SHAPHE_CAPSULE:
			{
				halfExtents.x = pPMXRigidBody->Width;
				halfExtents.y = pPMXRigidBody->Height;
				pShape = pPhysicsSystem->createShape( ksSHAPE_CAPSULE, halfExtents );
				break;
			}
			default:
				break;
		}

		// 質量と慣性テンソルの設定
		KsReal		mass = 0.0f;
		KsVector3d	localInertia;

		if( 0 != pPMXRigidBody->RigidBodyType )
		{
			mass = pPMXRigidBody->Mass;
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
		BoneOffset.setEulerZYX( pPMXRigidBody->Rotation.x, pPMXRigidBody->Rotation.y, pPMXRigidBody->Rotation.z );
		BoneOffset.setTranslate( pPMXRigidBody->Position.x, pPMXRigidBody->Position.y, pPMXRigidBody->Position.z );

		// 剛体の初期トランスフォーム作成
		KsMatrix4x4		Transform = KsMatrix4x4::IDENTITY;
		Transform.setTranslate( BonePos.x, BonePos.y, BonePos.z );
		Transform = BoneOffset * Transform;

		KsMotionState*		pMotionState = NULL;

		switch( pPMXRigidBody->RigidBodyType )
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
			//case 2 : pMotionState = ksNew btKinematicMotionState( Transform, bttrBoneOffset, pBone );	break;
			default:
				break;
		}

		// 剛体のパラメータの設定
		KsRigidBody::KsRigidBodyConstructionInfo	info( mass, pMotionState, pShape, localInertia );

		info.m_linearDamping     = pPMXRigidBody->LinearDamping;	// 移動減
		info.m_angularDamping    = pPMXRigidBody->AngularDamping;	// 回転減
		info.m_restitution       = pPMXRigidBody->Restitution;		// 反発力
		info.m_friction          = pPMXRigidBody->Friction;			// 摩擦力
		info.m_additionalDamping = ksTRUE;

		KsRigidBody*	pRigidBody = pPhysicsSystem->createRigidBody( info );

		// Kinematic設定
		if( 0 == pPMXRigidBody->RigidBodyType )
		{
			pRigidBody->setCollisionFlags( pRigidBody->getCollisionFlags() | ksCF_KINEMATIC_OBJECT );
			pRigidBody->setActivationState( ksDISABLE_DEACTIVATION );
		}

		pRigidBody->setSleepingThresholds( 0.0f, 0.0f );

		// 剛体をシミュレーションワールドに追加
		pWorld->addRigidBody( pRigidBody, 0x0001 << pPMXRigidBody->ColGroupIndex, pPMXRigidBody->ColGroupMask );

		// RigidBody追加
		pPhysicsController->addRigidBody( pRigidBody );

		// パラメータ生成
		KsPhysicsParameter*	pParameter = ksNew KsPhysicsParameter();

		pParameter->m_type          = pPMXRigidBody->RigidBodyType;
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
	for( KsUInt32 i=0 ; i < pPMX->ConstraintList.ConstraintCount ; i++ )
	{
		KS_PMX_CONSTRAINT*	pPMXConstraint = &pPMX->ConstraintList.ConstraintList[ i ];

		// コンストレイントのトランスフォームを作成
		KsMatrix4x4		bttrTransform;
		bttrTransform.setEulerZYX( pPMXConstraint->Rotation.x, pPMXConstraint->Rotation.y, pPMXConstraint->Rotation.z );
		bttrTransform.setTranslate( pPMXConstraint->Position.x, pPMXConstraint->Position.y, pPMXConstraint->Position.z );

		KsRigidBody*	pRigidBodyA = pPhysicsController->getRigidBody( pPMXConstraint->RigidA );
		KsRigidBody*	pRigidBodyB = pPhysicsController->getRigidBody( pPMXConstraint->RigidB );

		// 剛体A,Bから見たコンストレイントのトランスフォームを作成 
		KsMatrix4x4		bttrRigidAInvTransform = pRigidBodyA->getWorldTransform().inverse();
		KsMatrix4x4		bttrRigidBInvTransform = pRigidBodyB->getWorldTransform().inverse();

		//bttrRigidAInvTransform = bttrRigidAInvTransform * bttrTransform;
		//bttrRigidBInvTransform = bttrRigidBInvTransform * bttrTransform;

		bttrRigidAInvTransform = bttrTransform * bttrRigidAInvTransform;
		bttrRigidBInvTransform = bttrTransform * bttrRigidBInvTransform;

		KsPhysicsParameter*	pParameterA = pPhysicsController->getParameter( pPMXConstraint->RigidA );
		KsPhysicsParameter*	pParameterB = pPhysicsController->getParameter( pPMXConstraint->RigidB );

		KsSpringConstraint* pConstraint = (KsSpringConstraint*)pPhysicsSystem->createConstraint( ksCONSTRAINT_SPRING, *pRigidBodyA, *pRigidBodyB, bttrRigidAInvTransform, bttrRigidBInvTransform, ksTRUE );

		// 各種制限パラメータのセット
		pConstraint->setLinearLowerLimit( pPMXConstraint->PosLimitL.x, pPMXConstraint->PosLimitL.y, pPMXConstraint->PosLimitL.z );
		pConstraint->setLinearUpperLimit( pPMXConstraint->PosLimitL.x, pPMXConstraint->PosLimitL.y, pPMXConstraint->PosLimitL.z );

		pConstraint->setAngularLowerLimit( pPMXConstraint->RotLimitL.x, pPMXConstraint->RotLimitL.y, pPMXConstraint->RotLimitL.z );
		pConstraint->setAngularUpperLimit( pPMXConstraint->RotLimitL.x, pPMXConstraint->RotLimitL.y, pPMXConstraint->RotLimitL.z );

		// 0 : translation X
		if( pPMXConstraint->SpringPos.x != 0.0f )
		{
			pConstraint->enableSpring( 0, ksTRUE );
			pConstraint->setStiffness( 0, pPMXConstraint->SpringPos.x );
		}

			// 1 : translation Y
		if( pPMXConstraint->SpringPos.y != 0.0f )
		{
			pConstraint->enableSpring( 1, ksTRUE );
			pConstraint->setStiffness( 1, pPMXConstraint->SpringPos.y );
		}

			// 2 : translation Z
		if( pPMXConstraint->SpringPos.z != 0.0f )
		{
			pConstraint->enableSpring( 2, ksTRUE );
			pConstraint->setStiffness( 2, pPMXConstraint->SpringPos.z );
		}

		pConstraint->enableSpring( 3, ksTRUE );	pConstraint->setStiffness( 3, pPMXConstraint->SpringRot.x );
		pConstraint->enableSpring( 4, ksTRUE );	pConstraint->setStiffness( 4, pPMXConstraint->SpringRot.y );
		pConstraint->enableSpring( 5, ksTRUE );	pConstraint->setStiffness( 5, pPMXConstraint->SpringRot.z );

		pPhysicsController->addConstraint( pConstraint );

		// シミュレーションワールドに追加
		pWorld->addConstraint( pConstraint );
	}

	return pPhysicsController;
#else
	return NULL;
#endif
}

/*************************************************************************************************/
/*
 * PMXファイル読み込み処理
 * @param	filePath	ファイルパス
 * @return	PMXファイルデータ
 */
/*************************************************************************************************/
KsModel* KsModelCreateFromPMX( KS_PMX_DATA*	pPMX, KsUInt32 flags )
{
	KsRenderSystem*				pRenderSystem          = KsRenderSystem::getInstancePtr();
	KsShaderManager*			pShaderManager         = KsShaderManager::getInstancePtr();
	KsInputLayoutManager*		pInputLayoutManager    = KsInputLayoutManager::getInstancePtr();
	KsHardwareBufferManager*	pBufferManager         = KsHardwareBufferManager::getInstancePtr();

	KsVertexShader*				pVS = (KsVertexShader*)pShaderManager->createFromFile( "GBuffer.fx", "VS_GBuffer", ksSHADE_MODEL_5_0, ksVERTEX_SHADER );	// Vertex Shader 
	KsPixelShader*				pPS = (KsPixelShader*)pShaderManager->createFromFile(  "GBuffer.fx", "PS_GBuffer", ksSHADE_MODEL_5_0, ksPIXEL_SHADER  );	// Pixel Shader
	KsInputLayout*				pIL = pInputLayoutManager->createInputLayout( InputLayoutMMD, ksARRAYSIZE( InputLayoutMMD ), (KsVertexShader*)pVS );		// Input Layout
	KsConstantBuffer*			pCB = pBufferManager->createConstantBuffer( KsGBufferParameter::Size, 0 );													// Constant Buffer
	KsConstantBuffer*			pMB = pBufferManager->createConstantBuffer( KsMatrixPalletParameter::Size, 0 );												// Constant Buffer

	// モデルビルダー
	KsModelBuilder				builder;
	const KsInt32				materialCount = static_cast< KsInt32 >( pPMX->NumMaterial );	// マテリアル単位でパーツ分割する
	const KsInt32				boneCount     = static_cast< KsInt32 >( pPMX->NumBone );
	const KsUInt32				numVertex     = pPMX->NumVertex;

	KS_MMD_VERTEX*				pVertices     = ksNew KS_MMD_VERTEX[ numVertex ];
	KS_MMD_VERTEX*				pVertices_New = ksNew KS_MMD_VERTEX[ numVertex ];
	KsUInt32					offset        = 0;
	KsVector3d					headPos;
	KsChar						DataPath[ 1024 ];

	//-----------------------------------------------------------------------------
	// モデル生成開始
	//-----------------------------------------------------------------------------
	KsModel*	pModel = builder.start( pPMX->ModelInfo.Comment_J, boneCount );

	//-----------------------------------------------------------------------------
	// 親を抜き出す
	//-----------------------------------------------------------------------------
	for( KsInt32 i=0; i<boneCount; i++ )
	{
		KsBone*	pBone = ksNew KsBone();

		pBone->m_name    = pPMX->pBones[ i ].BoneName_J;
		pBone->m_index   = i + 1;

		// ルートかどうかをチェックする
		if( -1 == pPMX->pBones[ i ].Parent || 0xFFFF == pPMX->pBones[ i ].Parent )
		{
			headPos.set( pPMX->pBones[ i ].Position.x, pPMX->pBones[ i ].Position.y, pPMX->pBones[ i ].Position.z );

			pBone->m_parent           = 0;
			pBone->m_defaultTransform = KsMatrix4x4::CreateTranslation( headPos );
		}
		else
		{
			headPos.set(	pPMX->pBones[ i ].Position.x - pPMX->pBones[ pPMX->pBones[ i ].Parent ].Position.x,
							pPMX->pBones[ i ].Position.y - pPMX->pBones[ pPMX->pBones[ i ].Parent ].Position.y,
							pPMX->pBones[ i ].Position.z - pPMX->pBones[ pPMX->pBones[ i ].Parent ].Position.z );
			
			pBone->m_parent           = pPMX->pBones[ i ].Parent + 1;
			pBone->m_defaultTransform = KsMatrix4x4::CreateTranslation( headPos );
		}

		// 逆マトリックスを生成する
		builder.addBone( pBone );
	}

	//-----------------------------------------------------------------------------
	// 親子関係を構築する
	//-----------------------------------------------------------------------------
	builder.createHierarchy();

	//-----------------------------------------------------------------------------
	// AbsoluteMatrixを構築する
	//-----------------------------------------------------------------------------
	builder.createAbsoluteTransforms();

	//-----------------------------------------------------------------------------
	// 頂点を使いやすい形に変換しなおす
	//-----------------------------------------------------------------------------
	for( KsUInt32 vi = 0; vi < numVertex; vi++ )
	{
		KS_PMX_VERTEX*	pPMX_Vertices = &pPMX->pVertices[ vi ];

		pVertices[ vi ].x = pPMX_Vertices->Position.x;
		pVertices[ vi ].y = pPMX_Vertices->Position.y;
		pVertices[ vi ].z = pPMX_Vertices->Position.z;

		pVertices[ vi ].nx = pPMX_Vertices->Normal.x;
		pVertices[ vi ].ny = pPMX_Vertices->Normal.y;
		pVertices[ vi ].nz = pPMX_Vertices->Normal.z;

		pVertices[ vi ].u = pPMX_Vertices->TextureCoord.x;
		pVertices[ vi ].v = pPMX_Vertices->TextureCoord.y;

		pVertices[ vi ].indices_16[ 0 ] = builder.getMatrixPalletIndex( pPMX_Vertices->Weight.Indices[ 0 ] + 1 );
		pVertices[ vi ].indices_16[ 1 ] = builder.getMatrixPalletIndex( pPMX_Vertices->Weight.Indices[ 1 ] + 1 );
		pVertices[ vi ].indices_16[ 2 ] = builder.getMatrixPalletIndex( pPMX_Vertices->Weight.Indices[ 2 ] + 1 );
		pVertices[ vi ].indices_16[ 3 ] = builder.getMatrixPalletIndex( pPMX_Vertices->Weight.Indices[ 3 ] + 1 );

		pVertices[ vi ].weight[ 0 ] = pPMX_Vertices->Weight.Weight[ 0 ];
		pVertices[ vi ].weight[ 1 ] = pPMX_Vertices->Weight.Weight[ 1 ];
		pVertices[ vi ].weight[ 2 ] = pPMX_Vertices->Weight.Weight[ 2 ];
		pVertices[ vi ].weight[ 3 ] = pPMX_Vertices->Weight.Weight[ 3 ];
	}

	//-----------------------------------------------------------------------------
	// インデックス生成
	//-----------------------------------------------------------------------------
	KsUInt32 fs = 0;
	KsUInt32 fe = 0;

	for( KsInt32 mi=0; mi<materialCount; mi++ )
	{
		KS_PMX_MATERIAL*	pPMX_Material = &pPMX->pMaterials[ mi ];
		KsUInt32			numFaceVertex = static_cast<KsUInt32>( pPMX_Material->NumIndices );
		KsString*			pTextureName  = KsPMXGetTexture( pPMX, pPMX_Material->NormalTextureIndex );
		KsTexture*			pTexture      = NULL;
		KsEffectMMD*		pMaterial     = ksNew KsEffectMMD();

		// マテリアルパラメータをセットする
		pMaterial->setDiffuse(  pPMX_Material->Diffuse.x,  pPMX_Material->Diffuse.y,  pPMX_Material->Diffuse.z,  pPMX_Material->Diffuse.w );
		pMaterial->setAmbient(  pPMX_Material->Ambient.x,  pPMX_Material->Ambient.y,  pPMX_Material->Ambient.z,  1.0f );
		pMaterial->setSpecular( pPMX_Material->Specular.x, pPMX_Material->Specular.y, pPMX_Material->Specular.z, 1.0f );
		pMaterial->setSpecularity( pPMX_Material->SpecularPower );
		pMaterial->m_pVS = pVS;
		pMaterial->m_pPS = pPS;
		pMaterial->m_pCB = pCB;
		pMaterial->m_pMB = pMB;

		// Textureを読み込む
		if( pTextureName )
		{
			pMaterial->setDiffuseTextureName( *pTextureName );

			if( 0 == flags )
			{
				strcpy( DataPath, MODEL_DATA_PATH );
				strcat( DataPath, pTextureName->c_str() );
				pTexture = pRenderSystem->createTextureFromFile( DataPath, 0 );
			}
			else
			{
				pTexture = pRenderSystem->createTexture( NULL, 1, 1, KS_GI_FORMAT_R8G8B8A8_UNORM, 0, 0 );
				pTexture->setName( pTextureName->c_str() );
			}

			pMaterial->setDiffuseTexture( pTexture );
		}

		//
		fs  = fe;
		fe += numFaceVertex;

		KsUInt32	numIndex     = pPMX->NumFaces;
		KsUInt16*	pIndexMap    = ksNew KsUInt16[ numIndex ];
		KsUInt16*	pIndices_New = ksNew KsUInt16[ numIndex ];
		KsUInt32	vertexCount  = 0;
		KsUInt32	indexCount   = 0;

		KsMemset( pIndexMap, 0xffff, sizeof(KsUInt16) * numIndex );

		for( KsUInt32 i=fs; i<fe; i++ )
		{
			const KsUInt16 face    = pPMX->Indices[ i ];
			
			if( pIndexMap[ face ] == 0xffff )
			{
				pIndexMap[ face ] = vertexCount;

				pVertices_New[ vertexCount ] = pVertices[ face ];

				++vertexCount;
			}

			pIndices_New[ indexCount ] = pIndexMap[ face ];
			
			++indexCount;
		}

		// メッシュパーツ生成する
		builder.createMeshPart( pMaterial, pIL, vertexCount, &pVertices_New[ 0 ], indexCount, &pIndices_New[ 0 ] );

		offset += numFaceVertex;

		ksDELETEARRAY( pIndexMap );
		ksDELETEARRAY( pIndices_New );

	}

	//-----------------------------------------------------------------------------
	// 後処理
	//-----------------------------------------------------------------------------
	builder.finish();

	return pModel;
}

/*************************************************************************************************/
/*
 * PMXファイル読み込み処理
 * @param	filePath	ファイルパス
 * @return	PMXファイルデータ
 */
/*************************************************************************************************/
KsModel* KsModelCreateFromPMX( const KsString& filePath )
{
	KS_PMX_DATA*	pPMX = KsLoadPMXFile( filePath );

	if( NULL == pPMX )
	{
		return NULL;
	}

	return KsModelCreateFromPMX( pPMX );
}

/*************************************************************************************************/
/*
 * PMXファイル読み込み処理
 * @param	filePath	ファイルパス
 * @return	PMXファイルデータ
 */
/*************************************************************************************************/
KsActor* KsActorCreateFromPMX( const KsString& filePath )
{
	KS_PMX_DATA*	pPMX = KsLoadPMXFile( filePath );

	if( NULL == pPMX )
	{
		return NULL;
	}

	KsModel*				pModel   = KsModelCreateFromPMX( pPMX );
	KsHumanIK*				pHumanIK = KsHumanIKCreateFromPMX( pPMX, pModel );
	KsPhysicsController*	pPhysics = KsPhysicsControllerCreateFromPMX( pPMX, pModel );
	KsActor*				pActor   = ksNew KsActor( pModel );

	pActor->setHumanIK( pHumanIK );
	pActor->setPhysics( pPhysics );

	return pActor;

	return NULL;
}

