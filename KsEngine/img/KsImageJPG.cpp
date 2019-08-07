/************************************************************************************************/
/** 
 * @file		KsImageJPG.cpp
 * @brief		
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsImageJPG.h"
#include "./jpeg/jpeglib.h"
#include "./jpeg/jinclude.h"
#include "./jpeg/jerror.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
typedef struct
{
  struct jpeg_source_mgr	pub;
  KsFileObject*				infile;
  JOCTET*					buffer;
}my_source_mgr;

/************************************************************************************************/
/*
 * ������
 */
/************************************************************************************************/
void KS_init_source( j_decompress_ptr cinfo )
{
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
boolean KS_fill_input_buffer( j_decompress_ptr cinfo )
{
	return TRUE;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KS_skip_input_data( j_decompress_ptr cinfo, long num_bytes )
{
	my_source_mgr*	src = (my_source_mgr*) cinfo->src;

	if( num_bytes > 0 )
	{
		src->pub.next_input_byte += (size_t) num_bytes;
		src->pub.bytes_in_buffer -= (size_t) num_bytes;
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KS_term_source( j_decompress_ptr cinfo )
{
	ksDELETE( cinfo->src );
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KS_jpeg_stdio_src( j_decompress_ptr cinfo, KsFileObject* infile )
{
	/* �ʓ|�Ȃ̂ň�C�ɓǂݍ��� */
	KsByte*		pBuffer = new KsByte[ infile->getSize() ];
	infile->read( pBuffer, infile->getSize() );

	jpeg_source_mgr*   pJpgMgr = new jpeg_source_mgr;
	pJpgMgr->bytes_in_buffer   = infile->getSize();
	pJpgMgr->next_input_byte   = (JOCTET*)pBuffer;
	pJpgMgr->init_source       = KS_init_source;
	pJpgMgr->fill_input_buffer = KS_fill_input_buffer;
	pJpgMgr->skip_input_data   = KS_skip_input_data;
	pJpgMgr->term_source       = KS_term_source;
	pJpgMgr->resync_to_restart = jpeg_resync_to_restart;
	cinfo->src                 = pJpgMgr;
}
/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KsBool KsIsFileExtensionJPG( const KsChar* pFileName )
{
	/* �g���q�� jpg or jpeg or JPG or JPEG �����`�F�b�N���� */
	if( strstr( pFileName, ".jpg" ) ){
		return ksTRUE;
	}

	if( strstr( pFileName, ".jpeg" ) ){
		return ksTRUE;
	}

	if( strstr( pFileName, ".JPG" ) ){
		return ksTRUE;
	}

	return ( strstr( pFileName, ".JPEG" ) != 0 );
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsImage* KsLoadImageJPEG( FILE* pFile )
{
	struct jpeg_decompress_struct	jpegStruct;
	struct jpeg_error_mgr			jpegError;
	KsInt32						height      = 0;
	KsInt32						width       = 0;
	KsInt32						rowStride   = 0;
	KsInt32						offset      = 0;
	KsBool							hasAlpha    = ksFALSE;	/* �A���t�@�l�̏�񂪂��邩�ǂ����H */
	KsBool							isGreyscale = ksFALSE; /* �O���C�X�P�[���̃f�[�^���ǂ����H */
	KsByte*							pData       = NULL;
	KsByte**						ppRow       = NULL;
	KsImage*						pImage      = NULL;

	/*  JPEG�ǂݍ��� */
	jpegStruct.err = jpeg_std_error( &jpegError );
	
	/* �\���̂̐��� */
	jpeg_create_decompress( &jpegStruct );
	
	/* ����֐����g�p���� */
	jpeg_stdio_src( &jpegStruct, pFile );
	
	/* JPEG�w�b�_���̓ǂݍ��� */
	jpeg_read_header( &jpegStruct, ksTRUE );
	
	/* �𓀂̊J�n */
	jpeg_start_decompress( &jpegStruct );

    /* �s�o�b�t�@�̗̈�ݒ� */
    rowStride = jpegStruct.output_width * jpegStruct.output_components;

	/* �C���[�W���� */
	width  = jpegStruct.output_width;
	height = jpegStruct.output_height;

	/* �O���[�X�P�[���H */
	if( jpegStruct.jpeg_color_space == JCS_GRAYSCALE ){
		isGreyscale = ksTRUE;
	}

	/* �f�[�^�̈�m�� */
	pData = new KsByte[ rowStride * height ];

	if( !pData ){
		/* �������[�m�ۃG���[ */
		jpeg_finish_decompress( &jpegStruct );
		jpeg_destroy_decompress( &jpegStruct );
		return NULL;
	}

	ppRow = new KsByte*[ height ];

	if( !ppRow ){
		/* �������[�m�ۃG���[ */
		jpeg_finish_decompress( &jpegStruct );
		jpeg_destroy_decompress( &jpegStruct );
		ksDELETEARRAY( pData );
		return NULL;
	}

	/* �f�[�^�̓ǂݎ��p�ɃZ�b�g */
	for( KsInt32 i = 0; i < height; i++ ){
		ppRow[ i ] = &pData[ i * rowStride ];
	}

	/* �f�[�^�ǂݍ��ݏ��� */
	while( jpegStruct.output_scanline < jpegStruct.output_height ){
		offset += jpeg_read_scanlines( &jpegStruct, &ppRow[ offset ], jpegStruct.output_height - offset );
	}

	/* �㏈�� */
	jpeg_finish_decompress( &jpegStruct );
	jpeg_destroy_decompress( &jpegStruct );

	ksDELETEARRAY( ppRow );

	/* �C���[�W�𐶐� */
	pImage = new KsImage();

	pImage->m_pData  = pData;
	pImage->m_height = height;
	pImage->m_width  = width;
	pImage->m_format = ksIMAGE_R8G8B8;

	return pImage;
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsImage* KsLoadImageJPEG( KsFileObject* pFile )
{
	struct jpeg_decompress_struct	jpegStruct;
	struct jpeg_error_mgr			jpegError;
	KsInt32						height      = 0;
	KsInt32						width       = 0;
	KsInt32						rowStride   = 0;
	KsInt32						offset      = 0;
	KsBool							hasAlpha    = ksFALSE;	/* �A���t�@�l�̏�񂪂��邩�ǂ����H */
	KsBool							isGreyscale = ksFALSE; /* �O���C�X�P�[���̃f�[�^���ǂ����H */
	KsByte*							pData       = NULL;
	KsByte**						ppRow       = NULL;
	KsImage*						pImage      = NULL;

	/*  JPEG�ǂݍ��� */
	jpegStruct.err = jpeg_std_error( &jpegError );
	
	/* �\���̂̐��� */
	jpeg_create_decompress( &jpegStruct );
	
	/* ����֐����g�p����(���C�u�����ł́AFILE���炵���ǂݍ��߂Ȃ�) */
	KS_jpeg_stdio_src( &jpegStruct, pFile );
	
	/* JPEG�w�b�_���̓ǂݍ��� */
	jpeg_read_header( &jpegStruct, ksTRUE );
	
	/* �𓀂̊J�n */
	jpeg_start_decompress( &jpegStruct );

    /* �s�o�b�t�@�̗̈�ݒ� */
    rowStride = jpegStruct.output_width * jpegStruct.output_components;

	/* �C���[�W���� */
	width  = jpegStruct.output_width;
	height = jpegStruct.output_height;

	/* �O���[�X�P�[���H */
	if( jpegStruct.jpeg_color_space == JCS_GRAYSCALE ){
		isGreyscale = ksTRUE;
	}

	/* �f�[�^�̈�m�� */
	pData = new KsByte[ rowStride * height ];

	if( !pData ){
		/* �������[�m�ۃG���[ */
		jpeg_finish_decompress( &jpegStruct );
		jpeg_destroy_decompress( &jpegStruct );
		return NULL;
	}

	ppRow = new KsByte*[ height ];

	if( !ppRow ){
		/* �������[�m�ۃG���[ */
		jpeg_finish_decompress( &jpegStruct );
		jpeg_destroy_decompress( &jpegStruct );
		ksDELETEARRAY( pData );
		return NULL;
	}

	/* �f�[�^�̓ǂݎ��p�ɃZ�b�g */
	for( KsInt32 i = 0; i < height; i++ ){
		ppRow[ i ] = &pData[ i * rowStride ];
	}

	/* �f�[�^�ǂݍ��ݏ��� */
	while( jpegStruct.output_scanline < jpegStruct.output_height ){
		offset += jpeg_read_scanlines( &jpegStruct, &ppRow[ offset ], jpegStruct.output_height - offset );
	}

	/* �㏈�� */
	jpeg_finish_decompress( &jpegStruct );
	jpeg_destroy_decompress( &jpegStruct );

	ksDELETEARRAY( ppRow );

	/* �C���[�W�𐶐�(���ۂ́A24bit�ȊO�̏ꍇ���ݒ肷��) */
	pImage = new KsImage();

	pImage->m_pData  = pData;
	pImage->m_height = height;
	pImage->m_width  = width;
	pImage->m_format = ksIMAGE_R8G8B8;

	return pImage;
}

