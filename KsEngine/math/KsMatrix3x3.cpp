/************************************************************************************************/
/** 
 * @file		KsMatrix3x3.cpp
 * @brief		�}�g���b�N�X����
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/*************************************************************************************************/
/*
 * �P�ʍs��
 */
/*************************************************************************************************/
const KsMatrix3x3 KsMatrix3x3::IDENTITY(	1.0f, 0.0f, 0.0f,
											0.0f, 1.0f, 0.0f,
											0.0f, 0.0f, 1.0f );


/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
KsMatrix3x3::KsMatrix3x3( const KsQuaternion& refQuat )
{
    const KsReal xx = refQuat.x * refQuat.x;
    const KsReal yy = refQuat.y * refQuat.y;
    const KsReal zz = refQuat.z * refQuat.z;
    const KsReal xy = refQuat.x * refQuat.y;
    const KsReal zw = refQuat.z * refQuat.w;
    const KsReal zx = refQuat.z * refQuat.x;
    const KsReal yw = refQuat.y * refQuat.w;
    const KsReal yz = refQuat.y * refQuat.z;
    const KsReal xw = refQuat.x * refQuat.w;

    m11 = 1.0f - (2.0f*(yy + zz));	m12 = 2.0f*(xy + zw);			m13 = 2.0f * (zx - yw);
    m21 = 2.0f * (xy - zw);			m22 = 1.0f - (2.0f*(zz + xx));	m23 = 2.0f * (yz + xw);
    m31 = 2.0f * (zx + yw);			m32 = 2.0f * (yz - xw);			m33 = 1.0f - (2.0f*(yy + xx));
}

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
KsMatrix3x3& KsMatrix3x3::operator = ( const KsQuaternion& refQuat )
{
	KsReal		wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

	x2 = refQuat.x + refQuat.x;
	y2 = refQuat.y + refQuat.y;
	z2 = refQuat.z + refQuat.z;

	xx = refQuat.x * x2;   xy = refQuat.x * y2;   xz = refQuat.x * z2;
	yy = refQuat.y * y2;   yz = refQuat.y * z2;   zz = refQuat.z * z2;
	wx = refQuat.w * x2;   wy = refQuat.w * y2;   wz = refQuat.w * z2;

	m11 = 1.0f - (yy + zz);	m12 = xy + wz;			m13 = xz - wy;
	m21 = xy - wz;			m22 = 1.0f - (xx + zz); m23 = yz + wx;
	m31 = xz + wy;			m32 = yz - wx;			m33 = 1.0f - (xx + yy);

	return ( *this );
}

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
const KsMatrix3x3& KsMatrix3x3::set( const KsQuaternion& refQuat )
{
	KsReal		wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

	x2 = refQuat.x + refQuat.x;
	y2 = refQuat.y + refQuat.y;
	z2 = refQuat.z + refQuat.z;

	xx = refQuat.x * x2;   xy = refQuat.x * y2;   xz = refQuat.x * z2;
	yy = refQuat.y * y2;   yz = refQuat.y * z2;   zz = refQuat.z * z2;
	wx = refQuat.w * x2;   wy = refQuat.w * y2;   wz = refQuat.w * z2;

	m11 = 1.0f - (yy + zz);	m12 = xy + wz;			m13 = xz - wy;
	m21 = xy - wz;			m22 = 1.0f - (xx + zz); m23 = yz + wx;
	m31 = xz + wy;			m32 = yz - wx;			m33 = 1.0f - (xx + yy);

	return ( *this );
}

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
KsReal KsMatrix3x3::determinant() const
{
	return m11*m22*m33 + m21*m32*m13 + m31*m12*m23 - m11*m32*m23 - m31*m22*m13 - m21*m12*m33;
}

/*************************************************************************************************/
/*
 * �t�s����擾����
 * @return						�t�s��
 */
/*************************************************************************************************/
KsMatrix3x3 KsMatrix3x3::inverse()
{
	/* �f�^�~�i���g */
	KsReal	d = determinant();

	if( d < ksTOLERANCE2 )
	{
		return KsMatrix3x3::IDENTITY;
	}

	d = 1.0f / d;

	return KsMatrix3x3( d * ( m22*m33 - m23*m32 ), d * ( m13*m32 - m12*m33 ), d * ( m12*m23 - m13*m22 ), 
						d * ( m23*m31 - m21*m33 ), d * ( m11*m33 - m13*m31 ), d * ( m13*m21 - m11*m23 ), 
						d * ( m21*m32 - m22*m31 ), d * ( m12*m31 - m11*m32 ), d * ( m11*m22 - m12*m21 ) );

}

/*************************************************************************************************/
/*
 * �]�u����
 */
/*************************************************************************************************/
void KsMatrix3x3::transpose()
{
	KsReal	temp;
	
	temp = m[0][1]; m[0][1] = m[1][0]; m[1][0] = temp;
	temp = m[0][2]; m[0][2] = m[2][0]; m[2][0] = temp;
	temp = m[1][2]; m[1][2] = m[2][1]; m[2][1] = temp;
}

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
KsQuaternion KsMatrix3x3::getRotate() const
{
	return KsQuaternion( *this );
}

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
KsVector3d KsMatrix3x3::getScale() const
{
	return KsVector3d( m[ 0 ][ 0 ], m[ 1 ][ 1 ], m[ 2 ][ 2 ] );
}

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
void KsMatrix3x3::setEulerZYX( KsReal eulerX, KsReal eulerY, KsReal eulerZ )
{ 
	KsReal ci = KsCos(eulerX); 
	KsReal cj = KsCos(eulerY); 
	KsReal ch = KsCos(eulerZ); 
	KsReal si = KsSin(eulerX); 
	KsReal sj = KsSin(eulerY); 
	KsReal sh = KsSin(eulerZ); 
	KsReal cc = ci * ch; 
	KsReal cs = ci * sh; 
	KsReal sc = si * ch; 
	KsReal ss = si * sh;

	m11 = cj * ch; m12 = sj * sc - cs; m13 = sj * cc + ss;
	m21 = cj * sh; m22 = sj * ss + cc; m23 = sj * cs - sc;
	m31 = -sj;     m32 = cj * si;      m33 = cj * ci;
}

