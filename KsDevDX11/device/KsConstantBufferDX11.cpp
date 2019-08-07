/************************************************************************************************/
/** 
 * @file		KsConstantBufferDX11.cpp
 * @brief		定数バッファ
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
#include "KsDevDX11/device/KsConstantBufferDX11.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/*
 * コンストラクタ
 * @param	pRenderSystem	描画システム
 * @param	pData			データ読み込み用のポインタ
 * @param	size			データサイズ
 */
/************************************************************************************************/
KsConstantBufferDX11::KsConstantBufferDX11( KsRenderSystemDX11* pRenderSystem, void* pData, KsUInt32 size, KsUInt32 flags )
	: m_pRenderSystem( pRenderSystem )
	, m_pConstantBuffer( 0 )
{
	create( pRenderSystem, pData, size, flags );
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsConstantBufferDX11::~KsConstantBufferDX11()
{
	ksRELEASE( m_pConstantBuffer );
}

/************************************************************************************************/
/*
 * 定数バッファを生成する
 * @param	pRenderSystem	描画システム
 * @param	pData			データ読み込み用のポインタ
 * @param	size			データサイズ
 * @param	flags			フラグ
 * @retval	ksTRUE			生成成功
 * @retval	ksFALSE			生成失敗
 */
/************************************************************************************************/
KsBool KsConstantBufferDX11::create( KsRenderSystemDX11* pRenderSystem, void* pData, KsUInt32 size, KsUInt32 flags )
{
	// 定数バッファを作成する
	// バッファ情報の設定
	D3D11_BUFFER_DESC	desc;

	// ゼロクリアする
	KsZeroMemory( &desc, sizeof(desc) );

	if( flags == ksFLAG_CPU_ACCESS_WRITE )
	{
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else if( flags == ksFLAG_CPU_ACCESS_READ )
	{
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	}

	desc.ByteWidth      = size;
	desc.Usage          = D3D11_USAGE_DEFAULT;
	desc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;

	HRESULT hr = E_FAIL;

	if( pData )
	{
		D3D11_SUBRESOURCE_DATA	resource;

		resource.pSysMem          = pData;
		resource.SysMemPitch      = 0;
		resource.SysMemSlicePitch = 0;

		hr = pRenderSystem->getD3DDevice()->CreateBuffer( &desc, &resource, &m_pConstantBuffer );
	}
	else
	{
		hr = pRenderSystem->getD3DDevice()->CreateBuffer( &desc, NULL, &m_pConstantBuffer );
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
void KsConstantBufferDX11::destroy()
{
	delete this;
}

/************************************************************************************************/
/*
 * リソースを取得する
 * @return					 リソース
 */
/************************************************************************************************/
void* KsConstantBufferDX11::getBufferResource()
{
	return m_pConstantBuffer;
}

/************************************************************************************************/
/*
 * 定数バッファをロックする
 * @param	pContext		描画コンテキスト
 * @param	flags			ロックフラグ
 * @return					ロックしたバッファの先頭ポインタ
 */
/************************************************************************************************/
void* KsConstantBufferDX11::lock( const KsRenderContext* pContext, KsUInt32 flags )
{
	return NULL;
}

/************************************************************************************************/
/*
 * 定数バッファのロックを解除する
 */
/************************************************************************************************/
void KsConstantBufferDX11::unlock( const KsRenderContext* pContext )
{
}

/************************************************************************************************/
/*
 * 定数バッファからの読み込み
 * @param	pContext		描画コンテキスト
 * @param	pData			データ読み込み用のポインタ
 * @param	size			データサイズ
 */
/************************************************************************************************/
void KsConstantBufferDX11::read( const KsRenderContext* pContext, void* pData, KsUInt32 size )
{
}

/************************************************************************************************/
/*
 * 定数バッファへの書き込み
 * @param	pContext		描画コンテキスト
 * @param	pData			データ読み込み用のポインタ
 * @param	size			データサイズ
 */
/************************************************************************************************/
void KsConstantBufferDX11::write( const KsRenderContext* pContext, void* pData, KsUInt32 size )
{

}

