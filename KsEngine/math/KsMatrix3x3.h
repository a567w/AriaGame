/************************************************************************************************/
/** 
 * @file		KsMatrix3x3.h
 * @brief		マトリックス操作
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMATRIX3X3_H__
#define __KSMATRIX3X3_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsEngine/math/KsVector.h"
#include "KsEngine/math/KsPlane.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsVector3d;
class KsQuaternion;

/*************************************************************************************************/
/**
 * @class	KsMatrix3x3
 * @brief	マトリックス操作クラス
 * @author	Tsukasa Kato
 * @date	----/--/--
 * @since	----/--/--
 */
/*************************************************************************************************/
class ksENGINE_API KsMatrix3x3
{
	public:
		/**
		 * マトリックスの要素成分
		 */
		union
		{
			struct
			{
				KsReal	m11, m12, m13;
				KsReal	m21, m22, m23;
				KsReal	m31, m32, m33;
			};
			KsReal		m[ 3 ][ 3 ];
			KsReal		data[ 9 ];
		};

		/**
		 * コンストラクタ				単位行列で初期化されます
		 */
										KsMatrix3x3() :  m11(1.0f), m12(0.0f), m13(0.0f),
														 m21(0.0f), m22(1.0f), m23(0.0f),
														 m31(0.0f), m32(0.0f), m33(1.0f){}
		/**
		 * コンストラクタ
		 * @param	farray				初期化する値, この配列の順に 要素を初期化します
		 */
										KsMatrix3x3( const KsReal* fArray )
												:  m11( fArray[ 0] ), m12( fArray[ 1] ), m13( fArray[ 2] ),
												   m21( fArray[ 3] ), m22( fArray[ 4] ), m23( fArray[ 5] ),
												   m31( fArray[ 6] ), m32( fArray[ 7] ), m33( fArray[ 8] ) {}

		/**
		 * コンストラクタ(copy)
		 * @param	refMatrix			引数の値をコピーして初期化します
		 */
										KsMatrix3x3( const KsMatrix3x3& refMatrix )
												:  m11( refMatrix.m11 ), m12( refMatrix.m12 ), m13( refMatrix.m13 ),
												   m21( refMatrix.m21 ), m22( refMatrix.m22 ), m23( refMatrix.m23 ),
												   m31( refMatrix.m31 ), m32( refMatrix.m32 ), m33( refMatrix.m33 ){}


		/**
		 * コンストラクタ				それぞれの引数で要素を初期化します
		 */								
										KsMatrix3x3( KsReal me11, KsReal me12, KsReal me13,
												     KsReal me21, KsReal me22, KsReal me23,
												     KsReal me31, KsReal me32, KsReal me33 )
												   : m11( me11 ), m12( me12 ), m13( me13 ),
												     m21( me21 ), m22( me22 ), m23( me23 ),
												     m31( me31 ), m32( me32 ), m33( me33 ) {}

		/**
		 * コンストラクタ				 
		 */
										KsMatrix3x3( const KsQuaternion& refQuat );

		/**
		 * KsRealのポインタに変換してで取得できるようにする
		 */
										operator KsReal* () { return &m[ 0 ][ 0 ]; }
	
		/**
		 * KsRealのポインタに変換してで取得できるようにする
		 */
										operator const KsReal* () const { return &m[ 0 ][ 0 ]; }
	
		/**
		 * KsRealのポインタに変換してで取得できるようにする
		 */
		KsReal*							operator [] ( KsInt32 index ) { return &m[ index ][ 0 ]; }

		/**
		 * KsRealのポインタに変換してで取得できるようにする
		 */
		const KsReal*					operator [] ( KsInt32 index ) const { return &m[ index ][ 0 ]; }

		KsMatrix3x3&					operator = ( const KsMatrix3x3& refMatrix );
		KsMatrix3x3&					operator = ( const KsQuaternion& refMatrix );

		KsMatrix3x3&					operator *= ( const KsMatrix3x3& refMatrix );
		KsMatrix3x3&					operator += ( const KsMatrix3x3& refMatrix );
		KsMatrix3x3&					operator -= ( const KsMatrix3x3& refMatrix );
		KsMatrix3x3&					operator *= ( KsReal s );
		KsMatrix3x3&					operator /= ( KsReal s );

		//KsMatrix3x3					operator ~ () const;
		KsMatrix3x3						operator + () const;
		KsMatrix3x3						operator - () const;

		KsVector3d						operator * ( const KsVector3d&  refVector ) const;
		KsMatrix3x3						operator * ( const KsMatrix3x3& refMatrix ) const;
		KsMatrix3x3						operator + ( const KsMatrix3x3& refMatrix ) const;
		KsMatrix3x3						operator - ( const KsMatrix3x3& refMatrix ) const;

		KsMatrix3x3						operator * ( KsReal s ) const;
		KsMatrix3x3						operator / ( KsReal s ) const;

		KsBool							operator == ( const KsMatrix3x3& refMatrix ) const;
		KsBool							operator != ( const KsMatrix3x3& refMatrix ) const;

		friend KsMatrix3x3				operator * ( KsReal s, const KsMatrix3x3& refMatrix );
	
		/**
		 * 値をセットする
		 * @param	farray				初期化する値, この配列の順に 要素を初期化します
		 * @return						値がセットされたマトリックス
		 */
		const KsMatrix3x3&				set( const KsReal* fArray );

		/**
		 * クォータニオンから変換して値をセットする
		 * @param	refQuat				クォータニオン
		 * @return						値がセットされたマトリックス
		 */
		const KsMatrix3x3&				set( const KsQuaternion& refQuat );

		/**
		 * デタミナントを取得する
		 * @return						デタミナント
		 */
		KsReal							determinant() const;

		/**
		 * 逆行列を取得する
		 * A^-1 = 1/|A| * ~A (逆行列の公式を使う)
		 * デタミナントは余因子展開(|A| = Σ(-1)^(i+j) * a_ij*|A_ij| )
		 * @return						逆行列
		 */
		KsMatrix3x3						inverse();

		/**
		 * 転置する
		 */
		void							transpose();


		void							setScaleX( KsReal sx );
		void							setScaleY( KsReal sy );
		void							setScaleZ( KsReal sz );
		void							setScale( KsReal scale );
		void							setScale( KsReal sx, KsReal sy, KsReal sz );
		void							setScale( const KsVector3d& refScale );
		void							setScale( const KsVector3d* pScale );
		void							setRotateX( KsReal angle );
		void							setRotateY( KsReal angle );
		void							setRotateZ( KsReal angle );

		void							setEulerZYX( KsReal eulerX, KsReal eulerY, KsReal eulerZ );

		KsQuaternion					getRotate() const;
		KsVector3d						getScale() const;

		//逆行列
	
		/**
		 * 単位行列
		 */
		static const KsMatrix3x3		IDENTITY;
};

/*************************************************************************************************/
/*---------------------------<< インライン部分ヘッダーファイル >>----------------------------------*/
						#include "KsEngine/math/KsMatrix3x3.inl"
/*-----------------------------------------------------------------------------------------------*/
/*************************************************************************************************/

#endif /* __KSMATRIX3X3_H__ */


