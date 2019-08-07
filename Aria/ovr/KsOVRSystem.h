/************************************************************************************************/
/** 
 * @file		KsOVRSystem.h
 * @brief		OVRシステム
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSOVRSYSTEM_H__
#define __KSOVRSYSTEM_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsOVRSystem
 * @brief		ゲームコンフィッグ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsOVRSystem : public KsSingleton< KsOVRSystem >
{
	public:
		/**
		 * シングルトンの参照を取得
		 * @return							シングルトンの参照
		 */
		static KsOVRSystem&					getInstance();
		
		/**
		 * シングルトンのポインタを取得
		 * @return							シングルトンのポインタ
		 */
		static KsOVRSystem*					getInstancePtr();

	public:
		/**
		 * コンストラクタ
		 */
											KsOVRSystem();

		/**
		 * デストラクタ
		 */
		virtual								~KsOVRSystem();

		/**
		 * OVRセットアップする
		 * @retval		ksTRUE				OVRセットアップ成功
		 * @retval		ksFALSE				OVRセットアップ失敗
		 */
		KsBool								setup();

		/**
		 * OVRシャットダウンする
		 * @retval		ksTRUE				OVRシャットダウン成功
		 * @retval		ksFALSE				OVRシャットダウン失敗
		 */
		KsBool								shutdown();

	protected:
		OVR::DeviceManager*					m_pDeviceManager;
		OVR::HMDDevice*						m_pHMD;
		OVR::SensorDevice*					m_pSensor;;
		OVR::HMDInfo						m_hHMDInfo;
		OVR::LatencyTestDevice*				m_pLatencyTestDevice;
		OVR::Util::LatencyTest				m_LatencyUtil;
		OVR::SensorFusion					m_SensorFusion;
		KsUInt32							m_width;
		KsUInt32							m_height;
};

#endif /* __KSOVRSYSTEM_H__ */

