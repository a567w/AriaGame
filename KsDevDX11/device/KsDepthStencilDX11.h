/************************************************************************************************/
/** 
 * @file		KsDepthStencilDX11.h
 * @brief		�`��^�[�Q�b�g
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSDEPTHSTENCILDX11_H__
#define __KSDEPTHSTENCILDX11_H__

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
 * @class		KsDepthStencilDX11
 * @brief		�`��^�[�Q�b�g(DX11)
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsDepthStencilDX11 : public KsRenderTargetTexture
{
		friend class KsRenderSystemDX11;
		friend class KsRenderContextDX11;
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsDepthStencilDX11();

		/**
		 * �R���X�g���N�^
		 */
									KsDepthStencilDX11( KsTexture* pDepthStencilTexture, ID3D11DepthStencilView* pDepthStencilView );

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsDepthStencilDX11();

		/**
		 * ���b�N����
		 * @return					�f�[�^�̃|�C���^
		 */
		virtual void*				lock();

		/**
		 * ���b�N����������
		 */
		virtual void				unlock();

		/**
		 * �e�N�X�`���̔j��
		 */
		virtual void				destroy();

		/**
		 * ���\�[�X���擾����
		 * @return					 ���\�[�X
		 */
		virtual void*				getRenderResource() { return m_pDepthStencilView; }

	protected:
		ID3D11DepthStencilView*		m_pDepthStencilView;	/**< �[�x�X�e���V���r���[		*/
};



#endif		/* __KSDEPTHSTENCILDX11_H__ */



