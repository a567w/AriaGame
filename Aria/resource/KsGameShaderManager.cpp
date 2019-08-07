/************************************************************************************************/
/** 
 * @file		KsGameShaderManager.cpp
 * @brief		ゲームリソース
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "Aria/KsGamePreCompile.h"
#include "Aria/resource/KsGameShaderManager.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
template<> KsGameShaderManager* KsSingleton< KsGameShaderManager >::m_pInstance = 0;

/************************************************************************************************/
/*
 * シングルトンの参照を取得
 * @return							シングルトンの参照
 */
/************************************************************************************************/
KsGameShaderManager& KsGameShaderManager::getInstance()
{  
	return (*m_pInstance);  
}

/************************************************************************************************/
/*
 * シングルトンのポインタを取得
 * @return							シングルトンのポインタ
 */
/************************************************************************************************/
KsGameShaderManager* KsGameShaderManager::getInstancePtr()
{
	return m_pInstance;
}

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsGameShaderManager::KsGameShaderManager()
	: m_pFilePack( 0 )
{
	create( ".\\Shader\\shader.pak" );
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsGameShaderManager::~KsGameShaderManager()
{
	destroy();
}

/************************************************************************************************/
/*
 * ファイルパックからシェダーを生成する
 * @param	rFileName	ファイルパック
 * @retval	ksTRUE		成功
 * @retval	ksFALSE		失敗
 */
/************************************************************************************************/
KsBool KsGameShaderManager::create( const KsString& rFileName )
{
	m_pFilePack = ksNew KsFilePack();
	m_pFilePack->createFromFile( rFileName );

	KsShaderManager*	pShaderManager = KsShaderManager::getInstancePtr();

	for( KsUInt32 i=0; i<m_pFilePack->getNumFile(); i++ )
	{
		KsFilePackInfo*		pInfo      = m_pFilePack->getInfo( i );
		KsByte*				pData      = m_pFilePack->getData( i );
		ksSHADER_TYPE		shaderType = (ksSHADER_TYPE)pInfo->DataType;
		KsShaderProgram*	pProgram   = pShaderManager->createFromMemory( pData, pInfo->DataSize, shaderType );

		if( pProgram )
		{
			m_vpShaderTbl.add( pInfo->DataName, pProgram );
		}
		else
		{
			KsPrintf( "ERROR : Create shader[%d]:%s\n", i, pInfo->DataName );
		}
	}

	return ksTRUE;
}

/************************************************************************************************/
/*
 * すべてのリソースを解放する
 */
/************************************************************************************************/
void KsGameShaderManager::destroy()
{
	ksDELETE( m_pFilePack );
}

/************************************************************************************************/
/*
 * シェダープログラムを検索する
 * @param	rShaderName		シェダープログラム名
 * @return					シェダープログラム見つからない時はNULLを返す
 */
/************************************************************************************************/
KsShaderProgram* KsGameShaderManager::find( const KsString& rShaderName )
{
	KsHashTable<KsShaderProgram*>::KsHashNodeType*	pNode =	m_vpShaderTbl.find( rShaderName );

	if( pNode )
	{
		return pNode->m_pData;
	}

	return NULL;
}

