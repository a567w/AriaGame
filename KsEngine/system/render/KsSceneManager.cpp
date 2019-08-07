/************************************************************************************************/
/** 
 * @file		StSceneManager.cpp
 * @brief		�V�[���Ǘ�
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "StGameSystemManager.h"
#include "StSceneManager.h"
//#include "StCamera.h"
//#include "StLogo.h"
#include "StTitle.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
StSceneManager::StSceneManager()
{
	/* ���ɕ`��I�[�_�[�́A�w�肵�Ȃ��B */
	// �`�悵�Ȃ��t���O�𗧂ĂĂ����K�v������
	//m_order = 0xffffffff;
	m_type = stTASK_TYPE_MANAGER;
}
/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
StSceneManager::~StSceneManager()
{
}
/************************************************************************************************/
/*
 * ����������(�}�l�[�W���ɓo�^���ꂽ�Ƃ��ɓo�^)
 * @param		pParam				�p�����[�^
 */
/************************************************************************************************/
void* StSceneManager::initialize( void* pParam )
{
#pragma unused( pParam )
	/* ���S�\��(1�x����) */
	addScene( stGAME_SCENE_LOGO );

	/* �{���́A�V�[�����ƂɃJ����������ׂ� */
	//addChild( new StCamera() );

	return NULL;
}
/************************************************************************************************/
/*
 * �^�X�N�̎��s
 * @param		pParam				�p�����[�^
 */
/************************************************************************************************/
void* StSceneManager::execute( void* pParam )
{
	StGameSystemManager*	pGM = (StGameSystemManager*)pParam;

	/* �V�[���̕ύX���`�F�b�N���� */
	switch( m_scene )
	{
#if 0
		case stGAME_SCENE_LOGO:
		{
			/* ���S */	
			addScene( stGAME_SCENE_TITLE );
			break;
		}
		case stGAME_SCENE_TITLE:
		{
			/* �^�C�g�� */
			if( stMOVIE_MODE_GGENE == pGM->getMovieMode() ){
				addScene( stGAME_SCENE_GGENE_MENU );
			}
			else{
				addScene( stGAME_SCENE_GUNDAM_MENU );
			}
			break;
		}
		case stGAME_SCENE_GUNDAM_MENU:
		{
			addScene( stGAME_SCENE_TITLE );
			break;
		}
		case stGAME_SCENE_GGENE_MENU:
		{
			addScene( stGAME_SCENE_TITLE );
			break;
		}
#endif
		default: { break; }
	}

	return NULL;
}
/************************************************************************************************/
/*
 * �`�揈��
 * @param		pParam				�p�����[�^
 */
/************************************************************************************************/
void* StSceneManager::render( void* pParam )
{
#pragma unused( pParam )
	return NULL;
}
/************************************************************************************************/
/*
 * �㏈���֐��Ń������[����폜�����Ƃ��ɌĂ΂��
 * @param		pParam				�p�����[�^
 */
/************************************************************************************************/
void* StSceneManager::terminate( void* pParam )
{
#pragma unused( pParam )
	return NULL;
}
/************************************************************************************************/
/*
 * �㏈���֐��Ń������[����폜�����Ƃ��ɌĂ΂��
 * @param		pParam				�p�����[�^
 * �f�o�b�N���j���[����D���ȃV�[��������悤�ɂ���
 */
/************************************************************************************************/
StScene* StSceneManager::createScene( stGAME_SCENE_KIND scene )
{
	m_scene = scene;

	// �V�[���I���̎��Ɏ��̃V�[�����w�肵�ď�����
	switch( scene )
	{
		case stGAME_SCENE_LOGO:
		{
			/* ���S */
			//return new StLogo();
			////return new StMsgScriptTest();
			return new StTitle( this );
		}
		case stGAME_SCENE_TITLE:
		{
			/* �^�C�g�� */
			return new StTitle( this );
		}
		case stGAME_SCENE_TITLE_SELECT:
		{
			/* �^�C�g���I����� */
			//return new StGundamMenu();
		}
		case stGAME_SCENE_GUNDAM_MENU:
		{
			/* �K���_���V���[�Y�ʃ��[�r�[�I����� */
			//return new StGundamMenu();
		}
		case stGAME_SCENE_GGENE_MENU:
		{
			/* G�W�F�l�V���[�Y�ʃ��[�r�[�I����� */
			//return new StGGeneMenu();
		}
		case stGAME_SCENE_OPTION:
		{
			/* �I�v�V���� */
		}
		default: { break; }
	}

	return NULL;;
}
/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void StSceneManager::addScene( stGAME_SCENE_KIND scene )
{
	/* �w��V�[����ǉ����� */
	if( !getNumChild() ){
		addChild( createScene( scene ) );
	}
}

