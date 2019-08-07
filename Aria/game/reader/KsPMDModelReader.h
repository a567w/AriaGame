/************************************************************************************************/
/** 
 * @file		KsPMDModelReader.h
 * @brief		PMD Model Reader
 * @author		Tsukasa Kato
 * @date		2011/07/02
 * @since		2011/07/02
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSPMDMODELREADER_H__
#define __KSPMDMODELREADER_H__

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
 * PMD Model Reader
 * @class	KsPMDModelReader
 * @author  Tsukasa Kato
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class KsPMDModelReader : public KsFileAsyncReader
{
	public:
		/**
		 * コンストラクタ
		 * 同期読み込み(読み込みが終了するまで待つ)
		 * @param		fileName		ファイル名
		 */
										KsPMDModelReader( const KsString& fileName );

		/**
		 * デストラクタ
		 */
										~KsPMDModelReader();

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

	private:
		KsModel*						m_pModel;
};

#endif	/* __KSPMDMODELREADER_H__ */


