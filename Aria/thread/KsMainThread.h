/************************************************************************************************/
/** 
 * @file		KsMainThread.cpp
 * @brief		���C���X���b�h
 * @author		Tsukasa Kato
 * @date		2011/07/02
 * @since		2011/07/02
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMAINTHREAD_H__
#define __KSMAINTHREAD_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsGameSystem;

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * ���C���X���b�h
 * @class	KsThread
 * @author  Tsukasa Kato
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class KsMainThread : public KsThread
{
	public:
		/**
		 * �R���X�g���N�^
		 * @param	hInstance			�C���X�^���X
		 * @param	hPrevInstance		�C���X�^���X
		 * @param	lpCmdLine			�R�}���h���C��
		 * @param	nCmdShow			�R�}���h�\��
		 */
										KsMainThread( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, KsInt32 nCmdShow );

		/**
		 * �f�X�g���N�^
		 */
										~KsMainThread();

		/**
		 * �X���b�h�̃��C���֐�
		 * @return	���s�I������
		 */
		virtual KsUInt32				threadMain();


		/**
		 * ���C���X���b�h�̏������J�n����B
		 */
		KsBool							run();

		/**
		 * �����܂�������
		 */
		void							syncWait();

	private:
		KsGameSystem*					m_pGameSystem;			/**< �Q�[���V�X�e��		*/
		KsHandle						m_syncEvent;			/**< �����C�x���g			*/
		KsHandle						m_exitEvent;			/**< �I���C�x���g			*/
};

#endif	/* __KSMAINTHREAD_H__ */

