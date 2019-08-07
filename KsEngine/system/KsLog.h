/*************************************************************************************************/
/** 
 * @file		KsLog.h
 * @brief		ログマネージャ
 * @author		Tsukasa Kato
 * @date		2005/06/27
 * @since		2005/06/27
 * @version		1.0.0
 */
/*************************************************************************************************/
#ifndef __KSLOG_H__
#define __KSLOG_H__

/*===============================================================================================*/
/*								<< インクルードファイル >>										 */
/*===============================================================================================*/
#include "KsType.h"

/*===============================================================================================*/
/*										<< 定義 >>												 */
/*===============================================================================================*/
#define ksLOG_FILE_NAME	_T("log.txt")		/**< ログのファイル名	*/

/*************************************************************************************************/
/**
 * ログの出力先
 */
/*************************************************************************************************/
enum ksLOG_OUT
{
	ksLOG_OUT_NONE			= 0x0000,		/**< 空					*/
	ksLOG_OUT_CONSOLE		= 0x0001,		/**< コンソール			*/
	ksLOG_OUT_CONSOLE_WIN	= 0x0002,		/**< コンソールWindow	*/
	ksLOG_OUT_FILE			= 0x0004,		/**< ファイル			*/
};

#define ksLOG_OUT_MASK_DEFAULT		( ksLOG_OUT_FILE )
#define ksLOG_OUT_MASK_ALL			( ksLOG_OUT_CONSOLE | ksLOG_OUT_CONSOLE_WIN | ksLOG_OUT_FILE )

/*************************************************************************************************/
/**
 * ログレベル
 */
/*************************************************************************************************/
enum ksLOG_LEVEL
{
	ksLOG_LEVEL_NONE		= 0x0000,		/**< 空					*/
	ksLOG_LEVEL_MESSAGE		= 0x0001,		/**< メッセージ			*/
	ksLOG_LEVEL_WARRNING	= 0x0002,		/**< 注意				*/
	ksLOG_LEVEL_ASSERT		= 0x0004,		/**< 警告				*/
	ksLOG_LEVEL_ERROR		= 0x0008,		/**< エラー				*/
};

#define ksLOG_LEVEL_MASK_DEFAULT	( ksLOG_LEVEL_MESSAGE | ksLOG_LEVEL_WARRNING | ksLOG_LEVEL_ASSERT | ksLOG_LEVEL_ERROR )
#define ksLOG_LEVEL_MASK_ALL		( ksLOG_LEVEL_MESSAGE | ksLOG_LEVEL_WARRNING | ksLOG_LEVEL_ASSERT | ksLOG_LEVEL_ERROR )

/*************************************************************************************************/
/**
 * ログを残しておくためのクラス
 * @author	Tsukasa Kato
 * @since   2004/--/--
 * @version 2004/--/--
 * @note	
 */
/*************************************************************************************************/
class ksENGINE_API KsLogManager
{
	private:
		static FILE*					m_pFile;			/**< ファイルクラスのポインタ		*/
		static KsUInt16					m_logLevelMask;		/**< ログのレベルマスク			*/
		static KsUInt16					m_logOutputMask;	/**< ログの出力フラグ				*/
		static KsBool					m_isFileOpen;		/**< ファイルオープンフラグ		*/

    public:
    	/**
    	 * デストラクタ
    	 */
										~KsLogManager();
		 
    	/**
		 * メッセージをセットする
		 * @param		message			メッセージ
		 * @param		logLevel		ログレベル
		 */
		static void						message( const KsChar* message, ksLOG_LEVEL logLevel = ksLOG_LEVEL_MESSAGE );
		
		/**
		 * フォーマット付きでメッセージをセットする
		 * @param		logLevel		ログレベル
		 * @param		message			メッセージ
		 * @param		...				可変引数
		 */
		static void						message( ksLOG_LEVEL logLevel, const KsChar* format, ... );
		
		/**
		 * ログレベルマスクセット
		 * @param		logLevelMask	ログレベルマスク
		 */
		static void						setLogLevelMask( KsUInt16 logLevelMask );

		/**
		 * ログ出力マスクセット
		 * @param		logOutputMask	ログ出力マスク
		 */
		static void						setLogOutputMask( KsUInt16 logOutputMask );
		
		/**
		 * ログレベルマスク取得
		 * @return						ログレベルマスク
		 */
		static KsUInt16					getLogLevelMask();

		/**
		 * ログ出力マスク取得
		 * @return						ログ出力マスク
		 */
		static KsUInt16					getLogOutputMask();
};


#endif	/* __KSLOG_H__ */

