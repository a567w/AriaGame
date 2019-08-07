/************************************************************************************************/
/** 
 * @file		KsAdapterListDX11.cpp
 * @brief		アダプタ情報リスト
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
#include "KsDevDX11/device/KsAdapterListDX11.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * アダプターリストを列挙する
 */
/************************************************************************************************/
KsAdapterListDX11::KsAdapterListDX11( KsRenderSystem* pRenderSystem )
	: m_pRenderSystem( pRenderSystem )
{
	KsAssert( NULL != pRenderSystem, "DirectX object null pointer" );

	initialize( pRenderSystem );
}

/************************************************************************************************/
/**
 * デストラクタ( 開放処理 )
 */
/************************************************************************************************/
KsAdapterListDX11::~KsAdapterListDX11()
{
	ksDELETEARRAYTEMPLATE( m_vpAdapterList );
}

/************************************************************************************************/
/*
 * 初期化処理
 * @param							Direct3D9オブジェクト
 * @retval		ksTRUE				成功
 * @retval		ksFALSE				失敗
 */
/************************************************************************************************/
KsBool KsAdapterListDX11::initialize( KsRenderSystem* pRenderSystem )
{
	return enumerateAdapter();
}

/************************************************************************************************/
/*
 * アイテム数を取得する
 * @return									アイテム数
 */
/************************************************************************************************/
KsUInt32 KsAdapterListDX11::getAdpterCount() const 
{
	return m_vpAdapterList.size();
}

/************************************************************************************************/
/*
 * 指定インデックスのアダプタを取得する
 * @param			index					指定インデックス
 * @return									アダプタ
 */
/************************************************************************************************/
const KsAdapter* KsAdapterListDX11::getAdapter( KsInt32 index )
{
	return m_vpAdapterList[ index ];
}

/************************************************************************************************/
/*
 * アダプタを列挙する
 * @return	yTrue					列挙成功
 */
/************************************************************************************************/
KsBool KsAdapterListDX11::enumerateAdapter()
{
	HRESULT			hResult  = E_FAIL;
	IDXGIFactory*	pFactory = NULL;

	KsAssert( NULL == m_pAdapter, "m_pAdapter null pointer" );

	// ファクトリを作成する。
	hResult = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFactory) );

	if( ksFAILED( hResult ) )
	{
		ksRELEASE( pFactory );
		return ksFALSE;
	}

	// デフォルトアダプターを取得
	KsArray<KsAdapter*>		vAdapters;
	IDXGIAdapter*			pAdapter; 

    for( KsUInt32 i = 0; pFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND; ++i )
    {
		KsAdapterDX11* pAdapterDX = new KsAdapterDX11( pAdapter );

        vAdapters.push_back( pAdapterDX );
    } 

	return ksTRUE;
}


