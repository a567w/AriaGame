/************************************************************************************************/
/** 
 * @file		KsShaderManagerDX11.cpp
 * @brief		�V�F�[�_�[�}�l�[�W���[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsDevDX11/KsDevDX11PreCompile.h"
#include "KsDevDX11/shader/hlsl/KsShaderManagerDX11.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * �R���X�g���N�^
 * @param	pRenderSystem		�`��V�X�e��
 */
/************************************************************************************************/
KsShaderManagerDX11::KsShaderManagerDX11( KsRenderSystemDX11* pRenderSystem )
	: m_pRenderSystem( pRenderSystem )
{
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsShaderManagerDX11::~KsShaderManagerDX11()
{
}

/************************************************************************************************/
/*
 * �t�@�C������V�F�[�_�[�𐶐�
 * @param	pFileName			�t�@�C����
 * @param	pEntryPoint			�G���g���[�|�C���g
 * @param	shaderModel			�V�F�[�_�[���f��
 * @param	shaderType			�V�F�[�_�[�^�C�v
 * @return						�V�F�[�_�[�v���O�����̃|�C���^
 */
/************************************************************************************************/
KsShaderProgram* KsShaderManagerDX11::createFromFile( const KsChar* pFileName, const KsChar* pEntryPoint, ksSHADER_MODEL_TYPE shaderModel, ksSHADER_TYPE shaderType )
{
	KsShaderProgram*		pShader = findRefInc( pFileName );

	if( pShader )
	{
		return pShader;
	}

	switch( shaderType )
	{
		case ksVERTEX_SHADER:
		{
			// ���_�V�F�[�_�[
			KsVertexShaderDX11*	pShader = new KsVertexShaderDX11( m_pRenderSystem );
			pShader->createFromFile( pFileName, pEntryPoint, shaderModel );
			return pShader;
		}
		case ksPIXEL_SHADER:
		{
			// �s�N�Z���V�F�[�_�[
			KsPixelShaderDX11*	pShader = new KsPixelShaderDX11( m_pRenderSystem );
			pShader->createFromFile( pFileName, pEntryPoint, shaderModel );
			return pShader;
		}
		case ksGEOMETRY_SHADER:
		{
			// �W�I���g���V�F�[�_�[
			return NULL;
		}
		case ksCOMPUTE_SHADER:
		{
			// �R���s���[�g�V�F�[�_�[
			KsComputeShaderDX11*	pShader = new KsComputeShaderDX11( m_pRenderSystem );
			pShader->createFromFile( pFileName, pEntryPoint, shaderModel );
			return pShader;
		}
		default:
			break;
	}

	return NULL;
}

/************************************************************************************************/
/*
 * �f�[�^����V�F�[�_�[�𐶐�
 * @param	pData				�f�[�^
 * @param	dataSize			�f�[�^�T�C�Y
 * @param	shaderType			�V�F�[�_�[�^�C�v
 * @return						�V�F�[�_�[�v���O�����̃|�C���^
 */
/************************************************************************************************/
KsShaderProgram* KsShaderManagerDX11::createFromMemory( const void* pData, KsUInt32 dataSize, ksSHADER_TYPE shaderType )
{
	KsShaderProgram*		pShader = NULL;

	// �������Ă݂�

	if( pShader )
	{
		return pShader;
	}

	switch( shaderType )
	{
		case ksVERTEX_SHADER:
		{
			// ���_�V�F�[�_�[
			pShader = new KsVertexShaderDX11( m_pRenderSystem );
			break;
		}
		case ksPIXEL_SHADER:
		{
			// �s�N�Z���V�F�[�_�[
			pShader = new KsPixelShaderDX11( m_pRenderSystem );
			break;
		}
		case ksGEOMETRY_SHADER:
		{
			// �W�I���g���V�F�[�_�[
			break;
		}
		case ksCOMPUTE_SHADER:
		{
			// �R���s���[�g�V�F�[�_�[
			pShader = new KsComputeShaderDX11( m_pRenderSystem );
			break;
		}
		default:
			break;
	}

	// �V�F�[�_�[�𐶐�����
	if( !pShader->createFromMemory( pData, dataSize ) )
	{
		ksDELETE( pShader );
	}

	return pShader;
}

/************************************************************************************************/
/*
 * �t�@�C������V�F�[�_�[�𐶐�
 * @param	pFileName			�t�@�C����
 * @param	pEntryPoint			�G���g���[�|�C���g
 * @param	shaderModel			�V�F�[�_�[���f��
 * @param	shaderType			�V�F�[�_�[�^�C�v
 * @return						�V�F�[�_�[�v���O�����̃|�C���^
 */
/************************************************************************************************/
KsShaderProgram* KsShaderManagerDX11::createFromResource( const KsChar* pFileName, const KsChar* pEntryPoint, ksSHADER_MODEL_TYPE shaderModel, ksSHADER_TYPE shaderType )
{
	KsShaderProgram*		pShader = findRefInc( pFileName );

	if( pShader )
	{
		return pShader;
	}

	switch( shaderType )
	{
		case ksVERTEX_SHADER:
		{
			// ���_�V�F�[�_�[
			KsVertexShaderDX11*	pShader = new KsVertexShaderDX11( m_pRenderSystem );
			pShader->createFromFile( pFileName, pEntryPoint, shaderModel );
			return pShader;
		}
		case ksPIXEL_SHADER:
		{
			// �s�N�Z���V�F�[�_�[
			KsPixelShaderDX11*	pShader = new KsPixelShaderDX11( m_pRenderSystem );
			pShader->createFromFile( pFileName, pEntryPoint, shaderModel );
			return pShader;
		}
		case ksGEOMETRY_SHADER:
		{
			// �W�I���g���V�F�[�_�[
			return NULL;
		}
		case ksCOMPUTE_SHADER:
		{
			// �R���s���[�g�V�F�[�_�[
			KsComputeShaderDX11*	pShader = new KsComputeShaderDX11( m_pRenderSystem );
			pShader->createFromFile( pFileName, pEntryPoint, shaderModel );
			return pShader;
		}
		default:
			break;
	}

	return NULL;
}

