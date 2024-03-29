/************************************************************************************************/
/** 
 * @file		KsSwfDefineBitsJPEG2.h
 * @brief		SWFコマンド
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSWFDEFINEBITSJPEG2_H__
#define __KSSWFDEFINEBITSJPEG2_H__

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
 * @class		KsSwfDefineBitsJPEG2
 * @brief		SWFコマンド
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 * @note		なし
 */
/************************************************************************************************/
class ksSWF_API KsSwfDefineBitsJPEG2 : public KsSwfCommand
{
	public:
		/**
		 * コンストラクタ
		 */
								KsSwfDefineBitsJPEG2( KsFileObject* pFile, const KsSwfRecordHeader* tag );

		/**
		 * デストラクタ
		 */
		virtual					~KsSwfDefineBitsJPEG2();

		/**
		 * コマンド実行
		 */
		virtual void			execute();

	private:
		KsUInt32				m_characterID;	/**< キャラクタの ID	*/
		KsByte*					m_data;			/**< JPEG, PNG, GIF89a のいずれかの圧縮済み画像データ	*/
		KsUInt32				m_size;			/**< サイズ		*/
};

#endif	/* __KSSWFDEFINEBITSJPEG2_H__ */


