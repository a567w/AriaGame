/************************************************************************************************/
/** 
 * @file		KsFlashRect.h
 * @brief		FLASH用Rect
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSFLASHRECT_H__
#define __KSFLASHRECT_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsCore.h"

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsFlashRect
 * @brief		FLASH用Rect
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 * @note		なし
 */
/************************************************************************************************/
class KsFlashRect
{
	public:
		/**
		 * コンストラクタ
		 * @param	x1		左上位置標
		 * @param	y1		左上位置標
		 * @param	x2		左上位置標
		 * @param	y2		左上位置標
		 */
							KsFlashRect( KsInt32 x1, KsInt32 y1, KsInt32 x2, KsInt32 y2 );

		/**
		 * デフォルトコンストラクタ
		 */
							KsFlashRect();

		/**
		 * デストラクタ
		 */
	    virtual			~KsFlashRect();

		/**
		 * 定義されているかのチェック
		 * @retval	ksTRUE	
		 * @retval	ksFALSE	
		 */
	    KsBool				isDefined() const { return m_defined; }

		/**
		 * コンストラクタ
		 * @param	x1		左上位置標
		 * @param	y1		左上位置標
		 * @param	x2		左上位置標
		 * @param	y2		左上位置標
		 */
		void				setRect( KsInt32 x1, KsInt32 y1, KsInt32 x2, KsInt32 y2 );
	    
	    KsInt32				getX1() const { return m_x1; }
	    KsInt32				getX2() const { return m_x2; }
	    KsInt32				getY1() const { return m_y1; }
	    KsInt32				getY2() const { return m_y2; }

	    void				boundWith( const KsFlashRect &rect );

	private:
	    KsInt32				m_x1;			/**< */
	    KsInt32				m_y1;			/**< */
	    KsInt32				m_x2;			/**< */
	    KsInt32				m_y2;			/**< */
	    KsBool				m_defined;		/**< */
};


KsFlashRect::KsFlashRect()
	: x1( 0 )
	, y1( 0 )
	, x2( 0 )
	, y2( 0 )
	, m_defined( ksFALSE )
{
}

/**
* コンストラクタ
* @param	x1		左上位置標
* @param	y1		左上位置標
* @param	x2		左上位置標
* @param	y2		左上位置標
*/
KsFlashRect::KsFlashRect( KsInt32 x1, KsInt32 y1, KsInt32 x2, KsInt32 y2 )
	: m_x1( x1 )
	, m_y1( y1 )
	, m_x2( x2 )
	, m_y2( y2 )
	, m_defined( ksFALSE )
{
}

KsFlashRect::~KsFlashRect()
{
}

void KsFlashRect::setRect( KsInt32 x1, KsInt32 y1, KsInt32 x2, KsInt32 y2 )
{
	m_x1 = x1;
	m_y1 = y1;
	m_x2 = x2;
	m_y2 = y2;
}

void KsFlashRect::boundWith( const KsFlashRect &rect )
{
	x1 = min(x1,r.x1);
	x2 = max(x2, r.x2);
	y1 = min(y1,r.y1);
	y2 = max(y2, r.y2);
}

#endif	/* __KSFLASHRECT_H__ */

