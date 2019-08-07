/************************************************************************************************/
/** 
 * @file		KsSoundData.h
 * @brief		サウンドデータ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSSOUNDDATA_H__
#define __KSSOUNDDATA_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                          */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
typedef WORD  ksSOUNDINDEX;            // All normal indices
typedef BYTE  ksSOUNDNOTIFICATIONTYPE; // Notification type
typedef FLOAT ksSOUNDVARIABLEVALUE;    // Variable value
typedef WORD  ksSOUNDVARIABLEINDEX;    // Variable index
typedef WORD  ksSOUNDCATEGORY;         // Sound category
typedef BYTE  ksSOUNDCHANNEL;          // Audio channel
typedef FLOAT ksSOUNDVOLUME;           // Volume value
typedef LONG  ksSOUNDTIME;             // Time (in ms)
typedef SHORT ksSOUNDPITCH;            // Pitch value
typedef BYTE  ksSOUNDLOOPCOUNT;        // For all loops / recurrences
typedef BYTE  ksSOUNDVARIATIONWEIGHT;  // Variation weight
typedef BYTE  ksSOUNDPRIORITY;         // Sound priority
typedef BYTE  ksSOUNDINSTANCELIMIT;    // Instance limitations

/************************************************************************************************/
/**
 * サウンドステータス
 */
/************************************************************************************************/
enum ksSOUND_STATE
{
	ksSOUND_STATE_CREATED           = 0x00000001, /**<  Created, but nothing else			*/
	ksSOUND_STATE_PREPARING         = 0x00000002, /**<  In the middle of preparing			*/
	ksSOUND_STATE_PREPARED          = 0x00000004, /**<  Prepared, but not yet played		*/
	ksSOUND_STATE_PLAYING           = 0x00000008, /**<  Playing (though could be paused)	*/
	ksSOUND_STATE_STOPPING          = 0x00000010, /**<  Stopping							*/
	ksSOUND_STATE_STOPPED           = 0x00000020, /**<  Stopped								*/
	ksSOUND_STATE_PAUSED            = 0x00000040, /**<  Paused 								*/
	ksSOUND_STATE_INUSE             = 0x00000080, /**<  Object is in use 					*/
	ksSOUND_STATE_PREPAREFAILED     = 0x80000000, /**<  Object preparation failed.			*/
};


/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
enum ksSOUND_DATA_TYPE
{
	ksSOUND_DATA_UNKNOWN,
	ksSOUND_DATA_MEMORY,
	ksSOUND_DATA_STREAMING,
};

/************************************************************************************************/
/**
 * @class		KsSoundData
 * @brief		サウンドデータ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsSoundData
{
	public:
		/**
		 * コンストラクタ
		 */
								KsSoundData();

		/**
		 * デストラクタ
		 */
		virtual					~KsSoundData();

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
		 * @param	fVolume		ボリューム [ 0.0～1.0 ]
		 */
		virtual KsBool			setVolume( KsReal fVolume ) = 0;

		/**
		 * ループ回数をセットする
		 * @param	loopCount	ループ回数
		 */
		virtual void			setLoopCount( KsByte loopCount ) = 0;
};

#endif		/* __KSSOUNDDATA_H__ */

