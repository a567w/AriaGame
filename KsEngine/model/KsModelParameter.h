/************************************************************************************************/
/** 
 * @file		KsModelParameter.h
 * @brief		���f���p�����[�^
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMODELPARAMETER_H__
#define __KSMODELPARAMETER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/
#define MAX_BONES						256

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsGBufferParameter
 * @brief		���f��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsGBufferParameter
{
	public:
		static const KsUInt32	Size = sizeof(KsMatrix4x4)*(18);

	public:
		KsMatrix4x4				WorldViewProj;
		KsMatrix4x4				WorldView;
		KsMatrix4x4				ViewProj;
		KsMatrix4x4				Proj;
		KsMatrix4x4				World;
		KsVector4d				CameraNearFar;
		KsUInt32				FramebufferDimensionsX;
		KsUInt32				FramebufferDimensionsY;
		KsUInt32				FramebufferDimensionsZ;
		KsUInt32				FramebufferDimensionsW;
};

/************************************************************************************************/
/**
 * @class		KsMatrixPalletParameter
 * @brief		���f��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsMatrixPalletParameter
{
	public:
		static const KsUInt32	Size = sizeof(KsMatrix4x4)*(MAX_BONES+10);
	
	public:
		KsMatrix4x4				MatrixPalette[ MAX_BONES ];
};

/************************************************************************************************/
/**
 * @class		KsModelParameter
 * @brief		���f��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsModelParameter
{
	public:
		KsGBufferParameter				GBuffer;
		KsMatrixPalletParameter			Model;
};

#endif		/* __KSMODELPARAMETER_H__ */



