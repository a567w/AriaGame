/*************************************************************************************************/
/*                                                                                               */
/*                           << KsVector2d クラスのインライン関数 >>                             */
/*                                                                                               */
/*************************************************************************************************/
//===============================================================================================//
// 配列内の値を返す
//===============================================================================================//
inline KsReal& KsVector2d::operator [] ( KsInt32 index )
{
	return( ( (KsReal*)&x )[ index ] );
}
//===============================================================================================//
// 配列内の値を返す
//===============================================================================================//
inline const KsReal& KsVector2d::operator [] ( KsInt32 index ) const
{
	return( ( (KsReal*)&x )[ index ] );
}
//===============================================================================================//
// = 演算子 (代入)
//===============================================================================================//
inline const KsVector2d& KsVector2d::operator = ( const KsVector2d &refVector )
{
	x = refVector.x;
	y = refVector.y;

	return( *this );
}
//===============================================================================================//
// += 演算子
//===============================================================================================//
inline KsVector2d& KsVector2d::operator += ( const KsVector2d& refVector )
{
	x += refVector.x;
	y += refVector.y;

	return	(*this);
}
//===============================================================================================//
// -= 演算子
//===============================================================================================//
inline KsVector2d& KsVector2d::operator -= ( const KsVector2d& refVector )
{
	x -= refVector.x;
	y -= refVector.y;

	return	(*this);
}
//===============================================================================================//
//  *= 演算子
//===============================================================================================//
inline KsVector2d& KsVector2d::operator *= ( KsReal s )
{
	x *= s;
	y *= s;

	return	(*this);
}
//===============================================================================================//
//  /= 演算子
//===============================================================================================//
inline KsVector2d& KsVector2d::operator /= ( KsReal s )
{
	if( s < ksTOLERANCE ){
		return (*this);
	}

	x /= s;
	y /= s;

	return	(*this);
}
//===============================================================================================//
// + 演算子(加算)
//===============================================================================================//
inline KsVector2d KsVector2d::operator + () const 
{
	return ( *this );
}

//===============================================================================================//
// - 演算子(減算)
//===============================================================================================//
inline KsVector2d KsVector2d::operator - () const 
{
	return KsVector2d( -x, -y );
}
//===============================================================================================//
// + 演算子(加算)
//===============================================================================================//
inline KsVector2d KsVector2d::operator + ( const KsVector2d& refVector ) const 
{
	return KsVector2d( x + refVector.x, y + refVector.y );
}
//===============================================================================================//
// - 演算子(減算)
//===============================================================================================//
inline KsVector2d KsVector2d::operator - ( const KsVector2d& refVector ) const 
{
	return KsVector2d( x - refVector.x, y - refVector.y );
}
//===============================================================================================//
// * 演算子(掛算) 
//===============================================================================================//
inline KsVector2d KsVector2d::operator * ( KsReal s ) const 
{
	return KsVector2d( s*x, s*y );
}
//===============================================================================================//
// / 演算子(割算)
//===============================================================================================//
inline KsVector2d KsVector2d::operator / ( KsReal s ) const 
{
	if( KsFabs( s ) < ksTOLERANCE ){
		KsVector2d( x, y );
	}

	return KsVector2d( x/s, y/s );
}
//===============================================================================================//
// == 演算子(比較)
//===============================================================================================//
inline KsBool KsVector2d::operator == ( const KsVector2d& refVector ) const 
{
	return ( ( KsFabs( x - refVector.x ) < ksTOLERANCE ) && ( KsFabs( y - refVector.y ) < ksTOLERANCE ) );
}
//===============================================================================================//
// != 演算子(比較)
//===============================================================================================//
inline KsBool KsVector2d::operator != ( const KsVector2d& refVector ) const 
{
	return ( ( KsFabs( x - refVector.x ) > ksTOLERANCE ) || ( KsFabs( y - refVector.y ) > ksTOLERANCE ) );
}
//===============================================================================================//
// 値をセットする
//===============================================================================================//
inline void KsVector2d::set( KsReal xf, KsReal yf )
{
	x = xf;
	y = yf;
}
//===============================================================================================//
// 値をセットする
//===============================================================================================//
inline void KsVector2d::set( const KsReal* fArray )
{
	x = fArray[ 0 ];
	y = fArray[ 1 ];
}
//===============================================================================================//
//　指定された長さのベクトルに変更する
//===============================================================================================//
inline void KsVector2d::scaleTo( KsReal len )
{
	KsReal	len2 = length2();

	if( (len2 > ksTOLERANCE) && (KsFabs( len2 - (len*len) ) > ksTOLERANCE) )
	{
		KsReal	factor = ( len / KsSqrt( len2 ) );

		x *= factor;
		y *= factor;
	}
}
//===============================================================================================//
// 0.0fでリセットする
//===============================================================================================//
inline void KsVector2d::reset()
{
	x = y = 0.0f;
}

//===============================================================================================//
// 長さを求める
//===============================================================================================//
inline KsReal KsVector2d::length()
{
	return KsSqrt( x*x + y*y );
}
//===============================================================================================//
// 長さの2乗を求める
//===============================================================================================//
inline KsReal KsVector2d::length2()
{
	return ( x*x + y*y );
}
//===============================================================================================//
// 正規化
//===============================================================================================//
inline void KsVector2d::normalize()
{
	KsReal	norm = x*x + y*y;

	if( ( KsFabs( norm - 1.0f ) < ksTOLERANCE ) || ( norm < ksTOLERANCE2 ) ){
		return;
	}

	KsReal invNorm = 1.0f / KsSqrt( norm );

	x *= invNorm;
	y *= invNorm;
}
//===============================================================================================//
// 内積
//===============================================================================================//
inline KsReal KsVector2d::dotProduct( const KsVector2d& refVector ) const
{
	return ( x*refVector.x + y*refVector.y );
}











