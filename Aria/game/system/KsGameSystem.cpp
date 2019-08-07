/************************************************************************************************/
/** 
 * @file		KsGameSystem.cpp
 * @brief		�Q�[���V�X�e��
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                     �@      */
/*==============================================================================================*/
#include "Aria/KsGamePreCompile.h"
#include "Aria/game/system/KsGameSystem.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
KsGameSystem* KsGameSystem::m_pInstance = NULL;

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsGameSystem::KsGameSystem()
	: KsSceneManager()
	, m_bActive( ksFALSE )
	, m_pMainWindow( 0 )
	, m_pRenderSystem( 0 )
	, m_pPhysicsSystem( 0 )
	, m_pOVRSystem( 0 )
	, m_pVirtualMachine( 0 )
	, m_pInputSystem( 0 )
	, m_pPadManager( 0 )
	, m_pGameResourceManager( 0 )
	, m_pCameraManager( 0 )
	, m_pFileSystem( 0 )
	//, m_pSoundManager( 0 )
	, m_clearColor( 32, 64, 128, 0xff )
	, m_bRender( ksTRUE )
	, m_bMainLoop( ksTRUE )
	, m_pDeferredRender( 0 )
	, m_pPhysicsThread( 0 )
{
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsGameSystem::~KsGameSystem()
{
	/* �㏈�������� */
	terminate();
}

/************************************************************************************************/
/*
 * �Q�[������
 * @param	hInstance			�C���X�^���X
 * @param	hPrevInstance		�C���X�^���X
 * @param	lpCmdLine			�R�}���h���C��
 * @param	nCmdShow			�R�}���h�\��
 */
/************************************************************************************************/
KsBool KsGameSystem::create( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, KsInt32 nCmdShow )
{
	//---------------------------------------------------------------
	// �E�C���h�E�̐ݒ�t�@�C�����`�F�b�N����
	//---------------------------------------------------------------
	KsGameConfigManager::setup();

	//---------------------------------------------------------------
	// �E�C���h�E�̃p�����[�^�ۑ�
	//---------------------------------------------------------------
	KsAppInstance::setup( hInstance, hPrevInstance, lpCmdLine, nCmdShow );

	//---------------------------------------------------------------
	// �E�C���h�E�̃X�^�C���ݒ� 
	//---------------------------------------------------------------
	RECT	rect;

	KsWindowUtility::getDeskTopClientRect( &rect );

	m_mainWindowParam.m_caption   = ksGAME_TITLE;
	m_mainWindowParam.m_className = ksGAME_CLASS;
	m_mainWindowParam.m_style     = ksWINDOW_DEFAULT_STYLE;
	m_mainWindowParam.m_styleEx   = 0;
	m_mainWindowParam.m_posX      = ( rect.right  - rect.left )/2 - ksWINDOW_DEFAULT_SIZE_X/2;
	m_mainWindowParam.m_posY      = ( rect.bottom - rect.top  )/2 - ksWINDOW_DEFAULT_SIZE_Y/2;
	m_mainWindowParam.m_sizeX     = ksWINDOW_DEFAULT_SIZE_X;
	m_mainWindowParam.m_sizeY     = ksWINDOW_DEFAULT_SIZE_Y;

	try
	{
		/* �E�C���h�E���� */
		m_pMainWindow = ksNew KsWindow();

		if( !m_pMainWindow )
		{
			throw "�E�C���h�E�������m�ۃG���[!!";
		}

		if( !( m_pMainWindow->create( m_mainWindowParam, NULL, this ) ) )
		{
			throw "�E�C���h�E�����G���[!!";
		}

		/* �`��V�X�e������ */
		m_pRenderSystem = KsRenderSystemFactory( ksRENDERSYSTEM_DIRECTX11, m_pMainWindow );

		if( !m_pRenderSystem )
		{
			throw "�`��V�X�e�������G���[!!";
		}

		/* �����G���W���V�X�e������ */
		m_pPhysicsSystem = KsPhysicsSystemFactory( ksPHYSICSSYSTEM_BULLET, NULL );

		if( !m_pPhysicsSystem )
		{
			throw "�����G���W���V�X�e�������G���[!!";
		}
	}
	catch( const char *pszError )
	{
		/* �G���[ */
		KsError( pszError );

		ksDELETE( m_pMainWindow );

		return ksFALSE;
	}

	/* �������ƏI���̂Ƃ��E�G�C�g������K�v������ */

	return ksTRUE;
}

/************************************************************************************************/
/*
 * ����������
 * @retval		ksTRUE			����
 * @retval		ksFALSE			���s
 */
/************************************************************************************************/
KsBool KsGameSystem::initialize()
{
	/* COM������ */
	//#define _WIN32_DCOM
	//::CoInitializeEx( NULL, COINIT_APARTMENTTHREADED );
	::CoInitializeEx( NULL, COINIT_MULTITHREADED );

	/* �^�C�}�[������ */
	KsTimer::initialize();

	/* �t�@�C���V�X�e�������� */
	m_pFileSystem = ksNew KsFileSystem( ksTHREAD_PRIORITY_HIGHEST, 2 );

	/* ���̓}�l�[�W�������� */
	m_pInputSystem = ksNew KsInputSystem( KsGameCommon::ksGAME_PAD_MAX );

	/* �Q�[���p�b�h�}�l�[�W�������� */
	m_pPadManager = ksNew KsGamePadManager( m_pInputSystem );

	/* �Q�[�����\�[�X�}�l�[�W�������� */
	m_pGameResourceManager = ksNew KsGameResourceManager();

	/* �Q�[���p�V�F�_�[�}�l�[�W�������� */
	m_pGameShaderManager = ksNew KsGameShaderManager();

	/* �J�����}�l�[�W��������*/
	m_pCameraManager = ksNew KsCameraManager();
	
	/* �Q�[���T�E���h�}�l�[�W��������*/
	//m_pSoundManager = ksNew KsGameSoundManager();

	/* �o�[�`�����}�V�� */
	m_pVirtualMachine = ksNew KsVirtualMachine( ksVARIABLE_STACK_SIZE, ksHANDLE_LIST_BLOCK_SIZE, ksSTRUCT_MEMBER_BLOCK_SIZE );

	/* �f�B�t�@�[�h�����_�����O�V�X�e�������������� */
	m_pDeferredRender = ksNew KsDeferredRender( m_pRenderSystem, ksWINDOW_DEFAULT_SIZE_X, ksWINDOW_DEFAULT_SIZE_Y );

	/* Forward+�����_�����O�V�X�e�������������� */
	m_pForwardPlusRender = ksNew KsForwardPlusRender( m_pRenderSystem, ksWINDOW_DEFAULT_SIZE_X, ksWINDOW_DEFAULT_SIZE_Y );

	// OVR�V�X�e��
	m_pOVRSystem = ksNew KsOVRSystem();

	/* �����V�~�����[�V�����X���b�h�������� */
	//m_pPhysicsThread = ksNew KsPhysicsThread( ksTHREAD_PRIORITY_NORMAL, 3 );

	/* �V�[���Ǘ��V�X�e�������������� */
	KsSceneManager::initialize();

	/* �X�N���v�g�p���C�u���������[�h */
	KsScriptLoadSystemLib( m_pVirtualMachine );
	KsScriptLoadMathLib( m_pVirtualMachine );

	/* �f�o�b�N�V�X�e�������� */
	ksDEBUG_INIT( ".\\Font\\ascii.dds" );

	//KsLoadSwf("D:\\KGDC\\Aria\\Aria\\test.swf");

	return ksTRUE;
}

/************************************************************************************************/
/*
 * �㏈��
 * @retval		ksTRUE		����
 * @retval		ksFALSE		���s
 */
/************************************************************************************************/
KsBool KsGameSystem::terminate()
{
	//---------------------------------------------------------------
	// �f�o�b�N�t�H���g���
	//---------------------------------------------------------------
	ksDEBUG_TERM();

	/* �}�l�[�W�����Q�Ƃ��Ă���^�X�N������̂�,�܂��^�X�N�������Ȃ��Ƃ܂��� */
	KsSceneManager::terminate();

	/* �X�N���v�g�p���C�u�������A�����[�h */
	KsScriptUnloadMathLib( m_pVirtualMachine );
	KsScriptUnloadSystemLib( m_pVirtualMachine );

	//---------------------------------------------------------------
	// �㏈�� 
	//---------------------------------------------------------------
	ksDELETE( m_pPhysicsThread );
	ksDELETE( m_pOVRSystem );
	ksDELETE( m_pForwardPlusRender );
	ksDELETE( m_pDeferredRender );
	ksDELETE( m_pCameraManager );
	ksDELETE( m_pGameResourceManager );
	ksDELETE( m_pPadManager );
	ksDELETE( m_pInputSystem );
	ksDELETE( m_pVirtualMachine );
	//ksDELETE( m_pSoundManager );
	ksDELETE( m_pPhysicsSystem );
	ksDELETE( m_pRenderSystem );
	ksDELETE( m_pMainWindow );

	/* �t�@�C���V�X�e���㏈�� */
	ksDELETE( m_pFileSystem );

	/* �T�E���h�V�X�e���㏈�� */
	//ksDELETE( m_pSoundManager );

	/* �f�o�b�N�㏈�� */
	//ksDEBUG_TERM();

	//---------------------------------------------------------------
	// �E�C���h�E�̐ݒ�t�@�C�����`�F�b�N����
	//---------------------------------------------------------------
	KsGameConfigManager::shutdown();

	//---------------------------------------------------------------
	// COM�㏈�� 
	//---------------------------------------------------------------
	::CoUninitialize();

	return ksTRUE;
}

/************************************************************************************************/
/*
 * �\�t�g�E�F�A�[���Z�b�g����
 */
/************************************************************************************************/
void KsGameSystem::softwareReset()
{
}

/************************************************************************************************/
/*
 * �\�t�g���Z�b�g�v�������������ǂ����H
 */
/************************************************************************************************/
KsBool KsGameSystem::isSoftwareReset()
{
	return ksFALSE;
}

/************************************************************************************************/
/*
 * �Q�[�����I��������
 */
/************************************************************************************************/
void KsGameSystem::gameExit()
{
	m_bMainLoop = ksFALSE;
}

/************************************************************************************************/
/*
 * �Q�[�����[�v�����H
 * @retval		ksTRUE			�Q�[�����[�v��
 * @retval		ksFALSE			�Q�[�����[�v�I��
 */
/************************************************************************************************/
KsBool KsGameSystem::isGameLoop()
{
	if( m_pMainWindow->messageLoop() )
	{
		if( isSoftwareReset() )
		{
			return ksFALSE;
		}

		return ksTRUE;
	}

	gameExit();

	return ksFALSE;
}

/************************************************************************************************/
/*
 * �Q�[�����[�v�����H
 * @retval		ksTRUE			�Q�[�����[�v��
 * @retval		ksFALSE			�Q�[�����[�v�I��
 */
/************************************************************************************************/
KsBool KsGameSystem::messageLoop()
{
	while( m_pMainWindow->messageLoop() )
	{
	}

	return ksTRUE;
}

/************************************************************************************************/
/*
 * �`��J�n
 */
/************************************************************************************************/
void KsGameSystem::begineRender()
{
	/* �`��J�n */
	//m_pRenderSystem->beginScene( (ksCLEAR_FLAG_COLOR | ksCLEAR_FLAG_DEPTH ), m_clearColor, 1.0f, 0 );
}

/************************************************************************************************/
/*
 * �`��I��
 */
/************************************************************************************************/
void KsGameSystem::endRender()
{
	//ksDEBUG_PRINT( "FPS:%2d", KsTimer::getFps() );
	//ksDEBUG_FLUSH();

	/* �`��I�� */
	//m_pRenderSystem->endScene();

	/* �`��o�b�t�@�ƕ\���o�b�t�@�����ւ� */
	m_pRenderSystem->present();
}

/************************************************************************************************/
/*
 * ���s����
 */
/************************************************************************************************/
void KsGameSystem::execute( void* pParam )
{
	// �V�[���X�V
	KsSceneManager::execute( pParam );
}
/************************************************************************************************/
/*
 * �`�悷��
 */
/************************************************************************************************/
void KsGameSystem::render( void* pParam )
{
	// �V�[���`��
	KsSceneManager::render( pParam );

	/* �`�揈�� */
	//render( pParam );

	//begineRender();

	// �����_�����O
	//m_renderTbl.render( pParam );
	m_pDeferredRender->render();

	endRender();
}
/************************************************************************************************/
/*
 * �X�V����
 */
/************************************************************************************************/
void KsGameSystem::update( void* pParam )
{
	/* �폜�t���O�������Ă����� */
	//for( KsInt32 i=0; i<KsWorkArea::m_count; i++ )
	//{
		//kill( KsWorkArea::m_work[ i ], pParam );
	//}

	//KsWorkArea::clear();
}

/************************************************************************************************/
/*
 * ���ׂĂ̏��������s
 * @param	pParam		�����ł킽�����p�����[�^���^�X�N��execute��render�̈����ɓn��
 *						�f�t�H���g�ł́ANULL���ݒ肳��Ă���B
 */
/************************************************************************************************/
void KsGameSystem::run( void* pParam )
{
	if( m_pPhysicsThread )
	{
		m_pPhysicsThread->waitSimulation();
	}

	/* ���s */
	execute( pParam );

	/* �`��(�J�����̕`��͂�������) */
	if( isRender() )
	{
		render( pParam );
	}

	/* �X�V */
	update( pParam );

	if( m_pPhysicsThread )
	{
		m_pPhysicsThread->startSimulation();
	}
}

/************************************************************************************************/
/*
 * �|�[�����O����
 */
/************************************************************************************************/
void KsGameSystem::polling()
{
	m_pFileSystem->callback();
}

/************************************************************************************************/
/*
 * �T�E���h�X�V����
 */
/************************************************************************************************/
void KsGameSystem::sound()
{
	//m_pSoundManager->update();
}

/************************************************************************************************/
/*
 * �p�b�h����
 */
/************************************************************************************************/
void KsGameSystem::pad()
{
	/* �p�b�h���X�V */
	m_pPadManager->update();
}

/************************************************************************************************/
/*
 * VSync�҂��̏���(���z)
 */
/************************************************************************************************/
void KsGameSystem::vsync()
{
	/* �^�C�}�[�X�V */
	KsTimer::update();

	/* VSYNC �҂�(���z) */
	//KsTimer::vsync( KsTimer::ksFPS60 );
}

/************************************************************************************************/
/*
 * �Q�[�����[�v
 */
/************************************************************************************************/
void KsGameSystem::loop()
{
	/* �Q�[�����[�v */
	while( isMainLoop() )
	{
		/* �\�t�g�E�F�A���Z�b�g */
		softwareReset();

		if( isGameLoop() )
		{
			/* �t�@�C���V�X�e���|�[�����O */
			polling();

			/* �T�E���h�X�V���� */
			sound();

			/* ���͏��� */
			pad();

			/* ���s���� */
			run( this );

			/* VSYNC �҂�(���z) */
			vsync();
		}
	}
}

/************************************************************************************************/
/*
 * ���f����ǉ�����
 */
/************************************************************************************************/
void KsGameSystem::addModel( KsModel* pModel )
{
	m_pDeferredRender->addModel( pModel );
}

/************************************************************************************************/
/*
 * �A�N�^�[��ǉ�����
 */
/************************************************************************************************/
void KsGameSystem::addActor( KsActor* pActor )
{
	m_pDeferredRender->addActor( pActor );
}

/************************************************************************************************/
/*
 * �C���X�^���X�擾
 */
/************************************************************************************************/
KsGameSystem* KsGameSystem::getInstancePtr()
{
	if( !m_pInstance )
	{
		m_pInstance = ksNew KsGameSystem();
	}

	return m_pInstance;
}

/************************************************************************************************/
/*
 * �C���X�^���X�j��
 */
/************************************************************************************************/
void KsGameSystem::destoryInstance()
{
	ksDELETE( m_pInstance );
}

/************************************************************************************************/
/*
 * �Q�[���^�X�N��ǉ�����
 */
/************************************************************************************************/
KsBool KsGameSystem::addGameTask( KsTask* pTask )
{
	m_pInstance->addTask( pTask );

	return ksTRUE;
}

/************************************************************************************************/
/*
 * �Q�[���^�X�N����菜��
 */
/************************************************************************************************/
KsBool KsGameSystem::removeGameTask( KsTask* pTask )
{
	m_pInstance->removeTask( pTask );

	return ksTRUE;
}

/************************************************************************************************/
/*
 * �Q�[���V�X�e������
 * @param	hInstance			�C���X�^���X
 * @param	hPrevInstance		�C���X�^���X
 * @param	lpCmdLine			�R�}���h���C��
 * @param	nCmdShow			�R�}���h�\��
 * @note	���łɃE�C���h�E������ꍇ�́A��������Ƃ̃T�C�Y�ŕ���������
 */
/************************************************************************************************/
KsGameSystem* KsGameCreate( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, KsInt32 nCmdShow )
{
	/* �}�l�[�W���𐶐����� */
	KsGameSystem*	pGameSystem;
	
	/* �C���X�^���X�擾�����ł́A���������͂� */
	pGameSystem = KsGameSystem::getInstancePtr();

	/* ���� */
	pGameSystem->create( hInstance, hPrevInstance, lpCmdLine, nCmdShow );

	return pGameSystem;
}

/************************************************************************************************/
/*
 * �Q�[�����[�v
 * @param	pGame	�Q�[���V�X�e���̃|�C���^
 */
/************************************************************************************************/
void KsGameLoop( KsGameSystem* pGame )
{
	pGame->loop();
}

/************************************************************************************************/
/*
 * �Q�[���V�X�e���j��
 * @param	pGame	�Q�[���V�X�e���̃|�C���^
 */
/************************************************************************************************/
void KsGameDestroy( KsGameSystem* pGame )
{
	/* �J�� */
	KsGameSystem::destoryInstance();

	/* �������[���[�N�`�F�b�N */
	//KsDumpMemoryLeaks();
}

