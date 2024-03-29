/************************************************************************************************/
/** 
 * @file		KsPixelShader.cpp
 * @brief		シェーダーオブジェクト
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"
#include "KsPixelShader.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsPixelShader::KsPixelShader()
	: KsShaderProgram( ksPIXEL_SHADER )
{
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsPixelShader::~KsPixelShader()
{
}

