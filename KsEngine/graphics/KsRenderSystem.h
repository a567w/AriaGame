/************************************************************************************************/
/** 
 * @file		KsRenderSystem.h
 * @brief		�`��V�X�e��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSRENDERSYSTEM_H__
#define __KSRENDERSYSTEM_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsColor.h"
#include "KsLight.h"
#include "KsMaterial.h"
#include "KsViewport.h"
#include "KsRenderState.h"
#include "KsTexture.h"
#include "ksImage.h"
#include "KsVertexBuffer.h"
#include "KsVertexDeclaration.h"
#include "KsIndexBuffer.h"
#include "KsTextureManager.h"
#include "KsRenderTarget.h"
#include "KsRenderTargetTexture.h"
#include "KsHardwareBufferManager.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsRenderSystem
 * @brief		�x�[�X�`��V�X�e��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		Windows�Ń}���`�E�C���h�E�̏ꍇ�͕��������߂ɁA�V���O���g���ɂ�,���Ȃ�
 */
/************************************************************************************************/
class ksENGINE_API KsRenderSystem : public KsSingleton< KsRenderSystem >
{
	public:
		/**
		 * �V���O���g���̎Q�Ƃ��擾
		 * @return							�V���O���g���̎Q��
		 */
		static KsRenderSystem&				getInstance();
		
		/**
		 * �V���O���g���̃|�C���^���擾
		 * @return							�V���O���g���̃|�C���^
		 */
		static KsRenderSystem*				getInstancePtr();

	public:
		/**
		 * �R���X�g���N�^
		 */
											KsRenderSystem();

		/**
		 * �f�X�g���N�^
		 */
		virtual								~KsRenderSystem();

		/**
		 * ����������
		 * @param		hWnd				�E�C���h�E�̃n���h��
		 * @retval		ksTRUE				����������
		 * @retval		ksFALSE				���������s
		 */
		virtual KsBool						initialize( void* pParam ) = 0;

		/**
		 * �㏈��
		 * @retval		ksTRUE				�㏈������
		 * @retval		ksFALSE				�㏈�����s
		 */
		virtual KsBool						terminate() = 0;
		

		/**
		 * �V�[�����N���A����
		 * @param		flags				�`��t���O
		 * @param		color				�N���A�[�J���[
		 * @param		depth				�f�B�v�X�N���A����l
		 * @param		stencil				�X�e���V���N���A����l
		 */
		virtual void						clearScene( KsUInt32 flags, KsColor color, KsReal depth, KsUInt32 stencil ) = 0;

		/**
		 * �V�[���`��J�n
		 * @param		flags				�`��t���O
		 * @param		color				�N���A�[�J���[
		 * @param		depth				�f�B�v�X�N���A����l
		 * @param		stencil				�X�e���V���N���A����l
		 */
		virtual void						beginScene( KsUInt32 flags, KsColor color, KsReal depth, KsUInt32 stencil ) = 0;

		/**
		 * �V�[���`��I��
		 */
		virtual void						endScene() = 0;

		/**
		 * �`��o�b�t�@�ƕ\���o�b�t�@�����ւ�
		 */
		virtual void						present() = 0;

		/**
		 * �r���[�|�[�g���Z�b�g����
		 * @param		pViewport			�r���[�|�[�g�ݒ�
		 */
		virtual void						setViewport( const KsViewport* pViewport ) = 0;

		/**
		 * �t�H�O���Z�b�g����
		 */
		virtual void						setFog( ksFOG_MODE mode, KsColor color, KsReal start, KsReal end, KsReal density ) = 0;

		/*-------------------------------------<< �v���~�e�B�u�`��@�\�֌W >>--------------------------------------------------*/
		/**
		 * ���C����`��(2D)
		 * @param		x					X���W
		 * @param		y					Y���W
		 * @param		color				�F
		 */
		//virtual void						drawLine( KsInt16 x0, KsInt16 y0, KsInt16 x1, KsInt16 y1, KsUInt32 color ) = 0;

		/**
		 * �Z�`��`��
		 * @param		x					X���W
		 * @param		y					Y���W
		 * @param		w					��
		 * @param		h					����
		 * @param		color				�F
		 */
		virtual void						drawRect( KsReal x, KsReal y, KsReal w, KsReal h, KsColor color ) = 0;

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
		virtual void						drawRectEx( KsReal x, KsReal y, KsReal w, KsReal h, KsReal tx, KsReal ty, KsReal tw, KsReal th, KsColor color, KsTexture* pTexture ) = 0;

		/**
		 * �Z�`��`��
		 * @param		x					X���W
		 * @param		y					Y���W
		 * @param		w					��
		 * @param		h					����
		 * @param		u0					�e�N�X�`����X���W
		 * @param		v0					�e�N�X�`����Y���W
		 * @param		u1					�e�N�X�`���̕�
		 * @param		v1					�e�N�X�`���̍���
		 * @param		color				�F
		 * @param		pTexture			�e�N�X�`��
		 */
		//virtual void						drawRectEx( KsInt16 x, KsInt16 y, KsInt16 w, KsInt16 h, KsUInt16 tx, KsUInt16 ty, KsUInt16 tw, KsUInt16 th, KsUInt32 color, KsTexture* pTexture ) = 0;

		/**
		 * �X�v���C�g�`��
		 * @param		pSpritePrim			�X�v���C�g�̃v���~�e�B�u(4�̒��_�z����킽���Ȃ��ƃo�O��)
		 */
		//virtual void						drawSprite( KS_SPRITE_PRIM* pSpritePrim ) = 0;

		/**
		 *
		 */
		virtual void						drawIndexedPrimitive( ksPRIMITIVE_TYPE type, KsUInt32 vertexStart, KsUInt32 indexStart, KsUInt32 primitiveCount, KsVertexBuffer* pVertexBuffer, KsIndexBuffer* pIndexBuffer ) = 0;

		virtual void						drawPrimitive( ksPRIMITIVE_TYPE type, KsUInt32 vertexStart, KsUInt32 primitiveCount, KsVertexBuffer* pVertexBuffer ) = 0;

		virtual void						drawPrimitiveUP( ksPRIMITIVE_TYPE type, KsUInt32 primitiveCount, const void* pVertexStreamZeroData, KsUInt32 vertexStreamZeroStride ) = 0;

		virtual void						copyRect( KsRenderTarget* pSrcTarget, const KsRect* pSrcRect, KsRenderTarget* pDstTarget, const KsRect* pDstRect ) = 0;

		/*------------------------------------------<< �e�N�X�`���֌W >>------------------------------------------------------*/
		/**
		 * �e�N�X�`���𐶐�����
		 * @param		pFileName			�t�@�C����
		 * @param		flags				�����t���O
		 * @return							�e�N�X�`���̃|�C���^
		 */
		virtual KsTexture*					createTextureFromFile( const KsChar* pFileName, KsUInt32 flags ) = 0;

		/**
		 * �C���[�W�f�[�^����e�N�X�`���𐶐�����
		 * @param		pImage				�C���[�W�f�[�^�̃|�C���^
		 * @param		flags				�����t���O
		 * @return							�e�N�X�`���̃|�C���^
		 */
		//virtual KsTexture*					createTexture( KsImage* pImage, KsUInt32 flags ) = 0;

		/**
		 * �e�N�X�`���𐶐�����
		 * @param		pData				�C���[�W�f�[�^�̃|�C���^
		 * @param		width				�e�N�X�`���̕�
		 * @param		height				�e�N�X�`���̍���
		 * @param		format				�e�N�X�`���t�H�[�}�b�g
		 * @param		flags				�����t���O
		 * @return							�e�N�X�`���̃|�C���^
		 */
		virtual KsTexture*					createTexture( const KS_SUBRESOURCE_DATA* pData, KsUInt32 width, KsUInt32 height, KsUInt32 format, KsUInt32 flags, KsUInt32 usage ) = 0;

		/**
		 * �e�N�X�`�����Z�b�g����
		 * @param		statge				�e�N�X�`���X�e�[�W
		 * @param		pTexture			�e�N�X�`��
		 */
		virtual void						setTexture( KsUInt32 stage, KsTexture* pTexture ) = 0;

		/* �����_�[�^�[�Q�b�g */
		virtual KsRenderTarget*				getRenderTarget() = 0;
		virtual void						setRenderTarget( KsRenderTarget* pRenderTarget ) = 0;
		virtual KsRenderTarget*				createRenderTarget( KsUInt32 width, KsUInt32 height, ksPIXEL_FORMAT format, KsUInt32 flags ) = 0;
		virtual KsRenderTarget*				createOffscreenTarget( KsUInt32 width, KsUInt32 height, ksPIXEL_FORMAT format, KsUInt32 flags ) = 0;
		virtual KsRenderTargetTexture*		createRenderTargetTexture( KsUInt32 width, KsUInt32 height, ksPIXEL_FORMAT format, KsUInt32 flags ) = 0;
		virtual KsRenderTarget*				createRenderTargetFromFile( KsUInt32 width, KsUInt32 height, ksPIXEL_FORMAT format, const KsChar* pFileName, KsColor color ) = 0;
		virtual KsVertexDeclaration*		createVertexDeclaration( KS_VERTEX_ELEMENT* pVertexElements ) = 0;
		virtual KsRenderTarget*				createRenderTextureView( KsUInt32 width, KsUInt32 height, KsUInt32 format ) = 0;
		virtual KsRenderTarget*				createDepthStencilView( KsUInt32 width, KsUInt32 height, KsUInt32 format, KsUInt32 viewFormat, KsUInt32 resFormat ) = 0;
		virtual KsUnorderedAccessView*		createUnorderedAccessView( KsUInt32 elementSize, KsUInt32 numElements, KsUInt32 format, KsUInt32 flags ) = 0;
		virtual KsStructuredBuffer*			createStructuredBuffer( KsUInt32 elementSize, KsUInt32 numElements, KsUInt32 format, KsUInt32 flags ) = 0;
		virtual void						setVertexDeclaration( KsVertexDeclaration* pVertexDeclaration ) = 0;

		virtual KsSamplerState*				createSamplerState( const KS_SAMPLER_DESC* pSamplerStateDesc ) = 0;
		virtual KsBlendState*				createBlendState( const KS_BLEND_DESC* pBlendStateDesc ) = 0;
		virtual KsRasterizerState*			createRasterizerState( const KS_RASTERIZER_DESC* pRasterizerState ) = 0;
		virtual KsDepthStencilState*		createDepthStencilState( const KS_DEPTH_STENCIL_DESC* pDepthStencilDesc ) = 0;
		virtual KsRenderContext*			createDeferredContext() = 0;
		virtual KsCommandList*				createCommandList() = 0;
		

		/*-----------------------------------<< �}�e���A���֌W >>--------------------------------------------------*/
		/**
		 * �}�e���A�����Z�b�g����
		 * @param		pMaterial			�}�e���A��
		 */
		virtual void						setMaterial( KsMaterial* pMaterial ) = 0;

		/*-------------------------------------<< ���C�g�֌W >>--------------------------------------------------*/
		/**
		 * ���C�g��ǉ�����
		 * @param		index				���C�g�̃C���f�b�N�X
		 * @param		pLight				���C�g���
		 * @note							���C�g��ݒu�ł��鐔�́A�ő�W�ł��B<br>
		 *									���C�g����菜�����Ƃ��͎�菜���������C�g�̃C���f�b�N�X�ƃ��C�g��NULL���Z�b�g���Ă��������B
		 */
		virtual void						setLight( KsUInt32 index, const KsLight* pLight ) = 0;

		/**
		 * �w�胉�C�g��L���A�����ɂ���B
		 * @param		index				���C�g�̃C���f�b�N�X
		 * @param		flag				���C�g��ON OFF�̃t���O( ksTRUE: ON, ksFALSE: OFF )
		 */
		virtual void						setLightEnable( KsUInt32 index, KsBool flag ) = 0;

		/**
		 * �w��C���f�b�N�X�̃��C�g���擾����
		 * @param		index				�C���f�b�N�X
		 * @return							���C�g�̃|�C���^(�Z�b�g����Ă��Ȃ��Ƃ���NULL���Ԃ�)
		 */
		virtual KsLight*					getLight( KsUInt32 index );

		/*-------------------------------------<< �����_�[�X�e�[�g�֌W >>--------------------------------------------------*/
		/**
		 * �����_�[�X�e�[�g���X�^�b�N�Ƀv�b�V������
		 */
		void								pushRenderState();

		/**
		 * �����_�[�X�e�[�g���X�^�b�N�Ƀ|�b�v����
		 */
		void								popRenderState();

		/**
		 * �����_�[�X�e�[�g���Z�b�g����
		 * @param		state				�X�e�[�g�̎��
		 * @param		value				�X�e�[�g�ɑΉ�����l
		 */
		virtual void						setRenderState( ksRENDER_STATE_TYPE state, KsUInt32 value ) = 0;

		/**
		 * �T���v���[�X�e�[�g���Z�b�g����
		 * @param		sampler				�T���v���[�ԍ�
		 * @param		state				�X�e�[�g�̎��
		 * @param		value				�X�e�[�g�ɑΉ�����l
		 */
		virtual void						setSamplerState( KsUInt32 sampler, ksSAMPLER_STATE_TYPE state, KsUInt32 value ) = 0;

		/**
		 * �g�����X�t�H�[������
		 * @param		state				�g�����X�t�H�[���̃��[�h
		 * @param		pMatrix				�ϊ��}�g���b�N�X
		 */
		virtual void						setTransform( ksTRANSFORM_STATE state, const KsMatrix4x4* pMatrix ) = 0;

		/**
		 * ��{�ݒ��3D���[�h������������
		 */
		virtual void						auto2DMode() = 0;

		/**
		 * ��{�ݒ��3D���[�h������������
		 */
		virtual void						auto3DMode() = 0;

		/**
		 * �`��R���e�L�X�g���擾����
		 */
		KsRenderContext*					getRenderContex() { return m_pRenderContext; }

	protected:
		KsMatrix4x4							m_viewMatrix;					/**< �r���[�}�g���b�N�X					*/
		KsMatrix4x4							m_worldMatrix;					/**< ���[���h�}�g���b�N�X					*/
		KsMatrix4x4							m_textureMatrix;				/**< �e�N�X�`���}�g���b�N�X				*/
		KsTextureState						m_textureState;					/**< ���݂̃e�N�X�`���X�e�[�g				*/
		KsRenderState						m_renderState;					/**< ���݂̃����_�[�X�e�[�g				*/
		KsRenderStateStack					m_renderStateStack;				/**< �����_�[�X�e�[�g�X�^�b�N				*/
		KsLight								m_pLights[ ksLIGHT_MAX ];		/**< ���C�g									*/
		KsUInt32							m_clearFlags;					/**< �N���A�t���O							*/
		KsColor								m_clearColor;					/**< �o�b�t�@�̃N���A�J���[�Z�b�g		*/
		KsInt32								m_clearDepth;					/**< Z�o�b�t�@�̃N���A�l�Z�b�g			*/
		KsInt32								m_clearStencil;					/**< �X�e���V���o�b�t�@�̃N���A�l�Z�b�g	*/
		KsRenderContext*					m_pRenderContext;				/**< �`��R���e�L�X�g						*/
		KsTextureManager*					m_pTextureManager;				/**< �e�N�X�`���}�l�[�W��					*/
		KsHardwareBufferManager*			m_pHardwareBufferManager;		/**< �n�[�h�E�F�A�o�b�t�@�}�l�[�W��		*/
		KsShaderManager*					m_pShaderManager;				/**< �V�F�[�_�[�}�l�[�W��					*/
};

#endif		/* __KSRENDERSYSTEM_H__ */

