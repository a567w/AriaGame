/************************************************************************************************/
/** 
 * @file		KsSoundDataBank.h
 * @brief		サウンドデータバンク
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSOUNDDATABANK_H__
#define __KSSOUNDDATABANK_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                          */
/*==============================================================================================*/
#include "KsSoundData.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsSoundDataBank
 * @brief		サウンドデータ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsSoundDataBank
{
	public:
		/**
		 * コンストラクタ
		 */
								KsSoundDataBank();

		/**
		 * デストラクタ
		 */
		virtual					~KsSoundDataBank();

		/**
		 * ステータス取得
		 * @return				サウンドステータス
		 */
		virtual ksSOUND_STATE	getState() = 0;

		/**
		 * 再生
		 */
		virtual KsBool			play() = 0;

		/**
		 * ストップ
		 */
		virtual KsBool			stop() = 0;

		/**
		 * ポーズ
		 * @param				ポーズフラグ
		 */
		virtual KsBool			pause( KsBool bPause ) = 0;

		/**
		 * ボリューム
		 * @param	fVolume		ボリューム [ 0.0〜1.0 ]
		 */
		virtual KsBool			setVolume( KsReal fVolume ) = 0;

		/**
		 * ループ回数をセットする
		 * @param	loopCount	ループ回数
		 */
		virtual void			setLoopCount( KsByte loopCount ) = 0;
};

#endif		/* __KSSOUNDDATABANK_H__ */

