/************************************************************************************************/
/** 
 * @file		KsRenderState.h
 * @brief		�`��X�e�[�g
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSRENDERSTATE_H__
#define __KSRENDERSTATE_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsColor.h"
#include "KsLight.h"
#include "KsMaterial.h"
#include "KsViewport.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/
#define ksRENDER_TARGET_BACKBUFFER_SURFACE		( 0 )
#define ksRENDER_TARGET_DEPTHSTENCIL_SURFACE	( 1<<0 )
#define ksRENDER_TARGET_BACKBUFFER_TEXTURE		( 1<<1 )
#define ksRENDER_TARGET_DEPTHSTENCIL_TEXTURE	( 1<<2 )

#define ksLIGHT_MAX				( 4 )		/**< ���C�g�̍ő吔						*/
#define ksRENDER_STATE_STACK_MAX	( 16 )		/**< �����_�[�X�e�[�g�ő�X�^�b�N�T�C�Y	*/

/* �N���A�[�r�b�g */
#define ksCLEAR_FLAG_COLOR			( 1<<0 )	/**< �J���[�N���A�t���O					*/
#define ksCLEAR_FLAG_DEPTH			( 1<<1 )	/**< �[�x�o�b�t�@�N���A�t���O			*/
#define ksCLEAR_FLAG_STENCIL		( 1<<2 )	/**< �X�e���V���o�b�t�@�N���A�t���O		*/
#define ksCLEAR_FLAG_ACCUM			( 1<<3 )	/**< �A�L���[�����t�o�b�t�@				*/

#define ksLOCK_DISCARD				( 0 )
#define ksLOCK_DONOTWAIT			( 1 )
#define ksLOCK_NO_DIRTY_UPDATE		( 2 )
#define ksLOCK_NOOVERWRITE			( 3 )
#define ksLOCK_NOSYSLOCK			( 4 )
#define ksLOCK_READONLY				( 5 )

#define ksFVF_NONE					( 0x000 )
#define ksFVF_POSITION_MASK			( 0x00E )
#define ksFVF_XYZ					( 0x002 )
#define ksFVF_XYZRHW				( 0x004 )
#define ksFVF_XYZB1					( 0x006 )
#define ksFVF_XYZB2					( 0x008 )
#define ksFVF_XYZB3					( 0x00a )
#define ksFVF_XYZB4					( 0x00c )
#define ksFVF_XYZB5					( 0x00e )
#define ksFVF_NORMAL				( 0x010 )
#define ksFVF_DIFFUSE				( 0x040 )
#define ksFVF_SPECULAR				( 0x080 )

#define ksFVF_TEXCOUNT_MASK			( 0xf00 )
#define ksFVF_TEXCOUNT_SHIFT		( 8 )
#define ksFVF_TEX					( 0x100 )
#define ksFVF_TEX1					( 0x100 )
#define ksFVF_TEX2					( 0x200 )
#define ksFVF_TEX3					( 0x300 )
#define ksFVF_TEX4					( 0x400 )
#define ksFVF_TEX5					( 0x500 )
#define ksFVF_TEX6					( 0x600 )
#define ksFVF_TEX7					( 0x700 )
#define ksFVF_TEX8					( 0x800 )

#define ksFVF_INDICES				( 0x901 )
#define ksFVF_WEIGHT				( 0x910 )

#define ksFVF_LASTBETA_COLOR		( 0x1000 )
#define ksFVF_LASTBETA_UBYTE4		( 0x2000 )

#define ksFMT_INDEX16				( 0 )
#define ksFMT_INDEX32				( 1 )

#define ksFLAG_CPU_ACCESS_NONE		( 0 )
#define ksFLAG_CPU_ACCESS_WRITE		( 1 )
#define ksFLAG_CPU_ACCESS_READ		( 2 )

enum ksDECLUSAGE
{
    ksDECLUSAGE_POSITION = 0,
    ksDECLUSAGE_BLENDWEIGHT,   // 1
    ksDECLUSAGE_BLENDINDICES,  // 2
    ksDECLUSAGE_NORMAL,        // 3
    ksDECLUSAGE_PSIZE,         // 4
    ksDECLUSAGE_TEXCOORD,      // 5
    ksDECLUSAGE_TANGENT,       // 6
    ksDECLUSAGE_BINORMAL,      // 7
    ksDECLUSAGE_TESSFACTOR,    // 8
    ksDECLUSAGE_POSITIONT,     // 9
    ksDECLUSAGE_COLOR,         // 10
    ksDECLUSAGE_FOG,           // 11
    ksDECLUSAGE_DEPTH,         // 12
    ksDECLUSAGE_SAMPLE,        // 13
};

#define MAXD3DDECLUSAGE         D3DDECLUSAGE_SAMPLE
#define MAXD3DDECLUSAGEINDEX    15
#define MAXD3DDECLLENGTH        64 // does not include "end" marker vertex element


enum ksDECLMETHOD
{
    ksDECLMETHOD_DEFAULT = 0,
    ksDECLMETHOD_PARTIALU,
    ksDECLMETHOD_PARTIALV,
    ksDECLMETHOD_CROSSUV,    // Normal
    ksDECLMETHOD_UV,
    ksDECLMETHOD_LOOKUP,               // Lookup a displacement map
    ksDECLMETHOD_LOOKUPPRESAMPLED,     // Lookup a pre-sampled displacement map
};

// Declarations for _Type fields
//
enum ksDECLTYPE
{
    ksDECLTYPE_FLOAT1    =  0,  // 1D float expanded to (value, 0., 0., 1.)
    ksDECLTYPE_FLOAT2    =  1,  // 2D float expanded to (value, value, 0., 1.)
    ksDECLTYPE_FLOAT3    =  2,  // 3D float expanded to (value, value, value, 1.)
    ksDECLTYPE_FLOAT4    =  3,  // 4D float
    ksDECLTYPE_COLOR  =  4,  // 4D packed unsigned bytes mapped to 0. to 1. range
                                 // Input is in D3DCOLOR format (ARGB) expanded to (R, G, B, A)
    ksDECLTYPE_UBYTE4    =  5,  // 4D unsigned byte
    ksDECLTYPE_SHORT2    =  6,  // 2D signed short expanded to (value, value, 0., 1.)
    ksDECLTYPE_SHORT4    =  7,  // 4D signed short

// The following types are valid only with vertex shaders >= 2.0


    ksDECLTYPE_UBYTE4N   =  8,  // Each of 4 bytes is normalized by dividing to 255.0
    ksDECLTYPE_SHORT2N   =  9,  // 2D signed short normalized (v[0]/32767.0,v[1]/32767.0,0,1)
    ksDECLTYPE_SHORT4N   = 10,  // 4D signed short normalized (v[0]/32767.0,v[1]/32767.0,v[2]/32767.0,v[3]/32767.0)
    ksDECLTYPE_USHORT2N  = 11,  // 2D unsigned short normalized (v[0]/65535.0,v[1]/65535.0,0,1)
    ksDECLTYPE_USHORT4N  = 12,  // 4D unsigned short normalized (v[0]/65535.0,v[1]/65535.0,v[2]/65535.0,v[3]/65535.0)
    ksDECLTYPE_UDEC3     = 13,  // 3D unsigned 10 10 10 format expanded to (value, value, value, 1)
    ksDECLTYPE_DEC3N     = 14,  // 3D signed 10 10 10 format normalized and expanded to (v[0]/511.0, v[1]/511.0, v[2]/511.0, 1)
    ksDECLTYPE_FLOAT16_2 = 15,  // Two 16-bit floating point values, expanded to (value, value, 0, 1)
    ksDECLTYPE_FLOAT16_4 = 16,  // Four 16-bit floating point values
    ksDECLTYPE_UNUSED    = 17,  // When the type field in a decl is unused.
};


// This is used to initialize the last vertex element in a vertex declaration
// array
//
#define ksDECL_END() { 0xFF, 0, ksDECLTYPE_UNUSED, 0, 0, 0 }

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * �g�����X�t�H�[���̎��
 */
/************************************************************************************************/
typedef enum _ksTRANSFORM_STATE
{
	ksTRANSFORM_WORLD,				/**< ���[���h						*/
	ksTRANSFORM_VIEW,				/**< �r���[							*/
	ksTRANSFORM_PROJECTION,			/**< �v���W�F�N�V����				*/
	ksTRANSFORM_TEXTURE0,			/**< �e�N�X�`��0					*/
	ksTRANSFORM_TEXTURE1,			/**< �e�N�X�`��1					*/
	ksTRANSFORM_TEXTURE2,			/**< �e�N�X�`��2					*/
	ksTRANSFORM_TEXTURE3,			/**< �e�N�X�`��3					*/
	ksTRANSFORM_TEXTURE4,			/**< �e�N�X�`��4					*/
	ksTRANSFORM_TEXTURE5,			/**< �e�N�X�`��5					*/

}ksTRANSFORM_STATE;

/************************************************************************************************/
/**
 * �e�N�X�`���X�e�[�g
 */
/************************************************************************************************/
typedef enum _ksTEXTURE_STATE_TYPE
{
	ksTEXTURE_STATE_COLOR_OP  = 0,			/**< �e�N�X�`���t�@���N�V����				*/
	ksTEXTURE_STATE_ADDRESSU  = 1,			/**< �e�N�X�`�����W u �����̃��b�v���[�h 	*/
	ksTEXTURE_STATE_ADDRESSV  = 2,			/**< �e�N�X�`�����W v �����̃��b�v���[�h	*/
	ksTEXTURE_STATE_MAGFILTER = 3,			/**< �g��t�B���^						*/
	ksTEXTURE_STATE_MINFILTER = 4,			/**< �k���t�B���^						*/
	ksTEXTURE_STATE_MIPFILTER = 5,			/**< �~�b�v�}�b�v�t�B���^					*/
	ksTEXTURE_STATE_FORCE32   = 0x7fffffff,	/**< �����I��32bit�ɂ���					*/

}ksTEXTURE_STATE_TYPE;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef enum _ksTEXTURE_COLOR_OP_MODE
{
	ksTEXTURE_COLOR_OP_MODULATE = 0,
	ksTEXTURE_COLOR_OP_DECAL    = 1,
	ksTEXTURE_COLOR_OP_BLEND    = 2,
	ksTEXTURE_COLOR_OP_REPLACE  = 3,
	ksTEXTURE_COLOR_OP_ADD      = 4,
	ksTEXTURE_COLOR_OP_FORCE32  = 0x7fffffff,	/**< �����I��32bit�ɂ���	*/

}ksTEXTURE_COLOR_OP_MODE;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef enum _ksTEXTURE_ADDRESS_MODE
{
	ksTEXTURE_ADDRESS_REPEAT  = 0,
	ksTEXTURE_ADDRESS_CLAMP   = 1,
	ksTEXTURE_ADDRESS_FORCE32 = 0x7fffffff,	/**< �����I��32bit�ɂ���		*/

}ksTEXTURE_ADDRESS_MODE;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef enum _ksTEXTURE_FILTER
{
	ksTEXTURE_FILTER_NEAREST = 0,  
	ksTEXTURE_FILTER_LINEAR  = 1,
	ksTEXTURE_FILTER_FORCE32 = 0x7fffffff,	/**< �����I��32bit�ɂ���		*/

}ksTEXTURE_FILTER;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef enum _ksTEXTURE_MIPMAP_FILTER
{
	ksTEXTURE_MIPMAP_FILTER_NEAREST = 0,
	ksTEXTURE_MIPMAP_FILTER_LINEAR  = 1,
	ksTEXTURE_MIPMAP_FILTER_FORCE32 = 0x7fffffff,	/**< �����I��32bit�ɂ���		*/

}ksTEXTURE_MIPMAP_FILTER;

/************************************************************************************************/
/**
 * �����_�[�X�e�[�g
 */
/************************************************************************************************/
typedef enum _ksRENDER_STATE_TYPE
{
	ksRENDER_STATE_OP_BLEND           = 0,			/**< �u�����h���[�h											*/
	ksRENDER_STATE_SRC_BLEND          = 1,			/**< SRC�u�����f�B���O										*/
    ksRENDER_STATE_DST_BLEND          = 2,			/**< DEST�u�����f�B���O										*/
	ksRENDER_STATE_ALPHA_BLEND        = 3,			/**< �A���t�@�u�����h										*/
	ksRENDER_STATE_ALPHA_FUNC         = 4,			/**< �A���t�@�֐�											*/
	ksRENDER_STATE_ALPHA_REF          = 5,			/**< �A���t�@��l											*/
	ksRENDER_STATE_ALPHA_MASK         = 6,			/**< �A���t�@�}�X�N�l										*/

	ksRENDER_STATE_ZTEST_ENABLE       = 7,			/**< Z�o�b�t�@(ON,OFF)										*/
	ksRENDER_STATE_ZWRITE_ENABLE      = 8,			/**< Z���C�g(ON,OFF)										*/
	ksRENDER_STATE_ALPAHTEST_ENABLE   = 9,			/**< �A���t�@�e�X�g(ON,OFF)									*/
	ksRENDER_STATE_FOG_ENABLE         = 10,			/**< �t�H�O(ON,OFF)											*/
	ksRENDER_STATE_LIGHTING           = 11,			/**< ���C�e�B���O(ON,OFF)									*/
	ksRENDER_STATE_SHADE              = 12,			/**< �V�F�[�f�B���O											*/
	ksRENDER_STATE_CULL               = 13,			/**< �J�����O												*/

	ksRENDER_STATE_STENCIL_ENABLE     = 14,			/**< �X�e���V��(ON,OFF)										*/
	ksRENDER_STATE_STENCIL_FAIL       = 15,			/**< �X�e���V���e�X�g���s���̃I�y���[�V����					*/
	ksRENDER_STATE_STENCIL_ZFAIL      = 16,			/**< �X�e���V���e�X�g����Z�e�X�g�Ɏ��s���̃I�y���[�V����	*/
	ksRENDER_STATE_STENCIL_PASS       = 17,			/**< �X�e���V���e�X�g����Z�e�X�g�̐������̃I�y���[�V����	*/
	ksRENDER_STATE_STENCIL_FUNC       = 18,			/**< �X�e���V���t�@���N�V����								*/
	ksRENDER_STATE_STENCIL_REF        = 19,			/**< �X�e���V���̊�l										*/
	ksRENDER_STATE_STENCIL_MASK       = 20,			/**< �X�e���V���̃}�X�N�l									*/
	ksRENDER_STATE_STENCIL_WRITE_MASK = 21,			/**< �X�e���V���������݃}�X�N								*/
	ksRENDER_STATE_COLOR_TEST_ENABLE  = 22,			/**< �J���[�e�X�g(ON,OFF)									*/
	ksRENDER_STATE_COLOR_FUNC         = 23,			/**< �J���[�֐�												*/
	ksRENDER_STATE_COLOR_REF          = 24,			/**< �J���[��l											*/
	ksRENDER_STATE_COLOR_MASK         = 25,			/**< �J���[�}�X�N�l											*/
	ksRENDER_STATE_PIXEL_MASK         = 26,			/**< �s�N�Z���}�X�N											*/
	ksRENDER_STATE_LOGICAL_OP_ENABLE  = 27,			/**< ���W�J���I�y���[�V����(ON,OFF)							*/
	ksRENDER_STATE_LOGICAL_OP_BLEND   = 28,			/**< ���W�J���I�y���[�V�������[�h							*/

	ksRENDER_STATE_FORCE32            = 0x7fffffff,	/**< �����I��32bit�ɂ���									*/

}ksRENDER_STATE_TYPE;


/* Special sampler which is used in the tesselator */
#define ksDMAP_SAMPLER				( 256 )

/* Samplers used in vertex shaders */
#define ksVERTEX_TEXTURE_SAMPLER0 ( ksDMAP_SAMPLER + 1 )
#define ksVERTEX_TEXTURE_SAMPLER1 ( ksDMAP_SAMPLER + 2 )
#define ksVERTEX_TEXTURE_SAMPLER2 ( ksDMAP_SAMPLER + 3 )
#define ksVERTEX_TEXTURE_SAMPLER3 ( ksDMAP_SAMPLER + 4 )

/************************************************************************************************/
/**
 * �T���v���[�X�e�[�g
 */
/************************************************************************************************/
typedef enum _ksSAMPLER_STATE_TYPE
{
    ksSAMP_ADDRESSU       = 1,			/* TEXTUREADDRESS for U coordinate					*/
    ksSAMP_ADDRESSV       = 2,			/* TEXTUREADDRESS for V coordinate					*/
    ksSAMP_ADDRESSW       = 3,			/* TEXTUREADDRESS for W coordinate					*/
    ksSAMP_BORDERCOLOR    = 4,			/* COLOR											*/
    ksSAMP_MAGFILTER      = 5,			/* TEXTUREFILTER filter to use for magnification	*/
    ksSAMP_MINFILTER      = 6,			/* TEXTUREFILTER filter to use for minification		*/
    ksSAMP_MIPFILTER      = 7,			/* TEXTUREFILTER filter to use between mipmaps during minification */
    ksSAMP_MIPMAPLODBIAS  = 8,			/* float Mipmap LOD bias							*/
    ksSAMP_MAXMIPLEVEL    = 9,			/* DWORD 0..(n-1) LOD index of largest map to use (0 == largest) */
    ksSAMP_MAXANISOTROPY  = 10,			/* DWORD maximum anisotropy */
    ksSAMP_SRGBTEXTURE    = 11,			/* Default = 0 (which means Gamma 1.0, no correction required.) else correct for Gamma = 2.2 */
    ksSAMP_ELEMENTINDEX   = 12,			/* When multi-element texture is assigned to sampler, this indicates which element index to use.  Default = 0.  */
    ksSAMP_DMAPOFFSET     = 13,			/* Offset in vertices in the pre-sampled displacement map. Only valid for DMAPSAMPLER sampler  */
    ksSAMP_STATE_FORCE32  = 0x7fffffff, /**< �����I��32bit�ɂ���									*/

}ksSAMPLER_STATE_TYPE;

/************************************************************************************************/
/**
 * Values for D3DSAMP_***FILTER texture stage states
 */
/************************************************************************************************/
typedef enum _ksTEXTURE_FILTER_TYPE
{
	ksTEXF_NONE            = 0,				/**< filtering disabled (valid for mip filter only)	*/
	ksTEXF_POINT           = 1,				/**< nearest										*/
	ksTEXF_LINEAR          = 2,				/**< linear interpolation							*/
	ksTEXF_ANISOTROPIC     = 3,				/**< anisotropic									*/
	ksTEXF_PYRAMIDALQUAD   = 6,				/**< 4-sample tent									*/
	ksTEXF_GAUSSIANQUAD    = 7,				/**< 4-sample gaussian								*/
	ksTEXF_FORCE32         = 0x7fffffff,	/**< �����I��32bit�ɂ���							*/

}ksTEXTURE_FILTER_TYPE;

/************************************************************************************************/
/**
 * �u�����h�̉��Z
 */
/************************************************************************************************/
typedef enum _ksBLEND_OP_MODE
{
    ksBLEND_OP_ADD         = 1,			/**< ���ʂ͓]�����ɓ]���悪���Z�����  ( ���� = �]���� + �]���� )		*/
    ksBLEND_OP_SUBTRACT    = 2,			/**< ���ʂ͓]��������]���悪���Z�����( ���� = �]���� - �]���� )		*/
    ksBLEND_OP_REVSUBTRACT = 3,			/**< ���ʂ͓]���悩��]���������Z�����( ���� = �]���� - �]���� )		*/
    ksBLEND_OP_MIN         = 4,			/**< ���ʂ͓]�����Ɠ]����̍ŏ��l�ł���( ���� = MIN(�]����, �]����) )	*/
    ksBLEND_OP_MAX         = 5,			/**< ���ʂ͓]�����Ɠ]����̍ő�l�ł���( ���� = MAX(�]����, �]����) )	*/
    ksBLEND_OP_FORCE_DWORD = 0x7fffffff,/**< �����I��32bit�ɂ���												*/

}ksBLEND_OP_MODE;

/************************************************************************************************/
/**
 * �u�����hFUNC
 */
/************************************************************************************************/
typedef enum _ksALPHA_FUNC_MODE
{
	ksALPHA_FUNC_NEVER    = 0,			/**< �S�Ẵs�N�Z����`�悵�Ȃ�							*/
	ksALPHA_FUNC_ALWAYS   = 1,			/**< �S�Ẵs�N�Z����`�悷��							*/
	ksALPHA_FUNC_EQUAL    = 2,			/**< �ݒ�l���A���t�@�l�̏ꍇ�Ƀs�N�Z����`�悷��		*/
	ksALPHA_FUNC_NOTEQUAL = 3,			/**< �ݒ�l���A���t�@�l�̏ꍇ�Ƀs�N�Z����`�悷��		*/
	ksALPHA_FUNC_LESS     = 4,			/**< �ݒ�l���A���t�@�l�̏ꍇ�Ƀs�N�Z����`�悷��		*/
	ksALPHA_FUNC_LEQUAL   = 5,			/**< �ݒ�l���A���t�@�l�̏ꍇ�Ƀs�N�Z����`�悷��		*/
	ksALPHA_FUNC_GREATER  = 6,			/**< �ݒ�l���A���t�@�l�̏ꍇ�Ƀs�N�Z����`�悷��		*/
	ksALPHA_FUNC_GEQUAL   = 7,			/**< �ݒ�l���A���t�@�l�̏ꍇ�Ƀs�N�Z����`�悷��		*/
	ksALPHA_FUNC_FORCE32  = 0x7fffffff,	/**< �����I��32bit�ɂ���								*/

}ksALPHA_FUNC_MODE;

/************************************************************************************************/
/**
 * �X�e���V������
 */
/************************************************************************************************/
typedef enum _ksSTENCIL_OP_MODE
{
	ksSTENCIL_OP_KEEP    = 0,				/**< �������Ȃ�									*/
	ksSTENCIL_OP_ZERO    = 1,				/**< �X�e���V���l�� 0 �ɕύX����				*/
	ksSTENCIL_OP_REPLACE = 2,				/**< �X�e���V���l��ݒ�l�ɕύX����				*/
	ksSTENCIL_OP_INCRSAT = 3,				/**< �ő�l�ɒB����܂ő���������				*/
	ksSTENCIL_OP_DECRSAT = 4,				/**< 0 �ɂȂ�܂Ō���������						*/
	ksSTENCIL_OP_INVERT  = 5,				/**< �X�e���V���l�𔽓]����						*/
	ksSTENCIL_OP_INCR    = 6,				/**< �X�e���V���l�� 1 ��������					*/
	ksSTENCIL_OP_DECR    = 7,				/**< �X�e���V���l�� 1 ��������					*/
	ksSTENCIL_OP_FORCE32 = 0x7fffffff,		/**< �����I��32bit�ɂ���						*/

}ksSTENCIL_OP_MODE;

/************************************************************************************************/
/**
 * �X�e���V��FUNC
 */
/************************************************************************************************/
typedef enum _ksSTENCIL_FUNC_MODE
{
	ksSTENCIL_FUNC_NEVER    = 0,			/**< �S�Ẵs�N�Z����`�悵�Ȃ�							*/
	ksSTENCIL_FUNC_ALWAYS   = 1,			/**< �S�Ẵs�N�Z����`�悷��							*/
	ksSTENCIL_FUNC_EQUAL    = 2,			/**< �ݒ�l���X�e���V���l�̏ꍇ�Ƀs�N�Z����`�悷��		*/
	ksSTENCIL_FUNC_NOTEQUAL = 3,			/**< �ݒ�l���X�e���V���l�̏ꍇ�Ƀs�N�Z����`�悷��		*/
	ksSTENCIL_FUNC_LESS     = 4,			/**< �ݒ�l���X�e���V���l�̏ꍇ�Ƀs�N�Z����`�悷��		*/
	ksSTENCIL_FUNC_LEQUAL   = 5,			/**< �ݒ�l���X�e���V���l�̏ꍇ�Ƀs�N�Z����`�悷��		*/
	ksSTENCIL_FUNC_GREATER  = 6,			/**< �ݒ�l���X�e���V���l�̏ꍇ�Ƀs�N�Z����`�悷��		*/
	ksSTENCIL_FUNC_GEQUAL   = 7,			/**< �ݒ�l���X�e���V���l�̏ꍇ�Ƀs�N�Z����`�悷��		*/
	ksSTENCIL_FUNC_FORCE32  = 0x7fffffff,	/**< �����I��32bit�ɂ���								*/

}ksSTENCIL_FUNC_MODE;

/************************************************************************************************/
/**
 * �J���[FUNC
 */
/************************************************************************************************/
typedef enum _ksCOLOR_FUNC_MODE
{
	ksCOLOR_FUNC_NEVER    = 0,				/**< �S�Ẵs�N�Z����`�悵�Ȃ�						*/
	ksCOLOR_FUNC_ALWAYS   = 1,				/**< �S�Ẵs�N�Z����`�悷��							*/
	ksCOLOR_FUNC_EQUAL    = 2,				/**< �s�N�Z���J���[���Œ�l�̏ꍇ�Ƀs�N�Z����`�悷��	*/
	ksCOLOR_FUNC_NOTEQUAL = 3,				/**< �s�N�Z���J���[���Œ�l�̏ꍇ�Ƀs�N�Z����`�悷��	*/
	ksCOLOR_FUNC_FORCE32  = 0x7fffffff,		/**< �����I��32bit�ɂ���								*/

}ksCOLOR_FUNC_MODE;

/************************************************************************************************/
/**
 * �u�����h���[�h
 */
/************************************************************************************************/
typedef enum _ksBLEND_MODE
{
	ksBLEND_ZERO                = 1,			/**< �u�����f�B���O�W�� (0, 0, 0, 0)				*/
	ksBLEND_ONE                 = 2,			/**< �u�����f�B���O�W�� (1, 1, 1, 1)				*/
	ksBLEND_SRC_COLOR           = 3,			/**< �u�����f�B���O�W�� (Rs,Gs,Bs,As)				*/
	ksBLEND_DST_COLOR           = 4,			/**< �u�����f�B���O�W�� (Rd,Gd,Bd,Ad)				*/
	ksBLEND_ONE_MINUS_SRC_COLOR = 5,			/**< �u�����f�B���O�W�� (1-Rs,1-Gs,1-Bs,1-As)		*/
	ksBLEND_ONE_MINUS_DST_COLOR = 6,			/**< �u�����f�B���O�W�� (1-Rd,1-Gd,1-Bd,1-Ad)		*/
	ksBLEND_SRC_ALPHA           = 7,			/**< �u�����f�B���O�W�� (As, As, As, As)			*/
	ksBLEND_DST_ALPHA           = 8,			/**< �u�����f�B���O�W�� (Ad, Ad, Ad, Ad) �֎~		*/
	ksBLEND_ONE_MINUS_SRC_ALPHA = 9,			/**< �u�����f�B���O�W�� (1-As,1-As,1-As,1-As)		*/
	ksBLEND_ONE_MINUS_DST_ALPHA = 10,			/**< �u�����f�B���O�W�� (1-Ad,1-Ad,1-Ad,1-Ad)�֎~	*/
	ksBLEND_FORCE32             = 0x7fffffff,	/**< �����I��32bit�ɂ���							*/

}ksBLEND_MODE;

/************************************************************************************************/
/**
 * �V�F�[�f�B���O���[�h
 */
/************************************************************************************************/
typedef enum _ksSHADE_MODE
{
	ksSHADE_FLAT    = 1,				/**< �t���b�g�V�F�[�f�B���O		*/
	ksSHADE_GOURAUD = 2,				/**< �O�[���[�V�F�[�f�B���O		*/
	ksSHADE_FORCE32 = 0x7fffffff,		/**< �����I��32bit�ɂ���		*/

}ksSHADE_MODE;

/************************************************************************************************/
/**
 * �J�����O���[�h
 */
/************************************************************************************************/
typedef enum _ksCULL_MODE
{
	ksCULL_NONE    = 1,					/**< �w�ʂ̃J�����O�͂��Ȃ�		*/
	ksCULL_CW      = 2,					/**< �w�ʂ��E���ŃJ�����O����	*/
	ksCULL_CCW     = 3,					/**< �w�ʂ������ŃJ�����O����	*/
	ksCULL_FORCE32 = 0x7fffffff,		/**< �����I��32bit�ɂ���		*/

}ksCULL_MODE;

/************************************************************************************************/
/**
 * �J�����O���[�h
 */
/************************************************************************************************/
typedef enum _ksFOG_MODE
{
	ksFOG_NONE    = 0,					/**< �t�H�O�Ȃ�										*/
	ksFOG_EXP     = 1,					/**< �w���ŁA�t�H�O �G�t�F�N�g������				*/
	ksFOG_EXP2    = 2,					/**< �w���� 2 ��ŁA�t�H�O �G�t�F�N�g������			*/
	ksFOG_LINEAR  = 3,					/**< �n�_�ƏI�_�̊ԂŐ��`�Ƀt�H�O �G�t�F�N�g������	*/
	ksFOG_FORCE32 = 0x7fffffff,			/**< �����I��32bit�ɂ���							*/

}ksFOG_MODE;

/************************************************************************************************/
/**
 * �`��v���~�e�B�u�̃^�C�v
 */
/************************************************************************************************/
typedef enum _ksPRIMITIVE_TYPE
{
    ksPRIMITIVE_POINT_LIST     = 1,
    ksPRIMITIVE_LINE_LIST      = 2,
    ksPRIMITIVE_LINE_STRIP     = 3,
    ksPRIMITIVE_TRIANGLE_LIST  = 4,
    ksPRIMITIVE_TRIANGLE_STRIP = 5,
	ksPRIMITIVE_TRIANGLE_FAN   = 6,
    ksPRIMITIVE_FORCE32        = 0x7fffffff,

}ksPRIMITIVE_TYPE;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
class KsTextureState
{
	public:
		ksTEXTURE_COLOR_OP_MODE			m_colorOP;
		ksTEXTURE_ADDRESS_MODE			m_addressU;
		ksTEXTURE_ADDRESS_MODE			m_addressV;
		ksTEXTURE_FILTER				m_magFilter;
		ksTEXTURE_FILTER				m_minFilter;
		ksTEXTURE_MIPMAP_FILTER			m_mipMapFilter;
};

/************************************************************************************************/
/**
 * @class		KsRenderState
 * @brief		�����_�[�X�e�[�g
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsRenderState
{
	public:
		/* �������郌���_�[�X�e�[�g�̃r�b�g */
		//push ���ꂽ�Ƃ����ׂĂ̌���̂��ׂẴ����_�[�X�e�[�g��ۑ�����
		//pop  �̂Ƃ��͈Ⴄ���̂�����ύX����
		ksBLEND_OP_MODE					m_opBlend;
		ksBLEND_MODE					m_srcBlend;
		ksBLEND_MODE					m_dstBlend;
		
		KsBool							m_alphaBlend;
		ksALPHA_FUNC_MODE				m_alphaFunc;
		KsUInt32						m_alphaRef;
		KsUInt32						m_alphaMask;

		KsBool							m_zTest;
		KsBool							m_zWrite;
		KsBool							m_alphaTest;
		KsBool							m_fog;
		KsBool							m_lighting;
		ksSHADE_MODE					m_shadeMode;
		ksCULL_MODE						m_cullMode;

		KsBool							m_stencil;
		KsUInt32						m_stencilRef;
		KsUInt32						m_stencilMask;
		KsUInt32						m_stencilWriteMask;
		ksSTENCIL_OP_MODE				m_stencilOpFail;
		ksSTENCIL_OP_MODE				m_stencilOpZFail;
		ksSTENCIL_OP_MODE				m_stencilOpPass;
		ksSTENCIL_FUNC_MODE				m_stencilFunc;

		KsBool							m_colorTest;
		ksCOLOR_FUNC_MODE				m_colorFunc;
		KsUInt32						m_colorRef;
		KsUInt32						m_colorMask;

		KsUInt32						m_pixelMask;

		KsBool							m_logicalOp;
		//stLOGICAL_FUNC_MODE			m_logicalFunc;
		//KsUInt32						m_changeStateMask;	/**< �ύX���������_�[�X�e�[�g�̃}�X�N	*/
};

/************************************************************************************************/
/**
 * @class		KsRenderStateStack
 * @brief		�����_�[�X�e�[�g�X�^�b�N
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsRenderStateStack
{
	public:
		/**
		 * �R���X�g���N�^
		 */
											KsRenderStateStack() : m_index( 0 ) {}

		/**
		 * �����_�[�X�e�[�g���v�b�V������
		 * @param		pState				�v�b�V�����郌���_�[�X�e�[�g
		 * @retval		ksTRUE				����
		 * @retval		ksFALSE				���s
		 */
		KsBool								push( const KsRenderState* pState );

		/**
		 * �����_�[�X�e�[�g���|�b�v����
		 * @param		pState				�����_�[�X�e�[�g���擾���邽�߂̃|�C���^
		 * @retval		ksTRUE				����
		 * @retval		ksFALSE				���s
		 */
		KsBool								pop( KsRenderState* pState );

		/**
		 * �X�^�b�N���N���A�[����
		 */
		void								clear();

	private:
		KsRenderState						m_stack[ ksRENDER_STATE_STACK_MAX ];	/**< �����_�[�X�e�[�g�X�^�b�N	*/
		KsInt32								m_index;								/**< ���݂̃X�^�b�N�̐[��		*/
};


#endif /* __KSRENDERSTATE_H__ */

