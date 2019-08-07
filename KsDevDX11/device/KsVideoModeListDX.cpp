/************************************************************************************************/
/** 
 * @file		KsVideoModeDX.cpp
 * @brief		�r�f�����[�h���擾����
 * @author		Tsukasa Kato
 * @date		2004/08/17
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>											 */
/*==============================================================================================*/
#include "KsVideoModeDX.h"
#include "KsVideoModeListDX.h"
#include "KsAdapterDX.h"

/*==============================================================================================*/
/*									  << �錾 >>												*/
/*==============================================================================================*/


/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsVideoModeListDX::KsVideoModeListDX()
{
	m_pAdapter = NULL;
}

/************************************************************************************************/
/*
 * �R���X�g���N�^(�������t��)
 * @param			pAdapter				�A�_�v�^�N���X�̃|�C���^
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
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsVideoModeListDX::~KsVideoModeListDX()
{
	m_pAdapter = NULL;
	ksDELETEARRAYTEMPLATE( m_vpVideoModeList );
}

/************************************************************************************************/
/*
 * ������
 * @param			pAdapter				�A�_�v�^�N���X�̃|�C���^
 * @retval			ksTRUE					����
 * @retval			ksFALSE					���s
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

			// �ł��؂�Ȃ��ł��ׂẴ��[�h���擾����
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
 * �A�C�e�������擾����
 * @return									�A�C�e����
 */
/************************************************************************************************/
KsUInt32 KsVideoModeListDX::getCount()
{
	return	m_vpVideoModeList.size();
}

/************************************************************************************************/
/*
 * �w��C���f�b�N�X�̃r�f�I���[�h���擾����
 * @param			index					�w��C���f�b�N�X
 * @return									�r�f�I���[�h
 */
/************************************************************************************************/
KsVideoModeDX* KsVideoModeListDX::getItem( KsInt32 index )
{
	return m_vpVideoModeList[ index ];
}

/************************************************************************************************/
/*
 * �w�薼�̃r�f�I���[�h���擾����
 * @param			name					�r�f�I���[�h��
 * @return									�r�f�I���[�h
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



