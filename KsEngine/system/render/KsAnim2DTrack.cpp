/************************************************************************************************/
/** 
 * @file		KsAnimTrack.cpp
 * @brief		ボーン
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsAnim2DTrack.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsAnimKeyFrame
 * @brief		アニメーション
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
KsInt32 KsAnim2DTrack::getKeyFrame( KsReal time, KsReal *pParam, KsAnim2DKeyFrame* pKey1, KsAnim2DKeyFrame* pKey2, KsBool bLoop )
{
	if( time == 0.0f )
	{
		*pKey1  = *m_vKeyFrames[ 0 ];
		*pKey2  = *m_vKeyFrames[ 0 ];
		*pParam = 0.0f;
		return 0;
	}

	KsInt32	num = getNumKeyFrame()-1;

	if( time >= m_maxTime )
	{
		if( !bLoop )
		{
			*pKey1  = *m_vKeyFrames[ num ];
			*pKey2  = *m_vKeyFrames[ num ];
			*pParam = 1.0f;
			return num;
		}

		KsReal		param = KsFloor( time / m_maxTime );

		time = time - param * m_maxTime;
	}


	for( KsInt32 i=0; i<num; i++ )
	{
		if( (m_vKeyFrames[ i ]->m_time <= time) && (time < m_vKeyFrames[ i+1 ]->m_time) )
		{
			*pKey1 = *m_vKeyFrames[ i ];
			*pKey2 = *m_vKeyFrames[ i+1 ];

			KsReal	ft = time - m_vKeyFrames[ i ]->m_time;
			KsReal dt = m_vKeyFrames[ i+1 ]->m_time - m_vKeyFrames[ i ]->m_time;
			KsReal t;
			
			if( dt > 0.00000001f )
			{ 
				t = ft/dt;
			}
			else{
				t = 0.0f;
			}

			*pParam = t;

			return i;
		}
	}

	return -1;
}


