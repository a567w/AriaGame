/************************************************************************************************/
/** 
 * @file		KsTextureManager.cpp
 * @brief		�e�N�X�`���}�l�[�W��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"
#include "KsTextureManager.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
template<> KsTextureManager* KsSingleton< KsTextureManager >::m_pInstance = 0;

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsTextureManager::KsTextureManager() : m_pTop( 0 )
{
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsTextureManager::~KsTextureManager()
{
}

/************************************************************************************************/
/*
 * �w�肵�����O�̃e�N�X�`������������
 * �擾������ɎQ�ƃJ�E���g��������K�v������
 * @param	pFileName				�t�@�C����
 * @return							���������e�N�X�`���̃|�C���^
 */
/************************************************************************************************/
KsTexture* KsTextureManager::find( const KsChar* pFileName )
{
	KsTexture*		pTemp = m_pTop;
	KsUInt32		id    = KsCrc32( (KsUInt8*)pFileName );

	while( pTemp )
	{
		if( id == pTemp->m_id )
		{
			/* �����񂪓����������`�F�b�N���� */
			if( ks_strcmp( pFileName, pTemp->m_name.c_str() ) == 0 )
			{
				return pTemp;
			}
		}

		pTemp = pTemp->m_pNext;
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
KsTexture* KsTextureManager::findRefInc( const KsChar* pFileName )
{
	KsTexture*		pTexture = find( pFileName );

	if( pTexture )
	{
		pTexture->inc();
	}

	return pTexture;
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
KsBool KsTextureManager::add( KsTexture* pTexture )
{
	pTexture->m_pNext = m_pTop;
	m_pTop            = pTexture;

	pTexture->m_flags |= ksTEXTURE_FLAG_USE_MANAGER;

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
KsBool KsTextureManager::remove( KsTexture* pTexture )
{
	KsTexture*		pPrev;
	KsTexture*		pTemp;
	KsUInt32		id;

	if( m_pTop == NULL )
	{
		return ksFALSE;
	}

	if( pTexture == m_pTop )
	{
		m_pTop = m_pTop->m_pNext;
		return ksTRUE;
	}

	pPrev = m_pTop;
	pTemp = m_pTop->m_pNext;
	id    = KsCrc32( (KsUInt8*)(pTexture->m_name.c_str()) );

	while( pTemp )
	{
		if( id == pTemp->m_id )
		{
			/* �����񂪓����������`�F�b�N���� */
			if( ks_strcmp( pTexture->m_name.c_str(), pTemp->m_name.c_str() ) == 0 )
			{
			//if( pTexture->m_name == pTemp->m_name ){
				pPrev->m_pNext = pTemp->m_pNext;
				return ksTRUE;
			}
		}

		pPrev = pTemp;
		pTemp = pTemp->m_pNext;

	}

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
KsBool KsTextureManager::destroy( KsTexture* pTexture )
{
#ifdef _DEBUG
	if( pTexture->getRefCount() < 1 )
	{
		//StPrintf("texture ref count(%d)\n", pTexture->getRefCount() );
		return ksFALSE;
	}
#endif

	/* �Q�ƃJ�E���g��1��������e�N�X�`���}�l�[�W�������菜�� */
	if( pTexture->getRefCount() == 1 )
	{
		if( !remove( pTexture ) )
		{
			return ksFALSE;
		}
	}

	/* �Q�ƃJ�E���g�������� */
	pTexture->dec();

	return ksTRUE;
}

/************************************************************************************************/
/*
 * ���ׂẴe�N�X�`����j������(�Q�ƃJ�E���g�֌W�Ȃ��j�������)
 * @retval	ksTRUE					����
 * @retval	ksFALSE					���s
 */
/************************************************************************************************/
KsBool KsTextureManager::destroyAll()
{
	KsTexture*		pTemp = m_pTop;
	KsTexture*		pTexture;

	while( pTemp )
	{
		pTexture = pTemp;
		pTemp    = pTemp->m_pNext;

		delete pTexture;
	}

	m_pTop = NULL;

	return ksTRUE;
}


/************************************************************************************************/
/*
 * �V���O���g���̎Q�Ƃ��擾
 * @return							�V���O���g���̎Q��
 */
/************************************************************************************************/
KsTextureManager& KsTextureManager::getInstance()
{  
	return (*m_pInstance);  
}

/************************************************************************************************/
/*
 * �V���O���g���̃|�C���^���擾
 * @return							�V���O���g���̃|�C���^
 */
/************************************************************************************************/
KsTextureManager* KsTextureManager::getInstancePtr()
{
	return m_pInstance;
}

