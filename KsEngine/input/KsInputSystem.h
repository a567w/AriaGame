/************************************************************************************************/
/** 
 * @file		KsInputSystem.h
 * @brief		入力処理
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSINPUTSYSTEM_H__
#define __KSINPUTSYSTEM_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/


template class ksENGINE_API KsArray< KsPad* >;

/************************************************************************************************/
/**
 * @class		KsInputSystem
 * @brief		入力マネージャ(シングルトンクラス)
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
class ksENGINE_API KsInputSystem : public KsSingleton< KsInputSystem >
{
	public:
		/**
		 * インスタンス取得
		 * @return					インスタンス
		 */
		static KsInputSystem&		getInstance();

		/**
		 * インスタンス取得
		 * @return					インスタンス
		 */
		static KsInputSystem*		getInstancePtr();

	public:
		/**
		 * コンストラクタ
		 */
									KsInputSystem();

		/**
		 * コンストラクタ(初期化処理)
		 * @param	num				ジョイスティックドライバがサポートするジョイスティック数
		 */
									KsInputSystem( KsUInt32 num );

		/**
		 * デストラクタ
		 */
									~KsInputSystem();

		/**
		 * 初期化処理
		 * @param	num				ジョイスティックドライバがサポートするジョイスティック数
		 */
		void						initialize( KsUInt32 num );

		/*
		 * 開放処理
		 */
		void						release();

		/**
		 * 更新処理
		 */
		void						update();

		/**
		 * パッドのベタ入力を取得する
		 * @param	index			パッド番号
		 * @return					入力データ
		 */
		KsUInt32					getPadNow( KsUInt32 index ) { return m_vpPads[ index ]->m_now; }

		/**
		 * パッドのトリガー情報を取得する
		 * @param	index			パッド番号
		 * @return					入力データ
		 */
		KsUInt32					getPadTrg( KsUInt32 index ) { return m_vpPads[ index ]->m_trg; }

		/**
		 * パッドのリリース情報を取得する
		 * @param	index			パッド番号
		 * @return					入力データ
		 */
		KsUInt32					getPadOff( KsUInt32 index ) { return m_vpPads[ index ]->m_off; }

		/**
		 * パッドのリーピー情報を取得する
		 * @param	index			パッド番号
		 * @return					入力データ
		 */
		KsUInt32					getPadRpt( KsUInt32 index ) { return m_vpPads[ index ]->m_rpt; }

		/** 
		 * パッド数を取得する
		 * @return					パッド数
		 */
		KsUInt32					getNumPad() const { return m_padNum; }

		/**
		 * マウス情報を取得する
		 * @return					マウス情報
		 */
		KsMouse*					getMouse() { return m_vpMouses[ 0 ]; }

		/** 
		 * マウス数を取得する
		 * @return					マウス数
		 */
		KsUInt32					getNumMouse() const { return m_vpMouses.size(); }

	private:
		KsBool						m_bInit;			/**< 初期化フラグ		*/
		KsArray< KsPad* >			m_vpPads;			/**< パッド配列			*/
		KsArray< KsMouse* >			m_vpMouses;			/**< マウス配列			*/
		KsByte						m_keyData[ 256 ];	/**< キーデータ			*/
		KsUInt32					m_padMax;			/**< 最大パッド数		*/
		KsUInt32					m_padNum;			/**< パッド数			*/		
};



#endif /* __KSINPUTSYSTEM_H__ */

