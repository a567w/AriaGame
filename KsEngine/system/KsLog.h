/*************************************************************************************************/
/** 
 * @file		KsLog.h
 * @brief		���O�}�l�[�W��
 * @author		Tsukasa Kato
 * @date		2005/06/27
 * @since		2005/06/27
 * @version		1.0.0
 */
/*************************************************************************************************/
#ifndef __KSLOG_H__
#define __KSLOG_H__

/*===============================================================================================*/
/*								<< �C���N���[�h�t�@�C�� >>										 */
/*===============================================================================================*/
#include "KsType.h"

/*===============================================================================================*/
/*										<< ��` >>												 */
/*===============================================================================================*/
#define ksLOG_FILE_NAME	_T("log.txt")		/**< ���O�̃t�@�C����	*/

/*************************************************************************************************/
/**
 * ���O�̏o�͐�
 */
/*************************************************************************************************/
enum ksLOG_OUT
{
	ksLOG_OUT_NONE			= 0x0000,		/**< ��					*/
	ksLOG_OUT_CONSOLE		= 0x0001,		/**< �R���\�[��			*/
	ksLOG_OUT_CONSOLE_WIN	= 0x0002,		/**< �R���\�[��Window	*/
	ksLOG_OUT_FILE			= 0x0004,		/**< �t�@�C��			*/
};

#define ksLOG_OUT_MASK_DEFAULT		( ksLOG_OUT_FILE )
#define ksLOG_OUT_MASK_ALL			( ksLOG_OUT_CONSOLE | ksLOG_OUT_CONSOLE_WIN | ksLOG_OUT_FILE )

/*************************************************************************************************/
/**
 * ���O���x��
 */
/*************************************************************************************************/
enum ksLOG_LEVEL
{
	ksLOG_LEVEL_NONE		= 0x0000,		/**< ��					*/
	ksLOG_LEVEL_MESSAGE		= 0x0001,		/**< ���b�Z�[�W			*/
	ksLOG_LEVEL_WARRNING	= 0x0002,		/**< ����				*/
	ksLOG_LEVEL_ASSERT		= 0x0004,		/**< �x��				*/
	ksLOG_LEVEL_ERROR		= 0x0008,		/**< �G���[				*/
};

#define ksLOG_LEVEL_MASK_DEFAULT	( ksLOG_LEVEL_MESSAGE | ksLOG_LEVEL_WARRNING | ksLOG_LEVEL_ASSERT | ksLOG_LEVEL_ERROR )
#define ksLOG_LEVEL_MASK_ALL		( ksLOG_LEVEL_MESSAGE | ksLOG_LEVEL_WARRNING | ksLOG_LEVEL_ASSERT | ksLOG_LEVEL_ERROR )

/*************************************************************************************************/
/**
 * ���O���c���Ă������߂̃N���X
 * @author	Tsukasa Kato
 * @since   2004/--/--
 * @version 2004/--/--
 * @note	
 */
/*************************************************************************************************/
class ksENGINE_API KsLogManager
{
	private:
		static FILE*					m_pFile;			/**< �t�@�C���N���X�̃|�C���^		*/
		static KsUInt16					m_logLevelMask;		/**< ���O�̃��x���}�X�N			*/
		static KsUInt16					m_logOutputMask;	/**< ���O�̏o�̓t���O				*/
		static KsBool					m_isFileOpen;		/**< �t�@�C���I�[�v���t���O		*/

    public:
    	/**
    	 * �f�X�g���N�^
    	 */
										~KsLogManager();
		 
    	/**
		 * ���b�Z�[�W���Z�b�g����
		 * @param		message			���b�Z�[�W
		 * @param		logLevel		���O���x��
		 */
		static void						message( const KsChar* message, ksLOG_LEVEL logLevel = ksLOG_LEVEL_MESSAGE );
		
		/**
		 * �t�H�[�}�b�g�t���Ń��b�Z�[�W���Z�b�g����
		 * @param		logLevel		���O���x��
		 * @param		message			���b�Z�[�W
		 * @param		...				�ψ���
		 */
		static void						message( ksLOG_LEVEL logLevel, const KsChar* format, ... );
		
		/**
		 * ���O���x���}�X�N�Z�b�g
		 * @param		logLevelMask	���O���x���}�X�N
		 */
		static void						setLogLevelMask( KsUInt16 logLevelMask );

		/**
		 * ���O�o�̓}�X�N�Z�b�g
		 * @param		logOutputMask	���O�o�̓}�X�N
		 */
		static void						setLogOutputMask( KsUInt16 logOutputMask );
		
		/**
		 * ���O���x���}�X�N�擾
		 * @return						���O���x���}�X�N
		 */
		static KsUInt16					getLogLevelMask();

		/**
		 * ���O�o�̓}�X�N�擾
		 * @return						���O�o�̓}�X�N
		 */
		static KsUInt16					getLogOutputMask();
};


#endif	/* __KSLOG_H__ */

