/************************************************************************************************/
/** 
 * @file		KsShaderManager.cpp
 * @brief		�V�F�[�_�[�}�l�[�W���[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"
#include "KsShaderManager.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
template<> KsShaderManager* KsSingleton< KsShaderManager >::m_pInstance = 0;

/************************************************************************************************/
/*
 * �V���O���g���̎Q�Ƃ��擾
 * @return							�V���O���g���̎Q��
 */
/************************************************************************************************/
KsShaderManager& KsShaderManager::getInstance()
{  
	return (*m_pInstance);  
}
/************************************************************************************************/
/*
 * �V���O���g���̃|�C���^���擾
 * @return							�V���O���g���̃|�C���^
 */
/************************************************************************************************/
KsShaderManager* KsShaderManager::getInstancePtr()
{
	return m_pInstance;
}


/************************************************************************************************/
/*
 * �w�肵�����O�̃e�N�X�`������������
 * �擾������ɎQ�ƃJ�E���g��������K�v������
 * @param	pFileName				�t�@�C����
 * @return							���������e�N�X�`���̃|�C���^
 */
/************************************************************************************************/
KsShaderProgram* KsShaderManager::find( const KsChar* pFileName )
{
	KsHashNode<KsShaderProgram*>*		pNode;

	pNode = m_pShaders.find( pFileName );

	if( pNode )
	{
		return pNode->m_pData;
	}

	return NULL;
}

/************************************************************************************************/
/*
 * �������Č���������Q�ƃJ�E���g���A�b�v����
 * @param	pFileName				�t�@�C����
 * @return							���������e�N�X�`���̃|�C���^
 */
/************************************************************************************************/
KsShaderProgram* KsShaderManager::findRefInc( const KsChar* pFileName )
{
	KsShaderProgram*	pShader = find( pFileName );

	if( pShader )
	{
		pShader->inc();
	}

	return pShader;
}

/************************************************************************************************/
/*
 * �e�N�X�`����ǉ�����
 * DEBUG���[�h�̂Ƃ��́A2�d�o�^�`�F�b�N������
 * @param	pTexture				�ǉ�����e�N�X�`���̃|�C���^
 * @retval	ksTRUE					����
 * @retval	ksFALSE					���s
 */
/************************************************************************************************/
KsBool KsShaderManager::add( KsShaderProgram* pShader )
{
	KsHashNode<KsShaderProgram*>*		pNode;

	pNode = m_pShaders.find( pShader->getName().c_str() );

	if( !pNode )
	{
		m_pShaders.add( pShader->getName().c_str(), pShader );
	}

	return ksTRUE;
}

/************************************************************************************************/
/*
 * �e�N�X�`�����}�l�[�W�������菜��
 * @param	pTexture				��菜���e�N�X�`���̃|�C���^
 * @retval	ksTRUE					����
 * @retval	ksFALSE					���s
 */
/************************************************************************************************/
KsBool KsShaderManager::remove( KsShaderProgram* pShader )
{
	m_pShaders.destroy( pShader->getName().c_str() );

	return ksFALSE;
}

/************************************************************************************************/
/*
 * �e�N�X�`�����폜����
 * @param	pTexture				�폜����e�N�X�`���̃|�C���^
 * @retval	ksTRUE					����
 * @retval	ksFALSE					���s
 */
/************************************************************************************************/
KsBool KsShaderManager::destroy( KsShaderProgram* pShader )
{
#ifdef _DEBUG
	if( pShader->getRefCount() < 1 )
	{
		//StPrintf("texture ref count(%d)\n", pTexture->getRefCount() );
		return ksFALSE;
	}
#endif

	/* �Q�ƃJ�E���g��1��������e�N�X�`���}�l�[�W�������菜�� */
	if( pShader->getRefCount() == 1 )
	{
		if( !remove( pShader ) )
		{
			return ksFALSE;
		}
	}

	/* �Q�ƃJ�E���g�������� */
	pShader->dec();

	return ksTRUE;
}

/************************************************************************************************/
/*
 * ���ׂẴe�N�X�`����j������(�Q�ƃJ�E���g�֌W�Ȃ��j�������)
 * @retval	ksTRUE					����
 * @retval	ksFALSE					���s
 */
/************************************************************************************************/
KsBool KsShaderManager::destroyAll()
{
#if 0
	KsTexture*		pTemp = m_pTop;
	KsTexture*		pTexture;

	while( pTemp )
	{
		pTexture = pTemp;
		pTemp    = pTemp->m_pNext;

		delete pTexture;
	}

	m_pTop = NULL;
#endif

	return ksTRUE;
}

