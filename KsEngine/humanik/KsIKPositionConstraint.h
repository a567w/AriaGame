/************************************************************************************************/
/** 
 * @file		KsIKPositionConstraint.h
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
#ifndef __KSIKPOSITIONCONSTRAINT_H__
#define __KSIKPOSITIONCONSTRAINT_H__

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


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
	private:
		KsInt32					m_boneIndex;		/**< �{�[���C���f�b�N�X	*/
		KsVector3d				m_start;			/**< �J�n���W				*/
		KsVector3d				m_end;				/**< �I�����W				*/
		KsVector3d				m_current;			/**< ��ԍ��W				*/

	public:
		/**
		 * �R���X�g���N�^
		 */
								KsIKPositionConstraint();

		/**
		 * �f�X�g���N�^
		 */
		virtual					~KsIKPositionConstraint();

		/**
		 * �X�V����
		 * @param	gameTime	�Q�[���X�V����
		 */
		virtual void			update( KsReal gameTime );

		/**
		 * ��ԍ��W���Z�o����
		 * @param	rate		��ԃ��[�g
		 */
		void					interpolate( KsReal rate );

		/**
		 * �{�[���C���f�b�N�X���擾����
		 * @return				�{�[���C���f�b�N�X
		 */
		KsInt32					getBoneIndex() const { return m_boneIndex; }

		/**
		 * �{�[���C���f�b�N�X���擾����
		 * @param				�{�[���C���f�b�N�X
		 */
		void					setBoneIndex( KsInt32 boneIndex ) { m_boneIndex = boneIndex; }

};


#endif		/* __KSIKPOSITIONCONSTRAINT_H__ */

