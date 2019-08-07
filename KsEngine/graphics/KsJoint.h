/************************************************************************************************/
/** 
 * @file		KsJoint.h
 * @brief		ジョイント
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSJOINT_H__
#define __KSJOINT_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsType.h"
#include "KsVector.h"
#include "KsMatrix.h"
#include "KsQuaternion.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

#if 0
/************************************************************************************************/
/**
 * @class		KsJoint
 * @brief		ジョイント
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsJoint
{
	public:
		/**
		 * コンストラクタ
		 */
										KsJoint();

		/**
		 * デストラクタ
		 */
		virtual						~KsJoint();

	public:
		KsSkeleton*						m_pSkeleton;		/**< スケルトンのポインタ		*/
		std::string						m_name;				/**< 名前					*/
		KsInt32						m_id;				/**< ボーンID				*/
		KsUInt32						m_target;			/**< 描画ターゲット			*/
		KsUInt32						m_flags;			/**< 各種フラグ				*/
		KsInt32						m_parent;			/**< 親のID					*/
		KsJointIDList					m_children;			/**< 子供のIDリスト			*/
		KsUserData*						m_pUserData;		/**< ユーザーデータ			*/

		KsVector3d						m_initPivot;		/**< 初期の基点				*/
		KsVector3d						m_initTranslate;	/**< 初期の位置				*/
		KsQuaternion					m_initRotate;		/**< 初期の回転				*/
		KsVector3d						m_initScale;		/**< 初期のスケール			*/

		KsVector3d						m_pivot;			/**< 基点					*/
		KsVector3d						m_translate;		/**< 位置					*/
		KsQuaternion					m_rotate;			/**< 回転					*/
		KsVector3d						m_scale;			/**< スケール				*/

		KsMatrix4x4					m_localMatrix;		/**< ローカルマトリックス		*/
		KsMatrix4x4					m_worldMatrix;		/**< ワールドマトリックス		*/
		KsMatrix4x4					m_stackMatrix;		/**< マトリックススタック		*/
		KsVector3d						m_stackScale;		/**< スケールスタック			*/
};


class KsSkeleton;
class KsJoint;

typedef std::vector< KsInt32 >	KsJointIDList;


#endif

#endif		/* __KSJOINT_H__ */



