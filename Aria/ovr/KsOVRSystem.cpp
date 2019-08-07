/************************************************************************************************/
/** 
 * @file		KsOVRSystem.cpp
 * @brief		OVRシステム
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "Aria/KsGamePreCompile.h"
#include "Aria/ovr/KsOVRSystem.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
template<> KsOVRSystem* KsSingleton< KsOVRSystem >::m_pInstance = 0;

/************************************************************************************************/
/*
 * シングルトンの参照を取得
 * @return							シングルトンの参照
 */
/************************************************************************************************/
KsOVRSystem& KsOVRSystem::getInstance()
{  
	return (*m_pInstance);  
}

/************************************************************************************************/
/*
 * シングルトンのポインタを取得
 * @return							シングルトンのポインタ
 */
/************************************************************************************************/
KsOVRSystem* KsOVRSystem::getInstancePtr()
{
	return m_pInstance;
}

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsOVRSystem::KsOVRSystem()
	: m_pDeviceManager( 0 )
{
	setup();
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsOVRSystem::~KsOVRSystem()
{
	shutdown();
}

/************************************************************************************************/
/*
 * OVRセットアップする
 * @retval		ksTRUE				OVRセットアップ成功
 * @retval		ksFALSE				OVRセットアップ失敗
 */
/************************************************************************************************/
KsBool KsOVRSystem::setup()
{
	OVR::System::Init( OVR::Log::ConfigureDefaultLog( OVR::LogMask_All ) );

	m_pDeviceManager = OVR::DeviceManager::Create();

	m_pHMD = m_pDeviceManager->EnumerateDevices<OVR::HMDDevice>().CreateDevice();

	if( m_pHMD )
	{
		m_pSensor = m_pHMD->GetSensor();

		// This will initialize HMDInfo with information about configured IPD,
		// screen size and other variables needed for correct projection.
		// We pass HMD DisplayDeviceName into the renderer to select the
		// correct monitor in full-screen mode.
		if(m_pHMD->GetDeviceInfo(&m_hHMDInfo))
		{
			//RenderParams.MonitorName = hmd.DisplayDeviceName;
			//SConfig.SetHMDInfo(HMDInfo);
		}
	}
	else
	{
		// If we didn't detect an HMD, try to create the sensor directly.
		// This is useful for debugging sensor interaction; it is not needed in
		// a shipping app.
		m_pSensor = m_pDeviceManager->EnumerateDevices<OVR::SensorDevice>().CreateDevice();
	}

	// Create the Latency Tester device and assign it to the LatencyTesterUtil object.
	m_pLatencyTestDevice = m_pDeviceManager->EnumerateDevices<OVR::LatencyTestDevice>().CreateDevice();

	if( m_pLatencyTestDevice )
	{
		m_LatencyUtil.SetDevice( m_pLatencyTestDevice );
	}

	// Make the user aware which devices are present.
	if( m_pHMD == NULL && m_pSensor == NULL )
	{
		KsPrintf("NO HMD DETECTED\nNO SENSOR DETECTED\n");
	}
	else if(m_pHMD == NULL)
	{
		KsPrintf("NO HMD DETECTED\n");
	}
	else if(m_pSensor == NULL)
	{
		KsPrintf("NO SENSOR DETECTED\n");
	}
	else
	{
		KsPrintf("Press F9 for Full-Screen on Rift\n");
	}

	
	if( m_hHMDInfo.HResolution > 0)
	{
		m_width  = m_hHMDInfo.HResolution;
		m_height = m_hHMDInfo.VResolution;
	}

	if( m_pSensor )
	{
		// We need to attach sensor to SensorFusion object for it to receive
		// body frame messages and update orientation. SFusion.GetOrientation()
		// is used in OnIdle() to orient the view.
		m_SensorFusion.AttachToSensor( m_pSensor );

		//m_SensorFusion.SetDelegateMessageHandler(this);

		m_SensorFusion.SetPredictionEnabled(true);
	}

	return ksTRUE;
}

/************************************************************************************************/
/**
 * OVRシャットダウンする
 * @retval		ksTRUE				OVRシャットダウン成功
 * @retval		ksFALSE				OVRシャットダウン失敗
 */
/************************************************************************************************/
KsBool KsOVRSystem::shutdown()
{
	if( m_pSensor )
	{
		m_pSensor->Release();
		m_pSensor = NULL;
	}

	if( m_pDeviceManager )
	{
		m_pDeviceManager->Release();
		m_pDeviceManager = NULL;
	}

	OVR::System::Destroy();

	return ksTRUE;
}


