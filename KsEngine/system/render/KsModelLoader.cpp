/************************************************************************************************/
/** 
 * @file		KsModelLoader.h
 * @brief		モデルローダー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsModelLoader.h"
#include "KsVertexBufferDX.h"
#include "KsIndexBufferDX.h"
#include "KsHierarchy.h"



// ----------------------------------------------------------------------------
// シェーダー
// ----------------------------------------------------------------------------
// v0 = 頂点の位置
// v1 = 重み
// v2 = 重みのインデックス
// v3 = 法線
// v4 = テクスチャー座標
//------------------------------------------------------------------------------
// r0.w = Last blend weight
// r1 = 重みのインデックス
// r2 = 一時的な座標
// r3 = 一時的な法線
// r4 = カメラ空間での座標
// r5 = カメラ空間での法線
//------------------------------------------------------------------------------
// c9-c95 = 行列パレット
// c8	  = 平行光源
// c7	  = 環境光
// c2-c5  = 射影行列
// c1	  = 光源方向
// c0	  = {1, ライトのべき乗, 0, 1020.01};
//------------------------------------------------------------------------------
// oPos	  = 位置
// oD0	  = 平行光
// oD1	  = すぺきゅらー
// oT0	  = テクスチャー座標
//------------------------------------------------------------------------------

const char VertexShader0[] = {
"vs.1.1                            // シェーダ バージョン 1.1           \n"\
"mul r1,v2.zyxw,c0.wwww            // Geforce3 で UBYTE4 がないのを補う \n"\

"mov a0.x,r1.x                     // 1 つめの行列を設定                \n"\
"m4x3 r4,v0,c[a0.x + 9]                                                 \n"\
"m3x3 r5,v3,c[a0.x + 9]                                                 \n"\

"mov r4.w,c0.x                     // 座標変換                          \n"\
"m4x4 oPos,r4,c2                                                        \n"\

"dp3 r5.w, r5, r5                  // 法線の規格化                      \n"\
"rsq r5.w, r5.w                                                         \n"\
"mul r5, r5, r5.w                                                       \n"\

"dp3 r1.x, r5, c1                  // ライティング                      \n"\
"lit r1, r1                        //                                   \n"\
"mul r0, r1.y, c8                  // 平行光源                          \n"\
"add r0, r0, c7                    //  +環境光                          \n"\
"min oD0, r0, c0.x                 // 1以下にクランプ                   \n"\
"mov oD1, c0.zzzz                  // すぺきゅらーの設定                \n"\

"mov oT0, v4                       // テクスチャー座標のコピー          "
};
// ----------------------------------------------------------------------------
const char VertexShader1[] = {
"vs.1.1                            // シェーダ バージョン 1.1           \n"\
"mul r1,v2.zyxw,c0.wwww            // Geforce3 で UBYTE4 がないのを補う \n"\

"dp3 r0.w,v1.xyz,c0.xzz            // 最後の係数はウェイトの合計が1から算出 \n"\
"add r0.w,-r0.w,c0.x                                                    \n"\

"mov a0.x,r1.x                     // 1 つめの行列を設定                \n"\
"m4x3 r4,v0,c[a0.x + 9]                                                 \n"\
"m3x3 r5,v3,c[a0.x + 9]                                                 \n"\
"mul r4,r4,v1.xxxx                 // 係数をかけて合成する              \n"\
"mul r5,r5,v1.xxxx                                                      \n"\

"mov a0.x,r1.y                     // 2 つめの行列を設定                \n"\
"m4x3 r2,v0,c[a0.x + 9]                                                 \n"\
"m3x3 r3,v3,c[a0.x + 9]                                                 \n"\
"mad r4,r2,r0.wwww,r4              // 係数をかけて合成する              \n"\
"mad r5,r3,r0.wwww,r5                                                   \n"\

"mov r4.w,c0.x                     // 座標変換                          \n"\
"m4x4 oPos,r4,c2                                                        \n"\

"dp3 r5.w, r5, r5                  // 法線の規格化                      \n"\
"rsq r5.w, r5.w                                                         \n"\
"mul r5, r5, r5.w                                                       \n"\

"dp3 r1.x, r5, c1                  // ライティング                      \n"\
"lit r1, r1                        //                                   \n"\
"mul r0, r1.y, c8                  // 平行光源                          \n"\
"add r0, r0, c7                    //  +環境光                          \n"\
"min oD0, r0, c0.x                 // 1以下にクランプ                   \n"\
"mov oD1, c0.zzzz                  // すぺきゅらーの設定                \n"\

"mov oT0, v4                       // テクスチャー座標のコピー          "
};
// ----------------------------------------------------------------------------
const char VertexShader2[] = {
"vs.1.1                            // シェーダ バージョン 1.1           \n"\
"mul r1,v2.zyxw,c0.wwww            // Geforce3 で UBYTE4 がないのを補う \n"\

"dp3 r0.w,v1.xyz,c0.xxz            // 最後の係数はウェイトの合計が1から算出 \n"\
"add r0.w,-r0.w,c0.x                                                    \n"\

"mov a0.x,r1.x                     // 1 つめの行列を設定                \n"\
"m4x3 r4,v0,c[a0.x + 9]                                                 \n"\
"m3x3 r5,v3,c[a0.x + 9]                                                 \n"\
"mul r4,r4,v1.xxxx                 // 係数をかけて合成する              \n"\
"mul r5,r5,v1.xxxx                                                      \n"\

"mov a0.x,r1.y                     // 2 つめの行列を設定                \n"\
"m4x3 r2,v0,c[a0.x + 9]                                                 \n"\
"m3x3 r3,v3,c[a0.x + 9]                                                 \n"\
"mad r4,r2,v1.yyyy,r4              // 係数をかけて合成する              \n"\
"mad r5,r3,v1.yyyy,r5                                                   \n"\

"mov a0.x,r1.z                     // 3 つめの行列を設定                \n"\
"m4x3 r2,v0,c[a0.x + 9]                                                 \n"\
"m3x3 r3,v3,c[a0.x + 9]                                                 \n"\
"mad r4,r2,r0.wwww,r4              // 係数をかけて合成する              \n"\
"mad r5,r3,r0.wwww,r5                                                   \n"\

"mov r4.w,c0.x                     // 座標変換                          \n"\
"m4x4 oPos,r4,c2                                                        \n"\

"dp3 r5.w, r5, r5                  // 法線の規格化                      \n"\
"rsq r5.w, r5.w                                                         \n"\
"mul r5, r5, r5.w                                                       \n"\

"dp3 r1.x, r5, c1                  // ライティング                      \n"\
"lit r1, r1                        //                                   \n"\
"mul r0, r1.y, c8                  // 平行光源                          \n"\
"add r0, r0, c7                    //  +環境光                          \n"\
"min oD0, r0, c0.x                 // 1以下にクランプ                   \n"\
"mov oD1, c0.zzzz                  // すぺきゅらーの設定                \n"\

"mov oT0, v4                       // テクスチャー座標のコピー          "
};
// ----------------------------------------------------------------------------
const char VertexShader3[] = {
"vs.1.1                            // シェーダ バージョン 1.1           \n"\
"mul r1,v2.zyxw,c0.wwww            // Geforce3 で UBYTE4 がないのを補う \n"\

"dp3 r0.w,v1.xyz,c0.xxx            // 最後の係数はウェイトの合計が1から算出 \n"\
"add r0.w,-r0.w,c0.x                                                    \n"\

"mov a0.x,r1.x                     // 1 つめの行列を設定                \n"\
"m4x3 r4,v0,c[a0.x + 9]                                                 \n"\
"m3x3 r5,v3,c[a0.x + 9]                                                 \n"\
"mul r4,r4,v1.xxxx                 // 係数をかけて合成する              \n"\
"mul r5,r5,v1.xxxx                                                      \n"\

"mov a0.x,r1.y                     // 2 つめの行列を設定                \n"\
"m4x3 r2,v0,c[a0.x + 9]                                                 \n"\
"m3x3 r3,v3,c[a0.x + 9]                                                 \n"\
"mad r4,r2,v1.yyyy,r4              // 係数をかけて合成する              \n"\
"mad r5,r3,v1.yyyy,r5                                                   \n"\

"mov a0.x,r1.z                     // 3 つめの行列を設定                \n"\
"m4x3 r2,v0,c[a0.x + 9]                                                 \n"\
"m3x3 r3,v3,c[a0.x + 9]                                                 \n"\
"mad r4,r2,v1.zzzz,r4              // 係数をかけて合成する              \n"\
"mad r5,r3,v1.zzzz,r5                                                   \n"\

"mov a0.x,r1.w                     // 4 つめの行列を設定                \n"\
"m4x3 r2,v0,c[a0.x + 9]                                                 \n"\
"m3x3 r3,v3,c[a0.x + 9]                                                 \n"\
"mad r4,r2,r0.wwww,r4              // 係数をかけて合成する              \n"\
"mad r5,r3,r0.wwww,r5                                                   \n"\

"mov r4.w,c0.x                     // 座標変換                          \n"\
"m4x4 oPos,r4,c2                                                        \n"\

"dp3 r5.w, r5, r5                  // 法線の規格化                      \n"\
"rsq r5.w, r5.w                                                         \n"\
"mul r5, r5, r5.w                                                       \n"\

"dp3 r1.x, r5, c1                  // ライティング                      \n"\
"lit r1, r1                        //                                   \n"\
"mul r0, r1.y, c8                  // 平行光源                          \n"\
"add r0, r0, c7                    //  +環境光                          \n"\
"min oD0, r0, c0.x                 // 1以下にクランプ                   \n"\
"mov oD1, c0.zzzz                  // すぺきゅらーの設定                \n"\

"mov oT0, v4                       // テクスチャー座標のコピー          "
};

//-----------------------------------------------------------------------------
// 頂点シェーダーの生成
//-----------------------------------------------------------------------------
HRESULT CreateVertexShader( KsRenderSystemDX* pRS )
{
#if 0
	LPD3DXBUFFER pCode;
	HRESULT hr;
	
	// インデックススキニングのための頂点シェーダーの生成
	DWORD dwIndexedVertexDecl1[] = {
		D3DVSD_STREAM( 0 ),
		D3DVSD_REG( 0, D3DVSDT_FLOAT3 ),	// Position of first mesh
		D3DVSD_REG( 2, D3DVSDT_D3DCOLOR ),	// 合成する行列の指定
		D3DVSD_REG( 3, D3DVSDT_FLOAT3 ),	// 法線
		D3DVSD_REG( 4, D3DVSDT_FLOAT2 ),	// テクスチャー座標
		D3DVSD_END()
	};

	DWORD dwIndexedVertexDecl2[] = {
		D3DVSD_STREAM( 0 ),
		D3DVSD_REG( 0, D3DVSDT_FLOAT3 ),	// Position of first mesh
		D3DVSD_REG( 1, D3DVSDT_FLOAT1 ),	// 合成の重み
		D3DVSD_REG( 2, D3DVSDT_D3DCOLOR ),	// 合成する行列の指定
		D3DVSD_REG( 3, D3DVSDT_FLOAT3 ),	// 法線
		D3DVSD_REG( 4, D3DVSDT_FLOAT2 ),	// テクスチャー座標
		D3DVSD_END()
	};

	DWORD dwIndexedVertexDecl3[] =  {
		D3DVSD_STREAM( 0 ),
		D3DVSD_REG( 0, D3DVSDT_FLOAT3 ),	// Position of first mesh
		D3DVSD_REG( 1, D3DVSDT_FLOAT2 ),	// 合成の重み
		D3DVSD_REG( 2, D3DVSDT_D3DCOLOR ),	// 合成する行列の指定
		D3DVSD_REG( 3, D3DVSDT_FLOAT3 ),	// 法線
		D3DVSD_REG( 4, D3DVSDT_FLOAT2 ),	// テクスチャー座標
		D3DVSD_END()
	};

	DWORD dwIndexedVertexDecl4[] =  {
		D3DVSD_STREAM( 0 ),
		D3DVSD_REG( 0, D3DVSDT_FLOAT3 ),	// Position of first mesh
		D3DVSD_REG( 1, D3DVSDT_FLOAT3 ),	// 合成の重み
		D3DVSD_REG( 2, D3DVSDT_D3DCOLOR ),	// 合成する行列の指定
		D3DVSD_REG( 3, D3DVSDT_FLOAT3 ),	// 法線
		D3DVSD_REG( 4, D3DVSDT_FLOAT2 ),	// テクスチャー座標
		D3DVSD_END()
	};

	DWORD* dwIndexedVertexDecl[] = {
		dwIndexedVertexDecl1,
		dwIndexedVertexDecl2,
		dwIndexedVertexDecl3,
		dwIndexedVertexDecl4,
	};

	const char *shader_program[] = {
		VertexShader0,
		VertexShader1,
		VertexShader2,
		VertexShader3,
	};
	const int size[] = {
		sizeof(VertexShader0)-1,
		sizeof(VertexShader1)-1,
		sizeof(VertexShader2)-1,
		sizeof(VertexShader3)-1,
	};


	// アドレス レジスタが使えないならソフトウェアT&L
	DWORD bUseSW = (m_d3dCaps.VertexShaderVersion < D3DVS_VERSION(1, 1));

	for (DWORD i = 0; i < 4; ++i)  {
		// シェーダープログラムの読み込み
		if ( FAILED(hr = D3DXAssembleShader( shader_program[i] , size[i], 0 , NULL , &pCode , NULL)) ) return hr;

		// 頂点シェーダーの生成
		if( FAILED( hr = pRS->m_pD3DDev->CreateVertexShader( dwIndexedVertexDecl[i], 
											 (DWORD*)pCode->GetBufferPointer(),
											 &(m_dwIndexedVertexShader[i]) , bUseSW ? D3DUSAGE_SOFTWAREPROCESSING : 0 ) ) )
			return hr;

		pCode->Release();
	}
#endif
	return S_OK;
}

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
#define ksD3D_FVF_VERTEX_PNC	( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE )

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
typedef struct _KS_D3D_VERTEX_PNC
{
	KsReal			 x,  y,  z;
	KsReal			nx, ny, nz;
	DWORD			color;
}KS_D3D_VERTEX_PNC;


#define ksD3D_FVF_VERTEX_PNCT	( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

typedef struct _KS_D3D_VERTEX_PNCT
{
	KsReal			 x,  y,  z;
	KsReal			nx, ny, nz;
	DWORD			color;
	KsReal			tu, tv;
}KS_D3D_VERTEX_PNCT;

typedef struct _KS_D3D_VERTEX_PNT
{
	KsReal			 x,  y,  z;
	KsReal			nx, ny, nz;
	KsReal			tu, tv;
}KS_D3D_VERTEX_PNT;

typedef struct _KS_D3D_VERTEX_PWNCT
{
	KsReal			 x,  y,  z;
	KsReal			w1, w2, w3;
    DWORD			mi;
	KsReal			nx, ny, nz;
	DWORD			color;
	KsReal			tu, tv;
}KS_D3D_VERTEX_PWNCT;

#define ksD3D_FVF_VERTEX_PWNCT	( D3DFVF_XYZB4 | D3DFVF_LASTBETA_UBYTE4 | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

typedef struct _KS_D3D_VERTEX_PWNT
{
	KsReal			 x,  y,  z;
	KsReal			w1, w2, w3;
    DWORD			matrixIndices;
	KsReal			nx, ny, nz;
	KsReal			tu, tv;
}KS_D3D_VERTEX_PWNT;


//SetRenderState(D3DRS_INDEXEDVERTEXBLENDENABLE, TRUE );//インデックス付き頂点ブレンディングを有効
//->SetRenderState(D3DRS_VERTEXBLEND, D3DVBF_3WEIGHTS );  //ブレンディングの値を一つに設定
//SetTransform(D3DTS_WORLDMATRIX(0), &matBone0);

LPDIRECT3DTEXTURE9	pTexture;

KsMesh* KsModelLoadDX( KsRenderSystemDX* pRS, KsChar* pFileName )
{
	if( D3D_OK == D3DXCreateTextureFromFile( pRS->m_pD3DDevice, "juri_tex02.png", &pTexture ) ){
		//pRS->m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		//pRS->m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);

		//pRS->m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		//pRS->m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		//pRS->m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE); 
		pRS->m_pD3DDevice->SetTexture( 0, pTexture );
	}

	pRS->m_pD3DDevice->SetRenderState(D3DRS_INDEXEDVERTEXBLENDENABLE, TRUE );//インデックス付き頂点ブレンディングを有効
	pRS->m_pD3DDevice->SetRenderState(D3DRS_VERTEXBLEND, D3DVBF_3WEIGHTS ); 


	KS_KMD_FILE_HEADER		header;
	KS_KMD_MESH				mesh;
	KS_KMD_SUBMESH			subMesh;
	KS_KMD_HIERARCHY_NODE	node;
	KsMesh*					pMesh;
	KsHierarchy*			pHierarchy;
	FILE*					fp;
	
	fp = fopen( pFileName, "rb" );

	FILE*		fpp;

	fpp = fopen( "test.txt", "wt" );

	/* ファイルヘッダー読み込み */
	fread( &header, sizeof( KS_KMD_FILE_HEADER ), 1, fp );

	/* メッシュ情報取得 */
	fread( &mesh, sizeof( KS_KMD_MESH ), 1, fp );

	pMesh      = new KsMesh();
	pHierarchy = new KsHierarchy();

	//----------------------------------------------------------------
	/* 階層情報を取得する */
	for( KsUInt32 i=0; i<mesh.numHierarchyNode; i++ )
	{
		KsJoint*	pJoint = new KsJoint();

		fread( &node, sizeof( KS_KMD_HIERARCHY_NODE ), 1, fp );

		pJoint->m_initPivot.x     = node.pivot.x;
		pJoint->m_initPivot.y     = node.pivot.y;
		pJoint->m_initPivot.z     = node.pivot.z;
		pJoint->m_initTranslate.x = node.translate.x;
		pJoint->m_initTranslate.y = node.translate.y;
		pJoint->m_initTranslate.z = node.translate.z;
		pJoint->m_initRotate.x    = node.rotate.x;
		pJoint->m_initRotate.y    = node.rotate.y;
		pJoint->m_initRotate.z    = node.rotate.z;
		pJoint->m_initRotate.w    = node.rotate.w;
		pJoint->m_initScale.x     = node.scale.x;
		pJoint->m_initScale.y     = node.scale.y;
		pJoint->m_initScale.z     = node.scale.z;
		pJoint->m_pivot.x         = node.pivot.x;
		pJoint->m_pivot.y         = node.pivot.y;
		pJoint->m_pivot.z         = node.pivot.z;
		pJoint->m_translate.x     = node.translate.x;
		pJoint->m_translate.y     = node.translate.y;
		pJoint->m_translate.z     = node.translate.z;
		pJoint->m_rotate.x        = node.rotate.x;
		pJoint->m_rotate.y        = node.rotate.y;
		pJoint->m_rotate.z        = node.rotate.z;
		pJoint->m_rotate.w        = node.rotate.w;
		pJoint->m_scale.x         = node.scale.x;
		pJoint->m_scale.y         = node.scale.y;
		pJoint->m_scale.z         = node.scale.z;
		pJoint->m_id              = node.id;
		pJoint->m_flags           = node.flags;
		pJoint->m_parent          = node.parent;
		pJoint->m_target          = node.objLink;
	
		/* 子供の情報を取得する */
		for( KsUInt32 j=0; j<node.numChild; j++ ){
			KsInt32	childID;
			fread( &childID, sizeof( KsInt32 ), 1, fp );
			pJoint->m_children.push_back( childID );
		}

		pHierarchy->m_pJointList.push_back( pJoint );

		if( pJoint->m_parent == -1 ){
			pHierarchy->m_pRootJointList.push_back( pJoint );
		}
	}

	pMesh->m_pHierarchy = pHierarchy;
	//----------------------------------------------------------------

	/* サブメッシュ */
	for( KsUInt32 i=0; i<mesh.numSubMesh; i++ )
	{
		KsSubMesh*				pSubMesh;
		KS_KMD_VERTEX*			pVertex;
		KS_KMD_FACE*			pFace;
		KS_KMD_FACE_LIST*		pFaceList;
		KS_KMD_BONEWEIGHT*		pWeight;
		KsVertexBuffer*			pVB;
		KsIndexBuffer*			pIB;
		KsVertexData*			pVD;
		KsIndexData*			pID;

		/* サブメッシュの情報部取得 */
		fread( &subMesh, sizeof( KS_KMD_SUBMESH ), 1, fp );

		pSubMesh  = new KsSubMesh();
		pVertex   = new KS_KMD_VERTEX[ subMesh.numVertex ];
		pFace     = new KS_KMD_FACE[ subMesh.numFace ];
		pFaceList = new KS_KMD_FACE_LIST[ subMesh.numFaceList ];
		pWeight   = new KS_KMD_BONEWEIGHT[ subMesh.numBoneWeight ];
		pVD       = new KsVertexData();
		pID       = new KsIndexData();
		
		/* 頂点読み込み */
		fread( pVertex, sizeof( KS_KMD_VERTEX ), subMesh.numVertex, fp );
	
		/* 面情報読み込み */		
		fread( pFace, sizeof( KS_KMD_FACE ), subMesh.numFace, fp );

		/* 面構成情報読み込み */		
		fread( pFaceList, sizeof( KS_KMD_FACE_LIST ), subMesh.numFaceList, fp );

		/* ボーンのウエイト情報読み込み */
		for( KsUInt32 j=0; j<subMesh.numBoneWeight; j++ ){
			fread( &pWeight[ j ], sizeof( KS_KMD_BONE_DATA ), 1, fp );
			fread( pWeight[ j ].weight, sizeof( KS_KMD_WEIGHT ), pWeight[ j ].numWeight, fp );
		}
		
		pVB = new KsVertexBufferDX( pRS->m_pD3DDevice, sizeof(KS_D3D_VERTEX_PWNCT), subMesh.numVertex, ksD3D_FVF_VERTEX_PWNCT );
		pIB = new KsIndexBufferDX( pRS->m_pD3DDevice, subMesh.numFace*3 );

		KS_D3D_VERTEX_PWNCT*	pv = (KS_D3D_VERTEX_PWNCT*)pVB->lock( 0, subMesh.numVertex, D3DLOCK_DISCARD );

		for( KsUInt32 j=0; j<subMesh.numVertex; j++ ){
			pv[ j ].x     = pVertex[ j ].pos.x;
			pv[ j ].y     = pVertex[ j ].pos.y;
			pv[ j ].z     = pVertex[ j ].pos.z;
			pv[ j ].mi    = 0;
			pv[ j ].w1    = 0.0f;
			pv[ j ].w2    = 0.0f;
			pv[ j ].w3    = 0.0f;
			pv[ j ].nx    = pVertex[ j ].normal.x;
			pv[ j ].ny    = pVertex[ j ].normal.y;
			pv[ j ].nz    = pVertex[ j ].normal.z;
			pv[ j ].tu    = pVertex[ j ].uv.x;
			pv[ j ].tv    = pVertex[ j ].uv.y;
			pv[ j ].color = 0xffffffff;//pVertex[ j ].color;
		}
#if 1
		// ボーンの頂点インデックスをセットする
		for( KsUInt32 j=0; j<subMesh.numBoneWeight; j++ ){
			KsUInt32		index=0;
			
			fprintf( fpp, "[vertex Index %04d]", pWeight[ j ].vertexIndex );

			//for( KsInt32 n=0; n<pWeight[ j ].numWeight; n++ ){
			for( KsInt32 n=0; n<4; n++ )
			{
				if( n < pWeight[ j ].numWeight ){
					index |= ( pWeight[ j ].weight[ n ].index << (8*n));
					
					switch( n )
					{
						case 0: pv[ pWeight[ j ].vertexIndex ].w1 = pWeight[ j ].weight[ n ].weight; break;
						case 1: pv[ pWeight[ j ].vertexIndex ].w2 = pWeight[ j ].weight[ n ].weight; break;
						case 2: pv[ pWeight[ j ].vertexIndex ].w3 = pWeight[ j ].weight[ n ].weight; break;
						default: break;
					}
					fprintf( fpp, " %d(%f)", pWeight[ j ].weight[ n ].index, pWeight[ j ].weight[ n ].weight );
				}
				else{
					index |= (0x40 << (8*n));
					switch( n )
					{
						case 0: pv[ pWeight[ j ].vertexIndex ].w1 = 0.0f; break;
						case 1: pv[ pWeight[ j ].vertexIndex ].w2 = 0.0f; break;
						case 2: pv[ pWeight[ j ].vertexIndex ].w3 = 0.0f; break;
						default: break;
					}
					fprintf( fpp, " 0x20(0.0f)" );
				}
				
				//if( !pWeight[ j ].numWeight ){
				//	index = subMesh.id;
				//	pv[ pWeight[ j ].vertexIndex ].w1 = 1.0f;
				//}
				
			}

			if( !pWeight[ j ].numWeight ){
				pv[ pWeight[ j ].vertexIndex ].w1 = 1.0f;
				index = 0x00000040;
			}

			pv[ pWeight[ j ].vertexIndex ].mi = index;

			fprintf( fpp, "    0x%08x\n", index );
		}
#endif
		pVB->unlock();

		//pIB->write( pFace, 0, subMesh.numFace*3 );
		
		KsUInt16*	pi = (KsUInt16*)pIB->lock( 0, subMesh.numFace*3, D3DLOCK_DISCARD );

		for( KsUInt32 j=0; j<subMesh.numFace; j++ ){
			pi[ 0 ] = pFace[ j ].point[ 0 ];
			pi[ 1 ] = pFace[ j ].point[ 1 ];
			pi[ 2 ] = pFace[ j ].point[ 2 ];
			pi+=3;
		}

		pIB->unlock();

		pVD->m_pVertexBuffer = pVB;
		pID->m_pIndexBuffer  = pIB;

		pSubMesh->m_numVertex   = subMesh.numVertex;
		pSubMesh->m_numIndex    = subMesh.numFace * 3;
		pSubMesh->m_numFaceList = subMesh.numFaceList;
		pSubMesh->m_pVertices   = pVD;
		pSubMesh->m_pIndices    = pID;
		pSubMesh->m_pFaceList   = (KsFaceList*)pFaceList;

		pMesh->m_pSubMeshList.push_back( pSubMesh );

		delete [] pVertex;
		delete [] pFace;
		delete [] pWeight;
	}

	for( KsUInt32 i=0; i<mesh.numMaterial; i++ ){
		KS_KMD_MATERIAL		material;
		fread( &material, sizeof( KS_KMD_MATERIAL ), 1, fp );
		KsMaterial*		pMaterial = new KsMaterial();
		pMaterial->m_diffuse.set( material.diffuse.r, material.diffuse.g, material.diffuse.b, material.diffuse.a );
		pMaterial->m_ambient.set( material.ambient.r, material.ambient.g, material.ambient.b, material.ambient.a );
		pMaterial->m_emissive.set( material.emissive.r, material.emissive.g, material.emissive.b, material.emissive.a );
		pMaterial->m_specular.set( material.specular.r, material.specular.g, material.specular.b, material.specular.a );
		pMaterial->setPower( material.power );

		pMesh->m_pMaterialList.push_back( pMaterial );
	}

	fclose( fp );

	fclose( fpp );

	return pMesh;
}




void KsModelRenderDX( KsRenderSystemDX* pRS, KsMesh* pMesh, KsJoint* pJoint, KsJoint* pParent=NULL )
{
	KsUInt32		target = pJoint->m_target;

	KsMatrix		trans;
	KsMatrix		rot;
	
	//if( pJoint->m_id != 0 ){
	trans.setTranslate( pJoint->m_translate.x, pJoint->m_translate.y, pJoint->m_translate.z );
	
	if( pJoint->m_id == 0 ){
		trans.setTranslate( 1.0f, 0.0f, 0.0f );
	}

	rot = pJoint->m_rotate.convertToMatrix();
	//}

	//pJoint->m_localMatrix = trans * rot;
	pJoint->m_localMatrix = rot * trans;

	if( pParent ){
		pJoint->m_worldMatrix = pJoint->m_localMatrix * pParent->m_worldMatrix;
		//pJoint->m_worldMatrix = pParent->m_worldMatrix * pJoint->m_localMatrix;
	}
	else{
		pJoint->m_worldMatrix = pJoint->m_localMatrix;
	}

	KsMatrix	mat = pJoint->m_worldMatrix;
	//KsMatrix	mat = pJoint->m_localMatrix;

	KsMatrix		initMat;
	//pRS->m_pD3DDevice->SetTransform( D3DTS_WORLDMATRIX( 0x40 ), (D3DXMATRIX*)&initMat );

	if( pJoint->m_id == 0 ){
	pRS->m_pD3DDevice->SetTransform( D3DTS_WORLDMATRIX( 0x40 ), (D3DXMATRIX*)&pJoint->m_worldMatrix );
	}
	//pRS->m_pD3DDevice->SetTransform( D3DTS_WORLDMATRIX( pJoint->m_id ), (D3DXMATRIX*)&mat );

	if( pJoint->m_id == 1 ){
		pRS->m_pD3DDevice->SetTransform( D3DTS_WORLDMATRIX( 1 ), (D3DXMATRIX*)&mat );
	}

	if( pJoint->m_id == 2 ){
		pRS->m_pD3DDevice->SetTransform( D3DTS_WORLDMATRIX( 2 ), (D3DXMATRIX*)&mat );
	}

	//pRS->m_pD3DDevice->MultiplyTransform( D3DTS_WORLDMATRIX( pJoint->m_id ), (D3DXMATRIX*)&mat );

	/* 子供へ */
	for( KsUInt32 i=0; i<pJoint->m_children.size(); i++ ){
		KsModelRenderDX( pRS, pMesh, pMesh->m_pHierarchy->m_pJointList[ pJoint->m_children[ i ] ], pJoint );
	}

	mat = pJoint->m_worldMatrix;

	//mat.setTranslate( 1.0f, 1.0f, 0.0f );

	mat.m41 = pJoint->m_worldMatrix.m14;
	mat.m42 = pJoint->m_worldMatrix.m24;
	mat.m43 = pJoint->m_worldMatrix.m34;
	mat.m44 = pJoint->m_worldMatrix.m44;
	mat.m14 = pJoint->m_worldMatrix.m41;
	mat.m24 = pJoint->m_worldMatrix.m42;
	mat.m34 = pJoint->m_worldMatrix.m43;
	mat.m44 = pJoint->m_worldMatrix.m44;

#if 1
	//if( pJoint->m_id != 2 ){
	//pRS->setTransform( ksTRANSFORM_WORLD, &mat );
	//}
	//pRS->setTransform( ksTRANSFORM_WORLD, &pJoint->m_worldMatrix );

	/* 描画 */
	if( target < 100 ){
		
		pRS->setTransform( ksTRANSFORM_WORLD, &mat );

		KsSubMesh*	pSubMesh = pMesh->m_pSubMeshList[ target ];
		KsInt32	numFace = pSubMesh->m_numFaceList;	

		for( KsInt32 i=0; i<numFace; i++ ){
			KsInt32	matID = pSubMesh->m_pFaceList[ i ].m_materialID;
			KsInt32	start = pSubMesh->m_pFaceList[ i ].m_start * 3;
			KsInt32	numPrim = pSubMesh->m_pFaceList[ i ].m_end - pSubMesh->m_pFaceList[ i ].m_start;

			pRS->m_pD3DDevice->SetTexture( 0, pTexture );
			pRS->setMaterial( pMesh->getMaterial( matID ) );
			pRS->drawPrimitive( ksPRIMITIVE_TRIANGLE_LIST, 0, start, numPrim, pSubMesh->m_pVertices->m_pVertexBuffer, pSubMesh->m_pIndices->m_pIndexBuffer );
		}
	}
#endif
}


void KsModelRenderDX( KsRenderSystemDX* pRS, KsMesh* pMesh )
{
	KsModelRenderDX( pRS, pMesh, pMesh->m_pHierarchy->m_pRootJointList[ 0 ] );
}



typedef struct _KS_KAM_FILE_HEADER
{
	KsUInt32				signature;			/**< 識別用						*/
	KsUInt32				version;			/**< バージョン情報				*/
	KsUInt32				type;				/**< タイプ						*/
	KsUInt32				flags;				/**< 各種フラグ					*/
}KS_KAM_FILE_HEADER;

typedef struct _KS_KAM_INFO_HEADER
{
	KsInt32				start;
	KsInt32				end;
	KsInt32				fps;
	KsInt32				numTrack;
}KS_KAM_INFO_HEADER;

typedef struct _KS_KAM_TRACK
{
	KsInt32				target;
	KsInt32				maxTime;
	KsInt32				numFrame;
}KS_KAM_TRACK;

typedef struct _KS_KAM_KEY_FRAME
{
	KsInt32				time;				// フレーム
	KS_KMD_VECTOR3D			translate;			// 位置
	KS_KMD_VECTOR4D			rotate;				// 回転(クォータニオン)
	KS_KMD_VECTOR3D			scale;				// スケール

}KS_KAM_KEY_FRAME;


KsAnim* KsLoadAnim( const KsChar* pFileName )
{
	KS_KAM_FILE_HEADER		header;
	KS_KAM_INFO_HEADER		info;
	KS_KAM_TRACK			track;
	KS_KAM_KEY_FRAME		key;

	KsAnim*		pAnim = new KsAnim();

	FILE*	fp = fopen( pFileName, "rb" );

	/* ファイルヘッダー読み込み */
	fread( &header, sizeof( KS_KAM_FILE_HEADER ), 1, fp );
	fread( &info, sizeof( KS_KAM_INFO_HEADER ), 1, fp );

	pAnim->m_startTime = (KsReal)info.start;
	pAnim->m_endTime   = (KsReal)info.end;
	pAnim->m_frameRate = (KsReal)info.fps;

	pAnim->m_startTime /= pAnim->m_frameRate;
	pAnim->m_endTime /= pAnim->m_frameRate;

	for( KsInt32 i=0; i<info.numTrack; i++ )
	{
		KsAnimTrack*		pTrack;
		KsAnimKeyFrame*		pKey;

		fread( &track, sizeof( KS_KAM_TRACK ), 1, fp );
		
		pTrack = new KsAnimTrack();

		for( KsInt32 j=0; j<track.numFrame; j++ ){
			fread( &key, sizeof( KS_KAM_KEY_FRAME ), 1, fp );

			pKey = new KsAnimKeyFrame();
			pKey->m_time = (KsReal)key.time;

			pKey->m_time /= pAnim->m_frameRate;

			pKey->m_pos.x = key.translate.x;
			pKey->m_pos.y = key.translate.y;
			pKey->m_pos.z = key.translate.z;

			pKey->m_rotation.x = key.rotate.x;
			pKey->m_rotation.y = key.rotate.y;
			pKey->m_rotation.z = key.rotate.z;
			pKey->m_rotation.w = key.rotate.w;

			pTrack->m_vKeyFrames.push_back( pKey );
		}

		pAnim->m_pvTracks.push_back( pTrack );
	}

	fclose( fp );

	return pAnim;
}
KsInt32 KsAnimTrack::getKeyFrame( KsReal time, KsReal *pParam, KsAnimKeyFrame* pKey1, KsAnimKeyFrame* pKey2 )
{
	KsInt32	num = getNumKeyFrame()-1;

	for( KsInt32 i=0; i<num; i++ ){
		if( (m_vKeyFrames[ i ]->m_time <= time) && (time < m_vKeyFrames[ i+1 ]->m_time) ){
			*pKey1 = *m_vKeyFrames[ i ];
			*pKey2 = *m_vKeyFrames[ i+1 ];

			KsReal	ft = time - m_vKeyFrames[ i ]->m_time;
			KsReal dt = m_vKeyFrames[ i+1 ]->m_time - m_vKeyFrames[ i ]->m_time;
			KsReal t;
			
			if( dt > 0.00000001f ){ 
				t = ft/dt;
			}
			else{
				t = 0.0f;
			}

			*pParam = t;

			return i;
		}
	}

	return -1;
}


void KsAnim::anim( KsReal time, KsMesh* pMesh )
{
	if( m_endTime <= time ){
		time -= m_endTime;
	}

	for( KsInt32 i=0; i<getNumTrack(); i++ ){
		KsReal			t;
		KsAnimKeyFrame	key1;
		KsAnimKeyFrame	key2;

		m_pvTracks[ i ]->getKeyFrame( time, &t, &key1, &key2 );

		KsVector3d	pos = key1.m_pos + ( ( key2.m_pos - key1.m_pos ) * t );

		pMesh->m_pHierarchy->m_pJointList[ i ]->m_translate = pos;
		KsQuaternion	quat;
		KsQuaternionSlerp( &quat, &key1.m_rotation, &key2.m_rotation, t );
		pMesh->m_pHierarchy->m_pJointList[ i ]->m_rotate = quat;
	}
}


#if 0

// フレーム

 KeyFrame AnimationTrack::getInterpolatedKeyFrame(Real timeIndex)
{
	/* 現在のキーフレームと次のキーフレームを取得する */
void 	KsAnimKeyFrame*	pKey1, KsAnimKeyFrame* pKey2;


    // Return value (note unattached)
    KeyFrame kret(0, timeIndex);
    
    // Keyframe pointers
    KeyFrame *k1, *k2;
    unsigned short firstKeyIndex;

    Real t = this->getKeyFramesAtTime(timeIndex, &k1, &k2, &firstKeyIndex);

    if (t == 0.0)
    {
        // Just use k1
        kret.setRotation(k1->getRotation());
        kret.setTranslate(k1->getTranslate());
        kret.setScale(k1->getScale());
    }
    else
    {
        // Interpolate by t
        Animation::InterpolationMode im = mParent->getInterpolationMode();
        Animation::RotationInterpolationMode rim = mParent->getRotationInterpolationMode();
        Vector3 base;

		kret.setRotation( Quaternion::Slerp(t, k1->getRotation(), k2->getRotation(), mUseShortestRotationPath) );

        // Translation
        base = k1->getTranslate();
        kret.setTranslate( base + ((k2->getTranslate() - base) * t) );

        // Scale
        //base = k1->getScale();
        //kret.setScale( base + ((k2->getScale() - base) * t) );
    }
    
    return kret;
        
#endif






