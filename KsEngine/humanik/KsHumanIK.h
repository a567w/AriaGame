/************************************************************************************************/
/** 
 * @file		KsHumanIK.h
 * @brief		�l�ԗpIK
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#ifndef __KSHUMANIK_H__
#define __KSHUMANIK_H__

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsIKPoint
 * @brief		
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsIKPoint
{
	public:
								KsIKPoint( KsBone* pBone );

		KsBone*					getBone() { return m_pBone; }
		KsBool					IsIKLimitAngle() const { return m_bIKLimitAngle; }
		KsInt32					getIKLimitAngleType() const { return m_IKLimitAngleType; };

	public:
		KsBone*					m_pBone;
		KsBool					m_bIKLimitAngle;
		KsInt32					m_IKLimitAngleType;
};

/************************************************************************************************/
/**
 * @class		KsIKEffector
 * @brief		
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsIKEffector
{
	public:
		KsInt32					m_iterations;		// �ċA���Z��( IK�l1 )
		KsReal					m_controlWeight;	// IK�̉e���x( IK�l2 )
		KsIKPoint*				m_pTarget;
		KsIKPoint*				m_pEffector;
		KsArray<KsIKPoint*>		m_vpChain;	

	public:
		KsIKPoint*				getTargetPoint() { return m_pTarget; }
		KsIKPoint*				getEffectorPoint() { return m_pEffector; }
		KsIKPoint*				getChainPoint( KsUInt32 index ) { return m_vpChain[ index ]; }
		KsUInt32				getChainPointCount() const { return m_vpChain.size(); }
		KsInt32					getIterations() const { return m_iterations; }
		KsReal					getControlWeight() const { return m_controlWeight; }
};

/************************************************************************************************/
/**
 * @class		KsIKEffector
 * @brief		
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsIKParameter
{
	public:
		KsString				BoneName;			// IK�{�[���ԍ�
		KsString				TargetBoneName;		// IK�^�[�Q�b�g�{�[���ԍ�( IK�{�[�����ŏ��ɐڑ�����{�[�� )
		KsInt32					BoneIndex;			// IK�{�[���ԍ�
		KsInt32					TargetBoneIndex;	// IK�^�[�Q�b�g�{�[���ԍ�( IK�{�[�����ŏ��ɐڑ�����{�[�� )
		KsInt32					ChainLength;		// IK�`�F�[���̒���(�q�̐�)
		KsInt32					Iterations;			// �ċA���Z��( IK�l1 )
		KsReal					ControlWeight;		// IK�̉e���x( IK�l2 )
		KsArray<KsInt32>		ChildBoneIndices;	// IK�e�����̃{�[���ԍ�(ChainLength)
		KsArray<KsString>		ChildBoneNames;		// IK�e�����̃{�[���ԍ�(ChainLength)
};

/************************************************************************************************/
/**
 * @class		KsHumanIK
 * @brief		
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsHumanIK
{
	public:
						KsHumanIK( KsModel* pModel );
		virtual			~KsHumanIK();
		virtual void	update();
		
		void	updateIK();
		void	limitAngle( KsQuaternion& quat, KsIKPoint* pIKPoint );
	public:
		KsModel*					m_pModel;
		KsArray<KsIKParameter*>		m_vpParameters;
		KsArray<KsIKEffector*>		m_vpEffectors;
};

/************************************************************************************************/
/**
 * @class		KsIKConstraint
 * @brief		IK�R���X�g���C���g
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsIKConstraint
{
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsIKConstraint();

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsIKConstraint();

	public:

};

/************************************************************************************************/
/**
 * @class		KsIKPositionConstraint
 * @brief		�|�W�V�����R���X�g���C���g
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsIKPositionConstraint : public KsConstraint
{
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsIKPositionConstraint();

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsIKPositionConstraint();

	public:

};

/************************************************************************************************/
/**
 * @class		KsPositionConstraint
 * @brief		�f�B���N�V�����R���X�g���C���g
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsIKDirectionConstraint : public KsConstraint
{
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsIKDirectionConstraint();

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsIKDirectionConstraint();

	public:

};

/************************************************************************************************/
/**
 * @class		KsIKJoint
 * @brief		IK�p�W���C���g
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsIKJoint
{
	private:
		KsVector3d				m_position;		/**< �W���C���g�ʒu���W		*/

	public:
		/**
		 * �R���X�g���N�^
		 */
		KsIKJoint();

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsIKJoint();

		/**
		 * IK����p�p�����[�^���擾����
		 * @param	index			�C���f�b�N�X
		 * @return					IK����p�p�����[�^
		 */
		KsIKParameter*				getIKParameter( KsInt32 index );

	public:
		KsIKParameter*				m_pParameter;		/**< IK�p�����[�^			*/
		KsIKEffector*				m_pEffector;		/**< IK�G�t�F�N�^�[		*/
};

/************************************************************************************************/
/**
 * @class		KsHumanIK
 * @brief		�l�ԗpIK�V�X�e��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsHumanIK2
{
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsHumanIK2();

		/**
		 * �R���X�g���N�^
		 */
									KsHumanIK2( KsModel* pModel );

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsHumanIK2();

		/**
		 * �X�V����
		 * @param	gameTime		�Q�[���X�V����
		 */
		virtual void				update( KsReal gameTime );


		
	public:
		KsModel*					m_pModel;			/**< �^�[�Q�b�g���f��		*/
		KsArray<KsIKJoint*>			m_vpParameters;		/**< IK*/
		KsArray<KsIKEffector*>		m_vpEffectors;
		KsArray<KsIKPositionConstraint*>		m_vpPositionConstraints;
		KsArray<KsIKDirectionConstraint*>		m_vpKsIKDirectionConstraint;
};


#endif		/* __KSHUMANIK_H__ */

