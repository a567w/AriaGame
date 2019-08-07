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
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "StGameSystemManager.h"
#include "StCamera.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
StCamera::StCamera()
{
	//StGameSystemManager*	pSys = StGameSystemManager::instance();

	/* �`��ݒ� */

	/* �^�X�N�^�C�v���J�����ɂ��� */
	m_type  = stTASK_TYPE_CAMERA;

	/* �`�悷��I�[�_�[���w��(�Ƃ肠�����S�w��) */
	m_order = 0xffffffff;
}

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
StCamera::~StCamera()
{
	printf("del came\n");
}

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
void StCamera::beginRender()
{
	/* ���_�ݒ� */
	//Viewport();
	//Perspective();
	//OrthoRH();
	//LookAt();
}
/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
void StCamera::endRender()
{
}


#if 0
/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
KsCameraTask::KsCameraTask()
{
	KsGameSystemManager*	pSys = KsGameSystemManager::instance();

	/* �`��ݒ� */

	/* �^�X�N�^�C�v���J�����ɂ��� */
	m_type  = stTASK_TYPE_CAMERA;

	/* �`�悷��I�[�_�[���w��(�Ƃ肠�����S�w��) */
	m_order = 0xffffffff;

	/* �J�����̐ݒ� */
	m_viewport.m_x	  = 0;
	m_viewport.m_y	  = 0;
	m_viewport.m_w	  = pSys->m_mainWindowParam.m_sizeX;
	m_viewport.m_h	  = pSys->m_mainWindowParam.m_sizeY;
	m_viewport.m_near = 0.1f;
	m_viewport.m_far  = 1.0f;
	m_fovy			  = 45.0;
	m_aspect		  = ( (StReal)m_viewport.m_w )/( (StReal)m_viewport.m_h );

#if 1
	// ���ˉe
	m_eye.x			  = 0.0f;
	m_eye.y			  = 0.0f;
	m_eye.z			  = 1.0f;
	m_at.x			  = 0.0f;
	m_at.y			  = 0.0f;
	m_at.z			  = 0.0f;
	m_up.x			  = 0.0f;
	m_up.y			  = 1.0f;
	m_up.z			  = 0.0f;

	Viewport();
	OrthoRH();
	LookAt();

#else
	// �����ϊ�
	m_eye.x			  = 0.0f;
	m_eye.y			  = 0.5f;
	m_eye.z			  = 3.0f;
	m_at.x			  = 0.0f;
	m_at.y			  = 0.5f;
	m_at.z			  = 0.0f;
	m_up.x			  = 0.0f;
	m_up.y			  = 1.0f;
	m_up.z			  = 0.0f;
	m_right.x		  = 1.0f;
	m_right.y		  = 0.0f;
	m_right.z		  = 0.0f;

	Viewport();
	Perspective();
	LookAt();
#endif
}
/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
void KsCameraTask::Viewport()
{
	KsGameSystemManager*	pSys = KsGameSystemManager::instance();

	/* �r���[�|�[�g */
	pSys->m_pRenderSystem->setViewport( &m_viewport );
}
/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
void KsCameraTask::Perspective()
{
	KsGameSystemManager*	pSys = KsGameSystemManager::instance();

	/* �ˉe�ݒ� */
	StMatrixPerspectiveRH( m_projMatrix, m_fovy, m_aspect, m_viewport.m_near, m_viewport.m_far );
	pSys->m_pRenderSystem->setTransform( ksTRANSFORM_PROJECTION, &m_projMatrix );
}
/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
void KsCameraTask::OrthoRH()
{
	KsGameSystemManager*	pSys = KsGameSystemManager::instance();

	StMatrixOrthoRH( m_projMatrix, 0, (StReal)m_viewport.m_w, (StReal)m_viewport.m_h, 0, m_viewport.m_near, m_viewport.m_far );
	pSys->m_pRenderSystem->setTransform( ksTRANSFORM_PROJECTION, &m_projMatrix );
}
/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
void KsCameraTask::LookAt()
{
	KsGameSystemManager*	pSys = KsGameSystemManager::instance();

	/* ���_�ݒ� */
	StMatrixLookAtRH( m_viewMatrix, m_eye, m_at, m_up );
	pSys->m_pRenderSystem->setTransform( ksTRANSFORM_VIEW, &m_viewMatrix );
}

}

#endif

