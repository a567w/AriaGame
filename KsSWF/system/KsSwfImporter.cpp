/************************************************************************************************/
/** 
 * @file		KsSwfImporter.cpp
 * @brief		SWF読み込み
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsSWF/KsSWFPreCompile.h"
//#include <zlib.h>

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

#if 0
class KsSwfFillStyle
{
	public:
		KsUInt8				m_fillStyleType;
		KsSwfColor			m_color;
		KsSwfMatrix			m_gradientMatrix;
							m_gradient;
		KsUInt16			m_bitmapId;
		KsSwfMatrix			m_bitmapMatrix;
};


class KsSwfFillStyleArray
{
	KsUInt8					m_fillStyleCount;
	KsUInt8					m_fillStyleCountExtended;
	KsSwfFillStyle* 		m_fillStyles;
};
#endif

/************************************************************************************************/
/* 
 *
 */
/************************************************************************************************/
KsSwfImporter::KsSwfImporter()
	: m_pFile( 0 )
{
}

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsSwfImporter::KsSwfImporter( KsFileObject* pFile )
	: m_pFile( pFile )
{
	KsSwfFileHeader		fileHeader;
	KsSwfRecordHeader	tag;
	KsSwfCommand*		pCommand = NULL;
	KsBool				bLoop = ksTRUE;

	/* ファイルヘッダ取得する */
	readFileHeader( &fileHeader );

	/* タグを解析する */
	while( bLoop )
	{
		pCommand = NULL;

		/* レコードタグを取得する */
		readRecordHeader( &tag );

		/* タグIDでの処理わけ */
		switch( tag.getID() )
		{
			case ksSWF_FILEATTRIBUTES:
			{
				/* ファイルアトリビュート */
				pCommand = ksNew KsSwfFileAttributes( m_pFile );
				break;
			}
			case ksSWF_METADATA:
			{
				/* メタデータ */
				pCommand = ksNew KsSwfMetadata( m_pFile );
				break;
			}
			case ksSWF_END:
			{
				/* 終了タグ */
				pCommand = ksNew KsSwfEndCmd( m_pFile );
				bLoop = ksFALSE;
				break;
			}
			case ksSWF_SHOWFRAME:
			{
				/* 表示タグ */
				pCommand = ksNew ksSwfShowFrame( m_pFile );
				break;
			}
			case ksSWF_SETBACKGROUNDCOLOR:
			{
				/* 背景カラーをセットする */
				pCommand = ksNew KsSwfSetBackGroundColorCmd( m_pFile );
				break;
			}
			case ksSWF_PLACEOBJECT:
			{
				/* オブジェクト配置 */
				pCommand = ksNew KsSwfPlaceObject( m_pFile );
				break;
			}
			//case ksSWF_PLACEOBJECT2:
			//{
				//break;
			//}
			case ksSWF_REMOVEOBJECT:
			{
				/* オブジェクト削除 */
				pCommand = ksNew KsSwfRemoveObject( m_pFile );
				break;
			}
			case ksSWF_REMOVEOBJECT2:
			{
				/* オブジェクト削除 */
				pCommand = ksNew KsSwfRemoveObject2( m_pFile );
				break;
			}
			case ksSWF_JPEGTABLES:
			{
				/* JPEG Table */
				pCommand = ksNew KsSwfJPEGTables( m_pFile, &tag );
				break;
			}
			case ksSWF_FRAMELABEL:
			{
				/* フレームの名前 */
				pCommand = ksNew KsSwfFrameLabel( m_pFile );
				break;
			}
			case ksSWF_PROTECT:
			{
				/* プロテクト(ファイルがオーサリング環境での編集用にインポートできないことを示します。) */
				m_pFile->seek( tag.getSize(), SEEK_CUR );
				break;
			}
			case ksSWF_DEFINEBITS:
			{
				/* 画像データ */
				pCommand = ksNew KsSwfDefineBits( m_pFile, &tag );
				break;
			}
			case ksSWF_DEFINEBITSJPEG2:
			{
				/* 画像データ */
				pCommand = ksNew KsSwfDefineBitsJPEG2( m_pFile, &tag );
				break;
			}
			case ksSWF_DEFINEBITSJPEG3:
			{
				/* 画像データ */
				pCommand = ksNew KsSwfDefineBitsJPEG3( m_pFile, &tag );
				break;
			}
			case ksSWF_DEFINESCENEANDFRAMELABELDATA:
			{
				/* シーン */
				pCommand = ksNew KsSwfDefineSceneAndFrameLabelData( m_pFile, &tag );
				break;
			}
			case ksSWF_DEFINESHAPE4:
			{
				m_pFile->seek( tag.getSize(), SEEK_CUR );
				break;
			}
			case ksSWF_DEFINESHAPE:
			case ksSWF_DEFINESHAPE2:
			case ksSWF_DEFINESHAPE3:
			case ksSWF_DEFINEMORPHSHAPE:
			case ksSWF_DEFINELOSSLESS:
			case ksSWF_DEFINELOSSLESS2:
			case ksSWF_DEFINEBUTTON:
			case ksSWF_DEFINEBUTTON2:
			case ksSWF_DEFINEBUTTONCXFORM:
			case ksSWF_DEFINEBUTTONSOUND:
			case ksSWF_DEFINEFONT:
			case ksSWF_DEFINEFONT2:
			case ksSWF_DEFINEFONTINFO:
			case ksSWF_DEFINEEDITTEXT:
			case ksSWF_DEFINETEXT:
			case ksSWF_DEFINETEXT2:
			case ksSWF_DEFINESOUND:
			case ksSWF_SOUNDSTREAMBLOCK:
			case ksSWF_SOUNDSTREAMHEAD:
			case ksSWF_SOUNDSTREAMHEAD2:
			case ksSWF_DEFINESPRITE:
			case ksSWF_STARTSOUND:
			case ksSWF_DOACTION:
			case ksSWF_EXPORTASSETS:
			case ksSWF_IMPORTASSETS:
			default:
			{
				m_pFile->seek( tag.getSize(), SEEK_CUR );
				break;
			}
		}
	}

}


/************************************************************************************************/
/* 
 *
 */
/************************************************************************************************/
KsSwfImporter::~KsSwfImporter()
{
}

/************************************************************************************************/
/* 
 *
 */
/************************************************************************************************/
KsBool KsSwfImporter::readFileHeader( KsSwfFileHeader* pFileHeader )
{
	/* 識別データ */
	m_pFile->read( pFileHeader->m_signature, 3 );

	/* バージョン */
	pFileHeader->m_version = m_pFile->readUInt8();

	/* ファイルサイズ（圧縮されている場合は展開後のサイズ）*/
	pFileHeader->m_fileSize = m_pFile->readUInt32();

	/* ファイルフォーマットチェック */
	if( ks_strncmp( r_cast<const KsChar*>( pFileHeader->m_signature ), "FWS", 3 ) == 0 )
	{
		/* 通常 */
	}
	else if( ks_strncmp( r_cast<const KsChar*>( pFileHeader->m_signature ), "CWS", 3 ) == 0 )
	{
		/* 圧縮あり */
#if 0
		KsULong		uDecodeBufferSize = 0;
		KsULong		uSourceBufferSize = 0;
		KsByte*		pDecodeBuffer     = NULL;
		KsByte*		pSourceBuffer     = NULL;

		uDecodeBufferSize = s_cast<KsULong>( pFileHeader->m_fileSize );
		uSourceBufferSize = s_cast<KsULong>( pFileHeader->getFileSize() - 8 );

		pDecodeBuffer = ksNew KsByte[ uDecodeBufferSize ];
		pSourceBuffer = ksNew KsByte[ uSourceBufferSize ];

		/* バッファに読み込む */
		m_pFile->read( pSourceBuffer, uSourceBufferSize );

		/* ファイルを閉じる */
		ksDELETE( m_pFile );

		/* 展開する */
		KsInt32	ret = uncompress( pDecodeBuffer, &uDecodeBufferSize, pSourceBuffer, uSourceBufferSize );
		
		if( ret != Z_OK )
		{
			return ksFALSE;
		}

		/* ファイルをセットしなおす */
		m_pFile = new KsFileBuffer( pDecodeBuffer, uDecodeBufferSize );
#endif
	}
	else
	{
		/* エラー */
		return ksFALSE;
	}

	/* フレームサイズ */
	readRect( &pFileHeader->m_frameSize );

	/* フレームレート */
	KsInt16	frameRate = m_pFile->readInt16();
	pFileHeader->m_frameRate.setFromRaw( frameRate );

	/* フレーム数 */
	KsUInt16	frameCount = m_pFile->readUInt16();
	pFileHeader->m_frameCount = frameCount;

	return ksTRUE;
}

/************************************************************************************************/
/* 
 *
 */
/************************************************************************************************/
KsBool KsSwfImporter::readRecordHeader( KsSwfRecordHeader* pTag )
{
	KsUInt16	code = m_pFile->readUInt16();
	KsUInt16	id   = code >> 6;
	KsUInt32	size = code & 0x3f;

	if( size == 0x3f )
	{
		size = m_pFile->readUInt32();
	}

	pTag->m_id   = id;
	pTag->m_size = size;

	return ksTRUE;
}

/************************************************************************************************/
/* 
 *
 */
/************************************************************************************************/
KsBool KsSwfImporter::readRect( KsSwfRect* pRect )
{
	return KsSwfImporter::readRect( m_pFile, pRect );
}

/************************************************************************************************/
/* 
 *
 */
/************************************************************************************************/
KsBool KsSwfImporter::readMatrix( KsSwfMatrix* pMatrix )
{
	return KsSwfImporter::readMatrix( m_pFile, pMatrix );
}

/************************************************************************************************/
/* 
 *
 */
/************************************************************************************************/
KsBool KsSwfImporter::readRect( KsFileObject* pFile, KsSwfRect* pRect )
{
	/* SwfRect 情報取得 */
	KsBitReader		bitReader;
	KsUInt8			uTemp[ 512 ];
	KsLong			uBit       = 0;
	KsInt32			uByteSize  = 0;

	uTemp[ 0 ] = pFile->readUInt8();
	
	bitReader.setup( uTemp, sizeof(uTemp) );

	uBit = bitReader.getNBitInt( 5, 0 );

	/* 何バイトRect情報があるかを取得 */
	uByteSize = ( 5 + uBit * 4 );

	uByteSize += 7;
	uByteSize /= 8;

	pFile->read( &uTemp[ 1 ], uByteSize-1 );
	
	const KsInt32 x_min = s_cast<KsInt32>( bitReader.getNBitInt( uBit, 1 ) );
	const KsInt32 x_max = s_cast<KsInt32>( bitReader.getNBitInt( uBit, 1 ) );
	const KsInt32 y_min = s_cast<KsInt32>( bitReader.getNBitInt( uBit, 1 ) );
	const KsInt32 y_max = s_cast<KsInt32>( bitReader.getNBitInt( uBit, 1 ) );

	pRect->setRect( x_min, x_max, y_min, y_max );

	return ksTRUE;
}

/************************************************************************************************/
/* 
 *
 */
/************************************************************************************************/
KsBool KsSwfImporter::readMatrix( KsFileObject* pFile, KsSwfMatrix* pMatrix )
{
	/* SwfRect 情報取得 */
	KsBitReader		bitReader;
	KsUInt8			uTemp[ 512 ];
	KsLong			uBit       = 0;
	KsInt32			uByteSize  = 0;
	KsInt32			uTotalBit  = 0;

	uTemp[ 0 ] = pFile->readUInt8();
	
	bitReader.setup( uTemp, sizeof(uTemp) );

	KsBool	hasScale = bitReader.getNBitInt( 1, 0 );
	
	uTotalBit += 1;

	if( hasScale )
	{
		uBit = bitReader.getNBitInt( 5, 0 );

		/* 何バイト情報があるかを取得 */
		uTotalBit += 5;
		uTotalBit += uBit * 2;
	
		uByteSize  = ( uTotalBit + 7 ) / 8;

		pFile->read( &uTemp[ 1 ], uByteSize-1 );
	}

	if( !(uTotalBit % 8) )
	{
		/* 割り切れているのでさらに1バイトよみこむ */
		uTotalBit /= 8;
		uTemp[ uByteSize ] = pFile->readUInt8();
	}

	KsBool	hasRotate = bitReader.getNBitInt( 1, 0 );

	uTotalBit += 1;

	if( hasRotate )
	{
		uBit = bitReader.getNBitInt( 5, 0 );

		/* 何バイト情報があるかを取得 */
		uTotalBit += 5;
		uTotalBit += uBit * 2;
	
		uByteSize  = ( uTotalBit + 7 ) / 8;
	}

#if 0
					/*
					char align;
		unsigned		f_has_scale : 1;
		if(f_has_scale) {
			unsigned	f_scale_bits : 5;
			signed fixed	f_scale_x : f_scale_bits;
			signed fixed	f_scale_y : f_scale_bits;
		}
		unsigned		f_has_rotate : 1;
		if(f_has_rotate) {
			unsigned	f_rotate_bits : 5;
			signed fixed	f_rotate_skew0 : f_rotate_bits;
			signed fixed	f_rotate_skew1 : f_rotate_bits;
		}
		unsigned		f_translate_bits : 5;
		signed			f_translate_x : f_rotate_bits;
		signed			f_translate_y : f_rotate_bits;
		*/

	/* 何バイトRect情報があるかを取得 */
	uByteSize = ( 5 + uBit * 4 );

	uByteSize += 7;
	uByteSize /= 8;

	pFile->read( &uTemp[ 1 ], uByteSize-1 );
	
	KsInt32 x_min = s_cast<KsInt32>( bitReader.getNBitInt( uBit, 1 ) );
	KsInt32 x_max = s_cast<KsInt32>( bitReader.getNBitInt( uBit, 1 ) );
	KsInt32 y_min = s_cast<KsInt32>( bitReader.getNBitInt( uBit, 1 ) );
	KsInt32 y_max = s_cast<KsInt32>( bitReader.getNBitInt( uBit, 1 ) );

	pRect->setRect( x_min, x_max, y_min, y_max );
#endif

	return ksTRUE;
}


/************************************************************************************************/
/* 
 *
 */
/************************************************************************************************/
KsBool	KsLoadSwf( const KsChar* pFileName )
{
	KsFileObject*		pFile = ksNew KsFileBuffer();
	KsBool				bFlag = pFile->open( pFileName, ksFILE_FLAG_DEFAULT );
	//KsFileBitReader*	pReader = ksNew KsFileBitReader( pFileName );

	KsSwfImporter	impoter( pFile );

	return ksTRUE;
}


#if 0

とします。 origsize に元のサイズが入ります。

実際には compress()，compress2()，uncompress() の戻り値を調べてエラーがないことを確認しなければなりません。戻り値は次のいずれかです。

    * Z_OK 成功
    * Z_MEM_ERROR メモリ不足で malloc() できなかった
    * Z_BUF_ERROR 出力バッファのサイズ不足 



void Decode( KsByte* pOutputBuffer, KsInt32 outputBufferSize, const KsByte* pInputBuffer, KsInt32 inputBufferSize )
{
	/* ライブラリとやりとりするための構造体 */
	KsInt32	status = Z_OK;
	z_stream	stream;

    /* すべてのメモリ管理をライブラリに任せる */
    stream.zalloc    = Z_NULL;
    stream.zfree     = Z_NULL;
    stream.opaque    = Z_NULL;
	stream.next_in   = Z_NULL;
    stream.avail_in  = 0;
	stream.next_out  = pOutputBuffer;		/* 出力ポインタ		*/
    stream.avail_out = outputBufferSize;	/* 出力バッファ残量	*/

	/* 初期化 */
    if( inflateInit( &stream ) != Z_OK )
	{
        /* エラー */
    }

	while( status != Z_STREAM_END )
	{
		if( stream.avail_in == 0 )
		{
			/* 入力残量がゼロになれば */
			stream.next_in  = pInputBuffer;  /* 入力ポインタを元に戻す */
			stream.avail_in = fread(inbuf, 1, INBUFSIZ, fin); /* データを読む */
		}

		/* 展開 */
		status = inflate( &stream, Z_NO_FLUSH );
		
		if( status == Z_STREAM_END )
		{
			/* 完了 */
			break;
		}

		if( status != Z_OK )
		{
			/* エラー */
		}

		if( stream.avail_out == 0 )
		{
			/* 出力バッファが尽きれば */
			/* まとめて書き出す */
			if( fwrite(outbuf, 1, OUTBUFSIZ, fout) != OUTBUFSIZ )
			{
			}
			
			/* 出力ポインタを元に戻す */
			stream.next_out = outbuf;

			/* 出力バッファ残量を元に戻す */
			stream.avail_out = OUTBUFSIZ;
		}
	}

    /* 残りを吐き出す */
    if( (count = OUTBUFSIZ - stream.avail_out) != 0 )
	{
        if (fwrite(outbuf, 1, count, fout) != count)
		{

        }
    }

    /* 後始末 */
    if( inflateEnd( &stream ) != Z_OK )
	{
    }
#endif



