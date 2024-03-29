/************************************************************************************************/
/** 
 * @file		KsScriptSystemLib.h
 * @brief		スクリプト用のシステムライブラリ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSCRIPTSYSTEMLIB_H__
#define __KSSCRIPTSYSTEMLIB_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsTypeScript.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsVirtualMachine;

/************************************************************************************************/
/**
 * スクリプト用のシステムライブラリをロードする
 * @param	pVirtualMachine		このライブラリをロードするバーチャルマシンのポインタ
 * @retval	ksTRUE				ロード成功
 * @retval	ksFALSE				ロード失敗
 */
/************************************************************************************************/
ksSCRIPT_API KsBool KsScriptLoadSystemLib( KsVirtualMachine* pVirtualMachine );

/************************************************************************************************/
/**
 * スクリプト用のシステムライブラリをアンロードする
 * @param	pVirtualMachine		このライブラリをアンロードするバーチャルマシンのポインタ
 * @retval	ksTRUE				アンロード成功
 * @retval	ksFALSE				アンロード失敗
 */
/************************************************************************************************/
ksSCRIPT_API KsBool KsScriptUnloadSystemLib( KsVirtualMachine* pVirtualMachine );

#endif /* __KSSCRIPTSYSTEMLIB_H__ */



