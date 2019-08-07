/************************************************************************************************/
/** 
 * @file		KsImagePNG.cpp
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
#include "KsImagePNG.h"
#include "./png/png.h"

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
KsBool KsIsFileExtensionPNG( const KsChar* pFileName )
{
	/* �g���q�� tga or TGA �����`�F�b�N���� */
	if( strstr( pFileName, ".png" ) ){
		return ksTRUE;
	}

	return ( strstr( pFileName, ".PNG" ) != 0 );
}
/************************************************************************************************/
/*
 * �f�[�^�ǂݍ��ݗp�R�[���o�b�N�֐�
 * @param	pPngStruct		PNG�\����
 * @param	pDataBuf		�f�[�^�p�o�b�t�@
 * @param	size			�ǂݍ��݃T�C�Y
 */
/************************************************************************************************/
static void KsReadPngCallback( png_struct* pPngStruct, png_byte* pDataBuf, png_size_t size )
{
	KsFileObject*	pFile = (KsFileObject*)png_get_io_ptr( pPngStruct );

	/* ��Ƀt�@�C����ǂݍ���ł��珈�� */
	pFile->read( pDataBuf, (KsInt32)size );
}

/************************************************************************************************/
//*
//* �p�b�N���ꂽ�f�[�^����ǂݍ��ނƂ�������̂�FILE*�ł͂���

	/************************************************************************/
	/*	�摜�̃J���[�^�C�v���i�[���� int�ւ̃|�C���^���w�肵�܂��B				*/
	/*	�J���[�^�C�v�̊e�r�b�g�͈ȉ��̂悤�ɒ�`����܂��B					*/
	/*																		*/
	/*	bit0	�p���b�g�̎g�p(1)/���g�p(0)									*/
	/*	bit1	�J���[(1)/���m�N��(0)										*/
	/*	bit2	���`���l���L��(1)/����(0)									*/
	/*																		*/
	/*	���ۂɂ̓J���[�^�C�v(���� / �F�[�x)�͈ȉ��̕�����					*/
	/*	0(�O���[�X�P�[�� / 1,2,4,8,16) 										*/
	/*	2(True�J���[ / 8,16) 												*/
	/*	3(�C���f�b�N�X�J���[ / 1,2,4,8)										*/
	/*	4(���`���l���̂���O���[�X�P�[�� / 8,16)							*/
	/*	6(���`���l���̂��� True�J���[ / 8,16)								*/
	/************************************************************************/

 //
//************************************************************************************************/
KsImage* KsLoadImagePNG( KsFileObject* pFile )
{
	/* PNG�̓ǂݍ��� */
	KsByte*				pDataBuf        = NULL;
	png_struct*			pPngStruct      = NULL;
    png_info*			pPngInfo        = NULL;
	png_info*			pPngInfoEnd     = NULL;
	png_bytep*			ppData          = NULL;
	KsByte*				pData           = NULL;
	KsImage*			pImage          = NULL;
    KsInt32			width           = 0;
	KsInt32			height          = 0;
	KsInt32			depth           = 0;
	KsInt32			colorType       = 0;
    KsInt32			filterType      = 0;
	KsInt32			size            = 0;

	/* �擪�Ɉړ� */
	pFile->seek( 0, ksSEEK_SET );

	/* PNG���� */
	pPngStruct = png_create_read_struct( PNG_LIBPNG_VER_STRING, NULL, NULL, NULL );
	if( !pPngStruct )
	{
		return NULL;
	}

	/* PNG��� */
	pPngInfo = png_create_info_struct( pPngStruct );
	if( !pPngInfo )
	{
		return NULL;
	}

	/* �X�^�b�N�ێ��W�����v */
	if( setjmp( png_jmpbuf( pPngStruct) ) )
	{
		return NULL;
	}

	/* �o�b�t�@�ɓǂݍ��ݏ������Z�b�g */
	png_set_read_fn( pPngStruct, (void*)pFile, (png_rw_ptr)KsReadPngCallback );

	/* ���ǂݍ��� */
	png_read_info( pPngStruct, pPngInfo );

	width      = png_get_image_width( pPngStruct, pPngInfo );
	height     = png_get_image_height( pPngStruct, pPngInfo );
	depth      = png_get_bit_depth( pPngStruct, pPngInfo );
	colorType  = png_get_color_type( pPngStruct, pPngInfo );
	filterType = ( colorType == PNG_COLOR_TYPE_RGB_ALPHA ) ? 4 : 3;

	/* �p���b�g���g�p���Ă��邩? */
	if( colorType == PNG_COLOR_TYPE_PALETTE )
	{
		filterType = 3;
		colorType  = PNG_COLOR_TYPE_RGB;

		/* �p���b�g����RGB�ɕϊ� */
		png_set_palette_to_rgb( pPngStruct );
	}

	/* �O���C�X�P�[���Ő[�x��8�ȉ��Ȃ�H */
	if( ( colorType == PNG_COLOR_TYPE_GRAY ) && ( depth < 8 ) ){
		/* 8bit�ɕϊ����� */
		png_set_gray_1_2_4_to_8( pPngStruct );
	}

	/* �O���C�X�P�[��(�A���t�@�Ŏg�p����̂ŃR�����g) */
	if( colorType == PNG_COLOR_TYPE_GRAY )
	{
		filterType  = 1;
		//colorType = PNG_COLOR_TYPE_RGB;
		//png_set_gray_to_rgb( pPngStruct );
	}

	/* �A���t�@ */
	if( colorType == PNG_COLOR_TYPE_GRAY_ALPHA )
	{
		filterType = 4;
		colorType  = PNG_COLOR_TYPE_RGB_ALPHA;

		png_set_gray_to_rgb( pPngStruct );
	}

	if( png_get_valid( pPngStruct, pPngInfo, PNG_INFO_tRNS ) )
	{
		filterType = 4;
		colorType  = PNG_COLOR_TYPE_RGB_ALPHA;
		
		png_set_tRNS_to_alpha( pPngStruct );
	}

	/* �^�C�v�`�F�b�N */
	if( ( colorType != PNG_COLOR_TYPE_RGB ) && ( colorType != PNG_COLOR_TYPE_RGB_ALPHA ) )
	{
		return NULL;
	}

	/* 8bit ���� 16bit */
	if( depth > 8 ){
		png_set_strip_16( pPngStruct );
	}

	/* �X�V���� */
	png_read_update_info( pPngStruct, pPngInfo );

	/* �������[�m�� */
	ppData = new png_byte* [ height ];

	for( KsInt32 i=0; i<height; i++ )
	{
		ppData[ i ] = new png_byte[ png_get_rowbytes( pPngStruct, pPngInfo ) ];
	}

	/* �C���[�W�擾 */
	png_read_image( pPngStruct, ppData );

	/* �ǂݍ��ݏI�� */
	png_read_end( pPngStruct, pPngInfo );

	/* �C���[�W�f�[�^�������� */
	pData = new KsByte[ width * height * 3 ];

	for( KsInt32 j=0; j<height; j++ )
	{
		memcpy( ( pData + j*width*3 ), ppData[ j ], width * 3 );
	}

	/* �C���[�W�𐶐�(���ۂ́A24bit�ȊO�̏ꍇ���ݒ肷��) */
	pImage = new KsImage();
	
	// RGB or RGBA
	pImage->m_pData  = pData;
	pImage->m_height = height;
	pImage->m_width  = width;
	pImage->m_format = ksIMAGE_R8G8B8;

	/* �㏈�� */
	for( i=0; i<height; i++ )
	{
		ksDELETEARRAY( ppData[ i ] );
	}
	ksDELETEARRAY( ppData );

	/* �j�� */
	png_destroy_read_struct( &pPngStruct, &pPngInfo, png_infopp_NULL );

	return pImage;
}



