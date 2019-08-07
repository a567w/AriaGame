/************************************************************************************************/
/** 
 * @file		KsShaderManagerDX11.h
 * @brief		�V�F�[�_�[�}�l�[�W���[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSHADERMANAGERDX11_H__
#define __KSSHADERMANAGERDX11_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsRenderSystemDX;

/************************************************************************************************/
/**
 * @class		KsShaderManager
 * @brief		�V�F�[�_�[�}�l�[�W���[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		�{���́A�n�b�V���e�[�u���Ȃǂ��g�p�����ق������������܂�e�N�X�`���}�e���A���́A
 *				���܂�A�g��Ȃ��͂��Ȃ̂Ő��`�ŒT������B
 */
/************************************************************************************************/
class ksDEVDX11_API KsShaderManagerDX11 : public KsShaderManager
{
	public:
		/**
		 * �R���X�g���N�^
		 * @param	pRenderSystem		�`��V�X�e��
		 */
										KsShaderManagerDX11( KsRenderSystemDX11* pRenderSystem );

		/**
		 * �f�X�g���N�^
		 */
		virtual							~KsShaderManagerDX11();

		/**
		 * �t�@�C������V�F�[�_�[�𐶐�
		 * @param	pFileName			�t�@�C����
		 * @param	pEntryPoint			�G���g���[�|�C���g
		 * @param	shaderModel			�V�F�[�_�[���f��
		 * @param	shaderType			�V�F�[�_�[�^�C�v
		 * @return						�V�F�[�_�[�v���O�����̃|�C���^
		 */
		virtual KsShaderProgram*		createFromFile( const KsChar* pFileName, const KsChar* pEntryPoint, ksSHADER_MODEL_TYPE shaderModel, ksSHADER_TYPE shaderType );

		/**
		 * �f�[�^����V�F�[�_�[�𐶐�
		 * @param	pData				�f�[�^
		 * @param	dataSize			�f�[�^�T�C�Y
		 * @param	shaderType			�V�F�[�_�[�^�C�v
		 * @return						�V�F�[�_�[�v���O�����̃|�C���^
		 */
		virtual KsShaderProgram*		createFromMemory( const void* pData, KsUInt32 dataSize, ksSHADER_TYPE shaderType );

		/**
		 * �t�@�C������V�F�[�_�[�𐶐�
		 * @param	pFileName			�t�@�C����
		 * @param	pEntryPoint			�G���g���[�|�C���g
		 * @param	shaderModel			�V�F�[�_�[���f��
		 * @param	shaderType			�V�F�[�_�[�^�C�v
		 * @return						�V�F�[�_�[�v���O�����̃|�C���^
		 */
		virtual KsShaderProgram*		createFromResource( const KsChar* pFileName, const KsChar* pEntryPoint, ksSHADER_MODEL_TYPE shaderModel, ksSHADER_TYPE shaderType );

	private:
		KsRenderSystemDX11*				m_pRenderSystem;						/**< �`��V�X�e��	*/
};

#endif		/* __KSSHADERMANAGERDX11_H__ */

