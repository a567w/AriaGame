/************************************************************************************************/
/**
 * @file		KsBinaryReader.cpp
 * @brief		バイナリーリーダー
 * @author		Tsukasa Kato
 * @date		2004/03/30
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsEngine/KsEnginePreCompile.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/



/************************************************************************************************/
/*
 * コンストラクタ
 * @param		pFile			ファイルポインタ
 */
/************************************************************************************************/
KsBinaryReader::KsBinaryReader( const KsWChar* pFileName )
{
    size_t dataSize;

	readEntireFile( pFileName, &m_pData, &dataSize );

    m_pPos = m_pData;
    m_pEnd = m_pData + dataSize;
}

/************************************************************************************************/
/*
 * コンストラクタ
 * @param		pFile			ファイルポインタ
 */
/************************************************************************************************/
KsBinaryReader::KsBinaryReader( const KsSChar* pFileName )
{
    size_t dataSize;

	readEntireFile( pFileName, &m_pData, &dataSize );

    m_pPos = m_pData;
    m_pEnd = m_pData + dataSize;
}

/************************************************************************************************/
/*
 * コンストラクタ
 */
/************************************************************************************************/
KsBinaryReader::KsBinaryReader( const KsByte* dataBlob, KsUInt32 dataSize )
{
    m_pPos = dataBlob;
    m_pEnd = dataBlob + dataSize;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
HRESULT KsBinaryReader::readEntireFile( const KsWChar* fileName, KsByte** data, KsUInt32* dataSize )
{
    // Open the file.
#if (_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/)
	HANDLE hFile = CreateFile2(fileName, GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING, nullptr);
#else
    HANDLE hFile = CreateFileW(fileName, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
#endif

    if (!hFile)
        return HRESULT_FROM_WIN32(GetLastError());

    // Get the file size.
    LARGE_INTEGER fileSize = { 0 };

#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
    FILE_STANDARD_INFO fileInfo;

    if (!GetFileInformationByHandleEx(hFile, FileStandardInfo, &fileInfo, sizeof(fileInfo)))
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    fileSize = fileInfo.EndOfFile;
#else
    GetFileSizeEx(hFile, &fileSize);
#endif

    // File is too big for 32-bit allocation, so reject read.
    if (fileSize.HighPart > 0)
	{
        return E_FAIL;
	}

    // Create enough space for the file data.
    *data = ksNew KsByte[ fileSize.LowPart ];

    if( !*data )
	{
        return E_OUTOFMEMORY;
	}

    // Read the data in.
    DWORD bytesRead = 0;

    if (!ReadFile(hFile, *data, fileSize.LowPart, &bytesRead, nullptr))
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    if (bytesRead < fileSize.LowPart)
        return E_FAIL;

    *dataSize = bytesRead;
    
    return S_OK;
}

/************************************************************************************************/
/*
 *
 */
/************************************************************************************************/
HRESULT KsBinaryReader::readEntireFile( const KsSChar* pFileName, KsByte** data, KsUInt32* dataSize )
{
	KsWChar		wFileName[ MAX_PATH ];

	ks_mbstowcs( pFileName, wFileName, MAX_PATH );

#if (_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/)
	HANDLE hFile = CreateFile2( wFileName, GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING, nullptr );
#else
    HANDLE hFile = CreateFileW( wFileName, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );
#endif

    if (!hFile)
        return HRESULT_FROM_WIN32(GetLastError());

    // Get the file size.
    LARGE_INTEGER fileSize = { 0 };

#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
    FILE_STANDARD_INFO fileInfo;

    if (!GetFileInformationByHandleEx(hFile, FileStandardInfo, &fileInfo, sizeof(fileInfo)))
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    fileSize = fileInfo.EndOfFile;
#else
    GetFileSizeEx(hFile, &fileSize);
#endif

    // File is too big for 32-bit allocation, so reject read.
    if (fileSize.HighPart > 0)
	{
        return E_FAIL;
	}

    // Create enough space for the file data.
    *data = ksNew KsByte[ fileSize.LowPart ];

    if( !*data )
	{
        return E_OUTOFMEMORY;
	}

    // Read the data in.
    DWORD bytesRead = 0;

    if (!ReadFile(hFile, *data, fileSize.LowPart, &bytesRead, nullptr))
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    if (bytesRead < fileSize.LowPart)
        return E_FAIL;

    *dataSize = bytesRead;
    
    return S_OK;
}




