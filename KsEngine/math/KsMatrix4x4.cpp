/************************************************************************************************/
/** 
 * @file		KsMatrix4x4.cpp
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
const KsMatrix4x4 KsMatrix4x4::IDENTITY( 1.0f, 0.0f, 0.0f, 0.0f,
										 0.0f, 1.0f, 0.0f, 0.0f,
										 0.0f, 0.0f, 1.0f, 0.0f,
										 0.0f, 0.0f, 0.0f, 1.0f );


/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
KsMatrix4x4::KsMatrix4x4( const KsQuaternion& refQuat )
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

    m11 = 1.0f - (2.0f*(yy + zz));	m12 = 2.0f*(xy + zw);			m13 = 2.0f * (zx - yw);			m14 = 0.0f;
    m21 = 2.0f * (xy - zw);			m22 = 1.0f - (2.0f*(zz + xx));	m23 = 2.0f * (yz + xw);			m24 = 0.0f;
    m31 = 2.0f * (zx + yw);			m32 = 2.0f * (yz - xw);			m33 = 1.0f - (2.0f*(yy + xx));	m34 = 0.0f;
    m41 = 0.0f;						m42 = 0.0f;						m43 = 0.0f;						m44 = 1.0f;
}

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
KsMatrix4x4& KsMatrix4x4::operator = ( const KsQuaternion& refQuat )
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
const KsMatrix4x4& KsMatrix4x4::set( const KsQuaternion& refQuat )
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
KsReal KsMatrix4x4::determinant() const
{
	#define SUB(a,b) (m[2][a]*m[3][b] - m[3][a]*m[2][b])
	return
			 m[0][0] * (m[1][1]*SUB(2,3) - m[1][2]*SUB(1,3) + m[1][3]*SUB(1,2))
			-m[0][1] * (m[1][0]*SUB(2,3) - m[1][2]*SUB(0,3) + m[1][3]*SUB(0,2))
			+m[0][2] * (m[1][0]*SUB(1,3) - m[1][1]*SUB(0,3) + m[1][3]*SUB(0,1))
			-m[0][3] * (m[1][0]*SUB(1,2) - m[1][1]*SUB(0,2) + m[1][2]*SUB(0,1));
	#undef SUB
#if 0
	KsReal	d;

	d =	m[0][0] * ( m[1][1] * (m[2][2] * m[3][3] - m[3][2] * m[2][3]) -
					m[1][2] * (m[2][1] * m[3][3] - m[3][1] * m[2][3]) +
					m[1][3] * (m[2][1] * m[3][2] - m[3][1] * m[2][2]) )

	  - m[0][1] * ( m[1][0] * (m[2][2] * m[3][3] - m[3][2] * m[2][3]) -
					m[1][2] * (m[2][0] * m[3][3] - m[3][0] * m[2][3]) +
					m[1][3] * (m[2][0] * m[3][2] - m[3][0] * m[2][2]) )

	  + m[0][2] * ( m[1][0] * (m[2][1] * m[3][3] - m[3][1] * m[2][3]) -
					m[1][1] * (m[2][0] * m[3][3] - m[3][0] * m[2][3]) +
					m[1][3] * (m[2][0] * m[3][1] - m[3][0] * m[2][1]) )

	  - m[0][3] *  ( m[1][0] * (m[2][1] * m[3][2] - m[3][1] * m[2][2]) -
					 m[1][1] * (m[2][0] * m[3][2] - m[3][0] * m[2][2]) +
					 m[1][2] * (m[2][0] * m[3][1] - m[3][0] * m[2][1]) );

	return d;
#endif

}


/*************************************************************************************************/
/*
 * ���s����擾����
 * @return						���s��
 */
/*************************************************************************************************/
const KsReal KsMatrix4x4::minor( KsInt32 x, KsInt32 y ) const
{
	KsReal s[3][3];
	for (KsInt32 j=0, v=0; j<4; j++) {
			if (j==y) continue;
			for (KsInt32 i=0, u=0; i<4; i++) {
					if (i!=x) {
							s[v][u++] = m[j][i];
					}
			}
			v++;
	}
	#define SUB(a,b) (s[1][a]*s[2][b] - s[2][a]*s[1][b])
	return s[0][0] * SUB(1,2) - s[0][1] * SUB(0,2) + s[0][2] * SUB(0,1);
	#undef SUB
}

/*************************************************************************************************/
/*
 * �����s����擾����
 * @return						�����s��
 */
/*************************************************************************************************/
const KsMatrix4x4 KsMatrix4x4::adjoint() const
{
	KsMatrix4x4 a;

	for (KsInt32 j=0; j<4; j++)
	{
		for (KsInt32 i=0; i<4; i++)
		{
			a.m[i][j] = (((i+j)&1)?-1.0f:1.0f) * minor(i,j);
		}
	}
	return a;
}

/*************************************************************************************************/
/*
 * �t�s����擾����
 * @return						�t�s��
 */
/*************************************************************************************************/
KsMatrix4x4 KsMatrix4x4::inverse() const
{
	/* �f�^�~�i���g */
	KsReal	d = determinant();

	if( d < ksTOLERANCE2 )
	{
		return KsMatrix4x4::IDENTITY;
	}

	d = 1.0f / d;

	return KsMatrix4x4(   d * (   m[1][1] * (m[2][2] * m[3][3] - m[3][2] * m[2][3]) - 
								m[1][2] * (m[2][1] * m[3][3] - m[3][1] * m[2][3]) +
								m[1][3] * (m[2][1] * m[3][2] - m[3][1] * m[2][2]) ), 

					   -d * (   m[0][1] * (m[2][2] * m[3][3] - m[3][2] * m[2][3]) -
								m[0][2] * (m[2][1] * m[3][3] - m[3][1] * m[2][3]) +
								m[0][3] * (m[2][1] * m[3][2] - m[3][1] * m[2][2]) ),

						d * (   m[0][1] * (m[1][2] * m[3][3] - m[3][2] * m[1][3]) -
								m[0][2] * (m[1][1] * m[3][3] - m[3][1] * m[1][3]) +
								m[0][3] * (m[1][1] * m[3][2] - m[3][1] * m[1][2]) ),

					   -d * (   m[0][1] * (m[1][2] * m[2][3] - m[2][2] * m[1][3]) -
								m[0][2] * (m[1][1] * m[2][3] - m[2][1] * m[1][3]) +
								m[0][3] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) ),

					   -d * (   m[1][0] * (m[2][2] * m[3][3] - m[3][2] * m[2][3]) -
								m[1][2] * (m[2][0] * m[3][3] - m[3][0] * m[2][3]) +
								m[1][3] * (m[2][0] * m[3][2] - m[3][0] * m[2][2]) ), 

						d * (   m[0][0] * (m[2][2] * m[3][3] - m[3][2] * m[2][3]) -
								m[0][2] * (m[2][0] * m[3][3] - m[3][0] * m[2][3]) +
								m[0][3] * (m[2][0] * m[3][2] - m[3][0] * m[2][2]) ),

					   -d * (   m[0][0] * (m[1][2] * m[3][3] - m[3][2] * m[1][3]) -
								m[0][2] * (m[1][0] * m[3][3] - m[3][0] * m[1][3]) +
								m[0][3] * (m[1][0] * m[3][2] - m[3][0] * m[1][2]) ),

						d * (   m[0][0] * (m[1][2] * m[2][3] - m[2][2] * m[1][3]) -
								m[0][2] * (m[1][0] * m[2][3] - m[2][0] * m[1][3]) +
								m[0][3] * (m[1][0] * m[2][2] - m[2][0] * m[1][2]) ),

						d * (   m[1][0] * (m[2][1] * m[3][3] - m[3][1] * m[2][3]) -
								m[1][1] * (m[2][0] * m[3][3] - m[3][0] * m[2][3]) + 
								m[1][3] * (m[2][0] * m[3][1] - m[3][0] * m[2][1]) ), 

					   -d * (   m[0][0] * (m[2][1] * m[3][3] - m[3][1] * m[2][3]) -
								m[0][1] * (m[2][0] * m[3][3] - m[3][0] * m[2][3]) +
								m[0][3] * (m[2][0] * m[3][1] - m[3][0] * m[2][1]) ),

						d * (   m[0][0] * (m[1][1] * m[3][3] - m[3][1] * m[1][3]) -
								m[0][1] * (m[1][0] * m[3][3] - m[3][0] * m[1][3]) +
								m[0][3] * (m[1][0] * m[3][1] - m[3][0] * m[1][1]) ),

					   -d * (   m[0][0] * (m[1][1] * m[2][3] - m[2][1] * m[1][3]) -
								m[0][1] * (m[1][0] * m[2][3] - m[2][0] * m[1][3]) +
								m[0][3] * (m[1][0] * m[2][1] - m[2][0] * m[1][1]) ),

						   -d * (   m[1][0] * (m[2][1] * m[3][2] - m[3][1] * m[2][2]) -
								m[1][1] * (m[2][0] * m[3][2] - m[3][0] * m[2][2]) + 
								m[1][2] * (m[2][0] * m[3][1] - m[3][0] * m[2][1]) ), 

						d * (   m[0][0] * (m[2][1] * m[3][2] - m[3][1] * m[2][2]) -
								m[0][1] * (m[2][0] * m[3][2] - m[3][0] * m[2][2]) +
								m[0][2] * (m[2][0] * m[3][1] - m[3][0] * m[2][1]) ),

					   -d * (   m[0][0] * (m[1][1] * m[3][2] - m[3][1] * m[1][2]) -
								m[0][1] * (m[1][0] * m[3][2] - m[3][0] * m[1][2]) +
								m[0][2] * (m[1][0] * m[3][1] - m[3][0] * m[1][1]) ),

						d * (   m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) -
								m[0][1] * (m[1][0] * m[2][2] - m[2][0] * m[1][2]) +
								m[0][2] * (m[1][0] * m[2][1] - m[2][0] * m[1][1]) ) );

}

/*************************************************************************************************/
/*
 * �N�H�[�^�j�I������Δ����s������
 */
/*************************************************************************************************/
void KsMatrix4x4::partialDifferential( const KsQuaternion &q, const KsQuaternion &dq )
{
	m11 = -4.0f * (q.y * dq.y + q.z * dq.z);
	m12 =  2.0f * (q.x * dq.y + q.y * dq.x + q.w * dq.z + q.z * dq.w);
	m13 =  2.0f * (q.x * dq.z + q.z * dq.x - q.w * dq.y - q.y * dq.w);
	m21 =  2.0f * (q.x * dq.y + q.y * dq.x - q.w * dq.z - q.z * dq.w);
	m22 = -4.0f * (q.x * dq.x + q.z * dq.z);
	m23 =  2.0f * (q.y * dq.z + q.z * dq.y + q.w * dq.x + q.x * dq.w);
	m31 =  2.0f * (q.x * dq.z + q.z * dq.x + q.w * dq.y + q.y * dq.w);
	m32 =  2.0f * (q.y * dq.z + q.z * dq.y - q.w * dq.x - q.x * dq.w);
	m33 = -4.0f * (q.x * dq.x + q.y * dq.y);
	m44 =  0.0f;
}

/*************************************************************************************************/
/*
 * �]�u����
 */
/*************************************************************************************************/
void KsMatrix4x4::transpose()
{
	KsReal	temp;
	
	temp = m[0][1]; m[0][1] = m[1][0]; m[1][0] = temp;
	temp = m[0][2]; m[0][2] = m[2][0]; m[2][0] = temp;
	temp = m[0][3]; m[0][3] = m[3][0]; m[3][0] = temp;
	temp = m[1][2]; m[1][2] = m[2][1]; m[2][1] = temp;
	temp = m[1][3]; m[1][3] = m[3][1]; m[3][1] = temp;
	temp = m[2][3]; m[2][3] = m[3][2]; m[3][2] = temp;
}

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
KsQuaternion KsMatrix4x4::getRotate()
{
	return KsQuaternion( *this );
}

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
KsVector3d KsMatrix4x4::getScale()
{
	return KsVector3d( m[ 0 ][ 0 ], m[ 1 ][ 1 ], m[ 2 ][ 2 ] );
}

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
void KsMatrix4x4::setEulerZYX( KsReal eulerX, KsReal eulerY, KsReal eulerZ )
{ 
	const KsReal ci = KsCos(eulerX); 
	const KsReal cj = KsCos(eulerY); 
	const KsReal ch = KsCos(eulerZ); 
	const KsReal si = KsSin(eulerX); 
	const KsReal sj = KsSin(eulerY); 
	const KsReal sh = KsSin(eulerZ); 
	const KsReal cc = ci * ch; 
	const KsReal cs = ci * sh; 
	const KsReal sc = si * ch; 
	const KsReal ss = si * sh;

	m11 = cj * ch; m12 = sj * sc - cs; m13 = sj * cc + ss;
	m21 = cj * sh; m22 = sj * ss + cc; m23 = sj * cs - sc;
	m31 = -sj;     m32 = cj * si;      m33 = cj * ci;
}

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
KsMatrix4x4	KsMatrix4x4::CreateScale( const KsVector3d& refScale )
{
	KsMatrix4x4		retMatrix;

	retMatrix.setScale( refScale );

	return retMatrix;
}

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
KsMatrix4x4	KsMatrix4x4::CreateFromQuaternion( const KsQuaternion& refQuat )
{
	return KsMatrix4x4( refQuat );
}

/*************************************************************************************************/
/*
 *
 */
/*************************************************************************************************/
KsMatrix4x4	KsMatrix4x4::CreateTranslation( const KsVector3d& refTranslate )
{
	KsMatrix4x4		retMatrix;

	retMatrix.setTranslate( refTranslate );

	return retMatrix;
}

/*************************************************************************************************/
/*
 * �N�H�[�^�j�I������Δ����s������
 * @return						�Δ����s��
 */
/*************************************************************************************************/
KsMatrix4x4 KsMatrix4x4::CreatePartialDifferential( const KsQuaternion &q, const KsQuaternion &dq )
{
	KsMatrix4x4	m;

	m.partialDifferential( q, dq );

	return m;
}

/*************************************************************************************************/
/*
 * �����ˉe�s��𐶐�����(�E��n)
 * @param		projMatrix		�v���W�F�N�V�����}�g���b�N�X�ۑ��p
 * @param		fovy			����p
 * @param		aspect			�A�X�y�N�g��
 * @param		zNear			�ߋ����l
 * @param		zFar			�������l
 */
/*************************************************************************************************/
const KsMatrix4x4& KsMatrix4x4::PerspectiveRH( KsReal fovy, KsReal aspect, KsReal zNear, KsReal zFar )
{
	KsMatrix4x4	projMatrix;

	KsReal		th = fovy/2.0f;
	KsReal		f  = KsCos( th ) / KsSin( th );

	projMatrix.m11 =  f/aspect;
	projMatrix.m21 =  0.0f;
	projMatrix.m31 =  0.0f;
	projMatrix.m41 =  0.0f;

	projMatrix.m12 =  0.0f;
	projMatrix.m22 =  f;
	projMatrix.m32 =  0.0f;
	projMatrix.m42 =  0.0f;

	projMatrix.m13 =  0.0f;
	projMatrix.m23 =  0.0f;
	projMatrix.m33 =  zFar/( zNear - zFar );
	projMatrix.m43 =  zNear*zFar/( zNear - zFar );

	projMatrix.m14 =   0.0f;
	projMatrix.m24 =   0.0f;
	projMatrix.m34 =  -1.0f;
	projMatrix.m44 =   0.0f;

	return projMatrix;
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
void KsMatrixPerspectiveRH( KsMatrix4x4& projMatrix, KsReal fovy, KsReal aspect, KsReal zNear, KsReal zFar )
{
#if 0
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
#endif
	KsReal		th = fovy/2.0f;
	KsReal		f  = KsCos( th ) / KsSin( th );

	projMatrix.m11 =  f/aspect;
	projMatrix.m21 =  0.0f;
	projMatrix.m31 =  0.0f;
	projMatrix.m41 =  0.0f;

	projMatrix.m12 =  0.0f;
	projMatrix.m22 =  f;
	projMatrix.m32 =  0.0f;
	projMatrix.m42 =  0.0f;

	projMatrix.m13 =  0.0f;
	projMatrix.m23 =  0.0f;
	projMatrix.m33 =  zFar/( zNear - zFar );
	projMatrix.m43 =  zNear*zFar/( zNear - zFar );

	projMatrix.m14 =   0.0f;
	projMatrix.m24 =   0.0f;
	projMatrix.m34 =  -1.0f;
	projMatrix.m44 =   0.0f;
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
void KsMatrixOrthoRH( KsMatrix4x4& projMatrix, KsReal left, KsReal right, KsReal bottom, KsReal top, KsReal zNear, KsReal zFar )
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
void KsMatrixLookAtRH( KsMatrix4x4& viewMatrix, const KsVector3d& eye, const KsVector3d& at, const KsVector3d& up )
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

 xScale     0          0               0
0        yScale       0               0
0          0       zf/(zf-zn)         1
0          0       -zn*zf/(zf-zn)     0
where:
yScale = cot(fovY/2)

xScale = aspect ratio * yScale


 */
/************************************************************************************************/
void KsMatrixPerspectiveLH( KsMatrix4x4& projMatrix, KsReal fovy, KsReal aspect, KsReal zNear, KsReal zFar )
{
	KsReal		th = fovy/2.0f;
	KsReal		f  = KsCos( th ) / KsSin( th );

	projMatrix.m11 =  f/aspect;
	projMatrix.m21 =  0.0f;
	projMatrix.m31 =  0.0f;
	projMatrix.m41 =  0.0f;

	projMatrix.m12 =  0.0f;
	projMatrix.m22 =  f;
	projMatrix.m32 =  0.0f;
	projMatrix.m42 =  0.0f;

	projMatrix.m13 =  0.0f;
	projMatrix.m23 =  0.0f;
	projMatrix.m33 =  zFar/( zFar - zNear );
	projMatrix.m43 =  -zNear*zFar/( zFar - zNear );

	projMatrix.m14 =  0.0f;
	projMatrix.m24 =  0.0f;
	projMatrix.m34 =  1.0f;
	projMatrix.m44 =  0.0f;

#if 0
	projMatrix.m11 =  f/aspect;
	projMatrix.m21 =  0.0f;
	projMatrix.m31 =  0.0f;
	projMatrix.m41 =  0.0f;

	projMatrix.m12 =  0.0f;
	projMatrix.m22 =  f;
	projMatrix.m32 =  0.0f;
	projMatrix.m42 =  0.0f;

	projMatrix.m13 =  0.0f;
	projMatrix.m23 =  0.0f;
	projMatrix.m33 =  ( zFar + zNear )/( zNear - zFar );
	projMatrix.m43 =  2.0f*zFar*zNear/( zNear - zFar );

	projMatrix.m14 =  0.0f;
	projMatrix.m24 =  0.0f;
	projMatrix.m34 =  1.0f;
	projMatrix.m44 =  0.0f;
#endif

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
void KsMatrixOrthoLH( KsMatrix4x4& projMatrix, KsReal left, KsReal right, KsReal bottom, KsReal top, KsReal zNear, KsReal zFar )
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
void KsMatrixLookAtLH( KsMatrix4x4& viewMatrix, const KsVector3d& eye, const KsVector3d& at, const KsVector3d& up )
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
void KsMatrixShadow( KsMatrix4x4& shadowMatrix, const KsVector3d& light, const KsPlane& refPlane, KsReal point )
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


