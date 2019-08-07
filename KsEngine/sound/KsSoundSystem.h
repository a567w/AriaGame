/************************************************************************************************/
/** 
 * @file		KsSoundSystem.h
 * @brief		サウンドシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSSOUNDSYSTEM_H__
#define __KSSOUNDSYSTEM_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                          */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsSoundSystem
 * @brief		サウンドシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsSoundSystem
{
	public:
		/**
		 * コンストラクタ
		 */
											KsSoundSystem();

		/**
		 * デストラクタ
		 */
		virtual								~KsSoundSystem();

		/**
		 * 初期化処理
		 * @param		hWnd				ウインドウのハンドル
		 * @retval		ksTRUE				初期化成功
		 * @retval		ksFALSE				初期化失敗
		 */
		virtual KsBool						initialize( void* pParam ) = 0;

		/**
		 * 更新処理
		 * @retval		ksTRUE				更新成功
		 * @retval		ksFALSE				更新失敗
		 */
		virtual KsBool						update() = 0;

		/**
		 * 後処理
		 * @retval		ksTRUE				後処理成功
		 * @retval		ksFALSE				後処理失敗
		 */
		virtual KsBool						terminate() = 0;

		/**
		 *
		 */
		virtual KsSoundData*				createSoundDataMemory( KsChar* strFile, KsUInt32 seconds, KsUInt32 sampleRate, KsUInt32 channels, KsUInt32 bits ) = 0;

		virtual KsSoundData*				createSoundDataStreaming( KsChar* strFile, KsUInt32 seconds, KsUInt32 sampleRate, KsUInt32 channels, KsUInt32 bits ) = 0;
};

#endif		/* __KSSOUNDSYSTEM_H__ */

