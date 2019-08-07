/************************************************************************************************/
/**
 * @file		KsReadRequest.h
 * @brief		�t�@�C���V�X�e��
 * @author		Tsukasa Kato
 * @date		2004/03/30
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSREADREQUEST_H__
#define __KSREADREQUEST_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsFileAsyncReader;

/************************************************************************************************/
/**
 * �ǂݍ��݃X�e�[�g
 */
/************************************************************************************************/
enum ksREADING_STATE
{
	ksREADING_START      = 0,				/**< �ǂݍ��݊J�n�҂�			*/
	ksREADING_READ       = 1,				/**< �ǂݍ��ݒ�				*/
	ksREADING_END        = 2,				/**< �ǂݍ��ݏI��			*/
	ksREADING_OPEN_IDLE  = 3,				/**< �I�[�v���A�C�h�����O		*/
	ksREADING_READ_IDLE  = 4,				/**< �ǂݍ��݃A�C�h�����O		*/
	ksREADING_CLOSE_IDLE = 5,				/**< �N���[�Y�A�C�h�����O		*/
	ksREADING_ERROR      = 0x80000000,		/**< �G���[					*/
	ksREADING_FORCE32    = 0x7fffffff,		/**< ����32�r�b�g			*/
};


/************************************************************************************************/
/**
 * �t�@�C���ǂݍ��ݏI�����R�[���o�b�N
 */
/************************************************************************************************/
typedef void (*KsFileReadEndCB)( void* pData, KsInt32 size, void* pUserData );

/************************************************************************************************/
/**
 * @class		KsReadRequest
 * @brief		�ǂݍ��݃��N�G�X�g�N���X(�񓯊��ǂݍ��ݎ��Ɏg�p����)
 * @author		Tsukasa Kato
 * @date		2004/03/30
 * @version		1.0.0
 */
/************************************************************************************************/
class ksENGINE_API KsReadRequest
{
		friend class KsFileSystem;
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsReadRequest();

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsReadRequest();

		/**
		 * ���݂̃X�e�[�^�X���擾����
		 * @return					���݂̃X�e�[�^�X
		 */
		virtual ksREADING_STATE		getStatus() const { return m_status; }

		/**
		 * �ǂݍ��񂾃f�[�^�̃T�C�Y���擾����
		 * @return					�ǂݍ��񂾃f�[�^�̃T�C�Y
		 */
		virtual KsUInt32			getReadSize() const { return m_readSize; }

		/**
		 * �f�[�^�̃T�C�Y���擾����
		 * @return					�f�[�^�̃T�C�Y
		 */
		virtual KsUInt32			getDataSize() const { return m_dataSize; }

		/**
		 * �ǂݍ��݂悤�o�b�t�@���Z�b�g����(�w��o�b�t�@���g�p�������Ƃ�)
		 */
		virtual void				setBuffer( KsUInt8* pBuffer, KsUInt32 bufferSize );

		/**
		 * �o�b�t�@�̃|�C���^���擾����
		 * @return					�o�b�t�@�̃|�C���^
		 */
		virtual KsUInt8*			getBuffer() { return m_pBuffer; }

		/**
		 * �o�b�t�@�̃T�C�Y���擾����
		 * @return					�o�b�t�@�̃T�C�Y
		 */
		virtual KsUInt32			getBufferSize() { return m_bufferSize; }

		/**
		 * �R�[���o�b�N�i���C���p�j
		 */
		virtual void				callback();

		/**
		 * �R�[���o�b�N�i�X���b�h�p�j
		 */
		virtual void				callbackThread();

	protected:
		ksREADING_STATE				m_status;			/**< �X�e�[�^�X								*/
		KsBool						m_bufferFlag;		/**< �����ƊO���̂ǂ���Ŋm�ۂ������̃t���O	*/
		KsULong						m_bufferSize;		/**< �o�b�t�@�̃T�C�Y							*/
		KsUInt8*					m_pBuffer;			/**< �f�[�^�ǂݎ��p�o�b�t�@					*/
		KsULong						m_dataSize;			/**< �f�[�^�̃T�C�Y							*/
		KsULong						m_readSize;			/**< �ǂݍ��񂾃f�[�^�̃T�C�Y					*/
		KsString					m_fileName;			/**< �t�@�C����								*/
		KsHandle					m_fileHandle;		/**< �t�@�C���n���h��							*/
		KsHandle					m_threadHandle;		/**< �X���b�h�n���h��							*/
		KsUInt32					m_threadID;			/**< �X���b�hID								*/
		KsFileReadEndCB				m_callback;			/**< �R�[���o�b�N							*/
		void*						m_pUserData;		/**< ���[�U�[�f�[�^							*/
		KsFileReadEndCB				m_callbackThread;	/**< �R�[���o�b�N							*/
		void*						m_pUserDataThread;	/**< �X���b�h�p���[�U�[�f�[�^					*/
		OVERLAPPED					m_overlapped;		/**< �I�[�o�[���b�v							*/
		KsBool						m_bAutoDelete;		/**< �����폜�t���O							*/
};

#endif /* __KSREADREQUEST_H__ */

