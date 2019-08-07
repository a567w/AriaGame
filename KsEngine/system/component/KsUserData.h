/************************************************************************************************/
/** 
 * @file		KsUserData.h
 * @brief		���[�U�[�f�[�Ǘ�
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSUSERDATA_H__
#define __KSUSERDATA_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

enum ksCHUNK_TYPE
{
	ksCHUNK_NONE,
	ksCHUNK_TOP,
	ksCHUNK_KMD,
	ksCHUNK_FORCE32 = 0x7fffffff,
};

class KsChunk
{
	public:
		KsChunk();


		~KsChunk();

	public:
		ksCHUNK_TYPE	m_chunkType;
		KsInt32			m_dataSize;
		KsInt32			m_nextChunk;
};

KsChunk::KsChunk()
	: m_chunkType( ksCHUNK_NONE )
	, m_dataSize( 0 )
	, m_nextChunk( 0 )
{
}

/************************************************************************************************/
/**
 * @class		KsUserData
 * @brief		���[�U�[�f�[�^�N���X
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsUserData
{
		enum ksUSERDATA_ALLOC_TYPE
		{
			ksUSERDATA_ALLOC,
			ksUSERDATA_FREE,
		};

	public:
		/**
		 * �R���X�g���N�^
		 */
								KsUserData();

		/**
		 * @param	size		�m�ۂ���o�b�t�@�̃T�C�Y
		 */
								KsUserData( KsInt32 size );

		/*
		 * @param	pData		�f�[�^
		 * @param	size		�T�C�Y
		 * @param	allocType	�f�[�^�̊m�ۂ̃^�C�v
		 */
								KsUserData( KsByte* pData, KsInt32 size, KsBool allocType );

		/**
		 * �f�X�g���N�^
		 */
		virtual					~KsUserData();

		/*
		 * @param	size		�m�ۂ���o�b�t�@�̃T�C�Y
		 */
		KsBool					create( KsInt32 size );

		/**
		 * @param	pData		�f�[�^
		 * @param	size		�T�C�Y
		 * @param	allocType	�f�[�^�̊m�ۂ̃^�C�v
		 */
		KsBool					create( KsByte* pData, KsInt32 size, KsBool allocType );

		/**
		 * �j������
		 */
		void					destroy();

		/**
		 * �w��`�����N�ֈړ�����
		 * @param	chunk		�`�����N�^�C�v
		 * @param	index		�����C���f�b�N�X
		 * @return				�`�����N�f�[�^�̃T�C�Y
		 * @return				�f�[�^�̈ʒu
		 */
		KsInt32					findChunkSize( ksCHUNK_TYPE chunk, KsInt32 index=0 );

		/**
		 * �w��`�����N�ֈړ�����
		 * @param	chunk		�`�����N�^�C�v
		 * @param	index		�����C���f�b�N�X
		 * @return				�`�����N�f�[�^�̃T�C�Y
		 * @return				�f�[�^�̈ʒu
		 */
		KsByte*					findChunk( ksCHUNK_TYPE chunk, KsInt32 index=0 );

		/**
		 * �w��`�����N����f�[�^��ǂݍ���
		 * @param	pBuffer		�ǂݍ��݂悤�o�b�t�@
		 * @param	size		�ǂݍ��݂悤�o�b�t�@�̃T�C�Y
		 * @param	chunk		�`�����N�^�C�v
		 * @param	index		�����C���f�b�N�X
		 * @return				�`�����N�f�[�^�̃T�C�Y
		 */
		KsInt32					read( KsByte* pBuffer, KsInt32 size, ksCHUNK_TYPE chunk, KsInt32 index=0 );

		/**
		 * ���݈ʒu����w��T�C�Y�ǂݍ���
		 * @param	pBuffer		�ǂݍ��݂悤�o�b�t�@
		 * @param	size		�ǂݍ��݂悤�o�b�t�@�̃T�C�Y
		 * @return				�ǂݍ��񂾃T�C�Y
		 */
		KsInt32					read( KsByte* pBuffer, KsInt32 size );

		/**
		 * �w��`�����N����w��T�C�Y��������
		 * @param	pBuffer		�������ރf�[�^
		 * @param	size		�������ރf�[�^�T�C�Y
		 * @param	chunk		�`�����N�^�C�v
		 * @param	index		�����C���f�b�N�X
		 * @return				�������񂾃T�C�Y
		 */
		KsInt32					write( KsByte* pBuffer, KsInt32 size, ksCHUNK_TYPE chunk, KsInt32 index=0 );

		/**
		 * ���݈ʒu����w��T�C�Y��������
		 * @param	pBuffer		�������ރf�[�^
		 * @param	size		�������ރf�[�^�T�C�Y
		 * @return				�������񂾃T�C�Y
		 */
		KsInt32					write( KsByte* pBuffer, KsInt32 size );

		/** 
		 * �f�[�^�̃|�C���^�擾
		 * @param	pos			�ʒu���W
		 * @return				�f�[�^�̃|�C���^
		 */
		KsByte*					getData( KsInt32 pos=0 ) { return &m_pData[ 0 ]; }

		/**
		 * �T�C�Y���擾����
		 * @return				���[�U�[�f�[�^�̃T�C�Y
		 */
		KsInt32					getSize() const { return m_size; }

	protected:
		KsInt32					m_pos;			/**< �ʒu���W					*/
		KsByte*					m_pData;		/**< �f�[�^						*/
		KsInt32					m_size;			/**< �o�b�t�@�̃T�C�Y				*/
		ksUSERDATA_ALLOC_TYPE	m_allocType;	/**< �����Ŋm�ۂ����f�[�^���ǂ���	*/
};

#endif		/* __KSUSERDATA_H__ */



