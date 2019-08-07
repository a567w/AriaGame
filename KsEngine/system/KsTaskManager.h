/************************************************************************************************/
/** 
 * @file		KsTaskManager.h
 * @brief		��{�^�X�N
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSTASKMANAGER_H__
#define __KSTASKMANAGER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsTaskBase.h"
#include "KsOT.h"
#include "KsSingleton.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * 
 * @class		KsTaskManager
 * @brief		��{�^�X�N�}�l�[�W���N���X
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		�Ȃ�
 */
/************************************************************************************************/
class ksENGINE_API KsTaskManager
{
		friend class KsTaskBase;
	public:
		/**
		 * �R���X�g���N�^
		 * @brief	0�ŏ����������
		 */
											KsTaskManager();

		/**
		 * �f�X�g���N�^
		 */
		virtual							~KsTaskManager();

		/**
		 * ���[�g�^�X�N���Z�b�g����(���̂Ƃ����̃^�X�N�ɂǂ̃��[�U�[�f�[�^���Z�b�g����)
		 * ���̂Ƃ����`�惊���N���Đݒ肳���
		 * @param		pTask				�Z�b�g���郋�[�g�^�X�N
		 * @return							�O�̃��[�g�^�X�N�̃|�C���^��Ԃ�(�Ȃ��Ƃ���NULL��Ԃ�)
		 */
		KsTaskBase*								setRootTask( KsTaskBase* pTask );

		/**
		 * ���[�g�^�X�N���Z�b�g����
		 * @return							���[�g�^�X�N�̃|�C���^
		 */
		KsTaskBase*								getRootTask();

		/**
		 * ���s����
		 * @param		pParam				�p�����[�^
		 */
		virtual void						execute( void* pParam );

		/**
		 * �`�揈��
		 * @param		pParam				�p�����[�^
		 */
		virtual void						render( void* pParam );

		/**
		 * �X�V����
		 * @param		pParam				�p�����[�^
		 */
		virtual void						update( void* pParam );

		/**
		 * ���ׂĂ̏��������s
		 * @param		pParam				�����ł킽�����p�����[�^���^�X�N��execute��render�̈����ɓn��
		 *									�f�t�H���g�ł́ANULL���ݒ肳��Ă���B
		 */
		virtual void						run( void* pParam=NULL );

		/**
		 * �폜����
		 * @param		pTask				�폜����^�X�N�̃|�C���^
		 */
		void								kill( KsTaskBase* pTask, void* pParam );

		/**
		 * ���ׂč폜
		 */
		void								allKill( void* pParam );

		/**
		 * �R�[���o�b�N�֐�
		 */
		void								allCallback( KsTaskCallback callback, void* pUserData=0 );

		/**
		 * �R�[���o�b�N�֐�
		 */
		void								allChildCallback( KsTaskBase* pTask, KsTaskCallback callback, void* pUserData=0 );

	protected:
		/**
		 * �^�X�N���s�p�ċA�֐�
		 */
		void								taskExecute( KsTaskBase* pTask, void* pUserData );

		/**
		 * �`��J�n
		 */
		virtual void						begineRender();

		/**
		 * �`��I��
		 */
		virtual void						endRender();

	protected:
		KsTaskBase*								m_pRootTask;					/**< ���[�g�^�X�N		*/
		KsTaskCallback						m_pCallback;					/**< �R�[���o�b�N�֐�	*/
		KsOT								m_renderTbl;					/**< �`�惊���N�e�[�u��	*/

		static void*						setManagerCallback( KsTaskBase* pTask, void* pParam );
};



#endif /* __KSTASKMANAGER_H__ */

