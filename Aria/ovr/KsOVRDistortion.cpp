/************************************************************************************************/
/** 
 * @file		KsOVRDistortion.cpp
 * @brief		OVR Distortion
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "Aria/KsGamePreCompile.h"
#include "Aria/ovr/KsOVRDistortion.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

KsOVRDistortion::KsOVRDistortion( KsReal k0, KsReal k1, KsReal k2, KsReal k3 )
	: XCenterOffset(0), YCenterOffset(0), Scale(1.0f)
{ 
	setCoefficients(k0, k1, k2, k3);
	setChromaticAberration();
}

void KsOVRDistortion::setCoefficients( KsReal k0, KsReal k1, KsReal k2, KsReal k3 )
{
	K[0] = k0;
	K[1] = k1;
	K[2] = k2;
	K[3] = k3; 
}

void KsOVRDistortion::setChromaticAberration( KsReal red1, KsReal red2, KsReal blue1, KsReal blue2 )
{
	ChromaticAberration[0] = red1;
	ChromaticAberration[1] = red2;
	ChromaticAberration[2] = blue1;
	ChromaticAberration[3] = blue2;
}


//-----------------------------------------------------------------------------------
// DistortionFn applies distortion equation to the argument. The returned
// value should match distortion equation used in shader.
KsReal KsOVRDistortion::distortionFn(KsReal r) const
{        
	KsReal rsq   = r * r;
	KsReal scale = r * (K[0] + K[1] * rsq + K[2] * rsq * rsq + K[3] * rsq * rsq * rsq);
	return scale;
}

// DistortionFnInverse computes the inverse of the distortion function on an argument.
KsReal KsOVRDistortion::distortionFnInverse( KsReal r )
{
	OVR_ASSERT((r <= 10.0f));

	KsReal s, d;
	KsReal delta = r * 0.25f;

	s = r * 0.5f;
	d = KsFabs(r - distortionFn(s));

	for (int i = 0; i < 20; i++)
	{
		KsReal sUp   = s + delta;
		KsReal sDown = s - delta;
		KsReal dUp   = fabs(r - distortionFn(sUp));
		KsReal dDown = fabs(r - distortionFn(sDown));

		if (dUp < d)
		{
			s = sUp;
			d = dUp;
		}
		else if (dDown < d)
		{
			s = sDown;
			d = dDown;
		}
		else
		{
			delta *= 0.5f;
		}
	}

	return s;
}
