/************************************************************************************************/
/** 
 * @file		KsKinematicMotionState.h
 * @brief		�����V�~�����[�V�����V�X�e��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSDKINEMMATICMOTIONSTATE_H__
#define __KSDKINEMMATICMOTIONSTATE_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

// Kinematic�p���[�V�����X�e�[�g
struct btKinematicMotionState : public btMotionState
{
	KsBone*			m_pBone;
	btTransform		m_startWorldTrans;
	btTransform		m_boneOffset;
	btTransform		m_graphicsWorldTrans;
			

	btKinematicMotionState( const KsMatrix4x4& startTrans, const KsMatrix4x4& boneOffset, KsBone* pBone )
			: m_pBone( pBone )
	{
		m_startWorldTrans.setFromOpenGLMatrix( startTrans.data );
		m_boneOffset.setFromOpenGLMatrix( boneOffset.data );
		m_graphicsWorldTrans.setIdentity();
	}

	///synchronizes world transform from user to physics
	virtual void getWorldTransform( btTransform& centerOfMassWorldTrans ) const
	{
		btTransform		bttrBoneTransform;

		bttrBoneTransform.setFromOpenGLMatrix( (KsReal *)m_pBone->getWorldTransform() );

		centerOfMassWorldTrans = bttrBoneTransform * m_boneOffset;
	}

	///synchronizes world transform from physics to user
	///Bullet only calls the update of worldtransform for active objects
	virtual void setWorldTransform( const btTransform& centerOfMassWorldTrans )
	{
		m_graphicsWorldTrans = centerOfMassWorldTrans;
	}
};


/************************************************************************************************/
/**
 * @class		KsKinematicMotionState
 * @brief		�����V�~�����[�V�����V�X�e��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
class ksPHYSICSBULLET_API KsKinematicMotionState : public KsMotionState
{
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsKinematicMotionState( const KsMatrix4x4& refTransform, const KsMatrix4x4& refOffset, KsBone* pBone );

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsKinematicMotionState();

		/**
		 * ���\�[�X���擾����
		 * @return					 ���\�[�X
		 */
		virtual void*				getMotionStateResource();

	private:
		btKinematicMotionState*		m_pMotionState;
};

#endif		/* __KSDKINEMMATICMOTIONSTATE_H__ */

