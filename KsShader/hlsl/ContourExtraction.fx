/************************************************************************************************/
/** 
 * @file		ContourExtraction.fx
 * @brief		輪郭線を抽出する
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef CONTOUR_EXTRACTION_FX
#define CONTOUR_EXTRACTION_FX

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

Texture2D		g_NormalTexture : register( t0 );
Texture2D		g_ColorTexture  : register( t1 );
Texture2D		g_DepthTexture  : register( t3 );

SamplerState	g_NormalSampler : register( s0 )
{
	Filter   = MIN_MAG_MIP_LINEAR;
	AddressU = Clamp;
	AddressV = Clamp;
};

SamplerState	g_ColorSampler : register( s1 )
{
	Filter   = MIN_MAG_MIP_LINEAR;
	AddressU = Clamp;
	AddressV = Clamp;
};

SamplerState	g_DepthSampler : register( s3 )
{
	Filter   = MIN_MAG_MIP_LINEAR;
	AddressU = Clamp;
	AddressV = Clamp;
};

/************************************************************************************************/
/**
 * 球状環境マッピング
 * 環境マッピングの対象となる各頂点に指定するテクスチャ座標の公式
 * u = Nx/2 + 0.5
 * v = Ny/2 + 0.5
 */
/************************************************************************************************/
float3 KsDecodeSphereMap( float2 e )
{
	float2 tmp = e - e * e;
	float  f   = tmp.x + tmp.y;
	float  m   = sqrt( 4.0f * f - 1.0f );

	float3	n;

	n.xy = m * (e * 4.0f - 2.0f);
	n.z  = 3.0f - 8.0f * f;

	return n;
}

/************************************************************************************************/
/**
 * @struct		VS_INPUT
 * @brief		G-バッファ出力,構造体
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
struct VS_INPUT
{
	float3	Pos : POSITION;
	float2	Tex : TEXCOORD;
};

/************************************************************************************************/
/**
 * @struct		VS_OUTPUT
 * @brief		G-バッファ出力,構造体
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
struct VS_OUTPUT
{
	float4	Pos : SV_POSITION;
	float2	Tex : TEXCOORD;
};

/************************************************************************************************/
/**
 * 法線テクスチャから法線ベクトルを取得する
 */
/************************************************************************************************/
float3 KsGetNormalValue( float2 xy )
{
	float2	Normal = g_NormalTexture.Sample( g_NormalSampler, xy ).xy;

	return KsDecodeSphereMap( Normal );

	//return g_NormalTexture.Sample( g_NormalSampler, xy ).xyz;
}

/************************************************************************************************/
/**
 * ディフューズテクスチャからカラー値を取得する
 */
/************************************************************************************************/
float3 KsGetColorValue( float2 xy )
{
	return g_ColorTexture.Sample( g_ColorSampler, xy ).xyz;
}

/************************************************************************************************/
/**
 * 深度テクスチャから深度値を取得する
 */
/************************************************************************************************/
float KsGetDepthValue( float2 xy )
{
	return g_DepthTexture.Sample( g_DepthSampler, xy ).x;
}

/************************************************************************************************/
/**
 * エッジ検出
 */
/************************************************************************************************/
float KsEdge( float2 xy )
{
	float dx = 1.0/1280.0;
	float dy = 1.0/720.0;

	float3	oN = KsGetNormalValue( xy );
	float3	oC = KsGetColorValue ( xy );
	float	oZ = KsGetDepthValue ( xy );

	float3 dN1 = KsGetNormalValue( xy + float2( -dx,  0 ) );
	float3 dN2 = KsGetNormalValue( xy + float2(   0,-dy ) );
	float3 dN3 = KsGetNormalValue( xy + float2( -dx, dy ) );
	float3 dN4 = KsGetNormalValue( xy + float2( -dx,-dy ) );

	float  dZ1 = KsGetDepthValue( xy + float2( -dx,   0 ) );
	float  dZ2 = KsGetDepthValue( xy + float2(   0, -dy ) );
	float  dZ3 = KsGetDepthValue( xy + float2( -dx,  dy ) );
	float  dZ4 = KsGetDepthValue( xy + float2( -dx, -dy ) );

	float3 dC1 = KsGetColorValue( xy + float2( -dx,   0 ) );
	float3 dC2 = KsGetColorValue( xy + float2(   0, -dy ) );
	float3 dC3 = KsGetColorValue( xy + float2( -dx,  dy ) );
	float3 dC4 = KsGetColorValue( xy + float2( -dx, -dy ) );

	float  ddN  = dot( oN - dN1, oN - dN1 ) + dot( oN - dN2, oN - dN2 ) + 0.7f * dot( oN - dN3, oN - dN3 ) + 0.7f * dot( oN - dN4, oN - dN4 );
	float4 ddZZ = float4( oZ - dZ1, oZ - dZ2, 0.7f * ( oZ - dZ3 ), 0.7f * ( oZ - dZ4 ) );
	float  ddZ  = dot( ddZZ, ddZZ );
	float  ddC  = dot( oC - dC1, oC - dC1 ) + dot( oC - dC2, oC - dC2 ) + 0.7f * dot( oC - dC3, oC - dC3 ) + 0.7f * dot( oC - dC4, oC - dC4 );

	return saturate( max( 0.0f, ddN - 0.5f ) * 0.5f + max( 0.0f, ddZ - 0.0001f ) * 7000.0f + max( 0.0f, ddC - 0.02f ) * 15.0f );
}

float luminance( float3 color ) 
{
	return color.r*0.3 + color.g*0.59 + color.b*0.11; 
}

/************************************************************************************************/
/**
 * エッジ検出
 */
/************************************************************************************************/
float4 KsSobelFilter( float2 xy )
{
	float dx = 1.0/1280.0;
	float dy = 1.0/720.0;

	float UpLeft    = luminance( KsGetColorValue( xy + float2(  -dx,  -dy) ) ); 
	float Up        = luminance( KsGetColorValue( xy + float2( 0.0f,  -dy) ) ); 
	float UpRight   = luminance( KsGetColorValue( xy + float2(   dx,  -dy) ) ); 
	float Left      = luminance( KsGetColorValue( xy + float2(  -dx,  -dy) ) ); 
	float Right     = luminance( KsGetColorValue( xy + float2(   dx,  -dy) ) ); 
	float DownLeft  = luminance( KsGetColorValue( xy + float2(  -dx,   dy) ) ); 
	float Down      = luminance( KsGetColorValue( xy + float2( 0.0f,   dy) ) ); 
	float DownRight = luminance( KsGetColorValue( xy + float2(   dx,   dy) ) );

	float dX = -UpLeft - 2.0*Left - DownLeft + UpRight  + 2.0*Right + DownRight;
	float dY = -UpLeft - 2.0*Up   - UpRight  + DownLeft + 2.0*Down  + DownRight;

	float4 color = 1 - sqrt( dX*dX + dY*dY ); 
	color.w = 1.0;

	return color;
}

/************************************************************************************************/
/**
 * 頂点シェーダー
 */
/************************************************************************************************/
VS_OUTPUT VS_ContourExtraction( VS_INPUT In )
{
	// 出力データ
	VS_OUTPUT Out = (VS_OUTPUT)0;

	Out.Pos = float4( In.Pos, 1.0f );
	Out.Tex = In.Tex;

	return Out;
}

/************************************************************************************************/
/**
 * ピクセルシェーダー
 */
/************************************************************************************************/
float4 PS_ContourExtraction( VS_OUTPUT In ) : SV_Target
{
	//return float4( ( 1.0f - KsEdge( In.Tex ) ) * float3( 1.0f, 1.0f, 1.0f ), 1.0f );

	//return float4( ( 1.0f - KsEdge( In.Tex ) ) * float3( 1.0f, 1.0f, 1.0f ), 1.0f );
	
	float3 color = KsGetColorValue ( In.Tex );

	return float4( color * ( 1.0f - KsEdge( In.Tex ) ), 1.0f );

	//#define FrontColor	float4(0,0,0,1)	// 前景色
	//#define BackColor	float4(1,1,1,1)	// 背景色
	//float4 edge  = lerp( BackColor, FrontColor, KsEdge( In.Tex ) );
	//float4 color = float4( KsGetColorValue ( In.Tex ), 1.0f );
	//float  Tr    = 0.6f;

	//return lerp( color, edge, Tr );

	//return float4( KsGetNormalValue( In.Tex ), 1.0f );
	//return float4( KsGetColorValue( In.Tex ), 1.0f );
	//return KsSobelFilter( In.Tex );
}

#if 0
FxaaFloat4 FxaaPixelShader(
    pos,
    posPos,
    tex,
    tex,                        // these will be different for 360
    tex,                        // these will be different for 360
    rcpFrame,
    fxaaConsoleRcpFrameOpt,     // this is new
    fxaaConsoleRcpFrameOpt2,    // this is new 
    fxaaConsole360RcpFrameOpt2, // this is new
    0.75,                       // FXAA_QUALITY__SUBPIX
    0.166,                      // FXAA_QUALITY__EDGE_THRESHOLD
    0.0833,                     // FXAA_QUALITY__EDGE_THRESHOLD_MIN
    8.0,                        // FXAA_CONSOLE__EDGE_SHARPNESS
    0.125,                      // FXAA_CONSOLE__EDGE_THRESHOLD
    0.05,                       // FXAA_CONSOLE__EDGE_THRESHOLD_MIN
    fxaaConsole360ConstDir      // this is new
)


/************************************************************************************************/
/**
 * ピクセルシェーダー
 */
/************************************************************************************************/
float4 PS_MixBorderLine( VS_OUTPUT In ) : SV_Target
{
	return float4( ( 1.0f - KsEdge( In.Tex ) ) * float3( 1.0f, 1.0f, 1.0f ), 1.0f );
}

float4 MixPS(float2 Tex:TEXCOORD0, float2 MapTex:TEXCOORD1):COLOR{
	float e0=   0.25f*tex2D(EdgeMapSampler,MapTex)
				+ 0.125f*(tex2D(EdgeMapSampler,MapTex + float2(0,-1)*BasePosScale)
						+ tex2D(EdgeMapSampler,MapTex + float2(0,1)*BasePosScale)
						+ tex2D(EdgeMapSampler,MapTex + float2(1,0)*BasePosScale)
						+ tex2D(EdgeMapSampler,MapTex + float2(-1,0)*BasePosScale) )
				+ 0.0625f*(tex2D(EdgeMapSampler,MapTex + float2(-1,-1)*BasePosScale)
						+ tex2D(EdgeMapSampler,MapTex + float2(1,1)*BasePosScale)
						+ tex2D(EdgeMapSampler,MapTex + float2(1,-1)*BasePosScale)
						+ tex2D(EdgeMapSampler,MapTex + float2(-1,1)*BasePosScale) );
	return lerp(tex2D(ColorMapSampler,Tex), float4(e0,e0,e0,1) ,Tr);
}
#endif

#endif // CONTOUR_EXTRACTION_FX

