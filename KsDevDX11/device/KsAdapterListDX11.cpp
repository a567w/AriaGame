/************************************************************************************************/
/** 
 * @file		KsAdapterListDX11.cpp
 * @brief		�A�_�v�^��񃊃X�g
 * @author		Tsukasa Kato
 * @date		2003/03/22
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsDevDX11/KsDevDX11PreCompile.h"
#include "KsDevDX11/device/KsAdapterListDX11.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * �A�_�v�^�[���X�g��񋓂���
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
 * �f�X�g���N�^( �J������ )
 */
/************************************************************************************************/
KsAdapterListDX11::~KsAdapterListDX11()
{
	ksDELETEARRAYTEMPLATE( m_vpAdapterList );
}

/************************************************************************************************/
/*
 * ����������
 * @param							Direct3D9�I�u�W�F�N�g
 * @retval		ksTRUE				����
 * @retval		ksFALSE				���s
 */
/************************************************************************************************/
KsBool KsAdapterListDX11::initialize( KsRenderSystem* pRenderSystem )
{
	return enumerateAdapter();
}

/************************************************************************************************/
/*
 * �A�C�e�������擾����
 * @return									�A�C�e����
 */
/************************************************************************************************/
KsUInt32 KsAdapterListDX11::getAdpterCount() const 
{
	return m_vpAdapterList.size();
}

/************************************************************************************************/
/*
 * �w��C���f�b�N�X�̃A�_�v�^���擾����
 * @param			index					�w��C���f�b�N�X
 * @return									�A�_�v�^
 */
/************************************************************************************************/
const KsAdapter* KsAdapterListDX11::getAdapter( KsInt32 index )
{
	return m_vpAdapterList[ index ];
}

/************************************************************************************************/
/*
 * �A�_�v�^��񋓂���
 * @return	yTrue					�񋓐���
 */
/************************************************************************************************/
KsBool KsAdapterListDX11::enumerateAdapter()
{
	HRESULT			hResult  = E_FAIL;
	IDXGIFactory*	pFactory = NULL;

	KsAssert( NULL == m_pAdapter, "m_pAdapter null pointer" );

	// �t�@�N�g�����쐬����B
	hResult = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFactory) );

	if( ksFAILED( hResult ) )
	{
		ksRELEASE( pFactory );
		return ksFALSE;
	}

	// �f�t�H���g�A�_�v�^�[���擾
	KsArray<KsAdapter*>		vAdapters;
	IDXGIAdapter*			pAdapter; 

    for( KsUInt32 i = 0; pFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND; ++i )
    {
		KsAdapterDX11* pAdapterDX = new KsAdapterDX11( pAdapter );

        vAdapters.push_back( pAdapterDX );
    } 

	return ksTRUE;
}


