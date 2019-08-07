/************************************************************************************************/
/** 
 * @file		KsFreeCamera.h
 * @brief		フリーカメラ
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSFREECAMERA_H__
#define __KSFREECAMERA_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsFreeCamera
 * @brief		フリーカメラ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsFreeCamera : public KsCamera
{
	public:
		/** 
		 * コンストラクタ
		 */
								KsFreeCamera();

		/**
		 * デストラクタ
		 */
		virtual					~KsFreeCamera();

		/**
		 * カメラの更新処理
		 */
		virtual void			update();

	protected:
		/**
		 * マウス差分更新
		 */
		void					updateMouseDelta();

		void					constrainToBoundary( KsVector3d* pV );

		/**
		 * マウス更新
		 */
		void					updateMouse( const KsGameMouse& mouse );

	private:
		KsVector3d				m_position;
		KsVector3d				m_target;
		KsBool					m_isRotation;		// 右ボタンをドラッグ中かどうかのフラグ（0:非ドラッグ中,1:ドラッグ中）
		KsBool					m_isTranslate;		// 左ボタンをドラッグ中かどうかのフラグ（0:非ドラッグ中,1:ドラッグ中）
		KsBool					m_isDistance;		// 距離変更
		KsVector2d				m_rotVelocity;
		KsVector2d				m_mouseDelta;
		KsVector2d				m_mousePos;
		KsReal					m_rotationScaler;
		KsReal					m_framesToSmoothMouseData;
		KsReal					m_pitchAngle;
		KsReal					m_yawAngle;
		KsInt32					m_mousePosX;		// 最後に記録されたマウスカーソルのＸ座標
		KsInt32					m_mousePosY;		// 最後に記録されたマウスカーソルのＸ座標

		KsVector3d				m_vMinBoundary;
		KsVector3d				m_vMaxBoundary;

		KsVector3d				m_translate;		//
		KsVector3d				m_mousePosLast;		// 
		KsReal					m_pitch;			// Ｘ軸を中心とする回転角度
		KsReal					m_yaw;				// Ｙ軸を中心とする回転角度
		KsReal					m_distance;			// カメラの距離
		KsReal					m_moveScaler;

		KsVector3d				m_direction;
		KsMatrix4x4				m_cameraRot;
};


#endif		/* __KSFREECAMERA_H__ */

