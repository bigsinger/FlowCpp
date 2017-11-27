#include "stdafx.h"
#include "Log.h"
#include "Utils.h"
#include "Const.h"

CLog	g_log;

CLog::CLog() {
	m_nLogFlag = LOGTYPE::Console;
	m_hFile = INVALID_HANDLE_VALUE;
	CString s = GetStartPath() + Const::Default_Log_File_Name;
	SetLogFile(s);

#ifdef _LINUX
	pthread_mutex_init(&mutex_lock, NULL);
#endif
#ifdef WIN32
	InitializeCriticalSection(&m_cs);
#endif
}


CLog::~CLog() {
	if (m_hFile != INVALID_HANDLE_VALUE) {
		Close();
	}
}

BOOL CLog::Open() {
	BOOL bSuccess = FALSE;
	DWORD dwWrite = 0;
	CString strText;
	BOOL bNewCreated = FALSE;

	//日志文件不存在则创建之
	if (GetFileAttributesW(m_sLogFile) == -1) {
		bNewCreated = TRUE;
	}
	m_hFile = CreateFileW(m_sLogFile, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, NULL, NULL);
	if (m_hFile != INVALID_HANDLE_VALUE) {
		//日志文件如果超过1M则清除下
		DWORD dwFileSize = GetFileSize(m_hFile, NULL);
		if (dwFileSize > 1024 * 1024) {
			SetFilePointer(m_hFile, 0, 0, FILE_BEGIN);
			SetEndOfFile(m_hFile);
		} else {
			SetFilePointer(m_hFile, 0, 0, FILE_END);
		}

		if (bNewCreated == TRUE) {
			WORD magic = 0xFEFF;
			::WriteFile(m_hFile, &magic, 2, &dwWrite, NULL);
		}

	}

	this->Log("init");
	return bSuccess;
}

void CLog::Close() {
	if (m_hFile != INVALID_HANDLE_VALUE) {
		this->Log("exit");
		CloseHandle(m_hFile);
		m_hFile = INVALID_HANDLE_VALUE;

#ifdef _LINUX
		pthread_mutex_destroy(&mutex_lock);
#endif
#ifdef WIN32
		DeleteCriticalSection(&m_cs);
#endif
	}
}

void CLog::Log(const CHAR* lpszFormat, ...) {
	if (m_nLogFlag != LOGTYPE::None && lpszFormat) {
		CStringA strText;
		va_list args;
		va_start(args, lpszFormat);
		strText.FormatV(lpszFormat, args);
		va_end(args);

		strText = GetCurrentTimeStr() + strText + "\r\n";

		if (this->m_nLogFlag & LOGTYPE::Console) {
			printf_s(strText);
		}
		if (this->m_nLogFlag & LOGTYPE::Trace) {
			OutputDebugStringA(strText);
		}
		if (this->m_nLogFlag & LOGTYPE::File) {
			this->LogFile(strText);
		}
	}
}

BOOL CLog::LogFile(const CStringA&strMsg) {
	BOOL bSuccess = FALSE;
	DWORD dwWrite = 0;
	if (m_hFile != INVALID_HANDLE_VALUE) {
#ifdef _LINUX
		thread_mutex_lock(&mutex_lock);
#endif
#ifdef _WIN32
		EnterCriticalSection(&m_cs);
#endif

		CStringW strTextW = strMsg;
		bSuccess = WriteFile(m_hFile, (LPCWSTR)strTextW, strTextW.GetLength() * sizeof(WCHAR), &dwWrite, NULL);

#ifdef _LINUX
		pthread_mutex_unlock(&mutex_lock);
#endif
#ifdef _WIN32
		LeaveCriticalSection(&m_cs);
#endif
	} else {

	}
	return bSuccess;
}