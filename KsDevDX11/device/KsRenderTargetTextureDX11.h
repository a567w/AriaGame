/************************************************************************************************/
/** 
 * @file		KsRenderTargetTextureDX11.h
 * @brief		�`��^�[�Q�b�g
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSRENDERTARGETTEXTUREDX11_H__
#define __KSRENDERTARGETTEXTUREDX11_H__

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
 * @class		KsRenderTargetTextureDX11
 * @brief		�`��^�[�Q�b�g
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsRenderTargetTextureDX11 : public KsRenderTargetTexture
{
		friend class KsRenderSystemDX;
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsRenderTargetTextureDX11();

		/**
		 * �R���X�g���N�^
		 */
									KsRenderTargetTextureDX11( KsTexture* pRenderTexture, ID3D11RenderTargetView* pTargetView );

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsRenderTargetTextureDX11();

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
		virtual void*				getRenderResource() { return m_pTargetView; }

	protected:
		ID3D11RenderTargetView*		m_pTargetView;
};



#endif		/* __KSRENDERTARGETTEXTUREDX11_H__ */



