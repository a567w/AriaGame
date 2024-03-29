/************************************************************************************************/
/** 
 * @file		KsHierarchy.h
 * @brief		骨組み(階層構造)
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSHIERARCHY_H__
#define __KSHIERARCHY_H__
#if 0
/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsType.h"
#include "KsJoint.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


typedef std::vector< KsJoint* >	KsJointList;

/************************************************************************************************/
/**
 * @class		KsHierarchy
 * @brief		階層構造
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsHierarchy
{
	public:
		/**
		 * コンストラクタ
		 */
		KsHierarchy(){}

		/**
		 * デストラクタ
		 */
		virtual								~KsHierarchy(){}

	public:
		KsJointList								m_pRootJointList;	/**< ルートになるジョイントリスト	*/
		KsJointList								m_pJointList;		/**< ジョイントリスト				*/
};

#endif

#endif		/* __KSHIERARCHY_H__ */




