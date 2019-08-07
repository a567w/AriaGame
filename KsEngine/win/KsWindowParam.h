/*************************************************************************************************/
/** 
 * @file	KsWindowParam.h
 * @brief	�E�C���h�E�p�����[�^
 * @author	Tukasa Kato
 * @date	2003/03/22
 * @since	----/--/--
 * @version	1.0.0
 */
/*************************************************************************************************/
#ifndef __KSWINDOWSPARAM_H__
#define __KSWINDOWSPARAM_H__

/*===============================================================================================*/
/*                                 << �C���N���[�h >>                                             */
/*===============================================================================================*/

/*===============================================================================================*/
/*                                     << ��` >>                                                */
/*===============================================================================================*/
#define ksWINDOW_DEFAULT_SIZE_X	( 1280 )		/**< �E�C���h�E�̃f�t�H���g�̕�	*/
#define ksWINDOW_DEFAULT_SIZE_Y	(  720 )		/**< �E�C���h�E�̃f�t�H���g�̍���	*/
#define ksWINDOW_DEFAULT_STYLE	( WS_VISIBLE | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU )


/*************************************************************************************************/
/**
 * �E�C���h�E�A�v���P�[�V�����̃p�����[�^�N���X<BR>
 * @author  kato tukasa
 * @since   2003/03/22
 * @version ----/--/--
 */
/*************************************************************************************************/
class ksENGINE_API KsWindowParam
{
	public:
		KsString						m_caption;		/**< �L���v�V����				*/
		KsString						m_className;	/**< �N���X��					*/
		KsInt32							m_posX;			/**< �E�C���h�E��X���W			*/
		KsInt32							m_posY;			/**< �E�C���h�E��Y���W			*/
		KsInt32							m_sizeX;		/**< �E�C���h�E�̕�				*/
		KsInt32							m_sizeY;		/**< �E�C���h�E�̍���				*/
		KsUInt32						m_style;		/**< �E�C���h�E�̃X�^�C��			*/
		KsUInt32						m_styleEx;		/**< �g���E�C���h�E�X�^�C��		*/
		//WNDPROC						m_pCallback;	/**< �v���V�[�W��				*/

	public:
		/**
		 * �R���X�g���N�^
		 */
										KsWindowParam();

		/**
		 * �����t���R���X�g���N�^
		 * @param		caption			�L���v�V����
		 * @param		className		�o�^����N���X�l�[��
		 * @param		sizeX			�E�C���h�E�̕�
		 * @param		sizeY			�E�C���h�E�̍���
		 * @param		style			�E�C���h�E�̃X�^�C��
		 */
										KsWindowParam( const KsString& caption, const KsString& className, KsInt32 posX, KsInt32 posY, KsInt32 sizeX, KsInt32 sizeY, KsUInt32 style, KsUInt32 styeleEx=0 );

		/**
		 * �f�X�g���N�^
		 */
		virtual							~KsWindowParam();

		/**
		 * �p�����[�^���Z�b�g����
		 * @param		caption			�L���v�V����
		 * @param		className		�o�^����N���X�l�[��
		 * @param		sizeX			�E�C���h�E�̕�
		 * @param		sizeY			�E�C���h�E�̍���
		 * @param		style			�E�C���h�E�̃X�^�C��
		 */
		void							setParam( const KsString& caption, const KsString& className, KsInt32 posX, KsInt32 posY, KsInt32 sizeX, KsInt32 sizeY, KsUInt32 style, KsUInt32 styleEx=0 );
};


#endif	/* __KSWINDOWSPARAM_H__ */

