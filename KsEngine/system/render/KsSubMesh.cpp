/************************************************************************************************/
/** 
 * @file		KsSubMesh.cpp
 * @brief		ジオメトリ生成
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsSubMesh.h"

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
KsSubMesh::KsSubMesh()
{
}
/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsSubMesh::~KsSubMesh()
{
}

#if 0
/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsSubMesh::KsSubMesh()
{
	m_id[ 0 ]      = 'T';
	m_id[ 1 ]      = 'K';
	m_id[ 2 ]      = 'M';
	m_id[ 3 ]      = '\0';
	m_flags        = 0;
	m_numVertices  = 0;
	m_numFaces     = 0;
	m_numMaterials = 0;
	m_numTextures  = 0;
	m_pVertices    = NULL;
	m_pFaces       = NULL;
	m_pMaterials   = NULL;
	m_pTextures    = NULL;
}

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsSubMesh::KsSubMesh( KsUInt16 numVertices, KsUInt16 numFaces, KsUInt16 numMaterials, KsUInt16 numTextures )
{
	m_id[ 0 ]      = 'T';
	m_id[ 1 ]      = 'K';
	m_id[ 2 ]      = 'M';
	m_id[ 3 ]      = '\0';
	m_flags        = 0;
	m_numVertices  = 0;
	m_numFaces     = 0;
	m_numMaterials = 0;
	m_numTextures  = 0;
	m_pVertices    = NULL;
	m_pFaces       = NULL;
	m_pMaterials   = NULL;
	m_pTextures    = NULL;

	/* 生成する */
	Create( numVertices, numFaces, numMaterials, numTextures );
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsSubMesh::~KsSubMesh()
{
	/* 開放処理 */
	ksDELETEARRAY( m_pVertices );
	ksDELETEARRAY( m_pFaces );
	ksDELETEARRAY( m_pMaterials );
	ksDELETEARRAY( m_pTextures );
}

/************************************************************************************************/
/*
 *
 * HEADER
 * ID           :		4byte
 * フラグ       :		2byte
 * 頂点数       :		2byte
 * 面の数		:		2byte
 * マテリアル数 :		2byte
 * テクスチャ数 :		2byte
 */
/************************************************************************************************/
KsBool KsSubMesh::Create( void* pData )
{
	KsByte*   pBin = (KsByte*)pData;

	/* クリアー処理 */
	//Clear();

	/* ジオメトリのヘッダー読み込み */
	m_id[ 0 ]      = *( (KsUInt8*) pBin ); pBin += 1;
	m_id[ 1 ]      = *( (KsUInt8*) pBin ); pBin += 1;
	m_id[ 2 ]      = *( (KsUInt8*) pBin ); pBin += 1;
	m_id[ 3 ]      = *( (KsUInt8*) pBin ); pBin += 1;
	m_flags        = *( (KsUInt16*)pBin ); pBin += 2;
	m_numVertices  = *( (KsUInt16*)pBin ); pBin += 2;
	m_numFaces     = *( (KsUInt16*)pBin ); pBin += 2;
	m_numMaterials = *( (KsUInt16*)pBin ); pBin += 2;
	m_numTextures  = *( (KsUInt16*)pBin ); pBin += 2;

	KsAssert( m_numVertices != 0, "data num vertex zero" );
	KsAssert( m_numFaces    != 0, "data num face zero" );

	/* メモリー確保 */
	m_pVertices  = new KsVertex[ m_numVertices ];
	m_pFaces     = new KsFace[ m_numFaces ];
	
	if( m_numMaterials ){
		m_pMaterials = new KsMaterial[ m_numMaterials ];
	}
	if( m_numTextures ){
		m_pTextures  = new KsTexture[ m_numTextures ];
	}

	/* 頂点数 */
	for( KsUInt16 nv=0; nv<m_numVertices; nv++ ){
		m_pVertices[ nv ].m_id       = 0;
		m_pVertices[ nv ].m_flags    = 0;
		m_pVertices[ nv ].m_type     = 0;
		m_pVertices[ nv ].m_matID    = 0;
		m_pVertices[ nv ].m_boneID   = 0;
		m_pVertices[ nv ].m_vertex.x = *( (KsReal*)pBin ); pBin += 4;
		m_pVertices[ nv ].m_vertex.y = *( (KsReal*)pBin ); pBin += 4;
		m_pVertices[ nv ].m_vertex.z = *( (KsReal*)pBin ); pBin += 4;
		m_pVertices[ nv ].m_normal.x = *( (KsReal*)pBin ); pBin += 4;
		m_pVertices[ nv ].m_normal.y = *( (KsReal*)pBin ); pBin += 4;
		m_pVertices[ nv ].m_normal.z = *( (KsReal*)pBin ); pBin += 4;
		m_pVertices[ nv ].m_u        = 0.0f;
		m_pVertices[ nv ].m_v        = 0.0f;
	}

	/* 面の数 */
	for( KsUInt16 nf=0; nf<m_numFaces; nf++ ){
		m_pFaces[ nf ].m_flags          = 0;
		m_pFaces[ nf ].m_smoothingGroup = 0;
		m_pFaces[ nf ].m_groupIndex     = 0;
		m_pFaces[ nf ].m_indices[ 0 ]   = *( (KsUInt16*)pBin ); pBin += 2;
		m_pFaces[ nf ].m_indices[ 1 ]   = *( (KsUInt16*)pBin ); pBin += 2;
		m_pFaces[ nf ].m_indices[ 2 ]   = *( (KsUInt16*)pBin ); pBin += 2;
		m_pFaces[ nf ].m_indices[ 3 ]   = 0;
	}

	/* マテリアル数 */
	for( KsUInt16 nm=0; nm<m_numMaterials; nm++ ){
		KsColorReal		color;
		KsReal			power;

		/* ディフューズ */
		color.setRed(   *( (KsReal*)pBin ) ); pBin += 4;
		color.setGreen( *( (KsReal*)pBin ) ); pBin += 4;
		color.setBlue(  *( (KsReal*)pBin ) ); pBin += 4;
		color.setAlpha( *( (KsReal*)pBin ) ); pBin += 4;
		m_pMaterials[ nm ].setDiffuse( color );

		/* アンビエント */
		color.setRed(   *( (KsReal*)pBin ) ); pBin += 4;
		color.setGreen( *( (KsReal*)pBin ) ); pBin += 4;
		color.setBlue(  *( (KsReal*)pBin ) ); pBin += 4;
		color.setAlpha( *( (KsReal*)pBin ) ); pBin += 4;
		m_pMaterials[ nm ].setAmbient( color );

		/* エミッシブ */
		color.setRed(   *( (KsReal*)pBin ) ); pBin += 4;
		color.setGreen( *( (KsReal*)pBin ) ); pBin += 4;
		color.setBlue(  *( (KsReal*)pBin ) ); pBin += 4;
		color.setAlpha( *( (KsReal*)pBin ) ); pBin += 4;
		m_pMaterials[ nm ].setEmissive( color );

		/* スペキュラー */
		color.setRed(   *( (KsReal*)pBin ) ); pBin += 4;
		color.setGreen( *( (KsReal*)pBin ) ); pBin += 4;
		color.setBlue(  *( (KsReal*)pBin ) ); pBin += 4;
		color.setAlpha( *( (KsReal*)pBin ) ); pBin += 4;
		m_pMaterials[ nm ].setSpecular( color );

		/* パワー */
		power = *( (KsReal*)pBin ); pBin += 4;
		m_pMaterials[ nm ].setPower( power );
	}

	/* テクスチャ数ポインタのみ保存 */
	for( KsUInt16 nt=0; nt<m_numMaterials; nt++ ){
	}

	return ksTRUE;
}
/************************************************************************************************/
/*
 * ジオメトリを生成する
 */
/************************************************************************************************/
KsBool KsSubMesh::Create( KsFileObject* pFile )
{
	/* クリアー処理 */
	//Clear();

	/* ジオメトリのヘッダー部分を取得 */
	KS_GEOMETRY_HEADER		geometryHeader;
	pFile->read( &geometryHeader, sizeof( KS_GEOMETRY_HEADER ) );

	m_numVertices  = geometryHeader.numVertex;
	m_numFaces     = geometryHeader.numFace;
	m_numMaterials = geometryHeader.numMaterial;

	KsAssert( m_numVertices != 0, "data num vertex zero" );
	KsAssert( m_numFaces    != 0, "data num face zero" );

	/* メモリー確保 */
	m_pVertices  = new KsVertex[ m_numVertices ];
	m_pFaces     = new KsFace[ m_numFaces ];
	
	if( m_numMaterials ){
		m_pMaterials = new KsMaterial[ m_numMaterials ];
	}
	if( m_numTextures ){
		m_pTextures  = new KsTexture[ m_numTextures ];
	}

	/* 頂点数 */
	printf( "-------------<< 頂点情報 >>--------------\n" );
	for( KsUInt16 nv=0; nv<m_numVertices; nv++ ){
		m_pVertices[ nv ].m_id       = pFile->readUInt16();
		m_pVertices[ nv ].m_flags    = 0;
		m_pVertices[ nv ].m_type     = 0;
		m_pVertices[ nv ].m_matID    = pFile->readUInt16();
		m_pVertices[ nv ].m_boneID   = 0;
		m_pVertices[ nv ].m_vertex.x = (KsReal)pFile->readReal();
		m_pVertices[ nv ].m_vertex.y = (KsReal)pFile->readReal();
		m_pVertices[ nv ].m_vertex.z = (KsReal)pFile->readReal();
		m_pVertices[ nv ].m_normal.x = (KsReal)pFile->readReal();
		m_pVertices[ nv ].m_normal.y = (KsReal)pFile->readReal();
		m_pVertices[ nv ].m_normal.z = (KsReal)pFile->readReal();
		m_pVertices[ nv ].m_u        = (KsReal)pFile->readReal();
		m_pVertices[ nv ].m_v        = (KsReal)pFile->readReal();
		pFile->readReal();
	}

	/* 面の数 */
	printf( "--------------<< 面情報 >>---------------\n" );
	for( KsUInt16 nf=0; nf<m_numFaces; nf++ ){
		m_pFaces[ nf ].m_flags          = 0;
		m_pFaces[ nf ].m_smoothingGroup = 0;
		m_pFaces[ nf ].m_groupIndex     = 0;
		m_pFaces[ nf ].m_indices[ 0 ]   = (KsUInt16)pFile->readUInt16();
		m_pFaces[ nf ].m_indices[ 1 ]   = (KsUInt16)pFile->readUInt16();
		m_pFaces[ nf ].m_indices[ 2 ]   = (KsUInt16)pFile->readUInt16();
		m_pFaces[ nf ].m_indices[ 3 ]   = 0;
		m_pFaces[ nf ].m_matID          = (KsUInt16)pFile->readUInt16();
	}

	/* マテリアル数 */
	printf( "----------<< マテリアル情報 >>-----------\n" );
	for( KsUInt16 nm=0; nm<m_numMaterials; nm++ ){
		KsColorReal		color;
		KsReal			power;

		/* ディフューズ */
		color.setRed(   (KsReal)pFile->readReal() );
		color.setGreen( (KsReal)pFile->readReal() );
		color.setBlue(  (KsReal)pFile->readReal() );
		m_pMaterials[ nm ].setDiffuse( color );

		/* アンビエント */
		color.setRed(   (KsReal)pFile->readReal() );
		color.setGreen( (KsReal)pFile->readReal() );
		color.setBlue(  (KsReal)pFile->readReal() );
		m_pMaterials[ nm ].setAmbient( color );

		/* エミッシブ */
		color.setRed(   (KsReal)pFile->readReal() );
		color.setGreen( (KsReal)pFile->readReal() );
		color.setBlue(  (KsReal)pFile->readReal() );
		m_pMaterials[ nm ].setEmissive( color );

		/* スペキュラー */
		color.setRed(   (KsReal)pFile->readReal() );
		color.setGreen( (KsReal)pFile->readReal() );
		color.setBlue(  (KsReal)pFile->readReal() );
		m_pMaterials[ nm ].setSpecular( color );

		/* パワー */
		power = (KsReal)pFile->readReal();
		m_pMaterials[ nm ].setPower( power );

		// uv
		pFile->readReal();
		pFile->readReal();
		pFile->readReal();
		pFile->readReal();
	}

	/* テクスチャ数ポインタのみ保存 */
	for( KsUInt16 nt=0; nt<m_numMaterials; nt++ ){
	}

	return ksTRUE;
}

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
KsBool KsSubMesh::Create( KsUInt16 numVertices, KsUInt16 numFaces, KsUInt16 numMaterials, KsUInt16 numTextures )
{
	KsAssert( numVertices != 0, "data num vertex zero" );
	KsAssert( numFaces    != 0, "data num face zero" );

	m_numVertices  = numVertices;
	m_numFaces     = numFaces;
	m_numMaterials = numMaterials;
	m_numTextures  = numTextures;

	/* メモリー確保 */
	m_pVertices  = new KsVertex[ m_numVertices ];
	m_pFaces     = new KsFace[ m_numFaces ];
	
	if( m_numMaterials ){
		m_pMaterials = new KsMaterial[ m_numMaterials ];
	}
	if( m_numTextures ){
		m_pTextures  = new KsTexture[ m_numTextures ];
	}

	return ksTRUE;
}
#endif


