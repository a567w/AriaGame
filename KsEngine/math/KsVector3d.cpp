/************************************************************************************************/
/** 
 * @file		KsVector3d.cpp
 * @brief		2Dベクトル操作
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"
#include "KsVector3d.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


const KsVector3d KsVector3d::ZERO( 0.0f, 0.0f, 0.0f );
const KsVector3d KsVector3d::ONE(  1.0f, 1.0f, 1.0f );
const KsVector3d KsVector3d::UP(   0.0f, 1.0f, 0.0f );

const KsVector3d KsVector3d::V100(   1.0f, 0.0f, 0.0f );
const KsVector3d KsVector3d::V010(   0.0f, 1.0f, 0.0f );
const KsVector3d KsVector3d::V001(   0.0f, 0.0f, 1.0f );


KsReal KsVector3d::Dot( const KsVector3d& a, const KsVector3d& b )
{
	return ( a.x*b.x + a.y*b.y + a.z*b.z );
}

KsVector3d KsVector3d::Cross( const KsVector3d& a, const KsVector3d& b )
{
	return KsVector3d( (a.y*b.z - a.z*b.y), (a.z*b.x - a.x*b.z), (a.x*b.y - a.y*b.x) );
}


KsVector3d KsVector3d::Lerp( const KsVector3d& a, const KsVector3d& b, KsReal t )
{
	return ( a + ( b - a ) * t );
}

KsVector3d KsVector3d::Transform( const KsVector3d* pV, const KsQuaternion* pQuat )
{
	KsQuaternion	quat =  *pQuat;
	KsMatrix4x4		mat  = quat.convertToMatrix();

	return KsVector3d(	(pV->x * mat.m11) + (pV->y * mat.m21) + (pV->z * mat.m31) + mat.m41,
						(pV->x * mat.m12) + (pV->y * mat.m22) + (pV->z * mat.m32) + mat.m42,
						(pV->x * mat.m13) + (pV->y * mat.m23) + (pV->z * mat.m33) + mat.m43 );

}


KsVector3d KsVector3d::Transform( const KsVector3d* pV, const KsMatrix4x4* pMatrix )
{
	return KsVector3d(	(pV->x * pMatrix->m11) + (pV->y * pMatrix->m21) + (pV->z * pMatrix->m31) + pMatrix->m41,
						(pV->x * pMatrix->m12) + (pV->y * pMatrix->m22) + (pV->z * pMatrix->m32) + pMatrix->m42,
						(pV->x * pMatrix->m13) + (pV->y * pMatrix->m23) + (pV->z * pMatrix->m33) + pMatrix->m43 );

}

KsVector3d KsVector3d::TransformNormal( const KsVector3d* pV, const KsMatrix4x4* pMatrix )
{
	return KsVector3d(	(pV->x * pMatrix->m11) + (pV->y * pMatrix->m21) + (pV->z * pMatrix->m31),
						(pV->x * pMatrix->m12) + (pV->y * pMatrix->m22) + (pV->z * pMatrix->m32),
						(pV->x * pMatrix->m13) + (pV->y * pMatrix->m23) + (pV->z * pMatrix->m33) );

}

void KsVector3d::TransformArray( KsVector3d* pOut, KsUInt32 OutStride, const KsVector3d* pV, KsUInt32 VStride, const KsMatrix4x4* pM, KsUInt32 n )
{
	KsUInt8* pOutput;
	const KsUInt8 * pVector;
	pOutput = (KsUInt8*)pOut;
	pVector = (KsUInt8*)pV;

	for( KsUInt32 i = 0; i < n; i++ )
	{
		*pOut = KsVector3d::Transform( pV, pM );

		pVector+=VStride;
		pOutput+=OutStride;

		pOut = (KsVector3d*)pOutput;
		pV   = (KsVector3d*)pVector;
	}
}


