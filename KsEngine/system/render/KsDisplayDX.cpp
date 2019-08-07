/************************************************************************************************/
/**
 * @file	KsDisplayDX.cpp
 * @brief	ディスプレイ情報取得
 * @author	Tsukasa Kato
 * @date	2003/11/30
 * @version	1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsDisplayDX.h"
#include "KsVideoModeDX.h"
#include "KsAdapterDX.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*************************************************************************************************/
/*
 * コンストラクタ
 * @param		pAdapter				アダプタ
 */
/*************************************************************************************************/
KsDisplayDX::KsDisplayDX( KsAdapterDX* pAdapter )
{
	/* ディスプレイフォーマット */
	static D3DFORMAT	modeList[] = 
	{
		D3DFMT_X8R8G8B8,
		D3DFMT_A8R8G8B8,
		D3DFMT_A2R10G10B10,
		D3DFMT_X1R5G5B5,
		D3DFMT_A1R5G5B5,
		D3DFMT_R5G6B5,
	};

	/* ディスプレイフォーマット名 */
	static KsChar*		strList[] = 
	{
		"D3DFMT_X8R8G8B8",
		"D3DFMT_A8R8G8B8",
		"D3DFMT_A2R10G10B10",
		"D3DFMT_X1R5G5B5",
		"D3DFMT_A1R5G5B5",
		"D3DFMT_R5G6B5",
	};

	/* 仕様可能ディスプレイサイズ */
	static SIZE			sizeTbl[] = { { 640, 480 }, { 800, 600 }, { 1024, 768 } };

	// アダプタ情報を取得する
	KsVideoModeDXList*	pVideoModeList = pAdapter->getVideoModeList();

	// アダプタ名を取得
	m_adapterName = pAdapter->getAdapterDescription();

	for( KsUInt32 i=0; i<pVideoModeList->getCount(); i++ )
	{
		KsDisplayDX::KsDisplayDXItemPtr				pFindItem;
		KsDisplayDXItem::KsDisplayDXSubItemPtr		pFindSubItem;
		KsDisplayDXItem								item;
		KsDisplayDXSubItem							subItem;
		KsVideoModeDX*								pVideoMode   = pVideoModeList->getItem( i );
		KsBool										bFindDisplay = ksFALSE;
		KsUInt32									findFlag     = 0;

		/* ディスプレイサイズチェック */
		for( KsInt32 j=0; j<3; j++ ){
			if( ( sizeTbl[ j ].cx == pVideoMode->getWidth() ) && ( sizeTbl[ j ].cy == pVideoMode->getHeight() ) ){
				bFindDisplay = ksTRUE;
			}
		}

		if( !bFindDisplay ){
			continue;
		}
		
		/* 情報をセット */
		for( KsDisplayDXItemPtr it = m_vDisplayItems.begin(); it != m_vDisplayItems.end(); it++ )
		{
			if( ( it->getWidth() == pVideoMode->getWidth() ) && ( it->getHeight() == pVideoMode->getHeight() ) ){
				// すでに画面サイズは等しいものが登録されている

				// アイテムを取得する
				findFlag = 1;
				pFindItem = it;

				// サブアイテムのリフレッシュレートとフルカラーを調べる
				for( KsDisplayDXItem::KsDisplayDXSubItemPtr it2 = it->m_vSubItems.begin(); it2 != it->m_vSubItems.end(); it2++ ){
					
					if( it2->getRefreshRate() == pVideoMode->getRefreshRate() ){
						// リフレッシュレートも等しい

						findFlag = 2;
						pFindSubItem = it2;

						// あとは、フルカラーかどうかを調べるだけ
						for( std::vector< D3DFORMAT >::iterator it3 = it2->m_formatList.begin(); it3 != it2->m_formatList.end(); it3++ ){

							if( (*it3) == pVideoMode->getFormat() ){
								findFlag = 3;
							}
						}
						break;
					}
				}
				break;
			}
		}

		//KsLogManager::Message( ksLOG_LEVEL_NONE, "-----------------------------------------------------------------\n" );
		//KsLogManager::Message( ksLOG_LEVEL_NONE, "画面サイズ			: %d x %d\n",  pVideoMode->GetWidth(), pVideoMode->GetHeight() );
		//KsLogManager::Message( ksLOG_LEVEL_NONE, "画面の色			: %d bit color\n", pVideoMode->GetColorDepth() );
		// フルカラーかどうかをチェックする
		for( KsInt32 n=0; n<6; n++ ){
			if( modeList[ n ] == pVideoMode->getFormat() ){
				//KsLogManager::Message( ksLOG_LEVEL_NONE, "画面フォーマット	: %s\n", strList[ n ] );
			}
		}
		//KsLogManager::Message( ksLOG_LEVEL_NONE, "リフレッシュレート	: %d Hz\n",		pVideoMode->GetRefreshRate() );

		switch( findFlag )
		{
			case 0:
			{
				/* 登録されていない */
				item.setHeight( pVideoMode->getHeight() );
				item.setWidth( pVideoMode->getWidth() );

				subItem.setFormat( pVideoMode->getFormat() );
				subItem.setRefreshRate( pVideoMode->getRefreshRate() );
				subItem.m_formatList.push_back( pVideoMode->getFormat() );

				item.m_vSubItems.push_back( subItem );

				m_vDisplayItems.push_back( item );
				break;
			}
			case 1:
			{
				/* 画面サイズは同じ,リフレッシュレートが違う */
				subItem.setFormat( pVideoMode->getFormat() );
				subItem.setRefreshRate( pVideoMode->getRefreshRate() );
				subItem.m_formatList.push_back( pVideoMode->getFormat() );

				pFindItem->m_vSubItems.push_back( subItem );
				break;
			}
			case 2:
			{
				/* 画面フォーマットだけちがう */
				pFindSubItem->m_formatList.push_back( pVideoMode->getFormat() );
				break;
			}
			case 3:
			{
				//KsPrint( "-----------------------------------------------------------------\n" );
				//KsPrint( "画面の色			: %d bit color\n",	pVideoMode->GetColorDepth() );
				break;
			}
			default: break;
		}
	}
}

/*************************************************************************************************/
/*
 * コンストラクタ
 * @param		pAdapter				アダプタ
 */
/*************************************************************************************************/
KsDisplayDXList::KsDisplayDXList( KsAdapterDXList* pAdapterList )
{
	// アダプタ情報を取得する
	for( KsUInt32 i=0; i<pAdapterList->getCount(); i++ )
	{
		KsAdapterDX*	pAdapter = pAdapterList->getItem( i );

		m_vDisplays.push_back( new KsDisplayDX( pAdapter ) );
	}
}

/*************************************************************************************************/
/*
 * デストラクタ
 */
/*************************************************************************************************/
KsDisplayDXList::~KsDisplayDXList()
{
	for( KsDisplayDXPtr it=m_vDisplays.begin(); it != m_vDisplays.end(); it++ ){
		ksDELETE( *it );
	}
}

