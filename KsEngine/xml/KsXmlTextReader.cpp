/************************************************************************************************/
/** 
 * @file		KsString.h
 * @brief		�����񑀍�
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/


/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"

/*===============================================================================================*/
/*                                     << ��` >>                                                */
/*===============================================================================================*/

KsInt32 KsXmlAttributeWork::m_index = 0;
KsXmlAttribute KsXmlAttributeWork::m_work[ ksXML_ATTRIBUTE_WORK_SIZE ];
KsXmlAttribute* KsXmlAttributeWork::m_stack[ ksXML_ATTRIBUTE_WORK_SIZE ];




KsXmlAttribute* KsXmlAttributeWork::allocAttribute()
{
	if( m_index > 0 )
	{
		--m_index;
		
		return m_stack[ m_index ];
	}

	return NULL;
}

void KsXmlAttributeWork::freeAttribute( KsXmlAttribute* pAttribute )
{
	m_stack[ m_index ] = pAttribute;
	++m_index;
}


void KsXmlAttributeWork::create()
{
	for( KsInt32 i=0; i<ksXML_ATTRIBUTE_WORK_SIZE; i++ )
	{
		m_stack[ i ] = &m_work[ i ];
	}

	m_index = ksXML_ATTRIBUTE_WORK_SIZE;
}

void KsXmlAttributeWork::destory()
{
	m_index = 0;
}

void KsXmlAttributeWork::clear()
{
	for( KsInt32 i=0; i<ksXML_ATTRIBUTE_WORK_SIZE; i++ )
	{
		m_stack[ i ] = &m_work[ i ];
	}

	m_index = ksXML_ATTRIBUTE_WORK_SIZE;
}


/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsXmlTextReader::KsXmlTextReader()
	: m_readState( ksXmlInitial )
	, m_pFileBuffer( 0 )
	, m_pNameBuffer( 0 )
	, m_pValueBuffer( 0 )
	, m_hasPeek( ksFALSE )
	, m_nodeType( ksXmlNone )
	, m_nameSize( 0 )
	, m_valueSize( 0 )
	, m_attributeIndex( 0 )
	, m_pAttributeNameBuffer( 0 )
	, m_pAttributeValueBuffer( 0 )
	, m_attributeNameSize( 0 )
	, m_attributeValueSize( 0 )

{
}

KsXmlTextReader::KsXmlTextReader( const KsChar* pFileName )
	: m_readState( ksXmlInitial )
	, m_pFileBuffer( 0 )
	, m_pNameBuffer( 0 )
	, m_pValueBuffer( 0 )
	, m_hasPeek( ksFALSE )
	, m_nodeType( ksXmlNone )
	, m_nameSize( 0 )
	, m_valueSize( 0 )
	, m_attributeIndex( 0 )
	, m_pAttributeNameBuffer( 0 )
	, m_pAttributeValueBuffer( 0 )
	, m_attributeNameSize( 0 )
	, m_attributeValueSize( 0 )
{
	create( pFileName );
}

KsXmlTextReader::KsXmlTextReader( KsFileObject& file )
	: m_readState( ksXmlInitial )
	, m_pFileBuffer( 0 )
	, m_pNameBuffer( 0 )
	, m_pValueBuffer( 0 )
	, m_hasPeek( ksFALSE )
	, m_nodeType( ksXmlNone )
	, m_nameSize( 0 )
	, m_valueSize( 0 )
	, m_attributeIndex( 0 )
	, m_pAttributeNameBuffer( 0 )
	, m_pAttributeValueBuffer( 0 )
	, m_attributeNameSize( 0 )
	, m_attributeValueSize( 0 )
{
	create( file );
}

KsBool KsXmlTextReader::create( const KsChar* pFileName )
{
	destroy();

	m_readState      = ksXmlInitial;
	m_pFileBuffer    = NULL;
	m_pNameBuffer    = NULL;
	m_pValueBuffer   = NULL;
	m_hasPeek        = ksFALSE;
	m_nodeType       = ksXmlNone;
	m_nameSize       = 0;
	m_valueSize      = 0;
	m_attributeIndex = 0;
	m_pAttributeNameBuffer  = 0;
	m_pAttributeValueBuffer = 0;
	m_attributeNameSize     = 0;
	m_attributeValueSize    = 0;

	if( !m_file.open( pFileName, ksREAD ) )
	{
		return ksFALSE;
	}

	m_pFileBuffer = (KsChar*)m_file.getFilePtr();

	m_canSeek = m_pFileBuffer != NULL && readerPeek() != '\0';

	KsXmlAttributeWork::create();

	m_pNameBuffer           = new KsChar[ ksXML_TEXT_READER_BUFFER_SIZE ];
	m_pValueBuffer          = new KsChar[ ksXML_TEXT_READER_BUFFER_SIZE ];
	m_pAttributeNameBuffer  = new KsChar[ ksXML_TEXT_READER_BUFFER_SIZE ];
	m_pAttributeValueBuffer = new KsChar[ ksXML_TEXT_READER_BUFFER_SIZE ];

	m_attributes.arrayRalloc( ksXML_ATTRIBUTE_WORK_SIZE );

	return ksTRUE;
}

KsBool KsXmlTextReader::create( KsFileObject& file )
{
	destroy();

	m_readState      = ksXmlInitial;
	m_pFileBuffer    = NULL;
	m_pNameBuffer    = NULL;
	m_pValueBuffer   = NULL;
	m_hasPeek        = ksFALSE;
	m_nodeType       = ksXmlNone;
	m_nameSize       = 0;
	m_valueSize      = 0;
	m_attributeIndex = 0;
	m_pAttributeNameBuffer  = 0;
	m_pAttributeValueBuffer = 0;
	m_attributeNameSize     = 0;
	m_attributeValueSize    = 0;

	m_pFileBuffer = (KsChar*)file.getFilePtr();

	m_canSeek = m_pFileBuffer != NULL && readerPeek() != '\0';

	KsXmlAttributeWork::create();

	m_pNameBuffer           = new KsChar[ ksXML_TEXT_READER_BUFFER_SIZE ];
	m_pValueBuffer          = new KsChar[ ksXML_TEXT_READER_BUFFER_SIZE ];
	m_pAttributeNameBuffer  = new KsChar[ ksXML_TEXT_READER_BUFFER_SIZE ];
	m_pAttributeValueBuffer = new KsChar[ ksXML_TEXT_READER_BUFFER_SIZE ];

	m_attributes.arrayRalloc( ksXML_ATTRIBUTE_WORK_SIZE );

	return ksTRUE;
}

void KsXmlTextReader::destroy()
{
	close();
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsXmlTextReader::~KsXmlTextReader()
{
	destroy();
}


/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsBool KsXmlTextReader::read()
{
	if( NULL == m_pFileBuffer )
	{
		return ksFALSE;
	}

	m_readState = ksXmlInteractive;
	
	return readContent();
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsBool KsXmlTextReader::moveToNextAttribute()
{
	if( m_attributes.size() == 0 )
	{
		return ksFALSE;
	}

	if( m_attributeIndex == m_attributes.size() )
	{
		/* �I�� */
		m_attributes.clear();

		KsXmlAttributeWork::clear();

		m_attributeIndex = 0;
	}
	else
	{
		m_nameSize  = m_attributes[ m_attributeIndex ]->m_name.length();
		m_valueSize = m_attributes[ m_attributeIndex ]->m_value.length();
		memcpy( m_pNameBuffer,  m_attributes[ m_attributeIndex ]->m_name.c_str(), m_nameSize );
		memcpy( m_pValueBuffer, m_attributes[ m_attributeIndex ]->m_value.c_str(),  m_valueSize );
		m_pNameBuffer[ m_nameSize ]   = '\0';
		m_pValueBuffer[ m_valueSize ] = '\0';

		m_nodeType = ksXmlAttribute;
		++m_attributeIndex;
		return ksTRUE;
	}

	return ksFALSE;
}


/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsXmlTextReader::close()
{
	m_file.close();
	m_readState = ksXmlClosed;
	
	KsXmlAttributeWork::destory();
	m_attributes.clear();

	ksDELETEARRAY( m_pNameBuffer );
	ksDELETEARRAY( m_pValueBuffer );
	ksDELETEARRAY( m_pAttributeNameBuffer );
	ksDELETEARRAY( m_pAttributeValueBuffer );
}


/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsBool KsXmlTextReader::readContent()
{
	switch( peekChar() )
	{
		case '<':
		{
			readChar();
			readTag();
			break;
		}
		case '\r':
		{
			/* �X�y�[�X���΂� */
			readChar();
			return readContent();
		}
		case '\n':
		{
			/* ���s���΂� */
			readChar();
			return readContent();
		}
		case ' ':
		{
			/* �X�y�[�X���΂� */
			skipSpace();
			return readContent();
		}
		case '\0':
		{
			m_readState = ksXmlEndOfFile;
			m_nodeType  = ksXmlNone;
			clearAttributes();
			break;
		}
		default:
		{
			readText();
			break;
		}
	}

	return m_readState != ksXmlEndOfFile;
}


/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsXmlTextReader::readName()
{
	if( !KsXmlChar::isFirstNameChar( peekChar() ) )
	{
		throw KsXmlException("�d�l�ɏ������Ă��Ȃ������Ŏn�܂��Ă��܂�");
	}

	m_nameSize = 0;
	m_pNameBuffer[ m_nameSize ] = static_cast<KsChar>( readChar() );
	++m_nameSize;

	while( KsXmlChar::isNameChar( peekChar() ) )
	{
		m_pNameBuffer[ m_nameSize ] = static_cast<KsChar>( readChar() );
		++m_nameSize;
    }

	m_pNameBuffer[ m_nameSize ] = '\0';
}


/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsXmlTextReader::clearAttributes()
{
	if( m_attributes.size() > 0 )
	{
		KsXmlAttributeWork::clear();
		m_attributes.reset();
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsXmlTextReader::readAttributes()
{
	do
	{
		readAttributeName();
		skipSpace();
		expect( '=' );
		skipSpace();
		readAttribute();
		skipSpace();

		KsXmlAttribute*		pAttribute = KsXmlAttributeWork::allocAttribute();

		pAttribute->m_name  = m_pAttributeNameBuffer;
		pAttribute->m_value = m_pAttributeValueBuffer;

		m_attributes.push_back( pAttribute );
	
	}while( (peekChar() != '/') && (peekChar() != '>') && (peekChar() != '\0') );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsXmlTextReader::readAttribute()
{
	KsInt32 quoteChar = readChar();

	if( (quoteChar != '\'') && (quoteChar != '\"') ){
		throw KsXmlException("���p��������܂���");
	}

	m_attributeValueSize = 0;

	while( peekChar() != quoteChar )
	{
		KsInt32 ch = readChar();

		switch( ch )
		{
			case '<':
			{
				throw KsXmlException("�����l���Ƀ^�O���ʂ�����܂�");
				break;
			}
			case '\0':
			{
				throw KsXmlException("EOF�����o���܂���");
				break;
			}
			default:
			{
				m_pAttributeValueBuffer[ m_attributeValueSize ] = static_cast<KsChar>( ch );
				++m_attributeValueSize;
				break;
			}
		}
	}

	m_pAttributeValueBuffer[ m_attributeValueSize ] = '\0';

	readChar();
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsXmlTextReader::readEndTag()
{
	readName();

	skipSpace();
	expect( '>' );

	m_nodeType = ksXmlEndElement;
	clearAttributes();
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsXmlTextReader::readProcessingInstruction()
{
	readName();
	skipSpace();

	m_valueSize = 0;

	while( peekChar() != '\0' )
	{
		KsInt32 ch = readChar();

		if( ch == '?' && peekChar() == '>' )
		{
			readChar();
			break;
		}

		m_pValueBuffer[ m_valueSize ] = static_cast<KsChar>( ch );
		++m_valueSize;
	}

	m_pValueBuffer[ m_valueSize ] = '\0';

	/* '?'�ŗL�̏�����΂� */
	if( ks_strncmp( _T("xml"), m_pNameBuffer, ks_strlen( _T("xml") ) ) == 0 )
	{
		m_nodeType = ksXmlDeclaration;
	}
	else
	{
		m_nodeType = ksXmlProcessingInstruction;
	}

	clearAttributes();
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsXmlTextReader::readText()
{
	m_valueSize = 0;

	KsInt32 ch = peekChar();

	// 1�x�ÂR�s�[�͂��Ȃ��J�E���g�������čŌ�ɃR�s�[�ɂ���
	while( ch != '<' && ch != '\0' )
	{
		if( ch == '&' )
		{
			readChar();
		}
		else
		{
			m_pValueBuffer[ m_valueSize ] = static_cast<KsChar>( readChar() );
			++m_valueSize;
		}
		ch = peekChar();
	}

	m_pValueBuffer[ m_valueSize ] = '\0';
	m_nodeType = ksXmlText;
	clearAttributes();
}


/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsXmlTextReader::readDeclaration()
{
	KsInt32	ch = peekChar();

	switch( ch )
	{
		case '-':
		{	
			expect( _T("--") );
			readComment();
			break;
		}
		case '[':
		{
			//throw CSyntaxException("CDATA�錾�͎�������Ă��܂���");
			break;
		}
		case 'D':
		{
			//throw CSyntaxException("DOCTYPE�錾�͎�������Ă��܂���");
			break;
		}
		default:
		{
			break;
		}
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsXmlTextReader::readComment()
{
	m_valueSize = 0;

	while( peekChar() != '\0' )
	{ 
		KsInt32 ch = readChar();

		if( (ch == '-') && (peekChar() == '-') )
		{
			readChar();

			if( peekChar() != '>' ){
				throw KsXmlException("�R�����g������'--'�͊܂߂��܂���");
			}

			readChar();
			break;
		}

		m_pValueBuffer[ m_valueSize ] = static_cast<KsChar>( ch );
		++m_valueSize;
	}

	m_pValueBuffer[ m_valueSize ] = '\0';

	m_nodeType = ksXmlComment;
	clearAttributes();
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsInt32 KsXmlTextReader::readChar()
{
	KsInt32	ch;
	
	if( m_hasPeek )
	{
		ch = m_peekChar;
		m_hasPeek = ksFALSE;
	}
	else
	{
		ch = readerRead();
	}

	return ch;
}


/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsInt32 KsXmlTextReader::peekChar()
{
	if( m_canSeek )
	{
		return readerPeek();
	}

	if( m_hasPeek )
	{
		return m_peekChar;
	}

	m_peekChar = readerRead();
	m_hasPeek = ksTRUE;

	return m_peekChar;
}


/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsXmlTextReader::readTag()
{
	switch( peekChar() )
	{
		case '/':
		{
			readChar();
			readEndTag();
			break;
		}
		case '?':
		{
			readChar();
			readProcessingInstruction();
			break;
		}
		case '!':
		{
			readChar();
			readDeclaration();
			break;
		}
		default:
		{
			readStartTag();
			break;
		}
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsXmlTextReader::readStartTag()
{
	readName();
	skipSpace();

	clearAttributes();

	if( KsXmlChar::isFirstNameChar( peekChar() ) )
	{
		readAttributes();
	}

	if( peekChar() == '/' )
	{
		readChar();
	}

	expect( '>' );

	m_nodeType = ksXmlElement;
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsXmlTextReader::skipSpace()
{
	while( KsXmlChar::isWhitespace( peekChar() ) )
	{
		readChar();
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsXmlTextReader::expect( KsInt32 expected )
{
	KsInt32 ch = readChar();

	if( ch != expected )
	{
		throw KsXmlException("expect���s");
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsXmlTextReader::expect( const KsChar* expected )
{
	KsInt32 len = ks_strlen( expected );

	for( KsInt32 i=0; i<len; i++ )
	{
		expect( expected[ i ] );
	}
}


/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsXmlTextReader::readAttributeName()
{
	if( !KsXmlChar::isFirstNameChar( peekChar() ) )
	{
		throw KsXmlException("�d�l�ɏ������Ă��Ȃ������Ŏn�܂��Ă��܂�");
	}

	m_attributeNameSize = 0;
	m_pAttributeNameBuffer[ m_attributeNameSize ] = static_cast<KsChar>( readChar() );
	++m_attributeNameSize;

	while( KsXmlChar::isNameChar( peekChar() ) )
	{
		m_pAttributeNameBuffer[ m_attributeNameSize ] = static_cast<KsChar>( readChar() );
		++m_attributeNameSize;
    }

	m_pAttributeNameBuffer[ m_attributeNameSize ] = '\0';
}
