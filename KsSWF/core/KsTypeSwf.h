/************************************************************************************************/
/** 
 * @file		KsTypeD3D9.h
 * @brief		ビデをモードを取得する
 * @author		Tsukasa Kato
 * @date		2004/08/17
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSTYPESWF_H__
#define __KSTYPESWF_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include <KsEngine/KsType.h>
#include <KsEngine/KsCore.h>
#include <KsEngine/KsArray.h>
#include <KsEngine/KsString.h>
#include <KsEngine/KsLog.h>
#include <KsEngine/KsCrc.h>
#include <KsEngine/KsMath.h>
#include <KsEngine/KsFile.h>
#include <KsEngine/KsFileBuffer.h>
#include <KsEngine/KsFileSystem.h>
#include <KsEngine/KsRenderState.h>
#include <KsEngine/KsRenderSystem.h>
#include <KsEngine/KsShader.h>
#include <KsEngine/KsShaderManager.h>
#include <KsEngine/KsImage.h>
#include <KsEngine/KsTexture.h>
#include <KsEngine/KsTextureManager.h>
#include <KsEngine/KsRenderTarget.h>
#include <KsEngine/KsRenderTargetTexture.h>
#include <KsEngine/KsVertexBuffer.h>
#include <KsEngine/KsVertexDeclaration.h>
#include <KsEngine/KsIndexBuffer.h>
#include <KsEngine/KsHardwareBufferManager.h>

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
/* 出力形式 */
#ifdef ksBUILD_STATIC
	#define ksSWF_API
	#define ksSWF_EXTERN
#else
	#ifdef ksSWF_EXPORTS
		#define ksSWF_API			__declspec(dllexport)
		#define ksSWF_EXTERN
	#else
		#define ksSWF_API			__declspec(dllimport)
		#define ksSWF_EXTERN		extern
	#endif
#endif

#define ksSWF_CDECL __cdecl


#endif /* __KSTYPESWF_H__ */

