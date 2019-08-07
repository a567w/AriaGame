/************************************************************************************************/
/** 
 * @file		KsMatrix.cpp
 * @brief		�}�g���b�N�X����
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsPlane.h"
#include "KsMatrix.h"
#include "KsQuaternion.h"


/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

//===============================================================================================//
// �P�ʍs��
//===============================================================================================//
const KsMatrix KsMatrix::IDENTITY(	1.0f, 0.0f, 0.0f, 0.0f,
									0.0f, 1.0f, 0.0f, 0.0f,
									0.0f, 0.0f, 1.0f, 0.0f,
									0.0f, 0.0f, 0.0f, 1.0f );


/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
KsMatrix::KsMatrix( const KsQuaternion& refQuat )
{
	KsReal		wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

	x2 = refQuat.x + refQuat.x;
	y2 = refQuat.y + refQuat.y;
	z2 = refQuat.z + refQuat.z;

	xx = refQuat.x * x2;   xy = refQuat.x * y2;   xz = refQuat.x * z2;
	yy = refQuat.y * y2;   yz = refQuat.y * z2;   zz = refQuat.z * z2;
	wx = refQuat.w * x2;   wy = refQuat.w * y2;   wz = refQuat.w * z2;

	m11 = 1.0f - (yy + zz);	m12 = xy + wz;			m13 = xz - wy;			m14 = 0.0f;
	m21 = xy - wz;			m22 = 1.0f - (xx + zz); m23 = yz + wx;			m24 = 0.0f;
	m31 = xz + wy;			m32 = yz - wx;			m33 = 1.0f - (xx + yy);	m34 = 0.0f;
	m41 = 0.0f;				m42 = 0.0f;				m43 = 0.0f;				m44 = 1.0f;
}

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
KsMatrix& KsMatrix::operator = ( const KsQuaternion& refQuat )
{
	KsReal		wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

	x2 = refQuat.x + refQuat.x;
	y2 = refQuat.y + refQuat.y;
	z2 = refQuat.z + refQuat.z;

	xx = refQuat.x * x2;   xy = refQuat.x * y2;   xz = refQuat.x * z2;
	yy = refQuat.y * y2;   yz = refQuat.y * z2;   zz = refQuat.z * z2;
	wx = refQuat.w * x2;   wy = refQuat.w * y2;   wz = refQuat.w * z2;

	m11 = 1.0f - (yy + zz);	m12 = xy + wz;			m13 = xz - wy;			m14 = 0.0f;
	m21 = xy - wz;			m22 = 1.0f - (xx + zz); m23 = yz + wx;			m24 = 0.0f;
	m31 = xz + wy;			m32 = yz - wx;			m33 = 1.0f - (xx + yy);	m34 = 0.0f;
	m41 = 0.0f;				m42 = 0.0f;				m43 = 0.0f;				m44 = 1.0f;

	return ( *this );
}

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
const KsMatrix& KsMatrix::set( const KsQuaternion& refQuat )
{
	KsReal		wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

	x2 = refQuat.x + refQuat.x;
	y2 = refQuat.y + refQuat.y;
	z2 = refQuat.z + refQuat.z;

	xx = refQuat.x * x2;   xy = refQuat.x * y2;   xz = refQuat.x * z2;
	yy = refQuat.y * y2;   yz = refQuat.y * z2;   zz = refQuat.z * z2;
	wx = refQuat.w * x2;   wy = refQuat.w * y2;   wz = refQuat.w * z2;

	m11 = 1.0f - (yy + zz);	m12 = xy + wz;			m13 = xz - wy;			m14 = 0.0f;
	m21 = xy - wz;			m22 = 1.0f - (xx + zz); m23 = yz + wx;			m24 = 0.0f;
	m31 = xz + wy;			m32 = yz - wx;			m33 = 1.0f - (xx + yy);	m34 = 0.0f;
	m41 = 0.0f;				m42 = 0.0f;				m43 = 0.0f;				m44 = 1.0f;

	return ( *this );
}

/************************************************************************************************/
/*
 * �����ˉe�s��𐶐�����(�E��n)
 * @param		projMatrix		�v���W�F�N�V�����}�g���b�N�X�ۑ��p
 * @param		fovy			����p
 * @param		aspect			�A�X�y�N�g��
 * @param		zNear			�ߋ����l
 * @param		zFar			�������l
 */
/************************************************************************************************/
void KsMatrixPerspectiveRH( KsMatrix& projMatrix, KsReal fovy, KsReal aspect, KsReal zNear, KsReal zFar )
{
	KsReal		th = fovy/2.0f;
	KsReal		f  = KsCos( th ) / KsSin( th );

	projMatrix.m11 =  f/aspect;
	projMatrix.m12 =  0.0f;
	projMatrix.m13 =  0.0f;
	projMatrix.m14 =  0.0f;

	projMatrix.m21 =  0.0f;
	projMatrix.m22 =  f;
	projMatrix.m23 =  0.0f;
	projMatrix.m24 =  0.0f;

	projMatrix.m31 =  0.0f;
	projMatrix.m32 =  0.0f;
	projMatrix.m33 =  ( zFar + zNear )/( zNear - zFar );
	projMatrix.m34 = -1.0f;

	projMatrix.m41 =  0.0f;
	projMatrix.m42 =  0.0f;
	projMatrix.m43 =  2.0f*zFar*zNear/( zNear - zFar );
	projMatrix.m44 =  0.0f;
}

/************************************************************************************************/
/*
 * ���ˉe�s��𐶐�����(�E��n)
 * @param		projMatrix		�v���W�F�N�V�����}�g���b�N�X�ۑ��p
 * @param		left			���t�g
 * @param		right			���C�g
 * @param		bottom			�{�g��
 * @param		top				�g�b�v
 * @param		aspect			�A�X�y�N�g��
 * @param		zNear			�ߋ����l
 * @param		zFar			�������l
 */
/************************************************************************************************/
void KsMatrixOrthoRH( KsMatrix& projMatrix, KsReal left, KsReal right, KsReal bottom, KsReal top, KsReal zNear, KsReal zFar )
{
	projMatrix.m11 =  2.0f/( right - left );
	projMatrix.m12 =  0.0f;
	projMatrix.m13 =  0.0f;
	projMatrix.m14 =  0.0f;

	projMatrix.m21 =  0.0f;
	projMatrix.m22 =  2.0f/( top - bottom );
	projMatrix.m23 =  0.0f;
	projMatrix.m24 =  0.0f;

	projMatrix.m31 =  0.0f;
	projMatrix.m32 =  0.0f;
	projMatrix.m33 = -2.0f/( zFar - zNear );
	projMatrix.m34 =  0.0f;

	projMatrix.m41 = -( right + left )/( right - left );
	projMatrix.m42 = -( top + bottom )/( top - bottom );
	projMatrix.m43 = -( zFar + zNear )/( zFar - zNear );
	projMatrix.m44 =  1.0f;
}

/************************************************************************************************/
/*
 * ���_��ݒ肷��(�E��n)
 * @param		viewMatrix		�r���[�}�g���b�N�X�ۑ��p
 * @param		eye				���_
 * @param		at				�����_
 * @param		up				�A�b�v�x�N�g��
 */
/************************************************************************************************/
void KsMatrixLookAtRH( KsMatrix& viewMatrix, const KsVector3d& eye, const KsVector3d& at, const KsVector3d& up )
{
	KsVector3d		xaxis;
	KsVector3d		yaxis;
	KsVector3d		zaxis;

	zaxis = eye - at;
	zaxis.normalize();
	
	xaxis = KsCrossProduct( up, zaxis );
	xaxis.normalize();

	yaxis = KsCrossProduct( zaxis, xaxis );

	viewMatrix.m11 =  xaxis.x;
	viewMatrix.m21 =  xaxis.y;
	viewMatrix.m31 =  xaxis.z;
	viewMatrix.m41 = -xaxis.dotProduct( eye );
	
	viewMatrix.m12 =  yaxis.x;
	viewMatrix.m22 =  yaxis.y;
	viewMatrix.m32 =  yaxis.z;
	viewMatrix.m42 = -yaxis.dotProduct( eye );

	viewMatrix.m13 =  zaxis.x;
	viewMatrix.m23 =  zaxis.y;
	viewMatrix.m33 =  zaxis.z;
	viewMatrix.m43 = -zaxis.dotProduct( eye );

	viewMatrix.m14 =  0.0f;
	viewMatrix.m24 =  0.0f;
	viewMatrix.m34 =  0.0f;
	viewMatrix.m44 =  1.0f;
}

/************************************************************************************************/
/*
 * �����ˉe�s��𐶐�����(����n)
 * @param		projMatrix		�v���W�F�N�V�����}�g���b�N�X�ۑ��p
 * @param		fovy			����p
 * @param		aspect			�A�X�y�N�g��
 * @param		zNear			�ߋ����l
 * @param		zFar			�������l
 */
/************************************************************************************************/
void KsMatrixPerspectiveLH( KsMatrix& projMatrix, KsReal fovy, KsReal aspect, KsReal zNear, KsReal zFar )
{
	KsReal		th = fovy/2.0f;
	KsReal		f  = KsCos( th ) / KsSin( th );

	projMatrix.m11 =  f/aspect;
	projMatrix.m12 =  0.0f;
	projMatrix.m13 =  0.0f;
	projMatrix.m14 =  0.0f;

	projMatrix.m21 =  0.0f;
	projMatrix.m22 =  f;
	projMatrix.m23 =  0.0f;
	projMatrix.m24 =  0.0f;

	projMatrix.m31 =  0.0f;
	projMatrix.m32 =  0.0f;
	projMatrix.m33 =  ( zFar + zNear )/( zNear - zFar );
	projMatrix.m34 =  1.0f;

	projMatrix.m41 =  0.0f;
	projMatrix.m42 =  0.0f;
	projMatrix.m43 =  2.0f*zFar*zNear/( zNear - zFar );
	projMatrix.m44 =  0.0f;
}

/************************************************************************************************/
/*
 * ���ˉe�s��𐶐�����(����n)
 * @param		projMatrix		�v���W�F�N�V�����}�g���b�N�X�ۑ��p
 * @param		left			���t�g
 * @param		right			���C�g
 * @param		bottom			�{�g��
 * @param		top				�g�b�v
 * @param		aspect			�A�X�y�N�g��
 * @param		zNear			�ߋ����l
 * @param		zFar			�������l
 */
/************************************************************************************************/
void KsMatrixOrthoLH( KsMatrix& projMatrix, KsReal left, KsReal right, KsReal bottom, KsReal top, KsReal zNear, KsReal zFar )
{
	projMatrix.m11 =  2.0f/( right - left );
	projMatrix.m12 =  0.0f;
	projMatrix.m13 =  0.0f;
	projMatrix.m14 =  0.0f;

	projMatrix.m21 =  0.0f;
	projMatrix.m22 =  2.0f/( top - bottom );
	projMatrix.m23 =  0.0f;
	projMatrix.m24 =  0.0f;

	projMatrix.m31 =  0.0f;
	projMatrix.m32 =  0.0f;
	projMatrix.m33 = -2.0f/( zFar - zNear );
	projMatrix.m34 =  0.0f;

	projMatrix.m41 = -( right + left )/( right - left );
	projMatrix.m42 = -( top + bottom )/( top - bottom );
	projMatrix.m43 = -( zFar + zNear )/( zFar - zNear );
	projMatrix.m44 = -1.0f;
}
/************************************************************************************************/
/*
 * ���_��ݒ肷��(����n)
 * @param		viewMatrix		�r���[�}�g���b�N�X�ۑ��p
 * @param		eye				���_
 * @param		at				�����_
 * @param		up				�A�b�v�x�N�g��
 */
/************************************************************************************************/
void KsMatrixLookAtLH( KsMatrix& viewMatrix, const KsVector3d& eye, const KsVector3d& at, const KsVector3d& up )
{
	KsVector3d		xaxis;
	KsVector3d		yaxis;
	KsVector3d		zaxis;

	zaxis = at - eye;
	zaxis.normalize();
	
	xaxis = KsCrossProduct( up, zaxis );
	xaxis.normalize();

	yaxis = KsCrossProduct( zaxis, xaxis );

	viewMatrix.m11 =  xaxis.x;
	viewMatrix.m21 =  xaxis.y;
	viewMatrix.m31 =  xaxis.z;
	viewMatrix.m41 = -xaxis.dotProduct( eye );
	
	viewMatrix.m12 =  yaxis.x;
	viewMatrix.m22 =  yaxis.y;
	viewMatrix.m32 =  yaxis.z;
	viewMatrix.m42 = -yaxis.dotProduct( eye );

	viewMatrix.m13 =  zaxis.x;
	viewMatrix.m23 =  zaxis.y;
	viewMatrix.m33 =  zaxis.z;
	viewMatrix.m43 = -zaxis.dotProduct( eye );

	viewMatrix.m14 =  0.0f;
	viewMatrix.m24 =  0.0f;
	viewMatrix.m34 =  0.0f;
	viewMatrix.m44 =  1.0f;	
}

/************************************************************************************************/
/*
 * ���C�g����e���ˉe����悤��,�W�I���g���𕽖ʂɎˉe����B
 * @param		matrix			�r���[�}�g���b�N�X�ۑ��p
 * @param		eye				���_
 * @param		at				�����_
 * @param		up				�A�b�v�x�N�g��
 * @note
 * ���̊֐����Ԃ��s��́A���̌������g���Čv�Z����B 
 *	P = normalize(Plane);
 *	L = Light;
 *	d = dot(P, L)
 *
 *	P.a * L.x + d  P.a * L.y      P.a * L.z      P.a * L.w  
 *	P.b * L.x      P.b * L.y + d  P.b * L.z      P.b * L.w  
 *	P.c * L.x      P.c * L.y      P.c * L.z + d  P.c * L.w  
 *	P.d * L.x      P.d * L.y      P.d * L.z      P.d * L.w + d
 */
/************************************************************************************************/
void KsMatrixShadow( KsMatrix& shadowMatrix, const KsVector3d& light, const KsPlane& refPlane, KsReal point )
{
	KsPlane		plane = refPlane;
	
	plane.m_normal.normalize();
	
	KsReal		d = plane.distance( light );

	shadowMatrix.m11 = plane.m_normal.x * light.x + d;
	shadowMatrix.m21 = plane.m_normal.y * light.x;
	shadowMatrix.m31 = plane.m_normal.z * light.x;
	shadowMatrix.m41 = plane.m_distance * light.x;
	
	shadowMatrix.m12 = plane.m_normal.x * light.y;
	shadowMatrix.m22 = plane.m_normal.y * light.y + d;
	shadowMatrix.m32 = plane.m_normal.z * light.y;
	shadowMatrix.m42 = plane.m_distance * light.y;

	shadowMatrix.m13 = plane.m_normal.x * light.z;
	shadowMatrix.m23 = plane.m_normal.y * light.z;
	shadowMatrix.m33 = plane.m_normal.z * light.z + d;
	shadowMatrix.m43 = plane.m_distance * light.z;

	shadowMatrix.m14 = plane.m_normal.x * point;
	shadowMatrix.m24 = plane.m_normal.y * point;
	shadowMatrix.m34 = plane.m_normal.z * point;
	shadowMatrix.m44 = plane.m_distance * point + d;
}



