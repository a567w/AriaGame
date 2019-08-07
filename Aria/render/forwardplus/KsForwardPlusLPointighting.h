/************************************************************************************************/
/** 
 * @file		KsForwardPlusLPointighting.h
 * @brief		Foward+ライティング
 * @author		Tsukasa Kato
 * @date		2006/07/02
 * @since		2006/07/02
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSDFORWARDPLUSLIGHTING_H__
#define __KSDFORWARDPLUSLIGHTING_H__

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

#define MAX_LIGHTS_POWER				10
#define MAX_LIGHTS						( 1 << MAX_LIGHTS_POWER )
#define COMPUTE_SHADER_TILE_GROUP_DIM	16
#define COMPUTE_SHADER_TILE_GROUP_SIZE	(COMPUTE_SHADER_TILE_GROUP_DIM*COMPUTE_SHADER_TILE_GROUP_DIM)

/************************************************************************************************/
/**
 * @struct		KsPointLight
 * @brief		Must match shader equivalent structure
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
struct KsPointLight
{
	KsVector3d	positionView;
	KsReal		attenuationBegin;
	KsVector3d	color;
	KsReal		attenuationEnd;
};

/************************************************************************************************/
/**
 * @struct		KsFramebufferElement
 * @brief		Flat framebuffer RGBA16-encoded
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
struct KsFrameBufferElement
{
	KsUInt32	rb;
	KsUInt32	ga;
};

/************************************************************************************************/
/**
 * @struct		KsPointLightTransform
 * @brief		Host-side world-space initial transform data
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
struct KsPointLightTransform
{
	// Cylindrical coordinates
	KsReal		radius;
	KsReal		angle;
	KsReal		height;
	KsReal		animationSpeed;
};

/************************************************************************************************/
/**
 * @class		KsForwardPlusLPointighting
 * @brief		KsForwardPlusLPointightingクラス
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
class KsForwardPlusLPointighting
{
	public:
		/**
		 * コンストラクタ
		 * @param	pRenderSystem	描画システム
		 * @param	width			レンダーターゲットの幅
		 * @param	height			レンダーターゲットの高さ
		 */
		KsForwardPlusLPointighting( KsRenderSystem* pRenderSystem, KsUInt32 width, KsUInt32 height, KsUInt32 MSAA );

		/**
		 * デストラクタ
		 */
		virtual					~KsForwardPlusLPointighting();

		/**
		 * ライティングを初期化する
		 */
		void					initializeLight();

		/**
		 * シェーダーパラメータを更新する
		 */
		KsConstantBuffer*		getLightingBuffer() { return m_pLightingCB; }

		/**
		 * シェーダーパラメータを更新する
		 */
		KsUnorderedAccessView*	getLightingUAV() { return m_pLightBufferUAV; }
		
		/**
		 * ライトを更新する( ライト情報をテクスチャに書き込む )
		 * @param	elapsedTime	経過時間
		 */
		void					updateLight( KsReal elapsedTime, KsCamera* pCamera, KsModelParameter* pModelParameter );

		/**
		 * ライティング計算
		 */
		void					computeLighting( KsUInt32 numTexture, KsTexture** pTextures );

	protected:
		KsRenderSystem*			m_pRenderSystem;						/**< 描画システム					*/
		KsRenderContext*		m_pRenderContext;						/**< 描画コンテキスト					*/
		KsPointLight			m_vPointLight[ MAX_LIGHTS ];			/**< ポイントライト					*/
		KsPointLightTransform	m_vPointLightTrans[ MAX_LIGHTS ];		/**< ポイントライト					*/
		KsVector3d				m_vPointLightPos[ MAX_LIGHTS ];			/**< ポイントライト					*/
		KsComputeShader*		m_pLightingCS;							/**< ライト用コンピュートシェーダー	*/
		KsConstantBuffer*		m_pLightingCB;							/**< ライト用バッファ					*/
		KsUnorderedAccessView*	m_pLightBufferUAV;						/**< ライト用UAV						*/
		KsStructuredBuffer*		m_pLightParameter;						/**< ライトパラメータ					*/

		KsUInt32				m_dispatchWidth;						/**< Compute Shader Dispatch Widht	*/
		KsUInt32				m_dispatchHeight;						/**< Compute Shader Dispatch Height	*/
		KsReal					m_totalTime;							/**< */


        // point lights
        ID3D11Buffer*               m_pPointLightBufferCenterAndRadius;
        ID3D11ShaderResourceView*   m_pPointLightBufferCenterAndRadiusSRV;
        ID3D11Buffer*               m_pPointLightBufferColor;
        ID3D11ShaderResourceView*   m_pPointLightBufferColorSRV;

        // spot lights
        ID3D11Buffer*               m_pSpotLightBufferCenterAndRadius;
        ID3D11ShaderResourceView*   m_pSpotLightBufferCenterAndRadiusSRV;
        ID3D11Buffer*               m_pSpotLightBufferColor;
        ID3D11ShaderResourceView*   m_pSpotLightBufferColorSRV;
        ID3D11Buffer*               m_pSpotLightBufferSpotParams;
        ID3D11ShaderResourceView*   m_pSpotLightBufferSpotParamsSRV;

        // buffers for light culling
        ID3D11Buffer*               m_pLightIndexBuffer;
        ID3D11ShaderResourceView*   m_pLightIndexBufferSRV;
        ID3D11UnorderedAccessView*  m_pLightIndexBufferUAV;

};

#endif


#endif /* __KSDFORWARDPLUSLIGHTING_H__ */

