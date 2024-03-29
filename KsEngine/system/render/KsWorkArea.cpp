/************************************************************************************************/
/** 
 * @file		KsWorkArea.cpp
 * @brief		タスク用ワーク
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsWorkArea.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
KsInt32 KsWorkArea::m_count = 0;
KsTask* KsWorkArea::m_work[ ksWORK_AREA_MAX ];

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/	
/*
 * タスクのポインタを格納
 * @param		pTask			格納するタスクのポインタ
 */
/************************************************************************************************/
void KsWorkArea::push( KsTask* pTask )
{
	//ksAssert( m_count < ksWORK_AREA_MAX, "ワークーエリアオーバー!!" );
	m_work[ m_count ] = pTask;
	++m_count;
}
/************************************************************************************************/
/*
 * タスクのポインタを取り出し
 * @return						タスクのポインタを取り出す
 */
/************************************************************************************************/
KsTask* KsWorkArea::pop()
{
	--m_count;
	
	if( m_count < 0 ){
		return NULL;
	}

	return m_work[ m_count ];
}
/************************************************************************************************/
/*
 * ワーククリアー(カウントだけクリアーされる使う前には、必ずクリアーする)
 */
/************************************************************************************************/
void KsWorkArea::clear()
{
	m_count = 0;
}
