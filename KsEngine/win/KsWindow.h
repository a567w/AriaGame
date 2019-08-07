/*************************************************************************************************/
/** 
 * @file	KsWindow.h
 * @brief	�E�C���h�E
 * @author	Tukasa Kato
 * @date	2003/03/22
 * @since	----/--/--
 * @version	1.0.0
 */
/*************************************************************************************************/
#ifndef __KSWINDOWS_H__
#define __KSWINDOWS_H__

/*===============================================================================================*/
/*                                 << �C���N���[�h >>                                             */
/*===============================================================================================*/
#include <windows.h>
#include <winnls32.h>
#include <commctrl.h>
#include <Shlobj.h>

/*===============================================================================================*/
/*                                     << ��` >>                                                */
/*===============================================================================================*/


/*************************************************************************************************/
/**
 * �E�C���h�E�N���X<BR>
 * @author  kato tukasa
 * @since   2003/03/22
 * @version ----/--/--
 */
/*************************************************************************************************/
class ksENGINE_API KsWindow
{
	protected:
		KsWindowParam					m_windowParam;		/**< �E�C���h�E�̐����p�����[�^		*/
		WNDPROC							m_pWndProc;			/**< �E�C���h�v���V�[				*/
		HWND							m_hWnd;				/**< �E�C���h�E�n���h��				*/
		HMENU							m_hMenu;			/**< ���j���[�̃n���h��				*/
		KsBool							m_bMinimized;		/**< �E�C���h�E�̍ŏ����̃t���O		*/
		KsBool							m_bFullScreen;		/**< �t���X�N���[�����ǂ����̃t���O	*/
		KsBool							m_bCenter;			/**< */
		KsUInt32						m_flags;			/**< �E�C���h�E�̏�ԃt���O			*/
	
		//KsHookList					m_hookList;

	public:
		/**
		 * �R���X�g���N�^
		 */
										KsWindow() {}

		/**
		 * �R���X�g���N�^(�E�C���h�E����)
		 * @param		param			�E�C���h�E�����̂��߂̃p�����[�^
		 * @param		hParent			�e�E�C���h�E�̃n���h��
		 * @retval		ksTRUE			����
		 * @retval		ksFALSE			���s
		 */
										KsWindow( const KsWindowParam& param, HWND hParent = NULL, void* pUserData = NULL );

		/**
		 * �f�X�g���N�^
		 */
		virtual							~KsWindow() {}

		/**
		 * �E�C���h�E�̃p�����[�^���擾����
		 * @return						�E�C���h�E�p�����[�^
		 */
		const KsWindowParam&			getWindowParam()				{ return m_windowParam; }

		/**
		 * �E�C���h�E�̕����擾����
		 * @return						�E�C���h�E�̕�
		 */
		KsInt32							getWidth()				const	{ return m_windowParam.m_sizeX;	 }

		/**
		 * �E�C���h�E�̍������擾����
		 * @return						�E�C���h�E�̍���
		 */
		KsInt32							getHeight()				const	{ return m_windowParam.m_sizeY;	 }

		/**
		 * �E�C���h�E�̃n���h�����擾����
		 * @return						�E�C���h�E�̃n���h��
		 */
		HWND							getHWnd()				const	{ return m_hWnd; }

		/**
		 * ���j���[�̃n���h�����擾����
		 * @return						���j���[�̃n���h��
		 */
		HMENU							getHMenu()				const	{ return m_hMenu; }

		/**
		 * �E�C���h�E���ŏ�������Ă��邩���`�F�b�N����
		 * @retval		ksTRUE			�ŏ�������Ă���
		 * @retval		ksTRUE			�ŏ�������ĂȂ�
		 */
		KsBool							isMinmimized()			const	{ return m_bMinimized; }

		/**
		 * �t���X�N���[��������Ă��邩���`�F�b�N����
		 * @retval		ksTRUE			�t���X�N���[��������Ă���
		 * @retval		ksTRUE			�t���X�N���[��������ĂȂ�
		 */
		KsBool							isFullScreen()			const	{ return m_bFullScreen; }

		/**
		 * ���j���[�̃n���h�����Z�b�g����
		 * @param		hMenu			���j���[�̃n���h��
		 */
		void							setHMenu( HMENU hMenu )	{ m_hMenu = hMenu; }

		/**
		 * �E�C���h�E����
		 * @param		param			�E�C���h�E�����̂��߂̃p�����[�^
		 * @param		hParent			�e�E�C���h�E�̃n���h��
		 * @retval		ksTRUE			����
		 * @retval		ksFALSE			���s
		 */
		KsBool							create( const KsWindowParam& param, HWND hParent = NULL, void* pUserData = NULL );

		/**
		 * ���b�Z�[�W���[�v
		 * @return		���b�Z�[�W�v��
		 */
		KsInt32							messageLoop();

		/**
		 * �E�C���h�E�ʒu���Z�b�g
		 * @param		x				�E�C���h�E���Z�b�g����X���W
		 * @param		y				�E�C���h�E���Z�b�g����Y���W
		 */
		void							setPos( KsInt32 x, KsInt32 y );

		/**
		* �E�C���h�E�𒆉��ɃZ�b�g
		*/
		void							setCenter();

	protected:
		/**
		 * �E�C���h�E�v���V�[�W��
		 * @param		hWnd			�E�C���h�E�̃n���h��
		 * @param		uMsg			�E�C���h�E�̃��b�Z�[�W
		 * @param		wParam			�p�����[�^
		 * @param		lParam			�p�����[�^
		 * @return						�R�[���o�b�N
		 */
		static LRESULT CALLBACK			wndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
};


#endif	/* __KSWINDOW_H__ */

