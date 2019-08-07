/************************************************************************************************/
/** 
 * @file		KsBitReader.h
 * @brief		KsBitReader
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSBITREADER_H__
#define __KSBITREADER_H__

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
 * @class		KsBitReader
 * @brief		Bit Reader
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
class ksENGINE_API KsBitReader
{
	public:
		/**
		 * �R���X�g���N�^
		 */
							KsBitReader();

		/**
		 * �R���X�g���N�^
		 */
							KsBitReader( const KsByte* pBuffer, KsInt32 size );

		/**
		 * �f�X�g���N�^
		 */
		virtual				~KsBitReader();

		/**
		 * �Z�b�g�A�b�v
		 */
		void				setup( const KsByte* pBuffer, KsInt32 size );

		/**
		 * �ǂݍ���
		 */
		KsUInt32			readUInt32( KsUInt8 uReadBit );

		/**
		 * �ǂݍ���
		 */
		KsInt32				readInt32( KsUInt8 uReadBit );

		/**
		 * �ǂݍ���
		 */
		KsLong				getNBitInt( KsInt32 n, KsBool is_signed );

		/**
		 * �ǂݍ���
		 */
		KsUInt8				getByte();

		KsInt32				getTotalReadBit() const { return m_sTotalReadBit; }

		/** 
		 * �o�C�g�A���C�������Ƃ���
		 */
		void				byteAlign();

	protected:
		const KsByte*		m_pBuffer;
		KsInt32				m_sBufferSizeBit;
		KsInt32				m_sTotalReadBit;
		KsInt32				m_size;
		KsInt32				m_pos;
		KsUInt8				m_buf;
		KsUInt8				m_bits;
};

/************************************************************************************************/
/**
 * @class		KsFileBitReader
 * @brief		SWF FILE HEADER
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
class ksENGINE_API KsFileBitReader
{
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsFileBitReader();

		/**
		 * �R���X�g���N�^
		 */
									KsFileBitReader( const KsChar* pFileName );

		/**
		 * �R���X�g���N�^
		 */
									KsFileBitReader( const KsByte* pBuffer, KsInt32 size );

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsFileBitReader();

		/**
		 * �t�@�C�����畂�������_�̒l��ǂݍ���
		 * @return					���������_�̒l
		 */
		virtual KsReal				readReal();

		/**
		 * �t�@�C������32bit�����l��ǂݍ���
		 * @return					32bit�����l
		 */
		virtual KsInt32				readInt32();

		/**
		 * �t�@�C�����畄���Ȃ�32bit�����l��ǂݍ���
		 * @return					�����Ȃ�32bit�����l
		 */
		virtual KsUInt32			readUInt32();

		/**
		 * �t�@�C������16bit�����l��ǂݍ���
		 * @return					16bit�����l
		 */
		virtual KsInt16				readInt16();

		/**
		 * �t�@�C�����畄���Ȃ�16bit�����l��ǂݍ���
		 * @return					�����Ȃ�16bit�����l
		 */
		virtual KsUInt16			readUInt16();

		/**
		 * �t�@�C������8bit�����l��ǂݍ���
		 * @return					8bit�����l
		 */
		virtual KsInt8				readInt8();

		/**
		 * �t�@�C�����畄���Ȃ�8bit�����l��ǂݍ���
		 * @return					�����Ȃ�8bit�����l
		 */
		virtual KsUInt8				readUInt8();

		/**
		 * �o�b�t�@�Ɏw��o�C�g�����ǂݍ���
		 * @param	pBuffer			(OUT)�ǂݍ��ނ��߂̃o�b�t�@
		 * @param	count			�ǂݍ��ރo�C�g��
		 * @return					�ǂݍ��񂾃o�C�g��
		 */
		virtual KsSize				read( void *pBuffer, KsInt32 count );

		/**
		 * �r�b�g�����ǂݍ���
		 * @param	n				�ǂݍ��ރr�b�g��
		 * @param	bIsSigned		�������肩�ǂ����̃t���O
		 * @return					�w��r�b�g�����̐����l
		 */
		virtual KsInt32				readBit( KsInt32 n, KsBool bIsSigned );

		/** 
		 * �o�C�g�A���C�������Ƃ���
		 */
		virtual void				byteAlign();

		KsUInt8						getByte();

	protected:
		KsFileObject*				m_pFile;
		const KsByte*				m_pBuffer;
		KsInt32						m_sBufferSizeBit;
		KsInt32						m_sTotalReadBit;
		KsInt32						m_size;
		KsInt32						m_pos;
		KsUInt8						m_data;
		KsUInt8						m_bits;
};


#endif	/* __KSBITREADER_H__ */

