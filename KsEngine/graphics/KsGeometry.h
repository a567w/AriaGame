/************************************************************************************************/
/** 
 * @file		KsGeometry.h
 * @brief		ジオメトリ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSGEOMETRY_H__
#define __KSGEOMETRY_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
#define ksGEOMETRY_FVF_PNT	( ksFVF_XYZ | ksFVF_NORMAL | ksFVF_TEX )

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

struct KS_VERTEX_PC
{
    KsVector3d		Position;
    KsColorReal		Color;
};

struct KS_VERTEX_PT
{
    KsVector3d		Position;
    KsVector2d		TextureCoord;
};

struct KS_VERTEX_PN
{
    KsVector3d		Position;
    KsVector3d		Normal;
};


struct KS_VERTEX_PCT
{
    KsVector3d		Position;
    KsColorReal		Color;
    KsVector2d		TextureCoord;
};


struct KS_VERTEX_PNC
{
    KsVector3d		Position;
    KsVector3d		Normal;
	KsColorReal		Color;
};

struct KS_VERTEX_PNT
{
    KsVector3d		Position;
    KsVector3d		Normal;
    KsVector2d		TextureCoord;
};

struct KS_VERTEX_PNCT
{
    KsVector3d		Position;
    KsVector3d		Normal;
	KsColorReal		Color;
    KsVector2d		TextureCoord;
};



/************************************************************************************************/
/**
 * @class		KsGeometry
 * @brief		ジオメトリ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsGeometry
{
	public:
		KsGeometry();
		~KsGeometry();
        
		// Factory methods.
		KsBool				createCube     ( KsReal size     = 1, KsBool   rhcoords = ksTRUE );
		KsBool				createSphere   ( KsReal diameter = 1, KsUInt32 tessellation = 16,     KsBool   rhcoords     = ksTRUE );
#if 0
		KsBool				createGeoSphere( KsReal diameter = 1, KsUInt32 tessellation = 3,      KsBool   rhcoords     = ksTRUE );
		KsBool				createCylinder ( KsReal height   = 1, KsReal   diameter     = 1,      KsUInt32 tessellation = 32, KsBool rhcoords = ksTRUE );
		KsBool				createTorus    ( KsReal diameter = 1, KsReal   thickness    = 0.333f, KsUInt32 tessellation = 32, KsBool rhcoords = ksTRUE );
#endif
		// Draw the primitive.
		void				draw( KsMatrix4x4 world, KsMatrix4x4 view, KsMatrix4x4 projection, KsColor color = KsColor::WHITE, KsTexture* texture = nullptr, KsBool wireframe = ksFALSE );

		// Draw the primitive using a custom effect.
		void				draw( KsEffect* effect, KsInputLayout* inputLayout, KsBool alpha = ksFALSE, KsBool wireframe = ksFALSE );

		// create input layout for drawing with a custom effect.
		void				createInputLayout( KsEffect* effect, KsInputLayout** inputLayout );
        
	private:
		KsInputLayout*		m_pInputLayout;		/**< 頂点レイアウト		*/
		KsVertexBuffer*		m_pVertexBuffer;	/**< 頂点バッファ			*/
		KsIndexBuffer*		m_pIndexBuffer;		/**< インデックスバッファ	*/
		KsVertexShader*		m_pVShader;			/**< Vertex Shader		*/
		KsPixelShader*		m_pPShader;			/**< Pixel Shader		*/
};

#if 0

struct VSInput
{
    float4 Position : SV_Position;
};

struct VSInputVc
{
    float4 Position : SV_Position;
    float4 Color    : COLOR;
};

struct VSInputTx
{
    float4 Position : SV_Position;
    float2 TexCoord : TEXCOORD0;
};

struct VSInputTxVc
{
    float4 Position : SV_Position;
    float2 TexCoord : TEXCOORD0;
    float4 Color    : COLOR;
};

struct VSInputNm
{
    float4 Position : SV_Position;
    float3 Normal   : NORMAL;
};

struct VSInputNmVc
{
    float4 Position : SV_Position;
    float3 Normal   : NORMAL;
    float4 Color    : COLOR;
};

struct VSInputNmTx
{
    float4 Position : SV_Position;
    float3 Normal   : NORMAL;
    float2 TexCoord : TEXCOORD0;
};

struct VSInputNmTxVc
{
    float4 Position : SV_Position;
    float3 Normal   : NORMAL;
    float2 TexCoord : TEXCOORD0;
    float4 Color    : COLOR;
};

struct VSInputTx2
{
    float4 Position  : SV_Position;
    float2 TexCoord  : TEXCOORD0;
    float2 TexCoord2 : TEXCOORD1;
};

struct VSInputTx2Vc
{
    float4 Position  : SV_Position;
    float2 TexCoord  : TEXCOORD0;
    float2 TexCoord2 : TEXCOORD1;
    float4 Color     : COLOR;
};

struct VSInputNmTxWeights
{
    float4 Position : SV_Position;
    float3 Normal   : NORMAL;
    float2 TexCoord : TEXCOORD0;
    uint4  Indices  : BLENDINDICES0;
    float4 Weights  : BLENDWEIGHT0;
};



// Vertex shader output structures.

struct VSOutput
{
    float4 Diffuse    : COLOR0;
    float4 Specular   : COLOR1;
    float4 PositionPS : SV_Position;
};

struct VSOutputNoFog
{
    float4 Diffuse    : COLOR0;
    float4 PositionPS : SV_Position;
};

struct VSOutputTx
{
    float4 Diffuse    : COLOR0;
    float4 Specular   : COLOR1;
    float2 TexCoord   : TEXCOORD0;
    float4 PositionPS : SV_Position;
};

struct VSOutputTxNoFog
{
    float4 Diffuse    : COLOR0;
    float2 TexCoord   : TEXCOORD0;
    float4 PositionPS : SV_Position;
};

struct VSOutputPixelLighting
{
    float4 PositionWS : TEXCOORD0;
    float3 NormalWS   : TEXCOORD1;
    float4 Diffuse    : COLOR0;
    float4 PositionPS : SV_Position;
};

struct VSOutputPixelLightingTx
{
    float2 TexCoord   : TEXCOORD0;
    float4 PositionWS : TEXCOORD1;
    float3 NormalWS   : TEXCOORD2;
    float4 Diffuse    : COLOR0;
    float4 PositionPS : SV_Position;
};

struct VSOutputTx2
{
    float4 Diffuse    : COLOR0;
    float4 Specular   : COLOR1;
    float2 TexCoord   : TEXCOORD0;
    float2 TexCoord2  : TEXCOORD1;
    float4 PositionPS : SV_Position;
};

struct VSOutputTx2NoFog
{
    float4 Diffuse    : COLOR0;
    float2 TexCoord   : TEXCOORD0;
    float2 TexCoord2  : TEXCOORD1;
    float4 PositionPS : SV_Position;
};

struct VSOutputTxEnvMap
{
    float4 Diffuse    : COLOR0;
    float4 Specular   : COLOR1;
    float2 TexCoord   : TEXCOORD0;
    float3 EnvCoord   : TEXCOORD1;
    float4 PositionPS : SV_Position;
};



// Pixel shader input structures.

struct PSInput
{
    float4 Diffuse  : COLOR0;
    float4 Specular : COLOR1;
};

struct PSInputNoFog
{
    float4 Diffuse : COLOR0;
};

struct PSInputTx
{
    float4 Diffuse  : COLOR0;
    float4 Specular : COLOR1;
    float2 TexCoord : TEXCOORD0;
};

struct PSInputTxNoFog
{
    float4 Diffuse  : COLOR0;
    float2 TexCoord : TEXCOORD0;
};

struct PSInputPixelLighting
{
    float4 PositionWS : TEXCOORD0;
    float3 NormalWS   : TEXCOORD1;
    float4 Diffuse    : COLOR0;
};

struct PSInputPixelLightingTx
{
    float2 TexCoord   : TEXCOORD0;
    float4 PositionWS : TEXCOORD1;
    float3 NormalWS   : TEXCOORD2;
    float4 Diffuse    : COLOR0;
};

struct PSInputTx2
{
    float4 Diffuse   : COLOR0;
    float4 Specular  : COLOR1;
    float2 TexCoord  : TEXCOORD0;
    float2 TexCoord2 : TEXCOORD1;
};

struct PSInputTx2NoFog
{
    float4 Diffuse   : COLOR0;
    float2 TexCoord  : TEXCOORD0;
    float2 TexCoord2 : TEXCOORD1;
};

struct PSInputTxEnvMap
{
    float4 Diffuse  : COLOR0;
    float4 Specular : COLOR1;
    float2 TexCoord : TEXCOORD0;
    float3 EnvCoord : TEXCOORD1;
};

#endif


#endif		/* __KSGEOMETRY_H__ */

