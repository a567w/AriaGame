/************************************************************************************************/
/** 
 * @file		KsInterpolationController.h
 * @brief		モーション補間関係
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSINTERPOLATIONCONTROLLER_H__
#define __KSINTERPOLATIONCONTROLLER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


#if 0

enum ksInterpolationType
{
	/// <summary>
	/// No interpolation.
	/// </summary>
	ksInterpolation_None,
	/// <summary>
	/// Linear interpolation.
	/// </summary>
	ksInterpolation_Linear,
	/// <summary>
	/// Spline based interpolation.  Higher quality than linear but more expensive.
	/// </summary>
	ksInterpolation_SplineBased
};


/************************************************************************************************/
/**
 * @class		KsInterpolationController
 * @brief		モーション補間クラス
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsInterpolationController : public KsAnimationController
{
    private static Matrix curTransform, nextTransform, transform;
    
	private:
		ksInterpolationType		m_interpolationType;

	public:
	   KsInterpolationController( KsAnimation source, ksInterpolationType interpolationType )
			: base( source)
		{
			this.m_interpolationType = interpolationType;
		}

    /// <summary>
    /// Returns the current transform for a bone.
    /// </summary>
    /// <param name="pose">The bone.</param>
    /// <returns>The bone's current transform.</returns>
    virtual KsMatrix4x4 GetCurrentBoneTransform(KsBonePose pose)
    {
        KsKeyFrameCollection channel = base.AnimationSource.AnimationChannels[pose.Name];

        KsInt32 curIndex = channel.GetIndexByTime(base.ElapsedTime);

        if (m_interpolationType == ksInterpolationType.None)
        {
            return channel[curIndex].Transform;
        }

        KsInt32 nextIndex = curIndex + 1;

        if (nextIndex >= channel.Count)
        {
            return channel[curIndex].Transform;
        }
            
		// Numerator of the interpolation factor
        KsReal interpNumerator = (KsReal)(ElapsedTime - channel[curIndex].Time);
            
		// Denominator of the interpolation factor
        KsReal interpDenom = (KsReal)(channel[nextIndex].Time - channel[curIndex].Time);

        // The interpolation factor, or amount to interpolate between the current
        // and next frame
        KsReal interpAmount = interpNumerator / interpDenom;

        curTransform = channel[curIndex].Transform;
        nextTransform = channel[nextIndex].Transform;
        if (m_interpolationType == ksInterpolationType.Linear)
        {
            Matrix.Lerp(ref curTransform, ref nextTransform, interpAmount, out transform );
        }
        else
        {
            KsAnimationUtil.SlerpMatrix(ref curTransform, ref nextTransform, interpAmount, out transform );
        }
        return transform;
    }


    public 
		ksInterpolationType			getInterpolationType() const { return m_interpolationType; }

		void						setInterpolationType( ksInterpolationType interpolationType ) { m_interpolationType = interpolationType; }
}

#endif

#endif /* __KSINTERPOLATIONCONTROLLER_H__ */
