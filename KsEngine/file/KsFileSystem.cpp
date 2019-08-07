/************************************************************************************************/
/**
 * @file		KsFileSystem.cpp
 * @brief		�t�@�C���V�X�e��
 * @author		Tsukasa Kato
 * @date		2004/03/30
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
template<> KsFileSystem* KsSingleton< KsFileSystem >::m_pInstance = 0;

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsFileSystem& KsFileSystem::getInstance()
{
	return (*m_pInstance);
}
/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsFileSystem* KsFileSystem::getInstancePtr()
{
	return m_pInstance;
}

/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsFileSystem::KsFileSystem( ksTHREAD_PRIORITY_TYPE priority, KsUInt32 prosessor )
{
	m_packIndex = 0;
	m_pCurrentRequest = 0;
	m_bCancel = ksFALSE;

	m_pFileThread = ksNew KsFileThread( this, priority, prosessor );

	m_pFileThread->run();
}

/************************************************************************************************/
/*
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsFileSystem::~KsFileSystem()
{
}

/************************************************************************************************/
/*
 * �񓯊��ǂݍ���(�ǂݍ��݃��N�G�X�g���X�^�b�N�ɂ��߂Ă���)
 * �ǂݍ��ݗp���N�G�X�g��ǉ�����
 * @param		pRequest		���N�G�X�g
 */
/************************************************************************************************/
KsBool KsFileSystem::pushRequest( KsReadRequest* pRequest )
{
	KsBool	bStart = ksFALSE;

	m_mutex.lock();

	if( NULL == m_pCurrentRequest )
	{
		m_pCurrentRequest = pRequest;
		bStart            = ksTRUE;
	}
	else
	{
		// ���N�G�X�g�L���[�ɃZ�b�g
		m_requestQueue.push( pRequest );
	}

	m_mutex.unlock();

	// �X���b�h�J�n����
	if( bStart )
	{
		m_pFileThread->setWaitEvent();
	}

	return ksTRUE;
}

/************************************************************************************************/
/*
 * �񓯊��t�@�C���I�[�v��
 * @param		pRequest		���N�G�X�g
 * @return						�t�@�C���n���h��
 */
/************************************************************************************************/
KsHandle KsFileSystem::openAsync( KsReadRequest* pRequest )
{
	if( !pRequest )
	{
		return ksFALSE;
	}

	HANDLE	hFile = ::CreateFile(	pRequest->m_fileName.c_str(),
									GENERIC_READ,
									0,
									NULL,
									OPEN_EXISTING,
									FILE_FLAG_OVERLAPPED,
									NULL
									);

	if( INVALID_HANDLE_VALUE == hFile )
	{
		/* ERROR */
		pRequest->m_status = ksREADING_ERROR;
		return ksFALSE;
	}

	// (��)�������[�m�ۂ����b�N����悤�ɏC�����K�v�ł�
	KsInt32		fileSize = ::GetFileSize( hFile, NULL );
	KsByte*		pBuffer  = ksNew KsByte [ fileSize ];

	if( !pBuffer )
	{
		::CloseHandle( hFile );
		pRequest->m_status = ksREADING_ERROR;
		return ksFALSE;
	}

	pRequest->m_fileHandle	 = hFile;
	pRequest->m_dataSize	 = fileSize;
	pRequest->m_pBuffer		 = pBuffer;
	pRequest->m_status		 = ksREADING_READ;

	return pRequest;
}

/************************************************************************************************/
/*
 * �񓯊��t�@�C���I�[�v��
 * @param		pRequest		���N�G�X�g
 * @return						�t�@�C���n���h��
 */
/************************************************************************************************/
KsHandle KsFileSystem::readAsync( KsReadRequest* pRequest )
{
	KsBool	hRet = ::ReadFile( 
					pRequest->m_fileHandle,
					pRequest->m_pBuffer,
					pRequest->m_dataSize,
					&pRequest->m_readSize,
					&pRequest->m_overlapped 
				);

	pRequest->m_status = ksREADING_READ_IDLE;

	return pRequest;
}

/************************************************************************************************/
/*
 * �ǂݎ�蒆����
 */
/************************************************************************************************/
KsBool KsFileSystem::reading( KsReadRequest* pRequest )
{
	KsInt32		sErrorID;

	while( 1 )
	{
		if( pRequest->m_dataSize == pRequest->m_readSize )
		{
			break;
		}

		sErrorID = ::GetLastError();

		switch( sErrorID )
		{
			case ERROR_HANDLE_EOF:
			{
				break;
			}
			case ERROR_IO_INCOMPLETE:
			{
				break;
			}
			case ERROR_IO_PENDING:
			{
				if( ::GetOverlappedResult( pRequest->m_fileHandle, &pRequest->m_overlapped, &pRequest->m_readSize, ksTRUE ) )
				{
					m_pCurrentRequest->callbackThread();
					pRequest->m_status = ksREADING_END;
				}
				break;
			}
			default:
			{
				//KsMessage( "�ǂݍ��݃G���[" );
				::CloseHandle( pRequest->m_fileHandle );

				pRequest->m_status = ksREADING_ERROR;
				break;
			}
		}
	}

	return ksTRUE;
}

/************************************************************************************************/
/*
 * �񓯊��t�@�C���N���[�Y
 * @param		pRequest		���N�G�X�g
 * @retval		ksTRUE			����
 * @retval		ksFALSE			���s
 */
/************************************************************************************************/
KsBool KsFileSystem::closeAsync( KsReadRequest* pRequest )
{
	if( pRequest->m_fileHandle )
	{
		::CloseHandle( pRequest->m_fileHandle );
		pRequest->m_fileHandle = NULL;
	}

	const KsBool	bAutoDelete = m_pCurrentRequest->m_bAutoDelete;

	m_pCurrentRequest = NULL;

	if( bAutoDelete )
	{
		// �X���b�h�Z�[�t��delete�łȂ��Ƃ܂���
		ksDELETE( pRequest );
	}

	return ksTRUE;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsUInt32 __stdcall KsFileSystem::KsWorkerThreadFunc( PVOID pv )
{
	KsReadRequest*	pRequest = reinterpret_cast<KsReadRequest*>(pv);
	KsBool			hRet;
	KsInt32			sErrorID;

	hRet = ::ReadFile( 
					pRequest->m_fileHandle,
					pRequest->m_pBuffer,
					pRequest->m_dataSize,
					&pRequest->m_readSize,
					&pRequest->m_overlapped 
				);

	if( !hRet )
	{
		while( 1 )
		{
			if( pRequest->m_dataSize == pRequest->m_readSize )
			{
				break;
			}

			sErrorID = ::GetLastError();

			switch( sErrorID )
			{
				case ERROR_HANDLE_EOF:
				{
					break;
				}
				case ERROR_IO_INCOMPLETE:
				{
					break;
				}
				case ERROR_IO_PENDING:
				{
					::WaitForSingleObject( pRequest->m_fileHandle, INFINITE );

					if( ::GetOverlappedResult( pRequest->m_fileHandle, &pRequest->m_overlapped, &pRequest->m_readSize, ksTRUE ) )
					{
						//m_pCurrentRequest->callbackTH();
						//KsMessage( "Thread dpending" );
					}
					break;
				}
				default:
				{
					//KsMessage( "�ǂݍ��݃G���[" );
					::CloseHandle( pRequest->m_fileHandle );
					break;
				}
			}
		}
	}

	pRequest->callbackThread();

	pRequest->m_status = ksREADING_END;

	_endthreadex( 0 );

	return 0;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsBool KsFileSystem::setRequest( KsReadRequest* pRequest )
{
	if( !pRequest )
	{
		return ksFALSE;
	}

	HANDLE	hFile = ::CreateFile(	pRequest->m_fileName.c_str(),
									GENERIC_READ,
									0,
									NULL,
									OPEN_EXISTING,
									FILE_FLAG_OVERLAPPED,
									NULL
									);

	if( INVALID_HANDLE_VALUE == hFile )
	{
		/* ERROR */
		return ksFALSE;
	}

	KsInt32	fileSize = ::GetFileSize( hFile, NULL );
	KsByte*		pBuffer  = new KsByte [ fileSize ];

	if( !pBuffer )
	{
		::CloseHandle( hFile );
		return ksFALSE;
	}

	pRequest->m_fileHandle	 = hFile;
	pRequest->m_dataSize	 = fileSize;
	pRequest->m_pBuffer		 = pBuffer;
	pRequest->m_threadHandle = (KsHandle)_beginthreadex(
															NULL, 
															NULL, 
															KsWorkerThreadFunc, 
															(void*)pRequest, 
															NULL, 
															&pRequest->m_threadID
															);

	m_pCurrentRequest = pRequest;

	return ksTRUE;
}

/************************************************************************************************/
/*
 * �񓯊��ǂݍ��ݏ���(�L���[�ɂ��܂��Ă��郊�N�G�X�g�����Ԃɏ������Ă���)
 * @retval										�ǂݍ��ݏ�
 */
/************************************************************************************************/
KsInt32 KsFileSystem::polling()
{
	if( m_pCurrentRequest )
	{
		const ksREADING_STATE status = m_pCurrentRequest->getStatus();

		switch( status )
		{
			case ksREADING_START:
				/* �ǂݍ��݊J�n�҂�			*/
				openAsync( m_pCurrentRequest );
				break;
			case ksREADING_READ:
				/* �ǂݍ��ݒ�				*/
				readAsync( m_pCurrentRequest );
				break;
			case ksREADING_END:
				/* �ǂݍ��ݏI��				*/
				break;
			case ksREADING_OPEN_IDLE:
				/* �I�[�v���A�C�h�����O		*/
				break;
			case ksREADING_READ_IDLE:
				/* �ǂݍ��݃A�C�h�����O		*/
				reading( m_pCurrentRequest );
				break;
			case ksREADING_CLOSE_IDLE:
				/* �N���[�Y�A�C�h�����O		*/
				closeAsync( m_pCurrentRequest );
				break;
			case ksREADING_ERROR:
				/* �G���[					*/
				break;
			default:
				break;
		}
	}

	if( m_pCurrentRequest == NULL )
	{
		if( m_requestQueue.size() != 0 )
		{
			KsReadRequest*	pRequest = m_requestQueue.pop();
			setRequest( pRequest );
		}
		else
		{
			// ���N�G�X�g���Ȃ��Ȃ����̂ő҂���Ԃɂ���B
			m_pFileThread->resetWaitEvent();
		}
	}

	return 0;
}

/************************************************************************************************/
/*
* ���C������ĂԃR�[���o�b�N����
*/
/************************************************************************************************/
void KsFileSystem::callback()
{
	if( m_pCurrentRequest )
	{
		m_mutex.lock();
		
		m_pCurrentRequest->callback();
		
		m_mutex.unlock();
	}
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsHandle KsFileSystem::openAsync( const KsString& fileName, KsFileReadEndCB callback, void* pUserData, KsFileReadEndCB callbackTH, void* pUserDataTH )
{
	KsReadRequest*	pRequest = new KsReadRequest();

	if( !pRequest )
	{
		return NULL;
	}

	pRequest->m_status          = ksREADING_START;
	pRequest->m_fileName        = fileName;
	pRequest->m_callback        = callback;
	pRequest->m_pUserData       = pUserData;
	pRequest->m_callbackThread  = callbackTH;
	pRequest->m_pUserDataThread = pUserDataTH;

	/* ���N�G�X�g���L���[�ɂ��߂� */
	m_requestQueue.push( pRequest );

	return pRequest;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsHandle KsFileSystem::openAsync( const KsString& fileName, KsByte* pBuffer, KsInt32 size, KsFileReadEndCB callback, void* pUserData, KsFileReadEndCB callbackTH, void* pUserDataTH )
{
	KsReadRequest*	pRequest = new KsReadRequest();

	if( !pRequest )
	{
		return NULL;
	}

	pRequest->m_status          = ksREADING_START;
	pRequest->m_fileName        = fileName;
	pRequest->m_bufferFlag      = ksTRUE;
	pRequest->m_pBuffer         = pBuffer;
	pRequest->m_bufferSize      = size;
	pRequest->m_callback        = callback;
	pRequest->m_pUserData       = pUserData;
	pRequest->m_callbackThread  = callbackTH;
	pRequest->m_pUserDataThread = pUserDataTH;

	/* ���N�G�X�g���L���[�ɂ��߂� */
	m_requestQueue.push( pRequest );

	return pRequest;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
KsBool KsFileSystem::closeAsync( KsHandle handle )
{
	if( !handle ) return ksFALSE;

	KsReadRequest* pRequest = reinterpret_cast<KsReadRequest*>(handle);

	if( pRequest->m_fileHandle )
	{
		::CloseHandle( pRequest->m_fileHandle );
		pRequest->m_fileHandle = NULL;
	}

	ksDELETE( pRequest );

	return ksTRUE;
}

