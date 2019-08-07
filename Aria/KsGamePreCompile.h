/************************************************************************************************/
/** 
 * @file		KsGamePreCompile.h
 * @brief		プリコンパイルヘッダー
 * @author		Tsukasa Kato
 * @date		2005/06/27
 * @since		2005/06/27
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSGAMEPRECOMPILE_H__
#define __KSGAMEPRECOMPILE_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#define _WIN32_DCOM
#include <ObjBase.h>
#include <random>
#include <iostream>

//------------------------------------------------------------------
// Middleware Bullet 
//------------------------------------------------------------------
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

//------------------------------------------------------------------
// Middleware OVR 
//------------------------------------------------------------------
#include <OVRVersion.h>
#include <OVR.h>

//------------------------------------------------------------------
// Core System
//------------------------------------------------------------------
#include <KsEngine/KsCore.h>

//------------------------------------------------------------------
// DirectX11 Engine
//------------------------------------------------------------------
#include <KsDevDX11/KsCoreDX11.h>

//------------------------------------------------------------------
// Script Engine
//------------------------------------------------------------------
#include <KsScript/KsScriptCore.h>

//------------------------------------------------------------------
// SWF Engine
//------------------------------------------------------------------
#include <KsSWF/KsSWFCore.h>

//------------------------------------------------------------------
// Physics Engien [ Bullet ]
//------------------------------------------------------------------
#include <KsPhysicsBullet/KsPhysicsBullet.h>

//------------------------------------------------------------------
// MMD Plugin
//------------------------------------------------------------------
#include <KsMMD/KsMMD.h>

//------------------------------------------------------------------
// Game System
//------------------------------------------------------------------
#include "Aria/KsGameCommon.h"

#include "Aria/config/KsGameConfigManager.h"

#include "Aria/ovr/KsOVRType.h"
#include "Aria/ovr/KsOVRDistortion.h"
#include "Aria/ovr/KsOVRStereoEyeParams.h"
#include "Aria/ovr/KsOVRSystem.h"

#include "Aria/factory/KsPhysicsSystemFactory.h"
#include "Aria/factory/KsRenderSystemFactory.h"

#include "Aria/input/KsGameMouse.h"
#include "Aria/input/KsGamePad.h"
#include "Aria/input/KsGamePadManager.h"

#include "Aria/resource/KsGameResourceManager.h"
#include "Aria/resource/KsGameShaderManager.h"

#include "Aria/thread/KsMainThread.h"
#include "Aria/thread/KsPhysicsThread.h"
#include "Aria/thread/KsRenderThread.h"

#include "Aria/render/shadow/KsShadowManager.h"

#include "Aria/render/deferred/KsDeferredRender.h"
#include "Aria/render/deferred/KsContourEffect.h"
#include "Aria/render/deferred/KsDeferredEffect.h"
#include "Aria/render/deferred/KsDeferredLighting.h"
#include "Aria/render/deferred/KsDeferredRender.h"

#include "Aria/render/forwardplus/KsForwardPlusEffect.h"
#include "Aria/render/forwardplus/KsForwardPlusLPointighting.h"
#include "Aria/render/forwardplus/KsForwardPlusRender.h"

#include "Aria/game/camera/KsCameraFactory.h"
#include "Aria/game/camera/KsFreeCamera.h"
#include "Aria/game/camera/KsPlayerCamera.h"
#include "Aria/game/scene/KsSceneType.h"
#include "Aria/game/scene/KsSceneManager.h"
#include "Aria/game/reader/KsPMDModelReader.h"
#include "Aria/game/reader/KsPMDActorReader.h"
#include "Aria/game/system/KsGameSystem.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


#endif	/* __KSGAMEPRECOMPILE_H__ */

