/************************************************************************************************/
/** 
 * @file		KsVertexTypes.h
 * @brief		頂点タイプ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSVERTEXTYPES_H__
#define __KSVERTEXTYPES_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/



/************************************************************************************************/
/**
 * @class		KsVertexPositionColor
 * @brief		KsVertexPositionColor
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
struct ksENGINE_API KsVertexPositionColor
{
    KsVertexPositionColor();
    KsVertexPositionColor(KsVector3d const& position, KsVector4d const& color);

    KsVector3d position;
    KsVector4d color;

    static const KsInt32 InputElementCount = 2;
    static const KS_INPUT_ELEMENT_DESC InputElements[InputElementCount];
};


/************************************************************************************************/
/**
 * @class		KsVertexPositionTexture
 * @brief		KsVertexPositionTexture
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
struct ksENGINE_API KsVertexPositionTexture
{
    KsVertexPositionTexture();
    KsVertexPositionTexture(KsVector3d const& position, KsVector2d const& textureCoordinate);


    KsVector3d position;
    KsVector2d textureCoordinate;

    static const KsInt32 InputElementCount = 2;
    static const KS_INPUT_ELEMENT_DESC InputElements[InputElementCount];
};


/************************************************************************************************/
/**
 * @class		KsVertexPositionTexture
 * @brief		KsVertexPositionTexture
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
struct ksENGINE_API KsVertexPositionNormal
{
    KsVertexPositionNormal();
    KsVertexPositionNormal(KsVector3d const& position, KsVector3d const& normal);

    KsVector3d position;
    KsVector3d normal;

    static const KsInt32 InputElementCount = 2;
    static const KS_INPUT_ELEMENT_DESC InputElements[InputElementCount];
};


/************************************************************************************************/
/**
 * @class		KsVertexPositionTexture
 * @brief		KsVertexPositionTexture
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
struct ksENGINE_API KsVertexPositionColorTexture
{
    KsVertexPositionColorTexture();
    KsVertexPositionColorTexture(KsVector3d const& position, KsVector4d const& color, KsVector2d const& textureCoordinate);

    KsVector3d position;
    KsVector4d color;
    KsVector2d textureCoordinate;

    static const KsInt32 InputElementCount = 3;
    static const KS_INPUT_ELEMENT_DESC InputElements[InputElementCount];
};


/************************************************************************************************/
/**
 * @class		KsVertexPositionTexture
 * @brief		KsVertexPositionTexture
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
struct ksENGINE_API KsVertexPositionNormalColor
{
    KsVertexPositionNormalColor();
    KsVertexPositionNormalColor(KsVector3d const& position, KsVector3d const& normal, KsVector4d const& color);

    KsVector3d position;
    KsVector3d normal;
    KsVector4d color;

    static const KsInt32 InputElementCount = 3;
    static const KS_INPUT_ELEMENT_DESC InputElements[InputElementCount];
};


/************************************************************************************************/
/**
 * @class		KsVertexPositionTexture
 * @brief		KsVertexPositionTexture
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
struct ksENGINE_API KsVertexPositionNormalTexture
{
    KsVertexPositionNormalTexture();
    KsVertexPositionNormalTexture(KsVector3d const& position, KsVector3d const& normal, KsVector2d const& textureCoordinate);

    KsVector3d position;
    KsVector3d normal;
    KsVector2d textureCoordinate;

    static const KsInt32 InputElementCount = 3;
    static const KS_INPUT_ELEMENT_DESC InputElements[InputElementCount];
};


/************************************************************************************************/
/**
 * @class		KsVertexPositionTexture
 * @brief		KsVertexPositionTexture
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
struct ksENGINE_API KsVertexPositionNormalColorTexture
{
    KsVertexPositionNormalColorTexture();
    KsVertexPositionNormalColorTexture(KsVector3d const& position, KsVector3d const& normal, KsVector4d const& color, KsVector2d const& textureCoordinate);

    KsVector3d position;
    KsVector3d normal;
    KsVector4d color;
    KsVector2d textureCoordinate;

    static const KsInt32 InputElementCount = 4;
    static const KS_INPUT_ELEMENT_DESC InputElements[InputElementCount];
};

#endif		/* __KSVERTEXTYPES_H__ */

