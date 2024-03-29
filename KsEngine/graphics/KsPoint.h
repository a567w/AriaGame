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

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

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
class ksENGINE_API KsPoint
{
	public:
		KsInt32					x;
		KsInt32					y;

	public:
								KsPoint();
								KsPoint( KsInt32 x, KsInt32 y );
								KsPoint( KsReal x, KsReal y );
		void					set( KsInt32 x, KsInt32 y );
		void					set( KsReal x, KsReal y );
		KsPoint&				operator += ( const KsPoint& rhs );
		KsPoint					operator + ( const KsPoint& rhs ) const;
		KsPoint&				operator -= ( const KsPoint& rhs );
		KsPoint					operator - ( const KsPoint& rhs ) const;
		KsInt32&				operator [] ( KsUInt32 index );
		const KsInt32&			operator [] ( KsUInt32 index ) const;
		KsBool					operator == ( const KsPoint& rhs ) const;
		KsBool					operator != ( const KsPoint& rhs ) const;

		static const KsPoint	ZERO;
};


/*************************************************************************************************/
/*---------------------------<< インライン部分ヘッダーファイル >>--------------------------------*/
								#include "KsPoint.inl"
/*-----------------------------------------------------------------------------------------------*/
/*************************************************************************************************/

#endif /* __KSPOINT_H__ */