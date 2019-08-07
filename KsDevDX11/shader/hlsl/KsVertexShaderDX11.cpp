/************************************************************************************************/
/** 
 * @file		KsVertexShaderDX11.cpp
 * @brief		頂点シェーダー
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
#include "KsDevDX11/shader/hlsl/KsVertexShaderDX11.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

namespace
{
	KsChar*	VertexShaderModelNameTable[] = 
	{
		"vs_2_0",
		"vs_3_0",
		"vs_4_0",
		"vs_5_0"
	};
}

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsVertexShaderDX11::KsVertexShaderDX11( KsRenderSystemDX11* pRenderSystem )
	: KsVertexShader()
	, m_pRenderSystem( pRenderSystem )
	, m_pVertexShader( NULL )
	, m_pBlob( NULL )
	, m_pData( NULL )
	, m_dataSize( 0 )
{
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsVertexShaderDX11::~KsVertexShaderDX11()
{
	ksRELEASE( m_pBlob );
	ksRELEASE( m_pVertexShader );
}

/************************************************************************************************/
/*
 * ファイルから頂点シェーダーを生成する
 * @param	pFileName		ファイル名
 * @param	shaderModel		シェーダーモデル
 * @retval	ksTRUE			生成成功
 * @retval	ksFALSE			生成失敗
 */
/************************************************************************************************/
KsBool KsVertexShaderDX11::createFromFile( const KsChar* pFileName, const KsChar* pEntryPoint, ksSHADER_MODEL_TYPE shaderModel )
{
	ID3DBlob*		pBlob        = NULL;
	ID3DBlob*		pError       = NULL;
    HRESULT			hr           = S_OK;
	DWORD			flags        = D3DCOMPILE_ENABLE_STRICTNESS;
	ID3D11Device*	pDevice      = m_pRenderSystem->getD3DDevice();
	KsChar*			pShaderModel = VertexShaderModelNameTable[ shaderModel ];

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

	m_pData    = pBlob->GetBufferPointer();
	m_dataSize = pBlob->GetBufferSize();

	hr = pDevice->CreateVertexShader( m_pData, m_dataSize, NULL, &m_pVertexShader );

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
 * データから頂点シェーダーを生成する
 * @param	pData			データ
 * @param	dataSize		データサイズ
 * @retval	ksTRUE			生成成功
 * @retval	ksFALSE			生成失敗
 */
/************************************************************************************************/
KsBool KsVertexShaderDX11::createFromMemory( const void* pData, KsUInt32 dataSize )
{
	ID3D11Device*	pDevice = m_pRenderSystem->getD3DDevice();
	HRESULT			hr      = pDevice->CreateVertexShader( pData, dataSize, NULL, &m_pVertexShader );

	if( ksFAILED( hr ) )
	{
		return ksFALSE;
	}

	m_pData    = pData;
	m_dataSize = dataSize;

	return ksTRUE;
}

/************************************************************************************************/
/*
 * 破棄処理
 */
/************************************************************************************************/
void KsVertexShaderDX11::destroy()
{
	//
}

/************************************************************************************************/
/*
 * バッファのポインタを取得する
 * @return					バッファのポインタ
 */
/************************************************************************************************/
const void* KsVertexShaderDX11::getBufferPointer()
{
	return m_pData;
}

/************************************************************************************************/
/*
 * バッファのサイズを取得する
 * @return					バッファのサイズ
 */
/************************************************************************************************/
KsUInt32 KsVertexShaderDX11::getBufferSize()
{
	return m_dataSize;
}

