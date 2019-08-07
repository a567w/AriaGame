/************************************************************************************************/
/** 
 * @file		KsActor.h
 * @brief		�A�N�^�[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSACTOR_H__
#define __KSACTOR_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsActor
 * @brief		�A�N�^�[�N���X
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsActor
{
	protected:
		KsModel*					m_pModel;			/**< ���f���f�[�^			*/
		KsSkeleton*					m_pSkeleton;		/**< �X�P���g���f�[�^		*/
		KsAnimationController*		m_pCurrentAnim;		/**< ���݂̃A�j���f�[�^	*/
		KsHumanIK*					m_pHumanIK;			/**< IK����f�[�^			*/
		KsPhysicsController*		m_pPhysics;			/**< �������Z�f�[�^		*/

	public:
		/**
		 * �R���X�g���N�^
		 */
		KsActor();

		/**
		 * �R���X�g���N�^
		 */
		KsActor( KsModel* pModel );

		/**
		 * �f�X�g���N�^
		 */
		virtual ~KsActor();

		/**
		 * �X�V����
		 * @param	gameTime			�X�V����
		 */
		virtual void update( KsReal gameTime );

		/**
		 * �`�揈��
		 * @param	pRenderContext		�`��R���e�L�X�g
		 */
		virtual void draw( KsRenderContext* pRenderContext );

		/**
		 * �A�j���[�V�������Z�b�g����
		 * @param	pCurrentAnim		�A�j���[�V����
		 */
		void setAnimation( KsAnimationController* pCurrentAnim );

		/**
		 * �A�j���[�V�������Z�b�g����
		 * @return		���݂̃A�j���[�V����
		 */
		KsAnimationController* getAnimation() { return m_pCurrentAnim; }

		/**
		 * ���f���f�[�^���擾����
		 * @return		���f���f�[�^
		 */
		KsModel*		getModel() { return m_pModel; }

		/**
		 * IK���Z�b�g����
		 * @param	pHumanIK			IK
		 */
		void setHumanIK( KsHumanIK* pHumanIK );

		/**
		 * �������Z�f�[�^���Z�b�g����
		 * @param	pPhysics			�������Z�f�[�^
		 */
		void setPhysics( KsPhysicsController* pPhysics );
};


#endif /* __KSACTOR_H__ */
