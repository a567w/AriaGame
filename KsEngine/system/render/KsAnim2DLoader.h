/************************************************************************************************/
/** 
 * @file		KsAnimation.h
 * @brief		ボーン
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSANIMLOADER_H__
#define __KSANIMLOADER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsMeshLoader.h"
#include "KsAnimation.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsAnimation
 * @brief		アニメーション
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
typedef struct _KS_KAM_FILE_HEADER
{
	KsUInt32				signature;			/**< 識別用						*/
	KsUInt32				version;			/**< バージョン情報				*/
	KsUInt32				type;				/**< タイプ						*/
	KsUInt32				flags;				/**< 各種フラグ					*/
}KS_KAM_FILE_HEADER;

typedef struct _KS_KAM_INFO_HEADER
{
	KsInt32					start;
	KsInt32					end;
	KsInt32					fps;
	KsInt32					numTrack;
}KS_KAM_INFO_HEADER;

typedef struct _KS_KAM_TRACK
{
	KsInt32					target;
	KsInt32					maxTime;
	KsInt32					numFrame;
}KS_KAM_TRACK;

typedef struct _KS_KAM_KEY_FRAME
{
	KsInt32					time;				// フレーム
	KS_KMD_VECTOR3D			translate;			// 位置
	KS_KMD_VECTOR4D			rotate;				// 回転(クォータニオン)
	KS_KMD_VECTOR3D			scale;				// スケール

}KS_KAM_KEY_FRAME;

extern KsAnimation* KsLoadAnim( const KsChar* pFileName );


#endif /* __KSANIMLOADER_H__ */

