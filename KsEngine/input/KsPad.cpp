/************************************************************************************************/
/** 
 * @file		KsPad.cpp
 * @brief		ジョイパッド
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/*
 * コンストラクタ(指定番号のPADの初期化)
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
 * コンストラクタ(指定番号のPADの初期化)
 * @param		index		指定番号
 * @param		buttonMax	ボタンの数
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
 * デストラクタ
 */
/************************************************************************************************/
KsPad::~KsPad()
{
}

/************************************************************************************************/
/*
 * コンストラクタ(指定番号のPADの初期化)
 * @param		index		指定番号
 * @param		buttonMax	ボタンの数
 * @retval		ksTRUE		初期化成功
 * @retval		ksFALSE		初期化失敗
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

	/* サポートされるジョイスティック数を取得します */
	numJoy = joyGetNumDevs();

	/* 存在チェック */
	if( ( numJoy < 0 ) || ( index >= numJoy ) ){
		/* 存在しない */
		return ksFALSE;
	}

	m_id = JOYSTICKID1 + index;

	/* ジョイスティックを照会してその性能を調べます。 */
	if( joyGetDevCaps( m_id, &joyCaps, sizeof(JOYCAPS) ) != JOYERR_NOERROR ){
		return ksFALSE;
	}

	/* スティックセンターのための閾値 */
	m_limit_x1 = ( joyCaps.wXmax   + joyCaps.wXmin*2 )/3;
	m_limit_x2 = ( joyCaps.wXmax*2 + joyCaps.wXmin   )/3;
	m_limit_y1 = ( joyCaps.wYmax   + joyCaps.wYmin*2 )/3;
	m_limit_y2 = ( joyCaps.wYmax*2 + joyCaps.wYmin   )/3;

	/* チェック */
	if( joyGetPosEx( m_id, &joyInfo ) != JOYERR_NOERROR ){
		return ksFALSE;
	}

//	m_active = ksTRUE;

	m_state = 1;

	return ksTRUE;
}

/************************************************************************************************/
/*
 * 入力情報を読み込み
 * @return					入力データ
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
		/* 入力を取得できない、ジョイスティックが抜かれたかもしれない */
		return 0;
	}

	x = static_cast<KsUInt32>(joyInfo.dwXpos);
	y = static_cast<KsUInt32>(joyInfo.dwYpos);

	/* 方向キーのビット情報 */
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
	
	/* 指定のボタン数分だけビット列作成 */
	for( KsUInt32 i=0;i<m_buttonMax; i++ )
	{
		//押されてたらビットをセット
		if( joyInfo.dwButtons & ( 1<<i ) )
		{
			data |= ( ksPAD_TRIG1 << i );
		}
	}

	return data;
}

/************************************************************************************************/
/*
 * 指定キーとのマージ処理
 * @param	pKd				キーアサインデータ
 * @param	pBuf			キーデータ
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
 * 更新処理
 * @param	data			入力データ
 */
/************************************************************************************************/
void KsPad::update( KsUInt32 data )
{
	m_old = m_now;
	m_now = data;
	m_trg = ( m_now ^ m_old ) & m_now;
	m_off = ( m_now ^ m_old ) & m_old;

	// 全てのデジタルキーリピート処理
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



