/************************************************************************************************/
/** 
 * @file		KsMaterial.cpp
 * @brief		マテリアル
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"
#include "KsMaterial.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * コンストラクタ( マテリアルをセットする )
 * @param	pDiffuse			ディフューズ色
 * @param	pAmbient			アンビエント色
 * @param	pSpecular			スペキュラ色
 * @param	pEmissive			エミッション色
 * @param	power				スペキュラ ハイライトの鮮明
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
 * コンストラクタ( マテリアルをセットする )
 * @param	refDiffuse			ディフューズ色
 * @param	refAmbient			アンビエント色
 * @param	refSpecular			スペキュラ色
 * @param	refEmissive			エミッション色
 * @param	power				スペキュラ ハイライトの鮮明
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
 * コピーコンストラクタ
 * @param	refMaterial			マテリアル
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
 * コピーコンストラクタ
 * @param	pMaterial			マテリアル
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
 * マテリアルをセットする
 * @param	refDiffuse			ディフューズ色
 * @param	refAmbient			アンビエント色
 * @param	refSpecular			スペキュラ色
 * @param	refEmissive			エミッション色
 * @param	power				スペキュラ ハイライトの鮮明
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
 * マテリアルをセットする
 * @param	pDiffuse			ディフューズ色
 * @param	pAmbient			アンビエント色
 * @param	pSpecular			スペキュラ色
 * @param	pEmissive			エミッション色
 * @param	power				スペキュラ ハイライトの鮮明
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
 * マテリアルをセットする
 * @param	refMaterial			マテリアル
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
 * マテリアルをセットする
 * @param	pMaterial			マテリアル
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

