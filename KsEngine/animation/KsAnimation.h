/************************************************************************************************/
/** 
 * @file		KsAnimation.h
 * @brief		�A�j���[�V�����N���X
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSANIMATION_H__
#define __KSANIMATION_H__

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
 * @class		KsAnimation
 * @brief		�A�j���[�V����
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsAnimation
{
	private:
		KsReal					m_duration;			/**< �A�j���[�V��������					*/
		KsString				m_animationName;	/**< �A�j���[�V������						*/
		KsAnimationChannel*		m_boneAnimations;	/**< �{�[���A�j���[�V�����`�����l��		*/

	public:
		/**
		 * �R���X�g���N�^
		 */
		KsAnimation();

		/**
		 * �R���X�g���N�^
		 * @param	animationName		�A�j���[�V�����̖��O
		 * @param	pAnimationChannel	�A�j���[�V�����`�����l��
		 */
		KsAnimation( const KsString& animationName, KsAnimationChannel* pAnimationChannel );

		/**
		 * �f�X�g���N�^
		 */
		virtual					~KsAnimation();

		/**
		 * �A�j���[�V�����̌o�ߎ��Ԃ��擾����
		 * @return				�A�j���[�V�����̌o�ߎ���
		 */
		KsReal					getDuration() const { return m_duration; }

		/**
		 * �A�j���[�V�������O���擾����
		 * @return				�A�j���[�V�����̖��O
		 */
		const KsString&			getName() { return m_animationName; }

		/**
		 * �A�j���[�V�����`�����l�����擾����
		 * @return				�A�j���[�V�����`�����l��
		 */
		KsAnimationChannel*		getAnimationChannels() { return m_boneAnimations; }

		/**
		 * �e���{�[���̖��O���擾����
		 * @param	index		�C���f�b�N�X
		 * @return				�e���{�[���̖��O
		 */
		const KsString&			getAffectedBone( KsUInt32 index ) { return m_boneAnimations->getAffectedBone( index );}

		/**
		 * �e���{�[�����邩�ǂ������`�F�b�N����
		 * @param	boneName	�{�[���̖��O
		 * @retval	ksTRUE		�e���{�[���������Ă���
		 * @retval	ksFALSE		�e���{�[���������ĂȂ�
		 */
		KsBool					hasAffectsBone( const KsString& boneName ) { return m_boneAnimations->hasAffectsBone( boneName ); }
};


#endif /* __KSANIMATION_H__ */

