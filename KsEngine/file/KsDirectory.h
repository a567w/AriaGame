/************************************************************************************************/
/**
 * @file	KsDirectoy.h
 * @brief	ディレクトリ操作
 * @author	tsukasa kato
 * @date	2004/03/30
 * @version	1.0.0
 */
/************************************************************************************************/
#ifndef __KSDIRECTORY_H__
#define __KSDIRECTORY_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class	KsDirectoy
 * @brief	ディレクトリ取得
 * @author	tsukasa kato
 * @date	2003/11/30
 * @version	1.0.0
 */
/************************************************************************************************/
class KsDirectory
{
	public:
		/**
		 * コールバック関数
		 * @param		fileName			ファイル名
		 * @param		pData				データ
		 */
		typedef void						(*KsDirectoryCB)( const KsChar* fileName, void* pData );

	public:
		/**
		 * コンストラクタ
		 */
											KsDirectory();

		/**
		 * コンストラクタ
		 * @param		directoryName		ディレクトリ名
		 * @param		pParent				親ディレクトリ
		 */
											KsDirectory( const KsString& directoryName, KsDirectory* pParent );

		/**
		 * デストラクタ
		 */
		virtual								~KsDirectory();

		/**
		 * フルパスを取得する
		 * @return							フルパス
		 */
		const KsString&						getFullPath() const { return m_fullPath; }

		/**
		 * このディレクトリの名前を取得する
		 * @return							ディレクトリ名
		 */
		const KsString&						getDirectoryName() const { return m_directoryName; }

		/**
		 * 親のディレクトリを取得する
		 * @return							親のディレクトリ(存在しないときはNULLを返す)
		 */
		KsDirectory*						getParentDirectory() { return m_pParent; }

		/**
		 * ディレクトリを解析する
		 * @param		directory			解析するディレクトリ
		 */
		void								parseDirectory( const KsString& directory );

		/**
		 * アタッチする
		 * @param		directory			アタッチするディレクトリ
		 */
		void								attach( KsDirectory* pDirectory );

		/**
		 * デタッチする
		 * @param		directory			デタッチするディレクトリ
		 */
		void								detach( KsDirectory* pDirectory );
	
		/**
		 * ファイルリストを取得する
		 * @param 
		 */
		const KsString&						getFile( KsInt32 index ) const { return m_fileList[ index ]; }

		/**
		 * 
		 * 
		 */
		const KsDirectory*					getDirectory( KsInt32 index ) const { return m_vpDirectories[ index ]; }

		KsUInt32							getNumFile()	const { return static_cast<KsUInt32>( m_fileList.size() ); }

		KsUInt32							getNumDirectory()	const { return static_cast<KsUInt32>( m_vpDirectories.size() ); }

		// 階層の深さ
		//void								allFileExecCB();

	protected:
		//KsArray< KsFile > 本当はハッシュテーブルを使用したほうがいい
		KsArray< KsString >					m_fileList;				/**< ファイルリスト		*/
		KsArray< KsDirectory* >				m_vpDirectories;		/**< ディレクトリリスト	*/
		KsString							m_fullPath;				/**< フルパス			*/
		KsString							m_directoryName;		/**< ディレクトリ名		*/
		KsDirectory*						m_pParent;				/**< 親ディレクトリ		*/
};


#endif		/* __KSDIRECTORY_H__ */
