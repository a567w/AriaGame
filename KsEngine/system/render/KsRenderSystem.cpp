/************************************************************************************************/
/** 
 * @file		KsRenderSystem.h
 * @brief		カラー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsRenderSystem.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsBool KsRenderStateStack::push( const KsRenderState* pState )
{
	if( m_index < ksRENDER_STATE_STACK_MAX ){
		memcpy( &m_stack[ m_index ], pState, sizeof( KsRenderState ) );
		++m_index;

		return ksTRUE;
	}

	/* エラーメッセージ */
	//StMessage( "render state stack overflow" );

	return ksFALSE;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsBool KsRenderStateStack::pop( KsRenderState* pState )
{
	if( m_index > 0 ){
		--m_index;
		memcpy( pState, &m_stack[ m_index ], sizeof( KsRenderState ) );
		
		return ksTRUE;
	}
	/* エラーメッセージ */
	//StMessage( "render state stack zero limits" );

	return ksFALSE;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsRenderStateStack::clear()
{
	m_index = 0;
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
#if 0
	KsRenderState		state;

	/* レンダーステート取得 */
	if( !m_renderStateStack.pop( &state ) ){
		return;
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
	/* アルファテスト(ON,OFF) */
	if( state.m_alphaTest != m_renderState.m_alphaTest ){
		m_renderState.m_alphaTest = state.m_alphaTest;
		setRenderState( ksRENDER_STATE_ALPAHTEST_ENABLE, static_cast<KsUInt32>(m_renderState.m_alphaTest) );
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
#endif

}

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsRenderSystem::KsRenderSystem()
{
	/* 初期状態でのレンダーステートをセットしておく */
	//m_renderState.m_
	//m_renderState.m_srcBlend = ksBLEND_ONE;
	//m_renderState.m_dstBlend = ksBLEND_ZERO;

	m_clearFlags         = 0;
	//m_clearColor.m_color = 0;
	m_clearDepth         = 0;
	m_clearStencil       = 0;
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




