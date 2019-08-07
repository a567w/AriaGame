/************************************************************************************************/
/** 
 * @file		KsBlendState.cpp
 * @brief		DirectX�p�[�x�X�e���V���X�e�[�g
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
#include "KsBlendState.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * �f�t�H���g�u�����h�X�e�[�g
 */
/************************************************************************************************/
const KS_BLEND_DESC KsBlendState::DEFAULT = 
{
	ksFALSE,
	ksFALSE,
	{
		{ ksFALSE, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_COLOR_WRITE_ENABLE_ALL },
		{ ksFALSE, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_COLOR_WRITE_ENABLE_ALL },
		{ ksFALSE, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_COLOR_WRITE_ENABLE_ALL },
		{ ksFALSE, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_COLOR_WRITE_ENABLE_ALL },
		{ ksFALSE, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_COLOR_WRITE_ENABLE_ALL },
		{ ksFALSE, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_COLOR_WRITE_ENABLE_ALL },
		{ ksFALSE, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_COLOR_WRITE_ENABLE_ALL },
		{ ksFALSE, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_COLOR_WRITE_ENABLE_ALL }
	}
};

/************************************************************************************************/
/*
 * �f�t�H���g�u�����h�X�e�[�g
 */
/************************************************************************************************/
const KS_BLEND_DESC KsBlendState::SPRITE = 
{
	ksTRUE,
	ksFALSE,
	{
		{ ksTRUE, KS_BLEND_SRC_ALPHA, KS_BLEND_INV_SRC_ALPHA, KS_BLEND_OP_ADD, KS_BLEND_SRC_ALPHA, KS_BLEND_INV_SRC_ALPHA, KS_BLEND_OP_ADD, KS_COLOR_WRITE_ENABLE_ALL },
		{ ksTRUE, KS_BLEND_SRC_ALPHA, KS_BLEND_INV_SRC_ALPHA, KS_BLEND_OP_ADD, KS_BLEND_SRC_ALPHA, KS_BLEND_INV_SRC_ALPHA, KS_BLEND_OP_ADD, KS_COLOR_WRITE_ENABLE_ALL },
		{ ksTRUE, KS_BLEND_SRC_ALPHA, KS_BLEND_INV_SRC_ALPHA, KS_BLEND_OP_ADD, KS_BLEND_SRC_ALPHA, KS_BLEND_INV_SRC_ALPHA, KS_BLEND_OP_ADD, KS_COLOR_WRITE_ENABLE_ALL },
		{ ksTRUE, KS_BLEND_SRC_ALPHA, KS_BLEND_INV_SRC_ALPHA, KS_BLEND_OP_ADD, KS_BLEND_SRC_ALPHA, KS_BLEND_INV_SRC_ALPHA, KS_BLEND_OP_ADD, KS_COLOR_WRITE_ENABLE_ALL },
		{ ksTRUE, KS_BLEND_SRC_ALPHA, KS_BLEND_INV_SRC_ALPHA, KS_BLEND_OP_ADD, KS_BLEND_SRC_ALPHA, KS_BLEND_INV_SRC_ALPHA, KS_BLEND_OP_ADD, KS_COLOR_WRITE_ENABLE_ALL },
		{ ksTRUE, KS_BLEND_SRC_ALPHA, KS_BLEND_INV_SRC_ALPHA, KS_BLEND_OP_ADD, KS_BLEND_SRC_ALPHA, KS_BLEND_INV_SRC_ALPHA, KS_BLEND_OP_ADD, KS_COLOR_WRITE_ENABLE_ALL },
		{ ksTRUE, KS_BLEND_SRC_ALPHA, KS_BLEND_INV_SRC_ALPHA, KS_BLEND_OP_ADD, KS_BLEND_SRC_ALPHA, KS_BLEND_INV_SRC_ALPHA, KS_BLEND_OP_ADD, KS_COLOR_WRITE_ENABLE_ALL },
		{ ksTRUE, KS_BLEND_SRC_ALPHA, KS_BLEND_INV_SRC_ALPHA, KS_BLEND_OP_ADD, KS_BLEND_SRC_ALPHA, KS_BLEND_INV_SRC_ALPHA, KS_BLEND_OP_ADD, KS_COLOR_WRITE_ENABLE_ALL }
	}
};

/************************************************************************************************/
/*
 * Accum�u�����h�X�e�[�g
 */
/************************************************************************************************/
const KS_BLEND_DESC KsBlendState::ACCUMULATE = 
{
	ksFALSE,
	ksFALSE,
	{
		{ ksTRUE,  KS_BLEND_ONE, KS_BLEND_ONE,  KS_BLEND_OP_ADD, KS_BLEND_ONE, KS_BLEND_ONE,  KS_BLEND_OP_ADD, KS_COLOR_WRITE_ENABLE_ALL },
		{ ksFALSE, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_COLOR_WRITE_ENABLE_ALL },
		{ ksFALSE, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_COLOR_WRITE_ENABLE_ALL },
		{ ksFALSE, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_COLOR_WRITE_ENABLE_ALL },
		{ ksFALSE, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_COLOR_WRITE_ENABLE_ALL },
		{ ksFALSE, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_COLOR_WRITE_ENABLE_ALL },
		{ ksFALSE, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_COLOR_WRITE_ENABLE_ALL },
		{ ksFALSE, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_BLEND_ONE, KS_BLEND_ZERO, KS_BLEND_OP_ADD, KS_COLOR_WRITE_ENABLE_ALL }
	}
};


/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsBlendState::KsBlendState()
{
	KsZeroMemory( &m_blendStateDesc, sizeof(KS_BLEND_DESC) );
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsBlendState::KsBlendState( const KS_BLEND_DESC* pBlendStateDesc )
{
	KsMemCopy( &m_blendStateDesc, pBlendStateDesc, sizeof(KS_BLEND_DESC) );
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsBlendState::KsBlendState( const KS_BLEND_DESC& refBlendStateDesc )
	: m_blendStateDesc( refBlendStateDesc )
{
}


/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsBlendState::~KsBlendState()
{
}

