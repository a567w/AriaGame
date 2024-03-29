/************************************************************************************************/
/** 
 * @file		KsPhysicsSystem.h
 * @brief		物理シミュレーションシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSPHYSICSSYSTEM_H__
#define __KSPHYSICSSYSTEM_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsPhysicsSystem
 * @brief		物理シミュレーションシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
class ksENGINE_API KsPhysicsSystem : public KsSingleton< KsPhysicsSystem >
{
	public:
		/**
		 * シングルトンの参照を取得
		 * @return							シングルトンの参照
		 */
		static KsPhysicsSystem&				getInstance();
		
		/**
		 * シングルトンのポインタを取得
		 * @return							シングルトンのポインタ
		 */
		static KsPhysicsSystem*				getInstancePtr();

	public:
		/**
		 * コンストラクタ
		 */
											KsPhysicsSystem();

		/**
		 * デストラクタ
		 */
		virtual								~KsPhysicsSystem();

		/**
		 * 初期化処理
		 * @param		pParam				パラメータ
		 * @retval		ksTRUE				初期化成功
		 * @retval		ksFALSE				初期化失敗
		 */
		virtual KsBool						initialize( void* pParam ) = 0;

		/**
		 * 後処理
		 * @retval		ksTRUE				後処理成功
		 * @retval		ksFALSE				後処理失敗
		 */
		virtual KsBool						terminate() = 0;

};

#endif		/* __KSPHYSICSSYSTEM_H__ */

