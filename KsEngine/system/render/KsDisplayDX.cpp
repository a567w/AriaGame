/************************************************************************************************/
/**
 * @file	KsDisplayDX.cpp
 * @brief	�f�B�X�v���C���擾
 * @author	Tsukasa Kato
 * @date	2003/11/30
 * @version	1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsDisplayDX.h"
#include "KsVideoModeDX.h"
#include "KsAdapterDX.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*************************************************************************************************/
/*
 * �R���X�g���N�^
 * @param		pAdapter				�A�_�v�^
 */
/*************************************************************************************************/
KsDisplayDX::KsDisplayDX( KsAdapterDX* pAdapter )
{
	/* �f�B�X�v���C�t�H�[�}�b�g */
	static D3DFORMAT	modeList[] = 
	{
		D3DFMT_X8R8G8B8,
		D3DFMT_A8R8G8B8,
		D3DFMT_A2R10G10B10,
		D3DFMT_X1R5G5B5,
		D3DFMT_A1R5G5B5,
		D3DFMT_R5G6B5,
	};

	/* �f�B�X�v���C�t�H�[�}�b�g�� */
	static KsChar*		strList[] = 
	{
		"D3DFMT_X8R8G8B8",
		"D3DFMT_A8R8G8B8",
		"D3DFMT_A2R10G10B10",
		"D3DFMT_X1R5G5B5",
		"D3DFMT_A1R5G5B5",
		"D3DFMT_R5G6B5",
	};

	/* �d�l�\�f�B�X�v���C�T�C�Y */
	static SIZE			sizeTbl[] = { { 640, 480 }, { 800, 600 }, { 1024, 768 } };

	// �A�_�v�^�����擾����
	KsVideoModeDXList*	pVideoModeList = pAdapter->getVideoModeList();

	// �A�_�v�^�����擾
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

		/* �f�B�X�v���C�T�C�Y�`�F�b�N */
		for( KsInt32 j=0; j<3; j++ ){
			if( ( sizeTbl[ j ].cx == pVideoMode->getWidth() ) && ( sizeTbl[ j ].cy == pVideoMode->getHeight() ) ){
				bFindDisplay = ksTRUE;
			}
		}

		if( !bFindDisplay ){
			continue;
		}
		
		/* �����Z�b�g */
		for( KsDisplayDXItemPtr it = m_vDisplayItems.begin(); it != m_vDisplayItems.end(); it++ )
		{
			if( ( it->getWidth() == pVideoMode->getWidth() ) && ( it->getHeight() == pVideoMode->getHeight() ) ){
				// ���łɉ�ʃT�C�Y�͓��������̂��o�^����Ă���

				// �A�C�e�����擾����
				findFlag = 1;
				pFindItem = it;

				// �T�u�A�C�e���̃��t���b�V�����[�g�ƃt���J���[�𒲂ׂ�
				for( KsDisplayDXItem::KsDisplayDXSubItemPtr it2 = it->m_vSubItems.begin(); it2 != it->m_vSubItems.end(); it2++ ){
					
					if( it2->getRefreshRate() == pVideoMode->getRefreshRate() ){
						// ���t���b�V�����[�g��������

						findFlag = 2;
						pFindSubItem = it2;

						// ���Ƃ́A�t���J���[���ǂ����𒲂ׂ邾��
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
		//KsLogManager::Message( ksLOG_LEVEL_NONE, "��ʃT�C�Y			: %d x %d\n",  pVideoMode->GetWidth(), pVideoMode->GetHeight() );
		//KsLogManager::Message( ksLOG_LEVEL_NONE, "��ʂ̐F			: %d bit color\n", pVideoMode->GetColorDepth() );
		// �t���J���[���ǂ������`�F�b�N����
		for( KsInt32 n=0; n<6; n++ ){
			if( modeList[ n ] == pVideoMode->getFormat() ){
				//KsLogManager::Message( ksLOG_LEVEL_NONE, "��ʃt�H�[�}�b�g	: %s\n", strList[ n ] );
			}
		}
		//KsLogManager::Message( ksLOG_LEVEL_NONE, "���t���b�V�����[�g	: %d Hz\n",		pVideoMode->GetRefreshRate() );

		switch( findFlag )
		{
			case 0:
			{
				/* �o�^����Ă��Ȃ� */
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
				/* ��ʃT�C�Y�͓���,���t���b�V�����[�g���Ⴄ */
				subItem.setFormat( pVideoMode->getFormat() );
				subItem.setRefreshRate( pVideoMode->getRefreshRate() );
				subItem.m_formatList.push_back( pVideoMode->getFormat() );

				pFindItem->m_vSubItems.push_back( subItem );
				break;
			}
			case 2:
			{
				/* ��ʃt�H�[�}�b�g���������� */
				pFindSubItem->m_formatList.push_back( pVideoMode->getFormat() );
				break;
			}
			case 3:
			{
				//KsPrint( "-----------------------------------------------------------------\n" );
				//KsPrint( "��ʂ̐F			: %d bit color\n",	pVideoMode->GetColorDepth() );
				break;
			}
			default: break;
		}
	}
}

/*************************************************************************************************/
/*
 * �R���X�g���N�^
 * @param		pAdapter				�A�_�v�^
 */
/*************************************************************************************************/
KsDisplayDXList::KsDisplayDXList( KsAdapterDXList* pAdapterList )
{
	// �A�_�v�^�����擾����
	for( KsUInt32 i=0; i<pAdapterList->getCount(); i++ )
	{
		KsAdapterDX*	pAdapter = pAdapterList->getItem( i );

		m_vDisplays.push_back( new KsDisplayDX( pAdapter ) );
	}
}

/*************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/*************************************************************************************************/
KsDisplayDXList::~KsDisplayDXList()
{
	for( KsDisplayDXPtr it=m_vDisplays.begin(); it != m_vDisplays.end(); it++ ){
		ksDELETE( *it );
	}
}

