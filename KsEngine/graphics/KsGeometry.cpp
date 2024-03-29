/************************************************************************************************/
/** 
 * @file		KsGeometry.cpp
 * @brief		サンプラー設定クラス
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"
#include "KsGeometry.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsGeometry::KsGeometry()
{
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KsGeometry::~KsGeometry()
{
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KsBool KsGeometry::createCube( KsReal size, KsBool rhcoords )
{
    const KsInt32 FaceCount  = 6;
	const KsInt32 FaceVertex = 4;

    static const KsVector3d faceNormals[ FaceCount ] =
    {
        KsVector3d( 0,  0,  1 ),
        KsVector3d( 0,  0, -1 ),
        KsVector3d( 1,  0,  0 ),
        KsVector3d(-1,  0,  0 ),
        KsVector3d( 0,  1,  0 ),
        KsVector3d( 0, -1,  0 ),
    };

    static const KsVector2d textureCoordinates[ FaceVertex ] =
    {
        KsVector2d( 1, 0 ),
        KsVector2d( 1, 1 ),
        KsVector2d( 0, 1 ),
        KsVector2d( 0, 0 ),
    };

	static KsUInt16 indices[] = 
	{ 
		 0,  1,  2,  0,  2,  3,
		 4,  5,  6,  4,  6,  7,
		 8,  9, 10,  8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23,
	};

	KS_VERTEX_PNT	vertices[ FaceVertex * FaceCount ];
	KsUInt32		idx = 0;

    size *= 0.5f;

    for( KsInt32 i = 0; i < FaceCount; i++ )
    {
		KsVector3d normal = faceNormals[ i ];
        KsVector3d basis  = (i >= 4) ? KsVector3d::V001 : KsVector3d::V010;
        KsVector3d side1  = KsVector3d::Cross( normal, basis );
        KsVector3d side2  = KsVector3d::Cross( normal, side1 );

		vertices[ idx ].Position     = ( (normal - side1 - side2) * size );
		vertices[ idx ].Normal       = normal;
		vertices[ idx ].TextureCoord = textureCoordinates[ 0 ];
		++idx;

		vertices[ idx ].Position     = ( (normal - side1 + side2) * size );
		vertices[ idx ].Normal       = normal;
		vertices[ idx ].TextureCoord = textureCoordinates[ 1 ];
		++idx;

		vertices[ idx ].Position     = ( (normal + side1 + side2) * size );
		vertices[ idx ].Normal       = normal;
		vertices[ idx ].TextureCoord = textureCoordinates[ 2 ];
		++idx;

		vertices[ idx ].Position     = ( (normal + side1 - side2) * size );
		vertices[ idx ].Normal       = normal;
		vertices[ idx ].TextureCoord = textureCoordinates[ 3 ];
		++idx;
    }
	
	KsUInt32 numVertex = idx;
	KsUInt32 numIndex  = ksARRAYSIZE(indices);

#if 0
	KsShaderManager*		pShaderManager = KsShaderManager::getInstancePtr();
	KsInputLayoutManager*	pLayoutManager = KsInputLayoutManager::getInstancePtr();

	m_pVShader      = (KsVertexShader*)pShaderManager->createFromFile( "sprite.fx", "VS_Sprite", ksSHADE_MODEL_5_0, ksVERTEX_SHADER );
	m_pPShader      = (KsPixelShader*) pShaderManager->createFromFile( "sprite.fx", "PS_Sprite", ksSHADE_MODEL_5_0, ksPIXEL_SHADER  );
	m_pInputLayout  = pLayoutManager->createInputLayout( VS_SPRITE_LAYOUT, ksARRAYSIZE( VS_SPRITE_LAYOUT ), (KsVertexShader*)m_pVShader );
	m_pVertexBuffer = pBufferManager->createVertexBuffer( vertices, sizeof(KS_VERTEX_PNT), numVertex, ksGEOMETRY_FVF_PNT, ksCPU_ACCESS_WRITE );
	m_pIndexBuffer  = pBufferManager->createIndexBuffer ( indices,  sizeof(KsUInt16)*numIndex, numIndex, ksFMT_INDEX16, 0 );

#endif

	return ksTRUE;
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KsBool KsGeometry::createSphere( KsReal diameter, KsUInt32 tessellation, KsBool rhcoords )
{
	if( tessellation < 3 )
	{
		return ksFALSE;
	}

	const KsUInt32 verticalSegments   = tessellation;
	const KsUInt32 horizontalSegments = tessellation * 2;
	const KsReal   radius             = diameter * 0.5f;

	KS_VERTEX_PNT	vertices[ 512 ];
	KsUInt16		indices[ 1024 ];
	KsUInt32		vcnt = 0;
	KsUInt32		icnt = 0;

	for( KsUInt32 i = 0; i <= verticalSegments; i++ )
	{
		KsReal v = 1.0f - (KsReal)i / verticalSegments;

		KsReal latitude = (i * ksPI / verticalSegments) - ksHALF_PI;
		KsReal dy, dxz;

		dy  = KsSin( latitude );
		dxz = KsCos( latitude );

		for( KsUInt32 j = 0; j <= horizontalSegments; j++ )
		{
			KsReal u = (KsReal)j / horizontalSegments;

			KsReal longitude = j * ksPI / horizontalSegments;
			KsReal dx, dz;

			dx  = KsSin( longitude );
			dz  = KsCos( longitude );
			dx *= dxz;
			dz *= dxz;

			KsVector3d normal( dx, dy, dz );
			KsVector2d textureCoordinate( u, v );

			vertices[ vcnt ].Position = normal * radius;
			vertices[ vcnt ].Normal   = normal;
			vertices[ vcnt ].TextureCoord.set( u, v );

			++vcnt;
		}
	}

	// Fill the index buffer with triangles joining each pair of latitude rings.
	const KsUInt32 stride = horizontalSegments + 1;

	for( KsUInt32 i = 0; i < verticalSegments; i++ )
	{
		for( KsUInt32 j = 0; j <= horizontalSegments; j++ )
		{
			const KsUInt32 nextI = (i + 1);
			const KsUInt32 nextJ = (j + 1) % stride;

			indices[ icnt++ ] = (i * stride + j);
			indices[ icnt++ ] = (nextI * stride + j);
			indices[ icnt++ ] = (i * stride + nextJ);

			indices[ icnt++ ] = (i * stride + nextJ);
			indices[ icnt++ ] = (nextI * stride + j);
			indices[ icnt++ ] = (nextI * stride + nextJ);
		}
	}

	
	KsUInt32 numVertex = vcnt;
	KsUInt32 numIndex  = icnt;

	KsHardwareBufferManager*	pBufferManager = KsHardwareBufferManager::getInstancePtr();
	KsVertexBuffer*				pVertexBuffer  = pBufferManager->createVertexBuffer( vertices, sizeof(KS_VERTEX_PNT), numVertex, ksGEOMETRY_FVF_PNT, ksCPU_ACCESS_WRITE );
	KsIndexBuffer*				pIndexBuffer   = pBufferManager->createIndexBuffer ( indices,  sizeof(KsUInt16)*numIndex, numIndex, ksFMT_INDEX16, 0 );

	m_pVertexBuffer = pVertexBuffer;
	m_pIndexBuffer  = pIndexBuffer;

	return ksTRUE;
}


#if 0

//--------------------------------------------------------------------------------------
// Sphere
//--------------------------------------------------------------------------------------

// Creates a sphere primitive.
std::unique_ptr<GeometricPrimitive> GeometricPrimitive::CreateSphere(_In_ ID3D11DeviceContext* deviceContext, float diameter, size_t tessellation, bool rhcoords)
{
    VertexCollection vertices;
    IndexCollection indices;



    // Create rings of vertices at progressively higher latitudes.
    for (size_t i = 0; i <= verticalSegments; i++)
    {
        float v = 1 - (float)i / verticalSegments;

        float latitude = (i * XM_PI / verticalSegments) - XM_PIDIV2;
        float dy, dxz;

        XMScalarSinCos(&dy, &dxz, latitude);

        // Create a single ring of vertices at this latitude.
        for (size_t j = 0; j <= horizontalSegments; j++)
        {
            float u = (float)j / horizontalSegments;

            float longitude = j * XM_2PI / horizontalSegments;
            float dx, dz;

            XMScalarSinCos(&dx, &dz, longitude);

            dx *= dxz;
            dz *= dxz;

            XMVECTOR normal = XMVectorSet(dx, dy, dz, 0);
            XMVECTOR textureCoordinate = XMVectorSet(u, v, 0, 0);

            vertices.push_back(VertexPositionNormalTexture(normal * radius, normal, textureCoordinate));
        }
    }

    // Fill the index buffer with triangles joining each pair of latitude rings.
    size_t stride = horizontalSegments + 1;

    for (size_t i = 0; i < verticalSegments; i++)
    {
        for (size_t j = 0; j <= horizontalSegments; j++)
        {
            size_t nextI = i + 1;
            size_t nextJ = (j + 1) % stride;

            indices.push_back(i * stride + j);
            indices.push_back(nextI * stride + j);
            indices.push_back(i * stride + nextJ);

            indices.push_back(i * stride + nextJ);
            indices.push_back(nextI * stride + j);
            indices.push_back(nextI * stride + nextJ);
        }
    }

    // Create the primitive object.
    std::unique_ptr<GeometricPrimitive> primitive(new GeometricPrimitive());
    
    primitive->pImpl->Initialize(deviceContext, vertices, indices, rhcoords);

    return primitive;
}









//--------------------------------------------------------------------------------------
// File: GeometricPrimitive.cpp
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// http://go.microsoft.com/fwlink/?LinkId=248929
//--------------------------------------------------------------------------------------

#include "pch.h"
#include "GeometricPrimitive.h"
#include "Effects.h"
#include "CommonStates.h"
#include "VertexTypes.h"
#include "SharedResourcePool.h"
#include "Bezier.h"
#include <vector>
#include <map>

using namespace DirectX;
using namespace Microsoft::WRL;


namespace
{
    void CheckIndexOverflow(size_t value)
    {
        // Use >=, not > comparison, because some D3D level 9_x hardware does not support 0xFFFF index values.
        if (value >= USHRT_MAX)
            throw std::exception("Index value out of range: cannot tesselate primitive so finely");
    }


    // Temporary collection types used when generating the geometry.
    typedef std::vector<VertexPositionNormalTexture> VertexCollection;
    
    
    class IndexCollection : public std::vector<uint16_t>
    {
    public:
        // Sanity check the range of 16 bit index values.
        void push_back(size_t value)
        {
            CheckIndexOverflow(value);
            vector::push_back((uint16_t)value);
        }
    };


    // Helper for flipping winding of geometric primitives for LH vs. RH coords
    static void ReverseWinding( IndexCollection& indices, VertexCollection& vertices )
    {
        assert( (indices.size() % 3) == 0 );
        for( auto it = indices.begin(); it != indices.end(); it += 3 )
        {
            std::swap( *it, *(it+2) );
        }

        for( auto it = vertices.begin(); it != vertices.end(); ++it )
        {
            it->textureCoordinate.x = ( 1.f - it->textureCoordinate.x );
        }
    }


    // Helper for creating a D3D vertex or index buffer.
    template<typename T>
    static void CreateBuffer(_In_ ID3D11Device* device, T const& data, D3D11_BIND_FLAG bindFlags, _Outptr_ ID3D11Buffer** pBuffer)
    {
        assert( pBuffer != 0 );

        D3D11_BUFFER_DESC bufferDesc = { 0 };

        bufferDesc.ByteWidth = (UINT)data.size() * sizeof(T::value_type);
        bufferDesc.BindFlags = bindFlags;
        bufferDesc.Usage = D3D11_USAGE_DEFAULT;

        D3D11_SUBRESOURCE_DATA dataDesc = { 0 };

        dataDesc.pSysMem = &data.front();

        ThrowIfFailed(
            device->CreateBuffer(&bufferDesc, &dataDesc, pBuffer)
        );

        SetDebugObjectName(*pBuffer, "DirectXTK:GeometricPrimitive");
    }


    // Helper for creating a D3D input layout.
    static void CreateInputLayout(_In_ ID3D11Device* device, IEffect* effect, _Outptr_ ID3D11InputLayout** pInputLayout)
    {
        assert( pInputLayout != 0 );

        void const* shaderByteCode;
        size_t byteCodeLength;

        effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

        ThrowIfFailed(
            device->CreateInputLayout(VertexPositionNormalTexture::InputElements,
                                      VertexPositionNormalTexture::InputElementCount,
                                      shaderByteCode, byteCodeLength,
                                      pInputLayout)
        );

        SetDebugObjectName(*pInputLayout, "DirectXTK:GeometricPrimitive");
    }
}


// Internal GeometricPrimitive implementation class.
class GeometricPrimitive::Impl
{
public:
    void Initialize(_In_ ID3D11DeviceContext* deviceContext, VertexCollection& vertices, IndexCollection& indices, bool rhcoords );

    void Draw(CXMMATRIX world, CXMMATRIX view, CXMMATRIX projection, FXMVECTOR color, _In_opt_ ID3D11ShaderResourceView* texture, bool wireframe );

    void Draw(_In_ IEffect* effect, _In_ ID3D11InputLayout* inputLayout, bool alpha, bool wireframe );

    void CreateInputLayout(_In_ IEffect* effect, _Outptr_ ID3D11InputLayout** inputLayout);

private:
    ComPtr<ID3D11Buffer> mVertexBuffer;
    ComPtr<ID3D11Buffer> mIndexBuffer;

    UINT mIndexCount;

    // Only one of these helpers is allocated per D3D device context, even if there are multiple GeometricPrimitive instances.
    class SharedResources
    {
    public:
        SharedResources(_In_ ID3D11DeviceContext* deviceContext);

        void PrepareForRendering(bool alpha, bool wireframe);

        ComPtr<ID3D11DeviceContext> deviceContext;
        std::unique_ptr<BasicEffect> effect;

        ComPtr<ID3D11InputLayout> inputLayoutTextured;
        ComPtr<ID3D11InputLayout> inputLayoutUntextured;

        std::unique_ptr<CommonStates> stateObjects;
    };


    // Per-device-context data.
    std::shared_ptr<SharedResources> mResources;

    static SharedResourcePool<ID3D11DeviceContext*, SharedResources> sharedResourcesPool;
};


// Global pool of per-device-context GeometricPrimitive resources.
SharedResourcePool<ID3D11DeviceContext*, GeometricPrimitive::Impl::SharedResources> GeometricPrimitive::Impl::sharedResourcesPool;


// Per-device-context constructor.
GeometricPrimitive::Impl::SharedResources::SharedResources(_In_ ID3D11DeviceContext* deviceContext)
  : deviceContext(deviceContext)
{
    ComPtr<ID3D11Device> device;
    deviceContext->GetDevice(&device);

    // Create the BasicEffect.
    effect.reset(new BasicEffect(device.Get()));

    effect->EnableDefaultLighting();

    // Create state objects.
    stateObjects.reset(new CommonStates(device.Get()));

    // Create input layouts.
    effect->SetTextureEnabled(true);
    ::CreateInputLayout(device.Get(), effect.get(), &inputLayoutTextured);

    effect->SetTextureEnabled(false);
    ::CreateInputLayout(device.Get(), effect.get(), &inputLayoutUntextured);
}


// Sets up D3D device state ready for drawing a primitive.
void GeometricPrimitive::Impl::SharedResources::PrepareForRendering(bool alpha, bool wireframe)
{
    // Set the blend and depth stencil state.
    ID3D11BlendState* blendState;
    ID3D11DepthStencilState* depthStencilState;

    if (alpha)
    {
        // Alpha blended rendering.
        blendState = stateObjects->AlphaBlend();
        depthStencilState = stateObjects->DepthRead();
    }
    else
    {
        // Opaque rendering.
        blendState = stateObjects->Opaque();
        depthStencilState = stateObjects->DepthDefault();
    }

    deviceContext->OMSetBlendState(blendState, nullptr, 0xFFFFFFFF);
    deviceContext->OMSetDepthStencilState(depthStencilState, 0);

    // Set the rasterizer state.
    if ( wireframe )
        deviceContext->RSSetState( stateObjects->Wireframe() );
    else
        deviceContext->RSSetState( stateObjects->CullCounterClockwise() );

    ID3D11SamplerState* samplerState = stateObjects->LinearClamp();
         
    deviceContext->PSSetSamplers(0, 1, &samplerState);
}


// Initializes a geometric primitive instance that will draw the specified vertex and index data.
_Use_decl_annotations_
void GeometricPrimitive::Impl::Initialize(ID3D11DeviceContext* deviceContext, VertexCollection& vertices, IndexCollection& indices, bool rhcoords)
{
    if ( !rhcoords )
        ReverseWinding( indices, vertices );

    mResources = sharedResourcesPool.DemandCreate(deviceContext);

    ComPtr<ID3D11Device> device;
    deviceContext->GetDevice(&device);

    CreateBuffer(device.Get(), vertices, D3D11_BIND_VERTEX_BUFFER, &mVertexBuffer);
    CreateBuffer(device.Get(), indices, D3D11_BIND_INDEX_BUFFER, &mIndexBuffer);

    mIndexCount = static_cast<UINT>( indices.size() );
}


// Draws the primitive.
_Use_decl_annotations_
void GeometricPrimitive::Impl::Draw(CXMMATRIX world, CXMMATRIX view, CXMMATRIX projection, FXMVECTOR color,
                                    ID3D11ShaderResourceView* texture, bool wireframe, std::function<void()> setCustomState)
{
    assert( mResources != 0 );
    auto effect = mResources->effect.get();
    assert( effect != 0 );

    ID3D11InputLayout *inputLayout;
    if ( texture )
    {
        effect->SetTextureEnabled(true);
        effect->SetTexture(texture);

        inputLayout = mResources->inputLayoutTextured.Get();
    }
    else
    {
        effect->SetTextureEnabled(false);
        
        inputLayout = mResources->inputLayoutUntextured.Get();
    }

    float alpha = XMVectorGetW(color);

    // Set effect parameters.
    effect->SetWorld(world);
    effect->SetView(view);
    effect->SetProjection(projection);

    effect->SetDiffuseColor(color);
    effect->SetAlpha(alpha);

    Draw( effect, inputLayout, (alpha < 1.f), wireframe, setCustomState );
}


// Draw the primitive using a custom effect.
_Use_decl_annotations_
void GeometricPrimitive::Impl::Draw(IEffect* effect, ID3D11InputLayout* inputLayout, bool alpha, bool wireframe )
{
    assert( mResources != 0 );
    auto deviceContext = mResources->deviceContext.Get();
    assert( deviceContext != 0 );

    // Set state objects.
    mResources->PrepareForRendering(alpha, wireframe);

    // Set input layout.
    assert( inputLayout != 0 );
    deviceContext->IASetInputLayout(inputLayout);

    // Activate our shaders, constant buffers, texture, etc.
    assert(effect != 0);
    effect->Apply(deviceContext);

    // Set the vertex and index buffer.
    auto vertexBuffer = mVertexBuffer.Get();
    UINT vertexStride = sizeof(VertexPositionNormalTexture);
    UINT vertexOffset = 0;

    deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &vertexStride, &vertexOffset);

    deviceContext->IASetIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

    // Draw the primitive.
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    deviceContext->DrawIndexed(mIndexCount, 0, 0);
}


// Create input layout for drawing with a custom effect.
_Use_decl_annotations_
void GeometricPrimitive::Impl::CreateInputLayout( IEffect* effect, ID3D11InputLayout** inputLayout )
{
    assert( effect != 0 );
    assert( inputLayout != 0 );

    assert( mResources != 0 );
    auto deviceContext = mResources->deviceContext.Get();
    assert( deviceContext != 0 );

    ComPtr<ID3D11Device> device;
    deviceContext->GetDevice(&device);

    ::CreateInputLayout( device.Get(), effect, inputLayout );
}


//--------------------------------------------------------------------------------------
// GeometricPrimitive
//--------------------------------------------------------------------------------------

// Constructor.
GeometricPrimitive::GeometricPrimitive()
  : pImpl(new Impl())
{
}


// Destructor.
GeometricPrimitive::~GeometricPrimitive()
{
}


// Public entrypoints.
_Use_decl_annotations_
void GeometricPrimitive::Draw(CXMMATRIX world, CXMMATRIX view, CXMMATRIX projection, FXMVECTOR color, ID3D11ShaderResourceView* texture, bool wireframe )
{
    pImpl->Draw(world, view, projection, color, texture, wireframe );
}


_Use_decl_annotations_
void GeometricPrimitive::Draw(IEffect* effect, ID3D11InputLayout* inputLayout, bool alpha, bool wireframe )
{
    pImpl->Draw(effect, inputLayout, alpha, wireframe );
}


_Use_decl_annotations_
void GeometricPrimitive::CreateInputLayout(IEffect* effect, ID3D11InputLayout** inputLayout )
{
    pImpl->CreateInputLayout(effect, inputLayout);
}


//--------------------------------------------------------------------------------------
// Cube
//--------------------------------------------------------------------------------------

// Creates a cube primitive.
std::unique_ptr<GeometricPrimitive> GeometricPrimitive::CreateCube(_In_ ID3D11DeviceContext* deviceContext, float size, bool rhcoords)
{
    // A cube has six faces, each one pointing in a different direction.
    const int FaceCount = 6;

    static const XMVECTORF32 faceNormals[FaceCount] =
    {
        {  0,  0,  1 },
        {  0,  0, -1 },
        {  1,  0,  0 },
        { -1,  0,  0 },
        {  0,  1,  0 },
        {  0, -1,  0 },
    };

    static const XMVECTORF32 textureCoordinates[4] =
    {
        { 1, 0 },
        { 1, 1 },
        { 0, 1 },
        { 0, 0 },
    };

    VertexCollection vertices;
    IndexCollection indices;

    size /= 2;

    // Create each face in turn.
    for (int i = 0; i < FaceCount; i++)
    {
        XMVECTOR normal = faceNormals[i];

        // Get two vectors perpendicular both to the face normal and to each other.
        XMVECTOR basis = (i >= 4) ? g_XMIdentityR2 : g_XMIdentityR1;

        XMVECTOR side1 = XMVector3Cross(normal, basis);
        XMVECTOR side2 = XMVector3Cross(normal, side1);

        // Six indices (two triangles) per face.
        size_t vbase = vertices.size();
        indices.push_back(vbase + 0);
        indices.push_back(vbase + 1);
        indices.push_back(vbase + 2);

        indices.push_back(vbase + 0);
        indices.push_back(vbase + 2);
        indices.push_back(vbase + 3);

        // Four vertices per face.
        vertices.push_back(VertexPositionNormalTexture((normal - side1 - side2) * size, normal, textureCoordinates[0]));
        vertices.push_back(VertexPositionNormalTexture((normal - side1 + side2) * size, normal, textureCoordinates[1]));
        vertices.push_back(VertexPositionNormalTexture((normal + side1 + side2) * size, normal, textureCoordinates[2]));
        vertices.push_back(VertexPositionNormalTexture((normal + side1 - side2) * size, normal, textureCoordinates[3]));
    }

    // Create the primitive object.
    std::unique_ptr<GeometricPrimitive> primitive(new GeometricPrimitive());
    
    primitive->pImpl->Initialize(deviceContext, vertices, indices, rhcoords);

    return primitive;
}



//--------------------------------------------------------------------------------------
// Sphere
//--------------------------------------------------------------------------------------

// Creates a sphere primitive.
std::unique_ptr<GeometricPrimitive> GeometricPrimitive::CreateSphere(_In_ ID3D11DeviceContext* deviceContext, float diameter, size_t tessellation, bool rhcoords)
{
    VertexCollection vertices;
    IndexCollection indices;

    if (tessellation < 3)
        throw std::out_of_range("tesselation parameter out of range");

    size_t verticalSegments = tessellation;
    size_t horizontalSegments = tessellation * 2;

    float radius = diameter / 2;

    // Create rings of vertices at progressively higher latitudes.
    for (size_t i = 0; i <= verticalSegments; i++)
    {
        float v = 1 - (float)i / verticalSegments;

        float latitude = (i * XM_PI / verticalSegments) - XM_PIDIV2;
        float dy, dxz;

        XMScalarSinCos(&dy, &dxz, latitude);

        // Create a single ring of vertices at this latitude.
        for (size_t j = 0; j <= horizontalSegments; j++)
        {
            float u = (float)j / horizontalSegments;

            float longitude = j * XM_2PI / horizontalSegments;
            float dx, dz;

            XMScalarSinCos(&dx, &dz, longitude);

            dx *= dxz;
            dz *= dxz;

            XMVECTOR normal = XMVectorSet(dx, dy, dz, 0);
            XMVECTOR textureCoordinate = XMVectorSet(u, v, 0, 0);

            vertices.push_back(VertexPositionNormalTexture(normal * radius, normal, textureCoordinate));
        }
    }

    // Fill the index buffer with triangles joining each pair of latitude rings.
    size_t stride = horizontalSegments + 1;

    for (size_t i = 0; i < verticalSegments; i++)
    {
        for (size_t j = 0; j <= horizontalSegments; j++)
        {
            size_t nextI = i + 1;
            size_t nextJ = (j + 1) % stride;

            indices.push_back(i * stride + j);
            indices.push_back(nextI * stride + j);
            indices.push_back(i * stride + nextJ);

            indices.push_back(i * stride + nextJ);
            indices.push_back(nextI * stride + j);
            indices.push_back(nextI * stride + nextJ);
        }
    }

    // Create the primitive object.
    std::unique_ptr<GeometricPrimitive> primitive(new GeometricPrimitive());
    
    primitive->pImpl->Initialize(deviceContext, vertices, indices, rhcoords);

    return primitive;
}


//--------------------------------------------------------------------------------------
// Geodesic sphere
//--------------------------------------------------------------------------------------

// Creates a geosphere primitive.
std::unique_ptr<GeometricPrimitive> GeometricPrimitive::CreateGeoSphere(_In_ ID3D11DeviceContext* deviceContext, float diameter, size_t tessellation, bool rhcoords)
{
    // An undirected edge between two vertices, represented by a pair of indexes into a vertex array.
    // Becuse this edge is undirected, (a,b) is the same as (b,a).
    typedef std::pair<uint16_t, uint16_t> UndirectedEdge;

    // Makes an undirected edge. Rather than overloading comparison operators to give us the (a,b)==(b,a) property,
    // we'll just ensure that the larger of the two goes first. This'll simplify things greatly.
    auto makeUndirectedEdge = [](uint16_t a, uint16_t b)
    {
        return std::make_pair(std::max(a, b), std::min(a, b));
    };

    // Key: an edge
    // Value: the index of the vertex which lies midway between the two vertices pointed to by the key value
    // This map is used to avoid duplicating vertices when subdividing triangles along edges.
    typedef std::map<UndirectedEdge, uint16_t> EdgeSubdivisionMap;


    static const XMFLOAT3 OctahedronVertices[] =
    {
                              // when looking down the negative z-axis (into the screen)
        XMFLOAT3( 0,  1,  0), // 0 top
        XMFLOAT3( 0,  0, -1), // 1 front
        XMFLOAT3( 1,  0,  0), // 2 right
        XMFLOAT3( 0,  0,  1), // 3 back
        XMFLOAT3(-1,  0,  0), // 4 left
        XMFLOAT3( 0, -1,  0), // 5 bottom
    };
    static const uint16_t OctahedronIndices[] =
    {
        0, 1, 2, // top front-right face
        0, 2, 3, // top back-right face
        0, 3, 4, // top back-left face
        0, 4, 1, // top front-left face
        5, 1, 4, // bottom front-left face
        5, 4, 3, // bottom back-left face
        5, 3, 2, // bottom back-right face
        5, 2, 1, // bottom front-right face
    };

    const float radius = diameter / 2.0f;
    
    // Start with an octahedron; copy the data into the vertex/index collection.

    std::vector<XMFLOAT3> vertexPositions(std::begin(OctahedronVertices), std::end(OctahedronVertices));

    IndexCollection indices;
    indices.insert(indices.begin(), std::begin(OctahedronIndices), std::end(OctahedronIndices));

    // We know these values by looking at the above index list for the octahedron. Despite the subdivisions that are
    // about to go on, these values aren't ever going to change because the vertices don't move around in the array.
    // We'll need these values later on to fix the singularities that show up at the poles.
    const uint16_t northPoleIndex = 0;
    const uint16_t southPoleIndex = 5;
    
    for (size_t iSubdivision = 0; iSubdivision < tessellation; ++iSubdivision)
    {
        assert(indices.size() % 3 == 0); // sanity

        // We use this to keep track of which edges have already been subdivided.
        EdgeSubdivisionMap subdividedEdges;

        // The new index collection after subdivision.
        IndexCollection newIndices;

        const size_t triangleCount = indices.size() / 3;
        for (size_t iTriangle = 0; iTriangle < triangleCount; ++iTriangle)
        {
            // For each edge on this triangle, create a new vertex in the middle of that edge.
            // The winding order of the triangles we output are the same as the winding order of the inputs.

            // Indices of the vertices making up this triangle
            uint16_t iv0 = indices[iTriangle*3+0];
            uint16_t iv1 = indices[iTriangle*3+1];
            uint16_t iv2 = indices[iTriangle*3+2];
            
            // The existing vertices
            XMFLOAT3 v0 = vertexPositions[iv0];
            XMFLOAT3 v1 = vertexPositions[iv1];
            XMFLOAT3 v2 = vertexPositions[iv2];

            // Get the new vertices

            XMFLOAT3 v01; // vertex on the midpoint of v0 and v1
            XMFLOAT3 v12; // ditto v1 and v2
            XMFLOAT3 v20; // ditto v2 and v0
            uint16_t iv01; // index of v01
            uint16_t iv12; // index of v12
            uint16_t iv20; // index of v20

            // Function that, when given the index of two vertices, creates a new vertex at the midpoint of those vertices.
            auto divideEdge = [&](uint16_t i0, uint16_t i1, XMFLOAT3& outVertex, uint16_t& outIndex)
            {
                const UndirectedEdge edge = makeUndirectedEdge(i0, i1);

                // Check to see if we've already generated this vertex
                auto it = subdividedEdges.find(edge);
                if (it != subdividedEdges.end())
                {
                    // We've already generated this vertex before
                    outIndex = it->second; // the index of this vertex
                    outVertex = vertexPositions[outIndex]; // and the vertex itself
                }
                else
                {
                    // Haven't generated this vertex before: so add it now

                    // outVertex = (vertices[i0] + vertices[i1]) / 2
                    XMStoreFloat3(
                        &outVertex,
                        XMVectorScale(
                            XMVectorAdd(XMLoadFloat3(&vertexPositions[i0]), XMLoadFloat3(&vertexPositions[i1])),
                            0.5f
                        )
                    );

                    outIndex = static_cast<uint16_t>( vertexPositions.size() );
                    CheckIndexOverflow(outIndex);
                    vertexPositions.push_back(outVertex);

                    // Now add it to the map.
                    subdividedEdges.insert(std::make_pair(edge, outIndex));
                }
            };

            // Add/get new vertices and their indices
            divideEdge(iv0, iv1, v01, iv01);
            divideEdge(iv1, iv2, v12, iv12);
            divideEdge(iv0, iv2, v20, iv20);

            // Add the new indices. We have four new triangles from our original one:
            //        v0
            //        o
            //       /a\
            //  v20 o---o v01
            //     /b\c/d\
            // v2 o---o---o v1
            //       v12
            const uint16_t indicesToAdd[] =
            {
                 iv0, iv01, iv20, // a
                iv20, iv12,  iv2, // b
                iv20, iv01, iv12, // c
                iv01,  iv1, iv12, // d
            };
            newIndices.insert(newIndices.end(), std::begin(indicesToAdd), std::end(indicesToAdd));
        }

        indices = std::move(newIndices);
    }

    // Now that we've completed subdivision, fill in the final vertex collection
    VertexCollection vertices;
    vertices.reserve(vertexPositions.size());
    for (auto it = vertexPositions.begin(); it != vertexPositions.end(); ++it)
    {
        auto vertexValue = *it;

        auto normal = XMVector3Normalize(XMLoadFloat3(&vertexValue));
        auto pos = XMVectorScale(normal, radius);

        XMFLOAT3 normalFloat3;
        XMStoreFloat3(&normalFloat3, normal);

        // calculate texture coordinates for this vertex
        float longitude = atan2(normalFloat3.x, -normalFloat3.z);
        float latitude = acos(normalFloat3.y);

        float u = longitude / XM_2PI + 0.5f;
        float v = latitude / XM_PI;

        auto texcoord = XMVectorSet(1.0f - u, v, 0.0f, 0.0f);
        vertices.push_back(VertexPositionNormalTexture(pos, normal, texcoord));
    }

    // There are a couple of fixes to do. One is a texture coordinate wraparound fixup. At some point, there will be
    // a set of triangles somewhere in the mesh with texture coordinates such that the wraparound across 0.0/1.0
    // occurs across that triangle. Eg. when the left hand side of the triangle has a U coordinate of 0.98 and the
    // right hand side has a U coordinate of 0.0. The intent is that such a triangle should render with a U of 0.98 to
    // 1.0, not 0.98 to 0.0. If we don't do this fixup, there will be a visible seam across one side of the sphere.
    // 
    // Luckily this is relatively easy to fix. There is a straight edge which runs down the prime meridian of the
    // completed sphere. If you imagine the vertices along that edge, they circumscribe a semicircular arc starting at
    // y=1 and ending at y=-1, and sweeping across the range of z=0 to z=1. x stays zero. It's along this edge that we
    // need to duplicate our vertices - and provide the correct texture coordinates.
    size_t preFixupVertexCount = vertices.size();
    for (size_t i = 0; i < preFixupVertexCount; ++i)
    {
        // This vertex is on the prime meridian if position.x and texcoord.u are both zero (allowing for small epsilon).
        bool isOnPrimeMeridian = XMVector2NearEqual(
            XMVectorSet(vertices[i].position.x, vertices[i].textureCoordinate.x, 0.0f, 0.0f),
            XMVectorZero(),
            XMVectorSplatEpsilon());

        if (isOnPrimeMeridian)
        {
            size_t newIndex = vertices.size(); // the index of this vertex that we're about to add
            CheckIndexOverflow(newIndex);

            // copy this vertex, correct the texture coordinate, and add the vertex
            VertexPositionNormalTexture v = vertices[i];
            v.textureCoordinate.x = 1.0f;
            vertices.push_back(v);

            // Now find all the triangles which contain this vertex and update them if necessary
            for (size_t j = 0; j < indices.size(); j += 3)
            {
                uint16_t* triIndex0 = &indices[j+0];
                uint16_t* triIndex1 = &indices[j+1];
                uint16_t* triIndex2 = &indices[j+2];

                if (*triIndex0 == i)
                {
                    // nothing; just keep going
                }
                else if (*triIndex1 == i)
                {
                    std::swap(triIndex0, triIndex1); // swap the pointers (not the values)
                }
                else if (*triIndex2 == i)
                {
                    std::swap(triIndex0, triIndex2); // swap the pointers (not the values)
                }
                else
                {
                    // this triangle doesn't use the vertex we're interested in
                    continue;
                }

                // If we got to this point then triIndex0 is the pointer to the index to the vertex we're looking at
                assert(*triIndex0 == i);
                assert(*triIndex1 != i && *triIndex2 != i); // assume no degenerate triangles
                
                const VertexPositionNormalTexture& v0 = vertices[*triIndex0];
                const VertexPositionNormalTexture& v1 = vertices[*triIndex1];
                const VertexPositionNormalTexture& v2 = vertices[*triIndex2];

                // check the other two vertices to see if we might need to fix this triangle

                if (abs(v0.textureCoordinate.x - v1.textureCoordinate.x) > 0.5f ||
                    abs(v0.textureCoordinate.x - v2.textureCoordinate.x) > 0.5f)
                {
                    // yep; replace the specified index to point to the new, corrected vertex
                    *triIndex0 = static_cast<uint16_t>(newIndex);
                }
            }
        }
    }

    // And one last fix we need to do: the poles. A common use-case of a sphere mesh is to map a rectangular texture onto
    // it. If that happens, then the poles become singularities which map the entire top and bottom rows of the texture
    // onto a single point. In general there's no real way to do that right. But to match the behavior of non-geodesic
    // spheres, we need to duplicate the pole vertex for every triangle that uses it. This will introduce seams near the
    // poles, but reduce stretching.
    auto fixPole = [&](size_t poleIndex)
    {
        auto poleVertex = vertices[poleIndex];
        bool overwrittenPoleVertex = false; // overwriting the original pole vertex saves us one vertex

        for (size_t i = 0; i < indices.size(); i += 3)
        {
            // These pointers point to the three indices which make up this triangle. pPoleIndex is the pointer to the
            // entry in the index array which represents the pole index, and the other two pointers point to the other
            // two indices making up this triangle.
            uint16_t* pPoleIndex;
            uint16_t* pOtherIndex0;
            uint16_t* pOtherIndex1;
            if (indices[i + 0] == poleIndex)
            {
                pPoleIndex = &indices[i + 0];
                pOtherIndex0 = &indices[i + 1];
                pOtherIndex1 = &indices[i + 2];
            }
            else if (indices[i + 1] == poleIndex)
            {
                pPoleIndex = &indices[i + 1];
                pOtherIndex0 = &indices[i + 2];
                pOtherIndex1 = &indices[i + 0];
            }
            else if (indices[i + 2] == poleIndex)
            {
                pPoleIndex = &indices[i + 2];
                pOtherIndex0 = &indices[i + 0];
                pOtherIndex1 = &indices[i + 1];
            }
            else
            {
                continue;
            }

            const auto& otherVertex0 = vertices[*pOtherIndex0];
            const auto& otherVertex1 = vertices[*pOtherIndex1];

            // Calculate the texcoords for the new pole vertex, add it to the vertices and update the index
            VertexPositionNormalTexture newPoleVertex = poleVertex;
            newPoleVertex.textureCoordinate.x = (otherVertex0.textureCoordinate.x + otherVertex1.textureCoordinate.x) / 2;
            newPoleVertex.textureCoordinate.y = poleVertex.textureCoordinate.y;

            if (!overwrittenPoleVertex)
            {
                vertices[poleIndex] = newPoleVertex;
                overwrittenPoleVertex = true;
            }
            else
            {
                CheckIndexOverflow(vertices.size());

                *pPoleIndex = static_cast<uint16_t>(vertices.size());
                vertices.push_back(newPoleVertex);
            }
        }
    };

    fixPole(northPoleIndex);
    fixPole(southPoleIndex);

    // Create the primitive object.
    std::unique_ptr<GeometricPrimitive> primitive(new GeometricPrimitive());
    
    primitive->pImpl->Initialize(deviceContext, vertices, indices, rhcoords);
    return primitive;
}


//--------------------------------------------------------------------------------------
// Cylinder
//--------------------------------------------------------------------------------------

// Helper computes a point on a unit circle, aligned to the x/z plane and centered on the origin.
static XMVECTOR GetCircleVector(size_t i, size_t tessellation)
{
    float angle = i * XM_2PI / tessellation;
    float dx, dz;

    XMScalarSinCos(&dx, &dz, angle);

    return XMVectorPermute<0, 1, 4, 5>(XMLoadFloat(&dx), XMLoadFloat(&dz));
}


// Helper creates a triangle fan to close the end of a cylinder.
static void CreateCylinderCap(VertexCollection& vertices, IndexCollection& indices, size_t tessellation, float height, float radius, bool isTop)
{
    // Create cap indices.
    for (size_t i = 0; i < tessellation - 2; i++)
    {
        size_t i1 = (i + 1) % tessellation;
        size_t i2 = (i + 2) % tessellation;

        if (isTop)
        {
            std::swap(i1, i2);
        }

        size_t vbase = vertices.size();
        indices.push_back(vbase);
        indices.push_back(vbase + i1);
        indices.push_back(vbase + i2);
    }

    // Which end of the cylinder is this?
    XMVECTOR normal = g_XMIdentityR1;
    XMVECTOR textureScale = g_XMNegativeOneHalf;

    if (!isTop)
    {
        normal = -normal;
        textureScale *= g_XMNegateX;
    }

    // Create cap vertices.
    for (size_t i = 0; i < tessellation; i++)
    {
        XMVECTOR circleVector = GetCircleVector(i, tessellation);

        XMVECTOR position = (circleVector * radius) + (normal * height);

        XMVECTOR textureCoordinate = XMVectorMultiplyAdd(XMVectorSwizzle<0, 2, 3, 3>(circleVector), textureScale, g_XMOneHalf);

        vertices.push_back(VertexPositionNormalTexture(position, normal, textureCoordinate));
    }
}


// Creates a cylinder primitive.
std::unique_ptr<GeometricPrimitive> GeometricPrimitive::CreateCylinder(_In_ ID3D11DeviceContext* deviceContext, float height, float diameter, size_t tessellation, bool rhcoords)
{
    VertexCollection vertices;
    IndexCollection indices;

    if (tessellation < 3)
        throw std::out_of_range("tesselation parameter out of range");

    height /= 2;

    XMVECTOR topOffset = g_XMIdentityR1 * height;

    float radius = diameter / 2;
    size_t stride = tessellation + 1;

    // Create a ring of triangles around the outside of the cylinder.
    for (size_t i = 0; i <= tessellation; i++)
    {
        XMVECTOR normal = GetCircleVector(i, tessellation);

        XMVECTOR sideOffset = normal * radius;

        float u = (float)i / tessellation;

        XMVECTOR textureCoordinate = XMLoadFloat(&u);

        vertices.push_back(VertexPositionNormalTexture(sideOffset + topOffset, normal, textureCoordinate));
        vertices.push_back(VertexPositionNormalTexture(sideOffset - topOffset, normal, textureCoordinate + g_XMIdentityR1));

        indices.push_back(i * 2);
        indices.push_back((i * 2 + 2) % (stride * 2));
        indices.push_back(i * 2 + 1);

        indices.push_back(i * 2 + 1);
        indices.push_back((i * 2 + 2) % (stride * 2));
        indices.push_back((i * 2 + 3) % (stride * 2));
    }

    // Create flat triangle fan caps to seal the top and bottom.
    CreateCylinderCap(vertices, indices, tessellation, height, radius, true);
    CreateCylinderCap(vertices, indices, tessellation, height, radius, false);

    // Create the primitive object.
    std::unique_ptr<GeometricPrimitive> primitive(new GeometricPrimitive());
    
    primitive->pImpl->Initialize(deviceContext, vertices, indices, rhcoords);

    return primitive;
}


//--------------------------------------------------------------------------------------
// Torus
//--------------------------------------------------------------------------------------

// Creates a torus primitive.
std::unique_ptr<GeometricPrimitive> GeometricPrimitive::CreateTorus(_In_ ID3D11DeviceContext* deviceContext, float diameter, float thickness, size_t tessellation, bool rhcoords)
{
    VertexCollection vertices;
    IndexCollection indices;

    if (tessellation < 3)
        throw std::out_of_range("tesselation parameter out of range");

    size_t stride = tessellation + 1;

    // First we loop around the main ring of the torus.
    for (size_t i = 0; i <= tessellation; i++)
    {
        float u = (float)i / tessellation;

        float outerAngle = i * XM_2PI / tessellation - XM_PIDIV2;

        // Create a transform matrix that will align geometry to
        // slice perpendicularly though the current ring position.
        XMMATRIX transform = XMMatrixTranslation(diameter / 2, 0, 0) * XMMatrixRotationY(outerAngle);

        // Now we loop along the other axis, around the side of the tube.
        for (size_t j = 0; j <= tessellation; j++)
        {
            float v = 1 - (float)j / tessellation;

            float innerAngle = j * XM_2PI / tessellation + XM_PI;
            float dx, dy;

            XMScalarSinCos(&dy, &dx, innerAngle);

            // Create a vertex.
            XMVECTOR normal = XMVectorSet(dx, dy, 0, 0);
            XMVECTOR position = normal * thickness / 2;
            XMVECTOR textureCoordinate = XMVectorSet(u, v, 0, 0);

            position = XMVector3Transform(position, transform);
            normal = XMVector3TransformNormal(normal, transform);

            vertices.push_back(VertexPositionNormalTexture(position, normal, textureCoordinate));

            // And create indices for two triangles.
            size_t nextI = (i + 1) % stride;
            size_t nextJ = (j + 1) % stride;

            indices.push_back(i * stride + j);
            indices.push_back(i * stride + nextJ);
            indices.push_back(nextI * stride + j);

            indices.push_back(i * stride + nextJ);
            indices.push_back(nextI * stride + nextJ);
            indices.push_back(nextI * stride + j);
        }
    }

    // Create the primitive object.
    std::unique_ptr<GeometricPrimitive> primitive(new GeometricPrimitive());
    
    primitive->pImpl->Initialize(deviceContext, vertices, indices, rhcoords);

    return primitive;
}


//--------------------------------------------------------------------------------------
// Teapot
//--------------------------------------------------------------------------------------

// Include the teapot control point data.
namespace
{
    #include "TeapotData.inc"
}


// Tessellates the specified bezier patch.
static void TessellatePatch(VertexCollection& vertices, IndexCollection& indices, TeapotPatch const& patch, size_t tessellation, FXMVECTOR scale, bool isMirrored)
{
    // Look up the 16 control points for this patch.
    XMVECTOR controlPoints[16];

    for (int i = 0; i < 16; i++)
    {
        controlPoints[i] = TeapotControlPoints[patch.indices[i]] * scale;
    }

    // Create the index data.
    size_t vbase = vertices.size();
    Bezier::CreatePatchIndices(tessellation, isMirrored, [&](size_t index)
    {
        indices.push_back(vbase + index);
    });

    // Create the vertex data.
    Bezier::CreatePatchVertices(controlPoints, tessellation, isMirrored, [&](FXMVECTOR position, FXMVECTOR normal, FXMVECTOR textureCoordinate)
    {
        vertices.push_back(VertexPositionNormalTexture(position, normal, textureCoordinate));
    });
}


#endif

