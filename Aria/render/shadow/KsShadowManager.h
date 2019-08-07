/************************************************************************************************/
/** 
 * @file		KsShadowManager.h
 * @brief		�V���h�E�Ǘ�
 * @author		Tsukasa Kato
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSHADOWMANAGER_H__
#define __KSSHADOWMANAGER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/
#define MAX_CASCADES	8	// �J�X�P�[�h�A�V���h�E�}�b�v�ő啪����


/************************************************************************************************/
/**
 * @class		KsShadowManager
 * @brief		�V���h�E�Ǘ�
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsShadowManager
{
	public:
		/** 
		 * �R���X�g���N�^(����������)
		 * @param	pRenderSystem		�`��V�X�e��
		 * @param	width				�V���h�E�`��^�[�Q�b�g��
		 * @param	height				�V���h�E�`��^�[�Q�b�g����
		 * @param	shadowLevels		�V���h�E���x��
		 */
										KsShadowManager( KsRenderSystem* pRenderSystem, KsUInt32 width, KsUInt32 height, KsUInt32 shadowLevels );

		/**
		 * �f�X�g���N�^
		 */
		virtual							~KsShadowManager();

	protected:
		/**
		 * ����������
		 * @param	pRenderSystem		�`��V�X�e��
		 * @param	width				�V���h�E�`��^�[�Q�b�g��
		 * @param	height				�V���h�E�`��^�[�Q�b�g����
		 * @param	shadowLevels		�V���h�E���x��
		 */
		void							initialize( KsRenderSystem* pRenderSystem, KsUInt32 width, KsUInt32 height, KsUInt32 shadowLevels );

		/**
		 * 
		 */
		void							createAABBPoints( KsVector4d* vAABBPoints, const KsVector4d& vCenter, const KsVector4d& vExtents );

		/**
		 * 
		 */
		void							createFrustumPointsFromCascadeInterval( KsReal fCascadeIntervalBegin, KsReal fCascadeIntervalEnd, KsMatrix4x4& vProjection, KsVector4d* pvCornerPointsWorld );

		/**
		 * �t���[��������
		 */
		void							initFrame();

		void							renderShadowsForAllCascades();

	protected:
		KsRenderSystem*					m_pRenderSystem;					/**< �`��V�X�e��					*/
		KsRenderContext*				m_pRenderContext;					/**< �`��R���e�L�X�g					*/

		KsVector4d						m_vSceneAABBMin;					// AABB����p�o�E���f�B���O�{�b�N�X
		KsVector4d						m_vSceneAABBMax;					// AABB����p�o�E���f�B���O�{�b�N�X
		KsMatrix4x4						m_matShadowView;

		KsRenderTarget*					m_pShadowMapRT;						/**< �V���h�E�}�b�v �����_�[�^�[�Q�b�g		*/
		KsInputLayout*					m_pShadowMapIL;						/**< �V���h�E�}�b�v ���_���C�A�E�g		*/
		KsVertexShader*					m_pOrthoShadowVS;					/**< �V���h�E�}�b�v VS�V�F�[�_�[			*/
		
		KsMatrix4x4						m_matShadowProj[ MAX_CASCADES ];	/**< �v���W�F�N�V�����}�g���b�N�X			*/
		KsVertexShader*					m_pShadowMapVS[ MAX_CASCADES ];		/**< �V���h�E�}�b�v VS�V�F�[�_�[			*/
		KsPixelShader*					m_pShadowMapPS[ MAX_CASCADES ];		/**< �V���h�E�}�b�v PS�V�F�[�_�[			*/
		KsViewport						m_viewport[ MAX_CASCADES ];			/**< �V���h�E�}�b�v �r���[�|�[�g			*/

		KsInt32							m_cascadeLevels;					/**< �J�X�P�[�h�̃��x��					*/
		KsRasterizerState*				m_prsScene;
		KsRasterizerState*				m_prsShadow;
		KsRasterizerState*				m_prsShadowPancake;
		KsSamplerState*					m_pSamLinear;
		KsSamplerState*					m_pSamShadowPCF;
		KsSamplerState*					m_pSamShadowPoint;

		
};


#endif		/* __KSSHADOWMANAGER_H__ */

