/************************************************************************************************/
/** 
 * @file		KsRect.h
 * @brief		
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSRECT_H__
#define __KSRECT_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsCore.h"
#include "KsPoint.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsRect
 * @brief		
 * @author		Tsukasa Kato
 * @date		2004/03/30
 * @version		1.0.0
 */
/************************************************************************************************/
class ksENGINE_API KsRect
{
	public:
		KsInt32				x;
		KsInt32				y;
		KsInt32				w;
		KsInt32				h;


#if 0
	public:
								KsRect();
								KsRect( const KsPoint& origin, const KsPoint& size );
								KsRect( KsInt32 originX, KsInt32 originY, KsInt32 sizeX, KsInt32 sizeY );
								KsRect( KsReal originX, KsReal originY, KsReal sizeX, KsReal sizeY );
		void					set( KsInt32 originX, KsInt32 originY, KsInt32 sizeX, KsInt32 sizeY );
		void					set( KsReal originX, KsReal originY, KsReal sizeX, KsReal sizeY );
		void					set( const Point& origin, const Point& size );
		void					setOrigin( const Point& origin );
		void					setSize( const Point& size );
		const KsPoint&			getOrigin() const;
		const KsPoint&			getSize() const;
		KsBool					isEmpty() const;
	private:
		KsPoint					m_origin;
		KsPoint					m_size;
#endif
};


/*************************************************************************************************/
/*---------------------------<< インライン部分ヘッダーファイル >>--------------------------------*/
								//#include "KsRect.inl"
/*-----------------------------------------------------------------------------------------------*/
/*************************************************************************************************/


#endif /* __KSRECT_H__ */

