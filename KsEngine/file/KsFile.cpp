/*************************************************************************************************/
/**
 * @file	KsFile.cpp
 * @brief	�t�@�C������N���X
 * @author	tsukasa kato
 * @date	2003/11/30
 * @version	1.0.0
 */
/*************************************************************************************************/

/*===============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*===============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"

/*===============================================================================================*/
/*                                     << ��` >>                                                */
/*===============================================================================================*/

/*===============================================================================================*/
/*                                     << �錾 >>                                                */
/*===============================================================================================*/

//===============================================================================================//
// �R���X�g���N�^
//===============================================================================================//
KsFile::KsFile( const KsString& path, const KsString& fileName, KsInt32 flags, KsBool bOpen )//, KsDirectory *pDirectory )
{
	m_name        = fileName;
	m_path        = path;
	m_pFile       = 0;
	m_byteOrder   = ksLITTLEENDIAN;
	m_state       = ksINVALID;
	m_flags       = flags;
	m_size        = 0;
	
	if( bOpen ){
		open();
	}
}

//===============================================================================================//
// �R���X�g���N�^
//===============================================================================================//
KsFile::KsFile( const KsString& fullPath, KsInt32 flags )
{
	m_pFile       = 0;
	m_byteOrder   = ksLITTLEENDIAN;
	m_state       = ksINVALID;
	m_flags       = flags;
	m_size        = 0;
	
	open( fullPath, flags );
}

//===============================================================================================//
// �f�X�g���N�^
//===============================================================================================//
KsFile::~KsFile()
{
	close();
}

//===============================================================================================//
// �t���O����t�@�C�����[�h�ɕϊ�����
//===============================================================================================//
KsString KsFile::getFileMode( KsUInt32 flags )
{
	KsString	mode;

	if( (flags & ksAPPEND) && (flags & ksWRITE) ) { flags ^= ksWRITE; }

	     if( (flags & ksREAD) && (flags & ksAPPEND) ) { mode = _T("a+"); }
	else if( (flags & ksREAD) && (flags & ksWRITE ) ) { mode = _T("w+"); }
	else if(  flags & ksAPPEND ) { mode = _T("a"); }
	else if(  flags & ksREAD   ) { mode = _T("r"); }
	else if(  flags & ksWRITE  ) { mode = _T("w"); }
	else                         { return  _T(""); }

	//
	if( flags & ksBINARY ) { mode += _T("b"); }

	//
	if( flags & ksCOMMIT ) { mode += _T("c"); }

	return	mode;
}

//===============================================================================================//
// �t�@�C�� �|�C���^�̌��݈ʒu���擾����
//===============================================================================================//
KsInt32 KsFile::tell()
{
	return ftell( m_pFile );
}

//===============================================================================================//
// �w�肳�ꂽ�ʒu�Ƀt�@�C�� �|�C���^���ړ�����
//===============================================================================================//
KsInt32 KsFile::seek( KsInt32 offset, KsInt32 mode )
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
		fseek( m_pFile, offset, mode );
	}
	
	return ( tell() - pos );
}


//===============================================================================================//
// �t�@�C���I�[�v��
//===============================================================================================//
KsBool KsFile::open( const KsString& fullPath, KsInt32 flags, ksBYTE_ORDER byteOrder )
{
	KsChar		drive[ _MAX_DRIVE ];
	KsChar		dir[ _MAX_DIR ];
	KsChar		fname[ _MAX_FNAME ];
	KsChar		ext[ _MAX_EXT ];

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
	
		if( !( m_pFile = ks_fopen( fullPath.c_str(), mode.c_str() ) ) )
		{
			return ksFALSE;
		}
	}
	else if( !( m_pFile = ks_fopen( m_name.c_str(), mode.c_str() ) ) )
	{
		return ksFALSE;
	}
	
	m_state     = ksOPEN;
	m_byteOrder = byteOrder;
	
	seek( 0, SEEK_END );

	m_size = tell();

	seek( 0, SEEK_SET );
	
	return ksTRUE;
}


//===============================================================================================//
// �t�@�C���I�[�v��
//===============================================================================================//
KsBool KsFile::open( const KsString& path, const KsString& fileName, KsInt32 flags )
{
	close();
	
	if( fileName.length() ){
		m_name = fileName;
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
	
		if( !( m_pFile = ks_fopen( fullPath.c_str(), mode.c_str() ) ) )
		{
			return ksFALSE;
		}
	}
	else if( !( m_pFile = ks_fopen( m_name.c_str(), mode.c_str() ) ) )
	{
		return ksFALSE;
	}
	
	m_state = ksOPEN;
	
	seek( 0, SEEK_END );

	m_size = tell();

	seek( 0, SEEK_SET );
	
	return ksTRUE;
}

//===============================================================================================//
// �t�@�C�������
//===============================================================================================//
void KsFile::close()
{
	if( m_pFile ){
		fclose( m_pFile );
		m_pFile = NULL;
	}
	
	m_state = ksCLOSED;
}

//===============================================================================================//
// �t�@�C������ǂݍ���
//===============================================================================================//
KsSize KsFile::read( void* pBuffer, KsInt32 count )
{
	KsSize		size;

	if( pBuffer ){
		//size = fread( pBuffer, 1, count, m_pFile );
		size = fread( pBuffer, count, 1, m_pFile );
	}
	else{
		KsSize pos = tell();

		seek( count, SEEK_CUR );

		size = tell() - pos;
	}

	return size;
}

//===============================================================================================//
// �t�@�C������ǂݍ���
//===============================================================================================//
KsString KsFile::readString()
{
	KsString		str;
	KsChar			buf[ 4*1024 ];
	
	// �L�����ǂ����̃`�F�b�N
	if( !isValid() )
	{
		return str;
	}

	// �ǂݍ���
	ks_fgets( buf, 4*1024, m_pFile );
	str = buf;
	
	return str;
}

//===============================================================================================//
// �t�@�C������ǂݍ���
//===============================================================================================//
KsChar KsFile::readChar()
{
	KsChar val;

	// �L�����ǂ����̃`�F�b�N
	if( !isValid() )
	{
		return 0;
	}

	// �ǂݍ���
	fread( &val, 1, sizeof(KsChar), m_pFile );
	//val = fgetc( m_pFile );

	return val;
}

//===============================================================================================//
// �t�@�C������ǂݍ���
//===============================================================================================//
KsInt8 KsFile::readInt8()
{
	KsInt8 val;

	// �L�����ǂ����̃`�F�b�N
	if( !isValid() )
	{
		return 0;
	}

	// �ǂݍ���
	fread( &val, 1, sizeof(KsInt8), m_pFile );

	return val;
}

//===============================================================================================//
// �t�@�C������ǂݍ���
//===============================================================================================//
KsUInt8 KsFile::readUInt8()
{
	KsUInt8 val;

	// �L�����ǂ����̃`�F�b�N
	if( !isValid() )
	{
		return 0;
	}

	// �ǂݍ���
	fread( &val, 1, sizeof(KsUInt8), m_pFile );

	return val;
}

//===============================================================================================//
// �t�@�C������ǂݍ���
//===============================================================================================//
KsInt32 KsFile::readByte()
{
	KsInt32 val;

	// �L�����ǂ����̃`�F�b�N
	if( !isValid() )
	{
		return 0;
	}

	// �ǂݍ���
	fread( &val, 1, sizeof(KsUInt8), m_pFile );

	return val;
}

//===============================================================================================//
// �t�@�C������ǂݍ���
//===============================================================================================//
KsInt16 KsFile::readInt16()
{
	KS_DATA2	val;
	KS_DATA2	data;

	// �L�����ǂ����̃`�F�b�N
	if( !isValid() )
	{
		return 0;
	}

	// �ǂݍ���
	fread( &val, 1, sizeof(KS_DATA2), m_pFile );

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

//===============================================================================================//
// �t�@�C������ǂݍ���
//===============================================================================================//
KsUInt16 KsFile::readUInt16()
{
	KS_DATA2	val;
	KS_DATA2	data;

	// �L�����ǂ����̃`�F�b�N
	if( !isValid() )
	{
		return 0;
	}

	// �ǂݍ���
	fread( &val, 1, sizeof(KS_DATA2), m_pFile );

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


//===============================================================================================//
// �t�@�C������ǂݍ���
//===============================================================================================//
KsInt32 KsFile::readInt32()
{
	KS_DATA4	val;
	KS_DATA4	data;

	// �L�����ǂ����̃`�F�b�N
	if( !isValid() )
	{
		return 0;
	}

	// �ǂݍ���
	fread( &val, 1, sizeof(KS_DATA4), m_pFile );

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

//===============================================================================================//
// �t�@�C������ǂݍ���
//===============================================================================================//
KsUInt32 KsFile::readUInt32()
{
	KS_DATA4	val;
	KS_DATA4	data;

	// �L�����ǂ����̃`�F�b�N
	if( !isValid() )
	{
		return 0;
	}

	// �ǂݍ���
	fread( &val, 1, sizeof(KS_DATA4), m_pFile );

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

//===============================================================================================//
// �t�@�C������ǂݍ���
//===============================================================================================//
KsReal KsFile::readReal()
{
	KS_DATA4	val;
	KS_DATA4	data;

	// �L�����ǂ����̃`�F�b�N
	if( !isValid() )
	{
		return 0;
	}

	// �ǂݍ���
	fread( &val, 1, sizeof(KS_DATA4), m_pFile );

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
 * �G���R�[�h���ꂽ��������ǂݍ���
 * @return					�ϒ��T�C�Y�̃G���R�[�h���ꂽ 32-bit ������������
 */
/************************************************************************************************/
KsUInt32 KsFile::readEncodedU32()
{
	KsByte	data = 0;

	fread( &data, 1, sizeof(KsByte), m_pFile );

	KsUInt32 val = (KsUInt32)data;

	if( !(val & 0x00000080) )
	{
		return val;
	}

	fread( &data, 1, sizeof(KsByte), m_pFile );

	val = (val & 0x0000007f) | (KsUInt32)data << 7;

	if( !(val & 0x00004000) )
	{
		return val;
	}

	fread( &data, 1, sizeof(KsByte), m_pFile );

	val = (val & 0x00003fff) | (KsUInt32)data << 14;

	if( !(val & 0x00200000) )
	{
		return val;
	}

	fread( &data, 1, sizeof(KsByte), m_pFile );

	val = (val & 0x001fffff) | (KsUInt32)data << 21;

	if( !(val & 0x10000000) )
	{
		return val;
	}

	fread( &data, 1, sizeof(KsByte), m_pFile );

	val = (val & 0x0fffffff) | (KsUInt32)data << 28;

	return val;
}

/************************************************************************************************/
/*
 * �t�@�C���ɒl����������
 * @param	val				�������ޒl
 * @return					�������񂾃o�C�g��
 */
/************************************************************************************************/
KsSize KsFile::writeInt16( KsInt16 val )
{
	// �L�����ǂ����̃`�F�b�N
	if( !isValid() )
	{
		return 0;
	}

	// �G���f�B�A�����̃`�F�b�N
	if( ksLITTLEENDIAN == m_byteOrder )
	{
		// ���g���G���f�B�A��
		return fwrite( &val, 1, sizeof(KsInt16), m_pFile );
	}

	KS_DATA2	temp;
	KS_DATA2	data;

	temp.s16 = val;

	// �r�b�N�G���f�B�A��
	data.byte[ 0 ] = temp.byte[ 1 ];
	data.byte[ 1 ] = temp.byte[ 0 ];

	return fwrite( &data.s16, 1, sizeof(KsInt16), m_pFile );
}

/************************************************************************************************/
/*
 * �t�@�C���ɒl����������
 * @param	val				�������ޒl
 * @return					�������񂾃o�C�g��
 */
/************************************************************************************************/
KsSize KsFile::writeUInt16( KsUInt16 val )
{
	// �L�����ǂ����̃`�F�b�N
	if( !isValid() ){
		return 0;
	}

	// �G���f�B�A�����̃`�F�b�N
	if( ksLITTLEENDIAN == m_byteOrder ){
		// ���g���G���f�B�A��
		return fwrite( &val, 1, sizeof(KsUInt16), m_pFile );
	}

	KS_DATA2	temp;
	KS_DATA2	data;

	temp.u16 = val;

	// �r�b�N�G���f�B�A��
	data.byte[ 0 ] = temp.byte[ 1 ];
	data.byte[ 1 ] = temp.byte[ 0 ];

	return fwrite( &data.u16, 1, sizeof(KsUInt16), m_pFile );
}

/************************************************************************************************/
/*
 * �t�@�C���ɒl����������
 * @param	val				�������ޒl
 * @return					�������񂾃o�C�g��
 */
/************************************************************************************************/
KsSize KsFile::writeInt32( KsInt32 val )
{
	// �L�����ǂ����̃`�F�b�N
	if( !isValid() ){
		return 0;
	}

	// �G���f�B�A�����̃`�F�b�N
	if( ksLITTLEENDIAN == m_byteOrder ){
		// ���g���G���f�B�A��
		return fwrite( &val, 1, sizeof(KsInt32), m_pFile );
	}

	KS_DATA4	temp;
	KS_DATA4	data;

	temp.i32 = val;

	// �r�b�N�G���f�B�A��
	data.byte[ 0 ] = temp.byte[ 3 ];
	data.byte[ 1 ] = temp.byte[ 2 ];
	data.byte[ 2 ] = temp.byte[ 1 ];
	data.byte[ 3 ] = temp.byte[ 0 ];

	return fwrite( &data.i32, 1, sizeof(KsInt32), m_pFile );
}

/************************************************************************************************/
/*
 * �t�@�C���ɒl����������
 * @param	val				�������ޒl
 * @return					�������񂾃o�C�g��
 */
/************************************************************************************************/
KsSize KsFile::writeUInt32( KsUInt32 val )
{
	// �L�����ǂ����̃`�F�b�N
	if( !isValid() ){
		return 0;
	}

	// �G���f�B�A�����̃`�F�b�N
	if( ksLITTLEENDIAN == m_byteOrder ){
		// ���g���G���f�B�A��
		return fwrite( &val, 1, sizeof(KsUInt32), m_pFile );
	}

	KS_DATA4	temp;
	KS_DATA4	data;

	temp.u32 = val;

	// �r�b�N�G���f�B�A��
	data.byte[ 0 ] = temp.byte[ 3 ];
	data.byte[ 1 ] = temp.byte[ 2 ];
	data.byte[ 2 ] = temp.byte[ 1 ];
	data.byte[ 3 ] = temp.byte[ 0 ];

	return fwrite( &data.u32, 1, sizeof(KsUInt32), m_pFile );
}

/************************************************************************************************/
/*
 * �t�@�C���ɒl����������
 * @param	val				�������ޒl
 * @return					�������񂾃o�C�g��
 */
/************************************************************************************************/
KsSize KsFile::writeReal( KsReal val )
{
	// �L�����ǂ����̃`�F�b�N
	if( !isValid() ){
		return 0;
	}

	// �G���f�B�A�����̃`�F�b�N
	if( ksLITTLEENDIAN == m_byteOrder ){
		// ���g���G���f�B�A��
		return fwrite( &val, 1, sizeof(KsReal), m_pFile );
	}

	KS_DATA4	temp;
	KS_DATA4	data;

	temp.f = val;

	// �r�b�N�G���f�B�A��
	data.byte[ 0 ] = temp.byte[ 3 ];
	data.byte[ 1 ] = temp.byte[ 2 ];
	data.byte[ 2 ] = temp.byte[ 1 ];
	data.byte[ 3 ] = temp.byte[ 0 ];

	return fwrite( &data.f, 1, sizeof(KsReal), m_pFile );
}

/************************************************************************************************/
/*
 * �t�@�C���ɒl����������
 * @param	val				�������ޒl
 * @return					�������񂾃o�C�g��
 */
/************************************************************************************************/
KsSize KsFile::writeInt8( KsInt8 val )
{
	// �L�����ǂ����̃`�F�b�N
	if( !isValid() ){
		return 0;
	}

	// ���g���G���f�B�A��
	return fwrite( &val, 1, sizeof(KsInt8), m_pFile );
}

/************************************************************************************************/
/*
 * �t�@�C���ɒl����������
 * @param	val				�������ޒl
 * @return					�������񂾃o�C�g��
 */
/************************************************************************************************/
KsSize KsFile::writeUInt8( KsUInt8 val )
{
	// �L�����ǂ����̃`�F�b�N
	if( !isValid() ){
		return 0;
	}

	// ���g���G���f�B�A��
	return fwrite( &val, 1, sizeof(KsUInt8), m_pFile );
}

/************************************************************************************************/
/*
 * �t�@�C���ɒl����������
 * @param	val				�������ޒl
 * @return					�������񂾃o�C�g��
 */
/************************************************************************************************/
KsSize KsFile::writeChar( KsChar val )
{
	// �L�����ǂ����̃`�F�b�N
	if( !isValid() ){
		return 0;
	}

	// ���g���G���f�B�A��
	return fwrite( &val, 1, sizeof(KsChar), m_pFile );
}

/************************************************************************************************/
/*
 * �t�@�C���ɒl����������
 * @param	val				�������ޒl
 * @return					�������񂾃o�C�g��
 */
/************************************************************************************************/
KsSize KsFile::writeByte( KsInt32 val )
{
	// �L�����ǂ����̃`�F�b�N
	if( !isValid() ){
		return 0;
	}

	// ���g���G���f�B�A��
	return fwrite( &val, 1, sizeof(KsInt8), m_pFile );
}

/************************************************************************************************/
/*
 * �o�b�t�@����t�@�C���ɒl����������
 * @param	pBuffer			�������ރo�b�t�@
 * @param	count			�������ރo�C�g��
 * @return					�������񂾃o�C�g��
 */
/************************************************************************************************/
KsSize KsFile::write( const void *pBuffer, KsInt32 count )
{
	if( !isValid() || ( count <= 0 ) ){
		return 0;
	}

	KsSize size = 0;
	
	if( pBuffer ){
		size = fwrite( pBuffer, 1, count, m_pFile );
	}
	else
	{
		KsUInt32	pos = tell();
		seek( count, SEEK_CUR );
		size = tell() - pos;
	}

	return size;
}

