/************************************************************************************************/
/** 
 * @file		KsGameCommon.h
 * @brief		ゲーム共通定義
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSGAMECOMMON_H__
#define __KSGAMECOMMON_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
#define ksDEBUG_PREVIEW			( 1 )
//#define ksDEFERRED_SHADING_CS	( 1 )
#define ksDEFERRED_SHADING_PS	( 1 )
#define ksGAME_TITLE			"Aria Game System Version 0.0.1"
#define ksGAME_CLASS			"KsSystem"
//#define SPLASH_WINDOW_ON
#define USE_MRT_RENDER

/************************************************************************************************/
/**
 * @class		KsUpdateLv
 * @brief		Game2DCtrl更新レベル
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
class KsUpdateOrder
{
	public:
		enum
		{
			ksUPDATE_LV_SYSTEM = 0,
			ksUPDATE_LV_DEBUG,
			ksUPDATE_LV_FADE,
			ksUPDATE_LV_EFFECT,
			ksUPDATE_LV_MENU,
			ksUPDATE_LV_STAGE,
			ksUPDATE_LV_BG,
			ksUPDATE_LV_MAX,
		};

	public:
		static KsUInt32			system()	{ return ksUPDATE_LV_SYSTEM; }
		static KsUInt32			debug()		{ return ksUPDATE_LV_DEBUG;  }
		static KsUInt32			fade()		{ return ksUPDATE_LV_FADE;   }
		static KsUInt32			effect()	{ return ksUPDATE_LV_EFFECT; }
		static KsUInt32			menu()		{ return ksUPDATE_LV_MENU;   }
		static KsUInt32			stage()		{ return ksUPDATE_LV_STAGE;  }
		static KsUInt32			bg()		{ return ksUPDATE_LV_BG;     }
		static KsUInt32			orderMax()	{ return ksUPDATE_LV_MAX;    }
};


/************************************************************************************************/
/**
 * @class		KsDrawLv
 * @brief		Game2DCtrl描画レベル
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
class KsDrawOrder
{
	public:
		enum
		{
			ksDRAW_LV_SYSTEM = 0,
			ksDRAW_LV_DEBUG,
			ksDRAW_LV_FADE,
			ksDRAW_LV_EFFECT,
			ksDRAW_LV_MENU,
			ksDRAW_LV_STAGE,
			ksDRAW_LV_BG,
			ksDRAW_LV_MAX,
		};

	public:
		static KsUInt32			system()	{ return ksDRAW_LV_SYSTEM; }
		static KsUInt32			debug()		{ return ksDRAW_LV_DEBUG;  }
		static KsUInt32			fade()		{ return ksDRAW_LV_FADE;   }
		static KsUInt32			effect()	{ return ksDRAW_LV_EFFECT; }
		static KsUInt32			menu()		{ return ksDRAW_LV_MENU;   }
		static KsUInt32			stage()		{ return ksDRAW_LV_STAGE;  }
		static KsUInt32			bg()		{ return ksDRAW_LV_BG;     }
		static KsUInt32			orderMax()	{ return ksDRAW_LV_MAX;    }
};

/************************************************************************************************/
/**
 * @class		KsGameProcessPriority
 * @brief		処理の優先順位
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
class KsGameProcessPriority
{
	public:
		enum
		{
			ksPROCESS_PRIORITY_SYSTEM = 0,
			ksPROCESS_PRIORITY_DEBUG,
			ksPROCESS_PRIORITY_FADE,
			ksPROCESS_PRIORITY_EFFECT,
			ksPROCESS_PRIORITY_MENU,
			ksPROCESS_PRIORITY_GAME,
			ksPROCESS_PRIORITY_BG,
			ksPROCESS_PRIORITY_MAX = 31,
		};

	public:
		static KsUInt32			system()		{ return ksPROCESS_PRIORITY_SYSTEM; }
		static KsUInt32			debug()			{ return ksPROCESS_PRIORITY_DEBUG;  }
		static KsUInt32			fade()			{ return ksPROCESS_PRIORITY_FADE;   }
		static KsUInt32			effect()		{ return ksPROCESS_PRIORITY_EFFECT; }
		static KsUInt32			menu()			{ return ksPROCESS_PRIORITY_MENU;   }
		static KsUInt32			game()			{ return ksPROCESS_PRIORITY_GAME;   }
		static KsUInt32			bg()			{ return ksPROCESS_PRIORITY_BG;     }
		static KsUInt32			priorityMax()	{ return ksPROCESS_PRIORITY_MAX;    }
};

/************************************************************************************************/
/**
 * @class		KsGameRenderOrder
 * @brief		タスク描画オーダー
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
class KsGameRenderOrder
{
	public:
		enum
		{
			ksRENDER_ORDER_SYSTEM =  0,
			ksRENDER_ORDER_DEBUG  =  1,
			ksRENDER_ORDER_FADE   =  2,
			ksRENDER_ORDER_EFFECT =  3,

			ksRENDER_ORDER_MENU   =  4,
			ksRENDER_ORDER_GAME   =  5,
			ksRENDER_ORDER_TEST1  =  6,
			ksRENDER_ORDER_TEST2  =  7,


			ksRENDER_ORDER_3D_01  =  8,
			ksRENDER_ORDER_3D_02  =  9,
			ksRENDER_ORDER_3D_03  = 10,
			ksRENDER_ORDER_3D_04  = 11,
			ksRENDER_ORDER_3D_05  = 12,
			ksRENDER_ORDER_3D_06  = 13,
			ksRENDER_ORDER_3D_07  = 14,
			ksRENDER_ORDER_3D_08  = 15,

			ksRENDER_ORDER_3D_09  = 16,
			ksRENDER_ORDER_3D_10  = 17,
			ksRENDER_ORDER_3D_11  = 18,
			ksRENDER_ORDER_3D_12  = 19,
			ksRENDER_ORDER_3D_13  = 20,
			ksRENDER_ORDER_3D_14  = 21,
			ksRENDER_ORDER_3D_15  = 22,
			ksRENDER_ORDER_3D_16  = 23,
			

			ksRENDER_ORDER_BG     = 24,
			ksRENDER_ORDER_END    = 30,
			ksRENDER_ORDER_MAX    = 31
		};

	public:
		static KsUInt32			system()	{ return ksRENDER_ORDER_SYSTEM; }
		static KsUInt32			debug()		{ return ksRENDER_ORDER_DEBUG;  }
		static KsUInt32			fade()		{ return ksRENDER_ORDER_FADE;   }
		static KsUInt32			effect()	{ return ksRENDER_ORDER_EFFECT; }
		static KsUInt32			menu()		{ return ksRENDER_ORDER_MENU;   }
		static KsUInt32			game()		{ return ksRENDER_ORDER_GAME;   }
		static KsUInt32			bg()		{ return ksRENDER_ORDER_BG;     }
		static KsUInt32			orderMax()	{ return ksRENDER_ORDER_MAX;    }

		static KsUInt32			game2dOrder()
		{
			return (0);
		}

		static KsUInt32			game3dOrder()
		{
			return (0);
		}
};

/************************************************************************************************/
/**
 * @class		KsGameCommon
 * @brief		ゲーム共通定義
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
class KsGameCommon
{
	public:
		enum
		{
			ksGAME_PAD_MAX = 4,
		};
};

#endif /* __KSGAMECOMMON_H__ */



