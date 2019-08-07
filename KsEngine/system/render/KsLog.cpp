/*************************************************************************************************/
/** 
 * @file	KsLog.cpp
 * @brief	ログマネージャ
 * @author	Tsukasa Kato
 * @date	2004/08/12
 * @since	2004/08/12
 */
/*************************************************************************************************/

/*===============================================================================================*/
/*								【インクルードファイル】							 				 */
/*===============================================================================================*/
#include "KsLog.h"

/*===============================================================================================*/
/*										【宣言】								  					 */
/*===============================================================================================*/
FILE*		KsLogManager::m_pFile         = NULL;
KsUInt16	KsLogManager::m_logLevelMask  = ksLOG_LEVEL_MASK_DEFAULT;
KsUInt16	KsLogManager::m_logOutputMask = ksLOG_OUT_MASK_DEFAULT;
KsBool		KsLogManager::m_isFileOpen    = ksFALSE;

/*===============================================================================================*/
/*										【定義】								  					 */
/*===============================================================================================*/

/*************************************************************************************************/
/*
 * デストラクタ
 */
/*************************************************************************************************/
KsLogManager::~KsLogManager()
{
	if( m_isFileOpen ){
		fclose( m_pFile );
	}
}

/*************************************************************************************************/
/*
 * メッセージをセットする
 * @param		message			メッセージ
 * @param		logLevel		ログレベル
 */
/*************************************************************************************************/
void KsLogManager::message( const KsChar* message, ksLOG_LEVEL logLevel )
{
	static KsChar*	logLevelTbl[] = {
										"None    : ",
										"Message : ",
										"Warring : ",
										"Assert  : ",
										"Error   : ",
									};
	/* ファイルオープンチェック */
	if( !m_isFileOpen ){
		if( m_logOutputMask & ksLOG_OUT_FILE ){
			m_pFile = fopen( ksLOG_FILE_NAME, "at+" );
			m_isFileOpen = ksTRUE;
		}
	}

	/* 出力チェック */
	if( m_logLevelMask & logLevel )
	{
		/* タイムスタンプをのこしたほうがいい? */
		KsChar		buffer[ 512 ];
		KsInt32		type;
		
		switch( logLevel )
		{
			case ksLOG_LEVEL_MESSAGE:	{ type = 1; break; }
			case ksLOG_LEVEL_WARRNING:	{ type = 2; break; }
			case ksLOG_LEVEL_ASSERT:	{ type = 3; break; }
			case ksLOG_LEVEL_ERROR:		{ type = 4; break; }
			default:					{ type = 0; break; }
		}

		sprintf( buffer, "%s%s", logLevelTbl[ type ], message );
	
		/* 出力 */
		if( m_logOutputMask & ksLOG_OUT_CONSOLE ){
			printf( "%s\n", buffer );
		}
		
		if( m_logOutputMask & ksLOG_OUT_CONSOLE_WIN ){
			OutputDebugString( buffer );
		}
		
		if( m_logOutputMask & ksLOG_OUT_FILE ){
			fprintf( m_pFile, "%s", buffer );
		}
	}
	else{
		KsChar		buffer[ 512 ];

		if( logLevel == ksLOG_OUT_NONE ){
			sprintf( buffer, "%s", message );
	
			/* 出力 */
			if( m_logOutputMask & ksLOG_OUT_CONSOLE ){
				printf( "%s\n", buffer );
			}
			
			if( m_logOutputMask & ksLOG_OUT_CONSOLE_WIN ){
				OutputDebugString( buffer );
			}
			
			if( m_logOutputMask & ksLOG_OUT_FILE ){
				fprintf( m_pFile, "%s", buffer );
			}
		}
	}
}

/*************************************************************************************************/
/**
 * フォーマット付きでメッセージをセットする
 * @param		logLevel		ログレベル
 * @param		message			メッセージ
 * @param		...				可変引数
 */
/*************************************************************************************************/
void KsLogManager::message( ksLOG_LEVEL logLevel, const KsChar* format, ... )
{
	KsChar		buffer[ 1024 ];
	va_list		list;
	
	va_start( list, format );
	vsprintf( buffer, format, list );
	
	message( buffer, logLevel );
	
	va_end( list );
}

/*************************************************************************************************/
/*
 * ログレベルマスクセット
 * @param		logLevelMask	ログレベルマスク
 */
/*************************************************************************************************/
void KsLogManager::setLogLevelMask( KsUInt16 logLevelMask )
{
	m_logLevelMask = logLevelMask;
}

/*************************************************************************************************/
/*
 * ログ出力マスクセット
 * @param		logOutputMask	ログ出力マスク
 */
/*************************************************************************************************/
void KsLogManager::setLogOutputMask( KsUInt16 logOutputMask )
{
	m_logOutputMask = logOutputMask;
}

/*************************************************************************************************/
/*
 * ログレベルマスク取得
 * @return						ログレベルマスク
 */
/*************************************************************************************************/
KsUInt16 KsLogManager::getLogLevelMask() 
{
	return m_logOutputMask;
}

/*************************************************************************************************/
/*
 * ログ出力マスク取得
 * @return						ログ出力マスク
 */
/*************************************************************************************************/
KsUInt16 KsLogManager::getLogOutputMask() 
{
	return m_logOutputMask;
}




