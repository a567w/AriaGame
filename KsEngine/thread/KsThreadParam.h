/************************************************************************************************/
/** 
 * @file		KsThreadParam.h
 * @brief		スレッド管理
 * @author		Tsukasa Kato
 * @date		2004/08/17
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSTHREADPARAM_H__
#define __KSTHREADPARAM_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                          */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
typedef KsUInt32 ( __stdcall *KsThreadFunc )( void * );

/************************************************************************************************/
/**
 * スレッドプライオリティ
 * @enum	ksTHREAD_PRIORITY_TYPE
 * @author  Tsukasa Kato
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
enum ksTHREAD_PRIORITY_TYPE
{
	ksTHREAD_PRIORITY_TIME_CRITICAL = THREAD_PRIORITY_TIME_CRITICAL,
	ksTHREAD_PRIORITY_HIGHEST       = THREAD_PRIORITY_HIGHEST,
	ksTHREAD_PRIORITY_ABOVE_NORMAL  = THREAD_PRIORITY_ABOVE_NORMAL,
	ksTHREAD_PRIORITY_NORMAL        = THREAD_PRIORITY_NORMAL,
	ksTHREAD_PRIORITY_BELOW_NORMAL  = THREAD_PRIORITY_BELOW_NORMAL,
	ksTHREAD_PRIORITY_LOWEST        = THREAD_PRIORITY_LOWEST,
	ksTHREAD_PRIORITY_IDLE          = THREAD_PRIORITY_IDLE,
	ksTHREAD_PRIORITY_FORCE32       = 0x7fffffff
};

/************************************************************************************************/
/**
 * スレッドパラメータ
 * @class	KsThreadParam
 * @author  Tsukasa Kato
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class KsThreadParam
{
	public:
		KsMutex				m_mutex;		/**< 排他制御用				*/
		void*				m_pParam;		/**< スレッドパラメータ		*/
		KsBool				m_bStart;		/**< スタートフラグ			*/
		KsThreadCondition	m_condition;	/**< スレッドコンディション	*/
		KsThreadFunc		m_func;			/**< スレッドファンクション	*/
		//KsMemoryAllocator*	m_pAllocator;

	public:
		KsThreadParam();
		KsThreadParam( KsThreadFunc func, void* pParam );

		void				start();
		void				wait();
};

#endif		/* __KSTHREADPARAM_H__ */

