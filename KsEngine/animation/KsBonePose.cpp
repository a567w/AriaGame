/************************************************************************************************/
/** 
 * @file		KsBonePose.cpp
 * @brief		�{�[���|�[�Y
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsBonePose::KsBonePose()
{
	m_index                  = -1;;
	m_name                   = "none";
	m_pParent                = NULL;
	m_parent                 = -1;
	m_vpChildren.clear();
	m_blendFactor            = 0.0f;
	m_pCurrentAnimation      = NULL;
	m_pCurrentBlendAnimation = NULL;
	m_id                     = 0;
	m_flags                  = 0;
	m_initPivot              = KsVector3d::ZERO;
	m_initTranslate          = KsVector3d::ZERO;
	m_initRotate             = KsQuaternion::IDENTITY;
	m_initScale              = KsVector3d::ZERO;
	m_pivot                  = KsVector3d::ZERO;
	m_translate              = KsVector3d::ZERO;
	m_rotate                 = KsQuaternion::IDENTITY;
	m_scale                  = KsVector3d::ONE;
	m_defaultMatrix          = KsMatrix4x4::IDENTITY;
	m_localMatrix            = KsMatrix4x4::IDENTITY;
	m_worldMatrix            = KsMatrix4x4::IDENTITY;
	m_stackMatrix            = KsMatrix4x4::IDENTITY;
	m_stackScale             = KsVector3d::ONE;
	m_pSkeleton              = NULL;
	m_pUserData              = NULL;
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsBonePose::~KsBonePose()
{
}
