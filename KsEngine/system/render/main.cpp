/*************************************************************************************************/
/**
 * @file	main.cpp
 * @brief	���C���֐�
 * @author	Tsukasa Kato
 * @date	2004/12/13
 * @version	1.0.0
 */
/*************************************************************************************************/

/*===============================================================================================*/
/*                                 << �C���N���[�h >>                                             */
/*===============================================================================================*/
#include "StCommon.h"
#include "StModuleManager.h"
#include "StGameSystemManager.h"
#include "StMemoryManager.h"
#include "StMoviePlayer.h"

/*===============================================================================================*/
/*										<< ��` >>												 */
/*===============================================================================================*/

/* ���W���[�����ƃo�[�W���� (name, atribute, major, mainor) */
SCE_MODULE_INFO( ggmc, 0, 0, 1 );

/* malloc �p�q�[�v�T�C�Y */
SceInt32 sce_newlib_heap_kb_size = ( 18*1024 );	/*�@18 MB	*/

/* �X�^�b�N�T�C�Y */
SceInt32 sce_newlib_stack_kb_size = 512;		/*�@512 KB	*/

/* main()�֐��̓��삷��X���b�h�̗D��x */
SceInt32 sce_newlib_priority = 64;

/* �o�^���W���[���ꗗ */
static ST_MODULE_TBL_DATA		s_moduleTbl[] = 
{
	{ "KMODULE/videocodec.prx",      0,      0 },
	{ "KMODULE/sc_sascore.prx",      0,      1 },
	{ "KMODULE/audiocodec.prx",      0,      2 },
	{ "KMODULE/mpegbase.prx",        0,      3 },
	{ "MODULE/libatrac3plus.prx",    1,      4 },
	{ "MODULE/mpeg.prx",             1,      5 },
	{ "MODULE/libfont.prx",          1,      6 },
	{ "none",                   0xffff, 0xffff }
};

/*************************************************************************************************/
/**
 * �I���R�[���o�b�N�ɂ���ČĂяo�����֐����`���܂��B
 */
/*************************************************************************************************/
static int exitFunc( int count, int arg1, void* arg2 )
{
    /* arg1 �� NotifyCallback �œn���������ł� */
    /* arg2 �� CreateCallback �ŗ^����������ł� */
    StPrintf("** %s(0x%08x)\n", __FUNCTION__, *((int *)arg2));

    /**/
    /* �����ŃA�v���P�[�V�����ŗL�̏I���������s���܂��B */
    /* �摜��T�E���h�̏����͓��ɍs��Ȃ��Ă��\���܂���B */
    /**/
	StGameSystemManager*	pSys = (StGameSystemManager*)arg2;

	// �X���b�h�������Ă�����
	// �T�E���h�ƃ��[�r�[�̃X���b�h���~�߂�K�v������
	//pSys->crash();
	//StUmdUnAssign();

	/* ���[�r�[���Đ�����������X���b�h���I�������� */
	StMoviePlayer::exit();

	/* �Q�[���V�X�e���㏈�� */
	pSys->terminate();

	/* ���W���[���J�� */
	StModuleManager*		pModule = StModuleManager::instance();
	pModule->unloadAll();

    /* �Q�[���I���V�X�e���T�[�r�X���Ăяo���܂��B */
    sceKernelExitGame();

    /* ��L�֐��͂��̊֐����ɖ߂��Ă��܂���B */
    return 0;
}

/*************************************************************************************************/
/**
 * VFPU���g�����߂�Thread���g���K�v������
 */
/*************************************************************************************************/
#if 0
void StMainThread( SceSize _ArgNum, void* _ArgData )
{
	/* �}���`�X���b�h�ɂ���K�v���� */
	StModuleManager*		pModule = StModuleManager::instance();
	StGameSystemManager*	pSys    = StGameSystemManager::instance();
	SceUID					exitCB;

	/* ���W���[���ǂݍ��� */
	pModule->loadAll( s_moduleTbl );

    /*  HOME�܂���UMD��������ďI���p�̃R�[���o�b�N�֐����� */
	exitCB = sceKernelCreateCallback( "gameExitCB", exitFunc, (void *)pSys );

    /* �R�[���o�b�N��o�^���܂��B */
    sceKernelRegisterExitCallback( exitCB );

	/* �Q�[���V�X�e�������� */
	pSys->initialize();

	/* �Q�[�����[�v */
	pSys->gameLoop();

	/* �Q�[���V�X�e���㏈�� */
	pSys->terminate();

	/* �������[���[�N�`�F�b�N */
	StDumpMemoryLeaks();

	/* ���W���[���J�� */
	pModule->unloadAll();

	StPrintf( "PROGRAM EXIT!!\n" );

	return 0;
}
/*************************************************************************************************/
/**
 * ���C���X���b�h�X�^�[�g
 */
/*************************************************************************************************/
void StStartMainThread()
{
	SceUID		mainThread = 0;

	mainThread = sceKernelCreateThread( "main", MainThread, 64, 512*1024, SCE_KERNEL_TH_USE_VFPU, NULL );
	sceKernelStartThread( mainThread, 0, NULL );
	sceKernelSleepThread();
}
#endif
/*************************************************************************************************/
/**
 * ���C��
 */
/*************************************************************************************************/
int main(void)
{
	/* �}���`�X���b�h�ɂ���K�v���� */
	StModuleManager*		pModule = StModuleManager::instance();
	StGameSystemManager*	pSys    = StGameSystemManager::instance();
	SceUID					exitCB;

	/* ���W���[���ǂݍ��� */
	pModule->loadAll( s_moduleTbl );

    /*  HOME�܂���UMD��������ďI���p�̃R�[���o�b�N�֐����� */
	exitCB = sceKernelCreateCallback( "gameExitCB", exitFunc, (void *)pSys );

    /* �R�[���o�b�N��o�^���܂��B */
    sceKernelRegisterExitCallback( exitCB );

	/* �Q�[���V�X�e�������� */
	pSys->initialize();

	/* �Q�[�����[�v */
	pSys->gameLoop();

	/* �Q�[���V�X�e���㏈�� */
	pSys->terminate();

	/* �������[���[�N�`�F�b�N */
	StDumpMemoryLeaks();

	/* ���W���[���J�� */
	pModule->unloadAll();

	StPrintf( "PROGRAM EXIT!!\n" );

	return 0;
}







