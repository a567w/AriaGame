/************************************************************************************************/
/** 
 * @file		KsImageBMP.cpp
 * @brief		�C���[�W
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsImageBMP.h"
/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/* �g���q�̃`�F�b�N */
/************************************************************************************************/
KsBool KsIsFileExtensionBMP( const KsChar* pFileName )
{
	/* �g���q�� bmp or BMP �����`�F�b�N���� */
	if( strstr( pFileName, ".bmp" ) ){
		return ksTRUE;
	}

	return ( strstr( pFileName, ".BMP" ) != 0 );
}

#if 0
/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
KsImage* KsLoadImageBMP( KsFileObject* pFile )
{
	/* BMP�̓ǂݍ��� */
	KS_BITMAP_HEADER		header;
	KsImage*				pImage       = NULL;
	KsInt32*				pPaletteData = NULL;
	KsByte*					pData        = NULL;
	KsInt32				pitch        = 0;
	KsInt32				line         = 0;

	/* �擪�Ɉړ� */
	pFile->seek( 0, ksSEEK_SET );

	/* �w�b�_�[��ǂݍ��� */
	pFile->read( &header, sizeof(KS_BITMAP_HEADER) );

	/* BM���̃`�F�b�N */
	if( ( header.bmfh.bfType != ksMAKE_WORD( 'B', 'M' ) ) && ( header.bmfh.bfType != ksMAKE_WORD( 'M', 'B' ) ) )
	{
		//( "�r�b�g�}�b�v�摜�ł͂���܂���B\n" );
		return NULL;
	}

	/* ���k���������Ă���BMP�̓T�|�[�g�O */
	if( header.bmih.biCompression )
	{
		//( "�r�b�g�}�b�v�摜�ɃT�[�|�[�g�O�̈��k���������Ă��܂��B" );
		return NULL;
	}

	/* 4�o�C�g�o�E���_�����O���킹 */
	header.bmih.biSizeImage += ( 4 - ( header.bmih.biSizeImage & 3 ) );

	/* �p���b�g���g���Ă�����p���b�g��ǂݍ��� */
	KsInt32		pos          = pFile->tell();
	KsInt32		paletteSize  = ( header.bmfh.bfOffBits - pos ) / 4;

	if( paletteSize ){
		pPaletteData = new KsInt32[ paletteSize ];
		pFile->read( pPaletteData, paletteSize * sizeof(KsInt32) );
	}

	if( !header.bmih.biSizeImage ){
		header.bmih.biSizeImage = pFile->getSize() - header.bmfh.bfOffBits;
	}

	/* �C���[�W�f�[�^�ֈړ� */
	pFile->seek( 0, ksSEEK_SET );
	pFile->seek( header.bmfh.bfOffBits, ksSEEK_SET );

	if( header.bmih.biBitCount < 8 ){
		line  = ( 8 * header.bmih.biWidth ) + header.bmih.biBitCount;
		line += ( 8 - ( line & 7 ) );
		line  = line / 8;
	}
	else{
		line  = header.bmih.biWidth * ( header.bmih.biBitCount / 8 );
	}

	pitch = ( 4 - ( line & 3 ) );

	/* �f�[�^���擾 */
	pData = new KsByte[ header.bmih.biSizeImage ];
	pFile->read( pData, header.bmih.biSizeImage );

	/* �C���[�W���� */
	switch( header.bmih.biBitCount )
	{
		case 1:
		{
			//pImage = new KsImage( ksIMAGE_RGB24, header.width, header.height );
			break;
		}
		case 4:
		{
			//pImage = new KsImage( ksIMAGE_RGB24, header.width, header.height );
			break;
		}
		case 8:
		{
			//pImage = new KsImage( ksIMAGE_RGB24, header.width, header.height );
			break;
		}
		case 16:
		{
			//pImage = new KsImage( ksIMAGE_RGB24, header.width, header.height );
			break;
		}
		case 24:
		{
			pImage = new KsImage( ksIMAGE_A8R8G8B8, header.bmih.biWidth, header.bmih.biHeight );

			for( KsUInt32 i=0; i<header.bmih.biSizeImage/3; i++ )
			{
				if( ( pData[ i*3 ] == 0x00 ) && ( pData[ i*3+1 ] == 0xff ) && ( pData[ i*3+2 ] == 0x00 ) )
				{
					pImage->m_pData[ i*4+0 ] = 0;
					pImage->m_pData[ i*4+1 ] = 0;
					pImage->m_pData[ i*4+2 ] = 0;
					pImage->m_pData[ i*4+3 ] = 0;
				}
				else
				{
					pImage->m_pData[ i*4+0 ] = pData[ i*3+2 ];
					pImage->m_pData[ i*4+1 ] = pData[ i*3+1 ];
					pImage->m_pData[ i*4+2 ] = pData[ i*3+0 ];
					pImage->m_pData[ i*4+3 ] = 0xff;
				}
			}
			break;
		}

		default: break;
	};

	ksDELETEARRAY( pPaletteData );
	ksDELETEARRAY( pData );

	return pImage;
}
/************************************************************************************************/
/**
 * BMP�ǂݍ���
 * @param		pFileName		�t�@�C����
 * @return						�C���[�W�f�[�^
 *								���s�����Ƃ���NULL��Ԃ�
 */
/************************************************************************************************/
KsImage* KsLoadImageBMP( const KsChar* pFileName )
{
	KsFile		file;
	KsImage*	pImage;

	file.open( pFileName, ksREAD | ksBINARY );
	pImage = KsLoadImageBMP( &file );
	file.close();

	return pImage;
}
#endif


