/************************************************************************************************/
/** 
 * @file		KsVideoModeDX.cpp
 * @brief		ビデをモードを取得する
 * @author		Tsukasa Kato
 * @date		2004/08/17
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>											 */
/*==============================================================================================*/
#include "KsVideoModeDX.h"
#include "KsVideoModeListDX.h"
#include "KsAdapterDX.h"

/*==============================================================================================*/
/*									  << 宣言 >>												*/
/*==============================================================================================*/


/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsVideoModeListDX::KsVideoModeListDX()
{
	m_pAdapter = NULL;
}

/************************************************************************************************/
/*
 * コンストラクタ(初期化付き)
 * @param			pAdapter				アダプタクラスのポインタ
 */
/************************************************************************************************/
KsVideoModeListDX::KsVideoModeListDX( KsAdapterDX* pAdapter )
	: m_pAdapter( pAdapter )
{
	KsAssert( NULL != pAdapter, "adapter null pointer" );

	initialize( pAdapter );
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsVideoModeListDX::~KsVideoModeListDX()
{
	m_pAdapter = NULL;
	ksDELETEARRAYTEMPLATE( m_vpVideoModeList );
}

/************************************************************************************************/
/*
 * 初期化
 * @param			pAdapter				アダプタクラスのポインタ
 * @retval			ksTRUE					成功
 * @retval			ksFALSE					失敗
 */
/************************************************************************************************/
KsBool KsVideoModeListDX::initialize( KsAdapterDX* pAdapter )
{
	static D3DFORMAT	modeList[] = {	D3DFMT_X8R8G8B8,
										D3DFMT_A8R8G8B8,
										D3DFMT_A2R10G10B10,
										D3DFMT_X1R5G5B5,
										D3DFMT_A1R5G5B5,
										D3DFMT_R5G6B5,
									};

	LPDIRECT3D9		pD3D	= pAdapter->getD3D();
	KsUInt32		adapter = pAdapter->getAdapterNumber();

	//
	for( KsUInt32 loop=0; loop<ksARRAYSIZE(modeList); loop++ )
	{
		D3DFORMAT	mode = modeList[ loop ];

		for( KsUInt32 index=0; index< pD3D->GetAdapterModeCount( adapter, mode ); index++ )
		{
			D3DDISPLAYMODE		displayMode;

			pD3D->EnumAdapterModes( adapter, mode, index, &displayMode );

			// 打ち切らないですべてのモードを取得する
			KsBool	bFound = ksFALSE;
			
			for( KsUInt32 i=0; i<m_vpVideoModeList.size(); i++ )
			{
				D3DDISPLAYMODE tempDisp = m_vpVideoModeList[ i ]->getDisplayMode();

				if(		(tempDisp.Width  == displayMode.Width) 
					&&	(tempDisp.Height == displayMode.Height)
					&&	(tempDisp.Format == displayMode.Format) 
				)
				{
					if( tempDisp.RefreshRate == displayMode.RefreshRate )
					{
						bFound = ksTRUE;
					}
					break;
				}
			}

			if( !bFound ) { m_vpVideoModeList.push_back( new KsVideoModeDX( displayMode ) ); }
		}
	}

	return ksTRUE;
}

/************************************************************************************************/
/*
 * アイテム数を取得する
 * @return									アイテム数
 */
/************************************************************************************************/
KsUInt32 KsVideoModeListDX::getCount()
{
	return	m_vpVideoModeList.size();
}

/************************************************************************************************/
/*
 * 指定インデックスのビデオモードを取得する
 * @param			index					指定インデックス
 * @return									ビデオモード
 */
/************************************************************************************************/
KsVideoModeDX* KsVideoModeListDX::getItem( KsInt32 index )
{
	return m_vpVideoModeList[ index ];
}

/************************************************************************************************/
/*
 * 指定名のビデオモードを取得する
 * @param			name					ビデオモード名
 * @return									ビデオモード
 */
/************************************************************************************************/
KsVideoModeDX* KsVideoModeListDX::getItem( const KsString& name )
{
	for( KsUInt32 i=0; i<m_vpVideoModeList.size(); i++ )
	{
		if( m_vpVideoModeList[ i ]->getDisplayModeInfo() == name )
		{
			return m_vpVideoModeList[ i ];
		}
	}

	return	NULL;
}



