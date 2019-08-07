/************************************************************************************************/
/** 
 * @file		KsOVRDistortion.h
 * @brief		OVR Distortion
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSOVRDISTORTION_H__
#define __KSOVRDISTORTION_H__

/*==============================================================================================*/
/*                                  << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @enum		KsOVRDistortion
 * @brief		ステレオ カメラ タイプ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		
 *  DistortionConfig Provides controls for the distortion shader.
 *  - K[0] - K[3] are coefficients for the distortion function.
 *  - XCenterOffset is the offset of lens distortion center from the 
 *    center of one-eye screen half. [-1, 1] Range.
 *  - Scale is a factor of how much larger will the input image be,
 *    with a factor of 1.0f being no scaling. An inverse of this 
 *    value is applied to sampled UV coordinates (1/Scale).
 *  - ChromaticAberration is an array of parameters for controlling
 *    additional Red and Blue scaling in order to reduce chromatic aberration
 *    caused by the Rift lenses.
 */
/************************************************************************************************/
class KsOVRDistortion
{
	public:
		KsOVRDistortion(KsReal k0 = 1.0f, KsReal k1 = 0.0f, KsReal k2 = 0.0f, KsReal k3 = 0.0f);

		void setCoefficients(KsReal k0, KsReal k1 = 0.0f, KsReal k2 = 0.0f, KsReal k3 = 0.0f);

		void setChromaticAberration(KsReal red1 = 1.0f, KsReal red2 = 0.0f, KsReal blue1 = 1.0f, KsReal blue2 = 0.0f);


		// DistortionFn applies distortion equation to the argument. The returned
		// value should match distortion equation used in shader.
		KsReal  distortionFn(KsReal r) const;

		// DistortionFnInverse computes the inverse of the distortion function on an argument.
		KsReal	distortionFnInverse(KsReal r);

		KsReal			K[4];
		KsReal			XCenterOffset;
		KsReal			YCenterOffset;
		KsReal			Scale;
		// Additional per-channel scaling is applied after distortion:
		// Index [0] - Red channel constant coefficient.
		// Index [1] - Red channel r^2 coefficient.
		// Index [2] - Blue channel constant coefficient.
		// Index [3] - Blue channel r^2 coefficient.
		KsReal			ChromaticAberration[4]; 
};


#endif /* __KSOVRDISTORTION_H__ */

