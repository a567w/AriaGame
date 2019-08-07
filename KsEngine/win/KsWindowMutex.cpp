/*************************************************************************************************/
/** 
 * @file	KsWindowParam.cpp
 * @brief	ウインドウパラメータ
 * @author	Tukasa Kato
 * @date	2003/03/22
 * @since	----/--/--
 * @version	1.0.0
 */
/*************************************************************************************************/

/*===============================================================================================*/
/*                                 << インクルード >>                                             */
/*===============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"
#include "KsEngine/win/KsWindowMutex.h"

/*===============================================================================================*/
/*                                     << 定義 >>                                                */
/*===============================================================================================*/

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsWindowMutex::KsWindowMutex()
	: m_hMutex( 0 )
{
}

/************************************************************************************************/
/*
 * デストラクタ
 */
/************************************************************************************************/
KsWindowMutex::~KsWindowMutex()
{
	release();
}

/************************************************************************************************/
/*
 * 0 : 他に同名のものは存在しない→所有権獲得成功！
 * 1 : 他に同名のものが存在する。(error)
 */
/************************************************************************************************/
KsBool KsWindowMutex::open( const KsString& mutexName )
{
	// 同一プロセスのスレッド間でならCriticalSectionを用いるべき！
	release();

	// この名前で登録
	m_hMutex = CreateMutex( NULL, true, mutexName.c_str() );
	
	if( GetLastError() == ERROR_ALREADY_EXISTS )
	{
		return ksFALSE;
	}

	//	⇒エラーではなく、既存であるという意味で1を返している
	//	この場合も、MutexのOpenには成功していると考えることが出来る。
	
	// 既存のため所有権が獲得できていない

	return ksTRUE; // それ以外のエラーって想定できないし、いいんでない？
}

/************************************************************************************************/
/*
 * 所有権が獲得できるまで待つ
 */
/************************************************************************************************/
void KsWindowMutex::wait()
{
	::WaitForSingleObject( m_hMutex, INFINITE );	// 所有権が得られるまで待つ
}

/************************************************************************************************/
/*
 * Mutexを解放する
 */
/************************************************************************************************/
void KsWindowMutex::release()
{
	if( m_hMutex != NULL )
	{
		//	所有権の解放
		::ReleaseMutex( m_hMutex );

		//	生成したMutexの破棄する
		::CloseHandle( m_hMutex );
		
		//	他のが生きていると、無事破壊できるとも限らないが．．？

/*
	MSDNライブラリ2001年4月リリースより：
ハンドルを閉じるには、CloseHandle 関数を使います。プロセスが終了する際に、システムはそのプロセスが所有していたハンドルを自動的に閉じます。ミューテックスオブジェクトに対して 1 つまたは複数のハンドルが開いている場合、最後のハンドルが閉じた時点で、そのミューテックスオブジェクトは破棄されます。
*/
		//	「1 つまたは複数のハンドルが開いている」の「開いている」は、
		//	CreateMutexのことを意味するのだと思うが、
		//	つまり、解放に関しては、
		//	参照カウントのような処理をしていると考えることが出来るのだろう．．

		m_hMutex = NULL;
	}
}


