/************************************************************************************************/
/** 
 * @file		KsSpringConstraintBullet.h
 * @brief		物理シミュレーションシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSSPRINGCONSTRAINTBULLET_H__
#define __KSSPRINGCONSTRAINTBULLET_H__

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
 * @class		KsSpringConstraintBullet
 * @brief		物理シミュレーションシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
class ksPHYSICSBULLET_API KsSpringConstraintBullet : public KsSpringConstraint
{
	public:
		/**
		 * コンストラクタ
		 */
											KsSpringConstraintBullet( KsRigidBody& rbA, KsRigidBody& rbB, const KsMatrix4x4& frameInA, const KsMatrix4x4& frameInB, KsBool useLinearReferenceFrameA );

		/**
		 * デストラクタ
		 */
		virtual								~KsSpringConstraintBullet();

		virtual void						enableSpring( KsInt32 index, KsBool enable );
		virtual void						setStiffness( KsInt32 index, KsReal stiffness );
		virtual void						setDamping( KsInt32 index, KsReal damping );
		virtual void						setEquilibriumPoint();
		virtual void						setEquilibriumPoint( KsInt32 index );

		virtual void						setLinearLowerLimit( KsReal x, KsReal y, KsReal z );
		virtual void						setLinearUpperLimit( KsReal x, KsReal y, KsReal z );
		virtual void						setAngularLowerLimit( KsReal x, KsReal y, KsReal z );
		virtual void						setAngularUpperLimit( KsReal x, KsReal y, KsReal z );

		/**
		 * リソースを取得する
		 * @return							 リソース
		 */
		virtual void*						getConstraintResource();

	protected:
		btGeneric6DofSpringConstraint*		m_pSpringConstraint;
};

#endif		/* __KSSPRINGCONSTRAINTBULLET_H__ */

