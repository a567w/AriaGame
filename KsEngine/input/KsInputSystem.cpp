/************************************************************************************************/
/** 
 * @file		KsInputSystem.cpp
 * @brief		���͏���
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/


/* �p�b�h�P�p�L�[�A�T�C�� */
static KSKEYASSIGN	pad1[] = 
{
	{ ksKEY_UP,    ksPAD_UP    },
	{ ksKEY_DOWN,  ksPAD_DOWN  },
	{ ksKEY_LEFT,  ksPAD_LEFT  },
	{ ksKEY_RIGHT, ksPAD_RIGHT },
	{ ksKEY_Z,     ksPAD_TRIG1 },
	{ ksKEY_X,     ksPAD_TRIG2 },
	{ ksKEY_C,     ksPAD_TRIG3 },
	{ ksKEY_SPACE, ksPAD_TRIG9 },
	{ 0,           0           }
};

/* �Փ˂���̂�pad1�Ƃ��Ԃ�Ȃ��悤�ɂ��� */
static KSKEYASSIGN	pad2[] = 
{
	{ ksKEY_UP,    ksPAD_UP    },
	{ ksKEY_DOWN,  ksPAD_DOWN  },
	{ ksKEY_LEFT,  ksPAD_LEFT  },
	{ ksKEY_RIGHT, ksPAD_RIGHT },
	{ ksKEY_Z,     ksPAD_TRIG1 },
	{ ksKEY_X,     ksPAD_TRIG2 },
	{ ksKEY_C,     ksPAD_TRIG3 },
	{ ksKEY_SPACE, ksPAD_TRIG9 },
	{ 0,           0           }
};

/* �L�[�{�[�h�ƃp�b�h�̃A�T�C���Ƃ肠����2�܂� */
static KSKEYASSIGN* s_pKeyInfo[] = 
{
	pad1,	/*< PAD1���Q�Ƃ��� */
	pad2,	/*< PAD2���Q�Ƃ��� */
	NULL,
};

/************************************************************************************************/
/*
 * @class		KsInputSystem
 * @brief		���̓}�l�[�W��(�V���O���g���N���X)
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		�Ȃ�
 */
/************************************************************************************************/
template<> KsInputSystem*	KsSingleton<KsInputSystem>::m_pInstance = 0;

/************************************************************************************************/
/*
 * �C���X�^���X�擾
 * @return				�C���X�^���X
 */
/************************************************************************************************/
KsInputSystem&	KsInputSystem::getInstance()
{
	/*KsAssert( m_pInstance );*/
	return (*m_pInstance);
}

/************************************************************************************************/
/*
 * �C���X�^���X�擾
 * @return				�C���X�^���X
 */
/************************************************************************************************/
KsInputSystem*	KsInputSystem::getInstancePtr()
{
	return m_pInstance;
}

/************************************************************************************************/
/*
 * �R���X�g���N�^(����������)
 * @param	num			�W���C�X�e�B�b�N�h���C�o���T�|�[�g����W���C�X�e�B�b�N��
 */
/************************************************************************************************/
KsInputSystem::KsInputSystem() : m_bInit( ksFALSE )
{
}

/************************************************************************************************/
/*
 * �R���X�g���N�^(����������)
 * @param	num			�W���C�X�e�B�b�N�h���C�o���T�|�[�g����W���C�X�e�B�b�N��
 */
/************************************************************************************************/
KsInputSystem::KsInputSystem( KsUInt32 num ) : m_bInit( ksFALSE )
{
	initialize( num );
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsInputSystem::~KsInputSystem()
{
	release();
}

/************************************************************************************************/
/*
 * ����������
 * @param	num				�W���C�X�e�B�b�N�h���C�o���T�|�[�g����W���C�X�e�B�b�N��
 */
/************************************************************************************************/
void KsInputSystem::initialize( KsUInt32 num )
{
	if( !m_bInit )
	{
		JOYCAPS			joyCaps;

		m_padMax = ::joyGetNumDevs();
		m_padNum = 0;

		for( KsUInt32 i=0; i<m_padMax; i++ )
		{
			/* �W���C�X�e�B�b�N���Ɖ�Ă��̐��\�𒲂ׂ܂��B */
			if( joyGetDevCaps( JOYSTICKID1+i, &joyCaps, sizeof(JOYCAPS) ) == JOYERR_NOERROR )
			{
				++m_padNum;
				//m_vpPads.push_back( new KsPad( JOYSTICKID1+i ) );
			}
		}

		if( m_padNum == 0 )
		{
			m_padNum = 1;
		}

		for( KsUInt32 i=0; i< (num - m_padNum); i++ )
		{
			m_vpPads.push_back( new KsPad( JOYSTICKID1+i ) );
		}

		for( KsUInt32 i=0; i<1; i++ )
		{
			m_vpMouses.push_back( new KsMouse() );
		}

		m_bInit = ksTRUE;
	}
}

/************************************************************************************************/
/*
 * �X�V����
 */
/************************************************************************************************/
void KsInputSystem::update()
{
	KsUInt32	index = 0;
	KsUInt32	data  = 0;

	::GetKeyboardState( m_keyData );

	for( KsUInt32 i=0; i<m_padNum; i++ )
	{
		data  = m_vpPads[ i ]->read();
		data |= m_vpPads[ i ]->merge( s_pKeyInfo[ index ], m_keyData );
		m_vpPads[ i ]->update( data );
		index++;
	}

	for( KsUInt32 i=0; i<m_vpMouses.size(); i++ )
	{
		m_vpMouses[ i ]->update();
	}
}

/************************************************************************************************/
/*
 * �J������
 */
/************************************************************************************************/
void KsInputSystem::release()
{
	ksDELETEARRAYTEMPLATE( m_vpPads );
	ksDELETEARRAYTEMPLATE( m_vpMouses );
}



