/************************************************************************************************/
/**
 * @file	KsRenderSystemFactory.cpp
 * @brief	描画システム生成
 * @author	Tsukasa Kato
 * @date	2005/11/30
 * @version	1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "Aria/KsGamePreCompile.h"
#include "Aria/factory/KsRenderSystemFactory.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/*
 * @funcion	KsRenderSystemFactory
 * @brief	描画システム生成
 * @author  Tsukasa Kato
 * @since   2005/11/30
 * @version ----/--/--
 */
/************************************************************************************************/
KsRenderSystem* KsRenderSystemFactory( ksRENDERSYSTEM_TYPE type, void* pParam )
{
	switch( type )
	{
		case ksRENDERSYSTEM_OPENGL:
		{
			//--------------------------------------------------
			// OpenGLシステム	
			//--------------------------------------------------
			//return ksNew KsRenderSystemGL( pParam );
			return NULL;
		}
		case ksRENDERSYSTEM_DIRECTX9:
		{
			//--------------------------------------------------
			// DirectX9システム	
			//--------------------------------------------------
			//return ksNew KsRenderSystemDX9( pParam );
			return NULL;
		}
		case ksRENDERSYSTEM_DIRECTX11:
		{
			//--------------------------------------------------
			// DirectX11システム	
			//--------------------------------------------------
			return ksNew KsRenderSystemDX11( pParam );
		}
		default:
		{
			break;
		}
	}

	return NULL;
}


