/************************************************************************************************/
/** 
 * @file		StSceneManager.cpp
 * @brief		シーン管理
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "StGameSystemManager.h"
#include "StSceneManager.h"
//#include "StCamera.h"
//#include "StLogo.h"
#include "StTitle.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
StSceneManager::StSceneManager()
{
	/* 特に描画オーダーは、指定しない。 */
	// 描画しないフラグを立てておく必要がある
	//m_order = 0xffffffff;
	m_type = stTASK_TYPE_MANAGER;
}
/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
StSceneManager::~StSceneManager()
{
}
/************************************************************************************************/
/*
 * 初期化処理(マネージャに登録されたときに登録)
 * @param		pParam				パラメータ
 */
/************************************************************************************************/
void* StSceneManager::initialize( void* pParam )
{
#pragma unused( pParam )
	/* ロゴ表示(1度だけ) */
	addScene( stGAME_SCENE_LOGO );

	/* 本当は、シーンごとにカメラをつけるべき */
	//addChild( new StCamera() );

	return NULL;
}
/************************************************************************************************/
/*
 * タスクの実行
 * @param		pParam				パラメータ
 */
/************************************************************************************************/
void* StSceneManager::execute( void* pParam )
{
	StGameSystemManager*	pGM = (StGameSystemManager*)pParam;

	/* シーンの変更をチェックする */
	switch( m_scene )
	{
#if 0
		case stGAME_SCENE_LOGO:
		{
			/* ロゴ */	
			addScene( stGAME_SCENE_TITLE );
			break;
		}
		case stGAME_SCENE_TITLE:
		{
			/* タイトル */
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
 * 描画処理
 * @param		pParam				パラメータ
 */
/************************************************************************************************/
void* StSceneManager::render( void* pParam )
{
#pragma unused( pParam )
	return NULL;
}
/************************************************************************************************/
/*
 * 後処理関数でメモリーから削除されるときに呼ばれる
 * @param		pParam				パラメータ
 */
/************************************************************************************************/
void* StSceneManager::terminate( void* pParam )
{
#pragma unused( pParam )
	return NULL;
}
/************************************************************************************************/
/*
 * 後処理関数でメモリーから削除されるときに呼ばれる
 * @param		pParam				パラメータ
 * デバックメニューから好きなシーンを作れるようにする
 */
/************************************************************************************************/
StScene* StSceneManager::createScene( stGAME_SCENE_KIND scene )
{
	m_scene = scene;

	// シーン終了の時に次のシーンを指定して消える
	switch( scene )
	{
		case stGAME_SCENE_LOGO:
		{
			/* ロゴ */
			//return new StLogo();
			////return new StMsgScriptTest();
			return new StTitle( this );
		}
		case stGAME_SCENE_TITLE:
		{
			/* タイトル */
			return new StTitle( this );
		}
		case stGAME_SCENE_TITLE_SELECT:
		{
			/* タイトル選択画面 */
			//return new StGundamMenu();
		}
		case stGAME_SCENE_GUNDAM_MENU:
		{
			/* ガンダムシリーズ別ムービー選択画面 */
			//return new StGundamMenu();
		}
		case stGAME_SCENE_GGENE_MENU:
		{
			/* Gジェネシリーズ別ムービー選択画面 */
			//return new StGGeneMenu();
		}
		case stGAME_SCENE_OPTION:
		{
			/* オプション */
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
	/* 指定シーンを追加する */
	if( !getNumChild() ){
		addChild( createScene( scene ) );
	}
}

