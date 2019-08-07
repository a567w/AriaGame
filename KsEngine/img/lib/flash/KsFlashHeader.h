/************************************************************************************************/
/** 
 * @file		KsFlashBase.h
 * @brief		ゲームマネージャ
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSFLASHBASE_H__
#define __KSFLASHBASE_H__

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
 * @class		KsFlashRect
 * @brief		Flash(SWF)Header
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		最初の3 バイトは’FWS’、4 バイト目がヴァージョン、5～8 バイト目がファイルの長さである。
 *				その後画面のサイズ、フレームの再生レート、フレームの数が続く。
 */
/************************************************************************************************/
class KsFlashHeader
{
	public:

		/**
		 * デストラクタ
		 */
								KsFlashHeader( KsUInt8 version, KsUInt32 fileSize, KsInt32 width, KsInt32 height, KsUInt16 frameRate, KsUInt16 frameCount );
		
		/**
		 * デストラクタ
		 */
		virtual					KsFlashHeader( KsUInt8 version, KsUInt32 fileSize, KsInt32 width, KsInt32 height, KsReal64 frameRate, KsUInt16 frameCount );

		/**
		 * デストラクタ
		 */
								~KsFlashHeader() {}

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
		KsFlashRect				getFrameSize() { return m_rect; }

		/**
		 * フレームレートを取得する
		 * @return				フレームレート
		 */
		KsFlashFixed16			getFrameRate() const { return m_frameRate; }

		/**
		 * トータルフレーム数を取得する
		 * @return				トータルフレーム数
		 */
		KsUInt16				getFrameCount() const { return frameCount; }

	private:
		KsUInt8					m_signature[ 3 ];	/**< SWF 識別子				*/
		KsUInt8					m_version;			/**< バージョン				*/
		KsUInt32				m_fileSize;			/**< ファイルサイズ			*/
		KsFlashRect				m_frameSize;		/**< フレームサイズ			*/
		KsFlashFixed16			m_frameRate;		/**< フレームレート			*/
		KsUInt16				m_frameCount;		/**< トータルフレーム数		*/

	protected:
								KsFlashHeader() {}
		friend class KsFlashImporter;
};




62 byte


/************************************************************************************************/
/**
 * @class		KsFlashTag
 * @brief		Flash(SWF)Header
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		TagHeader 16bit
 *				| ID( 10 bit ) | length( 6 bit ) |
 *  tagID  = Code >> 6; 
 *  length = Code & 0x3f;
 *	length が 0x3f のときは32bit length
 */
/************************************************************************************************/
class KsFlashTag
{
	    friend class KsFlashImporter;
	
	public:
		/**
		 * コンストラクタ
		 * @param	tagID		タグID
		 * @param	length		タグの長さ
		 */
	    						KsFlashTag( KsUInt16 tagID, KsUInt32 length ) : m_tagID( tagID ), m_length( length ) {}

		/**
		 * デストラクタ
		 */
	    virtual					~KsFlashTag() {}

		/**
		 * タグIDを取得する
		 * @return				タグID
		 */
	    KsUInt16				getTagID() const { return m_tagID; }
	
		/**
		 * タグの長さを取得する
		 * @return				タグの長さ
		 */
	    KsUInt32				getTagLength() const { return m_length; }

	private:
	    KsUInt16				m_tagID;		/**< タグID			*/
	    KsUInt32				m_length;		/**< タグのサイズ	*/

	protected:
		/**
		 * コンストラクタ
		 */
	    						KsFlashTag() {}
};



class KsFlashTag
{
	public:
	    KsFlashTag() {}
	    ~FlashTag() {}

	    void 			setImportSize( KsUInt32 size ) { m_importSize = size; }	
	protected:
	    KsUInt32		m_importSize;
};





class KsFlashDisplayListTag : public KsFlashTag
{
	public:
		KsFlashDisplayListTag() {}
		virtual		~KsFlashDisplayListTag() {}
		virtual KsBool			isFrame() { return ksFALSE; }

};


class KsFlashIDEnabled
{
	public:
		KsFlashIDEnabled( KsBool count=ksTrue ) { if( count ){ m_charID = m_idFactory.getCharacterID(); } }

		void				getID( KsUInt16 id ) { m_charID=id; }
		KsUInt16			getID() const { return m_charID; }
	private:
		KsFlashIDFactory	m_idFactory;
		KsUInt16			m_charID;
};




#endif /* __KSFLASHBASE_H__ */

