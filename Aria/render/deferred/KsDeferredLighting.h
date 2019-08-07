/************************************************************************************************/
/** 
 * @file		KsDeferredLighting.h
 * @brief		�f�B�t�@�[�h���C�e�B���O
 * @author		Tsukasa Kato
 * @date		2006/07/02
 * @since		2006/07/02
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSDEFERREDLIGHTING_H__
#define __KSDEFERREDLIGHTING_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/
#define MAX_LIGHTS_POWER				10
#define MAX_LIGHTS						( 1 << MAX_LIGHTS_POWER )
#define COMPUTE_SHADER_TILE_GROUP_DIM	16
#define COMPUTE_SHADER_TILE_GROUP_SIZE	(COMPUTE_SHADER_TILE_GROUP_DIM*COMPUTE_SHADER_TILE_GROUP_DIM)

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @struct		KsPointLight
 * @brief		Must match shader equivalent structure
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		0.10
 * @note		�Ȃ�
 */
/************************************************************************************************/
struct KsPointLight
{
	KsVector3d	positionView;
	KsReal		attenuationBegin;
	KsVector3d	color;
	KsReal		attenuationEnd;
};

/************************************************************************************************/
/**
 * @struct		KsFramebufferElement
 * @brief		Flat framebuffer RGBA16-encoded
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		0.10
 * @note		�Ȃ�
 */
/************************************************************************************************/
struct KsFrameBufferElement
{
	KsUInt32	rb;
	KsUInt32	ga;
};

/************************************************************************************************/
/**
 * @struct		KsPointLightTransform
 * @brief		Host-side world-space initial transform data
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		0.10
 * @note		�Ȃ�
 */
/************************************************************************************************/
struct KsPointLightTransform
{
	// Cylindrical coordinates
	KsReal		radius;
	KsReal		angle;
	KsReal		height;
	KsReal		animationSpeed;
};

/************************************************************************************************/
/**
 * @class		KsDeferredLighting
 * @brief		KsDeferredLighting�N���X
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		0.10
 * @note		�Ȃ�
 */
/************************************************************************************************/
class KsDeferredLighting
{
	public:
		/**
		 * �R���X�g���N�^
		 * @param	pRenderSystem	�`��V�X�e��
		 * @param	width			�����_�[�^�[�Q�b�g�̕�
		 * @param	height			�����_�[�^�[�Q�b�g�̍���
		 */
		KsDeferredLighting( KsRenderSystem* pRenderSystem, KsUInt32 width, KsUInt32 height, KsUInt32 MSAA );

		/**
		 * �f�X�g���N�^
		 */
		virtual					~KsDeferredLighting();

		/**
		 * ���C�e�B���O������������
		 */
		void					initializeLight();

		/**
		 * �V�F�[�_�[�p�����[�^���X�V����
		 */
		KsConstantBuffer*		getLightingBuffer() { return m_pLightingCB; }

		/**
		 * �V�F�[�_�[�p�����[�^���X�V����
		 */
		KsUnorderedAccessView*	getLightingUAV() { return m_pLightBufferUAV; }
		
		/**
		 * ���C�g���X�V����( ���C�g�����e�N�X�`���ɏ������� )
		 * @param	elapsedTime	�o�ߎ���
		 */
		void					updateLight( KsReal elapsedTime, KsCamera* pCamera, KsModelParameter* pModelParameter );

		/**
		 * ���C�e�B���O�v�Z
		 */
		void					computeLighting( KsUInt32 numTexture, KsTexture** pTextures );

	protected:
		KsRenderSystem*			m_pRenderSystem;						/**< �`��V�X�e��					*/
		KsRenderContext*		m_pRenderContext;						/**< �`��R���e�L�X�g					*/
		KsPointLight			m_vPointLight[ MAX_LIGHTS ];			/**< �|�C���g���C�g					*/
		KsPointLightTransform	m_vPointLightTrans[ MAX_LIGHTS ];		/**< �|�C���g���C�g					*/
		KsVector3d				m_vPointLightPos[ MAX_LIGHTS ];			/**< �|�C���g���C�g					*/
		KsComputeShader*		m_pLightingCS;							/**< ���C�g�p�R���s���[�g�V�F�[�_�[	*/
		KsConstantBuffer*		m_pLightingCB;							/**< ���C�g�p�o�b�t�@					*/
		KsUnorderedAccessView*	m_pLightBufferUAV;						/**< ���C�g�pUAV						*/
		KsStructuredBuffer*		m_pLightParameter;						/**< ���C�g�p�����[�^					*/
		KsUInt32				m_dispatchWidth;						/**< Compute Shader Dispatch Widht	*/
		KsUInt32				m_dispatchHeight;						/**< Compute Shader Dispatch Height	*/
		KsReal					m_totalTime;							/**< */
};

#endif /* __KSDEFERREDLIGHTING_H__ */

