/************************************************************************************************/
/** 
 * @file		KsVector3d.h
 * @brief		3Dベクトル操作
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSVECTOR3D_H__
#define __KSVECTOR3D_H__

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
class KsQuaternion;

/*************************************************************************************************/
/**
 * @class	KsVector3d
 * @brief	3Dベクトル操作クラス
 * @author	tsukasa katou
 */
/*************************************************************************************************/
class ksENGINE_API KsVector3d
{
	public:
		/**
		 * ベクトルの x, y, z 成分
		 */
		KsReal							x, y, z;

		/**
		 * コンストラクタ				ゼロで初期化されます
		 */
										KsVector3d() : x( 0.0f ), y( 0.0f ), z( 0.0f ) {}

		/**
		 * コンストラクタ
		 * @param	val					初期化する値, この値でx, y, z を初期化します
		 */
										KsVector3d( KsReal val ) : x( val ), y( val ), z( val ) {}

		/**
		 * コンストラクタ
		 * @param	farray				初期化する値, この配列の順に x, y, z を初期化します
		 */
										KsVector3d( const KsReal* fArray ) : x( fArray[ 0 ] ), y( fArray[ 1 ] ), z( fArray[ 2 ] ) {}
	
		/**
		 * コンストラクタ(copy)
		 * @param	refVector			引数の値をコピーして初期化します
		 */
										KsVector3d( const KsVector3d& refVector ) : x( refVector.x ), y( refVector.y ), z( refVector.z ) {}
		/**
		 * コンストラクタ
		 * @param	xf					初期化するxの値
		 * @param	yf					初期化するyの値
		 * @param	zf					初期化するzの値
		 */
										KsVector3d( KsReal xf, KsReal yf, KsReal zf ) : x( xf ), y( yf ), z( zf ) {}

		/**
		 * KsRealのポインタに変換してで取得できるようにする
		 */
										operator KsReal* () { return &x; }

		/**
		 * KsRealのポインタに変換してで取得できるようにする
		 */
										operator const KsReal* () const { return &x; }

		/**
		 * 配列内の値を返す
		 * @param	num					返す配列のナンバー
		 * @return						配列内の先頭の参照
		 */
		KsReal&							operator[]( KsInt32 index );

		/**
		 * 配列内の値を返す
		 * @param	num					返す配列のナンバー
		 * @return						配列内の先頭の参照
		 */
		const KsReal&					operator[]( KsInt32 index ) const;

		/**
		 * ベクトルの( = )演算子
		 * @param	rkVector			値をコピーするベクトル
		 * @return						自分自身のベクトル参照( *this )
		 */
		const KsVector3d&				operator = ( const KsVector3d& rkVector );
							
		/**
		 * ベクトルの( += )演算子
		 * @param	rkVector			値を足すベクトル
		 * @return						自分自身のベクトル参照( *this )
		 */
		KsVector3d&						operator += ( const KsVector3d& refVector );

		/**
		 * ベクトルの( += )演算子
		 * @param	rkVector			値を足すベクトル
		 * @return						自分自身のベクトル参照( *this )
		 */
		KsVector3d&						operator -= ( const KsVector3d& refVector );

		/**
		 * ベクトルの( *= )演算子
		 * @param	s					ベクトルに掛ける値
		 * @return						自分自身のベクトル参照( *this )
		 */
		KsVector3d&						operator *= ( KsReal s );

		/**
		 * ベクトルの( /= )演算子
		 * @param	s					ベクトルを割る値
		 * @return						自分自身のベクトル参照( *this )
		 */
		KsVector3d&						operator /= ( KsReal s );

		/**
		 * ベクトルの( + )演算子
		 * @return						+ 演算子のベクトル
		 */
		KsVector3d						operator + () const;

		/**
		 * ベクトルの( - )演算子
		 * @return						- 演算子のベクトル
		 */
		KsVector3d						operator - () const;

		/**
		 * ベクトルの( + )演算子
		 * @param	refVector			計算するベクトル
		 * @return						結果のベクトル
		 */
		KsVector3d						operator + ( const KsVector3d& refVector ) const;

		/**
		 * ベクトルの( - )演算子
		 * @param	refVector			計算するベクトル
		 */
		KsVector3d						operator - ( const KsVector3d& refVector ) const;
	
		/**
		 * ベクトルの( * )演算子
		 * @param						掛ける値
		 * @return						結果のベクトル
		 */
		KsVector3d						operator * ( KsReal s ) const;
	
		/**
		 * ベクトルの( / )演算子
		 * @param	s					割る値
		 * @return						結果のベクトル
		 */
		KsVector3d						operator / ( KsReal s ) const;

		/**
		 * ベクトルが等しいかを判定する
		 * @param	refVector			判定するベクトル
		 * @retval	ksTRUE				等しい
		 * @retval	ksFALSE				等しくない
		 */
		KsBool							operator == ( const KsVector3d& refVector ) const;
	
		/**
		 * ベクトルが等しくないかを判定する
		 * @param	refVector			判定するベクトル
		 * @retval	ksTRUE				等しくない
		 * @retval	ksFALSE				等しい
		 */
		KsBool							operator != ( const KsVector3d& refVector ) const;

		/**
		 * 各成分をセットする
		 * @param	xf					x成分
		 * @param	yf					y成分
		 * @param	zf					z成分
		 */
		void							set( KsReal xf, KsReal yf, KsReal zf );
	
		/**
		 * 各成分をセットする
		 * @param	fArray				成分の先頭のポインタ
		 */
		void							set( const KsReal* fArray );
	
		/**
		 * 指定した長さのベクトルに変更する
		 * @param	len					変更する長さ
		 */
		void							scaleTo( KsReal len );
	
		/**
		 * ０でリセットする
		 */
		void							reset();
	
		/**
		 * ベクトルの長さを取得する
		 */
		KsReal							length();
	
		/**
		 * ベクトルの長さの２乗を取得する
		 */
		KsReal							length2();
	
		/**
		 * 正規化する
		 */
		void							normalize();
	
		/**
		 * 内積
		 * @param	refVector			内積するベクトル
		 * @return						内積結果のスカラー値
		 */
		KsReal							dotProduct( const KsVector3d& refVector ) const;

		/**
		 * 外積
		 * @param	refVector			外積するベクトル
		 * @return						外積結果のベクトル
		 */
		KsVector3d						crossProduct( const KsVector3d& refVector );

		/**
		 * ゼロベクトル
		 */
		static const KsVector3d			ZERO;

		/**
		 * 1.0fで初期化されたベクトル
		 */
		static const KsVector3d			ONE;

		/**
		 * (0,1,0)で初期化されたベクトル
		 */
		static const KsVector3d			UP;

		/**
		 * (1,0,0)で初期化されたベクトル
		 */
		static const KsVector3d			V100;

		/**
		 * (0,1,0)で初期化されたベクトル
		 */
		static const KsVector3d			V010;

		/**
		 * (0,0,1)で初期化されたベクトル
		 */
		static const KsVector3d			V001;

		static KsReal					Dot( const KsVector3d& a, const KsVector3d& b );
		static KsVector3d				Cross( const KsVector3d& a, const KsVector3d& b );
		static KsVector3d				Lerp( const KsVector3d& a, const KsVector3d& b, KsReal t );
		static KsVector3d				Transform( const KsVector3d* pV, const KsQuaternion* pQuat );
		static KsVector3d				Transform( const KsVector3d* pV, const KsMatrix4x4* pMatrix );
		static KsVector3d				TransformNormal( const KsVector3d* pV, const KsMatrix4x4* pMatrix );
		static void						TransformArray( KsVector3d* pOut, KsUInt32 OutStride, const KsVector3d* pV, KsUInt32 VStride, const KsMatrix4x4* pM, KsUInt32 n );

};

/************************************************************************************************/
/*---------------------------<< インライン部分ヘッダーファイル >>---------------------------------*/
								#include "KsEngine/math/KsVector3d.inl"
/*----------------------------------------------------------------------------------------------*/
/************************************************************************************************/


#endif /* __KSVECTOR3D_H__ */

