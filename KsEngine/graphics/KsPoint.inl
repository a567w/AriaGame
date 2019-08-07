

inline KsPoint::KsPoint()
	: x( 0 )
	, y( 0 )
{
}


inline KsPoint::KsPoint( KsInt32 x, KsInt32 y )
	: x( x )
	, y( y )
{
}


inline KsPoint::KsPoint( KsReal x, KsReal y )
	: x( s_cast<KsInt32>(x) )
	, y( s_cast<KsInt32>(y) )
{
}

inline void KsPoint::set( KsInt32 x, KsInt32 y )
{
	x = x;
	y = y;
}


inline KsPoint& KsPoint::operator += ( const KsPoint& rhs )
{
	x += rhs.x;
	y += rhs.y;
	return( *this );
}


inline KsPoint KsPoint::operator + ( const KsPoint& rhs ) const
{
	return KsPoint( x + rhs.x, y + rhs.y );
}


inline KsPoint& KsPoint::operator -= ( const KsPoint& rhs )
{
	x -= rhs.x;
	y -= rhs.y;
	return( *this );
}


inline KsPoint KsPoint::operator - ( const KsPoint& rhs ) const
{
	return KsPoint( x - rhs.x, y - rhs.y );
}


inline KsInt32& KsPoint::operator [] ( KsUInt32 index )
{
	return (&x)[index];
}


inline const KsInt32& KsPoint::operator [] ( KsUInt32 index ) const
{
	return (&x)[index];
}


inline KsBool KsPoint::operator == ( const KsPoint& rhs ) const
{
	return( ( x == rhs.x ) && ( y == rhs.y ) );
}


inline KsBool KsPoint::operator != ( const KsPoint& rhs ) const
{
	return( ( x != rhs.x ) || ( y != rhs.y ) );
}

