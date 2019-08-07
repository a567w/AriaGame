/************************************************************************************************/
/** 
 * @file		KsRenderSystemGL.cpp
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
#include "KsRenderSystemGL.h"
#include <GL/gl.h>

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
KsRenderSystemGL::KsRenderSystemGL()
{
	m_useStencilBuffer = ksFALSE;
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsRenderSystemGL::KsRenderSystemGL( HWND hWnd )
{
	initialize( hWnd );
}
/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsRenderSystemGL::~KsRenderSystemGL()
{
	terminate();
}
/************************************************************************************************/
/*
 * ������
 */
/************************************************************************************************/
KsBool KsRenderSystemGL::initialize( HWND hWnd )
{
	//m_useStencilBuffer = useStencilBuffer;	
	m_hWnd = hWnd;

	/* �f�o�C�X�R���e�L�X�g���擾 */
	if( !( m_hDC = ::GetDC( hWnd ) ) ){
		return ksFALSE;
	}

	/* �s�N�Z���t�H�[�}�b�g���Z�b�g���� */
	if( !setupPixelFormat() ){
		return ksFALSE;
	}
	
	/* �����_�����O�R���e�L�X�g�𐶐� */
	if( !(m_hRC = wglCreateContext( m_hDC ) ) ){
		return ksFALSE;
	}
	/* �����_�����O�R���e�L�X�g���A�N�e�B�u�ɂ��� */
	if( !wglMakeCurrent( m_hDC, m_hRC ) ){
		return ksFALSE;
	}

	/* �g�p�\�Ȃ�GL�̊g���@�\���Z�b�g���� */
	//SetExtensionGL();

	/* ���������_�����O�X�e�[�^�X���Z�b�g���� */
	//InitStatRender();

	return ksTRUE;
}
/************************************************************************************************/
/*
 * �㏈��
 */
/************************************************************************************************/
KsBool KsRenderSystemGL::terminate()
{
	//deleteAllTextures();

	/* �J������ */
	if( m_hRC )
	{
		if( !wglMakeCurrent( NULL, NULL ) ){
			return ksFALSE;
		}

		if( !wglDeleteContext( m_hRC ) ){
			return ksFALSE;
		}

		m_hRC = NULL;
	}

	if( m_hDC ){
		ReleaseDC( m_hWnd, m_hDC );
		m_hDC = NULL;
	}

	return ksTRUE;
}
/************************************************************************************************/
/*
 * �s�N�Z���t�H�[�}�b�g��������
 */
/************************************************************************************************/
KsBool KsRenderSystemGL::setupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof( PIXELFORMATDESCRIPTOR ),		/* �\���̂̃T�C�Y					*/
		1,										/* �\���̂̃o�[�W����					*/
		PFD_DRAW_TO_WINDOW |					/* �v���p�e�B�̃t���O					*/
		PFD_SUPPORT_OPENGL |					/* OpenGL�T�|�[�g					*/
		PFD_DOUBLEBUFFER,						/* �_�u���o�b�t�@���g�p				*/
		PFD_TYPE_RGBA,							/* RGBA�s�N�Z���t�H�[�}�b�g			*/
		16,										/* 16-bit�J���[�o�b�t�@				*/
		0, 0, 0, 0, 0, 0,						/* �e�r�b�g�����`					*/
		0,										/* �A���t�@�o�b�t�@					*/
		0,										/* �r�b�g�����`					*/
		0,										/* �A�L���[�����[�V�����o�b�t�@		*/
		0, 0, 0, 0,								/* �r�b�g�����`					*/
		16,										/* 16-bit�[�x�o�b�t�@				*/
		m_useStencilBuffer ? ksTRUE : ksFALSE,	/* �X�e���V���o�b�t�@					*/
		0,										/* AUX�o�b�t�@						*/
		PFD_MAIN_PLANE,							/* ���C�����C���[�^�C�v				*/
		0, 0, 0, 0								/* ��`�s�K�v						*/
	};

	KsInt32 pixelFormat;

	if( !( pixelFormat = ::ChoosePixelFormat( m_hDC, &pfd ) ) ){
		return ksFALSE;
	}
	
	// ���s������X�e���V���o�b�t�@�Ȃ��ł�����x�`�F�b�N����
	if( !( pixelFormat = ChoosePixelFormat( m_hDC, &pfd ) ) )
	{
		if( !m_useStencilBuffer ){
			return FALSE;
		}
		else{
			m_useStencilBuffer = ksFALSE;
			pfd.cStencilBits   = ksFALSE;
			if( !( pixelFormat = ::ChoosePixelFormat( m_hDC, &pfd ) ) ){
				return ksFALSE;
			}
		}
	}

    return ::SetPixelFormat( m_hDC, pixelFormat, &pfd );
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemGL::beginScene( KsUInt32 flags, KsColor color, KsReal depth, KsUInt32 stencil )
{
	KsUInt32	mask = 0;

	wglMakeCurrent( m_hDC, m_hRC );

	if( flags & ksCLEAR_FLAG_COLOR ){
		glClearColor( (KsReal)color.getRed()/255.0f, (KsReal)color.getGreen()/255.0f, (KsReal)color.getBlue()/255.0f, (KsReal)color.getAlpha() );
		mask |= GL_COLOR_BUFFER_BIT;
	}
	if( flags & ksCLEAR_FLAG_DEPTH ){
		// �����_�[�X�e�[�g�`�F�b�N����ZWrite
		//if( ){
		//	glDepthMask( GL_TRUE );
		//}

		glClearDepth( depth );
		mask |= GL_DEPTH_BUFFER_BIT;
	}
	if( flags & ksCLEAR_FLAG_STENCIL ){
		//glClearStencil( stencil );
		mask |= GL_STENCIL_BUFFER_BIT;
	}
	//if( flags & ){
	//	glClearAccum( 54.0f/255.0f, 63.0f/255.0f, 75.0f/255.0f, 0.0f );
	//	mask |= GL_ACCUM_BUFFER_BIT;
	//}

#if 0
        if (!mDepthWrite)
        {
            glDepthMask( GL_FALSE );
        }
        if (colourMask)
        {
            glColorMask(mColourWrite[0], mColourWrite[1], mColourWrite[2], mColourWrite[3]);
        }

#endif

	/* �N���A */
	glClear( mask );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemGL::endScene()
{
}

void KsRenderSystemGL::swapBuffer()
{
	::SwapBuffers( m_hDC );
}


#if 0
#include "StTexturePSP.h"
#include "StTextureManager.h"
#include "StFileBufferPSP.h"
#include "StFileSystemPSP.h"

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void StRenderSystemPSP::setFog( StReal zs, StReal ze, StUInt32 color )
{
	/* �t�H�O���Z�b�g���� */
	sceGuFog( zs, ze, color );
	sceGuEnable( SCEGU_FOG );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void StRenderSystemPSP::createRenderBuffer( StInt32 format )
{
	if( format == SCEGU_PF8888 ){
		/* 32bit mode */
		/* �`��o�b�t�@�̐ݒ� */
		sceGuDrawBuffer( format, SCEGU_VRAM_BP32_0, SCEGU_VRAM_WIDTH );
		/* �\���o�b�t�@�̐ݒ� */
		sceGuDispBuffer( SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT, SCEGU_VRAM_BP32_1, SCEGU_VRAM_WIDTH );
		/* Z�o�b�t�@�̐ݒ� */
		sceGuDepthBuffer( SCEGU_VRAM_BP32_2, SCEGU_VRAM_WIDTH );
	}
	else{
		/* 16bit mode */
		/* �`��o�b�t�@�̐ݒ� */
		sceGuDrawBuffer( format, SCEGU_VRAM_BP_0, SCEGU_VRAM_WIDTH );
		/* �\���o�b�t�@�̐ݒ� */
		sceGuDispBuffer( SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT, SCEGU_VRAM_BP_1, SCEGU_VRAM_WIDTH );
		/* Z�o�b�t�@�̐ݒ� */
		sceGuDepthBuffer( SCEGU_VRAM_BP_2, SCEGU_VRAM_WIDTH );
	}
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
StRenderSystemPSP::StRenderSystemPSP()
{
	m_pCurrentTexture = NULL;
}
/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
StRenderSystemPSP::~StRenderSystemPSP()
{
	/* �㏈������Ă��Ȃ�������㏈������悤�ɂ��� */
	//terminate();
}

/************************************************************************************************/
/*
 * ���C����`��(2D)
 * @param		x					X���W
 * @param		y					Y���W
 * @param		color				�F
 */
/************************************************************************************************/
void StRenderSystemPSP::drawLine( StInt16 x0, StInt16 y0, StInt16 x1, StInt16 y1, StUInt32 color )
{
	static StInt32	format = ( SCEGU_COLOR_PF8888 | SCEGU_VERTEX_SHORT | SCEGU_THROUGH );

	ST_PRIM_LINE2D*	pVertex = (ST_PRIM_LINE2D*)sceGuGetMemory( sizeof( ST_PRIM_LINE2D ) * 2 );

	pVertex[ 0 ].color = color;
	pVertex[ 0 ].x     = x0;
	pVertex[ 0 ].y     = y0;
	pVertex[ 0 ].z     = 0;

	pVertex[ 1 ].color = color;
	pVertex[ 1 ].x     = x1;
	pVertex[ 1 ].y     = y1;
	pVertex[ 1 ].z     = 0;

	sceGuDrawArray( SCEGU_PRIM_LINES, format, 2, 0, pVertex );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void StRenderSystemPSP::drawRect( StInt16 x, StInt16 y, StInt16 w, StInt16 h, StUInt32 color )
{
	static StInt32	format = ( SCEGU_COLOR_PF8888 | SCEGU_VERTEX_SHORT | SCEGU_THROUGH );

	ST_PRIM_RECT2D*	pVertex = (ST_PRIM_RECT2D*)sceGuGetMemory( sizeof( ST_PRIM_RECT2D ) * 2 );

	pVertex[ 0 ].color = color;
	pVertex[ 0 ].x     = x;
	pVertex[ 0 ].y     = y;
	pVertex[ 0 ].z     = 0;

	pVertex[ 1 ].color = color;
	pVertex[ 1 ].x     = x + w;
	pVertex[ 1 ].y     = y + h;
	pVertex[ 1 ].z     = 0;

	setTexture( 0, NULL );

	sceGuDrawArray( SCEGU_PRIM_RECTANGLES, format, 2, 0, pVertex );
}
/************************************************************************************************/
/*
 * �Z�`��`��
 * @param		x					X���W
 * @param		y					Y���W
 * @param		w					��
 * @param		h					����
 * @param		tx					�e�N�X�`����X���W
 * @param		ty					�e�N�X�`����Y���W
 * @param		tw					�e�N�X�`���̕�
 * @param		th					�e�N�X�`���̍���
 * @param		color				�F
 * @param		pTexture			�e�N�X�`��
 */
/************************************************************************************************/
void StRenderSystemPSP::drawRectEx( StInt16 x, StInt16 y, StInt16 w, StInt16 h, StUInt16 tx, StUInt16 ty, StUInt16 tw, StUInt16 th, StUInt32 color, StTexture* pTexture )
{
	static StInt32	format = ( SCEGU_TEXTURE_USHORT | SCEGU_COLOR_PF8888 | SCEGU_VERTEX_SHORT | SCEGU_THROUGH );

	ST_SPRITE_PRIM*	pVertex = (ST_SPRITE_PRIM*)sceGuGetMemory( sizeof( ST_SPRITE_PRIM ) * 2 );

	pVertex[ 0 ].color = color;
	pVertex[ 0 ].x     = x;
	pVertex[ 0 ].y     = y;
	pVertex[ 0 ].z     = 0;
	pVertex[ 0 ].u     = tx;
	pVertex[ 0 ].v     = ty;

	pVertex[ 1 ].color = color;
	pVertex[ 1 ].x     = x + w;
	pVertex[ 1 ].y     = y + h;
	pVertex[ 1 ].z     = 0;
	pVertex[ 1 ].u     = tx + tw;
	pVertex[ 1 ].v     = ty + th;

	setTexture( 0, pTexture );

	sceGuDrawArray( SCEGU_PRIM_RECTANGLES, format, 2, 0, pVertex );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void StRenderSystemPSP::drawSprite( ST_SPRITE_PRIM* pSpritePrim )
{
	static StInt32	format = ( SCEGU_TEXTURE_USHORT | SCEGU_COLOR_PF8888 | SCEGU_VERTEX_SHORT | SCEGU_THROUGH );

	// �L���b�V����������
	sceKernelDcacheWritebackAll();


	//sceGuDrawArray( SCEGU_PRIM_TRIANGLE_STRIP, format, 4, 0, pVertex );
	sceGuDrawArray( SCEGU_PRIM_TRIANGLE_STRIP, format, 4, 0, pSpritePrim );
	//sceGuDrawArray( SCEGU_PRIM_RECTANGLES, format, 2, 0, &pVertex[ 0 ] );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void StRenderSystemPSP::auto2DMode()
{
	ScePspFVector3	vec = { 0.614497f, 0.691714f, 0.379372f };

	StViewport		viewport;
	viewport.set( 0, 0, SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT, 50000, 10000 );
	//viewport.set( 0, 0, SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT, 65535, 0 );

	setViewport( &viewport );

	sceGuBlendFunc( SCEGU_ADD, SCEGU_SRC_ALPHA, SCEGU_ONE_MINUS_SRC_ALPHA, 0, 0 );
	sceGuEnable( SCEGU_BLEND );
	sceGuAlphaFunc( SCEGU_GREATER, 0x00, 0xff );
	sceGuDisable( SCEGU_ALPHA_TEST );
	sceGuDepthFunc( SCEGU_GEQUAL );
	sceGuEnable( SCEGU_DEPTH_TEST );
	sceGuFrontFace( SCEGU_CW );


	sceGuDisable( SCEGU_TEXTURE );
	sceGuShadeModel( SCEGU_SMOOTH );

	sceGuEnable( SCEGU_CLIP_PLANE );

	sceGuLightColor( 0, SCEGU_DIFFUSE, 0xffffffff );
	sceGuLight( 0, SCEGU_LIGHT_DIRECTION, SCEGU_DIFFUSE, &vec );
	sceGuEnable( SCEGU_LIGHT0 );
	sceGuEnable( SCEGU_LIGHTING );
	//sceGuDisable(SCEGU_LIGHT0);
	//sceGuDisable(SCEGU_LIGHTING);
	sceGuDisable( SCEGU_FOG );
	sceGuAmbient( 0xffdddddd );

	sceGuTexFunc(SCEGU_TEX_MODULATE, SCEGU_RGBA);
	sceGuTexFilter(SCEGU_LINEAR_MIPMAP_LINEAR, SCEGU_NEAREST);
	sceGuTexWrap(SCEGU_REPEAT, SCEGU_REPEAT);
	sceGuEnable(SCEGU_TEXTURE);

	/* ���ۂ̓J�����^�X�N���Ƃɐݒ肵���ق������� */
	/* 2D���[�h�Ȃ̂Ő��ˉe */
	sceGumMatrixMode( SCEGU_MATRIX_PROJECTION );
	//sceGumOrtho( 0, SCEGU_SCR_WIDTH, 0, SCEGU_SCR_HEIGHT, -1.0f, 1.0f );
	sceGumPerspective( SCEGU_RAD(45.0f), SCEGU_SCR_ASPECT, 1.000000f, 100.000000f );

	sceGumMatrixMode( SCEGU_MATRIX_WORLD );

	/* �`��I���ݒ� */
	sceGuFinish();
	
	/* �`��I���҂� */
	sceGuSync( SCEGU_SYNC_FINISH, SCEGU_SYNC_WAIT );

	/* ����VBLANK �J�n�܂� WAIT */
	sceDisplayWaitVblankCB();
}



/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void StRenderSystemPSP::beginScene()
{
	sceGuStart( SCEGU_IMMEDIATE, m_dispList, sizeof(m_dispList) );
#if 1
	if( m_clearFlags )
	{
		StInt32		flags = SCEGU_CLEAR_FAST;

		if( m_clearFlags & stCLEAR_FLAG_COLOR ){
			sceGuClearColor( m_clearColor.m_color );
			flags |= SCEGU_CLEAR_COLOR;
		}

		if( m_clearFlags & stCLEAR_FLAG_DEPTH ){
			sceGuClearDepth( m_clearDepth );
			flags |= SCEGU_CLEAR_DEPTH;
		}

		if( m_clearFlags & stCLEAR_FLAG_STENCIL ){
			sceGuClearStencil( m_clearStencil );
			flags |= SCEGU_CLEAR_STENCIL;
		}
		sceGuClear( flags );
	}
#else
	/* �Y��ő������ǁASCEGU_CLEAR_ALL���,168byte�����������[��H�� */
	sceGuClear( SCEGU_CLEAR_FASTALL );
#endif

}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void StRenderSystemPSP::endScene()
{
	sceGuFinish();
	sceGuSync( SCEGU_SYNC_FINISH, SCEGU_SYNC_WAIT );
}

/************************************************************************************************/
/*
 * �`��o�b�t�@�ƕ\���o�b�t�@�����ւ�
 */
/************************************************************************************************/
void StRenderSystemPSP::swapBuffer()
{
	sceGuSwapBuffers();
}

/************************************************************************************************/
/*
 * �r���[�|�[�g���Z�b�g����
 * @param		pViewport			�r���[�|�[�g�ݒ�
 */
/************************************************************************************************/
void StRenderSystemPSP::setViewport( const StViewport* pViewport )
{
	/* �r���[�|�[�g���Z�b�g���� */
	sceGuViewport( stRENDER_VIEWPORT_OFFSET_X + pViewport->m_x, stRENDER_VIEWPORT_OFFSET_Y + pViewport->m_y, pViewport->m_w, pViewport->m_h );
	sceGuDepthRange( pViewport->m_near, pViewport->m_far );

	/* �̈���Z�b�g���� */
	sceGuScissor( 0, 0, pViewport->m_w, pViewport->m_h );
	sceGuEnable( SCEGU_SCISSOR_TEST );
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void StRenderSystemPSP::setViewOffset( StInt32 offsetX, StInt32 offsetY )
{
	sceGuOffset( SCEGU_SCR_OFFSETX - offsetX, SCEGU_SCR_OFFSETY - offsetY );
}

/************************************************************************************************/
/*
 * �e�N�X�`���𐶐�����
 * @param		pFileName			�t�@�C����
 * @param		flags				�����t���O
 * @return							�e�N�X�`���̃|�C���^
 */
/************************************************************************************************/
StTexture* StRenderSystemPSP::createTexture( const StChar* pFileName, StUInt32 flags )
{
	// FileSystem ����ǂݍ��݂悤�ɕύX����
	StTextureManager*	pTextureManager;
	StTexture*			pTexture;
	StTexturePSP*		pTexturePSP;

	/* �e�N�X�`���}�l�[�W���̂��猟������ */
	pTextureManager = StTextureManager::instance();

	/* �������Č���������Q�ƃJ�E���g���A�b�v������ */
	pTexture = pTextureManager->findRefInc( pFileName );

	if( pTexture ){
		return pTexture;
	}

	/* PSP�p�e�N�X�`���𐶐� */
	pTexturePSP = new StTexturePSP( pFileName, flags );

	//StAssert( pTexture != NULL, "TexturePSP pointer null !!" );

	/* �e�N�X�`���}�l�[�W���ɓo�^ */
	pTextureManager->add( pTexturePSP );

	return pTexturePSP;
}
/************************************************************************************************/
/*
 * �C���[�W�f�[�^����e�N�X�`���𐶐�����
 * @param		pImage				�C���[�W�f�[�^�̃|�C���^
 * @param		flags				�����t���O
 * @return							�e�N�X�`���̃|�C���^
 */
/************************************************************************************************/
StTexture* StRenderSystemPSP::createTexture( StImage* pImage, StUInt32 flags )
{

	return NULL;
}
/************************************************************************************************/
/*
 * �e�N�X�`�����Z�b�g����
 * @param		statge				�e�N�X�`���X�e�[�W
 * @param		pTexture			�e�N�X�`��
 */
/************************************************************************************************/
void StRenderSystemPSP::setTexture( StUInt32 stage, StTexture* pTexture )
{
	//if( stage ){ return; }

	/* �e�N�X�`�������x���Z�b�g���Ȃ��悤�ɂ��� */
	if( m_pCurrentTexture == pTexture ){
		return;
	}
	else{
		m_pCurrentTexture = pTexture;
	}

	/* �e�N�X�`�����Z�b�g���� */
	if( pTexture ){
		/* �e�N�X�`���̃L���b�V�����N���A */
		sceGuTexFlush();

		/* �e�N�X�`����L���ɂ��� */
		sceGuEnable( SCEGU_TEXTURE );

		/* ���ۂ̓t���O�łǂ��炩���`�F�b�N���� */
		//sceGimPictureActivate( ((StTexturePSP*)pTexture)->m_pPicture );
		((StTexturePSP*)pTexture)->active();
		//(static_cast<StTexturePSP*>( pTexture ))->active();
	}
	else{
		/* �e�N�X�`���𖳌��ɂ��� */
		sceGuDisable( SCEGU_TEXTURE );
	}
}

/************************************************************************************************/
/*
 * �e�N�X�`���X�e�[�g���Z�b�g����
 * @param		statge				�e�N�X�`���X�e�[�W
 * @param		state				�Z�b�g����X�e�[�^�X�̎��
 * @param		value				�Z�b�g����l
 */
/************************************************************************************************/
void StRenderSystemPSP::setTextureState( StUInt32 stage, stTEXTURE_STATE_TYPE state, StUInt32 value )
{
	//if( stage ){ return; }

	static StInt32		texFunc[]      = {	SCEGU_TEX_MODULATE,
											SCEGU_TEX_DECAL,
											SCEGU_TEX_BLEND,
											SCEGU_TEX_REPLACE,
											SCEGU_TEX_ADD };

	static StInt32		warpFilter[]   = {	SCEGU_REPEAT, SCEGU_CLAMP };

	static StInt32		texFilter[]    = {	SCEGU_NEAREST, SCEGU_LINEAR };

	static StInt32		mipMapFilter[] = {	SCEGU_NEAREST_MIPMAP_NEAREST,
											SCEGU_NEAREST_MIPMAP_LINEAR,
											SCEGU_LINEAR_MIPMAP_NEAREST,
											SCEGU_LINEAR_MIPMAP_LINEAR };

	switch( state )
	{
		case stTEXTURE_STATE_COLOR_OP:
		{
			m_textureState.m_colorOP = static_cast<stTEXTURE_COLOR_OP_MODE>(value);
			sceGuTexFunc( texFunc[ value ], SCEGU_RGBA );
			break;
		}
		case stTEXTURE_STATE_ADDRESSU:
		{
			m_textureState.m_addressU = static_cast<stTEXTURE_ADDRESS_MODE>(value);
			sceGuTexWrap( warpFilter[ m_textureState.m_addressU ], warpFilter[ m_textureState.m_addressV ] );
			break;
		}
		case stTEXTURE_STATE_ADDRESSV:
		{
			m_textureState.m_addressV = static_cast<stTEXTURE_ADDRESS_MODE>(value);
			sceGuTexWrap( warpFilter[ m_textureState.m_addressU ], warpFilter[ m_textureState.m_addressV ] );
			break;
		}
		case stTEXTURE_STATE_MAGFILTER:
		{
			m_textureState.m_magFilter = static_cast<stTEXTURE_FILTER>(value);
			sceGuTexFilter( texFilter[ m_textureState.m_minFilter ], texFilter[ m_textureState.m_magFilter ] );
			break;
		}
		case stTEXTURE_STATE_MINFILTER:
		{
			m_textureState.m_minFilter = static_cast<stTEXTURE_FILTER>(value);
			sceGuTexFilter( texFilter[ m_textureState.m_minFilter ], texFilter[ m_textureState.m_magFilter ] );
			break;
		}
		case stTEXTURE_STATE_MIPFILTER:
		{
			StInt32		index;

			m_textureState.m_mipMapFilter = static_cast<stTEXTURE_MIPMAP_FILTER>(value);
			// �`�F�b�N���ăZ�b�g����K�v������
			if( m_textureState.m_minFilter == stTEXTURE_FILTER_NEAREST ){
				if( m_textureState.m_mipMapFilter == stTEXTURE_MIPMAP_FILTER_NEAREST ){
					index = 0;
				}
				else{
					index = 1;
				}
			}
			else{
				if( m_textureState.m_mipMapFilter == stTEXTURE_MIPMAP_FILTER_NEAREST ){
					index = 3;
				}
				else{
					index = 4;
				}
			}
			sceGuTexFilter( mipMapFilter[ index ], texFilter[ m_textureState.m_magFilter ] );
			break;
		}
		default: break;
	}
}

/************************************************************************************************/
/*
 * �}�e���A�����Z�b�g����
 */
/************************************************************************************************/
void StRenderSystemPSP::setMaterial( StMaterial* pMaterial )
{
	/* �S���L���ɂ��� */
	sceGuColorMaterial( SCEGU_AMBIENT | SCEGU_DIFFUSE | SCEGU_SPECULAR );
	
	/* �f�B�t���[�Y�F( �g�U�� ) */
	sceGuMaterial( SCEGU_AMBIENT, pMaterial->getDiffuse()->m_color );

	/* �A���r�G���g�F( ���� ) */
	sceGuMaterial( SCEGU_DIFFUSE, pMaterial->getAmbient()->m_color );

	/* �X�y�L�����F( ���ʌ� ) */
	sceGuMaterial( SCEGU_SPECULAR, pMaterial->getSpecular()->m_color );

	/* �G�~�b�V�����F */
	// none

	/* �X�y�L���� �n�C���C�g�̑N�� */
	sceGuSpecular( pMaterial->getPower() );
}

/************************************************************************************************/
/*
 * ���C�g��ǉ�����
 * @param		index				���C�g�̃C���f�b�N�X
 * @param		pLight				���C�g���
 * @note							���C�g��ݒu�ł��鐔�́A�ő�4�ł��B<br>
 *									���C�g����菜�����Ƃ��͎�菜���������C�g�̃C���f�b�N�X�ƃ��C�g��NULL���Z�b�g���Ă��������B
 */
/************************************************************************************************/
void StRenderSystemPSP::setLight( StUInt32 index, const StLight* pLight )
{
	StAssert( index < stLIGHT_MAX, "getLight index over !!" );

	static StInt32		lightIndex[] = { SCEGU_LIGHT0, SCEGU_LIGHT1, SCEGU_LIGHT2, SCEGU_LIGHT3 };
	static StInt32		lightMode[]  = { SCEGU_DIFFUSE, SCEGU_DIFFUSE_AND_SPECULAR, SCEGU_POWERED_DIFFUSE };

	/* ���C�g�^�C�v */
	switch( pLight->m_type )
	{
		case stLIGHT_TYPE_DIRECTION:
		{
			sceGuLight( index, SCEGU_LIGHT_DIRECTION, lightMode[ index ], (ScePspFVector3*)&pLight->m_position.x );
			break;
		}
		case stLIGHT_TYPE_POINT:
		{
			/* ���C�g���Z�b�g���� */
			sceGuLight( index, SCEGU_LIGHT_POINT, lightMode[ index ], (ScePspFVector3*)&pLight->m_position.x );
			break;
		}
		case stLIGHT_TYPE_SPOT:
		{
			/* ���C�g���Z�b�g���� */
			sceGuLight( index, SCEGU_LIGHT_SPOT, lightMode[ index ], (ScePspFVector3*)&pLight->m_position.x );
			sceGuLightSpot( index, pLight->m_falloff, pLight->m_conve, (ScePspFVector3*)&pLight->m_direction.x );
			break;
		}
		default: return;
	}

	/* �������̎w�� */
	sceGuLightAtt( index,pLight->m_attenuation0, pLight->m_attenuation1, pLight->m_attenuation2 );

	/* �J���[�̐ݒ� */
	sceGuLightColor( index, SCEGU_AMBIENT,  pLight->m_ambient.m_color );	/* �����J���[�̐ݒ� */
	sceGuLightColor( index, SCEGU_DIFFUSE,  pLight->m_diffuse.m_color );	/* �g�U���J���[�̐ݒ� */
	sceGuLightColor( index, SCEGU_SPECULAR, pLight->m_specular.m_color );	/* ���ʌ��J���[�̐ݒ� */

	/* ���� index ��L���� */
	sceGuEnable( lightIndex[ index ] );
	sceGuEnable( SCEGU_LIGHTING );

	//SCEGU_SINGLE_COLOR						/**< �v���C�}���J���[�̂�		*/
	//SCEGU_SEPARATE_SPECULAR_COLOR				/**< �Z�J���_���J���[			*/
}
/************************************************************************************************/
/**
 * �w�胉�C�g��L���A�����ɂ���B
 */
/************************************************************************************************/
void StRenderSystemPSP::setLightEnable( StUInt32 index, StBool flag )
{
	StAssert( index < stLIGHT_MAX, "getLight index over !!" );

	static StInt32		lightIndex[] = { SCEGU_LIGHT0, SCEGU_LIGHT1, SCEGU_LIGHT2, SCEGU_LIGHT3 };

	if( flag ){
		sceGuEnable( lightIndex[ index ] );
	}
	else{
		sceGuDisable( lightIndex[ index ] );
	}
}

/************************************************************************************************/
/*
 * �����_�[�X�e�[�g
 * @param		state				�X�e�[�g�̎��
 * @param		value				�X�e�[�g�ɑΉ�����l
 */
/************************************************************************************************/
void StRenderSystemPSP::setRenderState( stRENDER_STATE_TYPE state, StUInt32 value )
{
	switch( state )
	{
		case stRENDER_STATE_ZTEST_ENABLE:
		{
			/* ZTEST */
			setZTestEnable( static_cast<StBool>(value) );
			break;
		}
		case stRENDER_STATE_ZWRITE_ENABLE:
		{
			/* ZWRITE */
			setZWriteEnable( static_cast<StBool>(value) );
			break;
		}
		case stRENDER_STATE_SRC_BLEND:
		{
			/* SRC�u�����h���[�h�ݒ� */
			m_renderState.m_srcBlend = static_cast<stBLEND_MODE>(value);
			//setBlendFunc( m_renderState.m_srcBlend, m_renderState.m_dstBlend );
			break;
		}
		case stRENDER_STATE_DST_BLEND:
		{
			/* DST�u�����h���[�h�ݒ� */
			m_renderState.m_dstBlend = static_cast<stBLEND_MODE>(value);
			//setBlendFunc( m_renderState.m_srcBlend, m_renderState.m_dstBlend );
			break;
		}
		case stRENDER_STATE_ALPHA_BLEND:
		{
			/* �A���t�@�u�����h���Z�b�g */
			setAlphaBlend( static_cast<StBool>(value) );
			break;
		}
		case stRENDER_STATE_ALPAHTEST_ENABLE:
		{
			/* �A���t�@�e�X�g */
			setAlphaTestEnable( static_cast<StBool>(value) );
			break;
		}
		case stRENDER_STATE_FOG_ENABLE:
		{
			/* �t�H�O */
			setFogEnable( static_cast<StBool>(value) );
			break;
		}
		case stRENDER_STATE_LIGHTING:
		{
			/* ���C�g */
			setLightEnable( static_cast<StBool>(value) );
			break;
		}
		case stRENDER_STATE_CULL:
		{
			/* �J�����O�ݒ� */
			setCullMode( static_cast<stCULL_MODE>(value) );
			break;
		}
		case stRENDER_STATE_SHADE:
		{
			/* �V�F�[�f�B���O���[�h */
			setShadeMode( static_cast<stSHADE_MODE>(value) );
			break;
		}
		default: break;
	}
}
/************************************************************************************************/
/*
 * �����_�[�X�e�[�g
 * @param		state				�X�e�[�g�̎��
 * @param		value				�X�e�[�g�ɑΉ�����l
 */
/************************************************************************************************/
void StRenderSystemPSP::setZTestEnable( StBool value )
{
	if( value ){
		/* Z�e�X�g�L�� */
		sceGuEnable( SCEGU_DEPTH_TEST );
	}
	else{
		/* Z�e�X�g���� */
		sceGuDisable( SCEGU_DEPTH_TEST );
	}
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void StRenderSystemPSP::setZWriteEnable( StBool value )
{
	if( value ){
		/* ZWRITE�L�� */	
		sceGuDepthFunc( SCEGU_GEQUAL );
		sceGuDepthMask( 0 );
	}
	else{
		/* ZWRITE���� */
		sceGuDepthMask( 1 );
	}
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void StRenderSystemPSP::setAlphaTestEnable( StBool value )
{
	if( value ){
		/* �A���t�@�e�X�g�L�� */
		//sceGuAlphaFunc( SCEGU_GREATER, 0x00, 0xff );
		sceGuEnable( SCEGU_ALPHA_TEST );
	}
	else{
		/* �A���t�@�e�X�g���� */
		sceGuDisable( SCEGU_ALPHA_TEST );
	}
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void StRenderSystemPSP::setLightEnable( StBool value )
{
	if( value ){
		/* ���C�g�L�� */
		sceGuEnable( SCEGU_LIGHTING  );
	}
	else{
		/* ���C�g���� */
		sceGuDisable( SCEGU_LIGHTING  );
	}
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void StRenderSystemPSP::setFogEnable( StBool value )
{
	if( value ){
		/* �t�H�O�L�� */
		sceGuEnable( SCEGU_FOG );
	}
	else{
		/* �t�H�O���� */
		sceGuDisable( SCEGU_FOG );
	}
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void StRenderSystemPSP::setAlphaBlend( StBool value )
{
	if( value ){
		/* �u�����h�L�� */
		sceGuEnable( SCEGU_BLEND );
	}
	else{
		/* �u�����h���� */
		sceGuDisable( SCEGU_BLEND );
	}
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void StRenderSystemPSP::setShadeMode( stSHADE_MODE value )
{
    switch( value )
    {
		case stSHADE_FLAT:
		{
			sceGuShadeModel( SCEGU_FLAT );
			break;
		}
		case stSHADE_GOURAUD:
		{
			sceGuShadeModel( SCEGU_SMOOTH );
			break;
		}
		default:
		{
			sceGuShadeModel( SCEGU_SMOOTH );
			break;
		}
    }
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void StRenderSystemPSP::setCullMode( stCULL_MODE value )
{
	// �p�b�`�̃J�����O���K�v
	switch( value )
	{
		case stCULL_NONE:
		{
			/* �w�ʂ̃J�����O�Ȃ� */
			sceGuDisable( SCEGU_CULL_FACE );
			break;
		}
		case stCULL_CW:
		{
			/* �w�ʂ̃J�����O���� */
			sceGuEnable( SCEGU_CULL_FACE );
			sceGuFrontFace( SCEGU_CW );
			break;
		}
		case stCULL_CCW:
		{
			/* �w�ʂ̃J�����O���� */
			sceGuEnable( SCEGU_CULL_FACE );
			sceGuFrontFace( SCEGU_CW );
			break;
		}
		default:
		{
			/* �w�ʂ̃J�����O�Ȃ� */
			sceGuDisable( SCEGU_CULL_FACE );
			break;
		}
	}
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void StRenderSystemPSP::setBlendFunc( stBLEND_OP_MODE op, stBLEND_MODE src, stBLEND_MODE dst )
{
/*
static StInt32 blendTbl[] = 
{
	0,
	SCEGU_FIX_VALUE,
	SCEGU_FIX_VALUE,
	SCEGU_SRC_COLOR,
	SCEGU_DST_COLOR,
	SCEGU_ONE_MINUS_SRC_COLOR,
	SCEGU_ONE_MINUS_DST_COLOR,
	SCEGU_SRC_ALPHA,
	0,
	SCEGU_ONE_MINUS_SRC_ALPHA,
	0,
};

*/

	//D3DRS_SRCBLEND
	//D3DBLEND �񋓌^�̃����o�̂����ꂩ�ł���B�f�t�H���g�l�� D3DBLEND_ONE �ł���B 

	//D3DRS_DESTBLEND
	//D3DBLEND �񋓌^�̃����o�̂����ꂩ�ł���B�f�t�H���g�l�� D3DBLEND_ZERO �ł���B 


	//ZERO�̂Ƃ��͎w��̕����Œ�l�ŃZ�b�g
	//sceGuBlendFunc( SCEGU_ADD, SCEGU_FIX_VALUE, SCEGU_ONE_MINUS_SRC_ALPHA, 0, 0 );
	
	//ONE�̂Ƃ��͎w��̕����Œ�l�ŃZ�b�g
	//sceGuBlendFunc( SCEGU_ADD, SCEGU_FIX_VALUE, SCEGU_ONE_MINUS_SRC_ALPHA, 1, 0 );

	//glBlendFunc( blendTbl[ src ], blendTbl[ dst ] );
	//glEnable( GL_BLEND );
}

#if 0

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void StRenderSystemGL::setTransform( stTRANSFORM_STATE state, const StMatrix* pMatrix )
{
	switch( state )
	{
		case stTRANSFORM_WORLD:
		{
			/* ���[���h�ɃZ�b�g */
			KsMatrix		tempMatrix;
			m_worldMatrix = *pMatrix;
			tempMatrix   = m_worldMatrix * m_viewMatrix;

			sceGumMatrixMode( SCEGU_MATRIX_WORLD );
			sceGumLoadMatrix( &tempMatrix.m[ 0 ][ 0 ] );
			break;
		}
		case stTRANSFORM_VIEW:
		{
			/* �r���[�ɂɃZ�b�g */
			KsMatrix		tempMatrix;
			m_viewMatrix = *pMatrix;
			tempMatrix   = m_worldMatrix * m_viewMatrix;

			sceGumMatrixMode( SCEGU_MATRIX_VIEW );
			sceGumLoadMatrix( &tempMatrix.m[ 0 ][ 0 ] );
			break;
		}
		case stTRANSFORM_PROJECTION:
		{
			/* �v���W�F�N�V�������Z�b�g���� */
			sceGumMatrixMode( SCEGU_MATRIX_PROJECTION );
			sceGumLoadMatrix( &pMatrix->m[ 0 ][ 0 ] );
			break;
		}
		case stTRANSFORM_TEXTURE:
		{
			/* �e�N�X�`���p�}�g���b�N�X���Z�b�g���� */
			sceGumMatrixMode( SCEGU_MATRIX_TEXTURE );
			sceGumLoadMatrix( &pMatrix->m[ 0 ][ 0 ] );
			break;
		}
		default:{ break; }
	}
}

#endif
#endif



