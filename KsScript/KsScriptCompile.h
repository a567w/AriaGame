/************************************************************************************************/
/** 
 * @file		KsScriptPreCompile.h
 * @brief		�v���R���p�C���w�b�_�[
 * @author		Tsukasa Kato
 * @date		2005/06/27
 * @since		2005/06/27
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSCRIPTCOMPILE_H__
#define __KSSCRIPTCOMPILE_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

//#define ksBUILD_STATIC	// �v���W�F�N�g�Őݒ�
//#define ksBUILD_DYNAMIC	// �v���W�F�N�g�Őݒ�
//#define ksENGINE_EXPORTS	// �v���W�F�N�g�Őݒ�

/* �o�͌`�� */
#ifdef ksBUILD_STATIC
	#define ksSCRIPT_API
	#define ksSCRIPT_EXTERN
#else
	#ifdef ksSCRIPT_EXPORTS
		#define ksSCRIPT_API			__declspec(dllexport)
		#define ksSCRIPT_EXTERN
	#else
		#define ksSCRIPT_API			__declspec( dllimport )
		#define ksSCRIPT_EXTERN		extern
	#endif
#endif

#define ksSCRIPT_CDECL __cdecl


#endif	/* __KSSCRIPTCOMPILE_H__ */
