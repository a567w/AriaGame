/************************************************************************************************/
/** 
 * @file		KsFont.cpp
 * @brief		フォント描画
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"
#include "KsFont.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
namespace
{
	const KsUInt8 ksFontSignature[] = "KFNT";

    static inline bool operator< (KsGlyph const& left, KsGlyph const& right)
    {
        return left.Character < right.Character;
    }

    static inline bool operator< (KsWChar left, KsGlyph const& right)
    {
        return left < right.Character;
    }

    static inline bool operator< (KsGlyph const& left, KsWChar right)
    {
        return left.Character < right;
    }
}

/************************************************************************************************/
/*
 * コンストラクタ
 * @param	pFileName		ファイル名
 */
/************************************************************************************************/
KsFont::KsFont()
	: m_lineSpacing( 0.0f )
	, m_pTexture( 0 )
	, m_pDefaultGlyph( 0 )
	, m_pGraphics( 0 )
{
}

/************************************************************************************************/
/*
 * コンストラクタ
 * @param	pFileName		ファイル名
 */
/************************************************************************************************/
KsFont::KsFont( const KsWChar* pFileName )
	: m_lineSpacing( 0.0f )
	, m_pTexture( 0 )
	, m_pDefaultGlyph( 0 )
	, m_pGraphics( 0 )
{
	KsBinaryReader	reader( pFileName );

	create( &reader );
}

/************************************************************************************************/
/*
 * コンストラクタ
 * @param	pData			データ
 * @param	dataSize		データサイズ
 */
/************************************************************************************************/
KsFont::KsFont( const KsByte* pData, KsUInt32 dataSize )
	: m_lineSpacing( 0.0f )
	, m_pTexture( 0 )
	, m_pDefaultGlyph( 0 )
	, m_pGraphics( 0 )
{
	KsBinaryReader reader( pData, dataSize );
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsFont::~KsFont()
{
	destroy();
}

/************************************************************************************************/
/*
 * 生成する
 */
/************************************************************************************************/
void KsFont::create( const KsWChar* pFileName )
{
	KsBinaryReader	reader( pFileName );

	create( &reader );
}

/************************************************************************************************/
/*
 * 生成する
 */
/************************************************************************************************/
void KsFont::create( KsBinaryReader* pReader )
{
	// Validate the header.
	for( KsUInt8 const* magic = ksFontSignature; *magic; magic++ )
	{
		if( pReader->read<KsUInt8>() != *magic )
		{
			KsAssert( 0, "Not a MakeSpriteFont output binary" );
		}
	}

	// Read the glyph data.
	auto glyphCount = pReader->read<KsUInt32>();
	auto glyphData  = pReader->readArray<KsGlyph>(glyphCount);

	m_numGlyph = glyphCount;
	m_pGlyphs  = ksNew KsGlyph[ m_numGlyph ]; 

	KsMemCopy( m_pGlyphs, glyphData, m_numGlyph * sizeof(KsGlyph) );

	// Read font properties.
	m_lineSpacing = pReader->read<KsReal>();

	setDefaultCharacter((KsWChar)pReader->read<KsUInt32>());

	// Read the texture data.
	auto textureWidth  = pReader->read<KsUInt32>();
	auto textureHeight = pReader->read<KsUInt32>();
	auto textureFormat = pReader->read<KS_GI_FORMAT>();
	auto textureStride = pReader->read<KsUInt32>();
	auto textureRows   = pReader->read<KsUInt32>();
	auto textureData   = pReader->readArray<KsUInt8>(textureStride * textureRows);

	KS_SUBRESOURCE_DATA initData = { textureData, textureStride };

	KsRenderSystem*	pRS = KsRenderSystem::getInstancePtr();

	m_pTexture = pRS->createTexture( &initData, textureWidth, textureHeight, textureFormat, KS_BIND_SHADER_RESOURCE, KS_USAGE_IMMUTABLE );

	m_pGraphics = KsGraphics::getInstancePtr();
}

/************************************************************************************************/
/*
 * 破棄する
 */
/************************************************************************************************/
void KsFont::destroy()
{
	ksDELETEARRAY( m_pGlyphs );
	ksDELETE( m_pTexture );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
template<typename TAction> 
void KsFont::forEachGlyph( const KsWChar* pText, TAction action )
{
	KsReal x = 0.0f;
	KsReal y = 0.0f;

	for(; *pText; pText++ )
	{
		KsWChar character = *pText;

		switch( character )
		{
			case '\r':
			{
				// Skip carriage returns.
				continue;
			}
			case '\n':
			{
				// New line.
				x  = 0.0f;
				y += m_lineSpacing;
				break;
			}
			default:
			{
				// Output this character.
				const KsGlyph* pGlyph = findGlyph( character );

				x += pGlyph->XOffset;

				if( x < 0.0f )
				{
					x = 0.0f;
				}

				if( !iswspace( character ) )
				{
					action( pGlyph, x, y );
				}

				x += pGlyph->Subrect.w - pGlyph->Subrect.x + pGlyph->XAdvance;
				break;
			}
		}
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsFont::drawString( const KsWChar*  pText, KsInt32 x, KsInt32 y )
{
	KsVector2d offset;

	// Draw each character in turn.
	forEachGlyph(pText, [&](KsGlyph const* glyph, KsReal fx, KsReal fy)
	{
		offset.x = (KsReal)x + fx;
		offset.y = (KsReal)y + fy + glyph->YOffset;

		m_pGraphics->drawSprite( m_pTexture, offset.x, offset.y, (KsReal)(glyph->Subrect.w -glyph->Subrect.x), (KsReal)(glyph->Subrect.h -glyph->Subrect.y), 
			(KsReal)glyph->Subrect.x/256.0f, (KsReal)glyph->Subrect.y/112.0f,
			(KsReal)glyph->Subrect.w/256.0f, (KsReal)glyph->Subrect.h/112.0f );

		//spriteBatch->Draw(pImpl->texture.Get(), position, &glyph->Subrect, color, rotation, offset, scale, effects, layerDepth);
	});
}

void KsFont::drawString( const KsWChar* pText, const KsVector2d& position, KsColor color, KsReal rotation, const KsVector2d& origin, KsReal scale, ksSPRITE_EFFECTS effects, KsReal layerDepth )
{
#if 0
	// Lookup table indicates which way to move along each axis per SpriteEffects enum value.
	static KsVector2d axisDirectionTable[4] =
	{
		{ -1, -1 },
		{  1, -1 },
		{ -1,  1 },
		{  1,  1 },
	};

	// Lookup table indicates which axes are mirrored for each SpriteEffects enum value.
	static KsVector2d axisIsMirroredTable[4] =
	{
		{ 0, 0 },
		{ 1, 0 },
		{ 0, 1 },
		{ 1, 1 },
	};



	KsVector2d baseOffset = origin;

	// If the text is mirrored, offset the start position accordingly.
	if (effects)
	{
		//baseOffset -= measureString( pText ) * axisIsMirroredTable[effects & 3];
	}

	KsVector2d offset;

	// Draw each character in turn.
	forEachGlyph(pText, [&](KsGlyph const* glyph, KsReal x, KsReal y)
	{

		KsVector2d offset = XMVectorMultiplyAdd(XMVectorSet(x, y + glyph->YOffset, 0, 0), axisDirectionTable[effects & 3], baseOffset);
        
		if (effects)
		{
			XMVECTOR Result;
			Result.x = V1.x * V2.x + V3.x;
			Result.y = V1.y * V2.y+ V3.y;
			Result.z = V1.z * V2.z+ V3.z;
			Result.w = V1.w * V2.w+ V3.w;return Result;


			// For mirrored characters, specify bottom and/or right instead of top left.
			KsVector2d glyphRect = XMConvertVectorIntToFloat(XMLoadInt4(reinterpret_cast<uint32_t const*>(&glyph->Subrect)), 0);

			// xy = glyph width/height.
			glyphRect = XMVectorSwizzle<2, 3, 0, 1>(glyphRect) - glyphRect;

			offset = XMVectorMultiplyAdd(glyphRect, axisIsMirroredTable[effects & 3], offset);
		}

		m_pGraphics->drawSprite( m_pTexture, )

		spriteBatch->Draw(pImpl->texture.Get(), position, &glyph->Subrect, color, rotation, offset, scale, effects, layerDepth);
	});
#endif
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsFont::drawString( const KsSChar*  pText, const KsVector2d& position, KsColor color, KsReal rotation, const KsVector2d& origin, KsReal scale, ksSPRITE_EFFECTS effects, KsReal layerDepth )
{
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsFont::drawString( const KsString& rText, const KsVector2d& position, KsColor color, KsReal rotation, const KsVector2d& origin, KsReal scale, ksSPRITE_EFFECTS effects, KsReal layerDepth )
{
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsVector4d KsFont::measureString( const KsWChar* pText )
{
	KsVector4d result = KsVector4d::ZERO;

	forEachGlyph( pText, [&](KsGlyph const* glyph, KsReal x, KsReal y)
	{
		KsReal w = (KsReal)(glyph->Subrect.w - glyph->Subrect.x);
		KsReal h = (KsReal)(glyph->Subrect.h - glyph->Subrect.y) + glyph->YOffset;

		h = KsMax(h, m_lineSpacing);

		result = KsVector4d::Max( result, KsVector4d(x + w, y + h, 0, 0) );
	});

	return result;
}

/************************************************************************************************/
/* 
 *
 */
/************************************************************************************************/
KsInt32 KsFont::binarySearch( KsUInt32 key )
{
	KsInt32		left, right, center;
	
	left  = 0;
	right = m_numGlyph - 1;
	
	while( left <= right )
	{
		center = ( left + right ) / 2;
		
		if( m_pGlyphs[ center ].Character > key )
		{
			right = center - 1;
		}
		else if( m_pGlyphs[ center ].Character < key )
		{
			left = center + 1;
		}
		else
		{
			return center;
		}
	}

	return -1;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsBool KsFont::containsCharacter( KsWChar character )
{
	const KsInt32 index = binarySearch( (KsUInt32)character );

    return ( -1 != index );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
const KsGlyph* KsFont::findGlyph( KsWChar character )
{
	const KsInt32 index = binarySearch( (KsUInt32)character );

	if( -1 != index )
	{
		 return &m_pGlyphs[ index ];
	}

	if( m_pDefaultGlyph )
	{
		return m_pDefaultGlyph;
	}

	return NULL;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsWChar KsFont::getDefaultCharacter() const
{
    return m_pDefaultGlyph ? (KsWChar)m_pDefaultGlyph->Character : 0;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsFont::setDefaultCharacter( KsWChar character )
{
	m_pDefaultGlyph = NULL;

	if( character )
	{
		m_pDefaultGlyph = findGlyph( character );
	}
}

/************************************************************************************************/
/*
 * ラインスペースを取得する
 * @return	ラインスペース
 */
/************************************************************************************************/
KsReal KsFont::getLineSpacing() const
{
	return m_lineSpacing;
}

/************************************************************************************************/
/*
 * ラインスペースをセットする
 * @param	spacing	ラインスペース
 */
/************************************************************************************************/
void KsFont::setLineSpacing( KsReal spacing )
{
	m_lineSpacing = spacing;
}

