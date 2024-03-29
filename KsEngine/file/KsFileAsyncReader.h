/************************************************************************************************/
/** 
 * @file		KsFileAsyncReader.cpp
 * @brief		ファイルの非同期読み込みクラス
 * @author		Tsukasa Kato
 * @date		2011/07/02
 * @since		2011/07/02
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSFILEASYNCREADER_H__
#define __KSFILEASYNCREADER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * ファイルの非同期読み込みクラス
 * @class	KsFileAsyncReader
 * @author  Tsukasa Kato
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsFileAsyncReader : public KsReadRequest
{
	public:
		/**
		 * コンストラクタ
		 * 同期読み込み(読み込みが終了するまで待つ)
		 * @param		fileName		ファイル名
		 */
										KsFileAsyncReader( const KsString& fileName );

		/**
		 * コンストラクタ
		 * 同期読み込み(読み込みが終了するまで待つ)
		 * @param		pFileName		ファイル名
		 */
										KsFileAsyncReader( const KsChar* pFileName );

		/**
		 * デストラクタ
		 */
										~KsFileAsyncReader();

		/**
		 * コールバック（メイン用）
		 */
		virtual void					callback();

		/**
		 * コールバック（スレッド用）
		 */
		virtual void					callbackThread();

	protected:
		/**
		 * 読み込み終了時のコールバック関数
		 * @param		pFile			ファイルオブジェクト
		 */
		virtual KsBool					readEndCB( KsFileObject* pFile );

		/**
		 * 読み込み終了時のコールバック関数
		 * @param		pFile			ファイルオブジェクト
		 */
		virtual KsBool					readEndThreadCB( KsFileObject* pFile );
};

#endif	/* __KSFILEASYNCREADER_H__ */


