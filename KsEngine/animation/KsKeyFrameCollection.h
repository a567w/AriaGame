/************************************************************************************************/
/** 
 * @file		KsKeyFrameCollection.h
 * @brief		�L�[�t���[���R���N�V����
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSKEYFRAMECOLLECTION_H__
#define __KSKEYFRAMECOLLECTION_H__

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
 * @class		KsKeyFrameCollection
 * @brief		�L�[�t���[���R���N�V�����N���X
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsKeyFrameCollection
{
	private:
		KsString					m_boneName;
		KsInt32						m_duration;
		KsBool						m_hasTranslation;
		KsBool						m_hasRotation;
		KsBool						m_hasScale;
		KsArray<KsKeyFrame>			m_vKeyFrames;

	public:
		KsKeyFrameCollection();
		KsKeyFrameCollection( const KsString& boneName, KsKeyFrame* pKeyFrames, KsInt32 keyFrameCount,
								KsInt32 duration, KsBool hasTranslation, KsBool hasRotation, KsBool hasScale );



		KsInt32				getIndexByTime( KsReal ticks );

		KsMatrix4x4			getPoseMatrix( KsReal ticks );
	
		KsInt32				getDuration() const { return m_duration; }
		void				setDuration( KsInt32 duration ) { m_duration = duration; }

		const KsString&		getBoneName() { return m_boneName; }
		void				setBoneName( const KsString& boneName ) { m_boneName = boneName; }

		KsBool				getHasTranslation() const { return m_hasTranslation; }
		void				setHasTranslation( KsBool hasTranslation ) { m_hasTranslation = hasTranslation; }

		KsBool				getHasRotation() const { return m_hasRotation; }
		void				setHasRotation( KsBool hasRotation ) { m_hasRotation = hasRotation; }

		KsBool				getHasScale() const { return m_hasScale; }
		void				setHasScale( KsBool hasScale ) { m_hasScale = hasScale; }

        void				addSortedKeyFrame( const KsKeyFrame& keyFrame );

		KsUInt32			getKeyFrameCount() { return m_vKeyFrames.size(); }

		KsKeyFrame*			getKeyFrame( KsInt32 index ) { return &m_vKeyFrames[ index ]; }
};


#endif /* __KSKEYFRAMECOLLECTION_H__ */

