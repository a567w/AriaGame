/************************************************************************************************/
/** 
 * @file		sprite.fx
 * @brief		短形塗りつぶし
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

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
cbuffer cbGraphics2DBuffers : register( b0 )
{
	float4		BaseColor;
	float2		BasePosScale;
};


Texture2D txDiffuse : register( t0 );

SamplerState samLinear : register( s0 )
{
	Filter   = MIN_MAG_MIP_LINEAR;
	AddressU = Clamp;
	AddressV = Clamp;
};

//-------------------------------------------------------------
// 頂点シェーダーへの入力データ
//-------------------------------------------------------------
struct VS_INPUT
{
	float3 Pos		: POSITION;     // 頂点位置
	float4 Color	: COLOR;		// 色
	float2 Tex		: TEXCOORD;
};

//-------------------------------------------------------------
// 頂点シェーダーからの出力データ
//-------------------------------------------------------------
struct VS_OUTPUT
{
	float4 Pos		: SV_POSITION;		// 位置
	float4 Color	: COLOR0;			// 色
	float2 Tex		: TEXCOORD0;
};


//-------------------------------------------------------------
// 頂点シェーダー
//-------------------------------------------------------------
VS_OUTPUT VS_Sprite( VS_INPUT In )
{                
    // 出力データ
    VS_OUTPUT Out = (VS_OUTPUT)0;

    // 座標変換
	Out.Pos.x =  ( ( In.Pos.x - 0.5f ) * BasePosScale.x - 1.0f );
	Out.Pos.y = -( ( In.Pos.y - 0.5f ) * BasePosScale.y - 1.0f );
	Out.Pos.z = In.Pos.z;
	Out.Pos.w = 1.0f;
	Out.Color = In.Color;
	Out.Tex   = In.Tex;

    return Out;
}


//-------------------------------------------------------------
// 頂点シェーダー
//-------------------------------------------------------------
float4 PS_Sprite( VS_OUTPUT In ) : SV_Target
{
	float4 color = txDiffuse.Sample( samLinear, In.Tex ) * In.Color;

	if( color.a == 0.0f )
	{
		discard;
	}

	return color;
}

