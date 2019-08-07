/************************************************************************************************/
/** 
 * @file		KsThread.h
 * @brief		�X���b�h�Ǘ�
 * @author		Tsukasa Kato
 * @date		2004/08/17
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSTHREAD_H__
#define __KSTHREAD_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                          */
/*==============================================================================================*/
#include "KsMutex.h"
#include "KsEvent.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/
#define ksTHREAD_END()		_endthreadex( 0 )	/**< �X���b�h�I���}�N��		*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
typedef KsUInt32 ( __stdcall *KsThreadFunc )( void * );

/************************************************************************************************/
/**
 * �X���b�h
 * @class	KsThread
 * @author  Tsukasa Kato
 * @since   2003/03/22
 * @version ----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsThread
{
	public:
		/**
		 * �R���X�g���N�^
		 */
								KsThread();

		/**
		 * �R���X�g���N�^
		 * @param	pParam		�p�����[�^
		 */
		explicit				KsThread( KsThreadFunc func, void* pParam );

		/**
		 * �f�X�g���N�^
		 */
								~KsThread();

		/** 
		 * == ���Z�q�I�[�o�[���[�h
		 * @retval	ksTRUE		������
		 * @retval	ksFALSE		�������Ȃ�
		 */
		KsBool					operator == ( const KsThread& rhs ) const;

		/** 
		 * != ���Z�q�I�[�o�[���[�h
		 * @retval	ksTRUE		�������Ȃ�
		 * @retval	ksFALSE		������
		 */
		KsBool					operator != ( const KsThread& rhs ) const;

		/**
		 * �X���b�h�̏I����ҋ@����
		 */
		void					join();

		/**
		 * �g�p�v���Z�b�T���Z�b�g����
		 * @param	prosessor	�g�p�v���Z�b�T�ԍ�
		 */
		KsBool					setProcessor( KsUInt32 prosessor );

		/**
		 * �w�莞�Ԍ��݂̃X���b�h�̎��s���x�~����
		 * @param	time		�҂�����(ms)
		 */
		static void				sleep( const KsUInt32 time );

		/**
		 * ���݂̃X���b�h�̎��s�𒆒f���đ��̃X���b�h�֎��s������܂��B
		 */
		static void				yield();

	private:
		KsHandle				m_handle;		/**< �X���b�h�n���h��						*/
		KsUInt32				m_id;			/**< �X���b�hID							*/
		KsBool					m_bJoin;		/**< �X���b�h�o�^��Ԃ��ǂ����̃t���O		*/
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

        uint32 JobThread::threadMain()
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

                                InterlockedDecrement( &m_pJobSystem->remainingJobCount );
                        }
                        else
                        {
                                // no job pending..
                                // wait for the event
                                Threading::sleep( 10u );
                        }
                }
                return 0u;
        }

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
