/************************************************************************************************/
/**
 * @file		KsFileSystem.h
 * @brief		�t�@�C���V�X�e��
 * @author		Tsukasa Kato
 * @date		2004/03/30
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSFILESYSTEM_H__
#define __KSFILESYSTEM_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/
#define ksFILE_QUEUE_MAX		( 256 )		/**< �t�@�C���L���[�̍ő�T�C�Y		*/
#define ksPACK_LIST_MAX			( 8 )		/**< �p�b�N�t�@�C�����X�g�̍ő吔	*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsReadRequest;
class KsFileAsyncReader;
class KsFileThread;

/************************************************************************************************/
/**
 * @class		KsFileSystem
 * @brief		�t�@�C��s�V�X�e���I�u�W�F�N�g
 * @author		Tsukasa Kato
 * @date		2004/03/30
 * @version		1.0.0
 */
/************************************************************************************************/
class ksENGINE_API KsFileSystem : public KsSingleton< KsFileSystem >
{
	public:
		typedef KsQueue< KsReadRequest*, ksFILE_QUEUE_MAX >	KsFileQueue;
		//typedef KsArray<KsPack*>							KsPackArray;

	public:
		/**
		 * �V���O���g���̎Q�Ƃ��擾
		 * @return						�V���O���g���̎Q��
		 */
		static KsFileSystem&			getInstance();
		
		/**
		 * �V���O���g���̃|�C���^���擾
		 * @return						�V���O���g���̃|�C���^
		 */
		static KsFileSystem*			getInstancePtr();

	public:
		/**
		 * �R���X�g���N�^
		 */
										KsFileSystem( ksTHREAD_PRIORITY_TYPE priority=ksTHREAD_PRIORITY_NORMAL, KsUInt32 prosessor=0 );
		
		/**
		 * �f�X�g���N�^
		 */
		virtual							~KsFileSystem();

		/**
		 * ���b�N����
		 */
		void							lock() { m_mutex.lock(); }

		/**
		 * �A�����b�N����
		 */
		void							unlock() { m_mutex.unlock(); }

		/**
		 * �񓯊��ǂݍ���(�ǂݍ��݃��N�G�X�g���X�^�b�N�ɂ��߂Ă���)
		 * �ǂݍ��ݗp���N�G�X�g��ǉ�����
		 * @param		pRequest		���N�G�X�g
		 */
		virtual KsBool					pushRequest( KsReadRequest* pRequest );

		/**
		 * �񓯊��t�@�C���I�[�v��
		 * @param		pRequest		���N�G�X�g
		 * @return						�t�@�C���n���h��
		 */
		virtual KsHandle				openAsync( KsReadRequest* pRequest );

		/**
		 * �񓯊��t�@�C���I�[�v��
		 * @param		pRequest		���N�G�X�g
		 * @return						�t�@�C���n���h��
		 */
		virtual KsHandle				readAsync( KsReadRequest* pRequest );

		/**
		 * �ǂݎ�蒆����
		 * @param		pRequest		���N�G�X�g
		 * @retval		ksTRUE			����
		 * @retval		ksFALSE			���s
		 */
		virtual KsBool					reading( KsReadRequest* pRequest );

		/**
		 * �񓯊��t�@�C���N���[�Y
		 * @param		pRequest		���N�G�X�g
		 * @retval		ksTRUE			����
		 * @retval		ksFALSE			���s
		 */
		virtual KsBool					closeAsync( KsReadRequest* pRequest );

		/**
		 * ���C������ĂԃR�[���o�b�N����
		 */
		virtual void					callback();

		/**
		 * �񓯊��t�@�C���I�[�v��
		 * @param		fileName		�t�@�C����
		 * @param		callback		���C�����̓ǂݍ��ݏI���R�[���o�b�N
		 * @param		pUserData		���[�U�[�f�[�^
		 * @param		callbackTH		�X���b�h���̓ǂݍ��ݏI�����ɌĂ΂��
		 * @param		pUserDataTH		�X���b�h���̃��[�U�[�f�[�^
		 * @return						�t�@�C���n���h��
		 */
		virtual KsHandle				openAsync( const KsString& fileName, KsFileReadEndCB callback=0, void* pUserData=0, KsFileReadEndCB callbackTH=0, void* pUserDataTH=0 );

		/**
		 * �񓯊��t�@�C���I�[�v��
		 * @param		fileName		�t�@�C����
		 * @param		pBuffer			�o�b�t�@
		 * @param		size			�o�b�t�@�T�C�Y
		 * @param		callback		���C�����̓ǂݍ��ݏI���R�[���o�b�N
		 * @param		pUserData		���[�U�[�f�[�^
		 * @param		callbackTH		�X���b�h���̓ǂݍ��ݏI�����ɌĂ΂��
		 * @param		pUserDataTH		�X���b�h���̃��[�U�[�f�[�^
		 * @return						�t�@�C���n���h��
		 */
		virtual KsHandle				openAsync( const KsString& fileName, KsByte* pBuffer, KsInt32 size, KsFileReadEndCB callback=0, void* pUserData=0, KsFileReadEndCB callbackTH=0, void* pUserDataTH=0 );

		/**
		 * �񓯊��ǂݍ��ݏ���(�L���[�ɂ��܂��Ă��郊�N�G�X�g�����Ԃɏ������Ă���)
		 * @return						�ǂݍ��ݏ�
		 */
		virtual KsInt32					polling();

		/**
		 * �񓯊��t�@�C���N���[�Y
		 * @param		handle			�n���h��
		 * @retval		ksTRUE			����
		 * @retval		ksFALSE			���s
		 */
		virtual KsBool					closeAsync( KsHandle handle );

		/**
		 * �ǂݍ��݃��N�G�X�g���Z�b�g����
		 * @param		pRequest		���N�G�X�g�f�[�^
		 * @retval		ksTRUE			����
		 * @retval		ksFALSE			���s
		 */
		virtual KsBool					setRequest( KsReadRequest* pRequest );

		/**
		 * �񓯊��ǂݍ���(�ǂݍ��݃��N�G�X�g���L���[�ɂ��߂Ă���)
		 * @param		�ǂݍ��݂悤�L���[�ɂ��܂��Ă��郊�N�G�X�g���N���A�[����
		 */
		virtual void					cancelRequest(){ m_bCancel = ksTRUE; }

#if 0

		/**
		 * �����ǂݍ���(�ǂݍ��݂��I������܂ő҂�)
		 * @param		pFileName		�t�@�C����
		 * @param		ppBuffer		�f�[�^�󂯎��p�o�b�t�@�̃|�C���^
		 * @param		pSize			�o�b�t�@�̃T�C�Y���󂯎��悤�|�C���^
		 * @return						�ǂݍ��񂾃T�C�Y
		 */
		virtual KsUInt32				createRead( const KsChar* pFileName, KsUInt8** ppBuffer, KsUInt32* pSize );

		/**
		 * �����ǂݍ���(�ǂݍ��݂��I������܂ő҂�)
		 * @param		pFileName		�t�@�C����
		 * @param		pBuffer			�ǂݎ��p�o�b�t�@
		 * @param		size			�o�b�t�@�̃T�C�Y(�o�C�g)
		 * @return						�ǂݍ��񂾃T�C�Y
		 * @note		�ǂݎ��p�o�b�t�@�̃T�C�Y���U�S�̔{������Ȃ��ƃ_��
		 */
		virtual KsUInt32				read( const KsChar* pFileName, KsUInt8* pBuffer, KsUInt32 size );
		
		/**
		 * �񓯊��ǂݍ���(�ǂݍ��݃��N�G�X�g���L���[�ɂ��߂Ă���)
		 * @param		�ǂݍ��݂悤�L���[�ɂ��܂��Ă��郊�N�G�X�g���N���A�[����
		 */
		virtual void					clearRequest();
		
		/**
		 * �ǂݍ��݃��N�G�X�g�𐶐�����
		 * @param		pFileName		�ǂݍ��݂����t�@�C����
		 * @param		flags			�����t���O
		 * @return		�ǂݍ��݃��N�G�X�g�̃|�C���^
		 * @note		�Œ�o�b�t�@�����悤�������ꍇ�́Aflags = 0�ɂ��Đ������Ă���setBuffer()�ŃZ�b�g���Ă��������B
		 *				flags = 0��setBuffer()���Ȃ������Ƃ���pushRequest���ƂƂ��ɕK�v�ȃo�b�t�@�������m�ۂ���܂��B
		 *				pushRequest()�Ŋm�ۂ��ꂽ�o�b�t�@��destroyRequest()������ƊJ������܂��B
		 *				flags = 1�Ő��������Ƃ��́AcreateRequest()�̂Ƃ��ɕK�v�ȃo�b�t�@���m�ۂ���܂��B
		 *				����Ŋm�ۂ��ꂽ�o�b�t�@�́AdestroyRequest()�ł��J������Ȃ��̂Ŋe���J������K�v������܂��B
		 */
		virtual KsReadRequest*			createRequest( KsChar* pFileName, KsUInt32 flags=0 );

		/**
		 * �ǂݍ��݃��N�G�X�g��j������
		 * @param		pReq			�j���������ǂݍ��݃��N�G�X�g�̃|�C���^
		 */
		virtual void					destroyRequest( KsReadRequest* pRequest );
		
		/**
		 * �w��t�@�C���̓ǂݍ��ݏ󋵂��`�F�b�N����
		 * @retval						�ǂݍ��ݏ�
		 */
		virtual ksREADING_STATE		checkReadState( const KsChar* pFileName );
		
		/**
		 * �t�@�C���̑��݂��`�F�b�N��
		 * @param		pFileName		�t�@�C����
		 * @retval		ksTRUE			���݂��Ă���
		 * @retval		ksFALSE			���݂��Ă��Ȃ�
		 */
		virtual KsBool					isExist( KsChar* pFileNamee );

		//virtual void					packEntry( KsChar* pPackName );
#endif

		static KsUInt32 __stdcall	KsFileSystem::KsWorkerThreadFunc( PVOID pv );
	protected:
		KsReadRequest*					m_pCurrentRequest;		/**< ���݂̃��N�G�X�g					*/
		KsFileQueue						m_requestQueue;			/**< �ǂݍ��݃��N�G�X�g�̃L���[			*/
		//KsPack						m_packList[ ksPACK_LIST_MAX ];	/**< �p�b�N�t�@�C������ǂނƂ�			*/
		//KsArray<KsPack*>				m_vpPackes;
		KsUInt32						m_packIndex;			/**< �g�p�p�b�N�C���f�b�N�X				*/
		KsBool							m_bCancel;				/**< �L�����Z��					*/
		KsMutex							m_mutex;
		KsFileThread*					m_pFileThread;			/**< �t�@�C���X���b�h		*/
};


#endif /* __KSFILESYSTEM_H__ */

