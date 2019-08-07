/************************************************************************************************/
/** 
 * @file		KsUpdate.h
 * @brief		�X�V����
 * @author		Tsukasa Kato
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSUPDATE_H__
#define __KSUPDATE_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * �X�V�����^�X�N
 * @class		KsUpdate
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
class ksENGINE_API KsUpdate
{
		friend class KsTaskManager;
		friend class KsUpdateList;
	
	public:
		/**
		 * �R���X�g���N�^
		 * @brief	0�ŏ����������
		 */
											KsUpdate();

		/**
		 * �R���X�g���N�^
		 * @param	order					�X�V�I�[�_�[
		 */
											KsUpdate( KsUInt32 order );

		/**
		 * �f�X�g���N�^
		 */
		virtual								~KsUpdate();

		/**
		 * �^�X�N�̎���ID���擾����
		 * @return		�^�X�N��ID���擾����
		 */
		KsUInt32							getUpdateID() const { return m_updateID; }

		/**
		 * �I�[�_�[���擾����
		 * @return		�X�V�I�[�_�[���擾����
		 */
		KsUInt32							getUpdateOrder() const { return m_updateOrder; }

		/**
		 * �X�V���邩�ǂ������Z�b�g����
		 * @param		updateActive		�X�V���邩�ǂ������Z�b�g����
		 */
		void								setActiveUpdate( KsBool updateActive ) { m_updateActive = updateActive; }

		/**
		 * �X�V���邩�ǂ������擾����
		 * @return		�X�V���邩�ǂ������擾����
		 */
		KsBool								isActiveUpdate() const { return m_updateActive; }

		/**
		 * �X�V�v���C�I���e�B���擾����
		 * @return		�X�V�v���C�I���e�B���擾����
		 */
		KsUInt32							getUpdatePriority() const { return m_updatePriority; }

	protected:
		/**
		 * ����������(�}�l�[�W���ɓo�^���ꂽ�Ƃ��ɓo�^)
		 * @param		pParam				�p�����[�^
		 */
		virtual void*						initialize( void* pParam ) = 0;

		/**
		 * �X�V����
		 * @param		pParam				�p�����[�^
		 */
		virtual void*						update( void* pParam ) = 0;

		/**
		 * �㏈���֐��Ń������[����폜�����Ƃ��ɌĂ΂��
		 * @param		pParam				�p�����[�^
		 */
		virtual void*						terminate( void* pParam ) = 0;

		/**
		 * �j������(�}�l�[�W�����ō폜����)
		 */
		virtual void						destroyUpdate();

	protected:
		KsUInt32							m_updateID;			/**< �^�X�N����ID(�����I�Ɋ���U��?)	*/
		KsUInt32							m_updateOrder;		/**< �X�V�I�[�_�[					*/
		KsUInt32							m_updatePriority;	/**< �X�V�v���C�I���e�B				*/
		KsBool								m_updateActive;		/**< �X�V�A�N�e�B�u�t���O				*/
		KsBool								m_updateFlags;		/**< �X�V�t���O						*/
		KsUpdate*							m_pUpdatePrev;		/**< �X�V�O�����X�g					*/
		KsUpdate*							m_pUpdateNext;		/**< �X�V������X�g					*/
		KsTaskManager*						m_pUpdateManager;	/**< �^�X�N�}�l�[�W��					*/
};


#endif /* __KSUPDATE_H__ */

