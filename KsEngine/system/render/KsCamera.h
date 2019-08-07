/************************************************************************************************/
/** 
 * @file		StCamera.h
 * @brief		ゲームマネージャ
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __STCAMERA_H__
#define __STCAMERA_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
//#include "StViewport.h"
//#include "StVector.h"
//#include "StMatrix.h"
//#include "StQuaternion.h"
#include "StCameraObject.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/*==============================================================================================*/
/*                                     << 定義 >>                                               */
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
	stORTHOGRAPHIC,		/**< 正射影		*/
	stPERSPECTIVE,		/**< 透視射影	*/
};


class StCamera : public StCameraObject
{
	public:
		StCamera();
		virtual							~StCamera();

#if 0
		stPROJECTION_TYPE					m_projectionType;	/**< プロジェクションのタイプ		*/
		StViewport							m_viewport;			/**< ビューポート				*/
		StReal								m_fovy;				/**< 視野角						*/
		StReal								m_aspect;			/**< アスペクト比				*/
		StMatrix							m_projMatrix;		/**< プロジェクションマトリックス	*/
		StMatrix							m_viewMatrix;		/**< ビューマトリックス			*/
		StVector3d							m_eye;				/**< 視点						*/
		StVector3d							m_at;				/**< カメラのatベクトル			*/
		StVector3d							m_up;				/**< カメラのupベクトル			*/
		StVector3d							m_right;			/**< カメラのrightベクトル		*/

		void								Viewport();
		void								Perspective();
		void								OrthoRH();
		void								LookAt();
#endif

		// 描画開始
		virtual void						beginRender();
		virtual void						endRender();
};

#if 0
/************************************************************************************************/
/**
 * 透視射影行列を生成する(右手系)
 * @param		projMatrix		プロジェクションマトリックス保存用
 * @param		fovy			視野角
 * @param		aspect			アスペクト比
 * @param		zNear			近距離値
 * @param		zFar			遠距離値
 */
/************************************************************************************************/
extern void StMatrixPerspectiveRH( StMatrix& projMatrix, StReal fovy, StReal aspect, StReal zNear, StReal zFar );

/************************************************************************************************/
/**
 * 正射影行列を生成する(右手系)
 * @param		projMatrix		プロジェクションマトリックス保存用
 * @param		left			レフト
 * @param		right			ライト
 * @param		bottom			ボトム
 * @param		top				トップ
 * @param		aspect			アスペクト比
 * @param		zNear			近距離値
 * @param		zFar			遠距離値
 */
/************************************************************************************************/
extern void StMatrixOrthoRH( StMatrix& projMatrix, StReal left, StReal right, StReal bottom, StReal top, StReal zNear, StReal zFar );

/************************************************************************************************/
/**
 * 視点を設定する(右手系)
 * @param		viewMatrix		ビューマトリックス保存用
 * @param		eye				視点
 * @param		at				注視点
 * @param		up				アップベクトル
 */
/************************************************************************************************/
extern void StMatrixLookAtRH( StMatrix& viewMatrix, const StVector3d& eye, const StVector3d& at, const StVector3d& up );

/************************************************************************************************/
/**
 * 透視射影行列を生成する(左手系)
 * @param		projMatrix		プロジェクションマトリックス保存用
 * @param		fovy			視野角
 * @param		aspect			アスペクト比
 * @param		zNear			近距離値
 * @param		zFar			遠距離値
 */
/************************************************************************************************/
extern void StMatrixPerspectiveLH( StMatrix& projMatrix, StReal fovy, StReal aspect, StReal zNear, StReal zFar );

/************************************************************************************************/
/**
 * 正射影行列を生成する(左手系)
 * @param		projMatrix		プロジェクションマトリックス保存用
 * @param		left			レフト
 * @param		right			ライト
 * @param		bottom			ボトム
 * @param		top				トップ
 * @param		aspect			アスペクト比
 * @param		zNear			近距離値
 * @param		zFar			遠距離値
 */
/************************************************************************************************/
extern void StMatrixOrthoLH( StMatrix& projMatrix, StReal left, StReal right, StReal bottom, StReal top, StReal zNear, StReal zFar );

/************************************************************************************************/
/**
 * 視点を設定する(左手系)
 * @param		viewMatrix		ビューマトリックス保存用
 * @param		eye				視点
 * @param		at				注視点
 * @param		up				アップベクトル
 */
/************************************************************************************************/
extern void StMatrixLookAtLH( StMatrix& viewMatrix, const StVector3d& eye, const StVector3d& at, const StVector3d& up );
#endif


#endif		/* __STCAMERA_H__ */

