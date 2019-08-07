/************************************************************************************************/
/** 
 * @file		KsBone.h
 * @brief		�{�[���֌W
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSBONE_H__
#define __KSBONE_H__

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
 * @class		KsBone
 * @brief		���f���{�[���N���X
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsBone
{
		friend class KsModel;
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsBone();

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsBone();

		/**
		 * �{�[�������擾����
		 * @return					�{�[����
		 */
		const KsString&				getName() const { return m_name; }


		/**
		 * �{�[���C���f�b�N�X���擾����
		 * @return					�{�[���C���f�b�N�X
		 */
		KsInt32						getIndex() const { return m_index; }

		/**
		 * �e�{�[���C���f�b�N�X���擾����
		 * @return					�e�{�[���C���f�b�N�X
		 */
		KsInt32						getParentIndex() const { return m_parent; }

		/**
		 * �e�{�[�����擾����
		 * @return					�e�{�[��
		 */
		KsBone*						getParent() { return m_pParent; }


		/**
		 * �q���̃{�[���̐����擾����
		 * @return					�q���̐�
		 */
		KsUInt32					getNumChild() const { return m_vpChildren.size(); }

		/**
		 * �q���̃{�[�����擾����
		 * @return					�q���̃{�[��
		 */
		KsBone*						getChild( KsInt32 index ) { return m_vpChildren[ index ]; }

		/**
		 *
		 */
		KsMatrix4x4&				getDefaultTransform() { return m_defaultTransform; }

		/**
		 *
		 */
		KsMatrix4x4&				getBoneTransform() { return m_boneTransform; }

		/**
		 *
		 */
		KsMatrix4x4&				getAnimationTransform() { return m_animationTransform; }

		/**
		 *
		 */
		KsMatrix4x4&				getInverseTransform() { return m_inverseTransform; }

		/**
		 *
		 */
		KsMatrix4x4&				getWorldTransform() { return m_worldTransform; }

		/**
		 *
		 */
		KsMatrix4x4&				getSkinTransform() { return m_skinTransform; }

		/**
		 * �{�[����`�悷��
		 */
		void						draw();

	public:
		KsInt32						m_index;				/// Bones �R���N�V�������́A���̃{�[���̃C���f�b�N�X���擾���܂��B
		KsString					m_name;					/// ���̃{�[���̖��O���擾���܂��B
		KsInt32						m_parent;				/// �e�{�[���̃C���f�b�N�X
		KsBone*						m_pParent;				/// ���̃{�[���̐e���擾���܂��B
		KsArray<KsBone*>			m_vpChildren;			/// ���̃{�[���̎q�ł���{�[���̃R���N�V�������擾���܂��B
		KsMatrix4x4					m_defaultTransform;		/// �e�{�[������Ƃ��Ă��̃{�[�����g�����X�t�H�[�����邽�߂Ɏg�p�����s����擾�܂��͐ݒ肵�܂��B
		KsMatrix4x4					m_animationTransform;	/// �e�{�[������Ƃ��Ă��̃{�[�����g�����X�t�H�[�����邽�߂Ɏg�p�����s����擾�܂��͐ݒ肵�܂��B
		KsMatrix4x4					m_inverseTransform;
		KsMatrix4x4					m_boneTransform;
		KsMatrix4x4					m_worldTransform;
		KsMatrix4x4					m_skinTransform;
};


#endif		/* __KSBONE_H__ */



