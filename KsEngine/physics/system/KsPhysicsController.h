/************************************************************************************************/
/** 
 * @file		KsPhysicsController.h
 * @brief		�����V�~�����[�V�����V�X�e��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSPHYSICSANIMATIONCONTROLLER_H__
#define __KSPHYSICSANIMATIONCONTROLLER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsPhysicsController
 * @brief		�����V�~�����[�V�����V�X�e��
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
		 * �R���X�g���N�^
		 */
										KsPhysicsController();

		/**
		 * �f�X�g���N�^
		 */
		virtual							~KsPhysicsController();

		/**
		 * �X�V����
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

