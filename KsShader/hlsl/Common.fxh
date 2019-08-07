/************************************************************************************************/
/** 
 * @file		Common.fxh
 * @brief		���ʃf�[�^
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef COMMON_FXH
#define COMMON_FXH

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/
#define MAX_LIGHTS_POWER				10
#define MAX_LIGHTS						(1<<MAX_LIGHTS_POWER)
#define COMPUTE_SHADER_TILE_GROUP_DIM	16
#define COMPUTE_SHADER_TILE_GROUP_SIZE	(COMPUTE_SHADER_TILE_GROUP_DIM*COMPUTE_SHADER_TILE_GROUP_DIM)
#define DEFER_PER_SAMPLE				1
#define MSAA_SAMPLES					1
#define MAX_BONES						256

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @struct		KsSurfaceData
 * @brief		�T�[�t�F�[�X�f�[�^�\����
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
struct KsSurfaceData
{
	float3		PositionView;		// View space position
	float3		PositionViewDX;		// Screen space derivatives
	float3		PositionViewDY;		// of view space position
	float3		Normal;				// View space normal
	float4		Albedo;				// �f�B�t���[�Y
	float		SpecularAmount;		// ���˗�
	float		SpecularPower;		// �X�y�L�����p���[
};

/************************************************************************************************/
/**
 * @struct		UIConstants
 * @brief		�T�[�t�F�[�X�f�[�^�\����
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
struct UIConstants
{
	uint lightingOnly;
	uint faceNormals;
	uint visualizeLightCount;
	uint visualizePerSampleShading;
	uint lightCullTechnique;
};

/************************************************************************************************/
/**
 * @cbuffer		cbGBuffers
 * @brief		G-�o�b�t�@�o��,�\����
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
cbuffer cbGBuffers : register( b0 )
{
	float4x4			WorldViewProj;				// �r���[,�v���W�F�N�V�����}�g���b�N�X
	float4x4			WorldView;					// �v���W�F�N�V�����}�g���b�N�X
	float4x4			ViewProj;					// �v���W�F�N�V�����}�g���b�N�X
	float4x4			Proj;						// ���[���h�}�g���b�N�X
	float4x4			World;						// ���[���h�}�g���b�N�X
	float4				CameraNearFar;
	uint4				FramebufferDimensions;
	UIConstants			mUI;
};

/************************************************************************************************/
/**
 * @cbuffer		cbGBuffers
 * @brief		G-�o�b�t�@�o��,�\����
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
cbuffer cbMatrixPallet : register( b1 )
{
	float4x4			MatrixPalette[ MAX_BONES ];		// �}�g���b�N�X�p���b�g
};



/************************************************************************************************/
/**
 * �ŏ��l�ƍő�l�̋�Ԃň��������j�A��Ԃ������ʂ�\���A0 �` 1 �͈̔͂Ɏʑ��������l��Ԃ��܂��B
 */
/************************************************************************************************/
float linstep(float min, float max, float v)
{
	// saturate : �w�肳�ꂽ�l�� 0 �` 1 �͈̔͂ɃN�����v���܂��B
	return saturate((v - min) / (max - min));
}

/************************************************************************************************/
/**
 * RGBA 16-bit per component packed into a uint2 per texel
 */
/************************************************************************************************/
float4 UnpackRGBA16(uint2 e)
{
	return float4(f16tof32(e), f16tof32(e >> 16));
}

/************************************************************************************************/
/**
 * �J���[�l float4 �� uint2�ɕϊ�����
 */
/************************************************************************************************/
uint2 PackRGBA16(float4 c)
{
	return f32tof16(c.rg) | (f32tof16(c.ba) << 16);
}

/************************************************************************************************/
/**
 * Linearize the given 2D address + sample index into our flat framebuffer array
 */
/************************************************************************************************/
uint GetFramebufferSampleAddress(uint2 coords, uint sampleIndex)
{
	// Major ordering: Row (x), Col (y), MSAA sample
	return (sampleIndex * FramebufferDimensions.y + coords.y) * FramebufferDimensions.x + coords.x;
}

#endif // COMMON_FXH

