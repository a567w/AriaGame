/************************************************************************************************/
/** 
 * @file		KsAdapterDX11.cpp
 * @brief		�A�_�v�^���<BR>
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
#include "KsDevDX11/device/KsAdapterDX11.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * �R���X�g���N�^(�R�s�[)
 * @param		_pDXGIAdapter					�A�_�v�^
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
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsAdapterDX11::~KsAdapterDX11()
{
	//ksDELETE( m_pVideoModeList );
}

/************************************************************************************************/
/*
 * ����������
 * @param		pDXGIAdapter		IDXGIAdapter�I�u�W�F�N�g
 * @retval		ksTRUE				����
 * @retval		ksFALSE				���s
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

	// �A�_�v�^�[��
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
 * �A�_�v�^�����擾����
 * @return							�A�_�v�^��
 */
/************************************************************************************************/
const KsString& KsAdapterDX11::getAdapterName()
{
	return m_name;
}

/************************************************************************************************/
/*
 * �A�_�v�^�ڍׂ��擾����
 * @return							�A�_�v�^�ڍ�
 */
/************************************************************************************************/
const KsString& KsAdapterDX11::getAdapterDescription()
{
	return m_description;
}

/************************************************************************************************/
/*
 * �A�_�v�^�i���o�[���擾����
 * @return							�A�_�v�^�i���o		
 */
/************************************************************************************************/
const KsDisplayMode* KsAdapterDX11::getDisplayMode( KsInt32 index )
{
	return NULL;
}

/************************************************************************************************/
/*
 * �A�_�v�^�i���o�[���擾����
 * @return							�A�_�v�^�i���o		
 */
/************************************************************************************************/
const KsDisplayModeList* KsAdapterDX11::getDisplayModeList()
{
	return NULL;
}

/************************************************************************************************/
/*
 * �f�B�X�v���C���[�h��񋓂���
 * @return	yTrue					�񋓐���
 */
/************************************************************************************************/
KsBool KsAdapterDX11::enumerateDisplayMode()
{
	return ksTRUE;
}




#if 0
/************************************************************************************************/
/*
 * �A�_�v�^�����擾����
 * @return									�A�_�v�^��
 */
/************************************************************************************************/
KsString KsAdapterDX11::getAdapterName()
{
	return KsString( "none" );
	//return KsString( m_adapterIdentifier.Driver );
}

/************************************************************************************************/
/*
 * �A�_�v�^�ڍׂ��擾����
 * @return									�A�_�v�^�ڍ�
 */
/************************************************************************************************/
KsString KsAdapterDX11::getAdapterDescription()
{
	return KsString( "none" );
	//return KsString( m_adapterIdentifier.Description );
}









/************************************************************************************************/
/*
 * �A�_�v�^�i���o�[���擾����
 * @return									�A�_�v�^�i���o
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

// �f�t�H���g�A�_�v�^�[�̃C���^�[�t�F�[�X���쐬����
KsBool KsAdapterDX11::enumerateAdapters()
{
	// �A�_�v�^��񋓂���
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

	// �t�@�N�g�����쐬����B
	hResult = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFactory) );

	if( ksFAILED( hResult ) )
	goto EXIT;

	// �f�t�H���g�A�_�v�^�[���擾
	// IDXGIFactory::EnumAdapters
	hr = pFactory->EnumAdapters( 0, &m_pAdapter );
	if( ksFAILED( hResult ) ) goto EXIT;

	ksRELEASE( pFactory );

	return hr;
}

// �f�t�H���g�f�B�X�v���C�̃��[�h��񋓂���
HRESULT D3D11USER::GetDisplayMode()
{
   HRESULT hr = E_FAIL;
   IDXGIOutput* pOutput = NULL;
   DXGI_MODE_DESC* desc = NULL;

   TCHAR s[256];

   OutputMsg( _T("�f�B�X�v���C���[�h�ꗗ�̗�"), _T(""), _T("�J�n") );

   m_DisplayModeDesc.clear();

   // �A�_�v�^�[���擾�B
   hr = CreateAdapter();
   if( FAILED( hr ) ) goto EXIT;

   // �A�_�v�^�[�ɐڑ�����Ă���v���C�}���f�B�X�v���C���擾�B
   // IDXGIAdapter::EnumOutputs
   hr = m_Adapter->EnumOutputs( 0, &pOutput );
   if( FAILED( hr ) ) goto EXIT;

   UINT num;
   // �f�B�X�v���C���[�h�ꗗ�̔z�񐔂��擾
   // IDXGIOutput::GetDisplayModeList
   hr = pOutput->GetDisplayModeList( D3D11USER_FORMAT, 0, &num, NULL );
   if( FAILED( hr ) ) goto EXIT;

   desc = new DXGI_MODE_DESC[num];
   // �f�B�X�v���C���[�h�̈ꗗ���擾
   hr = pOutput->GetDisplayModeList( D3D11USER_FORMAT, 0, &num, desc );
   if( FAILED( hr ) ) goto EXIT;

   for( UINT i=0; i<num; i++ )
   {
      m_DisplayModeDesc.push_back( desc[i] );
      _stprintf_s( s, _T( "�𑜓x( %d : %d )�@���t���b�V�����[�g( %d / %d )" ),
       m_DisplayModeDesc[i].Width, m_DisplayModeDesc[i].Height, m_DisplayModeDesc[i].RefreshRate.Denominator, m_DisplayModeDesc[i].RefreshRate.Numerator );
      OutputMsg( _T("�f�B�X�v���C���[�h"), s, _T("���X�g�ɒǉ�") );      
   }

   OutputMsg( _T("�f�B�X�v���C���[�h�ꗗ�̗�"), _T(""), _T("����") );

   hr = S_OK;

EXIT:
   SAFE_DELETE_ARRAY( desc );
   SAFE_RELEASE( pOutput );

   return hr;
}

#endif

