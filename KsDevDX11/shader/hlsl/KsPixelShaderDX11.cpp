/************************************************************************************************/
/** 
 * @file		KsPixelShaderDX11.cpp
 * @brief		シェーダーオブジェクト
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
#include "KsDevDX11/shader/hlsl/KsPixelShaderDX11.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


namespace
{
	KsChar*	PixelShaderModelNameTable[] = 
	{
		"ps_2_0",
		"ps_3_0",
		"ps_4_0",
		"ps_5_0"
	};
}

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsPixelShaderDX11::KsPixelShaderDX11( KsRenderSystemDX11* pRenderSystem )
	: KsPixelShader()
	, m_pRenderSystem( pRenderSystem )
	, m_pPixelShader( NULL )
{
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsPixelShaderDX11::~KsPixelShaderDX11()
{
	ksRELEASE( m_pPixelShader );
}

/************************************************************************************************/
/*
 * ファイルからピクセルシェーダーを生成する
 * @param	pFileName		ファイル名
 * @param	pEntryPoint		エントリーポイント
 * @param	shaderModel		シェーダーモデル
 * @retval	ksTRUE			生成成功
 * @retval	ksFALSE			生成失敗
 */
/************************************************************************************************/
KsBool KsPixelShaderDX11::createFromFile( const KsChar* pFileName, const KsChar* pEntryPoint, ksSHADER_MODEL_TYPE shaderModel )
{
	ID3DBlob*		pBlob        = NULL;
	ID3DBlob*		pError       = NULL;
	HRESULT			hr           = S_OK;
	DWORD			flags        = D3DCOMPILE_ENABLE_STRICTNESS;
	ID3D11Device*	pDevice      = m_pRenderSystem->getD3DDevice();
	KsChar*			pShaderModel = PixelShaderModelNameTable[ shaderModel ];

#if defined( DEBUG ) || defined( _DEBUG )
	flags |= D3DCOMPILE_DEBUG;
#endif

#ifdef UNICODE
	hr = D3DCompileFromFile( pFileName, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, pEntryPoint, pShaderModel,  flags, 0, &pBlob, &pError );
#else
	KsWChar		wFileName[ MAX_PATH ];

	ks_mbstowcs( pFileName, wFileName, MAX_PATH );

	hr = D3DCompileFromFile( wFileName, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, pEntryPoint, pShaderModel,  flags, 0, &pBlob, &pError );
#endif // #ifdef UNICODE

	ksRELEASE( pError );

	if( ksFAILED( hr ) )
	{
		return ksFALSE;
	}

	hr = pDevice->CreatePixelShader( pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, &m_pPixelShader );

	ksRELEASE( pBlob );

	if( ksFAILED( hr ) )
	{
		return ksFALSE;
	}

	return ksTRUE;
}

/************************************************************************************************/
/*
 * データからピクセルシェーダーを生成する
 * @param	pData			データ
 * @param	dataSize		データサイズ
 * @param	shaderModel		シェーダーモデル
 * @retval	ksTRUE			生成成功
 * @retval	ksFALSE			生成失敗
 */
/************************************************************************************************/
KsBool KsPixelShaderDX11::createFromMemory( const void* pData, KsUInt32 dataSize )
{
	ID3D11Device*	pDevice = m_pRenderSystem->getD3DDevice();
	HRESULT			hr      = pDevice->CreatePixelShader( pData, dataSize, NULL, &m_pPixelShader );

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
void KsPixelShaderDX11::destroy()
{
}


