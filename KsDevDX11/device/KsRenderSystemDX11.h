/************************************************************************************************/
/** 
 * @file		KsRenderSystemDX11.h
 * @brief		DirectX�`��V�X�e��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSRENDERSYSTEMDX11_H__
#define __KSRENDERSYSTEMDX11_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsTextureManagerDX11;
class KsHardwareBufferManagerDX11;
class KsShaderManagerDX11;

/************************************************************************************************/
/**
 * @class		KsRenderSystemDX11
 * @brief		DirectX�p�̕`��V�X�e��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksDEVDX11_API KsRenderSystemDX11 : public KsRenderSystem
{
	public:
		/**
		 * �R���X�g���N�^
		 */
											KsRenderSystemDX11();

		/**
		 * �R���X�g���N�^
		 * @param		pParam				�����p�����[�^
		 */
											KsRenderSystemDX11( void* pParam );

		/**
		 * �f�X�g���N�^
		 */
		virtual								~KsRenderSystemDX11();

		/**
		 * ����������
		 * @param		hWnd				�E�C���h�E�̃n���h��
		 * @retval		ksTRUE				����������
		 * @retval		ksFALSE				���������s
		 */
		virtual KsBool						initialize( void* pParam );

		/**
		 * �㏈��
		 * @retval		ksTRUE				�㏈������
		 * @retval		ksFALSE				�㏈�����s
		 */
		virtual KsBool						terminate();

		/**
		 * �V�[�����N���A����
		 * @param		flags				�`��t���O
		 * @param		color				�N���A�[�J���[
		 * @param		depth				�f�B�v�X�N���A����l
		 * @param		stencil				�X�e���V���N���A����l
		 */
		virtual void						clearScene( KsUInt32 flags, KsColor color, KsReal depth, KsUInt32 stencil );

		/**
		 * �V�[���`��J�n
		 * @param		flags				�`��t���O
		 * @param		color				�N���A�[�J���[
		 * @param		depth				�f�B�v�X�N���A����l
		 * @param		stencil				�X�e���V���N���A����l
		 */
		virtual void						beginScene( KsUInt32 flags, KsColor color, KsReal depth, KsUInt32 stencil );

		/**
		 * �V�[���`��I��
		 */
		virtual void						endScene();

		/**
		 * �`��o�b�t�@�ƕ\���o�b�t�@�����ւ�
		 */
		virtual void						present();

		/**
		 * �r���[�|�[�g���Z�b�g����
		 * @param		pViewport			�r���[�|�[�g�ݒ�
		 */
		virtual void						setViewport( const KsViewport* pViewport );

		/**
		 * �t�H�O���Z�b�g����
		 */
		virtual void						setFog( ksFOG_MODE mode, KsColor color, KsReal start, KsReal end, KsReal density );

		/*-------------------------------------<< �v���~�e�B�u�`��@�\�֌W >>--------------------------------------------------*/
		/**
		 * ���C����`��(2D)
		 * @param		x					X���W
		 * @param		y					Y���W
		 * @param		color				�F
		 */
		//virtual void						drawLine( KsInt16 x0, KsInt16 y0, KsInt16 x1, KsInt16 y1, KsUInt32 color );

		/**
		 * �Z�`��`��
		 * @param		x					X���W
		 * @param		y					Y���W
		 * @param		w					��
		 * @param		h					����
		 * @param		color				�F
		 */
		virtual void						drawRect( KsReal x, KsReal y, KsReal w, KsReal h, KsColor color );

		/**
		 * �e�N�X�`���t���Z�`��`��
		 * @param		x					X���W
		 * @param		y					Y���W
		 * @param		w					��
		 * @param		h					����
		 * @param		tx					X���W
		 * @param		ty					Y���W
		 * @param		tw					��
		 * @param		th					����
		 * @param		color				�F
		 * @param		pTexture			�e�N�X�`��
		 */
		virtual void						drawRectEx( KsReal x, KsReal y, KsReal w, KsReal h, KsReal tx, KsReal ty, KsReal tw, KsReal th, KsColor color, KsTexture* pTexture );

		/**
		 *
		 */
		virtual void						drawIndexedPrimitive( ksPRIMITIVE_TYPE type, KsUInt32 vertexStart, KsUInt32 indexStart, KsUInt32 primitiveCount, KsVertexBuffer* pVertexBuffer, KsIndexBuffer* pIndexBuffer );

		virtual void						drawPrimitive( ksPRIMITIVE_TYPE type, KsUInt32 vertexStart, KsUInt32 primitiveCount, KsVertexBuffer* pVertexBuffer );

		virtual void						drawPrimitiveUP( ksPRIMITIVE_TYPE type, KsUInt32 primitiveCount, const void* pVertexStreamZeroData, KsUInt32 vertexStreamZeroStride );

		virtual void						copyRect( KsRenderTarget* pSrcTarget, const KsRect* pSrcRect, KsRenderTarget* pDstTarget, const KsRect* pDstRect );

#if 0
		/*------------------------------------------<< Render State�֌W >>--------------------------------------------------*/
		/*------------------------------------------<< Render State�֌W >>--------------------------------------------------*/

		//-------------------------------------------------------------------------------------------------------------------
		// Blend states.
		//-------------------------------------------------------------------------------------------------------------------
		virtual KsBlendState*				Opaque() = 0;
		virtual KsBlendState*				AlphaBlend() = 0;
		virtual KsBlendState*				Additive() = 0;
		virtual KsBlendState*				NonPremultiplied() = 0;

		//-------------------------------------------------------------------------------------------------------------------
		// Depth stencil states.
		//-------------------------------------------------------------------------------------------------------------------
		virtual KsDepthStencilState*		DepthNone() = 0;
		virtual KsDepthStencilState*		DepthDefault() = 0;
		virtual KsDepthStencilState*		DepthRead() = 0;

		//-------------------------------------------------------------------------------------------------------------------
		// Rasterizer states.
		//-------------------------------------------------------------------------------------------------------------------
		virtual KsRasterizerState*			CullNone() = 0;
		virtual KsRasterizerState*			CullClockwise() = 0;
		virtual KsRasterizerState*			CullCounterClockwise() = 0;
		virtual KsRasterizerState*			Wireframe() = 0;

		//-------------------------------------------------------------------------------------------------------------------
		// Sampler states.
		//-------------------------------------------------------------------------------------------------------------------
		virtual KsSamplerState*				PointWrap() = 0;
		virtual KsSamplerState*				PointClamp() = 0;
		virtual KsSamplerState*				LinearWrap() = 0;
		virtual KsSamplerState*				LinearClamp() = 0;
		virtual KsSamplerState*				AnisotropicWrap() = 0;
		virtual KsSamplerState*				AnisotropicClamp() = 0;
		//-------------------------------------------------------------------------------------------------------------------
		// Blend states.
		//-------------------------------------------------------------------------------------------------------------------
		virtual KsBlendState*				Opaque();
		virtual KsBlendState*				AlphaBlend();
		virtual KsBlendState*				Additive();
		virtual KsBlendState*				NonPremultiplied();

		//-------------------------------------------------------------------------------------------------------------------
		// Depth stencil states.
		//-------------------------------------------------------------------------------------------------------------------
		virtual KsDepthStencilState*		DepthNone();
		virtual KsDepthStencilState*		DepthDefault();
		virtual KsDepthStencilState*		DepthRead();

		//-------------------------------------------------------------------------------------------------------------------
		// Rasterizer states.
		//-------------------------------------------------------------------------------------------------------------------
		virtual KsRasterizerState*			CullNone();
		virtual KsRasterizerState*			CullClockwise();
		virtual KsRasterizerState*			CullCounterClockwise();
		virtual KsRasterizerState*			Wireframe();

		//-------------------------------------------------------------------------------------------------------------------
		// Sampler states.
		//-------------------------------------------------------------------------------------------------------------------
		virtual KsSamplerState*				PointWrap();
		virtual KsSamplerState*				PointClamp();
		virtual KsSamplerState*				LinearWrap();
		virtual KsSamplerState*				LinearClamp();
		virtual KsSamplerState*				AnisotropicWrap();
		virtual KsSamplerState*				AnisotropicClamp();
#endif

		/*------------------------------------------<< �e�N�X�`���֌W >>------------------------------------------------------*/
		/**
		 * �e�N�X�`���𐶐�����
		 * @param		pFileName			�t�@�C����
		 * @param		flags				�����t���O
		 * @return							�e�N�X�`���̃|�C���^
		 */
		virtual KsTexture*					createTextureFromFile( const KsChar* pFileName, KsUInt32 flags );

		/**
		 * �e�N�X�`���𐶐�����
		 * @param		pData				�C���[�W�f�[�^�̃|�C���^
		 * @param		width				�e�N�X�`���̕�
		 * @param		height				�e�N�X�`���̍���
		 * @param		format				�e�N�X�`���t�H�[�}�b�g
		 * @param		flags				�����t���O
		 * @return							�e�N�X�`���̃|�C���^
		 */
		virtual KsTexture*					createTexture( const KS_SUBRESOURCE_DATA* pData, KsUInt32 width, KsUInt32 height, KsUInt32 format, KsUInt32 flags, KsUInt32 usage );
		/**
		 * �C���[�W�f�[�^����e�N�X�`���𐶐�����
		 * @param		pImage				�C���[�W�f�[�^�̃|�C���^
		 * @param		flags				�����t���O
		 * @return							�e�N�X�`���̃|�C���^
		 */
		//virtual KsTexture*					createTexture( KsImage* pImage, KsUInt32 flags );

		/**
		 * �e�N�X�`�����Z�b�g����
		 * @param		statge				�e�N�X�`���X�e�[�W
		 * @param		pTexture			�e�N�X�`��
		 */
		virtual void						setTexture( KsUInt32 stage, KsTexture* pTexture );

		/*-----------------------------------<< render �֌W >>--------------------------------------------------*/
		/* �����_�[�^�[�Q�b�g */
		virtual KsRenderTarget*				getRenderTarget();
		virtual void						setRenderTarget( KsRenderTarget* pRenderTarget );
		virtual KsRenderTarget*				createRenderTarget( KsUInt32 width, KsUInt32 height, ksPIXEL_FORMAT format, KsUInt32 flags );
		virtual KsRenderTarget*				createOffscreenTarget( KsUInt32 width, KsUInt32 height, ksPIXEL_FORMAT format, KsUInt32 flags );
		virtual KsRenderTargetTexture*		createRenderTargetTexture( KsUInt32 width, KsUInt32 height, ksPIXEL_FORMAT format, KsUInt32 flags );
		virtual KsRenderTarget*				createRenderTargetFromFile( KsUInt32 width, KsUInt32 height, ksPIXEL_FORMAT format, const KsChar* pFileName, KsColor color );
		virtual KsVertexDeclaration*		createVertexDeclaration( KS_VERTEX_ELEMENT* pVertexElements );
		virtual KsRenderTarget*				createRenderTextureView( KsUInt32 width, KsUInt32 height, KsUInt32 format );
		virtual KsRenderTarget*				createDepthStencilView( KsUInt32 width, KsUInt32 height, KsUInt32 textureFormat, KsUInt32 viewFormat, KsUInt32 resFormat );
		virtual KsUnorderedAccessView*		createUnorderedAccessView( KsUInt32 elementSize, KsUInt32 numElements, KsUInt32 format, KsUInt32 flags );
		virtual KsStructuredBuffer*			createStructuredBuffer( KsUInt32 elementSize, KsUInt32 numElements, KsUInt32 format, KsUInt32 flags );
		virtual void						setVertexDeclaration( KsVertexDeclaration* pVertexDeclaration );

		virtual KsSamplerState*				createSamplerState( const KS_SAMPLER_DESC* pSamplerStateDesc );
		virtual KsBlendState*				createBlendState( const KS_BLEND_DESC* pBlendStateDesc );
		virtual KsRasterizerState*			createRasterizerState( const KS_RASTERIZER_DESC* pRasterizerState );
		virtual KsDepthStencilState*		createDepthStencilState( const KS_DEPTH_STENCIL_DESC* pDepthStencilDesc );
		virtual KsRenderContext*			createDeferredContext();
		virtual KsCommandList*				createCommandList();

		/*-----------------------------------<< �}�e���A���֌W >>--------------------------------------------------*/
		/**
		 * �}�e���A�����Z�b�g����
		 * @param		pMaterial			�}�e���A��
		 */
		virtual void						setMaterial( KsMaterial* pMaterial );

		/*-------------------------------------<< ���C�g�֌W >>--------------------------------------------------*/
		/**
		 * ���C�g��ǉ�����
		 * @param		index				���C�g�̃C���f�b�N�X
		 * @param		pLight				���C x�g���
		 * @note							���C�g��ݒu�ł��鐔�́A�ő�W�ł��B<br>
		 *									���C�g����菜�����Ƃ��͎�菜���������C�g�̃C���f�b�N�X�ƃ��C�g��NULL���Z�b�g���Ă��������B
		 */
		virtual void						setLight( KsUInt32 index, const KsLight* pLight );

		/**
		 * �w�胉�C�g��L���A�����ɂ���B
		 * @param		index				���C�g�̃C���f�b�N�X
		 * @param		flag				���C�g��ON OFF�̃t���O( ksTRUE: ON, ksFALSE: OFF )
		 */
		virtual void						setLightEnable( KsUInt32 index, KsBool flag );

		/*-------------------------------------<< �����_�[�X�e�[�g�֌W >>--------------------------------------------------*/
		/**
		 * �����_�[�X�e�[�g���Z�b�g����
		 * @param		state				�X�e�[�g�̎��
		 * @param		value				�X�e�[�g�ɑΉ�����l
		 */
		virtual void						setRenderState( ksRENDER_STATE_TYPE state, KsUInt32 value );

		/**
		 * �T���v���[�X�e�[�g���Z�b�g����
		 * @param		sampler				�T���v���[�ԍ�
		 * @param		state				�X�e�[�g�̎��
		 * @param		value				�X�e�[�g�ɑΉ�����l
		 */
		virtual void						setSamplerState( KsUInt32 sampler, ksSAMPLER_STATE_TYPE state, KsUInt32 value );

		/**
		 * �g�����X�t�H�[������
		 * @param		state				�g�����X�t�H�[���̃��[�h
		 * @param		pMatrix				�ϊ��}�g���b�N�X
		 */
		virtual void						setTransform( ksTRANSFORM_STATE state, const KsMatrix4x4* pMatrix );

		/**
		 * ��{�ݒ��3D���[�h������������
		 */
		virtual void						auto2DMode();

		/**
		 * ��{�ݒ��3D���[�h������������
		 */
		virtual void						auto3DMode();


#if 0
		/**
		 * ��{�ݒ��3D���[�h������������
		 */
		virtual void						auto2DMode();

		/**
		 * ��{�ݒ��3D���[�h������������
		 */
		virtual void						auto3DMode();

	public:
		KsBool								m_vsync;					/**< vsync���g�p���邩�̃t���O				*/
		KsBool								m_useStencilBuffer;			/**< �X�e���V���o�b�t�@���g�p���邩�ǂ���		*/

		D3DMULTISAMPLE_TYPE					m_FSAAType;					/**< �}���`�T���v�����O�^�C�v					*/
		KsUInt32							m_FSAAQuality;				/**< �}���`�T���v�����O�̕i��(level)			*/
	
		KsAdapterDX*						m_pAdapter;					/**< ���ݎg�p���Ă���A�_�v�^�[				*/
		KsAdapterListDX*					m_pAdapterList;				/**< �A�_�v�^�[���X�g							*/

		HWND								m_hWnd;						/**< �E�C���h�E�̃n���h��						*/
		//HINSTANCE							m_D3DLibrary;				/**< ���C�u����								*/
		KsRenderTarget*						m_pRenderTarget;			/**< �`��^�[�Q�b�g							*/
		KsBool								m_bDeviceLost;				/**< �f�o�C�X�����X�g���ꂽ���ǂ���			*/
		KsBool								m_bResetRenderState;
		KsBool								m_bFullScreen;


#endif
	public:
		ID3D11Device*						getD3DDevice() { return m_pDevice; }

	private:
		KsRenderTarget*						createRenderTargetView();
		KsRenderTarget*						createDepthStencilView();

	private:
		KsAdapterList*						m_pAdapterList;				/**< �A�_�v�^�[���X�g						*/
		IDXGISwapChain*						m_pSwapChain;				/**< 						*/
		ID3D11Device*						m_pDevice;					/**< 						*/
		KsWindow*							m_pWindow;					/**< 						*/
		KsShaderManagerDX11*				m_pShaderManager;			/**< 						*/
		KsTextureManagerDX11*				m_pTextureManager;			/**< 						*/
		KsInputLayoutManagerDX11*			m_pInputLayoutManager;		/**< 						*/
		KsHardwareBufferManagerDX11*		m_pHardwareBufferManager;	/**< 						*/
		KsGraphicsDX11*						m_pGraphics;				/**< 						*/
};

#endif		/* __KSRENDERSYSTEMDX11_H__ */


