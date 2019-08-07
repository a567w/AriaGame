/************************************************************************************************/
/** 
 * @file		KsIntermediateCode.h
 * @brief		中間コード書き込み用
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSINTERMEDIATECODE_H__
#define __KSINTERMEDIATECODE_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
#define ksCMD_CODE_SIZE		( 4 )
#define ksCMD_DATA_SIZE		( 4 )
#define ksCMD_CODE_DATA_SIZE	( ksCMD_CODE_SIZE + ksCMD_DATA_SIZE )

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
// スクリプト命令の種類(255まで)
enum ksCMD_TYPE
{
	ksCMD_ADD						= 0x01,
	ksCMD_SUB						= 0x02,
	ksCMD_MUL						= 0x03,
	ksCMD_DIV						= 0x04,
	ksCMD_REM						= 0x05,
	ksCMD_OR						= 0x06,
    ksCMD_XOR						= 0x07,
	ksCMD_AND						= 0x08,
	ksCMD_INV						= 0x09,
    ksCMD_SHL						= 0x0a,
    ksCMD_SHR						= 0x0b,
    ksCMD_LT						= 0x0c,
    ksCMD_GT						= 0x0d,
    ksCMD_LTE						= 0x0e,
    ksCMD_GTE						= 0x0f,
    ksCMD_EQ						= 0x10,
    ksCMD_NEQ						= 0x11,
	ksCMD_CALL						= 0x12,
	ksCMD_RET						= 0x13,
	ksCMD_RETV						= 0x14,
	ksCMD_GLOBAL					= 0x15,
	ksCMD_LOCAL						= 0x16,
	ksCMD_SHIFT_LEFT				= 0x17,
	ksCMD_SHIFT_RIGHT				= 0x18,
	ksCMD_PLUS						= 0x19,
	ksCMD_MINUS						= 0x1a,
	ksCMD_NOT						= 0x1b,
	ksCMD_PUSH_FUNC					= 0x1c,
	ksCMD_PUSH_STRUCT				= 0x1d,
	ksCMD_PUSH_ZERO					= 0x1e,
	ksCMD_PUSH_ONE					= 0x1f,
	ksCMD_PUSH_INT					= 0x20,
	ksCMD_PUSH_FLOAT				= 0x21,
	ksCMD_PUSH_STRING				= 0x22,
	ksCMD_PUSH_NULL					= 0x23,
	ksCMD_POP						= 0x24,

	/* ジャンプ命令 */
	ksCMD_JZ						= 0x25,		/* ZERO だったらジャンプ		*/
	ksCMD_JNZ						= 0x26,		/* NOT ZERO だったらジャンプ	*/
	ksCMD_JMP						= 0x27,		/* 無条件ジャンプ			*/

	ksCMD_SET_LOCAL					= 0x28,
	ksCMD_SET_LOCAL_ARRAY			= 0x29,
	ksCMD_SET_GLOBAL				= 0x2a,
	ksCMD_SET_GLOBAL_ARRAY			= 0x2b,
	ksCMD_SET_MEMBER				= 0x2c,

	ksCMD_GET_LOCAL					= 0x2d,
	ksCMD_GET_LOCAL_ARRAY			= 0x2e,
	ksCMD_GET_GLOBAL				= 0x2f,
	ksCMD_GET_GLOBAL_ARRAY			= 0x30,
	ksCMD_GET_MEMBER				= 0x31,
	
	/* 構造体用メンバ( 命令 + 値 + 値 ) */
	ksCMD_SET_MEMBER_LOCAL			= 0x32,
	ksCMD_SET_MEMBER_LOCAL_ARRAY	= 0x33,
	ksCMD_SET_MEMBER_GLOBAL			= 0x34,
	ksCMD_SET_MEMBER_GLOBAL_ARRAY	= 0x35,
	ksCMD_GET_MEMBER_LOCAL			= 0x36,
	ksCMD_GET_MEMBER_LOCAL_ARRAY	= 0x37,
	ksCMD_GET_MEMBER_GLOBAL			= 0x38,
	ksCMD_GET_MEMBER_GLOBAL_ARRAY	= 0x39,

	ksCMD_FORCE32					= 0x7fffffff,

};


#endif	/* __KSINTERMEDIATECODE_H__ */

