/************************************************************************************************/
/** 
 * @file		KsHardwareBufferManagerDX11.cpp
 * @brief		バッファマネージャ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsDevDX11/KsDevDX11PreCompile.h"
#include "KsDevDX11/device/KsHardwareBufferManagerDX11.h"

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
KsHardwareBufferManagerDX11::KsHardwareBufferManagerDX11( KsRenderSystemDX11* _RenderSystem )
	: m_RenderSystem( _RenderSystem )
{
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsHardwareBufferManagerDX11::~KsHardwareBufferManagerDX11()
{
}

/************************************************************************************************/
/*
 * 頂点バッファを生成する
 * @param		vertexSize		頂点サイズ
 * @param		numVertex		頂点数
 * @param		vertexFormat	頂点フォーマット
 * @param		flags			フラグ
 * @return						頂点バッファのポインタ
 */
/************************************************************************************************/
KsVertexBuffer* KsHardwareBufferManagerDX11::createVertexBuffer( KsUInt32 vertexSize, KsUInt32 numVertex, KsUInt32 vertexFormat, KsUInt32 flags )
{
	return new KsVertexBufferDX11( m_RenderSystem, NULL, vertexSize, numVertex, vertexFormat, flags );
}

/************************************************************************************************/
/*
 * 頂点バッファを生成する
 * @param		vertexSize		頂点サイズ
 * @param		numVertex		頂点数
 * @param		vertexFormat	頂点フォーマット
 * @param		flags			フラグ
 * @return						頂点バッファのポインタ
 */
/************************************************************************************************/
KsVertexBuffer* KsHardwareBufferManagerDX11::createVertexBuffer( void* pData, KsUInt32 vertexSize, KsUInt32 numVertex, KsUInt32 vertexFormat, KsUInt32 flags )
{
	return new KsVertexBufferDX11( m_RenderSystem, pData, vertexSize, numVertex, vertexFormat, flags );
}

/************************************************************************************************/
/*
 * インデックスバッファを生成する
 * @param		numIndex		インデックス数
 * @param		flags			フラグ
 * @return						インデックスバッファのポインタ
 */
/************************************************************************************************/
KsIndexBuffer* KsHardwareBufferManagerDX11::createIndexBuffer( KsUInt32 numIndex, KsUInt32 indexFormat, KsUInt32 flags )
{
	return new KsIndexBufferDX11( m_RenderSystem, NULL, 0, numIndex, indexFormat, flags );
}

/************************************************************************************************/
/*
 * インデックスバッファを生成する
 * @param		numIndex		インデックス数
 * @param		flags			フラグ
 * @return						インデックスバッファのポインタ
 */
/************************************************************************************************/
KsIndexBuffer* KsHardwareBufferManagerDX11::createIndexBuffer( void* pData, KsUInt32 size, KsUInt32 numIndex, KsUInt32 indexFormat, KsUInt32 flags )
{
	return new KsIndexBufferDX11( m_RenderSystem, pData, size, numIndex, indexFormat, flags );
}

/************************************************************************************************/
/*
 * 定数バッファを生成する
 * @param	pData				[in] データ読み込み用のポインタ
 * @param	size				[in] データサイズ
 * @param	flags				[in] フラグ
 * @return						定数バッファのポインタ
 */
 /************************************************************************************************/
KsConstantBuffer* KsHardwareBufferManagerDX11::createConstantBuffer( KsUInt32 size, KsUInt32 flags )
{
	return new KsConstantBufferDX11( m_RenderSystem, NULL, size, flags );
}

/************************************************************************************************/
/*
 * 定数バッファを生成する
 * @param	size				[in] バッファサイズ
 * @param	flags				[in] フラグ
 * @return						定数バッファのポインタ
 */
 /************************************************************************************************/
KsConstantBuffer* KsHardwareBufferManagerDX11::createConstantBuffer( void* pData, KsUInt32 size, KsUInt32 flags )
{
	return new KsConstantBufferDX11( m_RenderSystem, pData, size, flags );
}


