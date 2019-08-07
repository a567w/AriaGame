/************************************************************************************************/
/** 
 * @file		KsRenderThread.cpp
 * @brief		�`��X���b�h
 * @author		Tsukasa Kato
 * @date		2011/07/02
 * @since		2011/07/02
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "Aria/KsGamePreCompile.h"
#include "Aria/thread/KsRenderThread.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * �`��V�X�e������
 */
/************************************************************************************************/
KsRenderThread::KsRenderThread( KsRenderSystem* pRenderSystem, KsDeferredRender* pDeferredRender )
	: m_pRenderSystem( pRenderSystem )
	, m_pDeferredRender( pDeferredRender )
	, m_bThreadLoop( ksFALSE )
	, m_bClearState( ksFALSE )
	, m_bRestoreState( ksFALSE )
	, m_pRenderContext( 0 )
	, m_pCommandList( 0 )
{
	try
	{
		m_beginRenderEvent = KsCreateEvent( ksFALSE, ksFALSE, "BeginRenderEvent" );
		m_endRenderEvent   = KsCreateEvent( ksFALSE, ksFALSE, "EndRenderEvent" );

		m_pRenderContext   = pRenderSystem->createDeferredContext();
		m_pCommandList     = pRenderSystem->createCommandList();

		KS_DEPTH_STENCIL_DESC	desc = KsDepthStencilState::DEFAULT;
		desc.DepthFunc = KS_COMPARISON_GREATER_EQUAL;
		m_pDepthState = m_pRenderSystem->createDepthStencilState( &desc );

		//m_pRenderContext->setRenderTarget( pRenderSystem->getRenderContex()->getRenderTarget(), pRenderSystem->getRenderContex()->getDepthStencil() );

		if( !m_pRenderContext )
		{
			throw "�`��R���e�L�X�g�����G���[!!";
		}

		if( !m_pCommandList )
		{
			throw "�`��R�}���h���X�g�G���[!!";
		}
	}
	catch( const KsChar* pszError )
	{
		/* �G���[ */
		KsError( pszError );
	}
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsRenderThread::~KsRenderThread()
{
	KsCloseEvent( m_beginRenderEvent );
	KsCloseEvent( m_endRenderEvent );

	ksDELETE( m_pRenderContext );
	ksDELETE( m_pCommandList );
}

/************************************************************************************************/
/*
 * ���s����
 */
/************************************************************************************************/
KsBool KsRenderThread::run()
{
	m_bThreadLoop = ksTRUE;

	start();

	return ksTRUE;
}

/************************************************************************************************/
/*
 * �X���b�h�̃��C���֐�
 * @return	���s�I������
 */
/************************************************************************************************/
KsUInt32 KsRenderThread::threadMain()
{
	// �w��v���Z�b�T�����蓖�Ă�B
	//setProcessor( 1<<2 );

	/* �Q�[�����[�v */
	while( m_bThreadLoop )
	{
		// ���C���X���b�h�Ƃ̓����҂�
		KsWaitEvent( m_beginRenderEvent );

		// �X�e�[�g���N���A����
		if( m_bClearState )
		{
			m_pRenderContext->clearState();
		}

#if 0
		m_pDeferredRender->setViewport( 0, 0, 1280, 720, 0.0f, 1.0f, m_pRenderContext );

		// �����_�[�^�[�Q�b�g���Z�b�g���Ȃ��ƕ`�悳��Ȃ��B
		m_pDeferredRender->setRenderTarget_Default( m_pRenderContext );

		m_pRenderContext->setDepthStencilState( m_pDepthState, 0 );
		KsGraphics*	pGraphics = KsGraphics::getInstancePtr();

		pGraphics->setColorRect( 1.0f, 1.0f, 0.0f, 1.0f ); 
		pGraphics->drawRect( 0, 0, 400, 400 );
	
		pGraphics->flush( m_pRenderContext );

		//m_pRenderContext->clearScene( ksCLEAR_FLAG_COLOR, KsColor::RED, 1.0f, 0 );
#endif


		// �`�悷��
		//render( m_pRenderContext );

		// �R�}���h���X�g�𐶐�����
		m_pRenderContext->finishCommandList( m_bRestoreState, m_pCommandList );

		// �`��I���C�x���g���Z�b�g����
		KsSetEvent( m_endRenderEvent );
	}

	return 0;
}

/************************************************************************************************/
/*
 * �X���b�h�`��J�n����
 */
/************************************************************************************************/
void KsRenderThread::startBeginRender()
{
	// �`��I���C�x���g���Z�b�g����
	KsSetEvent( m_beginRenderEvent );
}

/************************************************************************************************/
/*
 * �`��I���C�x���g��҂�
 */
/************************************************************************************************/
void KsRenderThread::waitEndRender()
{
	// �`��I���C�x���g��҂�
	KsWaitEvent( m_endRenderEvent );
}

