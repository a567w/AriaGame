/************************************************************************************************/
/** 
 * @file		KsScriptSystemLib.cpp
 * @brief		スクリプト用のシステムライブラリ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsScript/KsScriptPreCompile.h"
#include "KsScriptSystemLib.h"
#include "KsVirtualMachine.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * 指定バーチャルマシンへのコンソール出力
 * @param	pVirtualMachine		バーチャルマシンのポインタ
 * @return	ksSCRIPT_OK			正常
 *			ksSCRIPT_ERROR		エラー
 */
/************************************************************************************************/
static KsInt32 ksCDECL KsScriptPrint( KsVirtualMachine* pVirtualMachine )
{
	if( pVirtualMachine->getVariableTypeTop() == ksVALUE_INT )
	{
		KsInt32		value_i = pVirtualMachine->getVariableTop()->m_value.i;
		return ksSCRIPT_OK;
	}
	else if( pVirtualMachine->getVariableTypeTop() == ksVALUE_FLOAT )
	{
		KsReal		value_f = pVirtualMachine->getVariableTop()->m_value.f;
		return ksSCRIPT_OK;
	}

	return ksSCRIPT_ERROR;
}

/************************************************************************************************/
/*
 * システム用の関数ポインタのテーブル
 */
/************************************************************************************************/
static KsScriptLibInfo	s_systemScript[] = 
{
	{ "print",		KsScriptPrint		},
	{ "end",		NULL				},
};

/************************************************************************************************/
/*
 * スクリプト用のシステムライブラリをロードする
 * @param	pVirtualMachine		このライブラリをロードするバーチャルマシンのポインタ
 * @retval	ksTRUE				ロード成功
 * @retval	ksFALSE				ロード失敗
 */
/************************************************************************************************/
KsBool KsScriptLoadSystemLib( KsVirtualMachine* pVirtualMachine )
{
	return pVirtualMachine->loadLib( s_systemScript );
}

/************************************************************************************************/
/*
 * スクリプト用のシステムライブラリをアンロードする
 * @param	pVirtualMachine		このライブラリをアンロードするバーチャルマシンのポインタ
 * @retval	ksTRUE				アンロード成功
 * @retval	ksFALSE				アンロード失敗
 */
/************************************************************************************************/
KsBool KsScriptUnloadSystemLib( KsVirtualMachine* pVirtualMachine )
{
	if( !pVirtualMachine )
	{
		return ksFALSE;
	}

	return pVirtualMachine->unloadLib( s_systemScript );
}






