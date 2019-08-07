/************************************************************************************************/
/** 
 * @file		KsSceneManager.h
 * @brief		シーン管理
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSSCENEMANAGER_H__
#define __KSSCENEMANAGER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsScene.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsSceneManager
 * @brief		シーン管理タスク
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
class KsSceneManager : public KsTaskManager
{
	public:
		/**
		 * コンストラクタ
		 */
											KsSceneManager();

		/**
		 * デストラクタ
		 */
		virtual								~KsSceneManager();
	
	protected:
		/**
		 * 初期化処理
		 * @retval		ksTRUE				成功
		 * @retval		ksFALSE				失敗
		 */
		KsBool								initialize();

		/**
		 * 後処理
		 * @retval		ksTRUE				成功
		 * @retval		ksFALSE				失敗
		 */
		KsBool								terminate();

		/**
		 * タスクの実行
		 * @param		pParam				パラメータ
		 */
		virtual void						execute( void* pParam );

		/**
		 * 描画処理
		 * @param		pParam				パラメータ
		 */
		virtual void						render( void* pParam );

	private:
		/**
		 * 指定シーンを生成する
		 * @param		scene				シーン
		 * @return							生成したシーンのポインタ
		 */
		KsScene*							createScene( ksSCENE_TYPE scene );

		/**
		 * 指定シーンを生成する
		 * @param		scene				シーン
		 * @return							生成したシーンのポインタ
		 */
		KsBool								addScene( ksSCENE_TYPE scene );

		/**
		 * 指定シーンを削除する
		 * @param		pScene				シーン
		 */
		void								destroyScene( KsScene* pScene );

	private:
		ksSCENE_TYPE						m_scene;
		KsScene*							m_pScene;	/**< 現在のシーン	*/
		//StCamera*							m_pCurrentCamera;
		//StCamera*							getNextCamera();
};


#endif /* __KSSCENEMANAGER_H__ */

