/************************************************************************************************/
/**
 * @file		KsBinaryReader.h
 * @brief		バイナリーリーダー
 * @author		Tsukasa Kato
 * @date		2004/03/30
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSBINARYREADER_H__
#define __KSBINARYREADER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsBinaryReader
 * @brief		バイナリーリーダー
 * @author		Tsukasa Kato
 * @date		2004/03/30
 * @version		1.0.0
 */
/************************************************************************************************/
class ksENGINE_API KsBinaryReader
{
	public:
		/**
		 * コンストラクタ
		 * @param		pFile			ファイルポインタ
		 */
		KsBinaryReader( const KsWChar* pFileName );

		/**
		 * コンストラクタ
		 * @param		pFile			ファイルポインタ
		 */
		KsBinaryReader( const KsSChar* pFileName );

		/**
		 * コンストラクタ
		 * @param		pFile			ファイルポインタ
		 */
		KsBinaryReader( const KsByte* pDataBlob, KsUInt32 dataSize );

		/**
		 * バイナリーから指定サイズを読み込む
		 * @return		データ
		 */
		template<typename T> T const& read()
		{
			return *readArray<T>(1);
		}

		/**
		 * バイナリーから指定サイズを読み込む
		 * @return		データ
		 */
		template<typename T> T const* readArray( KsUInt32 elementCount )
		{
			KsByte const* newPos = m_pPos + sizeof(T) * elementCount;

			if (newPos > m_pEnd)
				throw std::exception("End of file");

			T const* result = reinterpret_cast<T const*>(m_pPos);

			m_pPos = newPos;

			return result;
		}

		/**
		 * バイナリーから指定サイズを読み込む
		 * @return		データ
		 */
		static HRESULT readEntireFile( KsWChar const* pFileName, KsByte** pData, KsUInt32* pDataSize );

		/**
		 * バイナリーから指定サイズを読み込む
		 * @return		データ
		 */
		static HRESULT readEntireFile( KsSChar const* pFileName, KsByte** pData, KsUInt32* pDataSize );

	private:
		const KsByte*				m_pPos;			/**< */
		const KsByte*				m_pEnd;			/**< */
		KsByte*						m_pData;		/**< */


		// Prevent copying.
		KsBinaryReader( KsBinaryReader const&);
		KsBinaryReader& operator= ( KsBinaryReader const&);
};


#endif /* __KSBINARYREADER_H__ */


