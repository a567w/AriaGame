/************************************************************************************************/
/** 
 * @file		KsImageTGA.cpp
 * @brief		�C���[�W
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsImageTGA.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/*
 * �g���q�̃`�F�b�N
 */
/************************************************************************************************/
KsBool KsIsFileExtensionTGA( const KsChar* pFileName )
{
	/* �g���q�� tga or TGA �����`�F�b�N���� */
	if( strstr( pFileName, ".tga" ) ){
		return ksTRUE;
	}

	return ( strstr( pFileName, ".TGA" ) != 0 );
}

/************************************************************************************************/
/*
 * ���k��W�J����
 */
/************************************************************************************************/
static KsByte* KsLoadCommpressTGA( KsFileObject* pFile, KS_TGA_HEADER* pHeader )
{
	KsInt32		curByte = 0;
	KsInt32		depth   = 0;
	KsInt32		size    = 0;
	KsByte*		pData   = NULL;

	depth = pHeader->pixelDepth / 8;
	size  = pHeader->height * pHeader->width * depth;
	pData = new KsByte[ size ];

	while( curByte < size )
	{
		KsByte	chunkHeader = 0;

		pFile->read( &chunkHeader, sizeof(KsByte) );
		
		if( chunkHeader < 128 )
		{
			chunkHeader++;

			pFile->read( &pData[ curByte ], depth * chunkHeader );
			curByte += depth * chunkHeader;
		}
		else
		{
			chunkHeader -= 127;
			pFile->read( &pData[ curByte ], depth );

			for( KsInt32 i=0; i<chunkHeader; i++ )
			{
				for( KsInt32 j=0; j<depth; j++ ){
					pData[ curByte + j ] = pData[ curByte + j - depth ];
				}
				curByte += depth;
			}
		}
	}

	return pData;
}
#if 0
/************************************************************************************************/
/*
 * �p�b�N���ꂽ�f�[�^����ǂݍ��ނƂ�������̂�FILE*�ł͂���
 * KsFile���g�p����
 * pack->txd, pack->tga, txd, tga
 */
/************************************************************************************************/
KsImage* KsLoadImageTGA( KsFileObject* pFile )
{
	/* TGA�̓ǂݍ��� */
	KsByte*			pData  = NULL;
	KsImage*		pImage = NULL;
	KsInt32			depth  = 0;
	KsInt32			size   = 0;
	KS_TGA_HEADER	header;

	/* �擪�Ɉړ� */
	pFile->seek( 0, ksSEEK_SET );

	/* �w�b�_�[��ǂݍ��� */
	pFile->read( &header, sizeof(KS_TGA_HEADER) );

	if( header.idLength ){
		pFile->seek( header.idLength, ksSEEK_CUR );
	}

	/* �p���b�g�`�F�b�N */
	if( header.colorMapType != 0 ){
		pFile->seek( ( header.palletBits / 8 * header.palletMax ), ksSEEK_CUR );
	}

	depth = header.pixelDepth / 8;
	size  = header.height * header.width * depth;

	/* ���k���������Ă��邩�̃`�F�b�N */
	switch( header.imageType )
	{
		case 2:
		{
			/* �����k */
			pData = new KsByte[ size ];
		  	pFile->read( pData, size );
			/* RGB���Ȃ����ď㉺����ւ� */
			KsImageFlip_V( pData, header.width, header.height, header.pixelDepth );
			KsImageSwapRGB( pData, header.width, header.height, header.pixelDepth );
			break;
		}
		case 10:
		{
			/* ���k���� */
			pData = KsLoadCommpressTGA( pFile, &header ); 
			break;
		}
		default:
		{
			/* �G���[ */
			return NULL; 
		}
	}

	/* �J���[�[�x */
	switch( depth )
	{
		case 1:
		{
			break;
		}
		case 2:
		{
			// 16 bit image
			break;
		}
		case 3:
		{
			break;
		}
		case 4:
		{
			break;
		}
		default: break;
	}

	/* �C���[�W�𐶐�(���ۂ́A24bit�ȊO�̏ꍇ���ݒ肷��) */
	pImage = new KsImage();

	pImage->m_pData  = pData;
	pImage->m_height = header.height;
	pImage->m_width  = header.width;
	pImage->m_format = ksIMAGE_R8G8B8;

	return pImage;
}
#endif



