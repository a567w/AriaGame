/************************************************************************************************/
/** 
 * @file		KsMovieManager.cpp
 * @brief		
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsMovieManager.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
template<> KsMovieManager* KsSingleton< KsMovieManager >::m_pInstance = 0;

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsMovieManager& KsMovieManager::getInstance()
{  
	return (*m_pInstance);  
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsMovieManager* KsMovieManager::getInstancePtr()
{
	return m_pInstance;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsMovieManager::KsMovieManager( KsRenderSystem* pRenderSystem )
	: m_pRenderSystem( pRenderSystem )
{
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsMovieManager::~KsMovieManager()
{
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsMovie* KsMovieManager::createFromFile( const KsChar* pFileName )
{
#if 0
	KsMovie* pMovie = new KsMovie( this );

	char FilePath[MAX_PATH];
	if ( !LunaFile::GetFilePath( FilePath, pFile ) ) return NULL;

	if ( !pVMR->LoadFromFile( FilePath ) )
	{
		pVMR->Release();
		return NULL;
	}

	return pVMR;
#endif 
	return NULL;
}

