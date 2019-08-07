/************************************************************************************************/
/** 
 * @file		KsRenderThread.h
 * @brief		�`��X���b�h
 * @author		Tsukasa Kato
 * @date		2011/07/02
 * @since		2011/07/02
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSRENDERTHREAD_H__
#define __KSRENDERTHREAD_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsDeferredRender;

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * �`��X���b�h
 * @class	KsRenderThread
 * @author  Tsukasa Kato
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class KsRenderThread : public KsThread
{
	public:
		/**
		 * �R���X�g���N�^
		 */
										KsRenderThread( KsRenderSystem* pRenderSystem, KsDeferredRender* pDeferredRender );

		/**
		 * �f�X�g���N�^
		 */
										~KsRenderThread();

		/**
		 * ���s����
		 */
		KsBool							run();

		/**
		 * �X���b�h�̃��C���֐�
		 * @return	���s�I������
		 */
		virtual KsUInt32				threadMain();

		/**
		 * �X���b�h�`��J�n����
		 */
		void							startBeginRender();

		/**
		 * �`��I���C�x���g��҂�
		 */
		void							waitEndRender();
		
		/**
		 * �R�}���h���X�g���擾����
		 * @return	�R�}���h���X�g�̃|�C���^
		 */
		KsCommandList*					getCommandList() { return m_pCommandList; }

	private:
		KsHandle						m_syncEvent;			/**< �����C�x���g				*/
		KsHandle						m_beginRenderEvent;		/**< �`��J�n�C�x���g				*/
		KsHandle						m_endRenderEvent;		/**< �`��I���C�x���g				*/
		KsBool							m_bThreadLoop;			/**< �X���b�h���[�v				*/
		KsMainThread*					m_pMainThread;			/**< ���C���X���b�h				*/

		KsRenderSystem*					m_pRenderSystem;		/**< �`��V�X�e��				*/
		KsDeferredRender*				m_pDeferredRender;		/**< �f�B�t�@�[�h�`��V�X�e��		*/
		KsBool							m_bClearState;			/**< �X�e�[�g���N���A����			*/
		KsBool							m_bRestoreState;		/**< �X�e�[�g���N���A����			*/
		KsRenderContext*				m_pRenderContext;		/**< �`��R���e�L�X�g(�x��)		*/
		KsCommandList*					m_pCommandList;			/**< �`��R�}���h���X�g			*/

		KsDepthStencilState*			m_pDepthState;			/**< ���X�^���C�Y�X�e�[�g			*/
};


#endif	/* __KSRENDERTHREAD_H__ */


