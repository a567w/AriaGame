/************************************************************************************************/
/** 
 * @file		KsPoint.h
 * @brief		
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSPOINT_H__
#define __KSPOINT_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsCore.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

#if 0
//namespace deep
//{

	//namespace gui
	//{
/************************************************************************************************/
/**
 * @class		KsPoint
 * @brief		ジョイパッド取得クラス(Windows関数用)
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
class ksENGINE_API KsObject
{
		enum ksHitTestResult
		{
			ksOUTSIDE	= 0x0000,
			ksINSIDE	= 0x0001,
			ksEDGE		= 0x0003
		};

	public:
		KsUInt32				m_id;
		KsUInt32				m_flags;
		KsString				m_name;
		KsObject*				m_pParent;
		KsArray< KsObject* >	m_vpChildren;
		KsPoint					m_pos;
		KsPoint					m_posReal;
		KsPoint					m_size;

		void					update() = 0;
		void					draw() = 0;

		KsObject*				getParent() const { return m_pParent; }

		KsUInt32				getNumChildren() const;
	
		KsObject*				getChild( KsUInt32 index );
		ksHitTestResult			hitTest( const KsPoint& point ) const;

KsObject::HitTestResult KsObject::hitTest( const KsPoint& point ) const
{
	if(		( point.x < m_posReal.x ) 
		||	( point.y < m_posReal.y )
		||	( point.x >= ( m_posReal.x + m_size.x ) )
		||	( point.y >= ( m_posReal.y + m_size.y ) ) 
		)
	{
		return ksOUTSIDE;
	}

	if(		( point.x ==   m_posReal.x ) 
		||	( point.y ==   m_posReal.y ) 
		||	( point.x == ( m_posReal.x + m_size.x - 1 ) ) 
		||	( point.y == ( m_posReal.y + m_size.y - 1 ) ) 
		)
	{
		return ksEDGE;
	}

	return ksINSIDE;
}


};

class KsButton : public KsObject

	//! Callback when button has been pressed
	virtual void                                            onPress();

	virtual void                                            onMouseEnter( const input::MouseEvent* p_event );
	virtual void                                            onMouseLeave();
	virtual void                                            onMouseDown( const input::MouseEvent* p_event );
	virtual void                                            onMouseUp( const input::MouseEvent* p_event );
/*************************************************************************************************/
/*---------------------------<< インライン部分ヘッダーファイル >>--------------------------------*/
								//#include "KsPoint.inl"
/*-----------------------------------------------------------------------------------------------*/
/*************************************************************************************************/
#endif
//};
//};

#endif /* __KSPOINT_H__ */