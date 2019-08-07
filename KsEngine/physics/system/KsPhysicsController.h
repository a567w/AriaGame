/************************************************************************************************/
/** 
 * @file		KsPhysicsController.h
 * @brief		物理シミュレーションシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSPHYSICSANIMATIONCONTROLLER_H__
#define __KSPHYSICSANIMATIONCONTROLLER_H__

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
 * @class		KsPhysicsController
 * @brief		物理シミュレーションシステム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
class ksENGINE_API KsPhysicsController
{
	public:
		/**
		 * コンストラクタ
		 */
										KsPhysicsController();

		/**
		 * デストラクタ
		 */
		virtual							~KsPhysicsController();

		/**
		 * 更新処理
		 */
		void							update( KsReal gameTime );

		KsUInt32						getParameterCount() const { return m_pParameters.size(); }

		void							addParameter( KsPhysicsParameter* pParameter ) { m_pParameters.push_back( pParameter ); }
		KsPhysicsParameter*				getParameter( KsUInt32 index ) { return m_pParameters[ index ]; }

		void							addRigidBody( KsRigidBody* pRigidBody ) { m_pRigidBodies.push_back( pRigidBody ); }
		KsRigidBody*					getRigidBody( KsUInt32 index ) { return m_pRigidBodies[ index ]; }

		void							addConstraint( KsConstraint* pConstraint ) { m_pConstrains.push_back( pConstraint ); }
		KsConstraint*					getConstraint( KsUInt32 index ) { return m_pConstrains[ index ]; }

	private:
		KsArray<KsPhysicsParameter*>	m_pParameters;
		KsArray<KsRigidBody*>			m_pRigidBodies;
		KsArray<KsConstraint*>			m_pConstrains;
};

#endif		/* __KSPHYSICSANIMATIONCONTROLLER_H__ */

