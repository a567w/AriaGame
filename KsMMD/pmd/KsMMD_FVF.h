/************************************************************************************************/
/** 
 * @file		KsMMD_FVF.h
 * @brief		MMD FVF
 * @author		Tsukasa Kato
 * @date		2010/08/17
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSMMD_FVF_H__
#define __KSMMD_FVF_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
#define ksMMD_FVF	( ksFVF_XYZ | ksFVF_NORMAL | ksFVF_TEX0 | ksFVF_INDICES | ksFVF_WEIGHT )
#define MODEL_DATA_PATH	"D:\\MMD\\"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
static KS_INPUT_ELEMENT_DESC InputLayoutMMD[] =
{
    { "POSITION",		0, KS_GI_FORMAT_R32G32B32_FLOAT,	0,  0, KS_INPUT_PER_VERTEX_DATA, 0 },	// POSITION
	{ "NORMAL",			0, KS_GI_FORMAT_R32G32B32_FLOAT,	0, 12, KS_INPUT_PER_VERTEX_DATA, 0 },	// NORMAL
	{ "TEXCOORD",		0, KS_GI_FORMAT_R32G32_FLOAT,		0, 24, KS_INPUT_PER_VERTEX_DATA, 0 },	// UV
	{ "BLENDINDICES",	0, KS_GI_FORMAT_R8G8B8A8_UINT,		0, 32, KS_INPUT_PER_VERTEX_DATA, 0 },	// INDICES
	{ "BLENDWEIGHT",	0, KS_GI_FORMAT_R32G32B32A32_FLOAT,	0, 36, KS_INPUT_PER_VERTEX_DATA, 0 },	// WEIGHT
};

struct KS_MMD_VERTEX
{
	KsReal	x, y, z;
	KsReal	nx, ny, nz;
	KsReal	u, v;
	union
	{
		KsByte		indices[ 4 ];
		KsUInt16	indices_16[ 2 ];
	};
	KsReal	weight[ 4 ];
};

struct KS_MMD_VERTEX_PNIW
{
	KsReal	x, y, z;
	KsReal	nx, ny, nz;
	KsByte	indices[ 4 ];
	KsReal	weight[ 4 ];
};

#endif /* __KSMMD_FVF_H__ */



