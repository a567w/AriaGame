/************************************************************************************************/
/** 
 * @file		KsCommandList.h
 * @brief		コマンドリスト
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSCOMMANDLIST_H__
#define __KSCOMMANDLIST_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsCommandList
 * @brief		描画コンテキスト
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsCommandList
{
	public:
		/**
		 *  コンストラクタ
		 */
									KsCommandList(){}

		/**
		 * デストラクタ
		 */
		virtual						~KsCommandList(){}

		/**
		 * コマンドリストを取得する
		 */
		virtual void*				getCommandList () = 0;

		/**
		 * コマンドリストBufferを取得する
		 */
		virtual void**				getCommandListBuffer() = 0;

		/**
		 * クリアーする
		 */
		virtual void				clear() = 0;
};

#endif		/* __KSCOMMANDLIST_H__ */



