/************************************************************************************************/
/** 
 * @file		KsMeshPart.cpp
 * @brief		���b�V���p�[�c
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"

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
KsMeshPart::KsMeshPart()
	: m_pIndexBuffer( 0 )
	, m_pVertexBuffer( 0 )
	, m_numVertices( 0 )
	, m_primitiveCount( 0 )
	, m_startIndex( 0 )
	, m_vertexOffset( 0 )
	, m_pEffect( 0 )
	, m_numPallet( 0 )
	, m_pPallet( 0 )
{
}

/************************************************************************************************/
/*
 * �R���X�g���N�^( ���b�V���p�[�c�𐶐����܂��B)
 * @param	pEffect			�g�p����G�t�F�N�g�f�[�^
 * @param	pIndexBuffer	���b�V�������̃C���f�b�N�X �o�b�t�@�[
 * @param	pVertexBuffer	���b�V�� �p�[�c�̒��_�o�b�t�@�[
 * @param	pInputLayout	�C���v�b�g���C�A�E�g
 * @param	numVertices		�`��Ăяo�����Ɏg�p����钸�_�̐�
 * @param	primitiveCount	�����_�����O����v���~�e�B�u�̐�
 * @param	startIndex		�C���f�b�N�X�z��̒��Œ��_�̓ǂݎ����J�n����ʒu
 * @param	vertexOffset	���_�o�b�t�@�[�̍ŏ㕔����̃I�t�Z�b�g
 */
/************************************************************************************************/
KsMeshPart::KsMeshPart( KsEffect*		pEffect,
						KsIndexBuffer*	pIndexBuffer,
						KsVertexBuffer*	pVertexBuffer,
						KsInputLayout*	pInputLayout,
						KsInt32	numVertices,
						KsInt32	primitiveCount,
						KsInt32	startIndex,
						KsInt32 vertexOffset )
	: m_pEffect( pEffect )
	, m_pIndexBuffer( pIndexBuffer )
	, m_pVertexBuffer( pVertexBuffer )
	, m_pInputLayout( pInputLayout )
	, m_numVertices( numVertices )
	, m_primitiveCount( primitiveCount )
	, m_startIndex( startIndex )
	, m_vertexOffset( vertexOffset )
	, m_numPallet( 0 )
	, m_pPallet( 0 )
{
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsMeshPart::~KsMeshPart()
{
	destroy();
}

/************************************************************************************************/
/*
 * ���b�V���p�[�c�𐶐����܂��B
 * @param	pEffect			�g�p����G�t�F�N�g�f�[�^
 * @param	pIndexBuffer	���b�V�������̃C���f�b�N�X �o�b�t�@�[
 * @param	pVertexBuffer	���b�V�� �p�[�c�̒��_�o�b�t�@�[
 * @param	pInputLayout	�C���v�b�g���C�A�E�g
 * @param	numVertices		�`��Ăяo�����Ɏg�p����钸�_�̐�
 * @param	primitiveCount	�����_�����O����v���~�e�B�u�̐�
 * @param	startIndex		�C���f�b�N�X�z��̒��Œ��_�̓ǂݎ����J�n����ʒu
 * @param	vertexOffset	���_�o�b�t�@�[�̍ŏ㕔����̃I�t�Z�b�g
 */
/************************************************************************************************/
void KsMeshPart::create(  KsEffect* pEffect, KsIndexBuffer* pIndexBuffer, KsVertexBuffer* pVertexBuffer, KsInputLayout*	pInputLayout, KsInt32 numVertices, KsInt32 primitiveCount, KsInt32 startIndex, KsInt32 vertexOffset )
{
	m_pEffect        = pEffect;
	m_pIndexBuffer   = pIndexBuffer;	
	m_pVertexBuffer  = pVertexBuffer;
	m_pInputLayout   = pInputLayout;
	m_numVertices    = numVertices;
	m_primitiveCount = primitiveCount;
	m_startIndex     = startIndex;
	m_vertexOffset   = vertexOffset;	
}

/************************************************************************************************/
/*
 * �}�g���b�N�X�p���b�g�𐶐����܂��B
 * @param	numPallet		�}�g���b�N�X�p���b�g��
 * @param	pPallet			�}�g���b�N�X�p���b�g
 */
/************************************************************************************************/
void KsMeshPart::createPallet( KsInt32 numPallet, KsInt32* pPallet )
{
	if( 0 < numPallet )
	{
		m_numPallet = numPallet;
		m_pPallet   = new KsInt32 [ numPallet ];

		KsMemCopy( m_pPallet, pPallet, m_numPallet * sizeof(KsInt32) );
	}
}

/************************************************************************************************/
/*
 * ���b�V���p�[�c��j�����܂��B
 */
 /************************************************************************************************/
void KsMeshPart::destroy()
{
	ksDELETE( m_pIndexBuffer );
	ksDELETE( m_pVertexBuffer );
	ksDELETE( m_pPallet );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsMeshPart::updateParameter( KsModelParameter* pParameter )
{
	for( KsUInt32 i=0; i<m_vpBones.size(); i++ )
	{
		const KsBone*	pBone = m_vpBones[ i ];

		pParameter->Model.MatrixPalette[ i ] = pBone->m_skinTransform;
		pParameter->Model.MatrixPalette[ i ].transpose();
	}
}

/************************************************************************************************/
/*
 * �`�揈��
 * @param	pRenderContext	�`��R���e�L�X�g
 */
/************************************************************************************************/
void KsMeshPart::draw( KsRenderContext* pRenderContext, KsModelParameter* pParameter )
{
	updateParameter( pParameter );

	KsUInt32		stride = m_pVertexBuffer->getVertexSize();
	KsUInt32		offset = 0;

	pRenderContext->setInputLayout( m_pInputLayout );
	pRenderContext->setVertexBuffers( 0, 1, m_pVertexBuffer, &stride, &offset );
	pRenderContext->setIndexBuffer( m_pIndexBuffer, m_pIndexBuffer->getIndexFormatType(), 0 );
	pRenderContext->setPrimitiveTopology( KS_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	// �V�F�_�[���Z�b�g����
	m_pEffect->setShader( pRenderContext, pParameter );

	pRenderContext->drawIndexed( m_primitiveCount, 0, 0 );
}

