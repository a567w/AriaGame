/************************************************************************************************/
/** 
 * @file		KsDeferredRender.h
 * @brief		�f�B�t�@�[�h�����_�����O
 * @author		Tsukasa Kato
 * @date		2006/07/02
 * @since		2006/07/02
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSDEFERREDRENDER_H__
#define __KSDEFERREDRENDER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/
#define MSAA_SAMPLES					1

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsRenderThread;
class KsGameSystem;
class KsShadowManager;
class KsDeferredLighting;

/************************************************************************************************/
/**
 * @class		KsDeferredRender
 * @brief		��{�^�X�N�}�l�[�W���N���X
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		0.10
 * @note		�Ȃ�
 */
/************************************************************************************************/
class KsDeferredRender
{
	public:
		static const KsUInt32	MAX_GBUFFER = 5;
		static const KsUInt32	MRT_RENDER_COUNT = 3;
		static const KsUInt32	MAX_RENDER_THREAD = 8;

	public:
		// G-Buffer
		// RT 0 [ Albedo r, g, b ] [ Specular Intensity ]
		// RT 1 [ Normal x, y ] [ Specular Power. ]
		enum ksMRT_TYPE
		{
			ksMRT_NORMAL,			/**< �@�����	    */
			ksMRT_ALBEDO,			/**< Albedo     */
			ksMRT_POSITION,			/**< Position   */
			ksMRT_ZBUFFER,			/**< Z-Buffer   */
			ksMRT_ACCUMULATE		/**< Accumulate */
		};

	public:
		/**
		 * �R���X�g���N�^
		 * @param	pRenderSystem	�`��V�X�e��
		 * @param	width			�����_�[�^�[�Q�b�g�̕�
		 * @param	height			�����_�[�^�[�Q�b�g�̍���
		 */
		KsDeferredRender( KsRenderSystem* pRenderSystem, KsUInt32 width, KsUInt32 height, KsUInt32 MSAA=MSAA_SAMPLES );

		/**
		 * �f�X�g���N�^
		 */
		virtual					~KsDeferredRender();

		/**
		 * �r���[�|�[�g�ݒ�
		 * @param		x		X���W
		 * @param		y		X���W
		 * @param		w		��
		 * @param		h		����
 		 * @param		near	near�N���b�v�l
		 * @param		far		far�N���b�v�l
		 */
		void					setViewport( KsInt32 x, KsInt32 y, KsInt32 w, KsInt32 h, KsReal minZ, KsReal maxZ, KsRenderContext* pRenderContext=NULL );

		void					setRenderTarget_MRT( KsRenderContext* pRenderContext );
		void					setRenderTarget_Default( KsRenderContext* pRenderContext );
		void					clearScene();
		void					clearColor();
		void					clearDepthStencil();
		void					drawDebug();

		/**
		 * ���C�e�B���O������������
		 */
		void					initializeLight();

		/**
		 * �V�F�[�_�[�p�����[�^���X�V����
		 */
		void					updateShaderParameter();

		/**
		 * ���C�g���X�V����( ���C�g�����e�N�X�`���ɏ������� )
		 */
		void					updateLight();

		/**
		 * ���C�e�B���O�v�Z
		 */
		void					computeLighting();

		/**
		 * GBuffer��`�悷��
		 */
		void					renderGBuffer();

		/**
		 * �J�[�g�D�[���֊s����`�悷��
		 */
		void					renderContourExtraction();

		/**
		 * �ŏI�I�ȕ`�������
		 */
		void					finalRender();

		/**
		 * �`�揈��
		 */
		void					render();

		void					addModel( KsModel* pModel );
		void					addActor( KsActor* pActor );

	protected:
		KsRenderSystem*			m_pRenderSystem;						/**< �`��V�X�e��					*/
		KsRenderContext*		m_pRenderContext;						/**< �`��R���e�L�X�g					*/
		KsRenderTarget*			m_pBackBuffer;							/**< �o�b�N�o�b�t�@					*/
		KsRenderTarget*			m_pDepthStencil;						/**< �[�x�o�b�t�@					*/
		KsRenderTarget*			m_pGBuffer[ MAX_GBUFFER ];				/**< G-Buffer						*/
		KsTexture*				m_pGBufferTexture[ MAX_GBUFFER ];		/**< G-Buffer Texture				*/
		KsBool					m_isMRT;								/**< MRT���ǂ����H					*/
		KsModelParameter*		m_pParameter;							/**< Deferred �V�F�[�_�[�p�����[�^	*/
		KsUInt32				m_dispatchWidth;						/**< Compute Shader Dispatch Widht	*/
		KsUInt32				m_dispatchHeight;						/**< Compute Shader Dispatch Height	*/
		KsReal					m_totalTime;							/**< */
		KsViewport				m_viewport;								/**< �r���[�|�[�g					*/

		KsRasterizerState*		m_pRasterizerState;						/**< ���X�^���C�Y�X�e�[�g				*/
		KsBlendState*			m_pBlendState;							/**< ���X�^���C�Y�X�e�[�g				*/
		KsDepthStencilState*	m_pDepthState;							/**< ���X�^���C�Y�X�e�[�g				*/
		
		KsShadowManager*		m_pShadowManager;						/**< �V���h�E�Ǘ��N���X				*/

		// �^�X�N�}�l�[�W���Ɉڍs����
		KsArray<KsModel*>		m_pModels;								/**< */
		KsArray<KsActor*>		m_pActors;								/**< */

		//m_pDiffuseSampler;
		KsRenderThread*			m_pRenderThread[ MAX_RENDER_THREAD ];	/**< */
		KsUInt32				m_numRenderThread;						/**< */
		KsCamera*				m_pCamera;								/**< */

		KsEffect*				m_pDeferredEffect;						/**< Deferred �G�t�F�N�g				*/
		KsEffect*				m_pContourEffect;						/**< �J�[�g�D�[���֊s�� �G�t�F�N�g	*/
		KsDeferredLighting*		m_pLighting;							/**< ���C�e�B���O����	�N���X			*/
		KsGameSystem*			m_pGameSystem;							/**< �Q�[���V�X�e���Ǘ��N���X			*/
};

#endif /* __KSDEFERREDRENDER_H__ */

