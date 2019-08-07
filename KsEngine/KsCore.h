/*************************************************************************************************/
/**
 * @file	KsCore.h
 * @brief	コア定義
 * @author	Tsukasa Kato
 * @date	2003/11/30
 * @version	1.0.0
 */
/*************************************************************************************************/
#ifndef __KSCORE_H__
#define __KSCORE_H__

/*===============================================================================================*/
/*                                 << インクルード >>                                             */
/*===============================================================================================*/

//------------------------------------------------------------------
// システム系
//------------------------------------------------------------------
#include <KsEngine/system/KsType.h>				/* 型宣言		*/
#include <KsEngine/system/KsMacro.h>			/* マクロ		*/
#include <KsEngine/system/KsLog.h>				/* ログ			*/
#include <KsEngine/system/KsAssert.h>			/* マクロ		*/
#include <KsEngine/system/component/KsRefCounter.h>

//------------------------------------------------------------------
// スレッド系
//------------------------------------------------------------------
#include <KsEngine/thread/KsMutex.h>

//------------------------------------------------------------------
// 数値計算系
//------------------------------------------------------------------
#include <KsEngine/math/KsMath.h>

//------------------------------------------------------------------
// メモリー系
//------------------------------------------------------------------
#include <KsEngine/memory/KsMemory.h>	/* メモリー管理	*/

//------------------------------------------------------------------
// 自作テンプレートライブラリ系
//------------------------------------------------------------------
#include <KsEngine/system/ktl/KsSingleton.h>
#include <KsEngine/system/ktl/KsString.h>
#include <KsEngine/system/ktl/KsStringFixed.h>

//------------------------------------------------------------------
// 数値計算系
//------------------------------------------------------------------
#include <KsEngine/math/KsMath.h>

//------------------------------------------------------------------
// コレクションテンプレート
//------------------------------------------------------------------
#include <KsEngine/system/collections/KsArray.h>
#include <KsEngine/system/collections/KsHash.h>
#include <KsEngine/system/collections/KsList.h>
#include <KsEngine/system/collections/KsQueue.h>
#include <KsEngine/system/collections/KsRingBuffer.h>
#include <KsEngine/system/collections/KsStack.h>

//------------------------------------------------------------------
// チェック系
//------------------------------------------------------------------
#include <KsEngine/system/crc/KsCrc32.h>
#include <KsEngine/system/md5/KsMD5.h>

//------------------------------------------------------------------
// タスク
//------------------------------------------------------------------
#include <KsEngine/task/KsDraw.h>
#include <KsEngine/task/KsUpdate.h>
#include <KsEngine/task/KsTask.h>
#include <KsEngine/task/KsDrawList.h>
#include <KsEngine/task/KsUpdateList.h>
#include <KsEngine/task/KsTaskManager.h>

//------------------------------------------------------------------
// グラフィク系 
//------------------------------------------------------------------
#include <KsEngine/graphics/KsGIFormat.h>
#include <KsEngine/graphics/KsPoint.h>
#include <KsEngine/graphics/KsRect.h>
#include <KsEngine/graphics/KsFrustum.h>
#include <KsEngine/graphics/KsImage.h>
#include <KsEngine/graphics/KsViewport.h>
#include <KsEngine/graphics/KsCamera.h>
#include <KsEngine/graphics/KsCameraManager.h>
#include <KsEngine/graphics/KsInputLayout.h>
#include <KsEngine/graphics/KsInputLayoutManager.h>
#include <KsEngine/graphics/KsBufferObject.h>
#include <KsEngine/graphics/KsConstantBuffer.h>
#include <KsEngine/graphics/KsIndexBuffer.h>
#include <KsEngine/graphics/KsVertexBuffer.h>
#include <KsEngine/graphics/KsVertexTypes.h>

//------------------------------------------------------------------
// シェーダー
//------------------------------------------------------------------
#include <KsEngine/shader/KsShaderType.h>
#include <KsEngine/shader/KsShaderParam.h>
#include <KsEngine/shader/KsShaderProgram.h>
#include <KsEngine/shader/KsVertexShader.h>
#include <KsEngine/shader/KsPixelShader.h>
#include <KsEngine/shader/KsGeometryShader.h>
#include <KsEngine/shader/KsComputeShader.h>
#include <KsEngine/shader/KsShaderManager.h>
#include <KsEngine/shader/KsEffect.h>

//------------------------------------------------------------------
// 入力系
//------------------------------------------------------------------
#include <KsEngine/input/KsKeyDefine.h>
#include <KsEngine/input/KsMouse.h>
#include <KsEngine/input/KsPad.h>
#include <KsEngine/input/KsInputSystem.h>

//------------------------------------------------------------------
// スレッド系
//------------------------------------------------------------------
#include <KsEngine/thread/KsEvent.h>
#include <KsEngine/thread/KsMutex.h>
#include <KsEngine/thread/KsThreadCondition.h>
#include <KsEngine/thread/KsThreadLock.h>
#include <KsEngine/thread/KsThreadParam.h>
#include <KsEngine/thread/KsThread.h>
#include <KsEngine/thread/KsThreadGroup.h>

//------------------------------------------------------------------
// ファイルアクセス系
//------------------------------------------------------------------
#include <KsEngine/file/KsBitIO.h>
#include <KsEngine/file/KsPath.h>
#include <KsEngine/file/KsDirectory.h>
#include <KsEngine/file/KsBinaryReader.h>
#include <KsEngine/file/KsFile.h>
#include <KsEngine/file/KsFileBuffer.h>
#include <KsEngine/file/KsFileList.h>
#include <KsEngine/file/KsFileObject.h>
#include <KsEngine/file/KsFilePack.h>
#include <KsEngine/file/KsBitReader.h>
#include <KsEngine/file/KsReadRequest.h>
#include <KsEngine/file/KsFileThread.h>
#include <KsEngine/file/KsFileAsyncReader.h>
#include <KsEngine/file/KsFileSystem.h>
#include <KsEngine/file/KsLzss.h>
#include <KsEngine/file/KsBpe.h>
#include <KsEngine/file/KsPack.h>

//------------------------------------------------------------------
// XML 
//------------------------------------------------------------------
#include <KsEngine/xml/KsXmlReader.h>
#include <KsEngine/xml/KsXmlChar.h>
#include <KsEngine/xml/KsXmlTextReader.h>

//------------------------------------------------------------------
// 描画系 
//------------------------------------------------------------------
#include <KsEngine/graphics/KsDisplayMode.h>
#include <KsEngine/graphics/KsDisplayModeList.h>
#include <KsEngine/graphics/KsAdapter.h>
#include <KsEngine/graphics/KsAdapterList.h>
#include <KsEngine/graphics/KsColor.h>
#include <KsEngine/graphics/KsColorReal.h>
#include <KsEngine/graphics/KsRenderType.h>
#include <KsEngine/graphics/KsSamplerState.h>
#include <KsEngine/graphics/KsRasterizerState.h>
#include <KsEngine/graphics/KsBlendState.h>
#include <KsEngine/graphics/KsDepthStencilState.h>
#include <KsEngine/graphics/KsTexture.h>
#include <KsEngine/graphics/KsTextureManager.h>
#include <KsEngine/graphics/KsUnorderedAccessView.h>
#include <KsEngine/graphics/KsStructuredBuffer.h>
#include <KsEngine/graphics/KsRenderTarget.h>
#include <KsEngine/graphics/KsCommandList.h>
#include <KsEngine/graphics/KsRenderContext.h>
#include <KsEngine/graphics/KsRenderState.h>
#include <KsEngine/graphics/KsGraphicsType.h>
#include <KsEngine/graphics/KsGraphics.h>
#include <KsEngine/graphics/KsLine2DBatch.h>
#include <KsEngine/graphics/KsLine3DBatch.h>
#include <KsEngine/graphics/KsRectBatch.h>
#include <KsEngine/graphics/KsSpriteBatch.h>
#include <KsEngine/graphics/KsRenderSystem.h>

//------------------------------------------------------------------
// フォント
//------------------------------------------------------------------
#include <KsEngine/font/KsFont.h>

//------------------------------------------------------------------
// 物理計算系 
//------------------------------------------------------------------
#include <KsEngine/physics/shape/KsCollisionShape.h>
#include <KsEngine/physics/dynamics/KsMotionState.h>
#include <KsEngine/physics/dynamics/KsRigidBody.h>
#include <KsEngine/physics/dynamics/KsConstraint.h>
#include <KsEngine/physics/dynamics/KsSpringConstraint.h>
#include <KsEngine/physics/dynamics/KsWorld.h>
#include <KsEngine/physics/system/KsPhysicsType.h>
#include <KsEngine/physics/system/KsPhysicsParameter.h>
#include <KsEngine/physics/system/KsPhysicsController.h>
#include <KsEngine/physics/system/KsPhysicsSystem.h>

//------------------------------------------------------------------
// モデル 
//------------------------------------------------------------------
#include <KsEngine/model/KsModelParameter.h>
#include <KsEngine/model/KsBoundingSphere.h>
#include <KsEngine/model/KsBone.h>
#include <KsEngine/model/KsBoneCollection.h>
#include <KsEngine/model/KsMeshPart.h>
#include <KsEngine/model/KsMeshPartCollection.h>
#include <KsEngine/model/KsMesh.h>
#include <KsEngine/model/KsMeshCollection.h>
#include <KsEngine/model/KsEffectCollection.h>
#include <KsEngine/model/KsTextureCollection.h>
#include <KsEngine/model/KsModel.h>
#include <KsEngine/model/KsModelLoader.h>

//------------------------------------------------------------------
// アニメーション
//------------------------------------------------------------------
#include <KsEngine/animation/KsBezier.h>
#include <KsEngine/animation/KsBonePose.h>
#include <KsEngine/animation/KsSkeleton.h>
#include <KsEngine/animation/KsIAttachable.h>
#include <KsEngine/animation/KsKeyFrame.h>
#include <KsEngine/animation/KsKeyFrameCollection.h>
#include <KsEngine/animation/KsAnimationUtil.h>
#include <KsEngine/animation/KsAnimationChannel.h>
#include <KsEngine/animation/KsAnimation.h>
#include <KsEngine/animation/KsIAnimationController.h>
#include <KsEngine/animation/KsAnimationController.h>
#include <KsEngine/animation/KsInterpolationController.h>
#include <KsEngine/animation/KsHumanIK.h>

//------------------------------------------------------------------
// アクター
//------------------------------------------------------------------
#include <KsEngine/actor/KsActor.h>

//------------------------------------------------------------------
// サウンド系 
//------------------------------------------------------------------
#include <KsEngine/sound/KsSoundData.h>
#include <KsEngine/sound/KsSoundDataBank.h>

//------------------------------------------------------------------
// 時間関係 
//------------------------------------------------------------------
#include <KsEngine/timer/KsTimer.h>

//------------------------------------------------------------------
// Windows
//------------------------------------------------------------------
#include <KsEngine/win/KsAppInstance.h>
#include <KsEngine/win/KsWindowUtility.h>
#include <KsEngine/win/KsWindowMutex.h>
#include <KsEngine/win/KsWindowParam.h>
#include <KsEngine/win/KsWindow.h>

//------------------------------------------------------------------
// Debug
//------------------------------------------------------------------
#include <KsEngine/debug/KsDebugFont.h>
#include <KsEngine/debug/KsDebugFontManager.h>

/*===============================================================================================*/
/*                                     << 定義 >>                                                */
/*===============================================================================================*/

#endif	/* __KSCORE_H__ */

