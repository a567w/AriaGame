/************************************************************************************************/
/** 
 * @file		KsSceneManager.cpp
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
#include "Aria/KsGamePreCompile.h"
#include "Aria/game/scene/KsSceneManager.h"
#include "Aria/game/scene/KsTestScene.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
#if defined( _MASTER )
#define ksGAME_START_SCENE		ksSCENE_LOGO
#else
#define ksGAME_START_SCENE		ksSCENE_TEST_RENDER
#endif // #if defined( _MASTER )


/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsSceneManager::KsSceneManager()
	: KsTaskManager( KsUpdateOrder::orderMax(), KsDrawOrder::orderMax() )
{
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsSceneManager::~KsSceneManager()
{
	destroyScene( m_pScene );
}

/************************************************************************************************/
/*
 * 初期化処理
 * @retval		ksTRUE			成功
 * @retval		ksFALSE			失敗
 */
/************************************************************************************************/
KsBool KsSceneManager::initialize()
{
	addScene( ksGAME_START_SCENE );

	return ksTRUE;
}

/************************************************************************************************/
/*
 * 後処理
 * @retval		ksTRUE		成功
 * @retval		ksFALSE		失敗
 */
/************************************************************************************************/
KsBool KsSceneManager::terminate()
{
	return ksTRUE;
}

/************************************************************************************************/
/*
 * タスクの実行
 * @param		pParam				パラメータ
 */
/************************************************************************************************/
void KsSceneManager::execute( void* pParam )
{
	KsTaskManager::execute( pParam );

	/* シーンの変更をチェックする */
	if( m_pScene )
	{
		const ksSCENE_TYPE scene = m_pScene->getNextScene();

		if( ksSCENE_NONE != scene )
		{
			addScene( scene );
		}
	}
}
/************************************************************************************************/
/*
 * 描画処理
 * @param		pParam				パラメータ
 */
/************************************************************************************************/
void KsSceneManager::render( void* pParam )
{
	KsTaskManager::render( pParam );
}

/************************************************************************************************/
/*
 * 後処理関数でメモリーから削除されるときに呼ばれる
 * @param		pParam				パラメータ
 * デバックメニューから好きなシーンを作れるようにする
 */
/************************************************************************************************/
KsScene* KsSceneManager::createScene( ksSCENE_TYPE scene )
{
	// シーン終了の時に次のシーンを指定して消える
	switch( scene )
	{
		case ksSCENE_LOGO:
		{
			/* ロゴ */
		}
		case ksSCENE_TITLE:
		{
			/* タイトル */
		}
		case ksSCENE_TITLE_SELECT:
		{
			/* タイトル選択画面 */
		}
		case ksSCENE_OPTION:
		{
			/* オプション */
		}
		case ksSCENE_TEST_RENDER:
		{
			return ksNew KsTestScene();
		}
		default: { break; }
	}

	return NULL;;
}

/************************************************************************************************/
/*
 * 後処理関数でメモリーから削除されるときに呼ばれる
 * @param		pParam				パラメータ
 * デバックメニューから好きなシーンを作れるようにする
 */
/************************************************************************************************/
KsBool KsSceneManager::addScene( ksSCENE_TYPE scene )
{
	if( scene == m_scene )
	{
		return ksFALSE;
	}

	destroyScene( m_pScene );

	m_scene  = scene;
	m_pScene = createScene( scene );

	addTask( m_pScene );

	return ksTRUE;
}

/************************************************************************************************/
/*
 * 指定シーンを削除する
 * @param		pScene				シーン
 */
/************************************************************************************************/
void KsSceneManager::destroyScene( KsScene* pScene )
{
	if( NULL != m_pScene )
	{
		destroyTask( m_pScene );
	}
}


