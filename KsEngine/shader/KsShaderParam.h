/************************************************************************************************/
/** 
 * @file		KsShaderParam.h
 * @brief		シェーダーパラメータ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSHADERPARAM_H__
#define __KSSHADERPARAM_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @enum		ksSHADER_PARAM
 * @brief		シェーダーパラメータ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
enum ksSHADER_PARAM
{
	ksSHADER_TIME,
	ksSHADER_WORLD_MATRIX,
	ksSHADER_VIEW_MATRIX,
	ksSHADER_WORLD_VIEW_MATRIX,
	ksSHADER_VIEW_PROJECTION_MATRIX,
	ksSHADER_WORLD_VIEW_PROJECTION_MATRIX,
	ksSHADER_MATERIAL_DIFFUSE,
	ksSHADER_MATERIAL_AMBIENT,
	ksSHADER_MATERIAL_SPECULER,
	ksSHADER_LIGHT_DIFFUSE,
	ksSHADER_LIGHT_AMBIENT,
	ksSHADER_LIGHT_SPECULER,
	ksSHADER_GLOBAL_DATA_MAX,
	ksSHADER_FORCE32          = 0x7fffffff,
};

#endif		/* __KSSHADERPARAM_H__ */






#if 0


class ksENGINE_API KsShaderParam
{
	public:

		enum ksSHADER_PARAM_TYPE
		{
		  ksSHADER_PARAM_TYPE_NULL,
		  ksSHADER_PARAM_TYPE_SYSTEM,
		  PPT_FLOAT4,
		  PPT_VECTOR,
		  PPT_COLOR,
		  PPT_QUAT,
		  PPT_MATRIX
		};

		/**
		* \enum SHADERSYSTEMPARAM
		* \brief List of available system parameters for pipeline shaders
		*/
		enum SHADERSYSTEMPARAM
		{
		  /*! Bit set for all system matrix parameters */
		  SYSTEMMATRIXPARAM                          = 0x00010000,

		  /*! Current model matrix */
		  PSP_MODEL_MATRIX                           = 0x00010001,

		  /*! Current view matrix */
		  PSP_VIEW_MATRIX                            = 0x00010002,

		  /*! Current projection matrix */
		  PSP_PROJECTION_MATRIX                      = 0x00010003,

		  /*! Current concatenated model and view matrix */
		  PSP_MODELVIEW_MATRIX                       = 0x00010004,

		  /*! Current concatenated model, view and projection matrix */
		  PSP_MODELVIEWPROJ_MATRIX                   = 0x00010005,

		  /*! Inverted current model matrix */
		  PSP_INV_MODEL_MATRIX                       = 0x00010006,


		  /*! Bit set for all light parameters */
		  LIGHTPARAM                                 = 0x00020000,

		  /*! Current light position in world space */
		  PSP_LIGHT_POSITION                         = 0x00020001,

		  /*! Current light direction in world space */
		  PSP_LIGHT_DIRECTION                        = 0x00020002,

		  /*! Current light diffuse color */
		  PSP_LIGHT_DIFFUSE_COLOR                    = 0x00020003,

		  /*! Current light ambient color */
		  PSP_LIGHT_AMBIENT_COLOR                    = 0x00020004,

		  /*! Current light specular color */
		  PSP_LIGHT_SPECULAR_COLOR                   = 0x00020005,

		  /*! Current light position in object space */
		  PSP_LIGHT_POSITION_OBJECTSPACE             = 0x00020006,

		  /*! Current light direction in object space */
		  PSP_LIGHT_DIRECTION_OBJECTSPACE            = 0x00020007,

		  /*! Attenuation, values are 1.0f / ( constant | linear | quadratic ) for rgb channels respectively */
		  PSP_LIGHT_ATTENUATION                      = 0x00020008,

		  /*! Reciprocal attenuation, values are 1.0f / ( constant | linear | quadratic ) for rgb channels respectively */
		  PSP_LIGHT_REP_ATTENUATION                  = 0x00020009,


		  /*! Bit set for all mics system parameters */
		  MISCPARAM                                  = 0x00040000,

		  /*! Total ambient light color contributed by all lights, including directional and point lights */
		  PSP_TOTAL_LIGHT_AMBIENT_COLOR              = 0x00040001,

		  /*! Total ambient light color contributed by ambient lights, NOT including directional and point lights */
		  PSP_TOTAL_AMBIENTLIGHT_AMBIENT_COLOR       = 0x00040002,

		  /*! Eye position in object space */
		  PSP_EYE_POSITION_OBJECTSPACE               = 0x00040003
		};

		/*! Parameter index */
		unsigned int                                 m_uiIndex;

		/*! Parameter type */
		SHADERPARAMTYPE                              m_eType;

		/*! Value (depending on type) */
		union ShaderParamValue
		{
		  /*! System parameter (PPT_SYSTEM) */
		  SHADERSYSTEMPARAM                          m_eSystemID;

		  /*! Float (PPT_FLOAT4) */
		  float                                      m_afFloat[4];

		  /*! Vector (PPT_VECTOR), will be padded with 1.0f for w */
		  const Vector3d                            *m_pkVector;

		  /*! Color (PPT_COLOR) */
		  const Color                               *m_pkColor;

		  /*! Quaternion (PPT_QUAT) */
		  const Quaternion                          *m_pkQuaternion;

		  /*! Matrix (PPT_MATRIX) */
		  const Matrix                              *m_pkMatrix;

		}                                            m_Value;

		/*! Light index */
		unsigned int                                 m_uiLight;
};



#endif 

