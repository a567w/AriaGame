/************************************************************************************************/
/** 
 * @file		KsAdapter.cpp
 * @brief		�A�_�v�^���<BR>
 * @author		Tsukasa Kato
 * @date		2003/03/22
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsAdapterDX.h"
#include "KsVideoModeDX.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
KsInt32	KsAdapterDX::m_adapterCount = 0;

/************************************************************************************************/
/*
 * �R���X�g���N�^
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
 * �R���X�g���N�^(�R�s�[)
 * @param		refAdapter					�A�_�v�^
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
 * �R���X�g���N�^
 * @param		pD3D						Direct3D9�I�u�W�F�N�g
 * @param		adapterNumber				�A�_�v�^�i���o�[
 * @param		adapterIdentifier			�A�_�v�^�m�F
 * @param		desktopDisplayMode			�f�B�X�v���C���[�h
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
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsAdapterDX::~KsAdapterDX()
{
	ksDELETE( m_pVideoModeList );
	m_adapterCount--;
}

/************************************************************************************************/
/*
 * �A�_�v�^�����擾����
 * @return									�A�_�v�^��
 */
/************************************************************************************************/
std::string KsAdapterDX::getAdapterName()
{
	return std::string( m_adapterIdentifier.Driver );
}

/************************************************************************************************/
/*
 * �A�_�v�^�ڍׂ��擾����
 * @return									�A�_�v�^�ڍ�
 */
/************************************************************************************************/
std::string KsAdapterDX::getAdapterDescription()
{
	return std::string( m_adapterIdentifier.Description );
}

/************************************************************************************************/
/*
 * �A�_�v�^�i���o�[���擾����
 * @return									�A�_�v�^�i���o
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
 * �A�_�v�^�[���X�g��񋓂���
 */
/************************************************************************************************/
KsAdapterDXList::KsAdapterDXList( IDirect3D9* pD3D ) : m_pD3D( pD3D )
{
	//KsAssert( NULL != m_pD3D, "directX object null pointer" );

	initialize( pD3D );
}

/************************************************************************************************/
/**
 * �f�X�g���N�^( �J������ )
 */
/************************************************************************************************/
KsAdapterDXList::~KsAdapterDXList()
{
	m_adapterList.clear();
}

/************************************************************************************************/
/**
 * ����������
 */
/************************************************************************************************/
KsBool KsAdapterDXList::initialize( IDirect3D9* pD3D )
{
	// �A�_�v�^�����J��Ԃ�
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
 * �A�C�e�������擾����
 * @return									�A�C�e����
 */
/************************************************************************************************/
KsUInt32 KsAdapterDXList::getCount() const 
{
	return static_cast< KsUInt32 >( m_adapterList.size() );
}

/************************************************************************************************/
/*
 * �w��C���f�b�N�X�̃A�_�v�^���擾����
 * @param			index					�w��C���f�b�N�X
 * @return									�A�_�v�^
 */
/************************************************************************************************/
KsAdapterDX* KsAdapterDXList::getItem( KsInt32 index )
{
	return &m_adapterList[ index ];
}

/************************************************************************************************/
/*
 * �w�薼�̃A�_�v�^���擾����
 * @param			name					�A�_�v�^��
 * @return									�A�_�v�^
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



