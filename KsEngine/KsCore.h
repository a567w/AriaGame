/*************************************************************************************************/
/**
 * @file	KsCore.h
 * @brief	�R�A��`
 * @author	Tsukasa Kato
 * @date	2003/11/30
 * @version	1.0.0
 */
/*************************************************************************************************/
#ifndef __KSCORE_H__
#define __KSCORE_H__

/*===============================================================================================*/
/*                                 << �C���N���[�h >>                                             */
/*===============================================================================================*/

//------------------------------------------------------------------
// �V�X�e���n
//------------------------------------------------------------------
#include <KsEngine/system/KsType.h>				/* �^�錾		*/
#include <KsEngine/system/KsMacro.h>			/* �}�N��		*/
#include <KsEngine/system/KsLog.h>				/* ���O			*/
#include <KsEngine/system/KsAssert.h>			/* �}�N��		*/
#include <KsEngine/system/component/KsRefCounter.h>

//------------------------------------------------------------------
// �X���b�h�n
//------------------------------------------------------------------
#include <KsEngine/thread/KsMutex.h>

//------------------------------------------------------------------
// ���l�v�Z�n
//------------------------------------------------------------------
#include <KsEngine/math/KsMath.h>

//------------------------------------------------------------------
// �������[�n
//------------------------------------------------------------------
#include <KsEngine/memory/KsMemory.h>	/* �������[�Ǘ�	*/

//------------------------------------------------------------------
// ����e���v���[�g���C�u�����n
//------------------------------------------------------------------
#include <KsEngine/system/ktl/KsSingleton.h>
#include <KsEngine/system/ktl/KsString.h>
#include <KsEngine/system/ktl/KsStringFixed.h>

//------------------------------------------------------------------
// ���l�v�Z�n
//------------------------------------------------------------------
#include <KsEngine/math/KsMath.h>

//------------------------------------------------------------------
// �R���N�V�����e���v���[�g
//------------------------------------------------------------------
#include <KsEngine/system/collections/KsArray.h>
#include <KsEngine/system/collections/KsHash.h>
#include <KsEngine/system/collections/KsList.h>
#include <KsEngine/system/collections/KsQueue.h>
#include <KsEngine/system/collections/KsRingBuffer.h>
#include <KsEngine/system/collections/KsStack.h>

//------------------------------------------------------------------
// �`�F�b�N�n
//------------------------------------------------------------------
#include <KsEngine/system/crc/KsCrc32.h>
#include <KsEngine/system/md5/KsMD5.h>

//------------------------------------------------------------------
// �^�X�N
//------------------------------------------------------------------
#include <KsEngine/task/KsDraw.h>
#include <KsEngine/task/KsUpdate.h>
#include <KsEngine/task/KsTask.h>
#include <KsEngine/task/KsDrawList.h>
#include <KsEngine/task/KsUpdateList.h>
#include <KsEngine/task/KsTaskManager.h>

//------------------------------------------------------------------
// �O���t�B�N�n 
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
// �V�F�[�_�[
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
// ���͌n
//------------------------------------------------------------------
#include <KsEngine/input/KsKeyDefine.h>
#include <KsEngine/input/KsMouse.h>
#include <KsEngine/input/KsPad.h>
#include <KsEngine/input/KsInputSystem.h>

//------------------------------------------------------------------
// �X���b�h�n
//------------------------------------------------------------------
#include <KsEngine/thread/KsEvent.h>
#include <KsEngine/thread/KsMutex.h>
#include <KsEngine/thread/KsThreadCondition.h>
#include <KsEngine/thread/KsThreadLock.h>
#include <KsEngine/thread/KsThreadParam.h>
#include <KsEngine/thread/KsThread.h>
#include <KsEngine/thread/KsThreadGroup.h>

//------------------------------------------------------------------
// �t�@�C���A�N�Z�X�n
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
// �`��n 
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
// �t�H���g
//------------------------------------------------------------------
#include <KsEngine/font/KsFont.h>

//------------------------------------------------------------------
// �����v�Z�n 
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
// ���f�� 
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
// �A�j���[�V����
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
// �A�N�^�[
//------------------------------------------------------------------
#include <KsEngine/actor/KsActor.h>

//------------------------------------------------------------------
// �T�E���h�n 
//------------------------------------------------------------------
#include <KsEngine/sound/KsSoundData.h>
#include <KsEngine/sound/KsSoundDataBank.h>

//------------------------------------------------------------------
// ���Ԋ֌W 
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
/*                                     << ��` >>                                                */
/*===============================================================================================*/

#endif	/* __KSCORE_H__ */

