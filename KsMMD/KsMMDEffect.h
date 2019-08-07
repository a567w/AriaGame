/************************************************************************************************/
/** 
 * @file		KsPMD.h
 * @brief		PMD�t�@�C��
 * @author		Tsukasa Kato
 * @date		2010/12/17
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMMDEFFECT_H__
#define __KSMMDEFFECT_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                          */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsEffectMMD
 * @brief		Effect
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksMMD_API KsEffectMMD : public KsEffect
{
	public:
		void				setDiffuse( KsReal r, KsReal g, KsReal b, KsReal a ) { m_diffuse.set( r, g, b, a ); }
		void				setAmbient( KsReal r, KsReal g, KsReal b, KsReal a ) { m_ambient.set( r, g, b, a ); }
		void				setSpecular( KsReal r, KsReal g, KsReal b, KsReal a ) { m_specular.set( r, g, b, a ); }
		void				setSpecularity( KsReal specularity ) { m_specularity = specularity; }
		void				setDiffuseTextureName( const KsString& diffuseTextureName ) { m_diffuseTextureName = diffuseTextureName; }
		void				setDiffuseTexture( KsTexture* pDiffuseTexture ) { m_pDiffuseTexture = pDiffuseTexture; }
		virtual	void		setShader( KsRenderContext* pRenderContext, void* pParameter );
		
		const KsVector4d&	getDiffuse() { return m_diffuse; }
		const KsVector4d&	getAmbient() { return m_ambient; }
		const KsVector4d&	getSpecular() { return m_specular; }
		KsReal				getSpecularity() const { return m_specularity; }

		KsTexture*			getDiffuseTexture() { return m_pDiffuseTexture; }

		KsEffectMMD();

	private:
		KsVector4d			m_diffuse;			/// �f�B�t���[�Y
		KsVector4d			m_ambient;			/// ���F(ambient)
		KsVector4d			m_specular;			/// �X�y�L�����[�J���[
		KsReal				m_specularity;		/// �X�y�L�����l

	public:
		KsString			m_diffuseTextureName;	///
		KsTexture*			m_pDiffuseTexture;
		KsVertexShader*		m_pVS;
		KsPixelShader*		m_pPS;
		KsConstantBuffer*	m_pCB;
		KsConstantBuffer*	m_pMB;
};

#endif /* __KSMMDEFFECT_H__ */
