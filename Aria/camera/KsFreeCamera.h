/************************************************************************************************/
/** 
 * @file		KsFreeCamera.h
 * @brief		�t���[�J����
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSFREECAMERA_H__
#define __KSFREECAMERA_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsFreeCamera
 * @brief		�t���[�J����
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsFreeCamera : public KsCamera
{
	public:
		/** 
		 * �R���X�g���N�^
		 */
								KsFreeCamera();

		/**
		 * �f�X�g���N�^
		 */
		virtual					~KsFreeCamera();

		/**
		 * �J�����̍X�V����
		 */
		virtual void			update();

	protected:
		/**
		 * �}�E�X�����X�V
		 */
		void					updateMouseDelta();

		void					constrainToBoundary( KsVector3d* pV );

		/**
		 * �}�E�X�X�V
		 */
		void					updateMouse( const KsGameMouse& mouse );

	private:
		KsVector3d				m_position;
		KsVector3d				m_target;
		KsBool					m_isRotation;		// �E�{�^�����h���b�O�����ǂ����̃t���O�i0:��h���b�O��,1:�h���b�O���j
		KsBool					m_isTranslate;		// ���{�^�����h���b�O�����ǂ����̃t���O�i0:��h���b�O��,1:�h���b�O���j
		KsBool					m_isDistance;		// �����ύX
		KsVector2d				m_rotVelocity;
		KsVector2d				m_mouseDelta;
		KsVector2d				m_mousePos;
		KsReal					m_rotationScaler;
		KsReal					m_framesToSmoothMouseData;
		KsReal					m_pitchAngle;
		KsReal					m_yawAngle;
		KsInt32					m_mousePosX;		// �Ō�ɋL�^���ꂽ�}�E�X�J�[�\���̂w���W
		KsInt32					m_mousePosY;		// �Ō�ɋL�^���ꂽ�}�E�X�J�[�\���̂w���W

		KsVector3d				m_vMinBoundary;
		KsVector3d				m_vMaxBoundary;

		KsVector3d				m_translate;		//
		KsVector3d				m_mousePosLast;		// 
		KsReal					m_pitch;			// �w���𒆐S�Ƃ����]�p�x
		KsReal					m_yaw;				// �x���𒆐S�Ƃ����]�p�x
		KsReal					m_distance;			// �J�����̋���
		KsReal					m_moveScaler;

		KsVector3d				m_direction;
		KsMatrix4x4				m_cameraRot;
};


#endif		/* __KSFREECAMERA_H__ */

