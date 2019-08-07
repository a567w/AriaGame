/************************************************************************************************/
/** 
 * @file		PMDSkinModel.fx
 * @brief		PMD モデルシェダー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
#define MaxBones 256

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

//------------------------------------------------------------------------------------------------
// Input parameters.
//------------------------------------------------------------------------------------------------
cbuffer cbMMDBuffers : register( b0 )
{
	float4x4	WorldViewProj;					// ビュー,プロジェクションマトリックス
	float4x4	WorldView;
	float4x4	ViewProj;
	float4x4	Proj;
	float4x4	World;							// ワールドマトリックス
	float4x4	MatrixPalette[ MaxBones ];		// マトリックスパレット
    float4		CameraNearFar;
    uint4		FramebufferDimensions;
};


// Diffuse Texture
Texture2D textureDiffuse : register( t0 );

SamplerState samplerLinear : register( s0 )
{
	Filter   = MIN_MAG_MIP_LINEAR;
	AddressU = Clamp;
	AddressV = Clamp;
};

//texture textureDiffuse;
//sampler samplerLinear = sampler_state
//{
//    Texture = (textureDiffuse);
//    MinFilter = Linear;
//    MagFilter = Linear;
//    MipFilter = Linear;
//};


// Vertex shader input structure.
struct VS_INPUT
{
    float3 Position : POSITION;
    float3 Normal : NORMAL;
    float2 TexCoord : TEXCOORD;
    uint4 BoneIndices : BLENDINDICES;
    float4 BoneWeights : BLENDWEIGHT;
};


// Vertex shader output structure.
struct VS_OUTPUT
{
    float2 TexCoord : TEXCOORD0;
	float  Depth    : TEXCOORD1;
	float3 Normal   : NORMAL;
	float4 Position : SV_POSITION;
};

// Pixel shader input structure.
struct PS_INPUT
{
    float2 TexCoord : TEXCOORD0;
	float  Depth    : TEXCOORD1;
	float3 Normal   : NORMAL;
};

struct PS_OUTPUT
{
	float4 TextureColor : SV_Target0;
	float4 NormalColor  : SV_Target1;
	float4 DepthColor   : SV_Target2;
};

VS_OUTPUT VertexShaderPMD( VS_INPUT In )
{
    VS_OUTPUT	Out;
    
    // Blend between the weighted bone matrices.
    float4x4 skinTransform = 0;
   
    skinTransform += MatrixPalette[In.BoneIndices.x] * In.BoneWeights.x;
    skinTransform += MatrixPalette[In.BoneIndices.y] * In.BoneWeights.y;
    skinTransform += MatrixPalette[In.BoneIndices.z] * In.BoneWeights.z;
    skinTransform += MatrixPalette[In.BoneIndices.w] * In.BoneWeights.w;
  
	float4	position = float4( In.Position, 1.0f );
    position = mul(position, skinTransform);
    
	Out.Position = mul( position, WorldViewProj );

    // Skin the vertex normal, then compute lighting.
    float3 normal = normalize(mul(In.Normal, skinTransform));
    
    Out.TexCoord = In.TexCoord;
	Out.Normal   = normal;
    Out.Depth.x  = -1 + 1000.0f*( 1 - (Out.Position.z/Out.Position.w) );
    
    return Out;
}





// Pixel shader program.
PS_OUTPUT PixelShaderPMD( PS_INPUT In )
{
	PS_OUTPUT		Out;

	//float4 color = tex2D( samplerLinear, In.TexCoord );
	float4 color = textureDiffuse.Sample( samplerLinear, In.TexCoord );

	Out.TextureColor = color;
	Out.NormalColor  = float4( In.Normal, 1.0f );

    // The depth is Z divided by W. We return
    // this value entirely in a 32-bit red channel
    // using SurfaceFormat.Single.  This preserves the
    // floating-point data for finer detail.
	Out.DepthColor   = float4( In.Depth.x, In.Depth.x, In.Depth.x, 1 );

	return Out;
}



