/************************************************************************************************/
/** 
 * @file		KsSystemGL.cpp
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
#include "KsSystemGL.h"
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
	m_hWnd             = hWnd;

	/* デバイスコンテキストを取得 */
	if( !( m_hDC  = GetDC( hWnd ) ) ){
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
			if( !( pixelFormat = ChoosePixelFormat( m_hDC, &pfd ) ) ){
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
void KsRenderSystemGL::beginScene()// KsUInt32 flags, KsColor* pColor )
{
	wglMakeCurrent( m_hDC, m_hRC );

	//if( flags & GL_COLOR_BUFFER_BIT ){
	//	glClearColor( pColor.getRed(), pColor.getGreen(), pColor.getBlue(), pColor.getAlpha() );
	//}

	//if( flags & GL_DEPTH_BUFFER_BIT ){
	//	glDepthMask( GL_TRUE );
	//}

	glClearColor( 54.0f/255.0f, 63.0f/255.0f, 75.0f/255.0f, 0.0f );

#if 0
typedef enum ksCLEAR_TARGET_BUFFER
{
	ksCLEAR_COLOR_BUFFER   = ( 1<<0 ),
	ksCLEAR_ACCUM_BUFFER   = ( 1<<1 ),
	ksCLEAR_DEPTH_BUFFER   = ( 1<<2 ),
	ksCLEAR_STENCIL_BUFFER = ( 1<<3 ),

	glClearAccum( 54.0f/255.0f, 63.0f/255.0f, 75.0f/255.0f, 0.0f );
	glClearDepth( f );
	glClearStencil( int )
	GL_ACCUM_BUFFER_BIT
	GL_STENCIL_BUFFER_BIT
}
	if( 

	// D3DCLEAR_STENCIL
	/* ステンシルも？ */
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

#endif

}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemGL::endScene()
{
	SwapBuffers( m_hDC );
}
/************************************************************************************************/
/*
 * ビューポートをセットする
 * @param		pViewport			ビューポート設定
 */
/************************************************************************************************/
void KsRenderSystemGL::setViewport( const KsViewport* pViewport )
{
	glViewport( pViewport->m_x, pViewport->m_y, pViewport->m_w, pViewport->m_h );
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemGL::setMaterial( KsMaterial* pMaterial )
{
	/* GL_FRONT or GL_BACK or GL_FRONT_AND_BACK */

	/* ディフューズ色( 拡散光 ) */
	glMaterialfv( GL_FRONT, GL_DIFFUSE, pMaterial->getDiffuse()->getData() );

	/* アンビエント色( 環境光 ) */
	glMaterialfv( GL_FRONT, GL_AMBIENT, pMaterial->getAmbient()->getData() );

	/* エミッション色 */
	glMaterialfv( GL_FRONT, GL_EMISSION, pMaterial->getEmissive()->getData() );

	/* スペキュラ色( 鏡面光 ) */
	//glMaterialfv( GL_FRONT, GL_SPECULAR, pMaterial->GetSpecular()->getData() );

	/* スペキュラ ハイライトの鮮明 */
	//glMaterialf( GL_FRONT, GL_SHININESS, pMaterial->GetPower() );
	//glMaterialf( GL_FRONT, GL_SHININESS, 50.0f );
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemGL::setTexture(  KsUInt32 stage, KsTexture* pTexture )
{
	if( stage ){
		return;
	}

	//if( m_bMultiTextureExtension )
	//{
	//	glActiveTextureARB(stage == 0 ? GL_TEXTURE0_ARB : GL_TEXTURE1_ARB);
	//}

	/* テクスチャをセットする */
	if( pTexture ){
		/* テクスチャを有効にする */
		glEnable( GL_TEXTURE_2D );
		
		/* テクスチャをセットする */
		glBindTexture( GL_TEXTURE_2D, pTexture->getID() );
	}
	else{
		/* テクスチャを無効にする */
		glDisable( GL_TEXTURE_2D );
	}
}

#if 0
void KsRenderSystemGL::setTextureState( ksTEXTURE_STATE state )
{
	/* テクスチャモード */
	//GLint p = ClampTexture ? GL_CLAMP : GL_REPEAT;
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, p );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, p );
}
#endif

void KsRenderSystemGL::setTransform( ksTRANSFORM_STATE state, const KsMatrix* pMatrix )
{
	switch( state )
	{
		case ksTRANSFORM_WORLD:
		{
			KsMatrix		tempMatrix;
			m_worldMatrix = *pMatrix;
			tempMatrix   = m_worldMatrix * m_viewMatrix;

			glMatrixMode( GL_MODELVIEW );
			glLoadMatrixf( &tempMatrix.m[ 0 ][ 0 ] );
			break;
		}
		case ksTRANSFORM_VIEW:
		{
			KsMatrix		tempMatrix;
			m_viewMatrix = *pMatrix;
			tempMatrix   = m_worldMatrix * m_viewMatrix;

			glMatrixMode( GL_MODELVIEW );
			glLoadMatrixf( &tempMatrix.m[ 0 ][ 0 ] );
			break;
		}
		case ksTRANSFORM_PROJECTION:
		{
			/* プロジェクションをセットする */
			glMatrixMode( GL_PROJECTION );
			glLoadMatrixf( &pMatrix->m[ 0 ][ 0 ] );
			break;
		}
		default:{ break; }
	}
#if 0
	matrixGL[ 16 ];
	m_pMatrizes[ state ] = matrix;

	switch(state)
	{
		case ETS_VIEW:
		{
			/* OpenGL用のマトリックスに変換する */
			createGLMatrix( matrixGL, Matrizes[ETS_VIEW] * Matrizes[ETS_WORLD] );

			/* マトリックスセット */
			glMatrixMode( GL_MODELVIEW );
			glLoadMatrixf( matrixGL );
			break;
		}
		case ETS_WORLD:
		{
			/* OpenGL用のマトリックスに変換する */
			createGLMatrix( matrixGL, Matrizes[ETS_VIEW] * Matrizes[ETS_WORLD] );

			/* マトリックスセット */
			glMatrixMode( GL_MODELVIEW );
			glLoadMatrixf( matrixGL );
			break;
		}
		case ETS_PROJECTION:
		{
			/* OpenGL用のマトリックスに変換する */
			createGLMatrix( matrixGL, pMatrix );

			/* マトリックスセット */
			matrixGL[ 12 ] *= -1.0f;
			glMatrixMode( GL_PROJECTION );
			glLoadMatrixf( matrixGL );
			break;
		}
		default: { break; }
		
	}
#endif
}

/*-------------------------------------<< ライト関係 >>--------------------------------------------------*/
/**
* ライトを追加する
* @param		index				ライトのインデックス
* @param		pLight				ライト情報
* @note							ライトを設置できる数は、最大８です。<br>
*									ライトを取り除きいときは取り除きたいライトのインデックスとライトにNULLをセットしてください。
*/
void KsRenderSystemGL::addLight( KsUInt32 index, const KsLight* pLight )
{
}

/**
* 指定インデックスのライトを取得する
* @param		index				インデックス
* @return							ライトのポインタ(セットされていないときはNULLが返る)
*/
KsLight* KsRenderSystemGL::getLight( KsUInt32 index )
{
	return NULL;
}

/**
* 指定インデックスのライトを削除する
* @param		index				インデックス
* @return							セットされていたライトのポインタ(ないときは、NULLが返る)
*/
void KsRenderSystemGL::removeLight( KsUInt32 index )
{
}

/**
* すべてのライトを削除する
*/
void KsRenderSystemGL::removeAllLight()
{
}

/**
* 指定ライトを有効、無効にする。
*/
void KsRenderSystemGL::setLightEnable( KsUInt32 index, KsBool flag )
{
}
/*-------------------------------------<< レンダーステート関係 >>--------------------------------------------------*/

/**
* レンダーステートをスタックにプッシュする
*/
void KsRenderSystemGL::pushRenderState()
{
}
/**
* レンダーステートをスタックにポップする
*/
void KsRenderSystemGL::popRenderState()
{
}
/**
* レンダーステート
* @param		state				ステートの種類
* @param		value				ステートに対応する値
*/
void KsRenderSystemGL::setRenderState( ksRENDER_STATE_TYPE state, KsUInt32 value )
{
}


#if 0

class KsDrawPrimHeader
{
public:
	KsUInt16		m_flags;		/**< フラグ					*/
	KsUInt16		m_type;			/**< プリミティブのタイプ	*/
	KsUInt32		m_numData;		/**< データの数				*/
};


class KsDrawPrimData
{
};

class KsDrawPrimBase
{
public:
	KsDrawPrimHeader		m_header;

public:
							KsDrawPrimBase(){}
	virtual					~KsDrawPrimBase(){}
};

class KsDrawPrimStrip : public KsDrawPrimBase
{
public:

public:
	KsDrawPrimStrip();

	virtual			~KsDrawPrimStrip();
};


// プリミティブの種類によって描画を変更する
void KsDrawIndexPrimList( KsDrawPrimBase* pPrim )
{
	if (!checkPrimitiveCount(vertexCount))
		return;

	CVideoNull::drawIndexedTriangleList(vertices, vertexCount, indexList, triangleCount);

	setRenderStates3DMode();

	if (MultiTextureExtension)
		glClientActiveTextureARB(GL_TEXTURE0_ARB);

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY );
	glEnableClientState(GL_NORMAL_ARRAY );

	// convert colors to gl color format.

	const S3DVertex* p = vertices;
	ColorBuffer.set_used(vertexCount);
	for (s32 i=0; i<vertexCount; ++i)
	{
		ColorBuffer[i] = p->Color.toOpenGLColor();
		++p;
	}

	// draw everything

	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(video::SColor), &ColorBuffer[0]);
	glNormalPointer(GL_FLOAT, sizeof(S3DVertex), &vertices[0].Normal);
	glTexCoordPointer(2, GL_FLOAT, sizeof(S3DVertex), &vertices[0].TCoords);
	glVertexPointer(3, GL_FLOAT, sizeof(S3DVertex),  &vertices[0].Pos);

	glDrawElements(GL_TRIANGLES, triangleCount * 3, GL_UNSIGNED_SHORT, indexList);

	glFlush();

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY );
	glDisableClientState(GL_NORMAL_ARRAY );


}

/* 描画プリミティブの関数ポインタのテーブル */
static void (*KsDrawPrim)( KsDrawPrimitive* pPrim )[] = 
{
	KsDrawPrimStrip,		/**/
	KsDrawPrimList,			/**/
	KsDrawPrimFan,			/**/
	KsDrawIndexPrim,		/**/
	KsDrawIndexPrimStrip,	/**/
	KsDrawIndexPrimList,	/**/
	KsDrawIndexPrimFan,		/**/
	KsDrawLine,				/**/
	KsDrawPoint,			/**/
	KsDrawSphere			/**/
	KsDrawRectangle,		/**/
	KsDrawSprite,			/**/
}

void KsDrawObject( KsPrimType type, KsUInt16 numIndex, KsUInt16 numVertex, KsUInt16* pIndices, KsVertex* pVertex )
{
}

void KsRenderGL::drawPrimitive()
{
}


KsBool KsRenderGL::InitStatRender()
{
	glViewport(0, 0, screenSize.Width, screenSize.Height);
	glShadeModel(GL_SMOOTH);
	setAmbientLight(SColor(0,0,0,0));
	glClearDepth(1.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glDepthFunc(GL_LEQUAL);
	ResetRenderStates = true;
	setRenderStates3DMode();
	setFog(FogColor, LinearFog, FogStart, FogEnd, FogDensity, PixelFog, RangeFog);
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glClearDepth( 1.0f );
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_TEXTURE_2D );
	//glLineWidth( 2.0f );
	//glPointSize( 3.0f );

	return ksTRUE;
}




void KsRenderGL::SetFog( const KsFog* pFog )
{
	SetFog( pFog->pColor, ksFOG_MODE mode, KsReal start, KsReal end, KsReal density, KsBool pixelFog, KsBool rangeFog );
}

void KsRenderGL::SetFog( ksFOG_MODE mode, KsColor* pColor, KsReal start, KsReal end, KsReal density, KsBool pixelFog, KsBool rangeFog )
{
	GLint fogMode;

	/* フォグのモード選択 */
	switch( mode )
	{
		case FOG_EXP:
		{
			fogMode = GL_EXP;
			break;
		}
		case FOG_EXP2:
		{
			fogMode = GL_EXP2;
			break;
		}
		case FOG_LINEAR:
		{
			/* 直線 */
			fogMode = GL_LINEAR;
			break;
		}
		default:
		{
			/* 見つからないので、フォグ取り消し */
			glDisable( GL_FOG );
			return;
		}
	}

	/* フォグをセットする */
	glEnable( GL_FOG );
	/* モードセット */
	glFogi( GL_FOG_MODE, fogMode );
	/* カラー */
	glFogfv( GL_FOG_COLOR,   pColor->GetData() );
	/* 密度 */
	glFogf(  GL_FOG_DENSITY, density );
	glFogf(  GL_FOG_START,   start );
	glFogf(  GL_FOG_END,     end );
}



//! sets the current Texture
void CVideoOpenGL::setTexture(s32 stage, video::ITexture* texture)
{
	if (stage > 1)
		return;

	if (MultiTextureExtension)
		glActiveTextureARB(stage == 0 ? GL_TEXTURE0_ARB : GL_TEXTURE1_ARB);
	else
		if (stage != 0)
			return;
	
	if (texture && texture->getDriverType() != EDT_OPENGL)
	{
		glDisable(GL_TEXTURE_2D);
		os::Printer::log("Fatal Error: Tried to set a texture not owned by this driver.", ELL_ERROR);
		return;
	}

	if (texture == 0)
		glDisable(GL_TEXTURE_2D);
	else
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,
			((COpenGLTexture*)texture)->getOpenGLTextureName());

		GLint p = ClampTexture ? GL_CLAMP : GL_REPEAT;

		// TODO: reenable this. Seems to cause problems on some gfx adapters.
		//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, p);
		//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, p);
	}
}


void CVideoOpenGL::setRenderStates3DMode()
{
	if (CurrentRenderMode != ERM_3D)
	{
		// switch back the matrices
		GLfloat glmat[16];

		createGLMatrix(glmat, Matrizes[ETS_VIEW] * Matrizes[ETS_WORLD]);
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(glmat);

		createGLMatrix(glmat, Matrizes[ETS_PROJECTION]);
		glmat[12]*= -1.0f;
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(glmat);

		ResetRenderStates = true;
	}

	if (ResetRenderStates)
	{
		glFrontFace(GL_CW);
	}

	if (ResetRenderStates ||
		LastMaterial.AmbientColor != Material.AmbientColor ||
		LastMaterial.DiffuseColor != Material.DiffuseColor ||
		LastMaterial.SpecularColor != Material.SpecularColor ||
		LastMaterial.EmissiveColor != Material.EmissiveColor ||
		LastMaterial.Shininess != Material.Shininess)
	{
		GLfloat color[4];

		float inv = 1.0f / 255.0f;

		color[0] = Material.AmbientColor.getRed() * inv;
		color[1] = Material.AmbientColor.getGreen() * inv;
		color[2] = Material.AmbientColor.getBlue() * inv;
		color[3] = Material.AmbientColor.getAlpha() * inv;
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);

		color[0] = Material.DiffuseColor.getRed() * inv;
		color[1] = Material.DiffuseColor.getGreen() * inv;
		color[2] = Material.DiffuseColor.getBlue() * inv;
		color[3] = Material.DiffuseColor.getAlpha() * inv;
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);

		color[0] = Material.SpecularColor.getRed() * inv;
		color[1] = Material.SpecularColor.getGreen() * inv;
		color[2] = Material.SpecularColor.getBlue() * inv;
		color[3] = Material.SpecularColor.getAlpha() * inv;
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);

		color[0] = Material.EmissiveColor.getRed() * inv;
		color[1] = Material.EmissiveColor.getGreen() * inv;
		color[2] = Material.EmissiveColor.getBlue() * inv;
		color[3] = Material.EmissiveColor.getAlpha() * inv;
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color);

		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, Material.Shininess);
	}

	// blendmode

	if (ResetRenderStates || LastMaterial.MaterialType != Material.MaterialType)
	{
		switch(Material.MaterialType)
		{
		case EMT_SOLID_2_LAYER: // TODO: implement this material
		case EMT_SOLID:
		

			if (MultiTextureExtension)
			{
				glActiveTextureARB(GL_TEXTURE1_ARB);
				glDisable(GL_TEXTURE_2D);
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

				glActiveTextureARB(GL_TEXTURE0_ARB);
			}

			glDisable(GL_TEXTURE_GEN_S);
			glDisable(GL_TEXTURE_GEN_T);

			glDisable(GL_BLEND);
			glDisable(GL_ALPHA_TEST);
			glDepthMask(GL_TRUE);
			break;

		case EMT_TRANSPARENT_VERTEX_ALPHA:
			// just like EMT_TRANSPARENT_ADD_COLOR

		case EMT_TRANSPARENT_ALPHA_CHANNEL:
			// not implemented yet.

		case EMT_TRANSPARENT_ADD_COLOR:

			setTexture(1,0);

			if (MultiTextureExtension)
				glActiveTextureARB(GL_TEXTURE0_ARB);

			glDisable(GL_TEXTURE_GEN_S);
			glDisable(GL_TEXTURE_GEN_T);

			glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glEnable(GL_BLEND);
			glDisable(GL_ALPHA_TEST);
			glDepthMask(GL_FALSE);
			break;

		case EMT_LIGHTMAP_ADD:
		case EMT_LIGHTMAP_M2:
		case EMT_LIGHTMAP_M4:
		case EMT_LIGHTMAP:
		case EMT_LIGHTMAP_LIGHTING:
		case EMT_LIGHTMAP_LIGHTING_M2:
		case EMT_LIGHTMAP_LIGHTING_M4:

			if (MultiTextureExtension)
			{
				glDisable(GL_BLEND);
				glDisable(GL_ALPHA_TEST);
				glDepthMask(GL_TRUE);

				// diffuse map

				glActiveTextureARB(GL_TEXTURE0_ARB);
				glDisable(GL_TEXTURE_GEN_S);
				glDisable(GL_TEXTURE_GEN_T);

				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
				glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_REPLACE);

				// lightmap
												
				glActiveTextureARB(GL_TEXTURE1_ARB);

				glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_COMBINE_EXT);

				if (Material.MaterialType == EMT_LIGHTMAP_ADD)
					glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
				else
					glTexEnvi(GL_TEXTURE_ENV,GL_COMBINE_RGB_EXT, GL_MODULATE);

				glTexEnvi(GL_TEXTURE_ENV,GL_SOURCE0_RGB_EXT,GL_PREVIOUS_EXT);
				glTexEnvi(GL_TEXTURE_ENV,GL_OPERAND0_RGB_EXT,GL_SRC_COLOR);//GL_TEXTURE);

				glTexEnvi(GL_TEXTURE_ENV,GL_SOURCE1_RGB_EXT, GL_TEXTURE);
				glTexEnvi(GL_TEXTURE_ENV,GL_OPERAND1_RGB_EXT,GL_SRC_COLOR);

				glTexEnvi(GL_TEXTURE_ENV,GL_SOURCE2_RGB_EXT,GL_TEXTURE);
				glTexEnvi(GL_TEXTURE_ENV,GL_OPERAND2_RGB_EXT,GL_SRC_COLOR);

				if (Material.MaterialType == EMT_LIGHTMAP_M4)
					glTexEnvi(GL_TEXTURE_ENV, GL_RGB_SCALE_EXT, 4);
				else
				if (Material.MaterialType == EMT_LIGHTMAP_M2)
					glTexEnvi(GL_TEXTURE_ENV, GL_RGB_SCALE_EXT, 2);
				else
					glTexEnvi(GL_TEXTURE_ENV, GL_RGB_SCALE_EXT, 1);
			}
			break;

		case EMT_TRANSPARENT_REFLECTION_2_LAYER:
			{
				if (MultiTextureExtension)
				{
					glActiveTextureARB(GL_TEXTURE1_ARB);
					glDisable(GL_TEXTURE_2D);
					glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

					glActiveTextureARB(GL_TEXTURE0_ARB);
				}

				glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
				glEnable(GL_BLEND);
				glDisable(GL_ALPHA_TEST);
				glDepthMask(GL_FALSE);

				glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
				glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

				glEnable(GL_TEXTURE_GEN_S);
				glEnable(GL_TEXTURE_GEN_T);	
			}
			break;

		case EMT_REFLECTION_2_LAYER:
		case EMT_SPHERE_MAP:
			{
				if (MultiTextureExtension)
				{
					glActiveTextureARB(GL_TEXTURE1_ARB);
					glDisable(GL_TEXTURE_2D);
					glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

					glActiveTextureARB(GL_TEXTURE0_ARB);
				}

				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

				glDisable(GL_BLEND);
				glDisable(GL_ALPHA_TEST);
				glDepthMask(GL_TRUE);

				glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
				glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

				glEnable(GL_TEXTURE_GEN_S);
				glEnable(GL_TEXTURE_GEN_T);	
			}
			break;
		}
	}

	// bilinear

	if (ResetRenderStates || LastMaterial.BilinearFilter != Material.BilinearFilter)
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
			Material.BilinearFilter ? GL_LINEAR : GL_NEAREST);

	/*if (ResetRenderStates || LastMaterial.BilinearFilter != Material.BilinearFilter)
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
			Material.BilinearFilter ? GL_LINEAR : GL_NEAREST);

	// trilinear
	if (ResetRenderStates || LastMaterial.TrilinearFilter != Material.TrilinearFilter)
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			Material.TrilinearFilter ? GL_LINEAR_MIPMAP_NEAREST : GL_LINEAR_MIPMAP_LINEAR);*/

	// fillmode

	if (ResetRenderStates || LastMaterial.Wireframe != Material.Wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, Material.Wireframe ? GL_LINE : GL_FILL);

	// lighting

	if (ResetRenderStates || LastMaterial.Lighting != Material.Lighting)
	{
		if (Material.Lighting)
			glEnable(GL_LIGHTING);
		else
			glDisable(GL_LIGHTING);
	}

	// zbuffer

	if (ResetRenderStates || LastMaterial.ZBuffer != Material.ZBuffer)
	{
		if (Material.ZBuffer)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);
	}

	// zwrite

	if (!Material.isTransparent())
	{
		if (ResetRenderStates || LastMaterial.ZWriteEnable != Material.ZWriteEnable)
			glDepthMask(Material.ZWriteEnable ? GL_TRUE : GL_FALSE);
	}

	// back face culling

	if (ResetRenderStates || LastMaterial.BackfaceCulling != Material.BackfaceCulling)
	{
		if (Material.BackfaceCulling)
			glEnable(GL_CULL_FACE);
		else
			glDisable(GL_CULL_FACE);
	}

	// fog
	if (ResetRenderStates || LastMaterial.FogEnable != Material.FogEnable)
	{
		if (Material.FogEnable)
			glEnable(GL_FOG);
		else
			glDisable(GL_FOG);
	}

	LastMaterial = Material;

	ResetRenderStates = false;

	CurrentRenderMode = ERM_3D;
}


//! sets the needed renderstates
void CVideoOpenGL::setRenderStates2DMode(bool alpha, bool texture, bool alphaChannel)
{
	if (CurrentRenderMode != ERM_2D || Transformation3DChanged)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		Transformation3DChanged = false;

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_FOG);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_LIGHTING);

		if (MultiTextureExtension)
			glActiveTextureARB(GL_TEXTURE0_ARB);

		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);

		ClampTexture = false;
	}

	if (texture)
	{
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		if (alphaChannel)
		{
			/*
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glEnable(GL_BLEND); 
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
			glDisable(GL_ALPHA_TEST); */
		 
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glDisable(GL_BLEND);
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0);			
		}
		else
		{
			if (alpha)
			{
				glDisable(GL_ALPHA_TEST);
				glEnable(GL_BLEND);
			}
			else
			{
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
				glDisable(GL_ALPHA_TEST);
				glDisable(GL_BLEND);
			}
		}

	}
	else
	{
		if (alpha)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glDisable(GL_ALPHA_TEST);
		}
		else
		{
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glDisable(GL_BLEND);
			glDisable(GL_ALPHA_TEST);
		}
	}

	CurrentRenderMode = ERM_2D;
}

#endif
