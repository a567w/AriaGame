/*************************************************************************************************/
/** 
 * @file	KsPhysicsBulletCompile.h
 * @brief	�R���p�C���Ȃǂ̐ݒ�
 * @author	Tsukasa Kato
 * @date	2008/02/12
 * @since	2008/02/12
 */
/*************************************************************************************************/
#ifndef __KSPHYSICSBULLETCOMPILE_H__
#define __KSPHYSICSBULLETCOMPILE_H__

/*===============================================================================================*/
/*								<< �C���N���[�h�t�@�C�� >>										 */
/*===============================================================================================*/

/*===============================================================================================*/
/*                                     << ��` >>                                                */
/*===============================================================================================*/

//#define ksBUILD_STATIC	// �v���W�F�N�g�Őݒ�
//#define ksBUILD_DYNAMIC	// �v���W�F�N�g�Őݒ�
//#define ksENGINE_EXPORTS	// �v���W�F�N�g�Őݒ�

#if 0
#if defined( ksBUILD_DYNAMIC ) && defined( ksBUILD_STATIC )
	#undef ksBUILD_STATIC
#else
	#if !defined(ksBUILD_DYNAMIC)
		#define ksBUILD_DYNAMIC
	#endif
#endif
#endif

/* �o�͌`�� */
/* �o�͌`�� */
#ifdef ksBUILD_STATIC
	#define ksPHYSICSBULLET_API
	#define ksPHYSICSBULLET_EXTERN
#else
	#ifdef ksPHYSICSBULLET_EXPORTS
		#define ksPHYSICSBULLET_API			__declspec( dllexport )
		#define ksPHYSICSBULLET_EXTERN
	#else
		#define ksPHYSICSBULLET_API			__declspec( dllimport )
		#define ksPHYSICSBULLET_EXTERN		extern
	#endif
#endif

#define ksPHYSICSBULLET_CDECL __cdecl

/*===============================================================================================*/
/*                                     << �錾 >>                                                */
/*===============================================================================================*/


#endif	/* __KSPHYSICSBULLETCOMPILE_H__ */


