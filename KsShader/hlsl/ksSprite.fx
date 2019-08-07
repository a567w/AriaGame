//--------------------------------------------------------------------------------------
// File: Tutorial02.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

Texture2D txDiffuse : register( t0 );
SamplerState samLinear : register( s0 )
{
	Filter   = MIN_MAG_MIP_LINEAR;
	AddressU = Clamp;
	AddressV = Clamp;
};

//-------------------------------------------------------------
// �e��ϐ�
//-------------------------------------------------------------
cbuffer cbSpriteBuffers : register( b0 )
{
	float2		g_f2PosScale;
	float4		g_f4BaseColor;
};

//--------------------------------------------------------------------------------------
struct VS_INPUT
{
    float4 Pos : POSITION;
    float2 Tex : TEXCOORD0;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD0;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS( VS_INPUT input )
{
    PS_INPUT output = (PS_INPUT)0;
    output.Pos = input.Pos;
    output.Tex = input.Tex;
    
    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( PS_INPUT input ) : SV_Target
{
    //return float4( 1.0f, 1.0f, 0.0f, 1.0f );    // Yellow, with Alpha = 1
	//return g_f4BaseColor;

    //return txDiffuse.Sample( samLinear, input.Tex ) * g_f4BaseColor;

	return txDiffuse.Sample( samLinear, input.Tex );
	//return float4( input.Tex, 0.0f, 1.0f );
}

// For a release build
//fxc /T fx_4_0 /Fo BasicHLSL10.fxo BasicHLSL10.fx
//���̗�̐����́A���̂Ƃ���ł��B
//fx_4_0 �́A�^�[�Q�b�g �v���t�@�C���ł��B
//BasicHLSL10.fxo �́A�R���p�C�����ꂽ�G�t�F�N�g���܂ޏo�̓I�u�W�F�N�g �t�@�C���ł��B
//BasicHLSL10.fx �͓��̓G�t�F�N�g �t�@�C���ł��B
// For a debug build
//fxc /Od /Zi /T fx_4_0 /Fo BasicHLSL10.fxo BasicHLSL10.fx

