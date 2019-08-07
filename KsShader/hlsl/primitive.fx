/************************************************************************************************/
/** 
 * @file		line.fx
 * @brief		G-�o�b�t�@
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef PRIMITIVE_FX
#define PRIMITIVE_FX

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "Common.fxh"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @struct		VS_PRIMITIVE_INPUT
 * @brief		G-�o�b�t�@�o��,�\����
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
struct VS_PRIMITIVE_INPUT
{
	float3	Position    : POSITION;
	float4	Color       : COLOR;
};

/************************************************************************************************/
/**
 * @struct		VS_PRIMITIVE_OUTPUT
 * @brief		G-�o�b�t�@�o��,�\����
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
struct VS_PRIMITIVE_OUTPUT
{
	float4	Position    : SV_Position;
	float4	Color       : COLOR;
};


/************************************************************************************************/
/**
 * @struct		PS_OUTPUT
 * @brief		G-�o�b�t�@�o��,�\����
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
struct VS_PRIMITIVE_OUTPUT
{
	float4	Color : SV_Target0;
};


/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
VS_PRIMITIVE_OUTPUT VS_Primitive( VS_PRIMITIVE_INPUT In )
{
	VS_PRIMITIVE_OUTPUT	Out;

	float4	position = float4( In.Position, 1.0f );

	Out.Position = mul( position, WorldViewProj );
	Out.Color    = In.Color;

	return Out;
}

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
VS_PRIMITIVE_OUTPUT PS_Primitive( VS_PRIMITIVE_INPUT In )
{
	VS_PRIMITIVE_OUTPUT	Out;

	Out.Color = In.Color;

	return Out;
}



#endif // PRIMITIVE_FX
