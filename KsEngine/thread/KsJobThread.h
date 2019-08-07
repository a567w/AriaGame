/************************************************************************************************/
/** 
 * @file		KsThread.h
 * @brief		スレッド管理
 * @author		Tsukasa Kato
 * @date		2004/08/17
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSJOBTHREAD_H__
#define __KSJOBTHREAD_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                          */
/*==============================================================================================*/
#include "KsMutex.h"
#include "KsEvent.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
#define ksTHREAD_END()		_endthreadex( 0 )	/**< スレッド終了マクロ		*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
typedef KsUInt32 ( __stdcall *KsThreadFunc )( void * );

/************************************************************************************************/
/**
 * ジョブスレッド
 * @class	KsJobThread
 * @author  Tsukasa Kato
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsJobThread : public KsThread
{
	public:
		/**
		 * コンストラクタ
		 * @param	pParam		パラメータ
		 */
								KsJobThread();

		/**
		 * デストラクタ
		 */
								~KsJobThread();

		/**
		 * スレッドのメイン関数
		 * @return	実行終了結果
		 */
		virtual KsUInt32		threadMain();

	private:
		KsJobSystem*			m_pJobSystem;	/**< ジョブシステム */
};

KsUInt32 KsJobThread::threadMain()
{
	while( m_pJobSystem->isRunning )
	{
		// get next job:
		const JobDefinition* pNextJob;

		if( m_pJobSystem->pendingJobs.popFront( &pNextJob ) )
		{
			JobContext context;

			// execute job
			JobFunction pJobFunction = static_cast< JobFunction >( Memory::convertIntegerToPointer( pNextJob->binaryAddress ) );

			context.parameterAddress        = pNextJob->parameterAddress;
			context.parameterSize           = pNextJob->parameterSize;

			(*pJobFunction)( &context );

			KsThread::interlockedDecrement( &m_pJobSystem->remainingJobCount );
		}
		else
		{
			KsThread::sleep( 10 );
		}
	}

	return 0;
}

class ksENGINE_API KsJobSystem
{
	public:
		//job command queue
		LockingMessageQueue< const JobDefinition* > pendingJobs;

		// worker threads
		KsArray< KsJobThread* >		workerThreads;

		KsLong						m_jobCount;
		KsBool						m_isRunning;

		//
		KsMemoryAllocator*			m_pAllocator;
};

#endif		/* __KSTHREAD_H__ */


namespace motor3d
{

        class MemoryAllocator;

        struct JobContext;

        typedef void (*JobFunction)( JobContext* pContext );

        struct JobDefinition
        {
                MemorySize      definitionSize;
                MemorySize      binaryAddress;
                MemorySize      binarySize;

                // :TODO: replace with input/output stream definition
                MemorySize      parameterAddress;
                MemorySize      parameterSize;

        };

        //              struct JobDataStream
        //              {
        //                      MemorySize      address;
        //                      MemorySize      stride;
        //                      // MemorySize   count;
        //                      //MemorySizs    size;
        //                      //MemorySize    frequency;
        //              };
        //
        //              struct JobMemoryBuffer
        //              {
        //                      MemorySize              baseAddress;
        //                      MemorySize              size;
        //              };

        struct JobContext
        {
                enum
                {
                        MaxInputStreamCount     = 16u,
                        MaxOutputStreamCount = 16u
                };
                MemorySize              parameterAddress;
                MemorySize              parameterSize;
                //uint32                        jobId;

                //                      JobDataStream   inputStreams[ MaxInputStreamCount ];    // make this dynamic...
                //                      JobDataStream   outputStreams[ MaxOutputStreamCount ];

                //                      JobMemoryBuffer scratchMemory;
        };


        // :TODO: make this structure private?
        struct JobSystem;

        JobSystem*      createJobSystem( MemoryAllocator* pAllocator );
        void            destroyJobSystem( JobSystem* pJobSystem );

        MemorySize      getJobBinarySize( const void* pFunction );

        void            startJobs( JobSystem* pJobSystem, const JobDefinition* pJobs, MemorySize jobDefinitionSize, MemorySize jobCount );
        void            waitForCompletionOfAllJobs( JobSystem* pJobSystem );

}

//-----------------------------------------------------------------------------

#endif

----------------------------------------------------------------------------

namespace motor3d
{

        //-----------------------------------------------------------------------------

        class MemoryAllocator;
        class Thread;

        //-----------------------------------------------------------------------------

        struct ThreadContext
        {
                char                            name[ 128 ];
                Thread*                         pThread;
                MemoryAllocator*        pAllocator;
        };

        enum ThreadPriority
        {
                ThreadPriority_Lowest,
                ThreadPriority_BelowNormal,
                ThreadPriority_Normal,
                ThreadPriority_AboveNormal,
                ThreadPriority_Highest,
                ThreadPriority_Count
        };

        //-----------------------------------------------------------------------------

        namespace Threading
        {

                void                            initialize();
                void                            shutdown();

                MemorySize                      getSystemCoreCount();

                ThreadContext*          getCurrentContext();
                void                            sleep( unsigned int milliseconds );
        }

        //-----------------------------------------------------------------------------

}

//-----------------------------------------------------------------------------

#if defined( MOTOR3D_TARGET_PLATFORM_WIN32 )
#       include "motor3d/base/win32/thread_win32.hpp"
#else
#       error "Unsuported Platform!"
#endif

//-----------------------------------------------------------------------------

namespace motor3d
{

        //-----------------------------------------------------------------------------

        namespace Threading
        {

                ThreadId                getCurrentThreadId();

        }

        //-----------------------------------------------------------------------------

}

//-----------------------------------------------------------------------------

#endif // #ifndef MOTOR3D_THREAD_HPP_INCLUDED
namespace motor3d
{

        //------------------------------------------------------------------------------

        class JobThread;

        //------------------------------------------------------------------------------

        struct JobSystem
        {

                //job command queue
                LockingMessageQueue< const JobDefinition* > pendingJobs;

                // worker threads
                Array< JobThread* >     workerThreads;

                // atomic:
                LONG                            remainingJobCount;
                bool                            isRunning;

                //
                MemoryAllocator*        pAllocator;
        };

        //------------------------------------------------------------------------------

        class JobThread : public Thread
        {
        public:
                JobThread( JobSystem* pJobSystem )
                {
                        m_pJobSystem = pJobSystem;
                }

                virtual uint32          threadMain();

        private:
                JobSystem*      m_pJobSystem;
        };



        //------------------------------------------------------------------------------

        JobSystem* createJobSystem( MemoryAllocator* pAllocator )
        {
                // :TODO: make this an option
                const MemorySize threadCount = Threading::getSystemCoreCount();

                MOTOR3D_TRACE_INFO( "creating job system with %i threads\n", threadCount );
                // :TODO: this limit is baaad..
                // i should try to make this more flexible (at least put in a parameter..)
                const MemorySize maxJobCount = 65536u;

                JobSystem* pResult = MOTOR3D_NEW( pAllocator,JobSystem );

                pResult->pAllocator                     = pAllocator;
                pResult->isRunning                      = true;
                pResult->remainingJobCount      = 0u;

                pResult->pendingJobs.create( maxJobCount, pAllocator );

                pResult->workerThreads.create( threadCount, pAllocator );
                for( MemorySize i = 0u; i < threadCount; ++i )
                {
                        pResult->workerThreads[ i ] = MOTOR3D_NEW( pAllocator, JobThread )( pResult );
                        pResult->workerThreads[ i ]->create( "JobSystem WorkerThread", nullptr );
                        pResult->workerThreads[ i ]->setAffinityMask( 1u << i );
                        // :TODO: set thread priority to something useful..
                        pResult->workerThreads[ i ]->start();
                }

                return pResult;
        }

        //------------------------------------------------------------------------------

        void destroyJobSystem( JobSystem* pJobSystem )
        {
                waitForCompletionOfAllJobs( pJobSystem );
                pJobSystem->isRunning = false;

                for( MemorySize i = 0u; i < pJobSystem->workerThreads.getSize(); ++i )
                {
                        pJobSystem->workerThreads[ i ]->join();
                        pJobSystem->workerThreads[ i ]->destroy();

                        MOTOR3D_DELETE( pJobSystem->pAllocator, pJobSystem->workerThreads[ i ] );
                }
                pJobSystem->pendingJobs.destroy( pJobSystem->pAllocator );
                pJobSystem->workerThreads.destroy( pJobSystem->pAllocator );
                MOTOR3D_DELETE( pJobSystem->pAllocator, pJobSystem );
        }

        //------------------------------------------------------------------------------

        MemorySize getJobBinarySize( const void* pFunction )
        {
                MOTOR3D_USE_ARGUMENT( pFunction );
                return 0u;
        }

        //------------------------------------------------------------------------------

        void startJobs( JobSystem* pJobSystem, const JobDefinition* pJobs, MemorySize jobDefinitionSize, MemorySize jobCount )
        {
                const uint8* pJobDefinitionData = reinterpret_cast< const uint8* >( pJobs );
                for( MemorySize index = 0u; index < jobCount; ++index )
                {
                        pJobSystem->pendingJobs.pushBack( reinterpret_cast< const JobDefinition* >( pJobDefinitionData ) );

                        pJobDefinitionData += jobDefinitionSize;
                }

                LONG oldValue = pJobSystem->remainingJobCount;
                while( InterlockedCompareExchange( &pJobSystem->remainingJobCount, static_cast< LONG >( oldValue + jobCount ), oldValue ) != oldValue )
                {
                        oldValue = pJobSystem->remainingJobCount;
                }
        }

        //------------------------------------------------------------------------------

        void waitForCompletionOfAllJobs( JobSystem* pJobSystem )
        {
                while( pJobSystem->remainingJobCount > 0u )
                {
                        // :TODO: use event here...{
                        Threading::sleep( 5u );
                }
        }

        //------------------------------------------------------------------------------

}
