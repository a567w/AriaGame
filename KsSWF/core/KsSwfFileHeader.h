/************************************************************************************************/
/** 
 * @file		KsSwfFileHeader.h
 * @brief		SWFファイルヘッダ
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSWFFILEHEADER_H__
#define __KSSWFFILEHEADER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsSwfhHeader
 * @brief		SWF FILE HEADER
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 * @note		最初の3 バイトは’FWS’、4 バイト目がヴァージョン、5〜8 バイト目がファイルの長さである。
 *				その後画面のサイズ、フレームの再生レート、フレームの数が続く。
 */
/************************************************************************************************/
class ksSWF_API KsSwfFileHeader
{
		friend class KsSwfImporter;

	public:
		/**
		 * コンストラクタ
		 */
								KsSwfFileHeader();

		/**
		 * デストラクタ
		 */
		virtual					~KsSwfFileHeader();

		/**
		 * バージョンを取得する
		 * @return				SWFバージョン
		 */
		KsUInt8					getVersion() const { return m_version; }

		/**
		 * ファイルサイズを取得する
		 * @return				ファイルサイズ
		 */
		KsUInt32				getFileSize() const { return m_fileSize; }

		/**
		 * フレームサイズを取得する
		 * @return				フレームサイズ
		 */
		KsSwfRect				getFrameSize() { return m_frameSize; }

		/**
		 * フレームレートを取得する
		 * @return				フレームレート
		 */
		KsSwfFixed16			getFrameRate() const { return m_frameRate; }

		/**
		 * トータルフレーム数を取得する
		 * @return				トータルフレーム数
		 */
		KsUInt16				getFrameCount() const { return m_frameCount; }

	private:
		KsUInt8					m_signature[ 3 ];	/**< SWF 識別子				*/
		KsUInt8					m_version;			/**< バージョン				*/
		KsUInt32				m_fileSize;			/**< ファイルサイズ			*/
		KsSwfRect				m_frameSize;		/**< フレームサイズ			*/
		KsSwfFixed16			m_frameRate;		/**< フレームレート			*/
		KsUInt16				m_frameCount;		/**< トータルフレーム数		*/
};

#endif	/* __KSSWFFILEHEADER_H__ */

