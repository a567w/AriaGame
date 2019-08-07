/************************************************************************************************/
/** 
 * @file		KsAdapterDX11.cpp
 * @brief		アダプタ情報<BR>
 * @author		Tsukasa Kato
 * @date		2003/03/22
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsDevDX11/KsDevDX11PreCompile.h"
#include "KsDevDX11/device/KsAdapterDX11.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * コンストラクタ(コピー)
 * @param		_pDXGIAdapter					アダプタ
 */
/************************************************************************************************/
KsAdapterDX11::KsAdapterDX11( IDXGIAdapter* pDXGIAdapter )
	: m_pDXGIAdapter( pDXGIAdapter )
{
	initialize( pDXGIAdapter );

	
	//desc.Description;



	//m_pDXGIAdapter->EnumOutputs
	//m_pVideoModeList     = NULL;
	//CreateSoftwareAdapter
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsAdapterDX11::~KsAdapterDX11()
{
	//ksDELETE( m_pVideoModeList );
}

/************************************************************************************************/
/*
 * 初期化処理
 * @param		pDXGIAdapter		IDXGIAdapterオブジェクト
 * @retval		ksTRUE				成功
 * @retval		ksFALSE				失敗
 */
/************************************************************************************************/
KsBool KsAdapterDX11::initialize( IDXGIAdapter* pDXGIAdapter )
{
	KsAssert( pDXGIAdapter, "pDXGIAdapter null pointer" );

	DXGI_ADAPTER_DESC	desc; 

	if( pDXGIAdapter->GetDesc( &desc ) != S_OK ) 
	{
		return ksFALSE;
	}

	// アダプター名
	m_name = desc.Description;

	KsUInt32				i = 0;
	IDXGIOutput*			pOutput;

	while( pDXGIAdapter->EnumOutputs( i, &pOutput ) != DXGI_ERROR_NOT_FOUND )
	{
		//pOutput->GetDisplayModeList( 
		m_vpOutputs.push_back( pOutput );
		++i;
	}

	return ksTRUE;
}

/************************************************************************************************/
/*
 * アダプタ名を取得する
 * @return							アダプタ名
 */
/************************************************************************************************/
const KsString& KsAdapterDX11::getAdapterName()
{
	return m_name;
}

/************************************************************************************************/
/*
 * アダプタ詳細を取得する
 * @return							アダプタ詳細
 */
/************************************************************************************************/
const KsString& KsAdapterDX11::getAdapterDescription()
{
	return m_description;
}

/************************************************************************************************/
/*
 * アダプタナンバーを取得する
 * @return							アダプタナンバ		
 */
/************************************************************************************************/
const KsDisplayMode* KsAdapterDX11::getDisplayMode( KsInt32 index )
{
	return NULL;
}

/************************************************************************************************/
/*
 * アダプタナンバーを取得する
 * @return							アダプタナンバ		
 */
/************************************************************************************************/
const KsDisplayModeList* KsAdapterDX11::getDisplayModeList()
{
	return NULL;
}

/************************************************************************************************/
/*
 * ディスプレイモードを列挙する
 * @return	yTrue					列挙成功
 */
/************************************************************************************************/
KsBool KsAdapterDX11::enumerateDisplayMode()
{
	return ksTRUE;
}




#if 0
/************************************************************************************************/
/*
 * アダプタ名を取得する
 * @return									アダプタ名
 */
/************************************************************************************************/
KsString KsAdapterDX11::getAdapterName()
{
	return KsString( "none" );
	//return KsString( m_adapterIdentifier.Driver );
}

/************************************************************************************************/
/*
 * アダプタ詳細を取得する
 * @return									アダプタ詳細
 */
/************************************************************************************************/
KsString KsAdapterDX11::getAdapterDescription()
{
	return KsString( "none" );
	//return KsString( m_adapterIdentifier.Description );
}









/************************************************************************************************/
/*
 * アダプタナンバーを取得する
 * @return									アダプタナンバ
 */
/************************************************************************************************/
KsVideoModeListDX* KsAdapterDX11::getVideoModeList()
{
	if( !m_pVideoModeList )
	{
		m_pVideoModeList = new KsVideoModeListDX( this );
	}

	return m_pVideoModeList;
}

KsArray<KsAdapter*> EnumerateAdapters()
{
    IDXGIFactory*			pFactory = NULL;     

    // Create a DXGIFactory object.
    if( ksFAILED( CreateDXGIFactory(__uuidof(IDXGIFactory) ,(void**)&pFactory) ) )
    {
        return vAdapters;
    }

	KsArray<KsAdapter*>		vAdapters;
	IDXGIAdapter*			pAdapter; 

    for( KsUInt32 i = 0; pFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND; ++i )
    {
		KsAdapterDX11 pAdapterDX = ksNew KsAdapterDX11( pAdapter );

        vAdapters.push_back( pAdapterDX );
    } 


    if( pFactory )
    {
        pFactory->Release();
    }

    return vAdapters;

}

// デフォルトアダプターのインターフェースを作成する
KsBool KsAdapterDX11::enumerateAdapters()
{
	// アダプタを列挙する
	KsUInt32		idx = 0;
	IDXGIAdapter*	pAdapter; 

	KsArray<IDXGIAdapter1*> vAdapters; 

	while(pFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND) 
	{ 
		vAdapters.push_back(pAdapter); 
		++i; 
	} 


	HRESULT			hResult  = E_FAIL;
	IDXGIFactory*	pFactory = NULL;

	KsAssert( NULL == m_pAdapter );

	// ファクトリを作成する。
	hResult = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFactory) );

	if( ksFAILED( hResult ) )
	goto EXIT;

	// デフォルトアダプターを取得
	// IDXGIFactory::EnumAdapters
	hr = pFactory->EnumAdapters( 0, &m_pAdapter );
	if( ksFAILED( hResult ) ) goto EXIT;

	ksRELEASE( pFactory );

	return hr;
}

// デフォルトディスプレイのモードを列挙する
HRESULT D3D11USER::GetDisplayMode()
{
   HRESULT hr = E_FAIL;
   IDXGIOutput* pOutput = NULL;
   DXGI_MODE_DESC* desc = NULL;

   TCHAR s[256];

   OutputMsg( _T("ディスプレイモード一覧の列挙"), _T(""), _T("開始") );

   m_DisplayModeDesc.clear();

   // アダプターを取得。
   hr = CreateAdapter();
   if( FAILED( hr ) ) goto EXIT;

   // アダプターに接続されているプライマリディスプレイを取得。
   // IDXGIAdapter::EnumOutputs
   hr = m_Adapter->EnumOutputs( 0, &pOutput );
   if( FAILED( hr ) ) goto EXIT;

   UINT num;
   // ディスプレイモード一覧の配列数を取得
   // IDXGIOutput::GetDisplayModeList
   hr = pOutput->GetDisplayModeList( D3D11USER_FORMAT, 0, &num, NULL );
   if( FAILED( hr ) ) goto EXIT;

   desc = new DXGI_MODE_DESC[num];
   // ディスプレイモードの一覧を取得
   hr = pOutput->GetDisplayModeList( D3D11USER_FORMAT, 0, &num, desc );
   if( FAILED( hr ) ) goto EXIT;

   for( UINT i=0; i<num; i++ )
   {
      m_DisplayModeDesc.push_back( desc[i] );
      _stprintf_s( s, _T( "解像度( %d : %d )　リフレッシュレート( %d / %d )" ),
       m_DisplayModeDesc[i].Width, m_DisplayModeDesc[i].Height, m_DisplayModeDesc[i].RefreshRate.Denominator, m_DisplayModeDesc[i].RefreshRate.Numerator );
      OutputMsg( _T("ディスプレイモード"), s, _T("リストに追加") );      
   }

   OutputMsg( _T("ディスプレイモード一覧の列挙"), _T(""), _T("完了") );

   hr = S_OK;

EXIT:
   SAFE_DELETE_ARRAY( desc );
   SAFE_RELEASE( pOutput );

   return hr;
}

#endif

