/************************************************************************************************/
/** 
 * @file		KsSwfMetadata.h
 * @brief		SWFコマンド
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSWFMETADATA_H__
#define __KSSWFMETADATA_H__

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
 * @class		KsSwfMetadata
 * @brief		SWFコマンド
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 * @note		なし
 */
/************************************************************************************************/
class ksSWF_API KsSwfMetadata : public KsSwfCommand
{
	public:
		/**
		 * コンストラクタ
		 */
								KsSwfMetadata( KsFileObject* pFile );

		/**
		 * デストラクタ
		 */
		virtual					~KsSwfMetadata();

		/**
		 * コマンド実行
		 */
		virtual void			execute();

	private:
		KsString				m_string;			/**< 文字列	*/
};

#endif	/* __KSSWFMETADATA_H__ */


