/************************************************************************************************/
/** 
 * @file		KsQuaternion.h
 * @brief		クォータニオン操作
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSQUATERNION_H__
#define __KSQUATERNION_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

class KsMatrix4x4;
class KsVector3d;

/************************************************************************************************/
/**
 *	クォータニオン
 *	@class	Quaternion
 *	@brief	
 *	@autor	Tsukasa Kato
 */
/************************************************************************************************/
class ksENGINE_API KsQuaternion
{
	public:
		/**
		 * マトリックスの要素成分
		 */
		KsReal							x, y, z, w;

		/**
		 * コンストラクタ				 単位行列で初期化されます
		 */
										KsQuaternion() : x( 0.0f ), y( 0.0f ), z( 0.0f ), w( 1.0f ) {}

		/**
		 * コンストラクタ
		 * @param	farray				初期化する値, この配列の順に 要素を初期化します
		 */
										KsQuaternion( const KsReal* fArray ) : x( fArray[0] ), y( fArray[1] ), z( fArray[2] ), w( fArray[3] ) {}

		/**
		 * コンストラクタ
		 * @param	farray				初期化する値, この配列の順に 要素を初期化します
		 */
										KsQuaternion( KsReal qx, KsReal qy, KsReal qz, KsReal qw ) : x( qx ), y( qy ), z( qz ), w( qw ) {}

										KsQuaternion( const KsMatrix3x3& refMatrix );

										KsQuaternion( const KsMatrix4x4& refMatrix );
		/**
		 * KsRealのポインタに変換してで取得できるようにする
		 */
										operator KsReal* () { return &x; }

		/**
		 * KsRealのポインタに変換してで取得できるようにする
		 */
										operator const KsReal* () const { return &x; }

		/**
		 *
		 */
		KsQuaternion&					operator = ( const KsQuaternion& refQuat );
		KsQuaternion&					operator = ( const KsMatrix4x4& refMatrix );

		KsQuaternion&					operator += ( const KsQuaternion& refQuat );
		KsQuaternion&					operator -= ( const KsQuaternion& refQuat );
		KsQuaternion&					operator *= ( const KsQuaternion& refQuat );
		KsQuaternion&					operator *= ( KsReal s );
		KsQuaternion&					operator /= ( KsReal s );
	
		KsQuaternion					operator ~ () const;
		KsQuaternion					operator + () const;
		KsQuaternion					operator - () const;
	
		KsQuaternion					operator + ( const KsQuaternion& refQuat ) const;
		KsQuaternion					operator - ( const KsQuaternion& refQuat ) const;
		KsQuaternion					operator * ( const KsQuaternion& refQuat ) const;
		KsQuaternion					operator * ( KsReal s ) const;
		KsQuaternion					operator / ( KsReal s ) const;

		KsBool							operator == ( const KsQuaternion& refQuat ) const;
		KsBool							operator != ( const KsQuaternion& refQuat ) const;


		friend KsQuaternion				operator * ( KsReal s, const KsQuaternion& v ) { return v * s; }

		//逆行列
	

		KsReal							length() const;

		KsReal							length2() const;

		//Dot

		/**
		 * 正規化する
		 */
		void							normalize();

		/**
		 * 逆クォータニオン
		 */
		void							inverse();

		KsMatrix4x4						convertToMatrix();

		void							convertToMatrix( KsMatrix4x4* pMatrix );

		void							fromAxisRotation( const KsVector3d& refAxis, KsReal angle );
		void							fromEulerAngles( KsReal angleX, KsReal angleY, KsReal angleZ );
		void							convertToAxisRotation( KsVector3d* pAxis, KsReal* pAngle );
		KsVector3d						convertToEuler();

		//void							slerp( const KsQuaternion* pDest, KsReal t );

		static const KsQuaternion		IDENTITY;
		
		static KsQuaternion				CreateFromYawPitchRoll( KsReal yaw, KsReal pitch, KsReal roll );
		static KsQuaternion				CreateFromAxisAngle( const KsVector3d& refAxis, KsReal angle );
		static KsQuaternion				CreateFromRotationMatrix( const KsMatrix4x4& refMatrix );
		static KsQuaternion				CreateFromRotationMatrix( const KsMatrix3x3& refMatrix );
		static KsQuaternion				Slerp( const KsQuaternion& refSrc, const KsQuaternion& refDest, KsReal t );
		static KsQuaternion				Lerp( const KsQuaternion& refSrc, const KsQuaternion& refDest, KsReal t );
		static KsQuaternion				Multiply( const KsQuaternion& refA, const KsQuaternion& refB );
};

extern void KsQuaternionSlerp( KsQuaternion* pOut, const KsQuaternion* pSrc, const KsQuaternion* pDest, KsReal t );
extern void KsQuaternionLerp( KsQuaternion* pOut, const KsQuaternion* pSrc, const KsQuaternion* pDest, KsReal t );

/*************************************************************************************************/
/**
 * あるベクトルからあるベクトルへのクォータニオンを求める（最小弧クォータニオン）
 * @param		pQuat		クォータニオン
 * @param		pV0			変換前の行列
 * @param		pV1			変換後の行列
 * @note		フォーミングなどの外積が０に近いときおかしくなるための対処
 */
/*************************************************************************************************/
extern void KsRotationArc( KsQuaternion& quat, const KsVector3d& refV0, const KsVector3d refV1 );

/*************************************************************************************************/
/*---------------------------<< インライン部分ヘッダーファイル >>--------------------------------*/
								#include "KsEngine/math/KsQuaternion.inl"
/*-----------------------------------------------------------------------------------------------*/
/*************************************************************************************************/


#endif /* __KSQUATERNION_H__ */

