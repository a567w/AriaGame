/************************************************************************************************/
/** 
 * @file		KsSpringConstraint.h
 * @brief		�����V�~�����[�V�����V�X�e��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSSPRINGCONSTRAINT_H__
#define __KSSPRINGCONSTRAINT_H__

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
 * @class		KsSpringConstraint
 * @brief		�����V�~�����[�V�����V�X�e��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
class ksENGINE_API KsSpringConstraint : public KsConstraint
{
	public:
		/**
		 * �R���X�g���N�^
		 */
											KsSpringConstraint();

		/**
		 * �f�X�g���N�^
		 */
		virtual								~KsSpringConstraint();

		virtual void						setLinearLowerLimit( KsReal x, KsReal y, KsReal z ) = 0;
		virtual void						setLinearUpperLimit( KsReal x, KsReal y, KsReal z ) = 0;
		virtual void						setAngularLowerLimit( KsReal x, KsReal y, KsReal z ) = 0;
		virtual void						setAngularUpperLimit( KsReal x, KsReal y, KsReal z ) = 0;

		virtual void						enableSpring( KsInt32 index, KsBool enable ) = 0;
		virtual void						setStiffness( KsInt32 index, KsReal stiffness ) = 0;
		virtual void						setDamping( KsInt32 index, KsReal damping ) = 0;
		virtual void						setEquilibriumPoint() = 0;
		virtual void						setEquilibriumPoint( KsInt32 index ) = 0;
};

#endif		/* __KSSPRINGCONSTRAINT_H__ */

