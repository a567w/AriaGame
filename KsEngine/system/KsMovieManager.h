/************************************************************************************************/
/** 
 * @file		KsMovieManager.h
 * @brief		ムービーマネージャ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMOVIEMANAGER_H__
#define __KSMOVIEMANAGER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsMovie.h"
#include "KsSingleton.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsRenderSystem;

/************************************************************************************************/
/**
 * @class		KsMovieManager
 * @brief		ムービーマネージャ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsMovieManager : public KsSingleton< KsMovieManager >
{
	public:
		/**
		 * シングルトンの参照を取得
		 * @return							シングルトンの参照
		 */
		static KsMovieManager&			getInstance();
		
		/**
		 * シングルトンのポインタを取得
		 * @return							シングルトンのポインタ
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











