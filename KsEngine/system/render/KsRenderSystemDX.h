/************************************************************************************************/
/** 
 * @file		KsRenderSystemDX.h
 * @brief		カラー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSRENDERSYSTEMDX_H__
#define __KSRENDERSYSTEMDX_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsRenderSystem.h"
#include "KsBufferManagerDX.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr9.h>
#include <Cg/Cg.h>
#include <Cg/CgD3D9.h>

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/


/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsAdapterDXList;
class KsAdapterDX;

/************************************************************************************************/
/**
 * @class		KsRenderSystemDX
 * @brief		DirectX用の描画システム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsRenderSystemDX : public KsRenderSystem
{
	public:
		/**
		 * コンストラクタ
		 */
											KsRenderSystemDX();

		/**
		 * コンストラクタ
		 * @param		hWnd				ウインドウのハンドル
		 */
											KsRenderSystemDX( HWND hWnd );

		/**
		 * デストラクタ
		 */
		virtual							~KsRenderSystemDX();

		/**
		 * 初期化処理
		 * @param		hWnd				ウインドウのハンドル
		 * @retval		ksTRUE				初期化成功
		 * @retval		ksFALSE				初期化失敗
		 */
		virtual KsBool						initialize( HWND hWnd );

		/**
		 * 後処理
		 * @retval		ksTRUE				後処理成功
		 * @retval		ksFALSE				後処理失敗
		 */
		virtual KsBool						terminate();
		
		/**
		 * シーン描画開始
		 */
		virtual void						beginScene( KsUInt32 flags, KsColor color, KsReal depth, KsUInt32 stencil );

		/**
		 * シーン描画終了
		 */
		virtual void						endScene();

		/**
		 * 描画バッファと表示バッファを入れ替え
		 */
		virtual void						swapBuffer();

		/**
		 * マテリアルをセットする
		 * @param		pMaterial			マテリアル
		 */
		virtual void						setMaterial( KsMaterial* pMaterial );

		/**
		 * ビューポートをセットする
		 * @param		pViewport			ビューポート設定
		 */
		virtual void						setViewport( const KsViewport* pViewport );

		/**
		 * トランスフォームする
		 * @param		state				トランスフォームのモード
		 * @param		pMatrix				変換マトリックス
		 */
		virtual void						setTransform( ksTRANSFORM_STATE state, const KsMatrix* pMatrix );

		/**
		 * フォグをセットする
		 * @param		pFog				フォグをセットする( NULL )をセットするとフォグを無効
		 */
		virtual void						setFog( ksFOG_MODE mode, KsColor color, KsReal start, KsReal end, KsReal density );

		/**
		 * ライトを追加する
		 * @param		index				ライトのインデックス
		 * @param		pLight				ライト情報
		 * @note							ライトを設置できる数は、最大８です。<br>
		 *									ライトを取り除きいときは取り除きたいライトのインデックスとライトにNULLをセットしてください。
		 */
		virtual void						setLight( KsUInt32 index, const KsLight* pLight );

		/**
		 * 指定ライトを有効、無効にする。
		 * @param		index				ライトのインデックス
		 * @param		flag				ライトのON OFFのフラグ( ksTRUE: ON, ksFALSE: OFF )
		 */
		virtual void						setLightEnable( KsUInt32 index, KsBool flag );

		/**
		 * 短形を描画
		 * @param		x					X座標
		 * @param		y					Y座標
		 * @param		w					幅
		 * @param		h					高さ
		 * @param		color				色
		 */
		virtual void						drawRect( KsInt32 x, KsInt32 y, KsInt32 w, KsInt32 h, KsColor color );

		/**
		 *
		 */
		virtual void						drawPrimitive( ksPRIMITIVE_TYPE type, KsUInt32 vertexStart, KsUInt32 indexStart, KsUInt32 primitiveCount, KsVertexBuffer* pVertexBuffer, KsIndexBuffer* pIndexBuffer );

		virtual void						auto3DMode(){

			m_pD3DDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
			m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
			m_pD3DDevice->SetRenderState( D3DRS_SPECULARENABLE, TRUE );
			m_pD3DDevice->SetRenderState( D3DRS_COLORVERTEX, FALSE );
			m_pD3DDevice->SetRenderState( D3DRS_AMBIENT, D3DCOLOR_COLORVALUE( 0.2f, 0.2f, 0.2f, 1.0f ) );

			//m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
			m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

			D3DLIGHT9 light;
			ZeroMemory( &light, sizeof(light) );
			light.Type = D3DLIGHT_DIRECTIONAL;

			D3DXVECTOR3 vecDir;
			//vecDir = D3DXVECTOR3(0.5f, 2.0f, -5.5f);
			vecDir = D3DXVECTOR3(0.0f, -2.0f, -4.0f);
			D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );


			// set directional light diffuse color
			light.Diffuse.r = 1.0f;
			light.Diffuse.g = 1.0f;
			light.Diffuse.b = 1.0f;
			light.Diffuse.a = 1.0f;
			light.Specular.r = 1.0f;
			light.Specular.g = 1.0f;
			light.Specular.b = 1.0f;
			light.Specular.a = 1.0f;

			m_pD3DDevice->SetLight( 0, &light );
			m_pD3DDevice->LightEnable( 0, TRUE );


			D3DXMATRIX matView;
			D3DXVECTOR3 pos(0.0f, 0.8f, 3.0f);
			D3DXVECTOR3 pnt(0.0f, 0.8f, 0.0f);
			D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
			//D3DXMatrixLookAtLH(&matView, &pos, &pnt, &up);
			D3DXMatrixLookAtRH(&matView, &pos, &pnt, &up);
			m_pD3DDevice->SetTransform(D3DTS_VIEW, &matView); 



			D3DXMATRIX mProjection;
			//D3DXMatrixPerspectiveFovLH( &mProjection, D3DXToRadian( 45.0f ), 640.0f / 480.0f, 0.1f, 500.0f );
			D3DXMatrixPerspectiveFovRH( &mProjection, D3DXToRadian( 45.0f ), 640.0f / 480.0f, 0.1f, 500.0f );
			m_pD3DDevice->SetTransform( D3DTS_PROJECTION, &mProjection );

		}

	private:
		void								makeMatrixDX( D3DMATRIX* pMatrixDX, const KsMatrix* pMatrix  );
	public:
		IDirect3D9*							m_pD3D;					/**< DirectX Object							*/
		IDirect3DDevice9*					m_pD3DDevice;			/**< DirectX Device							*/
		D3DCAPS9							m_caps;					/**< DirectX Caps							*/
		D3DPRESENT_PARAMETERS				m_present;				/**< DirectX Present						*/
		KsBool								m_vsync;				/**< vsyncを使用するかのフラグ				*/
		KsBool								m_useStencilBuffer;		/**< ステンシルバッファを使用するかどうか		*/

		D3DMULTISAMPLE_TYPE					m_FSAAType;				/**< マルチサンプリングタイプ					*/
		KsUInt32							m_FSAAQuality;			/**< マルチサンプリングの品質(level)			*/
	
		KsAdapterDX*						m_pAdapter;				/**< 現在使用しているアダプター				*/
		KsAdapterDXList*					m_pAdapterList;			/**< アダプターリスト							*/

		HWND								m_hWnd;					/**< ウインドウのハンドル						*/
		//HINSTANCE							m_D3DLibrary;			/**< ライブラリ								*/
		//HINSTANCE							m_hInstance;			/**< ウインドウのインスタンス					*/
		//ConfigOptionMap						m_Options;				/**< オプション								*/

		KsBool								m_bDeviceLost;			/**< デバイスがロスト去れたかどうか			*/
		KsBool								m_bFullScreen;

};
#if 0

class KsRenderSystemDX : public KsRenderSystem
{
	public:

		/**
		 * テクスチャをセットする
		 * @param		statge				テクスチャステージ
		 * @param		pTexture			テクスチャ
		 */
		virtual void						setTexture(  KsUInt32 stage, KsTexture* pTexture );

		/**
		 * レンダーステート
		 * @param		state				ステートの種類
		 * @param		value				ステートに対応する値
		 */
		virtual void						setRenderState( ksRENDER_STATE_TYPE state, KsUInt32 value );

		void								setSrcBlendFunc( ksBLEND_MODE blend );
		void								setDstBlendFunc( ksBLEND_MODE blend );
		void								setCullMode( ksCULL_MODE value );
		void								setShadeMode( ksSHADE_MODE value );


		virtual KsTexture*					createTexture( const KsChar* pFileName );

	protected:
	
		IDirect3D9*							m_pD3D;					/**< DirectX Object							*/
		IDirect3DDevice9*					m_pD3DDevice;			/**< DirectX Device							*/
		D3DCAPS9							m_caps;					/**< DirectX Caps							*/
		D3DPRESENT_PARAMETERS				m_present;				/**< DirectX Present						*/
		KsBool								m_vsync;				/**< vsyncを使用するかのフラグ				*/
		KsBool								m_useStencilBuffer;		/**< ステンシルバッファを使用するかどうか		*/

		D3DMULTISAMPLE_TYPE					m_FSAAType;				/**< マルチサンプリングタイプ					*/
		KsUInt32							m_FSAAQuality;			/**< マルチサンプリングの品質(level)			*/
	
		KsAdapterDX*						m_pAdapter;				/**< 現在使用しているアダプター				*/
		KsAdapterDXList*					m_pAdapterList;			/**< アダプターリスト							*/

		HWND								m_hWnd;					/**< ウインドウのハンドル						*/

		KsBool								m_bDeviceLost;			/**< デバイスがロスト去れたかどうか			*/
		KsBool								m_bFullScreen;
};

#endif		/* __KSRENDERSYSTEMDX_H__ */

#endif

