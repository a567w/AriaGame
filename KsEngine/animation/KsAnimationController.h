/************************************************************************************************/
/** 
 * @file		KsAnimationController.h
 * @brief		�{�[���֌W
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSANIMATIONCONTROLLER_H__
#define __KSANIMATIONCONTROLLER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsAnimation;

/************************************************************************************************/
/**
 * @class		KsAnimationController
 * @brief		���f���{�[���N���X
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsAnimationController : public KsIAnimationController
{
		friend class KsModel;
	public:
		/**
		 * �R���X�g���N�^
		 */
								KsAnimationController( KsAnimation* pAnimation );

		/**
		 * �f�X�g���N�^
		 */
		virtual					~KsAnimationController();


		virtual void			update( KsReal gameTime );

		virtual KsMatrix4x4		getCurrentBoneTransform( const KsBone* pBone );
	
		
		virtual KsBool			containsAnimationTrack( const KsBone* pBone );

		KsReal					getDuration() const { return m_pAnimation->getDuration(); }

		void					setSpeedFactor( KsReal speedFactor ) { m_speedFactor = speedFactor; }
		KsReal					getSpeedFactor() const { return m_speedFactor; }
	private:
		KsAnimation*			m_pAnimation;
		KsReal					m_speedFactor;
		KsReal					m_elapsedTime;
		KsReal					m_elapsed;
		KsBool					m_isLooping;
};


#endif		/* __KSANIMATIONCONTROLLER_H__ */



