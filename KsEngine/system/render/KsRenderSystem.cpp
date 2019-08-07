/************************************************************************************************/
/** 
 * @file		KsRenderSystem.h
 * @brief		�J���[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsRenderSystem.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
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

	/* �G���[���b�Z�[�W */
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
	/* �G���[���b�Z�[�W */
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
 * �����_�[�X�e�[�g���X�^�b�N�Ƀv�b�V������
 */
/************************************************************************************************/
void KsRenderSystem::pushRenderState()
{
	m_renderStateStack.push( &m_renderState );
}

/************************************************************************************************/
/**
 * �����_�[�X�e�[�g���X�^�b�N�Ƀ|�b�v����
 */
/************************************************************************************************/
void KsRenderSystem::popRenderState()
{
#if 0
	KsRenderState		state;

	/* �����_�[�X�e�[�g�擾 */
	if( !m_renderStateStack.pop( &state ) ){
		return;
	}
	/* SRC�u�����f�B���O	*/
	if( state.m_srcBlend != m_renderState.m_srcBlend ){
		m_renderState.m_srcBlend = state.m_srcBlend;
		setRenderState( ksRENDER_STATE_SRC_BLEND, static_cast<KsUInt32>(m_renderState.m_srcBlend) );
	}
	/* DEST�u�����f�B���O */
	if( state.m_dstBlend != m_renderState.m_dstBlend ){
		m_renderState.m_dstBlend = state.m_dstBlend;
		setRenderState( ksRENDER_STATE_DST_BLEND, static_cast<KsUInt32>(m_renderState.m_dstBlend) );
	}
	/* �A���t�@�u�����h */
	if( state.m_alphaBlend != m_renderState.m_alphaBlend ){
		m_renderState.m_alphaBlend = state.m_alphaBlend;
		setRenderState( ksRENDER_STATE_ALPHA_BLEND, static_cast<KsUInt32>(m_renderState.m_alphaBlend) );
	}
	/* Z�o�b�t�@(ON,OFF)	*/
	if( state.m_zTest != m_renderState.m_zTest ){
		m_renderState.m_zTest = state.m_zTest;
		setRenderState( ksRENDER_STATE_ZTEST_ENABLE, static_cast<KsUInt32>(m_renderState.m_zTest) );
	}
	/* Z���C�g(ON,OFF)	*/
	if( state.m_zWrite != m_renderState.m_zWrite ){
		m_renderState.m_zWrite = state.m_zWrite;
		setRenderState( ksRENDER_STATE_ZWRITE_ENABLE, static_cast<KsUInt32>(m_renderState.m_zWrite) );
	}
	/* �A���t�@�e�X�g(ON,OFF) */
	if( state.m_alphaTest != m_renderState.m_alphaTest ){
		m_renderState.m_alphaTest = state.m_alphaTest;
		setRenderState( ksRENDER_STATE_ALPAHTEST_ENABLE, static_cast<KsUInt32>(m_renderState.m_alphaTest) );
	}
	/* ���C�e�B���O(ON,OFF) */
	if( state.m_lighting != m_renderState.m_lighting ){
		m_renderState.m_lighting = state.m_lighting;
		setRenderState( ksRENDER_STATE_LIGHTING, static_cast<KsUInt32>(m_renderState.m_lighting) );
	}
	/* �V�F�[�f�B���O */
	if( state.m_shadeMode != m_renderState.m_shadeMode ){
		m_renderState.m_shadeMode = state.m_shadeMode;
		setRenderState( ksRENDER_STATE_SHADE, static_cast<KsUInt32>(m_renderState.m_shadeMode) );
	}
	/* �J�����O */
	if( state.m_cullMode != m_renderState.m_cullMode ){
		m_renderState.m_cullMode = state.m_cullMode;
		setRenderState( ksRENDER_STATE_CULL, static_cast<KsUInt32>(m_renderState.m_cullMode) );
	}
#endif

}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsRenderSystem::KsRenderSystem()
{
	/* ������Ԃł̃����_�[�X�e�[�g���Z�b�g���Ă��� */
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
 * �w��C���f�b�N�X�̃��C�g���擾����
 * @param		index				�C���f�b�N�X
 * @return							���C�g�̃|�C���^(�Z�b�g����Ă��Ȃ��Ƃ���NULL���Ԃ�)
 */
/************************************************************************************************/
KsLight* KsRenderSystem::getLight( KsUInt32 index )
{
	//StAssert( index < ksLIGHT_MAX, "getLight index over !!" );

	return ( &m_pLights[ index ] );
}




