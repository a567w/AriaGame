/************************************************************************************************/
/** 
 * @file		KsCharacterPad.h
 * @brief		KsCharacterPadファイル
 * @author		Tsukasa Kato
 * @date		2010/12/17
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSCHARACTERPAD_H__
#define __KSCHARACTERPAD_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                          */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsCharacterPad
 * @brief		キャラクタークラス
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsCharacterPad : public KsUpdate
{
	public:
		/**
		 * コンストラクタ
		 */
									KsCharacterPad();

		/**
		 * デストラクタ
		 */
		virtual						~KsCharacterPad();

		/**
		 * 更新処理
		 * @param		pParam		パラメータ
		 */
		virtual void*				update( void* pParam );
};

#endif /* __KSCHARACTERPAD_H__ */
