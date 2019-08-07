/************************************************************************************************/
/** 
 * @file		KsBonePose.h
 * @brief		�{�[���|�[�Y
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSBONEPOSE_H__
#define __KSBONEPOSE_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
typedef KsArray<KsBonePose*>		KsBonePoseCollection;

/************************************************************************************************/
/**
 * @class		KsBone
 * @brief		�{�[��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsBonePose
{
	public:
		/**
		 * �R���X�g���N�^
		 */
										KsBonePose();

		/**
		 * �f�X�g���N�^
		 */
		virtual							~KsBonePose();

		/**
		 * �{�[�������擾����
		 * @return						�{�[����
		 */
		const KsString&					getName() { return m_name; }

		/**
		 * �{�[��ID���擾����
		 * @return						�{�[��ID
		 */
		KsInt32							getID() const { return m_id; }

		/**
		 * �{�[���̃t���O���擾����
		 * @return						�{�[���̊e��t���O
		 */
		KsUInt32						getFlags()	const { return m_flags; }

		/**
		 * �e�{�[�����擾����
		 * @return						�e�{�[��
		 */
		KsBone*							getParent() { return m_pParent; }

		/**
		 * �q���̃{�[�����擾����
		 * @return						�q���̃{�[��
		 */
		KsBone*							getChild( KsInt32 index ) { return m_pChildren[ index ]; }

	protected:
		KsInt32							m_index;					/**< �C���f�b�N�X�ԍ�				*/
		KsString						m_name;						/**< ���O						*/
		KsBonePose*						m_pParent;					/**< �e��ID						*/
		KsBonePoseCollection			m_vpChildren;				/**< �q�{�[���|�[�Y				*/
		KsReal							m_blendFactor;				/**<							*/
		KsBool							m_doesAnimContainChannel;	/**<							*/
		KsBool							m_doesBlendContainChannel;	/**<							*/
		KsIAnimationController*			m_pCurrentAnimation;		/**<							*/
		KsIAnimationController*			m_pCurrentBlendAnimation;	/**<							*/
		KsInt32							m_id;						/**< �{�[��ID					*/
		KsUInt32						m_flags;					/**< �e��t���O					*/
		KsVector3d						m_initPivot;				/**< �����̊�_					*/
		KsVector3d						m_initTranslate;			/**< �����̈ʒu					*/
		KsQuaternion					m_initRotate;				/**< �����̉�]					*/
		KsVector3d						m_initScale;				/**< �����̃X�P�[��				*/
		KsVector3d						m_pivot;					/**< ��_						*/
		KsVector3d						m_translate;				/**< �ʒu						*/
		KsQuaternion					m_rotate;					/**< ��]						*/
		KsVector3d						m_scale;					/**< �X�P�[��					*/
		KsMatrix4x4						m_defaultMatrix;			/**< �f�t�H���g�}�g���b�N�X		*/
		KsMatrix4x4						m_localMatrix;				/**< ���[�J���}�g���b�N�X			*/
		KsMatrix4x4						m_worldMatrix;				/**< ���[���h�}�g���b�N�X			*/
		KsMatrix4x4						m_stackMatrix;				/**< �}�g���b�N�X�X�^�b�N			*/
		KsVector3d						m_stackScale;				/**< �X�P�[���X�^�b�N				*/
		KsSkeleton*						m_pSkeleton;				/**< �X�P���g���̃|�C���^			*/
		KsBone*							m_pParent;					/**< �e��ID						*/
		KsBoneArray						m_pChildren;				/**< �q����ID���X�g				*/
		void*							m_pUserData;				/**< ���[�U�[�f�[�^				*/
};


#endif		/* __KSBONEPOSE_H__ */



