/************************************************************************************************/
/** 
 * @file		StCamera.h
 * @brief		�Q�[���}�l�[�W��
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __STCAMERA_H__
#define __STCAMERA_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
//#include "StViewport.h"
//#include "StVector.h"
//#include "StMatrix.h"
//#include "StQuaternion.h"
#include "StCameraObject.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class	
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
enum stPROJECTION_TYPE
{
	stORTHOGRAPHIC,		/**< ���ˉe		*/
	stPERSPECTIVE,		/**< �����ˉe	*/
};


class StCamera : public StCameraObject
{
	public:
		StCamera();
		virtual							~StCamera();

#if 0
		stPROJECTION_TYPE					m_projectionType;	/**< �v���W�F�N�V�����̃^�C�v		*/
		StViewport							m_viewport;			/**< �r���[�|�[�g				*/
		StReal								m_fovy;				/**< ����p						*/
		StReal								m_aspect;			/**< �A�X�y�N�g��				*/
		StMatrix							m_projMatrix;		/**< �v���W�F�N�V�����}�g���b�N�X	*/
		StMatrix							m_viewMatrix;		/**< �r���[�}�g���b�N�X			*/
		StVector3d							m_eye;				/**< ���_						*/
		StVector3d							m_at;				/**< �J������at�x�N�g��			*/
		StVector3d							m_up;				/**< �J������up�x�N�g��			*/
		StVector3d							m_right;			/**< �J������right�x�N�g��		*/

		void								Viewport();
		void								Perspective();
		void								OrthoRH();
		void								LookAt();
#endif

		// �`��J�n
		virtual void						beginRender();
		virtual void						endRender();
};

#if 0
/************************************************************************************************/
/**
 * �����ˉe�s��𐶐�����(�E��n)
 * @param		projMatrix		�v���W�F�N�V�����}�g���b�N�X�ۑ��p
 * @param		fovy			����p
 * @param		aspect			�A�X�y�N�g��
 * @param		zNear			�ߋ����l
 * @param		zFar			�������l
 */
/************************************************************************************************/
extern void StMatrixPerspectiveRH( StMatrix& projMatrix, StReal fovy, StReal aspect, StReal zNear, StReal zFar );

/************************************************************************************************/
/**
 * ���ˉe�s��𐶐�����(�E��n)
 * @param		projMatrix		�v���W�F�N�V�����}�g���b�N�X�ۑ��p
 * @param		left			���t�g
 * @param		right			���C�g
 * @param		bottom			�{�g��
 * @param		top				�g�b�v
 * @param		aspect			�A�X�y�N�g��
 * @param		zNear			�ߋ����l
 * @param		zFar			�������l
 */
/************************************************************************************************/
extern void StMatrixOrthoRH( StMatrix& projMatrix, StReal left, StReal right, StReal bottom, StReal top, StReal zNear, StReal zFar );

/************************************************************************************************/
/**
 * ���_��ݒ肷��(�E��n)
 * @param		viewMatrix		�r���[�}�g���b�N�X�ۑ��p
 * @param		eye				���_
 * @param		at				�����_
 * @param		up				�A�b�v�x�N�g��
 */
/************************************************************************************************/
extern void StMatrixLookAtRH( StMatrix& viewMatrix, const StVector3d& eye, const StVector3d& at, const StVector3d& up );

/************************************************************************************************/
/**
 * �����ˉe�s��𐶐�����(����n)
 * @param		projMatrix		�v���W�F�N�V�����}�g���b�N�X�ۑ��p
 * @param		fovy			����p
 * @param		aspect			�A�X�y�N�g��
 * @param		zNear			�ߋ����l
 * @param		zFar			�������l
 */
/************************************************************************************************/
extern void StMatrixPerspectiveLH( StMatrix& projMatrix, StReal fovy, StReal aspect, StReal zNear, StReal zFar );

/************************************************************************************************/
/**
 * ���ˉe�s��𐶐�����(����n)
 * @param		projMatrix		�v���W�F�N�V�����}�g���b�N�X�ۑ��p
 * @param		left			���t�g
 * @param		right			���C�g
 * @param		bottom			�{�g��
 * @param		top				�g�b�v
 * @param		aspect			�A�X�y�N�g��
 * @param		zNear			�ߋ����l
 * @param		zFar			�������l
 */
/************************************************************************************************/
extern void StMatrixOrthoLH( StMatrix& projMatrix, StReal left, StReal right, StReal bottom, StReal top, StReal zNear, StReal zFar );

/************************************************************************************************/
/**
 * ���_��ݒ肷��(����n)
 * @param		viewMatrix		�r���[�}�g���b�N�X�ۑ��p
 * @param		eye				���_
 * @param		at				�����_
 * @param		up				�A�b�v�x�N�g��
 */
/************************************************************************************************/
extern void StMatrixLookAtLH( StMatrix& viewMatrix, const StVector3d& eye, const StVector3d& at, const StVector3d& up );
#endif


#endif		/* __STCAMERA_H__ */

