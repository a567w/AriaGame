/************************************************************************************************/
/** 
 * @file		KsIndexBufferDX11.h
 * @brief		インデックスバッファ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsDevDX11/KsDevDX11PreCompile.h"
#include "KsDevDX11/device/KsIndexBufferDX11.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/*
 * インデックスバッファを生成する
 * @param	pDevice			デバイス
 * @param	numIndex		インデックスの数
 * @param	flags			フラグ
 */
/************************************************************************************************/
KsIndexBufferDX11::KsIndexBufferDX11( KsRenderSystemDX11* pRenderSystem, void* pData, KsUInt32 size, KsUInt32 numIndex, KsUInt32 indexFormat, KsUInt32 flags )
	: m_pRenderSystem( pRenderSystem )
	, m_pIndexBuffer( 0 )
{
	create( pRenderSystem, pData, size, numIndex, indexFormat, flags );
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsIndexBufferDX11::~KsIndexBufferDX11()
{
	ksRELEASE( m_pIndexBuffer );
}

/************************************************************************************************/
/*
 * インデックスバッファを生成する
 * @param	pRenderSystem	描画システム
 * @param	pData			データ読み込み用のポインタ
 * @param	size			データサイズ
 * @param	numIndex		インデックスの数
 * @param	indexFormat		インデックスフォーマット
 * @param	flags			フラグ
 * @retval	ksTRUE			生成成功
 * @retval	ksFALSE			生成失敗
 */
/************************************************************************************************/
KsBool KsIndexBufferDX11::create( KsRenderSystemDX11* pRenderSystem, void* pData, KsUInt32 size, KsUInt32 numIndex, KsUInt32 indexFormat, KsUInt32 flags )
{
	m_numIndex = numIndex;

	// インデックスバッファを作成する
	// バッファ情報の設定
	D3D11_BUFFER_DESC	desc;

	// ゼロクリアする
	KsZeroMemory( &desc, sizeof(desc) );

	if( ksFMT_INDEX16 == indexFormat )
	{
		m_indexFormatType = ksFMT_INDEX16;
		m_indexSize       = 2;
	}
	else if( ksFMT_INDEX32 == indexFormat )
	{
		m_indexFormatType = ksFMT_INDEX32;
		m_indexSize       = 4;
	}
	else
	{
		KsAssert( 0, "not index format." );
	}

	desc.ByteWidth      = m_indexSize * numIndex;
	desc.Usage          = D3D11_USAGE_DYNAMIC;
	desc.BindFlags      = D3D11_BIND_INDEX_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT hr = E_FAIL;

	if( pData )
	{
		D3D11_SUBRESOURCE_DATA	resource;

		resource.pSysMem          = pData;
		resource.SysMemPitch      = 0;
		resource.SysMemSlicePitch = 0;

		hr = pRenderSystem->getD3DDevice()->CreateBuffer( &desc, &resource, &m_pIndexBuffer );
	}
	else
	{
		hr = pRenderSystem->getD3DDevice()->CreateBuffer( &desc, NULL, &m_pIndexBuffer );
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
void KsIndexBufferDX11::destroy()
{
	delete this;
}

/************************************************************************************************/
/*
 * リソースを取得する
 * @return					 リソース
 */
/************************************************************************************************/
void* KsIndexBufferDX11::getBufferResource()
{
	return m_pIndexBuffer;
}

/************************************************************************************************/
/*
 * インデックスバッファをロックする
 * @param	pContext		描画コンテキスト
 * @param	flags			ロックフラグ
 * @return					ロックしたバッファの先頭ポインタ
 */
/************************************************************************************************/
void* KsIndexBufferDX11::lock( const KsRenderContext* pContext, KsUInt32 flags )
{
#if 0
	void*		pBuffer;

	m_pIndexBuffer->Lock( startIndex*m_indexSize, numIndex*m_indexSize, &pBuffer, flags );

	// データ設定
	
	hr = g_pContext->Map( m_pIndexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &m_resource );
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
 * インデックスバッファのロックを解除する
 */
/************************************************************************************************/
void KsIndexBufferDX11::unlock( const KsRenderContext* pContext )
{
	//g_pContext->Unmap( m_pIndexBuffer, 0 );

	//m_pIndexBuffer->Unlock();
}

/************************************************************************************************/
/*
 * インデックスバッファからの読み込み
 * @param	pContext		描画コンテキスト
 * @param	pData			データ読み込み用のポインタ
 * @param	size			データサイズ
 */
/************************************************************************************************/
void KsIndexBufferDX11::read( const KsRenderContext* pContext, void* pData, KsUInt32 size )
{
	((KsRenderContext*)pContext)->read( this, pData, size );
}

/************************************************************************************************/
/*
 * インデックスバッファへの書き込み
 * @param	pContext		描画コンテキスト
 * @param	pData			データ読み込み用のポインタ
 * @param	size			データサイズ
 */
/************************************************************************************************/
void KsIndexBufferDX11::write( const KsRenderContext* pContext, void* pData, KsUInt32 size )
{
#if 0
	void*		pBuffer;
	KsUInt32	length = numIndex*m_indexSize;

	m_pIndexBuffer->Lock( startIndex*m_indexSize, length, &pBuffer, D3DLOCK_READONLY );

	memcpy( pBuffer, pData, length );
	
	m_pIndexBuffer->Unlock();
#endif
}

