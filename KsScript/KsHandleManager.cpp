/************************************************************************************************/
/** 
 * @file		KsHandleManager.h
 * @brief		ハンドルマネージャ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsScript/KsScriptPreCompile.h"
#include "KsHandleManager.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/



/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsHandleManager::KsHandleManager()
{
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsHandleManager::~KsHandleManager()
{
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsHandle KsHandleManager::getStringHandle( const KsChar* pString )
{
	KsHashNode<KsHandleObject*>*		pNode;

	pNode = m_stringHandleList.find( pString );

	if( !pNode )
	{
		KsHandleObject*		pObject = new KsStringObject( pString );
		m_stringHandleList.add( pString, pObject );

		return pObject->getHandle();
	}

	return pNode->m_pData->getHandle();
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsHandle KsHandleManager::getGlobalHandle( const KsChar* pString )
{
	KsHashNode<KsHandleObject*>*		pNode;

	pNode = m_globalHandleList.find( pString );

	if( !pNode )
	{
		KsHandleObject*		pObject = new KsGlobalObject( pString );
		m_globalHandleList.add( pString, pObject );

		return pObject->getHandle();
	}

	return pNode->m_pData->getHandle();
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsHandle KsHandleManager::getStructHandle( const KsChar* pString )
{
	KsHashNode<KsHandleObject*>*		pNode;

	pNode = m_structHandleList.find( pString );

	if( !pNode )
	{
		KsHandleObject*		pObject = new KsStructObject( pString );
		m_structHandleList.add( pString, pObject );

		return pObject->getHandle();
	}

	return pNode->m_pData->getHandle();
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsGlobalObject* KsHandleManager::getGlobalObject( const KsChar* pString )
{
	KsHashNode<KsHandleObject*>*		pNode;

	pNode = m_globalHandleList.find( pString );

	if( !pNode ){ return NULL; }

	return (KsGlobalObject*)pNode->m_pData;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsStructObject* KsHandleManager::getStructObject( const KsChar* pString )
{
	KsHashNode<KsHandleObject*>*		pNode;

	pNode = m_structHandleList.find( pString );

	if( !pNode ){ return NULL; }

	return (KsStructObject*)pNode->m_pData;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsHandle KsHandleManager::createStringHandle( const KsChar* pString )
{
	KsHashNode<KsHandleObject*>*		pNode;
	KsStringObject*						pObject;

	pNode = m_stringHandleList.find( pString );

	if( !pNode )
	{
		pObject = new KsStringObject( pString );
		m_stringHandleList.add( pString, pObject );
		pObject->m_refCount = 1;
		return pObject->getHandle();
	}

	pObject = (KsStringObject*)pNode->m_pData;
	++pObject->m_refCount;

	return pObject->getHandle();
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsHandle KsHandleManager::createGlobalHandle( const KsChar* pString )
{
	KsHashNode<KsHandleObject*>*		pNode;
	KsGlobalObject*						pObject;

	pNode = m_globalHandleList.find( pString );

	if( !pNode )
	{
		pObject = new KsGlobalObject( pString );
		m_globalHandleList.add( pString, pObject );
		pObject->m_refCount = 1;
		return pObject->getHandle();
	}

	pObject = (KsGlobalObject*)pNode->m_pData;
	++pObject->m_refCount;

	return pObject->getHandle();
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsStructObject* KsHandleManager::createStructObject( const KsChar* pString )
{
	KsHashNode<KsHandleObject*>*		pNode;
	KsStructObject*						pObject;

	pNode = m_structHandleList.find( pString );

	if( !pNode )
	{
		pObject = new KsStructObject( pString );
		m_structHandleList.add( pString, pObject );
		pObject->m_refCount = 1;
		return pObject;
	}

	pObject = (KsStructObject*)pNode->m_pData;
	++pObject->m_refCount;

	return pObject;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsHandleManager::destoryStringObject( KsHandle handle )
{
	KsStringObject*		pObject = (KsStringObject*)KsGetHandleObject( handle );

	--pObject->m_refCount;
	if( pObject->m_refCount == 0 )
	{
		m_stringHandleList.destroy( pObject->getString().c_str() );
		delete pObject;
	}
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsHandleManager::destoryGlobalObject( KsHandle handle )
{
	KsGlobalObject*		pObject = (KsGlobalObject*)KsGetHandleObject( handle );

	--pObject->m_refCount;
	if( pObject->m_refCount == 0 )
	{
		/* 構造体だったら開放する必要がある */
		if( pObject->getVariable()->getType() == ksVALUE_STRCT )
		{
			KsVariable*		pVariables = (KsVariable*)pObject->getVariable()->m_value.h;
			delete [] pVariables;
		}

		m_globalHandleList.destroy( pObject->getString().c_str() );
		delete pObject;
	}
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsHandleManager::destoryStructObject( KsHandle handle )
{
	KsStructObject*		pObject = (KsStructObject*)KsGetHandleObject( handle );
	m_structHandleList.destroy( pObject->getString().c_str() );
	delete pObject;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsDestoryStringObject( KsHandleManager* pHM, KsHandle handle )
{
	pHM->destoryStringObject( handle );
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsDestoryGlobalObject( KsHandleManager* pHM, KsHandle handle )
{
	pHM->destoryGlobalObject( handle );
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
void KsDestoryStructObject( KsHandleManager* pHM, KsHandle handle )
{
	pHM->destoryStructObject( handle );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsHandle KsGetStringHandle( KsHandleManager* pHM, const KsChar* pString )
{
	return pHM->getStringHandle( pString );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsHandle KsGetGlobalHandle( KsHandleManager* pHM, const KsChar* pString )
{
	return pHM->getGlobalHandle( pString );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsHandle KsGetStructHandle( KsHandleManager* pHM, const KsChar* pString )
{
	return pHM->getStructHandle( pString );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsHandle KsGetFuncHandle( const KsChar* pString )
{
	static KsInt32 id = 0;

	return (KsHandle)(id++);
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsHandleObject* KsGetHandleObject( KsHandle handle )
{
	KsHandleObject*		pObject = (KsHandleObject*)handle;
	
	return pObject;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsGlobalObject* KsGetGlobalObject( KsHandleManager* pHM, const KsChar* pString )
{
	KsGlobalObject*		pObject = pHM->getGlobalObject( pString );

	if( !pObject )
	{
		pObject = pHM->getGlobalObject( pString );
	}

	return pObject;
}


/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsStructObject* KsGetStructObject( KsHandleManager* pHM, const KsChar* pString )
{
	KsStructObject*		pObject = pHM->getStructObject( pString );

	if( !pObject )
	{
		pObject = pHM->getStructObject( pString );
	}

	return pObject;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsHandle KsCreateStringHandle( KsHandleManager* pHM, const KsChar* pString )
{
	return pHM->createStringHandle( pString );
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsHandle KsCreateGlobalHandle( KsHandleManager* pHM, const KsChar* pString )
{
	return pHM->createGlobalHandle( pString );
}



