/************************************************************************************************/
/** 
 * @file		KsHardwareBufferManagerDX11.cpp
 * @brief		�o�b�t�@�}�l�[�W��
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
#include "KsDevDX11/device/KsHardwareBufferManagerDX11.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsHardwareBufferManagerDX11::KsHardwareBufferManagerDX11( KsRenderSystemDX11* _RenderSystem )
	: m_RenderSystem( _RenderSystem )
{
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsHardwareBufferManagerDX11::~KsHardwareBufferManagerDX11()
{
}

/************************************************************************************************/
/*
 * ���_�o�b�t�@�𐶐�����
 * @param		vertexSize		���_�T�C�Y
 * @param		numVertex		���_��
 * @param		vertexFormat	���_�t�H�[�}�b�g
 * @param		flags			�t���O
 * @return						���_�o�b�t�@�̃|�C���^
 */
/************************************************************************************************/
KsVertexBuffer* KsHardwareBufferManagerDX11::createVertexBuffer( KsUInt32 vertexSize, KsUInt32 numVertex, KsUInt32 vertexFormat, KsUInt32 flags )
{
	return new KsVertexBufferDX11( m_RenderSystem, NULL, vertexSize, numVertex, vertexFormat, flags );
}

/************************************************************************************************/
/*
 * ���_�o�b�t�@�𐶐�����
 * @param		vertexSize		���_�T�C�Y
 * @param		numVertex		���_��
 * @param		vertexFormat	���_�t�H�[�}�b�g
 * @param		flags			�t���O
 * @return						���_�o�b�t�@�̃|�C���^
 */
/************************************************************************************************/
KsVertexBuffer* KsHardwareBufferManagerDX11::createVertexBuffer( void* pData, KsUInt32 vertexSize, KsUInt32 numVertex, KsUInt32 vertexFormat, KsUInt32 flags )
{
	return new KsVertexBufferDX11( m_RenderSystem, pData, vertexSize, numVertex, vertexFormat, flags );
}

/************************************************************************************************/
/*
 * �C���f�b�N�X�o�b�t�@�𐶐�����
 * @param		numIndex		�C���f�b�N�X��
 * @param		flags			�t���O
 * @return						�C���f�b�N�X�o�b�t�@�̃|�C���^
 */
/************************************************************************************************/
KsIndexBuffer* KsHardwareBufferManagerDX11::createIndexBuffer( KsUInt32 numIndex, KsUInt32 indexFormat, KsUInt32 flags )
{
	return new KsIndexBufferDX11( m_RenderSystem, NULL, 0, numIndex, indexFormat, flags );
}

/************************************************************************************************/
/*
 * �C���f�b�N�X�o�b�t�@�𐶐�����
 * @param		numIndex		�C���f�b�N�X��
 * @param		flags			�t���O
 * @return						�C���f�b�N�X�o�b�t�@�̃|�C���^
 */
/************************************************************************************************/
KsIndexBuffer* KsHardwareBufferManagerDX11::createIndexBuffer( void* pData, KsUInt32 size, KsUInt32 numIndex, KsUInt32 indexFormat, KsUInt32 flags )
{
	return new KsIndexBufferDX11( m_RenderSystem, pData, size, numIndex, indexFormat, flags );
}

/************************************************************************************************/
/*
 * �萔�o�b�t�@�𐶐�����
 * @param	pData				[in] �f�[�^�ǂݍ��ݗp�̃|�C���^
 * @param	size				[in] �f�[�^�T�C�Y
 * @param	flags				[in] �t���O
 * @return						�萔�o�b�t�@�̃|�C���^
 */
 /************************************************************************************************/
KsConstantBuffer* KsHardwareBufferManagerDX11::createConstantBuffer( KsUInt32 size, KsUInt32 flags )
{
	return new KsConstantBufferDX11( m_RenderSystem, NULL, size, flags );
}

/************************************************************************************************/
/*
 * �萔�o�b�t�@�𐶐�����
 * @param	size				[in] �o�b�t�@�T�C�Y
 * @param	flags				[in] �t���O
 * @return						�萔�o�b�t�@�̃|�C���^
 */
 /************************************************************************************************/
KsConstantBuffer* KsHardwareBufferManagerDX11::createConstantBuffer( void* pData, KsUInt32 size, KsUInt32 flags )
{
	return new KsConstantBufferDX11( m_RenderSystem, pData, size, flags );
}


