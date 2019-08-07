/************************************************************************************************/
/** 
 * @file		KsString.cpp
 * @brief		������N���X
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

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsString::KsString() : m_pString( 0 ), m_length( 0 ), m_size( 0 )
{
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 * @param		string		������N���X�̎Q��
 */
/************************************************************************************************/
KsString::KsString( const KsString& string ) : m_pString( 0 ), m_length( 0 ), m_size( 0 )
{
	/* �������擾 */
	m_length = string.length();
	
	/* �o�b�t�@�T�C�Y���擾 */
	m_size = string.size();
	
	/* �������[���m�ۂ��Ȃ��� */
	ksDELETEARRAY( m_pString );

	m_pString = new KsChar[ m_size ];

	/* �R�s�[���� */
	KsMemCopy( m_pString, string.c_str(), m_size );
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 * @param		pString		������̃|�C���^
 */
/************************************************************************************************/
KsString::KsString( const KsSChar* pString ) : m_pString( 0 ), m_length( 0 ), m_size( 0 )
{
#ifdef UNICODE
	/* �������擾 */
	m_length = static_cast<KsUInt32>( strlen(pString) );

	/* �o�b�t�@�T�C�Y���擾 */
	m_size = m_length + 1;

	/* �������[���m�ۂ��Ȃ��� */
	ksDELETEARRAY( m_pString );

	m_pString = new KsChar[ m_size ];

	//���P�[���w��
	setlocale(LC_ALL,"japanese");

	//�ϊ�
	size_t	convLen = 0;
	mbstowcs_s( &convLen, m_pString, m_size, pString, _TRUNCATE );
	m_pString[ m_length ] = '\0';
#else
	/* �������擾 */
	m_length = static_cast<KsUInt32>( ks_strlen(pString) );

	/* �o�b�t�@�T�C�Y���擾 */
	m_size = m_length + 1;

	/* �������[���m�ۂ��Ȃ��� */
	ksDELETEARRAY( m_pString );

	m_pString = new KsChar[ m_size ];

	/* �R�s�[���� */
	KsMemCopy( m_pString, pString, m_size );

	m_pString[ m_length ] = '\0';
#endif // UNICODE
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 * @param		pString		������̃|�C���^
 */
/************************************************************************************************/
KsString::KsString( const KsWChar* pString ) : m_pString( 0 ), m_length( 0 ), m_size( 0 )
{
#ifdef UNICODE
	/* �������擾 */
	m_length = static_cast<KsUInt32>( ks_strlen(pString) );

	/* �o�b�t�@�T�C�Y���擾 */
	m_size = 2*(m_length + 1);

	/* �������[���m�ۂ��Ȃ��� */
	ksDELETEARRAY( m_pString );

	m_pString = new KsChar[ m_size ];

	/* �������[���N���A�[���� */
	KsZeroMemory( m_pString, m_size );

	/* �R�s�[���� */
	KsMemCopy( m_pString, pString, m_size );
#else
	/* �������擾 */
	m_length = static_cast<KsUInt32>( wcslen(pString) );

	/* �o�b�t�@�T�C�Y���擾 */
	m_size = 2*(m_length + 1);

	/* �������[���m�ۂ��Ȃ��� */
	ksDELETEARRAY( m_pString );

	m_pString = new KsChar[ m_size ];

	/* �������[���N���A�[���� */
	KsZeroMemory( m_pString, m_size );

	//���P�[���w��
	setlocale(LC_ALL,"japanese");

	//�ϊ�
	KsUInt32	convLen = 0;
	wcstombs_s( &convLen, m_pString, m_size, pString, _TRUNCATE );
#endif // UNICODE
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsString::~KsString()
{
	ksDELETEARRAY( m_pString );
}

/************************************************************************************************/
/*
 * �w��͈͂̕������폜����
 * @param		top			����������̐擪
 * @param		num			����������̐�
 */
/************************************************************************************************/
void KsString::erase( KsUInt32 top, KsUInt32 num )
{
	KsUInt32	length = m_length - num + 1;

	KsChar*		pBuf = new KsChar[ length ];

	if( pBuf )
	{
		ks_strncpy( pBuf, &m_pString[ top ], num );
		pBuf[ length ] = '\0';
	
		ksDELETEARRAY( m_pString );

		m_pString = pBuf;
		m_length  = length;
	}
}

/************************************************************************************************/
/*
 * ��������N���A
 */
/************************************************************************************************/
void KsString::clear()
{
	ksDELETEARRAY( m_pString );
	m_length  = 0;
	m_pString = 0;
}

/************************************************************************************************/
/*
 * ��������N���A
 */
/************************************************************************************************/
KsString& KsString::operator=( const KsString& string )
{
	/* �������擾 */
	m_length = string.length();

	/* �o�b�t�@�T�C�Y���擾 */
	m_size = string.size();
	
	/* �������[���m�ۂ��Ȃ��� */
	ksDELETEARRAY( m_pString );

	m_pString = new KsChar[ m_size ];

	/* �R�s�[���� */
	KsMemCopy( m_pString, string.c_str(), m_size );

	return	(*this);
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsString& KsString::operator=( const KsSChar* pString )
{
#ifdef UNICODE
	/* �������擾 */
	m_length = static_cast<KsUInt32>( strlen(pString) );

	/* �o�b�t�@�T�C�Y���擾 */
	m_size = m_length + 1;

	/* �������[���m�ۂ��Ȃ��� */
	ksDELETEARRAY( m_pString );

	m_pString = new KsChar[ m_size ];

	//���P�[���w��
	setlocale(LC_ALL,"japanese");

	//�ϊ�
	size_t	convLen = 0;
	mbstowcs_s( &convLen, m_pString, m_size, pString, _TRUNCATE );
	m_pString[ m_length ] = '\0';
#else
	/* �������擾 */
	m_length = static_cast<KsUInt32>( ks_strlen(pString) );

	/* �o�b�t�@�T�C�Y���擾 */
	m_size = m_length + 1;

	/* �������[���m�ۂ��Ȃ��� */
	ksDELETEARRAY( m_pString );

	m_pString = new KsChar[ m_size ];

	/* �R�s�[���� */
	KsMemCopy( m_pString, pString, m_size );

	m_pString[ m_length ] = '\0';
#endif // UNICODE

	return	(*this);
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsString& KsString::operator=( const KsWChar* pString )
{
#ifdef UNICODE
	/* �������擾 */
	m_length = static_cast<KsUInt32>( ks_strlen(pString) );

	/* �o�b�t�@�T�C�Y���擾 */
	m_size = 2*(m_length + 1);

	/* �������[���m�ۂ��Ȃ��� */
	ksDELETEARRAY( m_pString );

	m_pString = new KsChar[ m_size ];

	/* �������[���N���A�[���� */
	KsZeroMemory( m_pString, m_size );

	/* �R�s�[���� */
	KsMemCopy( m_pString, pString, m_size );
#else
	/* �������擾 */
	m_length = static_cast<KsUInt32>( wcslen(pString) );

	/* �o�b�t�@�T�C�Y���擾 */
	m_size = 2*(m_length + 1);

	/* �������[���m�ۂ��Ȃ��� */
	ksDELETEARRAY( m_pString );

	m_pString = new KsChar[ m_size ];

	/* �������[���N���A�[���� */
	KsZeroMemory( m_pString, m_size );

	//���P�[���w��
	setlocale(LC_ALL,"japanese");

	//�ϊ�
	KsUInt32	convLen = 0;
	wcstombs_s( &convLen, m_pString, m_size, pString, _TRUNCATE );
#endif // UNICODE

	return	(*this);
}


/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsString& KsString::operator=( const KsChar c )
{
	/* �������擾 */
	m_length = 1;

	/* �o�b�t�@�T�C�Y���擾 */
	m_size = 2;

	/* �������[���m�ۂ��Ȃ��� */
	ksDELETEARRAY( m_pString );

	m_pString = new KsChar[ 2 ];
	m_pString[ 1 ] = '\0';

	return	(*this);
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsString& KsString::operator+=( const KsString& string )
{
	/* �������擾 */
	m_length += string.length();

	/* �o�b�t�@�T�C�Y���擾 */
	m_size += string.length();

	/* �������[���m�ۂ��Ȃ��� */
	KsChar*		pTemp = new KsChar[ m_length+1 ];

	ks_strcpy( pTemp, m_pString );
	ks_strcat( pTemp, string.c_str() );

	ksDELETEARRAY( m_pString );

	m_pString = pTemp;

	return	(*this);
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsString& KsString::operator+=( const KsChar* pString )
{
	KsUInt32 len = static_cast<KsUInt32>( ks_strlen(pString) );

	/* �������擾 */
	m_length += len;

	/* �o�b�t�@�T�C�Y���擾 */
	m_size += len;

	/* �������[���m�ۂ��Ȃ��� */
	KsChar*		pTemp = new KsChar[ m_length+1 ];

	ks_strcpy( pTemp, m_pString );
	ks_strcat( pTemp, pString );

	ksDELETEARRAY( m_pString );

	m_pString = pTemp;

	return	(*this);
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsString& KsString::operator+=( const KsChar c )
{
	/* �������[���m�ۂ��Ȃ��� */
	KsChar*		pTemp = new KsChar[ m_length+2 ];

	ks_strcpy( pTemp, m_pString );
	pTemp[ m_length   ] = c;
	pTemp[ m_length+1 ] = '\0';

	/* �������擾 */
	m_length++;
	m_size++;

	ksDELETEARRAY( m_pString );

	m_pString = pTemp;

	return	(*this);
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsString KsString::operator+(const KsString& string )
{
	KsString		temp;

	temp  = (*this);
	temp += string;

	return temp;
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsString KsString::operator+(const KsChar* pString )
{
	KsString		temp;

	temp  = (*this);
	temp += pString;

	return temp;
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsString KsString::operator+(const KsChar c )
{
	KsString		temp;

	temp  = (*this);
	temp += c;

	return temp;
}

/************************************************************************************************/
/*
 * ���C�h������(WCHAR*)���}���`�o�C�g������(char*)�ɕϊ�
 * @param	wStrW		�ϊ��O������
 * @param	pOut		�ϊ�������i�[�o�b�t�@
 */
/************************************************************************************************/
KsUInt32 ks_wcstombs( const KsWChar* wStrW, KsSChar* pOut, KsUInt32 len )
{
	KsUInt32	wLen = 0;

	//���P�[���w��
	setlocale( LC_ALL,"japanese" );

	//�ϊ�
	wcstombs_s( &wLen, pOut, len, wStrW, _TRUNCATE );

	return wLen;
}

/************************************************************************************************/
/*
 * �}���`�o�C�g������(char*)�����C�h������(WCHAR*)�ɕϊ�
 */
/************************************************************************************************/
KsUInt32 ks_mbstowcs( const KsSChar* sStr, KsWChar* pOut, KsUInt32 len )
{
	KsUInt32	wLen = 0;

	//���P�[���w��
	setlocale( LC_ALL,"japanese" );

	//�ϊ�
	mbstowcs_s( &wLen, pOut, len, sStr, _TRUNCATE );

	return wLen;
}

