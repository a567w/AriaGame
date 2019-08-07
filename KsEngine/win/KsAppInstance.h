/*************************************************************************************************/
/** 
 * @file	KsAppInstance.h
 * @brief	�A�v���P�[�V�����C���X�^���X
 * @author	Tukasa Kato
 * @date	2003/03/22
 * @since	----/--/--
 * @version	1.0.0
 */
/*************************************************************************************************/
#ifndef __KSAPPINSTANCE_H__
#define __KSAPPINSTANCE_H__

/*===============================================================================================*/
/*                                 << �C���N���[�h >>                                             */
/*===============================================================================================*/

/*===============================================================================================*/
/*                                     << ��` >>                                                */
/*===============================================================================================*/


/*************************************************************************************************/
/**
 * @class	KsAppInstance
 * @brief	�E�C���h�E�A�v���P�[�V�����̃C���X�^���X�N���X
 * @author  kato tukasa
 * @since   2003/03/22
 * @version ----/--/--
 */
/*************************************************************************************************/
class ksENGINE_API KsAppInstance
{
	public:
		static HINSTANCE				m_hInstance;		/**< �E�B���h�E�����̃p�����[�^	*/
		static HINSTANCE				m_hPrevInstance;	/**< �E�B���h�E�����̃p�����[�^	*/
		static LPSTR					m_lpCmdLine;		/**< �E�B���h�E�����̃p�����[�^	*/
		static KsInt32					m_nCmdShow;			/**< �E�B���h�E�����̃p�����[�^	*/

		/**
		 * �p�����[�^���Z�b�g����
		 */
		static void						setup( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, KsInt32 nCmdShow );

		/**
		 * �f�X�g���N�^
		 */
										~KsAppInstance(){}

	private:
		/**
		 * �R���X�g���N�^
		 */
										KsAppInstance(){}
};


#endif	/* __KSAPPINSTANCE_H__ */
