/************************************************************************************************/
/**
 * @file		KsBitIO.h
 * @brief		�r�b�g����
 * @author		Tsukasa Kato
 * @date		2004/03/30
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSBITIO_H__
#define __KSBITIO_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsBitIO
 * @brief		�r�b�g����
 * @author		Tsukasa Kato
 * @date		2004/03/30
 * @version		1.0.0
 */
/************************************************************************************************/
class ksENGINE_API KsBitIO
{
	public:
		/**
		 * �R���X�g���N�^
		 */
										KsBitIO();

		/**
		 * �R���X�g���N�^
		 * @param		pFile			�t�@�C���|�C���^
		 */
										KsBitIO( FILE* pFile );

		/**
		 * �R���X�g���N�^
		 * @param		pBuffer			�o�b�t�@
		 */
										KsBitIO( KsByte* pBuffer );

		/**
		 * �f�X�g���N�^
		 */
										~KsBitIO(){}

		/**
		 * ����
		 * @param		pFile			�t�@�C���|�C���^
		 */
		void							create( FILE* pFile );

		/**
		 * ����
		 * @param		pBuffer			�o�b�t�@
		 */
		void							create( KsByte* pBuffer );

		/**
		 * �N���A
		 */
		void							clear();

		/**
		 * �t���O���Z�b�g
		 * @param		flag			�t���O
		 */
		void							pushFlag( KsByte flag );

		/**
		 * �f�[�^���Z�b�g
		 * @param		data			�f�[�^
		 */
		void							pushData( KsByte data );

		/**
		 * �����o��
		 */
		void							output();

		/**
		 * ���ׂď����o��
		 */
		void							outputAll();

		/**
		 * ���k�T�C�Y���擾����
		 * @param						���k�T�C�Y
		 */
		KsUInt32						getSize() const { return m_size; }

	private:
		KsBool							m_useFile;			/**< �t�@�C�����g���Ă��邩�H	*/
		KsByte*							m_pBuffer;			/**< �o�b�t�@					*/
		FILE*							m_pFile;			/**< �t�@�C���|�C���^			*/
		KsUInt32						m_count;			/**< �f�[�^�J�E���g				*/
		KsUInt32						m_size;				/**< ���k�T�C�Y					*/
		KsUInt32						m_index;			/**< �C���f�b�N�X				*/
		KsByte							m_mask;				/**< �}�X�N						*/
		KsByte							m_flags;			/**< �t���O						*/
		KsByte							m_data[ 16 ];		/**< �f�[�^�ۑ��p�o�b�t�@		*/
};


#endif		/* __KSBITIO_H__ */