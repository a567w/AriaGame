/************************************************************************************************/
/** 
 * @file		KsFontManager.cpp
 * @brief		
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsFontManager.h"
#include "KsFontData.h"
#include "KsFile.h"
#include "KsXmlTextReader.h"
#include "KsRenderSystem.h"
#include "KsTexture.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
template<> KsFontManager* KsSingleton< KsFontManager >::m_pInstance = 0;

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsFontManager& KsFontManager::getInstance()
{  
	return (*m_pInstance);  
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsFontManager* KsFontManager::getInstancePtr()
{
	return m_pInstance;
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsFontManager::KsFontManager( KsRenderSystem* pRenderSystem )
	: m_pRenderSystem( pRenderSystem )
{
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsFontManager::~KsFontManager()
{
	ksDELETEARRAYTEMPLATE( m_vpFonts );
}

/************************************************************************************************/
/*
 * �t�H���g����
 * @param		pFileName			�t�@�C����
 * @return							�t�H���g�f�[�^
 */
/************************************************************************************************/
KsFont* KsFontManager::createFromXml( const KsChar* pFileName )
{
	KsXmlTextReader*	pXmlReader = new KsXmlTextReader( pFileName );
	KsFontData*			pFontData  = new KsFontData();
	KsFont*				pFont      = NULL;
	KsTexture*			pTexture   = NULL;
	KsFile				file;
	KsString			strLayoutName;
	KsString			strTextureName;

	while( pXmlReader->read() )
	{
		const KsChar*	pName    = pXmlReader->getName();
		KsXmlNodeType	nodeType = pXmlReader->getNodeType();

		switch( nodeType )
		{
			case ksXmlElement:
			{
				if( strcmp( pName, "layout" ) == 0 )
				{
					pXmlReader->read();
					strLayoutName = pXmlReader->getValue();

					file.open( strLayoutName, ksFILE_FLAG_DEFAULT );
					pFontData->create( file );
				}
				else if( strcmp( pName, "texture" ) == 0 )
				{
					pXmlReader->read();
					strTextureName = pXmlReader->getValue();
					pTexture       = m_pRenderSystem->createTextureFromFile( strTextureName.c_str(), 0 );
					pFontData->addTexture( pTexture );
				}
				break;
			}
			case ksXmlText:
			{
				break;
			}
			case ksXmlEndElement:
			{
				break;
			}
			default: break;
		}
	}

	ksDELETE( pXmlReader );

	/* �t�H���g���� */
	pFont = new KsFont( m_pRenderSystem, pFontData );

	/* �t�H���g�ǉ� */
	addFont( pFont );

	return pFont;
}

/************************************************************************************************/
/*
 * �t�H���g�폜
 */
/************************************************************************************************/
/*
KsBool KsFontManager::destroyFont( KsFont* pFont )
{
	for( KsUInt32 i=0; i<m_vpFonts.size(); i++ )
	{
		KsFont*	pFontTemp = m_vpFonts[ i ];

		if( pFontTemp == pFont )
		{
			m_vpFonts.erase( i );
			ksDELETE( pFontTemp );
			return ksTRUE;
		}
	}

	return ksFALSE;
}
*/

