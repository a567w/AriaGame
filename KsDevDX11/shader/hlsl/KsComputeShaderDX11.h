/************************************************************************************************/
/** 
 * @file		KsComputeShaderDX11.h
 * @brief		�R���s���[�g�V�F�[�_�[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSCOMPUTESHADERDX11_H__
#define __KSCOMPUTESHADERDX11_H__

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
 * @class		KsComputeShaderDX11
 * @brief		�R���s���[�g�V�F�[�_�[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		
 */
/************************************************************************************************/
class ksDEVDX11_API KsComputeShaderDX11 : public KsComputeShader
{
		friend class KsRenderContextDX11;
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsComputeShaderDX11( KsRenderSystemDX11* pRenderSystem );

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsComputeShaderDX11();

		/**
		 * �t�@�C�����璸�_�V�F�[�_�[�𐶐�����
		 * @param	pFileName		�t�@�C����
		 * @param	shaderModel		�V�F�[�_�[���f��
		 * @retval	ksTRUE			��������
		 * @retval	ksFALSE			�������s
		 */
		virtual KsBool				createFromFile( const KsChar* pFileName, const KsChar* pEntryPoint, ksSHADER_MODEL_TYPE shaderModel );

		/**
		 * �f�[�^����R���s���[�g�V�F�[�_�[�𐶐�����
		 * @param	pData			�f�[�^
		 * @param	dataSize		�f�[�^�T�C�Y
		 * @retval	ksTRUE			��������
		 * @retval	ksFALSE			�������s
		 */
		virtual KsBool				createFromMemory( const void* pData, KsUInt32 dataSize );

		/**
		 * �j������
		 */
		virtual void				destroy();
	
		/**
		 * �o�b�t�@�̃|�C���^���擾����
		 * @return					�o�b�t�@�̃|�C���^
		 */
		virtual const void*			getBufferPointer();

		/**
		 * �o�b�t�@�̃T�C�Y���擾����
		 * @return					�o�b�t�@�̃T�C�Y
		 */
		virtual KsUInt32			getBufferSize();

	private:
		KsRenderSystemDX11*			m_pRenderSystem;
		ID3D11ComputeShader*		m_pComputeShader;	/**< �R���s���[�g�V�F�[�_�[�I�u�W�F�N�g	*/
		ID3DBlob*					m_pBlob;			/**< �V�F�[�_�[�I�u�W�F�N�g				*/
		//KsShaderManagerDX11*		m_pShaderManager;	/**< �V�F�[�_�[�}�l�[�W��				*/
};


#endif		/* __KSCOMPUTESHADERDX11_H__ */

