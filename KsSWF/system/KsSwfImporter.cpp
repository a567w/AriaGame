/************************************************************************************************/
/** 
 * @file		KsSwfImporter.cpp
 * @brief		SWF�ǂݍ���
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsSWF/KsSWFPreCompile.h"
//#include <zlib.h>

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
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
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsSwfImporter::KsSwfImporter( KsFileObject* pFile )
	: m_pFile( pFile )
{
	KsSwfFileHeader		fileHeader;
	KsSwfRecordHeader	tag;
	KsSwfCommand*		pCommand = NULL;
	KsBool				bLoop = ksTRUE;

	/* �t�@�C���w�b�_�擾���� */
	readFileHeader( &fileHeader );

	/* �^�O����͂��� */
	while( bLoop )
	{
		pCommand = NULL;

		/* ���R�[�h�^�O���擾���� */
		readRecordHeader( &tag );

		/* �^�OID�ł̏����킯 */
		switch( tag.getID() )
		{
			case ksSWF_FILEATTRIBUTES:
			{
				/* �t�@�C���A�g���r���[�g */
				pCommand = ksNew KsSwfFileAttributes( m_pFile );
				break;
			}
			case ksSWF_METADATA:
			{
				/* ���^�f�[�^ */
				pCommand = ksNew KsSwfMetadata( m_pFile );
				break;
			}
			case ksSWF_END:
			{
				/* �I���^�O */
				pCommand = ksNew KsSwfEndCmd( m_pFile );
				bLoop = ksFALSE;
				break;
			}
			case ksSWF_SHOWFRAME:
			{
				/* �\���^�O */
				pCommand = ksNew ksSwfShowFrame( m_pFile );
				break;
			}
			case ksSWF_SETBACKGROUNDCOLOR:
			{
				/* �w�i�J���[���Z�b�g���� */
				pCommand = ksNew KsSwfSetBackGroundColorCmd( m_pFile );
				break;
			}
			case ksSWF_PLACEOBJECT:
			{
				/* �I�u�W�F�N�g�z�u */
				pCommand = ksNew KsSwfPlaceObject( m_pFile );
				break;
			}
			//case ksSWF_PLACEOBJECT2:
			//{
				//break;
			//}
			case ksSWF_REMOVEOBJECT:
			{
				/* �I�u�W�F�N�g�폜 */
				pCommand = ksNew KsSwfRemoveObject( m_pFile );
				break;
			}
			case ksSWF_REMOVEOBJECT2:
			{
				/* �I�u�W�F�N�g�폜 */
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
				/* �t���[���̖��O */
				pCommand = ksNew KsSwfFrameLabel( m_pFile );
				break;
			}
			case ksSWF_PROTECT:
			{
				/* �v���e�N�g(�t�@�C�����I�[�T�����O���ł̕ҏW�p�ɃC���|�[�g�ł��Ȃ����Ƃ������܂��B) */
				m_pFile->seek( tag.getSize(), SEEK_CUR );
				break;
			}
			case ksSWF_DEFINEBITS:
			{
				/* �摜�f�[�^ */
				pCommand = ksNew KsSwfDefineBits( m_pFile, &tag );
				break;
			}
			case ksSWF_DEFINEBITSJPEG2:
			{
				/* �摜�f�[�^ */
				pCommand = ksNew KsSwfDefineBitsJPEG2( m_pFile, &tag );
				break;
			}
			case ksSWF_DEFINEBITSJPEG3:
			{
				/* �摜�f�[�^ */
				pCommand = ksNew KsSwfDefineBitsJPEG3( m_pFile, &tag );
				break;
			}
			case ksSWF_DEFINESCENEANDFRAMELABELDATA:
			{
				/* �V�[�� */
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
	/* ���ʃf�[�^ */
	m_pFile->read( pFileHeader->m_signature, 3 );

	/* �o�[�W���� */
	pFileHeader->m_version = m_pFile->readUInt8();

	/* �t�@�C���T�C�Y�i���k����Ă���ꍇ�͓W�J��̃T�C�Y�j*/
	pFileHeader->m_fileSize = m_pFile->readUInt32();

	/* �t�@�C���t�H�[�}�b�g�`�F�b�N */
	if( ks_strncmp( r_cast<const KsChar*>( pFileHeader->m_signature ), "FWS", 3 ) == 0 )
	{
		/* �ʏ� */
	}
	else if( ks_strncmp( r_cast<const KsChar*>( pFileHeader->m_signature ), "CWS", 3 ) == 0 )
	{
		/* ���k���� */
#if 0
		KsULong		uDecodeBufferSize = 0;
		KsULong		uSourceBufferSize = 0;
		KsByte*		pDecodeBuffer     = NULL;
		KsByte*		pSourceBuffer     = NULL;

		uDecodeBufferSize = s_cast<KsULong>( pFileHeader->m_fileSize );
		uSourceBufferSize = s_cast<KsULong>( pFileHeader->getFileSize() - 8 );

		pDecodeBuffer = ksNew KsByte[ uDecodeBufferSize ];
		pSourceBuffer = ksNew KsByte[ uSourceBufferSize ];

		/* �o�b�t�@�ɓǂݍ��� */
		m_pFile->read( pSourceBuffer, uSourceBufferSize );

		/* �t�@�C������� */
		ksDELETE( m_pFile );

		/* �W�J���� */
		KsInt32	ret = uncompress( pDecodeBuffer, &uDecodeBufferSize, pSourceBuffer, uSourceBufferSize );
		
		if( ret != Z_OK )
		{
			return ksFALSE;
		}

		/* �t�@�C�����Z�b�g���Ȃ��� */
		m_pFile = new KsFileBuffer( pDecodeBuffer, uDecodeBufferSize );
#endif
	}
	else
	{
		/* �G���[ */
		return ksFALSE;
	}

	/* �t���[���T�C�Y */
	readRect( &pFileHeader->m_frameSize );

	/* �t���[�����[�g */
	KsInt16	frameRate = m_pFile->readInt16();
	pFileHeader->m_frameRate.setFromRaw( frameRate );

	/* �t���[���� */
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
	/* SwfRect ���擾 */
	KsBitReader		bitReader;
	KsUInt8			uTemp[ 512 ];
	KsLong			uBit       = 0;
	KsInt32			uByteSize  = 0;

	uTemp[ 0 ] = pFile->readUInt8();
	
	bitReader.setup( uTemp, sizeof(uTemp) );

	uBit = bitReader.getNBitInt( 5, 0 );

	/* ���o�C�gRect��񂪂��邩���擾 */
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
	/* SwfRect ���擾 */
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

		/* ���o�C�g��񂪂��邩���擾 */
		uTotalBit += 5;
		uTotalBit += uBit * 2;
	
		uByteSize  = ( uTotalBit + 7 ) / 8;

		pFile->read( &uTemp[ 1 ], uByteSize-1 );
	}

	if( !(uTotalBit % 8) )
	{
		/* ����؂�Ă���̂ł����1�o�C�g��݂��� */
		uTotalBit /= 8;
		uTemp[ uByteSize ] = pFile->readUInt8();
	}

	KsBool	hasRotate = bitReader.getNBitInt( 1, 0 );

	uTotalBit += 1;

	if( hasRotate )
	{
		uBit = bitReader.getNBitInt( 5, 0 );

		/* ���o�C�g��񂪂��邩���擾 */
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

	/* ���o�C�gRect��񂪂��邩���擾 */
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

�Ƃ��܂��B origsize �Ɍ��̃T�C�Y������܂��B

���ۂɂ� compress()�Ccompress2()�Cuncompress() �̖߂�l�𒲂ׂăG���[���Ȃ����Ƃ��m�F���Ȃ���΂Ȃ�܂���B�߂�l�͎��̂����ꂩ�ł��B

    * Z_OK ����
    * Z_MEM_ERROR �������s���� malloc() �ł��Ȃ�����
    * Z_BUF_ERROR �o�̓o�b�t�@�̃T�C�Y�s�� 



void Decode( KsByte* pOutputBuffer, KsInt32 outputBufferSize, const KsByte* pInputBuffer, KsInt32 inputBufferSize )
{
	/* ���C�u�����Ƃ��Ƃ肷�邽�߂̍\���� */
	KsInt32	status = Z_OK;
	z_stream	stream;

    /* ���ׂẴ������Ǘ������C�u�����ɔC���� */
    stream.zalloc    = Z_NULL;
    stream.zfree     = Z_NULL;
    stream.opaque    = Z_NULL;
	stream.next_in   = Z_NULL;
    stream.avail_in  = 0;
	stream.next_out  = pOutputBuffer;		/* �o�̓|�C���^		*/
    stream.avail_out = outputBufferSize;	/* �o�̓o�b�t�@�c��	*/

	/* ������ */
    if( inflateInit( &stream ) != Z_OK )
	{
        /* �G���[ */
    }

	while( status != Z_STREAM_END )
	{
		if( stream.avail_in == 0 )
		{
			/* ���͎c�ʂ��[���ɂȂ�� */
			stream.next_in  = pInputBuffer;  /* ���̓|�C���^�����ɖ߂� */
			stream.avail_in = fread(inbuf, 1, INBUFSIZ, fin); /* �f�[�^��ǂ� */
		}

		/* �W�J */
		status = inflate( &stream, Z_NO_FLUSH );
		
		if( status == Z_STREAM_END )
		{
			/* ���� */
			break;
		}

		if( status != Z_OK )
		{
			/* �G���[ */
		}

		if( stream.avail_out == 0 )
		{
			/* �o�̓o�b�t�@���s����� */
			/* �܂Ƃ߂ď����o�� */
			if( fwrite(outbuf, 1, OUTBUFSIZ, fout) != OUTBUFSIZ )
			{
			}
			
			/* �o�̓|�C���^�����ɖ߂� */
			stream.next_out = outbuf;

			/* �o�̓o�b�t�@�c�ʂ����ɖ߂� */
			stream.avail_out = OUTBUFSIZ;
		}
	}

    /* �c���f���o�� */
    if( (count = OUTBUFSIZ - stream.avail_out) != 0 )
	{
        if (fwrite(outbuf, 1, count, fout) != count)
		{

        }
    }

    /* ��n�� */
    if( inflateEnd( &stream ) != Z_OK )
	{
    }
#endif



