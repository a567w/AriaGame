/************************************************************************************************/
/** 
 * @file		KsCalculate.cpp
 * @brief		演算命令
 * @author		Tsukasa Kato
 * @date		2006/10/17
 * @since		2006/10/17
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsScript/KsScriptPreCompile.h"
#include "KsScriptCalculate.h"

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
void KsVariableAdd( KsVariable* pOutVar, KsVariable* pVar1, KsVariable* pVar2 )
{
	if( (pVar1->getType() == ksVALUE_INT ) && (pVar2->getType() == ksVALUE_INT) )
	{
		/* 整数 */
		pOutVar->setInt( pVar1->m_value.i + pVar2->m_value.i );
	}
	else
	{
		/* 浮動小数 */
		pOutVar->setFloat( pVar1->getFloat() + pVar2->getFloat() );
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsVariableSub( KsVariable* pOutVar, KsVariable* pVar1, KsVariable* pVar2 )
{
	if( (pVar1->getType() == ksVALUE_INT ) && (pVar2->getType() == ksVALUE_INT) )
	{
		/* 整数 */
		pOutVar->setInt( pVar1->m_value.i - pVar2->m_value.i );
	}
	else
	{
		/* 浮動小数 */
		pOutVar->setFloat( pVar1->getFloat() - pVar2->getFloat() );
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsVariableMul( KsVariable* pOutVar, KsVariable* pVar1, KsVariable* pVar2 )
{
	if( (pVar1->getType() == ksVALUE_INT ) && (pVar2->getType() == ksVALUE_INT) )
	{
		/* 整数 */
		pOutVar->setInt( pVar1->m_value.i * pVar2->m_value.i );
	}
	else
	{
		/* 浮動小数 */
		pOutVar->setFloat( pVar1->getFloat() * pVar2->getFloat() );
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsVariableDiv( KsVariable* pOutVar, KsVariable* pVar1, KsVariable* pVar2 )
{
	if( (pVar1->getType() == ksVALUE_INT ) && (pVar2->getType() == ksVALUE_INT) )
	{
		/* 整数 */
		if( pVar2->m_value.i == 0 )
		{
			
		}
		
		pOutVar->setInt( pVar1->m_value.i / pVar2->m_value.i );
	}
	else
	{
		/* 浮動小数 */
		if( pVar2->getFloat() < 0.00000001f )
		{
		}
		pOutVar->setFloat( pVar1->getFloat() / pVar2->getFloat() );
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsVariableRem( KsVariable* pOutVar, KsVariable* pVar1, KsVariable* pVar2 )
{
	if( (pVar1->getType() == ksVALUE_INT ) && (pVar2->getType() == ksVALUE_INT) )
	{
		/* 整数 */
		if( pVar2->m_value.i == 0 )
		{
		}
		pOutVar->setInt( pVar1->m_value.i % pVar2->m_value.i );
	}
	else
	{
		/* 浮動小数 */
		if( pVar2->getFloat() < 0.00000001f )
		{
		}
		pOutVar->setFloat( fmodf( pVar1->getFloat(), pVar2->getFloat() ) );
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsVariableBitAND( KsVariable* pOutVar, KsVariable* pVar1, KsVariable* pVar2 )
{
	pOutVar->setInt( ( pVar1->getInt() & pVar2->getInt() ) );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsVariableBitOR( KsVariable* pOutVar, KsVariable* pVar1, KsVariable* pVar2 )
{
	pOutVar->setInt( ( pVar1->getInt() | pVar2->getInt() ) );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsVariableBitXOR( KsVariable* pOutVar, KsVariable* pVar1, KsVariable* pVar2 )
{
	pOutVar->setInt( ( pVar1->getInt() ^ pVar2->getInt() ) );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsVariableMinus( KsVariable* pOutVar, KsVariable* pVar1 )
{
	if( pVar1->getType() == ksVALUE_INT )
	{
		/* 整数 */
		pOutVar->setInt( -pVar1->m_value.i );
	}
	else
	{
		/* 浮動小数 */
		pOutVar->setFloat( -pVar1->m_value.f );
	}
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsVariableNot( KsVariable* pOutVar, KsVariable* pVar1 )
{
	if( pVar1->getType() == ksVALUE_INT )
	{
		/* 整数 */
		if( pVar1->m_value.i == 0 )
		{
			pOutVar->setInt( 1 );
		}
		else
		{
			pOutVar->setInt( 0 );
		}
	}
	else
	{
		/* 浮動小数 */
		if( pVar1->m_value.f == 0.0f )
		{
			pOutVar->setInt( 1 );
		}
		else
		{
			pOutVar->setInt( 0 );
		}
	}
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsVariableInv( KsVariable* pOutVar, KsVariable* pVar1 )
{
	pOutVar->setInt( (~pVar1->getInt()) );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsVariableShiftLeft( KsVariable* pOutVar, KsVariable* pVar1, KsVariable* pVar2 )
{
	pOutVar->setInt( ( pVar1->getInt() << pVar2->getInt() ) );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsVariableShiftRight( KsVariable* pOutVar, KsVariable* pVar1, KsVariable* pVar2 )
{
	pOutVar->setInt( ( pVar1->getInt() >> pVar2->getInt() ) );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsVariableEQ( KsVariable* pOutVar, KsVariable* pVar1, KsVariable* pVar2 )
{
	if( (pVar1->getType() == ksVALUE_INT ) && (pVar2->getType() == ksVALUE_INT) )
	{
		/* 整数 */
		pOutVar->setInt( (pVar1->m_value.i == pVar2->m_value.i) );
	}
	else
	{
		/* 浮動小数 */
		pOutVar->setFloat( (pVar1->getFloat() == pVar2->getFloat()) );
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsVariableNEQ( KsVariable* pOutVar, KsVariable* pVar1, KsVariable* pVar2 )
{
	if( (pVar1->getType() == ksVALUE_INT ) && (pVar2->getType() == ksVALUE_INT) )
	{
		/* 整数 */
		pOutVar->setInt( (pVar1->m_value.i != pVar2->m_value.i) );
	}
	else
	{
		/* 浮動小数 */
		pOutVar->setFloat( (pVar1->getFloat() != pVar2->getFloat()) );
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsVariableLT( KsVariable* pOutVar, KsVariable* pVar1, KsVariable* pVar2 )
{
	if( (pVar1->getType() == ksVALUE_INT ) && (pVar2->getType() == ksVALUE_INT) )
	{
		/* 整数 */
		pOutVar->setInt( (pVar1->m_value.i < pVar2->m_value.i) );
	}
	else
	{
		/* 浮動小数 */
		pOutVar->setFloat( (pVar1->getFloat() < pVar2->getFloat()) );
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsVariableGT( KsVariable* pOutVar, KsVariable* pVar1, KsVariable* pVar2 )
{
	if( (pVar1->getType() == ksVALUE_INT ) && (pVar2->getType() == ksVALUE_INT) )
	{
		/* 整数 */
		pOutVar->setInt( (pVar1->m_value.i > pVar2->m_value.i) );
	}
	else
	{
		/* 浮動小数 */
		pOutVar->setFloat( (pVar1->getFloat() > pVar2->getFloat()) );
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsVariableLTE( KsVariable* pOutVar, KsVariable* pVar1, KsVariable* pVar2 )
{
	if( (pVar1->getType() == ksVALUE_INT ) && (pVar2->getType() == ksVALUE_INT) )
	{
		/* 整数 */
		pOutVar->setInt( (pVar1->m_value.i <= pVar2->m_value.i) );
	}
	else
	{
		/* 浮動小数 */
		pOutVar->setFloat( (pVar1->getFloat() <= pVar2->getFloat()) );
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsVariableGTE( KsVariable* pOutVar, KsVariable* pVar1, KsVariable* pVar2 )
{
	if( (pVar1->getType() == ksVALUE_INT ) && (pVar2->getType() == ksVALUE_INT) )
	{
		/* 整数 */
		pOutVar->setInt( (pVar1->m_value.i >= pVar2->m_value.i) );
	}
	else
	{
		/* 浮動小数 */
		pOutVar->setFloat( (pVar1->getFloat() >= pVar2->getFloat()) );
	}
}


