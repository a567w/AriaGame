/************************************************************************************************/
/** 
 * @file		KsRenderContext.h
 * @brief		�`��R���e�L�X�g
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSRENDERCONTEXT_H__
#define __KSRENDERCONTEXT_H__

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
 * @class		KsRenderContext
 * @brief		�`��R���e�L�X�g
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsRenderContext
{
	public:
		/**
		 *  �R���X�g���N�^
		 */
									KsRenderContext(){}

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsRenderContext(){}

		/**
		 * �V�[�����N���A����
		 * @param		flags		�`��t���O
		 * @param		color		�N���A�[�J���[
		 * @param		depth		�f�B�v�X�N���A����l
		 * @param		stencil		�X�e���V���N���A����l
		 */
		virtual void				clearScene( KsUInt32 flags, KsColor color, KsReal depth, KsUInt32 stencil ) = 0;

		/**
		 * �V�[�����N���A����
		 * @param	numViews		�N���A�[���郌���_�[ �^�[�Q�b�g�̐�
		 * @param	flags			�`��t���O
		 * @param	color			�N���A�[�J���[
		 * @param	depth			�f�B�v�X�N���A����l
		 * @param	stencil			�X�e���V���N���A����l
		 */
		virtual void				clearScenes( KsUInt32 numViews, KsUInt32 flags, KsColor color, KsReal depth, KsUInt32 stencil ) = 0;

		/**
		 * �[�x�o�b�t�@���N���A����
		 * @param		flags		�N���A�t���O
		 * @param		depth		�f�B�v�X�N���A����l
		 * @param		stencil		�X�e���V���N���A����l
		 */
		virtual void				clearDepthStencil( KsRenderTarget* pTarget, KsUInt32 flags, KsReal depth, KsUInt32 stencil ) = 0;

		/**
		 * �����_�[�^�[�Q�b�g���Z�b�g����
		 * @param	pRenderTargetView		�`��^�[�Q�b�g
		 * @param	pDepthStencilView		�[�x�X�e���V���^�[�Q�b�g
		 */
		virtual void				setRenderTarget( KsRenderTarget* pRenderTargetView, KsRenderTarget* pDepthStencilView ) = 0;

		/**
		 * �����_�[�^�[�Q�b�g���Z�b�g����
		 * @param	pRenderTargetView		�`��^�[�Q�b�g
		 * @param	pDepthStencilView		�[�x�X�e���V���^�[�Q�b�g
		 */
		virtual void				setRenderTargets( KsUInt32 numViews, KsRenderTarget** ppRenderTargetView, KsRenderTarget* pDepthStencilView ) = 0;

		/**
		 * �r���[�|�[�g���Z�b�g����
		 * @param		pViewport	�r���[�|�[�g�ݒ�
		 */
		virtual void				setViewports( const KsViewport* pViewport ) = 0;
		virtual void				setInputLayout( KsInputLayout* pInputLayout ) = 0;

		virtual void				setVertexBuffer( const KsVertexBuffer* pBuffer ) = 0;
		virtual void				setIndexBuffer( const KsIndexBuffer* pBuffer ) = 0;

		virtual void				setVertexBuffers( KsUInt32 startSlot, KsUInt32 numBuffers, const KsVertexBuffer* pBuffer, const KsUInt32* pStride, const KsUInt32* pOffset ) = 0;
		virtual void				setIndexBuffer( const KsIndexBuffer* pBuffer, KsUInt32 indexFormat, KsUInt32 offset ) = 0;
		virtual void				setPrimitiveTopology( KS_PRIMITIVE_TOPOLOGY	type ) = 0;
		virtual void				setVertexShader( KsVertexShader* pShader ) = 0;
		virtual void				setPixelShader( KsPixelShader* pShader ) = 0;
		virtual void				setComputeShader( KsComputeShader* pShader ) = 0;

		virtual void				setVertexConstantBuffers( KsUInt32 startSlot, KsUInt32 numBuffers, const KsConstantBuffer* pConstantBuffers ) = 0;
		virtual void				setPixelConstantBuffers( KsUInt32 startSlot, KsUInt32 numBuffers, const KsConstantBuffer* pConstantBuffers ) = 0;

		virtual void				updateConstantBuffers( KsConstantBuffer* pConstantBuffers, const void* pSrcData ) = 0;

		virtual void				setComputeConstantBuffer( KsUInt32 startSlot, const KsConstantBuffer* pConstantBuffers ) = 0;
		virtual void				setComputeTexture( KsUInt32 startSlot, const KsTexture* pTexture ) = 0;
		virtual void				setComputeTextures( KsUInt32 startSlot, KsUInt32 numTexture, const KsTexture** pTextures ) = 0;
		virtual void				setComputeTextures( KsUInt32 startSlot, KsUInt32 numTexture, KsTexture** pTextures ) = 0;

		virtual void				setVertexTexture( KsUInt32 startSlot, KsUInt32 numViews, const KsTexture* pTexture ) = 0;
		virtual void				setVertexSamplers( KsUInt32 startSlot, KsUInt32 numViews, const KsSamplerState* pSampler ) = 0;
		virtual void				setPixelTexture( KsUInt32 startSlot, KsUInt32 numViews, const KsTexture* pTexture ) = 0;
		virtual void				setPixelSamplers( KsUInt32 startSlot, KsUInt32 numViews, const KsSamplerState* pSampler ) = 0;

		virtual void				setRasterizerState( KsRasterizerState* pRasterizerState ) = 0;
		virtual void				setBlendState( KsBlendState* pBlendState, const KsReal blendFactor[ 4 ], KsUInt32 sampleMask ) = 0;
		virtual void				setDepthStencilState( KsDepthStencilState* pDepthStencilState, KsUInt32 stencilRef ) = 0;

		virtual void				draw( KsUInt32 vertexCount, KsUInt32 startVertexLocation ) = 0;
		virtual void				drawIndexed( KsUInt32 indexCount, KsUInt32 startIndexLocation, KsInt32 baseVertexLocation ) = 0;


		virtual KsRenderTarget*		getRenderTarget() = 0;
		virtual KsRenderTarget*		getDepthStencil() = 0;

		virtual void				dispatch( KsUInt32 threadGroupCountX, KsUInt32 threadGroupCountY, KsUInt32 threadGroupCountZ ) = 0;

		virtual void				setUnorderedAccessViews( KsUInt32 startSlot, KsUInt32 numUAVs, KsUnorderedAccessView** ppUnorderedAccessViews, const KsUInt32* pUAVInitialCounts ) = 0;

		virtual void				read( KsBufferObject* pBuffer, void* pData, KsUInt32 size ) = 0;
		virtual void				write( KsBufferObject* pBuffer, void* pData, KsUInt32 size, KsUInt32 flags ) = 0;
		virtual void*				map( KsBufferObject* pBuffer, KsUInt32 flags ) = 0;
		virtual void				unmap( KsBufferObject* pBuffer ) = 0;


		virtual void				clearState() = 0;
		virtual KsBool				finishCommandList( KsBool restoreDeferredContextState, KsCommandList* pCommandList ) = 0;
		virtual void				executeCommandList( KsCommandList* pCommandList, KsBool restoreDeferredContextState ) = 0;
};

#endif		/* __KSRENDERCONTEXT_H__ */



