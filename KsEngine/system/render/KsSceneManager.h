/************************************************************************************************/
/** 
 * @file		StSceneManager.h
 * @brief		シーン管理
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __STSCENEMANAGER_H__
#define __STSCENEMANAGER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "StScene.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * シーンごとに管理する
 */
/************************************************************************************************/
typedef enum _stGAME_SCENE_KIND
{
	stGAME_SCENE_NONE          =  0,					/**< シーンなし						*/
	stGAME_SCENE_LOGO          =  1,					/**< ロゴ							*/
	stGAME_SCENE_TITLE         =  2,					/**< タイトルスタート画面				*/
	stGAME_SCENE_TITLE_SELECT  =  3,					/**< タイトル選択画面					*/
	stGAME_SCENE_GUNDAM_MENU   =  4,					/**< ガンダムシリーズで選択メニュ		*/
	stGAME_SCENE_GGENE_MENU    =  5,					/**< Gジェネシリーズで選択メニュ		*/
	stGAME_SCENE_MUSIC_GALLERY =  6,					/**< ミュージックギャラリー			*/
	stGAME_SCENE_OPTION        =  7,					/**< オプション						*/
	stGAME_SCENE_DEMO_MOVI     =  8,					/**< デモムービー再生					*/
	stGAME_SCENE_MOVI          =  9,					/**< ムービー再生					*/
	stGAME_SCENE_CREDIT        = 10,					/**< クレジット画面					*/
	stGAME_SCENE_FORCE32       = 0x7fffffff,			/**< 強制32ビット					*/

}stGAME_SCENE_KIND;


/************************************************************************************************/
/**
 * @class		StSceneManager
 * @brief		シーン管理タスク
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
class StSceneManager : public StTask
{
	public:
		/**
		 * コンストラクタ
		 */
											StSceneManager();

		/**
		 * デストラクタ
		 */
		virtual								~StSceneManager();
	
	protected:
		/**
		 * 初期化処理(マネージャに登録されたときに登録)
		 * @param		pParam				パラメータ
		 */
		virtual void*						initialize( void* pParam );

		/**
		 * タスクの実行
		 * @param		pParam				パラメータ
		 */
		virtual void*						execute( void* pParam );

		/**
		 * 描画処理
		 * @param		pParam				パラメータ
		 */
		virtual void*						render( void* pParam );

		/**
		 * 後処理関数でメモリーから削除されるときに呼ばれる
		 * @param		pParam				パラメータ
		 */
		virtual void*						terminate( void* pParam );

	private:
		/**
		 * 指定シーンを生成する
		 * @param		scene				シーン
		 * @return							生成したシーンのポインタ
		 */
		StScene*							createScene( stGAME_SCENE_KIND scene );

		/**
		 * 指定シーンを追加する
		 * @param		scene				シーン
		 */
		void								addScene( stGAME_SCENE_KIND scene );

		//sceneCheck()
		//checkScene( )

	private:
		stGAME_SCENE_KIND					m_scene;	/**< 現在のシーン	*/
		
		/* sceneマネージャのほうで現在のカメラとワールドを管理する */
		// マネージャのほうで
		//StCamera*							m_pCurrentCamera;
		//StCamera*							getNextCamera();
};


#endif /* __STSCENEMANAGER_H__ */

