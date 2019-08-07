/************************************************************************************************/
/** 
 * @file		KsTextureDX11.cpp
 * @brief		DirectX�p�e�N�X�`��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsDevDX11/KsDevDX11PreCompile.h"
#include "KsDevDX11/device/KsTextureDX11.h"
#include "KsDevDX11/device/KsTextureManagerDX11.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
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

	// �����`�F�b�N
	KsAssert( ksSUCCEEDED( hr ), "ERROR:CreateTexture" );

#if 0
	D3D11_TEXTURE2D_DESC	desc;
	m_pD3D11Texture = reinterpret_cast<ID3D11Texture2D*>( pResource );

	// �e�N�X�`���ڍׂ��擾����
	m_pD3D11Texture->GetDesc( &desc );

	// �e�N�X�`���ݒ�
	m_id            = KsCrc32( (KsUInt8*)pFileName );
	m_name          = pFileName;
	m_width         = static_cast<KsUInt16>( desc.Width );
	m_height        = static_cast<KsUInt16>( desc.Height );
	m_numMipmap     = static_cast<KsUInt32>( desc.MipLevels - 1 );
	m_mipLevels     = static_cast<KsUInt32>( desc.MipLevels );

	// ShaderResourceView���쐬����
	D3D11_SHADER_RESOURCE_VIEW_DESC	srvDesc;
	
	KsZeroMemory( &srvDesc, sizeof(srvDesc) );

	srvDesc.Format                    = desc.Format;
	srvDesc.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels       = desc.MipLevels;

	hr = pRenderSystem->getD3DDevice()->CreateShaderResourceView( m_pD3D11Texture, &srvDesc, &m_pShaderResourceView );

	KsAssert( ksSUCCEEDED( hr ), "CreateShaderResourceView" );
#endif

	/* �e�N�X�`���̃t���O�Z�b�g */
	m_flags  = flags;
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 * @param		pImage			�C���[�W�t�@�C��
 * @param		flags			�ǂݍ��ݕ��@�̃t���O
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
 * �R���X�g���N�^
 * @param		pD3D11Texture		Direct3D�e�N�X�`��
 * @param		pShaderView			�V�F�[�_�[���\�[�X�r���[
 */
/************************************************************************************************/
KsTextureDX11::KsTextureDX11( ID3D11Texture2D* pD3D11Texture, ID3D11ShaderResourceView* pShaderResourceView )
	: m_pD3D11Texture( pD3D11Texture )
	, m_pShaderResourceView( pShaderResourceView )
	, m_pImage( 0 )
{
	D3D11_TEXTURE2D_DESC	desc;

	// �e�N�X�`���ڍׂ��擾����
	m_pD3D11Texture->GetDesc( &desc );

	// �e�N�X�`���ݒ�
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

	/* �C���[�W�f�[�^�J�� */
	ksDELETE( m_pImage );
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsTextureDX11::destroy()
{
	/* �e�N�X�`���}�l�[�W�����g�p���Ă��邩�ǂ����̃`�F�b�N */
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
		/* �Q�ƃJ�E���g�������܂� */
		dec();
	}
}

/************************************************************************************************/
/*
 * �e�N�X�`�����A�N�e�B�u�ɂ���
 */
/************************************************************************************************/
void KsTextureDX11::active()
{

}

/************************************************************************************************/
/*
 * ���\�[�X���擾����
 * @return							 ���\�[�X
 */
/************************************************************************************************/
void* KsTextureDX11::getBufferResource()
{
	return NULL;
}

/************************************************************************************************/
/*
 * �o�b�t�@�����b�N����
 * @param	pContext				�`��R���e�L�X�g
 * @param	flags					���b�N�t���O
 * @return							���b�N�����o�b�t�@�̐擪�|�C���^
 */
 /************************************************************************************************/
void* KsTextureDX11::lock( const KsRenderContext* pContext, KsUInt32 flags )
{
	return NULL;
}

/************************************************************************************************/
/*
 * �o�b�t�@�̃��b�N����������
 * @param	pContext				�`��R���e�L�X�g
 */
 /************************************************************************************************/
void KsTextureDX11::unlock( const KsRenderContext* pContext )
{
}

/************************************************************************************************/
/*
 * �o�b�t�@����̓ǂݍ���
 * @param	pContext				�`��R���e�L�X�g
 * @param	pData					�f�[�^�ǂݍ��ݗp�̃|�C���^
 * @param	size					�f�[�^�T�C�Y
 */
 /************************************************************************************************/
void KsTextureDX11::read( const KsRenderContext* pContext, void* pData, KsUInt32 size )
{
}

/************************************************************************************************/
/*
 * �o�b�t�@�ւ̏�������
 * @param	pContext				�`��R���e�L�X�g
 * @param	pData					�f�[�^�ǂݍ��ݗp�̃|�C���^
 * @param	size					�f�[�^�T�C�Y
 */
 /************************************************************************************************/
void KsTextureDX11::write( const KsRenderContext* pContext, void* pData, KsUInt32 size )
{
}

