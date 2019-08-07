/************************************************************************************************/
/** 
 * @file		KsSwfDefineShape2.h
 * @brief		SWFコマンド
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSWFDEFINESHAPE2_H__
#define __KSSWFDEFINESHAPE2_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsSwfDefineShape2
 * @brief		SWFコマンド
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 * @note		なし
 */
/************************************************************************************************/
class ksSWF_API KsSwfDefineShape2 : public KsSwfCommand
{
	public:
		/**
		 * コンストラクタ
		 */
							KsSwfDefineShape2( KsFileObject* pFile );

		/**
		 * デストラクタ
		 */
		virtual				~KsSwfDefineShape2();

		/**
		 * コマンド実行
		 */
		virtual void		execute();
};

#endif	/* __KSSWFDEFINESHAPE2_H__ */


