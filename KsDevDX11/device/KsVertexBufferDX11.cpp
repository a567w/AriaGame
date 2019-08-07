/************************************************************************************************/
/** 
 * @file		KsVertexBufferDX11.h
 * @brief		���_�o�b�t�@
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
#include "KsDevDX11/device/KsVertexBufferDX11.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/*
 * �R���X�g���N�^(���_�o�b�t�@�𐶐�����)
 * @param	pRenderSystem	�`��V�X�e��
 * @param	pData			�f�[�^�ǂݍ��ݗp�̃|�C���^
 * @param	vertexSize		���_�T�C�Y
 * @param	numVertex		���_��
 * @param	vertexFormat	���_�t�H�[�}�b�g
 * @param	flags			�t���O
 */
/************************************************************************************************/
KsVertexBufferDX11::KsVertexBufferDX11( KsRenderSystemDX11* pRenderSystem, void* pData, KsUInt32 vertexSize, KsUInt32 numVertex, KsUInt32 vertexFormat, KsUInt32 flags )
	: m_pRenderSystem( pRenderSystem )
	, m_pVertexBuffer( 0 )
{
	create( pRenderSystem, pData, vertexSize, numVertex, vertexFormat, flags );
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsVertexBufferDX11::~KsVertexBufferDX11()
{
	ksRELEASE( m_pVertexBuffer );
}

/************************************************************************************************/
/*
 * ���_�o�b�t�@�𐶐�����
 * @param	pRenderSystem	�`��V�X�e��
 * @param	pData			�f�[�^�ǂݍ��ݗp�̃|�C���^
 * @param	vertexSize		���_�T�C�Y
 * @param	numVertex		���_��
 * @param	vertexFormat	���_�t�H�[�}�b�g
 * @param	flags			�t���O
 * @retval	ksTRUE			��������
 * @retval	ksFALSE			�������s
 */
/************************************************************************************************/
KsBool KsVertexBufferDX11::create( KsRenderSystemDX11* pRenderSystem, void* pData, KsUInt32 vertexSize, KsUInt32 numVertex, KsUInt32 vertexFormat, KsUInt32 flags )
{
	m_vertexSize   = vertexSize;
	m_numVertex    = numVertex;
	m_vertexFormat = vertexFormat;

	// ���_�o�b�t�@���쐬����
	// �o�b�t�@���̐ݒ�
	D3D11_BUFFER_DESC	desc;

	// �[���N���A����
	KsZeroMemory( &desc, sizeof(desc) );

	desc.ByteWidth      = m_vertexSize * m_numVertex;
	desc.Usage          = D3D11_USAGE_DEFAULT;
	desc.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = flags;

	if( flags == ksCPU_ACCESS_WRITE )
	{
		desc.Usage = D3D11_USAGE_DYNAMIC;
	}

	HRESULT hr = E_FAIL;

	if( pData )
	{
		D3D11_SUBRESOURCE_DATA	resource;
		
		KsZeroMemory( &resource, sizeof(resource) );

		resource.pSysMem          = pData;
		resource.SysMemPitch      = 0;
		resource.SysMemSlicePitch = 0;

		hr = pRenderSystem->getD3DDevice()->CreateBuffer( &desc, &resource, &m_pVertexBuffer );
	}
	else
	{
		hr = pRenderSystem->getD3DDevice()->CreateBuffer( &desc, NULL, &m_pVertexBuffer );
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
void KsVertexBufferDX11::destroy()
{
	delete this;
}

/************************************************************************************************/
/*
 * ���\�[�X���擾����
 * @return					 ���\�[�X
 */
/************************************************************************************************/
void* KsVertexBufferDX11::getBufferResource()
{
	return m_pVertexBuffer;
}

/************************************************************************************************/
/*
 * ���_�o�b�t�@�����b�N����
 * @param	pContext		�`��R���e�L�X�g
 * @param	flags			���b�N�t���O
 * @return					���b�N�����o�b�t�@�̐擪�|�C���^
 */
/************************************************************************************************/
void* KsVertexBufferDX11::lock( const KsRenderContext* pContext, KsUInt32 flags )
{
#if 0
	void*		pBuffer;

	m_pVertexBuffer->Lock( startIndex*m_indexSize, numIndex*m_indexSize, &pBuffer, flags );

	// �f�[�^�ݒ�
	
	hr = g_pContext->Map( m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &m_resource );
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
 * ���_�o�b�t�@�̃��b�N����������
 */
/************************************************************************************************/
void KsVertexBufferDX11::unlock( const KsRenderContext* pContext )
{
	//g_pContext->Unmap( m_pVertexBuffer, 0 );

	//m_pVertexBuffer->Unlock();
}

/************************************************************************************************/
/*
 * ���_�o�b�t�@����̓ǂݍ���
 * @param	pContext		�`��R���e�L�X�g
 * @param	pData			�f�[�^�ǂݍ��ݗp�̃|�C���^
 * @param	size			�f�[�^�T�C�Y
 */
/************************************************************************************************/
void KsVertexBufferDX11::read( const KsRenderContext* pContext, void* pData, KsUInt32 size )
{
	((KsRenderContext*)pContext)->read( this, pData, size );
}

/************************************************************************************************/
/*
 * ���_�o�b�t�@�ւ̏�������
 * @param	pContext		�`��R���e�L�X�g
 * @param	pData			�f�[�^�ǂݍ��ݗp�̃|�C���^
 * @param	size			�f�[�^�T�C�Y
 */
/************************************************************************************************/
void KsVertexBufferDX11::write( const KsRenderContext* pContext, void* pData, KsUInt32 size )
{
#if 0
	void*		pBuffer;
	KsUInt32	length = numIndex*m_indexSize;

	m_pVertexBuffer->Lock( startIndex*m_indexSize, length, &pBuffer, D3DLOCK_READONLY );

	memcpy( pBuffer, pData, length );
	
	m_pVertexBuffer->Unlock();
#endif
}

