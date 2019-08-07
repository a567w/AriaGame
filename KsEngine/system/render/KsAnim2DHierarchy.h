/************************************************************************************************/
/** 
 * @file		KsAnimKeyFrame.h
 * @brief		ボーン
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSANIM2DHIERARCHY_H__
#define __KSANIM2DHIERARCHY_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsCore.h"
#include "KsColor.h"
#include "KsVector.h"
#include "KsArray.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsAnim2DJoint;

#if 0

/************************************************************************************************/
/**
 * @class		KsAnim2DHierarchy
 * @brief		階層構造
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsAnim2DHierarchy
{
		typedef KsArray< KsAnim2DJoint* >	KsAnim2DJointArray;

	public:
		/**
		 * コンストラクタ
		 */
								KsAnim2DHierarchy();

		/**
		 * デストラクタ
		 */
		virtual				~KsAnim2DHierarchy();

		/**
		 * ルートジョイント数を取得する
		 * @return				ルートジョイント数
		 */
		KsUInt32				getNumRootJoint() { return m_vpRootJoints.size(); }

		/**
		 * ルートジョイントを取得する
		 * @param	index		ルートジョイントインデックス
		 * @return				指定のルートジョイントのポインタ
		 */
		KsAnim2DJoint*			getRootJoint( KsUInt32 index=0 ) { return m_vpRootJoints[ index ]; }

		/**
		 * ジョイント数を取得する
		 * @return				ジョイント数
		 */
		KsUInt32				getNumJoint() { return m_vpJoints.size(); }

		/**
		 * ジョイントを取得する
		 * @param	index		インデックス
		 * @return				指定ジョイントのポインタ
		 */
		KsAnim2DJoint*			getJoint( KsUInt32 index ) { return m_vpJoints[ index ]; }

		/** 
		 * ジョイントを検索する
		 * @param	id			ID
		 * @return				指定ジョイントのポインタ
		 */
		KsAnim2DJoint*			findJoint( KsInt32 id );

		/**
		 * 子供の更新処理
		 * @param	pJoint		ジョイント
		 * @param	pParent		親ジョイント
		 */
		void					updateChild( KsAnim2DJoint* pJoint, const KsAnim2DJoint* pParent );

		/**
		 * 更新処理
		 * @param	pCtrlJoint	コントロールジョイント
		 */
		void					update( const KsAnim2DJoint* pCtrlJoint=NULL );

		/**
		 * 階層を破棄する
		 */
		void					destroy();

	public:
		KsAnim2DJointArray		m_vpRootJoints;	/**< ルートになるジョイントリスト			*/
		KsAnim2DJointArray		m_vpJoints;		/**< ジョイントリスト(すべてのジョイント)	*/
};

#endif

#endif /* __KSANIM2DHIERARCHY_H__ */

