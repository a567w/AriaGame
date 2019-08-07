/************************************************************************************************/
/** 
 * @file	KsFileBufferBuffer.cpp
 * @brief	�t�@�C������N���X
 * @author	tsukasa kato
 * @date	2003/11/30
 * @version	1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * �R���X�g���N�^
 * @param	path			�t�@�C���̃p�X
 * @param	fileName		�t�@�C����
 * @param	flags			�t�@�C���̃I�[�v���t���O
 * @param	bOpen			�I�[�v�����邩�ǂ����̃t���O
 *							(ksTRUE:���ƃI�[�v������, ksFALSE:���ƃp�X�ƃt�@�C�������Z�b�g���邾��)
 */
/************************************************************************************************/
KsFileBuffer::KsFileBuffer( const KsString& path, const KsString& fileName, KsInt32 flags, KsBool bOpen )
{
	m_name        = fileName;
	m_path        = path;
	m_pBuffer     = 0;
	m_byteOrder   = ksLITTLEENDIAN;
	m_state       = ksINVALID;
	m_flags       = flags;
	m_size        = 0;
	m_pos         = 0;
	
	if( bOpen )
	{
		open();
	}
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 * @param	fullPath		�t�@�C���̃t���p�X
 * @param	flags			�t�@�C���̃I�[�v���t���O
 */
/************************************************************************************************/
KsFileBuffer::KsFileBuffer( const KsString& fullPath, KsInt32 flags )
{
	m_pBuffer     = 0;
	m_byteOrder   = ksLITTLEENDIAN;
	m_state       = ksINVALID;
	m_flags       = flags;
	m_size        = 0;
	m_pos         = 0;
	
	open( fullPath, flags );
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 * @param	pBuffer			�f�[�^�̎��̂̃o�b�t�@
 * @param	size			�f�[�^�T�C�Y
 * @param	bAlloc			�����ŐV���Ɋm�ۂ��邩�ǂ����̃t���O
 */
/************************************************************************************************/
KsFileBuffer::KsFileBuffer( KsByte* pBuffer, KsInt32 size, KsInt32 flags, KsBool bAlloc )
{
	if( bAlloc )
	{
		m_pBuffer = new KsByte[ size ];
		//KsAssert( );
	}
	else{
		m_pBuffer = pBuffer;
	}
	
	m_byteOrder   = ksLITTLEENDIAN;
	m_state       = ksOPEN;
	m_flags       = flags;
	m_size        = size;
	m_pos         = 0;
	m_bAlloc      = bAlloc;
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsFileBuffer::~KsFileBuffer()
{
	close();
}

/************************************************************************************************/
/*
 * �t���O����t�@�C�����[�h���擾����
 * @param	flags			�t�@�C�����J�����[�h�t���O
 * @return					�t�@�C�����J��������̃��[�h
 */
/************************************************************************************************/
KsString KsFileBuffer::getFileMode( KsUInt32 flags )
{
	KsString	mode;

	if( (flags & ksAPPEND) && (flags & ksWRITE) ) { flags ^= ksWRITE; }

	     if( (flags & ksREAD) && (flags & ksAPPEND) ) { mode = _T("a+"); }
	else if( (flags & ksREAD) && (flags & ksWRITE ) ) { mode = _T("w+"); }
	else if(  flags & ksAPPEND ) { mode = _T("a"); }
	else if(  flags & ksREAD   ) { mode = _T("r"); }
	else if(  flags & ksWRITE  ) { mode = _T("w"); }
	else                         { return  _T(""); }

	if( flags & ksBINARY ) { mode += _T("b"); }
	if( flags & ksCOMMIT ) { mode += _T("c"); }

	return	mode;
}

/************************************************************************************************/
/*
 * �t�@�C�����J��
 * @param	fullPath		�t�@�C���̃t���p�X
 * @param	flags			�t�@�C���̃I�[�v���t���O
 * @retval	ksTRUE			����
 * @retval	ksFALSE			���s
 */
/************************************************************************************************/
KsBool KsFileBuffer::open( const KsString& fullPath, KsInt32 flags, ksBYTE_ORDER byteOrder )
{
	KsChar		drive[ _MAX_DRIVE ];
	KsChar		dir[ _MAX_DIR ];
	KsChar		fname[ _MAX_FNAME ];
	KsChar		ext[ _MAX_EXT ];
	FILE*		fp = NULL;

	ks_splitpath( fullPath.c_str(), drive, dir, fname, ext );

	KsString		path( drive );
	KsString		name( fname );

	path += dir;	// �p�X
	name += ext;	// �t�@�C����

	close();

	if( name.length() ){
		m_name = name;
	}
	
	if( path.length() ){
		m_path = path;
	}

	if( flags != ksNONE ){
		m_flags = flags;
	}

	KsString mode = getFileMode( m_flags );
	
	if( m_path.length() )
	{
		KsString fullPath = m_path;
		
		if( fullPath[ fullPath.length() - 1 ] != '/' && fullPath[ fullPath.length() - 1 ] != '\\' ){
			fullPath += '\\';
		}
	
		fullPath += m_name;
	
		if( !( fp = ks_fopen( fullPath.c_str(), mode.c_str() ) ) )
		{
			return ksFALSE;
		}
	}
	else if( !( fp = ks_fopen( m_name.c_str(), mode.c_str() ) ) )
	{
		return ksFALSE;
	}
	
	m_state     = ksOPEN;
	m_byteOrder = byteOrder;
	
	fseek( fp, 0, SEEK_END );

	m_size = ftell( fp );

	fseek( fp, 0, SEEK_SET );

	m_pBuffer = new KsByte[ m_size ];

	if( m_pBuffer == NULL ){
		fclose( fp );
		return ksFALSE;
	}

	m_bAlloc = ksTRUE;

	fread( m_pBuffer, 1, m_size, fp );

	fclose( fp );

	return ksTRUE;
}

/************************************************************************************************/
/*
 * �t�@�C�����J��
 * @param	path			�t�@�C���̃p�X
 * @param	fileName		�t�@�C����
 * @param	flags			�t�@�C���̃I�[�v���t���O
 * @retval	ksTRUE			����
 * @retval	ksFALSE			���s
 */
/************************************************************************************************/
KsBool KsFileBuffer::open( const KsString& path, const KsString& fileName, KsInt32 flags )
{
	FILE*		fp = NULL;

	close();

	if( fileName.length() )
	{
		m_name = fileName;
	}
	
	if( path.length() )
	{
		m_path = path;
	}

	if( flags != ksNONE ){
		m_flags = flags;
	}

	KsString mode = getFileMode( m_flags );
	
	if( m_path.length() )
	{
		KsString fullPath = m_path;
		
		if( fullPath[ fullPath.length() - 1 ] != '/' && fullPath[ fullPath.length() - 1 ] != '\\' )
		{
			fullPath += '\\';
		}
	
		fullPath += m_name;
	
		if( !( fp = ks_fopen( fullPath.c_str(), mode.c_str() ) ) )
		{
			return ksFALSE;
		}
	}
	else if( !( fp = ks_fopen( m_name.c_str(), mode.c_str() ) ) )
	{
		return ksFALSE;
	}
	
	m_state     = ksOPEN;
	
	fseek( fp, 0, SEEK_END );

	m_size = ftell( fp );

	fseek( fp, 0, SEEK_SET );

	m_pBuffer = new KsByte[ m_size ];

	if( m_pBuffer == NULL ){
		fclose( fp );
		return ksFALSE;
	}

	m_bAlloc = ksTRUE;

	fread( m_pBuffer, 1, m_size, fp );

	fclose( fp );

	return ksTRUE;
}

/************************************************************************************************/
/*
 * �t�@�C�������
 */
/************************************************************************************************/
void KsFileBuffer::close()
{
	if( m_bAlloc )
	{
		ksDELETEARRAY( m_pBuffer );	
	}
	else
	{
		m_pBuffer = NULL;
	}

	m_state = ksCLOSED;
}

/************************************************************************************************/
/*
 * �w�肳�ꂽ�ʒu�Ƀt�@�C�� �|�C���^���ړ�����
 * @param	offset			�w��ʒu����̃o�C�g��
 * @param	mode			�w��ʒu
 * @return					����ɏ������ꂽ�ꍇ�A0 ��Ԃ��܂��B����ȊO�̏ꍇ�� 0 �ȊO�̒l��Ԃ��܂�
 */
/************************************************************************************************/
KsInt32 KsFileBuffer::seek( KsInt32 offset, KsInt32 mode )
{
	if( !isValid() ){
		return 0;
	}

	KsInt32 pos = tell();

	if( ( m_size <= 0 ) ||
	    ( ( mode == SEEK_SET ) && ( offset != pos ) ) ||
	    ( ( mode == SEEK_CUR ) && ( offset ) )        ||
		( ( mode == SEEK_END ) && ( m_size - offset != pos ) ) )
	{
		switch( mode )
		{
			case SEEK_SET:
			{
				m_pos = offset;
				break;
			}
			case SEEK_CUR:
			{
				m_pos += offset;
				break;
			}
			case SEEK_END:
			{
				m_pos = m_size;
				break;
			}
			default:
			{
				return 0;
			}
		}
	}
	
	return ( tell() - m_pos );
}

/************************************************************************************************/
/*
 * �t�@�C�����畂�������_�̒l��ǂݍ���
 * @return					���������_�̒l
 */
/************************************************************************************************/
KsReal KsFileBuffer::readReal()
{
	KS_DATA4	val;
	KS_DATA4	data;

	// �L�����ǂ����̃`�F�b�N
	if( !isValid() )
	{
		return 0;
	}

	// �ǂݍ���
	KsSize		size = sizeof(KS_DATA4);
	KsMemCopy( &val, &m_pBuffer[ m_pos ], size );
	m_pos += static_cast< KsInt32 >(size);

	// �G���f�B�A�����̃`�F�b�N
	if( ksLITTLEENDIAN == m_byteOrder )
	{
		// ���g���G���f�B�A��
		return	( val.f );
	}
	
	// �r�b�N�G���f�B�A��
	data.byte[ 0 ] = val.byte[ 3 ];
	data.byte[ 1 ] = val.byte[ 2 ];
	data.byte[ 2 ] = val.byte[ 1 ];
	data.byte[ 3 ] = val.byte[ 0 ];

	return ( data.f );
}

/************************************************************************************************/
/*
 * �t�@�C������32bit�����l��ǂݍ���
 * @return					32bit�����l
 */
/************************************************************************************************/
KsInt32 KsFileBuffer::readInt32()
{
	KS_DATA4	val;
	KS_DATA4	data;

	// �L�����ǂ����̃`�F�b�N
	if( !isValid() )
	{
		return 0;
	}

	KsSize		size = sizeof(KS_DATA4);
	KsMemCopy( &val, &m_pBuffer[ m_pos ], size );
	m_pos += static_cast< KsInt32 >(size);

	// �G���f�B�A�����̃`�F�b�N
	if( ksLITTLEENDIAN == m_byteOrder )
	{
		// ���g���G���f�B�A��
		return	( val.i32 );
	}
	
	// �r�b�N�G���f�B�A��
	data.byte[ 0 ] = val.byte[ 3 ];
	data.byte[ 1 ] = val.byte[ 2 ];
	data.byte[ 2 ] = val.byte[ 1 ];
	data.byte[ 3 ] = val.byte[ 0 ];

	return ( data.i32 );
}

/************************************************************************************************/
/*
 * �t�@�C�����畄���Ȃ�32bit�����l��ǂݍ���
 * @return					�����Ȃ�32bit�����l
 */
/************************************************************************************************/
KsUInt32 KsFileBuffer::readUInt32()
{
	KS_DATA4	val;
	KS_DATA4	data;

	// �L�����ǂ����̃`�F�b�N
	if( !isValid() )
	{
		return 0;
	}

	KsSize		size = sizeof(KS_DATA4);
	KsMemCopy( &val, &m_pBuffer[ m_pos ], size );
	m_pos += static_cast< KsInt32 >(size);

	// �G���f�B�A�����̃`�F�b�N
	if( ksLITTLEENDIAN == m_byteOrder )
	{
		// ���g���G���f�B�A��
		return	( val.u32 );
	}
	
	// �r�b�N�G���f�B�A��
	data.byte[ 0 ] = val.byte[ 3 ];
	data.byte[ 1 ] = val.byte[ 2 ];
	data.byte[ 2 ] = val.byte[ 1 ];
	data.byte[ 3 ] = val.byte[ 0 ];

	return ( data.u32 );
}

/************************************************************************************************/
/*
 * �t�@�C������16bit�����l��ǂݍ���
 * @return					16bit�����l
 */
/************************************************************************************************/
KsInt16 KsFileBuffer::readInt16()
{
	KS_DATA2	val;
	KS_DATA2	data;

	// �L�����ǂ����̃`�F�b�N
	if( !isValid() ){
		return 0;
	}

	KsSize		size = sizeof(KS_DATA2);
	KsMemCopy( &val, &m_pBuffer[ m_pos ], size );
	m_pos += static_cast< KsInt32 >(size);

	// �G���f�B�A�����̃`�F�b�N
	if( ksLITTLEENDIAN == m_byteOrder )
	{
		// ���g���G���f�B�A��
		return	( val.s16 );
	}
	
	// �r�b�N�G���f�B�A��
	data.byte[ 0 ] = val.byte[ 1 ];
	data.byte[ 1 ] = val.byte[ 0 ];

	return ( data.s16 );
}

/************************************************************************************************/
/*
 * �t�@�C�����畄���Ȃ�16bit�����l��ǂݍ���
 * @return					�����Ȃ�16bit�����l
 */
/************************************************************************************************/
KsUInt16 KsFileBuffer::readUInt16()
{
	KS_DATA2	val;
	KS_DATA2	data;

	// �L�����ǂ����̃`�F�b�N
	if( !isValid() )
	{
		return 0;
	}

	KsSize		size = sizeof(KS_DATA2);
	KsMemCopy( &val, &m_pBuffer[ m_pos ], size );
	m_pos += static_cast< KsInt32 >(size);

	// �G���f�B�A�����̃`�F�b�N
	if( ksLITTLEENDIAN == m_byteOrder )
	{
		// ���g���G���f�B�A��
		return	( val.u16 );
	}
	
	// �r�b�N�G���f�B�A��
	data.byte[ 0 ] = val.byte[ 1 ];
	data.byte[ 1 ] = val.byte[ 0 ];

	return ( data.u16 );
}

/************************************************************************************************/
/*
 * �t�@�C������8bit�����l��ǂݍ���
 * @return					8bit�����l
 */
/************************************************************************************************/
KsChar KsFileBuffer::readChar()
{
	KsChar	val;

	// �L�����ǂ����̃`�F�b�N
	if( !isValid() )
	{
		return 0;
	}

	// �ǂݍ���
	KsMemCopy( &val, &m_pBuffer[ m_pos ], 1 );
	++m_pos;

	return val;
}

/************************************************************************************************/
/*
 * �t�@�C�����畄���Ȃ�8bit�����l��ǂݍ���
 * @return					�����Ȃ�8bit�����l
 */
/************************************************************************************************/
KsInt8 KsFileBuffer::readInt8()
{
	KsInt8 val;

	// �L�����ǂ����̃`�F�b�N
	if( !isValid() )
	{
		return 0;
	}

	// �ǂݍ���
	KsMemCopy( &val, &m_pBuffer[ m_pos ], 1 );
	++m_pos;

	return val;
}

/************************************************************************************************/
/*
 * �t�@�C������ꕶ����ǂݍ���
 * @return					�ꕶ�����̒l
 */
/************************************************************************************************/
KsUInt8 KsFileBuffer::readUInt8()
{
	KsUInt8 val;

	// �L�����ǂ����̃`�F�b�N
	if( !isValid() ){
		return 0;
	}

	// �ǂݍ���
	KsMemCopy( &val, &m_pBuffer[ m_pos ], 1 );
	++m_pos;

	return val;
}

/************************************************************************************************/
/*
 * �t�@�C�����畄���Ȃ�8bit�����l��ǂݍ���
 * @return					�����l
 */
/************************************************************************************************/
KsInt32 KsFileBuffer::readByte()
{
	KsInt32 val;

	// �L�����ǂ����̃`�F�b�N
	if( !isValid() )
	{
		return 0;
	}

	// �ǂݍ���
	KsMemCopy( &val, &m_pBuffer[ m_pos ], 1 );
	++m_pos;

	return val;
}

/************************************************************************************************/
/*
 * �t�@�C�����當�����ǂݍ���
 * @return					������
 */
/************************************************************************************************/
KsString KsFileBuffer::readString()
{
	KsString		str;
	KsChar			buf[ 4*1024 ];
	KsInt32			count = 0;

	// �L�����ǂ����̃`�F�b�N
	if( !isValid() )
	{
		return str;
	}

	// �ǂݍ���
	for( KsInt32 i=0; m_pBuffer[ m_pos+i ] != '\0'; i++ )
	{
		++count;
		if( m_size < (count + m_pos) )
		{
			break;
		}
	}
	++count;

	KsMemCopy( buf, &m_pBuffer[ m_pos ], count );
	buf[ count ] = '\0';
	m_pos += count;

	str = buf;
	
	return str;
}

/************************************************************************************************/
/*
 * �G���R�[�h���ꂽ��������ǂݍ���
 * @return					�ϒ��T�C�Y�̃G���R�[�h���ꂽ 32-bit ������������
 */
/************************************************************************************************/
KsUInt32 KsFileBuffer::readEncodedU32()
{
	KsUInt32 val = (KsUInt32)m_pBuffer[ m_pos++ ];

	if( !(val & 0x00000080) )
	{
		return val;
	}

	val = (val & 0x0000007f) | (KsUInt32)m_pBuffer[ m_pos++ ] << 7;

	if( !(val & 0x00004000) )
	{
		return val;
	}

	val = (val & 0x00003fff) | (KsUInt32)m_pBuffer[ m_pos++ ] << 14;

	if( !(val & 0x00200000) )
	{
		return val;
	}

	val = (val & 0x001fffff) | (KsUInt32)m_pBuffer[ m_pos++ ] << 21;

	if( !(val & 0x10000000) )
	{
		return val;
	}

	val = (val & 0x0fffffff) | (KsUInt32)m_pBuffer[ m_pos++ ] << 28;

	return val;
}

/************************************************************************************************/
/*
 * �o�b�t�@�Ɏw��o�C�g�����ǂݍ���
 * @param	pBuffer			(OUT)�ǂݍ��ނ��߂̃o�b�t�@
 * @param	count			�ǂݍ��ރo�C�g��
 * @return					�ǂݍ��񂾃o�C�g��
 */
/************************************************************************************************/
KsSize KsFileBuffer::read( void* pBuffer, KsInt32 count )
{
	KsSize	readSize = 0;

	if( pBuffer )
	{
		if( m_pos + count > m_size )
		{
			readSize = m_size - m_pos;
		}
		else
		{
			readSize = count;
		}

		KsMemCopy( pBuffer, &m_pBuffer[ m_pos ], readSize );
		m_pos += count;
	}

	return readSize;
}

/************************************************************************************************/
/*
 * �t�@�C���ɒl����������
 * @param	val				�������ޒl
 * @return					�������񂾃o�C�g��
 */
/************************************************************************************************/
KsSize KsFileBuffer::writeInt16( KsInt16 val )
{
	// �L�����ǂ����̃`�F�b�N
	if( !isValid() ){
		return 0;
	}

	KsSize	size = sizeof( KsUInt16 );

	// �G���f�B�A�����̃`�F�b�N
	if( ksLITTLEENDIAN == m_byteOrder )
	{
		// ���g���G���f�B�A��
		KsMemCopy( &m_pBuffer[ m_pos ], &val, size );
		m_pos += static_cast< KsInt32 >(size);
	}
	else
	{
		KS_DATA2	temp;
		KS_DATA2	data;

		temp.s16 = val;

		// �r�b�N�G���f�B�A��
		data.byte[ 0 ] = temp.byte[ 1 ];
		data.byte[ 1 ] = temp.byte[ 0 ];

		KsMemCopy( &m_pBuffer[ m_pos ], &data.s16, size );
		m_pos += static_cast< KsInt32 >(size);
	}

	return size;
}

/************************************************************************************************/
/*
 * �t�@�C���ɒl����������
 * @param	val				�������ޒl
 * @return					�������񂾃o�C�g��
 */
/************************************************************************************************/
KsSize KsFileBuffer::writeUInt16( KsUInt16 val )
{
	// �L�����ǂ����̃`�F�b�N
	if( !isValid() ){
		return 0;
	}

	KsSize	size = sizeof( KsUInt16 );

	// �G���f�B�A�����̃`�F�b�N
	if( ksLITTLEENDIAN == m_byteOrder )
	{
		// ���g���G���f�B�A��
		KsMemCopy( &m_pBuffer[ m_pos ], &val, size );
		m_pos += static_cast< KsInt32 >(size);
	}
	else
	{
		KS_DATA2	temp;
		KS_DATA2	data;

		temp.u16 = val;

		// �r�b�N�G���f�B�A��
		data.byte[ 0 ] = temp.byte[ 1 ];
		data.byte[ 1 ] = temp.byte[ 0 ];

		KsMemCopy( &m_pBuffer[ m_pos ], &data.u16, size );
		m_pos += static_cast< KsInt32 >(size);
	}

	return size;
}

/************************************************************************************************/
/*
 * �t�@�C���ɒl����������
 * @param	val				�������ޒl
 * @return					�������񂾃o�C�g��
 */
/************************************************************************************************/
KsSize KsFileBuffer::writeInt32( KsInt32 val )
{
	// �L�����ǂ����̃`�F�b�N
	if( !isValid() ){
		return 0;
	}

	KsSize	size = sizeof( KsInt32 );

	// �G���f�B�A�����̃`�F�b�N
	if( ksLITTLEENDIAN == m_byteOrder )
	{
		// ���g���G���f�B�A��
		KsMemCopy( &m_pBuffer[ m_pos ], &val, size );
		m_pos += static_cast< KsInt32 >(size);
	}
	else
	{
		KS_DATA4	temp;
		KS_DATA4	data;

		temp.i32 = val;

		// �r�b�N�G���f�B�A��
		data.byte[ 0 ] = temp.byte[ 3 ];
		data.byte[ 1 ] = temp.byte[ 2 ];
		data.byte[ 2 ] = temp.byte[ 1 ];
		data.byte[ 3 ] = temp.byte[ 0 ];

		KsMemCopy( &m_pBuffer[ m_pos ], &data.i32, size );
		m_pos += static_cast< KsInt32 >(size);
	}

	return size;
}

/************************************************************************************************/
/*
 * �t�@�C���ɒl����������
 * @param	val				�������ޒl
 * @return					�������񂾃o�C�g��
 */
/************************************************************************************************/
KsSize KsFileBuffer::writeUInt32( KsUInt32 val )
{
	// �L�����ǂ����̃`�F�b�N
	if( !isValid() ){
		return 0;
	}

	KsSize	size = sizeof( KsUInt32 );

	// �G���f�B�A�����̃`�F�b�N
	if( ksLITTLEENDIAN == m_byteOrder )
	{
		// ���g���G���f�B�A��
		KsMemCopy( &m_pBuffer[ m_pos ], &val, size );
		m_pos += static_cast< KsInt32 >(size);
	}
	else
	{
		KS_DATA4	temp;
		KS_DATA4	data;

		temp.u32 = val;

		// �r�b�N�G���f�B�A��
		data.byte[ 0 ] = temp.byte[ 3 ];
		data.byte[ 1 ] = temp.byte[ 2 ];
		data.byte[ 2 ] = temp.byte[ 1 ];
		data.byte[ 3 ] = temp.byte[ 0 ];

		KsMemCopy( &m_pBuffer[ m_pos ], &data.u32, size );
		m_pos += static_cast< KsInt32 >(size);
	}

	return size;
}

/************************************************************************************************/
/*
 * �t�@�C���ɒl����������
 * @param	val				�������ޒl
 * @return					�������񂾃o�C�g��
 */
/************************************************************************************************/
KsSize KsFileBuffer::writeReal( KsReal val )
{
	// �L�����ǂ����̃`�F�b�N
	if( !isValid() ){
		return 0;
	}

	KsSize	size = sizeof( KsReal );

	// �G���f�B�A�����̃`�F�b�N
	if( ksLITTLEENDIAN == m_byteOrder )
	{
		// ���g���G���f�B�A��
		KsMemCopy( &m_pBuffer[ m_pos ], &val, size );
		m_pos += static_cast< KsInt32 >(size);
	}
	else
	{
		KS_DATA4	temp;
		KS_DATA4	data;

		temp.f = val;

		// �r�b�N�G���f�B�A��
		data.byte[ 0 ] = temp.byte[ 3 ];
		data.byte[ 1 ] = temp.byte[ 2 ];
		data.byte[ 2 ] = temp.byte[ 1 ];
		data.byte[ 3 ] = temp.byte[ 0 ];

		KsMemCopy( &m_pBuffer[ m_pos ], &data.f, size );
		m_pos += static_cast< KsInt32 >(size);
	}

	return size;
}

/************************************************************************************************/
/*
 * �t�@�C���ɒl����������
 * @param	val				�������ޒl
 * @return					�������񂾃o�C�g��
 */
/************************************************************************************************/
KsSize KsFileBuffer::writeInt8( KsInt8 val )
{
	// �L�����ǂ����̃`�F�b�N
	if( !isValid() ){
		return 0;
	}

	KsSize size = sizeof(KsInt8);

	KsMemCopy( m_pBuffer, &val, size );

	return size;
}

/************************************************************************************************/
/*
 * �t�@�C���ɒl����������
 * @param	val				�������ޒl
 * @return					�������񂾃o�C�g��
 */
/************************************************************************************************/
KsSize KsFileBuffer::writeUInt8( KsUInt8 val )
{
	// �L�����ǂ����̃`�F�b�N
	if( !isValid() ){
		return 0;
	}

	KsSize size = sizeof(KsUInt8);

	KsMemCopy( &m_pBuffer[ m_pos ], &val, size );
	m_pos += static_cast< KsInt32 >(size);

	return size;
}

/************************************************************************************************/
/*
 * �t�@�C���ɒl����������
 * @param	val				�������ޒl
 * @return					�������񂾃o�C�g��
 */
/************************************************************************************************/
KsSize KsFileBuffer::writeChar( KsChar val )
{
	// �L�����ǂ����̃`�F�b�N
	if( !isValid() )
	{
		return 0;
	}

	KsSize size = sizeof(KsChar);

	KsMemCopy( &m_pBuffer[ m_pos ], &val, size );
	m_pos += static_cast< KsInt32 >(size);

	return size;
}

/************************************************************************************************/
/*
 * �t�@�C���ɒl����������
 * @param	val				�������ޒl
 * @return					�������񂾃o�C�g��
 */
/************************************************************************************************/
KsSize KsFileBuffer::writeByte( KsInt32 val )
{
	// �L�����ǂ����̃`�F�b�N
	if( !isValid() )
	{
		return 0;
	}

	KsSize size = sizeof(KsByte);

	KsMemCopy( &m_pBuffer[ m_pos ], &val, size );
	m_pos += static_cast< KsInt32 >(size);

	return size;
}

/************************************************************************************************/
/*
 * �o�b�t�@����t�@�C���ɒl����������
 * @param	pBuffer			�������ރo�b�t�@
 * @param	count			�������ރo�C�g��
 * @return					�������񂾃o�C�g��
 */
/************************************************************************************************/
KsSize KsFileBuffer::write( const void *pBuffer, KsInt32 count )
{
	if( !isValid() || ( count <= 0 ) )
	{
		return 0;
	}

	KsSize size = 0;
	
	if( pBuffer )
	{
		if( m_size < ( m_pos + count )  )
		{
			size = m_size - m_pos;
		}
		else
		{
			size = count;
		}

		KsMemCopy( &m_pBuffer[ m_pos ], pBuffer, size );

		m_pos += count;
	}
	else
	{
		KsUInt32	pos = tell();
		seek( count, SEEK_CUR );
		size = tell() - pos;
	}

	return size;
}



