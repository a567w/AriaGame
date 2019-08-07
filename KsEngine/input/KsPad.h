/************************************************************************************************/
/** 
 * @file		KsPAD.h
 * @brief		ジョイパッド
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSPAD_H__
#define __KSPAD_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
#define ksDEFAULT_REPEAT_START			( 10 )		/**< デフォルトリピート開始カウント		*/
#define ksDEFALUT_REPEAT_INTERVAL		( 15 )		/**< デフォルトリピート間隔				*/

/************************************************************************************************/
/**
 * 検査キー定義構造体
 * これによりJOYパッドとキーボードのキーアサインを共通化する
 */
/************************************************************************************************/
typedef struct _KSKEYASSIGN
{
	KsUInt32			key;	/**< KEY */
	KsUInt32			pad;	/**< PAD */
}KSKEYASSIGN;

/************************************************************************************************/
/**
 * @class		KsPad
 * @brief		ジョイパッド取得クラス(Windows関数用)
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
class ksENGINE_API KsPad
{
	public:
		KsUInt32					m_now;			/**< 現在の入力値							*/
		KsUInt32					m_old;			/**< 一つ前の入力値							*/
		KsUInt32					m_trg;			/**< 押されたとき(now ^ old) & now			*/
		KsUInt32					m_off;			/**< 離されたとき(now ^ old) & old			*/
		KsUInt32					m_rpt;			/**< リピート								*/
		KsUInt32					m_rptStart;		/**< リピート開始時間							*/
		KsUInt32					m_rptInterval;	/**< リピート間隔							*/
		KsUInt32					m_timer;		/**< タイマー（リピート用）					*/
		KsUInt32					m_buttonMax;	/**< 使用ボタンの最大値						*/
		KsUInt32					m_state;		/**< 動作可能か?								*/
		KsUInt32					m_id;			/**< ID										*/
		KsUInt32					m_limit_x1;		/**< スティックの閾値→						*/
		KsUInt32					m_limit_x2;		/**< スティックの閾値←						*/
		KsUInt32					m_limit_y1;		/**< スティックの閾値↑						*/
		KsUInt32					m_limit_y2;		/**< スティックの閾値↓						*/

	public:
		/**
		 * コンストラクタ
		 */
									KsPad();

		/**
		 * コンストラクタ(指定番号のPADの初期化)
		 * @param		index		指定番号
		 * @param		buttonMax	ボタンの数
		 */
									KsPad( KsInt32 index, KsInt32 buttonMax=16 );

		/**
		 * デストラクタ
		 */
		virtual						~KsPad();

		/**
		 * 指定番号のPADの初期化
		 * @param		index		指定番号
		 * @param		buttonMax	ボタンの数
		 * @retval		ksTRUE		初期化成功
		 * @retval		ksFALSE		初期化失敗
		 */
		virtual KsBool				initialize( KsInt32 index, KsInt32 buttonMax=16 );

		/**
		 * 入力情報を読み込み
		 * @return					入力データ
		 */
		virtual KsUInt32			read();

		/**
		 * 指定キーとのマージ処理
		 * @param	pKd				キーアサインデータ
		 * @param	pBuf			キーデータ
		 */
		virtual KsUInt32			merge( KSKEYASSIGN*	pKd, KsByte* pBuf );

		/**
		 * 更新処理
		 * @param	data			入力データ
		 */
		virtual void				update( KsUInt32 data );
};

#endif /* __KSPAD_H__ */

