/************************************************************************************************/
/** 
 * @file		KsFontManager.h
 * @brief		
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSFONTMANAGER_H__
#define __KSFONTMANAGER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsType.h"
#include "KsArray.h"
#include "KsFont.h"
#include "KsSingleton.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsRenderSystem;

/************************************************************************************************/
/**
 * @class		KsFontManager
 * @brief		
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsFontManager : public KsSingleton< KsFontManager >
{
	public:
		/**
		 * �R���X�g���N�^
		 */
											KsFontManager( KsRenderSystem* pRenderSystem );

		/**
		 * �f�X�g���N�^
		 */
		virtual							~KsFontManager();

		/**
		 * �t�H���g����
		 * @param		pFileName			�t�@�C����
		 * @return							�t�H���g�f�[�^
		 */
		virtual KsFont*					createFromXml( const KsChar* pFileName );

		/**
		 * �t�H���g�폜
		 */
		//virtual KsBool					destroyFont( KsFont* pFont );

		/**
		 * �t�H���g��ǉ�����B
		 * @param		pFont				�t�H���g�f�[�^
		 * @return							�C���f�b�N�X
		 */
		KsUInt32							addFont( KsFont* pFont ) { m_vpFonts.push_back(pFont); return m_vpFonts.size(); }

		/**
		 * �t�H���g�f�[�^���擾
		 * @param		index				�C���f�b�N�X
		 * @return							�t�H���g�f�[�^
		 */
		KsFont*								getFont( KsUInt32 index=0 ) { return m_vpFonts[ index ]; }

		/**
		 * �V���O���g���̎Q�Ƃ��擾
		 * @return							�V���O���g���̎Q��
		 */
		static KsFontManager&				getInstance();
		
		/**
		 * �V���O���g���̃|�C���^���擾
		 * @return							�V���O���g���̃|�C���^
		 */
		static KsFontManager*				getInstancePtr();

	protected:
		KsRenderSystem*						m_pRenderSystem;
		KsArray< KsFont* >					m_vpFonts;
};

#endif		/* __KSFONTMANAGER_H__ */



