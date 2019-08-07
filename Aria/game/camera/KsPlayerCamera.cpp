/************************************************************************************************/
/** 
 * @file		KsPlayerCamera.cpp
 * @brief		プレイヤーカメラ
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "Aria/KsGamePreCompile.h"
#include "Aria/game/camera/KsPlayerCamera.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * コンストラクタ
 * @param	mode		モード
 */
/************************************************************************************************/
KsPlayerCamera::KsPlayerCamera( ksSTEREO_MODE mode )
	//: m_mode( mode )
	//, m_interpupillaryDistance( 0.064f )
	//, m_aspectMultiplier( 1.0f )
	//, m_yfov( 0.0f )

{
#if 0
	// And default distortion for it.
	m_distortion.setCoefficients(1.0f, 0.22f, 0.24f);
	m_distortion.Scale = 1.0f; // Will be computed later.

	// Fit left of the image.
	m_distortionFitX = -1.0f;
	m_distortionFitY =  0.0f;

	KsGameSystem*	pGameSystem = KsGameSystem::getInstancePtr();

	// ビューポート設定
	setViewport( 0, 0, 1280, 720, 0.0f, 1.0f );

	// プロジェクション設定( 1-zにするのでこっちをつかう)
	//setPerspective( ksDEG( 45.0f ), pGameSystem->getWindowAspectRatio(), 0.05f, 1500.0f );
	setPerspective( ksDEG( 45.0f ), pGameSystem->getWindowAspectRatio(), 1500.0f, 0.05f );
	
	// ビューマトリックス設定	
	//lookAt( m_position, m_target, KsVector3d::UP );


	/*
      m_fullView(vp), DirtyFlag(true),
      m_yfov(0), m_aspect(vp.w / float(vp.h)), 
	  ProjectionCenterOffset(0);
      OrthoPixelOffset(0);
*/

	//m_fullView(vp);
	//m_yfov(0), m_aspect(vp.w / float(vp.h)), ProjectionCenterOffset(0),
	//OrthoPixelOffset(0)
#endif

}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsPlayerCamera::~KsPlayerCamera()
{
}

/************************************************************************************************/
/*
 * カメラの更新処理
 */
/************************************************************************************************/
void KsPlayerCamera::update()
{
#if 0
	KsVector3d		eye;
	KsVector3d		target;

	KsQuaternion	cameraRot = KsQuaternion::CreateFromYawPitchRoll( m_yaw, m_pitch, 0.0f );
	m_position  = KsVector3d::Transform( &m_direction, &cameraRot );

	// ビューマトリックス設定	
	lookAt( eye, target, KsVector3d::UP );

	m_viewProjMatrix = m_viewMatrix * m_projMatrix;
#endif
	KsCamera::update();
}

#if 0
/************************************************************************************************/
/*
 * プロジェクションオフセットの更新
 */
/************************************************************************************************/
void KsPlayerCamera::updateProjectionOffset()
{
	const KsReal viewCenter         = HMD.HScreenSize * 0.25f;
	const KsReal eyeProjectionShift = viewCenter - HMD.LensSeparationDistance * 0.5f;
	m_projectionCenterOffset        = 4.0f * eyeProjectionShift / HMD.HScreenSize;
}

/************************************************************************************************/
/*
 * 2D用カメラの更新
 */
/************************************************************************************************/
void KsPlayerCamera::update2D()
{
	KsReal metersToPixels          = (HMD.HResolution / HMD.HScreenSize);
	KsReal lensDistanceScreenPixels= metersToPixels * HMD.LensSeparationDistance;
	KsReal eyeDistanceScreenPixels = metersToPixels * m_interpupillaryDistance;
	KsReal offCenterShiftPixels    = (HMD.EyeToScreenDistance / 0.8f) * eyeDistanceScreenPixels;
	KsReal leftPixelCenter         = (HMD.HResolution / 2) - lensDistanceScreenPixels * 0.5f;
	KsReal rightPixelCenter        = lensDistanceScreenPixels * 0.5f;
	KsReal pixelDifference         = leftPixelCenter - rightPixelCenter;
    
	// This computes the number of pixels that fit within specified 2D FOV (assuming
	// distortion scaling will be done).
	KsReal percievedHalfScreenDistance = tan(m_area2DFov * 0.5f) * HMD.EyeToScreenDistance;
	KsReal vfovSize = 2.0f * percievedHalfScreenDistance / m_distortion.Scale;
	m_fovPixels = HMD.VResolution * vfovSize / HMD.VScreenSize;
    
	// Create orthographic matrix.   
	KsMatrix4x4& m      = m_orthoCenter;
	m.m[0][0] =  m_fovPixels / (m_fullView.m_w * 0.5f);
	m.m[1][1] = -m_fovPixels / m_fullView.m_h;
	m.m[0][3] = 0;
	m.m[1][3] = 0;
	m.m[2][2] = 0;

	KsReal orthoPixelOffset = (pixelDifference + offCenterShiftPixels/m_distortion.Scale) * 0.5f;
	m_orthoPixelOffset = orthoPixelOffset * 2.0f / m_fovPixels;
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsPlayerCamera::setHMDInfo( const OVR::HMDInfo& hmd )
{
	HMD = hmd;
	m_distortion.K[0] = hmd.DistortionK[0];
	m_distortion.K[1] = hmd.DistortionK[1];
	m_distortion.K[2] = hmd.DistortionK[2];
	m_distortion.K[3] = hmd.DistortionK[3];

	m_distortion.setChromaticAberration( hmd.ChromaAbCorrection[0], hmd.ChromaAbCorrection[1],
										 hmd.ChromaAbCorrection[2], hmd.ChromaAbCorrection[3] );

	m_updateFlag |= ksVIEWMATRIX_UPDATE;
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsPlayerCamera::setDistortionFitPointVP( KsReal x, KsReal y )
{
	m_distortionFitX = x;
	m_distortionFitY = y;
	m_updateFlag |= ksVIEWMATRIX_UPDATE;
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsPlayerCamera::setDistortionFitPointPixels( KsReal x, KsReal y )
{
	m_distortionFitX = (4 * x / KsReal(m_fullView.m_w)) - 1.0f;
	m_distortionFitY = (2 * y / KsReal(m_fullView.m_h)) - 1.0f;
	m_updateFlag |= ksVIEWMATRIX_UPDATE;
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsPlayerCamera::set2DAreaFov( KsReal fovRadians )
{
	m_area2DFov = fovRadians;
	m_updateFlag |= ksVIEWMATRIX_UPDATE;
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsPlayerCamera::updateComputedState()
{
	// Need to compute all of the following:
	//   - Aspect Ratio
	//   - FOV
	//   - Projection offsets for 3D
	//   - Distortion XCenterOffset
	//   - Update 2D
	//   - Initialize EyeRenderParams

	// Compute aspect ratio. Stereo mode cuts width in half.
	m_aspect = KsReal(m_fullView.m_w) / KsReal(m_fullView.m_h);
	m_aspect *= (m_mode == ksSTEREO_NONE) ? 1.0f : 0.5f;
	m_aspect *= m_aspectMultiplier; 

	updateDistortionOffsetAndScale();

	// Compute Vertical FOV based on distance, distortion, etc.
	// Distance from vertical center to render vertical edge perceived through the lens.
	// This will be larger then normal screen size due to magnification & distortion.
	//
	// This percievedHalfRTDistance equation should hold as long as the render target
	// and display have the same aspect ratios. What we'd like to know is where the edge
	// of the render target will on the perceived screen surface. With NO LENS,
	// the answer would be:
	//
	//  halfRTDistance = (VScreenSize / 2) * aspect *
	//                   DistortionFn_Inverse( DistortionScale / aspect )
	//
	// To model the optical lens we eliminates DistortionFn_Inverse. Aspect ratios
	// cancel out, so we get:
	//
	//  halfRTDistance = (VScreenSize / 2) * DistortionScale
	//
	if( m_mode  == ksSTEREO_NONE )
	{
		m_yfov = ksDEG( 80.0f );
	}
	else
	{
		KsReal percievedHalfRTDistance = (HMD.VScreenSize / 2) * m_distortion.Scale;    
		m_yfov = 2.0f * atan(percievedHalfRTDistance/HMD.EyeToScreenDistance);
	}

	updateProjectionOffset();
	update2D();
	updateEyeParams();

	m_updateFlag &= ~ksVIEWMATRIX_UPDATE;
}

void KsPlayerCamera::updateDistortionOffsetAndScale()
{
	// Distortion center shift is stored separately, since it isn't affected
	// by the eye distance.
	KsReal lensOffset        = HMD.LensSeparationDistance * 0.5f;
	KsReal lensShift         = HMD.HScreenSize * 0.25f - lensOffset;
	KsReal lensViewportShift = 4.0f * lensShift / HMD.HScreenSize;
	m_distortion.XCenterOffset= lensViewportShift;

	// Compute distortion scale from m_distortionFitX & m_distortionFitY.
	// Fit value of 0.0 means "no fit".
	if ((fabs(m_distortionFitX) < 0.0001f) &&  (fabs(m_distortionFitY) < 0.0001f))
	{
		m_distortion.Scale = 1.0f;
	}
	else
	{
		// Convert fit value to distortion-centered coordinates before fit radius
		// calculation.
		KsReal stereoAspect = 0.5f * KsReal(m_fullView.m_w) / KsReal(m_fullView.m_h);
		KsReal dx           = m_distortionFitX - m_distortion.XCenterOffset;
		KsReal dy           = m_distortionFitY / stereoAspect;
		KsReal fitRadius    = sqrt(dx * dx + dy * dy);
		m_distortion.Scale   = m_distortion.distortionFn(fitRadius)/fitRadius;
	}
}





void KsPlayerCamera::updateEyeParams()
{
	// Projection matrix for the center eye, which the left/right matrices are based on.
	KsMatrix4x4 projCenter = KsMatrix4x4::PerspectiveRH( m_yfov, m_aspect, 1500.0f, 0.05f );
	KsReal minZ = 0.0f;
	KsReal maxZ = 1.0f;

	switch( m_mode )
	{
		case ksSTEREO_NONE:
		{
			m_eye[0].set( ksSTEREO_EYE_CENTER, m_fullView, 0, projCenter, m_orthoCenter );
			break;
		}
		case ksSTEREO_LEFT_RIGHT_MULTIPASS:
		{
			KsMatrix4x4 projLeft   = KsMatrix4x4::CreateTranslation( KsVector3d( m_projectionCenterOffset, 0, 0 ) ) * projCenter;
			KsMatrix4x4 projRight  = KsMatrix4x4::CreateTranslation( KsVector3d(-m_projectionCenterOffset, 0, 0 ) ) * projCenter;
			KsMatrix4x4 orthoLeft  = m_orthoCenter * KsMatrix4x4::CreateTranslation( KsVector3d( m_orthoPixelOffset, 0, 0 ) );
			KsMatrix4x4 orthoRight = m_orthoCenter * KsMatrix4x4::CreateTranslation( KsVector3d(-m_orthoPixelOffset, 0, 0 ) );

			KsViewport	vpLeft     = KsViewport( m_fullView.m_x, m_fullView.m_y, m_fullView.m_w/2, m_fullView.m_h, minZ, maxZ );
			KsViewport	vpRight    = KsViewport( m_fullView.m_x + m_fullView.m_w/2, m_fullView.m_y, m_fullView.m_w/2, m_fullView.m_h, minZ, maxZ );

			m_eye[0].set( ksSTEREO_EYE_LEFT,  vpLeft,   m_interpupillaryDistance * 0.5f, projLeft,  orthoLeft,  &m_distortion );
			m_eye[1].set( ksSTEREO_EYE_RIGHT, vpRight, -m_interpupillaryDistance * 0.5f, projRight, orthoRight, &m_distortion );
			break;
		}
		default: break;
	}
}

#if 0
const KsOVRStereoEyeParams& KsPlayerCamera::GetEyeRenderParams( ksSTEREO_EYE_TYPE type )
{
	static const KsUInt32 eyeParamIndices[3] = { 0, 0, 1 };

	//updateIfDirty();

	return m_eye[ eyeParamIndices[ type ] ];
}
#endif


#if 0





//-----------------------------------------------------------------------------------
// **** StereoConfig Implementation

StereoConfig::StereoConfig(StereoMode mode, const Viewport& vp)
    : Mode(mode),
      m_interpupillaryDistance(0.064f), m_aspectMultiplier(1.0f),
      m_fullView(vp), DirtyFlag(true),
      m_yfov(0), m_aspect(vp.w / float(vp.h)), ProjectionCenterOffset(0),
      OrthoPixelOffset(0)
{
    // And default distortion for it.
    m_distortion.SetCoefficients(1.0f, 0.22f, 0.24f);
    m_distortion.Scale = 1.0f; // Will be computed later.

    // Fit left of the image.
    m_distortionFitX = -1.0f;
    m_distortionFitY = 0.0f;

    // Initialize "fake" default HMD values for testing without HMD plugged in.
    // These default values match those returned by the HMD.
    HMD.HResolution            = 1280;
    HMD.VResolution            = 800;
    HMD.HScreenSize            = 0.14976f;
    HMD.VScreenSize            = HMD.HScreenSize / (1280.0f / 800.0f);
    HMD.InterpupillaryDistance = InterpupillaryDistance;
    HMD.LensSeparationDistance = 0.0635f;
    HMD.EyeToScreenDistance    = 0.041f;
    HMD.DistortionK[0]         = Distortion.K[0];
    HMD.DistortionK[1]         = Distortion.K[1];
    HMD.DistortionK[2]         = Distortion.K[2];
    HMD.DistortionK[3]         = 0;

    Set2DAreaFov(DegreeToRad(85.0f));
}






#endif

#endif
