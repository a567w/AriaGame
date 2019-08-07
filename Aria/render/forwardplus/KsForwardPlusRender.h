/************************************************************************************************/
/** 
 * @file		KsForwardPlusRender.h
 * @brief		Foward+�����_�����O
 * @author		Tsukasa Kato
 * @date		2006/07/02
 * @since		2006/07/02
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSDFORWARDPLUSRENDER_H__
#define __KSDFORWARDPLUSRENDER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsForwardPlusRender
 * @brief		��{�^�X�N�}�l�[�W���N���X
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		0.10
 * @note		�Ȃ�
 */
/************************************************************************************************/
class KsForwardPlusRender
{
	public:
		static const KsUInt32 MAX_NUM_LIGHTS          = 2*1024;
        static const KsUInt32 TILE_RES                = 16;
        static const KsUInt32 MAX_NUM_LIGHTS_PER_TILE = 544;

		/**
		 * �R���X�g���N�^
		 * @param	pRenderSystem	�`��V�X�e��
		 * @param	width			�����_�[�^�[�Q�b�g�̕�
		 * @param	height			�����_�[�^�[�Q�b�g�̍���
		 */
		KsForwardPlusRender( KsRenderSystem* pRenderSystem, KsUInt32 width, KsUInt32 height, KsUInt32 MSAA=MSAA_SAMPLES );

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsForwardPlusRender();

		/**
		 * �r���[�|�[�g�ݒ�
		 * @param		x		X���W
		 * @param		y		X���W
		 * @param		w		��
		 * @param		h		����
 		 * @param		near	near�N���b�v�l
		 * @param		far		far�N���b�v�l
		 */
		void						setViewport( KsInt32 x, KsInt32 y, KsInt32 w, KsInt32 h, KsReal minZ, KsReal maxZ, KsRenderContext* pRenderContext=NULL );

	private:
		/**
		 * �����_�[�X�e�[�g�𐶐�����
		 */
		void						createRenderState();

	private:
		KsRenderSystem*				m_pRenderSystem;				/**< �`��V�X�e��						*/
		KsRenderContext*			m_pRenderContext;				/**< �`��R���e�L�X�g					*/
		KsGameSystem*				m_pGameSystem;					/**< �Q�[���V�X�e���Ǘ��N���X			*/
		KsViewport					m_viewport;						/**< �r���[�|�[�g						*/


        // state
		KsBlendState*				m_pAdditiveBlendingState;		/**< �s�����u�����h�X�e�[�g				*/
		KsDepthStencilState*		m_pDisableDepthWrite;			/**< �[�x�X�e���V���X�e�[�g				*/
		KsDepthStencilState*		m_pDisableDepthTest;			/**< �[�x�X�e���V���X�e�[�g				*/
		KsRasterizerState*			m_pDisableCulling;				/**< ���X�^���C�Y�X�e�[�g				*/
};


#if 0

class KsRenderThread;
class KsGameSystem;
class KsShadowManager;
class KsDeferredLighting;

/************************************************************************************************/
/**
 * @class		KsForwardPlusRender
 * @brief		��{�^�X�N�}�l�[�W���N���X
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		0.10
 * @note		�Ȃ�
 */
/************************************************************************************************/
class KsForwardPlusRender
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
		KsForwardPlusRender( KsRenderSystem* pRenderSystem, KsUInt32 width, KsUInt32 height, KsUInt32 MSAA=MSAA_SAMPLES );

		/**
		 * �f�X�g���N�^
		 */
		virtual					~KsForwardPlusRender();

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
		KsRasterizerState*		m_pRasterizerState;						/**< ���X�^���C�Y�X�e�[�g				*/
		KsBlendState*			m_pOpaqueState;							/**< �s�����u�����h�X�e�[�g				*/
		KsBlendState*			m_pAlphaToCoverageState;				/**< �A���t�@�u�����h�X�e�[�g			*/
		KsDepthStencilState*	m_pDepthState;							/**< �[�x�X�e���V���X�e�[�g				*/


		KS_BLEND_DESC			desc = KsBlendState::DEFAULT;
		m_pBlendState = pRenderSystem->createBlendState( &desc );

	// ���X�^���C�Y�X�e�[�g
	{
		KS_RASTERIZER_DESC		desc = KsRasterizerState::DEFAULT;
		//desc.CullMode = KS_CULL_NONE;
		desc.CullMode = KS_CULL_BACK;
		desc.
		m_pRasterizerState = pRenderSystem->createRasterizerState( &desc );

    D3D11_BLEND_DESC BlendStateDesc;
    BlendStateDesc.AlphaToCoverageEnable = FALSE;
    BlendStateDesc.IndependentBlendEnable = FALSE;
    BlendStateDesc.RenderTarget[0].BlendEnable = FALSE;
    BlendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    BlendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE; 
    BlendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO; 
    BlendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    BlendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE; 
    BlendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO; 
    BlendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    V_RETURN( pd3dDevice->CreateBlendState( &BlendStateDesc, &g_pOpaqueState ) );
    BlendStateDesc.AlphaToCoverageEnable = TRUE;
    V_RETURN( pd3dDevice->CreateBlendState( &BlendStateDesc, &g_pAlphaToCoverageState ) );


	}

	// �u�����h�X�e�[�g
	{
		KS_BLEND_DESC			desc = KsBlendState::DEFAULT;
		m_pBlendState = pRenderSystem->createBlendState( &desc );
	}

	// ���X�^���C�Y�X�e�[�g
	{
		KS_DEPTH_STENCIL_DESC	desc = KsDepthStencilState::DEFAULT;
		desc.DepthFunc = KS_COMPARISON_GREATER_EQUAL;
		m_pDepthState = pRenderSystem->createDepthStencilState( &desc );
	}

		KsRenderSystem*			m_pRenderSystem;						/**< �`��V�X�e��						*/
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

#endif

#endif /* __KSDFORWARDPLUSRENDER_H__ */

