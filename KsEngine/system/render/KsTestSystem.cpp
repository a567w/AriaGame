
#include "KsTestSystem.h"
#include "KsWindowUtil.h"
#include "KsModelLoader.h"



KsTestSystem*	KsTestSystemCreate()
{
	return new KsTestSystem();
}

KsTestSystem::KsTestSystem()
{
	m_pMainWindow   = NULL;
}

KsTestSystem::~KsTestSystem()
{
	ksDELETE( m_pMainWindow );
}


KsBool KsTestSystem::Create( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, KsInt32 nCmdShow )
{
	KsAppInstance::set( hInstance, hPrevInstance, lpCmdLine, nCmdShow );

	RECT	rect;

	KsGetDeskTopClientRect( &rect );

	KsWindowParam	mainWindowParam;

	m_mainWindowParam.m_caption   = "Test";
	m_mainWindowParam.m_className = "KsSystem";
	m_mainWindowParam.m_style     = ksWINDOW_DEFAULT_STYLE;
	m_mainWindowParam.m_styleEx   = 0;
	m_mainWindowParam.m_posX      = ( rect.right  - rect.left )/2 - 320;
	m_mainWindowParam.m_posY      = ( rect.bottom - rect.top  )/2 - 240;
	m_mainWindowParam.m_sizeX     = 640;
	m_mainWindowParam.m_sizeY     = 480;

	m_pMainWindow = new KsWindow();

	if( !m_pMainWindow ){
		return ksFALSE;
	}

	if( !( m_pMainWindow->create( m_mainWindowParam ) ) ){
		return ksFALSE;
	}

	//m_pRenderSystem = new KsRenderSystemGL( m_pMainWindow->getHWnd() );
	m_pRenderSystem = new KsRenderSystemDX( m_pMainWindow->getHWnd() );


	m_pRenderSystem->auto3DMode();

	// 初期化と終了のときウエイトを入れる必要がある

	return ksTRUE;
}


/************************************************************************************************/
/*
 * ウエイト
 */
/************************************************************************************************/
void vsync( KsInt32 count )
{
			KsUInt32	nowTime;
	static KsUInt32	endTime = timeGetTime();

	while( 1 )
	{
		nowTime = timeGetTime();

		if( 33 <= nowTime - endTime ){
			endTime = nowTime;
			break;
		}
		else{
			Sleep( 1 );
		}
	}
}

void KsTestSystem::Loop()
{
	KsRenderSystemDX*	pRS = (KsRenderSystemDX*)m_pRenderSystem;

	//KsMesh*		pMeshDX = KsModelLoadDX( pRS, "test.kmd" );
	//KsAnim*		pAnim	= KsLoadAnim( "anim.anm" );
	//KsMesh*		pMeshDX = KsModelLoadDX( pRS, "gim.kmd" );
	KsMesh*		pMeshDX = KsModelLoadDX( pRS, "juri.kmd" );
	//KsMesh*		pMeshDX = KsModelLoadDX( pRS, "a.kmd" );
	//KsAnim*		pAnim	= KsLoadAnim( "gim.anm" );
	KsAnim*		pAnim	= KsLoadAnim( "juri.anm" );

	//KsMesh*		pMeshDX = KsModelLoadDX( pRS, "juri.kmd" );
	//KsAnim*		pAnim	= KsLoadAnim( "juri.anm" );

	KsMatrix		matrix;

	KsReal			time = 0.0f;

	do{
		m_pRenderSystem->beginScene( ksCLEAR_FLAG_COLOR | ksCLEAR_FLAG_DEPTH, KsColor( 0, 80, 80, 1 ), 1.0f, 0 );
		
		m_pRenderSystem->setTransform( ksTRANSFORM_WORLD, &matrix );

		//pAnim->anim( time, pMeshDX );
		KsModelRenderDX( pRS, pMeshDX );
		//KsModel(  pRS, pMeshDX );

		m_pRenderSystem->endScene();

		m_pRenderSystem->swapBuffer();

		if( time >= pAnim->m_endTime ){
			time = 0.0f;
		}

		time += 1.0f/30.0f;

		vsync( 1 );

	}while( m_pMainWindow->messageLoop() );
}
