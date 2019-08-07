/************************************************************************************************/
/** 
 * @file		KsShaderManagerHLSL.h
 * @brief		�V�F�[�_�[�}�l�[�W���[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSSHADERMANAGERHLSL_H__
#define __KSSHADERMANAGERHLSL_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsTypeD3D9.h"

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
class ksDEVD3D9_API KsShaderManagerHLSL : public KsShaderManager
{
	public:
		/**
		 * �R���X�g���N�^
		 * @param	pRenderSystem		�`��V�X�e��
		 */
										KsShaderManagerHLSL( KsRenderSystemDX* pRenderSystem );

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsShaderManagerHLSL();

		/**
		 * �t�@�C������V�F�[�_�[�𐶐�
		 * @param	pName				�V�F�[�_�[��
		 * @param	bCompiled			�R���p�C���ς݂��ǂ����̃t���O
		 * @return						�V�F�[�_�[�f�[�^�̃|�C���^
		 */
		virtual KsShader*				createFromFile( const KsChar* pName, KsBool _bCompiled );

		/**
		 * ���\�[�X����V�F�[�_�[�𐶐�
		 * @param	pName				�V�F�[�_�[��
		 * @param	bCompiled			�R���p�C���ς݂��ǂ����̃t���O
		 * @return						�V�F�[�_�[�f�[�^�̃|�C���^
		 */
		virtual KsShader*				createFromResource( const KsChar* pName, KsBool _bCompiled );

		virtual void					setVertexShaderConstantB( KsUInt32 startRegister, const KsBool*  pConstantData, KsUInt32 count );
		virtual void					setVertexShaderConstantF( KsUInt32 startRegister, const KsReal*  pConstantData, KsUInt32 count );
		virtual void					setVertexShaderConstantI( KsUInt32 startRegister, const KsInt32* pConstantData, KsUInt32 count );

		virtual void					setPixelShaderConstantB( KsUInt32 startRegister, const KsBool*  pConstantData, KsUInt32 count );
		virtual void					setPixelShaderConstantF( KsUInt32 startRegister, const KsReal*  pConstantData, KsUInt32 count );
		virtual void					setPixelShaderConstantI( KsUInt32 startRegister, const KsInt32* pConstantData, KsUInt32 count );

	private:
		D3DXHANDLE						m_handls[ ksSHADER_GLOBAL_DATA_MAX ];	/**< �n���h�����X�g	*/
		KsRenderSystemDX*				m_pRenderSystem;						/**< �`��V�X�e��	*/
};

#endif		/* __KSSHADERMANAGERHLSL_H__ */

