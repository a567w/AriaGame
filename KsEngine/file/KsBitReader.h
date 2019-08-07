/************************************************************************************************/
/** 
 * @file		KsBitReader.h
 * @brief		KsBitReader
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSBITREADER_H__
#define __KSBITREADER_H__

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
 * @class		KsBitReader
 * @brief		Bit Reader
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
class ksENGINE_API KsBitReader
{
	public:
		/**
		 * コンストラクタ
		 */
							KsBitReader();

		/**
		 * コンストラクタ
		 */
							KsBitReader( const KsByte* pBuffer, KsInt32 size );

		/**
		 * デストラクタ
		 */
		virtual				~KsBitReader();

		/**
		 * セットアップ
		 */
		void				setup( const KsByte* pBuffer, KsInt32 size );

		/**
		 * 読み込み
		 */
		KsUInt32			readUInt32( KsUInt8 uReadBit );

		/**
		 * 読み込み
		 */
		KsInt32				readInt32( KsUInt8 uReadBit );

		/**
		 * 読み込み
		 */
		KsLong				getNBitInt( KsInt32 n, KsBool is_signed );

		/**
		 * 読み込み
		 */
		KsUInt8				getByte();

		KsInt32				getTotalReadBit() const { return m_sTotalReadBit; }

		/** 
		 * バイトアラインメンとする
		 */
		void				byteAlign();

	protected:
		const KsByte*		m_pBuffer;
		KsInt32				m_sBufferSizeBit;
		KsInt32				m_sTotalReadBit;
		KsInt32				m_size;
		KsInt32				m_pos;
		KsUInt8				m_buf;
		KsUInt8				m_bits;
};

/************************************************************************************************/
/**
 * @class		KsFileBitReader
 * @brief		SWF FILE HEADER
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
class ksENGINE_API KsFileBitReader
{
	public:
		/**
		 * コンストラクタ
		 */
									KsFileBitReader();

		/**
		 * コンストラクタ
		 */
									KsFileBitReader( const KsChar* pFileName );

		/**
		 * コンストラクタ
		 */
									KsFileBitReader( const KsByte* pBuffer, KsInt32 size );

		/**
		 * デストラクタ
		 */
		virtual						~KsFileBitReader();

		/**
		 * ファイルから浮動小数点の値を読み込む
		 * @return					浮動小数点の値
		 */
		virtual KsReal				readReal();

		/**
		 * ファイルから32bit整数値を読み込む
		 * @return					32bit整数値
		 */
		virtual KsInt32				readInt32();

		/**
		 * ファイルから符号なし32bit整数値を読み込む
		 * @return					符号なし32bit整数値
		 */
		virtual KsUInt32			readUInt32();

		/**
		 * ファイルから16bit整数値を読み込む
		 * @return					16bit整数値
		 */
		virtual KsInt16				readInt16();

		/**
		 * ファイルから符号なし16bit整数値を読み込む
		 * @return					符号なし16bit整数値
		 */
		virtual KsUInt16			readUInt16();

		/**
		 * ファイルから8bit整数値を読み込む
		 * @return					8bit整数値
		 */
		virtual KsInt8				readInt8();

		/**
		 * ファイルから符号なし8bit整数値を読み込む
		 * @return					符号なし8bit整数値
		 */
		virtual KsUInt8				readUInt8();

		/**
		 * バッファに指定バイト数分読み込む
		 * @param	pBuffer			(OUT)読み込むためのバッファ
		 * @param	count			読み込むバイト数
		 * @return					読み込んだバイト数
		 */
		virtual KsSize				read( void *pBuffer, KsInt32 count );

		/**
		 * ビット数分読み込む
		 * @param	n				読み込むビット数
		 * @param	bIsSigned		符号ありかどうかのフラグ
		 * @return					指定ビット数分の整数値
		 */
		virtual KsInt32				readBit( KsInt32 n, KsBool bIsSigned );

		/** 
		 * バイトアラインメンとする
		 */
		virtual void				byteAlign();

		KsUInt8						getByte();

	protected:
		KsFileObject*				m_pFile;
		const KsByte*				m_pBuffer;
		KsInt32						m_sBufferSizeBit;
		KsInt32						m_sTotalReadBit;
		KsInt32						m_size;
		KsInt32						m_pos;
		KsUInt8						m_data;
		KsUInt8						m_bits;
};


#endif	/* __KSBITREADER_H__ */

