/************************************************************************************************/
/** 
 * @file		KsVariable.h
 * @brief		変数クラス
 * @author		Tsukasa Kato
 * @date		2006/10/17
 * @since		2006/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSVARIABLE_H__
#define __KSVARIABLE_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsTypeScript.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * スクリプト用の変数
 * @class	KsVariable
 * @author	Tsukasa Kato
 * @since   2006/--/--
 * @version 2006/--/--
 */
/************************************************************************************************/
class ksSCRIPT_API KsVariable
{
	public:
		ksVALUE_TYPE				m_type;			/**< 値のタイプ		*/
		KsValue						m_value;		/**< 値				*/

	public:
		/**
		 * コンストラクタ
		 */
									KsVariable();

		/**
		 * コンストラクタ
		 * @param	value_int		整数値
		 */
									KsVariable( KsInt32 value_int );

		/**
		 * コンストラクタ
		 * @param	value_float		実数値
		 */
									KsVariable( KsReal value_float );

		/**
		 * タイプを取得する
		 */
		ksVALUE_TYPE				getType() const;

		/**
		 * 整数値をセットする
		 * @param	value_int		整数値
		 */
		void						setInt( KsInt32 value_int );

		/**
		 * 実数値をセットする
		 * @param	value_float		実数値
		 */
		void						setFloat( KsReal value_float );

		/**
		 * ハンドルをセットする
		 * @param	value_handle	実数値
		 */
		void						setHandle( KsHandle value_handle );

		/**
		 * 実数値を取得する
		 * @return					実数値
		 */
		KsReal						getFloat() const;

		/**
		 * 整数値を取得する
		 * @return					実数値
		 */
		KsInt32					getInt() const;

		/**
		 * ハンドルを取得する
		 * @return					ハンドル
		 */
		KsHandle					getHandle() const;

		/**
		 * 変数値を取得する
		 * @return					変数値
		 */
		KsValue						getValue() const;

		/**
		 * =演算子オーバーロード（値の代入）
		 * @param	value			変数値の参照
		 * @return					自分自身の参照
		 */
		KsVariable&					operator=( const KsVariable& value );
};

#endif		/* __KSVARIABLE_H__ */

