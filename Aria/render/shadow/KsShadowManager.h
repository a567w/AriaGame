/************************************************************************************************/
/** 
 * @file		KsShadowManager.h
 * @brief		シャドウ管理
 * @author		Tsukasa Kato
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSHADOWMANAGER_H__
#define __KSSHADOWMANAGER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
#define MAX_CASCADES	8	// カスケード、シャドウマップ最大分割数


/************************************************************************************************/
/**
 * @class		KsShadowManager
 * @brief		シャドウ管理
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsShadowManager
{
	public:
		/** 
		 * コンストラクタ(初期化処理)
		 * @param	pRenderSystem		描画システム
		 * @param	width				シャドウ描画ターゲット幅
		 * @param	height				シャドウ描画ターゲット高さ
		 * @param	shadowLevels		シャドウレベル
		 */
										KsShadowManager( KsRenderSystem* pRenderSystem, KsUInt32 width, KsUInt32 height, KsUInt32 shadowLevels );

		/**
		 * デストラクタ
		 */
		virtual							~KsShadowManager();

	protected:
		/**
		 * 初期化処理
		 * @param	pRenderSystem		描画システム
		 * @param	width				シャドウ描画ターゲット幅
		 * @param	height				シャドウ描画ターゲット高さ
		 * @param	shadowLevels		シャドウレベル
		 */
		void							initialize( KsRenderSystem* pRenderSystem, KsUInt32 width, KsUInt32 height, KsUInt32 shadowLevels );

		/**
		 * 
		 */
		void							createAABBPoints( KsVector4d* vAABBPoints, const KsVector4d& vCenter, const KsVector4d& vExtents );

		/**
		 * 
		 */
		void							createFrustumPointsFromCascadeInterval( KsReal fCascadeIntervalBegin, KsReal fCascadeIntervalEnd, KsMatrix4x4& vProjection, KsVector4d* pvCornerPointsWorld );

		/**
		 * フレーム初期化
		 */
		void							initFrame();

		void							renderShadowsForAllCascades();

	protected:
		KsRenderSystem*					m_pRenderSystem;					/**< 描画システム					*/
		KsRenderContext*				m_pRenderContext;					/**< 描画コンテキスト					*/

		KsVector4d						m_vSceneAABBMin;					// AABB判定用バウンディングボックス
		KsVector4d						m_vSceneAABBMax;					// AABB判定用バウンディングボックス
		KsMatrix4x4						m_matShadowView;

		KsRenderTarget*					m_pShadowMapRT;						/**< シャドウマップ レンダーターゲット		*/
		KsInputLayout*					m_pShadowMapIL;						/**< シャドウマップ 頂点レイアウト		*/
		KsVertexShader*					m_pOrthoShadowVS;					/**< シャドウマップ VSシェーダー			*/
		
		KsMatrix4x4						m_matShadowProj[ MAX_CASCADES ];	/**< プロジェクションマトリックス			*/
		KsVertexShader*					m_pShadowMapVS[ MAX_CASCADES ];		/**< シャドウマップ VSシェーダー			*/
		KsPixelShader*					m_pShadowMapPS[ MAX_CASCADES ];		/**< シャドウマップ PSシェーダー			*/
		KsViewport						m_viewport[ MAX_CASCADES ];			/**< シャドウマップ ビューポート			*/

		KsInt32							m_cascadeLevels;					/**< カスケードのレベル					*/
		KsRasterizerState*				m_prsScene;
		KsRasterizerState*				m_prsShadow;
		KsRasterizerState*				m_prsShadowPancake;
		KsSamplerState*					m_pSamLinear;
		KsSamplerState*					m_pSamShadowPCF;
		KsSamplerState*					m_pSamShadowPoint;

		
};


#endif		/* __KSSHADOWMANAGER_H__ */

