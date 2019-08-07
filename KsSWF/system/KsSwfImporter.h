/************************************************************************************************/
/** 
 * @file		KsSwfImporter.h
 * @brief		SWF読み込み
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSWFIMPORTER_H__
#define __KSSWFIMPORTER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
//#include "KsTypeSwf.h"
//#include "KsSwfFileHeader.h"
//#include "KsSwfTag.h"
//#include "KsSwfMatrix.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsSwfImporter
 * @brief		SWF読み込み
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 * @note		なし
 */
/************************************************************************************************/
class ksSWF_API KsSwfImporter
{
	protected:
		KsFileObject*			m_pFile;		/**< ファイルオブジェクト	*/

	public:
		/**
		 * コンストラクタ
		 */
								KsSwfImporter();

		/**
		 * コンストラクタ
		 */
								KsSwfImporter( KsFileObject* pFile );
	    
		/**
		 * デストラクタ
		 */
								~KsSwfImporter();

		/**
		 * ファイルヘッダを取得する
		 */
		KsBool					readFileHeader( KsSwfFileHeader* pFileHeader );

		/**
		 * タグを読み込み
		 */
		KsBool					readRecordHeader( KsSwfRecordHeader* pTag );

		/**
		 * Rect情報を読み込み
		 */
		KsBool					readRect( KsSwfRect* pRect );

		/**
		 *
		 */
		KsBool					readMatrix( KsSwfMatrix* pMatrix );

		/**
		 *
		 */
		static KsBool			readRect( KsFileObject* pFile, KsSwfRect* pRect );
		static KsBool			readMatrix( KsFileObject* pFile, KsSwfMatrix* pMatrix );
};

ksSWF_API KsBool	KsLoadSwf( const KsChar* pFileName );

#endif	/* __KSSWFIMPORTER_H__ */


