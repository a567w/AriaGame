/************************************************************************************************/
/** 
 * @file		KsDepthStencilStateDX11.h
 * @brief		DirectX�p�[�x�X�e���V���X�e�[�g
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSDEPTHSTENCILSTATEDX11_H__
#define __KSDEPTHSTENCILSTATEDX11_H__

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
 * @class		KsDepthStencilStateDX11
 * @brief		�[�x�X�e���V���X�e�[�g
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		�Q�ƃJ�E���^��
 */
/************************************************************************************************/
class ksDEVDX11_API KsDepthStencilStateDX11 : public KsDepthStencilState
{
		friend class KsRenderSystemDX11;
		friend class KsRenderContextDX11;
	public:
		/**
		 * �R���X�g���N�^
		 */
											KsDepthStencilStateDX11( KsRenderSystemDX11* pDevice, const KS_DEPTH_STENCIL_DESC* pDepthStencilDesc );

		/**
		 * �f�X�g���N�^
		 */
		virtual								~KsDepthStencilStateDX11();

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
		ID3D11DepthStencilState*			m_pState;
};

#endif		/* __KSDEPTHSTENCILSTATEDX11_H__ */

