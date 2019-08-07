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
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsRenderSystemGL.h"
#include <GL/gl.h>

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/*
 * コンストラクタ
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
 * デストラクタ
 */
/************************************************************************************************/
KsRenderSystemGL::~KsRenderSystemGL()
{
	terminate();
}
/************************************************************************************************/
/*
 * 初期化
 */
/************************************************************************************************/
KsBool KsRenderSystemGL::initialize( HWND hWnd )
{
	//m_useStencilBuffer = useStencilBuffer;	
	m_hWnd = hWnd;

	/* デバイスコンテキストを取得 */
	if( !( m_hDC = ::GetDC( hWnd ) ) ){
		return ksFALSE;
	}

	/* ピクセルフォーマットをセットする */
	if( !setupPixelFormat() ){
		return ksFALSE;
	}
	
	/* レンダリングコンテキストを生成 */
	if( !(m_hRC = wglCreateContext( m_hDC ) ) ){
		return ksFALSE;
	}
	/* レンダリングコンテキストをアクティブにする */
	if( !wglMakeCurrent( m_hDC, m_hRC ) ){
		return ksFALSE;
	}

	/* 使用可能ならGLの拡張機能をセットする */
	//SetExtensionGL();

	/* 初期レンダリングステータスをセットする */
	//InitStatRender();

	return ksTRUE;
}
/************************************************************************************************/
/*
 * 後処理
 */
/************************************************************************************************/
KsBool KsRenderSystemGL::terminate()
{
	//deleteAllTextures();

	/* 開放処理 */
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
 * ピクセルフォーマットを初期化
 */
/************************************************************************************************/
KsBool KsRenderSystemGL::setupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof( PIXELFORMATDESCRIPTOR ),		/* 構造体のサイズ					*/
		1,										/* 構造体のバージョン					*/
		PFD_DRAW_TO_WINDOW |					/* プロパティのフラグ					*/
		PFD_SUPPORT_OPENGL |					/* OpenGLサポート					*/
		PFD_DOUBLEBUFFER,						/* ダブルバッファを使用				*/
		PFD_TYPE_RGBA,							/* RGBAピクセルフォーマット			*/
		16,										/* 16-bitカラーバッファ				*/
		0, 0, 0, 0, 0, 0,						/* 各ビット数を定義					*/
		0,										/* アルファバッファ					*/
		0,										/* ビット数を定義					*/
		0,										/* アキュームレーションバッファ		*/
		0, 0, 0, 0,								/* ビット数を定義					*/
		16,										/* 16-bit深度バッファ				*/
		m_useStencilBuffer ? ksTRUE : ksFALSE,	/* ステンシルバッファ					*/
		0,										/* AUXバッファ						*/
		PFD_MAIN_PLANE,							/* メインレイヤータイプ				*/
		0, 0, 0, 0								/* 定義不必要						*/
	};

	KsInt32 pixelFormat;

	if( !( pixelFormat = ::ChoosePixelFormat( m_hDC, &pfd ) ) ){
		return ksFALSE;
	}
	
	// 失敗したらステンシルバッファなしでもう一度チェックする
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
		// レンダーステートチェックしてZWrite
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

	/* クリア */
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
	/* フォグをセットする */
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
		/* 描画バッファの設定 */
		sceGuDrawBuffer( format, SCEGU_VRAM_BP32_0, SCEGU_VRAM_WIDTH );
		/* 表示バッファの設定 */
		sceGuDispBuffer( SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT, SCEGU_VRAM_BP32_1, SCEGU_VRAM_WIDTH );
		/* Zバッファの設定 */
		sceGuDepthBuffer( SCEGU_VRAM_BP32_2, SCEGU_VRAM_WIDTH );
	}
	else{
		/* 16bit mode */
		/* 描画バッファの設定 */
		sceGuDrawBuffer( format, SCEGU_VRAM_BP_0, SCEGU_VRAM_WIDTH );
		/* 表示バッファの設定 */
		sceGuDispBuffer( SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT, SCEGU_VRAM_BP_1, SCEGU_VRAM_WIDTH );
		/* Zバッファの設定 */
		sceGuDepthBuffer( SCEGU_VRAM_BP_2, SCEGU_VRAM_WIDTH );
	}
}

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
StRenderSystemPSP::StRenderSystemPSP()
{
	m_pCurrentTexture = NULL;
}
/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
StRenderSystemPSP::~StRenderSystemPSP()
{
	/* 後処理されていなかったら後処理するようにする */
	//terminate();
}

/************************************************************************************************/
/*
 * ラインを描画(2D)
 * @param		x					X座標
 * @param		y					Y座標
 * @param		color				色
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
 * 短形を描画
 * @param		x					X座標
 * @param		y					Y座標
 * @param		w					幅
 * @param		h					高さ
 * @param		tx					テクスチャのX座標
 * @param		ty					テクスチャのY座標
 * @param		tw					テクスチャの幅
 * @param		th					テクスチャの高さ
 * @param		color				色
 * @param		pTexture			テクスチャ
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

	// キャッシュ書き込み
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

	/* 実際はカメラタスクごとに設定したほうがいい */
	/* 2Dモードなので正射影 */
	sceGumMatrixMode( SCEGU_MATRIX_PROJECTION );
	//sceGumOrtho( 0, SCEGU_SCR_WIDTH, 0, SCEGU_SCR_HEIGHT, -1.0f, 1.0f );
	sceGumPerspective( SCEGU_RAD(45.0f), SCEGU_SCR_ASPECT, 1.000000f, 100.000000f );

	sceGumMatrixMode( SCEGU_MATRIX_WORLD );

	/* 描画終了設定 */
	sceGuFinish();
	
	/* 描画終了待ち */
	sceGuSync( SCEGU_SYNC_FINISH, SCEGU_SYNC_WAIT );

	/* 次のVBLANK 開始まで WAIT */
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
	/* 綺麗で速いけど、SCEGU_CLEAR_ALLより,168byte多くメモリーを食う */
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
 * 描画バッファと表示バッファを入れ替え
 */
/************************************************************************************************/
void StRenderSystemPSP::swapBuffer()
{
	sceGuSwapBuffers();
}

/************************************************************************************************/
/*
 * ビューポートをセットする
 * @param		pViewport			ビューポート設定
 */
/************************************************************************************************/
void StRenderSystemPSP::setViewport( const StViewport* pViewport )
{
	/* ビョーポートをセットする */
	sceGuViewport( stRENDER_VIEWPORT_OFFSET_X + pViewport->m_x, stRENDER_VIEWPORT_OFFSET_Y + pViewport->m_y, pViewport->m_w, pViewport->m_h );
	sceGuDepthRange( pViewport->m_near, pViewport->m_far );

	/* 領域をセットする */
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
 * テクスチャを生成する
 * @param		pFileName			ファイル名
 * @param		flags				生成フラグ
 * @return							テクスチャのポインタ
 */
/************************************************************************************************/
StTexture* StRenderSystemPSP::createTexture( const StChar* pFileName, StUInt32 flags )
{
	// FileSystem から読み込みように変更する
	StTextureManager*	pTextureManager;
	StTexture*			pTexture;
	StTexturePSP*		pTexturePSP;

	/* テクスチャマネージャのから検索する */
	pTextureManager = StTextureManager::instance();

	/* 検索して見つかったら参照カウントをアップさせる */
	pTexture = pTextureManager->findRefInc( pFileName );

	if( pTexture ){
		return pTexture;
	}

	/* PSP用テクスチャを生成 */
	pTexturePSP = new StTexturePSP( pFileName, flags );

	//StAssert( pTexture != NULL, "TexturePSP pointer null !!" );

	/* テクスチャマネージャに登録 */
	pTextureManager->add( pTexturePSP );

	return pTexturePSP;
}
/************************************************************************************************/
/*
 * イメージデータからテクスチャを生成する
 * @param		pImage				イメージデータのポインタ
 * @param		flags				生成フラグ
 * @return							テクスチャのポインタ
 */
/************************************************************************************************/
StTexture* StRenderSystemPSP::createTexture( StImage* pImage, StUInt32 flags )
{

	return NULL;
}
/************************************************************************************************/
/*
 * テクスチャをセットする
 * @param		statge				テクスチャステージ
 * @param		pTexture			テクスチャ
 */
/************************************************************************************************/
void StRenderSystemPSP::setTexture( StUInt32 stage, StTexture* pTexture )
{
	//if( stage ){ return; }

	/* テクスチャを何度もセットしないようにする */
	if( m_pCurrentTexture == pTexture ){
		return;
	}
	else{
		m_pCurrentTexture = pTexture;
	}

	/* テクスチャをセットする */
	if( pTexture ){
		/* テクスチャのキャッシュをクリア */
		sceGuTexFlush();

		/* テクスチャを有効にする */
		sceGuEnable( SCEGU_TEXTURE );

		/* 実際はフラグでどちらかをチェックする */
		//sceGimPictureActivate( ((StTexturePSP*)pTexture)->m_pPicture );
		((StTexturePSP*)pTexture)->active();
		//(static_cast<StTexturePSP*>( pTexture ))->active();
	}
	else{
		/* テクスチャを無効にする */
		sceGuDisable( SCEGU_TEXTURE );
	}
}

/************************************************************************************************/
/*
 * テクスチャステートをセットする
 * @param		statge				テクスチャステージ
 * @param		state				セットするステータスの種類
 * @param		value				セットする値
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
			// チェックしてセットする必要がある
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
 * マテリアルをセットする
 */
/************************************************************************************************/
void StRenderSystemPSP::setMaterial( StMaterial* pMaterial )
{
	/* 全部有効にする */
	sceGuColorMaterial( SCEGU_AMBIENT | SCEGU_DIFFUSE | SCEGU_SPECULAR );
	
	/* ディフューズ色( 拡散光 ) */
	sceGuMaterial( SCEGU_AMBIENT, pMaterial->getDiffuse()->m_color );

	/* アンビエント色( 環境光 ) */
	sceGuMaterial( SCEGU_DIFFUSE, pMaterial->getAmbient()->m_color );

	/* スペキュラ色( 鏡面光 ) */
	sceGuMaterial( SCEGU_SPECULAR, pMaterial->getSpecular()->m_color );

	/* エミッション色 */
	// none

	/* スペキュラ ハイライトの鮮明 */
	sceGuSpecular( pMaterial->getPower() );
}

/************************************************************************************************/
/*
 * ライトを追加する
 * @param		index				ライトのインデックス
 * @param		pLight				ライト情報
 * @note							ライトを設置できる数は、最大4です。<br>
 *									ライトを取り除きいときは取り除きたいライトのインデックスとライトにNULLをセットしてください。
 */
/************************************************************************************************/
void StRenderSystemPSP::setLight( StUInt32 index, const StLight* pLight )
{
	StAssert( index < stLIGHT_MAX, "getLight index over !!" );

	static StInt32		lightIndex[] = { SCEGU_LIGHT0, SCEGU_LIGHT1, SCEGU_LIGHT2, SCEGU_LIGHT3 };
	static StInt32		lightMode[]  = { SCEGU_DIFFUSE, SCEGU_DIFFUSE_AND_SPECULAR, SCEGU_POWERED_DIFFUSE };

	/* ライトタイプ */
	switch( pLight->m_type )
	{
		case stLIGHT_TYPE_DIRECTION:
		{
			sceGuLight( index, SCEGU_LIGHT_DIRECTION, lightMode[ index ], (ScePspFVector3*)&pLight->m_position.x );
			break;
		}
		case stLIGHT_TYPE_POINT:
		{
			/* ライトをセットする */
			sceGuLight( index, SCEGU_LIGHT_POINT, lightMode[ index ], (ScePspFVector3*)&pLight->m_position.x );
			break;
		}
		case stLIGHT_TYPE_SPOT:
		{
			/* ライトをセットする */
			sceGuLight( index, SCEGU_LIGHT_SPOT, lightMode[ index ], (ScePspFVector3*)&pLight->m_position.x );
			sceGuLightSpot( index, pLight->m_falloff, pLight->m_conve, (ScePspFVector3*)&pLight->m_direction.x );
			break;
		}
		default: return;
	}

	/* 減衰率の指定 */
	sceGuLightAtt( index,pLight->m_attenuation0, pLight->m_attenuation1, pLight->m_attenuation2 );

	/* カラーの設定 */
	sceGuLightColor( index, SCEGU_AMBIENT,  pLight->m_ambient.m_color );	/* 環境光カラーの設定 */
	sceGuLightColor( index, SCEGU_DIFFUSE,  pLight->m_diffuse.m_color );	/* 拡散光カラーの設定 */
	sceGuLightColor( index, SCEGU_SPECULAR, pLight->m_specular.m_color );	/* 鏡面光カラーの設定 */

	/* 光源 index を有効に */
	sceGuEnable( lightIndex[ index ] );
	sceGuEnable( SCEGU_LIGHTING );

	//SCEGU_SINGLE_COLOR						/**< プライマリカラーのみ		*/
	//SCEGU_SEPARATE_SPECULAR_COLOR				/**< セカンダリカラー			*/
}
/************************************************************************************************/
/**
 * 指定ライトを有効、無効にする。
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
 * レンダーステート
 * @param		state				ステートの種類
 * @param		value				ステートに対応する値
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
			/* SRCブレンドモード設定 */
			m_renderState.m_srcBlend = static_cast<stBLEND_MODE>(value);
			//setBlendFunc( m_renderState.m_srcBlend, m_renderState.m_dstBlend );
			break;
		}
		case stRENDER_STATE_DST_BLEND:
		{
			/* DSTブレンドモード設定 */
			m_renderState.m_dstBlend = static_cast<stBLEND_MODE>(value);
			//setBlendFunc( m_renderState.m_srcBlend, m_renderState.m_dstBlend );
			break;
		}
		case stRENDER_STATE_ALPHA_BLEND:
		{
			/* アルファブレンドをセット */
			setAlphaBlend( static_cast<StBool>(value) );
			break;
		}
		case stRENDER_STATE_ALPAHTEST_ENABLE:
		{
			/* アルファテスト */
			setAlphaTestEnable( static_cast<StBool>(value) );
			break;
		}
		case stRENDER_STATE_FOG_ENABLE:
		{
			/* フォグ */
			setFogEnable( static_cast<StBool>(value) );
			break;
		}
		case stRENDER_STATE_LIGHTING:
		{
			/* ライト */
			setLightEnable( static_cast<StBool>(value) );
			break;
		}
		case stRENDER_STATE_CULL:
		{
			/* カリング設定 */
			setCullMode( static_cast<stCULL_MODE>(value) );
			break;
		}
		case stRENDER_STATE_SHADE:
		{
			/* シェーディングモード */
			setShadeMode( static_cast<stSHADE_MODE>(value) );
			break;
		}
		default: break;
	}
}
/************************************************************************************************/
/*
 * レンダーステート
 * @param		state				ステートの種類
 * @param		value				ステートに対応する値
 */
/************************************************************************************************/
void StRenderSystemPSP::setZTestEnable( StBool value )
{
	if( value ){
		/* Zテスト有効 */
		sceGuEnable( SCEGU_DEPTH_TEST );
	}
	else{
		/* Zテスト無効 */
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
		/* ZWRITE有効 */	
		sceGuDepthFunc( SCEGU_GEQUAL );
		sceGuDepthMask( 0 );
	}
	else{
		/* ZWRITE無効 */
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
		/* アルファテスト有効 */
		//sceGuAlphaFunc( SCEGU_GREATER, 0x00, 0xff );
		sceGuEnable( SCEGU_ALPHA_TEST );
	}
	else{
		/* アルファテスト無効 */
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
		/* ライト有効 */
		sceGuEnable( SCEGU_LIGHTING  );
	}
	else{
		/* ライト無効 */
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
		/* フォグ有効 */
		sceGuEnable( SCEGU_FOG );
	}
	else{
		/* フォグ無効 */
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
		/* ブレンド有効 */
		sceGuEnable( SCEGU_BLEND );
	}
	else{
		/* ブレンド無効 */
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
	// パッチのカリングも必要
	switch( value )
	{
		case stCULL_NONE:
		{
			/* 背面のカリングなし */
			sceGuDisable( SCEGU_CULL_FACE );
			break;
		}
		case stCULL_CW:
		{
			/* 背面のカリングあり */
			sceGuEnable( SCEGU_CULL_FACE );
			sceGuFrontFace( SCEGU_CW );
			break;
		}
		case stCULL_CCW:
		{
			/* 背面のカリングあり */
			sceGuEnable( SCEGU_CULL_FACE );
			sceGuFrontFace( SCEGU_CW );
			break;
		}
		default:
		{
			/* 背面のカリングなし */
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
	//D3DBLEND 列挙型のメンバのいずれかである。デフォルト値は D3DBLEND_ONE である。 

	//D3DRS_DESTBLEND
	//D3DBLEND 列挙型のメンバのいずれかである。デフォルト値は D3DBLEND_ZERO である。 


	//ZEROのときは指定の方を固定値でセット
	//sceGuBlendFunc( SCEGU_ADD, SCEGU_FIX_VALUE, SCEGU_ONE_MINUS_SRC_ALPHA, 0, 0 );
	
	//ONEのときは指定の方を固定値でセット
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
			/* ワールドにセット */
			KsMatrix		tempMatrix;
			m_worldMatrix = *pMatrix;
			tempMatrix   = m_worldMatrix * m_viewMatrix;

			sceGumMatrixMode( SCEGU_MATRIX_WORLD );
			sceGumLoadMatrix( &tempMatrix.m[ 0 ][ 0 ] );
			break;
		}
		case stTRANSFORM_VIEW:
		{
			/* ビューににセット */
			KsMatrix		tempMatrix;
			m_viewMatrix = *pMatrix;
			tempMatrix   = m_worldMatrix * m_viewMatrix;

			sceGumMatrixMode( SCEGU_MATRIX_VIEW );
			sceGumLoadMatrix( &tempMatrix.m[ 0 ][ 0 ] );
			break;
		}
		case stTRANSFORM_PROJECTION:
		{
			/* プロジェクションをセットする */
			sceGumMatrixMode( SCEGU_MATRIX_PROJECTION );
			sceGumLoadMatrix( &pMatrix->m[ 0 ][ 0 ] );
			break;
		}
		case stTRANSFORM_TEXTURE:
		{
			/* テクスチャ用マトリックスをセットする */
			sceGumMatrixMode( SCEGU_MATRIX_TEXTURE );
			sceGumLoadMatrix( &pMatrix->m[ 0 ][ 0 ] );
			break;
		}
		default:{ break; }
	}
}

#endif
#endif



