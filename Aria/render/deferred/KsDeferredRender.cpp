/************************************************************************************************/
/** 
 * @file		KsDeferredRender.cpp
 * @brief		�f�B�t�@�[�h�����_�����O
 * @author		Tsukasa Kato
 * @date		2006/07/02
 * @since		2006/07/02
 * @version		0.1
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << ���[�j���O�}�� >>                                          */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                 << ���C�u���������N >>                                        */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "Aria/KsGamePreCompile.h"
#include "Aria/render/deferred/KsDeferredRender.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsDeferredRender::KsDeferredRender( KsRenderSystem* pRenderSystem, KsUInt32 width, KsUInt32 height, KsUInt32 MSAA )
	: m_pRenderSystem( pRenderSystem )
	, m_pRenderContext( 0 )
	, m_pBackBuffer( 0 )
	, m_pDepthStencil( 0 )
	, m_isMRT( ksFALSE )
	, m_pParameter( 0 )
	, m_dispatchWidth( 0 )
	, m_dispatchHeight( 0 )
	, m_totalTime( 0.0f )
	, m_numRenderThread( 0 )
	, m_pDeferredEffect( 0 )
	, m_pContourEffect( 0 )
	, m_pLighting( 0 )
{
	//----------------------------------------------------------------------
	// �p�����[�^������������B
	//----------------------------------------------------------------------
	KsZeroMemory( m_pGBuffer, sizeof(m_pGBuffer) );
	KsZeroMemory( m_pGBufferTexture, sizeof(m_pGBufferTexture) );
	KsZeroMemory( m_pRenderThread, sizeof(m_pRenderThread) );

	//----------------------------------------------------------------------
	// �x���R���e�L�X�g���쐬����
	//----------------------------------------------------------------------
	m_pRenderThread[ 0 ] = ksNew KsRenderThread( pRenderSystem, this );
	m_pRenderThread[ 0 ]->run();
	++m_numRenderThread;

	//----------------------------------------------------------------------
	// �f�B�t�@�[�h�����_�����O�p�̃e�N�X�`�����쐬����
	//----------------------------------------------------------------------

	// Normal Specular [ R, G, B, A]
	m_pGBuffer[ ksMRT_NORMAL     ] = pRenderSystem->createRenderTextureView( width, height,  KS_GI_FORMAT_R16G16B16A16_FLOAT );

	// Albedo [ R, G, B, A]
	m_pGBuffer[ ksMRT_ALBEDO     ] = pRenderSystem->createRenderTextureView( width, height, KS_GI_FORMAT_R8G8B8A8_UNORM );

	// Position [R, G]
	m_pGBuffer[ ksMRT_POSITION   ] = pRenderSystem->createRenderTextureView( width, height, KS_GI_FORMAT_R16G16_FLOAT );

	// ZBuffer
	m_pGBuffer[ ksMRT_ZBUFFER    ] = pRenderSystem->createDepthStencilView( width, height, KS_GI_FORMAT_R32_TYPELESS, KS_GI_FORMAT_D32_FLOAT, KS_GI_FORMAT_R32_FLOAT );

	// Light [ R, G, B, A] (deferred lighting accumulation buffer)
	m_pGBuffer[ ksMRT_ACCUMULATE ] = pRenderSystem->createRenderTextureView( width, height, KS_GI_FORMAT_R16G16B16A16_FLOAT );

	// �e�N�X�`�����o���Ă���
	m_pGBufferTexture[ ksMRT_NORMAL     ] = ((KsRenderTargetTexture*)m_pGBuffer[ ksMRT_NORMAL     ])->getTexture();
	m_pGBufferTexture[ ksMRT_ALBEDO     ] = ((KsRenderTargetTexture*)m_pGBuffer[ ksMRT_ALBEDO     ])->getTexture();
	m_pGBufferTexture[ ksMRT_POSITION   ] = ((KsRenderTargetTexture*)m_pGBuffer[ ksMRT_POSITION   ])->getTexture();
	m_pGBufferTexture[ ksMRT_ZBUFFER    ] = ((KsRenderTargetTexture*)m_pGBuffer[ ksMRT_ZBUFFER    ])->getTexture();
	m_pGBufferTexture[ ksMRT_ACCUMULATE ] = ((KsRenderTargetTexture*)m_pGBuffer[ ksMRT_ACCUMULATE ])->getTexture();

	// �e�N�X�`�������Z�b�g���Ă���
	m_pGBufferTexture[ ksMRT_NORMAL     ]->setName( "G-Buffer0" );
	m_pGBufferTexture[ ksMRT_ALBEDO     ]->setName( "G-Buffer1" );
	m_pGBufferTexture[ ksMRT_POSITION   ]->setName( "G-Buffer2" );
	m_pGBufferTexture[ ksMRT_ZBUFFER    ]->setName( "Z-Buffer"  );
	m_pGBufferTexture[ ksMRT_ACCUMULATE ]->setName( "Accumulate" );

	//----------------------------------------------------------------------
	// ���C�g�ݒ������
	//----------------------------------------------------------------------

	// �����_�[�^�[�Q�b�g���擾���Ă���(�C�~�f�B�G�C�g �R���e�L�X�g)
	m_pRenderContext = pRenderSystem->getRenderContex();

	m_pBackBuffer   = m_pRenderContext->getRenderTarget();
	m_pDepthStencil = m_pRenderContext->getDepthStencil();

	// ���C�e�B���O�p�Z�b�g�A�b�v
	KsShaderManager*			pShaderManager         = KsShaderManagerDX11::getInstancePtr();
	KsHardwareBufferManager*	pHardwareBufferManager = KsHardwareBufferManagerDX11::getInstancePtr();
	KsInputLayoutManager*		pInputLayoutManager    = KsInputLayoutManagerDX11::getInstancePtr();

	// ���C�e�B���O��������
	m_pLighting = ksNew KsDeferredLighting( pRenderSystem, width, height, MSAA );

	// Deferred �G�t�F�N�g	
	m_pDeferredEffect = ksNew KsDeferredEffect();

	// �J�[�g�D�[���֊s�� �G�t�F�N�g	
	m_pContourEffect =ksNew KsContourEffect();

	// �R���X�^���g�o�b�t�@
	m_pParameter = new KsModelParameter();

	// ���X�^���C�Y�X�e�[�g
	{
		KS_RASTERIZER_DESC		desc = KsRasterizerState::DEFAULT;
		//desc.CullMode = KS_CULL_NONE;
		desc.CullMode = KS_CULL_BACK;
		m_pRasterizerState = pRenderSystem->createRasterizerState( &desc );
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

	// �r���[�|�[�g�ݒ�
	setViewport( 0, 0, 1280, 720, 0.0f, 1.0f );

	//----------------------------------------------------------------------
	// �V���h�E�}�b�v�Ǘ�����
	//----------------------------------------------------------------------
	KsUInt32		shadowLevels = 3;
	KsUInt32		shadowWidth  = 2048;
	KsUInt32		shadowHeight = 2048;
	m_pShadowManager = ksNew KsShadowManager( pRenderSystem, shadowWidth, shadowHeight, shadowLevels );

	//----------------------------------------------------------------------
	// �J��������
	//----------------------------------------------------------------------
	KsCameraManager*	pCameraManager = KsCameraManager::getInstancePtr();
	m_pCamera = ksNew KsFreeCamera();

	pCameraManager->addCamera( m_pCamera );
	pCameraManager->addCamera( ksNew KsPlayerCamera() );
	pCameraManager->setActiveCamera( m_pCamera );
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsDeferredRender::~KsDeferredRender()
{
	ksDELETE( m_pLighting );

	for( KsUInt32 i=0; i<ksARRAYSIZE(m_pGBuffer); i++ )
	{
		ksDELETE( m_pGBuffer[ i ] );
	}
}

/************************************************************************************************/
/*
 * �r���[�|�[�g�ݒ�
 * @param		x		X���W
 * @param		y		X���W
 * @param		w		��
 * @param		h		����
 * @param		near	near�N���b�v�l
 * @param		far		far�N���b�v�l
 */
/************************************************************************************************/
void KsDeferredRender::setViewport( KsInt32 x, KsInt32 y, KsInt32 w, KsInt32 h, KsReal minZ, KsReal maxZ, KsRenderContext* pRenderContext )
{
	// �r���[�|�[�g�ݒ�
	m_viewport.set( x, y, w, h, minZ, maxZ );

	if( pRenderContext )
	{
		pRenderContext->setViewports( &m_viewport );
	}
	else
	{
		m_pRenderContext->setViewports( &m_viewport );
	}
}

/************************************************************************************************/
/*
 * �}���`�����_�[�^�[�Q�b�g���Z�b�g����
 */
/************************************************************************************************/
void KsDeferredRender::setRenderTarget_MRT( KsRenderContext* pRenderContext )
{
	// MRT�Z�b�g
	pRenderContext->setRenderTargets( 3, m_pGBuffer, m_pGBuffer[ ksMRT_ZBUFFER ] );

	m_isMRT = ksTRUE;
}

/************************************************************************************************/
/*
 * �����_�[�^�[�Q�b�g���f�t�H���g�ɖ߂�
 */
/************************************************************************************************/
void KsDeferredRender::setRenderTarget_Default( KsRenderContext* pRenderContext )
{
	// �����_�[�^�[�Q�b�g�����ɖ߂�
	pRenderContext->setRenderTarget( m_pBackBuffer, m_pDepthStencil );

	m_isMRT = ksFALSE;
}

/************************************************************************************************/
/*
 * �V�[�����N���A����
 */
/************************************************************************************************/
void KsDeferredRender::clearScene()
{
	// �^�[�Q�b�g���N���A�[����
	if( m_isMRT )
	{
		m_pRenderContext->clearScenes( 3, (ksCLEAR_FLAG_COLOR | ksCLEAR_FLAG_DEPTH ), KsColor::BLACK, 1.0f, 0 );
	}
	else
	{
		m_pRenderContext->clearScene( (ksCLEAR_FLAG_COLOR | ksCLEAR_FLAG_DEPTH ), KsColor::BLUE, 1.0f, 0 );
	}
}

/************************************************************************************************/
/*
 * �J���[���N���A����
 */
/************************************************************************************************/
void KsDeferredRender::clearColor()
{
	// �^�[�Q�b�g���N���A�[����
	if( m_isMRT )
	{
		KsColor		clearColor( 0, 0, 0, 0 );

		m_pRenderContext->clearScene( ksCLEAR_FLAG_COLOR, clearColor, 1.0f, 0 );
	}
	else
	{
		m_pRenderContext->clearScene( ksCLEAR_FLAG_COLOR, KsColor::BLUE, 1.0f, 0 );
	}
}

/************************************************************************************************/
/*
 * �[�x���N���A����
 */
/************************************************************************************************/
void KsDeferredRender::clearDepthStencil()
{
	// �[�x�X�e���V���o�b�t�@���N���A�[����
	m_pRenderContext->clearScene( ksCLEAR_FLAG_DEPTH | ksCLEAR_FLAG_STENCIL, KsColor::BLACK, 0.0f, 0 );
}

/************************************************************************************************/
/*
 * ���C�e�B���O������������
 */
/************************************************************************************************/
void KsDeferredRender::initializeLight()
{
}

/************************************************************************************************/
/*
 * �V�F�[�_�[�p�����[�^���X�V����
 */
/************************************************************************************************/
void KsDeferredRender::updateShaderParameter()
{
	//KsReal			fNear       = 0.1f;
	//KsReal			fFar        = 1000.0f;

	// (1-z)�Ōv�Z����̂ł�����
	KsReal			fNear       = 1500.0f;
	KsReal			fFar        = 0.05f;
	KsMatrix4x4		worldMat    = KsMatrix4x4::IDENTITY;

	m_pCamera->update();

	m_pParameter->GBuffer.World         = worldMat;
	m_pParameter->GBuffer.Proj          = m_pCamera->getProjMatrix();
	m_pParameter->GBuffer.ViewProj      = m_pCamera->getViewProjMatrix();
	m_pParameter->GBuffer.WorldView     = worldMat * m_pCamera->getViewMatrix();
	m_pParameter->GBuffer.WorldViewProj = worldMat * m_pCamera->getViewProjMatrix();

	m_pParameter->GBuffer.CameraNearFar.set( fNear, fFar, 0.0f, 0.0f );
	m_pParameter->GBuffer.FramebufferDimensionsX = 1280;
	m_pParameter->GBuffer.FramebufferDimensionsY = 720;
	m_pParameter->GBuffer.FramebufferDimensionsZ = 0;
	m_pParameter->GBuffer.FramebufferDimensionsW = 0;

	m_pParameter->GBuffer.World.transpose();
	m_pParameter->GBuffer.Proj.transpose();
	m_pParameter->GBuffer.ViewProj.transpose();
	m_pParameter->GBuffer.WorldView.transpose();
	m_pParameter->GBuffer.WorldViewProj.transpose();

	//m_pRenderContext->updateConstantBuffers( m_pLighting->getLightingBuffer(), m_pParameter );

}

/************************************************************************************************/
/*
 * ���C�g���X�V����( ���C�g�����e�N�X�`���ɏ������� )
 */
/************************************************************************************************/
void KsDeferredRender::updateLight()
{
	m_pLighting->updateLight( 1.0f/60.0f, m_pCamera, m_pParameter );
}

/************************************************************************************************/
/*
 * GBuffer��`�悷��
 */
/************************************************************************************************/
void KsDeferredRender::renderGBuffer()
{
	// �[�x�X�e���V���o�b�t�@���N���A�[����
	//m_pRenderContext->clearDepthStencil( m_pGBuffer[ ksMRT_ZBUFFER ], ksCLEAR_FLAG_DEPTH | ksCLEAR_FLAG_STENCIL, 0.0f, 0 );

	// �[�x�X�e���V���X�e�[�g���Z�b�g����
	m_pRenderContext->setDepthStencilState( m_pDepthState, 0 );
	
	// MRT ���Z�b�g����
	m_pRenderContext->setRenderTargets( MRT_RENDER_COUNT, m_pGBuffer, m_pGBuffer[ ksMRT_ZBUFFER ] );

	m_pRenderContext->clearScenes( 3, (ksCLEAR_FLAG_COLOR | ksCLEAR_FLAG_DEPTH ), KsColor::BLACK, 0.0f, 0 );

	// �u�����h�X�e�[�g
	m_pRenderContext->setBlendState( m_pBlendState, 0, 0xFFFFFFFF );

	// ���X�^���C�U�[�X�e�[�g
	m_pRenderContext->setRasterizerState( m_pRasterizerState );

	// �r���[�|�[�g���Z�b�g����
	m_pRenderContext->setViewports( &m_viewport );

	// ���f����`�悷��
	// Input Layout
	// constant buffer G-Buffer�p( VS, PS�����Z�b�g����)
	// VS, PS���Z�b�g����
	for( KsUInt32 i=0; i<m_pActors.size(); i++ )
	{
		KsActor* pActor = m_pActors[ i ];
		pActor->update( 1.0f/60.0f );
		pActor->draw( m_pRenderContext );
	}

	for( KsUInt32 i=0; i<m_pModels.size(); i++ )
	{
		KsModel* pModel = m_pModels[ i ];
		pModel->update();
		pModel->draw( m_pRenderContext );
	}

	// �����_�[�^�[�Q�b�g�����Z�b�g����
	m_pRenderContext->setRenderTargets( 0, 0, 0 );
}

/************************************************************************************************/
/*
 * ���C�e�B���O����
 */
/************************************************************************************************/
void KsDeferredRender::computeLighting()
{
	m_pLighting->computeLighting( MRT_RENDER_COUNT+1, &m_pGBufferTexture[ 0 ] );
}

/************************************************************************************************/
/*
 * �V�[����`�悷��
 */
/************************************************************************************************/
void KsDeferredRender::finalRender()
{
	m_pDeferredEffect->setShader( m_pRenderContext, this );

	m_pRenderContext->setPixelTexture( 0, 1, 0 );
	m_pRenderContext->setPixelConstantBuffers( 0, 1, m_pLighting->getLightingBuffer() );
	m_pRenderContext->setPrimitiveTopology( KS_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
	m_pRenderContext->setPixelTexture( 8, 1, m_pLighting->getLightingUAV() );
	m_pRenderContext->drawIndexed( 4, 0, 0 );

	//m_pRenderContext->clearState();
}

/************************************************************************************************/
/*
 * �J�[�g�D�[���֊s��
 */
/************************************************************************************************/
void KsDeferredRender::renderContourExtraction()
{
	const KsUInt32	stride = sizeof( KS_CONTOUR_VERTEX );
	const KsUInt32	offset = 0;

	//m_pRenderContext->setPixelTexture( 0, 1, 0 );
	//m_pRenderContext->setPixelTexture( 8, 1, m_pLightBufferUAV );
	m_pRenderContext->setPixelTexture( 0, 1, m_pGBufferTexture[ ksMRT_NORMAL     ] );
	m_pRenderContext->setPixelTexture( 1, 1, m_pGBufferTexture[ ksMRT_ALBEDO     ] );
	m_pRenderContext->setPixelTexture( 3, 1, m_pGBufferTexture[ ksMRT_ZBUFFER    ] );

	m_pContourEffect->setShader( m_pRenderContext, this );

	m_pRenderContext->setPrimitiveTopology( KS_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
	m_pRenderContext->drawIndexed( 4, 0, 0 );
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsDeferredRender::drawDebug()
{
	KsGraphics*	pGraphics = KsGraphics::getInstancePtr();

	pGraphics->drawSprite( ((KsRenderTargetTexture*)m_pGBuffer[ ksMRT_NORMAL     ])->getTexture(),   0,   0, 640, 360 );
	pGraphics->drawSprite( ((KsRenderTargetTexture*)m_pGBuffer[ ksMRT_ALBEDO     ])->getTexture(), 640,   0, 640, 360 );
	pGraphics->drawSprite( ((KsRenderTargetTexture*)m_pGBuffer[ ksMRT_POSITION   ])->getTexture(),   0, 360, 640, 360 );
	//pGraphics->drawSprite( ((KsRenderTargetTexture*)m_pGBuffer[ ksMRT_ZBUFFER    ])->getTexture(), 640, 360, 640, 360 );
	//pGraphics->drawSprite( ((KsRenderTargetTexture*)m_pGBuffer[ ksMRT_ACCUMULATE ])->getTexture(), 640, 360, 640, 360 );
	pGraphics->drawSprite( m_pLighting->getLightingUAV(), 640, 360, 640, 360 );	
	
	pGraphics->flush( m_pRenderContext );
}

/************************************************************************************************/
/*
 * �V�[����`�悷��
 */
/************************************************************************************************/
void KsDeferredRender::render()
{
	// �ʃX���b�h�̕`��X���b�h����
	for( KsUInt32 i=0; i<m_numRenderThread; i++ )
	{
		m_pRenderThread[ i ]->startBeginRender();
	}

#if 1
	// ���C�g�X�V
	updateLight();

	// G-Buffer�𐶐�����
	renderGBuffer();

	// �p�����[�^���X�V����
	updateShaderParameter();

	// ���C�e�B���O
	computeLighting();

	// �����_�[�^�[�Q�b�g�����ɖ߂�
	setRenderTarget_Default( m_pRenderContext );

	// �^�[�Q�b�g���N���A�[����
	//pDeferredRender->clearScene();

	// �ŏI�����_�����O
	finalRender();
	//renderContourExtraction();

	//drawDebug();

	KsGraphics*	pGraphics = KsGraphics::getInstancePtr();

	pGraphics->flush( m_pRenderContext );

	ksDEBUG_FLUSH();

#endif

	// �`��I���҂�
	for( KsUInt32 i=0; i<m_numRenderThread; i++ )
	{
		m_pRenderThread[ i ]->waitEndRender();
	}
	//KsWaitEventForMultiple( m_numRenderThread,  g_hEndPerSceneRenderDeferredEvent );

	// �`��R�}���h���s����
	for( KsUInt32 i=0; i<m_numRenderThread; i++ )
	{
		m_pRenderContext->executeCommandList( m_pRenderThread[ i ]->getCommandList(), ksTRUE );
		//m_pRenderThread[ i ]->getCommandList()->clear();
	}
}

/************************************************************************************************/
/*
 * ���f����ǉ�����
 */
/************************************************************************************************/
void KsDeferredRender::addModel( KsModel* pModel )
{
	m_pModels.push_back( pModel );
}

/************************************************************************************************/
/*
 * �A�N�^�[��ǉ�����
 */
/************************************************************************************************/
void KsDeferredRender::addActor( KsActor* pActor )
{
	m_pActors.push_back( pActor );
}

