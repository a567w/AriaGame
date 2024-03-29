/************************************************************************************************/
/** 
 * @file		KsConstraint.h
 * @brief		物理シミュレーションシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSCONSTRAINT_H__
#define __KSCONSTRAINT_H__

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
 * @class		KsConstraint
 * @brief		物理シミュレーションシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
class ksENGINE_API KsConstraint
{
	public:
		/**
		 * コンストラクタ
		 */
									KsConstraint();

		/**
		 * デストラクタ
		 */
		virtual						~KsConstraint();

		/**
		 * リソースを取得する
		 * @return					 リソース
		 */
		virtual void*				getConstraintResource() = 0;
};

#endif		/* __KSCONSTRAINT_H__ */

