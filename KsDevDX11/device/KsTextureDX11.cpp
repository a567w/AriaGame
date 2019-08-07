/************************************************************************************************/
/** 
 * @file		KsTextureDX11.cpp
 * @brief		DirectX用テクスチャ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsDevDX11/KsDevDX11PreCompile.h"
#include "KsDevDX11/device/KsTextureDX11.h"
#include "KsDevDX11/device/KsTextureManagerDX11.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KsTextureDX11::KsTextureDX11()
	: m_pImage( 0 )
	, m_pD3D11Texture( 0 )
	, m_pShaderResourceView( 0 )
{
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KsTextureDX11::KsTextureDX11( KsRenderSystemDX11* pRenderSystem, const KsChar* pFileName, KsUInt32 flags )
	: m_pImage( 0 )
	, m_pD3D11Texture( 0 )
	, m_pShaderResourceView( 0 )
{
	ID3D11Resource*		pResource;

#ifdef UNICODE
	HRESULT hr = KsCreateDDSTextureFromFile( pRenderSystem->getD3DDevice(), pFileName, &pResource, NULL, 0 );
#else
	KsWChar		wFileName[ MAX_PATH ];

	ks_mbstowcs( pFileName, wFileName, MAX_PATH );

	HRESULT hr = KsCreateDDSTextureFromFile( pRenderSystem->getD3DDevice(), wFileName, &pResource, &m_pShaderResourceView, 0 );
#endif // #ifdef UNICODE

	// 生成チェック
	KsAssert( ksSUCCEEDED( hr ), "ERROR:CreateTexture" );

#if 0
	D3D11_TEXTURE2D_DESC	desc;
	m_pD3D11Texture = reinterpret_cast<ID3D11Texture2D*>( pResource );

	// テクスチャ詳細を取得する
	m_pD3D11Texture->GetDesc( &desc );

	// テクスチャ設定
	m_id            = KsCrc32( (KsUInt8*)pFileName );
	m_name          = pFileName;
	m_width         = static_cast<KsUInt16>( desc.Width );
	m_height        = static_cast<KsUInt16>( desc.Height );
	m_numMipmap     = static_cast<KsUInt32>( desc.MipLevels - 1 );
	m_mipLevels     = static_cast<KsUInt32>( desc.MipLevels );

	// ShaderResourceViewを作成する
	D3D11_SHADER_RESOURCE_VIEW_DESC	srvDesc;
	
	KsZeroMemory( &srvDesc, sizeof(srvDesc) );

	srvDesc.Format                    = desc.Format;
	srvDesc.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels       = desc.MipLevels;

	hr = pRenderSystem->getD3DDevice()->CreateShaderResourceView( m_pD3D11Texture, &srvDesc, &m_pShaderResourceView );

	KsAssert( ksSUCCEEDED( hr ), "CreateShaderResourceView" );
#endif

	/* テクスチャのフラグセット */
	m_flags  = flags;
}

/************************************************************************************************/
/*
 * コンストラクタ
 * @param		pImage			イメージファイル
 * @param		flags			読み込み方法のフラグ
 */
/************************************************************************************************/
KsTextureDX11::KsTextureDX11( KsImage* pImage, KsUInt32 flags )
{
	if( flags )
	{
		m_pImage = pImage->clone();
	}
	else
	{
		m_pImage = pImage;
	}

	m_width  = m_pImage->m_width;
	m_height = m_pImage->m_height;
}

/************************************************************************************************/
/*
 * コンストラクタ
 * @param		pD3D11Texture		Direct3Dテクスチャ
 * @param		pShaderView			シェーダーリソースビュー
 */
/************************************************************************************************/
KsTextureDX11::KsTextureDX11( ID3D11Texture2D* pD3D11Texture, ID3D11ShaderResourceView* pShaderResourceView )
	: m_pD3D11Texture( pD3D11Texture )
	, m_pShaderResourceView( pShaderResourceView )
	, m_pImage( 0 )
{
	D3D11_TEXTURE2D_DESC	desc;

	// テクスチャ詳細を取得する
	m_pD3D11Texture->GetDesc( &desc );

	// テクスチャ設定
	m_width         = static_cast<KsUInt16>( desc.Width );
	m_height        = static_cast<KsUInt16>( desc.Height );
	m_numMipmap     = static_cast<KsUInt32>( desc.MipLevels - 1 );
	m_mipLevels     = static_cast<KsUInt32>( desc.MipLevels );
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KsTextureDX11::~KsTextureDX11()
{
	ksRELEASE( m_pD3D11Texture );
	ksRELEASE( m_pShaderResourceView );

	/* イメージデータ開放 */
	ksDELETE( m_pImage );
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsTextureDX11::destroy()
{
	/* テクスチャマネージャを使用しているかどうかのチェック */
	if( m_flags & ksTEXTURE_FLAG_USE_MANAGER )
	{
		KsTextureManager*	pTextureManager =KsTextureManager::getInstancePtr();

		if( pTextureManager )
		{
			pTextureManager->destroy( this );
		}
	}
	else
	{
		/* 参照カウントを下げます */
		dec();
	}
}

/************************************************************************************************/
/*
 * テクスチャをアクティブにする
 */
/************************************************************************************************/
void KsTextureDX11::active()
{

}

/************************************************************************************************/
/*
 * リソースを取得する
 * @return							 リソース
 */
/************************************************************************************************/
void* KsTextureDX11::getBufferResource()
{
	return NULL;
}

/************************************************************************************************/
/*
 * バッファをロックする
 * @param	pContext				描画コンテキスト
 * @param	flags					ロックフラグ
 * @return							ロックしたバッファの先頭ポインタ
 */
 /************************************************************************************************/
void* KsTextureDX11::lock( const KsRenderContext* pContext, KsUInt32 flags )
{
	return NULL;
}

/************************************************************************************************/
/*
 * バッファのロックを解除する
 * @param	pContext				描画コンテキスト
 */
 /************************************************************************************************/
void KsTextureDX11::unlock( const KsRenderContext* pContext )
{
}

/************************************************************************************************/
/*
 * バッファからの読み込み
 * @param	pContext				描画コンテキスト
 * @param	pData					データ読み込み用のポインタ
 * @param	size					データサイズ
 */
 /************************************************************************************************/
void KsTextureDX11::read( const KsRenderContext* pContext, void* pData, KsUInt32 size )
{
}

/************************************************************************************************/
/*
 * バッファへの書き込み
 * @param	pContext				描画コンテキスト
 * @param	pData					データ読み込み用のポインタ
 * @param	size					データサイズ
 */
 /************************************************************************************************/
void KsTextureDX11::write( const KsRenderContext* pContext, void* pData, KsUInt32 size )
{
}

