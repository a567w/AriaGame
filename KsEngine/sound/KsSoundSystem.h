/************************************************************************************************/
/** 
 * @file		KsSoundSystem.h
 * @brief		�T�E���h�V�X�e��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSSOUNDSYSTEM_H__
#define __KSSOUNDSYSTEM_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                          */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsSoundSystem
 * @brief		�T�E���h�V�X�e��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsSoundSystem
{
	public:
		/**
		 * �R���X�g���N�^
		 */
											KsSoundSystem();

		/**
		 * �f�X�g���N�^
		 */
		virtual								~KsSoundSystem();

		/**
		 * ����������
		 * @param		hWnd				�E�C���h�E�̃n���h��
		 * @retval		ksTRUE				����������
		 * @retval		ksFALSE				���������s
		 */
		virtual KsBool						initialize( void* pParam ) = 0;

		/**
		 * �X�V����
		 * @retval		ksTRUE				�X�V����
		 * @retval		ksFALSE				�X�V���s
		 */
		virtual KsBool						update() = 0;

		/**
		 * �㏈��
		 * @retval		ksTRUE				�㏈������
		 * @retval		ksFALSE				�㏈�����s
		 */
		virtual KsBool						terminate() = 0;

		/**
		 *
		 */
		virtual KsSoundData*				createSoundDataMemory( KsChar* strFile, KsUInt32 seconds, KsUInt32 sampleRate, KsUInt32 channels, KsUInt32 bits ) = 0;

		virtual KsSoundData*				createSoundDataStreaming( KsChar* strFile, KsUInt32 seconds, KsUInt32 sampleRate, KsUInt32 channels, KsUInt32 bits ) = 0;
};

#endif		/* __KSSOUNDSYSTEM_H__ */

