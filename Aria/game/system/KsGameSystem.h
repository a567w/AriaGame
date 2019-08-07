/************************************************************************************************/
/** 
 * @file		KsGameSystem.h
 * @brief		ゲームシステム
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSGAMESYSTEM_H__
#define __KSGAMESYSTEM_H__

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
 * @class		KsGameSystem
 * @brief		基本タスクマネージャクラス
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.10
 * @note		なし
 */
/************************************************************************************************/
class KsGameSystem : public KsSceneManager
{
	public:
		/**
		 * インスタンス取得
		 */
		static KsGameSystem*			getInstancePtr();

		/**
		 * 開放
		 */
		static void						destoryInstance();

		/**
		 * ゲームタスクを追加する
		 */
		static KsBool					addGameTask( KsTask* pTask );

		/**
		 * ゲームタスクを取り除く
		 */
		static KsBool					removeGameTask( KsTask* pTask );

	protected:
		/**
		 * コンストラクタ(シングルトンのためにprotected)
		 */
										KsGameSystem();
	public:
		/**
		 * デストラクタ
		 */
		virtual							~KsGameSystem();

		/**
		 * ゲーム生成
		 * @param	hInstance			インスタンス
		 * @param	hPrevInstance		インスタンス
		 * @param	lpCmdLine			コマンドライン
		 * @param	nCmdShow			コマンド表示
		 */
		KsBool							create( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, KsInt32 nCmdShow );
		
		/**
		 * メインループ
		 */
		void							loop();

		/**
		 * 初期化処理
		 * @retval		ksTRUE			成功
		 * @retval		ksFALSE			失敗
		 */
		KsBool							initialize();

		/**
		 * 後処理
		 * @retval		ksTRUE			成功
		 * @retval		ksFALSE			失敗
		 */
		KsBool							terminate();

		/**
		 * メッセージループ
		 */
		KsBool							messageLoop();

		/** 
		 * 描画システム取得
		 * @return						描画システムのポインタ
		 */
		KsRenderSystem*					getRenderSystem() { return m_pRenderSystem; }

		/**
		 * クリアーカラー
		 * @param		color			クリアーカラー値
		 */
		void							setClearColor( const KsColor& color ) { m_clearColor = color; }

		/**
		 * アクティブ状態かのフラグをセットする
		 */
		void							setActive( KsBool _bActive ) { m_bActive = _bActive; }

		/**
		 * アクティブ状態か?
		 * @retval		ksTRUE			アクティブ
		 * @retval		ksFALSE			非アクティブ
		 */
		KsBool							isActive() const { return m_bActive; }

		/**
		 * 描画するかのフラグをセットする
		 */
		void							setRender( KsBool _bRender ) { m_bRender = _bRender; }

		/**
		 * 描画するか?
		 * @retval		ksTRUE			描画
		 * @retval		ksFALSE			非描画
		 */
		KsBool							isRender() const { return m_bRender; }

		/**
		 * ゲームを終了させる
		 */
		void							gameExit();

		/**
		 * メインループ中か？
		 * @retval		ksTRUE			メインループ中
		 * @retval		ksFALSE			メインループ終了
		 */
		KsBool							isMainLoop() const { return m_bMainLoop; }

		/**
		 * ゲームループ中か？
		 * @retval		ksTRUE			ゲームループ中
		 * @retval		ksFALSE			ゲームループ終了
		 */
		KsBool							isGameLoop();
		
		/**
		 * ウインドウの幅を取得する
		 * @return						ウインドウの幅
		 */
		KsInt32							getWindowWidth() const	{ return m_pMainWindow->getWidth();	 }

		/**
		 * ウインドウの高さを取得する
		 * @return						ウインドウの高さ
		 */
		KsInt32							getWindowHeight() const	{ return m_pMainWindow->getHeight(); }

		/**
		 * ウインドウのアスペクト比を取得する
		 * @return						ウインドウのアスペクト比
		 */
		KsReal							getWindowAspectRatio() const { return ((KsReal)m_pMainWindow->getWidth())/((KsReal)m_pMainWindow->getHeight()); }

		/**
		 * フレームレートを取得する
		 */
		KsReal							getFrameRate() const { return 1.0f/60.0f; }

		/**
		 * モデルを追加する
		 */
		void							addModel( KsModel* pModel );

		/**
		 * アクターを追加する
		 */
		void							addActor( KsActor* pActor );

	protected:
		/**
		 * 実行処理
		 * @param		pParam			パラメータ
		 */
		virtual void					execute( void* pParam );

		/**
		 * 描画処理
		 * @param		pParam			パラメータ
		 */
		virtual void					render( void* pParam );

		/**
		 * 更新処理
		 * @param		pParam			パラメータ
		 */
		virtual void					update( void* pParam );

		/**
		 * すべての処理を実行
		 * @param		pParam			ここでわたしたパラメータがタスクのexecuteやrenderの引数に渡る
		 *								デフォルトでは、NULLが設定されている。
		 */
		virtual void					run( void* pParam );

		/**
		 * 描画開始
		 */
		virtual void					begineRender();

		/**
		 * 描画終了
		 */
		virtual void					endRender();

		/**
		 * VSync待ちの処理(仮想)
		 * @param	count				何回まつか？
		 */
		void							vsync( KsInt32 count );

		/**
		 * ソフトウェアーリセット処理
		 */
		void							softwareReset();

		/**
		 * ソフトリセット要求があったかどうか？
		 */
		KsBool							isSoftwareReset();
	
	protected:
		
		/**
		 * ポーリング処理
		 */
		void							polling();

		/*
		 * サウンド更新処理
		 */
		void							sound();

		/**
		 * パッド処理
		 */
		void							pad();

		/**
		 * VSync待ちの処理(仮想)
		 */
		void							vsync();

	public:
		KsWindowParam					m_mainWindowParam;		/**< ウインドウパラメータ			*/
		KsWindow*						m_pMainWindow;			/**< ウインドウフレーム			*/
		KsRenderSystem*					m_pRenderSystem;		/**< 描画システム					*/
		KsPhysicsSystem*				m_pPhysicsSystem;		/**< 物理エンジンシステム			*/
		KsOVRSystem*					m_pOVRSystem;			/**< OVRシステム					*/
		KsVirtualMachine*				m_pVirtualMachine;		/**< バーチャルマシン				*/
		KsInputSystem*					m_pInputSystem;			/**< 入力システム					*/
		KsGamePadManager*				m_pPadManager;			/**< パッドマネージャ				*/
		KsGameResourceManager*			m_pGameResourceManager;	/**< ゲームリソースマネージャ		*/
		KsGameShaderManager*			m_pGameShaderManager;	/**< ゲームシェーダーマネージャ		*/
		KsCameraManager*				m_pCameraManager;		/**< カメラマネージャ				*/
		KsFileSystem*					m_pFileSystem;			/**< ファイルシステム				*/
		//KsGameSoundManager*			m_pSoundManager;		/**< ゲームサウンドマネージャ		*/
		KsColor							m_clearColor;			/**< バッファクリアカラー			*/
		KsBool							m_bActive;				/**< アクティブかどうか?			*/
		KsBool							m_bRender;				/**< 描画するかどうか?				*/
		KsBool							m_bMainLoop;			/**< ゲームループフラグ			*/
//		KsThreadGroup					m_threadGroup;			/**< スレッドグループ				*/
		KsDeferredRender*				m_pDeferredRender;		/**< ディファードレンダー			*/
		KsForwardPlusRender*			m_pForwardPlusRender;	/**< Forward+					*/
		KsPhysicsThread*				m_pPhysicsThread;		/**< 物理シミュレーション			*/
	public:
		/* マネージャのインスタンス */
		static KsGameSystem*			m_pInstance;			/**< インスタンス					*/
};


/************************************************************************************************/
/**
 * ゲームシステム生成
 * @param	hInstance			インスタンス
 * @param	hPrevInstance		インスタンス
 * @param	lpCmdLine			コマンドライン
 * @param	nCmdShow			コマンド表示
 * @note	すでにウインドウがある場合は、それをもとのサイズで復旧させる
 */
/************************************************************************************************/
extern KsGameSystem* KsGameCreate( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, KsInt32 nCmdShow );

/************************************************************************************************/
/*
 * ゲームループ
 * @param	pGame	ゲームシステムのポインタ
 */
/************************************************************************************************/
extern void KsGameLoop( KsGameSystem* pGame );

/************************************************************************************************/
/*
 * ゲームシステム破棄
 * @param	pGame	ゲームシステムのポインタ
 */
/************************************************************************************************/
extern void KsGameDestroy( KsGameSystem* pGame );


#endif		/* __KSGAMESYSTEM_H__ */