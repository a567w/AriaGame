/************************************************************************************************/
/**
 * @file	KsPhysicsSystemFactory.cpp
 * @brief	�����V���~���[�V�����V�X�e������
 * @author	Tsukasa Kato
 * @date	2005/11/30
 * @version	1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "Aria/KsGamePreCompile.h"
#include "Aria/factory/KsPhysicsSystemFactory.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/*
 * @funcion	KsPhysicsSystemFactory
 * @brief	�����V���~���[�V�����V�X�e������
 * @author  Tsukasa Kato
 * @since   2005/11/30
 * @version ----/--/--
 */
/************************************************************************************************/
KsPhysicsSystem* KsPhysicsSystemFactory( ksPHYSICSSYSTEM_TYPE type, void* pParam )
{
	switch( type )
	{
		case ksPHYSICSSYSTEM_BULLET:
		{
			//--------------------------------------------------
			// Bullet�V�X�e��	
			//--------------------------------------------------
			KsPhysicsSystemBullet*	pPhysicsSystem = ksNew KsPhysicsSystemBullet();

			pPhysicsSystem->createWorld();

			return pPhysicsSystem;
		}
		case ksPHYSICSSYSTEM_PHYSX:
		{
			//--------------------------------------------------
			// PhysX�V�X�e��	
			//--------------------------------------------------
			return NULL;
		}
		case ksPHYSICSSYSTEM_HAVOK:
		{
			//--------------------------------------------------
			// Havok�V�X�e��	
			//--------------------------------------------------
			return NULL;
		}
		default:
		{
			break;
		}
	}

	return NULL;
}

