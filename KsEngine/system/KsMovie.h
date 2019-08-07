/************************************************************************************************/
/** 
 * @file		KsMovie.h
 * @brief		
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMOVIE_H__
#define __KSMOVIE_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsType.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsTexture;

/************************************************************************************************/
/**
 * @class		KsMovie
 * @brief		���[�r�[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsMovie
{
	public:
		/**
		 * �R���X�g���N�^
		 */
								KsMovie();

		/**
		 * �f�X�g���N�^
		 */
		virtual				~KsMovie();

		virtual KsBool			play()   = 0;
		virtual void			stop()   = 0;
		virtual KsBool			isPlay() = 0;
		virtual KsTexture*		getTexture() = 0;
		virtual KsBool			loadFromFile( const KsChar* pFileName ) = 0;
};

#endif		/* __KSMOVIE_H__ */


