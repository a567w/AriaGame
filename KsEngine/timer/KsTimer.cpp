/************************************************************************************************/
/** 
 * @file		KsTimer.cpp
 * @brief		タイマー
 * @author		Tsukasa Kato
 * @data		2005/06/27
 * @since		2005/06/27
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
LARGE_INTEGER	KsTimer::m_frequency;
KsBool			KsTimer::m_support          = ksFALSE;
KsReal			KsTimer::m_frameTime        = ( 1.0f/60.0f );
KsUInt32		KsTimer::m_initTime         = 0;
KsUInt32		KsTimer::m_frameCount       = 0;
KsUInt32		KsTimer::m_fpsCount         = 0;
KsUInt32		KsTimer::m_fps              = 0;
KsUInt32		KsTimer::m_lastFrameTime    = 0;
KsUInt32		KsTimer::m_startTime        = 0;
KsUInt32		KsTimer::m_cpuTime          = 0;
KsUInt32		KsTimer::m_gpuTime          = 0;
KsUInt32		KsTimer::m_totalTime        = 0;
KsUInt32		KsTimer::m_cpuPerformance   = 0;
KsUInt32		KsTimer::m_gpuPerformance   = 0;
KsUInt32		KsTimer::m_totalPerformance = 0;

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsTimer::KsTimer()
{
	m_elapsedTime = 1.0f/60.0f;
}

/************************************************************************************************/
/*
 * 初期化
 */
/************************************************************************************************/
void KsTimer::initialize()
{
	if( QueryPerformanceFrequency( &m_frequency ) ){
		m_support = ksTRUE;
	}
	else{
		m_support   = ksFALSE;
	}

	m_initTime         = 0;
	m_frameCount       = 0;
	m_fpsCount         = 0;
	m_fps              = 0;
	m_lastFrameTime    = 0;
	m_startTime        = 0;
	m_cpuTime          = 0;
	m_gpuTime          = 0;
	m_totalTime        = 0;
	m_cpuPerformance   = 0;
	m_gpuPerformance   = 0;
	m_totalPerformance = 0;
}

/************************************************************************************************/
/*
 * ミリ秒で時間を取得
 * @return		ミリ秒
 */
/************************************************************************************************/
KsUInt32 KsTimer::getTimeCount()
{
	if( m_support )
	{
		LARGE_INTEGER	time;
		QueryPerformanceCounter( &time );
		return static_cast<KsUInt32>( ( time.QuadPart ) * 1000 / m_frequency.QuadPart );
	}

	return static_cast< KsUInt32 >( GetTickCount64() );
}

/************************************************************************************************/
/*
 * マイクロ秒で時間を取得
 * @return						ミリ秒
 */
/************************************************************************************************/
KsInt64 KsTimer::getMicroCount()
{
	if( m_support )
	{
		LARGE_INTEGER	time;
		QueryPerformanceCounter( &time );
		return static_cast<KsInt64>( time.QuadPart * 1000000 / m_frequency.QuadPart );
	}

	return static_cast< KsInt64 >( GetTickCount64()*1000 );
}

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
KsUInt32 KsTimer::getFps() 
{
	return (m_fps+1);
}

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
KsUInt32 KsTimer::getFrameCount() 
{
	return m_frameCount;
}

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
void KsTimer::update()
{
	KsUInt32	now = getTimeCount();

	/* FPS更新 */
	if( now > ( m_lastFrameTime + 1000 ) )
	{
		m_fps           = m_fpsCount;
		m_fpsCount      = 0;
		m_lastFrameTime = now;
	}

	/* 経過フレーム更新 */
	++m_frameCount;
	++m_fpsCount;
}

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
void KsTimer::vsync( ksFPS_TYPE _fpsType )
{
	static KsUInt32 fpsTbl[] = { 16, 34, 71 };
	static KsUInt32 endTime  = timeGetTime();
			KsUInt32 counter  = fpsTbl[ _fpsType ];
			KsUInt32 nowTime;

	while( 1 )
	{
		nowTime = getTimeCount();

		if( counter < (nowTime - endTime) )
		{
			endTime = nowTime;
			break;
		}
		else
		{
			::Sleep( 0 );
		}
	}
}

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
void KsTimer::setStart()
{
	m_cpuPerformance   = (KsUInt32)( (KsReal)( m_cpuTime - m_startTime ) / m_frameTime * 0.1f );
	m_gpuPerformance   = (KsUInt32)( (KsReal)( m_gpuTime - m_cpuTime ) / m_frameTime * 0.1f );
	m_totalPerformance = (KsUInt32)( (KsReal)( m_totalTime - m_startTime ) / m_frameTime * 0.1f );

	m_startTime = getTimeCount();
}

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
void KsTimer::setCpu()
{
	m_cpuTime = getTimeCount();
}

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
void KsTimer::setGpu()
{
	m_gpuTime = getTimeCount();
}

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
void KsTimer::setTotal()
{
	m_totalTime = getTimeCount();
}

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
KsUInt32 KsTimer::getCpuPerformance()
{
	return m_cpuPerformance;
}

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
KsUInt32 KsTimer::getGpuPerformance()
{
	return m_gpuPerformance;
}

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
KsUInt32 KsTimer::getTotalPerformance()
{
	return m_totalPerformance;
}


