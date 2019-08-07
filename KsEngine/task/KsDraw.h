/************************************************************************************************/
/** 
 * @file		KsDraw.h
 * @brief		�`��^�X�N
 * @author		Tsukasa Kato
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSDRAW_H__
#define __KSDRAW_H__

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
 * @class		KsDraw
 * @brief		�`��^�X�N
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
class ksENGINE_API KsDraw
{
		friend class KsTaskManager;
		friend class KsDrawList;
	
	public:
		/**
		 * �R���X�g���N�^
		 * @brief	0�ŏ����������
		 */
											KsDraw();

		/**
		 * �R���X�g���N�^
		 * @param	order					�`��I�[�_�[
		 */
											KsDraw( KsUInt32 order );

		/**
		 * �f�X�g���N�^
		 */
		virtual								~KsDraw();

		/**
		 * �^�X�N�̎���ID���擾����
		 * @return		�^�X�N��ID���擾����
		 */
		KsUInt32							getDrawID() const { return m_drawID; }

		/**
		 * �I�[�_�[���擾����
		 * @return		�`��I�[�_�[���擾����
		 */
		KsUInt32							getDrawOrder() const { return m_drawOrder; }

		/**
		 * �`�悷�邩�ǂ������Z�b�g����
		 * @param		drawActive		�`�悷�邩�ǂ������Z�b�g����
		 */
		void								setActiveDraw( KsBool drawActive ) { m_drawActive = drawActive; }

		/**
		 * �`�悷�邩�ǂ������擾����
		 * @return		�`�悷�邩�ǂ������擾����
		 */
		KsBool								isActiveDraw() const { return m_drawActive; }

		/**
		 * �`��v���C�I���e�B���擾����
		 * @return		�`��v���C�I���e�B���擾����
		 */
		KsUInt32							getDrawPriority() const { return m_drawPriority; }

	protected:
		/**
		 * ����������(�}�l�[�W���ɓo�^���ꂽ�Ƃ��ɓo�^)
		 * @param		pParam				�p�����[�^
		 */
		virtual void*						initializeGraphics( void* pParam ) = 0;

		/**
		 * �`�揈��
		 * @param		pParam				�p�����[�^
		 */
		virtual void*						draw( void* pParam ) = 0;

		/**
		 * �㏈���֐��Ń������[����폜�����Ƃ��ɌĂ΂��
		 * @param		pParam				�p�����[�^
		 */
		virtual void*						terminateGraphics( void* pParam ) = 0;

		/**
		 * �j������(�}�l�[�W�����ō폜����)
		 */
		virtual void						destroyDraw();

	protected:
		KsUInt32							m_drawID;		/**< �^�X�N����ID(�����I�Ɋ���U��?)	*/
		KsUInt32							m_drawOrder;	/**< �`��I�[�_�[					*/
		KsUInt32							m_drawPriority;	/**< �`��v���C�I���e�B				*/
		KsBool								m_drawActive;	/**< �`��A�N�e�B�u�t���O				*/
		KsBool								m_drawFlags;	/**< �`��t���O						*/
		KsDraw*								m_pDrawPrev;	/**< �`��O�����X�g					*/
		KsDraw*								m_pDrawNext;	/**< �`�������X�g					*/
		KsTaskManager*						m_pDrawManager;	/**< �^�X�N�}�l�[�W��					*/
};

#endif /* __KSDRAW_H__ */

