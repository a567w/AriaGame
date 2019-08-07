/************************************************************************************************/
/** 
 * @file		KsMaterial.cpp
 * @brief		�}�e���A��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"
#include "KsMaterial.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * �R���X�g���N�^( �}�e���A�����Z�b�g���� )
 * @param	pDiffuse			�f�B�t���[�Y�F
 * @param	pAmbient			�A���r�G���g�F
 * @param	pSpecular			�X�y�L�����F
 * @param	pEmissive			�G�~�b�V�����F
 * @param	power				�X�y�L���� �n�C���C�g�̑N��
 */
/************************************************************************************************/
KsMaterial::KsMaterial( const KsColorReal* pDiffuse, const KsColorReal* pAmbient, const KsColorReal* pSpecular, const KsColorReal* pEmissive, KsReal power )
{
	m_diffuse.set( pDiffuse );
	m_ambient.set( pAmbient );
	m_specular.set( pSpecular );
	m_emissive.set( pEmissive );
	m_power = power;
}

/************************************************************************************************/
/*
 * �R���X�g���N�^( �}�e���A�����Z�b�g���� )
 * @param	refDiffuse			�f�B�t���[�Y�F
 * @param	refAmbient			�A���r�G���g�F
 * @param	refSpecular			�X�y�L�����F
 * @param	refEmissive			�G�~�b�V�����F
 * @param	power				�X�y�L���� �n�C���C�g�̑N��
 */
/************************************************************************************************/
KsMaterial::KsMaterial( const KsColorReal& refDiffuse, const KsColorReal& refAmbient, const KsColorReal& refSpecular, const KsColorReal& refEmissive, KsReal power )
{
	m_diffuse.set( refDiffuse );
	m_ambient.set( refAmbient );
	m_specular.set( refSpecular );
	m_emissive.set( refEmissive );
	m_power = power;
}

/************************************************************************************************/
/*
 * �R�s�[�R���X�g���N�^
 * @param	refMaterial			�}�e���A��
 */
/************************************************************************************************/
KsMaterial::KsMaterial( const KsMaterial& refMaterial )
{
	m_diffuse.set( refMaterial.m_diffuse );
	m_ambient.set( refMaterial.m_ambient );
	m_specular.set( refMaterial.m_specular );
	m_emissive.set( refMaterial.m_emissive );
	m_power = refMaterial.m_power;
}

/************************************************************************************************/
/*
 * �R�s�[�R���X�g���N�^
 * @param	pMaterial			�}�e���A��
 */
/************************************************************************************************/
KsMaterial::KsMaterial( const KsMaterial* pMaterial )
{
	m_diffuse.set( pMaterial->m_diffuse );
	m_ambient.set( pMaterial->m_ambient );
	m_specular.set( pMaterial->m_specular );
	m_emissive.set( pMaterial->m_emissive );
	m_power = pMaterial->m_power;
}

/************************************************************************************************/
/*
 * �}�e���A�����Z�b�g����
 * @param	refDiffuse			�f�B�t���[�Y�F
 * @param	refAmbient			�A���r�G���g�F
 * @param	refSpecular			�X�y�L�����F
 * @param	refEmissive			�G�~�b�V�����F
 * @param	power				�X�y�L���� �n�C���C�g�̑N��
 */
/************************************************************************************************/
void KsMaterial::set( const KsColorReal& refDiffuse, const KsColorReal& refAmbient, const KsColorReal& refSpecular, const KsColorReal& refEmissive, KsReal power )
{
	m_diffuse.set( refDiffuse );
	m_ambient.set( refAmbient );
	m_specular.set( refSpecular );
	m_emissive.set( refEmissive );
	m_power = power;
}

/************************************************************************************************/
/*
 * �}�e���A�����Z�b�g����
 * @param	pDiffuse			�f�B�t���[�Y�F
 * @param	pAmbient			�A���r�G���g�F
 * @param	pSpecular			�X�y�L�����F
 * @param	pEmissive			�G�~�b�V�����F
 * @param	power				�X�y�L���� �n�C���C�g�̑N��
 */
/************************************************************************************************/
void KsMaterial::set( const KsColorReal* pDiffuse, const KsColorReal* pAmbient, const KsColorReal* pSpecular, const KsColorReal* pEmissive, KsReal power )
{
	m_diffuse.set( pDiffuse );
	m_ambient.set( pAmbient );
	m_specular.set( pSpecular );
	m_emissive.set( pEmissive );
	m_power = power;
}

/************************************************************************************************/
/*
 * �}�e���A�����Z�b�g����
 * @param	refMaterial			�}�e���A��
 */
/************************************************************************************************/
void KsMaterial::set( const KsMaterial& refMaterial )
{
	m_diffuse.set( refMaterial.m_diffuse );
	m_ambient.set( refMaterial.m_ambient );
	m_specular.set( refMaterial.m_specular );
	m_emissive.set( refMaterial.m_emissive );
	m_power    = refMaterial.m_power;
	m_pTexture = refMaterial.m_pTexture;
}

/************************************************************************************************/
/*
 * �}�e���A�����Z�b�g����
 * @param	pMaterial			�}�e���A��
 */
/************************************************************************************************/
void KsMaterial::set( const KsMaterial* pMaterial )
{
	m_diffuse.set( pMaterial->m_diffuse );
	m_ambient.set( pMaterial->m_ambient );
	m_specular.set( pMaterial->m_specular );
	m_emissive.set( pMaterial->m_emissive );
	m_power    = pMaterial->m_power;
	m_pTexture = pMaterial->m_pTexture;
}

