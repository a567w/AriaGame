/************************************************************************************************/
/** 
 * @file		KsCommandListDX11.cpp
 * @brief		コマンドリスト(DX11用)
 * @author		Tsukasa Kato
 * @date		2004/08/17
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>											 */
/*==============================================================================================*/
#include "KsDevDX11/KsDevDX11PreCompile.h"
#include "KsDevDX11/device/KsCommandListDX11.h"


/*==============================================================================================*/
/*									  << 宣言 >>												*/
/*==============================================================================================*/


/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsCommandListDX11::KsCommandListDX11()
	: m_pCommandList( 0 )
{
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsCommandListDX11::~KsCommandListDX11()
{
	ksRELEASE( m_pCommandList );
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
void KsCommandListDX11::clear()
{
	ksRELEASE( m_pCommandList );
}

