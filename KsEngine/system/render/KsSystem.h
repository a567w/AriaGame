/************************************************************************************************/
/** 
 * @file		KsSystem.h
 * @brief		カラー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSRENDERSYS_H__
#define __KSRENDERSYS_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsType.h"
#include "KsMaterial.h"
#include "KsMatrix.h"
#include "KsViewport.h"
//#include "KsFog.h"
#include "KsLight.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
#define ksLIGHT_MAX		( 8 )		/**< ライトの最大数		*/

enum ksTRANSFORM_STATE
{
	ksTRANSFORM_WORLD,
	ksTRANSFORM_VIEW,
	ksTRANSFORM_PROJECTION,
	//ksTRANSFORM_TEXTURE0,
	//ksTRANSFORM_TEXTURE1,
	//ksTRANSFORM_TEXTURE2,
	//ksTRANSFORM_TEXTURE3,
	//ksTRANSFORM_TEXTURE4,
	//ksTRANSFORM_TEXTURE5,
};

typedef enum _ksRENDER_STATE_TYPE
{

	ksRENDER_STATE_FORCE32 = 0x7fffffff,
}ksRENDER_STATE_TYPE;


typedef enum _ksRENDER_PRIM_TYPE
{

}ksRENDER_PRIM_TYPE;

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsRenderSystemGL
 * @brief		OpenGL用の描画システム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsRenderSystem
{
	public:
		/**
		 * コンストラクタ
		 */
											KsRenderSystem(){}
											
		/**
		 * デストラクタ
		 */
		virtual							~KsRenderSystem(){}

		/**
		 * 初期化処理
		 * @param		hWnd				ウインドウのハンドル
		 * @retval		ksTRUE				初期化成功
		 * @retval		ksFALSE				初期化失敗
		 */
		virtual KsBool						initialize( HWND hWnd ) = 0;

		/**
		 * 後処理
		 * @retval		ksTRUE				後処理成功
		 * @retval		ksFALSE				後処理失敗
		 */
		virtual KsBool						terminate() = 0;
		
		/**
		 * シーン描画開始
		 */
		virtual void						beginScene() = 0;

		/**
		 * シーン描画終了
		 */
		virtual void						endScene() = 0;

		/**
		 * ビューポートをセットする
		 * @param		pViewport			ビューポート設定
		 */
		virtual void						setViewport( const KsViewport* pViewport ) = 0;


		/**
		 * トランスフォームする
		 * @param		state				トランスフォームのモード
		 * @param		pMatrix				変換マトリックス
		 */
		virtual void						setTransform( ksTRANSFORM_STATE state, const KsMatrix* pMatrix ) = 0;

		/**
		 * フォグをセットする
		 * @param		pFog				フォグをセットする( NULL )をセットするとフォグを無効
		 */
		//virtual void						setFog( const KsFog* pFog ) = 0;

		/**
		 * テクスチャをセットする
		 * @param		statge				テクスチャステージ
		 * @param		pTexture			テクスチャ
		 */
		virtual void						setTexture(  KsUInt32 stage, KsTexture* pTexture ) = 0;


		/**
		 * マテリアルをセットする
		 * @param		pMaterial			マテリアル
		 */
		virtual void						setMaterial( KsMaterial* pMaterial ) = 0;

#if 0
/*-------------------------------------<< ライト関係 >>--------------------------------------------------*/
		/**
		 * ライトを追加する
		 * @param		index				ライトのインデックス
		 * @param		pLight				ライト情報
		 * @note							ライトを設置できる数は、最大８です。<br>
		 *									ライトを取り除きいときは取り除きたいライトのインデックスとライトにNULLをセットしてください。
		 */
		virtual void						addLight( KsUInt32 index, const KsLight* pLight ) = 0;

		/**
		 * 指定インデックスのライトを取得する
		 * @param		index				インデックス
		 * @return							ライトのポインタ(セットされていないときはNULLが返る)
		 */
		virtual KsLight*					getLight( KsUInt32 index ) = 0;

		/**
		 * 指定インデックスのライトを削除する
		 * @param		index				インデックス
		 * @return							セットされていたライトのポインタ(ないときは、NULLが返る)
		 */
		virtual void						removeLight( KsUInt32 index ) = 0;

		/**
		 * すべてのライトを削除する
		 */
		virtual void						removeAllLight() = 0;

		/**
		 * 指定ライトを有効、無効にする。
		 */
		virtual void						setLightEnable( KsUInt32 index, KsBool flag ) = 0;
/*-------------------------------------<< レンダーステート関係 >>--------------------------------------------------*/

		/**
		 * レンダーステートをスタックにプッシュする
		 */
		virtual void						pushRenderState() = 0;

		/**
		 * レンダーステートをスタックにポップする
		 */
		virtual void						popRenderState() = 0;

		/**
		 * レンダーステート
		 * @param		state				ステートの種類
		 * @param		value				ステートに対応する値
		 */
		virtual void						setRenderState( ksRENDER_STATE_TYPE state, KsUInt32 value ) = 0;

/*-------------------------------------<< プリミティブ描画機能関係 >>--------------------------------------------------*/
#endif

		/**
		 * 描画処理
		 * @param			pVetices
		 */
		//virtual void				drawIndexedPrimitive( ksPRIMITIVE_TYPE type, const KsVertex* pVertices, KsUInt32 numVertex, const KsUInt16* pIndeces, KsUInt32 primitiveCount );
		//virtual void				drawIndexedTriangleList( const KsVertex* pVertices, KsUInt32 numVertex, const KsUInt16* pIndeces, KsUInt32 primitiveCount );
		//virtual void				drawLine( const KsVector3d& start, const KsVector3d& end, KsColor color);

	protected:
		KsMatrix							m_viewMatrix;					/**< ビューマトリックス		*/
		KsMatrix							m_worldMatrix;					/**< ワールドマトリックス		*/
		KsMatrix							m_textureMatrix;				/**< テクスチャマトリックス	*/
		KsLight*							m_pLights[ ksLIGHT_MAX ];		/**< ライト					*/
		//KsFog								m_fog;							/**< フォグ					*/
		KsViewport							m_viewport;						/**< ビューポート			*/
};








#if 0
    D3DPT_POINTLIST = 1,
    D3DPT_LINELIST = 2,
    D3DPT_LINESTRIP = 3,
    D3DPT_TRIANGLELIST = 4,
    D3DPT_TRIANGLESTRIP = 5,
    D3DPT_TRIANGLEFAN = 6,
    D3DPT_FORCE_DWORD = 0x7fffffff
D3DPT_POINTLIST
頂点を個々の点の集合としてレンダリングする。この値は、インデックス付きプリミティブではサポートされない。

D3DPT_LINELIST
個々の線分のリストとして頂点をレンダリングする。このプリミティブ タイプを使う呼び出しは、その個数が 2 より小さいか、奇数の場合は失敗する。 

D3DPT_LINESTRIP
単一のポリラインとして頂点をレンダリングする。このプリミティブ タイプを使う呼び出しは、その個数が 2 より小さい場合は失敗する。 

D3DPT_TRIANGLELIST
個々の三角形の連続として指定の頂点をレンダリングする。各 3 つの頂点のグループは個別に三角形を定義する。

背面のカリングは、現在のカリング モード レンダリング ステートの影響を受ける。


D3DPT_TRIANGLESTRIP
頂点を三角形ストリップとしてレンダリングする。背面カリング フラグは、偶数番号の三角形で自動的に反転する。 

D3DPT_TRIANGLEFAN
頂点を三角形ファンとしてレンダリングする。 

D3DPT_FORCE_DWORD
この列挙型を強制的に 32 ビット サイズにコンパイルする。この値は使われていない。
	
		
		//virtual void				drawBox( const KsBox& box

		virtual void				draw3DLine(const core::vector3df& start, const core::vector3df& end, SColor color = SColor(255,255,255,255));

		//! Draws a 3d triangle.
		virtual void draw3DTriangle(const core::triangle3df& triangle,
			SColor color = SColor(255,255,255,255));

		//! Draws a 3d axis aligned box.
		virtual void draw3DBox(const core::aabbox3d<f32> box,
			SColor color = SColor(255,255,255,255));

		//! draws an 2d image
		virtual void draw2DImage(video::ITexture* texture, const core::position2d<s32>& destPos);

		//! draws an 2d image, using a color (if color is other then Color(255,255,255,255)) and the alpha channel of the texture if wanted.
		virtual void draw2DImage(video::ITexture* texture, const core::position2d<s32>& destPos, 
			const core::rect<s32>& sourceRect, const core::rect<s32>* clipRect = 0,
			SColor color=SColor(255,255,255,255), bool useAlphaChannelOfTexture=false);

		//! draw an 2d rectangle
		virtual void draw2DRectangle(SColor color, const core::rect<s32>& pos, const core::rect<s32>* clip = 0);

		//! Draws a 2d line. 
		virtual void draw2DLine(const core::position2d<s32>& start,
								const core::position2d<s32>& end, 
								SColor color=SColor(255,255,255,255));

void CVideoOpenGL::loadExtensions()
{
	KsReal	version = atof( (KsChar*)glGetString( GL_VERSION ) );

	if( version >= 1.2f ){
		
	}
	else{
		/* OpenGLのバージョンが古い */
	}

	const GLubyte* t = glGetString(GL_EXTENSIONS);
	s32 len = (s32)strlen((const char*)t);
	c8 *str = new c8[len+1];
	c8* p = str;

	for (s32 i=0; i<len; ++i)
	{
		str[i] = (char)t[i];

		if (str[i] == ' ')
		{
			str[i] = 0;
			if (strstr(p, "GL_ARB_multitexture"))
			{
				MultiTextureExtension = true;
				break;
			}

			p = p + strlen(p) + 1;
		}
	}

	delete [] str;

	if (MultiTextureExtension)
	{
		glActiveTextureARB   = (PFNGLACTIVETEXTUREARBPROC) wglGetProcAddress("glActiveTextureARB");
		glClientActiveTextureARB= (PFNGLCLIENTACTIVETEXTUREARBPROC) wglGetProcAddress("glClientActiveTextureARB");
		if (!glActiveTextureARB || !glClientActiveTextureARB)
		{
			MultiTextureExtension = false;
			os::Printer::log("Failed to load OpenGL's multitexture extension, proceeding without.", ELL_WARNING);
		}

		glGetIntegerv(GL_MAX_TEXTURE_UNITS_ARB, &MaxTextureUnits);
	}

	if (MaxTextureUnits < 2)
	{
		MultiTextureExtension = false;
		os::Printer::log("Warning: OpenGL device only has one texture unit. Disabling multitexturing.", ELL_WARNING);
	}
}

#endif


#endif		/* __KSRENDERSYS_H__ */