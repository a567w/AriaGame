/************************************************************************************************/
/** 
 * @file		KsFilePack.h
 * @brief		ファイルパック
 * @author		Tsukasa Kato
 * @date		2004/11/24
 * @since		2004/11/24
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSFILEPACK_H__
#define __KSFILEPACK_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/*************************************************************************************************/
/**
 * パックファイルヘッダ構造体
 */
/*************************************************************************************************/
struct KsFilePackHeader
{
	KsByte				Signature[ 4 ];						/**< 識別用(KPAK)					*/
	KsUInt32			Version;							/**< バージョン						*/
	KsUInt32			NumFiles;							/**< ファイル数						*/
	KsUInt32			TotalSize;							/**< トータルデータサイズ				*/
};

/*************************************************************************************************/
/**
 * パックファイル情報構造体2
 */
/*************************************************************************************************/
struct KsFilePackInfo
{
	KsSChar				DataName[ 52 ];						/**< データの名前					*/
	KsUInt32			DataSize;							/**< データサイズ					*/
	KsUInt32			DataOffset;							/**< データオフセット				*/
	KsUInt16			DataKind;							/**< データオフの種類				*/
	KsUInt16			DataType;							/**< データオフのタイプ			*/
};

/************************************************************************************************/
/**
 * @class		KsFilePack
 * @brief		ファイルパックファイル構造
 * @author		Tsukasa Kato
 * @date		2004/03/30
 * @version		1.0.0
 */
/************************************************************************************************/
class ksENGINE_API KsFilePack
{
	public:
		/**
		 * コンストラクタ
		 */
									KsFilePack();

		/**
		 * デストラクタ
		 */
		virtual						~KsFilePack();

		/**
		 * 最初にデータを読み込んでパック検索データを生成する
		 * @param	fullPath		ファイルオ名
		 * @retval	ksTRUE			生成成功
		 * @retval	ksFALSE			生成失敗
		 */
		KsBool						createFromFile( const KsString& fullPath );

		/**
		 * 最初にデータを読み込んでパック検索データを生成する
		 * @param	pFile			ファイルオブジェクト
		 * @retval	ksTRUE			生成成功
		 * @retval	ksFALSE			生成失敗
		 */
		KsBool						create( KsFileObject* pFile );

		/**
		 * 破棄する
		 */
		void						destroy();

		/**
		 * ファイルを数を取得する
		 * @return					ファイル数
		 */
		KsUInt32					getNumFile();

		/**
		 * ファイルを取得する
		 * @param		index		インデックス
		 * @return					ファイル情報
		 */
		KsFilePackInfo*				getInfo( KsUInt32 index );

		/**
		 * ファイルを取得する
		 * @param		index		インデックス
		 * @return					ファイルデータ
		 */
		KsByte*						getData( KsUInt32 index );

	public:
		KsFilePackHeader			m_header;		/**< ファイルヘッダー		*/
		KsFilePackInfo*				m_pInfoList;	/**< ファイル情報リスト	*/
		KsByte*						m_pData;		/**< ファイルデータ		*/
};


#endif /* __KSFILEPACK_H__ */


