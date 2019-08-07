/************************************************************************************************/
/** 
 * @file		KsTimer.h
 * @brief		タイマー
 * @author		Tsukasa Kato
 * @data		2005/06/27
 * @since		2005/06/27
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSTIMER_H__
#define __KSTIMER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsTimer
 * @brief		タイマー
 * @author		Tsukasa Kato
 * @data		2005/06/27
 * @since		2005/06/27
 */
/************************************************************************************************/
class ksENGINE_API KsTimer
{
	public:

		enum ksFPS_TYPE
		{
			ksFPS60 = 0,
			ksFPS30 = 1,
			ksFPS15 = 2,
		};

	public:
		/**
		 * コンストラクタ
		 */
		KsTimer();

	public:
		/**
		 * 初期化
		 */
		static void					initialize();

		/**
		 * ミリ秒で時間を取得
		 * @return					ミリ秒
		 */
		static KsUInt32				getTimeCount();

		/**
		 * マイクロ秒で時間を取得
		 * @return					マイクロ秒
		 */
		static KsInt64				getMicroCount();

		/**
		 * FPSを取得する
		 * @return					FPS
		 */
		static KsUInt32				getFps();

		/**
		 * フレームカウントを取得
		 * @return					フレームカウント
		 */
		static KsUInt32				getFrameCount();

		/**
		 * 更新処理
		 */
		static void					update();

		static void					vsync( ksFPS_TYPE _fpsType = ksFPS60 );

		static void					setStart();
		static void					setCpu();
		static void					setGpu();
		static void					setTotal();

		static KsUInt32				getCpuPerformance();
		static KsUInt32				getGpuPerformance();
		static KsUInt32				getTotalPerformance();

		KsReal						getElapsedTime() const { return m_elapsedTime; }

	private:
		static LARGE_INTEGER		m_frequency;				/**< 繰返し速度			*/
		static KsBool				m_support;					/**< サポート状態		*/
		static KsUInt32				m_initTime;					/**< 初期時間			*/
		static KsReal				m_frameTime;				/**< フレームタイム		*/
		static KsUInt32				m_frameCount;				/**< 経過フレーム数		*/
		static KsUInt32				m_fps;						/**< FPS値				*/
		static KsUInt32				m_fpsCount;					/**< FPS計測用			*/
		static KsUInt32				m_startTime;				/**< 計測開始時間		*/
		static KsUInt32				m_cpuTime;					/**< CUP処理時間			*/
		static KsUInt32				m_gpuTime;					/**< GPU処理時間			*/
		static KsUInt32				m_totalTime;				/**< 全体処理時間		*/
		static KsUInt32				m_lastFrameTime;			/**< 前回FPS更新時刻		*/
		static KsUInt32				m_cpuPerformance;			/**< CPUパフォーマンス	*/
		static KsUInt32				m_gpuPerformance;			/**< GPUパフォーマンス	*/
		static KsUInt32				m_totalPerformance;			/**< 合計パフォーマンス	*/
		KsReal						m_elapsedTime;				/**< 経過時間			*/
};


#endif		/* __KSTIMER_H__ */


