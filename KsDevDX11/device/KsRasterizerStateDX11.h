/************************************************************************************************/
/** 
 * @file		KsRasterizerStateDX11.h
 * @brief		DirectX�p�[�x�X�e���V���X�e�[�g
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSRASTERIZERSTATEDX11_H__
#define __KSRASTERIZERSTATEDX11_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsRasterizerStateDX11
 * @brief		�[�x�X�e���V���X�e�[�g
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		�Q�ƃJ�E���^��
 */
/************************************************************************************************/
class ksDEVDX11_API KsRasterizerStateDX11 : public KsRasterizerState
{
		friend class KsRenderSystemDX11;
		friend class KsRenderContextDX11;
	public:
		/**
		 * �R���X�g���N�^
		 */
											KsRasterizerStateDX11( KsRenderSystemDX11* pDevice, const KS_RASTERIZER_DESC* pRasterizerState );


		/**
		 * �f�X�g���N�^
		 */
		virtual								~KsRasterizerStateDX11();

		/**
		 * �e�N�X�`���̔j��
		 */
		virtual void						destroy();

		/**
		 * ���\�[�X���擾����
		 * @return							���\�[�X
		 */
		virtual void*						getRenderResource();

	protected:
		ID3D11RasterizerState*				m_pState;
};

#endif		/* __KSRASTERIZERSTATEDX11_H__ */
