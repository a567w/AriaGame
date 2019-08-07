/************************************************************************************************/
/** 
 * @file		KsRenderSystem.cpp
 * @brief		描画システム
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"
#include "KsRenderSystem.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
template<> KsRenderSystem* KsSingleton< KsRenderSystem >::m_pInstance = 0;

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsRenderSystem& KsRenderSystem::getInstance()
{  
	return (*m_pInstance);  
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsRenderSystem* KsRenderSystem::getInstancePtr()
{
	return m_pInstance;
}


/************************************************************************************************/
/**
 * レンダーステートをスタックにプッシュする
 */
/************************************************************************************************/
void KsRenderSystem::pushRenderState()
{
	m_renderStateStack.push( &m_renderState );
}

/************************************************************************************************/
/**
 * レンダーステートをスタックにポップする
 */
/************************************************************************************************/
void KsRenderSystem::popRenderState()
{
	KsRenderState		state;

	/* レンダーステート取得 */
	if( !m_renderStateStack.pop( &state ) ){
		return;
	}

	/* ブレンディング	*/
	if( state.m_opBlend != m_renderState.m_opBlend ){
		m_renderState.m_opBlend = state.m_opBlend;
		setRenderState( ksRENDER_STATE_ALPHA_BLEND, static_cast<KsUInt32>(m_renderState.m_opBlend) );
	}
	/* SRCブレンディング	*/
	if( state.m_srcBlend != m_renderState.m_srcBlend ){
		m_renderState.m_srcBlend = state.m_srcBlend;
		setRenderState( ksRENDER_STATE_SRC_BLEND, static_cast<KsUInt32>(m_renderState.m_srcBlend) );
	}
	/* DESTブレンディング */
	if( state.m_dstBlend != m_renderState.m_dstBlend ){
		m_renderState.m_dstBlend = state.m_dstBlend;
		setRenderState( ksRENDER_STATE_DST_BLEND, static_cast<KsUInt32>(m_renderState.m_dstBlend) );
	}
	/* アルファブレンド */
	if( state.m_alphaBlend != m_renderState.m_alphaBlend ){
		m_renderState.m_alphaBlend = state.m_alphaBlend;
		setRenderState( ksRENDER_STATE_ALPHA_BLEND, static_cast<KsUInt32>(m_renderState.m_alphaBlend) );
	}
	/* Zバッファ(ON,OFF)	*/
	if( state.m_zTest != m_renderState.m_zTest ){
		m_renderState.m_zTest = state.m_zTest;
		setRenderState( ksRENDER_STATE_ZTEST_ENABLE, static_cast<KsUInt32>(m_renderState.m_zTest) );
	}
	/* Zライト(ON,OFF)	*/
	if( state.m_zWrite != m_renderState.m_zWrite ){
		m_renderState.m_zWrite = state.m_zWrite;
		setRenderState( ksRENDER_STATE_ZWRITE_ENABLE, static_cast<KsUInt32>(m_renderState.m_zWrite) );
	}
	/* フォグのON, OFF */
	if( state.m_fog != m_renderState.m_fog ){
		m_renderState.m_fog = state.m_fog;
		setRenderState( ksRENDER_STATE_FOG_ENABLE, static_cast<KsUInt32>(m_renderState.m_fog) );
	}
	/* アルファテスト(ON,OFF) */
	if( state.m_alphaTest != m_renderState.m_alphaTest ){
		m_renderState.m_alphaTest = state.m_alphaTest;
		setRenderState( ksRENDER_STATE_ALPAHTEST_ENABLE, static_cast<KsUInt32>(m_renderState.m_alphaTest) );
	}
	/* アルファFUNC */
	if( state.m_alphaFunc != m_renderState.m_alphaFunc ){
		m_renderState.m_alphaFunc = state.m_alphaFunc;
		setRenderState( ksRENDER_STATE_ALPHA_FUNC, static_cast<KsUInt32>(m_renderState.m_alphaFunc) );
	}
	/* アルファの基準値 */
	if( state.m_alphaRef != m_renderState.m_alphaRef ){
		m_renderState.m_alphaRef = state.m_alphaRef;
		setRenderState( ksRENDER_STATE_ALPHA_REF, static_cast<KsUInt32>(m_renderState.m_alphaRef) );
	}
	/* アルファのマスク値 */
	if( state.m_alphaMask != m_renderState.m_alphaMask ){
		m_renderState.m_alphaMask = state.m_alphaMask;
		setRenderState( ksRENDER_STATE_ALPHA_MASK, static_cast<KsUInt32>(m_renderState.m_alphaMask) );
	}
	/* ライティング(ON,OFF) */
	if( state.m_lighting != m_renderState.m_lighting ){
		m_renderState.m_lighting = state.m_lighting;
		setRenderState( ksRENDER_STATE_LIGHTING, static_cast<KsUInt32>(m_renderState.m_lighting) );
	}
	/* シェーディング */
	if( state.m_shadeMode != m_renderState.m_shadeMode ){
		m_renderState.m_shadeMode = state.m_shadeMode;
		setRenderState( ksRENDER_STATE_SHADE, static_cast<KsUInt32>(m_renderState.m_shadeMode) );
	}
	/* カリング */
	if( state.m_cullMode != m_renderState.m_cullMode ){
		m_renderState.m_cullMode = state.m_cullMode;
		setRenderState( ksRENDER_STATE_CULL, static_cast<KsUInt32>(m_renderState.m_cullMode) );
	}
	/* ステンシル(ON,OFF) */
	if( state.m_stencil != m_renderState.m_stencil ){
		m_renderState.m_stencil = state.m_stencil;
		setRenderState( ksRENDER_STATE_STENCIL_ENABLE, static_cast<KsUInt32>(m_renderState.m_stencil) );
	}
	/* ステンシルの基準値 */
	if( state.m_stencilRef != m_renderState.m_stencilRef ){
		m_renderState.m_stencilRef = state.m_stencilRef;
		setRenderState( ksRENDER_STATE_STENCIL_REF, static_cast<KsUInt32>(m_renderState.m_stencilRef) );
	}
	/* ステンシルのマスク値 */
	if( state.m_stencilMask != m_renderState.m_stencilMask ){
		m_renderState.m_stencilMask = state.m_stencilMask;
		setRenderState( ksRENDER_STATE_STENCIL_MASK, static_cast<KsUInt32>(m_renderState.m_stencilMask) );
	}
	/* ステンシルの書き込みマスク値 */
	if( state.m_stencilWriteMask != m_renderState.m_stencilWriteMask ){
		m_renderState.m_stencilWriteMask = state.m_stencilWriteMask;
		setRenderState( ksRENDER_STATE_STENCIL_WRITE_MASK, static_cast<KsUInt32>(m_renderState.m_stencilWriteMask) );
	}
	/* ステンシルテスト失敗時のオペレーション */
	if( state.m_stencilOpFail != m_renderState.m_stencilOpFail ){
		m_renderState.m_stencilOpFail = state.m_stencilOpFail;
		setRenderState( ksRENDER_STATE_STENCIL_FAIL, static_cast<KsUInt32>(m_renderState.m_stencilOpFail) );
	}
	/* ステンシルテストかつZテストに失敗時のオペレーション */
	if( state.m_stencilOpZFail != m_renderState.m_stencilOpZFail ){
		m_renderState.m_stencilOpZFail = state.m_stencilOpZFail;
		setRenderState( ksRENDER_STATE_STENCIL_ZFAIL, static_cast<KsUInt32>(m_renderState.m_stencilOpZFail) );
	}
	/* ステンシルテストかつZテストの成功時のオペレーション */
	if( state.m_stencilOpPass != m_renderState.m_stencilOpPass ){
		m_renderState.m_stencilOpPass = state.m_stencilOpPass;
		setRenderState( ksRENDER_STATE_STENCIL_PASS, static_cast<KsUInt32>(m_renderState.m_stencilOpPass) );
	}
	/* ステンシルファンクション */
	if( state.m_stencilFunc != m_renderState.m_stencilFunc ){
		m_renderState.m_stencilFunc = state.m_stencilFunc;
		setRenderState( ksRENDER_STATE_STENCIL_FUNC, static_cast<KsUInt32>(m_renderState.m_stencilFunc) );
	}
#if 0
		ksALPHA_FUNC_MODE				m_alphaFunc;
		KsUInt32						m_alphaRef;
		KsUInt32						m_alphaMask;

		KsBool							m_colorTest;
		ksCOLOR_FUNC_MODE				m_colorFunc;
		KsUInt32						m_colorRef;
		KsUInt32						m_colorMask;
		KsUInt32						m_pixelMask;
		KsBool							m_logicalOp;
#endif
}

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsRenderSystem::KsRenderSystem()
	: m_pRenderContext( 0 )
	, m_pTextureManager( 0 )
	, m_pHardwareBufferManager( 0 )
	, m_pShaderManager( 0 )
	, m_clearFlags( 0 )
	, m_clearDepth( 0 )
	, m_clearStencil( 0 )
{
	/* 初期状態でのレンダーステートをセットしておく */
	//m_renderState.m_
	//m_renderState.m_srcBlend = ksBLEND_ONE;
	//m_renderState.m_dstBlend = ksBLEND_ZERO;
	//m_clearColor.m_color = 0;
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
KsRenderSystem::~KsRenderSystem()
{
	ksDELETE( m_pShaderManager );
	ksDELETE( m_pHardwareBufferManager );
	ksDELETE( m_pTextureManager );
	ksDELETE( m_pRenderContext );
}

/************************************************************************************************/
/*
 * 指定インデックスのライトを取得する
 * @param		index				インデックス
 * @return							ライトのポインタ(セットされていないときはNULLが返る)
 */
/************************************************************************************************/
KsLight* KsRenderSystem::getLight( KsUInt32 index )
{
	//StAssert( index < ksLIGHT_MAX, "getLight index over !!" );

	return ( &m_pLights[ index ] );
}


