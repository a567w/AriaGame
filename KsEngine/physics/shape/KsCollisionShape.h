/************************************************************************************************/
/** 
 * @file		KsCollisionShape.h
 * @brief		物理シミュレーションシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSCOLLISIONSHAPE_H__
#define __KSCOLLISIONSHAPE_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsCollisionShape
 * @brief		物理シミュレーションシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
class ksENGINE_API KsCollisionShape
{
	public:
		/**
		 * コンストラクタ
		 */
									KsCollisionShape();

		/**
		 * デストラクタ
		 */
		virtual						~KsCollisionShape();

		/**
		 * 慣性テンソルの計算
		 */
		virtual void				calculateLocalInertia( KsReal mass, KsVector3d& inertia ) = 0;

		/**
		 * コリジョンシェイプのリソースを取得する
		 */
		virtual void*				getCollisionShapeResource() = 0;
};

#endif		/* __KSCOLLISIONSHAPE_H__ */

