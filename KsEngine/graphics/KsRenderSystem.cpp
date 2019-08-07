/************************************************************************************************/
/** 
 * @file		KsRenderSystem.cpp
 * @brief		�`��V�X�e��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"
#include "KsRenderSystem.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
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
	KsRenderState		state;

	/* �����_�[�X�e�[�g�擾 */
	if( !m_renderStateStack.pop( &state ) ){
		return;
	}

	/* �u�����f�B���O	*/
	if( state.m_opBlend != m_renderState.m_opBlend ){
		m_renderState.m_opBlend = state.m_opBlend;
		setRenderState( ksRENDER_STATE_ALPHA_BLEND, static_cast<KsUInt32>(m_renderState.m_opBlend) );
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
	/* �t�H�O��ON, OFF */
	if( state.m_fog != m_renderState.m_fog ){
		m_renderState.m_fog = state.m_fog;
		setRenderState( ksRENDER_STATE_FOG_ENABLE, static_cast<KsUInt32>(m_renderState.m_fog) );
	}
	/* �A���t�@�e�X�g(ON,OFF) */
	if( state.m_alphaTest != m_renderState.m_alphaTest ){
		m_renderState.m_alphaTest = state.m_alphaTest;
		setRenderState( ksRENDER_STATE_ALPAHTEST_ENABLE, static_cast<KsUInt32>(m_renderState.m_alphaTest) );
	}
	/* �A���t�@FUNC */
	if( state.m_alphaFunc != m_renderState.m_alphaFunc ){
		m_renderState.m_alphaFunc = state.m_alphaFunc;
		setRenderState( ksRENDER_STATE_ALPHA_FUNC, static_cast<KsUInt32>(m_renderState.m_alphaFunc) );
	}
	/* �A���t�@�̊�l */
	if( state.m_alphaRef != m_renderState.m_alphaRef ){
		m_renderState.m_alphaRef = state.m_alphaRef;
		setRenderState( ksRENDER_STATE_ALPHA_REF, static_cast<KsUInt32>(m_renderState.m_alphaRef) );
	}
	/* �A���t�@�̃}�X�N�l */
	if( state.m_alphaMask != m_renderState.m_alphaMask ){
		m_renderState.m_alphaMask = state.m_alphaMask;
		setRenderState( ksRENDER_STATE_ALPHA_MASK, static_cast<KsUInt32>(m_renderState.m_alphaMask) );
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
	/* �X�e���V��(ON,OFF) */
	if( state.m_stencil != m_renderState.m_stencil ){
		m_renderState.m_stencil = state.m_stencil;
		setRenderState( ksRENDER_STATE_STENCIL_ENABLE, static_cast<KsUInt32>(m_renderState.m_stencil) );
	}
	/* �X�e���V���̊�l */
	if( state.m_stencilRef != m_renderState.m_stencilRef ){
		m_renderState.m_stencilRef = state.m_stencilRef;
		setRenderState( ksRENDER_STATE_STENCIL_REF, static_cast<KsUInt32>(m_renderState.m_stencilRef) );
	}
	/* �X�e���V���̃}�X�N�l */
	if( state.m_stencilMask != m_renderState.m_stencilMask ){
		m_renderState.m_stencilMask = state.m_stencilMask;
		setRenderState( ksRENDER_STATE_STENCIL_MASK, static_cast<KsUInt32>(m_renderState.m_stencilMask) );
	}
	/* �X�e���V���̏������݃}�X�N�l */
	if( state.m_stencilWriteMask != m_renderState.m_stencilWriteMask ){
		m_renderState.m_stencilWriteMask = state.m_stencilWriteMask;
		setRenderState( ksRENDER_STATE_STENCIL_WRITE_MASK, static_cast<KsUInt32>(m_renderState.m_stencilWriteMask) );
	}
	/* �X�e���V���e�X�g���s���̃I�y���[�V���� */
	if( state.m_stencilOpFail != m_renderState.m_stencilOpFail ){
		m_renderState.m_stencilOpFail = state.m_stencilOpFail;
		setRenderState( ksRENDER_STATE_STENCIL_FAIL, static_cast<KsUInt32>(m_renderState.m_stencilOpFail) );
	}
	/* �X�e���V���e�X�g����Z�e�X�g�Ɏ��s���̃I�y���[�V���� */
	if( state.m_stencilOpZFail != m_renderState.m_stencilOpZFail ){
		m_renderState.m_stencilOpZFail = state.m_stencilOpZFail;
		setRenderState( ksRENDER_STATE_STENCIL_ZFAIL, static_cast<KsUInt32>(m_renderState.m_stencilOpZFail) );
	}
	/* �X�e���V���e�X�g����Z�e�X�g�̐������̃I�y���[�V���� */
	if( state.m_stencilOpPass != m_renderState.m_stencilOpPass ){
		m_renderState.m_stencilOpPass = state.m_stencilOpPass;
		setRenderState( ksRENDER_STATE_STENCIL_PASS, static_cast<KsUInt32>(m_renderState.m_stencilOpPass) );
	}
	/* �X�e���V���t�@���N�V���� */
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
 * �R���X�g���N�^
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
	/* ������Ԃł̃����_�[�X�e�[�g���Z�b�g���Ă��� */
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


