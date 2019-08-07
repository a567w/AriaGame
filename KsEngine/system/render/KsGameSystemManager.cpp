#if 0

/************************************************************************************************/
/** 
 * @file		KsGameSystemManager.cpp
 * @brief		�Q�[���}�l�[�W��
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsGameSystemManager.h"
#include "StPs2IOP.h"
#include "StTimer.h"
#include "StVBlank.h"
#include "StMallocFix.h"
#include "StSceneManager.h"
#include "StDebugManager.h"
//#include "StTimer.h"
//#include "StSprite.h"
//#include "StDebugManager.h"
//#include "StSoundUtil.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsGameSystemManager::KsGameSystemManager()
{
	m_gameMode            = 0;
	m_gameTimer           = 0;
	m_exitFlag            = stSOFT_EXIT_FLAG_OFF;
	m_softResetFlag       = stSOFT_RESET_FLAG_OFF;
	m_softResetPermission = stPERMISSION_OK;
	m_pauseFlag           = stPAUSE_FLAG_OFF;
	m_pausePermission     = stPERMISSION_OK;
	m_pPadManager   = NULL;
}
/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsGameSystemManager::~KsGameSystemManager()
{
	
}

/************************************************************************************************/
/**
* �C���X�^���X�擾
*/
/************************************************************************************************/
KsGameSystemManager* KsGameSystemManager::getInstance()
{
	static KsGameSystemManager		gsm;

	return ( &gsm );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsGameSystemManager::initialize()
{
	/* �^�C�}������ */
	StTimerInitialize();

	/* �p�b�h������ */
	StPadManagerInitialize();

	/* RenderWare������ */
	m_renderSystem.initialize();
	
	/* �p�����[�^���Z�b�g */
	//m_pFileSystem = StFileSystemPSP::instance();
	m_pPadManager = StPadManager::instance();
	
	/* �^�X�N�I�[�_�[���Z�b�g���� */
	setTaskOrder();
	
	/* �Œ�1�́A�J����������Ă����� */
	/* ���[�g�^�X�N����� */
	setRootTask( new StSceneManager() );
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsGameSystemManager::terminate()
{
	/* �}�l�[�W�����Q�Ƃ��Ă���^�X�N������̂�,�܂��^�X�N�������Ȃ��Ƃ܂��� */
	allKill( this );

	/* �`��V�X�e�����J������ */
	m_renderSystem.terminate();

	/* �t�@�C���V�X�e���㏈�� */
	//StFileSystemPSPTerminate();

	/* ���O�֌W�㏈�� */
	//StLogTerminate();

}
/************************************************************************************************/
/*
 * �\�t�g���Z�b�g
 */
/************************************************************************************************/
void KsGameSystemManager::softResetInitialize()
{
	/* �\�t�g���Z�b�gOFF */
	m_softResetFlag = stSOFT_RESET_FLAG_OFF;

	/* �������Ƃǂ̃V�[���ɖ߂邩�Ȃǂ̏�� */
}
/************************************************************************************************/
/*
 * �\�t�g���Z�b�g�`�F�b�N
 */
/************************************************************************************************/
void KsGameSystemManager::softExitCheck()
{
	if( ( m_pPadManager->getNow() & stPAD_SOFT_RESET ) == stPAD_SOFT_RESET ){
		m_softResetFlag = stSOFT_RESET_FLAG_ON;
		m_exitFlag      = stSOFT_EXIT_FLAG_ON;
	}
}
/************************************************************************************************/
/*
 * �Q�[�����[�v
 */
/************************************************************************************************/
void KsGameSystemManager::gameLoop()
{
	/* �Q�[�����[�v */
	while( m_exitFlag )
	{
		/* �Q�[���V�X�e���n�̏����� */
		softResetInitialize();

		while( m_softResetFlag )
		{
			/* �p�b�h���X�V */
			//KsPadManagerUpdate();

			/* �^�X�N���s(�`�悪�I�����Ă���ꊇ�ō폜����������悤�ɕύX����) */
			run( (void*)this );

			/* �I���`�F�b�N */
			softExitCheck();

			/* �^�C�}�[�̍X�V */
			StTimerUpdate();
		}
	}

}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsGameSystemManager::begineRender()
{
	//m_renderSystem.beginScene();
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsGameSystemManager::endRender()
{
	//m_renderSystem.endScene();
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsGameSystemManager::setTaskOrder()
{
	/* �X�v���C�g�^�X�N�̓\�[�g���g�p����悤�ɂ��� */
	//this->m_renderTbl.getOrder( stSPRITE_TASK_ORDER )->setFlags( stOT_FLAGS_PRIORITYSORT );
}

#if 0
sTestSystem*	KsTestSystemCreate()
{
	return new KsTestSystem();
}

KsTestSystem::KsTestSystem()
{
	m_pMainWindow   = NULL;
}

KsTestSystem::~KsTestSystem()
{
	ksDELETE( m_pMainWindow );
}

KsBool KsGameSystemManager::createWindow()
{
	RECT			rect;

	/* �f�X�N�g�b�v�̃N���C�A���g�̈���擾���� */
	KsGetDeskTopClientRect( &rect );

	/* ini �t�@�C������ݒ���擾���� */
	/*
	�t���X�N���[��
	window size x y
	flag
	*/
	/* �E�C���h�E�̐����p��[���[�^���Z�b�g���� */
	m_mainWindowParam.m_caption   = "Test";
	m_mainWindowParam.m_className = "KsSystem";
	m_mainWindowParam.m_style     = ksWINDOW_DEFAULT_STYLE;
	m_mainWindowParam.m_styleEx   = 0;
	m_mainWindowParam.m_posX      = ( rect.right  - rect.left )/2 - 320;
	m_mainWindowParam.m_posY      = ( rect.bottom - rect.top  )/2 - 240;
	m_mainWindowParam.m_sizeX     = 640;
	m_mainWindowParam.m_sizeY     = 480;

	/* �E�C���h�E���� */
	m_pMainWindow = new KsWindow();

	if( !m_pMainWindow ){
		return ksFALSE;
	}

	if( !( m_pMainWindow->create( m_mainWindowParam ) ) ){
		return ksFALSE;
	}

	return ksTRUE;
}

KsBool KsTestSystem::Create( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, KsInt32 nCmdShow )
{
	KsAppInstance::set( hInstance, hPrevInstance, lpCmdLine, nCmdShow );

	//m_pRenderSystem = new KsRenderSystemGL( m_pMainWindow->getHWnd() );
	m_pRenderSystem = new KsRenderSystemDX( m_pMainWindow->getHWnd() );


	m_pRenderSystem->auto3DMode();

	// �������ƏI���̂Ƃ��E�G�C�g������K�v������

	return ksTRUE;
}


/************************************************************************************************/
/*
 * �E�G�C�g
 */
/************************************************************************************************/


void KsTestSystem::Loop()
{
	do{
		m_pRenderSystem->beginScene( ksCLEAR_FLAG_COLOR | ksCLEAR_FLAG_DEPTH, KsColor( 0, 80, 80, 1 ), 1.0f, 0 );
		m_pRenderSystem->endScene();
		m_pRenderSystem->swapBuffer();
		vsync( 1 );

	}while( m_pMainWindow->messageLoop() );
}
#endif



#endif

