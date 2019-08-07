/************************************************************************************************/
/** 
 * @file		KsShadowManager.cpp
 * @brief		シャドウ管理
 * @author		Tsukasa Kato
 * @date		2011/10/17
 * @since		2011/10/17
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "Aria/KsGamePreCompile.h"
#include "Aria/render/shadow/KsShadowManager.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * コンストラクタ
 * @param	pRenderSystem		描画システム
 * @param	width				シャドウ描画ターゲット幅
 * @param	height				シャドウ描画ターゲット高さ
 * @param	shadowLevels		シャドウレベル
 */
/************************************************************************************************/
KsShadowManager::KsShadowManager( KsRenderSystem* pRenderSystem, KsUInt32 width, KsUInt32 height, KsUInt32 shadowLevels )
	: m_cascadeLevels( 3 )
{
	for( KsUInt32 index=0; index<MAX_CASCADES; index++ ) 
	{
		m_viewport[ index ].set( 0, 0, 0, 0, 0.0f, 1.0f );

		m_pShadowMapVS[ index ] = NULL;
		m_pShadowMapPS[ index ] = NULL;
	}

	// 初期化する
	initialize( pRenderSystem, width, height, shadowLevels );
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsShadowManager::~KsShadowManager()
{
	ksDELETE( m_prsScene );
	ksDELETE( m_prsShadow );
	ksDELETE( m_prsShadowPancake );

	ksDELETE( m_pSamLinear );
	ksDELETE( m_pSamShadowPCF );
	ksDELETE( m_pSamShadowPoint );

	ksDELETE( m_pShadowMapRT );
}

/************************************************************************************************/
/*
 * 初期化処理
 * @param	pRenderSystem		描画システム
 * @param	width				シャドウ描画ターゲット幅
 * @param	height				シャドウ描画ターゲット高さ
 * @param	shadowLevels		シャドウレベル
 */
/************************************************************************************************/
void KsShadowManager::initialize( KsRenderSystem* pRenderSystem, KsUInt32 width, KsUInt32 height, KsUInt32 shadowLevels )
{
	for( KsUInt32 index=0; index<shadowLevels; index++ ) 
	{
		m_viewport[ index ].set( 0, 0, width * index, height, 0.0f, 1.0f );
	}

	// レンダーターゲット生成
	m_pShadowMapRT = pRenderSystem->createDepthStencilView( shadowLevels * width, height, KS_GI_FORMAT_R32_TYPELESS, KS_GI_FORMAT_D32_FLOAT, KS_GI_FORMAT_R32_FLOAT );


	// サンプラー生成
	KS_SAMPLER_DESC SamDesc;
	SamDesc.Filter         = KS_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU       = KS_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV       = KS_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW       = KS_TEXTURE_ADDRESS_WRAP;
	SamDesc.MipLODBias     = 0.0f;
	SamDesc.MaxAnisotropy  = 1;
	SamDesc.ComparisonFunc = KS_COMPARISON_ALWAYS;
	SamDesc.BorderColor[0] = 0;
	SamDesc.BorderColor[1] = 0;
	SamDesc.BorderColor[2] = 0;
	SamDesc.BorderColor[3] = 0;
	SamDesc.MinLOD         = 0.0f;
	SamDesc.MaxLOD         = ksFLOAT32_MIN;

	m_pSamLinear = pRenderSystem->createSamplerState( &SamDesc );


	KS_SAMPLER_DESC SamDescShad = 
	{
		KS_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT,// KS_FILTER Filter;
		KS_TEXTURE_ADDRESS_BORDER, //KS_TEXTURE_ADDRESS_MODE AddressU;
		KS_TEXTURE_ADDRESS_BORDER, //KS_TEXTURE_ADDRESS_MODE AddressV;
		KS_TEXTURE_ADDRESS_BORDER, //KS_TEXTURE_ADDRESS_MODE AddressW;
		0,//FLOAT MipLODBias;
		0,//UINT MaxAnisotropy;
		KS_COMPARISON_LESS , //KS_COMPARISON_FUNC ComparisonFunc;
		0.0,0.0,0.0,0.0,//FLOAT BorderColor[ 4 ];
		0,//FLOAT MinLOD;
		0//FLOAT MaxLOD;   
	};

	m_pSamShadowPCF = pRenderSystem->createSamplerState( &SamDescShad );

	SamDescShad.MaxAnisotropy  = 15;
	SamDescShad.AddressU       = KS_TEXTURE_ADDRESS_CLAMP;
	SamDescShad.AddressV       = KS_TEXTURE_ADDRESS_CLAMP;
	SamDescShad.Filter         = KS_FILTER_ANISOTROPIC;
	SamDescShad.ComparisonFunc = KS_COMPARISON_NEVER;

	m_pSamShadowPoint = pRenderSystem->createSamplerState( &SamDescShad );


	// ラスタライズステート生成
	KS_RASTERIZER_DESC drd = 
	{
		KS_FILL_SOLID,
		KS_CULL_NONE,
		ksFALSE,
		0,
		0.0f,
		0.0f,
		ksTRUE,
		ksFALSE,
		ksTRUE,
		ksFALSE
	};

	m_prsScene  = pRenderSystem->createRasterizerState( &drd );

	drd.SlopeScaledDepthBias = 1.0f;
	m_prsShadow = pRenderSystem->createRasterizerState( &drd );
	
	drd.DepthClipEnable = ksFALSE;
	m_prsShadowPancake = pRenderSystem->createRasterizerState( &drd );

	// AABB判定用バウンディングボックス
	m_vSceneAABBMin = KsVector4d::MIN; 
	m_vSceneAABBMax = KsVector4d::MAX;
}


//--------------------------------------------------------------------------------------
// This function converts the "center, extents" version of an AABB into 8 points.
//--------------------------------------------------------------------------------------
void KsShadowManager::createAABBPoints( KsVector4d* vAABBPoints, const KsVector4d& vCenter, const KsVector4d& vExtents )
{
	//This map enables us to use a for loop and do vector math.
	static const KsVector4d vExtentsMap[] = 
	{ 
		KsVector4d(  1.0f,  1.0f, -1.0f, 1.0f ), 
		KsVector4d( -1.0f,  1.0f, -1.0f, 1.0f ), 
		KsVector4d(  1.0f, -1.0f, -1.0f, 1.0f ), 
		KsVector4d( -1.0f, -1.0f, -1.0f, 1.0f ), 
		KsVector4d(  1.0f,  1.0f,  1.0f, 1.0f ), 
		KsVector4d( -1.0f,  1.0f,  1.0f, 1.0f ), 
		KsVector4d(  1.0f, -1.0f,  1.0f, 1.0f ), 
		KsVector4d( -1.0f, -1.0f,  1.0f, 1.0f ) 
	};

	//最初の 2 つのベクトルの積を、3 番目のベクトルに加算します。
	for( KsUInt32 index = 0; index < 8; ++index ) 
	{
		vAABBPoints[ index ] = KsVector4d::MultiplyAdd( vExtentsMap[index], vExtents, vCenter ); 
	}
}


#if 0
	// Calcaulte the AABB for the scene by iterating through all the meshes in the SDKMesh file.
	for( UINT i =0; i < pMesh->GetNumMeshes( ); ++i ) 
	{
		SDKMESH_MESH* msh = pMesh->GetMesh( i );
		vMeshMin = XMVectorSet( msh->BoundingBoxCenter.x - msh->BoundingBoxExtents.x,
				msh->BoundingBoxCenter.y - msh->BoundingBoxExtents.y,
				msh->BoundingBoxCenter.z - msh->BoundingBoxExtents.z,
				1.0f );

		vMeshMax = XMVectorSet( msh->BoundingBoxCenter.x + msh->BoundingBoxExtents.x,
				msh->BoundingBoxCenter.y + msh->BoundingBoxExtents.y,
				msh->BoundingBoxCenter.z + msh->BoundingBoxExtents.z,
				1.0f );
		m_vSceneAABBMin = XMVectorMin( vMeshMin, m_vSceneAABBMin );
		m_vSceneAABBMax = XMVectorMax( vMeshMax, m_vSceneAABBMax );
	}
#endif
//--------------------------------------------------------------------------------------
// This function takes the camera's projection matrix and returns the 8
// points that make up a view frustum.
// The frustum is scaled to fit within the Begin and End interval paramaters.
//--------------------------------------------------------------------------------------
void KsShadowManager::createFrustumPointsFromCascadeInterval( KsReal fCascadeIntervalBegin, 
															  KsReal fCascadeIntervalEnd, 
															  KsMatrix4x4&	vProjection,
															  KsVector4d*	pvCornerPointsWorld ) 
{
#if 0
	XNA::Frustum vViewFrust;
	ComputeFrustumFromProjection( &vViewFrust, &vProjection );
	vViewFrust.Near = fCascadeIntervalBegin;
	vViewFrust.Far = fCascadeIntervalEnd;

	static const XMVECTORU32 vGrabY = {0x00000000,0xFFFFFFFF,0x00000000,0x00000000};
	static const XMVECTORU32 vGrabX = {0xFFFFFFFF,0x00000000,0x00000000,0x00000000};

	XMVECTORF32 vRightTop = {vViewFrust.RightSlope,vViewFrust.TopSlope,1.0f,1.0f};
	XMVECTORF32 vLeftBottom = {vViewFrust.LeftSlope,vViewFrust.BottomSlope,1.0f,1.0f};
	XMVECTORF32 vNear = {vViewFrust.Near,vViewFrust.Near,vViewFrust.Near,1.0f};
	XMVECTORF32 vFar = {vViewFrust.Far,vViewFrust.Far,vViewFrust.Far,1.0f};
	XMVECTOR vRightTopNear = XMVectorMultiply( vRightTop, vNear );
	XMVECTOR vRightTopFar = XMVectorMultiply( vRightTop, vFar );
	XMVECTOR vLeftBottomNear = XMVectorMultiply( vLeftBottom, vNear );
	XMVECTOR vLeftBottomFar = XMVectorMultiply( vLeftBottom, vFar );

	pvCornerPointsWorld[0] = vRightTopNear;
	pvCornerPointsWorld[1] = XMVectorSelect( vRightTopNear, vLeftBottomNear, vGrabX );
	pvCornerPointsWorld[2] = vLeftBottomNear;
	pvCornerPointsWorld[3] = XMVectorSelect( vRightTopNear, vLeftBottomNear,vGrabY );

	pvCornerPointsWorld[4] = vRightTopFar;
	pvCornerPointsWorld[5] = XMVectorSelect( vRightTopFar, vLeftBottomFar, vGrabX );
	pvCornerPointsWorld[6] = vLeftBottomFar;
	pvCornerPointsWorld[7] = XMVectorSelect( vRightTopFar ,vLeftBottomFar, vGrabY );
#endif

}

#if 0


//--------------------------------------------------------------------------------------
// This function is where the real work is done. We determin the matricies and constants used in 
// shadow generation and scene generation.
//--------------------------------------------------------------------------------------
HRESULT CascadedShadowsManager::InitFrame ( ID3D11Device* pd3dDevice, CDXUTSDKMesh* mesh ) 
{
   
    ReleaseAndAllocateNewShadowResources( pd3dDevice );

    // Copy D3DX matricies into XNA Math matricies.
    const D3DXMATRIX* mD3DXViewCameraProjection = m_pViewerCamera->GetProjMatrix();
    XMMATRIX matViewCameraProjection = XMLoadFloat4x4((XMFLOAT4X4*)&mD3DXViewCameraProjection->_11 );
    const D3DXMATRIX* mD3DXViewCameraView = m_pViewerCamera->GetViewMatrix();
    XMMATRIX matViewCameraView = XMLoadFloat4x4((XMFLOAT4X4*)&mD3DXViewCameraView->_11);
    const D3DXMATRIX* mD3DLightView = m_pLightCamera->GetViewMatrix();
    XMMATRIX matLightCameraView = XMLoadFloat4x4((XMFLOAT4X4*)&mD3DLightView ->_11);

    XMVECTOR det;
    XMMATRIX matInverseViewCamera = XMMatrixInverse( &det,  matViewCameraView );

    // Convert from min max representation to center extents represnetation.
    // This will make it easier to pull the points out of the transformation.
    XMVECTOR vSceneCenter = m_vSceneAABBMin + m_vSceneAABBMax;
    vSceneCenter  *= g_vHalfVector;
    XMVECTOR vSceneExtents = m_vSceneAABBMax - m_vSceneAABBMin;
    vSceneExtents *= g_vHalfVector;    

    XMVECTOR vSceneAABBPointsLightSpace[8];
    // This function simply converts the center and extents of an AABB into 8 points
    CreateAABBPoints( vSceneAABBPointsLightSpace, vSceneCenter, vSceneExtents );
    // Transform the scene AABB to Light space.
    for( int index =0; index < 8; ++index ) 
    {
        vSceneAABBPointsLightSpace[index] = XMVector4Transform( vSceneAABBPointsLightSpace[index], matLightCameraView ); 
    }

    
    FLOAT fFrustumIntervalBegin, fFrustumIntervalEnd;
    XMVECTOR vLightCameraOrthographicMin;  // light space frustrum aabb 
    XMVECTOR vLightCameraOrthographicMax;
    FLOAT fCameraNearFarRange = m_pViewerCamera->GetFarClip() - m_pViewerCamera->GetNearClip();
       
    XMVECTOR vWorldUnitsPerTexel = g_vZero; 

    // We loop over the cascades to calculate the orthographic projection for each cascade.
    for( INT iCascadeIndex=0; iCascadeIndex < m_CopyOfCascadeConfig.m_nCascadeLevels; ++iCascadeIndex ) 
    {
        // Calculate the interval of the View Frustum that this cascade covers. We measure the interval 
        // the cascade covers as a Min and Max distance along the Z Axis.
        if( m_eSelectedCascadesFit == FIT_TO_CASCADES ) 
        {
            // Because we want to fit the orthogrpahic projection tightly around the Cascade, we set the Mimiumum cascade 
            // value to the previous Frustum end Interval
            if( iCascadeIndex==0 ) fFrustumIntervalBegin = 0.0f;
            else fFrustumIntervalBegin = (FLOAT)m_iCascadePartitionsZeroToOne[ iCascadeIndex - 1 ];
        } 
        else 
        {
            // In the FIT_TO_SCENE technique the Cascades overlap eachother.  In other words, interval 1 is coverd by
            // cascades 1 to 8, interval 2 is covered by cascades 2 to 8 and so forth.
            fFrustumIntervalBegin = 0.0f;
        }

        // Scale the intervals between 0 and 1. They are now percentages that we can scale with.
        fFrustumIntervalEnd = (FLOAT)m_iCascadePartitionsZeroToOne[ iCascadeIndex ];        
        fFrustumIntervalBegin/= (FLOAT)m_iCascadePartitionsMax;
        fFrustumIntervalEnd/= (FLOAT)m_iCascadePartitionsMax;
        fFrustumIntervalBegin = fFrustumIntervalBegin * fCameraNearFarRange;
        fFrustumIntervalEnd = fFrustumIntervalEnd * fCameraNearFarRange;
        XMVECTOR vFrustumPoints[8];

        // This function takes the began and end intervals along with the projection matrix and returns the 8
        // points that repreresent the cascade Interval
        CreateFrustumPointsFromCascadeInterval( fFrustumIntervalBegin, fFrustumIntervalEnd, 
            matViewCameraProjection, vFrustumPoints );

        vLightCameraOrthographicMin = g_vFLTMAX;
        vLightCameraOrthographicMax = g_vFLTMIN;

        XMVECTOR vTempTranslatedCornerPoint;
        // This next section of code calculates the min and max values for the orthographic projection.
        for( int icpIndex=0; icpIndex < 8; ++icpIndex ) 
        {
            // Transform the frustum from camera view space to world space.
            vFrustumPoints[icpIndex] = XMVector4Transform ( vFrustumPoints[icpIndex], matInverseViewCamera );
            // Transform the point from world space to Light Camera Space.
            vTempTranslatedCornerPoint = XMVector4Transform ( vFrustumPoints[icpIndex], matLightCameraView );
            // Find the closest point.
            vLightCameraOrthographicMin = XMVectorMin ( vTempTranslatedCornerPoint, vLightCameraOrthographicMin );
            vLightCameraOrthographicMax = XMVectorMax ( vTempTranslatedCornerPoint, vLightCameraOrthographicMax );
        }

        // This code removes the shimmering effect along the edges of shadows due to
        // the light changing to fit the camera.
        if( m_eSelectedCascadesFit == FIT_TO_SCENE ) 
        {
            // Fit the ortho projection to the cascades far plane and a near plane of zero. 
            // Pad the projection to be the size of the diagonal of the Frustum partition. 
            // 
            // To do this, we pad the ortho transform so that it is always big enough to cover 
            // the entire camera view frustum.
            XMVECTOR vDiagonal = vFrustumPoints[0] - vFrustumPoints[6];
            vDiagonal = XMVector3Length( vDiagonal );
            
            // The bound is the length of the diagonal of the frustum interval.
            FLOAT fCascadeBound = XMVectorGetX( vDiagonal );
            
            // The offset calculated will pad the ortho projection so that it is always the same size 
            // and big enough to cover the entire cascade interval.
            XMVECTOR vBoarderOffset = ( vDiagonal - 
                                        ( vLightCameraOrthographicMax - vLightCameraOrthographicMin ) ) 
                                        * g_vHalfVector;
            // Set the Z and W components to zero.
            vBoarderOffset *= g_vMultiplySetzwToZero;
            
            // Add the offsets to the projection.
            vLightCameraOrthographicMax += vBoarderOffset;
            vLightCameraOrthographicMin -= vBoarderOffset;

            // The world units per texel are used to snap the shadow the orthographic projection
            // to texel sized increments.  This keeps the edges of the shadows from shimmering.
            FLOAT fWorldUnitsPerTexel = fCascadeBound / (float)m_CopyOfCascadeConfig.m_iBufferSize;
            vWorldUnitsPerTexel = XMVectorSet( fWorldUnitsPerTexel, fWorldUnitsPerTexel, 0.0f, 0.0f ); 


        } 
        else if( m_eSelectedCascadesFit == FIT_TO_CASCADES ) 
        {

            // We calculate a looser bound based on the size of the PCF blur.  This ensures us that we're 
            // sampling within the correct map.
            float fScaleDuetoBlureAMT = ( (float)( m_iPCFBlurSize * 2 + 1 ) 
                /(float)m_CopyOfCascadeConfig.m_iBufferSize );
            XMVECTORF32 vScaleDuetoBlureAMT = { fScaleDuetoBlureAMT, fScaleDuetoBlureAMT, 0.0f, 0.0f };

            
            float fNormalizeByBufferSize = ( 1.0f / (float)m_CopyOfCascadeConfig.m_iBufferSize );
            XMVECTOR vNormalizeByBufferSize = XMVectorSet( fNormalizeByBufferSize, fNormalizeByBufferSize, 0.0f, 0.0f );

            // We calculate the offsets as a percentage of the bound.
            XMVECTOR vBoarderOffset = vLightCameraOrthographicMax - vLightCameraOrthographicMin;
            vBoarderOffset *= g_vHalfVector;
            vBoarderOffset *= vScaleDuetoBlureAMT;
            vLightCameraOrthographicMax += vBoarderOffset;
            vLightCameraOrthographicMin -= vBoarderOffset;
           
            // The world units per texel are used to snap  the orthographic projection
            // to texel sized increments.  
            // Because we're fitting tighly to the cascades, the shimmering shadow edges will still be present when the 
            // camera rotates.  However, when zooming in or strafing the shadow edge will not shimmer.
            vWorldUnitsPerTexel = vLightCameraOrthographicMax - vLightCameraOrthographicMin;
            vWorldUnitsPerTexel *= vNormalizeByBufferSize;

        }
        float fLightCameraOrthographicMinZ = XMVectorGetZ( vLightCameraOrthographicMin );


        if( m_bMoveLightTexelSize ) 
        {

            // We snape the camera to 1 pixel increments so that moving the camera does not cause the shadows to jitter.
            // This is a matter of integer dividing by the world space size of a texel
            vLightCameraOrthographicMin /= vWorldUnitsPerTexel;
            vLightCameraOrthographicMin = XMVectorFloor( vLightCameraOrthographicMin );
            vLightCameraOrthographicMin *= vWorldUnitsPerTexel;
            
            vLightCameraOrthographicMax /= vWorldUnitsPerTexel;
            vLightCameraOrthographicMax = XMVectorFloor( vLightCameraOrthographicMax );
            vLightCameraOrthographicMax *= vWorldUnitsPerTexel;

        }
 
        //These are the unconfigured near and far plane values.  They are purposly awful to show 
        // how important calculating accurate near and far planes is.
        FLOAT fNearPlane = 0.0f;
        FLOAT fFarPlane = 10000.0f;

        if( m_eSelectedNearFarFit == FIT_NEARFAR_AABB ) 
        {

            XMVECTOR vLightSpaceSceneAABBminValue = g_vFLTMAX;  // world space scene aabb 
            XMVECTOR vLightSpaceSceneAABBmaxValue = g_vFLTMIN;       
            // We calculate the min and max vectors of the scene in light space. The min and max "Z" values of the  
            // light space AABB can be used for the near and far plane. This is easier than intersecting the scene with the AABB
            // and in some cases provides similar results.
            for(int index=0; index< 8; ++index) 
            {
                vLightSpaceSceneAABBminValue = XMVectorMin( vSceneAABBPointsLightSpace[index], vLightSpaceSceneAABBminValue );
                vLightSpaceSceneAABBmaxValue = XMVectorMax( vSceneAABBPointsLightSpace[index], vLightSpaceSceneAABBmaxValue );
            }

            // The min and max z values are the near and far planes.
            fNearPlane = XMVectorGetZ( vLightSpaceSceneAABBminValue );
            fFarPlane = XMVectorGetZ( vLightSpaceSceneAABBmaxValue );
        } 
        else if( m_eSelectedNearFarFit == FIT_NEARFAR_SCENE_AABB 
            || m_eSelectedNearFarFit == FIT_NEARFAR_PANCAKING ) 
        {
            // By intersecting the light frustum with the scene AABB we can get a tighter bound on the near and far plane.
            ComputeNearAndFar( fNearPlane, fFarPlane, vLightCameraOrthographicMin, 
                vLightCameraOrthographicMax, vSceneAABBPointsLightSpace );
            if (m_eSelectedNearFarFit == FIT_NEARFAR_PANCAKING )
            {
                if ( fLightCameraOrthographicMinZ > fNearPlane )
                {
                    fNearPlane = fLightCameraOrthographicMinZ;
                }
            }
        } 
        else 
        {
        
        }
        // Craete the orthographic projection for this cascade.
        D3DXMatrixOrthoOffCenterLH( &m_matShadowProj[ iCascadeIndex ], 
            XMVectorGetX( vLightCameraOrthographicMin ), 
            XMVectorGetX( vLightCameraOrthographicMax ), 
            XMVectorGetY( vLightCameraOrthographicMin ), 
            XMVectorGetY( vLightCameraOrthographicMax ), 
            fNearPlane, fFarPlane );

        m_fCascadePartitionsFrustum[ iCascadeIndex ] = fFrustumIntervalEnd;
    }
    m_matShadowView = *m_pLightCamera->GetViewMatrix();
   

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Render the cascades into a texture atlas.
//--------------------------------------------------------------------------------------
HRESULT KsShadowManager::RenderShadowsForAllCascades ( ID3D11Device* pd3dDevice, 
            ID3D11DeviceContext* pd3dDeviceContext, 
            CDXUTSDKMesh* pMesh 
            ) {

    HRESULT hr = S_OK;

    D3DXMATRIX dxmatWorldViewProjection;
    D3DXMATRIX dxmatWorld;


	// 深度ステンシルバッファをクリアーする
	m_pRenderContext->clearDepthStencil( m_pCascadedShadowMapDSV, ksCLEAR_FLAG_DEPTH, 0.0f, 0 );

    pd3dDeviceContext->ClearDepthStencilView( m_pCascadedShadowMapDSV, D3D11_CLEAR_DEPTH, 1.0, 0 );
    ID3D11RenderTargetView* pnullView = NULL; 
    // Set a null render target so as not to render color.
    pd3dDeviceContext->OMSetRenderTargets( 1, &pnullView , m_pCascadedShadowMapDSV );

    if ( m_eSelectedNearFarFit == FIT_NEARFAR_PANCAKING )
    {
        pd3dDeviceContext->RSSetState( m_prsShadowPancake );
    }
    else 
    {
        pd3dDeviceContext->RSSetState( m_prsShadow );
    }
    // Iterate over cascades and render shadows.
    for( INT currentCascade=0; currentCascade < m_CopyOfCascadeConfig.m_nCascadeLevels; ++currentCascade ) 
    {

        // Each cascade has its own viewport because we're storing all the cascades in one large texture.
        pd3dDeviceContext->RSSetViewports( 1, &m_RenderVP[currentCascade] );
        dxmatWorld = *m_pLightCamera->GetWorldMatrix();
        
        // We calculate the matrices in the Init function.
        dxmatWorldViewProjection =  m_matShadowView * m_matShadowProj[currentCascade];
        
        D3D11_MAPPED_SUBRESOURCE MappedResource;
        V( pd3dDeviceContext->Map( m_pcbGlobalConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource ) );
        CB_ALL_SHADOW_DATA* pcbAllShadowConstants = ( CB_ALL_SHADOW_DATA* )MappedResource.pData;
        D3DXMatrixTranspose( &pcbAllShadowConstants->m_WorldViewProj, &dxmatWorldViewProjection );
        D3DXMATRIX matIdentity;
        D3DXMatrixIdentity( &matIdentity );
        // The model was exported in world space, so we can pass the identity up as the world transform.
        D3DXMatrixTranspose( &pcbAllShadowConstants->m_World, &matIdentity );
        pd3dDeviceContext->Unmap( m_pcbGlobalConstantBuffer, 0 );
        pd3dDeviceContext->IASetInputLayout( m_pVertexLayoutMesh );

        // No pixel shader is bound as we're only writing out depth.
        pd3dDeviceContext->VSSetShader( m_pvsRenderOrthoShadow, NULL, 0 );
        pd3dDeviceContext->PSSetShader( NULL, NULL, 0 );
        pd3dDeviceContext->GSSetShader( NULL, NULL, 0 );
        
        pd3dDeviceContext->VSSetConstantBuffers( 0, 1, &m_pcbGlobalConstantBuffer );

        pMesh->Render( pd3dDeviceContext, 0, 1 );
    }
    
    pd3dDeviceContext->RSSetState( NULL );
    pd3dDeviceContext->OMSetRenderTargets( 1, &pnullView, NULL );

    return hr;

}


#endif

void KsShadowManager::renderShadowsForAllCascades()
{
	// 深度ステンシルバッファをクリアーする
	m_pRenderContext->clearDepthStencil( m_pShadowMapRT, ksCLEAR_FLAG_DEPTH, 0.0f, 0 );

	//pd3dDeviceContext->ClearDepthStencilView( m_pCascadedShadowMapDSV, D3D11_CLEAR_DEPTH, 1.0, 0 );

	// レンダーターゲット をセットする（Color, Depth）
	m_pRenderContext->setRenderTarget( NULL, m_pShadowMapRT );

	// レンダーステートをセットする
	//m_pRenderContext->
#if 0
	// 指定オブジェクトをすべて描画する

#endif

#if 0
	// 影用テクスチャ作成
	for( KsInt32 i=0; i<m_nCascadeLevels; i++ )
	{
		// Viewport を設定する
		pd3dDeviceContext->RSSetViewports( 1, &m_RenderVP[currentCascade] );
		dxmatWorld = *m_pLightCamera->GetWorldMatrix();
        
		// We calculate the matrices in the Init function.
		dxmatWorldViewProjection =  m_matShadowView * m_matShadowProj[currentCascade];
        
		D3D11_MAPPED_SUBRESOURCE MappedResource;
		V( pd3dDeviceContext->Map( m_pcbGlobalConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource ) );
		CB_ALL_SHADOW_DATA* pcbAllShadowConstants = ( CB_ALL_SHADOW_DATA* )MappedResource.pData;
		D3DXMatrixTranspose( &pcbAllShadowConstants->m_WorldViewProj, &dxmatWorldViewProjection );
		D3DXMATRIX matIdentity;
		D3DXMatrixIdentity( &matIdentity );
		// The model was exported in world space, so we can pass the identity up as the world transform.
		D3DXMatrixTranspose( &pcbAllShadowConstants->m_World, &matIdentity );
		pd3dDeviceContext->Unmap( m_pcbGlobalConstantBuffer, 0 );
		pd3dDeviceContext->IASetInputLayout( m_pVertexLayoutMesh );

		// No pixel shader is bound as we're only writing out depth.
		pd3dDeviceContext->VSSetShader( m_pvsRenderOrthoShadow, NULL, 0 );
		pd3dDeviceContext->PSSetShader( NULL, NULL, 0 );
		pd3dDeviceContext->GSSetShader( NULL, NULL, 0 );
        
		pd3dDeviceContext->VSSetConstantBuffers( 0, 1, &m_pcbGlobalConstantBuffer );

		pMesh->Render( pd3dDeviceContext, 0, 1 );
	}
	// Cleanup
	//m_pRenderContext->setComputeShader( 0 );
	m_pRenderContext->setVertexShader( 0 );
	m_pRenderContext->setPixelShader( 0 );
	
	m_pRenderContext->setRenderTargets( 0, 0, 0 );
#endif

}
