/************************************************************************************************/
/** 
 * @file		KsScriptFormat.h
 * @brief		�X�N���v�g�t�@�C���t�H�[�}�b�g
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSSCRIPTFORMAT_H__
#define __KSSCRIPTFORMAT_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsVariable.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/
#define ksSCRIPT_SIGNATURE		ksMAKE_DWORD( '@', 'K', 'G', 'S' )
#define ksSCRIPT_VERSION		( 0x00010000 )

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*
���ԃR�[�h�t�@�C���t�H�[�}�b�g
----------------------------------------------------------------------------
HEADER
	signature				4byte
	version					4byte
	offsetInfo				4byte
	offsetCode				4byte			
----------------------------------------------------------------------------
INFO
	numString				2byte	
	numGlobal				2byte
	numFunc					2byte
	numStruct				2byte

	offsetGlobal			4byte			�O���[�o���ϐ����ւ̃I�t�Z�b�g
	offsetFunc				4byte			
	offsetStruct			4byte
	offsetString			4byte

	FILE(�t�@�C�������[�J���ƃO���[�o���̊֐��𕪂��邽��)
		length				2byte
		name				�ϒ�

	STRING
		numString				2byte
			STRING
				length			2byte		������̒���
				next			2byte		���̕�����ւ̃I�t�Z�b�g
				string			��			������
				numCode			2byte		�m�ۂ������Ƃɏ���������R�[�h��
					offset		4byte		numCode������(offsetCode����̃I�t�Z�b�g)
			.....�J��Ԃ�

	GLOBAL
		numGlobal				2byte
			VARIABL_GLOBAL
				length			2byte		������̒���
				next			2byte		���̕�����ւ̃I�t�Z�b�g
				numCode			2byte		�m�ۂ������Ƃɏ���������R�[�h��
					offset		4byte		numCode������(offsetCode����̃I�t�Z�b�g)
				string			��			������
			.....�J��Ԃ�

	FUNC
		numFunc					2byte
			id					4byte		�֐���ID
			numArg				2byte		�����̐�
			numVar				2byte		���[�J���ϐ��̐�
			stackSize			4byte		���̊֐��̃X�^�b�N�T�C�Y
			codeSize			4byte		�֐��̃R�[�h�T�C�Y
			codeOffset			4byte		�R�[�h��񕔂���̃I�t�Z�b�g�A�h���X
			next				4byte		���̊֐��ւ̃I�t�Z�b�g�A�h���X(0�ŏI��)
			numLocal			2byte
				VARIABL_LOCAL(�I�t�Z�b�g���ɓ����Ă���)
					length		2byte		������̒���
					next		2byte		���̕�����ւ̃I�t�Z�b�g
					string		��			������
					.....�J��Ԃ�
			.....�J��Ԃ�

	STRUCT
		numStruct			2byte

----------------------------------------------------------------------------
CODE
	size		4byte		�R�[�h�T�C�Y
	data		�T�C�Y��
----------------------------------------------------------------------------
	
*/

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_SCRIPT_FILE_HEADER
{
	KsUInt32			signature;			/**< ���ʗp�T�C��							*/
	KsUInt32			version;			/**< �o�[�W�������							*/
	KsUInt32			offsetInfo;			/**< ��񕔂ւ̃I�t�Z�b�g�A�h���X			*/
	KsUInt32			offsetCode;			/**< �R�}���h���ւ̃I�t�Z�b�g�A�h���X		*/
}KS_SCRIPT_FILE_HEADER;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_SCRIPT_INFO_HEADER
{
	KsUInt32			numString;			/**< ������̐�								*/
	KsUInt32			numGlobal;			/**< �O���[�o���ϐ��̐�						*/
	KsUInt32			numFunc;			/**< �֐��̐�								*/
	KsUInt32			numStruct;			/**< �\���̂̐�								*/
	KsUInt32			offsetString;		/**< ��������ւ̃I�t�Z�b�g				*/
	KsUInt32			offsetGlobal;		/**< �O���[�o���ϐ����ւ̃I�t�Z�b�g		*/
	KsUInt32			offsetFunc;			/**< ������̐�								*/
	KsUInt32			offsetStruct;		/**< ������̐�								*/

}KS_SCRIPT_INFO_HEADER;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_SCRIPT_FUNC_INFO
{
	KsUInt32			id;					/**< �֐���ID								*/
	KsUInt16			numArg;				/**< �����̐�								*/
	KsUInt16			numVar;				/**< ���[�J���ϐ��̐�						*/
	KsUInt32			stackSize;			/**< ���̊֐��̃X�^�b�N�T�C�Y				*/
	KsUInt32			codeSize;			/**< �֐��̃R�[�h�T�C�Y						*/
	KsUInt32			codeOffset;			/**< �R�[�h��񕔂���̃I�t�Z�b�g�A�h���X	*/
	KsUInt32			nextOffset;			/**< ���̊֐��ւ̃I�t�Z�b�g�A�h���X(0�ŏI��)*/
	KsChar*				pSymbol;			/**< �֐��� + arg0+'\0'...local2+'\0'+'\0' 4�o�C�g�A���C�������g	*/
}KS_SCRIPT_FUNC_INFO;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef struct _KS_SCRIPT_STRUCT_INFO
{
	KsUInt16			numVar;				/**< �����o�[�ϐ��̐�							*/
	KsUInt16			numFunc;			/**< �����o�[�֐��̐�							*/
	KsUInt32			nextOffset;			/**< ���̍\���̂ւ̃I�t�Z�b�g�A�h���X(0�ŏI��)	*/
	KsChar*				pSymbol;			/**< �\���̖� + �����o�[�ϐ�	+ �����o�[�֐�	*/
}KS_SCRIPT_STRUCT_INFO;



#endif		/* __KSSCRIPTFORMAT_H__	*/





