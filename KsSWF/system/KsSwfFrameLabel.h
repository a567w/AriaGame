/************************************************************************************************/
/** 
 * @file		KsSwfFrameLabel.h
 * @brief		SWF�R�}���h
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSWFFRAMELABEL_H__
#define __KSSWFFRAMELABEL_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsSwfFrameLabel
 * @brief		SWF�R�}���h
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 * @note		�Ȃ�
 */
/************************************************************************************************/
class ksSWF_API KsSwfFrameLabel : public KsSwfCommand
{
	public:
		/**
		 * �R���X�g���N�^
		 */
								KsSwfFrameLabel( KsFileObject* pFile );

		/**
		 * �f�X�g���N�^
		 */
		virtual					~KsSwfFrameLabel();

		/**
		 * �R�}���h���s
		 */
		virtual void			execute();

	private:
		KsString				m_name;			/**< �t���[���̖��O	*/
};

#endif	/* __KSSWFFRAMELABEL_H__ */

