/************************************************************************************************/
/** 
 * @file		KsIndexBufferDX11.h
 * @brief		�C���f�b�N�X�o�b�t�@
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSINDEXBUFFERDX11_H__
#define __KSINDEXBUFFERDX11_H__

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
 * @class		KsIndexBufferDX
 * @brief		�C���f�b�N�X�o�b�t�@
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksDEVDX11_API KsIndexBufferDX11 : public KsIndexBuffer
{
		friend class KsRenderContextDX11;
	public:
		/**
		 * �R���X�g���N�^
		 * @param	pRenderSystem	�`��V�X�e��
		 * @param	pData			�f�[�^�ǂݍ��ݗp�̃|�C���^
		 * @param	size			�f�[�^�T�C�Y
		 * @param	numIndex		�C���f�b�N�X�̐�
		 * @param	indexFormat		�C���f�b�N�X�t�H�[�}�b�g
		 * @param	flags			�t���O
		 */
									KsIndexBufferDX11( KsRenderSystemDX11* pRenderSystem, void* pData, KsUInt32 size, KsUInt32 numIndex, KsUInt32 indexFormat, KsUInt32 flags );

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsIndexBufferDX11();

		/**
		 * �C���f�b�N�X�o�b�t�@�𐶐�����
		 * @param	pRenderSystem	�`��V�X�e��
		 * @param	pData			�f�[�^�ǂݍ��ݗp�̃|�C���^
		 * @param	size			�f�[�^�T�C�Y
		 * @param	numIndex		�C���f�b�N�X�̐�
		 * @param	indexFormat		�C���f�b�N�X�t�H�[�}�b�g
		 * @param	flags			�t���O
		 * @retval	ksTRUE			��������
		 * @retval	ksFALSE			�������s
		 */
		virtual KsBool				create( KsRenderSystemDX11* pRenderSystem, void* pData, KsUInt32 size, KsUInt32 numIndex, KsUInt32 indexFormat, KsUInt32 flags );

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
		 * �C���f�b�N�X�o�b�t�@�����b�N����
		 * @param	pContext		�`��R���e�L�X�g
		 * @param	flags			���b�N�t���O
		 * @return					���b�N�����o�b�t�@�̐擪�|�C���^
		 */
		virtual void*				lock( const KsRenderContext* pContext, KsUInt32 flags );

		/**
		 * �C���f�b�N�X�o�b�t�@�̃��b�N����������
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
		 * �C���f�b�N�X�o�b�t�@�o�b�t�@���擾
		 * @return					�C���f�b�N�X�o�b�t�@�̃|�C���^
		 */
		ID3D11Buffer*				getIndexBuffer() { return m_pIndexBuffer; }

	private:
		KsRenderSystemDX11*			m_pRenderSystem;	/**< �`��V�X�e��				*/
		ID3D11Buffer*				m_pIndexBuffer;		/**< DirectX�C���f�b�N�X�o�b�t�@	*/
		KsUInt32					m_indexSize;		/**< �C���f�b�N�X�T�C�Y			*/
		D3D11_MAPPED_SUBRESOURCE	m_resource;			/**< �A�N�Z�X�p���\�[�X			*/
};


#endif		/* __KSINDEXBUFFERDX11_H__ */


