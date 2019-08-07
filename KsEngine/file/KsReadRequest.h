/************************************************************************************************/
/**
 * @file		KsReadRequest.h
 * @brief		ファイルシステム
 * @author		Tsukasa Kato
 * @date		2004/03/30
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSREADREQUEST_H__
#define __KSREADREQUEST_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsFileAsyncReader;

/************************************************************************************************/
/**
 * 読み込みステート
 */
/************************************************************************************************/
enum ksREADING_STATE
{
	ksREADING_START      = 0,				/**< 読み込み開始待ち			*/
	ksREADING_READ       = 1,				/**< 読み込み中				*/
	ksREADING_END        = 2,				/**< 読み込み終了			*/
	ksREADING_OPEN_IDLE  = 3,				/**< オープンアイドリング		*/
	ksREADING_READ_IDLE  = 4,				/**< 読み込みアイドリング		*/
	ksREADING_CLOSE_IDLE = 5,				/**< クローズアイドリング		*/
	ksREADING_ERROR      = 0x80000000,		/**< エラー					*/
	ksREADING_FORCE32    = 0x7fffffff,		/**< 強制32ビット			*/
};


/************************************************************************************************/
/**
 * ファイル読み込み終了時コールバック
 */
/************************************************************************************************/
typedef void (*KsFileReadEndCB)( void* pData, KsInt32 size, void* pUserData );

/************************************************************************************************/
/**
 * @class		KsReadRequest
 * @brief		読み込みリクエストクラス(非同期読み込み時に使用する)
 * @author		Tsukasa Kato
 * @date		2004/03/30
 * @version		1.0.0
 */
/************************************************************************************************/
class ksENGINE_API KsReadRequest
{
		friend class KsFileSystem;
	public:
		/**
		 * コンストラクタ
		 */
									KsReadRequest();

		/**
		 * デストラクタ
		 */
		virtual						~KsReadRequest();

		/**
		 * 現在のステータスを取得する
		 * @return					現在のステータス
		 */
		virtual ksREADING_STATE		getStatus() const { return m_status; }

		/**
		 * 読み込んだデータのサイズを取得する
		 * @return					読み込んだデータのサイズ
		 */
		virtual KsUInt32			getReadSize() const { return m_readSize; }

		/**
		 * データのサイズを取得する
		 * @return					データのサイズ
		 */
		virtual KsUInt32			getDataSize() const { return m_dataSize; }

		/**
		 * 読み込みようバッファをセットする(指定バッファを使用したいとき)
		 */
		virtual void				setBuffer( KsUInt8* pBuffer, KsUInt32 bufferSize );

		/**
		 * バッファのポインタを取得する
		 * @return					バッファのポインタ
		 */
		virtual KsUInt8*			getBuffer() { return m_pBuffer; }

		/**
		 * バッファのサイズを取得する
		 * @return					バッファのサイズ
		 */
		virtual KsUInt32			getBufferSize() { return m_bufferSize; }

		/**
		 * コールバック（メイン用）
		 */
		virtual void				callback();

		/**
		 * コールバック（スレッド用）
		 */
		virtual void				callbackThread();

	protected:
		ksREADING_STATE				m_status;			/**< ステータス								*/
		KsBool						m_bufferFlag;		/**< 内部と外部のどちらで確保したかのフラグ	*/
		KsULong						m_bufferSize;		/**< バッファのサイズ							*/
		KsUInt8*					m_pBuffer;			/**< データ読み取り用バッファ					*/
		KsULong						m_dataSize;			/**< データのサイズ							*/
		KsULong						m_readSize;			/**< 読み込んだデータのサイズ					*/
		KsString					m_fileName;			/**< ファイル名								*/
		KsHandle					m_fileHandle;		/**< ファイルハンドル							*/
		KsHandle					m_threadHandle;		/**< スレッドハンドル							*/
		KsUInt32					m_threadID;			/**< スレッドID								*/
		KsFileReadEndCB				m_callback;			/**< コールバック							*/
		void*						m_pUserData;		/**< ユーザーデータ							*/
		KsFileReadEndCB				m_callbackThread;	/**< コールバック							*/
		void*						m_pUserDataThread;	/**< スレッド用ユーザーデータ					*/
		OVERLAPPED					m_overlapped;		/**< オーバーラップ							*/
		KsBool						m_bAutoDelete;		/**< 自動削除フラグ							*/
};

#endif /* __KSREADREQUEST_H__ */

