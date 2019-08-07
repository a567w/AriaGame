/************************************************************************************************/
/** 
 * @file		KsScriptMathLib.cpp
 * @brief		スクリプト用の計算ライブラリ
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
#include "KsScriptMathLib.h"
#include "KsVirtualMachine.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
static KsInt32 ksCDECL KsScriptAbs( KsVirtualMachine* pVirtualMachine )
{
	if( pVirtualMachine->getVariableTypeTop() == ksVALUE_INT )
	{
		KsInt32		value_i = KsAbs( pVirtualMachine->getVariableTop()->m_value.i );
		pVirtualMachine->getVariable( 1 )->setInt( value_i );
		return ksSCRIPT_OK;
	}
	else if( pVirtualMachine->getVariableTypeTop() == ksVALUE_FLOAT )
	{
		KsReal		value_f = KsFabs( pVirtualMachine->getVariableTop()->m_value.f );
		pVirtualMachine->getVariable( 1 )->setFloat( value_f );
		return ksSCRIPT_OK;
	}

	return ksSCRIPT_ERROR;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
static KsInt32 ksCDECL KsScriptSqrt( KsVirtualMachine* pVirtualMachine )
{
	if( pVirtualMachine->getVariableTypeTop() == ksVALUE_INT )
	{
		KsInt32		value_i = (KsInt32)( KsSqrt( (KsReal)pVirtualMachine->getVariableTop()->m_value.i ) );
		pVirtualMachine->getVariable( 1 )->setInt( value_i );
		return ksSCRIPT_OK;
	}
	else if( pVirtualMachine->getVariableTypeTop() == ksVALUE_FLOAT )
	{
		KsReal		value_f = KsSqrt( pVirtualMachine->getVariableTop()->m_value.f );
		pVirtualMachine->getVariable( 1 )->setFloat( value_f );
		return ksSCRIPT_OK;
	}

	return ksSCRIPT_ERROR;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
static KsInt32 ksCDECL KsScriptSin( KsVirtualMachine* pVirtualMachine )
{
	if( pVirtualMachine->getVariableTypeTop() == ksVALUE_INT )
	{
		KsInt32		value_i = (KsInt32)( KsSin( (KsReal)pVirtualMachine->getVariableTop()->m_value.i ) );
		pVirtualMachine->getVariable( 1 )->setInt( value_i );
		return ksSCRIPT_OK;
	}
	else if( pVirtualMachine->getVariableTypeTop() == ksVALUE_FLOAT )
	{
		KsReal		value_f = KsSin( pVirtualMachine->getVariableTop()->m_value.f );
		pVirtualMachine->getVariable( 1 )->setFloat( value_f );
		return ksSCRIPT_OK;
	}

	return ksSCRIPT_ERROR;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
static KsInt32 ksCDECL KsScriptCos( KsVirtualMachine* pVirtualMachine )
{
	if( pVirtualMachine->getVariableTypeTop() == ksVALUE_INT )
	{
		KsInt32		value_i = (KsInt32)( KsCos( (KsReal)pVirtualMachine->getVariableTop()->m_value.i ) );
		pVirtualMachine->getVariable( 1 )->setInt( value_i );
		return ksSCRIPT_OK;
	}
	else if( pVirtualMachine->getVariableTypeTop() == ksVALUE_FLOAT )
	{
		KsReal		value_f = KsCos( pVirtualMachine->getVariableTop()->m_value.f );
		pVirtualMachine->getVariable( 1 )->setFloat( value_f );
		return ksSCRIPT_OK;
	}

	return ksSCRIPT_ERROR;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
static KsInt32 ksCDECL KsScriptTan( KsVirtualMachine* pVirtualMachine )
{
	if( pVirtualMachine->getVariableTypeTop() == ksVALUE_INT )
	{
		KsInt32		value_i = (KsInt32)( KsTan( (KsReal)pVirtualMachine->getVariableTop()->m_value.i ) );
		pVirtualMachine->getVariable( 1 )->setInt( value_i );
		return ksSCRIPT_OK;
	}
	else if( pVirtualMachine->getVariableTypeTop() == ksVALUE_FLOAT )
	{
		KsReal		value_f = KsTan( pVirtualMachine->getVariableTop()->m_value.f );
		pVirtualMachine->getVariable( 1 )->setFloat( value_f );
		return ksSCRIPT_OK;
	}

	return ksSCRIPT_ERROR;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
static KsInt32 ksCDECL KsScriptAsin( KsVirtualMachine* pVirtualMachine )
{
	if( pVirtualMachine->getVariableTypeTop() == ksVALUE_INT )
	{
		KsInt32		value_i = (KsInt32)( KsASin( (KsReal)pVirtualMachine->getVariableTop()->m_value.i ) );
		pVirtualMachine->getVariable( 1 )->setInt( value_i );
		return ksSCRIPT_OK;
	}
	else if( pVirtualMachine->getVariableTypeTop() == ksVALUE_FLOAT )
	{
		KsReal		value_f = KsASin( pVirtualMachine->getVariableTop()->m_value.f );
		pVirtualMachine->getVariable( 1 )->setFloat( value_f );
		return ksSCRIPT_OK;
	}

	return ksSCRIPT_ERROR;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
static KsInt32 ksCDECL KsScriptAcos( KsVirtualMachine* pVirtualMachine )
{
	if( pVirtualMachine->getVariableTypeTop() == ksVALUE_INT )
	{
		KsInt32		value_i = (KsInt32)( KsACos( (KsReal)pVirtualMachine->getVariableTop()->m_value.i ) );
		pVirtualMachine->getVariable( 1 )->setInt( value_i );
		return ksSCRIPT_OK;
	}
	else if( pVirtualMachine->getVariableTypeTop() == ksVALUE_FLOAT )
	{
		KsReal		value_f = KsACos( pVirtualMachine->getVariableTop()->m_value.f );
		pVirtualMachine->getVariable( 1 )->setFloat( value_f );
		return ksSCRIPT_OK;
	}

	return ksSCRIPT_ERROR;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
static KsInt32 ksCDECL KsScriptAtan( KsVirtualMachine* pVirtualMachine )
{
	if( pVirtualMachine->getVariableTypeTop() == ksVALUE_INT )
	{
		KsInt32		value_i = (KsInt32)( KsATan( (KsReal)pVirtualMachine->getVariableTop()->m_value.i ) );
		pVirtualMachine->getVariable( 1 )->setInt( value_i );
		return ksSCRIPT_OK;
	}
	else if( pVirtualMachine->getVariableTypeTop() == ksVALUE_FLOAT )
	{
		KsReal		value_f = KsATan( pVirtualMachine->getVariableTop()->m_value.f );
		pVirtualMachine->getVariable( 1 )->setFloat( value_f );
		return ksSCRIPT_OK;
	}

	return ksSCRIPT_ERROR;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
static KsInt32 ksCDECL KsScriptRand( KsVirtualMachine* pVirtualMachine )
{
	//pVirtualMachine->pushInt( KsRand() );

	return ksSCRIPT_ERROR;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
static KsInt32 ksCDECL KsScriptRandSeed( KsVirtualMachine* pVirtualMachine )
{
	//KsSRand( 1000 );
	//pVirtualMachine->pushInt( 0 );

	return ksSCRIPT_ERROR;
}


/************************************************************************************************/
/*
 * 計算ライブラリ用の関数ポインタのテーブル
 */
/************************************************************************************************/
static KsScriptLibInfo	s_mathScript[] = 
{
	{ "abs",		KsScriptAbs			},
	{ "sqrt",		KsScriptSqrt		},
	{ "sin",		KsScriptSin			},
	{ "cos",		KsScriptCos			},
	{ "tan",		KsScriptTan			},
	{ "asin",		KsScriptAsin		},
	{ "acos",		KsScriptAcos		},
	{ "atan",		KsScriptAtan		},
	{ "rand",		KsScriptRand		},
	{ "srand",		KsScriptRandSeed	},
	{ "end",		NULL				},
};

/************************************************************************************************/
/*
 * スクリプト用の計算ライブラリをロードする
 * @param	pVirtualMachine		このライブラリをロードするバーチャルマシンのポインタ
 * @retval	ksTRUE				ロード成功
 * @retval	ksFALSE				ロード失敗
 */
/************************************************************************************************/
KsBool KsScriptLoadMathLib( KsVirtualMachine* pVirtualMachine )
{
	if( !pVirtualMachine )
	{
		return ksFALSE;
	}

	return pVirtualMachine->loadLib( s_mathScript );
}
/************************************************************************************************/
/*
 * スクリプト用の計算ライブラリをアンロードする
 * @param	pVirtualMachine		このライブラリをアンロードするバーチャルマシンのポインタ
 * @retval	ksTRUE				アンロード成功
 * @retval	ksFALSE				アンロード失敗
 */
/************************************************************************************************/
KsBool KsScriptUnloadMathLib( KsVirtualMachine* pVirtualMachine )
{
	if( !pVirtualMachine )
	{
		return ksFALSE;
	}

	return pVirtualMachine->unloadLib( s_mathScript );
}

