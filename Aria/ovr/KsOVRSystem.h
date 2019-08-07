/************************************************************************************************/
/** 
 * @file		KsOVRSystem.h
 * @brief		OVR�V�X�e��
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSOVRSYSTEM_H__
#define __KSOVRSYSTEM_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsOVRSystem
 * @brief		�Q�[���R���t�B�b�O
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsOVRSystem : public KsSingleton< KsOVRSystem >
{
	public:
		/**
		 * �V���O���g���̎Q�Ƃ��擾
		 * @return							�V���O���g���̎Q��
		 */
		static KsOVRSystem&					getInstance();
		
		/**
		 * �V���O���g���̃|�C���^���擾
		 * @return							�V���O���g���̃|�C���^
		 */
		static KsOVRSystem*					getInstancePtr();

	public:
		/**
		 * �R���X�g���N�^
		 */
											KsOVRSystem();

		/**
		 * �f�X�g���N�^
		 */
		virtual								~KsOVRSystem();

		/**
		 * OVR�Z�b�g�A�b�v����
		 * @retval		ksTRUE				OVR�Z�b�g�A�b�v����
		 * @retval		ksFALSE				OVR�Z�b�g�A�b�v���s
		 */
		KsBool								setup();

		/**
		 * OVR�V���b�g�_�E������
		 * @retval		ksTRUE				OVR�V���b�g�_�E������
		 * @retval		ksFALSE				OVR�V���b�g�_�E�����s
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

