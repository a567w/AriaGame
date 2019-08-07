/************************************************************************************************/
/** 
 * @file		KsComputeShaderDX11.cpp
 * @brief		�R���s���[�g�V�F�[�_�[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsDevDX11/KsDevDX11PreCompile.h"
#include "KsDevDX11/shader/hlsl/KsComputeShaderDX11.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
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
 * �R���X�g���N�^
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
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsComputeShaderDX11::~KsComputeShaderDX11()
{
	ksRELEASE( m_pBlob );
	ksRELEASE( m_pComputeShader );
}

/************************************************************************************************/
/*
 * �t�@�C������R���s���[�g�V�F�[�_�[�𐶐�����
 * @param	pFileName		�t�@�C����
 * @param	shaderModel		�V�F�[�_�[���f��
 * @retval	ksTRUE			��������
 * @retval	ksFALSE			�������s
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
	// InputLayout�p�Ɏ���Ă���
	m_pBlob = pBlob;

	if( ksFAILED( hr ) )
	{
		return ksFALSE;
	}

	return ksTRUE;
}

/************************************************************************************************/
/*
 * �f�[�^����R���s���[�g�V�F�[�_�[�𐶐�����
 * @param	pData			�f�[�^
 * @param	dataSize		�f�[�^�T�C�Y
 * @param	shaderModel		�V�F�[�_�[���f��
 * @retval	ksTRUE			��������
 * @retval	ksFALSE			�������s
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
 * �j������
 */
/************************************************************************************************/
void KsComputeShaderDX11::destroy()
{
	//
}

/************************************************************************************************/
/*
 * �o�b�t�@�̃|�C���^���擾����
 * @return					�o�b�t�@�̃|�C���^
 */
/************************************************************************************************/
const void* KsComputeShaderDX11::getBufferPointer()
{
	return m_pBlob->GetBufferPointer();
}

/************************************************************************************************/
/*
 * �o�b�t�@�̃T�C�Y���擾����
 * @return					�o�b�t�@�̃T�C�Y
 */
/************************************************************************************************/
KsUInt32 KsComputeShaderDX11::getBufferSize()
{
	return m_pBlob->GetBufferSize();
}

