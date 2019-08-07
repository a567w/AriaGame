/************************************************************************************************/
/** 
 * @file		KsIndexBufferDX11.h
 * @brief		�C���f�b�N�X�o�b�t�@
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
#include "KsDevDX11/device/KsIndexBufferDX11.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/*
 * �C���f�b�N�X�o�b�t�@�𐶐�����
 * @param	pDevice			�f�o�C�X
 * @param	numIndex		�C���f�b�N�X�̐�
 * @param	flags			�t���O
 */
/************************************************************************************************/
KsIndexBufferDX11::KsIndexBufferDX11( KsRenderSystemDX11* pRenderSystem, void* pData, KsUInt32 size, KsUInt32 numIndex, KsUInt32 indexFormat, KsUInt32 flags )
	: m_pRenderSystem( pRenderSystem )
	, m_pIndexBuffer( 0 )
{
	create( pRenderSystem, pData, size, numIndex, indexFormat, flags );
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsIndexBufferDX11::~KsIndexBufferDX11()
{
	ksRELEASE( m_pIndexBuffer );
}

/************************************************************************************************/
/*
 * �C���f�b�N�X�o�b�t�@�𐶐�����
 * @param	pRenderSystem	�`��V�X�e��
 * @param	pData			�f�[�^�ǂݍ��ݗp�̃|�C���^
 * @param	size			�f�[�^�T�C�Y
 * @param	numIndex		�C���f�b�N�X�̐�
 * @param	indexFormat		�C���f�b�N�X�t�H�[�}�b�g
 * @param	flags			�t���O
 * @retval	ksTRUE			��������
 * @retval	ksFALSE			�������s
 */
/************************************************************************************************/
KsBool KsIndexBufferDX11::create( KsRenderSystemDX11* pRenderSystem, void* pData, KsUInt32 size, KsUInt32 numIndex, KsUInt32 indexFormat, KsUInt32 flags )
{
	m_numIndex = numIndex;

	// �C���f�b�N�X�o�b�t�@���쐬����
	// �o�b�t�@���̐ݒ�
	D3D11_BUFFER_DESC	desc;

	// �[���N���A����
	KsZeroMemory( &desc, sizeof(desc) );

	if( ksFMT_INDEX16 == indexFormat )
	{
		m_indexFormatType = ksFMT_INDEX16;
		m_indexSize       = 2;
	}
	else if( ksFMT_INDEX32 == indexFormat )
	{
		m_indexFormatType = ksFMT_INDEX32;
		m_indexSize       = 4;
	}
	else
	{
		KsAssert( 0, "not index format." );
	}

	desc.ByteWidth      = m_indexSize * numIndex;
	desc.Usage          = D3D11_USAGE_DYNAMIC;
	desc.BindFlags      = D3D11_BIND_INDEX_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT hr = E_FAIL;

	if( pData )
	{
		D3D11_SUBRESOURCE_DATA	resource;

		resource.pSysMem          = pData;
		resource.SysMemPitch      = 0;
		resource.SysMemSlicePitch = 0;

		hr = pRenderSystem->getD3DDevice()->CreateBuffer( &desc, &resource, &m_pIndexBuffer );
	}
	else
	{
		hr = pRenderSystem->getD3DDevice()->CreateBuffer( &desc, NULL, &m_pIndexBuffer );
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
void KsIndexBufferDX11::destroy()
{
	delete this;
}

/************************************************************************************************/
/*
 * ���\�[�X���擾����
 * @return					 ���\�[�X
 */
/************************************************************************************************/
void* KsIndexBufferDX11::getBufferResource()
{
	return m_pIndexBuffer;
}

/************************************************************************************************/
/*
 * �C���f�b�N�X�o�b�t�@�����b�N����
 * @param	pContext		�`��R���e�L�X�g
 * @param	flags			���b�N�t���O
 * @return					���b�N�����o�b�t�@�̐擪�|�C���^
 */
/************************************************************************************************/
void* KsIndexBufferDX11::lock( const KsRenderContext* pContext, KsUInt32 flags )
{
#if 0
	void*		pBuffer;

	m_pIndexBuffer->Lock( startIndex*m_indexSize, numIndex*m_indexSize, &pBuffer, flags );

	// �f�[�^�ݒ�
	
	hr = g_pContext->Map( m_pIndexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &m_resource );
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
 * �C���f�b�N�X�o�b�t�@�̃��b�N����������
 */
/************************************************************************************************/
void KsIndexBufferDX11::unlock( const KsRenderContext* pContext )
{
	//g_pContext->Unmap( m_pIndexBuffer, 0 );

	//m_pIndexBuffer->Unlock();
}

/************************************************************************************************/
/*
 * �C���f�b�N�X�o�b�t�@����̓ǂݍ���
 * @param	pContext		�`��R���e�L�X�g
 * @param	pData			�f�[�^�ǂݍ��ݗp�̃|�C���^
 * @param	size			�f�[�^�T�C�Y
 */
/************************************************************************************************/
void KsIndexBufferDX11::read( const KsRenderContext* pContext, void* pData, KsUInt32 size )
{
	((KsRenderContext*)pContext)->read( this, pData, size );
}

/************************************************************************************************/
/*
 * �C���f�b�N�X�o�b�t�@�ւ̏�������
 * @param	pContext		�`��R���e�L�X�g
 * @param	pData			�f�[�^�ǂݍ��ݗp�̃|�C���^
 * @param	size			�f�[�^�T�C�Y
 */
/************************************************************************************************/
void KsIndexBufferDX11::write( const KsRenderContext* pContext, void* pData, KsUInt32 size )
{
#if 0
	void*		pBuffer;
	KsUInt32	length = numIndex*m_indexSize;

	m_pIndexBuffer->Lock( startIndex*m_indexSize, length, &pBuffer, D3DLOCK_READONLY );

	memcpy( pBuffer, pData, length );
	
	m_pIndexBuffer->Unlock();
#endif
}

