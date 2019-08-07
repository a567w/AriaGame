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
#ifndef __KSMODEL_H__
#define __KSMODEL_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsModel
 * @brief		���f��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsModel
{
	public:
		KsString					m_modelName;	/// ���f����
		KsBone*						m_pRoot;		/// ���[�g�{�[��
		KsBoneCollection			m_vpBones;		/// �{�[���R���N�V����
		KsMeshCollection			m_vpMeshes;		/// �I�u�W�F�N�g�̃R���N�V����
		KsTextureCollection			m_vpTextures;	/// �e�N�X�`���R���N�V����
		KsEffectCollection			m_vpEffects;	/// �G�t�F�N�g�R���N�V����
		KsModelParameter*			m_pParameter;	/// ���f���p�����[�^
		KsCamera*					m_pCamera;		/// �J����
		//KsUserData*				m_pUserData;	/// ���[�U�[�f�[�^

	public:
		/**
		 * �R���X�g���N�^
		 */
									KsModel();

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsModel();

		/***
		 * �X�V����
		 */
		void						update();

		/** 
		 * �`�揈��
		 * @param	pRenderContext	�`��R���e�L�X�g
		 */
		void						draw( KsRenderContext* pRenderContext );

		KsBool						updateShaderParameter();
		void						updateBoneMatrix();
		void						updateWorldMatrix();
		void						updateSkinMatrix();

		/**
		 * �e�q�֌W���\�z����
		 */
		void						createHierarchy();

		/**
		 * �}�e���A�����\�z����
		 */
		void						createMaterial();

	private:
		void						calculateAbsoluteTransforms( KsBone* pBone );

	public:
		const KsString&				getModelName() { return m_modelName; }
		KsModelParameter*			getParameter() { return m_pParameter; }
		KsInt32						getBoneIndex( const KsString& name );
		KsUInt32					getBoneCount() const { return m_vpBones.size(); }
		KsUInt32					getMeshCount() const { return m_vpMeshes.size(); }
		KsUInt32					getTextureCount() const { return m_vpTextures.size(); }
		KsUInt32					getEffectCount() const { return m_vpEffects.size(); }

		const KsBone*				getBone( KsUInt32 index ) { return m_vpBones[ index ]; }
		const KsMesh*				getMesh( KsUInt32 index ) { return m_vpMeshes[ index ]; }
		KsTexture*					getTexture( KsUInt32 index ) { return m_vpTextures[ index ]; }
		const KsEffect*				getEffect( KsUInt32 index ) { return m_vpEffects[ index ]; }
		KsEffect*					getEffectDirect( KsUInt32 index ) { return m_vpEffects[ index ]; }

		virtual void				setWorldMatrix( const KsMatrix4x4& worldMatrix );
		virtual void				setViewMatrix( const KsMatrix4x4& viewMatrix );
		virtual void				setProjectionMatrix( const KsMatrix4x4& projMatrix );

		KsTexture*					findTexture( KsChar* pName );
		

	public:
		void						setModelName( const KsString& modelName ) { m_modelName = modelName; }
		void						addBone( KsBone* pBone ) { m_vpBones.push_back( pBone ); }
		void						addMesh( KsMesh* pMesh ) { m_vpMeshes.push_back( pMesh ); }
		void						addTexture( KsTexture* pTexture );
		void						addEffect( KsEffect* pEffect );
};


#endif		/* __KSMODEL_H__ */



