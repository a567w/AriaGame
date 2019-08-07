/************************************************************************************************/
/** 
 * @file		KsOVRType.h
 * @brief		OVRタイプ
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSOVRSTEREOEYEPARAMS_H__
#define __KSOVRSTEREOEYEPARAMS_H__

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
 * @class		KsOVRStereoEyeParams
 * @brief		ステレオ Eye
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsOVRStereoEyeParams
{
	public:
		ksSTEREO_EYE_TYPE			m_eyeType;			/**< */
		KsViewport					m_viewport;			/**< */
		KsMatrix4x4					m_viewAdjust;		/**< Translation to be applied to view matrix. */
		KsMatrix4x4					m_projection;		/**< Projection matrix used with this eye. */
		KsMatrix4x4					m_orthoProjection;	/**< Orthographic projection used with this eye. */
		const KsOVRDistortion*		m_pDistortion;		/**< */

	public:
		void set( ksSTEREO_EYE_TYPE eye, const KsViewport& vp, KsReal vofs, const KsMatrix4x4& proj, const KsMatrix4x4& orthoProj, const KsOVRDistortion* distortion = 0 );
};


#endif /* __KSOVRSTEREOEYEPARAMS_H__ */

