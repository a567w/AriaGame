/************************************************************************************************/
/** 
 * @file		KsRenderContextDX11.cpp
 * @brief		描画コンテキスト(DX11用)
 * @author		Tsukasa Kato
 * @date		2004/08/17
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>											 */
/*==============================================================================================*/
#include "KsDevDX11/KsDevDX11PreCompile.h"
#include "KsDevDX11/device/KsRenderContextDX11.h"


/*==============================================================================================*/
/*									  << 宣言 >>												*/
/*==============================================================================================*/


/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsRenderContextDX11::KsRenderContextDX11()
	: m_pDeviceContext( 0 )
	, m_pDepthStencilView( 0 )
{
	KsZeroMemory( m_pRenderTargetViews, sizeof(m_pRenderTargetViews) );
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsRenderContextDX11::~KsRenderContextDX11()
{
	ksRELEASE( m_pDeviceContext );
}

/************************************************************************************************/
/*
 * シーンをクリアする
 * @param		flags		描画フラグ
 * @param		color		クリアーカラー
 * @param		depth		ディプスクリアする値
 * @param		stencil		ステンシルクリアする値
 */
/************************************************************************************************/
void KsRenderContextDX11::clearScene( KsUInt32 flags, KsColor color, KsReal depth, KsUInt32 stencil )
{
	if( flags & ksCLEAR_FLAG_COLOR )
	{
		KsReal clearColor[ 4 ];

		clearColor[ 0 ] = ((KsReal)color.getRed())   / 255.0f;
		clearColor[ 1 ] = ((KsReal)color.getGreen()) / 255.0f;
		clearColor[ 2 ] = ((KsReal)color.getBlue())  / 255.0f;
		clearColor[ 3 ] = ((KsReal)color.getAlpha()) / 255.0f;

		ID3D11RenderTargetView*	pTargetViewDX11 = reinterpret_cast<ID3D11RenderTargetView*>( m_pRenderTargetViews[ 0 ]->getRenderResource() );

		m_pDeviceContext->ClearRenderTargetView( pTargetViewDX11, clearColor );
	}

	KsUInt32	uDepthStencilFlags = 0;

	if( flags & ksCLEAR_FLAG_DEPTH )
	{
		uDepthStencilFlags |= D3D11_CLEAR_DEPTH;
	}

	if( flags & ksCLEAR_FLAG_STENCIL )
	{
		uDepthStencilFlags |= D3D11_CLEAR_STENCIL;
	}

	if( uDepthStencilFlags )
	{
		m_pDeviceContext->ClearDepthStencilView( m_pDepthStencilView->m_pDepthStencilView, uDepthStencilFlags, depth, stencil );
	}
}

/************************************************************************************************/
/*
 * 深度バッファをクリアする
 * @param		flags		クリアフラグ
 * @param		depth		ディプスクリアする値
 * @param		stencil		ステンシルクリアする値
 */
/************************************************************************************************/
void KsRenderContextDX11::clearDepthStencil( KsRenderTarget* pTarget, KsUInt32 flags, KsReal depth, KsUInt32 stencil )
{
	KsUInt32	uDepthStencilFlags = 0;

	if( flags & ksCLEAR_FLAG_DEPTH )
	{
		uDepthStencilFlags |= D3D11_CLEAR_DEPTH;
	}

	if( flags & ksCLEAR_FLAG_STENCIL )
	{
		uDepthStencilFlags |= D3D11_CLEAR_STENCIL;
	}

	if( uDepthStencilFlags )
	{
		m_pDeviceContext->ClearDepthStencilView( ((KsDepthStencilDX11*)m_pDepthStencilView)->m_pDepthStencilView, uDepthStencilFlags, depth, stencil );
	}
}

/************************************************************************************************/
/*
 * シーンをクリアする
 * @param	numViews		クリアーするレンダー ターゲットの数
 * @param	flags			描画フラグ
 * @param	color			クリアーカラー
 * @param	depth			ディプスクリアする値
 * @param	stencil			ステンシルクリアする値
 */
/************************************************************************************************/
void KsRenderContextDX11::clearScenes( KsUInt32 numViews, KsUInt32 flags, KsColor color, KsReal depth, KsUInt32 stencil )
{
	if( flags & ksCLEAR_FLAG_COLOR )
	{
		KsReal clearColor[ 4 ];

		clearColor[ 0 ] = ((KsReal)color.getRed())   / 255.0f;
		clearColor[ 1 ] = ((KsReal)color.getGreen()) / 255.0f;
		clearColor[ 2 ] = ((KsReal)color.getBlue())  / 255.0f;
		clearColor[ 3 ] = ((KsReal)color.getAlpha()) / 255.0f;

		for( KsUInt32 i=0; i<numViews; i++ )
		{
			ID3D11RenderTargetView*	pTargetViewDX11 = reinterpret_cast<ID3D11RenderTargetView*>( m_pRenderTargetViews[ i ]->getRenderResource() );

			m_pDeviceContext->ClearRenderTargetView( pTargetViewDX11, clearColor );
		}
	}

	KsUInt32	uDepthStencilFlags = 0;

	if( flags & ksCLEAR_FLAG_DEPTH )
	{
		uDepthStencilFlags |= D3D11_CLEAR_DEPTH;
	}

	if( flags & ksCLEAR_FLAG_STENCIL )
	{
		uDepthStencilFlags |= D3D11_CLEAR_STENCIL;
	}

	if( uDepthStencilFlags )
	{
		m_pDeviceContext->ClearDepthStencilView( m_pDepthStencilView->m_pDepthStencilView, uDepthStencilFlags, depth, stencil );
	}
}

/************************************************************************************************/
/*
 * レンダーターゲットをセットする
 * @param	pRenderTargetView		描画ターゲット
 * @param	pDepthStencilView		深度ステンシルターゲット
 */
/************************************************************************************************/
void KsRenderContextDX11::setRenderTarget( KsRenderTarget* pRenderTargetView, KsRenderTarget* pDepthStencilView )
{
	if( !pRenderTargetView && !pDepthStencilView )
	{
		m_pDeviceContext->OMSetRenderTargets( 0, 0, 0 );
	}
	else
	{
		m_pRenderTargetViews[ 0 ] = pRenderTargetView ? reinterpret_cast<KsRenderTargetDX11*>( pRenderTargetView ) : NULL;
		m_pDepthStencilView       = pDepthStencilView ? reinterpret_cast<KsDepthStencilDX11*>( pDepthStencilView ) : NULL;

		ID3D11RenderTargetView*	pTargetViewDX11       = reinterpret_cast<ID3D11RenderTargetView*>( m_pRenderTargetViews[ 0 ]->getRenderResource() );
		ID3D11DepthStencilView*	pDepthStencilViewDX11 = m_pDepthStencilView ? m_pDepthStencilView->m_pDepthStencilView : NULL;

		// レンダリングターゲットを設定する
		m_pDeviceContext->OMSetRenderTargets( 1, &pTargetViewDX11, pDepthStencilViewDX11 );
	}
}

/************************************************************************************************/
/*
 * @param	numViews				バインドするレンダー ターゲットの数
 * @param	pRenderTargetView		レンダー ターゲットの配列
 * @param	pDepthStencilView		深度ステンシルターゲット
 */
/************************************************************************************************/
void KsRenderContextDX11::setRenderTargets( KsUInt32 numViews, KsRenderTarget** ppRenderTargetView, KsRenderTarget* pDepthStencilView )
{
	if( 0 == numViews )
	{
		// レンダリングターゲットをリセットする
		m_pDeviceContext->OMSetRenderTargets( 0, 0, 0 );
		return;
	}

	ID3D11RenderTargetView*	pTargetViewsDX11[ KS_RENDER_TARGET_COUNT ];

	for( KsUInt32 i=0; i<numViews; i++ )
	{
		m_pRenderTargetViews[ i ] = reinterpret_cast<KsRenderTargetDX11*>( ppRenderTargetView[ i ] );
		pTargetViewsDX11[ i ]     = reinterpret_cast<ID3D11RenderTargetView*>( m_pRenderTargetViews[ i ]->getRenderResource() );
	}

	m_pDepthStencilView  = pDepthStencilView ? reinterpret_cast<KsDepthStencilDX11*>( pDepthStencilView ) : NULL;

	ID3D11DepthStencilView*	pDepthStencilViewDX11 = m_pDepthStencilView ? m_pDepthStencilView->m_pDepthStencilView : NULL;

	// レンダリングターゲットを設定する
	m_pDeviceContext->OMSetRenderTargets( numViews, pTargetViewsDX11, pDepthStencilViewDX11 );
}

/************************************************************************************************/
/*
 * ビューポートをセットする
 * @param		pViewport			ビューポート設定
 */
/************************************************************************************************/
void KsRenderContextDX11::setViewports( const KsViewport* pViewport )
{
	// ついでにビューポートの設定
	D3D11_VIEWPORT	vp;
	vp.Width    = static_cast<KsReal>( pViewport->m_w );
	vp.Height   = static_cast<KsReal>( pViewport->m_h );
	vp.MinDepth = static_cast<KsReal>( pViewport->m_minZ );
	vp.MaxDepth = static_cast<KsReal>( pViewport->m_maxZ );
	vp.TopLeftX = static_cast<KsReal>( pViewport->m_x );
	vp.TopLeftY = static_cast<KsReal>( pViewport->m_y );

	m_pDeviceContext->RSSetViewports( 1, &vp );
}

/************************************************************************************************/
/*
 * インデックスバッファをセットする
 */
/************************************************************************************************/
void KsRenderContextDX11::setVertexBuffer( const KsVertexBuffer* pBuffer )
{
	KsUInt32		stride = pBuffer->getVertexSize();
    KsUInt32		offset = 0;

	this->setVertexBuffers( 0, 1, pBuffer, &stride, &offset );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::setIndexBuffer( const KsIndexBuffer* pBuffer )
{
	this->setIndexBuffer( pBuffer, pBuffer->getIndexFormatType(), 0 );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::setVertexBuffers( KsUInt32 startSlot, KsUInt32 numBuffers, const KsVertexBuffer* pBuffer, const KsUInt32* pStride, const KsUInt32* pOffset )
{
	m_pDeviceContext->IASetVertexBuffers( startSlot, numBuffers, &((const KsVertexBufferDX11*)pBuffer)->m_pVertexBuffer, pStride, pOffset );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::setIndexBuffer( const KsIndexBuffer* pBuffer, KsUInt32 indexFormat, KsUInt32 offset )
{
	static DXGI_FORMAT	indexFormatDX[] = { DXGI_FORMAT_R16_UINT, DXGI_FORMAT_R32_UINT };

	m_pDeviceContext->IASetIndexBuffer( ((KsIndexBufferDX11*)pBuffer)->m_pIndexBuffer, indexFormatDX[ indexFormat ], offset );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::setInputLayout( KsInputLayout* pInputLayout )
{
	m_pDeviceContext->IASetInputLayout( ((KsInputLayoutDX11*)pInputLayout)->m_pVertexLayout );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::setPrimitiveTopology( KS_PRIMITIVE_TOPOLOGY type )
{
	m_pDeviceContext->IASetPrimitiveTopology( static_cast<D3D11_PRIMITIVE_TOPOLOGY>(type) );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::setVertexShader( KsVertexShader* pShader )
{
	if( pShader )
	{
		m_pDeviceContext->VSSetShader( ((KsVertexShaderDX11*)pShader)->m_pVertexShader, NULL, 0 );
	}
	else
	{
		m_pDeviceContext->VSSetShader( NULL, NULL, 0 );
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::setPixelShader( KsPixelShader* pShader )
{
	if( pShader )
	{
		m_pDeviceContext->PSSetShader( ((KsPixelShaderDX11*)pShader)->m_pPixelShader, NULL, 0 );
	}
	else
	{
		m_pDeviceContext->PSSetShader( NULL, NULL, 0 );
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::setComputeShader( KsComputeShader* pShader )
{
	if( pShader )
	{
		m_pDeviceContext->CSSetShader( ((KsComputeShaderDX11*)pShader)->m_pComputeShader, NULL, 0 );
	}
	else
	{
		m_pDeviceContext->CSSetShader( NULL, NULL, 0 );
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::draw( KsUInt32 vertexCount, KsUInt32 startVertexLocation )
{
	m_pDeviceContext->Draw( vertexCount, startVertexLocation );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::drawIndexed( KsUInt32 indexCount, KsUInt32 startIndexLocation, KsInt32 baseVertexLocation )
{
	m_pDeviceContext->DrawIndexed( indexCount, startIndexLocation, baseVertexLocation );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::setVertexConstantBuffers( KsUInt32 startSlot, KsUInt32 numBuffers, const KsConstantBuffer* pConstantBuffers )
{
	m_pDeviceContext->VSSetConstantBuffers( startSlot, numBuffers, &((const KsConstantBufferDX11*)pConstantBuffers)->m_pConstantBuffer );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::setPixelConstantBuffers( KsUInt32 startSlot, KsUInt32 numBuffers, const KsConstantBuffer* pConstantBuffers )
{
	m_pDeviceContext->PSSetConstantBuffers( startSlot, numBuffers, &((const KsConstantBufferDX11*)pConstantBuffers)->m_pConstantBuffer );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::updateConstantBuffers( KsConstantBuffer* pConstantBuffers, const void* pSrcData )
{
	m_pDeviceContext->UpdateSubresource( ((KsConstantBufferDX11*)pConstantBuffers)->m_pConstantBuffer, 0, NULL, pSrcData, 0, 0 );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::setComputeConstantBuffer( KsUInt32 startSlot, const KsConstantBuffer* pConstantBuffers )
{
	m_pDeviceContext->CSSetConstantBuffers( startSlot, 1, &((const KsConstantBufferDX11*)pConstantBuffers)->m_pConstantBuffer );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::setComputeTexture( KsUInt32 startSlot, const KsTexture* pTexture )
{
	KsTexture*						pTempTexture        = const_cast<KsTexture*>( pTexture );
	ID3D11ShaderResourceView*		pShaderResourceView = (ID3D11ShaderResourceView*)pTempTexture->getTextureResource();

	m_pDeviceContext->CSSetShaderResources( startSlot, 1, &pShaderResourceView );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::setComputeTextures( KsUInt32 startSlot, KsUInt32 numTexture, const KsTexture** pTextures )
{
	ID3D11ShaderResourceView*	ppShaderResourceViews[ 8 ] = {0, 0, 0, 0, 0, 0, 0, 0};

	if( pTextures )
	{
		for( KsUInt32 i=0; i<numTexture; i++ )
		{
			ppShaderResourceViews[ i ] = (ID3D11ShaderResourceView*)(const_cast<KsTexture*>( pTextures[ i ] ))->getTextureResource();
		}
	}

	m_pDeviceContext->CSSetShaderResources( startSlot, numTexture, ppShaderResourceViews );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::setComputeTextures( KsUInt32 startSlot, KsUInt32 numTexture, KsTexture** pTextures )
{
	ID3D11ShaderResourceView*	ppShaderResourceViews[ 8 ] = {0, 0, 0, 0, 0, 0, 0, 0};

	if( pTextures )
	{
		for( KsUInt32 i=0; i<numTexture; i++ )
		{
			ppShaderResourceViews[ i ] = (ID3D11ShaderResourceView*)pTextures[ i ]->getTextureResource();
		}
	}

	m_pDeviceContext->CSSetShaderResources( startSlot, numTexture, ppShaderResourceViews );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::setVertexTexture( KsUInt32 startSlot, KsUInt32 numViews, const KsTexture* pTexture )
{
	KsTexture*						pTempTexture        = const_cast<KsTexture*>( pTexture );
	ID3D11ShaderResourceView*		pShaderResourceView = (ID3D11ShaderResourceView*)pTempTexture->getTextureResource();

	m_pDeviceContext->VSSetShaderResources( startSlot, numViews, &pShaderResourceView );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::setVertexSamplers( KsUInt32 startSlot, KsUInt32 numViews, const KsSamplerState* pSampler )
{
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::setPixelTexture( KsUInt32 startSlot, KsUInt32 numViews, const KsTexture* pTexture )
{
	if( !pTexture )
	{
		ID3D11ShaderResourceView* nullSRV[8] = {0, 0, 0, 0, 0, 0, 0, 0};
		m_pDeviceContext->PSSetShaderResources( startSlot, numViews, nullSRV );
		return;
	}
	KsTexture*						pTempTexture        = const_cast<KsTexture*>( pTexture );
	ID3D11ShaderResourceView*		pShaderResourceView = (ID3D11ShaderResourceView*)pTempTexture->getTextureResource();

	m_pDeviceContext->PSSetShaderResources( startSlot, numViews, &pShaderResourceView );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::setPixelSamplers( KsUInt32 startSlot, KsUInt32 numViews, const KsSamplerState* pSampler )
{
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::setRasterizerState( KsRasterizerState* pRasterizerState )
{
	m_pDeviceContext->RSSetState( (ID3D11RasterizerState*)pRasterizerState->getRenderResource() );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::setBlendState( KsBlendState* pBlendState, const KsReal blendFactor[ 4 ], KsUInt32 sampleMask )
{
	//static const KsReal	s_BlendFactor[ 4 ] = { 0.0f, 0.0f, 0.0f, 0.0f };
	static const KsReal	s_BlendFactor[ 4 ] = { 1.0f, 1.0f, 1.0f, 1.0f };

	if( NULL == blendFactor )
	{
		m_pDeviceContext->OMSetBlendState( (ID3D11BlendState*)pBlendState->getRenderResource(), s_BlendFactor, sampleMask );
	}
	else
	{
		m_pDeviceContext->OMSetBlendState( (ID3D11BlendState*)pBlendState->getRenderResource(), blendFactor, sampleMask );
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::setDepthStencilState( KsDepthStencilState* pDepthStencilState, KsUInt32 stencilRef )
{
	m_pDeviceContext->OMSetDepthStencilState( (ID3D11DepthStencilState*)pDepthStencilState->getRenderResource(), stencilRef );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::setUnorderedAccessViews( KsUInt32 startSlot, KsUInt32 numUAVs, KsUnorderedAccessView** ppUnorderedAccessViews, const KsUInt32* pUAVInitialCounts )
{
	static ID3D11UnorderedAccessView*		nullUAV[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

	if( ppUnorderedAccessViews )
	{
		m_pDeviceContext->CSSetUnorderedAccessViews( startSlot, numUAVs, &((const KsUnorderedAccessViewDX11*)ppUnorderedAccessViews[ 0 ])->m_pUnorderedAccessView, pUAVInitialCounts );
	}
	else
	{
		m_pDeviceContext->CSSetUnorderedAccessViews( startSlot, numUAVs, nullUAV, 0 );
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::dispatch( KsUInt32 threadGroupCountX, KsUInt32 threadGroupCountY, KsUInt32 threadGroupCountZ )
{
	m_pDeviceContext->Dispatch( threadGroupCountX, threadGroupCountY, threadGroupCountZ );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::read( KsBufferObject* pBuffer, void* pData, KsUInt32 size )
{
	D3D11_MAPPED_SUBRESOURCE	mappedResource;
	ID3D11Buffer*				pBufferD3D = reinterpret_cast<ID3D11Buffer*>( pBuffer->getBufferResource() );

	HRESULT hRet = m_pDeviceContext->Map( pBufferD3D, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource );

	if( S_OK == hRet )
	{
		memcpy( pData, mappedResource.pData, size );

		m_pDeviceContext->Unmap( pBufferD3D, 0 );
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::write( KsBufferObject* pBuffer, void* pData, KsUInt32 size, KsUInt32 flags )
{
	//flags
	D3D11_MAPPED_SUBRESOURCE	mappedResource;
	ID3D11Buffer*				pBufferD3D = reinterpret_cast<ID3D11Buffer*>( pBuffer->getBufferResource() );

	HRESULT hRet = m_pDeviceContext->Map( pBufferD3D, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource );

	if( S_OK == hRet )
	{
		memcpy( mappedResource.pData, pData, size );

		m_pDeviceContext->Unmap( pBufferD3D, 0 );
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void* KsRenderContextDX11::map( KsBufferObject* pBuffer, KsUInt32 flags )
{
	D3D11_MAPPED_SUBRESOURCE	mappedResource;
	ID3D11Buffer*				pBufferD3D = reinterpret_cast<ID3D11Buffer*>( pBuffer->getBufferResource() );

	m_pDeviceContext->Map( pBufferD3D, 0, static_cast<D3D11_MAP>(flags), 0, &mappedResource );

	return mappedResource.pData;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::unmap( KsBufferObject* pBuffer )
{
	ID3D11Buffer*				pBufferD3D = reinterpret_cast<ID3D11Buffer*>( pBuffer->getBufferResource() );

	m_pDeviceContext->Unmap( pBufferD3D, 0 );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::clearState()
{
	m_pDeviceContext->ClearState();
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsBool KsRenderContextDX11::finishCommandList( KsBool restoreDeferredContextState, KsCommandList* pCommandList )
{
	ID3D11CommandList**		ppCommandListDX11 = reinterpret_cast<ID3D11CommandList**>( pCommandList->getCommandListBuffer() );

	KsUInt32 hRet = m_pDeviceContext->FinishCommandList( restoreDeferredContextState, ppCommandListDX11 );

	return ksTRUE;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderContextDX11::executeCommandList( KsCommandList* pCommandList, KsBool restoreDeferredContextState )
{
	ID3D11CommandList*		pCommandListDX11 = reinterpret_cast<ID3D11CommandList*>( pCommandList->getCommandList() );

	m_pDeviceContext->ExecuteCommandList( pCommandListDX11, restoreDeferredContextState );
}

