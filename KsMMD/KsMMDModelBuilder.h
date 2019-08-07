/************************************************************************************************/
/** 
 * @file		KsPMD.h
 * @brief		PMDファイル
 * @author		Tsukasa Kato
 * @date		2010/12/17
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMMDMODELBUILDER_H__
#define __KSMMDMODELBUILDER_H__

/*==============================================================================================*/
/*                                 << インクルード >>												*/
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsModelBuilder
 * @brief		Model Biulder
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksMMD_API KsModelBuilder
{
	public:
		/**
		 * コンストラクタ
		 */

								KsModelBuilder();

		/**
		 * デストラクタ
		 */
								~KsModelBuilder();
	
		KsModel* 				start( const KsString& name, KsUInt32 boneCount );
		KsModel*				finish();

		void					createMeshPart( KsEffect* pEffect, KsInputLayout* pInputLayout, KsUInt32 numVertex, KS_MMD_VERTEX* pVertices, KsUInt32 numIndex, KsUInt16* pIndices );
		void					createHierarchy();
		void					createAbsoluteTransforms();

		void					addBone( KsBone* pBone ){ m_vpBones.push_back( pBone ); }
		KsInt32					getMatrixPalletIndex( KsInt32 index ) const { return m_boneConvertTbl[ index ]; }
	public:
		KsModel*				m_pModel;
		KsMesh*					m_pMesh;
		KsBoneCollection		m_vpBones;
		KsBone*					m_pRoot;
		KsUInt32				m_boneCount;
		KsInt32					m_boneConvertTbl[ 1024 ];
};

void KsCalculateAbsoluteTransforms( KsModel* pModel, KsBone* pBone );
void KsBuildBoneIndex( KsBone* pBone, KsInt32* pIndex, KsInt32* conv_tbl, KsBoneCollection* vpBones );
void KsBuildParentBoneIndex( KsBone* pBone );

#endif /* __KSMMDMODELBUILDER_H__ */

