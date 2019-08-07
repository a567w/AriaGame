/************************************************************************************************/
/** 
 * @file		KsFontData.cpp
 * @brief		�t�H���g�f�[�^
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsFontData.h"
#include "KsTexture.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsFontData::KsFontData()
	: m_pFontInfo( 0 )
	, m_sheetWidth( 0 )
	, m_sheetHeight( 0 )
	, m_numSheet( 0 )
	, m_fontSize( 0 )
	, m_numFont( 0 )
	, m_bAlpha( ksFALSE )
	, m_bAntialias( ksFALSE )
{
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsFontData::KsFontData( KsFileObject& file )
	: m_pFontInfo( 0 )
	, m_sheetWidth( 0 )
	, m_sheetHeight( 0 )
	, m_numSheet( 0 )
	, m_fontSize( 0 )
	, m_numFont( 0 )
	, m_bAlpha( ksFALSE )
	, m_bAntialias( ksFALSE )
{
	create( file );
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsFontData::~KsFontData()
{
	destroy();
}

KsBool KsFontData::create( KsFileObject& file )
{
	destroy();

	m_pFontInfo   = 0;
	m_sheetWidth  = 0;
	m_sheetHeight = 0;
	m_numSheet    = 0;
	m_fontSize    = 0;
	m_numFont     = 0;
	m_bAlpha      = 0;
	m_bAntialias  = 0;

	KsHeader	header;

	file.read( &header, sizeof(KsHeader) );

	if( stricmp( header.signature, "KFD" ) )
	{
		return ksFALSE;
	}

	//--------------------------------------------------------------
	// �w�b�_�[
	//--------------------------------------------------------------
	m_fontSize		= header.fontSize;
	m_numFont		= header.numFont;
	m_numSheet		= header.numSheet;
	m_sheetWidth	= header.sheetWidth;
	m_sheetHeight	= header.sheetHeight;

	//--------------------------------------------------------------
	// �C���f�b�N�X
	//--------------------------------------------------------------
	KsMemCopy( m_fontTbl, header.fontTbl, sizeof(KsUInt16)*ksCODE_TABLE_SIZE );

	//--------------------------------------------------------------
	// �f�[�^
	//--------------------------------------------------------------
	m_pFontInfo = new KsFontInfo[ m_numFont ];
	file.read( m_pFontInfo, sizeof(KsFontInfo) * m_numFont );

	return ksTRUE;
}

void KsFontData::destroy()
{
	ksDELETEARRAY( m_pFontInfo );

	for( KsUInt32 i=0; i<m_vpTextures.size(); i++ )
	{
		ksDESTROY( m_vpTextures[ i ] );
	}
	
	m_vpTextures.clear();
}

#if 0
//=============================================================================
/**
*/
//=============================================================================
Bool KsFontData::getWidth( const char *pStr, KsInt32 *pLeft, KsInt32 *pCenter, KsInt32 *pRight )
{
	KsUInt16 code = getCharCode( (unsigned char *)pStr );
	KsUInt16 index = m_IndexTbl[ code2Index(code) ];
	if ( index != 0xFFFF )
	{
		if ( pLeft   != NULL ) *pLeft	= m_pSheetTbl[index].abcA;
		if ( pCenter != NULL ) *pCenter	= m_pSheetTbl[index].abcB;
		if ( pRight  != NULL ) *pRight	= m_pSheetTbl[index].abcC;

		return true;
	}

	return false;
}
#endif


KsUInt16 KsFontData::code2Index( KsUInt16 code )
{
	KsUInt16	codeShift = 0;

	// ���p����
	if( code <= ksCODE_ASCII_END )
	{
		return code;
	}

	code -= ksCODE_SJIS_A_START - ksCODE_ASCII_END;
	codeShift += ksCODE_SJIS_A_START - ksCODE_ASCII_END;

	// �S�p�����i��P�u���b�N
	if( code <= ksCODE_SJIS_A_END - codeShift )
	{
		return code;
	}

	code -= ksCODE_SJIS_B_START - ksCODE_SJIS_A_END;
	codeShift += ksCODE_SJIS_B_START - ksCODE_SJIS_A_END;

	// �S�p�����i��Q�u���b�N
	if ( code <= ksCODE_SJIS_B_END - codeShift )
	{
		return code;
	}

	code -= ksCODE_SJIS_C_START - ksCODE_SJIS_B_END;
	codeShift += ksCODE_SJIS_C_START - ksCODE_SJIS_B_END;

	// �S�p�����i��R�u���b�N
	if ( code <= ksCODE_SJIS_C_END - codeShift )
	{
		return code;
	}

	return 0xFFFF;
}


//==========================================================================
//
//		�S�p�`�F�b�N
//
//==========================================================================
KsBool KsFontData::ismbblead( KsUInt8 c )
{
	if ( c < 0x81 ) return ksFALSE;
	if ( c < 0xA0 ) return ksTRUE;
	if ( c < 0xE0 ) return ksFALSE;
	if ( c < 0xFF ) return ksTRUE;

	return ksFALSE;
}

//==========================================================================
//
//		�����R�[�h�擾
//
//==========================================================================
KsUInt16 KsFontData::getCharCode( KsUInt8* pStr )
{
	if ( ismbblead( pStr[0] ) )
	{
		return (KsUInt16)( pStr[0]<<8 | pStr[1] );
	}

	return (KsUInt16)pStr[0];
}

//==========================================================================
//
//		�����R�[�h�擾
//
//==========================================================================
KsInt32 KsFontData::getCharCode( KsUInt8* pStr, KsUInt16* pCode )
{
	if ( ismbblead( pStr[0] ) )
	{
		*pCode = (KsUInt16)( pStr[0]<<8 | pStr[1] );

		return 2;
	}

	*pCode = pStr[0];

	return 1;
}