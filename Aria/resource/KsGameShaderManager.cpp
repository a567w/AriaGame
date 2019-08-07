/************************************************************************************************/
/** 
 * @file		KsGameShaderManager.cpp
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
#include "Aria/resource/KsGameShaderManager.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/
template<> KsGameShaderManager* KsSingleton< KsGameShaderManager >::m_pInstance = 0;

/************************************************************************************************/
/*
 * �V���O���g���̎Q�Ƃ��擾
 * @return							�V���O���g���̎Q��
 */
/************************************************************************************************/
KsGameShaderManager& KsGameShaderManager::getInstance()
{  
	return (*m_pInstance);  
}

/************************************************************************************************/
/*
 * �V���O���g���̃|�C���^���擾
 * @return							�V���O���g���̃|�C���^
 */
/************************************************************************************************/
KsGameShaderManager* KsGameShaderManager::getInstancePtr()
{
	return m_pInstance;
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsGameShaderManager::KsGameShaderManager()
	: m_pFilePack( 0 )
{
	create( ".\\Shader\\shader.pak" );
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsGameShaderManager::~KsGameShaderManager()
{
	destroy();
}

/************************************************************************************************/
/*
 * �t�@�C���p�b�N����V�F�_�[�𐶐�����
 * @param	rFileName	�t�@�C���p�b�N
 * @retval	ksTRUE		����
 * @retval	ksFALSE		���s
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
 * ���ׂẴ��\�[�X���������
 */
/************************************************************************************************/
void KsGameShaderManager::destroy()
{
	ksDELETE( m_pFilePack );
}

/************************************************************************************************/
/*
 * �V�F�_�[�v���O��������������
 * @param	rShaderName		�V�F�_�[�v���O������
 * @return					�V�F�_�[�v���O����������Ȃ�����NULL��Ԃ�
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

