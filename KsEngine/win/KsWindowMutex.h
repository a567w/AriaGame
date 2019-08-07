/*************************************************************************************************/
/** 
 * @file	KsWindowMutex.h
 * @brief	�E�C���h�E
 * @author	Tukasa Kato
 * @date	2003/03/22
 * @since	----/--/--
 * @version	1.0.0
 */
/*************************************************************************************************/
#ifndef __KSWINDOWMUTEX_H__
#define __KSWINDOWMUTEX_H__

/*===============================================================================================*/
/*                                 << �C���N���[�h >>                                             */
/*===============================================================================================*/

/*===============================================================================================*/
/*                                     << ��` >>                                                */
/*===============================================================================================*/


/*************************************************************************************************/
/**
 * �E�C���h�E�~���[�e�b�N�X�N���X
 * @author  kato tukasa
 * @since   2003/03/22
 * @version ----/--/--
 */
/*************************************************************************************************/
class ksENGINE_API KsWindowMutex
{
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsWindowMutex();
		
		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsWindowMutex();

		/**
		 * 0 : ���ɓ����̂��̂͑��݂��Ȃ������L���l�������I
		 * 1 : ���ɓ����̂��̂����݂���B(error)
		 */
		KsBool						open( const KsString& mutexName );

		/**
		 * ���L�����l���ł���܂ő҂�
		 */
		void						wait();
	
		/**
		 * Mutex���������
		 */
		void						release();

	protected:
		HANDLE						m_hMutex;	/**< Mutex �n���h�� */
};


#endif /* __KSWINDOWMUTEX_H__ */

