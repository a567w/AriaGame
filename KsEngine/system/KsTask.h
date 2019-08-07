/************************************************************************************************/
/** 
 * @file		KsTask.h
 * @brief		��{�^�X�N
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSTASK_H__
#define __KSTASK_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                          */
/*==============================================================================================*/
#include "KsCore.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/
#define ksTASK_NAME_LENGTH			( 16 )			/**< �^�X�N�̖��O�̍ő咷( 15���� + '\0' )	*/
#define ksTASK_ORDER_DEFAULT		(  4 )			/**< �f�t�H���g�̃^�X�N�I�[�_�[				*/


/************************************************************************************************/
/**
 * @enum	�^�X�N�̃^�C�v
 */
/************************************************************************************************/
enum ksTASK_TYPE
{
	ksTASK_TYPE_BASE    = 0,				/**< ��{�^�X�N				*/
	ksTASK_TYPE_SCENE   = 1,				/**< �V�[���^�X�N			*/
	ksTASK_TYPE_SPRITE  = 2,				/**< �X�v���C�g�^�X�N		*/
	ksTASK_TYPE_SHADOW  = 3,				/**< �e�p�^�X�N				*/
	ksTASK_TYPE_MANAGER = 4,				/**< ����^�X�N				*/
	ksTASK_TYPE_DEBUG   = 16,				/**< �f�o�b�N�p�^�X�N		*/
	ksTASK_TYPE_CAMERA  = 0xffff,
};

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * ��{�^�X�N�N���X
 * @class		KsTaskBase
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
class ksENGINE_API KsTaskBase
{
		friend class KsTaskManager;
	
	public:
		/**
		 * �R���X�g���N�^
		 * @brief	0�ŏ����������
		 */
											KsTaskBase();

		/**
		 * �R���X�g���N�^
		 * @param	order					�`��I�[�_�[
		 */
											KsTaskBase( KsUInt32 order );

		/**
		 * �f�X�g���N�^
		 */
		virtual							~KsTaskBase();

		/**
		 * �q�^�X�N��ǉ�����
		 * @param		pTask				�ǉ�����q�^�X�N�̃|�C���^
		 * @param		pUserData			���[�U�[�f�[�^
		 * @note		���[�U�[�f�[�^��NULL�̂Ƃ��́A�}�l�[�W���̎��s�����̂Ƃ���,
		 *				�}�l�[�W���ɓn���ꂽ���[�U�[�f�[�^�����[�U�[�f�[�^�ɓn����ď����������B
		 *				�������A���̏ꍇ�AaddChild�����Ƃ��ɂ́A���������Ă΂�Ȃ��B���̂��߁A
		 *				���[�U�[�f�[�^��NULL�ȊO������Ƃ��̃��[�U�[�f�[�^���g�p����addChild�����Ƃ���
		 *				�ǉ����ꂽ�^�X�N�̏������������Ă΂��B
		 */
		void								add( KsTaskBase* pTask, void* pUserData=NULL );

		/**
		 * �����̃^�X�N���Ƃ�͂���(�K�w�́A�����ɂ����܂�)
		 */
		void								detach();

		/**
		 * ������艺�̊K�w����^�X�N���폜����(�폜�t���O���A����)
		 */
		void								remove();

		/**
		 * ������艺�̊K�w����^�X�N���폜����(�폜�t���O���A����)
		 */
		void								destroy();

		/**
		 * ID(����������艺�̊K�w�����v����^�X�N����������)
		 * @param		id					��������ID
		 */
		KsTaskBase*							find( KsUInt32 id );

		/**
		 * ���O����(����������艺�̊K�w�����v����^�X�N����������)
		 *
		 */
		KsTaskBase*							find( const KsChar* name );

		/**
		 * �^�X�N�����Z�b�g����
		 * @param		string				�^�X�N��
		 */
		void								setName( const KsChar* string );

		/**
		 * �^�X�N�̎���ID���Z�b�g����(��{�I�ɂ͂��Ԃ�Ȃ��悤�ɂ���)
		 * @param		id					�^�X�N��ID
		 */
		void								setID( KsUInt32 id );

		/**
		 * �^�X�N�����擾����
		 * @return		�^�X�N���̕�����( �Œ�15���� + '\0' )
		 */
		const KsChar*						getName();

		/**
		 * �^�X�N�̎���ID���擾����
		 * @return		�^�X�N��ID���擾����
		 */
		KsUInt32							getID() const;


		/**
		 * �^�X�N�̃^�C�v���擾����
		 */
		ksTASK_TYPE							getType() const;

		/**
		 * �D�揇�ʂ��Z�b�g����
		 * @return							�v���C�I���e�B
		 */
		KsTaskPRIORITY						getPriority() const;

		/**
		 * �I�_�[���擾����
		 */
		KsUInt32							getOrder() const;

	protected:
		/**
		 * ����������(�}�l�[�W���ɓo�^���ꂽ�Ƃ��ɓo�^)
		 * @param		pParam				�p�����[�^
		 */
		virtual void*						initialize( void* pParam ) = 0;

		/**
		 * �^�X�N�̎��s
		 * @param		pParam				�p�����[�^
		 */
		virtual void*						update( void* pParam ) = 0;

		/**
		 * �`�揈��
		 * @param		pParam				�p�����[�^
		 */
		virtual void*						draw( void* pParam ) = 0;

		/**
		 * �㏈���֐��Ń������[����폜�����Ƃ��ɌĂ΂��
		 * @param		pParam				�p�����[�^
		 */
		virtual void*						terminate( void* pParam ) = 0;

	protected:
		KsChar								m_name[ ksTASK_NAME_LENGTH ];		/**< �^�X�N���̍ő咷					*/
		KsUInt32							m_id;								/**< �^�X�N����ID(�����I�Ɋ���U��?)	*/
		ksTASK_TYPE							m_type;								/**< �^�X�N�̃^�C�v(���)				*/

		KsReal								m_wait;													
		KsTaskParam							m_UpdateParam;
		KsTaskParam							m_DrawParam;
		KsRenderCommandBuffer*				
		KsTaskManager*						m_pManager;							/**< �o�^����Ă���}�l�[�W���̃|�C���^	*/
};

class KsTaskParam
{


	KsBool			m_bActive;		
	KsUInt32		m_order;
	KsTaskBase*		m_pPrev;
	KsTaskBase*		m_pNext;


/**< �E�G�C�g�^�C�}�[					*/
/**< �e�^�X�N�̃|�C���^					*/
/**< �q�^�X�N�̃|�C���^					*/
/**< �`�惊���N�O						*/
/**< �`�惊���N��						*/







}

#endif /* _KSTASK_H__ */

