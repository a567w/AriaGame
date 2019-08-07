/************************************************************************************************/
/** 
 * @file		KsInputSystem.h
 * @brief		���͏���
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSINPUTSYSTEM_H__
#define __KSINPUTSYSTEM_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/


template class ksENGINE_API KsArray< KsPad* >;

/************************************************************************************************/
/**
 * @class		KsInputSystem
 * @brief		���̓}�l�[�W��(�V���O���g���N���X)
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		�Ȃ�
 */
/************************************************************************************************/
class ksENGINE_API KsInputSystem : public KsSingleton< KsInputSystem >
{
	public:
		/**
		 * �C���X�^���X�擾
		 * @return					�C���X�^���X
		 */
		static KsInputSystem&		getInstance();

		/**
		 * �C���X�^���X�擾
		 * @return					�C���X�^���X
		 */
		static KsInputSystem*		getInstancePtr();

	public:
		/**
		 * �R���X�g���N�^
		 */
									KsInputSystem();

		/**
		 * �R���X�g���N�^(����������)
		 * @param	num				�W���C�X�e�B�b�N�h���C�o���T�|�[�g����W���C�X�e�B�b�N��
		 */
									KsInputSystem( KsUInt32 num );

		/**
		 * �f�X�g���N�^
		 */
									~KsInputSystem();

		/**
		 * ����������
		 * @param	num				�W���C�X�e�B�b�N�h���C�o���T�|�[�g����W���C�X�e�B�b�N��
		 */
		void						initialize( KsUInt32 num );

		/*
		 * �J������
		 */
		void						release();

		/**
		 * �X�V����
		 */
		void						update();

		/**
		 * �p�b�h�̃x�^���͂��擾����
		 * @param	index			�p�b�h�ԍ�
		 * @return					���̓f�[�^
		 */
		KsUInt32					getPadNow( KsUInt32 index ) { return m_vpPads[ index ]->m_now; }

		/**
		 * �p�b�h�̃g���K�[�����擾����
		 * @param	index			�p�b�h�ԍ�
		 * @return					���̓f�[�^
		 */
		KsUInt32					getPadTrg( KsUInt32 index ) { return m_vpPads[ index ]->m_trg; }

		/**
		 * �p�b�h�̃����[�X�����擾����
		 * @param	index			�p�b�h�ԍ�
		 * @return					���̓f�[�^
		 */
		KsUInt32					getPadOff( KsUInt32 index ) { return m_vpPads[ index ]->m_off; }

		/**
		 * �p�b�h�̃��[�s�[�����擾����
		 * @param	index			�p�b�h�ԍ�
		 * @return					���̓f�[�^
		 */
		KsUInt32					getPadRpt( KsUInt32 index ) { return m_vpPads[ index ]->m_rpt; }

		/** 
		 * �p�b�h�����擾����
		 * @return					�p�b�h��
		 */
		KsUInt32					getNumPad() const { return m_padNum; }

		/**
		 * �}�E�X�����擾����
		 * @return					�}�E�X���
		 */
		KsMouse*					getMouse() { return m_vpMouses[ 0 ]; }

		/** 
		 * �}�E�X�����擾����
		 * @return					�}�E�X��
		 */
		KsUInt32					getNumMouse() const { return m_vpMouses.size(); }

	private:
		KsBool						m_bInit;			/**< �������t���O		*/
		KsArray< KsPad* >			m_vpPads;			/**< �p�b�h�z��			*/
		KsArray< KsMouse* >			m_vpMouses;			/**< �}�E�X�z��			*/
		KsByte						m_keyData[ 256 ];	/**< �L�[�f�[�^			*/
		KsUInt32					m_padMax;			/**< �ő�p�b�h��		*/
		KsUInt32					m_padNum;			/**< �p�b�h��			*/		
};



#endif /* __KSINPUTSYSTEM_H__ */

