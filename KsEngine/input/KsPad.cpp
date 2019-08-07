/************************************************************************************************/
/** 
 * @file		KsPad.cpp
 * @brief		�W���C�p�b�h
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * �R���X�g���N�^(�w��ԍ���PAD�̏�����)
 */
/************************************************************************************************/
KsPad::KsPad()
{
	m_now         = 0;
	m_old         = 0;
	m_trg         = 0;
	m_off         = 0;
	m_rpt         = 0;
	m_rptStart    = ksDEFAULT_REPEAT_START;
	m_rptInterval = ksDEFALUT_REPEAT_INTERVAL;
	m_timer       = 0;
	m_buttonMax   = 0;
	m_state       = 0;
	m_id          = 0;
	m_limit_x1    = 0;
	m_limit_x2    = 0;
	m_limit_y1    = 0;
	m_limit_y2    = 0;
}

/************************************************************************************************/
/*
 * �R���X�g���N�^(�w��ԍ���PAD�̏�����)
 * @param		index		�w��ԍ�
 * @param		buttonMax	�{�^���̐�
 */
/************************************************************************************************/
KsPad::KsPad( KsInt32 index, KsInt32 buttonMax )
{
	m_now         = 0;
	m_old         = 0;
	m_trg         = 0;
	m_off         = 0;
	m_rpt         = 0;
	m_rptStart    = ksDEFAULT_REPEAT_START;
	m_rptInterval = ksDEFALUT_REPEAT_INTERVAL;
	m_timer       = 0;
	m_buttonMax   = 0;
	m_state       = 0;
	m_id          = 0;
	m_limit_x1    = 0;
	m_limit_x2    = 0;
	m_limit_y1    = 0;
	m_limit_y2    = 0;

	initialize( index, buttonMax );
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsPad::~KsPad()
{
}

/************************************************************************************************/
/*
 * �R���X�g���N�^(�w��ԍ���PAD�̏�����)
 * @param		index		�w��ԍ�
 * @param		buttonMax	�{�^���̐�
 * @retval		ksTRUE		����������
 * @retval		ksFALSE		���������s
 */
/************************************************************************************************/
KsBool KsPad::initialize( KsInt32 index, KsInt32 buttonMax )
{
	JOYCAPS			joyCaps;
	JOYINFOEX		joyInfo;
	KsInt32			numJoy;

//	m_active    = ksFALSE;
//	m_select    = index;
	m_buttonMax = buttonMax;

	/* �T�|�[�g�����W���C�X�e�B�b�N�����擾���܂� */
	numJoy = joyGetNumDevs();

	/* ���݃`�F�b�N */
	if( ( numJoy < 0 ) || ( index >= numJoy ) ){
		/* ���݂��Ȃ� */
		return ksFALSE;
	}

	m_id = JOYSTICKID1 + index;

	/* �W���C�X�e�B�b�N���Ɖ�Ă��̐��\�𒲂ׂ܂��B */
	if( joyGetDevCaps( m_id, &joyCaps, sizeof(JOYCAPS) ) != JOYERR_NOERROR ){
		return ksFALSE;
	}

	/* �X�e�B�b�N�Z���^�[�̂��߂�臒l */
	m_limit_x1 = ( joyCaps.wXmax   + joyCaps.wXmin*2 )/3;
	m_limit_x2 = ( joyCaps.wXmax*2 + joyCaps.wXmin   )/3;
	m_limit_y1 = ( joyCaps.wYmax   + joyCaps.wYmin*2 )/3;
	m_limit_y2 = ( joyCaps.wYmax*2 + joyCaps.wYmin   )/3;

	/* �`�F�b�N */
	if( joyGetPosEx( m_id, &joyInfo ) != JOYERR_NOERROR ){
		return ksFALSE;
	}

//	m_active = ksTRUE;

	m_state = 1;

	return ksTRUE;
}

/************************************************************************************************/
/*
 * ���͏���ǂݍ���
 * @return					���̓f�[�^
 */
/************************************************************************************************/
KsUInt32 KsPad::read()
{
	if( !m_state ){
		return 0;
	}

	KsUInt32		x;
	KsUInt32		y;
	JOYINFOEX		joyInfo;
	KsUInt32		data = 0;
	
	joyInfo.dwSize  = sizeof(JOYINFOEX);
	joyInfo.dwFlags = JOY_RETURNALL;
	
	if( joyGetPosEx( m_id, &joyInfo ) != JOYERR_NOERROR ){
		/* ���͂��擾�ł��Ȃ��A�W���C�X�e�B�b�N�������ꂽ��������Ȃ� */
		return 0;
	}

	x = static_cast<KsUInt32>(joyInfo.dwXpos);
	y = static_cast<KsUInt32>(joyInfo.dwYpos);

	/* �����L�[�̃r�b�g��� */
	if( y <= m_limit_y1 ){
		data |= ksPAD_UP;
	}
	else if( y >= m_limit_y2 ){
		data |= ksPAD_DOWN;
	}

	if( x <= m_limit_x1 ){
		data |= ksPAD_LEFT;
	}
	else if( x >=  m_limit_x2 ){
		data |= ksPAD_RIGHT;
	}
	
	/* �w��̃{�^�����������r�b�g��쐬 */
	for( KsUInt32 i=0;i<m_buttonMax; i++ )
	{
		//������Ă���r�b�g���Z�b�g
		if( joyInfo.dwButtons & ( 1<<i ) )
		{
			data |= ( ksPAD_TRIG1 << i );
		}
	}

	return data;
}

/************************************************************************************************/
/*
 * �w��L�[�Ƃ̃}�[�W����
 * @param	pKd				�L�[�A�T�C���f�[�^
 * @param	pBuf			�L�[�f�[�^
 */
/************************************************************************************************/
KsUInt32 KsPad::merge( KSKEYASSIGN*	pKd, KsByte* pBuf )
{
	KsUInt32	data = 0;

	do
	{
		if( pBuf[ pKd->key ] & 0x80 ){
			data |= pKd->pad;
		}
		pKd++;
	}while( pKd->key != 0 );

	return data;
}

/************************************************************************************************/
/*
 * �X�V����
 * @param	data			���̓f�[�^
 */
/************************************************************************************************/
void KsPad::update( KsUInt32 data )
{
	m_old = m_now;
	m_now = data;
	m_trg = ( m_now ^ m_old ) & m_now;
	m_off = ( m_now ^ m_old ) & m_old;

	// �S�Ẵf�W�^���L�[���s�[�g����
	if( m_old == m_now ){
		++m_timer;
		if( (m_timer > m_rptStart) && ( ( (m_timer - m_rptStart) % m_rptInterval ) == 0 ) ){
			m_rpt = m_now;
		}
		else{
			m_rpt = 0;
		}
	}
	else{
		m_rpt   = m_now;
		m_timer = 0;
	}
}



