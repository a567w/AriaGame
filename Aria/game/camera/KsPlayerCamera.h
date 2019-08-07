/************************************************************************************************/
/** 
 * @file		KsPlayerCamera.h
 * @brief		プレイヤーカメラ
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSPLAYERCAMERA_H__
#define __KSPLAYERCAMERA_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsPlayerCamera
 * @brief		フリーカメラ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsPlayerCamera : public KsCamera
{
	public:
		/** 
		 * コンストラクタ
		 * @param	mode		モード
		 */
								KsPlayerCamera( ksSTEREO_MODE mode = ksSTEREO_LEFT_RIGHT_MULTIPASS );

		/**
		 * デストラクタ
		 */
		virtual					~KsPlayerCamera();

		/**
		 * カメラの更新処理
		 */
		virtual void			update();

#if 0
	protected:
		/**
		 * プロジェクションオフセットの更新
		 */
		void					updateProjectionOffset();

		void					updateComputedState();

		void					updateDistortionOffsetAndScale();

		/**
		 * 2D用カメラの更新
		 */
		void					update2D();
		void					updateEyeParams();

		void					setHMDInfo( const OVR::HMDInfo& hmd );
		void					setDistortionFitPointVP( KsReal x, KsReal y );
		void					setDistortionFitPointPixels( KsReal x, KsReal y );
		void					set2DAreaFov( KsReal fovRadians );

	private:
		ksSTEREO_MODE			m_mode;						/**< 表示モード								*/
		KsReal					m_interpupillaryDistance;	/**< 瞳孔間距離								*/
		KsReal					m_aspectMultiplier;			/**< アスペクト乗数							*/
		KsOVRDistortion			m_distortion;				/**< 歪曲設定									*/
		KsReal					m_distortionFitX;			/**< 歪曲率-X値 [-1,1]						*/
		KsReal					m_distortionFitY;			/**< 歪曲率-Y値 [-1,1]						*/
		KsViewport				m_fullView;					/**< ウインドウ全体のビューポート				*/
		KsViewport				m_viewport;					/**< Entire window viewport.				*/
		KsReal					m_area2DFov;				/**< FOV range mapping to [-1, 1] 2D area.	*/
		KsReal					m_yfov;						/**< Vertical FOV.							*/
		KsReal					m_projectionCenterOffset;	/**< プロジェクション中心オフセット				*/
		KsOVRStereoEyeParams	m_eye[ 2 ];					/**< eye									*/
		KsOVRSystem*			m_pOVR;						/**< OVR System								*/
		KsReal					m_fovPixels;				/**< Fov ピクセル								*/
		KsMatrix4x4				m_orthoCenter;				/**< 正射影中心								*/
		KsReal					m_orthoPixelOffset;			/**< 正射影ピクセルオフセット					*/
		OVR::HMDInfo			HMD;						/**< HMD									*/
#endif
};

#if 0
class StereoConfig
{
public:

    StereoConfig(StereoMode mode = Stereo_LeftRight_Multipass,
                 const Viewport& fullViewport = Viewport(0,0, 1280,800));
 

    // *** Modifiable State Access

    // Sets a stereo rendering mode and updates internal cached
    // state (matrices, per-eye view) based on it.
    void        SetStereoMode(StereoMode mode)  { Mode = mode; DirtyFlag = true; }
    StereoMode  GetStereoMode() const           { return Mode; }

    // Sets HMD parameters; also initializes distortion coefficients.
    void        SetHMDInfo(const HMDInfo& hmd);
    const HMDInfo& GetHMDInfo() const           { return HMD; }

    // Query physical eye-to-screen distance in meters, which combines screen-to-lens and
    // and lens-to-eye pupil distances. Modifying this value adjusts FOV.
    float       GetEyeToScreenDistance() const  { return HMD.EyeToScreenDistance; }
    void        SetEyeToScreenDistance(float esd) { HMD.EyeToScreenDistance = esd; DirtyFlag = true; }

    // Interpupillary distance used for stereo, in meters. Default is 0.064m (64 mm).
    void        SetIPD(float ipd)               { InterpupillaryDistance = ipd; DirtyFlag = true; }
    float       GetIPD() const                  { return InterpupillaryDistance; }

    // Set full render target viewport; for HMD this includes both eyes. 
    void        SetFullViewport(const Viewport& vp);
    const Viewport& GetFullViewport() const     { return FullView; }

    // Aspect ratio defaults to ((w/h)*multiplier) computed per eye.
    // Aspect multiplier allows adjusting aspect ratio consistently for Stereo/NoStereo.
    void        SetAspectMultiplier(float m)    { m_aspectMultiplier = m; DirtyFlag = true; }
    float       GetAspectMultiplier() const     { return m_aspectMultiplier; }

    
    // For the distorted image to fill rendered viewport, input texture render target needs to be
    // scaled by DistortionScale before sampling. The scale factor is computed by fitting a point
    // on of specified radius from a distortion center, more easily specified as a coordinate.
    // SetDistortionFitPointVP sets the (x,y) coordinate of the point that scale will be "fit" to,
    // assuming [-1,1] coordinate range for full left-eye viewport. A fit point is a location
    // where source (pre-distortion) and target (post-distortion) image match each other.
    // For the right eye, the interpretation of 'u' will be inverted.  
    void       SetDistortionFitPointVP(float x, float y);
    // SetDistortionFitPointPixels sets the (x,y) coordinate of the point that scale will be "fit" to,
    // specified in pixeld for full left-eye texture.
    void       SetDistortionFitPointPixels(float x, float y);

    // Changes all distortion settings.
    // Note that setting HMDInfo also changes Distortion coefficients.
    void        SetDistortionConfig(const DistortionConfig& d) { Distortion = d; DirtyFlag = true; }
    
    // Modify distortion coefficients; useful for adjustment tweaking.
    void        SetDistortionK(int i, float k)  { Distortion.K[i] = k; DirtyFlag = true; }
    float       GetDistortionK(int i) const     { return Distortion.K[i]; }

    // Sets the fieldOfView that the 2D coordinate area stretches to.
    void        Set2DAreaFov(float fovRadians);


    // *** Computed State

    // Return current aspect ratio.
    float      GetAspect()                      { updateIfDirty(); return Aspect; }
    
    // Return computed vertical FOV in radians/degrees.
    float      GetYFOVRadians()                 { updateIfDirty(); return YFov; }
    float      GetYFOVDegrees()                 { return RadToDegree(GetYFOVRadians()); }

    // Query horizontal projection center offset as a distance away from the
    // one-eye [-1,1] unit viewport.
    // Positive return value should be used for left eye, negative for right eye. 
    float      GetProjectionCenterOffset()      { updateIfDirty(); return ProjectionCenterOffset; }

    // GetDistortionConfig isn't const because XCenterOffset bay need to be recomputed.  
    const DistortionConfig& GetDistortionConfig() { updateIfDirty(); return Distortion; }

    // Returns DistortionScale factor by which input texture size is increased to make
    // post-distortion result distortion fit the viewport.
    float      GetDistortionScale()             { updateIfDirty(); return Distortion.Scale; }

    // Returns the size of a pixel within 2D coordinate system.
    float      Get2DUnitPixel()                 { updateIfDirty();  return (2.0f / (FovPixels * Distortion.Scale)); }

    // Returns full set of Stereo rendering parameters for the specified eye.
    const StereoEyeParams& GetEyeRenderParams(StereoEye eye);
   
private:    

    void updateIfDirty()   { if (DirtyFlag) updateComputedState(); }
    void updateComputedState();

    void updateDistortionOffsetAndScale();
    void updateProjectionOffset();
    void update2D();
    void updateEyeParams();


    // *** Modifiable State

    StereoMode         Mode;
    float              InterpupillaryDistance;
    float              m_aspectMultiplier;               // Multiplied into aspect ratio to change it.
    HMDInfo            HMD;
    DistortionConfig   Distortion;
    float              DistortionFitX, DistortionFitY; // In [-1,1] half-screen viewport units.
    Viewport           FullView;                       // Entire window viewport.

    float              Area2DFov;                      // FOV range mapping to [-1, 1] 2D area.
 
    // *** Computed State
 
    bool               DirtyFlag;   // Set when any if the modifiable state changed.
    float              YFov;        // Vertical FOV.
    float              Aspect;      // Aspect ratio: (w/h)*AspectMultiplier.
    float              ProjectionCenterOffset;
    StereoEyeParams    EyeRenderParams[2];

  
    // ** 2D Rendering

    // Number of 2D pixels in the FOV. This defines [-1,1] coordinate range for 2D.  
    float              FovPixels;
    Matrix4f           OrthoCenter;
    float              OrthoPixelOffset;
};
#endif


#endif		/* __KSPLAYERCAMERA_H__ */

