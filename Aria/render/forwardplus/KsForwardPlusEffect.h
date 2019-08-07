/************************************************************************************************/
/** 
 * @file		KsForwardPlusEffect.h
 * @brief		Foward+Effectファイル
 * @author		Tsukasa Kato
 * @date		2010/12/17
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSDFORWARDPLUSEFFECT_H__
#define __KSDFORWARDPLUSEFFECT_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                          */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


#pragma pack(push,1)

/************************************************************************************************/
/**
 * @struct		KS_CB_PER_OBJECT
 * @brief		KS_CB_PER_OBJECT
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
struct KS_CB_PER_OBJECT
{
	KsMatrix4x4		mWorldViewProjection;
	KsMatrix4x4		mWorldView;
	KsMatrix4x4		mWorld;
	KsVector4d		MaterialAmbientColorUp;
	KsVector4d		MaterialAmbientColorDown;
};

/************************************************************************************************/
/**
 * @struct		KS_CB_PER_FRAME
 * @brief		KS_CB_PER_FRAME
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
struct KS_CB_PER_FRAME
{
    KsMatrix4x4		m_mProjection;
    KsMatrix4x4		m_mProjectionInv;
    KsVector3d		m_vCameraPos;
    KsReal			m_fAlphaTest;
	KsUInt32		m_uNumLights;
    KsUInt32		m_uWindowWidth;
    KsUInt32		m_uWindowHeight;
    KsUInt32		m_uMaxNumLightsPerTile;
};

#pragma pack(pop)


#if 0



        // point lights
        ID3D11Buffer*               m_pPointLightBufferCenterAndRadius;
        ID3D11ShaderResourceView*   m_pPointLightBufferCenterAndRadiusSRV;
        ID3D11Buffer*               m_pPointLightBufferColor;
        ID3D11ShaderResourceView*   m_pPointLightBufferColorSRV;

/************************************************************************************************/
/**
 * @class		KsDeferredEffect
 * @brief		Effect
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsDeferredEffect : public KsEffect
{
	public:
		/**
		 * コンストラクタ
		 */
		KsDeferredEffect();

		/**
		 * デストラクタ
		 */
		virtual				~KsDeferredEffect();

		/**
		 * シェーダーセット
		 */
		virtual	void		setShader( KsRenderContext* pRenderContext, void* pParameter );
};

#endif


#endif /* __KSDFORWARDPLUSEFFECT_H__ */
