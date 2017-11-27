#pragma once
class CLog
{
private:
	enum LOGTYPE {
		All = -1,
		None = 0,
		Console = 1,
		Trace = 2,
		File = 4,
	};

public:
	CLog();

	~CLog();

public:
	void Log(const CHAR* lpszFormat, ...);
	void EnableLogAll(bool isEnable) {
		if (isEnable) {
			m_nLogFlag = LOGTYPE::All;
		} else {
			m_nLogFlag = LOGTYPE::None;
		}
	}
	void EnableLogConsole(bool isEnable) {
		if (isEnable) {
			m_nLogFlag |= LOGTYPE::Console;
		} else {
			m_nLogFlag &= ~LOGTYPE::Console;
		}
	}
	void EnableLogTrace(bool isEnable) {
		if (isEnable) {
			m_nLogFlag |= LOGTYPE::Trace;
		} else {
			m_nLogFlag &= ~LOGTYPE::Trace;
		}
	}
	void EnableLogFile(bool isEnable) {
		if (isEnable) {
			m_nLogFlag |= LOGTYPE::File;
		} else {
			m_nLogFlag &= ~LOGTYPE::File;
		}
	}
	void SetLogFile(const CString &sFileName) {
		if (sFileName.IsEmpty() == FALSE && m_sLogFile.CompareNoCase(sFileName) != 0) {
			Close();
			m_sLogFile = sFileName;
			Open();
		}
	}

private:
	BOOL Open();
	void Close();
	BOOL LogFile(const CStringA&strMsg);

private:
	int		 m_nLogFlag;
	CStringW m_sLogFile;
	HANDLE m_hFile;

#ifdef _LINUX
	pthread_mutex_t		mutex_lock;
#endif
#ifdef WIN32
	CRITICAL_SECTION	m_cs;
#endif
};

extern CLog	g_log;
//#define LOG		g_log.Log("%s %s::%d", __FUNCTION__, __FILE__, __LINE__);
#define LOG(...)	g_log.Log(__VA_ARGS__);