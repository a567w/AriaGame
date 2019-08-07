/*************************************************************************************************/
/**
 * @file	KsImage.cpp
 * @brief	�C���[�W
 * @author	Tsukasa Kato
 * @date	2005/01/25
 * @version	1.0.0
 */
/*************************************************************************************************/

/*===============================================================================================*/
/*                                 << �C���N���[�h >>                                             */
/*===============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"
#include "KsImage.h"

/*===============================================================================================*/
/*                                     << ��` >>                                                */
/*===============================================================================================*/

/*===============================================================================================*/
/*                                     << �錾 >>                                                */
/*===============================================================================================*/

/*************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/*************************************************************************************************/
KsImage::KsImage()
	: m_imageFormat( ksIMAGE_UNKNOWN )
	, m_pixelFormat( ksPIXEL_UNKNOWN )
	, m_flags( 0 )
	, m_width( 0 )
	, m_height( 0 )
	, m_pData( 0 )
	, m_pClut( 0 )
{
}
/*************************************************************************************************/
/*
 * �R�s�[�R���X�g���N�^
 * @param	pImage				�C���[�W�̃|�C���^
 */
/*************************************************************************************************/
KsImage::KsImage( KsImage* pImage )
{
	KsInt32			size = 0;
	KsInt32			num  = 0;

	m_flags       = pImage->m_flags;
	m_width       = pImage->m_width;
	m_height      = pImage->m_height;
	m_pixelFormat = pImage->m_pixelFormat;
	m_imageFormat = pImage->m_imageFormat;

	if( pImage->m_pData )
	{
		// �m��
		switch( m_imageFormat )
		{
			case ksIMAGE_A1R5G5B5:
			case ksIMAGE_A4R4G4B4:
			case ksIMAGE_R5G6B5:
			{
				size = m_width * m_height * 2;
				break;
			}
			case ksIMAGE_A8R8G8B8:
			{
				size = m_width * m_height * 4;
				break;
			}
			case ksIMAGE_INDEX4:
			{
				size = m_width * m_height / 2;
				num  = 0x0f;
				break;
			}
			case ksIMAGE_INDEX8:
			{
				size = m_width * m_height;
				num  = 0xff;
				break;
			}
			default: break;
		}
		m_pData = new KsUInt8[ size ];
		memcpy( m_pData, pImage->m_pData, size );
	}

	if( pImage->m_pClut )
	{
		switch( m_pixelFormat )
		{
			case ksPIXEL_A1R5G5B5:
			case ksPIXEL_A4R4G4B4:
			case ksPIXEL_R5G6B5:
			{
				size = num * 2;
				break;
			}
			case ksPIXEL_A8R8G8B8:
			{
				size = num * 4;
				break;
			}
			default: break;
		}
		m_pClut = new KsUInt8[ size ];
		memcpy( m_pClut, pImage->m_pClut, size );
	}
}
/*************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/*************************************************************************************************/
KsImage::~KsImage()
{
	destroy();
}

/*************************************************************************************************/
/*
 * �C���[�W���N���[������
 * @return						�N���[�������C���[�W�ł��[�̃|�C���^
 */
/*************************************************************************************************/
KsImage* KsImage::clone()
{
	return new KsImage( this );
}

/************************************************************************************************/
/*
 * �C���[�W�𐶐�����
 * @param	format				�t�H�[�}�b�g
 * @param	width				��
 * @param	height				����
 * @retval	ksTRUE				��������
 * @retval	ksFALSE				�������s
 */
/************************************************************************************************/
KsBool KsImage::create( ksPIXEL_FORMAT format, KsInt32 width, KsInt32 height )
{
	KsInt32	size = width * height;

	m_pixelFormat = format;
	m_width       = width;
	m_height      = height;

	switch( format )
	{
		case ksPIXEL_X1R5G5B5:
		case ksPIXEL_A1R5G5B5:
		case ksPIXEL_R5G6B5:
		{
			size *= 2;
			break;
		}
		case ksPIXEL_X8R8G8B8:
		case ksPIXEL_A8R8G8B8:
		{
			size *= 4;
			break;
		}
		default: break;
	}

	m_pData = new KsByte[ size ];

	if( !m_pData ){
		return ksFALSE;
	}

	return ksTRUE;
}

/************************************************************************************************/
/*
 * �C���[�W��j������
 */
/************************************************************************************************/
void KsImage::destroy()
{
	ksDELETEARRAY( m_pClut );
	ksDELETEARRAY( m_pData );
}

