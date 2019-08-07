/************************************************************************************************/
/** 
 * @file		KsStructuredBufferDX11.h
 * @brief		UAV�N���X
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSTRUCTUREBUFFERDX11_H__
#define __KSSTRUCTUREBUFFERDX11_H__

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
 * @class		KsStructuredBuffer
 * @brief		UAV�N���X
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		�Q�ƃJ�E���^��
 */
/************************************************************************************************/
class ksDEVDX11_API KsStructuredBufferDX11 : public KsStructuredBuffer
{
		friend class KsRenderContextDX11;
	public:
		/**
		 * �R���X�g���N�^( UAV�o�b�t�@�𐶐����� )
		 * @param	pRenderSystem	�`��V�X�e��
		 * @param	elementSize		�v�f�T�C�Y
		 * @param	numElements		�v�f��
		 * @param	format			�t�H�[�}�b�g
		 * @param	flags			�t���O
		 */
									KsStructuredBufferDX11( KsRenderSystemDX11* pRenderSystem, KsUInt32 elementSize, KsUInt32 numElements, KsUInt32 format, KsUInt32 flags );

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsStructuredBufferDX11();

		/**
		 * UAV�o�b�t�@�𐶐�����
		 * @param	pRenderSystem	�`��V�X�e��
		 * @param	elementSize		�v�f�T�C�Y
		 * @param	numElements		�v�f��
		 * @param	format			�t�H�[�}�b�g
		 * @param	flags			�t���O
		 * @retval	ksTRUE			��������
		 * @retval	ksFALSE			�������s
		 */
		virtual KsBool				create( KsRenderSystemDX11* pRenderSystem, KsUInt32 elementSize, KsUInt32 numElements, KsUInt32 format, KsUInt32 flags );

		/**
		 * �j������
		 */
		virtual void				destroy();

		/**
		 * �e�N�X�`�����A�N�e�B�u�ɂ���
		 */
		virtual void				active();

		/**
		 * ���\�[�X���擾����
		 * @return					 ���\�[�X
		 */
		virtual void*				getBufferResource();

		/**
		 * ���\�[�X���擾����
		 * @return					���\�[�X
		 */
		virtual void*				getTextureResource() { return m_pShaderResourceView; }

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

	private:
		KsUInt32					m_elementSize;
		KsUInt32					m_numElements;
		KsUInt32					m_format;
		ID3D11Buffer*				m_pBuffer;
		ID3D11ShaderResourceView*	m_pShaderResourceView;
		ID3D11UnorderedAccessView*	m_pUnorderedAccessView;
};

#endif		/* __KSSTRUCTUREBUFFERDX11_H__ */



