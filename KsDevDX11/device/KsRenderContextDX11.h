/************************************************************************************************/
/** 
 * @file		KsRenderContextDX11.h
 * @brief		描画コンテキスト(DX11用)
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSRENDERCONTEXTDX11_H__
#define __KSRENDERCONTEXTDX11_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsRenderContextDX11
 * @brief		描画コンテキスト(DX11用)
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksDEVDX11_API KsRenderContextDX11 : public KsRenderContext
{
		friend class KsRenderSystemDX11;

	public:
		static const KsUInt32		KS_RENDER_TARGET_COUNT = 16;

	public:
		/**
		 * コンストラクタ
		 */
									KsRenderContextDX11();

		/**
		 * デストラクタ
		 */
		virtual						~KsRenderContextDX11();

		/**
		 * シーンをクリアする
		 * @param		flags		描画フラグ
		 * @param		color		クリアーカラー
		 * @param		depth		ディプスクリアする値
		 * @param		stencil		ステンシルクリアする値
		 */
		virtual void				clearScene( KsUInt32 flags, KsColor color, KsReal depth, KsUInt32 stencil );

		/**
		 * シーンをクリアする
		 * @param	numViews		クリアーするレンダー ターゲットの数
		 * @param	flags			描画フラグ
		 * @param	color			クリアーカラー
		 * @param	depth			ディプスクリアする値
		 * @param	stencil			ステンシルクリアする値
		 */
		virtual void				clearScenes( KsUInt32 numViews, KsUInt32 flags, KsColor color, KsReal depth, KsUInt32 stencil );

		/**
		 * 深度バッファをクリアする
		 * @param		flags		クリアフラグ
		 * @param		depth		ディプスクリアする値
		 * @param		stencil		ステンシルクリアする値
		 */
		virtual void				clearDepthStencil( KsRenderTarget* pTarget, KsUInt32 flags, KsReal depth, KsUInt32 stencil );

		/**
		 * レンダーターゲットをセットする
		 * @param	pRenderTargetView		描画ターゲット
		 * @param	pDepthStencilView		深度ステンシルターゲット
		 */
		virtual void				setRenderTarget( KsRenderTarget* pRenderTargetView, KsRenderTarget* pDepthStencilView );

		/**
		 * レンダーターゲットをセットする
		 * @param	numViews				バインドするレンダー ターゲットの数
		 * @param	pRenderTargetView		レンダー ターゲットの配列
		 * @param	pDepthStencilView		深度ステンシルターゲット
		 */
		virtual void				setRenderTargets( KsUInt32 numViews, KsRenderTarget** ppRenderTargetView, KsRenderTarget* pDepthStencilView );

		/**
		 * ビューポートをセットする
		 * @param		pViewport	ビューポート設定
		 */
		virtual void				setViewports( const KsViewport* pViewport );
		
		virtual void				setInputLayout( KsInputLayout* pInputLayout );

		virtual void				setVertexBuffer( const KsVertexBuffer* pBuffer );
		virtual void				setIndexBuffer( const KsIndexBuffer* pBuffer );

		virtual void				setVertexBuffers( KsUInt32 startSlot, KsUInt32 numBuffers, const KsVertexBuffer* pBuffer, const KsUInt32* pStride, const KsUInt32* pOffset );
		virtual void				setIndexBuffer( const KsIndexBuffer* pBuffer, KsUInt32 indexFormat, KsUInt32 offset );
		virtual void				setPrimitiveTopology( KS_PRIMITIVE_TOPOLOGY	type );
		virtual void				setVertexShader( KsVertexShader* pShader );
		virtual void				setPixelShader( KsPixelShader* pShader );
		virtual void				setComputeShader( KsComputeShader* pShader );
		virtual void				setVertexConstantBuffers( KsUInt32 startSlot, KsUInt32 numBuffers, const KsConstantBuffer* pConstantBuffers );
		virtual void				setPixelConstantBuffers( KsUInt32 startSlot, KsUInt32 numBuffers, const KsConstantBuffer* pConstantBuffers );
		virtual void				updateConstantBuffers( KsConstantBuffer* pConstantBuffers, const void* pSrcData );

		virtual void				setComputeConstantBuffer( KsUInt32 startSlot, const KsConstantBuffer* pConstantBuffers );
		virtual void				setComputeTexture( KsUInt32 startSlot, const KsTexture* pTexture );
		virtual void				setComputeTextures( KsUInt32 startSlot, KsUInt32 numTexture, const KsTexture** pTextures );
		virtual void				setComputeTextures( KsUInt32 startSlot, KsUInt32 numTexture, KsTexture** pTextures );

		virtual void				setVertexTexture( KsUInt32 startSlot, KsUInt32 numViews, const KsTexture* pTexture );
		virtual void				setVertexSamplers( KsUInt32 startSlot, KsUInt32 numViews, const KsSamplerState* pSampler );
		virtual void				setPixelTexture( KsUInt32 startSlot, KsUInt32 numViews, const KsTexture* pTexture );
		virtual void				setPixelSamplers( KsUInt32 startSlot, KsUInt32 numViews, const KsSamplerState* pSampler );
		virtual void				draw( KsUInt32 vertexCount, KsUInt32 startVertexLocation );
		virtual void				drawIndexed( KsUInt32 indexCount, KsUInt32 startIndexLocation, KsInt32 baseVertexLocation );

		virtual void				setRasterizerState( KsRasterizerState* pRasterizerState );
		virtual void				setBlendState( KsBlendState* pBlendState, const KsReal blendFactor[ 4 ], KsUInt32 sampleMask );
		virtual void				setDepthStencilState( KsDepthStencilState* pDepthStencilState, KsUInt32 stencilRef );

		virtual KsRenderTarget*		getRenderTarget() { return m_pRenderTargetViews[ 0 ]; }
		virtual KsRenderTarget*		getDepthStencil() { return m_pDepthStencilView; }
		virtual KsRenderTarget*		getRenderTarget( KsUInt32 index ) { return m_pRenderTargetViews[ index ]; }

		virtual void				setUnorderedAccessViews( KsUInt32 startSlot, KsUInt32 numUAVs, KsUnorderedAccessView** ppUnorderedAccessViews, const KsUInt32* pUAVInitialCounts );
		virtual void				dispatch( KsUInt32 threadGroupCountX, KsUInt32 threadGroupCountY, KsUInt32 threadGroupCountZ );

		virtual void				read( KsBufferObject* pBuffer, void* pData, KsUInt32 size );
		virtual void				write( KsBufferObject* pBuffer, void* pData, KsUInt32 size, KsUInt32 flags );
		virtual void*				map( KsBufferObject* pBuffer, KsUInt32 flags );
		virtual void				unmap( KsBufferObject* pBuffer );

		virtual void				clearState();
		virtual KsBool				finishCommandList( KsBool restoreDeferredContextState, KsCommandList* pCommandList );
		virtual void				executeCommandList( KsCommandList* pCommandList, KsBool restoreDeferredContextState );

		/* デバイスコンテキスト			*/
		ID3D11DeviceContext*		getDeviceContex() { return m_pDeviceContext; }

	public:
		ID3D11DeviceContext*		m_pDeviceContext;								/**< デバイスコンテキスト			*/
		KsRenderTargetDX11*			m_pRenderTargetView;							/**< 描画ターゲット				*/
		KsDepthStencilDX11*			m_pDepthStencilView;							/**< 深度ステンシルターゲット		*/
		KsRenderTargetDX11*			m_pRenderTargetViews[ KS_RENDER_TARGET_COUNT ];	/**< 描画ターゲット				*/
};

#endif		/* __KSRENDERCONTEXTDX11_H__ */



