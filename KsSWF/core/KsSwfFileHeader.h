/************************************************************************************************/
/** 
 * @file		KsSwfFileHeader.h
 * @brief		SWF�t�@�C���w�b�_
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSWFFILEHEADER_H__
#define __KSSWFFILEHEADER_H__

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
 * @class		KsSwfhHeader
 * @brief		SWF FILE HEADER
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 * @note		�ŏ���3 �o�C�g�́fFWS�f�A4 �o�C�g�ڂ����@�[�W�����A5�`8 �o�C�g�ڂ��t�@�C���̒����ł���B
 *				���̌��ʂ̃T�C�Y�A�t���[���̍Đ����[�g�A�t���[���̐��������B
 */
/************************************************************************************************/
class ksSWF_API KsSwfFileHeader
{
		friend class KsSwfImporter;

	public:
		/**
		 * �R���X�g���N�^
		 */
								KsSwfFileHeader();

		/**
		 * �f�X�g���N�^
		 */
		virtual					~KsSwfFileHeader();

		/**
		 * �o�[�W�������擾����
		 * @return				SWF�o�[�W����
		 */
		KsUInt8					getVersion() const { return m_version; }

		/**
		 * �t�@�C���T�C�Y���擾����
		 * @return				�t�@�C���T�C�Y
		 */
		KsUInt32				getFileSize() const { return m_fileSize; }

		/**
		 * �t���[���T�C�Y���擾����
		 * @return				�t���[���T�C�Y
		 */
		KsSwfRect				getFrameSize() { return m_frameSize; }

		/**
		 * �t���[�����[�g���擾����
		 * @return				�t���[�����[�g
		 */
		KsSwfFixed16			getFrameRate() const { return m_frameRate; }

		/**
		 * �g�[�^���t���[�������擾����
		 * @return				�g�[�^���t���[����
		 */
		KsUInt16				getFrameCount() const { return m_frameCount; }

	private:
		KsUInt8					m_signature[ 3 ];	/**< SWF ���ʎq				*/
		KsUInt8					m_version;			/**< �o�[�W����				*/
		KsUInt32				m_fileSize;			/**< �t�@�C���T�C�Y			*/
		KsSwfRect				m_frameSize;		/**< �t���[���T�C�Y			*/
		KsSwfFixed16			m_frameRate;		/**< �t���[�����[�g			*/
		KsUInt16				m_frameCount;		/**< �g�[�^���t���[����		*/
};

#endif	/* __KSSWFFILEHEADER_H__ */

