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
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
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
		friend class KsUpdate;
		friend class KsDraw;
		friend class KsTask;
	public:
		/**
		 * �R���X�g���N�^
		 * @param		numUpdateList		�X�V���X�g��
		 * @param		numDrawList			�`�惊�X�g��
		 */
											KsTaskManager( KsUInt32 numUpdateList, KsUInt32 numDrawList );

		/**
		 * �f�X�g���N�^
		 */
		virtual								~KsTaskManager();

		/**
		 * ���ׂĂ̏��������s
		 * @param		pParam				�����ł킽�����p�����[�^���^�X�N��execute��render�̈����ɓn��
		 *									�f�t�H���g�ł́ANULL���ݒ肳��Ă���B
		 */
		virtual void						run( void* pParam=NULL );

		/**
		 * �X�V����
		 * @param		pParam				�p�����[�^
		 */
		virtual void						execute( void* pParam );

		/**
		 * �`�揈��
		 * @param		pParam				�p�����[�^
		 */
		virtual void						render( void* pParam );

		/**
		 * 
		 */
		virtual void						addTask( KsTask* pTask );

		/**
		 * 
		 */
		virtual void						addUpdate( KsUpdate* pUpdate );

		/**
		 * 
		 */
		virtual void						addDraw( KsDraw* pDraw );


		virtual void						removeTask( KsTask* pTask );

		/**
		 * 
		 */
		virtual void						removeUpdate( KsUpdate* pUpdate );

		/**
		 * 
		 */
		virtual void						removeDraw( KsDraw* pDraw );

		virtual void						destroyTask( KsTask* pTask );

		/**
		 * 
		 */
		virtual void						destroyUpdate( KsUpdate* pUpdate );

		/**
		 * 
		 */
		virtual void						destroyDraw( KsDraw* pDraw );

		virtual void						destroyAll();
	protected:
		/**
		 * �`��J�n
		 */
		virtual void						begineRender();

		/**
		 * �`��I��
		 */
		virtual void						endRender();

	protected:
		KsUInt32							m_numUpdateList;	/**< */
		KsUInt32							m_numDrawList;		/**< */
		KsUpdateList*						m_pUpdates;			/**< �X�V���X�g	*/
		KsDrawList*							m_pDraws;			/**< �`�惊�X�g	*/
};


#endif /* __KSTASKMANAGER_H__ */

