/************************************************************************************************/
/** 
 * @file		KsTextureDX11.h
 * @brief		DirectX�p�e�N�X�`��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSTEXTUREDX11_H__
#define __KSTEXTUREDX11_H__

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
 * @class		KsTextureDX11
 * @brief		�e�N�X�`��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		�Q�ƃJ�E���^��
 */
/************************************************************************************************/
class ksDEVDX11_API KsTextureDX11 : public KsTexture
{
		friend class KsRenderSystemDX11;
		friend class KsRenderContextDX11;
	public:
		/**
		 * �R���X�g���N�^
		 */
											KsTextureDX11();

		/**
		 * �R���X�g���N�^
		 * @param		pFileName			�t�@�C����
		 * @param		flags				�ǂݍ��ݕ��@�̃t���O
		 */
											KsTextureDX11( KsRenderSystemDX11* pRenderSystem, const KsChar* pFileName, KsUInt32 flags );

		/**
		 * �R���X�g���N�^
		 * @param		pImage				�C���[�W�t�@�C��
		 * @param		flags				�ǂݍ��ݕ��@�̃t���O
		 */
											KsTextureDX11( KsImage* pImage, KsUInt32 flags );

		/**
		 * �R���X�g���N�^
		 * @param		pD3D11Texture		Direct3D�e�N�X�`��
		 * @param		pShaderView			�V�F�[�_�[���\�[�X�r���[
		 */
											KsTextureDX11( ID3D11Texture2D* pD3D11Texture, ID3D11ShaderResourceView* pShaderResourceView );

		/**
		 * �f�X�g���N�^
		 */
		virtual								~KsTextureDX11();

		/**
		 * �e�N�X�`���̔j��
		 */
		virtual void						destroy();

		/**
		 * �e�N�X�`�����A�N�e�B�u�ɂ���
		 */
		virtual void						active();

		/**
		 * ���\�[�X���擾����
		 * @return							 ���\�[�X
		 */
		virtual void*						getBufferResource();

		/**
		 * ���\�[�X���擾����
		 * @return							 ���\�[�X
		 */
		virtual void*						getTextureResource() { return m_pShaderResourceView; }

		/**
		 * �o�b�t�@�����b�N����
		 * @param	pContext				�`��R���e�L�X�g
		 * @param	flags					���b�N�t���O
		 * @return							���b�N�����o�b�t�@�̐擪�|�C���^
		 */
		virtual void*						lock( const KsRenderContext* pContext, KsUInt32 flags );

		/**
		 * �o�b�t�@�̃��b�N����������
		 * @param	pContext				�`��R���e�L�X�g
		 */
		virtual void						unlock( const KsRenderContext* pContext );

		/**
		 * �o�b�t�@����̓ǂݍ���
		 * @param	pContext				�`��R���e�L�X�g
		 * @param	pData					�f�[�^�ǂݍ��ݗp�̃|�C���^
		 * @param	size					�f�[�^�T�C�Y
		 */
		virtual void						read( const KsRenderContext* pContext, void* pData, KsUInt32 size );

		/**
		 * �o�b�t�@�ւ̏�������
		 * @param	pContext				�`��R���e�L�X�g
		 * @param	pData					�f�[�^�ǂݍ��ݗp�̃|�C���^
		 * @param	size					�f�[�^�T�C�Y
		 */
		virtual void						write( const KsRenderContext* pContext, void* pData, KsUInt32 size );

		/**
		 * ID3D11Texture2D�̃|�C���^���擾����
		 * @return							ID3D11Texture2D�̃|�C���^
		 */
		virtual ID3D11Texture2D*			getD3D11Texture() { return m_pD3D11Texture; }

		/**
		 * ID3D11ShaderResourceView�̃|�C���^���擾����
		 * @return							�V�F�[�_�[���\�[�X�r���[�̃|�C���^
		 */
		virtual ID3D11ShaderResourceView*	getD3D11ShaderResourceView() { return m_pShaderResourceView; }

	protected:
		KsImage*							m_pImage;				/**< �C���[�W�f�[�^			*/
		ID3D11Texture2D*					m_pD3D11Texture;		/**< Direct3D�e�N�X�`��		*/
		ID3D11ShaderResourceView*			m_pShaderResourceView;	/**< �V�F�[�_�[���\�[�X�r���[	*/
};


#endif		/* __KSTEXTUREDX11_H__ */

