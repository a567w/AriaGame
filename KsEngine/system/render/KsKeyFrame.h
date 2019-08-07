/************************************************************************************************/
/** 
 * @file		KsKeyFrame.h
 * @brief		カラー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSKEYFRAME_H__
#define __KSKEYFRAME_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsType.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * 
 * @class	
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsKeyFrame
{
	public:
		/**
		 * コンストラクタ
		 */
										KsKeyFrame() : m_time( 0.0f ) { m_scale.x = 1.0f; m_scale.y = 1.0f; m_scale.z = 1.0f; }

		/**
		 * デストラクタ
		 */
		virtual							~KsKeyFrame(){}

		KsReal							GetTime() const { return m_time; }
		const KsVector3d				GetPos()	{ return m_pos; }
		const KsQuaternion				GetRot()	{ return m_rot; }
		const KsVector3d				GetScale()	{ return m_scale; }

		void							SetTime( KsReal time ) const { m_time = time; }
		void							SetPos( const KsVector3d& pos )	{ m_pos = pos; }
		void							SetRot( const KsQuaternion& rot )	{ m_rot = rot; }
		void							SetScale( const KsVector3d& scale )	{ m_scale = scale; }

	protected:
		KsReal							m_time;		/**< 時間		*/
		KsVector3d						m_pos;		/**< 位置		*/
		KsQuaternion					m_rot;		/**< 回転		*/
		KsVector3d						m_scale;	/**< スケール	*/
};

class KsAnim
{
	private:
		typedef std::vector< KsKeyFrame* >		KsKeyFrameList;

		/**
		 * アニメの補完の種類
		 */
		enum ksANIM_INTERPOLATE_KIND
		{
			ksANIM_INTERPOLATE_LINEAR,		/**< 直線補完		*/
			ksANIM_INTERPOLATE_SPLINE,		/**< スプライン補完	*/
			// エルミート補完
		};

	public:
		/**
		 * コンストラクタ
		 */
										KsAnim();

		/**
		 * デストラクタ
		 */
		virtual							~KsAnim();

		/**
		 * キーフレームを追加する
		 * @param		pFrame			追加するキーフレーム
		 */
		void							AddKeyFrame( const KsKeyFrame* pFrame );

		/**
		 * 更新処理
		 * @param		dt				更新時間
		 * @note		時間は,[ 0.0f･･･1.0f ]で管理する
		 */
		void							Update( KsReal dt );

	protected:
		KsInt32							m_id;				/**< ID									*/
		KsInt32							m_startKeyFrame;	/**< 開始キーフレーム					*/
		KsInt32							m_lastKeyFrame;		/**< 終了キーフレーム					*/
		KsInt32							m_nextKeyFrame;		/**< 次のキーフレーム					*/
		KsReal							m_totalTime;		/**< トータル時間						*/
		KsReal							m_currentTime;		/**< 現在の時間							*/
		KsReal							m_offsetTime;		/**< 0.0fから1.0fの間にするまでの補正値	*/
		KsKeyFrameList					m_vKeyFrames;		/**< キーフレームリスト					*/
};

#if 0
void KsAnim::AddKeyFrame( const KsKeyFrame* pFrame )
{
	m_vKeyFrames->push_back( pFrame );
}

void KsAnim::Update( KsReal dt )
{
	KsInt32		numKeyFrame = m_vKeyFrames.size();

	/* アニメ情報がないか？ */
	if( numKeyFrame <= 1 ){
		return;
	}

	/* 時間更新 */
	m_currentTime += dt * m_offsetTime;

	if( m_currentTime >= 1.0f ){
		m_currentTime = fmod( m_currentTime, 1.0f );
	}

	m_lastKeyFrame   = 0;

	while( ( m_lastKeyFrame < numKeyFrame ) && ( m_vKeyFrames[ m_lastKeyFrame ]->m_fT <= m_currentTime ) )
	{
		++m_lastKeyFrame;
	}

	if( --m_lastKeyFrame < 0 ){
		m_lastKeyFrame = numKeyFrame - 1;
	}

	m_nextKeyFrame = ( m_lastKeyFrame + 1 ) % numKeyFrame;

	//float fInterval = m_vKeyFrames[ m_nextKeyframe ]->m_fT - m_vKeyFrames[ m_lastKeyFrame ]->m_fT;

	//if( fInterval < 0.0f )
	//	fInterval += 1.0f;

	//float fOffset   = m_fCurTime - m_vKeyFrames[ m_iLastKeyframe ]->m_fT;

	//if( fOffset < 0.0f )
	//	fOffset += 1.0f;

	//m_fOffset = fOffset / fInterval;
}
    KeyFrame AnimationTrack::getInterpolatedKeyFrame(Real timeIndex) const
    {
        // Return value
        KeyFrame kret(timeIndex);
        
        // Keyframe pointers
        KeyFrame *k1, *k2;
        unsigned short firstKeyIndex;

        Real t = this->getKeyFramesAtTime(timeIndex, &k1, &k2, &firstKeyIndex);

        if (t == 0.0)
        {
            // Just use k1
            kret.setRotation(k1->getRotation());
            kret.setTranslate(k1->getTranslate());
            kret.setScale(k1->getScale());
        }
        else
        {
            // Interpolate by t
            Animation::InterpolationMode im = mParent->getInterpolationMode();
            Vector3 base;
            switch(im)
            {
            case Animation::IM_LINEAR:
                // Interpolate linearly
                // Rotation
                // Interpolate to nearest rotation
                kret.setRotation( Quaternion::Slerp(t, k1->getRotation(), k2->getRotation(), true) );

                // Translation
                base = k1->getTranslate();
                kret.setTranslate( base + ((k2->getTranslate() - base) * t) );

                // Scale
                base = k1->getScale();
                kret.setScale( base + ((k2->getScale() - base) * t) );
                break;

            case Animation::IM_SPLINE:
                // Spline interpolation

                // Build splines if required
                if (mSplineBuildNeeded)
                {
                    buildInterpolationSplines();
                }

                // Rotation
                kret.setRotation( mRotationSpline.interpolate(firstKeyIndex, t) );

                // Translation
                kret.setTranslate( mPositionSpline.interpolate(firstKeyIndex, t) );

                // Scale
                kret.setScale( mScaleSpline.interpolate(firstKeyIndex, t) );

                break;
            }

        }
        
        return kret;
        
    }
    //---------------------------------------------------------------------
    void AnimationTrack::apply(Real timePos, Real weight, bool accumulate)
    {
        applyToNode(mTargetNode, timePos, weight, accumulate);
        
    }
    //---------------------------------------------------------------------
    Node* AnimationTrack::getAssociatedNode(void) const
    {
        return mTargetNode;
    }
    //---------------------------------------------------------------------
    void AnimationTrack::setAssociatedNode(Node* node)
    {
        mTargetNode = node;
    }
    //---------------------------------------------------------------------
    void AnimationTrack::applyToNode(Node* node, Real timePos, Real weight, bool accumulate)
    {
        KeyFrame kf = this->getInterpolatedKeyFrame(timePos);
		if (accumulate) 
        {
            // add to existing. Weights are not relative, but treated as absolute multipliers for the animation
            Vector3 translate = kf.getTranslate() * weight;
			node->translate(translate);

			// interpolate between no-rotation and full rotation, to point 'weight', so 0 = no rotate, 1 = full
			Quaternion rotate = Quaternion::Slerp(weight, Quaternion::IDENTITY, kf.getRotation());
			node->rotate(rotate);

			Vector3 scale = kf.getScale();
			// Not sure how to modify scale for cumulative anims... leave it alone
			//scale = ((Vector3::UNIT_SCALE - kf.getScale()) * weight) + Vector3::UNIT_SCALE;
			node->scale(scale);
		} 
        else 
        {
			// apply using weighted transform method
			node->_weightedTransform(weight, kf.getTranslate(), kf.getRotation(),
				kf.getScale());
		}
    }
    //---------------------------------------------------------------------
    void AnimationTrack::buildInterpolationSplines(void) const
    {
        // Don't calc automatically, do it on request at the end
        mPositionSpline.setAutoCalculate(false);
        mRotationSpline.setAutoCalculate(false);
        mScaleSpline.setAutoCalculate(false);

        mPositionSpline.clear();
        mRotationSpline.clear();
        mScaleSpline.clear();

        KeyFrameList::const_iterator i, iend;
        iend = mKeyFrames.end(); // precall to avoid overhead
        for (i = mKeyFrames.begin(); i != iend; ++i)
        {
            mPositionSpline.addPoint((*i)->getTranslate());
            mRotationSpline.addPoint((*i)->getRotation());
            mScaleSpline.addPoint((*i)->getScale());
        }

        mPositionSpline.recalcTangents();
        mRotationSpline.recalcTangents();
        mScaleSpline.recalcTangents();


        mSplineBuildNeeded = false;
    }
#endif


#endif		/* __KSKEYFRAME_H__ */
