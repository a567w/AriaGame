/************************************************************************************************/
/** 
 * @file		KsVertexBufferDX11.h
 * @brief		頂点バッファ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsDevDX11/KsDevDX11PreCompile.h"
#include "KsDevDX11/device/KsVertexBufferDX11.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/*
 * コンストラクタ(頂点バッファを生成する)
 * @param	pRenderSystem	描画システム
 * @param	pData			データ読み込み用のポインタ
 * @param	vertexSize		頂点サイズ
 * @param	numVertex		頂点数
 * @param	vertexFormat	頂点フォーマット
 * @param	flags			フラグ
 */
/************************************************************************************************/
KsVertexBufferDX11::KsVertexBufferDX11( KsRenderSystemDX11* pRenderSystem, void* pData, KsUInt32 vertexSize, KsUInt32 numVertex, KsUInt32 vertexFormat, KsUInt32 flags )
	: m_pRenderSystem( pRenderSystem )
	, m_pVertexBuffer( 0 )
{
	create( pRenderSystem, pData, vertexSize, numVertex, vertexFormat, flags );
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsVertexBufferDX11::~KsVertexBufferDX11()
{
	ksRELEASE( m_pVertexBuffer );
}

/************************************************************************************************/
/*
 * 頂点バッファを生成する
 * @param	pRenderSystem	描画システム
 * @param	pData			データ読み込み用のポインタ
 * @param	vertexSize		頂点サイズ
 * @param	numVertex		頂点数
 * @param	vertexFormat	頂点フォーマット
 * @param	flags			フラグ
 * @retval	ksTRUE			生成成功
 * @retval	ksFALSE			生成失敗
 */
/************************************************************************************************/
KsBool KsVertexBufferDX11::create( KsRenderSystemDX11* pRenderSystem, void* pData, KsUInt32 vertexSize, KsUInt32 numVertex, KsUInt32 vertexFormat, KsUInt32 flags )
{
	m_vertexSize   = vertexSize;
	m_numVertex    = numVertex;
	m_vertexFormat = vertexFormat;

	// 頂点バッファを作成する
	// バッファ情報の設定
	D3D11_BUFFER_DESC	desc;

	// ゼロクリアする
	KsZeroMemory( &desc, sizeof(desc) );

	desc.ByteWidth      = m_vertexSize * m_numVertex;
	desc.Usage          = D3D11_USAGE_DEFAULT;
	desc.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = flags;

	if( flags == ksCPU_ACCESS_WRITE )
	{
		desc.Usage = D3D11_USAGE_DYNAMIC;
	}

	HRESULT hr = E_FAIL;

	if( pData )
	{
		D3D11_SUBRESOURCE_DATA	resource;
		
		KsZeroMemory( &resource, sizeof(resource) );

		resource.pSysMem          = pData;
		resource.SysMemPitch      = 0;
		resource.SysMemSlicePitch = 0;

		hr = pRenderSystem->getD3DDevice()->CreateBuffer( &desc, &resource, &m_pVertexBuffer );
	}
	else
	{
		hr = pRenderSystem->getD3DDevice()->CreateBuffer( &desc, NULL, &m_pVertexBuffer );
	}

	if( ksFAILED( hr ) )
	{
		return ksFALSE;
	}

	return ksTRUE;
}

/************************************************************************************************/
/*
 * 破棄処理
 */
/************************************************************************************************/
void KsVertexBufferDX11::destroy()
{
	delete this;
}

/************************************************************************************************/
/*
 * リソースを取得する
 * @return					 リソース
 */
/************************************************************************************************/
void* KsVertexBufferDX11::getBufferResource()
{
	return m_pVertexBuffer;
}

/************************************************************************************************/
/*
 * 頂点バッファをロックする
 * @param	pContext		描画コンテキスト
 * @param	flags			ロックフラグ
 * @return					ロックしたバッファの先頭ポインタ
 */
/************************************************************************************************/
void* KsVertexBufferDX11::lock( const KsRenderContext* pContext, KsUInt32 flags )
{
#if 0
	void*		pBuffer;

	m_pVertexBuffer->Lock( startIndex*m_indexSize, numIndex*m_indexSize, &pBuffer, flags );

	// データ設定
	
	hr = g_pContext->Map( m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &m_resource );
	if( ksSUCCEEDED(hr) )
	{
		USHORT*	p = reinterpret_cast<USHORT*>(resource.pData);
		p[0] = 0; p[1] = 1; p[2] = 2; p[3] = 3;
		
	}

	return pBuffer;
#endif
	return NULL;
}

/************************************************************************************************/
/*
 * 頂点バッファのロックを解除する
 */
/************************************************************************************************/
void KsVertexBufferDX11::unlock( const KsRenderContext* pContext )
{
	//g_pContext->Unmap( m_pVertexBuffer, 0 );

	//m_pVertexBuffer->Unlock();
}

/************************************************************************************************/
/*
 * 頂点バッファからの読み込み
 * @param	pContext		描画コンテキスト
 * @param	pData			データ読み込み用のポインタ
 * @param	size			データサイズ
 */
/************************************************************************************************/
void KsVertexBufferDX11::read( const KsRenderContext* pContext, void* pData, KsUInt32 size )
{
	((KsRenderContext*)pContext)->read( this, pData, size );
}

/************************************************************************************************/
/*
 * 頂点バッファへの書き込み
 * @param	pContext		描画コンテキスト
 * @param	pData			データ読み込み用のポインタ
 * @param	size			データサイズ
 */
/************************************************************************************************/
void KsVertexBufferDX11::write( const KsRenderContext* pContext, void* pData, KsUInt32 size )
{
#if 0
	void*		pBuffer;
	KsUInt32	length = numIndex*m_indexSize;

	m_pVertexBuffer->Lock( startIndex*m_indexSize, length, &pBuffer, D3DLOCK_READONLY );

	memcpy( pBuffer, pData, length );
	
	m_pVertexBuffer->Unlock();
#endif
}

