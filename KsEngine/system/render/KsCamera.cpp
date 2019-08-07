/************************************************************************************************/
/** 
 * @file		StCamera.h
 * @brief		カメラ
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "StGameSystemManager.h"
#include "StCamera.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
StCamera::StCamera()
{
	//StGameSystemManager*	pSys = StGameSystemManager::instance();

	/* 描画設定 */

	/* タスクタイプをカメラにする */
	m_type  = stTASK_TYPE_CAMERA;

	/* 描画するオーダーを指定(とりあえず全指定) */
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
	/* 視点設定 */
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

	/* 描画設定 */

	/* タスクタイプをカメラにする */
	m_type  = stTASK_TYPE_CAMERA;

	/* 描画するオーダーを指定(とりあえず全指定) */
	m_order = 0xffffffff;

	/* カメラの設定 */
	m_viewport.m_x	  = 0;
	m_viewport.m_y	  = 0;
	m_viewport.m_w	  = pSys->m_mainWindowParam.m_sizeX;
	m_viewport.m_h	  = pSys->m_mainWindowParam.m_sizeY;
	m_viewport.m_near = 0.1f;
	m_viewport.m_far  = 1.0f;
	m_fovy			  = 45.0;
	m_aspect		  = ( (StReal)m_viewport.m_w )/( (StReal)m_viewport.m_h );

#if 1
	// 正射影
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
	// 透視変換
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

	/* ビューポート */
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

	/* 射影設定 */
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

	/* 視点設定 */
	StMatrixLookAtRH( m_viewMatrix, m_eye, m_at, m_up );
	pSys->m_pRenderSystem->setTransform( ksTRANSFORM_VIEW, &m_viewMatrix );
}

}

#endif

