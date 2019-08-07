/*************************************************************************************************/
/** 
 * @file	KsWindowUtility.h
 * @brief	Windows�֌W���[�e�B���e�B
 * @author	Tukasa Kato
 * @date	2003/03/22
 * @since	----/--/--
 * @version	1.0.0
 */
/*************************************************************************************************/
#ifndef __KSWINDOWUTILITY_H__
#define __KSWINDOWUTILITY_H__

/*===============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*===============================================================================================*/

/*************************************************************************************************/
/**
 * �E�C���h�E���[�e�B���e�B�[�N���X<BR>
 * @author  kato tukasa
 * @since   2003/03/22
 * @version ----/--/--
 */
/*************************************************************************************************/
class ksENGINE_API KsWindowUtility
{
	public:
		/**
		 * �^�X�N�o�[���������f�X�N�g�b�v�̃T�C�Y���擾����
		 * @param		pRect		(OUT)�T�C�Y���擾����\���̂̃|�C���^
		 */
		static void			getDeskTopClientRect( RECT* pRect );

		/**
		 * �f�X�N�g�b�v�̃T�C�Y���擾����
		 * @param		pRect		(OUT)�T�C�Y���擾����\���̂̃|�C���^
		 */
		static void			getDeskTopWindowRect( RECT* pRect );

		/**
		 * GetNativeSystemInfo���b�p�[�֐�
		 * @parm	lpSystemInfo	(OUT)�V�X�e�������擾����\���̂̃|�C���^
		 * @retval	ksTRUE			�擾����
		 * @retval	ksFALSE			�擾���s
		 * @note GetNativeSystemInfo��Windows XP�ȍ~�ŃT�|�[�g����Ă���B
		 *		 ���̂���Windows 2000�ȑO�ł�ksFALSE���Ԃ�
		 */
		static KsBool		getNativeSystemInfo( LPSYSTEM_INFO lpSystemInfo );

		/**
		 * �v���Z�b�T�̐����擾����
		 * @return	�v���Z�b�T�̐�
		 */
		static KsUInt32		getNumProcessor();

		/**
		 * �������E�C���h�E���A�N�e�B�u�ɂ���
		 */
		static KsBool		activeFindWindow( const KsChar* pClassName, const KsChar* pWindowName );
};


#endif /* __KSWINDOWUTILITY_H__ */

