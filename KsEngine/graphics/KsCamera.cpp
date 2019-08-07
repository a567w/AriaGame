/************************************************************************************************/
/** 
 * @file		StCamera.h
 * @brief		�J����
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"
#include "KsCamera.h"
#include "KsRenderSystem.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
KsCamera* KsCamera::s_pActiveCamera = 0;

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/*************************************************************************************************/
KsCamera::KsCamera()
{
	/* �`��ݒ� */
	m_coordinateType = ksCOORD_LEFT;

	/* �^�X�N�^�C�v���J�����ɂ��� */
//	m_type  = ksTASK_TYPE_CAMERA;

	/* �`�悷��I�[�_�[���w��(�Ƃ肠�����S�w��) */
//	m_order = ksTASK_RENDER_ORDER_ALL;

	m_pRenderSystem = NULL;
}

/*************************************************************************************************/
/*
 * �R���X�g���N�^
 * @param	pRenderSystem	�`��V�X�e��
 */
/*************************************************************************************************/
KsCamera::KsCamera( KsRenderSystem* pRenderSystem )
{
	/* �`��ݒ� */
	m_coordinateType = ksCOORD_LEFT;

	/* �^�X�N�^�C�v���J�����ɂ��� */
//	m_type  = ksTASK_TYPE_CAMERA;

	/* �`�悷��I�[�_�[���w��(�Ƃ肠�����S�w��) */
//	m_order = ksTASK_RENDER_ORDER_ALL;

	m_pRenderSystem = pRenderSystem;
}

/*************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/*************************************************************************************************/
KsCamera::~KsCamera()
{
}

/*************************************************************************************************/
/*
 * ���W�n�̃^�C�v���Z�b�g����
 * @param	type			���W�n�̃^�C�v
 */
/*************************************************************************************************/
void KsCamera::setCoordinateType( ksCOORDINATE_TYPE type )
{
	m_coordinateType = type;
}

/*************************************************************************************************/
/*
 * �r���[�|�[�g�̃Z�b�g
 * @param		x		X���W
 * @param		y		X���W
 * @param		w		��
 * @param		h		����
 * @param		near	near�N���b�v�l
 * @param		far		far�N���b�v�l
 */
/*************************************************************************************************/
void KsCamera::setViewport( KsInt32 x, KsInt32 y, KsInt32 w, KsInt32 h, KsReal minZ, KsReal maxZ )
{
	m_viewport.set( x, y, w, h, minZ, maxZ );
	m_updateFlag |= ksVIEWPORT_UPDATE;
}

/*************************************************************************************************/
/*
 * �r���[�|�[�g�̃Z�b�g
 * @param		viewport	�r���[�|�[�g
 */
/*************************************************************************************************/
void KsCamera::setViewport( const KsViewport& viewport )
{
	m_viewport.set( viewport.m_x, viewport.m_y, viewport.m_w, viewport.m_h, viewport.m_minZ, viewport.m_maxZ );
	m_updateFlag |= ksVIEWPORT_UPDATE;
}

/*************************************************************************************************/
/*
 * �����ˉe�s��𐶐�����
 * @param		fovy		����p
 * @param		aspect		�A�X�y�N�g��
 * @param		zNear		�ߋ����l
 * @param		zFar		�������l
 */
/*************************************************************************************************/
void KsCamera::setPerspective( KsReal fovy, KsReal aspect, KsReal zNear, KsReal zFar )
{
	m_fovy   = fovy;
	m_aspect = aspect;
	m_zNear  = zNear;
	m_zFar   = zFar;

	m_projectionType = ksPERSPECTIVE;

	if( m_coordinateType == ksCOORD_LEFT )
	{
		KsMatrixPerspectiveLH( m_projMatrix, m_fovy, m_aspect, m_zNear, m_zFar );
	}
	else
	{
		KsMatrixPerspectiveRH( m_projMatrix, m_fovy, m_aspect, m_zNear, m_zFar );
	}

	m_updateFlag |= ksPROJECTION_UPDATE;
}

/*************************************************************************************************/
/*
 * ���ˉe�s��𐶐�����
 * @param		projMatrix	�v���W�F�N�V�����}�g���b�N�X�ۑ��p
 * @param		left		���t�g
 * @param		right		���C�g
 * @param		bottom		�{�g��
 * @param		top			�g�b�v
 * @param		aspect		�A�X�y�N�g��
 * @param		zNear		�ߋ����l
 * @param		zFar		�������l
 */
/*************************************************************************************************/
void KsCamera::setOrtho( KsReal left, KsReal right, KsReal bottom, KsReal top, KsReal zNear, KsReal zFar )
{
	m_left   = left;
	m_right  = right;
	m_bottom = bottom;
	m_top    = top;
	m_zNear  = zNear;
	m_zFar   = zFar;

	m_projectionType = ksORTHOGRAPHIC;
	m_updateFlag |= ksPROJECTION_UPDATE;
}

/*************************************************************************************************/
/*
 * �J������Look-At���Z�b�g����
 * @param	eye		���_�ʒu
 * @param	target	�^�[�Q�b�g
 * @param	up		up �x�N�g��
 */
/*************************************************************************************************/
void KsCamera::lookAt( const KsVector3d& eye, const KsVector3d& target, const KsVector3d& up )
{
	if( m_coordinateType == ksCOORD_LEFT )
	{
		KsMatrixLookAtLH( m_viewMatrix, eye, target, up );
	}
	else
	{
		KsMatrixLookAtRH( m_viewMatrix, eye, target, up );
	}
	m_updateFlag |= ksVIEWMATRIX_UPDATE;
}

/*************************************************************************************************/
/*
 * �`��J�n
 */
/*************************************************************************************************/
void KsCamera::beginRender()
{
//	KsAssert( m_pRenderSystem != NULL, "renderSystem null pointer\n" );

	if( !m_pRenderSystem )
	{
		return;
	}

	/* �X�V���� */
	update();

	/* �`��J�n */
	//m_pRenderSystem->beginScene( m_clearFlags, m_clearColor, m_clearDepth, m_clearSstencil );
}

/*************************************************************************************************/
/*
 * �`��I��
 */
/*************************************************************************************************/
void KsCamera::endRender()
{
	if( !m_pRenderSystem )
	{
		return;
	}

	/* �`��I�� */
	//m_pRenderSystem->endScene();
}

/*************************************************************************************************/
/*
 * �X�V����
 */
/*************************************************************************************************/
void KsCamera::update()
{
	if( m_updateFlag )
	{
		/* viewport */
		if( m_updateFlag & ksVIEWPORT_UPDATE )
		{

		}

		/* �v���W�F�N�V���� */
		if( m_updateFlag & ksPROJECTION_UPDATE )
		{
			if( m_coordinateType == ksCOORD_LEFT )
			{
				/* ����n */
				if( m_projectionType == ksPERSPECTIVE )
				{
					KsMatrixPerspectiveLH( m_projMatrix, m_fovy, m_aspect, m_zNear, m_zFar );
				}
				else if( m_projectionType == ksORTHOGRAPHIC )
				{
					KsMatrixOrthoLH( m_projMatrix, m_left, m_right, m_bottom, m_top, m_zNear, m_zFar );
				}
			}
			else if( m_coordinateType == ksCOORD_RIGHT )
			{
				/* �E��n */
				if( m_projectionType == ksPERSPECTIVE )
				{
					KsMatrixPerspectiveRH( m_projMatrix, m_fovy, m_aspect, m_zNear, m_zFar );
				}
				else if( m_projectionType == ksORTHOGRAPHIC )
				{
					KsMatrixOrthoRH( m_projMatrix, m_left, m_right, m_bottom, m_top, m_zNear, m_zFar );
				}
			}
		}

		/* �r���[�}�g���b�N�X */
		if( m_updateFlag & ksVIEWMATRIX_UPDATE )
		{
		}

		/* �t���X�^�� */
		if( m_updateFlag & ksFRUSUM_UPDATE )
		{
			
		}

		m_viewProjMatrix = m_viewMatrix * m_projMatrix;

		m_updateFlag = ksNONE_UPDATE;
	}

	if( !m_pRenderSystem )
	{
		return;
	}
}

