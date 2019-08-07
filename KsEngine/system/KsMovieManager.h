/************************************************************************************************/
/** 
 * @file		KsMovieManager.h
 * @brief		���[�r�[�}�l�[�W��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMOVIEMANAGER_H__
#define __KSMOVIEMANAGER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsMovie.h"
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
 * @class		KsMovieManager
 * @brief		���[�r�[�}�l�[�W��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsMovieManager : public KsSingleton< KsMovieManager >
{
	public:
		/**
		 * �V���O���g���̎Q�Ƃ��擾
		 * @return							�V���O���g���̎Q��
		 */
		static KsMovieManager&			getInstance();
		
		/**
		 * �V���O���g���̃|�C���^���擾
		 * @return							�V���O���g���̃|�C���^
		 */
		static KsMovieManager*			getInstancePtr();

	public:
										KsMovieManager( KsRenderSystem* pRenderSystem );

		virtual						~KsMovieManager();

		virtual KsMovie*				createFromFile( const KsChar* pFileName );

	protected:
		KsRenderSystem*					m_pRenderSystem;
};

#endif		/* __KSMOVIEMANAGER_H__ */










