/************************************************************************************************/
/** 
 * @file		KsFlashBase.h
 * @brief		�Q�[���}�l�[�W��
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSFLASHBASE_H__
#define __KSFLASHBASE_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsFlashRect
 * @brief		Flash(SWF)Header
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		�ŏ���3 �o�C�g�́fFWS�f�A4 �o�C�g�ڂ����@�[�W�����A5�`8 �o�C�g�ڂ��t�@�C���̒����ł���B
 *				���̌��ʂ̃T�C�Y�A�t���[���̍Đ����[�g�A�t���[���̐��������B
 */
/************************************************************************************************/
class KsFlashHeader
{
	public:

		/**
		 * �f�X�g���N�^
		 */
								KsFlashHeader( KsUInt8 version, KsUInt32 fileSize, KsInt32 width, KsInt32 height, KsUInt16 frameRate, KsUInt16 frameCount );
		
		/**
		 * �f�X�g���N�^
		 */
		virtual					KsFlashHeader( KsUInt8 version, KsUInt32 fileSize, KsInt32 width, KsInt32 height, KsReal64 frameRate, KsUInt16 frameCount );

		/**
		 * �f�X�g���N�^
		 */
								~KsFlashHeader() {}

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
		KsFlashRect				getFrameSize() { return m_rect; }

		/**
		 * �t���[�����[�g���擾����
		 * @return				�t���[�����[�g
		 */
		KsFlashFixed16			getFrameRate() const { return m_frameRate; }

		/**
		 * �g�[�^���t���[�������擾����
		 * @return				�g�[�^���t���[����
		 */
		KsUInt16				getFrameCount() const { return frameCount; }

	private:
		KsUInt8					m_signature[ 3 ];	/**< SWF ���ʎq				*/
		KsUInt8					m_version;			/**< �o�[�W����				*/
		KsUInt32				m_fileSize;			/**< �t�@�C���T�C�Y			*/
		KsFlashRect				m_frameSize;		/**< �t���[���T�C�Y			*/
		KsFlashFixed16			m_frameRate;		/**< �t���[�����[�g			*/
		KsUInt16				m_frameCount;		/**< �g�[�^���t���[����		*/

	protected:
								KsFlashHeader() {}
		friend class KsFlashImporter;
};




62 byte


/************************************************************************************************/
/**
 * @class		KsFlashTag
 * @brief		Flash(SWF)Header
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		TagHeader 16bit
 *				| ID( 10 bit ) | length( 6 bit ) |
 *  tagID  = Code >> 6; 
 *  length = Code & 0x3f;
 *	length �� 0x3f �̂Ƃ���32bit length
 */
/************************************************************************************************/
class KsFlashTag
{
	    friend class KsFlashImporter;
	
	public:
		/**
		 * �R���X�g���N�^
		 * @param	tagID		�^�OID
		 * @param	length		�^�O�̒���
		 */
	    						KsFlashTag( KsUInt16 tagID, KsUInt32 length ) : m_tagID( tagID ), m_length( length ) {}

		/**
		 * �f�X�g���N�^
		 */
	    virtual					~KsFlashTag() {}

		/**
		 * �^�OID���擾����
		 * @return				�^�OID
		 */
	    KsUInt16				getTagID() const { return m_tagID; }
	
		/**
		 * �^�O�̒������擾����
		 * @return				�^�O�̒���
		 */
	    KsUInt32				getTagLength() const { return m_length; }

	private:
	    KsUInt16				m_tagID;		/**< �^�OID			*/
	    KsUInt32				m_length;		/**< �^�O�̃T�C�Y	*/

	protected:
		/**
		 * �R���X�g���N�^
		 */
	    						KsFlashTag() {}
};



class KsFlashTag
{
	public:
	    KsFlashTag() {}
	    ~FlashTag() {}

	    void 			setImportSize( KsUInt32 size ) { m_importSize = size; }	
	protected:
	    KsUInt32		m_importSize;
};





class KsFlashDisplayListTag : public KsFlashTag
{
	public:
		KsFlashDisplayListTag() {}
		virtual		~KsFlashDisplayListTag() {}
		virtual KsBool			isFrame() { return ksFALSE; }

};


class KsFlashIDEnabled
{
	public:
		KsFlashIDEnabled( KsBool count=ksTrue ) { if( count ){ m_charID = m_idFactory.getCharacterID(); } }

		void				getID( KsUInt16 id ) { m_charID=id; }
		KsUInt16			getID() const { return m_charID; }
	private:
		KsFlashIDFactory	m_idFactory;
		KsUInt16			m_charID;
};




#endif /* __KSFLASHBASE_H__ */

