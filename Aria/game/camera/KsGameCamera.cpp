/************************************************************************************************/
/** 
 * @file		KsGameCamera.cpp
 * @brief		Game�J����
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsGameCamera.h"
#include "KsGameSystem.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsGame2DCamera::KsGame2DCamera()
{
	KsGameSystem*	pGameSystem = KsGetGS();
	KsInt32		width       = pGameSystem->getWindowWidth();
	KsInt32		height      = pGameSystem->getWindowHeight();
	
	/* �`��V�X�e�����Z�b�g */
	m_pRenderSystem = KsGetRS();

	/* �`�悷��I�[�_�[���w�� */
	m_order = ksTASK_RENDER_ORDER_ALL;

	setViewport( 0, 0, width, height, 0.0f, 1.0f );
	setOrtho( 0.0f, 0.0f, 1.0f, 1.0f, 0.1f, 1.0f );
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsGame2DCamera::~KsGame2DCamera()
{
}

/************************************************************************************************/
/*
 * �`��J�n
 */
/************************************************************************************************/
void KsGame2DCamera::beginRender()
{
	if( !m_pRenderSystem )
	{
		return;
	}

	/* �X�V���� */
	update();

	/* viewport */
	m_pRenderSystem->setViewport( &m_viewport );
		
	/* �v���W�F�N�V���� */
	m_pRenderSystem->setTransform( ksTRANSFORM_PROJECTION, &m_projMatrix );
		
	/* �r���[�}�g���b�N�X */
	m_pRenderSystem->setTransform( ksTRANSFORM_VIEW, &m_viewMatrix );		
}

/************************************************************************************************/
/*
 * �`��I��
 */
/************************************************************************************************/
void KsGame2DCamera::endRender()
{
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsGame3DCamera::KsGame3DCamera()
{
	KsGameSystem*	pGameSystem = KsGetGS();
	KsInt32		width       = pGameSystem->getWindowWidth();
	KsInt32		height      = pGameSystem->getWindowHeight();
	
	/* �`��V�X�e�����Z�b�g */
	m_pRenderSystem = KsGetRS();

	/* �`�悷��I�[�_�[���w�� */
	m_order = ksTASK_RENDER_ORDER_ALL;

	setViewport( 0, 0, width, height, 0.0f, 1.0f );
	setPerspective( ksDEG( 45.0f ), 1.0f, 0.1f, 500.0f );

	KsVector3d eye( 2.0f, 2.0f, -5.0f );
	KsVector3d target(0.0f, 0.0f, 0.0f);
	KsVector3d up(0.0f, 1.0f, 0.0f);

	lookAt( target, eye, up );

#if 0
	D3DXVECTOR3 pos( 2.0f, 2.0f, -5.0f );
	D3DXVECTOR3 pnt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);


	D3DXMatrixLookAtLH(&matView, &pos, &pnt, &up);
    D3DXMatrixPerspectiveFovLH(&mProjection, D3DXToRadian(60.0f), 1.0f, 0.0f, 1.0f);

    m_pD3DDevice->SetTransform( D3DTS_VIEW, &matView );
    m_pD3DDevice->SetTransform( D3DTS_PROJECTION, &mProjection );
#endif

}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsGame3DCamera::~KsGame3DCamera()
{
}

/************************************************************************************************/
/*
 * �`��J�n
 */
/************************************************************************************************/
void KsGame3DCamera::beginRender()
{
	if( !m_pRenderSystem )
	{
		return;
	}

	/* �X�V���� */
	update();

	/* viewport */
	m_pRenderSystem->setViewport( &m_viewport );
		
	/* �v���W�F�N�V���� */
	m_pRenderSystem->setTransform( ksTRANSFORM_PROJECTION, &m_projMatrix );
		
	/* �r���[�}�g���b�N�X */
	m_pRenderSystem->setTransform( ksTRANSFORM_VIEW, &m_viewMatrix );		
}

/************************************************************************************************/
/*
 * �`��I��
 */
/************************************************************************************************/
void KsGame3DCamera::endRender()
{
}
