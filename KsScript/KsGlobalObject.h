/************************************************************************************************/
/** 
 * @file		KsGlobalObject.h
 * @brief		ハンドルオブジェクト
 * @author		Tsukasa Kato
 * @date		2006/10/17
 * @since		2006/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSGLOBALOBJECT_H__
#define __KSGLOBALOBJECT_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsStringObject.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * 文字列などの変数オブジェクト用
 * @class	KsGlobalObject
 * @author	Tsukasa Kato
 * @since   2006/--/--
 * @version 2006/--/--
 */
/************************************************************************************************/
class KsGlobalObject : public KsStringObject
{
		friend class KsHandleManager;
		friend class KsVirtualMachine;
	public:
		/**
		 * コンストラクタ
		 */
									KsGlobalObject(){}

		/**
		 * コンストラクタ
		 * @param	pString			文字列
		 */
									KsGlobalObject( const KsChar* pString ) : KsStringObject( pString ) {}

		/**
		 * デストラクタ
		 */
		virtual					~KsGlobalObject(){}

		/**
		 * 値のタイプ
		 * @return					値のタイプ(文字列)
		 */
		virtual ksVALUE_TYPE		getType() const { return m_variable.getType(); }

		/**
		 * 整数の変数をセットする
		 * @param	value			整数値
		 */
		void						setVarInt( KsInt32 value ){ m_variable.setInt( value ); }

		/**
		 * 浮動少数値をセットする
		 * @param	value			浮動少数値
		 */
		void						setVarFloat( KsReal value ){ m_variable.setFloat( value ); }

		/**
		 * ハンドルをセットする
		 * @param	value			ハンドル値
		 */
		void						setVarHandle( KsHandle value ){ m_variable.setHandle( value ); }

		/**
		 * 変数をセットする
		 * @param	value			変数
		 */
		void						setVariable( const KsVariable& variable ){ m_variable = variable; }

		/**
		 * 整数値を取得する
		 * @return					整数値
		 */
		KsInt32					getVarInt() const { return m_variable.getInt(); }

		/**
		 * 浮動少数値を取得する
		 * @return					整数値
		 */
		KsReal						getVarFloat() const { return m_variable.getFloat(); }

		/**
		 * ハンドル値を取得する
		 * @return					整数値
		 */
		KsHandle					getVarHandle() const { return m_variable.getHandle(); }

		/**
		 * 変数値を取得する
		 * @return					整数値
		 */
		const KsVariable*			getVariable() { return &m_variable; }

	protected:
		KsVariable					m_variable;		/**< 変数値構造	*/
};


#endif /* __KSGLOBALOBJECT_H__ */

