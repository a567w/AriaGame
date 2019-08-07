	/************************************************************************************************/
/** 
 * @file		KsAssert.h
 * @brief		�A�T�[�g����
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSASSERT_H__
#define __KSASSERT_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsType.h"


/*************************************************************************************************/
/**
 * �f�o�b�N�p�}�N��(�u���C�N�|�C���g�ݒ�)
 */
/*************************************************************************************************/
#ifdef _DEBUG
	/* �u���C�N�|�C���g�ݒ� */
	//#ifdef _WIN
	#define KsDebugBreak()			__asm { int 3 }
	//#endif
#else
	#define KsDebugBreak()			::exit( 0 );
#endif

/*************************************************************************************************/
/**
 * �A�T�[�g�p�}�N��, ���O�ɏ����c���܂��B
 */
/*************************************************************************************************/
//#ifdef _MASTER
#if 1
	// �x��(�}�X�^�[�ł́C�����Ȃ�)
	#define KsAssert( cmp, str )
	#define KsAssertEx( cmp )
#else
	// �x��(���O�Ɏc��)
	#define KsAssert( cmp, str )	if( !(cmp) ){															\
										KsChar		buf[ 512 ];												\
										sprintf( buf,"%s [ FILE %s, LINE %d ]\n", str, __FILE__,__LINE__);	\
										KsLogManager::message( str, ksLOG_LEVEL_ASSERT );					\
										KsDebugBreak();														\
									}

	#define KsAssertEx( cmp )		if( !(cmp) ){													\
										KsChar		buf[ 512 ];										\
										sprintf( buf,"FILE %s, LINE %d\n", __FILE__,__LINE__);		\
										KsLogManager::message( buf, ksLOG_LEVEL_ASSERT );			\
										KsDebugBreak();												\
									}
#endif

/*************************************************************************************************/
/**
 * ���b�Z�[�W�p�}�N��, ���O�ɏ����c���܂��B
 */
/*************************************************************************************************/
#ifdef _MASTER
	#define KsMessage( str )
#else
	#define KsMessage( str ) KsLogManager::message( str, ksLOG_LEVEL_MESSAGE )
#endif

/*************************************************************************************************/
/**
 * �G���[�p�}�N��, ���O�ɏ����c���܂��B
 */
/*************************************************************************************************/
#ifdef _MASTER
	#define KsError( str )
#else
	#define KsError( str )		KsLogManager::message( str, ksLOG_LEVEL_ERROR );
#endif


/*************************************************************************************************/
/**
 * �G���[�p�}�N��, ���O�ɏ����c���܂��B
 */
/*************************************************************************************************/
inline void KsPrintf( const KsChar* pszFormat, ... )
{
#if !defined( _MASTER )
	va_list	argp;
	KsChar pszBuf[ 512 ];
	va_start(argp, pszFormat);
	vsprintf( pszBuf, pszFormat, argp);
	va_end(argp);
	OutputDebugString( pszBuf );
#endif
}

#endif	/* __KSASSERT_H__ */
