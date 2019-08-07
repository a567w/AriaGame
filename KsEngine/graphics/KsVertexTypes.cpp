/************************************************************************************************/
/** 
 * @file		KsVertexTypes.cpp
 * @brief		���_�^�C�v
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"
#include "KsVertexTypes.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsVertexPositionColor::KsVertexPositionColor()
{
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsVertexPositionColor::KsVertexPositionColor(KsVector3d const& position, KsVector4d const& color)
	: position(position)
	, color(color)
{
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsVertexPositionTexture::KsVertexPositionTexture()
{
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsVertexPositionTexture::KsVertexPositionTexture(KsVector3d const& position, KsVector2d const& textureCoordinate)
	: position(position)
	, textureCoordinate(textureCoordinate)
{
}


/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsVertexPositionNormal::KsVertexPositionNormal()
{
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsVertexPositionNormal::KsVertexPositionNormal(KsVector3d const& position, KsVector3d const& normal)
    : position(position)
    , normal(normal)
{
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsVertexPositionColorTexture::KsVertexPositionColorTexture()
{
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
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
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsVertexPositionNormalColor::KsVertexPositionNormalColor()
{
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
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
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsVertexPositionNormalTexture::KsVertexPositionNormalTexture()
{
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
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
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsVertexPositionNormalColorTexture::KsVertexPositionNormalColorTexture()
{
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
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









