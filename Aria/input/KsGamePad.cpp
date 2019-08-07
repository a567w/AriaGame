/************************************************************************************************/
/** 
 * @file		KsGamePad.cpp
 * @brief		�Q�[���p�b�h���͏���
 * @author		Tsukasa Kato
 * @date		2006/10/17
 * @since		2006/10/17
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "Aria/KsGamePreCompile.h"
#include "Aria/input/KsGamePad.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsKeyConfig::KsKeyConfig()
{
	m_decision = ksPAD_TRIG1;
	m_cancel   = ksPAD_TRIG2;
	m_menuOpen = ksPAD_TRIG1;
	m_up       = ksPAD_UP;
	m_down     = ksPAD_DOWN;
	m_left     = ksPAD_LEFT;
	m_right    = ksPAD_RIGHT;
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 * @param	pInputSystem	���̓V�X�e��
 * @param	padIndex		�p�b�h�C���f�b�N�X
 */
/************************************************************************************************/
KsGamePad::KsGamePad( KsInputSystem* pInputSystem, KsInt32 padIndex )
	: m_pInputSystem( pInputSystem )
	, m_padIndex( padIndex )
{
}

KsGamePad::~KsGamePad()
{
}

KsBool KsGamePad::isCancelOn() const
{
	return ( m_pInputSystem->getPadNow( m_padIndex ) & m_keyConfig.m_cancel );
}

KsBool KsGamePad::isCancelOff() const 
{
	return ( m_pInputSystem->getPadOff( m_padIndex ) & m_keyConfig.m_cancel );
}

KsBool KsGamePad::isCancelRepeat() const
{
	return ( m_pInputSystem->getPadRpt( m_padIndex ) & m_keyConfig.m_cancel );
}

KsBool KsGamePad::isCancelPress() const 
{
	return ( m_pInputSystem->getPadTrg( m_padIndex ) & m_keyConfig.m_cancel );
}

KsBool KsGamePad::isDecisionOn() const
{
	return ( m_pInputSystem->getPadNow( m_padIndex ) & m_keyConfig.m_decision );
}

KsBool KsGamePad::isDecisionPress() const 
{
	return ( m_pInputSystem->getPadTrg( m_padIndex ) & m_keyConfig.m_decision );
}

KsBool KsGamePad::isDecisionOff() const 
{
	return ( m_pInputSystem->getPadOff( m_padIndex ) & m_keyConfig.m_decision );
}

KsBool KsGamePad::isDecisionRepeat() const
{
	return ( m_pInputSystem->getPadRpt( m_padIndex ) & m_keyConfig.m_decision );
}

KsBool KsGamePad::isUpOn() const
{
	return ( m_pInputSystem->getPadNow( m_padIndex ) & m_keyConfig.m_up );
}

KsBool KsGamePad::isUpPress() const
{
	return ( m_pInputSystem->getPadTrg( m_padIndex ) & m_keyConfig.m_up );
}

KsBool KsGamePad::isUpOff() const
{
	return ( m_pInputSystem->getPadOff( m_padIndex ) & m_keyConfig.m_up );
}

KsBool KsGamePad::isUpRepeat() const
{
	return ( m_pInputSystem->getPadRpt( m_padIndex ) & m_keyConfig.m_up );
}

KsBool KsGamePad::isDownOn() const
{
	return ( m_pInputSystem->getPadNow( m_padIndex ) & m_keyConfig.m_down );
}

KsBool KsGamePad::isDownPress() const
{
	return ( m_pInputSystem->getPadTrg( m_padIndex ) & m_keyConfig.m_down );
}

KsBool KsGamePad::isDownOff() const
{
	return ( m_pInputSystem->getPadTrg( m_padIndex ) & m_keyConfig.m_down );
}

KsBool KsGamePad::isDownRepeat() const
{
	return ( m_pInputSystem->getPadRpt( m_padIndex ) & m_keyConfig.m_down );
}


KsBool KsGamePad::isLeftOn() const
{
	return ( m_pInputSystem->getPadNow( m_padIndex ) & m_keyConfig.m_left );
}

KsBool KsGamePad::isLeftPress() const
{
	return ( m_pInputSystem->getPadTrg( m_padIndex ) & m_keyConfig.m_left );
}

KsBool KsGamePad::isLeftOff() const
{
	return ( m_pInputSystem->getPadOff( m_padIndex ) & m_keyConfig.m_left );
}

KsBool KsGamePad::isLeftRepeat() const
{
	return ( m_pInputSystem->getPadRpt( m_padIndex ) & m_keyConfig.m_left );
}


KsBool KsGamePad::isRightOn() const
{
	return ( m_pInputSystem->getPadNow( m_padIndex ) & m_keyConfig.m_right );
}

KsBool KsGamePad::isRightPress() const
{
	return ( m_pInputSystem->getPadTrg( m_padIndex ) & m_keyConfig.m_right );
}

KsBool KsGamePad::isRightOff() const
{
	return ( m_pInputSystem->getPadOff( m_padIndex ) & m_keyConfig.m_right );
}

KsBool KsGamePad::isRightRepeat() const
{
	return ( m_pInputSystem->getPadRpt( m_padIndex ) & m_keyConfig.m_right );
}


