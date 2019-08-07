/************************************************************************************************/
/** 
 * @file		KsVertexBufferDX11.h
 * @brief		���_�o�b�t�@
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSVERTEXBUFFERDX11_H__
#define __KSVERTEXBUFFERDX11_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsRenderSystemDX11;

/************************************************************************************************/
/**
 * @class		KsVertexBufferDX11
 * @brief		���_�o�b�t�@
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksDEVDX11_API KsVertexBufferDX11 : public KsVertexBuffer
{
		friend class KsRenderContextDX11;
	public:
		/**
		 * ���_�o�b�t�@�𐶐�����
		 * @param	pRenderSystem	�`��V�X�e��
		 * @param	pData			�f�[�^�ǂݍ��ݗp�̃|�C���^
		 * @param	vertexSize		���_�T�C�Y
		 * @param	numVertex		���_��
		 * @param	vertexFormat	���_�t�H�[�}�b�g
		 * @param	flags			�t���O
		 */
									KsVertexBufferDX11( KsRenderSystemDX11* pRenderSystem, void* pData, KsUInt32 vertexSize, KsUInt32 numVertex, KsUInt32 vertexFormat, KsUInt32 flags );

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsVertexBufferDX11();

		/**
		 * ���_�o�b�t�@�𐶐�����
		 * @param	pRenderSystem	�`��V�X�e��
		 * @param	pData			�f�[�^�ǂݍ��ݗp�̃|�C���^
		 * @param	vertexSize		���_�T�C�Y
		 * @param	numVertex		���_��
		 * @param	vertexFormat	���_�t�H�[�}�b�g
		 * @param	flags			�t���O
		 * @retval	ksTRUE			��������
		 * @retval	ksFALSE			�������s
		 */
		virtual KsBool				create( KsRenderSystemDX11* pRenderSystem, void* pData, KsUInt32 vertexSize, KsUInt32 numVertex, KsUInt32 vertexFormat, KsUInt32 flags );

		/**
		 * �j������
		 */
		virtual void				destroy();

		/**
		 * ���\�[�X���擾����
		 * @return					 ���\�[�X
		 */
		virtual void*				getBufferResource();

		/**
		 * ���_�o�b�t�@�����b�N����
		 * @param	pContext		�`��R���e�L�X�g
		 * @param	flags			���b�N�t���O
		 * @return					���b�N�����o�b�t�@�̐擪�|�C���^
		 */
		virtual void*				lock( const KsRenderContext* pContext, KsUInt32 flags );

		/**
		 * ���_�o�b�t�@�̃��b�N����������
		 * @param	pContext		�`��R���e�L�X�g
		 */
		virtual void				unlock( const KsRenderContext* pContext );

		/**
		 * �C���f�b�N�X�o�b�t�@����̓ǂݍ���
		 * @param	pContext		�`��R���e�L�X�g
		 * @param	pData			�f�[�^�ǂݍ��ݗp�̃|�C���^
		 * @param	size			�f�[�^�T�C�Y
		 */
		virtual void				read( const KsRenderContext* pContext, void* pData, KsUInt32 size );

		/**
		 * �C���f�b�N�X�o�b�t�@�ւ̏�������
		 * @param	pContext		�`��R���e�L�X�g
		 * @param	pData			�f�[�^�ǂݍ��ݗp�̃|�C���^
		 * @param	size			�f�[�^�T�C�Y
		 */
		virtual void				write( const KsRenderContext* pContext, void* pData, KsUInt32 size );

		/**
		 * ���_�o�b�t�@���擾
		 * @return					���_�o�b�t�@�̃|�C���^
		 */
		ID3D11Buffer*				getVertexBuffer() { return m_pVertexBuffer; }

	private:
		KsRenderSystemDX11*			m_pRenderSystem;	/**< �`��V�X�e��			*/
		ID3D11Buffer*				m_pVertexBuffer;	/**< DirectX���_�o�b�t�@		*/
		D3D11_MAPPED_SUBRESOURCE	m_resource;			/**< �A�N�Z�X�p���\�[�X		*/
};


#endif		/* __KSVERTEXBUFFERDX11_H__ */


