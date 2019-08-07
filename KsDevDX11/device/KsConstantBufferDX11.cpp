/************************************************************************************************/
/** 
 * @file		KsConstantBufferDX11.cpp
 * @brief		�萔�o�b�t�@
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
#include "KsDevDX11/device/KsConstantBufferDX11.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/*
 * �R���X�g���N�^
 * @param	pRenderSystem	�`��V�X�e��
 * @param	pData			�f�[�^�ǂݍ��ݗp�̃|�C���^
 * @param	size			�f�[�^�T�C�Y
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
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsConstantBufferDX11::~KsConstantBufferDX11()
{
	ksRELEASE( m_pConstantBuffer );
}

/************************************************************************************************/
/*
 * �萔�o�b�t�@�𐶐�����
 * @param	pRenderSystem	�`��V�X�e��
 * @param	pData			�f�[�^�ǂݍ��ݗp�̃|�C���^
 * @param	size			�f�[�^�T�C�Y
 * @param	flags			�t���O
 * @retval	ksTRUE			��������
 * @retval	ksFALSE			�������s
 */
/************************************************************************************************/
KsBool KsConstantBufferDX11::create( KsRenderSystemDX11* pRenderSystem, void* pData, KsUInt32 size, KsUInt32 flags )
{
	// �萔�o�b�t�@���쐬����
	// �o�b�t�@���̐ݒ�
	D3D11_BUFFER_DESC	desc;

	// �[���N���A����
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
 * �j������
 */
/************************************************************************************************/
void KsConstantBufferDX11::destroy()
{
	delete this;
}

/************************************************************************************************/
/*
 * ���\�[�X���擾����
 * @return					 ���\�[�X
 */
/************************************************************************************************/
void* KsConstantBufferDX11::getBufferResource()
{
	return m_pConstantBuffer;
}

/************************************************************************************************/
/*
 * �萔�o�b�t�@�����b�N����
 * @param	pContext		�`��R���e�L�X�g
 * @param	flags			���b�N�t���O
 * @return					���b�N�����o�b�t�@�̐擪�|�C���^
 */
/************************************************************************************************/
void* KsConstantBufferDX11::lock( const KsRenderContext* pContext, KsUInt32 flags )
{
	return NULL;
}

/************************************************************************************************/
/*
 * �萔�o�b�t�@�̃��b�N����������
 */
/************************************************************************************************/
void KsConstantBufferDX11::unlock( const KsRenderContext* pContext )
{
}

/************************************************************************************************/
/*
 * �萔�o�b�t�@����̓ǂݍ���
 * @param	pContext		�`��R���e�L�X�g
 * @param	pData			�f�[�^�ǂݍ��ݗp�̃|�C���^
 * @param	size			�f�[�^�T�C�Y
 */
/************************************************************************************************/
void KsConstantBufferDX11::read( const KsRenderContext* pContext, void* pData, KsUInt32 size )
{
}

/************************************************************************************************/
/*
 * �萔�o�b�t�@�ւ̏�������
 * @param	pContext		�`��R���e�L�X�g
 * @param	pData			�f�[�^�ǂݍ��ݗp�̃|�C���^
 * @param	size			�f�[�^�T�C�Y
 */
/************************************************************************************************/
void KsConstantBufferDX11::write( const KsRenderContext* pContext, void* pData, KsUInt32 size )
{

}

