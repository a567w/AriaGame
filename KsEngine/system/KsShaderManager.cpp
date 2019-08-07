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
#include "KsShaderManager.h"
#include "KsShader.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
template<> KsShaderManager* KsSingleton< KsShaderManager >::m_pInstance = 0;

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsShaderManager& KsShaderManager::getInstance()
{  
	return (*m_pInstance);  
}
/************************************************************************************************/
/*
 *
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
KsShader* KsShaderManager::find( const KsChar* pFileName )
{
	KsHashNode<KsShader*>*		pNode;

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
KsShader* KsShaderManager::findRefInc( const KsChar* pFileName )
{
	KsShader*	pShader = find( pFileName );

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
KsBool KsShaderManager::add( KsShader* pShader )
{
	KsHashNode<KsShader*>*		pNode;

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
KsBool KsShaderManager::remove( KsShader* pShader )
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
KsBool KsShaderManager::destroy( KsShader* pShader )
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

