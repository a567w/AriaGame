/************************************************************************************************/
/** 
 * @file		KsGameResourceManager.cpp
 * @brief		�Q�[�����\�[�X
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "Aria/KsGamePreCompile.h"
#include "Aria/resource/KsGameResourceManager.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/
template<> KsGameResourceManager* KsSingleton< KsGameResourceManager >::m_pInstance = 0;

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsGameResourceManager& KsGameResourceManager::getInstance()
{  
	return (*m_pInstance);  
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsGameResourceManager* KsGameResourceManager::getInstancePtr()
{
	return m_pInstance;
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsGameResourceManager::KsGameResourceManager()
{
	create();
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsGameResourceManager::~KsGameResourceManager()
{
	destroy();
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsGameResourceManager::create()
{
	//m_vpTextures[ 0 ].push_back( );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsGameResourceManager::destroyTextures( ksTEXTURE_RESOURCE_TYPE type )
{
	for( KsUInt32 i=0; i<m_vpTextures[ type ].size(); i++ )
	{
		m_vpTextures[ type ][ i ]->destroy();
	}

	m_vpTextures[ type ].clear();
}

/************************************************************************************************/
/*
 * 
 */
/************************************************************************************************/
void KsGameResourceManager::destroy()
{
	for( KsUInt32 i=0; i<ksTEXTURE_RESOURCE_MAX; i++ )
	{
		destroyTextures( s_cast<ksTEXTURE_RESOURCE_TYPE>( i ) );
	}
}
