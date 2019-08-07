/************************************************************************************************/
/** 
 * @file		KsRenderSystemDX.cpp
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
#include "KsRenderSystemDX.h"
#include "KsAdapterDX.h"
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
KsRenderSystemDX::KsRenderSystemDX()
{
	m_pD3D             = NULL;
	m_pD3DDevice       = NULL;
	m_pAdapterList     = NULL;
	m_pAdapter         = NULL;
	m_useStencilBuffer = ksFALSE;
	m_bDeviceLost      = ksFALSE;
	m_bFullScreen      = ksFALSE;
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsRenderSystemDX::KsRenderSystemDX( HWND hWnd )
{
	m_pD3D             = NULL;
	m_pD3DDevice       = NULL;
	m_pAdapterList     = NULL;
	m_pAdapter         = NULL;
	m_useStencilBuffer = ksFALSE;
	m_bDeviceLost      = ksFALSE;
	m_bFullScreen      = ksFALSE;

	initialize( hWnd );
}
/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsRenderSystemDX::~KsRenderSystemDX()
{
	terminate();
}
/************************************************************************************************/
/*
 * 初期化
 */
/************************************************************************************************/
KsBool KsRenderSystemDX::initialize( HWND hWnd )
{
	HRESULT			hr;
	D3DDEVTYPE		devType = D3DDEVTYPE_HAL;
	KsBool			vsync  = ksFALSE;
	KsInt32		width  = 640;
	KsInt32		height = 480;

	//m_useStencilBuffer = useStencilBuffer;	
	m_hWnd = hWnd;
	m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );

	if( !m_pD3D ){
		return ksFALSE;
	}

	/* アダプタリストを取得する */
	//m_pAdapterList = new KsAdapterDXList( m_pD3D );

	/* 本当は選択して選ぶがここでは、0番を選択する */
	//m_pAdapter = m_pAdapterList->getItem( 0 );

	ZeroMemory( &m_present, sizeof(m_present) );

	/* 本当は、使用可能かどうかをチェックする必要がある */
	m_present.SwapEffect             = D3DSWAPEFFECT_DISCARD;
	m_present.Windowed               = m_bFullScreen ? FALSE : TRUE;
	m_present.EnableAutoDepthStencil = 1;//m_useStencilBuffer;
	m_present.BackBufferCount        = 1;
	m_present.BackBufferWidth        = width;
	m_present.BackBufferHeight       = height;
	m_present.hDeviceWindow          = hWnd;
	m_present.BackBufferFormat       = D3DFMT_R5G6B5;

	if( vsync ){
		m_present.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	}
	else{
		m_present.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}

	//m_present.MultiSampleType = mFSAAType;
	//m_present.MultiSampleQuality = (mFSAAQuality == 0) ? NULL : mFSAAQuality;

	/* ステンシルバッファチェック */
	if( m_useStencilBuffer )
	{
		m_present.AutoDepthStencilFormat = D3DFMT_D24S8;

		if( FAILED( m_pD3D->CheckDeviceFormat( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_present.BackBufferFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D24S8 ) ) )
		{
			m_useStencilBuffer = ksFALSE;
		}
		else if( FAILED( m_pD3D->CheckDepthStencilMatch( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_present.BackBufferFormat, m_present.BackBufferFormat, D3DFMT_D24S8 ) ) )
		{
			m_useStencilBuffer = ksFALSE;
		} 		
	}
	/* ステンシルバッファ使用不可または、使わないとき */
	if( !m_useStencilBuffer ){
		m_present.AutoDepthStencilFormat = D3DFMT_D16;
	}

	hr = m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_present, &m_pD3DDevice );

	if( FAILED( hr ) )
	{
		hr = m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_MIXED_VERTEXPROCESSING , &m_present, &m_pD3DDevice );

		if( FAILED( hr ) )
		{
			hr = m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_present, &m_pD3DDevice );

			if( FAILED( hr ) )
			{
				hr = m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_present, &m_pD3DDevice );
			}
		}
	}

	if( FAILED( hr ) )
	{
		printf("aa\n");	
	}

	//if( SUCCEEDED( hr ) ){
	//mpD3DDevice->GetRenderTarget( 0, &mpRenderSurface );
	//mpD3DDevice->GetDepthStencilSurface( &mpRenderZBuffer );
	//}

	m_pD3DDevice->GetDeviceCaps( &m_caps );

	if( m_useStencilBuffer && (!(m_caps.StencilCaps & D3DSTENCILCAPS_DECR) || !(m_caps.StencilCaps & D3DSTENCILCAPS_INCR) || !(m_caps.StencilCaps & D3DSTENCILCAPS_KEEP)) )
	{
		m_useStencilBuffer = ksFALSE;
	}

	return ksTRUE;
}
/************************************************************************************************/
/*
 * 後処理
 */
/************************************************************************************************/
KsBool KsRenderSystemDX::terminate()
{
	ksDELETE( m_pAdapterList );
	ksRELEASE( m_pD3DDevice );
	ksRELEASE( m_pD3D );

	return ksTRUE;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX::beginScene( KsUInt32 flags, KsColor color, KsReal depth, KsUInt32 stencil )
{

#if 0
	#define FAILED(Status) ((HRESULT)(Status)<0)

	HRESULT		hr;

	if( m_bDeviceLost )
	{
		if( FAILED( hr = m_pD3DDevice->TestCooperativeLevel() ) )
        {
			if( hr == D3DERR_DEVICELOST ){
				return false;
			}

            if( hr == D3DERR_DEVICENOTRESET )
            {
				if( FAILED( m_pD3DDevice->Reset(&present) ) ){
					return false;
				}

				m_bDeviceLost = false;
				ResetRenderStates = true;
            }
            return false;
        }
	}
#endif

	KsUInt32	mask = 0;

	if( flags & ksCLEAR_FLAG_COLOR ){
		mask |= D3DCLEAR_TARGET;
	}
	if( flags & ksCLEAR_FLAG_DEPTH ){
		mask |= D3DCLEAR_ZBUFFER;
	}
	if( flags & ksCLEAR_FLAG_STENCIL ){
		mask |= D3DCLEAR_STENCIL;
	}

	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	m_pD3DDevice->Clear( 0, NULL, mask, D3DCOLOR_ARGB( color.getAlpha(), color.getRed(), color.getGreen(), color.getBlue() ), depth, stencil );

	m_pD3DDevice->BeginScene();
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX::endScene()
{
	//if( m_bDeviceLost ){ return; }
	m_pD3DDevice->EndScene();
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX::swapBuffer()
{
	if( D3DERR_DEVICELOST == m_pD3DDevice->Present( NULL, NULL, NULL, NULL ) ){
		m_bDeviceLost = ksTRUE;
	}
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX::setMaterial( KsMaterial* pMaterial )
{
	D3DMATERIAL9		material;
	
	material.Diffuse.r  = pMaterial->getDiffuse()->getRed();
	material.Diffuse.g  = pMaterial->getDiffuse()->getGreen();
	material.Diffuse.b  = pMaterial->getDiffuse()->getBlue();
	material.Diffuse.a  = pMaterial->getDiffuse()->getAlpha();
	
	material.Ambient.r  = pMaterial->getAmbient()->getRed();
	material.Ambient.g  = pMaterial->getAmbient()->getGreen();
	material.Ambient.b  = pMaterial->getAmbient()->getBlue();
	material.Ambient.a  = pMaterial->getAmbient()->getAlpha();
	
	material.Emissive.r = pMaterial->getEmissive()->getRed();
	material.Emissive.g = pMaterial->getEmissive()->getGreen();
	material.Emissive.b = pMaterial->getEmissive()->getBlue();
	material.Emissive.a = pMaterial->getEmissive()->getAlpha();

	material.Power      = pMaterial->getPower();

	m_pD3DDevice->SetMaterial( &material);
}
/************************************************************************************************/
/*
 * ビューポートをセットする
 * @param		pViewport			ビューポート設定
 */
/************************************************************************************************/
void KsRenderSystemDX::setViewport( const KsViewport* pViewport )
{
	m_pD3DDevice->SetViewport( (D3DVIEWPORT9*)pViewport );
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX::makeMatrixDX( D3DMATRIX* pMatrixDX, const KsMatrix* pMatrix  )
{
#if 1
	memcpy( pMatrixDX, pMatrix, sizeof(D3DMATRIX) );

	pMatrixDX->_41 = pMatrix->m14;
	pMatrixDX->_42 = pMatrix->m24;
	pMatrixDX->_43 = pMatrix->m34;
	pMatrixDX->_44 = pMatrix->m44;
	pMatrixDX->_14 = pMatrix->m41;
	pMatrixDX->_24 = pMatrix->m42;
	pMatrixDX->_34 = pMatrix->m43;
	pMatrixDX->_44 = pMatrix->m44;
#endif
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX::setTransform( ksTRANSFORM_STATE state, const KsMatrix* pMatrix )
{
	D3DMATRIX		matrixDX;

	makeMatrixDX( &matrixDX, pMatrix );

	switch( state )
	{
		case ksTRANSFORM_WORLD:
		{
			/* ワールドにセット */
			m_pD3DDevice->SetTransform( D3DTS_WORLD, &matrixDX );
			break;
		}
		case ksTRANSFORM_VIEW:
		{
			/* ビューににセット */
			m_pD3DDevice->SetTransform( D3DTS_VIEW, &matrixDX );
			break;
		}
		case ksTRANSFORM_PROJECTION:
		{
			/* プロジェクションをセットする */
			m_pD3DDevice->SetTransform( D3DTS_PROJECTION, &matrixDX );
			break;
		}
		case ksTRANSFORM_TEXTURE0:
		{
			m_pD3DDevice->SetTransform( D3DTS_TEXTURE0, &matrixDX );
			break;
		}
		case ksTRANSFORM_TEXTURE1:
		{
			m_pD3DDevice->SetTransform( D3DTS_TEXTURE1, &matrixDX );
			break;
		}
		case ksTRANSFORM_TEXTURE2:
		{
			m_pD3DDevice->SetTransform( D3DTS_TEXTURE2, &matrixDX );
			break;
		}
		case ksTRANSFORM_TEXTURE3:
		{
			m_pD3DDevice->SetTransform( D3DTS_TEXTURE3, &matrixDX );
			break;
		}
		case ksTRANSFORM_TEXTURE4:
		{
			m_pD3DDevice->SetTransform( D3DTS_TEXTURE4, &matrixDX );
			break;
		}
		case ksTRANSFORM_TEXTURE5:
		{
			m_pD3DDevice->SetTransform( D3DTS_TEXTURE5, &matrixDX );
			break;
		}
		default:{ break; }
	}
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX::setFog( ksFOG_MODE mode, KsColor color, KsReal start, KsReal end, KsReal density  )
{
	D3DRENDERSTATETYPE		on;
	D3DRENDERSTATETYPE		off;

	if( m_caps.RasterCaps & D3DPRASTERCAPS_FOGTABLE ){
		on  = D3DRS_FOGTABLEMODE;
		off = D3DRS_FOGVERTEXMODE;
	}
	else{
		on  = D3DRS_FOGVERTEXMODE;
		off = D3DRS_FOGTABLEMODE;
	}

	switch( mode )
	{
		case ksFOG_NONE:
		{
			m_pD3DDevice->SetRenderState( on, D3DFOG_NONE );
			m_pD3DDevice->SetRenderState( D3DRS_FOGENABLE, FALSE );
			return;
		}
		case ksFOG_EXP:
		{
			m_pD3DDevice->SetRenderState( D3DRS_FOGENABLE, TRUE );
			m_pD3DDevice->SetRenderState( off, D3DFOG_NONE );
			m_pD3DDevice->SetRenderState( on,  D3DFOG_EXP );
			m_pD3DDevice->SetRenderState( D3DRS_FOGDENSITY, *(DWORD*)(&density) );
			break;
		}
		case ksFOG_EXP2:
		{
			m_pD3DDevice->SetRenderState( D3DRS_FOGENABLE, TRUE );
			m_pD3DDevice->SetRenderState( off, D3DFOG_NONE );
			m_pD3DDevice->SetRenderState( on,  D3DFOG_EXP2 );
			m_pD3DDevice->SetRenderState( D3DRS_FOGDENSITY, *(DWORD*)(&density) ); 
			break;
		}
		case ksFOG_LINEAR:
		{
			m_pD3DDevice->SetRenderState( D3DRS_FOGENABLE, TRUE );
			m_pD3DDevice->SetRenderState( off, D3DFOG_NONE );
			m_pD3DDevice->SetRenderState( on,  D3DFOG_LINEAR );
			m_pD3DDevice->SetRenderState( D3DRS_FOGSTART, *(DWORD*)(&start) ); 
			m_pD3DDevice->SetRenderState( D3DRS_FOGEND,   *(DWORD*)(&end)   ); 
			break;
		}
		default: break;
	}

	m_pD3DDevice->SetRenderState( D3DRS_FOGCOLOR, D3DCOLOR_ARGB( color.getAlpha(), color.getRed(), color.getGreen(), color.getBlue() ) );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX::drawRect( KsInt32 x, KsInt32 y, KsInt32 w, KsInt32 h, KsColor color )
{
	struct KsVertex2D
	{
		FLOAT x, y, z, rhw; // The transformed position for the vertex.
		DWORD color;        // The vertex color.
	};

	KsVertex2D			vertices[ 4 ];
	DWORD				argb = D3DCOLOR_ARGB( color.getAlpha(), color.getRed(), color.getGreen(), color.getBlue() );

	vertices[ 0 ].x     = (KsReal)x;
	vertices[ 0 ].y     = (KsReal)y;
	vertices[ 0 ].z     = 0.0f;
	vertices[ 0 ].rhw   = 1.0f;
	vertices[ 0 ].color = argb;

	vertices[ 1 ].x     = (KsReal)( x + w );
	vertices[ 1 ].y     = (KsReal)y;
	vertices[ 1 ].z     = 0.0f;
	vertices[ 1 ].rhw   = 1.0f;
	vertices[ 1 ].color = argb;

	vertices[ 2 ].x     = (KsReal)x;
	vertices[ 2 ].y     = (KsReal)( y + h );
	vertices[ 2 ].z     = 0.0f;
	vertices[ 2 ].rhw   = 1.0f;
	vertices[ 2 ].color = argb;

	vertices[ 3 ].x     = (KsReal)( x + w );
	vertices[ 3 ].y     = (KsReal)( y + h );
	vertices[ 3 ].z     = 0.0f;
	vertices[ 3 ].rhw   = 1.0f;
	vertices[ 3 ].color = argb;

	static KsUInt16	indeces[] = { 0, 1, 2, 1, 3, 2 };

	m_pD3DDevice->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE );

	m_pD3DDevice->DrawIndexedPrimitiveUP(	D3DPT_TRIANGLELIST,
											0,
											4, 
											2,
											indeces,
											D3DFMT_INDEX16,
											vertices,
											sizeof(KsVertex2D)
										);

}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX::drawPrimitive( ksPRIMITIVE_TYPE type, KsUInt32 vertexStart, KsUInt32 indexStart, KsUInt32 primitiveCount, KsVertexBuffer* pVertexBuffer, KsIndexBuffer* pIndexBuffer )
{
	D3DPRIMITIVETYPE	primitiveType;

	switch( type )
	{
		case ksPRIMITIVE_POINT_LIST:
		{
			primitiveType = D3DPT_POINTLIST;
			break;
		}
		case ksPRIMITIVE_LINE_LIST:
		{
			primitiveType = D3DPT_LINELIST;
			break;
		}
		case ksPRIMITIVE_LINE_STRIP:
		{
			primitiveType = D3DPT_LINESTRIP;
			break;
		}
		case ksPRIMITIVE_TRIANGLE_LIST:
		{
			primitiveType = D3DPT_TRIANGLELIST;
			break;
		}
		case ksPRIMITIVE_TRIANGLE_STRIP:
		{
			primitiveType = D3DPT_TRIANGLESTRIP;
			break;
		}
		default: return;
	}

	KsVertexBufferDX*	pVertex = static_cast< KsVertexBufferDX* >( pVertexBuffer );
	KsIndexBufferDX*	pIndex  = static_cast< KsIndexBufferDX* >( pIndexBuffer );

	m_pD3DDevice->SetFVF( pVertex->getFVF() );
	m_pD3DDevice->SetStreamSource( 0, pVertex->getVertexBuffer(), 0, pVertex->getVertexSize() );
	m_pD3DDevice->SetIndices( pIndex->getIndexBuffer() );

	m_pD3DDevice->DrawIndexedPrimitive( primitiveType, vertexStart, 0, pVertex->getNumVertex() - vertexStart, indexStart, primitiveCount );
}
/************************************************************************************************/
/*
 * ライトを追加する
 * @param		index				ライトのインデックス
 * @param		pLight				ライト情報
 * @note							ライトを設置できる数は、最大８です。<br>
 *									ライトを取り除きいときは取り除きたいライトのインデックスとライトにNULLをセットしてください。
 */
/************************************************************************************************/
void KsRenderSystemDX::setLight( KsUInt32 index, const KsLight* pLight )
{
	D3DLIGHT9		light;

	switch( pLight->m_type )
	{
		case ksLIGHT_TYPE_DIRECTION:
		{
			light.Type = D3DLIGHT_DIRECTIONAL;
			break;
		}
		case ksLIGHT_TYPE_POINT:
		{
			light.Type = D3DLIGHT_POINT;
			break;
		}
		case ksLIGHT_TYPE_SPOT:
		{
			light.Type = D3DLIGHT_SPOT;
			break;
		}
		default: break;
	}

	light.Diffuse.a    = pLight->m_diffuse.getAlpha();
	light.Diffuse.r    = pLight->m_diffuse.getRed();
	light.Diffuse.g    = pLight->m_diffuse.getGreen();
	light.Diffuse.b    = pLight->m_diffuse.getBlue();
	light.Specular.a   = pLight->m_specular.getAlpha();
	light.Specular.r   = pLight->m_specular.getRed();
	light.Specular.g   = pLight->m_specular.getGreen();
	light.Specular.b   = pLight->m_specular.getBlue();
	light.Ambient.a    = pLight->m_ambient.getAlpha();
	light.Ambient.r    = pLight->m_ambient.getRed();
	light.Ambient.g    = pLight->m_ambient.getGreen();
	light.Ambient.b    = pLight->m_ambient.getBlue();
	light.Position.x   = pLight->m_position.x;
	light.Position.y   = pLight->m_position.y;
	light.Position.z   = pLight->m_position.z;
	light.Direction.x  = pLight->m_direction.x;
	light.Direction.y  = pLight->m_direction.y;
	light.Direction.z  = pLight->m_direction.z;
	light.Range        = pLight->m_range;
	light.Falloff      = pLight->m_falloff;
	light.Attenuation0 = pLight->m_attenuation0;
    light.Attenuation1 = pLight->m_attenuation1;
    light.Attenuation2 = pLight->m_attenuation2;
	light.Theta        = pLight->m_theta;
	light.Phi          = pLight->m_phi;

	m_pD3DDevice->SetLight( index, &light );
}

/************************************************************************************************/
/*
 * 指定ライトを有効、無効にする。
 * @param		index				ライトのインデックス
 * @param		flag				ライトのON OFFのフラグ( ksTRUE: ON, ksFALSE: OFF )
 */
/************************************************************************************************/
void KsRenderSystemDX::setLightEnable( KsUInt32 index, KsBool flag )
{
	m_pD3DDevice->LightEnable( index, flag );
}

#if 0


#include "KsTextureDX.h"


/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderSystemDX::setTexture(  KsUInt32 stage, KsTexture* pTexture )
{
	m_pD3DDevice->SetTexture( stage, static_cast< KsTextureDX* >( pTexture )->getDirect3DTexture() );
}



/*-------------------------------------<< レンダーステート関係 >>--------------------------------------------------*/


void KsRenderSystemDX::setRenderState( ksRENDER_STATE_TYPE state, KsUInt32 value )
{
	switch( state )
	{
		case ksRENDER_STATE_ZTEST_ENABLE:
		{
			/* ZTEST */
			m_pD3DDevice->SetRenderState( D3DRS_ZENABLE, static_cast<DWORD>(value) );
			break;
		}
		case ksRENDER_STATE_ZWRITE_ENABLE:
		{
			/* ZWRITE */
			m_pD3DDevice->SetRenderState( D3DRS_ZWRITEENABLE, static_cast<DWORD>(value) );
			break;
		}
		case ksRENDER_STATE_SRC_BLEND:
		{
			/* SRCブレンドモード設定 */
			m_renderState.m_srcBlend = static_cast<ksBLEND_MODE>(value);
			setSrcBlendFunc( m_renderState.m_srcBlend );
			break;
		}
		case ksRENDER_STATE_DST_BLEND:
		{
			/* DSTブレンドモード設定 */
			m_renderState.m_dstBlend = static_cast<ksBLEND_MODE>(value);
			setDstBlendFunc( m_renderState.m_dstBlend );
			break;
		}
		case ksRENDER_STATE_ALPHA_BLEND:
		{
			/* アルファブレンドをセット */
			m_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, static_cast<DWORD>(value) );
			break;
		}
		case ksRENDER_STATE_ALPAHTEST_ENABLE:
		{
			/* アルファテスト */
			m_pD3DDevice->SetRenderState( D3DRS_ALPHATESTENABLE, static_cast<DWORD>(value) );
			break;
		}
		case ksRENDER_STATE_LIGHTING:
		{
			/* ライト */
			m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, static_cast<DWORD>(value) );
			break;
		}
		case ksRENDER_STATE_CULL:
		{
			/* カリング設定 */
			setCullMode( static_cast<ksCULL_MODE>(value) );
			break;
		}
		case ksRENDER_STATE_SHADE:
		{
			/* シェーディングモード */
			setShadeMode( static_cast<ksSHADE_MODE>(value) );
			break;
		}
		default: break;
	}
}
void KsRenderSystemDX::setSrcBlendFunc( ksBLEND_MODE blend )
{
	static D3DBLEND blendTbl[] = {	D3DBLEND_ZERO,
									D3DBLEND_ZERO,
									D3DBLEND_ONE,
									D3DBLEND_SRCCOLOR,
									D3DBLEND_DESTCOLOR,
									D3DBLEND_INVSRCCOLOR,
									D3DBLEND_INVDESTCOLOR,
									D3DBLEND_SRCALPHA,
									D3DBLEND_DESTALPHA,
									D3DBLEND_INVSRCALPHA,
									D3DBLEND_INVDESTALPHA
								};

	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, (DWORD)blendTbl[ blend ]  );
}
void KsRenderSystemDX::setDstBlendFunc( ksBLEND_MODE blend )
{
	static D3DBLEND blendTbl[] = {	D3DBLEND_ZERO,
									D3DBLEND_ZERO,
									D3DBLEND_ONE,
									D3DBLEND_SRCCOLOR,
									D3DBLEND_DESTCOLOR,
									D3DBLEND_INVSRCCOLOR,
									D3DBLEND_INVDESTCOLOR,
									D3DBLEND_SRCALPHA,
									D3DBLEND_DESTALPHA,
									D3DBLEND_INVSRCALPHA,
									D3DBLEND_INVDESTALPHA
								};

	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, (DWORD)blendTbl[ blend ]  );
}
void KsRenderSystemDX::setCullMode( ksCULL_MODE value )
{
	switch( value )
	{
		case ksCULL_NONE:
		{
			/* 背面のカリングなし */
			m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, (DWORD)D3DCULL_NONE );
			break;
		}
		case ksCULL_CW:
		{
			/* 背面のカリングあり */
			m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, (DWORD)D3DCULL_CW );
			break;
		}
		case ksCULL_CCW:
		{
			/* 背面のカリングあり */
			m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, (DWORD)D3DCULL_CCW );
			break;
		}
		default:
		{
			/* 背面のカリングなし */
			m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, (DWORD)D3DCULL_NONE );
			break;
		}
	}
}
void KsRenderSystemDX::setShadeMode( ksSHADE_MODE value )
{
    switch( value )
    {
		case ksSHADE_FLAT:
		{
			m_pD3DDevice->SetRenderState( D3DRS_SHADEMODE, (DWORD)D3DSHADE_FLAT );
			break;
		}
		case ksSHADE_GOURAUD:
		{
			m_pD3DDevice->SetRenderState( D3DRS_SHADEMODE, (DWORD)D3DSHADE_GOURAUD );
			break;
		}
		default:
		{
			m_pD3DDevice->SetRenderState( D3DRS_SHADEMODE, (DWORD)D3DSHADE_GOURAUD );
			break;
		}
    }
}



KsTexture*	KsRenderSystemDX::createTexture( const KsChar* pFileName )
{
	KsTextureDX*	pTexture = new KsTextureDX();

	if( pTexture ){
		D3DXCreateTextureFromFile( m_pD3DDevice, pFileName,  &(pTexture->m_pDirect3DTexture) );
	}
	//m_pD3DDevice->CreateTexture( 256, 256, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &pTex, NULL );

	//m_pD3DDevice->CreateTexture(

	//D3DXCreateTextureFromFileEx( m_pD3DDevice, 256, 256, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &pTex );
	//D3DXCreateTextureFromFileEx(m_pD3DDevice,pFileName,256,256, 1,0,D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0,255,0),NULL,NULL, &(pTexture->m_pDirect3DTexture)  );

	//return pTexture;
	return pTexture;
}


#endif

