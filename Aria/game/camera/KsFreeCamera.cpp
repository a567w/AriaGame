/************************************************************************************************/
/** 
 * @file		KsFreeCamera.cpp
 * @brief		フリーカメラ
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "Aria/KsGamePreCompile.h"
#include "Aria/game/camera/KsFreeCamera.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsFreeCamera::KsFreeCamera()
{
	m_position.set( 0.0f, 35.0f, -54.0f );
	m_target.set( 0.0f, 22.0f, 0.0f );

	KsGameSystem*	pGameSystem = KsGameSystem::getInstancePtr();

	// ビューポート設定
	setViewport( 0, 0, 1280, 720, 0.0f, 1.0f );

	// プロジェクション設定( 1-zにするのでこっちをつかう)
	//setPerspective( ksDEG( 45.0f ), pGameSystem->getWindowAspectRatio(), 0.05f, 1500.0f );
	setPerspective( ksDEG( 45.0f ), pGameSystem->getWindowAspectRatio(), 1500.0f, 0.05f );
	
	// ビューマトリックス設定	
	lookAt( m_position, m_target, KsVector3d::UP );

	KsCamera::update();

	m_rotVelocity = KsVector2d::ZERO;
	m_mouseDelta  = KsVector2d::ZERO;
	m_mousePos    = KsVector2d::ZERO;

	m_moveScaler     = 0.25f;
	m_rotationScaler = 0.005f;
	m_framesToSmoothMouseData = 2.0f;

	m_isRotation  = ksFALSE;
	m_isTranslate = ksFALSE;

	m_pitchAngle  = 0.0f;
	m_yawAngle    = 0.0f;

	m_mousePosX   = 0;
	m_mousePosY   = 0;

	m_pitch = ksDEG( -30.0f );
	m_yaw   = ksDEG( 180.0f );

	m_direction.set( 0.0f, 0.0f, 54.0f );
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsFreeCamera::~KsFreeCamera()
{
}

/************************************************************************************************/
/*
 * カメラの更新処理
 */
/************************************************************************************************/
void KsFreeCamera::update()
{
	KsGamePadManager* pPadManager = KsGamePadManager::getInstancePtr();

	const KsGameMouse mouse = pPadManager->getGameMouse();

	// マウスの更新処理
	updateMouse( mouse );

	//if( m_bClipToBoundary )
	//	ConstrainToBoundary( &m_vEye );

	KsVector3d		eye;
	KsVector3d		target;

	KsQuaternion	cameraRot = KsQuaternion::CreateFromYawPitchRoll( m_yaw, m_pitch, 0.0f );
	m_position  = KsVector3d::Transform( &m_direction, &cameraRot );

	eye    = m_position - m_translate;
	target = m_target   - m_translate;

	// ビューマトリックス設定	
	lookAt( eye, target, KsVector3d::UP );

	m_viewProjMatrix = m_viewMatrix * m_projMatrix;

	KsCamera::update();
}

/************************************************************************************************/
/*
 * マウス差分更新
 */
/************************************************************************************************/
void KsFreeCamera::updateMouseDelta()
{
	KsGamePadManager* pPadManager = KsGamePadManager::getInstancePtr();

	const KsGameMouse mouse = pPadManager->getGameMouse();

	KsReal			fPercentOfNew = 1.0f / m_framesToSmoothMouseData;
	KsReal			fPercentOfOld = 1.0f - fPercentOfNew;
	KsVector2d		curMousePos( (KsReal)mouse.getPosX(), (KsReal)mouse.getPosY() );
	KsVector2d		curMouseDelta;

	curMouseDelta = curMousePos - m_mousePos;

	m_mousePos     = curMousePos;

	m_mouseDelta.x = m_mouseDelta.x * fPercentOfOld + curMouseDelta.x * fPercentOfNew;
	m_mouseDelta.y = m_mouseDelta.y * fPercentOfOld + curMouseDelta.y * fPercentOfNew;

	m_rotVelocity  = m_mouseDelta * m_rotationScaler;
}

//--------------------------------------------------------------------------------------
// Clamps pV to lie inside m_vMinBoundary & m_vMaxBoundary
//--------------------------------------------------------------------------------------
void KsFreeCamera::constrainToBoundary( KsVector3d* pV )
{
	// Constrain vector to a bounding box 
	pV->x = KsMax( pV->x, m_vMinBoundary.x );
	pV->y = KsMax( pV->y, m_vMinBoundary.y );
	pV->z = KsMax( pV->z, m_vMinBoundary.z );

	pV->x = KsMin( pV->x, m_vMaxBoundary.x );
	pV->y = KsMin( pV->y, m_vMaxBoundary.y );
	pV->z = KsMin( pV->z, m_vMaxBoundary.z );
}

/************************************************************************************************/
/*
 * マウス更新
 */
/************************************************************************************************/
void KsFreeCamera::updateMouse( const KsGameMouse& mouse )
{
	//-------------------------------------------------------------------------
	// マウス左ボタン
	//-------------------------------------------------------------------------
	if( mouse.isLeftButtonDown() )
	{
		// マウス左ボタンが押された
		if( !m_isRotation )
		{
			m_mousePosLast.x = (KsReal)mouse.getPosX();
			m_mousePosLast.y = (KsReal)mouse.getPosY();
		}

		m_isRotation = ksTRUE;
	}
	else if( mouse.isLeftButtonUp() )
	{
		// マウス左ボタンが離された
		m_isRotation = ksFALSE;
	}

	//-------------------------------------------------------------------------
	// マウス右ボタン
	//-------------------------------------------------------------------------
	if( mouse.isRightButtonDown() )
	{
		// マウス右ボタンが押された
		if( !m_isTranslate )
		{
			m_mousePosLast.x = (KsReal)mouse.getPosX();
			m_mousePosLast.y = (KsReal)mouse.getPosY();
		}
		m_isTranslate = ksTRUE;
	}
	else if( mouse.isRightButtonUp() )
	{
		// マウス右ボタンが離された
		m_isTranslate = ksFALSE;
	}

	//-------------------------------------------------------------------------
	// ホイールが操作された
	//-------------------------------------------------------------------------
	if( mouse.isWheel() )
	{
		m_isDistance = ksFALSE;
	}
	


	KsReal		px = (KsReal)mouse.getPosX();
	KsReal		py = (KsReal)mouse.getPosY();
	KsReal		dx = ( px - m_mousePosLast.x );
	KsReal		dy = ( py - m_mousePosLast.y );

	// カメラの距離を変更する
	if( m_isDistance )
	{
		//m_mousePosLast.z;
	}

	// マウスによるカメラの回転処理
	if( m_isRotation )
	{
		m_pitch -= dy * m_rotationScaler;

		m_pitch = KsMax( -ksHALF_PI, m_pitch );
		m_pitch = KsMin( +ksHALF_PI, m_pitch );

		m_yaw   -= dx * m_rotationScaler;
	}

	//-------------------------------------------------------------------------
	// 並行移動処理
	//-------------------------------------------------------------------------
	if( m_isTranslate )
	{
		m_translate.x -= dx * m_moveScaler;
		m_translate.y += dy * m_moveScaler;
	}

	//-------------------------------------------------------------------------
	// 現在のマウス座標を記録
	//-------------------------------------------------------------------------
	m_mousePosLast.x = (KsReal)mouse.getPosX();
	m_mousePosLast.y = (KsReal)mouse.getPosY();
	m_mousePosLast.z = (KsReal)mouse.getPosZ();
}



