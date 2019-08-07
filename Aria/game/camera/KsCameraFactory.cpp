/************************************************************************************************/
/** 
 * @file		KsCameraFactory.cpp
 * @brief		カメラ生成
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "Aria/KsGamePreCompile.h"
#include "Aria/game/camera/KsCameraFactory.h"
#include "Aria/game/camera/KsFreeCamera.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/*
 * 指定カメラを生成する
 * @param	cameraType	生成するカメラタイプ
 * @return				生成したカメラのポインタ
 */
/************************************************************************************************/
KsCamera* KsCameraFactory::create( ksCAMERA_TYPE cameraType )
{
	KsCamera*	pCamera = NULL;

	switch( cameraType )
	{
		case ksFREE_CAMERA:
		{
			/* フリーカメラ */
			pCamera = ksNew KsFreeCamera();
			break;
		}
		case ksSHADOW_CAMERA:
		{
			/* 影生成用カメラ */
			break;
		}
		default:
		{
			KsAssert( 0, "# Not Create Camera!" );
			break;
		}
	}

	return pCamera;
}

