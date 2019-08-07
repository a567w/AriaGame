/************************************************************************************************/
/** 
 * @file		KsShaderHLSL.h
 * @brief		�V�F�[�_�[�}�l�[�W���[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSSHADERHLSL_H__
#define __KSSHADERHLSL_H__

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
 * @class		KsShaderHLSL
 * @brief		�V�F�[�_�[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		
 */
/************************************************************************************************/
class ksDEVD3D9_API KsShaderHLSL : public KsShader
{
		friend class KsShaderManagerHLSL;

	public:
		/**
		 * �R���X�g���N�^
		 */
									KsShaderHLSL( KsRenderSystemDX* pRenderSystem );

		/**
		 * �f�X�g���N�^
		 */
		virtual					~KsShaderHLSL();

		/**
		 * �V�F�[�_�J�n
		 */
		virtual void				begine();

		/**
		 * �V�F�[�_�I��
		 */
		virtual void				end();

		/**
		 * �w��p�X�J�n
		 */
		virtual void				beginePass( KsUInt32 pass );

		/**
		 * �p�X�I��
		 */
		virtual void				endPass();

		/**
		 * �e�N�j�b�N���Z�b�g����
		 * @param	index			�e�N�j�b�N�C���f�b�N�X
		 */
		virtual void				setTechnique( KsUInt32 index );

		/**
		 * �e�N�j�b�N���Z�b�g����
		 * @param	hTechnique		�e�N�j�b�N�n���h��
		 */
		virtual void				setTechnique( KsHandle hTechnique );

		/**
		  * �e�N�j�b�N���Z�b�g����
		 * @param	pTechniqueName	�e�N�j�b�N��
		 */
		virtual void				setTechnique( const KsChar* pTechniqueName );

		/**
		 * �e�N�j�b�N�̃n���h���擾����
		 * @param	pTechniqueName	�e�N�j�b�N��
		 * @return					�e�N�j�b�N�̃n���h��
		 */
		virtual KsHandle			getTechnique( const KsChar* pTechniqueName );

		virtual void				setVertexShaderConstantB( KsUInt32 startRegister, const KsBool*  pConstantData, KsUInt32 count );
		virtual void				setVertexShaderConstantF( KsUInt32 startRegister, const KsReal*  pConstantData, KsUInt32 count );
		virtual void				setVertexShaderConstantI( KsUInt32 startRegister, const KsInt32* pConstantData, KsUInt32 count );

		virtual void				setPixelShaderConstantB( KsUInt32 startRegister, const KsBool*  pConstantData, KsUInt32 count );
		virtual void				setPixelShaderConstantF( KsUInt32 startRegister, const KsReal*  pConstantData, KsUInt32 count );
		virtual void				setPixelShaderConstantI( KsUInt32 startRegister, const KsInt32* pConstantData, KsUInt32 count );

#if 0
		KsHandle					getParameterByName( const KsChar* pName ) = 0;

		void						setVector( KsHandle handle, const KsVector4d* pValue ) = 0;
		void						setVectorArray( KsHandle handle, const KsVector4d* pValueArray, KsUInt32 count ) = 0;

		void						setInt( KsHandle handle, KsInt32 value ) = 0;
		void						setIntArray( KsHandle handle, const KsInt32* pValueArray, KsUInt32 count ) = 0;

		void						setBool( KsHandle handle, KsBool value ) = 0;
		void						setBoolArray( KsHandle handle, const KsBool* pValueArray, KsUInt32 count ) = 0;

		void						setFloat( KsHandle handle, KsReal value ) = 0;
		void						setFloatArray( KsHandle handle, const KsReal* pValueArray, KsUInt32 count ) = 0;

		void						setMatrix( KsHandle handle, const KsMatrix4x4* pValue ) = 0;
		void						setMatrixArray( KsHandle handle, const KsVector4d* pValueArray, KsUInt32 count ) = 0;

		void						setMatrixTranspose( KsHandle handle, const KsMatrix4x4* pValue ) = 0;
		void						setMatrixTransposeArray( KsHandle handle, const KsVector4d* pValueArray, KsUInt32 count ) = 0;
#endif

	private:
		void						initialize( const KsChar* pName, LPD3DXEFFECT pEffect );

	private:
		KsRenderSystemDX*			m_pRenderSystem;		/**< �`��V�X�e��		*/
		LPD3DXEFFECT				m_pEffect;				/**< �G�t�F�N�g			*/
		D3DXHANDLE*					m_hTechniques;			/**< �e�N�j�b�N�n���h��	*/
};


#endif		/* __KSSHADERHLSL_H__ */




