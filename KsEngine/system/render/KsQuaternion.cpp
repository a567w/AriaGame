/*************************************************************************************************/
/**
 * @file KsMatrix.cpp
 */
/*************************************************************************************************/

/*************************************************************************************************/
/*                                 << インクルード >>                                             */
/*************************************************************************************************/
#include "KsQuaternion.h"
#include "KsVector.h"
#include "KsMatrix.h"

/*************************************************************************************************/
/*                                     << 定義 >>                                                */
/*************************************************************************************************/

/*************************************************************************************************/
/*                                     << 宣言 >>                                                */
/*************************************************************************************************/

//===============================================================================================//
// 単位行列
//===============================================================================================//
const KsQuaternion KsQuaternion::IDENTITY( 0.0f, 0.0f, 0.0f, 1.0f );


//===============================================================================================//
//
//===============================================================================================//
KsQuaternion& KsQuaternion::operator = ( const KsMatrix& refMatrix )
{
	KsReal	trace = refMatrix.m11 + refMatrix.m[ 1 ][ 1 ] + refMatrix.m[ 2 ][ 2 ];
	KsReal	root;

	if( trace > 0.0f )
	{
		root = KsSqrt( trace + 1.0f );

		w = 0.5f * root;

		root = 0.5f / root;

		x = ( refMatrix[ 2 ][ 1 ] - refMatrix[ 1 ][ 2 ] ) * root;
		y = ( refMatrix[ 0 ][ 2 ] - refMatrix[ 2 ][ 0 ] ) * root;
		z = ( refMatrix[ 1 ][ 0 ] - refMatrix[ 0 ][ 1 ] ) * root;
	}
	else
	{
		KsInt32 next[ 3 ] = { 1, 2, 0 };
		KsInt32 i = 0;
		
		if( refMatrix[ 1 ][ 1 ] > refMatrix[ 0 ][ 0 ] ) { i = 1; }
		if( refMatrix[ 2 ][ 2 ] > refMatrix[ i ][ i ] ) { i = 2; }

		KsInt32 j = next[ i ];
		KsInt32 k = next[ j ];

		root = KsSqrt( refMatrix[ i ][ i ] - refMatrix[ j ][ j ] - refMatrix[ k ][ k ] + 1.0f );

		KsReal*		pQuat[ 3 ] = { &x, &y, &z };

		*(pQuat[ i ]) = 0.5f * root;

		root = 0.5f / root;

		w = ( refMatrix[ k ][ j ] - refMatrix[ j ][ k ] ) * root;

		*(pQuat[ j ]) = ( refMatrix[ j ][ i ] + refMatrix[ i ][ j ] ) * root;
		*(pQuat[ k ]) = ( refMatrix[ k ][ i ] + refMatrix[ i ][ k ] ) * root;
	}

	normalize();

	return (*this);
}

//===============================================================================================//
// 
//===============================================================================================//
void KsQuaternion::fromAxisRotation( const KsVector3d& refAxis, KsReal angle )
{
	KsReal	ang = 0.5f * angle;
	KsReal	sin = KsSin( ang );

	x = sin * refAxis.x;
	y = sin * refAxis.y;
	z = sin * refAxis.z;
	w = KsCos( ang );

	normalize();
}


//===============================================================================================//
// 
//===============================================================================================//
void KsQuaternion::fromEulerAngles( KsReal angleX, KsReal angleY, KsReal angleZ )
{
	KsReal		angle;
	KsReal		sr, sp, sy, cr, cp, cy;
	KsReal		cpcy, spcy, cpsy, spsy;

	/* Yaw */
	angle = 0.5f * angleZ;
	sy = KsSin( angle );
	cy = KsCos( angle );

	/* Pitch */
	angle = 0.5f * angleY;
	sp = KsSin( angle );
	cp = KsCos( angle );

	/* Roll */
	angle = 0.5f * angleX;
	sr = KsSin( angle );
	cr = KsCos( angle );

	cpcy = cp * cy;
	spcy = sp * cy;
	cpsy = cp * sy;
	spsy = sp * sy;

	x = sr * cpcy - cr * spsy;
	y = cr * spcy + sr * cpsy;
	z = cr * cpsy - sr * spcy;
	w = cr * cpcy + sr * spsy;

	normalize();
}

//===============================================================================================//
// 
//===============================================================================================//
void KsQuaternion::convertToAxisRotation( KsVector3d* pAxis, KsReal* pAngle )
{
	KsReal length = x*x + y*y + z*z;

	if ( length > 0.0 )
	{
		*pAngle = 2.0f * KsAcos( w );

		KsReal invLength = 1.0f / KsLog( length );

		pAxis->x = x * invLength;
		pAxis->y = y * invLength;
		pAxis->z = z * invLength;
	}
	else
	{
		*pAngle = 0.0f;

		pAxis->x = 0.0f;
		pAxis->y = 0.0f;
		pAxis->z = 1.0f;
	}
}

//===============================================================================================//
// 
//===============================================================================================//
KsMatrix KsQuaternion::convertToMatrix()
{
	KsMatrix matrix;

	convertToMatrix( &matrix );

	return matrix;
}



//===============================================================================================//
// 
//===============================================================================================//
void KsQuaternion::convertToMatrix( KsMatrix* pMatrix )
{
	//--------------------------------------------------------//
	//                << 行列への変換 >>                      //
	//                                                        //
	//      | 1-2*y*y-2*z*z, 2*x*y-2*w*z,   2*x*z+2*w*y   |   //
	// Rq = | 2*x*y+2*w*z,   1-2*x*x-2*z*z, 2*y*z-2*w*x   |   //
	//      | 2*x*z-2*w*y,   2*y*z+2*w*x,   1-2*x*x-2*y*y |   //
	//                                                        //
	//--------------------------------------------------------//
	
	pMatrix->m11 = 1.0f - 2.0f*y*y - 2.0f*z*z; pMatrix->m12 = 2.0f*x*y - 2.0f*w*z;        pMatrix->m13 = 2.0f*x*z + 2.0f*w*y;        pMatrix->m14 = 0.0f;
	pMatrix->m21 = 2.0f*x*y + 2.0f*w*z;        pMatrix->m22 = 1.0f - 2.0f*x*x - 2.0f*z*z; pMatrix->m23 = 2.0f*y*z - 2.0f*w*x;        pMatrix->m24 = 0.0f;
	pMatrix->m31 = 2.0f*x*z - 2.0f*w*y;        pMatrix->m32 = 2.0f*y*z + 2.0f*w*x;        pMatrix->m33 = 1.0f - 2.0f*x*x - 2.0f*y*y; pMatrix->m34 = 0.0f;
	pMatrix->m41 = 0.0f;                       pMatrix->m42 = 0.0f;                       pMatrix->m43 = 0.0f;                       pMatrix->m44 = 1.0f;
}


//===============================================================================================//
// 
//===============================================================================================//
void KsQuaternionToMatrix( KsQuaternion* pQuat, KsMatrix* pMatrix )
{
	pMatrix->m11 = 1.0f - 2.0f * pQuat->y * pQuat->y - 2.0f * pQuat->z * pQuat->z;
	pMatrix->m21 = 2.0f * pQuat->x * pQuat->y + 2.0f * pQuat->w * pQuat->z;
	pMatrix->m31 = 2.0f * pQuat->x * pQuat->z - 2.0f * pQuat->w * pQuat->y;
	pMatrix->m41 = 0.0f;

	pMatrix->m12 = 2.0f * pQuat->x * pQuat->y - 2.0f * pQuat->w * pQuat->z;
	pMatrix->m22 = 1.0f - 2.0f * pQuat->x * pQuat->x - 2.0f * pQuat->z * pQuat->z;
	pMatrix->m32 = 2.0f * pQuat->y * pQuat->z + 2.0f * pQuat->w * pQuat->x;
	pMatrix->m42 = 0.0f;

	pMatrix->m13 = 2.0f * pQuat->x * pQuat->z + 2.0f * pQuat->w * pQuat->y;
	pMatrix->m23 = 2.0f * pQuat->y * pQuat->z - 2.0f * pQuat->w * pQuat->x;
	pMatrix->m33 = 1.0f - 2.0f * pQuat->x * pQuat->x - 2.0f * pQuat->y * pQuat->y;
	pMatrix->m43 = 0.0f;

	pMatrix->m14 = 0.0f;
	pMatrix->m24 = 0.0f;
	pMatrix->m34 = 0.0f;
	pMatrix->m44 = 1.0f;
}



//===============================================================================================//
// 
//===============================================================================================//
void KsQuaternionSlerp( KsQuaternion* pOut, const KsQuaternion* pSrc, const KsQuaternion* pDest, KsReal t )
{
	/* cosθ = q1・q2  */
	KsReal		cos = pSrc->x * pDest->x + pSrc->y * pDest->y + pSrc->z * pDest->z + pSrc->w * pDest->w;
	KsReal		angle;

	if( -1.0f < cos )
	{
		if( cos < 1.0 ){
			angle = KsAcos( cos );
		}
		else{
			angle = 0.0f;
		}
	}
	else
	{
		angle = ksPI;
	}

	if( KsFabs( angle ) < 0.001f ){
		if( pOut != pSrc ){
			*pOut = *pSrc;
		}
		return;
	}

	KsReal		sin    = KsSin( angle );
	KsReal		invSin = 1.0f / sin;
	KsReal		val1   = KsSin( ( 1.0f - t ) * angle ) * invSin;
	KsReal		val2   = KsSin( t * angle ) * invSin;

	pOut->x = pSrc->x * val1 + pDest->x * val2;
	pOut->y = pSrc->y * val1 + pDest->y * val2;
	pOut->z = pSrc->z * val1 + pDest->z * val2;
	pOut->w = pSrc->w * val1 + pDest->w * val2;
}





