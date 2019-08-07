/************************************************************************************************/
/** 
 * @file		KsForwardPlusLPointighting.h
 * @brief		Foward+���C�e�B���O
 * @author		Tsukasa Kato
 * @date		2006/07/02
 * @since		2006/07/02
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSDFORWARDPLUSLIGHTING_H__
#define __KSDFORWARDPLUSLIGHTING_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


#if 0

#define MAX_LIGHTS_POWER				10
#define MAX_LIGHTS						( 1 << MAX_LIGHTS_POWER )
#define COMPUTE_SHADER_TILE_GROUP_DIM	16
#define COMPUTE_SHADER_TILE_GROUP_SIZE	(COMPUTE_SHADER_TILE_GROUP_DIM*COMPUTE_SHADER_TILE_GROUP_DIM)

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
 * @class		KsForwardPlusLPointighting
 * @brief		KsForwardPlusLPointighting�N���X
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		0.10
 * @note		�Ȃ�
 */
/************************************************************************************************/
class KsForwardPlusLPointighting
{
	public:
		/**
		 * �R���X�g���N�^
		 * @param	pRenderSystem	�`��V�X�e��
		 * @param	width			�����_�[�^�[�Q�b�g�̕�
		 * @param	height			�����_�[�^�[�Q�b�g�̍���
		 */
		KsForwardPlusLPointighting( KsRenderSystem* pRenderSystem, KsUInt32 width, KsUInt32 height, KsUInt32 MSAA );

		/**
		 * �f�X�g���N�^
		 */
		virtual					~KsForwardPlusLPointighting();

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


        // point lights
        ID3D11Buffer*               m_pPointLightBufferCenterAndRadius;
        ID3D11ShaderResourceView*   m_pPointLightBufferCenterAndRadiusSRV;
        ID3D11Buffer*               m_pPointLightBufferColor;
        ID3D11ShaderResourceView*   m_pPointLightBufferColorSRV;

        // spot lights
        ID3D11Buffer*               m_pSpotLightBufferCenterAndRadius;
        ID3D11ShaderResourceView*   m_pSpotLightBufferCenterAndRadiusSRV;
        ID3D11Buffer*               m_pSpotLightBufferColor;
        ID3D11ShaderResourceView*   m_pSpotLightBufferColorSRV;
        ID3D11Buffer*               m_pSpotLightBufferSpotParams;
        ID3D11ShaderResourceView*   m_pSpotLightBufferSpotParamsSRV;

        // buffers for light culling
        ID3D11Buffer*               m_pLightIndexBuffer;
        ID3D11ShaderResourceView*   m_pLightIndexBufferSRV;
        ID3D11UnorderedAccessView*  m_pLightIndexBufferUAV;

};

#endif


#endif /* __KSDFORWARDPLUSLIGHTING_H__ */

