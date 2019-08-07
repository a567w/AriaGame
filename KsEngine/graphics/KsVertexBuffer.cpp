/************************************************************************************************/
/** 
 * @file		KsVertexBuffer.cpp
 * @brief		頂点バッファ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"
#include "KsVertexBuffer.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * コンストラクタ
 */
/************************************************************************************************/
KsVertexBuffer::KsVertexBuffer()
	: m_vertexSize( 0 )
	, m_numVertex( 0 )
	, m_vertexFormat( 0 )
{
}

/************************************************************************************************/
/**
 * デストラクタ
 */
/************************************************************************************************/
KsVertexBuffer::~KsVertexBuffer()
{
}

