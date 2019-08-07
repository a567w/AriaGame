/*************************************************************************************************/
/** 
 * @file	KsCompile.h
 * @brief	�R���p�C���Ȃǂ̐ݒ�
 * @author	Tsukasa Kato
 * @date	2008/02/12
 * @since	2008/02/12
 */
/*************************************************************************************************/
#ifndef __KSCOMPILE_H__
#define __KSCOMPILE_H__

/*===============================================================================================*/
/*								<< �C���N���[�h�t�@�C�� >>										 */
/*===============================================================================================*/

/*===============================================================================================*/
/*                                     << ��` >>                                                */
/*===============================================================================================*/

//#define ksBUILD_STATIC	// �v���W�F�N�g�Őݒ�
//#define ksBUILD_DYNAMIC	// �v���W�F�N�g�Őݒ�
//#define ksENGINE_EXPORTS	// �v���W�F�N�g�Őݒ�

/* �o�͌`�� */
#ifdef ksBUILD_STATIC
	#define ksENGINE_API
	#define ksEXTERN
#else
	#ifdef ksENGINE_EXPORTS
		#define ksENGINE_API	__declspec( dllexport )
		#define ksEXTERN
	#else
		#define ksENGINE_API	__declspec( dllimport )
		#define ksEXTERN		extern
	#endif
#endif

#define ksCDECL __cdecl

#ifdef WIN32
	#include <vector>
	#include <map>
	#include <string>

	#ifdef _MSC_VER
		#pragma warning( disable : 4231 )
		#pragma warning( disable : 4251 )	/* �e���v���[�g�G�N�X�|�[�g���̌x��		*/
		#pragma warning( disable : 4311 )	/* �|�C���^���琮���l�ւ̕ύX				*/
		#pragma warning( disable : 4312 )	/* �����l����|�C���^�ւ̕ύX				*/
		#pragma warning( disable : 4333 )	/* �E�V�t�g�̉񐔂��������܂��B�f�[�^��������\��������܂�				*/
		#pragma warning( disable : 4661 )	/* �����I�ȃe���v���[�g�̃C���X�^���X�����v���ɑ΂��ēK�؂Ȓ�`������܂���B */
		#pragma warning( disable : 4819 )
		#pragma warning( disable : 4995 )
		#pragma warning( disable : 4996 )
	#endif
#endif

/*===============================================================================================*/
/*                                     << �錾 >>                                                */
/*===============================================================================================*/


#endif	/* __KSCOMPILE_H__ */


