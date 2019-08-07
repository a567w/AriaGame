/************************************************************************************************/
/** 
 * @file		KsShader.h
 * @brief		�V�F�[�_�[�}�l�[�W���[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSSHADER_H__
#define __KSSHADER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsType.h"
#include "KsRefCounter.h"
#include "KsString.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsShader
 * @brief		�V�F�[�_�[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		
 */
/************************************************************************************************/
class ksENGINE_API KsShader : public KsRefCounter
{
		friend class KsShaderManager;

	public:

		/**
		 * �V�F�[�_�[�^�C�v
		 */
		enum ksSHADER_TYPE
		{
			ksPIXEL_SHADER,
			ksVERTEX_SHADER,
			ksPIXEL_AND_VERTEX_SHADER,
		};

	public:
		/**
		 * �R���X�g���N�^
		 */
									KsShader();

		/**
		 * �f�X�g���N�^
		 */
		virtual					~KsShader();

		/**
		 * �V�F�[�_�J�n
		 */
		virtual void				begine() = 0;

		/**
		 * �V�F�[�_�I��
		 */
		virtual void				end() = 0;

		/**
		 * �w��p�X�J�n
		 */
		virtual void				beginePass( KsUInt32 pass ) = 0;

		/**
		 * �p�X�I��
		 */
		virtual void				endPass() = 0;

		/**
		 * �e�N�j�b�N���Z�b�g����
		 * @param	index			�e�N�j�b�N�C���f�b�N�X
		 */
		virtual void				setTechnique( KsUInt32 index ) = 0;

		/**
		 * �e�N�j�b�N���Z�b�g����
		 * @param	hTechnique		�e�N�j�b�N�n���h��
		 */
		virtual void				setTechnique( KsHandle hTechnique ) = 0;

		/**
		  * �e�N�j�b�N���Z�b�g����
		 * @param	pTechniqueName	�e�N�j�b�N��
		 */
		virtual void				setTechnique( const KsChar* pTechniqueName ) = 0;

		/**
		 * �e�N�j�b�N�̃n���h���擾����
		 * @param	pTechniqueName	�e�N�j�b�N��
		 * @return					�e�N�j�b�N�̃n���h��
		 */
		virtual KsHandle			getTechnique( const KsChar* pTechniqueName ) = 0;

		virtual void				setVertexShaderConstantB( KsUInt32 startRegister, const KsBool*  pConstantData, KsUInt32 count ) = 0;
		virtual void				setVertexShaderConstantF( KsUInt32 startRegister, const KsReal*  pConstantData, KsUInt32 count ) = 0;
		virtual void				setVertexShaderConstantI( KsUInt32 startRegister, const KsInt32* pConstantData, KsUInt32 count ) = 0;

		virtual void				setPixelShaderConstantB( KsUInt32 startRegister, const KsBool*  pConstantData, KsUInt32 count ) = 0;
		virtual void				setPixelShaderConstantF( KsUInt32 startRegister, const KsReal*  pConstantData, KsUInt32 count ) = 0;
		virtual void				setPixelShaderConstantI( KsUInt32 startRegister, const KsInt32* pConstantData, KsUInt32 count ) = 0;

		/**
		 * �V�F�[�_�[ID���擾����
		 * @return					�V�F�[�_�[ID
		 */
		KsUInt32					getID() const { return m_id; }

		/**
		 * �V�F�[�_�[�����擾����
		 * @return					�V�F�[�_�[��
		 */
		const KsString&				getName() { return m_name; }

		/**
		 * ���݂̃e�N�j�b�N�ԍ����擾����
		 * @return					���݂̃e�N�j�b�N�ԍ�
		 */
		KsHandle					getCurrentTechnique() const { return m_hCurrentTechnique; }

		/** 
		 * �e�N�j�b�N�����擾����
		 * @return					�e�N�j�b�N��
		 */
		KsUInt32					getNumTechnique() const { return m_numTechnique; }

		/**
		 * �p�X�����擾����
		 * @return					�p�X��
		 */
		KsUInt32					getNumPass() const { return m_numPass; }

	protected:
		KsUInt32					m_id;					/**< �V�F�[�_�[ID				*/
		KsString					m_name;					/**< �V�F�[�_�[��				*/
		KsHandle					m_hCurrentTechnique;	/**< �g�p�e�N�j�b�N�C���f�b�N�X	*/
		KsUInt32					m_numTechnique;			/**< �e�N�j�b�N��				*/
		KsUInt32					m_numPass;				/**< �p�X��						*/

		//void						setViewMatrx();
		//void						setVierProjMatrix();
		//void						setTime();
};


#endif		/* __KSSHADER_H__ */

