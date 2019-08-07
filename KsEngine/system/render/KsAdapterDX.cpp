/************************************************************************************************/
/** 
 * @file		KsAdapter.cpp
 * @brief		アダプタ情報<BR>
 * @author		Tsukasa Kato
 * @date		2003/03/22
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsAdapterDX.h"
#include "KsVideoModeDX.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
KsInt32	KsAdapterDX::m_adapterCount = 0;

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsAdapterDX::KsAdapterDX()
{
	m_pD3D           = NULL;
	m_pVideoModeList = NULL;
	m_tempNumber     = ++m_adapterCount;

	ZeroMemory( &m_adapterIdentifier,  sizeof(m_adapterIdentifier)  );
	ZeroMemory( &m_desktopDisplayMode, sizeof(m_desktopDisplayMode) );
}

/************************************************************************************************/
/*
 * コンストラクタ(コピー)
 * @param		refAdapter					アダプタ
 */
/************************************************************************************************/
KsAdapterDX::KsAdapterDX( const KsAdapterDX& refAdapter )
{
	m_pD3D               = refAdapter.m_pD3D;
	m_pVideoModeList     = NULL;
	m_tempNumber	     = ++m_adapterCount;
	m_adapterNumber      = refAdapter.m_adapterNumber;
	m_adapterIdentifier  = refAdapter.m_adapterIdentifier;
	m_desktopDisplayMode = refAdapter.m_desktopDisplayMode;
}

/************************************************************************************************/
/*
 * コンストラクタ
 * @param		pD3D						Direct3D9オブジェクト
 * @param		adapterNumber				アダプタナンバー
 * @param		adapterIdentifier			アダプタ確認
 * @param		desktopDisplayMode			ディスプレイモード
 */
/************************************************************************************************/
KsAdapterDX::KsAdapterDX( LPDIRECT3D9 pD3D, unsigned int adapterNumber, D3DADAPTER_IDENTIFIER9 adapterIdentifier, D3DDISPLAYMODE desktopDisplayMode )
{
	m_pD3D               = pD3D;
	m_pVideoModeList     = NULL;
	m_tempNumber	     = ++m_adapterCount;
	m_adapterNumber      = adapterNumber;
	m_adapterIdentifier  = adapterIdentifier;
	m_desktopDisplayMode = desktopDisplayMode;
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsAdapterDX::~KsAdapterDX()
{
	ksDELETE( m_pVideoModeList );
	m_adapterCount--;
}

/************************************************************************************************/
/*
 * アダプタ名を取得する
 * @return									アダプタ名
 */
/************************************************************************************************/
std::string KsAdapterDX::getAdapterName()
{
	return std::string( m_adapterIdentifier.Driver );
}

/************************************************************************************************/
/*
 * アダプタ詳細を取得する
 * @return									アダプタ詳細
 */
/************************************************************************************************/
std::string KsAdapterDX::getAdapterDescription()
{
	return std::string( m_adapterIdentifier.Description );
}

/************************************************************************************************/
/*
 * アダプタナンバーを取得する
 * @return									アダプタナンバ
 */
/************************************************************************************************/
KsVideoModeDXList* KsAdapterDX::getVideoModeList()
{
	if( !m_pVideoModeList ){
		m_pVideoModeList = new KsVideoModeDXList( this );
	}

	return m_pVideoModeList;
}

/************************************************************************************************/
/**
 * アダプターリストを列挙する
 */
/************************************************************************************************/
KsAdapterDXList::KsAdapterDXList( IDirect3D9* pD3D ) : m_pD3D( pD3D )
{
	//KsAssert( NULL != m_pD3D, "directX object null pointer" );

	initialize( pD3D );
}

/************************************************************************************************/
/**
 * デストラクタ( 開放処理 )
 */
/************************************************************************************************/
KsAdapterDXList::~KsAdapterDXList()
{
	m_adapterList.clear();
}

/************************************************************************************************/
/**
 * 初期化処理
 */
/************************************************************************************************/
KsBool KsAdapterDXList::initialize( IDirect3D9* pD3D )
{
	// アダプタ数分繰り返す
	for( KsUInt32 i=0; i<pD3D->GetAdapterCount(); i++ )
	{
		D3DADAPTER_IDENTIFIER9		adapterIdentifier;
		D3DDISPLAYMODE				displayMode;

		pD3D->GetAdapterIdentifier( i, 0, &adapterIdentifier );
		pD3D->GetAdapterDisplayMode( i, &displayMode );

		m_adapterList.push_back( KsAdapterDX( pD3D, i, adapterIdentifier, displayMode ) );
	}

	return ksTRUE;
}

/************************************************************************************************/
/*
 * アイテム数を取得する
 * @return									アイテム数
 */
/************************************************************************************************/
KsUInt32 KsAdapterDXList::getCount() const 
{
	return static_cast< KsUInt32 >( m_adapterList.size() );
}

/************************************************************************************************/
/*
 * 指定インデックスのアダプタを取得する
 * @param			index					指定インデックス
 * @return									アダプタ
 */
/************************************************************************************************/
KsAdapterDX* KsAdapterDXList::getItem( KsInt32 index )
{
	return &m_adapterList[ index ];
}

/************************************************************************************************/
/*
 * 指定名のアダプタを取得する
 * @param			name					アダプタ名
 * @return									アダプタ
 */
/************************************************************************************************/
KsAdapterDX* KsAdapterDXList::getItem( const std::string &name )
{
	for( KsAdapterDXPtr it=m_adapterList.begin(); it!=m_adapterList.end(); it++ )
	{
		if( it->getAdapterDescription() == name ){
			return &(*it);
		}
	}

	return NULL;
}



