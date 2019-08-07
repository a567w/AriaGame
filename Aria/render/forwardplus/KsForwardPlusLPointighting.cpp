/************************************************************************************************/
/** 
 * @file		KsForwardPlusLPointighting.cpp
 * @brief		Foward+�����_�����O
 * @author		Tsukasa Kato
 * @date		2006/07/02
 * @since		2006/07/02
 * @version		0.1
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << ���[�j���O�}�� >>                                         */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                 << ���C�u���������N >>                                       */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "Aria/KsGamePreCompile.h"
#include "Aria/render/forwardplus/KsForwardPlusLPointighting.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

#if 0
/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KsVector3d KsHueToRGB( KsReal hue )
{
	KsReal	intPart;
	KsReal	fracPart = modf(hue * 6.0f, &intPart);
	KsInt32	region   = static_cast<KsInt32>(intPart);

	switch( region )
	{
		case 0: return KsVector3d(1.0f, fracPart, 0.0f);
		case 1: return KsVector3d(1.0f - fracPart, 1.0f, 0.0f);
		case 2: return KsVector3d(0.0f, 1.0f, fracPart);
		case 3: return KsVector3d(0.0f, 1.0f - fracPart, 1.0f);
		case 4: return KsVector3d(fracPart, 0.0f, 1.0f);
		case 5: return KsVector3d(1.0f, 0.0f, 1.0f - fracPart);
		default: break;
	}

	return	KsVector3d::ZERO;
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsForwardPlusLPointighting::KsForwardPlusLPointighting( KsRenderSystem* pRenderSystem, KsUInt32 width, KsUInt32 height, KsUInt32 MSAA )
	: m_pRenderSystem( pRenderSystem )
	, m_pRenderContext( 0 )
	, m_pLightingCS( 0 )
	, m_pLightingCB( 0 )
	, m_pLightBufferUAV( 0 )
	, m_pLightParameter( 0 )
	, m_dispatchWidth( 0 )
	, m_dispatchHeight( 0 )
	, m_totalTime( 0.0f )
{
	// �����_�[�^�[�Q�b�g���擾���Ă���(�C�~�f�B�G�C�g �R���e�L�X�g)
	m_pRenderContext = pRenderSystem->getRenderContex();

	//----------------------------------------------------------------------
	// ���C�g�ݒ������
	//----------------------------------------------------------------------

	// ���C�e�B���O�p�Z�b�g�A�b�v
	KsShaderManager*			pShaderManager         = KsShaderManagerDX11::getInstancePtr();
	KsHardwareBufferManager*	pHardwareBufferManager = KsHardwareBufferManagerDX11::getInstancePtr();
	KsInputLayoutManager*		pInputLayoutManager    = KsInputLayoutManagerDX11::getInstancePtr();

	// ���C�e�B���O�p�V�F�[�_�[(�R���s���[�g�V�F�[�_�[)
	m_pLightingCS = (KsComputeShader*)pShaderManager->createFromFile( "ComputeLighting.fx", "CS_LightingTile", ksSHADE_MODEL_5_0, ksCOMPUTE_SHADER );

	// ���C�e�B���O�p�R���X�^���g�o�b�t�@
	m_pLightingCB = pHardwareBufferManager->createConstantBuffer( sizeof(KsModelParameter), 0 );

	// UAV �A�N�Z�X�p
	m_pLightParameter = pRenderSystem->createStructuredBuffer( sizeof(KsPointLight), MAX_LIGHTS, 1, D3D11_BIND_SHADER_RESOURCE );
	m_pLightBufferUAV = pRenderSystem->createUnorderedAccessView( sizeof(KsFrameBufferElement), width * height * MSAA, 0, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS );

	m_dispatchWidth  = (width  + COMPUTE_SHADER_TILE_GROUP_DIM - 1) / COMPUTE_SHADER_TILE_GROUP_DIM;
	m_dispatchHeight = (height + COMPUTE_SHADER_TILE_GROUP_DIM - 1) / COMPUTE_SHADER_TILE_GROUP_DIM;


	// ���C�g������������
	initializeLight();
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsForwardPlusLPointighting::~KsForwardPlusLPointighting()
{
	ksDELETE( m_pLightingCS );
	ksDELETE( m_pLightingCB );
	ksDELETE( m_pLightBufferUAV );
	ksDELETE( m_pLightParameter );
}


/************************************************************************************************/
/*
 * ���C�e�B���O������������
 */
/************************************************************************************************/
void KsForwardPlusLPointighting::initializeLight()
{
	std::tr1::mt19937 rng(1337);

	std::tr1::uniform_real<KsReal> radiusNormDist(0.0f, 1.0f);
	const KsReal maxRadius = 200.0f;
	std::tr1::uniform_real<KsReal> angleDist(0.0f, 2.0f * ksPI); 
	std::tr1::uniform_real<KsReal> heightDist(0.0f, 30.0f);
	std::tr1::uniform_real<KsReal> animationSpeedDist(2.0f, 20.0f);
	std::tr1::uniform_int<KsInt32> animationDirection(0, 1);
	std::tr1::uniform_real<KsReal> hueDist(0.0f, 1.0f);
	std::tr1::uniform_real<KsReal> intensityDist(0.1f, 0.5f);
	std::tr1::uniform_real<KsReal> attenuationDist(2.0f, 20.0f);

	const KsReal attenuationStartFactor = 0.8f;

	for( KsUInt32 i=0; i<MAX_LIGHTS; i++ )
	{
		KsPointLight&			params = m_vPointLight[i];
		KsPointLightTransform&	init   = m_vPointLightTrans[i];

		init.radius = std::sqrt(radiusNormDist(rng)) * maxRadius;
		init.angle  = angleDist(rng);
		init.height = heightDist(rng);
		// Normalize by arc length
		init.animationSpeed = (animationDirection(rng) * 2 - 1) * animationSpeedDist(rng) / init.radius;
		// HSL->RGB, vary light hue
		params.color            = KsHueToRGB(hueDist(rng)) * intensityDist(rng);
		params.color.set( 1.0f, 1.0f, 1.0f );
		params.attenuationEnd   = attenuationDist(rng);
		params.attenuationBegin = attenuationStartFactor * params.attenuationEnd;
	}
}


/************************************************************************************************/
/*
 * ���C�g���X�V����( ���C�g�����e�N�X�`���ɏ������� )
 * @param	elapsedTime	�o�ߎ���
 */
/************************************************************************************************/
void KsForwardPlusLPointighting::updateLight( KsReal elapsedTime, KsCamera* pCamera, KsModelParameter* pModelParameter )
{
	m_totalTime += elapsedTime;

	m_pRenderContext->updateConstantBuffers( m_pLightingCB, pModelParameter );

	// Update positions of active lights
	for( KsUInt32 i=0; i<MAX_LIGHTS; i++ )
	{
		const KsPointLightTransform& initTransform = m_vPointLightTrans[i];
		KsReal angle = initTransform.angle + m_totalTime * initTransform.animationSpeed;
		
		m_vPointLightPos[i] = KsVector3d( initTransform.radius * std::cos(angle), initTransform.height, initTransform.radius * std::sin(angle) );
	}

	// Transform light world positions into view space and store in our parameters array
	KsVector3d::TransformArray(&m_vPointLight[0].positionView, sizeof(KsPointLight), &m_vPointLightPos[0], sizeof(KsVector3d), &pCamera->getViewMatrix(), MAX_LIGHTS );

	// ���C�g����Struct�o�b�t�@�ɏ�������
	m_pRenderContext->write( m_pLightParameter, &m_vPointLight[ 0 ], sizeof(m_vPointLight), 0 );

	// ���C�g
	KsPointLight* pLight = (KsPointLight*)m_pRenderContext->map( m_pLightParameter, KS_MAP_WRITE_DISCARD );

	for( KsUInt32 i=0; i<MAX_LIGHTS; i++ )
	{
		pLight[ i ] = m_vPointLight[ i ];
	}

	m_pRenderContext->unmap( m_pLightParameter );
}


/************************************************************************************************/
/*
 * ���C�e�B���O����
 */
/************************************************************************************************/
void KsForwardPlusLPointighting::computeLighting( KsUInt32 numTexture, KsTexture** pTextures )
{
	// World, ViewProj, �Ȃǂ̃R���X�^���g�o�b�t�@���Z�b�g����
	// GBuffer���Z�b�g(�v�Z�Ŏg��)
	// ���C�g�̈ʒu�Ȃǂ̃e�N�X�`�����Z�b�g����
	// ���C�e�B���O����,��������UAV�e�N�X�`�����Z�b�g����(UAV)

	m_pRenderContext->setComputeConstantBuffer( 0, m_pLightingCB );						// World, ViewProj, �Ȃǂ̃R���X�^���g�o�b�t�@���Z�b�g����
	m_pRenderContext->setComputeTextures( 0, numTexture, &pTextures[ 0 ] );				// GBuffer���Z�b�g(�v�Z�Ŏg��)
	m_pRenderContext->setComputeTexture ( 5, m_pLightParameter );						// ���C�g�̈ʒu�Ȃǂ̃e�N�X�`�����Z�b�g����
	m_pRenderContext->setUnorderedAccessViews( 0, 1, &m_pLightBufferUAV, 0 );			// ���C�e�B���O����,��������UAV�e�N�X�`�����Z�b�g����(UAV)
	m_pRenderContext->setComputeShader( m_pLightingCS );								// �V�F�_�[�Z�b�g
		
	// Compute shader�����s����
	m_pRenderContext->dispatch( m_dispatchWidth, m_dispatchHeight, 1 );

	// Cleanup
	m_pRenderContext->setComputeShader( 0 );
	m_pRenderContext->setVertexShader( 0 );
	m_pRenderContext->setPixelShader( 0 );
	m_pRenderContext->setRenderTargets( 0, 0, 0 );

	//m_pRenderContext->setVertexTexture( 0, 8, 0 );
	//m_pRenderContext->setPixelTexture( 0, 8, 0 );
	//const KsTexture** pNullTextures = NULL;
	//m_pRenderContext->setComputeTextures( 0, 8, pNullTextures );
	m_pRenderContext->setComputeTextures( 0, 8, (const KsTexture** )NULL );

	m_pRenderContext->setUnorderedAccessViews( 0, 1, 0, 0 );
}

#endif

