/************************************************************************************************/
/** 
 * @file		KsPhysicsSystem.h
 * @brief		�����V�~�����[�V�����V�X�e��
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
#include "KsPhysicsSystem.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
template<> KsPhysicsSystem* KsSingleton< KsPhysicsSystem >::m_pInstance = 0;

/************************************************************************************************/
/*
 * �V���O���g���̎Q�Ƃ��擾
 * @return	�V���O���g���̎Q��
 */
/************************************************************************************************/
KsPhysicsSystem& KsPhysicsSystem::getInstance()
{  
	return (*m_pInstance);  
}

/************************************************************************************************/
/*
 * �V���O���g���̃|�C���^���擾
 * @return	�V���O���g���̃|�C���^
 */
/************************************************************************************************/
KsPhysicsSystem* KsPhysicsSystem::getInstancePtr()
{
	return m_pInstance;
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsPhysicsSystem::KsPhysicsSystem()
{

}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsPhysicsSystem::~KsPhysicsSystem()
{

}

