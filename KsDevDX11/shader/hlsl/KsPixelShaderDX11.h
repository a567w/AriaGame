/************************************************************************************************/
/** 
 * @file		KsPixelShaderDX11.h
 * @brief		�s�N�Z���V�F�[�_�[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSPIXELSHADERDX11_H__
#define __KSPIXELSHADERDX11_H__

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
 * @class		KsPixelShaderDX11
 * @brief		�s�N�Z���V�F�[�_�[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		
 */
/************************************************************************************************/
class ksDEVDX11_API KsPixelShaderDX11 : public KsPixelShader
{
		friend class KsRenderContextDX11;
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsPixelShaderDX11( KsRenderSystemDX11* pRenderSystem );

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsPixelShaderDX11();

		/**
		 * �t�@�C������s�N�Z���V�F�[�_�[�𐶐�����
		 * @param	pFileName		�t�@�C����
		 * @param	pEntryPoint		�G���g���[�|�C���g
		 * @param	shaderModel		�V�F�[�_�[���f��
		 * @retval	ksTRUE			��������
		 * @retval	ksFALSE			�������s
		 */
		virtual KsBool				createFromFile( const KsChar* pFileName, const KsChar* pEntryPoint, ksSHADER_MODEL_TYPE shaderModel );

		/**
		 * �f�[�^����s�N�Z���V�F�[�_�[�𐶐�����
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

	private:
		KsRenderSystemDX11*			m_pRenderSystem;
		ID3D11PixelShader*			m_pPixelShader;
};


#endif		/* __KSPIXELSHADERDX11_H__ */

