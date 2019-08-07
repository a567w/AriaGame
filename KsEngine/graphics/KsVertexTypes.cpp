/************************************************************************************************/
/** 
 * @file		KsVertexTypes.cpp
 * @brief		頂点タイプ
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
#include "KsVertexTypes.h"

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
KsVertexPositionColor::KsVertexPositionColor()
{
}

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsVertexPositionColor::KsVertexPositionColor(KsVector3d const& position, KsVector4d const& color)
	: position(position)
	, color(color)
{
}

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsVertexPositionTexture::KsVertexPositionTexture()
{
}

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsVertexPositionTexture::KsVertexPositionTexture(KsVector3d const& position, KsVector2d const& textureCoordinate)
	: position(position)
	, textureCoordinate(textureCoordinate)
{
}


/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsVertexPositionNormal::KsVertexPositionNormal()
{
}

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsVertexPositionNormal::KsVertexPositionNormal(KsVector3d const& position, KsVector3d const& normal)
    : position(position)
    , normal(normal)
{
}

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsVertexPositionColorTexture::KsVertexPositionColorTexture()
{
}

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsVertexPositionColorTexture::KsVertexPositionColorTexture(KsVector3d const& position, KsVector4d const& color, KsVector2d const& textureCoordinate)
    : position(position)
    , color(color)
    , textureCoordinate(textureCoordinate)
{
}


/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsVertexPositionNormalColor::KsVertexPositionNormalColor()
{
}

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsVertexPositionNormalColor::KsVertexPositionNormalColor(KsVector3d const& position, KsVector3d const& normal, KsVector4d const& color)
    : position(position)
    , normal(normal)
    , color(color)
{
}



/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsVertexPositionNormalTexture::KsVertexPositionNormalTexture()
{
}

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsVertexPositionNormalTexture::KsVertexPositionNormalTexture(KsVector3d const& position, KsVector3d const& normal, KsVector2d const& textureCoordinate)
    : position(position)
    , normal(normal)
    , textureCoordinate(textureCoordinate)
{
}


/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsVertexPositionNormalColorTexture::KsVertexPositionNormalColorTexture()
{
}

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsVertexPositionNormalColorTexture::KsVertexPositionNormalColorTexture(KsVector3d const& position, KsVector3d const& normal, KsVector4d const& color, KsVector2d const& textureCoordinate)
    : position(position)
    , normal(normal)
    , color(color)
    , textureCoordinate(textureCoordinate)
{
}




// Vertex struct holding position and color information.
const KS_INPUT_ELEMENT_DESC KsVertexPositionColor::InputElements[] =
{
    { "SV_Position", 0, KS_GI_FORMAT_R32G32B32_FLOAT,    0, KS_APPEND_ALIGNED_ELEMENT, KS_INPUT_PER_VERTEX_DATA, 0 },
    { "COLOR",       0, KS_GI_FORMAT_R32G32B32A32_FLOAT, 0, KS_APPEND_ALIGNED_ELEMENT, KS_INPUT_PER_VERTEX_DATA, 0 },
};


// Vertex struct holding position and texture mapping information.
const KS_INPUT_ELEMENT_DESC KsVertexPositionTexture::InputElements[] =
{
    { "SV_Position", 0, KS_GI_FORMAT_R32G32B32_FLOAT,    0, KS_APPEND_ALIGNED_ELEMENT, KS_INPUT_PER_VERTEX_DATA, 0 },
    { "TEXCOORD",    0, KS_GI_FORMAT_R32G32_FLOAT,       0, KS_APPEND_ALIGNED_ELEMENT, KS_INPUT_PER_VERTEX_DATA, 0 },
};


// Vertex struct holding position and normal vector.
const KS_INPUT_ELEMENT_DESC KsVertexPositionNormal::InputElements[] =
{
    { "SV_Position", 0, KS_GI_FORMAT_R32G32B32_FLOAT,    0, KS_APPEND_ALIGNED_ELEMENT, KS_INPUT_PER_VERTEX_DATA, 0 },
    { "NORMAL",      0, KS_GI_FORMAT_R32G32B32_FLOAT,    0, KS_APPEND_ALIGNED_ELEMENT, KS_INPUT_PER_VERTEX_DATA, 0 },
};

        
// Vertex struct holding position, color, and texture mapping information.
const KS_INPUT_ELEMENT_DESC KsVertexPositionColorTexture::InputElements[] =
{
    { "SV_Position", 0, KS_GI_FORMAT_R32G32B32_FLOAT,    0, KS_APPEND_ALIGNED_ELEMENT, KS_INPUT_PER_VERTEX_DATA, 0 },
    { "COLOR",       0, KS_GI_FORMAT_R32G32B32A32_FLOAT, 0, KS_APPEND_ALIGNED_ELEMENT, KS_INPUT_PER_VERTEX_DATA, 0 },
    { "TEXCOORD",    0, KS_GI_FORMAT_R32G32_FLOAT,       0, KS_APPEND_ALIGNED_ELEMENT, KS_INPUT_PER_VERTEX_DATA, 0 },
};


// Vertex struct holding position, normal vector, and color information.
const KS_INPUT_ELEMENT_DESC KsVertexPositionNormalColor::InputElements[] =
{
    { "SV_Position", 0, KS_GI_FORMAT_R32G32B32_FLOAT,    0, KS_APPEND_ALIGNED_ELEMENT, KS_INPUT_PER_VERTEX_DATA, 0 },
    { "NORMAL",      0, KS_GI_FORMAT_R32G32B32_FLOAT,    0, KS_APPEND_ALIGNED_ELEMENT, KS_INPUT_PER_VERTEX_DATA, 0 },
    { "COLOR",       0, KS_GI_FORMAT_R32G32B32A32_FLOAT, 0, KS_APPEND_ALIGNED_ELEMENT, KS_INPUT_PER_VERTEX_DATA, 0 },
};

        
// Vertex struct holding position, normal vector, and texture mapping information.
const KS_INPUT_ELEMENT_DESC KsVertexPositionNormalTexture::InputElements[] =
{
    { "SV_Position", 0, KS_GI_FORMAT_R32G32B32_FLOAT,    0, KS_APPEND_ALIGNED_ELEMENT, KS_INPUT_PER_VERTEX_DATA, 0 },
    { "NORMAL",      0, KS_GI_FORMAT_R32G32B32_FLOAT,    0, KS_APPEND_ALIGNED_ELEMENT, KS_INPUT_PER_VERTEX_DATA, 0 },
    { "TEXCOORD",    0, KS_GI_FORMAT_R32G32_FLOAT,       0, KS_APPEND_ALIGNED_ELEMENT, KS_INPUT_PER_VERTEX_DATA, 0 },
};


// Vertex struct holding position, normal vector, color, and texture mapping information.
const KS_INPUT_ELEMENT_DESC KsVertexPositionNormalColorTexture::InputElements[] =
{
    { "SV_Position", 0, KS_GI_FORMAT_R32G32B32_FLOAT,    0, KS_APPEND_ALIGNED_ELEMENT, KS_INPUT_PER_VERTEX_DATA, 0 },
    { "NORMAL",      0, KS_GI_FORMAT_R32G32B32_FLOAT,    0, KS_APPEND_ALIGNED_ELEMENT, KS_INPUT_PER_VERTEX_DATA, 0 },
    { "COLOR",       0, KS_GI_FORMAT_R32G32B32A32_FLOAT, 0, KS_APPEND_ALIGNED_ELEMENT, KS_INPUT_PER_VERTEX_DATA, 0 },
    { "TEXCOORD",    0, KS_GI_FORMAT_R32G32_FLOAT,       0, KS_APPEND_ALIGNED_ELEMENT, KS_INPUT_PER_VERTEX_DATA, 0 },
};









