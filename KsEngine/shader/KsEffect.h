/************************************************************************************************/
/** 
 * @file		KsEffect.h
 * @brief		�G�t�F�N�g�t�@�C��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSEFFECT_H__
#define __KSEFFECT_H__

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
 * @class		KsEffect
 * @brief		�G�t�F�N�g�t�@�C��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		
 */
/************************************************************************************************/
class ksENGINE_API KsEffect
{
		friend class KsShaderManager;
	public:
		/**
		 * �R���X�g���N�^
		 */
										KsEffect();

		/**
		 * �f�X�g���N�^
		 */
		virtual							~KsEffect();

		virtual	void					setShader( KsRenderContext* pRenderContext, void* pParameter );

		KsVertexShader*					getVertexShader( KsUInt32 index=0 );
		KsPixelShader*					getPixelShader( KsUInt32 index=0 );
		KsGeometryShader*				getGeometryShader( KsUInt32 index=0 );
		KsComputeShader*				getComputeShader( KsUInt32 index=0 );
		KsInputLayout*					getInputLayout( KsUInt32 index=0 );
		KsVertexBuffer*					getVertexBuffer( KsUInt32 index=0 );
		KsIndexBuffer*					getIndexBuffer( KsUInt32 index=0 );

		void							addVertexShader( KsVertexShader* pShader );
		void							addPixelShader( KsPixelShader* pShader );
		void							addGeometryShader( KsGeometryShader* pShader );
		void							addComputeShader( KsComputeShader* pShader );

		void							addInputLayout( KsInputLayout* pLayout );
		void							addVertexBuffer( KsVertexBuffer* pVertexBuffer );
		void							addIndexBuffer( KsIndexBuffer* pIndexBuffer );

		KsUInt32						getVertexShaderCount() const;
		KsUInt32						getPixelShaderCount() const;
		KsUInt32						getGeometryShaderCount() const;
		KsUInt32						getComputeShaderCount() const;
		KsUInt32						getInputLayoutCount() const;
		KsUInt32						getVertexBufferCount() const;
		KsUInt32						getIndexBufferCount() const;

	protected:
		KsArray<KsVertexShader*>		m_pVertexShaders;
		KsArray<KsPixelShader*>			m_pPixelShaders;
		KsArray<KsGeometryShader*>		m_pGeometryShaders;
		KsArray<KsComputeShader*>		m_pComputeShaders;

		KsArray<KsInputLayout*>			m_pInputLayouts;		/**< ���_�o�b�t�@			*/
		KsArray<KsVertexBuffer*>		m_pVertexBuffers;		/**< �C���f�b�N�X�o�b�t�@		*/
		KsArray<KsIndexBuffer*>			m_pIndexBuffers;		/**< �C���v�b�g���C�A�E�g		*/
};


#endif		/* __KSEFFECT_H__ */

