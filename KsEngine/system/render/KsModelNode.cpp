/************************************************************************************************/
/** 
 * @file		KsModelNode.h
 * @brief		カラー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsModelNode.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
KsModelNode::KsModelNode()
{
	m_pGeometry = NULL;
	m_pParent   = NULL;
}

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
KsModelNode::~KsModelNode()
{
	ksDELETE( m_pGeometry );
}

