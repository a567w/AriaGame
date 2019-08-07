/************************************************************************************************/
/** 
 * @file		KsGameSystem.h
 * @brief		�Q�[���V�X�e��
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSGAMESYSTEM_H__
#define __KSGAMESYSTEM_H__

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
 * @class		KsGameSystem
 * @brief		��{�^�X�N�}�l�[�W���N���X
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		�Ȃ�
 */
/************************************************************************************************/
class KsGameSystem : public KsSceneManager
{
	public:
		/**
		 * �C���X�^���X�擾
		 */
		static KsGameSystem*			getInstancePtr();

		/**
		 * �J��
		 */
		static void						destoryInstance();

		/**
		 * �Q�[���^�X�N��ǉ�����
		 */
		static KsBool					addGameTask( KsTask* pTask );

		/**
		 * �Q�[���^�X�N����菜��
		 */
		static KsBool					removeGameTask( KsTask* pTask );

	protected:
		/**
		 * �R���X�g���N�^(�V���O���g���̂��߂�protected)
		 */
										KsGameSystem();
	public:
		/**
		 * �f�X�g���N�^
		 */
		virtual							~KsGameSystem();

		/**
		 * �Q�[������
		 * @param	hInstance			�C���X�^���X
		 * @param	hPrevInstance		�C���X�^���X
		 * @param	lpCmdLine			�R�}���h���C��
		 * @param	nCmdShow			�R�}���h�\��
		 */
		KsBool							create( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, KsInt32 nCmdShow );
		
		/**
		 * ���C�����[�v
		 */
		void							loop();

		/**
		 * ����������
		 * @retval		ksTRUE			����
		 * @retval		ksFALSE			���s
		 */
		KsBool							initialize();

		/**
		 * �㏈��
		 * @retval		ksTRUE			����
		 * @retval		ksFALSE			���s
		 */
		KsBool							terminate();

		/**
		 * ���b�Z�[�W���[�v
		 */
		KsBool							messageLoop();

		/** 
		 * �`��V�X�e���擾
		 * @return						�`��V�X�e���̃|�C���^
		 */
		KsRenderSystem*					getRenderSystem() { return m_pRenderSystem; }

		/**
		 * �N���A�[�J���[
		 * @param		color			�N���A�[�J���[�l
		 */
		void							setClearColor( const KsColor& color ) { m_clearColor = color; }

		/**
		 * �A�N�e�B�u��Ԃ��̃t���O���Z�b�g����
		 */
		void							setActive( KsBool _bActive ) { m_bActive = _bActive; }

		/**
		 * �A�N�e�B�u��Ԃ�?
		 * @retval		ksTRUE			�A�N�e�B�u
		 * @retval		ksFALSE			��A�N�e�B�u
		 */
		KsBool							isActive() const { return m_bActive; }

		/**
		 * �`�悷�邩�̃t���O���Z�b�g����
		 */
		void							setRender( KsBool _bRender ) { m_bRender = _bRender; }

		/**
		 * �`�悷�邩?
		 * @retval		ksTRUE			�`��
		 * @retval		ksFALSE			��`��
		 */
		KsBool							isRender() const { return m_bRender; }

		/**
		 * �Q�[�����I��������
		 */
		void							gameExit();

		/**
		 * ���C�����[�v�����H
		 * @retval		ksTRUE			���C�����[�v��
		 * @retval		ksFALSE			���C�����[�v�I��
		 */
		KsBool							isMainLoop() const { return m_bMainLoop; }

		/**
		 * �Q�[�����[�v�����H
		 * @retval		ksTRUE			�Q�[�����[�v��
		 * @retval		ksFALSE			�Q�[�����[�v�I��
		 */
		KsBool							isGameLoop();
		
		/**
		 * �E�C���h�E�̕����擾����
		 * @return						�E�C���h�E�̕�
		 */
		KsInt32							getWindowWidth() const	{ return m_pMainWindow->getWidth();	 }

		/**
		 * �E�C���h�E�̍������擾����
		 * @return						�E�C���h�E�̍���
		 */
		KsInt32							getWindowHeight() const	{ return m_pMainWindow->getHeight(); }

		/**
		 * �E�C���h�E�̃A�X�y�N�g����擾����
		 * @return						�E�C���h�E�̃A�X�y�N�g��
		 */
		KsReal							getWindowAspectRatio() const { return ((KsReal)m_pMainWindow->getWidth())/((KsReal)m_pMainWindow->getHeight()); }

		/**
		 * �t���[�����[�g���擾����
		 */
		KsReal							getFrameRate() const { return 1.0f/60.0f; }

		/**
		 * ���f����ǉ�����
		 */
		void							addModel( KsModel* pModel );

		/**
		 * �A�N�^�[��ǉ�����
		 */
		void							addActor( KsActor* pActor );

	protected:
		/**
		 * ���s����
		 * @param		pParam			�p�����[�^
		 */
		virtual void					execute( void* pParam );

		/**
		 * �`�揈��
		 * @param		pParam			�p�����[�^
		 */
		virtual void					render( void* pParam );

		/**
		 * �X�V����
		 * @param		pParam			�p�����[�^
		 */
		virtual void					update( void* pParam );

		/**
		 * ���ׂĂ̏��������s
		 * @param		pParam			�����ł킽�����p�����[�^���^�X�N��execute��render�̈����ɓn��
		 *								�f�t�H���g�ł́ANULL���ݒ肳��Ă���B
		 */
		virtual void					run( void* pParam );

		/**
		 * �`��J�n
		 */
		virtual void					begineRender();

		/**
		 * �`��I��
		 */
		virtual void					endRender();

		/**
		 * VSync�҂��̏���(���z)
		 * @param	count				����܂��H
		 */
		void							vsync( KsInt32 count );

		/**
		 * �\�t�g�E�F�A�[���Z�b�g����
		 */
		void							softwareReset();

		/**
		 * �\�t�g���Z�b�g�v�������������ǂ����H
		 */
		KsBool							isSoftwareReset();
	
	protected:
		
		/**
		 * �|�[�����O����
		 */
		void							polling();

		/*
		 * �T�E���h�X�V����
		 */
		void							sound();

		/**
		 * �p�b�h����
		 */
		void							pad();

		/**
		 * VSync�҂��̏���(���z)
		 */
		void							vsync();

	public:
		KsWindowParam					m_mainWindowParam;		/**< �E�C���h�E�p�����[�^			*/
		KsWindow*						m_pMainWindow;			/**< �E�C���h�E�t���[��			*/
		KsRenderSystem*					m_pRenderSystem;		/**< �`��V�X�e��					*/
		KsPhysicsSystem*				m_pPhysicsSystem;		/**< �����G���W���V�X�e��			*/
		KsOVRSystem*					m_pOVRSystem;			/**< OVR�V�X�e��					*/
		KsVirtualMachine*				m_pVirtualMachine;		/**< �o�[�`�����}�V��				*/
		KsInputSystem*					m_pInputSystem;			/**< ���̓V�X�e��					*/
		KsGamePadManager*				m_pPadManager;			/**< �p�b�h�}�l�[�W��				*/
		KsGameResourceManager*			m_pGameResourceManager;	/**< �Q�[�����\�[�X�}�l�[�W��		*/
		KsGameShaderManager*			m_pGameShaderManager;	/**< �Q�[���V�F�[�_�[�}�l�[�W��		*/
		KsCameraManager*				m_pCameraManager;		/**< �J�����}�l�[�W��				*/
		KsFileSystem*					m_pFileSystem;			/**< �t�@�C���V�X�e��				*/
		//KsGameSoundManager*			m_pSoundManager;		/**< �Q�[���T�E���h�}�l�[�W��		*/
		KsColor							m_clearColor;			/**< �o�b�t�@�N���A�J���[			*/
		KsBool							m_bActive;				/**< �A�N�e�B�u���ǂ���?			*/
		KsBool							m_bRender;				/**< �`�悷�邩�ǂ���?				*/
		KsBool							m_bMainLoop;			/**< �Q�[�����[�v�t���O			*/
//		KsThreadGroup					m_threadGroup;			/**< �X���b�h�O���[�v				*/
		KsDeferredRender*				m_pDeferredRender;		/**< �f�B�t�@�[�h�����_�[			*/
		KsForwardPlusRender*			m_pForwardPlusRender;	/**< Forward+					*/
		KsPhysicsThread*				m_pPhysicsThread;		/**< �����V�~�����[�V����			*/
	public:
		/* �}�l�[�W���̃C���X�^���X */
		static KsGameSystem*			m_pInstance;			/**< �C���X�^���X					*/
};


/************************************************************************************************/
/**
 * �Q�[���V�X�e������
 * @param	hInstance			�C���X�^���X
 * @param	hPrevInstance		�C���X�^���X
 * @param	lpCmdLine			�R�}���h���C��
 * @param	nCmdShow			�R�}���h�\��
 * @note	���łɃE�C���h�E������ꍇ�́A��������Ƃ̃T�C�Y�ŕ���������
 */
/************************************************************************************************/
extern KsGameSystem* KsGameCreate( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, KsInt32 nCmdShow );

/************************************************************************************************/
/*
 * �Q�[�����[�v
 * @param	pGame	�Q�[���V�X�e���̃|�C���^
 */
/************************************************************************************************/
extern void KsGameLoop( KsGameSystem* pGame );

/************************************************************************************************/
/*
 * �Q�[���V�X�e���j��
 * @param	pGame	�Q�[���V�X�e���̃|�C���^
 */
/************************************************************************************************/
extern void KsGameDestroy( KsGameSystem* pGame );


#endif		/* __KSGAMESYSTEM_H__ */