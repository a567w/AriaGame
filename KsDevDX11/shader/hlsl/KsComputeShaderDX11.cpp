/************************************************************************************************/
/** 
 * @file		KsComputeShaderDX11.cpp
 * @brief		コンピュートシェーダー
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
#include "KsDevDX11/shader/hlsl/KsComputeShaderDX11.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

namespace
{
	KsChar*	ComputeShaderModelNameTable[] = 
	{
		"cs_2_0",
		"cs_3_0",
		"cs_4_0",
		"cs_5_0"
	};
}

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsComputeShaderDX11::KsComputeShaderDX11( KsRenderSystemDX11* pRenderSystem )
	: KsComputeShader()
	, m_pRenderSystem( pRenderSystem )
	, m_pComputeShader( NULL )
	, m_pBlob( NULL )
{
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsComputeShaderDX11::~KsComputeShaderDX11()
{
	ksRELEASE( m_pBlob );
	ksRELEASE( m_pComputeShader );
}

/************************************************************************************************/
/*
 * ファイルからコンピュートシェーダーを生成する
 * @param	pFileName		ファイル名
 * @param	shaderModel		シェーダーモデル
 * @retval	ksTRUE			生成成功
 * @retval	ksFALSE			生成失敗
 */
/************************************************************************************************/
KsBool KsComputeShaderDX11::createFromFile( const KsChar* pFileName, const KsChar* pEntryPoint, ksSHADER_MODEL_TYPE shaderModel )
{
	ID3DBlob*		pBlob        = NULL;
	ID3DBlob*		pError       = NULL;
    HRESULT			hr           = S_OK;
	DWORD			flags        = D3DCOMPILE_ENABLE_STRICTNESS;
	ID3D11Device*	pDevice      = m_pRenderSystem->getD3DDevice();
	KsChar*			pShaderModel = ComputeShaderModelNameTable[ shaderModel ];

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

	hr = pDevice->CreateComputeShader( pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, &m_pComputeShader );

	//ksRELEASE( pBlob );
	// InputLayout用に取っておく
	m_pBlob = pBlob;

	if( ksFAILED( hr ) )
	{
		return ksFALSE;
	}

	return ksTRUE;
}

/************************************************************************************************/
/*
 * データからコンピュートシェーダーを生成する
 * @param	pData			データ
 * @param	dataSize		データサイズ
 * @param	shaderModel		シェーダーモデル
 * @retval	ksTRUE			生成成功
 * @retval	ksFALSE			生成失敗
 */
/************************************************************************************************/
KsBool KsComputeShaderDX11::createFromMemory( const void* pData, KsUInt32 dataSize )
{
	ID3D11Device*	pDevice = m_pRenderSystem->getD3DDevice();
	HRESULT			hr      = pDevice->CreateComputeShader( pData, dataSize, NULL, &m_pComputeShader );

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
void KsComputeShaderDX11::destroy()
{
	//
}

/************************************************************************************************/
/*
 * バッファのポインタを取得する
 * @return					バッファのポインタ
 */
/************************************************************************************************/
const void* KsComputeShaderDX11::getBufferPointer()
{
	return m_pBlob->GetBufferPointer();
}

/************************************************************************************************/
/*
 * バッファのサイズを取得する
 * @return					バッファのサイズ
 */
/************************************************************************************************/
KsUInt32 KsComputeShaderDX11::getBufferSize()
{
	return m_pBlob->GetBufferSize();
}

