/*************************************************************************************************/
/** 
 * @file		KsLog.cpp
 * @brief		���O�}�l�[�W��
 * @author		Tsukasa Kato
 * @date		2005/06/27
 * @since		2005/06/27
 * @version		1.0.0
 */
/*************************************************************************************************/

/*===============================================================================================*/
/*								�y�C���N���[�h�t�@�C���z							 				 */
/*===============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"

/*===============================================================================================*/
/*										�y�錾�z								  					 */
/*===============================================================================================*/
FILE*		KsLogManager::m_pFile         = NULL;
KsUInt16	KsLogManager::m_logLevelMask  = ksLOG_LEVEL_MASK_DEFAULT;
KsUInt16	KsLogManager::m_logOutputMask = ksLOG_OUT_MASK_DEFAULT;
KsBool		KsLogManager::m_isFileOpen    = ksFALSE;

/*===============================================================================================*/
/*										�y��`�z								  					 */
/*===============================================================================================*/
#define ksDEBUG_OUT		OutputDebugString

/*************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/*************************************************************************************************/
KsLogManager::~KsLogManager()
{
	if( m_isFileOpen )
	{
		fclose( m_pFile );
	}
}

/*************************************************************************************************/
/*
 * ���b�Z�[�W���Z�b�g����
 * @param		message			���b�Z�[�W
 * @param		logLevel		���O���x��
 */
/*************************************************************************************************/
void KsLogManager::message( const KsChar* message, ksLOG_LEVEL logLevel )
{
	static KsChar*	logLevelTbl[] = {
										_T("None    : "),
										_T("Message : "),
										_T("Warring : "),
										_T("Assert  : "),
										_T("Error   : "),
									};
	/* �t�@�C���I�[�v���`�F�b�N */
	if( !m_isFileOpen )
	{
		if( m_logOutputMask & ksLOG_OUT_FILE )
		{
			m_pFile = ks_fopen( ksLOG_FILE_NAME, _T("at+") );
			m_isFileOpen = ksTRUE;
		}
	}

	/* �o�̓`�F�b�N */
	if( m_logLevelMask & logLevel )
	{
		/* �^�C���X�^���v���̂������ق�������? */
		KsChar		buffer[ 1024 ];
		KsInt32		type;
		
		switch( logLevel )
		{
			case ksLOG_LEVEL_MESSAGE:	{ type = 1; break; }
			case ksLOG_LEVEL_WARRNING:	{ type = 2; break; }
			case ksLOG_LEVEL_ASSERT:	{ type = 3; break; }
			case ksLOG_LEVEL_ERROR:		{ type = 4; break; }
			default:					{ type = 0; break; }
		}

#ifdef  UNICODE
		swprintf( &buffer[0], 1024, L"%s%s", logLevelTbl[ type ], message );
#else
		sprintf( buffer, "%s%s", logLevelTbl[ type ], message );
#endif // #ifdef  UNICODE
	
		/* �o�� */
		if( m_logOutputMask & ksLOG_OUT_CONSOLE )
		{
			printf( "%s\n", buffer );
		}
		
		if( m_logOutputMask & ksLOG_OUT_CONSOLE_WIN )
		{
			ksDEBUG_OUT( buffer );
		}
		
		if( m_logOutputMask & ksLOG_OUT_FILE )
		{
			fprintf( m_pFile, "%s", buffer );
		}
	}
	else
	{
		KsChar		buffer[ 1024 ];

		if( logLevel == ksLOG_OUT_NONE )
		{
			sprintf( buffer, "%s", message );
	
			/* �o�� */
			if( m_logOutputMask & ksLOG_OUT_CONSOLE )
			{
				printf( "%s\n", buffer );
			}
			
			if( m_logOutputMask & ksLOG_OUT_CONSOLE_WIN )
			{
				ksDEBUG_OUT( buffer );
			}
			
			if( m_logOutputMask & ksLOG_OUT_FILE )
			{
				fprintf( m_pFile, "%s", buffer );
			}
		}
	}
}

/*************************************************************************************************/
/**
 * �t�H�[�}�b�g�t���Ń��b�Z�[�W���Z�b�g����
 * @param		logLevel		���O���x��
 * @param		message			���b�Z�[�W
 * @param		...				�ψ���
 */
/*************************************************************************************************/
void KsLogManager::message( ksLOG_LEVEL logLevel, const KsChar* format, ... )
{
	KsChar		buffer[ 512 ];
	va_list		list;
	
	va_start( list, format );
	ks_vsprintf( buffer, 512, format, list );
	
	message( buffer, logLevel );
	
	va_end( list );
}

/*************************************************************************************************/
/*
 * ���O���x���}�X�N�Z�b�g
 * @param		logLevelMask	���O���x���}�X�N
 */
/*************************************************************************************************/
void KsLogManager::setLogLevelMask( KsUInt16 logLevelMask )
{
	m_logLevelMask = logLevelMask;
}

/*************************************************************************************************/
/*
 * ���O�o�̓}�X�N�Z�b�g
 * @param		logOutputMask	���O�o�̓}�X�N
 */
/*************************************************************************************************/
void KsLogManager::setLogOutputMask( KsUInt16 logOutputMask )
{
	m_logOutputMask = logOutputMask;
}

/*************************************************************************************************/
/*
 * ���O���x���}�X�N�擾
 * @return						���O���x���}�X�N
 */
/*************************************************************************************************/
KsUInt16 KsLogManager::getLogLevelMask() 
{
	return m_logOutputMask;
}

/*************************************************************************************************/
/*
 * ���O�o�̓}�X�N�擾
 * @return						���O�o�̓}�X�N
 */
/*************************************************************************************************/
KsUInt16 KsLogManager::getLogOutputMask() 
{
	return m_logOutputMask;
}


